#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characterTextures/BloodBodyPartType.h"
#include "zombie/core/ImmutableColor.h"
#include "zombie/popman/ObjectPool.h"

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
    int category;
    ImmutableColor tint;
    float hue;
    std::string decalTexture;
    int decalX;
    int decalY;
    int decalWidth;
    int decalHeight;
   const float[] blood = new float[BloodBodyPartType.MAX.index()];
   const float[] dirt = new float[BloodBodyPartType.MAX.index()];
   const float[] basicPatches = new float[BloodBodyPartType.MAX.index()];
   const float[] denimPatches = new float[BloodBodyPartType.MAX.index()];
   const float[] leatherPatches = new float[BloodBodyPartType.MAX.index()];
   const float[] hole = new float[BloodBodyPartType.MAX.index()];
   static const ObjectPool<ModelInstanceTextureCreator$ItemData> pool = std::make_shared<ObjectPool>(ModelInstanceTextureCreator$ItemData::new);

   private ModelInstanceTextureCreator$ItemData() {
   }
}
} // namespace model
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
