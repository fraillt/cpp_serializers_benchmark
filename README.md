# CPP serializers benchmark

### tested libraries
* [bitsery](https://github.com/fraillt/bitsery) 5.2.1
* [boost](https://www.boost.org/) 1.77.0
* [cereal](https://uscilab.github.io/cereal/) 1.3.0
* [flatbuffers](https://google.github.io/flatbuffers/) 2.0.0
* [yas](https://github.com/niXman/yas) 7.1.0
* [protobuf](https://developers.google.com/protocol-buffers/) 3.17.3
* [zpp](https://github.com/eyalz800/serializer) 0.5
* [msgpack](https://github.com/msgpack/msgpack-c) 3.3.0

## GCC 10.3.0 (Ubuntu 20.04 x64)

| library     | test case                                                  | bin size | data size | ser time | des time |
| ----------- | ---------------------------------------------------------- | -------- | --------- | -------- | -------- |
| bitsery     | general                                                    | 70608B   | 6913B     | 1119ms   | 1166ms   |
| bitsery     | brief syntax[<sup>1</sup>](#additional-tests-information)  | 70584B   | 6913B     | 1047ms   | 1067ms   |
| bitsery     | compatibility[<sup>2</sup>](#additional-tests-information) | 70880B   | 7113B     | 1136ms   | 1039ms   |
| bitsery     | compression[<sup>3</sup>](#additional-tests-information)   | 70552B   | 4213B     | 1607ms   | 1492ms   |
| bitsery     | fixed buffer[<sup>4</sup>](#additional-tests-information)  | 53368B   | 6913B     | 702ms    | 1166ms   |
| bitsery     | stream[<sup>5</sup>](#additional-tests-information)        | 59312B   | 6913B     | 1285ms   | 5777ms   |
| bitsery     | unsafe read[<sup>6</sup>](#additional-tests-information)   | 66536B   | 6913B     | 1491ms   | 1175ms   |
| boost       | general                                                    | 278656B  | 11037B    | 15391ms  | 12912ms  |
| cereal      | general                                                    | 62088B   | 10413B    | 10518ms  | 10245ms  |
| flatbuffers | general                                                    | 70728B   | 14924B    | 9075ms   | 3701ms   |
| handwritten | general[<sup>7</sup>](#additional-tests-information)       | 47736B   | 10413B    | 1409ms   | 1509ms   |
| handwritten | unsafe[<sup>8</sup>](#additional-tests-information)        | 47744B   | 10413B    | 1424ms   | 1165ms   |
| iostream    | general[<sup>9</sup>](#additional-tests-information)       | 53568B   | 8413B     | 10695ms  | 13751ms  |
| msgpack     | general                                                    | 88840B   | 8857B     | 3340ms   | 13842ms  |
| protobuf    | general                                                    | 2086616B | 10018B    | 21229ms  | 22077ms  |
| protobuf    | arena[<sup>10</sup>](#additional-tests-information)        | 2086624B | 10018B    | 10163ms  | 12062ms  |
| yas         | general[<sup>11</sup>](#additional-tests-information)      | 60752B   | 10463B    | 2107ms   | 1554ms   |
| yas         | compression[<sup>12</sup>](#additional-tests-information)  | 65072B   | 7315B     | 2677ms   | 2392ms   |
| yas         | stream[<sup>13</sup>](#additional-tests-information)       | 55888B   | 10463B    | 10489ms  | 11289ms  |
| zpp         | general                                                    | 57816B   | 8413B     | 1446ms   | 1588ms   |

## Clang 12.0.0 (Ubuntu 20.04 x64)


| library     | test case                                                  | bin size | data size | ser time | des time |
| ----------- | ---------------------------------------------------------- | -------- | --------- | -------- | -------- |
| bitsery     | general                                                    | 49616B   | 6913B     | 1516ms   | 1450ms   |
| bitsery     | brief syntax[<sup>1</sup>](#additional-tests-information)  | 55400B   | 6913B     | 1948ms   | 1546ms   |
| bitsery     | compatibility[<sup>2</sup>](#additional-tests-information) | 54448B   | 7113B     | 1716ms   | 1580ms   |
| bitsery     | compression[<sup>3</sup>](#additional-tests-information)   | 54784B   | 4213B     | 3167ms   | 3222ms   |
| bitsery     | fixed buffer[<sup>4</sup>](#additional-tests-information)  | 45248B   | 6913B     | 690ms    | 1518ms   |
| bitsery     | stream[<sup>5</sup>](#additional-tests-information)        | 54816B   | 6913B     | 1661ms   | 4684ms   |
| bitsery     | unsafe read[<sup>6</sup>](#additional-tests-information)   | 49784B   | 6913B     | 1639ms   | 957ms    |
| boost       | general                                                    | 236840B  | 11037B    | 12616ms  | 10876ms  |
| cereal      | general                                                    | 61520B   | 10413B    | 7824ms   | 6907ms   |
| flatbuffers | general                                                    | 58544B   | 14924B    | 8429ms   | 2955ms   |
| handwritten | general[<sup>7</sup>](#additional-tests-information)       | 43168B   | 10413B    | 1143ms   | 1004ms   |
| handwritten | unsafe[<sup>8</sup>](#additional-tests-information)        | 43168B   | 10413B    | 1155ms   | 911ms    |
| iostream    | general[<sup>9</sup>](#additional-tests-information)       | 48688B   | 8413B     | 8506ms   | 10731ms  |
| msgpack     | general                                                    | 77304B   | 8857B     | 2865ms   | 12362ms  |
| protobuf    | general                                                    | 1781640B | 10018B    | 15266ms  | 17188ms  |
| protobuf    | arena[<sup>10</sup>](#additional-tests-information)        | 1781672B | 10018B    | 7517ms   | 9792ms   |
| yas         | general[<sup>11</sup>](#additional-tests-information)      | 55224B   | 10463B    | 1707ms   | 1433ms   |
| yas         | compression[<sup>12</sup>](#additional-tests-information)  | 55544B   | 7315B     | 2309ms   | 2453ms   |
| yas         | stream[<sup>13</sup>](#additional-tests-information)       | 50632B   | 10463B    | 8333ms   | 9225ms   |
| zpp         | general                                                    | 56024B   | 8413B     | 2284ms   | 1395ms   |

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
