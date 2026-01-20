#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/asset/AssetManager/AssetParams.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace model {


class ModelMesh {
public:
    bool bStatic;
    ModelMesh animationsMesh;
}
} // namespace model
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
