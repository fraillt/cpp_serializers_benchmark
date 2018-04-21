//MIT License
//
//Copyright (c) 2017 Mindaugas Vinkelis
//
//Permission is hereby granted, free of charge, to any person obtaining a copy
//of this software and associated documentation files (the "Software"), to deal
//in the Software without restriction, including without limitation the rights
//to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//copies of the Software, and to permit persons to whom the Software is
//furnished to do so, subject to the following conditions:
//
//The above copyright notice and this permission notice shall be included in all
//copies or substantial portions of the Software.
//
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//SOFTWARE.

#include "testing/test.h"

#include "serializer.h"

namespace zpp {
namespace serializer {

template<typename Archive>
void serialize(Archive &archive, MyTypes::Vec3 &o) {
    archive(o.x, o.y, o.z);
}

template<typename Archive>
void serialize(Archive &archive, const MyTypes::Vec3 &o) {
    archive(o.x, o.y, o.z);
}

template<typename Archive>
void serialize(Archive &archive, MyTypes::Weapon &o) {
    archive(o.name, o.damage);
}

template<typename Archive>
void serialize(Archive &archive, const MyTypes::Weapon &o) {
    archive(o.name, o.damage);
}

template<typename Archive>
void serialize(Archive &archive, MyTypes::Monster &o) {
    archive(o.name, o.equipped, o.weapons, o.pos, o.path, o.mana, o.inventory, o.hp, o.color);
}

template<typename Archive>
void serialize(Archive &archive, const MyTypes::Monster &o) {
    archive(o.name, o.equipped, o.weapons, o.pos, o.path, o.mana, o.inventory, o.hp, o.color);
}

}}

class ZppArchiver : public ISerializerTest {
public:
    Buf serialize(const std::vector<MyTypes::Monster> &data) override {
        m_data.clear();
        zpp::serializer::memory_output_archive archive(m_data);
        archive(data);
        return { m_data.data(), m_data.size() };
    }

    void deserialize(Buf buf, std::vector<MyTypes::Monster> &resVec) override {
        zpp::serializer::memory_view_input_archive archive(buf.ptr, buf.bytesCount);
        archive(resVec);
    }

    TestInfo testInfo() const override {
        return {
                SerializationLibrary::ZPP,
                "general",
                ""
        };
    }

private:
    std::vector<unsigned char> m_data;
};

int main() {
    ZppArchiver test;
    return runTest(test);
}
