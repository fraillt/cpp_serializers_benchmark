# CPP serializers benchmark

### tested libraries
* [bitsery](https://github.com/fraillt/bitsery) 5.0.0
* [boost](https://www.boost.org/) 1.70.0
* [cereal](https://uscilab.github.io/cereal/) 1.2.2
* [flatbuffers](https://google.github.io/flatbuffers/) 1.11.0
* [yas](https://github.com/niXman/yas) 7.0.2
* [protobuf](https://developers.google.com/protocol-buffers/) 3.8.0
* [zpp](https://github.com/eyalz800/serializer) 0.3

## GCC 8.3.0 (Ubuntu 18.04 x64)

| library     | test case                                                  | bin size | data size | ser time | des time |
| ----------- | ---------------------------------------------------------- | -------- | --------- | -------- | -------- |
| bitsery     | general                                                    | 74704B   | 6913B     | 1252ms   | 1170ms   |
| bitsery     | brief syntax[<sup>1</sup>](#additional-tests-information)  | 74376B   | 6913B     | 1044ms   | 1022ms   |
| bitsery     | compatibility[<sup>2</sup>](#additional-tests-information) | 78768B   | 7113B     | 1295ms   | 1213ms   |
| bitsery     | compression[<sup>3</sup>](#additional-tests-information)   | 74664B   | 4213B     | 1445ms   | 1325ms   |
| bitsery     | fixed buffer[<sup>4</sup>](#additional-tests-information)  | 45704B   | 6913B     | 1061ms   | 1203ms   |
| bitsery     | stream[<sup>5</sup>](#additional-tests-information)        | 55384B   | 6913B     | 1644ms   | 4350ms   |
| bitsery     | unsafe read[<sup>6</sup>](#additional-tests-information)   | 70808B   | 6913B     | 1276ms   | 1091ms   |
| boost       | general                                                    | 270264B  | 11037B    | 9952ms   | 8767ms   |
| cereal      | general                                                    | 81232B   | 10413B    | 6497ms   | 5470ms   |
| flatbuffers | general                                                    | 65760B   | 14924B    | 6762ms   | 2173ms   |
| handwritten | general[<sup>7</sup>](#additional-tests-information)       | 39272B   | 10413B    | 1042ms   | 896ms    |
| handwritten | unsafe[<sup>8</sup>](#additional-tests-information)        | 39280B   | 10413B    | 1095ms   | 819ms    |
| iostream    | general[<sup>9</sup>](#additional-tests-information)       | 49136B   | 8413B     | 7546ms   | 8915ms   |
| protobuf    | general                                                    | 1920384B | 10018B    | 12202ms  | 15096ms  |
| protobuf    | arena[<sup>10</sup>](#additional-tests-information)        | 1920568B | 10018B    | 6836ms   | 9919ms   |
| yas         | general[<sup>11</sup>](#additional-tests-information)      | 59576B   | 10463B    | 1352ms   | 1109ms   |
| yas         | compression[<sup>12</sup>](#additional-tests-information)  | 72840B   | 7315B     | 1673ms   | 1598ms   |
| yas         | stream[<sup>13</sup>](#additional-tests-information)       | 50992B   | 10463B    | 7377ms   | 7566ms   |
| zpp         | general                                                    | 45360B   | 8413B     | 1127ms   | 1102ms   |

## Clang 8.0.1 (Ubuntu 18.04 x64)

| library     | test case                                                  | bin size | data size | ser time | des time |
| ----------- | ---------------------------------------------------------- | -------- | --------- | -------- | -------- |
| bitsery     | general                                                    | 45776B   | 6913B     | 1857ms   | 1322ms   |
| bitsery     | brief syntax[<sup>1</sup>](#additional-tests-information)  | 51320B   | 6913B     | 1997ms   | 1382ms   |
| bitsery     | compatibility[<sup>2</sup>](#additional-tests-information) | 50608B   | 7113B     | 1900ms   | 1394ms   |
| bitsery     | compression[<sup>3</sup>](#additional-tests-information)   | 50888B   | 4213B     | 3215ms   | 2976ms   |
| bitsery     | fixed buffer[<sup>4</sup>](#additional-tests-information)  | 45024B   | 6913B     | 1029ms   | 1404ms   |
| bitsery     | stream[<sup>5</sup>](#additional-tests-information)        | 46536B   | 6913B     | 1739ms   | 4406ms   |
| bitsery     | unsafe read[<sup>6</sup>](#additional-tests-information)   | 45664B   | 6913B     | 1845ms   | 927ms    |
| boost       | general                                                    | 235752B  | 11037B    | 12056ms  | 10384ms  |
| cereal      | general                                                    | 52904B   | 10413B    | 7328ms   | 6130ms   |
| flatbuffers | general                                                    | 57912B   | 14924B    | 8107ms   | 2296ms   |
| handwritten | general[<sup>7</sup>](#additional-tests-information)       | 38632B   | 10413B    | 1011ms   | 796ms    |
| handwritten | unsafe[<sup>8</sup>](#additional-tests-information)        | 38632B   | 10413B    | 984ms    | 749ms    |
| iostream    | general[<sup>9</sup>](#additional-tests-information)       | 40312B   | 8413B     | 7756ms   | 8914ms   |
| protobuf    | general                                                    | 1762016B | 10018B    | 11198ms  | 15622ms  |
| protobuf    | arena[<sup>10</sup>](#additional-tests-information)        | 1762224B | 10018B    | 6040ms   | 10418ms  |
| yas         | general[<sup>11</sup>](#additional-tests-information)      | 46728B   | 10463B    | 1356ms   | 1027ms   |
| yas         | compression[<sup>12</sup>](#additional-tests-information)  | 51384B   | 7315B     | 1926ms   | 1589ms   |
| yas         | stream[<sup>13</sup>](#additional-tests-information)       | 46112B   | 10463B    | 7254ms   | 7728ms   |
| zpp         | general                                                    | 47832B   | 8413B     | 1297ms   | 1137ms   |

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
