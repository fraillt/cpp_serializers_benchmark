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
#include <cereal/archives/binary.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/string.hpp>

namespace cereal {

    template<typename Archive>
    void serialize(Archive &archive, MyTypes::Vec3 &o) {
        archive(o.x, o.y, o.z);
    }

    template<typename Archive>
    void serialize(Archive &archive, MyTypes::Weapon &o) {
        archive(o.name, o.damage);
    }

    template<typename Archive>
    void serialize(Archive &archive, MyTypes::Monster &o) {
        archive(o.name, o.equipped, o.weapons, o.pos, o.path, o.mana, o.inventory, o.hp, o.color, o.image);
    }

}

class CerealArchiver : public ISerializerTest {
public:
    Buf serialize(const std::vector<MyTypes::Monster> &data) override {
        std::stringstream _stream;
        cereal::BinaryOutputArchive archive(_stream);

        archive(data);

        if (_buf.empty())
            _buf = _stream.str();
        return {
                reinterpret_cast<uint8_t *>(std::addressof(*_buf.begin())),
                _buf.size()
        };
    }

    void deserialize(Buf buf, std::vector<MyTypes::Monster> &resVec) override {
        std::stringstream stream(_buf);
        cereal::BinaryInputArchive archive(stream);

        archive(resVec);
    }

    TestInfo testInfo() const override {
        return {
                SerializationLibrary::CEREAL,
                "general",
                ""
        };
    }

private:
    std::string _buf;
};

int main() {
    CerealArchiver test;
    return runTest(test);
}
