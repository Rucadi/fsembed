#include <iostream>
#include <filesystem>
#include <vector>
#include <string_view>
#include <string>
#include <queue>
#include <fstream>
#include <format>
#include <ranges>
#include <set>
#include <deque>


constexpr auto Makefile = []{
		static constexpr char _sbo[]{
			#embed "embeddings/Makefile"
		};
		return std::string_view{_sbo, sizeof(_sbo)};
	}();

constexpr auto fsembed_internal = []{
		static constexpr char _sbo[]{
			#embed "embeddings/fsembed_internal.hpp"
		};
		return std::string_view{_sbo, sizeof(_sbo)};
	}();

constexpr auto fsembed_hpp = []{
		static constexpr char _sbo[]{
			#embed "embeddings/fsembed.hpp"
		};
		return std::string_view{_sbo, sizeof(_sbo)};
	}();

struct Entry
{
    std::string path;
    std::string name;
    size_t size;
    size_t folder_idx;
};

struct Folder
{
    std::string path;
    std::string name;

    size_t start_idx;
    size_t end_idx;
};


std::string static_embed_view_initializer(std::string_view filename)
{
    std::string result;
        result += "\t[]{\n";
            result += "\t\tstatic constexpr char _sbo[]{\n";
                result += "\t\t\t#embed \"" + std::string(filename) + "\"\n";
            result += "\t\t};\n";
            result += "\t\treturn std::string_view{_sbo, sizeof(_sbo)};\n";
        result += "\t}()\n";
    return result;
}


std::string end_sentinel(size_t idx){
    return "const Entry _"+std::to_string(idx)+"{ \"\", \"\", nullptr};\n";
}

std::string entry_declaration(const Entry& entry, size_t idx, bool is_relative, bool is_last)
{
    std::string result = "";
    std::string next = "&_"+std::to_string(idx+1);
    if (is_last) {
        result += end_sentinel(idx+1);
    }
    
    std::string sidx = std::to_string(idx); 
    std::string path = entry.path + "/" + entry.name;
    if (is_relative)
        path = "../../" + path;
    else 
        path = std::filesystem::absolute(path).string();
    result += "const Entry _" + sidx + "{ ";
    result += "\"" + entry.name + "\",\n";
    result += static_embed_view_initializer(path);
    result +=", " +  next;
    result += "};";
    return result;
}

struct output_file{
    std::string path;   
    std::deque<std::string> file_contents;

    void push_front(const std::string& line)
    {
        file_contents.push_front(line);
    }

    void push_back(const std::string& line)
    {
        file_contents.push_back(line);
    }

    void realize()
    {
        std::filesystem::create_directories(std::filesystem::path(path).parent_path());
        std::ofstream file(path);
        for(auto& line : file_contents)
        {
            file<<line<<std::endl;
        }
    }
};

void compile(std::vector<Entry>& entries, 
            std::vector<Folder>& folders, 
            const std::string_view nspace = "my_namespace", 
            std::filesystem::path output_dir = "fsembed_filesystems",
            bool is_relative = true)
{

    auto full_path = output_dir / nspace;
    if (std::filesystem::exists(full_path))
    {
        std::filesystem::remove_all(full_path);
    }
    
    std::filesystem::create_directories(full_path);

    //Generate all the file entries
    size_t accum_size = 0;
    size_t max_size = 1024 * 1024 * 10;
    std::ofstream entry_file;
    std::vector<output_file> output_entries_cpp = {};
    size_t current_size = max_size;
    bool last = true;
    for(auto [idx, entry] : entries  | std::views::enumerate  | std::views::reverse  )
    {
        if (current_size + entry.size >= max_size)
        {
            output_entries_cpp.push_back(output_file{output_dir / nspace / (std::to_string(idx)+".cpp"), {}});
            current_size = 0;
        }
        output_entries_cpp.back().push_back(entry_declaration(entry, idx, is_relative, last));
        current_size += entry.size;
        last = false;
    }


    for(auto& file : output_entries_cpp)
    {
        file.push_front("namespace "+std::string(nspace)+"{");
        file.push_front(R"(
#include <string_view>
#include "extern_defs.hpp"
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc23-extensions"
            )");
        
        file.push_back(R"(
}
#pragma clang diagnostic pop
)");
        file.realize();
    }
    /////////////////////////////////////////

    //extern_defs.hpp header
    output_file compile_header{output_dir / nspace / "extern_defs.hpp", {}};
    compile_header.push_front("#pragma once");
    compile_header.push_back("#include \"fsembed_internal.hpp\"");
    compile_header.push_back("using fsembed::Entry;");
    compile_header.push_back("using fsembed::Folder;");
    compile_header.push_back("namespace "+std::string(nspace)+"{");
    for(auto [idx, entry] : entries | std::views::enumerate  )
    {
        std::string sidx = std::to_string(idx);
        compile_header.push_back("extern const Entry _" + sidx + ";");
    }
    compile_header.push_back("extern const Entry _" + std::to_string(entries.size())  + ";");
    compile_header.push_back("}");
    compile_header.realize();
    /////////////////////////////////////////


    // Generate all folder entries
    output_file compile_folders{output_dir / nspace / "folders.cpp", {}};
    compile_folders.push_back("#include \"extern_defs.hpp\"");
    compile_folders.push_back("#include \"include.hpp\"");
    compile_folders.push_back("namespace "+std::string(nspace)+"{");
    
    compile_folders.push_back("const std::array<Folder, " + std::to_string(folders.size()+2) + "> folders{");
    compile_folders.push_back("Folder{ \"\", nullptr, nullptr},");
    for (auto [idx, folder] : folders | std::views::enumerate)
    {
        std::string sidx = std::to_string(idx);
        compile_folders.push_back("Folder{\"" + folder.path + "\", &_" + std::to_string(folder.start_idx) + ", &_" + std::to_string(folder.end_idx) + "},");
    }
    compile_folders.push_back("Folder{ \"\", nullptr, nullptr},");
    compile_folders.push_back("};");
    compile_folders.push_back("}");
    compile_folders.realize();


    // Generate the include file, it just has the array of folders and the namespace
    output_file compile_include{output_dir / nspace / "include.hpp", {}};
    compile_include.push_back("#pragma once");
    compile_include.push_back("#include <array>");
    compile_include.push_back("#include \"fsembed_internal.hpp\"");
    compile_include.push_back("namespace "+std::string(nspace)+"{");
    compile_include.push_back("extern const std::array<fsembed::Folder, " + std::to_string(folders.size()+2) + "> folders;");
    compile_include.push_back("}");
    compile_include.realize();

    output_file internal_include{output_dir / nspace / "fsembed_internal.hpp", {}};
    internal_include.push_back(fsembed_internal.data());
    internal_include.realize();

    // Generate the Makefile
    output_file makefile{output_dir / nspace / "Makefile", {}};
    makefile.push_back(Makefile.data());
    makefile.realize();

}


std::vector<Entry> entries;
std::vector<Folder> folder_entries;


std::pair<std::vector<std::string>, std::vector<std::string> > get_folders_and_files(const std::string& path)
{
    std::vector<std::string> folders;
    std::vector<std::string> files;

    for (const auto& entry : std::filesystem::directory_iterator(path))
    {
        if (entry.is_directory())
        {
            folders.push_back(entry.path().filename().string());
        }
        else if (entry.is_regular_file())
        {
            files.push_back(entry.path().filename().string());
        }
    }

    return {folders, files};
}



int main(int argc, char** argv)
{
    // Read folder and name from command line
    if (argc < 3)
    {
        std::cerr << "Usage: " << argv[0] << " <directory> <name> [--absolute] [--maintain-root]\n";
        return 1;
    }

    std::filesystem::path path = argv[1];
    std::string folder_name = argv[2];
    std::set<std::string> flags;
    for (int i = 3; i < argc; ++i)
    {
        flags.insert(argv[i]);
    }

    if (!std::filesystem::exists(path))
    {
        std::cerr << "Error: " << path << " does not exist.\n";
        return 1;
    }

    if (!std::filesystem::is_directory(path))
    {
        std::cerr << "Error: " << path << " is not a directory.\n";
        return 1;
    }

    std::deque<std::string> folders;
    folders.push_front(path.string());
    while(!folders.empty())
    {
        auto current_path = folders.front();
        folders.pop_front();
        auto [subfolders, files] = get_folders_and_files(current_path);
        for (const auto& folder : subfolders)
        {
            folders.push_front(current_path + "/" + folder);
        }


        Folder folder_entry;
        if (folder_entries.empty())
        {
            folder_entry.start_idx = 0;
            folder_entry.end_idx = files.size();
        }
        else
        {
            folder_entry.start_idx = folder_entries.back().end_idx;
            folder_entry.end_idx = folder_entry.start_idx + files.size();
        }


        if (flags.count("--maintain-root"))
        {
            folder_entry.path = current_path;
        }
        else
        {
            folder_entry.path = std::filesystem::relative(current_path, path).string();
            //if path is "." then set "/" as the path
            if (folder_entry.path == ".")
            {
                folder_entry.path = "/";
            }
        }

        folder_entries.push_back(folder_entry);
        for (const auto& file : files)
        {
            Entry entry;
            entry.path = current_path;
            entry.name = file;
            entry.size = std::filesystem::file_size(current_path + "/" + file);
            entry.folder_idx = folder_entries.size() - 1;
            entries.push_back(entry);
        }
    }

    std::cout<<"Compiling "<<entries.size()<<" entries and "<<folder_entries.size()<<" folders\n";
    compile(entries, folder_entries, folder_name, "fsembed_filesystems", !flags.count("--absolute"));

    output_file fsembed_hpp_file{"include/fsembed.hpp", {}};
    fsembed_hpp_file.push_back(fsembed_hpp.data());
    fsembed_hpp_file.realize();
}