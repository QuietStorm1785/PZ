#pragma once
#include "se/krka/kahlua/j2se/KahluaTableImpl.h"
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "zombie/Lua/LuaManager.h"
#include "zombie/util/Type.h"
#include <cstdint>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace population {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class DefaultClothing {
public:
 static const DefaultClothing instance = new DefaultClothing();
public
 DefaultClothing.Clothing Pants = new DefaultClothing.Clothing();
public
 DefaultClothing.Clothing TShirt = new DefaultClothing.Clothing();
public
 DefaultClothing.Clothing TShirtDecal = new DefaultClothing.Clothing();
public
 DefaultClothing.Clothing Vest = new DefaultClothing.Clothing();
 bool m_dirty = true;

 void checkDirty() {
 if (this->m_dirty) {
 this->m_dirty = false;
 this->init();
 }
 }

 void init() {
 this->Pants.clear();
 this->TShirt.clear();
 this->TShirtDecal.clear();
 this->Vest.clear();
 KahluaTable table = Type.tryCastTo(LuaManager.env.rawget("DefaultClothing"),
 KahluaTable.class);
 if (table != nullptr) {
 this->initClothing(table, this->Pants, "Pants");
 this->initClothing(table, this->TShirt, "TShirt");
 this->initClothing(table, this->TShirtDecal, "TShirtDecal");
 this->initClothing(table, this->Vest, "Vest");
 }
 }

 void initClothing(KahluaTable table1, DefaultClothing.Clothing clothing,
 std::string_view string) {
 KahluaTable table0 =
 Type.tryCastTo(table1.rawget(string), KahluaTable.class);
 if (table0 != nullptr) {
 this->tableToArrayList(table0, "hue", clothing.hue);
 this->tableToArrayList(table0, "texture", clothing.texture);
 this->tableToArrayList(table0, "tint", clothing.tint);
 }
 }

 void tableToArrayList(KahluaTable table, std::string_view string,
 ArrayList<String> arrayList) {
 KahluaTableImpl kahluaTableImpl = (KahluaTableImpl)table.rawget(string);
 if (kahluaTableImpl != nullptr) {
 int int0 = 1;

 for (int int1 = kahluaTableImpl.len(); int0 <= int1; int0++) {
 void *object = kahluaTableImpl.rawget(int0);
 if (object != nullptr) {
 arrayList.add(object.toString());
 }
 }
 }
 }

 std::string pickPantsHue() {
 this->checkDirty();
 return OutfitRNG.pickRandom(this->Pants.hue);
 }

 std::string pickPantsTexture() {
 this->checkDirty();
 return OutfitRNG.pickRandom(this->Pants.texture);
 }

 std::string pickPantsTint() {
 this->checkDirty();
 return OutfitRNG.pickRandom(this->Pants.tint);
 }

 std::string pickTShirtTexture() {
 this->checkDirty();
 return OutfitRNG.pickRandom(this->TShirt.texture);
 }

 std::string pickTShirtTint() {
 this->checkDirty();
 return OutfitRNG.pickRandom(this->TShirt.tint);
 }

 std::string pickTShirtDecalTexture() {
 this->checkDirty();
 return OutfitRNG.pickRandom(this->TShirtDecal.texture);
 }

 std::string pickTShirtDecalTint() {
 this->checkDirty();
 return OutfitRNG.pickRandom(this->TShirtDecal.tint);
 }

 std::string pickVestTexture() {
 this->checkDirty();
 return OutfitRNG.pickRandom(this->Vest.texture);
 }

 std::string pickVestTint() {
 this->checkDirty();
 return OutfitRNG.pickRandom(this->Vest.tint);
 }

private
 static class Clothing {
 ArrayList<String> hue = std::make_unique<ArrayList<>>();
 ArrayList<String> texture = std::make_unique<ArrayList<>>();
 ArrayList<String> tint = std::make_unique<ArrayList<>>();

 void clear() {
 this->hue.clear();
 this->texture.clear();
 this->tint.clear();
 }
 }
}
} // namespace population
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
