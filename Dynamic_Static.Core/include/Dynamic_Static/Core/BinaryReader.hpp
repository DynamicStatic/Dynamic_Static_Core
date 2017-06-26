
/*
================================================================================

  MIT License

  Copyright (c) 2016 Dynamic_Static

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.

================================================================================
*/

#include "Dynamic_Static/Core/Defines.hpp"
#include "Dynamic_Static/Core/NonCopyable.hpp"

#include <string>
#include <vector>
#include <fstream>

namespace Dynamic_Static
{
    /**
     * Provides high level control over read operations on binary files.
     */
    class BinaryReader
        : NonCopyable
    {
    private:
        size_t mSize { 0 };
        std::ifstream mFileStream;

    public:
        /**
         * Constructs an instance of BinaryReader.
         */
        BinaryReader() = default;

        /**
         * Constructs an instance of BinaryReader.
         * @param [in] filePath The path of the binary file to open for reading
         * \n Exception - std::runtime_error : File couldn't be opened
         */
        BinaryReader(const std::string& filePath);

        /**
         * Moves an instance of BinaryReader.
         * @param [in] other The BinaryReader to move from
         */
        BinaryReader(BinaryReader&& other) = default;

        /**
         * Moves an instance of BinaryReader.
         * @param [in] other The BinaryReader to move from
         */
        BinaryReader& operator=(BinaryReader&& other) = default;

    public:
        /**
         * Gets the size in bytes of the file being read by this BinaryReader.
         * @return The size in bytes of the file being read by this BinaryReader
         */
        size_t size() const;

        /**
         * Gets this BinaryReader's position in the file being read.
         * @return This BinaryReader's position in the file being read
         */
        size_t position() const;

        /**
         * Sets this BinaryReader's position in the file being read.
         * @param [in] position This BinaryReader's position in the file being read
         * \n Exception - std::runtime_error : offset exceeds file size
         */
        void position(size_t position);

        /**
         * Sets this BinaryReader's position to a given offset from a given origin.
         * @param [in]           offset The number of bytes to seek from the given origin
         * @param [in, optional] origin The position to seek from (default = std::ios::cur)
         * \n Exception - std::runtime_error : offset exceeds file size
         * \n Exception - std::runtime_error : offset from current position exceeds file size
         * \n Exception - std::logic_error   : A value besides std::ios::beg, std::ios::cur, or set::ios::end was given for origin
         */
        void seek(size_t offset, std::ios::seekdir origin = std::ios::cur);

        /**
         * Opens a file for reading.
         * @param [in] filePath The path of the binary file to open for reading
         * \n Exception - std::runtime_error : File couldn't be opened
         */
        void open(const std::string& filePath);

        /**
         * Closes the file being read.
         */
        void close();

        /**
         * Reads a given number of elements of a given type into a preallocated buffer.
         * @param <T>        The type of elements to read
         * @param [in] data  The address of the buffer to write the read elements into
         * @param [in] count The number of elements to read
         */
        template <typename T>
        void read(T* data, size_t count)
        {
            if (mFileStream.is_open() && data && count) {
                size_t dataSize = sizeof(T) * count;
                if (position() + dataSize > size()) {
                    throw std::runtime_error("Attempted to read past the end of the file");
                }

                mFileStream.read(reinterpret_cast<char*>(data), dataSize);
            }
        }

        /**
         * Reads a single element of a given type.
         * @param <T> The type of element to read
         * @return The element read
         */
        template <typename T>
        T read()
        {
            T value { };
            read(&value, 1);
            return value;
        }

        /**
         * Peeks a given number of elements of a given type into a preallocated buffer.
         * @param <T>        The type of elements to peek
         * @param [in] data  The address of the buffer to write the peeked elements into
         * @param [in] count The number of elements to peek
         */
        template <typename T>
        void peek(T* data, size_t count)
        {
            size_t currentPosition = position();
            read(data, count);
            position(currentPosition);
        }

        /**
         * Peeks a single element of a given type.
         * @param <T> The type of element to peek
         * @return The element read
         */
        template <typename T>
        T peak()
        {
            T value { };
            peek(&value, 1);
            return value;
        }

        /**
         * Populates a std::vector with the contents of this BinaryFile's interpreted as a given type.
         * @param <T>       The type to interpret this BinaryFile's contents as (optional = uint8_t)
         * @param [in] data The std::vector to populate with this BinaryFile's contents
         */
        template <typename T = uint8_t>
        void contents(std::vector<T>& data)
        {
            data.clear();
            size_t currentPosition = position();
            position(0);
            read(data.data(), size() / sizeof(T));
            position(currentPosition);
        }

        /**
         * Gets a std::vector populated with the contents of this BinaryFile's interpreted as a given type.
         * @param <T> The type to interpret this BinaryFile's contents as (optional = uint8_t)
         * @return The std::vector populated with this BinaryFile's contents
         */
        template <typename T = uint8_t>
        std::vector<T> contents()
        {
            std::vector<T> data;
            contents(data);
            return data;
        }
    };
} // namespace Dynamic_Static
