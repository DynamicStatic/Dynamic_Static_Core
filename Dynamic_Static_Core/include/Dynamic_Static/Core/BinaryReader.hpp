
/*
=====================================================================================

    The MIT License(MIT)

    Copyright(c) 2016 to this->moment()->next() Dynamic_Static

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

#include "Dynamic_Static/Core/Defines.hpp"
#include "Dynamic_Static/Core/NonCopyable.hpp"

#include <string>
#include <vector>
#include <fstream>

namespace Dynamic_Static {
    /**
     * Provides high level control over read operations on binary files.
     */
    class BinaryReader
        : NonCopyable {
    private:
        size_t m_size { 0 };
        std::ifstream m_file_stream;

    public:
        /**
         * Constructs an instance of BinaryReader.
         */
        BinaryReader() = default;

        /**
         * Constructs an instance of BinaryReader.
         * \n Exception - std::runtime_error : The specified file couldn't be opened
         * @param [in] file_path The file path to construct this BinaryReader with.
         */
        BinaryReader(const std::string& file_path);

        /**
         * Moves an instance of BinaryReader.
         * @param [in] other The BniaryReader to move from
         */
        BinaryReader(BinaryReader&& other) = default;

        /**
         * Moves an instance of BinaryReader.
         * @param [in] other The BniaryReader to move from
         */
        BinaryReader& operator=(BinaryReader&& other) = default;

    public:
        /**
         * Gets the size in bytes of the file being read by this BinaryReader.
         * @return The size in bytes of the file being read by this BinaryReader
         */
        size_t size() const;

        /**
         * Gets this BinaryReader's postion in the file being read.
         * @return This BinaryReader's postion in the file being read.
         */
        size_t position() const;

        /**
         * Sets this BinaryReader's position in the file being read.
         * \n Exception - std::runtime_error : The position exceeds the size of the file being read
         * @param [in] position The byte to set this BinaryReader's position to
         */
        void position(size_t position);

        /**
         * Sets this BinaryReader's position to a specified offset from a specified position.
         * \n Exception - std::runtime_error : The position after the offset exceeds the size of the file being read
         * \n Exception - std::runtime_error : The position after the offset is negative
         */
        void seek(size_t offset, std::ios::seekdir seek_origin = std::ios::beg);

        /**
         * Opens a file to begin reading.
         * \n Exception - std::runtime_error :  The specified file couldn't be opened
         * @param [in] file_path The path to the file to open
         */
        void open(const std::string& file_path);

        /**
         * Closes the file.
         */
        void close();

        /**
         * Extacts an object of a specfied type from this BinaryReader's file without advancing the position in the file.
         * \n Exception - std::runtime_error : Attempted to read past the end of the file
         * @param <T> The type of object to extract
         * @return The extracted object
         */
        template <typename T>
        T peek()
        {
            T value { };
            return extract(false, 1, &value);
        }

        /**
         * Extracts a specified number of objects of a specified type from this BinaryReader's file without advancing the position in the file.
         * \n Exception - std::runtime_error : Attempted to read past the end of the file
         * @param <T>   The type of objects to extract
         * @param count The number of objects to extract
         * @return The extracted objects
         */
        template <typename T>
        std::vector<T> peek(size_t count)
        {
            std::vector<T> data;
            return peek(count, data);
        }

        /**
         * Extracts a specified number of objects of a specified type from this BinaryReader's file without advancing the position in the file.
         * \n Exception - std::runtime_error : Attempted to read past the end of the file
         * @param <T>   The type of objects to extract
         * @param count The number of objects to extract
         * @param data  The std::vector that will be populated with the extracted objects
         */
        template <typename T>
        std::vector<T>& peek(size_t count, std::vector<T>& data)
        {
            data.resize(count);
            extract(false, count, data.data());
            return data;
        }

        /**
         * Extracts an object of a specfied type from this BinaryReader's file without.
         * \n Exception - std::runtime_error : Attempted to read past the end of the file
         * @param <T> The type of object to extract
         * @return The extracted object
         */
        template <typename T>
        T read()
        {
            T value { };
            return extract(true, 1, &value);
        }

        /**
         * Extracts a specified number of objects of a specified type from this BinaryReader's file.
         * \n Exception - std::runtime_error : Attempted to read past the end of the file
         * @param <T>   The type of objects to extract
         * @param count The number of objects to extract
         * @return The extracted objects
         */
        template <typename T>
        std::vector<T> read(size_t count)
        {
            std::vector<T> data;
            return extract(true, count, data);
        }

        /**
         * Extracts a specified number of objects of a specified type from this BinaryReader's file.
         * \n Exception - std::runtime_error : Attempted to read past the end of the file
         * @param <T>   The type of objects to extract
         * @param count The number of objects to extract
         * @param data  The std::vector that will be populated with the extracted objects
         */
        template <typename T>
        std::vector<T>& read(size_t count, std::vector<T>& data)
        {
            data.resize(count);
            extract(true, count, data.data());
            return data;
        }

        /**
         * Gets the contents of the file being read by this BinaryReader.
         * @param <T> The type to recieve the file contents as
         *            \n Default : uint8_t
         * @return The contents of the file being read by this BinaryReader
         */
        template <typename T = uint8_t>
        std::vector<T> contents()
        {
            std::vector<T> data;
            size_t current_position = position();
            position(0);
            read(m_size / sizeof(T), data);
            position(current_position);
            return data;
        }

    private:
        template <typename T>
        void extract(bool advance_file_position, size_t count, T* data)
        {
            if (count && m_file_stream.is_open()) {
                size_t size = sizeof(T) * count;
                if (position() + size > m_size) {
                    throw std::runtime_error("Attempted to read past the end of the file");
                }

                size_t current_position = position();
                m_file_stream.read(reinterpret_cast<char*>(data), size);
                if (!advance_file_position) {
                    position(current_position);
                }
            }
        }
    };
}
