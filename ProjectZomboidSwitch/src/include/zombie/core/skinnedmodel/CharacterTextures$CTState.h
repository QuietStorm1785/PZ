#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/skinnedmodel/CharacterTextures/CTEntry.h"
#include "zombie/core/skinnedmodel/CharacterTextures/CTEntryList.h"
#include "zombie/core/skinnedmodel/DeadBodyAtlas/BodyTexture.h"
#include "zombie/iso/IsoDirections.h"

namespace zombie {
namespace core {
namespace skinnedmodel {


class CharacterTextures {
public:
    std::string m_name;
   const CTEntryList[] m_entries = new CTEntryList[IsoDirections.values().length];

   CharacterTextures$CTState() {
      for (int var1 = 0; var1 < this.m_entries.length; var1++) {
         this.m_entries[var1] = std::make_unique<CTEntryList>();
      }
   }

    CTEntry getEntry(IsoDirections var1, int var2) {
    CTEntryList var3 = this.m_entries[var1.index()];

      for (int var4 = 0; var4 < var3.size(); var4++) {
    CTEntry var5 = (CTEntry)var3.get(var4);
         if (var5.m_frame == var2) {
    return var5;
         }
      }

    return nullptr;
   }

    void addEntry(IsoDirections var1, int var2, BodyTexture var3) {
    CTEntryList var4 = this.m_entries[var1.index()];
    CTEntry var5 = std::make_shared<CTEntry>();
      var5.m_frame = var2;
      var5.m_texture = var3;
      var4.push_back(var5);
   }
}
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
