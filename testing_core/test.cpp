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

    const std::vector<MyTypes::Monster>& data = MyTypes::createMonsters(monstersCount);
    std::vector<MyTypes::Monster> res{};

    //warmup
    std::cout << "monsters=" << monstersCount << ", samples=" << repeatCount << std::endl;
    std::cout << "warmup..." << std::endl;
    auto buf = archive.serialize(data);
    for (auto i = 0; i < 5; ++i) {
        buf = archive.serialize(data);
        archive.deserialize(buf, res);
    }
    if (res != data) {
        std::cout << "result != data, abort." << std::endl;
        return;
    }

    // calculate the actual memory used for storing data
    // remove all container and ease of access overhead
    size_t datasize_bytes = 0;
    size_t container_overhead = 0;
    for( auto& monster : data )
     {
        datasize_bytes += sizeof(MyTypes::Monster);
        datasize_bytes += monster.name.size();
        for ( auto& weapon : monster.weapons )
        {
          datasize_bytes += sizeof( MyTypes::Weapon );
          datasize_bytes += weapon.name.size();
          // remove container overhead
          container_overhead += sizeof( std::string );
        }
        for ( auto& point : monster.path )
        {
          datasize_bytes += sizeof(MyTypes::Vec3);
        }
        for ( auto& item : monster.inventory )
        {
          datasize_bytes += sizeof(uint8_t);
        }
        // all vector containers are same not depending on stored type
        container_overhead += sizeof( std::vector<uint8_t> ) * 3;
        container_overhead += sizeof( std::string);
     }

    std::cout << std::endl;

    double compression = buf.bytesCount/static_cast<double>(datasize_bytes - container_overhead)*100;

    /* std::cout << "actual used data size: \t\t" << datasize_bytes - container_overhead << "B" << std::endl; */
    std::cout << "serialized data size: \t\t" << buf.bytesCount << "B" << std::endl;
    std::cout << "compression ratio: \t\t" << compression << "%" << std::endl;
    std::cout << std::endl;

    //begin serialization
    auto start = std::chrono::steady_clock::now();
    for (auto i = 0; i < repeatCount; ++i)
        archive.serialize(data);
    auto end = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "serialize time: \t\t" << duration.count() / 1000 << "ms" << std::endl;


    //deserialize on top of old object
    start = std::chrono::steady_clock::now();
    for (auto i = 0; i < repeatCount; ++i) {
        archive.deserialize(buf, res);
    }
    end = std::chrono::steady_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "deserialize time: \t\t" << duration.count() / 1000 << "ms" << std::endl;


}
