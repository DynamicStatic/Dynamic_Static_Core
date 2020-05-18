
/*
==========================================
  Copyright (c) 2020 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include <ostream>
#include <sstream>
#include <tuple>

namespace dst {

/**
Provides a mechanism for grouping stream writes that require all writes to evaluate to a non empty std::string
*/
template<typename ...Args>
class StreamGuard final
{
public:
    /**
    Constructs an instance of StreamGuard<>
    @param [args] The arguments to stream via this StreamGuard<>
    */
    inline StreamGuard(const Args&... args)
        : mArgs { args... }
    {
    }

    /**
    Writes a given StreamGuard<> to a a given std::ostream
    @param [in] stream The std::ostream to write the given StreamGuard<> to
    @param [in] streamGuard The StreamGuard<> to write to the given std::ostream
    @return A reference to the given std::ostream
        @note If any of the arguments provided when constructing the given StreamGuard<> evaluate to an empty std::string when written to the given std::ostream all writes are discarded
    */
    inline friend std::ostream& operator<<(std::ostream& stream, StreamGuard& streamGuard)
    {
        streamGuard.mPosition = stream.tellp();
        streamGuard.process_stream(stream);
        return stream;
    }

private:
    template <size_t Index = 0>
    inline typename std::enable_if<Index == sizeof...(Args), void>::type process_stream(std::ostream& stream)
    {
        #if 1
        stream << mStrStrm.str();
        #endif
    }

    template <size_t Index = 0>
    inline typename std::enable_if<Index < sizeof...(Args), void>::type process_stream(std::ostream& stream)
    {
        // TODO : It's very annoying to have to keep a std::stringstream member here.
        //  It causes this class to not be general purpose.  Currently it's only being
        //  used to process text so it's fine, but it would be much nicer to manipulate
        //  the std::ostream's std::basic_streambuf<> so that when it's flushed, it
        //  doesn't flush past the modified output position.
        #if 1
        auto position = mStrStrm.tellp();
        mStrStrm << std::get<Index>(mArgs);
        if (position < mStrStrm.tellp()) {
            process_stream<Index + 1>(stream);
        }
        #else
        auto position = stream.tellp();
        stream << std::get<Index>(mArgs);
        if (position < stream.tellp()) {
            process_stream<Index + 1>(stream);
        } else {
            stream.seekp(mPosition);
        }
        #endif
    }

    std::tuple<const Args&...> mArgs;
    std::ostream::pos_type mPosition { 0 };
    #if 1
    std::stringstream mStrStrm;
    #endif
    StreamGuard(const StreamGuard<Args...>&) = delete;
    StreamGuard(StreamGuard<Args...>&&) = delete;
    StreamGuard<Args...>& operator=(const StreamGuard<Args...>&) = delete;
    StreamGuard<Args...>& operator=(StreamGuard<Args...>&&) = delete;
};

} // namespace dst
