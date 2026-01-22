#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "zombie/GameWindow.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/WornItems/BodyLocations.h"
#include "zombie/characters/WornItems/WornItems.h"
#include "zombie/core/Core.h"
#include "zombie/core/PerformanceSettings.h"
#include "zombie/core/SpriteRenderer.h"
#include "zombie/core/opengl/Shader.h"
#include "zombie/core/skinnedmodel/DeadBodyAtlas.h"
#include "zombie/core/skinnedmodel/ModelManager.h"
#include "zombie/core/skinnedmodel/advancedanimation/AnimNode.h"
#include "zombie/core/skinnedmodel/advancedanimation/AnimState.h"
#include "zombie/core/skinnedmodel/advancedanimation/AnimatedModel.h"
#include "zombie/core/skinnedmodel/advancedanimation/AnimationSet.h"
#include "zombie/core/skinnedmodel/population/Outfit.h"
#include "zombie/core/skinnedmodel/population/OutfitManager.h"
#include "zombie/core/skinnedmodel/visual/HumanVisual.h"
#include "zombie/core/skinnedmodel/visual/IHumanVisual.h"
#include "zombie/core/skinnedmodel/visual/ItemVisual.h"
#include "zombie/core/skinnedmodel/visual/ItemVisuals.h"
#include "zombie/core/textures/ColorInfo.h"
#include "zombie/core/textures/Texture.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/inventory/InventoryItem.h"
#include "zombie/inventory/ItemContainer.h"
#include "zombie/inventory/types/Clothing.h"
#include "zombie/inventory/types/InventoryContainer.h"
#include "zombie/inventory/types/Moveable.h"
#include "zombie/iso/IsoCamera.h"
#include "zombie/iso/IsoCell.h"
#include "zombie/iso/IsoDirections.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoMetaCell.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/IsoUtils.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/SliceY.h"
#include "zombie/iso/objects/IsoMannequin/Drawer.h"
#include "zombie/iso/objects/IsoMannequin/MannequinZone.h"
#include "zombie/iso/objects/IsoMannequin/PerPlayer.h"
#include "zombie/iso/objects/IsoMannequin/StaticPerPlayer.h"
#include "zombie/iso/sprite/IsoSprite.h"
#include "zombie/network/GameServer.h"
#include "zombie/scripting/ScriptManager.h"
#include "zombie/scripting/objects/MannequinScript.h"
#include "zombie/scripting/objects/ModelScript.h"
#include "zombie/util/StringUtils.h"
#include "zombie/util/list/PZArrayUtil.h"
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace iso {
namespace objects {


class IsoMannequin : public IsoObject {
public:
    static const ColorInfo inf = std::make_shared<ColorInfo>();
    bool bInit = false;
    bool bFemale = false;
    bool bZombie = false;
    bool bSkeleton = false;
    std::string mannequinScriptName = nullptr;
    std::string modelScriptName = nullptr;
    std::string textureName = nullptr;
    std::string animSet = nullptr;
    std::string animState = nullptr;
    std::string pose = nullptr;
    std::string outfit = nullptr;
    const HumanVisual humanVisual = std::make_shared<HumanVisual>(this);
    const ItemVisuals itemVisuals = std::make_shared<ItemVisuals>();
    const WornItems wornItems;
    MannequinScript mannequinScript = nullptr;
    ModelScript modelScript = nullptr;
   private const PerPlayer[] perPlayer = new PerPlayer[4];
    bool bAnimate = false;
    AnimatedModel animatedModel = nullptr;
   private Drawer[] drawers = nullptr;
    float screenX;
    float screenY;
   private static const StaticPerPlayer[] staticPerPlayer = new StaticPerPlayer[4];

    public IsoMannequin(IsoCell var1) {
      super(var1);
      this.wornItems = std::make_shared<WornItems>(BodyLocations.getGroup("Human"));

      for (int var2 = 0; var2 < 4; var2++) {
         this.perPlayer[var2] = std::make_unique<PerPlayer>();
      }
   }

    public IsoMannequin(IsoCell var1, IsoGridSquare var2, IsoSprite var3) {
      super(var1, var2, var3);
      this.wornItems = std::make_shared<WornItems>(BodyLocations.getGroup("Human"));

      for (int var4 = 0; var4 < 4; var4++) {
         this.perPlayer[var4] = std::make_unique<PerPlayer>();
      }
   }

    std::string getObjectName() {
      return "Mannequin";
   }

    HumanVisual getHumanVisual() {
      return this.humanVisual;
   }

    void getItemVisuals(ItemVisuals var1) {
      this.wornItems.getItemVisuals(var1);
   }

    bool isFemale() {
      return this.bFemale;
   }

    bool isZombie() {
      return this.bZombie;
   }

    bool isSkeleton() {
      return this.bSkeleton;
   }

    bool isItemAllowedInContainer(ItemContainer var1, InventoryItem var2) {
      return dynamic_cast<Clothing*>(var2) != nullptr && !StringUtils.isNullOrWhitespace(((Clothing)var2).getBodyLocation())
         ? true
         : dynamic_cast<InventoryContainer*>(var2) != nullptr && !StringUtils.isNullOrWhitespace(((InventoryContainer)var2).canBeEquipped());
   }

    std::string getMannequinScriptName() {
      return this.mannequinScriptName;
   }

    void setMannequinScriptName(const std::string& var1) {
      if (!StringUtils.isNullOrWhitespace(var1)) {
         if (ScriptManager.instance.getMannequinScript(var1) != nullptr) {
            this.mannequinScriptName = var1;
            this.bInit = true;
            this.mannequinScript = nullptr;
            this.textureName = nullptr;
            this.animSet = nullptr;
            this.animState = nullptr;
            this.pose = nullptr;
            this.outfit = nullptr;
            this.humanVisual.clear();
            this.itemVisuals.clear();
            this.wornItems.clear();
            this.initMannequinScript();
            this.initModelScript();
            if (this.outfit == nullptr) {
    Outfit var2 = OutfitManager.instance.GetRandomNonProfessionalOutfit(this.bFemale);
               this.humanVisual.dressInNamedOutfit(var2.m_Name, this.itemVisuals);
            } else if (!"none".equalsIgnoreCase(this.outfit)) {
               this.humanVisual.dressInNamedOutfit(this.outfit, this.itemVisuals);
            }

            this.humanVisual.setHairModel("");
            this.humanVisual.setBeardModel("");
            this.createInventory(this.itemVisuals);
            this.validateSkinTexture();
            this.validatePose();
            this.syncModel();
         }
      }
   }

    std::string getPose() {
      return this.pose;
   }

    void setRenderDirection(IsoDirections var1) {
    int var2 = IsoCamera.frameState.playerIndex;
      if (var1 != this.perPlayer[var2].renderDirection) {
         this.perPlayer[var2].renderDirection = var1;
      }
   }

    void rotate(IsoDirections var1) {
      if (var1 != nullptr && var1 != IsoDirections.Max) {
         this.dir = var1;

         for (int var2 = 0; var2 < 4; var2++) {
            this.perPlayer[var2].atlasTex = nullptr;
         }

         if (GameServer.bServer) {
            this.sendObjectChange("rotate");
         }
      }
   }

    void saveChange(const std::string& var1, KahluaTable var2, ByteBuffer var3) {
      if ("rotate" == var1)) {
         var3.put((byte)this.dir.index());
      } else {
         super.saveChange(var1, var2, var3);
      }
   }

    void loadChange(const std::string& var1, ByteBuffer var2) {
      if ("rotate" == var1)) {
    uint8_t var3 = var2.get();
         this.rotate(IsoDirections.fromIndex(var3));
      } else {
         super.loadChange(var1, var2);
      }
   }

    void getVariables(std::string> var1) {
      var1.put("Female", this.bFemale ? "true" : "false");
      var1.put("Pose", this.getPose());
   }

    void load(ByteBuffer var1, int var2, bool var3) {
      super.load(var1, var2, var3);
      this.dir = IsoDirections.fromIndex(var1.get());
      this.bInit = var1.get() == 1;
      this.bFemale = var1.get() == 1;
      this.bZombie = var1.get() == 1;
      this.bSkeleton = var1.get() == 1;
      if (var2 >= 191) {
         this.mannequinScriptName = GameWindow.ReadString(var1);
      }

      this.pose = GameWindow.ReadString(var1);
      this.humanVisual.load(var1, var2);
      this.textureName = this.humanVisual.getSkinTexture();
      this.wornItems.clear();
      if (this.container == nullptr) {
         this.container = std::make_shared<ItemContainer>("mannequin", this.getSquare(), this);
         this.container.setExplored(true);
      }

      this.container.clear();
      if (var1.get() == 1) {
         try {
            this.container.ID = var1.getInt();
    std::vector var4 = this.container.load(var1, var2);
    uint8_t var5 = var1.get();

            for (int var6 = 0; var6 < var5; var6++) {
    std::string var7 = GameWindow.ReadString(var1);
    short var8 = var1.getShort();
               if (var8 >= 0 && var8 < var4.size() && this.wornItems.getBodyLocationGroup().getLocation(var7) != nullptr) {
                  this.wornItems.setItem(var7, (InventoryItem)var4.get(var8));
               }
            }
         } catch (Exception var9) {
            if (this.container != nullptr) {
               DebugLog.log("Failed to stream in container ID: " + this.container.ID);
            }
         }
      }
   }

    void save(ByteBuffer var1, bool var2) {
    ItemContainer var3 = this.container;
      this.container = nullptr;
      super.save(var1, var2);
      this.container = var3;
      var1.put((byte)this.dir.index());
      var1.put((byte)(this.bInit ? 1 : 0));
      var1.put((byte)(this.bFemale ? 1 : 0));
      var1.put((byte)(this.bZombie ? 1 : 0));
      var1.put((byte)(this.bSkeleton ? 1 : 0));
      GameWindow.WriteString(var1, this.mannequinScriptName);
      GameWindow.WriteString(var1, this.pose);
      this.humanVisual.save(var1);
      if (var3 != nullptr) {
         var1.put((byte)1);
         var1.putInt(var3.ID);
    std::vector var4 = var3.save(var1);
         if (this.wornItems.size() > 127) {
            throw RuntimeException("too many worn items");
         }

         var1.put((byte)this.wornItems.size());
         this.wornItems.forEach(var2x -> {
            GameWindow.WriteString(var1, var2x.getLocation());
            var1.putShort((short)var4.indexOf(var2x.getItem()));
         });
      } else {
         var1.put((byte)0);
      }
   }

    void saveState(ByteBuffer var1) {
      if (!this.bInit) {
         this.initOutfit();
      }

      this.save(var1);
   }

    void loadState(ByteBuffer var1) {
      var1.get();
      var1.get();
      this.load(var1, 195);
      this.initOutfit();
      this.validateSkinTexture();
      this.validatePose();
      this.syncModel();
   }

    void addToWorld() {
      super.addToWorld();
      this.initOutfit();
      this.validateSkinTexture();
      this.validatePose();
      this.syncModel();
   }

    void initMannequinScript() {
      if (!StringUtils.isNullOrWhitespace(this.mannequinScriptName)) {
         this.mannequinScript = ScriptManager.instance.getMannequinScript(this.mannequinScriptName);
      }

      if (this.mannequinScript == nullptr) {
         this.modelScriptName = this.bFemale ? "FemaleBody" : "MaleBody";
         this.textureName = this.bFemale ? "F_Mannequin_White" : "M_Mannequin_White";
         this.animSet = "mannequin";
         this.animState = this.bFemale ? "female" : "male";
         this.outfit = nullptr;
      } else {
         this.bFemale = this.mannequinScript.isFemale();
         this.modelScriptName = this.mannequinScript.getModelScriptName();
         if (this.textureName == nullptr) {
            this.textureName = this.mannequinScript.getTexture();
         }

         this.animSet = this.mannequinScript.getAnimSet();
         this.animState = this.mannequinScript.getAnimState();
         if (this.pose == nullptr) {
            this.pose = this.mannequinScript.getPose();
         }

         if (this.outfit == nullptr) {
            this.outfit = this.mannequinScript.getOutfit();
         }
      }
   }

    void initModelScript() {
      if (!StringUtils.isNullOrWhitespace(this.modelScriptName)) {
         this.modelScript = ScriptManager.instance.getModelScript(this.modelScriptName);
      }
   }

    void validateSkinTexture() {
   }

    void validatePose() {
    AnimationSet var1 = AnimationSet.GetAnimationSet(this.animSet, false);
      if (var1 == nullptr) {
         DebugLog.General.warn("ERROR: mannequin AnimSet \"%s\" doesn't exist", new Object[]{this.animSet});
         this.pose = "Invalid";
      } else {
    AnimState var2 = var1.GetState(this.animState);
         if (var2 == nullptr) {
            DebugLog.General.warn("ERROR: mannequin AnimSet \"%s\" state \"%s\" doesn't exist", new Object[]{this.animSet, this.animState});
            this.pose = "Invalid";
         } else {
            for (AnimNode var4 : var2.m_Nodes) {
               if (var4.m_Name.equalsIgnoreCase(this.pose)) {
                  return;
               }
            }

            if (var2.m_Nodes == nullptr) {
               DebugLog.General
                  .warn("ERROR: mannequin AnimSet \"%s\" state \"%s\" node \"%s\" doesn't exist", new Object[]{this.animSet, this.animState, this.pose});
               this.pose = "Invalid";
            } else {
    AnimNode var5 = (AnimNode)PZArrayUtil.pickRandom(var2.m_Nodes);
               this.pose = var5.m_Name;
            }
         }
      }
   }

    void render(float var1, float var2, float var3, ColorInfo var4, bool var5, bool var6, Shader var7) {
    int var8 = IsoCamera.frameState.playerIndex;
      var1 += 0.5F;
      var2 += 0.5F;
      this.calcScreenPos(var1, var2, var3);
      this.renderShadow(var1, var2, var3);
      if (this.bAnimate) {
         this.animatedModel.update();
    Drawer var14 = this.drawers[SpriteRenderer.instance.getMainStateIndex()];
         var14.init(var1, var2, var3);
         SpriteRenderer.instance.drawGeneric(var14);
      } else {
    IsoDirections var9 = this.dir;
    PerPlayer var10 = this.perPlayer[var8];
         if (var10.renderDirection != nullptr && var10.renderDirection != IsoDirections.Max) {
            this.dir = var10.renderDirection;
            var10.renderDirection = nullptr;
            var10.bWasRenderDirection = true;
            var10.atlasTex = nullptr;
         } else if (var10.bWasRenderDirection) {
            var10.bWasRenderDirection = false;
            var10.atlasTex = nullptr;
         }

         if (var10.atlasTex == nullptr) {
            var10.atlasTex = DeadBodyAtlas.instance.getBodyTexture(this);
            DeadBodyAtlas.instance.render();
         }

         this.dir = var9;
         if (var10.atlasTex != nullptr) {
            if (this.isHighlighted()) {
               inf.r = this.getHighlightColor().r;
               inf.g = this.getHighlightColor().g;
               inf.b = this.getHighlightColor().b;
               inf.a = this.getHighlightColor().a;
            } else {
               inf.r = var4.r;
               inf.g = var4.g;
               inf.b = var4.b;
               inf.a = var4.a;
            }

            var4 = inf;
            if (!this.isHighlighted() && PerformanceSettings.LightingFrameSkip < 3) {
               this.square.interpolateLight(var4, var1 - this.square.getX(), var2 - this.square.getY());
            }

            var10.atlasTex.render((int)this.screenX, (int)this.screenY, var4.r, var4.g, var4.b, this.getAlpha(var8));
            if (Core.bDebug) {
            }
         }
      }
   }

    void renderFxMask(float var1, float var2, float var3, bool var4) {
   }

    void calcScreenPos(float var1, float var2, float var3) {
      if (IsoSprite.globalOffsetX == -1.0F) {
         IsoSprite.globalOffsetX = -IsoCamera.frameState.OffX;
         IsoSprite.globalOffsetY = -IsoCamera.frameState.OffY;
      }

      this.screenX = IsoUtils.XToScreen(var1, var2, var3, 0);
      this.screenY = IsoUtils.YToScreen(var1, var2, var3, 0);
      this.sx = this.screenX;
      this.sy = this.screenY;
      this.screenX = this.sx + IsoSprite.globalOffsetX;
      this.screenY = this.sy + IsoSprite.globalOffsetY;
      IsoObject[] var4 = (IsoObject[])this.square.getObjects().getElements();

      for (int var5 = 0; var5 < this.square.getObjects().size(); var5++) {
    IsoObject var6 = var4[var5];
         if (var6.isTableSurface()) {
            this.screenY = this.screenY - (var6.getSurfaceOffset() + 1.0F) * Core.TileScale;
         }
      }
   }

    void renderShadow(float var1, float var2, float var3) {
    Texture var4 = Texture.getSharedTexture("dropshadow");
    int var5 = IsoCamera.frameState.playerIndex;
    float var6 = 0.8F * this.getAlpha(var5);
    ColorInfo var7 = this.square.lighting[var5].lightInfo();
      var6 *= (var7.r + var7.g + var7.b) / 3.0F;
      var6 *= 0.8F;
    float var8 = this.screenX - var4.getWidth() / 2.0F * Core.TileScale;
    float var9 = this.screenY - var4.getHeight() / 2.0F * Core.TileScale;
      SpriteRenderer.instance
         .render(var4, var8, var9, (float)var4.getWidth() * Core.TileScale, (float)var4.getHeight() * Core.TileScale, 1.0F, 1.0F, 1.0F, var6, nullptr);
   }

    void initOutfit() {
      if (this.bInit) {
         this.initMannequinScript();
         this.initModelScript();
      } else {
         this.bInit = true;
         this.getPropertiesFromSprite();
         this.getPropertiesFromZone();
         this.initMannequinScript();
         this.initModelScript();
         if (this.outfit == nullptr) {
    Outfit var1 = OutfitManager.instance.GetRandomNonProfessionalOutfit(this.bFemale);
            this.humanVisual.dressInNamedOutfit(var1.m_Name, this.itemVisuals);
         } else if (!"none".equalsIgnoreCase(this.outfit)) {
            this.humanVisual.dressInNamedOutfit(this.outfit, this.itemVisuals);
         }

         this.humanVisual.setHairModel("");
         this.humanVisual.setBeardModel("");
         this.createInventory(this.itemVisuals);
      }
   }

    void getPropertiesFromSprite() {
    std::string var1 = this.sprite.name;
      switch (var1) {
         case "location_shop_mall_01_65":
            this.mannequinScriptName = "FemaleWhite01";
            this.dir = IsoDirections.SE;
            break;
         case "location_shop_mall_01_66":
            this.mannequinScriptName = "FemaleWhite02";
            this.dir = IsoDirections.S;
            break;
         case "location_shop_mall_01_67":
            this.mannequinScriptName = "FemaleWhite03";
            this.dir = IsoDirections.SE;
            break;
         case "location_shop_mall_01_68":
            this.mannequinScriptName = "MaleWhite01";
            this.dir = IsoDirections.SE;
            break;
         case "location_shop_mall_01_69":
            this.mannequinScriptName = "MaleWhite02";
            this.dir = IsoDirections.S;
            break;
         case "location_shop_mall_01_70":
            this.mannequinScriptName = "MaleWhite03";
            this.dir = IsoDirections.SE;
            break;
         case "location_shop_mall_01_73":
            this.mannequinScriptName = "FemaleBlack01";
            this.dir = IsoDirections.SE;
            break;
         case "location_shop_mall_01_74":
            this.mannequinScriptName = "FemaleBlack02";
            this.dir = IsoDirections.S;
            break;
         case "location_shop_mall_01_75":
            this.mannequinScriptName = "FemaleBlack03";
            this.dir = IsoDirections.SE;
            break;
         case "location_shop_mall_01_76":
            this.mannequinScriptName = "MaleBlack01";
            this.dir = IsoDirections.SE;
            break;
         case "location_shop_mall_01_77":
            this.mannequinScriptName = "MaleBlack02";
            this.dir = IsoDirections.S;
            break;
         case "location_shop_mall_01_78":
            this.mannequinScriptName = "MaleBlack03";
            this.dir = IsoDirections.SE;
      }
   }

    void getPropertiesFromZone() {
      if (this.getObjectIndex() != -1) {
    IsoMetaCell var1 = IsoWorld.instance.getMetaGrid().getCellData(this.square.x / 300, this.square.y / 300);
         if (var1 != nullptr && var1.mannequinZones != nullptr) {
    std::vector var2 = var1.mannequinZones;
    MannequinZone var3 = nullptr;

            for (int var4 = 0; var4 < var2.size(); var4++) {
               var3 = (MannequinZone)var2.get(var4);
               if (var3.contains(this.square.x, this.square.y, this.square.z)) {
                  break;
               }

               var3 = nullptr;
            }

            if (var3 != nullptr) {
               if (var3.bFemale != -1) {
                  this.bFemale = var3.bFemale == 1;
               }

               if (var3.dir != IsoDirections.Max) {
                  this.dir = var3.dir;
               }

               if (var3.mannequinScript != nullptr) {
                  this.mannequinScriptName = var3.mannequinScript;
               }

               if (var3.skin != nullptr) {
                  this.textureName = var3.skin;
               }

               if (var3.pose != nullptr) {
                  this.pose = var3.pose;
               }

               if (var3.outfit != nullptr) {
                  this.outfit = var3.outfit;
               }
            }
         }
      }
   }

    void syncModel() {
      this.humanVisual.setForceModelScript(this.modelScriptName);
    std::string var1 = this.modelScriptName;
      switch (var1) {
         case "FemaleBody":
            this.humanVisual.setForceModel(ModelManager.instance.m_femaleModel);
            break;
         case "MaleBody":
            this.humanVisual.setForceModel(ModelManager.instance.m_maleModel);
            break;
         default:
            this.humanVisual.setForceModel(ModelManager.instance.getLoadedModel(this.modelScriptName));
      }

      this.humanVisual.setSkinTextureName(this.textureName);
      this.wornItems.getItemVisuals(this.itemVisuals);

      for (int var3 = 0; var3 < 4; var3++) {
         this.perPlayer[var3].atlasTex = nullptr;
      }

      if (this.bAnimate) {
         if (this.animatedModel == nullptr) {
            this.animatedModel = std::make_unique<AnimatedModel>();
            this.drawers = new Drawer[3];

            for (int var4 = 0; var4 < this.drawers.length; var4++) {
               this.drawers[var4] = std::make_shared<Drawer>(this);
            }
         }

         this.animatedModel.setAnimSetName(this.getAnimSetName());
         this.animatedModel.setState(this.getAnimStateName());
         this.animatedModel.setVariable("Female", this.bFemale);
         this.animatedModel.setVariable("Pose", this.getPose());
         this.animatedModel.setAngle(this.dir.ToVector());
         this.animatedModel.setModelData(this.humanVisual, this.itemVisuals);
      }
   }

    void createInventory(ItemVisuals var1) {
      if (this.container == nullptr) {
         this.container = std::make_shared<ItemContainer>("mannequin", this.getSquare(), this);
         this.container.setExplored(true);
      }

      this.container.clear();
      this.wornItems.setFromItemVisuals(var1);
      this.wornItems.addItemsToItemContainer(this.container);
   }

    void wearItem(InventoryItem var1, IsoGameCharacter var2) {
      if (this.container.contains(var1)) {
    ItemVisual var3 = var1.getVisual();
         if (var3 != nullptr) {
            if (dynamic_cast<Clothing*>(var1) != nullptr && !StringUtils.isNullOrWhitespace(((Clothing)var1).getBodyLocation())) {
               this.wornItems.setItem(((Clothing)var1).getBodyLocation(), var1);
            } else {
               if (!(dynamic_cast<InventoryContainer*>(var1) != nullptr) || StringUtils.isNullOrWhitespace(((InventoryContainer)var1).canBeEquipped())) {
                  return;
               }

               this.wornItems.setItem(((InventoryContainer)var1).canBeEquipped(), var1);
            }

            if (var2 != nullptr) {
    std::vector var4 = this.container.getItems();

               for (int var5 = 0; var5 < var4.size(); var5++) {
    InventoryItem var6 = (InventoryItem)var4.get(var5);
                  if (!this.wornItems.contains(var6)) {
                     this.container.removeItemOnServer(var6);
                     this.container.Remove(var6);
                     var2.getInventory().AddItem(var6);
                     var5--;
                  }
               }
            }

            this.syncModel();
         }
      }
   }

    void checkClothing(InventoryItem var1) {
      for (int var2 = 0; var2 < this.wornItems.size(); var2++) {
    InventoryItem var3 = this.wornItems.getItemByIndex(var2);
         if (this.container == nullptr || this.container.getItems().indexOf(var3) == -1) {
            this.wornItems.remove(var3);
            this.syncModel();
            var2--;
         }
      }
   }

    std::string getAnimSetName() {
      return this.animSet;
   }

    std::string getAnimStateName() {
      return this.animState;
   }

    void getCustomSettingsFromItem(InventoryItem var1) {
      if (dynamic_cast<Moveable*>(var1) != nullptr) {
    ByteBuffer var2 = var1.getByteData();
         if (var2 == nullptr) {
            return;
         }

         var2.rewind();
    int var3 = var2.getInt();
         var2.get();
         var2.get();
         this.load(var2, var3);
      }
   }

    void setCustomSettingsToItem(InventoryItem var1) {
      if (dynamic_cast<Moveable*>(var1) != nullptr) {
         /* synchronized - TODO: add std::mutex */ (SliceY.SliceBufferLock) {
    ByteBuffer var3 = SliceY.SliceBuffer;
            var3.clear();
            var3.putInt(195);
            this.save(var3);
            var3.flip();
            var1.byteData = ByteBuffer.allocate(var3.limit());
            var1.byteData.put(var3);
         }

         if (this.container != nullptr) {
            var1.setActualWeight(var1.getActualWeight() + this.container.getContentsWeight());
         }
      }
   }

    static bool isMannequinSprite(IsoSprite var0) {
      return "Mannequin" == var0.getProperties().Val("CustomName"));
   }

    void resetMannequin() {
      this.bInit = false;
      this.bFemale = false;
      this.bZombie = false;
      this.bSkeleton = false;
      this.mannequinScriptName = nullptr;
      this.modelScriptName = nullptr;
      this.textureName = nullptr;
      this.animSet = nullptr;
      this.animState = nullptr;
      this.pose = nullptr;
      this.outfit = nullptr;
      this.humanVisual.clear();
      this.itemVisuals.clear();
      this.wornItems.clear();
      this.mannequinScript = nullptr;
      this.modelScript = nullptr;
      this.bAnimate = false;
   }

    static void renderMoveableItem(Moveable var0, int var1, int var2, int var3, IsoDirections var4) {
    int var5 = IsoCamera.frameState.playerIndex;
    StaticPerPlayer var6 = staticPerPlayer[var5];
      if (var6 == nullptr) {
         var6 = staticPerPlayer[var5] = std::make_shared<StaticPerPlayer>(var5);
      }

      var6.renderMoveableItem(var0, var1, var2, var3, var4);
   }

    static void renderMoveableObject(IsoMannequin var0, int var1, int var2, int var3, IsoDirections var4) {
      var0.setRenderDirection(var4);
   }

    static IsoDirections getDirectionFromItem(Moveable var0, int var1) {
    StaticPerPlayer var2 = staticPerPlayer[var1];
      if (var2 == nullptr) {
         var2 = staticPerPlayer[var1] = std::make_shared<StaticPerPlayer>(var1);
      }

      return var2.getDirectionFromItem(var0);
   }
}
} // namespace objects
} // namespace iso
} // namespace zombie
