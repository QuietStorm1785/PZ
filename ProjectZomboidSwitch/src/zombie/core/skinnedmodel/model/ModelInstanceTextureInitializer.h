#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/EquippedTextureCreator.h"
#include "zombie/core/SpriteRenderer.h"
#include "zombie/core/skinnedmodel/model/ModelInstanceTextureInitializer/RenderData.h"
#include "zombie/inventory/InventoryItem.h"
#include "zombie/inventory/types/HandWeapon.h"
#include "zombie/popman/ObjectPool.h"
#include "zombie/util/Type.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace model {


class ModelInstanceTextureInitializer {
public:
    bool m_bRendered;
    ModelInstance m_modelInstance;
    InventoryItem m_item;
    float m_bloodLevel;
    int m_changeNumberMain = 0;
    int m_changeNumberThread = 0;
   private const RenderData[] m_renderData = new RenderData[3];
   private static const ObjectPool<ModelInstanceTextureInitializer> pool = std::make_shared<ObjectPool>(ModelInstanceTextureInitializer::new);

    void init(ModelInstance var1, InventoryItem var2) {
      this.m_item = var2;
      this.m_modelInstance = var1;
    HandWeapon var3 = (HandWeapon)Type.tryCastTo(var2, HandWeapon.class);
      this.m_bloodLevel = var3 == nullptr ? 0.0F : var3.getBloodLevel();
      this.setDirty();
   }

    void init(ModelInstance var1, float var2) {
      this.m_item = nullptr;
      this.m_modelInstance = var1;
      this.m_bloodLevel = var2;
      this.setDirty();
   }

    void setDirty() {
      this.m_changeNumberMain++;
      this.m_bRendered = false;
   }

    bool isDirty() {
      return !this.m_bRendered;
   }

    void renderMain() {
      if (!this.m_bRendered) {
    int var1 = SpriteRenderer.instance.getMainStateIndex();
         if (this.m_renderData[var1] == nullptr) {
            this.m_renderData[var1] = std::make_unique<RenderData>();
         }

    RenderData var2 = this.m_renderData[var1];
         if (var2.m_textureCreator == nullptr) {
            var2.m_changeNumber = this.m_changeNumberMain;
            var2.m_textureCreator = EquippedTextureCreator.alloc();
            if (this.m_item == nullptr) {
               var2.m_textureCreator.init(this.m_modelInstance, this.m_bloodLevel);
            } else {
               var2.m_textureCreator.init(this.m_modelInstance, this.m_item);
            }

            var2.m_bRendered = false;
         }
      }
   }

    void render() {
    int var1 = SpriteRenderer.instance.getRenderStateIndex();
    RenderData var2 = this.m_renderData[var1];
      if (var2 != nullptr) {
         if (var2.m_textureCreator != nullptr) {
            if (!var2.m_bRendered) {
               if (var2.m_changeNumber == this.m_changeNumberThread) {
                  var2.m_bRendered = true;
               } else {
                  var2.m_textureCreator.render();
                  if (var2.m_textureCreator.isRendered()) {
                     this.m_changeNumberThread = var2.m_changeNumber;
                     var2.m_bRendered = true;
                  }
               }
            }
         }
      }
   }

    void postRender() {
    int var1 = SpriteRenderer.instance.getMainStateIndex();
    RenderData var2 = this.m_renderData[var1];
      if (var2 != nullptr) {
         if (var2.m_textureCreator != nullptr) {
            if (var2.m_textureCreator.isRendered() && var2.m_changeNumber == this.m_changeNumberMain) {
               this.m_bRendered = true;
            }

            if (var2.m_bRendered) {
               var2.m_textureCreator.postRender();
               var2.m_textureCreator = nullptr;
            }
         }
      }
   }

    bool isRendered() {
    int var1 = SpriteRenderer.instance.getRenderStateIndex();
    RenderData var2 = this.m_renderData[var1];
      if (var2 == nullptr) {
    return true;
      } else {
         return var2.m_textureCreator == nullptr ? true : var2.m_bRendered;
      }
   }

    static ModelInstanceTextureInitializer alloc() {
      return (ModelInstanceTextureInitializer)pool.alloc();
   }

    void release() {
      pool.release(this);
   }
}
} // namespace model
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
