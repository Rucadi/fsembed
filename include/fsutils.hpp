#pragma once
#include "fsembed.hpp"
#include <span>
#include <coroutine>
#include "generator.hpp"
#include <span>
#include <ranges>

#include <iostream>

namespace fsembed
{
    struct EntryWithPath {
        std::string_view path;
        const Entry* entry;
    };




const fsembed::Folder* findFolder(std::span<const fsembed::Folder> folders, std::string_view path)
{
    for (const auto& folder : folders)
        if (folder.path == path)
            return &folder;
    return nullptr;
}


generator<const fsembed::Entry*> getEntriesInFolder(const fsembed::Folder* folder)
{
    for (const fsembed::Entry* entry = folder->start; entry != folder->end; entry=entry->next)
    {
        co_yield entry;
    }
}

fsembed::EntryWithPath findFile(std::span<const fsembed::Folder> folders, std::string_view path)
{
    
    //find the folder 
    std::string_view folder_path = path.substr(0, path.find_last_of('/'));
    const fsembed::Folder* folder = findFolder(folders, folder_path);
    if (folder == nullptr)
        return {};
    
    //find the file
    for(const fsembed::Entry* entry : getEntriesInFolder(folder))
    {
        if (entry->name == path.substr(path.find_last_of('/')+1))
            return {folder_path, entry};
    }

    return {};
}

generator<fsembed::EntryWithPath> iterateFilesystem(std::span<const fsembed::Folder> folders)
{
    //subspan folders to skip first and last element
    folders = folders.subspan(1, folders.size()-2);
    for (const fsembed::Folder& current_folder : folders)
    {
        for(const fsembed::Entry* entry : getEntriesInFolder(&current_folder))
        {
            co_yield fsembed::EntryWithPath{current_folder.path, entry};
        }
    }
}

const fsembed::Folder* getParentFolder(const fsembed::Folder* folder)
{
    std::string_view parent_path = folder->path.substr(0, folder->path.find_last_of('/'));
    while(folder->start != nullptr)
    {
        if (folder->path == parent_path)
            return folder;
        folder--;
    }

    return nullptr;
}

generator<const fsembed::Folder*> getSubfolders(const fsembed::Folder* folder)
{
    
    std::string_view initial_path = folder->path;
    folder++;
    while (folder->path.starts_with(initial_path) && folder->start != nullptr)
    {
        co_yield folder;
        folder++;
    }
}

//get subfolders recursive
generator<const fsembed::Folder*> getSubfoldersRecursive(const fsembed::Folder* folder)
{
    for (const fsembed::Folder* subfolder : getSubfolders(folder))
    {
        co_yield subfolder;
        for (const fsembed::Folder* subsubfolder : getSubfoldersRecursive(subfolder))
        {
            co_yield subsubfolder;
        }
    }
}

generator<fsembed::EntryWithPath> getEntriesInFolderRecursive(const fsembed::Folder* folder)
{
    for (const fsembed::Entry* entry : getEntriesInFolder(folder))
    {
        co_yield {folder->path, entry};
    }
    for (const fsembed::Folder* subfolder : getSubfolders(folder))
    {   
        for(auto ewp : getEntriesInFolderRecursive(subfolder))
        {
            co_yield ewp;
        }
    }
}


}