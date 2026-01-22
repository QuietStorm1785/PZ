#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/asset/Asset.h"
#include "zombie/asset/AssetManager.h"
#include "zombie/asset/AssetManager/AssetParams.h"
#include "zombie/asset/AssetPath.h"
#include "zombie/core/skinnedmodel/model/Model/ModelAssetParams.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace model {


class ModelAssetManager : public AssetManager {
public:
    static const ModelAssetManager instance = std::make_shared<ModelAssetManager>();

    void startLoading(Asset var1) {
   }

    Asset createAsset(AssetPath var1, AssetParams var2) {
      return std::make_shared<Model>(var1, this, (ModelAssetParams)var2);
   }

    void destroyAsset(Asset var1) {
   }
}
} // namespace model
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
