#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "fmod/fmod/FMODManager.h"
#include "zombie/GameTime.h"
#include "zombie/IndieGL.h"
#include "zombie/Lua/LuaEventManager.h"
#include "zombie/WorldSoundManager.h"
#include "zombie/audio/BaseSoundEmitter.h"
#include "zombie/audio/parameters/ParameterMeleeHitSurface/Material.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoGameCharacter/Location.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/Core.h"
#include "zombie/core/Rand.h"
#include "zombie/core/SpriteRenderer.h"
#include "zombie/core/opengl/Shader.h"
#include "zombie/core/textures/ColorInfo.h"
#include "zombie/core/textures/Texture.h"
#include "zombie/inventory/types/HandWeapon.h"
#include "zombie/iso/CellLoader.h"
#include "zombie/iso/IsoCamera.h"
#include "zombie/iso/IsoCell.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoMovingObject.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/IsoUtils.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/LosUtil.h"
#include "zombie/iso/SpriteDetails/IsoObjectType.h"
#include "zombie/iso/objects/IsoTree/TreeShader.h"
#include "zombie/iso/sprite/IsoSprite.h"
#include "zombie/iso/sprite/IsoSpriteInstance.h"
#include "zombie/util/list/PZArrayUtil.h"
#include "zombie/vehicles/BaseVehicle.h"
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace iso {
namespace objects {


class IsoTree : public IsoObject {
public:
    static const int MAX_SIZE = 6;
    int LogYield = 1;
    int damage = 500;
    int size = 4;
    bool bRenderFlag;
    float fadeAlpha;
   private static const Location[] s_chopTreeLocation = new Location[4];
   private static const std::vector<IsoGridSquare> s_chopTreeIndicators = std::make_unique<std::vector<>>();
    static IsoTree s_chopTreeHighlighted = nullptr;

    static IsoTree getNew() {
      /* synchronized - TODO: add std::mutex */ (CellLoader.isoTreeCache) {
         if (CellLoader.isoTreeCache.empty()) {
            return std::make_unique<IsoTree>();
         } else {
    IsoTree var1 = (IsoTree)CellLoader.isoTreeCache.pop();
            var1.sx = 0.0F;
    return var1;
         }
      }
   }

    public IsoTree() {
   }

    public IsoTree(IsoCell var1) {
      super(var1);
   }

    void save(ByteBuffer var1, bool var2) {
      super.save(var1, var2);
      var1.put((byte)this.LogYield);
      var1.put((byte)(this.damage / 10));
   }

    void load(ByteBuffer var1, int var2, bool var3) {
      super.load(var1, var2, var3);
      this.LogYield = var1.get();
      this.damage = var1.get() * 10;
      if (this.sprite != nullptr && this.sprite.getProperties().Val("tree") != nullptr) {
         this.size = int.parseInt(this.sprite.getProperties().Val("tree"));
         if (this.size < 1) {
            this.size = 1;
         }

         if (this.size > 6) {
            this.size = 6;
         }
      }
   }

    void checkMoveWithWind() {
      this.checkMoveWithWind(true);
   }

    void reset() {
      super.reset();
   }

    public IsoTree(IsoGridSquare var1, const std::string& var2) {
      super(var1, var2, false);
      this.initTree();
   }

    public IsoTree(IsoGridSquare var1, IsoSprite var2) {
      super(var1.getCell(), var1, var2);
      this.initTree();
   }

    void initTree() {
      this.setType(IsoObjectType.tree);
      if (this.sprite.getProperties().Val("tree") != nullptr) {
         this.size = int.parseInt(this.sprite.getProperties().Val("tree"));
         if (this.size < 1) {
            this.size = 1;
         }

         if (this.size > 6) {
            this.size = 6;
         }
      } else {
         this.size = 4;
      }

      switch (this.size) {
         case 1:
         case 2:
            this.LogYield = 1;
            break;
         case 3:
         case 4:
            this.LogYield = 2;
            break;
         case 5:
            this.LogYield = 3;
            break;
         case 6:
            this.LogYield = 4;
      }

      this.damage = this.LogYield * 80;
   }

    std::string getObjectName() {
      return "Tree";
   }

    void Damage(float var1) {
    float var2 = var1 * 0.05F;
      this.damage = (int)(this.damage - var2);
      if (this.damage <= 0) {
         this.square.transmitRemoveItemFromSquare(this);
         this.square.RecalcAllWithNeighbours(true);
    int var3 = this.LogYield;

         for (int var4 = 0; var4 < var3; var4++) {
            this.square.AddWorldInventoryItem("Base.Log", 0.0F, 0.0F, 0.0F);
            if (Rand.Next(4) == 0) {
               this.square.AddWorldInventoryItem("Base.TreeBranch", 0.0F, 0.0F, 0.0F);
            }

            if (Rand.Next(4) == 0) {
               this.square.AddWorldInventoryItem("Base.Twigs", 0.0F, 0.0F, 0.0F);
            }
         }

         this.reset();
         CellLoader.isoTreeCache.push_back(this);

         for (int var5 = 0; var5 < IsoPlayer.numPlayers; var5++) {
            LosUtil.cachecleared[var5] = true;
         }

         IsoGridSquare.setRecalcLightTime(-1);
         GameTime.instance.lightSourceUpdate = 100.0F;
         LuaEventManager.triggerEvent("OnContainerUpdate");
      }
   }

    void HitByVehicle(BaseVehicle var1, float var2) {
    BaseSoundEmitter var3 = IsoWorld.instance.getFreeEmitter(this.square.x + 0.5F, this.square.y + 0.5F, this.square.z);
    long var4 = var3.playSound("VehicleHitTree");
      var3.setParameterValue(var4, FMODManager.instance.getParameterDescription("VehicleSpeed"), var1.getCurrentSpeedKmHour());
      WorldSoundManager.instance.addSound(nullptr, this.square.getX(), this.square.getY(), this.square.getZ(), 20, 20, true, 4.0F, 15.0F);
      this.Damage(this.damage);
   }

    void WeaponHit(IsoGameCharacter var1, HandWeapon var2) {
    int var3 = var2.getConditionLowerChance() * 2 + var1.getMaintenanceMod();
      if (!var2.getCategories().contains("Axe")) {
         var3 = var2.getConditionLowerChance() / 2 + var1.getMaintenanceMod();
      }

      if (Rand.NextBool(var3)) {
         var2.setCondition(var2.getCondition() - 1);
      }

      if (dynamic_cast<IsoPlayer*>(var1) != nullptr) {
         ((IsoPlayer)var1).setMeleeHitSurface(Material.Tree);
         var1.getEmitter().playSound(var2.getZombieHitSound());
      } else {
         var1.getEmitter().playSound("ChopTree");
      }

      WorldSoundManager.instance.addSound(nullptr, this.square.getX(), this.square.getY(), this.square.getZ(), 20, 20, true, 4.0F, 15.0F);
      this.setRenderEffect(RenderEffectType.Hit_Tree_Shudder, true);
    float var4 = var2.getTreeDamage();
      if (var1.Traits.Axeman.isSet() && var2.getCategories().contains("Axe")) {
         var4 *= 1.5F;
      }

      this.damage = (int)(this.damage - var4);
      if (this.damage <= 0) {
         this.square.transmitRemoveItemFromSquare(this);
         var1.getEmitter().playSound("FallingTree");
         this.square.RecalcAllWithNeighbours(true);
    int var5 = this.LogYield;

         for (int var6 = 0; var6 < var5; var6++) {
            this.square.AddWorldInventoryItem("Base.Log", 0.0F, 0.0F, 0.0F);
            if (Rand.Next(4) == 0) {
               this.square.AddWorldInventoryItem("Base.TreeBranch", 0.0F, 0.0F, 0.0F);
            }

            if (Rand.Next(4) == 0) {
               this.square.AddWorldInventoryItem("Base.Twigs", 0.0F, 0.0F, 0.0F);
            }
         }

         this.reset();
         CellLoader.isoTreeCache.push_back(this);

         for (int var7 = 0; var7 < IsoPlayer.numPlayers; var7++) {
            LosUtil.cachecleared[var7] = true;
         }

         IsoGridSquare.setRecalcLightTime(-1);
         GameTime.instance.lightSourceUpdate = 100.0F;
         LuaEventManager.triggerEvent("OnContainerUpdate");
      }

      LuaEventManager.triggerEvent("OnWeaponHitTree", var1, var2);
   }

    void setHealth(int var1) {
      this.damage = Math.max(var1, 0);
   }

    int getHealth() {
      return this.damage;
   }

    int getMaxHealth() {
      return this.LogYield * 80;
   }

    int getSize() {
      return this.size;
   }

    float getSlowFactor(IsoMovingObject var1) {
    float var2 = 1.0F;
      if (dynamic_cast<IsoGameCharacter*>(var1) != nullptr) {
         if ("parkranger" == ((IsoGameCharacter)var1).getDescriptor().getProfession())) {
            var2 = 1.5F;
         }

         if ("lumberjack" == ((IsoGameCharacter)var1).getDescriptor().getProfession())) {
            var2 = 1.2F;
         }
      }

      if (this.size == 1 || this.size == 2) {
         return 0.8F * var2;
      } else {
         return this.size != 3 && this.size != 4 ? 0.3F * var2 : 0.5F * var2;
      }
   }

    void render(float var1, float var2, float var3, ColorInfo var4, bool var5, bool var6, Shader var7) {
      if (this.isHighlighted()) {
         if (this.square != nullptr) {
            s_chopTreeHighlighted = this;
         }
      } else {
    int var8 = IsoCamera.frameState.playerIndex;
         if (!this.bRenderFlag && !(this.fadeAlpha < this.getTargetAlpha(var8))) {
            this.renderInner(var1, var2, var3, var4, var5, false);
         } else {
            IndieGL.enableStencilTest();
            IndieGL.glStencilFunc(517, 128, 128);
            this.renderInner(var1, var2, var3, var4, var5, false);
    float var9 = 0.044999998F * (GameTime.getInstance().getMultiplier() / 1.6F);
            if (this.bRenderFlag && this.fadeAlpha > 0.25F) {
               this.fadeAlpha -= var9;
               if (this.fadeAlpha < 0.25F) {
                  this.fadeAlpha = 0.25F;
               }
            }

            if (!this.bRenderFlag) {
    float var10 = this.getTargetAlpha(var8);
               if (this.fadeAlpha < var10) {
                  this.fadeAlpha += var9;
                  if (this.fadeAlpha > var10) {
                     this.fadeAlpha = var10;
                  }
               }
            }

    float var12 = this.getAlpha(var8);
    float var11 = this.getTargetAlpha(var8);
            this.setAlphaAndTarget(var8, this.fadeAlpha);
            IndieGL.glStencilFunc(514, 128, 128);
            this.renderInner(var1, var2, var3, var4, true, false);
            this.setAlpha(var8, var12);
            this.setTargetAlpha(var8, var11);
            if (TreeShader.instance.StartShader()) {
               TreeShader.instance.setOutlineColor(0.1F, 0.1F, 0.1F, 1.0F - this.fadeAlpha);
               this.renderInner(var1, var2, var3, var4, true, true);
               IndieGL.EndShader();
            }

            IndieGL.glStencilFunc(519, 255, 255);
         }

         this.checkChopTreeIndicator(var1, var2, var3);
      }
   }

    void renderInner(float var1, float var2, float var3, ColorInfo var4, bool var5, bool var6) {
      if (this.sprite != nullptr && this.sprite.name != nullptr && this.sprite.name.contains("JUMBO")) {
    float var12 = this.offsetX;
    float var15 = this.offsetY;
         this.offsetX = 384 * Core.TileScale / 2 - 96 * Core.TileScale;
         this.offsetY = 256 * Core.TileScale - 32 * Core.TileScale;
         if (this.offsetX != var12 || this.offsetY != var15) {
            this.sx = 0.0F;
         }
      } else {
    float var7 = this.offsetX;
    float var8 = this.offsetY;
         this.offsetX = 32 * Core.TileScale;
         this.offsetY = 96 * Core.TileScale;
         if (this.offsetX != var7 || this.offsetY != var8) {
            this.sx = 0.0F;
         }
      }

      if (var6 && this.sprite != nullptr) {
    Texture var13 = this.sprite.getTextureForCurrentFrame(this.dir);
         if (var13 != nullptr) {
            TreeShader.instance.setStepSize(0.25F, var13.getWidth(), var13.getHeight());
         }
      }

      super.render(var1, var2, var3, var4, false, false, nullptr);
      if (this.AttachedAnimSprite != nullptr) {
    int var14 = this.AttachedAnimSprite.size();

         for (int var16 = 0; var16 < var14; var16++) {
    IsoSpriteInstance var9 = (IsoSpriteInstance)this.AttachedAnimSprite.get(var16);
    int var10 = IsoCamera.frameState.playerIndex;
    float var11 = this.getTargetAlpha(var10);
            this.setTargetAlpha(var10, 1.0F);
            var9.render(this, var1, var2, var3, this.dir, this.offsetX, this.offsetY, this.isHighlighted() ? this.getHighlightColor() : var4);
            this.setTargetAlpha(var10, var11);
            var9.update();
         }
      }
   }

    void setSprite(IsoSprite var1) {
      super.setSprite(var1);
      this.initTree();
   }

    bool isMaskClicked(int var1, int var2, bool var3) {
      if (super.isMaskClicked(var1, var2, var3)) {
    return true;
      } else if (this.AttachedAnimSprite == nullptr) {
    return false;
      } else {
         for (int var4 = 0; var4 < this.AttachedAnimSprite.size(); var4++) {
            if (((IsoSpriteInstance)this.AttachedAnimSprite.get(var4)).parentSprite.isMaskClicked(this.dir, var1, var2, var3)) {
    return true;
            }
         }

    return false;
      }
   }

    static void setChopTreeCursorLocation(int var0, int var1, int var2, int var3) {
      if (s_chopTreeLocation[var0] == nullptr) {
         s_chopTreeLocation[var0] = std::make_shared<Location>(-1, -1, -1);
      }

    Location var4 = s_chopTreeLocation[var0];
      var4.x = var1;
      var4.y = var2;
      var4.z = var3;
   }

    void checkChopTreeIndicator(float var1, float var2, float var3) {
      if (!this.isHighlighted()) {
    int var4 = IsoCamera.frameState.playerIndex;
    Location var5 = s_chopTreeLocation[var4];
         if (var5 != nullptr && var5.x != -1 && this.square != nullptr) {
            if (this.getCell().getDrag(var4) == nullptr) {
               var5.x = -1;
            } else {
               if (IsoUtils.DistanceToSquared(this.square.x + 0.5F, this.square.y + 0.5F, var5.x + 0.5F, var5.y + 0.5F) < 12.25F) {
                  s_chopTreeIndicators.push_back(this.square);
               }
            }
         }
      }
   }

    static void renderChopTreeIndicators() {
      if (!s_chopTreeIndicators.empty()) {
         PZArrayUtil.forEach(s_chopTreeIndicators, IsoTree::renderChopTreeIndicator);
         s_chopTreeIndicators.clear();
      }

      if (s_chopTreeHighlighted != nullptr) {
    IsoTree var0 = s_chopTreeHighlighted;
         s_chopTreeHighlighted = nullptr;
         var0.renderInner(var0.square.x, var0.square.y, var0.square.z, var0.getHighlightColor(), false, false);
      }
   }

    static void renderChopTreeIndicator(IsoGridSquare var0) {
    Texture var1 = Texture.getSharedTexture("media/ui/chop_tree.png");
      if (var1 != nullptr && var1.isReady()) {
    float var2 = var0.x;
    float var3 = var0.y;
    float var4 = var0.z;
    float var5 = IsoUtils.XToScreen(var2, var3, var4, 0) + IsoSprite.globalOffsetX;
    float var6 = IsoUtils.YToScreen(var2, var3, var4, 0) + IsoSprite.globalOffsetY;
         var5 -= 32 * Core.TileScale;
         var6 -= 96 * Core.TileScale;
         SpriteRenderer.instance.render(var1, var5, var6, 64 * Core.TileScale, 128 * Core.TileScale, 0.0F, 0.5F, 0.0F, 0.75F, nullptr);
      }
   }
}
} // namespace objects
} // namespace iso
} // namespace zombie
