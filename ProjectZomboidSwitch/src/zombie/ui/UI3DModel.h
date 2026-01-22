#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/SurvivorDesc.h"
#include "zombie/core/Rand.h"
#include "zombie/core/SpriteRenderer.h"
#include "zombie/core/skinnedmodel/advancedanimation/AnimatedModel.h"
#include "zombie/core/skinnedmodel/population/IClothingItemListener.h"
#include "zombie/core/skinnedmodel/population/OutfitManager.h"
#include "zombie/iso/IsoDirections.h"
#include "zombie/ui/UI3DModel/Drawer.h"
#include "zombie/util/StringUtils.h"

namespace zombie {
namespace ui {


class UI3DModel : public UIElement {
public:
    const AnimatedModel animatedModel = std::make_shared<AnimatedModel>();
    IsoDirections dir = IsoDirections.E;
    bool bDoExt = false;
    long nextExt = -1L;
   private const Drawer[] drawers = new Drawer[3];
    float zoom = 0.0F;
    float yOffset = 0.0F;
    float xOffset = 0.0F;

    public UI3DModel(KahluaTable var1) {
      super(var1);

      for (int var2 = 0; var2 < this.drawers.length; var2++) {
         this.drawers[var2] = std::make_shared<Drawer>(this);
      }

      if (OutfitManager.instance != nullptr) {
         OutfitManager.instance.addClothingItemListener(this);
      }
   }

    void render() {
      if (this.isVisible()) {
         super.render();
         if (this.Parent == nullptr || this.Parent.maxDrawHeight == -1 || !(this.Parent.maxDrawHeight <= this.y)) {
            if (this.bDoExt) {
    long var1 = System.currentTimeMillis();
               if (this.nextExt < 0L) {
                  this.nextExt = var1 + Rand.Next(5000, 10000);
               }

               if (this.nextExt < var1) {
                  this.animatedModel.getActionContext().reportEvent("EventDoExt");
                  this.animatedModel.setVariable("Ext", Rand.Next(0, 6) + 1);
                  this.nextExt = -1L;
               }
            }

            this.animatedModel.update();
    Drawer var3 = this.drawers[SpriteRenderer.instance.getMainStateIndex()];
            var3.init(this.getAbsoluteX().intValue(), this.getAbsoluteY().intValue());
            SpriteRenderer.instance.drawGeneric(var3);
         }
      }
   }

    void setDirection(IsoDirections var1) {
      this.dir = var1;
      this.animatedModel.setAngle(var1.ToVector());
   }

    IsoDirections getDirection() {
      return this.dir;
   }

    void setAnimate(bool var1) {
      this.animatedModel.setAnimate(var1);
   }

    void setAnimSetName(const std::string& var1) {
      this.animatedModel.setAnimSetName(var1);
   }

    void setDoRandomExtAnimations(bool var1) {
      this.bDoExt = var1;
   }

    void setIsometric(bool var1) {
      this.animatedModel.setIsometric(var1);
   }

    void setOutfitName(const std::string& var1, bool var2, bool var3) {
      this.animatedModel.setOutfitName(var1, var2, var3);
   }

    void setCharacter(IsoGameCharacter var1) {
      this.animatedModel.setCharacter(var1);
   }

    void setSurvivorDesc(SurvivorDesc var1) {
      this.animatedModel.setSurvivorDesc(var1);
   }

    void setState(const std::string& var1) {
      this.animatedModel.setState(var1);
   }

    void reportEvent(const std::string& var1) {
      if (!StringUtils.isNullOrWhitespace(var1)) {
         this.animatedModel.getActionContext().reportEvent(var1);
      }
   }

    void clothingItemChanged(const std::string& var1) {
      this.animatedModel.clothingItemChanged(var1);
   }

    void setZoom(float var1) {
      this.zoom = var1;
   }

    void setYOffset(float var1) {
      this.yOffset = var1;
   }

    void setXOffset(float var1) {
      this.xOffset = var1;
   }
}
} // namespace ui
} // namespace zombie
