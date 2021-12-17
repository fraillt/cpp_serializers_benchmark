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

#include "zpp_bits.h"

class ZppBitsFixedArchiver : public ISerializerTest {
public:
    Buf serialize(const std::vector<MyTypes::Monster> &data) override {
        zpp::bits::out out{m_data};
        (void) out(data);
        return { std::data(m_data), out.position() };
    }

    void deserialize(Buf buf, std::vector<MyTypes::Monster> &resVec) override {
        (void) zpp::bits::in{std::span{buf.ptr, buf.bytesCount}}(resVec);
    }

    TestInfo testInfo() const override {
        return {
                SerializationLibrary::ZPP_BITS,
                "fixed buffer",
                ""
        };
    }

private:
    unsigned char m_data[150000];
};

int main() {
    ZppBitsFixedArchiver test;
    return runTest(test);
}
