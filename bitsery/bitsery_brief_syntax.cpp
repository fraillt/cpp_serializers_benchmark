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
#include <bitsery/brief_syntax.h>
#include <bitsery/brief_syntax/vector.h>
#include <bitsery/brief_syntax/string.h>


namespace bitsery {

    template<typename S>
    void serialize(S &s, MyTypes::Vec3 &o) {
        s(o.x, o.y, o.z);
    }

    template<typename S>
    void serialize(S &s, MyTypes::Weapon &o) {
        s(maxSize(o.name, 10),//this maxSize function is optional
                  o.damage);
    }

    template<typename S>
    void serialize(S &s, MyTypes::Monster &o) {
        s(maxSize(o.name, 10),
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

using Buffer = std::vector<uint8_t>;
using InputAdapter = bitsery::InputBufferAdapter<Buffer>;
using OutputAdapter = bitsery::OutputBufferAdapter<Buffer>;

class BitseryVerboseSyntaxArchiver : public ISerializerTest {
public:

    Buf serialize(const std::vector<MyTypes::Monster> &data) override {
        _buf = Buffer{};
        bitsery::Serializer<OutputAdapter> ser(_buf);
        ser.container(data, 100000000);
        ser.adapter().flush();
        return Buf{std::addressof(*std::begin(_buf)), ser.adapter().writtenBytesCount()};
    }

    void deserialize(Buf buf, std::vector<MyTypes::Monster> &res) override {
        bitsery::Deserializer<InputAdapter> des(_buf.begin(), buf.bytesCount);
        des.container(res, 100000000);
    }

    TestInfo testInfo() const override {
        return {
                SerializationLibrary::BITSERY,
                "brief syntax",
                "deserialization using `brief_syntax`, similar to `cereal`"
        };
    }

private:
    Buffer _buf{};
};

int main() {
    BitseryVerboseSyntaxArchiver test{};
    return runTest(test);
}
