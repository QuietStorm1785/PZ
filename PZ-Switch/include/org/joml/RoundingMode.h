#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace org {
namespace joml {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class RoundingMode {
public:
 static const int TRUNCATE = 0;
 static const int CEILING = 1;
 static const int FLOOR = 2;
 static const int HALF_EVEN = 3;
 static const int HALF_DOWN = 4;
 static const int HALF_UP = 5;

private
 RoundingMode() {}
}
} // namespace joml
} // namespace org
