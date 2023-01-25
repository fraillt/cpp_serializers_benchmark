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
#include <yas/mem_streams.hpp>
#include <yas/binary_iarchive.hpp>
#include <yas/binary_oarchive.hpp>
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
        ar & o.name & o.equipped & o.weapons & o.pos & o.path & o.mana & o.inventory & o.hp & o.color & o.image;
    }

}

class YasArchiver : public ISerializerTest {
public:

    Buf serialize(const std::vector<MyTypes::Monster> &data) override {
        yas::mem_ostream os;
        yas::binary_oarchive<yas::mem_ostream, yas::binary | yas::no_header> oa(os);
        oa & data;
        if (_buf.size == 0)
            _buf = os.get_shared_buffer();

        return {reinterpret_cast<const uint8_t *>(_buf.data.get()), _buf.size};
    }

    void deserialize(Buf buf, std::vector<MyTypes::Monster> &resVec) override {

        yas::mem_istream is(buf.ptr, buf.bytesCount);
        yas::binary_iarchive<yas::mem_istream, yas::binary | yas::no_header> ia(is);

        ia & resVec;
    }

    TestInfo testInfo() const override {
        return {
                SerializationLibrary::YAS,
                "general",
                "use yas::mem_<io>stream as buffer"
        };
    }

private:
    yas::shared_buffer _buf;
};


int main() {
    YasArchiver test;
    return runTest(test);
}
