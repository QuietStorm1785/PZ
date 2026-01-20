#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/set/hash/TIntHashSet.h"
#include "zombie/savefile/PlayerDB/PlayerData.h"

namespace zombie {
namespace savefile {


class PlayerDB {
public:
    virtual ~PlayerDB() = default;
    void init(TIntHashSet var1);

    void Reset();

    void save(PlayerData var1);

    bool load(PlayerData var1);

    bool loadEverythingExceptBytes(PlayerData var1);
}
} // namespace savefile
} // namespace zombie
