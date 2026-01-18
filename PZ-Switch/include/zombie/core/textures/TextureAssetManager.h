#pragma once
#include "zombie/asset/Asset.h"
#include "zombie/asset/AssetManager.h"
#include "zombie/asset/AssetPath.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace core {
namespace textures {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class TextureAssetManager : public AssetManager {
public:
 static const TextureAssetManager instance = new TextureAssetManager();

 void startLoading(Asset var1) {}

 Asset createAsset(AssetPath assetPath, AssetManager.AssetParams assetParams) {
 return new Texture(assetPath, this,
 (Texture.TextureAssetParams)assetParams);
 }

 void destroyAsset(Asset var1) {}
}
} // namespace textures
} // namespace core
} // namespace zombie
