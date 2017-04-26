
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

#include "Dynamic_Static/Core/SharedObjectFactory.hpp"

namespace Dynamic_Static {
    class Widget final {

    private:
        float mValue { };

    public:
        Widget(float value)
            : mValue { value }
        {
        }

    public:
        float value() const
        {
            return mValue;
        }

        // template <typename ...Args>
        // static std::shared_ptr<Widget> create(Args&&... args)
        // {
        //     return std::shared_ptr<Widget>(new Widget(std::forward<Args>(args)...));
        // }
    };
} // namespace Dynamic_Static

namespace Dynamic_Static {
    class Whatsit final {

    private:
        size_t mValue { };

    public:
        Whatsit(size_t value)
            : mValue { value }
        {
        }

    public:
        size_t value() const
        {
            return mValue;
        }
    };
} // namespace Dynamic_Static

namespace Dynamic_Static {
    class Machine final {
    };
}  // namespace Dynamic_Static

int main(/* int argc, char* argv[] */)
{
    using namespace Dynamic_Static;
    dst::SharedObjectFactory<
        Widget,
        Whatsit
    > factory;
    auto w0 = factory.create<Widget>(3.14f);
    auto w1 = factory.create<Whatsit>(16);
    auto w2 = factory.create<Widget>(64.0f);
    auto ws = factory.objects<Widget>();
    return 0;
}
