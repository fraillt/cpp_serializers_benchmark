# CPP serializers benchmark

### tested libraries
* [bitsery](https://github.com/fraillt/bitsery) 5.0.3
* [boost](https://www.boost.org/) 1.72.0
* [cereal](https://uscilab.github.io/cereal/) 1.3.0
* [flatbuffers](https://google.github.io/flatbuffers/) 1.11.0
* [yas](https://github.com/niXman/yas) 7.0.5
* [protobuf](https://developers.google.com/protocol-buffers/) 3.11.2
* [zpp](https://github.com/eyalz800/serializer) 0.4

## GCC 8.3.0 (Ubuntu 18.04 x64)

| library     | test case                                                  | bin size | data size | ser time | des time |
| ----------- | ---------------------------------------------------------- | -------- | --------- | -------- | -------- |
| bitsery     | general                                                    | 74592B   | 6913B     | 959ms    | 927ms    |
| bitsery     | brief syntax[<sup>1</sup>](#additional-tests-information)  | 70168B   | 6913B     | 852ms    | 870ms    |
| bitsery     | compatibility[<sup>2</sup>](#additional-tests-information) | 83128B   | 7113B     | 970ms    | 984ms    |
| bitsery     | compression[<sup>3</sup>](#additional-tests-information)   | 70416B   | 4213B     | 1282ms   | 1115ms   |
| bitsery     | fixed buffer[<sup>4</sup>](#additional-tests-information)  | 44896B   | 6913B     | 590ms    | 909ms    |
| bitsery     | stream[<sup>5</sup>](#additional-tests-information)        | 55384B   | 6913B     | 1358ms   | 4368ms   |
| bitsery     | unsafe read[<sup>6</sup>](#additional-tests-information)   | 74624B   | 6913B     | 960ms    | 748ms    |
| boost       | general                                                    | 270264B  | 11037B    | 9826ms   | 8313ms   |
| cereal      | general                                                    | 83792B   | 10413B    | 6324ms   | 5698ms   |
| flatbuffers | general                                                    | 65760B   | 14924B    | 5129ms   | 2142ms   |
| handwritten | general[<sup>7</sup>](#additional-tests-information)       | 39272B   | 10413B    | 1023ms   | 882ms    |
| handwritten | unsafe[<sup>8</sup>](#additional-tests-information)        | 39280B   | 10413B    | 1039ms   | 829ms    |
| iostream    | general[<sup>9</sup>](#additional-tests-information)       | 49136B   | 8413B     | 8154ms   | 8885ms   |
| protobuf    | general                                                    | 1968312B | 10018B    | 11966ms  | 13919ms  |
| protobuf    | arena[<sup>10</sup>](#additional-tests-information)        | 1968496B | 10018B    | 6786ms   | 8923ms   |
| yas         | general[<sup>11</sup>](#additional-tests-information)      | 59440B   | 10463B    | 1908ms   | 1217ms   |
| yas         | compression[<sup>12</sup>](#additional-tests-information)  | 72872B   | 7315B     | 2353ms   | 1726ms   |
| yas         | stream[<sup>13</sup>](#additional-tests-information)       | 50992B   | 10463B    | 7352ms   | 7548ms   |
| zpp         | general                                                    | 45360B   | 8413B     | 1036ms   | 1110ms   |

## Clang 9.0.0 (Ubuntu 18.04 x64)

| library     | test case                                                  | bin size | data size | ser time | des time |
| ----------- | ---------------------------------------------------------- | -------- | --------- | -------- | -------- |
| bitsery     | general                                                    | 45032B   | 6913B     | 1362ms   | 1368ms   |
| bitsery     | brief syntax[<sup>1</sup>](#additional-tests-information)  | 50920B   | 6913B     | 1676ms   | 1537ms   |
| bitsery     | compatibility[<sup>2</sup>](#additional-tests-information) | 49872B   | 7113B     | 1376ms   | 1411ms   |
| bitsery     | compression[<sup>3</sup>](#additional-tests-information)   | 50200B   | 4213B     | 2845ms   | 3136ms   |
| bitsery     | fixed buffer[<sup>4</sup>](#additional-tests-information)  | 40872B   | 6913B     | 599ms    | 1389ms   |
| bitsery     | stream[<sup>5</sup>](#additional-tests-information)        | 46512B   | 6913B     | 1643ms   | 4361ms   |
| bitsery     | unsafe read[<sup>6</sup>](#additional-tests-information)   | 45208B   | 6913B     | 1205ms   | 883ms    |
| boost       | general                                                    | 228752B  | 11037B    | 11173ms  | 8878ms   |
| cereal      | general                                                    | 53296B   | 10413B    | 7122ms   | 6078ms   |
| flatbuffers | general                                                    | 57888B   | 14924B    | 6618ms   | 2283ms   |
| handwritten | general[<sup>7</sup>](#additional-tests-information)       | 38608B   | 10413B    | 974ms    | 800ms    |
| handwritten | unsafe[<sup>8</sup>](#additional-tests-information)        | 38616B   | 10413B    | 982ms    | 755ms    |
| iostream    | general[<sup>9</sup>](#additional-tests-information)       | 40296B   | 8413B     | 7497ms   | 8885ms   |
| protobuf    | general                                                    | 1830616B | 10018B    | 10995ms  | 13609ms  |
| protobuf    | arena[<sup>10</sup>](#additional-tests-information)        | 1830824B | 10018B    | 5791ms   | 8267ms   |
| yas         | general[<sup>11</sup>](#additional-tests-information)      | 46704B   | 10463B    | 1489ms   | 1117ms   |
| yas         | compression[<sup>12</sup>](#additional-tests-information)  | 50928B   | 7315B     | 1994ms   | 1866ms   |
| yas         | stream[<sup>13</sup>](#additional-tests-information)       | 45936B   | 10463B    | 7093ms   | 7359ms   |
| zpp         | general                                                    | 47816B   | 8413B     | 1361ms   | 1119ms   |

### Additional tests information

1. forward\/backward compatibility enabled for `Monster`
2. all components of Vec3 is compressed in \[-1.0, 1.0\] range with precision 0.01
3. use non-resizable buffer uint8\_t\[150000\] for serialization
4. deserialization using `brief_syntax` syntax, similar to `cereal`
5. use stream input\/output adapter, underlying type is std::stringstream
6. on deserialization do not check for buffer end
7. check buffer size on reading, but writing buffer is preallocated std::array&lt;uint8\_t, 1000000&gt;
8. doesn't check for buffer size when reading, buffer: std::array&lt;uint8\_t, 1000000&gt;
9. use std::stringstream's internal std::string
10. use arena allocator
11. use yas::mem\_&lt;io&gt;stream as buffer
12. with yas::no\_header and yas::compacted
13. using std::stringstream

NOTE: tests for protobuf and flatbuffers is not 100% fair, because huge amount of CPU cycles goes to converting from generated types, to our defined types.

## Why another cpp serializers benchmark

I'm aware that [cpp-serializers](https://github.com/thekvs/cpp-serializers) project already exists, but it's testing set is way too simple and you cannot compile each project to separate executable.

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

All data is random generated, although seed is hard-coded to get predictable results when running same test multiple times.

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
* warmup step, in which serialization and deserialization is run 5 times, to warmup cpu cache and check if deserialized data equals to original data.
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
