
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
    BinaryReader::BinaryReader(const std::string& filePath)
    {
        // TODO : Is BinaryReader doing too much by opening and managing the file?
        //        Should BinaryReader accept an std::ifstream that must be managed
        //        externally?  It does make it easier to automate reads and file
        //        traversal when we can make assumptions about the state of the
        //        std::ifstream that we're using.
        open(filePath);
    }

    size_t BinaryReader::size() const { return mSize; }

    size_t BinaryReader::position() const
    {
        size_t position = 0;
        if (mFileStream.is_open()) {
            // NOTE : We're doing a const_cast() here because tellg()
            //        isn't const, but we want position() to be const.
            //        This const_cast() is unsafe until we're handling
            //        all std::basic_ios::exceptions and failure states.
            //        It's worth noting that m_file_stream's constness
            //        is self imposed here for the sake of position()...
            //        this const_cast doesn't violate anything in ::std.
            // NOTE : const_cast should probably be preferred over mutable.
            //        Scalpel vs sledgehammer...
            auto fileStreamPtr = const_cast<std::ifstream*>(&mFileStream);
            position = static_cast<size_t>(fileStreamPtr->tellg());
        }

        return position;
    }

    void BinaryReader::position(size_t position)
    {
        seek(position);
    }

    void BinaryReader::seek(size_t offset, std::ios::seekdir seekOrigin)
    {
        if (mFileStream.is_open()) {
            switch (seekOrigin) {
                case std::ios::beg: {
                    if (offset > mSize) {
                        throw std::runtime_error(
                            "File size is " + std::to_string(mSize) + "; an offset of " + std::to_string(offset) + " from the beginning of the file exceeds the file size"
                        );
                    }
                } break;

                case std::ios::cur: {
                    if (position() + offset > mSize) {
                        throw std::runtime_error(
                            "File size is " + std::to_string(mSize) + "; an offset of " + std::to_string(offset) + " from the current position (" + std::to_string(position()) + ") exceeds the file size"
                        );
                    }
                } break;

                case std::ios::end: {
                    if (offset > mSize) {
                        throw std::runtime_error(
                            "File size is " + std::to_string(mSize) + "; an offset of " + std::to_string(offset) + " from the end of the file results in a negative position"
                        );
                    }
                } break;

                default:
                    throw std::logic_error("Unkonwn value passed for seek_origin.  The only accepted values are std::ios::beg, std::ios::cur, and std::ios::beg");
            }

            mFileStream.seekg(offset, seekOrigin);
        }
    }

    void BinaryReader::open(const std::string& filePath)
    {
        close();
        mFileStream.open(filePath, std::ios::binary | std::ios::ate);
        if (mFileStream.is_open()) {
            // TODO : Need to set the exception mask and correctly respond to failure states.
            mSize = position();
            position(0);
        } else {
            throw std::runtime_error("File @\"" + filePath + "\" couldn't be opened");
        }
    }

    void BinaryReader::close()
    {
        mFileStream.close();
        mSize = 0;
    }
} // namespace Dynamic_Static
