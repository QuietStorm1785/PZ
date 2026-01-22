#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/skinnedmodel/CharacterTextures/CTAnimSet.h"
#include "zombie/core/skinnedmodel/CharacterTextures/CTEntry.h"
#include "zombie/core/skinnedmodel/CharacterTextures/CTState.h"
#include "zombie/core/skinnedmodel/DeadBodyAtlas/BodyTexture.h"
#include "zombie/iso/IsoDirections.h"

namespace zombie {
namespace core {
namespace skinnedmodel {


class CharacterTextures {
public:
   const std::vector<CTAnimSet> m_animSets = std::make_unique<std::vector<>>();

    CTAnimSet getAnimSet(const std::string& var1) {
      for (int var2 = 0; var2 < this.m_animSets.size(); var2++) {
    CTAnimSet var3 = this.m_animSets.get(var2);
         if (var3.m_name == var1)) {
    return var3;
         }
      }

    return nullptr;
   }

    BodyTexture getTexture(const std::string& var1, const std::string& var2, IsoDirections var3, int var4) {
    CTAnimSet var5 = this.getAnimSet(var1);
      if (var5 == nullptr) {
    return nullptr;
      } else {
    CTState var6 = var5.getState(var2);
         if (var6 == nullptr) {
    return nullptr;
         } else {
    CTEntry var7 = var6.getEntry(var3, var4);
    return var7 = = nullptr ? nullptr : var7.m_texture;
         }
      }
   }

    void addTexture(const std::string& var1, const std::string& var2, IsoDirections var3, int var4, BodyTexture var5) {
    CTAnimSet var6 = this.getAnimSet(var1);
      if (var6 == nullptr) {
         var6 = std::make_unique<CTAnimSet>();
         var6.m_name = var1;
         this.m_animSets.push_back(var6);
      }

      var6.addEntry(var2, var3, var4, var5);
   }

    void clear() {
      this.m_animSets.clear();
   }
}
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
