
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

#define DYNAMIC_STATIC_STREAM_GUARD_MEMBER_STRING_STREAM

namespace dst {

/**
TODO : Documentation
*/
template<typename ...Args>
class StreamGuard final
{
public:
    /**
    Constructs an instance of StreamGuard
    TODO : Documentation
    */
    StreamGuard(const Args&... args)
        : mArgs(args...)
    {
    }

    /**
    TODO : Documentation
    */
    friend std::ostream& operator<<(std::ostream& stream, StreamGuard& streamGuard)
    {
        streamGuard.mPosition = stream.tellp();
        streamGuard.process_stream(stream);
        return stream;
    }

private:
    template <size_t Index = 0>
    inline typename std::enable_if<Index == sizeof...(Args), void>::type
        process_stream(std::ostream& stream)
    {
        #ifdef DYNAMIC_STATIC_STREAM_GUARD_MEMBER_STRING_STREAM
        stream << mStrStrm.str();
        #endif
    }

    template <size_t Index = 0>
    inline typename std::enable_if<Index < sizeof...(Args), void>::type
        process_stream(std::ostream& stream)
    {
        // TODO : It's very annoying to have to keep a std::stringstream member here.
        //  It causes this class to not be general purpose.  Currently it's only being
        //  used to process text so it's fine, but it would be much nicer to manipulate
        //  the std::ostream's std::basic_streambuf<> so that when it flushes after
        //  resetting the output position it doesn't flush past it.
        #ifdef DYNAMIC_STATIC_STREAM_GUARD_MEMBER_STRING_STREAM
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
    #ifdef DYNAMIC_STATIC_STREAM_GUARD_MEMBER_STRING_STREAM
    std::stringstream mStrStrm;
    #endif
    StreamGuard(const StreamGuard<Args...>&) = delete;
    StreamGuard(StreamGuard<Args...>&&) = delete;
    StreamGuard<Args...>& operator=(const StreamGuard<Args...>&) = delete;
    StreamGuard<Args...>& operator=(StreamGuard<Args...>&&) = delete;
};

} // namespace dst
