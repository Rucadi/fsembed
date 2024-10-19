
#pragma once
#include <span>
#include <coroutine>
#include <span>
#include <ranges>
#include <optional>
#include <string_view>



#ifndef FSEMBED_INTERNAL_DEF
#define FSEMBED_INTERNAL_DEF
namespace fsembed
{    
    struct Entry
    {
        std::string_view name;
        std::string_view content;
        const Entry* next;
    };

    struct Folder 
    {
        std::string_view path;
        const Entry* start;
        const Entry* end;
    };
}
#endif


namespace fsembed
{
    template <typename T>
    struct generator
    {
        // Inner class for coroutine promise type
        struct promise_type
        {
            std::optional<T> current_value;

            generator<T> get_return_object()
            {
                return generator{std::coroutine_handle<promise_type>::from_promise(*this)};
            }

            std::suspend_always initial_suspend() const noexcept
            {
                return {};
            }

            std::suspend_always final_suspend() const noexcept
            {
                return {};
            }

            std::suspend_always yield_value(T value) noexcept
            {
                current_value = std::move(value);
                return {};
            }

            void return_void() noexcept {}

            void unhandled_exception()
            {
                std::terminate(); // Handle exceptions by terminating the program
            }
        };

        using handle_type = std::coroutine_handle<promise_type>;

        explicit generator(handle_type h) : coro(h) {}
        generator(generator const &) = delete;
        generator(generator &&other) noexcept : coro(other.coro)
        {
            other.coro = nullptr;
        }

        ~generator()
        {
            if (coro)
                coro.destroy();
        }

        // Iterator class for the generator
        struct iterator
        {
            handle_type coro;

            iterator() noexcept : coro(nullptr) {}
            iterator(handle_type coro) : coro(coro) {}

            iterator &operator++()
            {
                coro.resume();
                if (coro.done())
                    coro = nullptr;
                return *this;
            }

            bool operator==(const iterator &other) const
            {
                return coro == other.coro;
            }

            bool operator!=(const iterator &other) const
            {
                return !(*this == other);
            }

            const T &operator*() const
            {
                return coro.promise().current_value.value();
            }

            const T *operator->() const
            {
                return &(operator*());
            }
        };

        iterator begin()
        {
            if (coro)
            {
                coro.resume();
                if (!coro.done())
                {
                    return iterator{coro};
                }
            }
            return iterator{nullptr};
        }

        iterator end()
        {
            return iterator{nullptr};
        }

    private:
        handle_type coro;
    };

    struct EntryWithPath
    {
        std::string_view path;
        const Entry *entry;
    };

    const fsembed::Folder *findFolder(std::span<const fsembed::Folder> folders, std::string_view path)
    {
        for (const auto &folder : folders)
            if (folder.path == path)
                return &folder;
        return nullptr;
    }

    generator<const fsembed::Entry *> getEntriesInFolder(const fsembed::Folder *folder)
    {
        for (const fsembed::Entry *entry = folder->start; entry != folder->end; entry = entry->next)
        {
            co_yield entry;
        }
    }

    fsembed::EntryWithPath findFile(std::span<const fsembed::Folder> folders, std::string_view path)
    {

        // find the folder
        std::string_view folder_path = path.substr(0, path.find_last_of('/'));
        const fsembed::Folder *folder = findFolder(folders, folder_path);
        if (folder == nullptr)
            return {};

        // find the file
        for (const fsembed::Entry *entry : getEntriesInFolder(folder))
        {
            if (entry->name == path.substr(path.find_last_of('/') + 1))
                return {folder_path, entry};
        }

        return {};
    }

    generator<fsembed::EntryWithPath> iterateFilesystem(std::span<const fsembed::Folder> folders)
    {
        // subspan folders to skip first and last element
        folders = folders.subspan(1, folders.size() - 2);
        for (const fsembed::Folder &current_folder : folders)
        {
            for (const fsembed::Entry *entry : getEntriesInFolder(&current_folder))
            {
                co_yield fsembed::EntryWithPath{current_folder.path, entry};
            }
        }
    }

    const fsembed::Folder *getParentFolder(const fsembed::Folder *folder)
    {
        std::string_view parent_path = folder->path.substr(0, folder->path.find_last_of('/'));
        while (folder->start != nullptr)
        {
            if (folder->path == parent_path)
                return folder;
            folder--;
        }

        return nullptr;
    }

    generator<const fsembed::Folder *> getSubfolders(const fsembed::Folder *folder)
    {

        std::string_view initial_path = folder->path;
        folder++;
        while (folder->path.starts_with(initial_path) && folder->start != nullptr)
        {
            co_yield folder;
            folder++;
        }
    }

    // get subfolders recursive
    generator<const fsembed::Folder *> getSubfoldersRecursive(const fsembed::Folder *folder)
    {
        for (const fsembed::Folder *subfolder : getSubfolders(folder))
        {
            co_yield subfolder;
            for (const fsembed::Folder *subsubfolder : getSubfoldersRecursive(subfolder))
            {
                co_yield subsubfolder;
            }
        }
    }

    generator<fsembed::EntryWithPath> getEntriesInFolderRecursive(const fsembed::Folder *folder)
    {
        for (const fsembed::Entry *entry : getEntriesInFolder(folder))
        {
            co_yield {folder->path, entry};
        }
        for (const fsembed::Folder *subfolder : getSubfolders(folder))
        {
            for (auto ewp : getEntriesInFolderRecursive(subfolder))
            {
                co_yield ewp;
            }
        }
    }

}
