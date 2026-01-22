#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace vehicles {

class VehiclesDB2 {
public:
    virtual ~VehiclesDB2() = default;
    void accept(int var1, const std::string& var2, int var3, int var4, float var5, float var6, float var7, int var8, byte[] var9, bool var10);
}
} // namespace vehicles
} // namespace zombie
