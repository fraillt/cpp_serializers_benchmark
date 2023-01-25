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
#include <bitsery/bitsery.h>
#include <bitsery/adapter/buffer.h>
#include <bitsery/traits/vector.h>
#include <bitsery/traits/string.h>
//enable forward/backward compatibility
#include <bitsery/ext/growable.h>

namespace bitsery {

    template<typename S>
    void serialize(S &s, MyTypes::Vec3 &o) {
        s.value4b(o.x);
        s.value4b(o.y);
        s.value4b(o.z);
    }

    template<typename S>
    void serialize(S &s, MyTypes::Weapon &o) {
        s.text1b(o.name, 10);
        s.value2b(o.damage);
    }

    template<typename S>
    void serialize(S &s, MyTypes::Monster &o) {
        //Growable extension enables forward/backward compatibility
        s.ext(o, ext::Growable{}, [](S& s, MyTypes::Monster &o1) {
            s.value1b(o1.color);
            s.value2b(o1.mana);
            s.value2b(o1.hp);
            s.object(o1.equipped);
            s.object(o1.pos);
            s.container(o1.path, 10);
            s.container(o1.weapons, 10);
            s.container1b(o1.inventory, 10);
            s.text1b(o1.name, 10);
            s.container1b(o1.image, 100000000);
        });
    }
}

//enable forward/backward compatibility
struct SessionEnabled : public bitsery::DefaultConfig {
    static constexpr bool BufferSessionsEnabled = true;
};

using Buffer = std::vector<uint8_t>;
using InputAdapter = bitsery::InputBufferAdapter<Buffer>;
using OutputAdapter = bitsery::OutputBufferAdapter<Buffer>;

class BitseryCompatibilityArchiver : public ISerializerTest {
public:

    Buf serialize(const std::vector<MyTypes::Monster> &data) override {
        _buf.clear();
        bitsery::Serializer<OutputAdapter> ser{_buf};
        ser.container(data, 100000000);
        ser.adapter().flush();
        return Buf{std::addressof(*std::begin(_buf)), ser.adapter().writtenBytesCount()};
    }

    void deserialize(Buf buf, std::vector<MyTypes::Monster> &res) override {
        bitsery::Deserializer<InputAdapter> des( _buf.begin(), buf.bytesCount );
        des.container(res, 100000000);
    }

    TestInfo testInfo() const override {
        return {
                SerializationLibrary::BITSERY,
                "compatibility",
                "forward/backward compatibility enabled for `Monster`"
        };
    }

private:
    Buffer _buf{};
};

int main() {
    BitseryCompatibilityArchiver test{};
    return runTest(test);
}
