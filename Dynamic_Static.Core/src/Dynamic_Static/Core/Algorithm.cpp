
/*
=====================================================================================

    The MIT License(MIT)

    Copyright(c) 2017 to this->moment()->next() Dynamic_Static

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

#include "Dynamic_Static/Core/Algorithm.hpp"

#include <memory>

namespace Dynamic_Static {
    namespace BinPack {
        struct Rectangle final {
            uint32_t x;
            uint32_t y;
            uint32_t width;
            uint32_t height;
            uint32_t area() { return width * height; };
        };

        struct Node final {
            Rectangle rectangle;
            Node* left { nullptr };
            Node* right { nullptr };
            Node* overflow { nullptr };
            bool occupied { false };
            static thread_local std::vector<std::unique_ptr<Node>> sNodes;

            Node() = default;
            ~Node() = default;

            Node* insert(BinEntry2D& entry)
            {
                Node* node = nullptr;
                if (left && right) {
                    // TODO : Make insert and split configurable...
                    bool insertLeft = left->rectangle.area() < right->rectangle.area();
                    node = insertLeft ? left->insert(entry) : right->insert(entry);
                    if (!node) {
                        node = insertLeft ? right->insert(entry) : left->insert(entry);
                    }
                } else
                if (!occupied &&
                    rectangle.width  >= entry.width &&
                    rectangle.height >= entry.height) {

                    left = create();
                    left->rectangle = Rectangle {
                        rectangle.x,
                        rectangle.y      + entry.height,
                        rectangle.width,
                        rectangle.height - entry.height
                    };

                    right = create();
                    right->rectangle = Rectangle {
                        rectangle.x     + entry.width,
                        rectangle.y,
                        rectangle.width - entry.width,
                                          entry.height
                    };

                    entry.x = rectangle.x;
                    entry.y = rectangle.y;
                    occupied = true;
                    node = this;
                }

                return node;
            }

            static Node* create()
            {
                sNodes.push_back(std::make_unique<Node>());
                return sNodes.back().get();
            }

            static void clear()
            {
                sNodes.clear();
            }
        };

        thread_local std::vector<std::unique_ptr<Node>> Node::sNodes;
    } // namespace BinPack
} // namespace Dynamic_Static

namespace Dynamic_Static {
    BinPackResult bin_pack(std::vector<BinEntry2D>& entries, uint32_t padding, uint32_t pageCountHint)
    {
        std::sort(
            entries.begin(), entries.end(),
            [](const BinEntry2D& entry0, const BinEntry2D& entry1)
            {
                // TODO : Make sort configurable...
                auto max0 = std::max(entry0.width, entry0.height);
                auto max1 = std::max(entry1.width, entry1.height);
                return max0 > max1;
            }
        );

        BinPackResult result;
        uint32_t sourceArea = 0;
        for (auto& entry : entries) {
            entry.width += padding;
            entry.height += padding;
            sourceArea += entry.width * entry.height;
        }

        // TODO : Make max page size configurable...
        while (result.pageSize * result.pageSize * result.pageCount < sourceArea) {
            if (result.pageCount++ >= std::max<uint32_t>(pageCountHint, 1) - 1) {
                result.pageCount = 1;
                result.pageSize += 1;
            }
        }

        result.pageCount = 1;
        auto root = BinPack::Node::create();
        root->rectangle.width = result.pageSize;
        root->rectangle.height = result.pageSize;
        for (auto& entry : entries) {
            entry.page = 0;
            auto node = root;
            while (!node->insert(entry)) {
                if (!node->overflow) {
                    node->overflow = BinPack::Node::create();
                    node->overflow->rectangle.width = result.pageSize;
                    node->overflow->rectangle.height = result.pageSize;
                    ++result.pageCount;
                }

                node = node->overflow;
                ++entry.page;
            }
        }

        BinPack::Node::clear();
        for (auto& entry : entries) {
            entry.width -= padding;
            entry.height -= padding;
        }

        return result;
    }
} // namespace Dynamic_Static
