
#ifndef PROTOBUF_SERIALIZE_UTILS_H
#define PROTOBUF_SERIALIZE_UTILS_H

#include <testing/test.h>
#include <algorithm>

#include "monster.pb.h"

using namespace mygame;
using namespace google::protobuf;

void serializeWeapon(Weapon* res, const MyTypes::Weapon& data) {
  res->set_name(data.name);
  res->set_damage(data.damage);
}

void serializeVec3(Vec3* res, const MyTypes::Vec3& data) {
  res->set_x(data.x);
  res->set_y(data.y);
  res->set_z(data.z);
}

void serializeMonster(Monster* res, const MyTypes::Monster& data) {
  serializeVec3(res->mutable_pos(), data.pos);
  res->set_mana(data.mana);
  res->set_hp(data.hp);
  res->set_name(data.name);
  std::string inv{};
  inv.resize(data.inventory.size());
  std::copy(data.inventory.begin(), data.inventory.end(), inv.begin());
  res->set_inventory(std::move(inv));
  switch (data.color) {
  case MyTypes::Red: res->set_color(Monster_Color_Red); break;
  case MyTypes::Green: res->set_color(Monster_Color_Green);break;
  case MyTypes::Blue: res->set_color(Monster_Color_Blue);break;
  }
  auto weapons = res->mutable_weapons();
  for (const auto& w:data.weapons) {
    serializeWeapon(weapons->Add(), w);
  }
  serializeWeapon(res->mutable_equipped(), data.equipped);
  auto path = res->mutable_path();
  for (const auto& p: data.path) {
    serializeVec3(path->Add(), p);
  }
}

void deserializeVec3(const Vec3& data, MyTypes::Vec3& res) {
  res.x = data.x();
  res.y = data.y();
  res.z = data.z();
}

void deserializeWeapon(const Weapon& data, MyTypes::Weapon& res) {
  res.name = data.name();
  res.damage = data.damage();
}

void deserializeMonster(const Monster& data, MyTypes::Monster& res) {
  deserializeVec3(data.pos(), res.pos);
  res.mana = data.mana();
  res.hp = data.hp();
  res.name = data.name();
  res.inventory.resize(data.inventory().size());
  std::copy(data.inventory().begin(), data.inventory().end(), res.inventory.begin());
  switch (data.color()) {
  case Monster_Color_Red: res.color = MyTypes::Color::Red; break;
  case Monster_Color_Green: res.color = MyTypes::Color::Green;break;
  case Monster_Color_Blue: res.color = MyTypes::Color::Blue;break;
  default: break;
  }
  res.weapons.resize(data.weapons().size());
  auto beginDataWpn = data.weapons().begin();
  for (auto& w: res.weapons) {
    deserializeWeapon(*beginDataWpn, w);
    ++beginDataWpn;
  }
  deserializeWeapon(data.equipped(), res.equipped);
  res.path.resize(data.path().size());
  auto beginDataP = data.path().begin();
  for (auto& p: res.path) {
    deserializeVec3(*beginDataP, p);
    ++beginDataP;
  }
}

#endif //PROTOBUF_SERIALIZE_UTILS_H
