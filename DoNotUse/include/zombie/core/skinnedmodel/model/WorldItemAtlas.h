#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/joml/Matrix4f.h"
#include "zombie/core/Core.h"
#include "zombie/core/ImmutableColor.h"
#include "zombie/core/SpriteRenderer.h"
#include "zombie/core/logger/ExceptionLogger.h"
#include "zombie/core/skinnedmodel/model/WorldItemAtlas/Atlas.h"
#include "zombie/core/skinnedmodel/model/WorldItemAtlas/AtlasEntry.h"
#include "zombie/core/skinnedmodel/model/WorldItemAtlas/Checksummer.h"
#include "zombie/core/skinnedmodel/model/WorldItemAtlas/ClearAtlasTexture.h"
#include "zombie/core/skinnedmodel/model/WorldItemAtlas/ItemParams.h"
#include "zombie/core/skinnedmodel/model/WorldItemAtlas/ItemTexture.h"
#include "zombie/core/skinnedmodel/model/WorldItemAtlas/ItemTextureDrawer.h"
#include "zombie/core/skinnedmodel/model/WorldItemAtlas/RenderJob.h"
#include "zombie/core/skinnedmodel/model/WorldItemAtlas/WeaponPartParams.h"
#include "zombie/core/textures/TextureFBO.h"
#include "zombie/debug/DebugOptions.h"
#include "zombie/input/GameKeyboard.h"
#include "zombie/inventory/InventoryItem.h"
#include "zombie/inventory/types/WeaponPart.h"
#include "zombie/popman/ObjectPool.h"
#include <algorithm>

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace model {


class WorldItemAtlas {
public:
    static const int ATLAS_SIZE = 512;
    static const int MATRIX_SIZE = 1024;
    static const float MAX_ZOOM = 2.5F;
    TextureFBO fbo;
    static const WorldItemAtlas instance = std::make_shared<WorldItemAtlas>();
   private const std::unordered_map<std::string, ItemTexture> itemTextureMap = std::make_unique<std::unordered_map<>>();
   private const std::vector<Atlas> AtlasList = std::make_unique<std::vector<>>();
    const ItemParams itemParams = std::make_shared<ItemParams>();
    const Checksummer checksummer = std::make_shared<Checksummer>();
   private static const std::stack<RenderJob> JobPool = std::make_unique<std::stack<>>();
   private const std::vector<RenderJob> RenderJobs = std::make_unique<std::vector<>>();
   private const ObjectPool<ItemTextureDrawer> itemTextureDrawerPool = std::make_shared<ObjectPool>(ItemTextureDrawer::new);
   private const ObjectPool<WeaponPartParams> weaponPartParamPool = std::make_shared<ObjectPool>(WeaponPartParams::new);
   private const std::vector<WeaponPart> m_tempWeaponPartList = std::make_unique<std::vector<>>();
    static const Matrix4f s_attachmentXfrm = std::make_shared<Matrix4f>();
    static const ImmutableColor ROTTEN_FOOD_COLOR = std::make_shared<ImmutableColor>(0.5F, 0.5F, 0.5F);

    ItemTexture getItemTexture(InventoryItem var1) {
      return this.itemParams.init(var1) ? this.getItemTexture(this.itemParams) : nullptr;
   }

    ItemTexture getItemTexture(ItemParams var1) {
    std::string var2 = this.getItemKey(var1);
    ItemTexture var3 = this.itemTextureMap.get(var2);
      if (var3 != nullptr) {
    return var3;
      } else {
    AtlasEntry var4 = std::make_shared<AtlasEntry>();
         var4.key = var2;
         var3 = std::make_unique<ItemTexture>();
         var3.itemParams.copyFrom(var1);
         var3.entry = var4;
         this.itemTextureMap.put(var2, var3);
         this.RenderJobs.push_back(RenderJob.getNew().init(var1, var4));
    return var3;
      }
   }

    void assignEntryToAtlas(AtlasEntry var1, int var2, int var3) {
      if (var1.atlas == nullptr) {
         for (int var4 = 0; var4 < this.AtlasList.size(); var4++) {
    Atlas var5 = this.AtlasList.get(var4);
            if (!var5.isFull() && var5.ENTRY_WID == var2 && var5.ENTRY_HGT == var3) {
               var5.addEntry(var1);
               return;
            }
         }

    Atlas var6 = std::make_shared<Atlas>(this, 512, 512, var2, var3);
         var6.addEntry(var1);
         this.AtlasList.push_back(var6);
      }
   }

    std::string getItemKey(ItemParams var1) {
      try {
         this.checksummer.reset();
         this.checksummer.update(var1.m_model.Name);
         if (var1.m_weaponParts != nullptr) {
            for (int var2 = 0; var2 < var1.m_weaponParts.size(); var2++) {
    WeaponPartParams var3 = (WeaponPartParams)var1.m_weaponParts.get(var2);
               this.checksummer.update(var3.m_model.Name);
            }
         }

         this.checksummer.update((int)(var1.worldScale * 1000.0F));
         this.checksummer.update((byte)(var1.m_tintR * 255.0F));
         this.checksummer.update((byte)(var1.m_tintG * 255.0F));
         this.checksummer.update((byte)(var1.m_tintB * 255.0F));
         this.checksummer.update((int)(var1.m_angle.x * 1000.0F));
         this.checksummer.update((int)(var1.m_angle.y * 1000.0F));
         this.checksummer.update((int)(var1.m_angle.z * 1000.0F));
         this.checksummer.update((byte)var1.m_foodState.ordinal());
         return this.checksummer.checksumToString();
      } catch (Throwable var4) {
         ExceptionLogger.logException(var4);
         return "bogus";
      }
   }

    void render() {
      for (int var1 = 0; var1 < this.AtlasList.size(); var1++) {
    Atlas var2 = this.AtlasList.get(var1);
         if (var2.clear) {
            SpriteRenderer.instance.drawGeneric(std::make_shared<ClearAtlasTexture>(var2));
         }
      }

      if (!this.RenderJobs.empty()) {
         for (int var3 = 0; var3 < this.RenderJobs.size(); var3++) {
    RenderJob var4 = this.RenderJobs.get(var3);
            if (var4.done != 1 || var4.renderRefCount <= 0) {
               if (var4.done == 1 && var4.renderRefCount == 0) {
                  this.RenderJobs.remove(var3--);

                  assert !JobPool.contains(var4);

                  JobPool.push(var4);
               } else {
                  var4.entry.bRenderMainOK = var4.renderMain();
                  if (var4.entry.bRenderMainOK) {
                     var4.renderRefCount++;
                     SpriteRenderer.instance.drawGeneric(var4);
                  }
               }
            }
         }
      }
   }

    void renderUI() {
      if (DebugOptions.instance.WorldItemAtlasRender.getValue() && GameKeyboard.isKeyPressed(209)) {
         this.Reset();
      }

      if (DebugOptions.instance.WorldItemAtlasRender.getValue()) {
    int var1 = 512 / Core.TileScale;
         var1 /= 2;
    int var2 = 0;
    int var3 = 0;

         for (int var4 = 0; var4 < this.AtlasList.size(); var4++) {
    Atlas var5 = this.AtlasList.get(var4);
            SpriteRenderer.instance.renderi(nullptr, var2, var3, var1, var1, 1.0F, 1.0F, 1.0F, 0.75F, nullptr);
            SpriteRenderer.instance.renderi(var5.tex, var2, var3, var1, var1, 1.0F, 1.0F, 1.0F, 1.0F, nullptr);
    float var6 = (float)var1 / var5.tex.getWidth();

            for (int var7 = 0; var7 <= var5.tex.getWidth() / var5.ENTRY_WID; var7++) {
               SpriteRenderer.instance
                  .renderline(
                     nullptr, (int)(var2 + var7 * var5.ENTRY_WID * var6), var3, (int)(var2 + var7 * var5.ENTRY_WID * var6), var3 + var1, 0.5F, 0.5F, 0.5F, 1.0F
                  );
            }

            for (int var9 = 0; var9 <= var5.tex.getHeight() / var5.ENTRY_HGT; var9++) {
               SpriteRenderer.instance
                  .renderline(
                     nullptr,
                     var2,
                     (int)(var3 + var1 - var9 * var5.ENTRY_HGT * var6),
                     var2 + var1,
                     (int)(var3 + var1 - var9 * var5.ENTRY_HGT * var6),
                     0.5F,
                     0.5F,
                     0.5F,
                     1.0F
                  );
            }

            var3 += var1;
            if (var3 + var1 > Core.getInstance().getScreenHeight()) {
               var3 = 0;
               var2 += var1;
            }
         }
      }
   }

    void Reset() {
      if (this.fbo != nullptr) {
         this.fbo.destroyLeaveTexture();
         this.fbo = nullptr;
      }

      this.AtlasList.forEach(Atlas::Reset);
      this.AtlasList.clear();
      this.itemTextureMap.values().forEach(ItemTexture::Reset);
      this.itemTextureMap.clear();
      JobPool.forEach(RenderJob::Reset);
      JobPool.clear();
      this.RenderJobs.clear();
   }
}
} // namespace model
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
