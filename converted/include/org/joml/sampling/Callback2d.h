#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace org {
namespace joml {
namespace sampling {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.

class Callback2d {
public:
 virtual ~Callback2d() = default;
 void onNewSample(float var1, float var2);
}
} // namespace sampling
} // namespace joml
} // namespace org
