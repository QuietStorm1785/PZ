#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/popman/ObjectPool.h"
#include "zombie/vehicles/UI3DScene/CharacterDrawer.h"
#include "zombie/vehicles/UI3DScene/SceneCharacter.h"
#include "zombie/vehicles/UI3DScene/SceneObjectRenderData.h"

namespace zombie {
namespace vehicles {


class UI3DScene {
public:
    const CharacterDrawer m_drawer = std::make_shared<CharacterDrawer>();
   private static const ObjectPool<UI3DScene$CharacterRenderData> s_pool = std::make_shared<ObjectPool>(UI3DScene$CharacterRenderData::new);

   private UI3DScene$CharacterRenderData() {
   }

    SceneObjectRenderData initCharacter(SceneCharacter var1) {
      this.m_drawer.init(var1, this);
      super.init(var1);
    return this;
   }

    void release() {
      s_pool.release(this);
   }
}
} // namespace vehicles
} // namespace zombie
