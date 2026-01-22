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


class Model {
public:
    std::string meshName;
    std::string textureName;
    int textureFlags;
    std::string shaderName;
    bool bStatic = false;
    ModelMesh animationsModel;
}
} // namespace model
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
