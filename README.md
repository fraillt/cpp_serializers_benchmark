# CPP serializers benchmark

### tested libraries
* bitsery 4.5.1
* boost 1.69.0
* cereal 1.2.2
* flatbuffers 1.10.0
* yas 7.0.2
* zpp 0.3

## GCC 8.2.0 (Ubuntu 18.04 x64)

| library     | test case                                                    | bin size | data size | ser time | des time |
| ----------- | ------------------------------------------------------------ | -------- | --------- | -------- | -------- |
| bitsery     | general                                                      | 69576B   | 6913B     | 1291ms   | 1199ms   |
| bitsery     | compatibility[<sup>1</sup>](#additional-tests-information)   | 82824B   | 7016B     | 1334ms   | 1293ms   |
| bitsery     | compression[<sup>2</sup>](#additional-tests-information)     | 69496B   | 4213B     | 1518ms   | 1297ms   |
| bitsery     | fixed buffer[<sup>3</sup>](#additional-tests-information)    | 44864B   | 6913B     | 1082ms   | 1197ms   |
| bitsery     | flexible syntax[<sup>4</sup>](#additional-tests-information) | 73272B   | 6913B     | 1218ms   | 1045ms   |
| bitsery     | stream[<sup>5</sup>](#additional-tests-information)          | 50616B   | 6913B     | 1687ms   | 4584ms   |
| bitsery     | unsafe read[<sup>6</sup>](#additional-tests-information)     | 69672B   | 6913B     | 1241ms   | 1189ms   |
| boost       | general                                                      | 270072B  | 11037B    | 10380ms  | 9038ms   |
| cereal      | general                                                      | 81328B   | 10413B    | 6907ms   | 5485ms   |
| flatbuffers | general                                                      | 70200B   | 14924B    | 7370ms   | 2567ms   |
| handwritten | general[<sup>7</sup>](#additional-tests-information)         | 39384B   | 10413B    | 1069ms   | 978ms    |
| handwritten | unsafe[<sup>8</sup>](#additional-tests-information)          | 39392B   | 10413B    | 1107ms   | 857ms    |
| iostream    | general[<sup>9</sup>](#additional-tests-information)         | 49040B   | 8413B     | 7859ms   | 8898ms   |
| yas         | general[<sup>10</sup>](#additional-tests-information)        | 59688B   | 10463B    | 1336ms   | 1175ms   |
| yas         | compression[<sup>11</sup>](#additional-tests-information)    | 72944B   | 7315B     | 2066ms   | 1624ms   |
| yas         | stream[<sup>12</sup>](#additional-tests-information)         | 50992B   | 10463B    | 7876ms   | 7899ms   |
| zpp         | general                                                      | 45472B   | 8413B     | 1065ms   | 1129ms   |

## Clang 8.0.0 (Ubuntu 18.04 x64)

| library     | test case                                                    | bin size | data size | ser time | des time |
| ----------- | ------------------------------------------------------------ | -------- | --------- | -------- | -------- |
| bitsery     | general                                                      | 45048B   | 6913B     | 1817ms   | 1448ms   |
| bitsery     | compatibility[<sup>1</sup>](#additional-tests-information)   | 55848B   | 7016B     | 1985ms   | 1745ms   |
| bitsery     | compression[<sup>2</sup>](#additional-tests-information)     | 49936B   | 4213B     | 3038ms   | 3111ms   |
| bitsery     | fixed buffer[<sup>3</sup>](#additional-tests-information)    | 40352B   | 6913B     | 1072ms   | 1461ms   |
| bitsery     | flexible syntax[<sup>4</sup>](#additional-tests-information) | 50608B   | 6913B     | 1989ms   | 1552ms   |
| bitsery     | stream[<sup>5</sup>](#additional-tests-information)          | 46336B   | 6913B     | 1754ms   | 4292ms   |
| bitsery     | unsafe read[<sup>6</sup>](#additional-tests-information)     | 44960B   | 6913B     | 1894ms   | 973ms    |
| boost       | general                                                      | 235680B  | 11037B    | 11883ms  | 10589ms  |
| cereal      | general                                                      | 53192B   | 10413B    | 7472ms   | 6139ms   |
| flatbuffers | general                                                      | 58072B   | 14924B    | 8026ms   | 2806ms   |
| handwritten | general[<sup>7</sup>](#additional-tests-information)         | 38920B   | 10413B    | 983ms    | 779ms    |
| handwritten | unsafe[<sup>8</sup>](#additional-tests-information)          | 38920B   | 10413B    | 974ms    | 783ms    |
| iostream    | general[<sup>9</sup>](#additional-tests-information)         | 40600B   | 8413B     | 8138ms   | 8907ms   |
| yas         | general[<sup>10</sup>](#additional-tests-information)        | 46840B   | 10463B    | 1402ms   | 1010ms   |
| yas         | compression[<sup>11</sup>](#additional-tests-information)    | 51504B   | 7315B     | 1963ms   | 1540ms   |
| yas         | stream[<sup>12</sup>](#additional-tests-information)         | 46352B   | 10463B    | 7678ms   | 7767ms   |
| zpp         | general                                                      | 47896B   | 8413B     | 1345ms   | 1191ms   |

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
