
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

#include "Dynamic_Static/Core/BinaryReader.hpp"

namespace Dynamic_Static {
    BinaryReader::BinaryReader(const std::string& file_path)
    {
        // TODO : Is BinaryReader doing too much by opening and managing the file?
        //        Should BinaryReader accept an std::ifstream that must be managed
        //        externally?  It does make it easier to automate reads and file
        //        traversal when we can make assumptions about the state of the
        //        std::ifstream that we're using.
        open(file_path);
    }

    size_t BinaryReader::size() const { return m_size; }

    size_t BinaryReader::position() const
    {
        size_t position = 0;
        if (m_file_stream.is_open()) {
            // NOTE : We're doing a const_cast() here because tellg()
            //        isn't const, but we want position() to be const.
            //        This const_cast() is unsafe until we're handling
            //        all std::basic_ios::exceptions and failure states.
            auto file_stream_ptr = const_cast<std::ifstream*>(&m_file_stream);
            position = file_stream_ptr->tellg();
        }

        return position;
    }

    void BinaryReader::position(size_t position)
    {
        seek(position);
    }

    void BinaryReader::seek(size_t offset, std::ios::seekdir seek_origin)
    {
        if (m_file_stream.is_open()) {
            switch (seek_origin) {
                case std::ios::beg: {
                    if (offset > m_size) {
                        throw std::runtime_error(
                            "File size is " + std::to_string(m_size) + "; an offset of " + std::to_string(offset) + " from the beginning of the file exceeds the file size"
                        );
                    }
                } break;

                case std::ios::cur: {
                    if (position() + offset > m_size) {
                        throw std::runtime_error(
                            "File size is " + std::to_string(m_size) + "; an offset of " + std::to_string(offset) + " from the current position (" + std::to_string(position()) + ") exceeds the file size"
                        );
                    }
                } break;

                case std::ios::end: {
                    if (offset > m_size) {
                        throw std::runtime_error(
                            "File size is " + std::to_string(m_size) + "; an offset of " + std::to_string(offset) + " from the end of the file results in a negative position"
                        );
                    }
                } break;
            }

            m_file_stream.seekg(offset, seek_origin);
        }
    }

    void BinaryReader::open(const std::string& file_path)
    {
        close();
        m_file_stream.open(file_path, std::ios::binary | std::ios::ate);
        if (m_file_stream.is_open()) {
            // TODO : Need to set the exception mask and correctly respond to failure states.
            m_size = position();
            position(0);
        } else {
            throw std::runtime_error("File @ \"" + file_path + "\" couldn't be opened");
        }
    }

    void BinaryReader::close()
    {
        m_file_stream.close();
        m_size = 0;
    }

    std::vector<uint8_t> BinaryReader::contents()
    {
        std::vector<uint8_t> file_contents;
        size_t current_position = position();
        position(0);
        read(m_size, file_contents);
        position(current_position);
        return file_contents;
    }
}
