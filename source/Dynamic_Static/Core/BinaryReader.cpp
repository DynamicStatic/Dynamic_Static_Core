
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

#include "Dynamic_Static/Core/BinaryReader.hpp"
#include "Dynamic_Static/Core/ToString.hpp"

namespace Dynamic_Static {

    BinaryReader::BinaryReader(const std::string& filePath)
    {
        // TODO : BinaryReader should accept a file interface.
        open(filePath);
    }

    size_t BinaryReader::size() const
    {
        // TODO : Size doesn't handle file changes.
        return mSize;
    }

    size_t BinaryReader::position() const
    {
        size_t position = 0;
        if (mFileStream.is_open()) {
            // NOTE : We're doing a const_cast() here becuase tellg() isn't
            //        const, but we want position() to be.  It's worth noting
            //        that mFileStream's constness is self imposed here.
            auto fileStreamPtr = const_cast<std::ifstream*>(&mFileStream);
            position = static_cast<size_t>(fileStreamPtr->tellg());
        }

        return position;
    }

    void BinaryReader::position(size_t position)
    {
        seek(position, std::ios::beg);
    }

    void BinaryReader::seek(size_t offset, std::ios::seekdir origin)
    {
        if (mFileStream.is_open()) {
            switch (origin) {
                case std::ios::beg:
                case std::ios::end:
                {
                    if (offset > mSize) {
                        throw std::runtime_error(
                            "offset (" + dst::to_string(offset) + ") exceeds file size (" + dst::to_string(size()) + ")"
                        );
                    }
                } break;

                case std::ios::cur:
                {
                    if (position() + offset > size()) {
                        throw std::runtime_error(
                            "offset (" + dst::to_string(offset) + ") from current position (" + dst::to_string(position()) + ") exceeds file size (" + dst::to_string(size()) + ")"
                        );
                    }
                } break;

                default:
                    throw std::logic_error("A value besides std::ios::beg, std::ios::cur, or set::ios::end was given for origin");
            }

            mFileStream.seekg(offset, origin);
        }
    }

    void BinaryReader::open(const std::string& filePath)
    {
        close();
        mFileStream.open(filePath, std::ios::binary | std::ios::ate);
        if (mFileStream.is_open()) {
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
