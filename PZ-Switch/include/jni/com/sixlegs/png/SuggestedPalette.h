#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace com {
namespace sixlegs {
namespace png {

class SuggestedPalette {
:
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
