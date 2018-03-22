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
#include <algorithm>
#include "monster_generated.h"

using namespace MyGame::Sample;

class FlatbuffersArchiver : public ISerializerTest {
public:

    auto createWeapon(flatbuffers::FlatBufferBuilder &builder, const MyTypes::Weapon &weapon) {
        auto name = builder.CreateString(weapon.name);
        return CreateWeapon(builder, name, weapon.damage);
    }

    Buf serialize(const std::vector<MyTypes::Monster> &data) override {
        _builder.Clear();
        std::vector<flatbuffers::Offset < Monster>>
        monstersVec{};
        for (auto &m:data) {
            // Create a FlatBuffer's `vector` from the `std::vector`.
            std::vector<flatbuffers::Offset < Weapon>>
            weaponsVec{};
            for (auto &w:m.weapons)
                weaponsVec.push_back(createWeapon(_builder, w));
            auto weapons = _builder.CreateVector(weaponsVec);

            // Second, serialize the rest of the objects needed by the Monster.
            auto position = Vec3(m.pos.x, m.pos.y, m.pos.z);
            auto name = _builder.CreateString(m.name);
            auto inventory = _builder.CreateVector(m.inventory);
            std::vector<Vec3> pathVec{};
            for (auto &p:m.path)
                pathVec.push_back(Vec3(p.x, p.y, p.z));
            auto path = _builder.CreateVectorOfStructs(pathVec);
            auto equiped = createWeapon(_builder, m.equipped);

            // Shortcut for creating monster with all fields set:
            monstersVec.push_back(
                    CreateMonster(_builder,
                                  &position,
                                  m.mana,
                                  m.hp,
                                  name,
                                  inventory,
                                  static_cast<Color>(m.color),
                                  weapons,
                                  equiped,
                                  path));
        }
        auto monsters = _builder.CreateVector(monstersVec);
        auto root = CreateMonstersList(_builder, monsters);
        _builder.Finish(root);
        return Buf{_builder.GetBufferPointer(), _builder.GetSize()};
    }

    void deserialize(Buf buf, std::vector<MyTypes::Monster> &res) override {
        auto ver = flatbuffers::Verifier(buf.ptr, buf.bytesCount);
        if (VerifyMonstersListBuffer(ver)) {
            auto monsters = GetMonstersList(buf.ptr);
            auto data = monsters->data();
            res.resize(data->size());
            for (auto i = 0u; i < data->size(); ++i) {
                auto m = data->Get(i);
                auto &resM = res[i];
                resM.equipped = MyTypes::Weapon{m->equipped()->name()->data(), m->equipped()->damage()};
                resM.name.resize(m->name()->size());
                //cannot memcpy, because data is not contigous on flatbuffers
                std::copy(m->name()->begin(), m->name()->end(), resM.name.begin());
                resM.color = static_cast<MyTypes::Color>(m->color());
                resM.hp = m->hp();
                resM.mana = m->mana();
                resM.pos = MyTypes::Vec3{m->pos()->x(), m->pos()->y(), m->pos()->z()};
                resM.inventory.resize(m->inventory()->size());
                std::copy(m->inventory()->begin(), m->inventory()->end(), resM.inventory.begin());
                resM.weapons.resize(m->weapons()->size());
                std::transform(m->weapons()->begin(), m->weapons()->end(), resM.weapons.begin(), [](const auto &w) {
                    return MyTypes::Weapon{w->name()->data(), w->damage()};
                });
                resM.path.resize(m->path()->size());
                std::transform(m->path()->begin(), m->path()->end(), resM.path.begin(), [](const auto &p) {
                    return MyTypes::Vec3{p->x(), p->y(), p->z()};
                });
            }
        }
    };

    TestInfo testInfo() const override {
        return {
                SerializationLibrary::FLATBUFFERS,
                "general",
                ""
        };
    }

private:
    flatbuffers::FlatBufferBuilder _builder;
};

int main() {
    FlatbuffersArchiver test;
    return runTest(test);
}