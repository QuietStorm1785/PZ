#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace com {
namespace sixlegs {
namespace png {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class SuggestedPalette {
public:
 virtual ~SuggestedPalette() = default;
 std::string getName();

 int getSampleCount();

 int getSampleDepth();

 void getSample(int var1, short[] var2);

 int getFrequency(int var1);
}
} // namespace png
} // namespace sixlegs
} // namespace com
