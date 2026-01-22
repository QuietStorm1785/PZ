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
#include "zombie/core/textures/Texture/TextureAssetParams.h"

namespace zombie {
namespace core {
namespace textures {


class TextureAssetManager : public AssetManager {
public:
    static const TextureAssetManager instance = std::make_shared<TextureAssetManager>();

    void startLoading(Asset var1) {
   }

    Asset createAsset(AssetPath var1, AssetParams var2) {
      return std::make_shared<Texture>(var1, this, (TextureAssetParams)var2);
   }

    void destroyAsset(Asset var1) {
   }
}
} // namespace textures
} // namespace core
} // namespace zombie
