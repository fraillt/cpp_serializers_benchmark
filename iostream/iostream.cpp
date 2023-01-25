//MIT License
//
//Copyright (c) 2018 Niall Douglas <http://www.nedprod.com/>
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
#include <sstream>

namespace iostream_ops
{
  template<class T> inline void write(std::ostream &s, const std::vector<T> &v);
  inline void write(std::ostream &s, unsigned char v) { s.write((char *) &v, sizeof(v)); }
  inline void write(std::ostream &s, char v) { s.write((char *) &v, sizeof(v)); }
  inline void write(std::ostream &s, short v) { s.write((char *) &v, sizeof(v)); }
  inline void write(std::ostream &s, unsigned v) { s.write((char *) &v, sizeof(v)); }
  inline void write(std::ostream &s, float v) { s.write((char *) &v, sizeof(v)); }
  inline void write(std::ostream &s, const std::string &v)
  {
    unsigned l = v.size();
    write(s, l);
    s.write(v.c_str(), l);
  }
  inline void write(std::ostream &s, const MyTypes::Color &v)
  {
    write(s, (char) v);
  }
  inline void write(std::ostream &s, const MyTypes::Vec3 &v)
  {
    write(s, v.x);
    write(s, v.y);
    write(s, v.z);
  }
  inline void write(std::ostream &s, const MyTypes::Weapon &v)
  {
    write(s, v.name);
    write(s, v.damage);
  }
  inline void write(std::ostream &s, const MyTypes::Monster &v)
  {
    write(s, v.pos);
    write(s, v.mana);
    write(s, v.hp);
    write(s, v.name);
    write(s, v.inventory);
    write(s, v.color);
    write(s, v.weapons);
    write(s, v.equipped);
    write(s, v.path);
    write(s, v.image);
  }
  template<class T> inline void write(std::ostream &s, const std::vector<T> &v)
  {
    unsigned l = (unsigned) v.size();
    write(s, l);
    for(unsigned n = 0; n < l; n++)
    {
      write(s, v[n]);
    }
  }
  
  
  
  
  
  template<class T> inline void read(std::istream &s, std::vector<T> &v);
  inline void read(std::istream &s, unsigned char &v) { s.read((char *) &v, sizeof(v)); }
  inline void read(std::istream &s, char &v) { s.read((char *) &v, sizeof(v)); }
  inline void read(std::istream &s, short &v) { s.read((char *) &v, sizeof(v)); }
  inline void read(std::istream &s, unsigned &v) { s.read((char *) &v, sizeof(v)); }
  inline void read(std::istream &s, float &v) { s.read((char *) &v, sizeof(v)); }
  inline void read(std::istream &s, std::string &v)
  {
    unsigned l;
    read(s, l);
    v.resize(l);
    s.read((char *) v.c_str(), l);
  }
  inline void read(std::istream &s, MyTypes::Color &v)
  {
    char i;
    read(s, i);
    v = (MyTypes::Color) i;
  }
  inline void read(std::istream &s, MyTypes::Vec3 &v)
  {
    read(s, v.x);
    read(s, v.y);
    read(s, v.z);
  }
  inline void read(std::istream &s, MyTypes::Weapon &v)
  {
    read(s, v.name);
    read(s, v.damage);
  }
  inline void read(std::istream &s, MyTypes::Monster &v)
  {
    read(s, v.pos);
    read(s, v.mana);
    read(s, v.hp);
    read(s, v.name);
    read(s, v.inventory);
    read(s, v.color);
    read(s, v.weapons);
    read(s, v.equipped);
    read(s, v.path);
    read(s, v.image);
  }
  template<class T> inline void read(std::istream &s, std::vector<T> &v)
  {
    unsigned l;
    read(s, l);
    v.clear();
    v.reserve(l);
    for(unsigned n = 0; n < l; n++)
    {
      T a;
      read(s, a);
      v.push_back(std::move(a));
    }
  }
}

class IoStreams : public ISerializerTest {
public:

  Buf serialize(const std::vector<MyTypes::Monster> &data) override {
    using namespace iostream_ops;
    std::ostringstream os;
    write(os, data);
    //copy only once to permanent buffer
    if (_buf.empty()) {
      _buf = os.str();
    }

    return {
            reinterpret_cast<uint8_t *>(std::addressof(*_buf.begin())),
            _buf.size()
    };
  }

  void deserialize(Buf buf, std::vector<MyTypes::Monster> &resVec) override {
    using namespace iostream_ops;
    std::istringstream is(_buf);
    read(is, resVec);
  }

  TestInfo testInfo() const override {
    return {
      SerializationLibrary::IOSTREAM,
      "general",
      "use std::stringstream's internal std::string"
    };
  }

private:
    std::string _buf;
};


int main() {
    IoStreams test;
    return runTest(test);
}
