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
#include <iostream>
#include <chrono>

static constexpr int MONSTERS_COUNT = MONSTERS;
static constexpr int SAMPLES_COUNT = SAMPLES;


int runTest(ISerializerTest& testCase) {
    //test
    auto info = testCase.testInfo();
    std::cout << std::endl << "* TEST: " << getLibraryName(info.library) << std::endl;
    std::cout << "* name       : " << info.name << std::endl;
    std::cout << "* info       : " << info.info << std::endl;

    const std::vector<MyTypes::Monster>& data = MyTypes::createMonsters(MONSTERS_COUNT);
    std::vector<MyTypes::Monster> res{};
    //warmup
    auto buf = testCase.serialize(data);
    for (auto i = 0; i < 5; ++i) {
        buf = testCase.serialize(data);
        testCase.deserialize(buf, res);
    }
    if (res != data) {
        std::cout << "result != data, abort." << std::endl;
        return -1;
    }
    std::cout << "* data size  : " << buf.bytesCount << std::endl;

    //begin serialization
    auto start = std::chrono::steady_clock::now();
    for (auto i = 0; i < SAMPLES_COUNT; ++i)
        testCase.serialize(data);
    auto end = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "* serialize  : " << duration.count() / 1000 << std::endl;

    //deserialize on top of old object
    start = std::chrono::steady_clock::now();
    for (auto i = 0; i < SAMPLES_COUNT; ++i) {
        testCase.deserialize(buf, res);
    }
    end = std::chrono::steady_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "* deserialize: " << duration.count() / 1000 << std::endl;
    return 0;
}

std::string getLibraryName(SerializationLibrary name) {
    switch (name) {
        case SerializationLibrary::BITSERY:
            return "bitsery";
        case SerializationLibrary::BOOST:
            return "boost";
        case SerializationLibrary::CEREAL:
            return "cereal";
        case SerializationLibrary::FLATBUFFERS:
            return "flatbuffers";
        case SerializationLibrary::HAND_WRITTEN:
            return "handwritten";
        case SerializationLibrary::IOSTREAM:
            return "iostream";
        case SerializationLibrary::MSGPACK:
            return "msgpack";
        case SerializationLibrary::PROTOBUF:
            return "protobuf";
        case SerializationLibrary::YAS:
            return "yas";
        case SerializationLibrary::ZPP_BITS:
            return "zpp_bits";
    }
    throw "Unknown library name";
}
