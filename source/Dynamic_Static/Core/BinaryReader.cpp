
/*
==========================================
    Copyright (c) 2016 Dynamic_Static
    Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "Dynamic_Static/Core/BinaryReader.hpp"
#include "Dynamic_Static/Core/ToString.hpp"

namespace Dynamic_Static {

    BinaryReader::BinaryReader(const std::string& filePath)
    {
        // TODO : BinaryReader ctor() should take std::fstream argument.
        open(filePath);
    }

    size_t BinaryReader::get_size() const
    {
        // TODO : Size doesn't handle file changes.
        return mSize;
    }

    size_t BinaryReader::get_position() const
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

    void BinaryReader::set_position(size_t position)
    {
        seek(position, std::ios::beg);
    }

    void BinaryReader::seek(size_t offset, std::ios::seekdir origin)
    {
        if (mFileStream.is_open()) {
            switch (origin) {
                case std::ios::beg:
                case std::ios::end: {
                    if (offset > mSize) {
                        throw std::runtime_error(
                            "offset (" + dst::to_string(offset) + ") exceeds file size (" + dst::to_string(get_size()) + ")"
                        );
                    }
                } break;

                case std::ios::cur: {
                    if (get_position() + offset > get_size()) {
                        throw std::runtime_error(
                            "offset (" + dst::to_string(offset) + ") from current position (" + dst::to_string(get_position()) + ") exceeds file size (" + dst::to_string(get_size()) + ")"
                        );
                    }
                } break;

                default: {
                    throw std::logic_error("A value besides std::ios::beg, std::ios::cur, or set::ios::end was given for origin");
                }
            }

            mFileStream.seekg(offset, origin);
        }
    }

    void BinaryReader::open(const std::string& filePath)
    {
        close();
        mFileStream.open(filePath, std::ios::binary | std::ios::ate);
        if (mFileStream.is_open()) {
            mSize = get_position();
            set_position(0);
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
