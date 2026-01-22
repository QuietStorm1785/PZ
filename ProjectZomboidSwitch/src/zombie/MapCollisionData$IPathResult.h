#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {

class MapCollisionData {
public:
    virtual ~MapCollisionData() = default;
    void finished(int var1, int var2, int var3);
}
} // namespace zombie
