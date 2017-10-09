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
#include <array>
#include <cstring>

class HandWrittenTest : public ISerializerTest {
public:

    Buf serialize(const std::vector<MyTypes::Monster> &data) override {
        auto begin = std::addressof(*_buf.begin());
        _pos = begin;
        writeSize(data.size());
        for (auto& m:data) {
            write(m.hp);
            write(m.mana);
            writeSize(m.name.size());
            write(m.name.data(), m.name.size());
            write(static_cast<const typename std::underlying_type<MyTypes::Color>::type&>(m.color));
            writeSize(m.inventory.size());
            write(m.inventory.data(), m.inventory.size());
            writeSize(m.weapons.size());
            for (auto& w:m.weapons) {
                writeWeapon(w);
            }
            writeSize(m.path.size());
            for (auto& p:m.path) {
                writeVec(p);
            }
            writeWeapon(m.equipped);
            writeVec(m.pos);
        }
        return {begin, static_cast<size_t >(std::distance(begin, _pos))};
    }

    void deserialize(Buf buf, std::vector<MyTypes::Monster> &res) override {
        _pos = const_cast<uint8_t *>(buf.ptr);
        _end = std::next(_pos, buf.bytesCount);
        size_t size;
        readSize(size);
        if (size > 1000000)
            return;
        res.resize(size);
        for (auto& m:res) {
            read(m.hp);
            read(m.mana);
            readSize(size); if (size > 100) return;
            m.name.resize(size);
            read(const_cast<char*>(m.name.data()), size);
            read(reinterpret_cast<typename std::underlying_type<MyTypes::Color>::type&>(m.color));
            readSize(size);if (size > 100) return;
            m.inventory.resize(size);
            read(m.inventory.data(), size);
            readSize(size);if (size > 100) return;
            m.weapons.resize(size);
            for (auto& w:m.weapons) {
                readWeapon(w);
            }
            readSize(size);if (size > 100) return;
            m.path.resize(size);
            for (auto& p:m.path) {
                readVec(p);
            }
            readWeapon(m.equipped);
            readVec(m.pos);
        }

    }
private:

    void writeWeapon(const MyTypes::Weapon& w) {
        write(w.damage);
        writeSize(w.name.size());
        write(w.name.data(), w.name.size());
    }

    void writeVec(const MyTypes::Vec3& p) {
        write(p.x);
        write(p.y);
        write(p.z);
    }

    void readWeapon(MyTypes::Weapon& w) {
        read(w.damage);
        size_t size;
        readSize(size);if (size > 100) return;
        w.name.resize(size);
        read(const_cast<char*>(w.name.data()), size);
    }

    void readVec(MyTypes::Vec3& p) {
        read(p.x);
        read(p.y);
        read(p.z);
    }

    template <typename T>
    void write(const T& v) {
        write(&v, 1);
    }

    template <typename T>
    void write(const T* v, size_t count) {
        const auto size = count * sizeof(T);
        std::memcpy(_pos, v, size);
        _pos += size;
    }

    template <typename T>
    void read(T& v) {
        read(&v, 1);
    }

    template <typename T>
    void read(T* v, size_t count) {
        //check for overflow
        const auto size = count * sizeof(T);
        if (std::distance(_pos, _end) >= size) {
            std::memcpy(v, _pos, size);
            _pos += size;
        }
    }

    //same implementation as in bitsery
    void readSize(size_t& size) {
        uint8_t hb{};
        read(hb);
        if (hb < 0x80u) {
            size = hb;
        } else {
            uint8_t lb{};
            read(lb);
            if (hb & 0x40u) {
                uint16_t lw{};
                read(lw);
                size = ((((hb & 0x3Fu) << 8) | lb) << 16) | lw;
            } else {
                size = ((hb & 0x7Fu) << 8) | lb;
            }
        }
    }

    //same implementation as in bitsery
    void writeSize(const size_t size) {
        if (size < 0x80u) {
            write(static_cast<uint8_t>(size));
        } else {
            if (size < 0x4000u) {
                write(static_cast<uint8_t>((size >> 8) | 0x80u));
                write(static_cast<uint8_t>(size));
            } else {
                write(static_cast<uint8_t>((size >> 24) | 0xC0u));
                write(static_cast<uint8_t>(size >> 16));
                write(static_cast<uint16_t>(size));
            }
        }
    }

    uint8_t* _pos{};
    uint8_t* _end{};
    std::array<uint8_t, 1000000> _buf{};
};


int main () {
    HandWrittenTest test{};
    runTest("hand written\n\tbuffer: std::array<uint8_t, 1000000>\n\tcheck size on reading\n\tcompress size", test, MONSTERS, SAMPLES);
    return 0;
}
