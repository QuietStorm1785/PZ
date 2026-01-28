#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <GL/glew.h>
#include "zombie/characterTextures/ItemSmartTexture.h"
#include "zombie/core/skinnedmodel/ModelManager.h"
#include "zombie/core/skinnedmodel/model/ModelInstance.h"
#include "zombie/core/textures/SmartTexture.h"
#include "zombie/core/textures/Texture.h"
#include "zombie/core/textures/TextureDraw/GenericDrawer.h"
#include "zombie/inventory/InventoryItem.h"
#include "zombie/inventory/types/HandWeapon.h"
#include "zombie/popman/ObjectPool.h"

namespace zombie {
namespace characters {


class EquippedTextureCreator : public GenericDrawer {
public:
    bool bRendered;
    ModelInstance modelInstance;
    float bloodLevel;
   private const std::vector<Texture> texturesNotReady = std::make_unique<std::vector<>>();
   private static const ObjectPool<EquippedTextureCreator> pool = std::make_shared<ObjectPool>(EquippedTextureCreator::new);

    void init(ModelInstance var1, InventoryItem var2) {
    float var3 = 0.0F;
      if (dynamic_cast<HandWeapon*>(var2) != nullptr) {
         var3 = ((HandWeapon)var2).getBloodLevel();
      }

      this.init(var1, var3);
   }

    void init(ModelInstance var1, float var2) {
      this.bRendered = false;
      this.texturesNotReady.clear();
      this.modelInstance = var1;
      this.bloodLevel = var2;
      if (this.modelInstance != nullptr) {
         this.modelInstance.renderRefCount++;
    Texture var3 = this.modelInstance.tex;
         if (dynamic_cast<SmartTexture*>(var3) != nullptr) {
            var3 = nullptr;
         }

         if (var3 != nullptr && !var3.isReady()) {
            this.texturesNotReady.push_back(var3);
         }

         var3 = Texture.getSharedTexture("media/textures/BloodTextures/BloodOverlayWeapon.png");
         if (var3 != nullptr && !var3.isReady()) {
            this.texturesNotReady.push_back(var3);
         }

         var3 = Texture.getSharedTexture("media/textures/BloodTextures/BloodOverlayWeaponMask.png");
         if (var3 != nullptr && !var3.isReady()) {
            this.texturesNotReady.push_back(var3);
         }
      }
   }

    void render() {
      for (int var1 = 0; var1 < this.texturesNotReady.size(); var1++) {
    Texture var2 = this.texturesNotReady.get(var1);
         if (!var2.isReady()) {
            return;
         }
      }

      GL11.glPushAttrib(2048);

      try {
         this.updateTexture(this.modelInstance, this.bloodLevel);
      } finally {
         GL11.glPopAttrib();
      }

      this.bRendered = true;
   }

    void updateTexture(ModelInstance var1, float var2) {
      if (var1 != nullptr) {
    ItemSmartTexture var3 = nullptr;
         if (var2 > 0.0F) {
            if (var1.dynamic_cast<ItemSmartTexture*>(tex) != nullptr) {
               var3 = (ItemSmartTexture)var1.tex;
            } else if (var1.tex != nullptr) {
               var3 = std::make_shared<ItemSmartTexture>(var1.tex.getName());
            }
         } else if (var1.dynamic_cast<ItemSmartTexture*>(tex) != nullptr) {
            var3 = (ItemSmartTexture)var1.tex;
         }

         if (var3 != nullptr) {
            var3.setBlood("media/textures/BloodTextures/BloodOverlayWeapon.png", "media/textures/BloodTextures/BloodOverlayWeaponMask.png", var2, 300);
            var3.calculate();
            var1.tex = var3;
         }
      }
   }

    void postRender() {
      ModelManager.instance.derefModelInstance(this.modelInstance);
      this.texturesNotReady.clear();
      if (!this.bRendered) {
      }

      pool.release(this);
   }

    bool isRendered() {
      return this.bRendered;
   }

    static EquippedTextureCreator alloc() {
      return (EquippedTextureCreator)pool.alloc();
   }
}
} // namespace characters
} // namespace zombie
