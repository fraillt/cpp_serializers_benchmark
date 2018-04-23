# CPP serializers benchmark

### tested libraries
* bitsery 4.2.1
* boost 1.66.0
* cereal 1.2.2
* flatbuffers 1.8.0
* yas 6.0.3
* zpp 0.1

## GCC 7.2.0 (Ubuntu 17.10 x64)

| library     | test case                                                    | bin size | data size | ser time | des time |
| ----------- | ------------------------------------------------------------ | -------- | --------- | -------- | -------- |
| bitsery     | general                                                      | 64656B   | 6913B     | 1176ms   | 1158ms   |
| bitsery     | compatibility[<sup>1</sup>](#additional-tests-information)   | 73240B   | 7016B     | 1197ms   | 1410ms   |
| bitsery     | compression[<sup>2</sup>](#additional-tests-information)     | 64576B   | 4213B     | 1343ms   | 1298ms   |
| bitsery     | fixed buffer[<sup>3</sup>](#additional-tests-information)    | 44184B   | 6913B     | 1118ms   | 1200ms   |
| bitsery     | flexible syntax[<sup>4</sup>](#additional-tests-information) | 64072B   | 6913B     | 1125ms   | 948ms    |
| bitsery     | stream[<sup>5</sup>](#additional-tests-information)          | 54080B   | 6913B     | 1609ms   | 4951ms   |
| boost       | general                                                      | 265560B  | 11037B    | 10331ms  | 8558ms   |
| cereal      | general                                                      | 73632B   | 10413B    | 6493ms   | 5482ms   |
| flatbuffers | general                                                      | 66088B   | 14924B    | 7297ms   | 2789ms   |
| handwritten | general[<sup>6</sup>](#additional-tests-information)         | 42736B   | 10413B    | 1045ms   | 885ms    |
| handwritten | unsafe[<sup>7</sup>](#additional-tests-information)          | 38648B   | 10413B    | 1036ms   | 846ms    |
| yas         | general[<sup>8</sup>](#additional-tests-information)         | 62976B   | 10463B    | 1613ms   | 1407ms   |
| yas         | compression[<sup>9</sup>](#additional-tests-information)     | 71664B   | 7315B     | 2166ms   | 1595ms   |
| yas         | stream[<sup>10</sup>](#additional-tests-information)         | 50112B   | 10463B    | 8514ms   | 7769ms   |
| zpp         | general                                                      | 44576B   | 8413B     | 1021ms   | 1061ms   |

## Clang 5.0.0 (Ubuntu 17.10 x64)

| library     | test case                                                    | bin size | data size | ser time | des time |
| ----------- | ------------------------------------------------------------ | -------- | --------- | -------- | -------- |
| bitsery     | general                                                      | 48968B   | 6913B     | 1369ms   | 1322ms   |
| bitsery     | compatibility[<sup>1</sup>](#additional-tests-information)   | 55864B   | 7016B     | 1609ms   | 1598ms   |
| bitsery     | compression[<sup>2</sup>](#additional-tests-information)     | 50072B   | 4213B     | 2736ms   | 3669ms   |
| bitsery     | fixed buffer[<sup>3</sup>](#additional-tests-information)    | 40632B   | 6913B     | 1051ms   | 1341ms   |
| bitsery     | stream[<sup>4</sup>](#additional-tests-information)          | 46568B   | 6913B     | 1768ms   | 4679ms   |
| bitsery     | flexible syntax[<sup>5</sup>](#additional-tests-information) | 51096B   | 6913B     | 1754ms   | 1425ms   |
| boost       | general                                                      | 222808B  | 11037B    | 11464ms  | 9882ms   |
| cereal      | general                                                      | 53328B   | 10413B    | 8207ms   | 6260ms   |
| flatbuffers | general                                                      | 59616B   | 14924B    | 8973ms   | 2617ms   |
| handwritten | general[<sup>6</sup>](#additional-tests-information)         | 39096B   | 10413B    | 1016ms   | 785ms    |
| handwritten | unsafe[<sup>7</sup>](#additional-tests-information)          | 39096B   | 10413B    | 990ms    | 755ms    |
| yas         | general[<sup>8</sup>](#additional-tests-information)         | 56016B   | 10463B    | 3065ms   | 1801ms   |
| yas         | compression[<sup>9</sup>](#additional-tests-information)     | 55928B   | 7315B     | 3549ms   | 2306ms   |
| yas         | stream[<sup>10</sup>](#additional-tests-information)         | 46440B   | 10463B    | 8387ms   | 7802ms   |
| zpp         | general                                                      | 48064B   | 8413B     | 1313ms   | 1124ms   |

### Additional tests information

1. forward\/backward compatibility enabled for `Monster`
2. all components of Vec3 is compressed in \[-1.0, 1.0\] range with precision 0.01
3. use non-resizable buffer uint8\_t\[150000\] for serialization
4. use stream input\/output adapter, underlying type is std::stringstream
5. deserialization using `flexible` syntax, similar to `cereal`
6. check buffer size on reading, but writing buffer is preallocated std::array&lt;uint8\_t, 1000000&gt;
7. doesn't check for buffer size when reading, buffer: std::array&lt;uint8\_t, 1000000&gt;
8. use yas::mem\_&lt;io&gt;stream as buffer
9. with yas::no\_header and yas::compacted
10. using std::stringstream

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
