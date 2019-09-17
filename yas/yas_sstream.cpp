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

#include <testing/test.h>

#include <sstream>
#include <yas/serialize.hpp>
#include <yas/types/std/vector.hpp>
#include <yas/types/std/string.hpp>

namespace yas {

    template<typename Archive>
    void serialize(Archive &ar, MyTypes::Vec3 &o) {
        ar & o.x & o.y & o.z;
    }

    template<typename Archive>
    void serialize(Archive &ar, MyTypes::Weapon &o) {

        ar & o.name & o.damage;
    }

    template<typename Archive>
    void serialize(Archive &ar, MyTypes::Monster &o) {
        ar & o.name & o.equipped & o.weapons & o.pos & o.path & o.mana & o.inventory & o.hp & o.color;
    }

}

class YasArchiverSStream : public ISerializerTest {
public:

    Buf serialize(const std::vector<MyTypes::Monster> &data) override {
        std::stringstream ss;
        yas::std_ostream_adapter os{ss};
        yas::save<yas::file | yas::binary | yas::no_header>(os, data);

        if (_buf.empty())
            _buf = ss.str();

        return {
            reinterpret_cast<uint8_t *>(std::addressof(*_buf.begin())),
            _buf.size()
        };
    }

    void deserialize(Buf buf, std::vector<MyTypes::Monster> &resVec) override {
        std::stringstream ss{_buf};
        yas::std_istream_adapter is(ss);
        yas::load<yas::file | yas::binary | yas::no_header>(is, resVec);
    }

    TestInfo testInfo() const override {
        return {
            SerializationLibrary::YAS,
            "stream",
            "using std::stringstream"
        };
    }

private:
    std::string _buf;
};


int main() {
    YasArchiverSStream test;
    return runTest(test);
}
