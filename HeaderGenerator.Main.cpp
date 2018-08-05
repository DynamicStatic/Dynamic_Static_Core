
/*
==========================================
  Copyright (c) 2018-2018 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "Dynamic_Static/Core/File.hpp"
#include "Dynamic_Static/Core/FileSystem.hpp"
#include "Dynamic_Static/Core/StringUtilities.hpp"

#include <fstream>
#include <set>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

class File final
{
public:
    std::vector<std::string> dstIncludes;
    std::vector<std::string> stdIncludes;
    std::vector<std::string> lines;

public:
    File(
        const std::string& filePath,
        bool skipStdIncludeExtraction
    )
    {
        bool pragmaOnceFound = false;
        for (const auto& line : dst::File::read_all_lines(filePath)) {
            if (line == "#pragma once") {
                pragmaOnceFound = true;
                continue;
            }
            if (pragmaOnceFound) {
                if (line.find("#include") != std::string::npos) {
                    if (line.find("Dynamic_Static/Core/") != std::string::npos) {
                        auto include = dst::remove(dst::remove(line, "#include "), '"');
                        dstIncludes.push_back(include);
                    } else {
                        if (skipStdIncludeExtraction) {
                            lines.push_back(line);
                        } else {
                            stdIncludes.push_back(line);
                        }
                    }
                } else {
                    lines.push_back(line);
                }
            }
        }
        for (auto itr = lines.begin(); itr != lines.end(); ++itr) {
            if (itr->empty()) {
                auto jtr = itr + 1;
                while (jtr != lines.end() && jtr->empty()) {
                    lines.erase(jtr);
                    jtr = itr + 1;
                }
            }
        }
    }
};

void process_files(
    std::unordered_map<std::string, File>& unprocessedFiles,
    std::set<std::string>& processedFilePaths,
    std::vector<File>& processedFiles,
    const std::string& filePath,
    const File& file
)
{
    for (const auto& include : file.dstIncludes) {
        if (processedFilePaths.find(include) == processedFilePaths.end()) {
            auto dependency = unprocessedFiles.find(include);
            process_files(
                unprocessedFiles,
                processedFilePaths,
                processedFiles,
                dependency->first,
                dependency->second
            );
            if (processedFilePaths.insert(dependency->first).second) {
                processedFiles.push_back(dependency->second);
            }
        }
    }
    if (processedFilePaths.insert(filePath).second) {
        processedFiles.push_back(file);
    }
}

int main()
{
    static const std::set<std::string> ForceDefineSymbol {
        "#define _USE_MATH_DEFINES"
    };
    static const std::set<std::string> SkipStdIncludeExtraction {
        "Dynamic_Static/Core/Math/Defines.hpp",
        "Dynamic_Static/Core/Memory.hpp",
        "Dynamic_Static/Core/Win32LeanAndMean.hpp",
    };
    static const std::vector<std::string> ForceIncludeOrder {
        "Dynamic_Static/Core/Defines.hpp",
        "Dynamic_Static/Core/Math/Defines.hpp",
        "Dynamic_Static/Core/Win32LeanAndMean.hpp",
        "Dynamic_Static/Core/Memory.hpp",
    };
    std::ofstream dstCore(
        DYNAMIC_STATIC_CORE_INCLUDE_DIRECTORY DYNAMIC_STATIC ".Core.hpp"
    );
    dstCore <<
R"(
/*
==========================================
  Copyright (c) 2011-2018 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

)";
    for (const auto& symbol : ForceDefineSymbol) {
        dstCore << symbol << std::endl;
    }
    std::unordered_map<std::string, File> unprocessedFiles;
    std::set<std::string> stdIncludes;
    auto directoryPath = DYNAMIC_STATIC_CORE_INCLUDE_DIRECTORY DYNAMIC_STATIC;
    for (const auto& directoryEntry : dst::filesystem::recursive_directory_iterator(directoryPath)) {
        if (dst::filesystem::is_regular_file(directoryEntry)) {
            std::string fullPath = directoryEntry.path().string();
            auto relativePath = dst::scrub_path(fullPath);
            relativePath = dst::remove(relativePath, DYNAMIC_STATIC_CORE_INCLUDE_DIRECTORY);
            bool skipStdIncludeExtraction = SkipStdIncludeExtraction.find(relativePath) != SkipStdIncludeExtraction.end();
            auto& file = unprocessedFiles.insert({ relativePath, File(fullPath, skipStdIncludeExtraction) }).first->second;
            for (const auto& stdInclude : file.stdIncludes) {
                stdIncludes.insert(stdInclude);
            }
        }
    }
    for (const auto& stdInclude : stdIncludes) {
        dstCore << stdInclude << std::endl;
    }
    std::set<std::string> processedFilePaths;
    std::vector<File> processedFiles;
    for (const auto& filePath : ForceIncludeOrder) {
        auto itr = unprocessedFiles.find(filePath);
        processedFilePaths.insert(itr->first);
        processedFiles.push_back(itr->second);
    }
    for (auto itr : unprocessedFiles) {
        process_files(
            unprocessedFiles,
            processedFilePaths,
            processedFiles,
            itr.first,
            itr.second
        );
    }
    for (const auto& file : processedFiles) {
        bool populated = false;
        std::stringstream strStrm;
        for (const auto& line : file.lines) {
            if (ForceDefineSymbol.find(line) == ForceDefineSymbol.end()) {
                strStrm << line << std::endl;
            }
            if (!line.empty()) {
                populated = true;
            }
        }
        if (populated) {
            dstCore << strStrm.str();
        }
    }
    return 0;
}
