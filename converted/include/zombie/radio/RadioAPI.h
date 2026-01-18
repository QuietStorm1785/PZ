#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "zombie/Lua/LuaManager.h"
#include <algorithm>

namespace zombie {
namespace radio {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class RadioAPI {
public:
 static RadioAPI instance;

 static int timeToTimeStamp(int days, int hours, int minutes) {
 return days * 24 + hours * 60 + minutes;
 }

 static int timeStampToDays(int stamp) {
 return stamp / 1440;
 }

 static int timeStampToHours(int stamp) {
 return stamp / 60 % 24;
 }

 static int timeStampToMinutes(int stamp) {
 return stamp % 60;
 }

 static bool hasInstance() {
 return instance != nullptr;
 }

 static RadioAPI getInstance() {
 if (instance.empty()) {
 instance = std::make_unique<RadioAPI>();
 }

 return instance;
 }

 private RadioAPI() {
 }

 KahluaTable getChannels(const std::string& category) {
 std::unordered_map map = ZomboidRadio.getInstance().GetChannelList(category);
 KahluaTable table = LuaManager.platform.newTable();
 if (map != nullptr) {
 for (Entry entry : map.entrySet()) {
 table.rawset(entry.getKey(), entry.getValue());
 }
 }

 return table;
 }
}
} // namespace radio
} // namespace zombie
