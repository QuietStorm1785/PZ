#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/EquippedTextureCreator.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace model {


class ModelInstanceTextureInitializer {
public:
    int m_changeNumber = 0;
    bool m_bRendered;
    EquippedTextureCreator m_textureCreator;

   private ModelInstanceTextureInitializer$RenderData() {
   }
}
} // namespace model
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
