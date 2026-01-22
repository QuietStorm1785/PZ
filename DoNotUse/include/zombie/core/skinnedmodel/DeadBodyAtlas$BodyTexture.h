#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/SpriteRenderer.h"
#include "zombie/core/skinnedmodel/DeadBodyAtlas/AtlasEntry.h"
#include "zombie/core/skinnedmodel/DeadBodyAtlas/BodyTextureDrawer.h"
#include "zombie/core/textures/ColorInfo.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/IsoObjectPicker.h"

namespace zombie {
namespace core {
namespace skinnedmodel {


class DeadBodyAtlas {
public:
    AtlasEntry entry;

    void render(float var1, float var2, float var3, float var4, float var5, float var6) {
      if (this.entry.ready && this.entry.tex.isReady()) {
         this.entry
            .tex
            .render(
               var1 - this.entry.w / 2.0F - this.entry.offsetX,
               var2 - this.entry.h / 2.0F - this.entry.offsetY,
               this.entry.w,
               this.entry.h,
               var3,
               var4,
               var5,
               var6,
               nullptr
            );
      } else {
         SpriteRenderer.instance
            .drawGeneric(((BodyTextureDrawer)DeadBodyAtlas.instance.bodyTextureDrawerPool.alloc()).init(this, var1, var2, var3, var4, var5, var6));
      }
   }

    void renderObjectPicker(float var1, float var2, ColorInfo var3, IsoGridSquare var4, IsoObject var5) {
      if (this.entry.ready) {
         IsoObjectPicker.Instance
            .Add((int)(var1 - this.entry.w / 2), (int)(var2 - this.entry.h / 2), this.entry.w, this.entry.h, var4, var5, false, 1.0F, 1.0F);
      }
   }
}
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
