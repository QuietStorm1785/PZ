#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/asset/Asset.h"
#include "zombie/asset/AssetManager.h"
#include "zombie/asset/AssetPath.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace model {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class ModelAssetManager : public AssetManager {
public:
 static const ModelAssetManager instance = new ModelAssetManager();

 void startLoading(Asset var1) {
 }

 Asset createAsset(AssetPath assetPath, AssetManager.AssetParams assetParams) {
 return new Model(assetPath, this, (Model.ModelAssetParams)assetParams);
 }

 void destroyAsset(Asset var1) {
 }
}
} // namespace model
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
