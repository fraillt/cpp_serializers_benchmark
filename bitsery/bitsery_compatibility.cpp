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
//#include <bitsery/traits/string.h>
#include <bitsery/flexible.h>
#include <bitsery/flexible/vector.h>
#include <bitsery/flexible/string.h>
//enable forward/backward compatibility
#include <bitsery/ext/growable.h>

namespace bitsery {


    template<typename S>
    void serialize(S& s, MyTypes::Vec3 &o) {
        s.archive(o.x, o.y, o.z);
    }

    template<typename S>
    void serialize(S& s, MyTypes::Weapon &o) {
        s.archive(maxSize(o.name, 10),
                  o.damage);
    }

    template<typename S>
    void serialize(S& s, MyTypes::Monster &o) {
        s.ext(o, ext::Growable{}, [&s](MyTypes::Monster& o1) {
            s.archive(maxSize(o1.name, 10),
                      o1.equipped,
                      maxSize(o1.weapons, 10),
                      o1.pos,
                      maxSize(o1.path, 10),
                      o1.mana,
                      maxSize(o1.inventory, 10),
                      o1.hp,
                      o1.color);
        });
    }
}

//enable forward/backward compatibility
struct SessionEnabled:public bitsery::DefaultConfig {
    static constexpr bool BufferSessionsEnabled = true;
};

using Buffer = std::vector<uint8_t>;
using InputAdapter = bitsery::InputBufferAdapter<Buffer>;
using OutputAdapter = bitsery::OutputBufferAdapter<Buffer>;
using Writer = bitsery::AdapterWriter<OutputAdapter, SessionEnabled>;
using Reader = bitsery::AdapterReader<InputAdapter, SessionEnabled>;

class BitseryArchiver : public ISerializerTest {
public:

    Buf serialize(const std::vector<MyTypes::Monster> &data) override {
        _buf.clear();

        bitsery::BasicSerializer<Writer> ser(OutputAdapter{_buf});
        ser.container(data, 100000000);
        auto& bw = bitsery::AdapterAccess::getWriter(ser);
        bw.flush();
        return Buf{std::addressof(*std::begin(_buf)), bw.writtenBytesCount()};
    }

    void deserialize(Buf buf, std::vector<MyTypes::Monster> &res) override {

        bitsery::BasicDeserializer<Reader> des(InputAdapter{_buf.begin(), buf.bytesCount});
        des.container(res, 100000000);
    }
private:
    Buffer _buf{};
};

int main () {
    BitseryArchiver test{};
    runTest("bitsery\n\tbuffer: std::vector<uint8_t>\n\tcompatibility enabled for Monster type", test, MONSTERS, SAMPLES);
    return 0;
}
