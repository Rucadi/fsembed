#include "fsembed_filesystems/example/include.hpp"
#include <iostream>
#include "include/fsembed.hpp"

int main()
{
    for(const auto [path, entry] : fsembed::iterateFilesystem(example::folders))
    {
        std::cout<<"Path: "<<path<<"  "<<entry->name<<std::endl;
        std::cout<<"Content: "<<entry->content<<std::endl;
    }
}