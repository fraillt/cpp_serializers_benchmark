//MIT License
//
//Copyright (c) 2019 Mindaugas Vinkelis
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

#include "protobuf.h"

class ProtobufArchiver : public ISerializerTest {
public:

    Buf serialize(const std::vector<MyTypes::Monster> &data) override {
        Monsters res;
        auto monsters = res.mutable_monsters();
        for (const auto& m: data) {
            serializeMonster(monsters->Add(), m);
        }
        res.SerializeToString(&_buf);
        return {
            reinterpret_cast<uint8_t *>(std::addressof(*_buf.begin())),
            _buf.size()
        };
    }

    void deserialize(Buf buf, std::vector<MyTypes::Monster> &res) override {
        Monsters des;
        des.ParseFromString(_buf);
        res.resize(des.monsters().size());
        auto beginDesM = des.monsters().begin();
        for (auto& m: res) {
            deserializeMonster(*beginDesM, m);
            ++beginDesM;
        }
    };

    TestInfo testInfo() const override {
        return {
            SerializationLibrary::PROTOBUF,
            "general",
            ""
        };
    }

private:
  std::string _buf;
};

int main() {
    GOOGLE_PROTOBUF_VERIFY_VERSION;
    ProtobufArchiver test;
    auto res = runTest(test);
    google::protobuf::ShutdownProtobufLibrary();
    return res;
}
