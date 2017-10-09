# bitsery benchmark

## testing setup

* monsters=50
* samples=300000

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

## GCC 7.1.0 (Ubuntu 16.04 x64)
| APP                           | binary size | data size | ser time | des time |
|-------------------------------|-------------|-----------|----------|----------|
| test_bitsery                  | 64704       | 7565      | 1229     | 1086     |
| test_bitsery_compatibility    | 69288       | 7669      | 1374     | 1327     |
| test_bitsery_compression      | 44000       | 4784      | 1370     | 2463     |
| test_bitsery_fixed_buffer     | 44176       | 7565      | 987      | 1080     |
| test_bitsery_sstream          | 49792       | 7565      | 4384     | 4424     |
| test_bitsery_verbose_syntax   | 65432       | 7565      | 1271     | 1343     |
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
| test_bitsery_compression      | 47144       | 4617      | 1445     | 3945     |
| test_bitsery_fixed_buffer     | 46360       | 7398      | 1054     | 1544     |
| test_bitsery_sstream          | 47192       | 7398      | 4347     | 4754     |
| test_bitsery_verbose_syntax   | 49704       | 7398      | 1534     | 1514     |
| test_cereal                   | 54032       | 11094     | 7513     | 6420     |
| test_flatbuffers              | 60304       | 15952     | 12414    | 3016     |
| test_hand_written             | 39576       | 7398      | 1057     | 971      |
| test_hand_written_no_checking | 39512       | 11094     | 1091     | 850      |
| test_yas                      | 56568       | 11144     | 3232     | 2182     |
| test_yas_compression          | 56368       | 8358      | 3629     | 3680     |
| test_yas_sstream              | 47000       | 11144     | 8466     | 8155     |