#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/skinnedmodel/DeadBodyAtlas/BodyTexture.h"

namespace zombie {
namespace core {
namespace skinnedmodel {


class CharacterTextures {
public:
    int m_frame;
    BodyTexture m_texture;

   private CharacterTextures$CTEntry() {
   }
}
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
