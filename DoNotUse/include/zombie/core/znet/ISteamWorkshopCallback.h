#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace core {
namespace znet {

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
