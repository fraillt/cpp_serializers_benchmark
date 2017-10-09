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

#include "testing_core/test.h"
#include <bitsery/bitsery.h>
#include <bitsery/adapter/buffer.h>
//#include <bitsery/traits/vector.h>
//#include <bitsery/traits/array.h>
#include <bitsery/flexible.h>
#include <bitsery/flexible/vector.h>
#include <bitsery/flexible/string.h>

#include <bitsery/ext/value_range.h>

namespace bitsery {

    template<typename S>
    void serialize(S& s, MyTypes::Vec3 &o) {
        s.enableBitPacking([&o](typename S::BPEnabledType& sbp) {
            constexpr ext::ValueRange<float> range{-1.0f,1.0f, 0.01f};
            sbp.ext(o.x, range);
            sbp.ext(o.y, range);
            sbp.ext(o.z, range);
        });
        //s.archive(o.x, o.y, o.z);
    }

    template<typename S>
    void serialize(S& s, MyTypes::Weapon &o) {
        s.archive(maxSize(o.name, 10),//this maxSize function is optional
                  o.damage);
    }

    template<typename S>
    void serialize(S& s, MyTypes::Monster &o) {
        s.archive(maxSize(o.name, 10),
                  o.equipped,
                  maxSize(o.weapons, 10),
                  o.pos,
                  maxSize(o.path, 10),
                  o.mana,
                  maxSize(o.inventory, 10),
                  o.hp,
                  o.color);
    }
}

using Buffer = uint8_t[150000];
using InputAdapter = bitsery::InputBufferAdapter<const uint8_t*>;
using OutputAdapter = bitsery::OutputBufferAdapter<Buffer>;
using Writer = bitsery::AdapterWriter<OutputAdapter, bitsery::DefaultConfig>;
using Reader = bitsery::AdapterReader<InputAdapter, bitsery::DefaultConfig>;

class BitseryArchiver : public ISerializerTest {
public:

    Buf serialize(const std::vector<MyTypes::Monster> &data) override {

        bitsery::Serializer<OutputAdapter> ser(OutputAdapter{_buf});
        ser.container(data, 100000000);
        auto& bw = bitsery::AdapterAccess::getWriter(ser);
        bw.flush();
        return Buf{std::addressof(*std::begin(_buf)), bw.writtenBytesCount()};

    }

    void deserialize(Buf buf, std::vector<MyTypes::Monster> &res) override {
        bitsery::BasicDeserializer<Reader> des(InputAdapter{buf.ptr, buf.bytesCount});
        des.container(res, 100000000);
    }
private:
    Buffer _buf{};
};

int main () {
    BitseryArchiver test{};
    runTest("bitsery compression\n\tbuffer: uint8_t[150000]\n\tall components of Vec3 is compressed in [-1.0, 1.0] range with precision 0.01",
            test, MONSTERS, SAMPLES);
    return 0;
}
