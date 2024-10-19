
#pragma once

#ifndef FSEMBED_INTERNAL_DEF
#define FSEMBED_INTERNAL_DEF
#include <string_view>
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