
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

#include "Dynamic_Static/Core/Dependency.hpp"
#include "Dynamic_Static/Core/Collection.hpp"
#include "Dynamic_Static/Core/NonCopyable.hpp"
#include "Dynamic_Static/Core/SharedObjectFactory.hpp"

#include <string>
#include <iostream>

#include <vector>
#include <memory>
#include <utility>
#include <functional>

#if 0
namespace Dynamic_Static {
    template <typename Object>
    class Factory
        : dst::NonCopyable {
    private:
        mutable std::vector<std::weak_ptr<Object>> mObjects;

    public:
        const std::vector<std::weak_ptr<Object>>& objects() const
        {
            mObjects.erase(
                std::remove_if(
                    mObjects.begin(), mObjects.end(),
                    [](std::weak_ptr<Object> object)
                    {
                        return object.expired();
                    }
                ),
                mObjects.end()
            );

            return mObjects;
        }

    protected:
        template <typename T, typename ...Args>
        std::shared_ptr<T> create(Args... args)
        {
            auto object = std::make_shared<Object>(std::forward<Args>(args)...);
            mObjects.push_back(object);
            return object;
        }

        void push(std::shared_ptr<Object> object)
        {
            mObjects.push_back(object);
        }
    };
} // namespace Dynamic_Static

namespace Dynamic_Static {
    class Image;
    class Buffer;
    class Device;
    class PhysicalDevice;
} // namespace Dynamic_Static

namespace Dynamic_Static {
    class GObject
        : dst::NonCopyable {
    private:
        std::string mName { "GObject" };
    };
} // namespace Dynamic_Static

namespace Dynamic_Static {
} // namespace Dynamic_Static

namespace Dynamic_Static {
    class Image final
        : public GObject
        , public Dependency<Device> {
    public:
        void test_func() const
        {
            std::cout << "== Image::test_func()" << std::endl;
        }
    };
} // namespace Dynamic_Static

namespace Dynamic_Static {
    class Buffer final
        : public GObject
        , public Dependency<Device> {
    public:
        void test_func() const
        {
            std::cout << "== Buffer::test_func()" << std::endl;
        }
    };
} // namespace Dynamic_Static

namespace Dynamic_Static {
    class Device final
        : public std::enable_shared_from_this<Device>
        , public Dependency<std::shared_ptr<PhysicalDevice>>
        , dst::Factory<Buffer>
        , dst::Factory<Image>
        , public GObject {
        friend class PhysicalDevice;
    private:
        Device(std::shared_ptr<PhysicalDevice> physicalDevice)
            : Dependency(physicalDevice)
        {
        }

    public:
        PhysicalDevice& physical_device()
        {
            return *dependency();
        }

        const PhysicalDevice& physical_device() const
        {
            return *dependency();
        }

        void test_func() const
        {
            std::cout << "== Device::test_func()" << std::endl;
        }
    };
} // namespace Dynamic_Static

namespace Dynamic_Static {
    class PhysicalDevice final
        : public std::enable_shared_from_this<PhysicalDevice>
        , dst::Factory<Device>
        , public GObject {
    public:
        const std::vector<std::weak_ptr<Device>>& devices() const
        {
            return Factory<Device>::objects();
        }

        std::shared_ptr<Device> create_device()
        {
            auto device = std::shared_ptr<Device>(new Device(shared_from_this()));
            Factory<Device>::push(device);
            return device;
        }
    };
} // namespace Dynamic_Static
#endif

// class Widget final {
// 
// };
// 
// class Woozle final {
// 
// };
// 
// template <typename T>
// class Factory {
// private:
//     std::vector<T> mObjects;
// 
// public:
//     void create_object()
//     {
//         mObjects.push_back(T());
//     }
// 
//     const std::vector<T>& objects() const
//     {
//         return mObjects;
//     }
// };
// 
// class Machine final
//     : public Factory<Widget>
//     , public Factory<Woozle> {
// public:
//     template <typename T>
//     void create_object()
//     {
//         Factory<T>::create_object();
//     }
// 
//     template <typename T>
//     const std::vector<T>& objects() const
//     {
//         return Factory<T>::objects();
//     }
// };

int main_ex();

int main(/* int argc, char* argv[] */)
{
    return main_ex();
    // using namespace dst;
    // auto physicalDevice = std::make_shared<PhysicalDevice>();
    // auto sp = physicalDevice->shared_from_this();
    // 
    // {
    //     auto device = physicalDevice->create_device();
    //     auto devices0 = physicalDevice->devices();
    //     if (auto d = devices0[0].lock()) {
    //         d->test_func();
    //     }
    // 
    //     int break0 = 1;
    // }
    // 
    // auto devices1 = physicalDevice->devices();
    // int break1 = 1;

    // Machine machine;
    // machine.create_object<Widget>();
    // machine.create_object<Woozle>();
    // auto widgets = machine.objects<Widget>();
    // auto woozles = machine.objects<Woozle>();

    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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
    class Machine final
        : SharedObjectFactory<Widget>
        , SharedObjectFactory<Whatsit>
        //, public ISharedObjectFactory
    {
    public:
        template <typename T, typename ...Args>
        std::shared_ptr<T> create(Args&&... args)
        {
            return SharedObjectFactory<T>::create(std::forward<Args>(args)...);
        }

    private:
        // template <typename T>
        // Widget* allocate() override
        // {
        //     return new Widget(3.14f);
        // }
    };
}  // namespace Dynamic_Static

int main_ex()
{
    using namespace Dynamic_Static;
    //Machine machine;
    //machine.create<Widget>(3.14f);

    std::tuple<int, float> t;

    //std::get<0>(t) = 4;
    //std::get<1>(t) = 3.14f;

    std::get<float>(t) = 3.14f;

    SharedObjectFactory<
        Widget,
        Whatsit
    > factory;
    auto w0 = factory.create<Widget>(3.14f);
    auto w1 = factory.create<Whatsit>(16);
    auto w2 = factory.create<Widget>(64.0f);
    auto ws = factory.objects<Widget>();

    //List<TypeList<A, B, C>>::type myTuple;
    //auto& a = std::get<A>(myTuple);
    //auto& b = std::get<B>(myTuple);
    //auto& c = std::get<C>(myTuple);

    //List<TypeList<A, B, C>> myList;
    //myList.push_back<A>(A { });
    //myList.push_back<C>(C { });
    //myList.push_back<C>(C { });

    return 0;
}
