#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/IsoPlayer.h"
#include "zombie/inventory/InventoryItem.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include <algorithm>

namespace zombie {
namespace modding {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class ModUtilsJava {
public:
 static std::string getRandomUUID() {
 return UUID.randomUUID().toString();
 }

 static bool sendItemListNet(IsoPlayer player0, ArrayList<InventoryItem> arrayList, IsoPlayer player1, const std::string& string0, const std::string& string1) {
 if (arrayList != nullptr) {
 string0 = string0 != nullptr ? string0 : "-1";
 if (GameClient.bClient) {
 if (arrayList.size() > 50) {
 return false;
 }

 for (int int0 = 0; int0 < arrayList.size(); int0++) {
 InventoryItem item = (InventoryItem)arrayList.get(int0);
 if (!player0.getInventory().getItems().contains(item) {
 return false;
 }
 }

 return GameClient.sendItemListNet(player0, arrayList, player1, string0, string1);
 }

 if (GameServer.bServer) {
 return GameServer.sendItemListNet(nullptr, player0, arrayList, player1, string0, string1);
 }
 }

 return false;
 }
}
} // namespace modding
} // namespace zombie
