#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "jassimp/AiPostProcessSteps.h"
#include "zombie/asset/AssetManager/AssetParams.h"
#include <algorithm>

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace model {


class AiSceneAsset {
public:
   EnumSet<AiPostProcessSteps> post_process_step_set;
}
} // namespace model
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
