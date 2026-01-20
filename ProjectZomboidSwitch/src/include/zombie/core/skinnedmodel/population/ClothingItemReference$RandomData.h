#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/ImmutableColor.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace population {


class ClothingItemReference {
public:
    bool m_Active = true;
    float m_Hue = 0.0F;
    ImmutableColor m_Tint = ImmutableColor.white;
    std::string m_BaseTexture;
    ClothingItemReference m_PickedItemRef;
    std::string m_TextureChoice;
    std::string m_Decal;

    void reset() {
      this.m_Active = true;
      this.m_Hue = 0.0F;
      this.m_Tint = ImmutableColor.white;
      this.m_BaseTexture = nullptr;
      this.m_PickedItemRef = nullptr;
      this.m_TextureChoice = nullptr;
      this.m_Decal = nullptr;
   }
}
} // namespace population
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
