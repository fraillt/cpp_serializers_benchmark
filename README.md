# CPP serializers benchmark

### tested libraries

* [bitsery](https://github.com/fraillt/bitsery) 5.2.1
* [boost](https://www.boost.org/) 1.77.0
* [cereal](https://uscilab.github.io/cereal/) 1.3.0
* [flatbuffers](https://google.github.io/flatbuffers/) 2.0.0
* [yas](https://github.com/niXman/yas) 7.1.0
* [protobuf](https://developers.google.com/protocol-buffers/) 3.17.3
* [zpp_bits](https://github.com/eyalz800/zpp_bits) 2.0
* [msgpack](https://github.com/msgpack/msgpack-c) 3.3.0

## GCC 11 (Ubuntu 22.04 x64)

Base monster + image 3-channel 24bit 3840x2160.

Time of encoding/decoding the image was not taken into account.

| library     | test case                                                  | data size  | ser time per sample | des time per sample |
|-------------|------------------------------------------------------------|------------|---------------------|---------------------|
| bitsery     | general                                                    | 124.648 MB | 30.60 ms            | 17.56 ms            |
| bitsery     | brief syntax[<sup>1</sup>](#additional-tests-information)  | 124.648 MB | 30.84 ms            | 17.70 ms            |
| bitsery     | compatibility[<sup>2</sup>](#additional-tests-information) | 124.648 MB | 30.69 ms            | 17.69 ms            |
| bitsery     | compression[<sup>3</sup>](#additional-tests-information)   | 124.648 MB | 32.30 ms            | 17.60 ms            |
| bitsery     | fixed buffer[<sup>4</sup>](#additional-tests-information)  | ---        | ---                 | ---                 |
| bitsery     | stream[<sup>5</sup>](#additional-tests-information)        | 124.648 MB | 153.77 ms           | 107.22 ms           |
| bitsery     | unsafe read[<sup>6</sup>](#additional-tests-information)   | 124.648 MB | 30.84 ms            | 17.74 ms            |
| boost       | general                                                    | ---        | ---                 | ---                 |
| cereal      | general                                                    | 124.648 MB | 151.18 ms           | 105.81 ms           |
| flatbuffers | general                                                    | 124.649 MB | 177.42 ms           | 51.85 ms            |
| handwritten | general[<sup>7</sup>](#additional-tests-information)       | ---        | ---                 | ---                 |
| handwritten | unsafe[<sup>8</sup>](#additional-tests-information)        | ---        | ---                 | ---                 |
| iostream    | general[<sup>9</sup>](#additional-tests-information)       | 124.648 MB | 1725.35 ms          | 1744.32 ms          |
| msgpack     | general                                                    | 124.648 MB | 17.28 ms            | 100.12 ms           |
| protobuf    | general                                                    | ---        | ---                 | ---                 |
| protobuf    | arena[<sup>10</sup>](#additional-tests-information)        | ---        | ---                 | ---                 |
| yas         | general[<sup>11</sup>](#additional-tests-information)      | 124.648 MB | 106.26 ms           | 17.55 ms            |
| yas         | compression[<sup>12</sup>](#additional-tests-information)  | 124.648 MB | 107.86 ms           | 17.83 ms            |
| yas         | stream[<sup>13</sup>](#additional-tests-information)       | 124.648 MB | 148.79 ms           | 106.36 ms           |
| zpp_bits    | general                                                    | 124.648 MB | 17.26 ms            | 17.37 ms            |
| zpp_bits    | fixed buffer                                               | ---        | ---                 | ---                 |

### Additional tests information

1. deserialization using `brief\_syntax`, similar to `cereal`
2. forward\/backward compatibility enabled for `Monster`
3. all components of Vec3 is compressed in \[-1.0, 1.0\] range with precision 0.01
4. use non-resizable buffer uint8\_t\[150000\] for serialization
5. use stream input\/output adapter, underlying type is std::stringstream
6. on deserialization do not check for errors
7. check buffer size on reading, but writing buffer is preallocated std::array&lt;uint8\_t, 1000000&gt;
8. doesn't check for buffer size when reading, buffer: std::array&lt;uint8\_t, 1000000&gt;
9. use std::stringstream's internal std::string
10. use arena allocator
11. use yas::mem\_&lt;io&gt;stream as buffer
12. with yas::no\_header and yas::compacted
13. using std::stringstream

NOTE: tests for protobuf and flatbuffers is not 100% fair, because huge amount of CPU cycles goes to converting from
generated types, to our defined types.

## Why another cpp serializers benchmark

I'm aware that [cpp-serializers](https://github.com/thekvs/cpp-serializers) project already exists, but it's testing set
is way too simple and you cannot compile each project to separate executable.

This project contains more realisting data that needs to be serialized.

```cpp
    enum Color : uint8_t {
Red,
Green,
Blue
};

struct Vec3 {
float x;
float y;
float z;
};

struct Weapon {
std::string name;
int16_t damage;
};

struct Monster {
Vec3 pos;
int16_t mana;
int16_t hp;
std::string name;
std::vector<uint8_t> inventory;
Color color;
std::vector<Weapon> weapons;
Weapon equipped;
std::vector<Vec3> path;
};
```

All data is random generated, although seed is hard-coded to get predictable results when running same test multiple
times.

All projects implement same interface for serialization and deserialization.

```cpp
struct Buf {
    const uint8_t* ptr;
    size_t bytesCount;
};

class ISerializerTest {
public:
    virtual Buf serialize(const std::vector<MyTypes::Monster>& data) = 0;
    virtual void deserialize(Buf buf, std::vector<MyTypes::Monster>& res) = 0;
    virtual ~ISerializerTest() = default;
};
```

Testing routine consist of few steps:

* data generation step, in which monsters are generated (default 50 monsters)
* warmup step, in which serialization and deserialization is run 5 times, to warmup cpu cache and check if deserialized
  data equals to original data.
* measurement step, runs serialization and deserialization multiple times (default 300000 samples),
  deserialization happens on same object, to avoid costly allocate operations for new object construction each time.

## Building & testing

1. Build project
    ```bash
    mkdir build && cd build
    cmake ..
    make
    ```
2. Run tests with `ctest -VV` **OR**
3. Generate testing results *(requires nodejs)*
    ```bash
    cd ../tools/
    npm install
    npm start
    ```
