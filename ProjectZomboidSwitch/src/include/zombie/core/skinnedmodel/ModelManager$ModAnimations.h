#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/skinnedmodel/model/AnimationAsset.h"

namespace zombie {
namespace core {
namespace skinnedmodel {


class ModelManager {
public:
    const std::string m_modID;
   public const std::vector<AnimationAsset> m_animationAssetList = std::make_unique<std::vector<>>();
   public const std::unordered_map<std::string, AnimationAsset> m_animationAssetMap = std::make_unique<std::unordered_map<>>();
    int m_priority;

   public ModelManager$ModAnimations(std::string var1) {
      this.m_modID = var1;
   }

    void setPriority(int var1) {
      if (!$assertionsDisabled && var1 < -1) {
         throw std::make_unique<AssertionError>();
      } else {
         this.m_priority = var1;
      }
   }

    bool isActive() {
      return this.m_priority != -1;
   }
}
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
