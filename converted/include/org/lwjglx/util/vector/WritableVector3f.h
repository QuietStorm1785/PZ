#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace org {
namespace lwjglx {
namespace util {
namespace vector {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.

class WritableVector3f {
public:
 virtual ~WritableVector3f() = default;
 void setZ(float var1);

 void set(float var1, float var2, float var3);
}
} // namespace vector
} // namespace util
} // namespace lwjglx
} // namespace org
