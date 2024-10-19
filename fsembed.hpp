#pragma once

#include <array>
#include <string_view>
#include <generator>


struct Entry
{
    std::string_view path;
    std::string_view name;
    std::string_view content;
};

struct Folder
{
    std::string_view path;
    std::string_view name;

    size_t start_idx;
    size_t end_idx;

    size_t folder_idx;
};

std::generator<const Entry&> getEntriesInFolder(const Folder& folder)
{
    for (size_t i = folder.start_idx; i <= folder.end_idx; i++)
    {
        co_yield entries[i];
    }
}

std::generator<const Folder&> getFoldersInFolder()
{
    for (const auto& folder : folder_entries)
    {
        co_yield folder;
    }
}

std::generator<const Entry&> getEntriesInFolderRecursive(const Folder& folder)
{
    for (size_t i = folder.start_idx; i <= folder.end_idx; i++)
    {
        co_yield entries[i];
    }
    for (const auto& subfolder : getFoldersInFolder())
    {
        for (const auto& entry : getEntriesInFolderRecursive(subfolder))
        {
            co_yield entry;
        }
    }
}

std::generator<const Folder&> getFoldersInFolderRecursive(const Folder& folder)
{
    co_yield folder;
    for (const auto& subfolder : getFoldersInFolder())
    {
        for (const auto& subsubfolder : getFoldersInFolderRecursive(subfolder))
        {
            co_yield subsubfolder;
        }
    }
}
