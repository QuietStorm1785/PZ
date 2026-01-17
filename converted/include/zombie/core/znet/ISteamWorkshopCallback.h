#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace core {
namespace znet {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class ISteamWorkshopCallback {
public:
  virtual ~ISteamWorkshopCallback() = default;
  void onItemCreated(long var1, bool var3);

  void onItemNotCreated(int var1);

  void onItemUpdated(bool var1);

  void onItemNotUpdated(int var1);

  void onItemSubscribed(long var1);

  void onItemNotSubscribed(long var1, int var3);

  void onItemDownloaded(long var1);

  void onItemNotDownloaded(long var1, int var3);

  void onItemQueryCompleted(long var1, int var3);

  void onItemQueryNotCompleted(long var1, int var3);
}
} // namespace znet
} // namespace core
} // namespace zombie
