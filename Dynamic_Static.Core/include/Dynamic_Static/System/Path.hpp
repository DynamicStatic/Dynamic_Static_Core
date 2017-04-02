
/*
=====================================================================================

    The MIT License(MIT)

    Copyright(c) 2017 to this->moment()->next() Dynamic_Static

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files(the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions :

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
    THE SOFTWARE.

=====================================================================================
*/

#pragma once

#include "Dynamic_Static/Core/Collection.hpp"
#include "Dynamic_Static/System/Defines.hpp"

#include <string>

namespace Dynamic_Static {
    namespace System {
        namespace Path {
            /**
             * Scrubs an std::string containing a path.
             * @param [in] path The path to scrub
             * @return The scrubbed path
             */
            std::string scrub(const std::string& path);

            /**
             * Combines two std::strings into a single path.
             * @param [in] path0 The first path
             * @param [in] path1 The second path
             * @return The combined path
             */
            std::string combine(const std::string& path0, const std::string& path1);

            /**
             * Combines a Collection<std::string> into a single path.
             * @param  [in] paths The paths to combine
             * @return The combined path
             */
            std::string combine(const Collection<std::string>& paths);

            /**
             * Gets the file extension of a specified path.
             * @param [in] path The path to get the file extension from
             * @return The file extension of the specified path
             */
            std::string extension(const std::string& path);

            /**
             * Gets a value indicating whether or not the specified path has a file extension.
             * @param [in] path The path to check for a file extension
             * @return Whether or not the specified path has a file extension
             */
            bool has_extension(const std::string& path);

            /**
             * Gets the file name and extension of the specified path.
             * @param [in] path The path to get the file name and extension from
             * @return The file name and extension of the specified path
             */
            std::string file_name(const std::string& path);

            /**
             * Gets the directory name of the specified path.
             * @param [in] path The path to get the directory name from
             * @return The directory name of the specified path
             */
            std::string directory(const std::string& path);
        } // namespace Path
    } // namespace System
} // namespace Dynamic_Static
