
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
#include <tuple>

namespace dst {

/**
TODO : Documentation
*/
template<typename ...Args>
class StreamGuard final
{
public:
    /**
    Constructs an instance of NewlineGuard
    TODO : Documentation
    */
    StreamGuard(const Args&... args)
        : mArgs(args...)
    {
    }

    /**
    TODO : Documentation
    */
    friend std::ostream& operator<<(std::ostream& stream, const StreamGuard& streamGuard)
    {
        streamGuard.process_stream(stream);
        return stream;
    }

private:
    template <size_t Index = 0>
    inline typename std::enable_if<Index == sizeof...(Args), void>::type
        process_stream(std::ostream&) const
    {
    }

    template <size_t Index = 0>
    inline typename std::enable_if<Index < sizeof...(Args), void>::type
        process_stream(std::ostream& stream) const
    {
        auto position = stream.tellp();
        stream << std::get<Index>(mArgs);
        if (position < stream.tellp()) {
            process_stream<Index + 1>(stream);
        }
    }

    std::tuple<const Args&...> mArgs;
    StreamGuard(const StreamGuard<Args...>&) = delete;
    StreamGuard(StreamGuard<Args...>&&) = delete;
    StreamGuard<Args...>& operator=(const StreamGuard<Args...>&) = delete;
    StreamGuard<Args...>& operator=(StreamGuard<Args...>&&) = delete;
};

} // namespace dst
