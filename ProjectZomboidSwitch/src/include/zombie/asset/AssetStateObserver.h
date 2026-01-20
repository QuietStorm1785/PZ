#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/asset/Asset/State.h"

namespace zombie {
namespace asset {


class AssetStateObserver {
public:
    virtual ~AssetStateObserver() = default;
    void onStateChanged(State var1, State var2, Asset var3);
}
} // namespace asset
} // namespace zombie
