#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace iso {

class IsoGridSquare {
public:
    virtual ~IsoGridSquare() = default;
    IsoGridSquare getGridSquare(int var1, int var2, int var3);
}
} // namespace iso
} // namespace zombie
