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


#include "test.h"
#include <iostream>
#include <chrono>

void runTest(const std::string& name, ISerializerTest& archive, int monstersCount, int repeatCount) {
    //test
    std::cout << std::endl << "*** TEST : " << name << std::endl;

    std::cout << "warmpup...: monsters=" << monstersCount << ", samples=" << repeatCount;
    const std::vector<MyTypes::Monster>& data = MyTypes::createMonsters(monstersCount);
    std::vector<MyTypes::Monster> res{};
    //warmup
    auto buf = archive.serialize(data);
    for (auto i = 0; i < 5; ++i) {
        buf = archive.serialize(data);
        archive.deserialize(buf, res);
    }
    if (res != data) {
        std::cout << "result != data, abort." << std::endl;
        return;
    }
    std::cout << ", serialized data size: " << buf.bytesCount << "B" << std::endl;

    //begin serialization
    std::cout << "*serialize*" << std::endl;
    auto start = std::chrono::steady_clock::now();
    for (auto i = 0; i < repeatCount; ++i)
        archive.serialize(data);
    auto end = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "\ttime: " << duration.count() / 1000 << "ms" << std::endl;

    //begin deserialization
//    std::cout << "*deserialize* on empty object" << std::endl;
//    start = std::chrono::steady_clock::now();
//    for (auto i = 0; i < repeatCount; ++i) {
//        std::vector<MyTypes::Monster> tmp{};
//        archive.deserialize(buf, tmp);
//    }
//    end = std::chrono::steady_clock::now();
//    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
//    std::cout << "\ttime: " << duration.count() / 1000 << "ms" << std::endl;

    //deserialize on top of old object
    std::cout << "*deserialize on same object*" << std::endl;
    start = std::chrono::steady_clock::now();
    for (auto i = 0; i < repeatCount; ++i) {
        archive.deserialize(buf, res);
    }
    end = std::chrono::steady_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "\ttime: " << duration.count() / 1000 << "ms" << std::endl;

}
