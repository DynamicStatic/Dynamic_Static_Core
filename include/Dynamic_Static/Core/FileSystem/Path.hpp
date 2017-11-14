
/*
==========================================
    Copyright (c) 2017 Dynamic_Static
    Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "Dynamic_Static/Core/Defines.hpp"

#include "gsl/span"

#include <string>

namespace Dynamic_Static {
namespace Path {

    /**
     * Scrubs a given path.
     * @param [in] path The path to scrub
     * @reutrn The scrubbed path
     */
    std::string scrub(const std::string& path);

    /**
     * Gets the absolute path from a path relative to the current working directory.
     * @param [in] path The relative path to get the absolute path for
     * @return The absolute path
     */
    std::string absolute(const std::string& path);

    /**
     * Combines two paths.
     * @param [in] path0 The first path
     * @param [in] path1 The second path
     * @return The combined path
     */
    std::string combine(const std::string& path0, const std::string& path1);

    /**
     * Combines multiple paths.
     * @param [in] paths The paths to combine
     * @return The combined path
     */
    std::string combine(gsl::span<const std::string> paths);

    /**
     * Gets a value indicating whether or not a given path has a file extension.
     * @param [in] path The path to check for a file extension
     * @return Whether or not the given path has a file extension
     */
    bool has_extension(const std::string& path);

    /**
     * Gets the file extension of a given path.
     * @param [in] path The path to get the file extension from
     * @return The file extension of the given path
     */
    std::string extension(const std::string& path);

    /**
     * Removes the file extension from a given path.
     * @param [in]           path      The path to remove the file extension from
     * @param [in, optional] recursive Whether or not to remove all '.' separated file extensions (default = false)
     * @return The path the file extension removed
     */
    std::string remove_extension(const std::string& path, bool recursive = false);

    /**
     * Gets the file name and extension of a given path.
     * @param [in] path The path to get the file name and extension from
     * @return The file name and extension of the given path
     */
    std::string file_name(const std::string& path);

    /**
     * Gets the directory name of the given path.
     * @param [in] path The path to get the directory name from
     * @return The directory name of the given path
     */
    std::string directory_name(const std::string& path);

} // namespace Path
} // namespace Dynamic_Static
