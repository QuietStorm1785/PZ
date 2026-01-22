#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/asset/Asset.h"
#include "zombie/asset/Asset/State.h"
#include "zombie/asset/AssetManager.h"
#include "zombie/asset/AssetManager/AssetParams.h"
#include "zombie/asset/AssetPath.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace advancedanimation {


class AnimNodeAssetManager : public AssetManager {
public:
    static const AnimNodeAssetManager instance = std::make_shared<AnimNodeAssetManager>();

    void startLoading(Asset var1) {
    AnimNodeAsset var2 = (AnimNodeAsset)var1;
      var2.m_animNode = AnimNode.Parse(var1.getPath().getPath());
      if (var2.m_animNode == nullptr) {
         this.onLoadingFailed(var1);
      } else {
         this.onLoadingSucceeded(var1);
      }
   }

    void onStateChanged(State var1, State var2, Asset var3) {
      super.onStateChanged(var1, var2, var3);
      if (var2 == State.READY) {
      }
   }

    Asset createAsset(AssetPath var1, AssetParams var2) {
      return std::make_shared<AnimNodeAsset>(var1, this);
   }

    void destroyAsset(Asset var1) {
   }
}
} // namespace advancedanimation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
