#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/debug/DebugLog.h"

namespace zombie {
namespace core {
namespace znet {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class SteamUGCDetails {
public:
 long ID;
 std::string title;
 long timeCreated;
 long timeUpdated;
 int fileSize;
 private long[] childIDs;

 public SteamUGCDetails(long long0, const std::string& string, long long1, long long2, int int0, long[] longs) {
 this->ID = long0;
 this->title = string;
 this->timeCreated = long1;
 this->timeUpdated = long2;
 this->fileSize = int0;
 this->childIDs = longs;
 }

 long getID() {
 return this->ID;
 }

 std::string getIDString() {
 return SteamUtils.convertSteamIDToString(this->ID);
 }

 std::string getTitle() {
 return this->title;
 }

 long getTimeCreated() {
 return this->timeCreated;
 }

 long getTimeUpdated() {
 return this->timeUpdated;
 }

 int getFileSize() {
 return this->fileSize;
 }

 public long[] getChildren() {
 return this->childIDs;
 }

 int getNumChildren() {
 return this->childIDs == nullptr ? 0 : this->childIDs.length;
 }

 long getChildID(int index) {
 if (index >= 0 && index < this->getNumChildren()) {
 return this->childIDs[index];
 } else {
 throw IndexOutOfBoundsException("invalid child index");
 }
 }

 std::string getState() {
 long long0 = SteamWorkshop.instance.GetItemState(this->ID);
 if (!SteamWorkshopItem.ItemState.Subscribed.and(long0) {
 return "NotSubscribed";
 } else if (SteamWorkshopItem.ItemState.DownloadPending.and(long0) {
 DebugLog.log(SteamWorkshopItem.ItemState.toString(long0) + " ID=" + this->ID);
 return "Downloading";
 } else if (SteamWorkshopItem.ItemState.NeedsUpdate.and(long0) {
 return "NeedsUpdate";
 } else {
 return SteamWorkshopItem.ItemState.Installed.and(long0) ? "Installed" : "Error";
 }
 }
}
} // namespace znet
} // namespace core
} // namespace zombie
