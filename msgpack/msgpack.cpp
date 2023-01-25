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
#include <msgpack.hpp>

MSGPACK_ADD_ENUM(MyTypes::Color);

namespace msgpack {
MSGPACK_API_VERSION_NAMESPACE(MSGPACK_DEFAULT_API_NS) {
namespace adaptor {

template<>
struct pack<MyTypes::Vec3> {
    template <typename Stream>
    packer<Stream>& operator()(msgpack::packer<Stream>& msgpack, MyTypes::Vec3 const& var) const {
        msgpack.pack_array(3);
        msgpack.pack(var.x);
        msgpack.pack(var.y);
        msgpack.pack(var.z);
        return msgpack;
    }
};
template<>
struct convert<MyTypes::Vec3> {
    msgpack::object const& operator()(msgpack::object const& o, MyTypes::Vec3& v) const {
        if (o.type != msgpack::type::ARRAY) throw msgpack::type_error();
        if (o.via.array.size != 3) throw msgpack::type_error();
        v = MyTypes::Vec3{
            o.via.array.ptr[0].as<float>(),
            o.via.array.ptr[1].as<float>(),
            o.via.array.ptr[2].as<float>()
        };
        return o;
    }
};

template<>
struct pack<MyTypes::Weapon> {
    template <typename Stream>
    packer<Stream>& operator()(msgpack::packer<Stream>& msgpack, MyTypes::Weapon const& var) const {
        msgpack.pack_array(2);
        msgpack.pack(var.name);
        msgpack.pack(var.damage);
        return msgpack;
    }
};

template<>
struct pack<cv::Mat> {
    template <typename Stream>
    packer<Stream>& operator()(msgpack::packer<Stream>& msgpack, cv::Mat const& var) const {
        std::vector<uint8_t> buffer;
        cv::imencode(".png", var, buffer);
        msgpack.pack(buffer);
        return msgpack;
    }
};


template<>
struct convert<MyTypes::Weapon> {
    msgpack::object const& operator()(msgpack::object const& o, MyTypes::Weapon& v) const {
        if (o.type != msgpack::type::ARRAY) throw msgpack::type_error();
        if (o.via.array.size != 2) throw msgpack::type_error();
        v = MyTypes::Weapon{
            o.via.array.ptr[0].as<std::string>(),
            o.via.array.ptr[1].as<int16_t>()
        };
        return o;
    }
};

template<>
struct pack<MyTypes::Monster> {
    template <typename Stream>
    packer<Stream>& operator()(msgpack::packer<Stream>& msgpack, MyTypes::Monster const& var) const {
        msgpack.pack_array(10);
        msgpack.pack(var.pos);
        msgpack.pack(var.mana);
        msgpack.pack(var.hp);
        msgpack.pack(var.name);
        msgpack.pack(var.inventory);
        msgpack.pack(var.color);
        msgpack.pack(var.weapons);
        msgpack.pack(var.equipped);
        msgpack.pack(var.path);
        msgpack.pack(var.image);
        return msgpack;
    }
};
template<>
struct convert<MyTypes::Monster> {
    msgpack::object const& operator()(msgpack::object const& o, MyTypes::Monster& v) const {
        if (o.type != msgpack::type::ARRAY) throw msgpack::type_error();
        if (o.via.array.size != 10) throw msgpack::type_error();

        v = MyTypes::Monster{
            o.via.array.ptr[0].as<MyTypes::Vec3>(),
            o.via.array.ptr[1].as<int16_t>(),
            o.via.array.ptr[2].as<int16_t>(),
            o.via.array.ptr[3].as<std::string>(),
            o.via.array.ptr[4].as<std::vector<uint8_t>>(),
            o.via.array.ptr[5].as<MyTypes::Color>(),
            o.via.array.ptr[6].as<std::vector<MyTypes::Weapon>>(),
            o.via.array.ptr[7].as<MyTypes::Weapon>(),
            o.via.array.ptr[8].as<std::vector<MyTypes::Vec3>>(),
            o.via.array.ptr[9].as<std::vector<uint8_t>>()
        };
        return o;
    }
};
}
}
}

class msgpackArchiver : public ISerializerTest {
public:

    Buf serialize(const std::vector<MyTypes::Monster> &data) override {
        _buf.clear();
        msgpack::pack(_buf, data);

        return Buf{reinterpret_cast<uint8_t *>(_buf.data()), _buf.size()};
    }

    void deserialize(Buf buf, std::vector<MyTypes::Monster> &res) override {
        msgpack::object_handle oh = msgpack::unpack(_buf.data(), _buf.size());
        msgpack::object obj = oh.get();
        obj.convert(res);
    }

    TestInfo testInfo() const override {
        return {
            SerializationLibrary::MSGPACK,
            "general",
            ""
        };
    }

private:
    msgpack::sbuffer _buf{};
};

int main() {
    msgpackArchiver test{};
    return runTest(test);
}
