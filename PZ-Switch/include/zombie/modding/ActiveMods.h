#pragma once
#include "zombie/GameWindow.h"
#include "zombie/MapGroups.h"
#include "zombie/core/Core.h"
#include "zombie/core/SpriteRenderer.h"
#include "zombie/debug/DebugOptions.h"
#include "zombie/gameStates/ChooseGameInfo.h"
#include "zombie/ui/TextManager.h"
#include "zombie/ui/UIFont.h"
#include "zombie/util/StringUtils.h"
#include <algorithm>
#include <cstdint>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace modding {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class ActiveMods {
public:
private
 static ArrayList<ActiveMods> s_activeMods =
 std::make_unique<ArrayList<>>();
 static const ActiveMods s_loaded = new ActiveMods("loaded");
 const std::string id;
private
 ArrayList<String> mods = std::make_unique<ArrayList<>>();
private
 ArrayList<String> mapOrder = std::make_unique<ArrayList<>>();

 static int count() { return s_activeMods.size(); }

 static ActiveMods getByIndex(int index) { return s_activeMods.get(index); }

 static ActiveMods getById(std::string_view _id) {
 int int0 = indexOf(_id);
 return int0 = = -1 ? create(_id) : s_activeMods.get(int0);
 }

 static int indexOf(std::string_view _id) {
 _id = _id.trim();
 requireValidId(_id);

 for (int int0 = 0; int0 < s_activeMods.size(); int0++) {
 ActiveMods activeMods = s_activeMods.get(int0);
 if (activeMods.id.equalsIgnoreCase(_id) {
 return int0;
 }
 }

 return -1;
 }

 static ActiveMods create(std::string_view string) {
 requireValidId(string);
 if (indexOf(string) != -1) {
 throw IllegalStateException("id \"" + string + "\" exists");
 } else {
 ActiveMods activeMods = new ActiveMods(string);
 s_activeMods.add(activeMods);
 return activeMods;
 }
 }

 static void requireValidId(std::string_view string) {
 if (StringUtils.isNullOrWhitespace(string) {
 throw IllegalArgumentException("id is nullptr or whitespace");
 }
 }

 static void setLoadedMods(ActiveMods activeMods) {
 if (activeMods != nullptr) {
 s_loaded.copyFrom(activeMods);
 }
 }

 static bool requiresResetLua(ActiveMods activeMods) {
 Objects.requireNonNull(activeMods);
 return !s_loaded.mods == activeMods.mods);
 }

 static void renderUI() {
 if (DebugOptions.instance.ModRenderLoaded.getValue()) {
 if (!GameWindow.DrawReloadingLua) {
 UIFont uIFont = UIFont.DebugConsole;
 int int0 = TextManager.instance.getFontHeight(uIFont);
 std::string string0 = "Active Mods:";
 int int1 = TextManager.instance.MeasureStringX(uIFont, string0);

 for (int int2 = 0; int2 < s_loaded.mods.size(); int2++) {
 std::string string1 = s_loaded.mods.get(int2);
 int int3 = TextManager.instance.MeasureStringX(uIFont, string1);
 int1 = Math.max(int1, int3);
 }

 uint8_t byte0 = 10;
 int1 += byte0 * 2;
 int int4 = Core.width - 20 - int1;
 uint8_t byte1 = 20;
 int int5 = (1 + s_loaded.mods.size()) * int0 + byte0 * 2;
 SpriteRenderer.instance.renderi(nullptr, int4, byte1, int1, int5, 0.0F,
 0.5F, 0.75F, 1.0F, nullptr);
 int int6;
 TextManager.instance.DrawString(uIFont, int4 + byte0,
 int6 = byte1 + byte0, string0, 1.0, 1.0,
 1.0, 1.0);

 for (int int7 = 0; int7 < s_loaded.mods.size(); int7++) {
 std::string string2 = s_loaded.mods.get(int7);
 TextManager.instance.DrawString(uIFont, int4 + byte0, int6 += int0,
 string2, 1.0, 1.0, 1.0, 1.0);
 }
 }
 }
 }

 static void Reset() { s_loaded.clear(); }

public
 ActiveMods(std::string_view _id) {
 requireValidId(_id);
 this->id = _id;
 }

 void clear() {
 this->mods.clear();
 this->mapOrder.clear();
 }

public
 ArrayList<String> getMods() { return this->mods; }

public
 ArrayList<String> getMapOrder() { return this->mapOrder; }

 void copyFrom(ActiveMods other) {
 this->mods.clear();
 this->mapOrder.clear();
 this->mods.addAll(other.mods);
 this->mapOrder.addAll(other.mapOrder);
 }

 void setModActive(std::string_view modID, bool active) {
 modID = modID.trim();
 if (!StringUtils.isNullOrWhitespace(modID) {
 if (active) {
 if (!this->mods.contains(modID) {
 this->mods.add(modID);
 }
 } else {
 this->mods.remove(modID);
 }
 }
 }

 bool isModActive(std::string_view modID) {
 modID = modID.trim();
 return StringUtils.isNullOrWhitespace(modID) ? false
 : this->mods.contains(modID);
 }

 void removeMod(std::string_view modID) {
 modID = modID.trim();
 this->mods.remove(modID);
 }

 void removeMapOrder(std::string_view folder) {
 this->mapOrder.remove(folder);
 }

 void checkMissingMods() {
 if (!this->mods.empty()) {
 for (int int0 = this->mods.size() - 1; int0 >= 0; int0--) {
 std::string string = this->mods.get(int0);
 if (ChooseGameInfo.getAvailableModDetails(string) == nullptr) {
 this->mods.remove(int0);
 }
 }
 }
 }

 void checkMissingMaps() {
 if (!this->mapOrder.empty()) {
 MapGroups mapGroups = new MapGroups();
 mapGroups.createGroups(this, false);
 if (mapGroups.checkMapConflicts()) {
 std::vector arrayList = mapGroups.getAllMapsInOrder();

 for (int int0 = this->mapOrder.size() - 1; int0 >= 0; int0--) {
 std::string string = this->mapOrder.get(int0);
 if (!arrayList.contains(string) {
 this->mapOrder.remove(int0);
 }
 }
 } else {
 this->mapOrder.clear();
 }
 }
 }
}
} // namespace modding
} // namespace zombie
