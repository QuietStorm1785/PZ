#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/skinnedmodel/CharacterTextures/CTState.h"
#include "zombie/core/skinnedmodel/DeadBodyAtlas/BodyTexture.h"
#include "zombie/iso/IsoDirections.h"

namespace zombie {
namespace core {
namespace skinnedmodel {


class CharacterTextures {
public:
    std::string m_name;
   const std::vector<CTState> m_states = std::make_unique<std::vector<>>();

   private CharacterTextures$CTAnimSet() {
   }

    CTState getState(const std::string& var1) {
      for (int var2 = 0; var2 < this.m_states.size(); var2++) {
    CTState var3 = this.m_states.get(var2);
         if (var3.m_name == var1)) {
    return var3;
         }
      }

    return nullptr;
   }

    void addEntry(const std::string& var1, IsoDirections var2, int var3, BodyTexture var4) {
    CTState var5 = this.getState(var1);
      if (var5 == nullptr) {
         var5 = std::make_unique<CTState>();
         var5.m_name = var1;
         this.m_states.push_back(var5);
      }

      var5.addEntry(var2, var3, var4);
   }
}
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
