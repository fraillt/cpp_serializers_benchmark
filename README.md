# CPP serializers benchmark

### tested libraries
* bitsery 4.1.0
* boost 1.65.1
* cereal 1.2.2
* flatbuffers 1.7.1
* yas 5.0.0

## GCC 7.1.0 (Ubuntu 16.04 x64)
| APP                           | binary size | data size | ser time | des time |
|-------------------------------|-------------|-----------|----------|----------|
| test_bitsery                  | 64704       | 7565      | 1229     | 1086     |
| test_bitsery_compatibility    | 69288       | 7669      | 1374     | 1327     |
| test_bitsery_compression      | 64880       | 4784      | 1641     | 2462     |
| test_bitsery_fixed_buffer     | 44176       | 7565      | 987      | 1080     |
| test_bitsery_sstream          | 50120       | 7565      | 1467     | 4779     |
| test_bitsery_verbose_syntax   | 65432       | 7565      | 1271     | 1343     |
| test_boost                    | 252752      | 11885     | 10855    | 9120     |
| test_cereal                   | 74848       | 11261     | 6708     | 6799     |
| test_flatbuffers              | 67032       | 16100     | 8793     | 3028     |
| test_hand_written             | 43496       | 7565      | 1095     | 1467     |
| test_hand_written_no_checking | 39408       | 11261     | 1074     | 896      |
| test_yas                      | 63864       | 11311     | 1616     | 1712     |
| test_yas_compression          | 72688       | 8523      | 2387     | 2890     |
| test_yas_sstream              | 51048       | 11311     | 8627     | 7885     |

## Clang 4.0.0 (Ubuntu 16.04 x64)

| APP                           | binary size | data size | ser time | des time |
|-------------------------------|-------------|-----------|----------|----------|
| test_bitsery                  | 51328       | 7398      | 1848     | 1601     |
| test_bitsery_compatibility    | 57768       | 7502      | 2137     | 1803     |
| test_bitsery_compression      | 52040       | 4617      | 3060     | 3937     |
| test_bitsery_fixed_buffer     | 46360       | 7398      | 1054     | 1544     |
| test_bitsery_sstream          | 52568       | 7398      | 1862     | 5077     |
| test_bitsery_verbose_syntax   | 49704       | 7398      | 1534     | 1514     |
| test_boost                    | 230696      | 11718     | 12493    | 10133    |
| test_cereal                   | 54032       | 11094     | 7513     | 6420     |
| test_flatbuffers              | 60304       | 15952     | 12414    | 3016     |
| test_hand_written             | 39576       | 7398      | 1057     | 971      |
| test_hand_written_no_checking | 39512       | 11094     | 1091     | 850      |
| test_yas                      | 56568       | 11144     | 3232     | 2182     |
| test_yas_compression          | 56368       | 8358      | 3629     | 3680     |
| test_yas_sstream              | 47000       | 11144     | 8466     | 8155     |

`monsters = 50, running samples = 300000`

*data is generated using std implementation of `<random>`*

*implementations of uniform_xxx_distribution is different on different systems*

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

