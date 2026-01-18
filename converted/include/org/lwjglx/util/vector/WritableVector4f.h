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

class WritableVector4f {
public:
 virtual ~WritableVector4f() = default;
 void setW(float var1);

 void set(float var1, float var2, float var3, float var4);
}
} // namespace vector
} // namespace util
} // namespace lwjglx
} // namespace org
