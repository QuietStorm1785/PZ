#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/lwjgl/util/vector/Matrix4f.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace animation {


class AnimTrackSampler {
public:
    virtual ~AnimTrackSampler() = default;
    float getTotalTime();

    bool isLooped();

    void moveToTime(float var1);

    float getCurrentTime();

    void getBoneMatrix(int var1, Matrix4f var2);

    int getNumBones();
}
} // namespace animation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
