#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characterTextures/BloodBodyPartType.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace model {


class ModelInstanceTextureCreator {
public:
    ModelInstance modelInstance;
    const CharacterMask mask = std::make_shared<CharacterMask>();
    std::string maskFolder;
    std::string baseTexture;
   const float[] blood = new float[BloodBodyPartType.MAX.index()];
   const float[] dirt = new float[BloodBodyPartType.MAX.index()];

   private ModelInstanceTextureCreator$CharacterData() {
   }
}
} // namespace model
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
