# CPP serializers benchmark

### tested libraries
* bitsery 4.3.0
* boost 1.66.0
* cereal 1.2.2
* flatbuffers 1.8.0
* yas 6.0.3
* zpp 0.1

## GCC 7.3.0 (Ubuntu 17.10 x64)

| library     | test case                                                    | bin size | data size | ser time | des time |
| ----------- | ------------------------------------------------------------ | -------- | --------- | -------- | -------- |
| bitsery     | general                                                      | 64656B   | 6913B     | 1155ms   | 1210ms   |
| bitsery     | compatibility[<sup>1</sup>](#additional-tests-information)   | 73240B   | 7016B     | 1196ms   | 1392ms   |
| bitsery     | compression[<sup>2</sup>](#additional-tests-information)     | 64576B   | 4213B     | 1343ms   | 1329ms   |
| bitsery     | fixed buffer[<sup>3</sup>](#additional-tests-information)    | 44184B   | 6913B     | 1103ms   | 1232ms   |
| bitsery     | flexible syntax[<sup>4</sup>](#additional-tests-information) | 64072B   | 6913B     | 1112ms   | 1002ms   |
| bitsery     | stream[<sup>5</sup>](#additional-tests-information)          | 54080B   | 6913B     | 1562ms   | 4380ms   |
| bitsery     | unsafe read[<sup>6</sup>](#additional-tests-information)     | 64744B   | 6913B     | 1177ms   | 1157ms   |
| boost       | general                                                      | 265560B  | 11037B    | 10248ms  | 8114ms   |
| cereal      | general                                                      | 73632B   | 10413B    | 6275ms   | 5347ms   |
| flatbuffers | general                                                      | 66088B   | 14924B    | 7135ms   | 2769ms   |
| handwritten | general[<sup>7</sup>](#additional-tests-information)         | 42736B   | 10413B    | 1012ms   | 890ms    |
| handwritten | unsafe[<sup>8</sup>](#additional-tests-information)          | 38648B   | 10413B    | 1033ms   | 825ms    |
| iostream    | general[<sup>9</sup>](#additional-tests-information)         | 48568B   | 8413B     | 8046ms   | 9000ms   |
| yas         | general[<sup>10</sup>](#additional-tests-information)        | 62976B   | 10463B    | 1561ms   | 1365ms   |
| yas         | compression[<sup>11</sup>](#additional-tests-information)    | 71664B   | 7315B     | 2162ms   | 1533ms   |
| yas         | stream[<sup>12</sup>](#additional-tests-information)         | 50112B   | 10463B    | 7977ms   | 7907ms   |
| zpp         | general                                                      | 44576B   | 8413B     | 1047ms   | 1101ms   |

## Clang 5.0.1 (Ubuntu 17.10 x64)

| library     | test case                                                    | bin size | data size | ser time | des time |
| ----------- | ------------------------------------------------------------ | -------- | --------- | -------- | -------- |
| bitsery     | general                                                      | 49104B   | 6913B     | 1398ms   | 1397ms   |
| bitsery     | compatibility[<sup>1</sup>](#additional-tests-information)   | 56000B   | 7016B     | 1545ms   | 1670ms   |
| bitsery     | compression[<sup>2</sup>](#additional-tests-information)     | 50208B   | 4213B     | 2683ms   | 3601ms   |
| bitsery     | fixed buffer[<sup>3</sup>](#additional-tests-information)    | 44864B   | 6913B     | 1015ms   | 1386ms   |
| bitsery     | flexible syntax[<sup>4</sup>](#additional-tests-information) | 51240B   | 6913B     | 1833ms   | 1430ms   |
| bitsery     | stream[<sup>5</sup>](#additional-tests-information)          | 50800B   | 6913B     | 1709ms   | 4341ms   |
| bitsery     | unsafe read[<sup>6</sup>](#additional-tests-information)     | 49384B   | 6913B     | 1438ms   | 970ms    |
| boost       | general                                                      | 222944B  | 11037B    | 11256ms  | 9588ms   |
| cereal      | general                                                      | 57560B   | 10413B    | 7384ms   | 6166ms   |
| flatbuffers | general                                                      | 59752B   | 14924B    | 8853ms   | 2468ms   |
| handwritten | general[<sup>7</sup>](#additional-tests-information)         | 39232B   | 10413B    | 975ms    | 791ms    |
| handwritten | unsafe[<sup>8</sup>](#additional-tests-information)          | 39232B   | 10413B    | 978ms    | 762ms    |
| iostream    | general[<sup>9</sup>](#additional-tests-information)         | 40800B   | 8413B     | 8096ms   | 8795ms   |
| yas         | general[<sup>10</sup>](#additional-tests-information)        | 56152B   | 10463B    | 2970ms   | 1860ms   |
| yas         | compression[<sup>11</sup>](#additional-tests-information)    | 56064B   | 7315B     | 3571ms   | 2296ms   |
| yas         | stream[<sup>12</sup>](#additional-tests-information)         | 46576B   | 10463B    | 7675ms   | 7564ms   |
| zpp         | general                                                      | 48200B   | 8413B     | 1336ms   | 1128ms   |

### Additional tests information

1. forward\/backward compatibility enabled for `Monster`
2. all components of Vec3 is compressed in \[-1.0, 1.0\] range with precision 0.01
3. use non-resizable buffer uint8\_t\[150000\] for serialization
4. deserialization using `flexible` syntax, similar to `cereal`
5. use stream input\/output adapter, underlying type is std::stringstream
6. on deserialization do not check for buffer end
7. check buffer size on reading, but writing buffer is preallocated std::array&lt;uint8\_t, 1000000&gt;
8. doesn't check for buffer size when reading, buffer: std::array&lt;uint8\_t, 1000000&gt;
9. use std::stringstream's internal std::string
10. use yas::mem\_&lt;io&gt;stream as buffer
11. with yas::no\_header and yas::compacted
12. using std::stringstream


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
    cat ./result/table.md
    ```
