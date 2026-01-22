#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/SpriteRenderer.h"
#include "zombie/core/skinnedmodel/model/WorldItemAtlas/AtlasEntry.h"
#include "zombie/core/skinnedmodel/model/WorldItemAtlas/ItemParams.h"
#include "zombie/core/skinnedmodel/model/WorldItemAtlas/ItemTextureDrawer.h"
#include "zombie/inventory/InventoryItem.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace model {


class WorldItemAtlas {
public:
    const ItemParams itemParams = std::make_shared<ItemParams>();
    AtlasEntry entry;

    bool isStillValid(InventoryItem var1) {
      return this.entry == nullptr ? false : this.itemParams.isStillValid(var1);
   }

    bool isRenderMainOK() {
      return this.entry.bRenderMainOK;
   }

    bool isTooBig() {
      return this.entry.bTooBig;
   }

    void render(float var1, float var2, float var3, float var4, float var5, float var6) {
      if (this.entry.ready && this.entry.tex.isReady()) {
         SpriteRenderer.instance
            .m_states
            .getPopulatingActiveState()
            .render(
               this.entry.tex,
               var1 - (this.entry.w / 2.0F - this.entry.offsetX) / 2.5F,
               var2 - (this.entry.h / 2.0F - this.entry.offsetY) / 2.5F,
               this.entry.w / 2.5F,
               this.entry.h / 2.5F,
               var3,
               var4,
               var5,
               var6,
               nullptr
            );
      } else {
         SpriteRenderer.instance
            .drawGeneric(((ItemTextureDrawer)WorldItemAtlas.instance.itemTextureDrawerPool.alloc()).init(this, var1, var2, var3, var4, var5, var6));
      }
   }

    void Reset() {
      this.itemParams.Reset();
      this.entry = nullptr;
   }
}
} // namespace model
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
