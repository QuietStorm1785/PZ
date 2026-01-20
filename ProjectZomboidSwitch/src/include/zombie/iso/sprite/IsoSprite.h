#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameTime.h"
#include "zombie/GameWindow.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/Core.h"
#include "zombie/core/SpriteRenderer.h"
#include "zombie/core/opengl/CharacterModelCamera.h"
#include "zombie/core/properties/PropertyContainer.h"
#include "zombie/core/skinnedmodel/ModelCameraRenderData.h"
#include "zombie/core/skinnedmodel/ModelManager.h"
#include "zombie/core/skinnedmodel/ModelManager/ModelSlot.h"
#include "zombie/core/textures/ColorInfo.h"
#include "zombie/core/textures/Mask.h"
#include "zombie/core/textures/Texture.h"
#include "zombie/core/textures/TextureDraw.h"
#include "zombie/debug/DebugOptions.h"
#include "zombie/debug/LineDrawer.h"
#include "zombie/iso/IsoCamera.h"
#include "zombie/iso/IsoDirections.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoMovingObject.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/IsoObjectPicker.h"
#include "zombie/iso/IsoUtils.h"
#include "zombie/iso/IsoWater.h"
#include "zombie/iso/SpriteDetails/IsoObjectType.h"
#include "zombie/iso/Vector2.h"
#include "zombie/iso/Vector3.h"
#include "zombie/iso/WorldConverter.h"
#include "zombie/iso/sprite/IsoSprite/l_renderCurrentAnim.h"
#include "zombie/util/StringUtils.h"
#include "zombie/vehicles/BaseVehicle.h"
#include "zombie/vehicles/VehicleModelCamera.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace zombie {
namespace iso {
namespace sprite {


class IsoSprite {
public:
    static int maxCount = 0;
    static float alphaStep = 0.05F;
    static float globalOffsetX = -1.0F;
    static float globalOffsetY = -1.0F;
    static const ColorInfo info = std::make_shared<ColorInfo>();
   private static const std::unordered_map<std::string, Object[]> AnimNameSet = std::make_unique<std::unordered_map<>>();
    int firerequirement;
    std::string burntTile;
    bool forceAmbient;
    bool solidfloor;
    bool canBeRemoved;
    bool attachedFloor;
    bool cutW;
    bool cutN;
    bool solid;
    bool solidTrans;
    bool invisible;
    bool alwaysDraw;
    bool forceRender;
    bool moveWithWind = false;
    bool isBush = false;
    static const uint8_t RL_DEFAULT = 0;
    static const uint8_t RL_FLOOR = 1;
    uint8_t renderLayer = 0;
    int windType = 1;
    bool Animate = true;
    IsoAnim CurrentAnim = nullptr;
    bool DeleteWhenFinished = false;
    bool Loop = true;
    short soffX = 0;
    short soffY = 0;
    const PropertyContainer Properties = std::make_shared<PropertyContainer>();
    const ColorInfo TintMod = std::make_shared<ColorInfo>(1.0F, 1.0F, 1.0F, 1.0F);
   public const std::unordered_map<std::string, IsoAnim> AnimMap = new std::unordered_map<>(2);
   public const std::vector<IsoAnim> AnimStack = new std::vector<>(1);
    std::string name;
    int tileSheetIndex = 0;
    int ID = 20000000;
    IsoSpriteInstance def;
    ModelSlot modelSlot;
    IsoSpriteManager parentManager;
    IsoObjectType type = IsoObjectType.MAX;
    std::string parentObjectName = nullptr;
    IsoSpriteGrid spriteGrid;
    bool treatAsWallOrder = false;
    bool hideForWaterRender = false;

    void setHideForWaterRender() {
      this.hideForWaterRender = true;
   }

    public IsoSprite() {
      this.parentManager = IsoSpriteManager.instance;
      this.def = IsoSpriteInstance.get(this);
   }

    public IsoSprite(IsoSpriteManager var1) {
      this.parentManager = var1;
      this.def = IsoSpriteInstance.get(this);
   }

    static IsoSprite CreateSprite(IsoSpriteManager var0) {
      return std::make_shared<IsoSprite>(var0);
   }

    static IsoSprite CreateSpriteUsingCache(const std::string& var0, const std::string& var1, int var2) {
    IsoSprite var3 = CreateSprite(IsoSpriteManager.instance);
      return var3.setFromCache(var0, var1, var2);
   }

    static IsoSprite getSprite(IsoSpriteManager var0, int var1) {
      if (WorldConverter.instance.TilesetConversions != nullptr
         && !WorldConverter.instance.TilesetConversions.empty()
         && WorldConverter.instance.TilesetConversions.containsKey(var1)) {
         var1 = (int)WorldConverter.instance.TilesetConversions.get(var1);
      }

      return var0.IntMap.containsKey(var1) ? (IsoSprite)var0.IntMap.get(var1) : nullptr;
   }

    static void setSpriteID(IsoSpriteManager var0, int var1, IsoSprite var2) {
      if (var0.IntMap.containsKey(var2.ID)) {
         var0.IntMap.remove(var2.ID);
         var2.ID = var1;
         var0.IntMap.put(var1, var2);
      }
   }

    static IsoSprite getSprite(IsoSpriteManager var0, IsoSprite var1, int var2) {
      if (var1.name.contains("_")) {
         std::string[] var3 = var1.name.split("_");
    int var4 = int.parseInt(var3[var3.length - 1].trim());
         var4 += var2;
         return (IsoSprite)var0.NamedMap.get(var1.name.substr(0, var1.name.lastIndexOf("_")) + "_" + var4);
      } else {
    return nullptr;
      }
   }

    static IsoSprite getSprite(IsoSpriteManager var0, const std::string& var1, int var2) {
    IsoSprite var3 = (IsoSprite)var0.NamedMap.get(var1);
    std::string var4 = var3.name.substr(0, var3.name.lastIndexOf(95));
    std::string var5 = var3.name.substr(var3.name.lastIndexOf(95) + 1);
      if (var3.name.contains("_")) {
    int var6 = int.parseInt(var5.trim());
         var6 += var2;
         return var0.getSprite(var4 + "_" + var6);
      } else {
    return nullptr;
      }
   }

    static void DisposeAll() {
      AnimNameSet.clear();
   }

    static bool HasCache(const std::string& var0) {
      return AnimNameSet.containsKey(var0);
   }

    IsoSpriteInstance newInstance() {
      return IsoSpriteInstance.get(this);
   }

    PropertyContainer getProperties() {
      return this.Properties;
   }

    std::string getParentObjectName() {
      return this.parentObjectName;
   }

    void setParentObjectName(const std::string& var1) {
      this.parentObjectName = var1;
   }

    void save(DataOutputStream var1) {
      GameWindow.WriteString(var1, this.name);
   }

    void load(DataInputStream var1) {
      this.name = GameWindow.ReadString(var1);
      this.LoadFramesNoDirPageSimple(this.name);
   }

    void Dispose() {
      for (IsoAnim var2 : this.AnimMap.values()) {
         var2.Dispose();
      }

      this.AnimMap.clear();
      this.AnimStack.clear();
      this.CurrentAnim = nullptr;
   }

    bool isMaskClicked(IsoDirections var1, int var2, int var3) {
      try {
    Texture var4 = ((IsoDirectionFrame)this.CurrentAnim.Frames.get((int)this.def.Frame)).directions[var1.index()];
         if (var4 == nullptr) {
    return false;
         } else {
    Mask var5 = var4.getMask();
            if (var5 == nullptr) {
    return false;
            } else {
               var2 = (int)(var2 - var4.offsetX);
               var3 = (int)(var3 - var4.offsetY);
               return var5.get(var2, var3);
            }
         }
      } catch (Exception var6) {
         Logger.getLogger(GameWindow.class.getName()).log(Level.SEVERE, nullptr, var6);
    return true;
      }
   }

    bool isMaskClicked(IsoDirections var1, int var2, int var3, bool var4) {
      if (this.CurrentAnim == nullptr) {
    return false;
      } else {
         this.initSpriteInstance();

         try {
            if (this.CurrentAnim != nullptr && this.CurrentAnim.Frames != nullptr && !(this.def.Frame >= this.CurrentAnim.Frames.size())) {
    Texture var5 = ((IsoDirectionFrame)this.CurrentAnim.Frames.get((int)this.def.Frame)).directions[var1.index()];
               if (var5 == nullptr) {
    return false;
               } else {
    Mask var6 = var5.getMask();
                  if (var6 == nullptr) {
    return false;
                  } else {
                     if (var4) {
                        var2 = (int)(var2 - (var5.getWidthOrig() - var5.getWidth() - var5.offsetX));
                        var3 = (int)(var3 - var5.offsetY);
                        var2 = var5.getWidth() - var2;
                     } else {
                        var2 = (int)(var2 - var5.offsetX);
                        var3 = (int)(var3 - var5.offsetY);
                     }

                     return var2 >= 0 && var3 >= 0 && var2 <= var5.getWidth() && var3 <= var5.getHeight() ? var6.get(var2, var3) : false;
                  }
               }
            } else {
    return false;
            }
         } catch (Exception var7) {
            Logger.getLogger(GameWindow.class.getName()).log(Level.SEVERE, nullptr, var7);
    return true;
         }
      }
   }

    float getMaskClickedY(IsoDirections var1, int var2, int var3, bool var4) {
      try {
    Texture var5 = ((IsoDirectionFrame)this.CurrentAnim.Frames.get((int)this.def.Frame)).directions[var1.index()];
         if (var5 == nullptr) {
            return 10000.0F;
         } else {
    Mask var6 = var5.getMask();
            if (var6 == nullptr) {
               return 10000.0F;
            } else {
               if (var4) {
                  var2 = (int)(var2 - (var5.getWidthOrig() - var5.getWidth() - var5.offsetX));
                  var3 = (int)(var3 - var5.offsetY);
                  var2 = var5.getWidth() - var2;
               } else {
                  var2 = (int)(var2 - var5.offsetX);
                  var3 = (int)(var3 - var5.offsetY);
                  var2 = var5.getWidth() - var2;
               }

    return var3;
            }
         }
      } catch (Exception var7) {
         Logger.getLogger(GameWindow.class.getName()).log(Level.SEVERE, nullptr, var7);
         return 10000.0F;
      }
   }

    Texture LoadFrameExplicit(const std::string& var1) {
      this.CurrentAnim = std::make_unique<IsoAnim>();
      this.AnimMap.put("default", this.CurrentAnim);
      this.CurrentAnim.ID = this.AnimStack.size();
      this.AnimStack.push_back(this.CurrentAnim);
      return this.CurrentAnim.LoadFrameExplicit(var1);
   }

    void LoadFrames(const std::string& var1, const std::string& var2, int var3) {
      if (!this.AnimMap.containsKey(var2)) {
         this.CurrentAnim = std::make_unique<IsoAnim>();
         this.AnimMap.put(var2, this.CurrentAnim);
         this.CurrentAnim.ID = this.AnimStack.size();
         this.AnimStack.push_back(this.CurrentAnim);
         this.CurrentAnim.LoadFrames(var1, var2, var3);
      }
   }

    void LoadFramesReverseAltName(const std::string& var1, const std::string& var2, const std::string& var3, int var4) {
      if (!this.AnimMap.containsKey(var3)) {
         this.CurrentAnim = std::make_unique<IsoAnim>();
         this.AnimMap.put(var3, this.CurrentAnim);
         this.CurrentAnim.ID = this.AnimStack.size();
         this.AnimStack.push_back(this.CurrentAnim);
         this.CurrentAnim.LoadFramesReverseAltName(var1, var2, var3, var4);
      }
   }

    void LoadFramesNoDirPage(const std::string& var1, const std::string& var2, int var3) {
      this.CurrentAnim = std::make_unique<IsoAnim>();
      this.AnimMap.put(var2, this.CurrentAnim);
      this.CurrentAnim.ID = this.AnimStack.size();
      this.AnimStack.push_back(this.CurrentAnim);
      this.CurrentAnim.LoadFramesNoDirPage(var1, var2, var3);
   }

    void LoadFramesNoDirPageDirect(const std::string& var1, const std::string& var2, int var3) {
      this.CurrentAnim = std::make_unique<IsoAnim>();
      this.AnimMap.put(var2, this.CurrentAnim);
      this.CurrentAnim.ID = this.AnimStack.size();
      this.AnimStack.push_back(this.CurrentAnim);
      this.CurrentAnim.LoadFramesNoDirPageDirect(var1, var2, var3);
   }

    void LoadFramesNoDirPageSimple(const std::string& var1) {
      if (this.AnimMap.containsKey("default")) {
    IsoAnim var2 = this.AnimMap.get("default");
         this.AnimStack.remove(var2);
         this.AnimMap.remove("default");
      }

      this.CurrentAnim = std::make_unique<IsoAnim>();
      this.AnimMap.put("default", this.CurrentAnim);
      this.CurrentAnim.ID = this.AnimStack.size();
      this.AnimStack.push_back(this.CurrentAnim);
      this.CurrentAnim.LoadFramesNoDirPage(var1);
   }

    void ReplaceCurrentAnimFrames(const std::string& var1) {
      if (this.CurrentAnim != nullptr) {
         this.CurrentAnim.Frames.clear();
         this.CurrentAnim.LoadFramesNoDirPage(var1);
      }
   }

    void LoadFramesPageSimple(const std::string& var1, const std::string& var2, const std::string& var3, const std::string& var4) {
      this.CurrentAnim = std::make_unique<IsoAnim>();
      this.AnimMap.put("default", this.CurrentAnim);
      this.CurrentAnim.ID = this.AnimStack.size();
      this.AnimStack.push_back(this.CurrentAnim);
      this.CurrentAnim.LoadFramesPageSimple(var1, var2, var3, var4);
   }

    void LoadFramesPcx(const std::string& var1, const std::string& var2, int var3) {
      if (!this.AnimMap.containsKey(var2)) {
         this.CurrentAnim = std::make_unique<IsoAnim>();
         this.AnimMap.put(var2, this.CurrentAnim);
         this.CurrentAnim.ID = this.AnimStack.size();
         this.AnimStack.push_back(this.CurrentAnim);
         this.CurrentAnim.LoadFramesPcx(var1, var2, var3);
      }
   }

    void PlayAnim(IsoAnim var1) {
      if (this.CurrentAnim == nullptr || this.CurrentAnim != var1) {
         this.CurrentAnim = var1;
      }
   }

    void PlayAnim(const std::string& var1) {
      if ((this.CurrentAnim == nullptr || !this.CurrentAnim.name == var1)) && this.AnimMap.containsKey(var1)) {
         this.CurrentAnim = this.AnimMap.get(var1);
      }
   }

    void PlayAnimUnlooped(const std::string& var1) {
      if (this.AnimMap.containsKey(var1)) {
         if (this.CurrentAnim == nullptr || !this.CurrentAnim.name == var1)) {
            this.CurrentAnim = this.AnimMap.get(var1);
         }

         this.CurrentAnim.looped = false;
      }
   }

    void ChangeTintMod(ColorInfo var1) {
      this.TintMod.r = var1.r;
      this.TintMod.g = var1.g;
      this.TintMod.b = var1.b;
      this.TintMod.a = var1.a;
   }

    void RenderGhostTile(int var1, int var2, int var3) {
    IsoSpriteInstance var4 = IsoSpriteInstance.get(this);
      var4.alpha = var4.targetAlpha = 0.6F;
      this.render(var4, nullptr, var1, var2, var3, IsoDirections.N, 32 * Core.TileScale, 96 * Core.TileScale, IsoGridSquare.getDefColorInfo(), true);
   }

    void RenderGhostTileRed(int var1, int var2, int var3) {
    IsoSpriteInstance var4 = IsoSpriteInstance.get(this);
      var4.tintr = 0.65F;
      var4.tintg = 0.2F;
      var4.tintb = 0.2F;
      var4.alpha = var4.targetAlpha = 0.6F;
      this.render(var4, nullptr, var1, var2, var3, IsoDirections.N, 32 * Core.TileScale, 96 * Core.TileScale, IsoGridSquare.getDefColorInfo(), true);
   }

    void RenderGhostTileColor(int var1, int var2, int var3, float var4, float var5, float var6, float var7) {
      this.RenderGhostTileColor(var1, var2, var3, 0.0F, 0.0F, var4, var5, var6, var7);
   }

    void RenderGhostTileColor(int var1, int var2, int var3, float var4, float var5, float var6, float var7, float var8, float var9) {
    IsoSpriteInstance var10 = IsoSpriteInstance.get(this);
      var10.tintr = var6;
      var10.tintg = var7;
      var10.tintb = var8;
      var10.alpha = var10.targetAlpha = var9;
      IsoGridSquare.getDefColorInfo().r = IsoGridSquare.getDefColorInfo().g = IsoGridSquare.getDefColorInfo().b = IsoGridSquare.getDefColorInfo().a = 1.0F;
    int var11 = Core.TileScale;
      this.render(var10, nullptr, var1, var2, var3, IsoDirections.N, 32 * var11 + var4, 96 * var11 + var5, IsoGridSquare.getDefColorInfo(), true);
   }

    bool hasActiveModel() {
      if (!ModelManager.instance.bDebugEnableModels) {
    return false;
      } else {
         return !ModelManager.instance.isCreated() ? false : this.modelSlot != nullptr && this.modelSlot.active;
      }
   }

    void renderVehicle(IsoSpriteInstance var1, IsoObject var2, float var3, float var4, float var5, float var6, float var7, ColorInfo var8, bool var9) {
      if (var1 != nullptr) {
         if (this.hasActiveModel()) {
            SpriteRenderer.instance
               .drawGeneric(((ModelCameraRenderData)ModelCameraRenderData.s_pool.alloc()).init(VehicleModelCamera.instance, this.modelSlot));
            SpriteRenderer.instance.drawModel(this.modelSlot);
            if (!BaseVehicle.RENDER_TO_TEXTURE) {
               return;
            }
         }

         info.r = var8.r;
         info.g = var8.g;
         info.b = var8.b;
         info.a = var8.a;

         try {
            if (var9) {
               var1.renderprep(var2);
            }

    float var10 = 0.0F;
    float var11 = 0.0F;
            if (globalOffsetX == -1.0F) {
               globalOffsetX = -IsoCamera.frameState.OffX;
               globalOffsetY = -IsoCamera.frameState.OffY;
            }

            if (var2 == nullptr || var2.sx == 0.0F || dynamic_cast<IsoMovingObject*>(var2) != nullptr) {
               var10 = IsoUtils.XToScreen(var3 + var1.offX, var4 + var1.offY, var5 + var1.offZ, 0);
               var11 = IsoUtils.YToScreen(var3 + var1.offX, var4 + var1.offY, var5 + var1.offZ, 0);
               var10 -= var6;
               var11 -= var7;
               if (var2 != nullptr) {
                  var2.sx = var10;
                  var2.sy = var11;
               }
            }

            if (var2 != nullptr) {
               var10 = var2.sx + globalOffsetX;
               var11 = var2.sy + globalOffsetY;
               var10 += this.soffX;
               var11 += this.soffY;
            } else {
               var10 += globalOffsetX;
               var11 += globalOffsetY;
               var10 += this.soffX;
               var11 += this.soffY;
            }

            if (var9) {
               if (var1.tintr != 1.0F || var1.tintg != 1.0F || var1.tintb != 1.0F) {
                  info.r = info.r * var1.tintr;
                  info.g = info.g * var1.tintg;
                  info.b = info.b * var1.tintb;
               }

               info.a = var1.alpha;
            }

            if (!this.hasActiveModel() && (this.TintMod.r != 1.0F || this.TintMod.g != 1.0F || this.TintMod.b != 1.0F)) {
               info.r = info.r * this.TintMod.r;
               info.g = info.g * this.TintMod.g;
               info.b = info.b * this.TintMod.b;
            }

            if (this.hasActiveModel()) {
    float var12 = var1.getScaleX() * Core.TileScale;
    float var13 = -var1.getScaleY() * Core.TileScale;
    float var14 = 0.666F;
               var12 /= 4.0F * var14;
               var13 /= 4.0F * var14;
    int var15 = ModelManager.instance.bitmap.getTexture().getWidth();
    int var16 = ModelManager.instance.bitmap.getTexture().getHeight();
               var10 -= var15 * var12 / 2.0F;
               var11 -= var16 * var13 / 2.0F;
    float var17 = ((BaseVehicle)var2).jniTransform.origin.y / 2.46F;
               var11 += 96.0F * var17 / var13 / var14;
               var11 += 27.84F / var13 / var14;
               if (Core.getInstance().RenderShader != nullptr && Core.getInstance().getOffscreenBuffer() != nullptr) {
                  SpriteRenderer.instance
                     .render((Texture)ModelManager.instance.bitmap.getTexture(), var10, var11, var15 * var12, var16 * var13, 1.0F, 1.0F, 1.0F, info.a, nullptr);
               } else {
                  SpriteRenderer.instance
                     .render(
                        (Texture)ModelManager.instance.bitmap.getTexture(), var10, var11, var15 * var12, var16 * var13, info.r, info.g, info.b, info.a, nullptr
                     );
               }

               if (Core.bDebug && DebugOptions.instance.ModelRenderBounds.getValue()) {
                  LineDrawer.drawRect(var10, var11, var15 * var12, var16 * var13, 1.0F, 1.0F, 1.0F, 1.0F, 1);
               }
            }

            info.r = 1.0F;
            info.g = 1.0F;
            info.b = 1.0F;
         } catch (Exception var18) {
            Logger.getLogger(GameWindow.class.getName()).log(Level.SEVERE, nullptr, var18);
         }
      }
   }

    IsoSpriteInstance getSpriteInstance() {
      this.initSpriteInstance();
      return this.def;
   }

    void initSpriteInstance() {
      if (this.def == nullptr) {
         this.def = IsoSpriteInstance.get(this);
      }
   }

    void render(IsoObject var1, float var2, float var3, float var4, IsoDirections var5, float var6, float var7, ColorInfo var8, bool var9) {
      this.render(var1, var2, var3, var4, var5, var6, var7, var8, var9, nullptr);
   }

   public const void render(
      IsoObject var1, float var2, float var3, float var4, IsoDirections var5, float var6, float var7, ColorInfo var8, boolean var9, Consumer<TextureDraw> var10
   ) {
      this.render(this.getSpriteInstance(), var1, var2, var3, var4, var5, var6, var7, var8, var9, var10);
   }

   public const void render(
      IsoSpriteInstance var1, IsoObject var2, float var3, float var4, float var5, IsoDirections var6, float var7, float var8, ColorInfo var9, boolean var10
   ) {
      this.render(var1, var2, var3, var4, var5, var6, var7, var8, var9, var10, nullptr);
   }

   public void render(
      IsoSpriteInstance var1,
      IsoObject var2,
      float var3,
      float var4,
      float var5,
      IsoDirections var6,
      float var7,
      float var8,
      ColorInfo var9,
      boolean var10,
      Consumer<TextureDraw> var11
   ) {
      if (this.hasActiveModel()) {
         this.renderActiveModel();
      } else {
         this.renderCurrentAnim(var1, var2, var3, var4, var5, var6, var7, var8, var9, var10, var11);
      }
   }

   public void renderCurrentAnim(
      IsoSpriteInstance var1,
      IsoObject var2,
      float var3,
      float var4,
      float var5,
      IsoDirections var6,
      float var7,
      float var8,
      ColorInfo var9,
      boolean var10,
      Consumer<TextureDraw> var11
   ) {
      if (DebugOptions.instance.IsoSprite.RenderSprites.getValue()) {
         if (this.CurrentAnim != nullptr && !this.CurrentAnim.Frames.empty()) {
    float var12 = this.getCurrentSpriteFrame(var1);
            info.set(var9);
    Vector3 var13 = l_renderCurrentAnim.colorInfoBackup.set(info.r, info.g, info.b);
    Vector2 var14 = l_renderCurrentAnim.spritePos.set(0.0F, 0.0F);
            this.prepareToRenderSprite(var1, var2, var3, var4, var5, var6, var7, var8, var10, (int)var12, var14);
            this.performRenderFrame(var1, var2, var6, (int)var12, var14.x, var14.y, var11);
            info.r = var13.x;
            info.g = var13.y;
            info.b = var13.z;
         }
      }
   }

    float getCurrentSpriteFrame(IsoSpriteInstance var1) {
      if (this.CurrentAnim.FramesArray == nullptr) {
         this.CurrentAnim.FramesArray = this.CurrentAnim.Frames.toArray(new IsoDirectionFrame[0]);
      }

      if (this.CurrentAnim.FramesArray.length != this.CurrentAnim.Frames.size()) {
         this.CurrentAnim.FramesArray = this.CurrentAnim.Frames.toArray(this.CurrentAnim.FramesArray);
      }

    float var2;
      if (var1.Frame >= this.CurrentAnim.Frames.size()) {
         var2 = this.CurrentAnim.FramesArray.length - 1;
      } else if (var1.Frame < 0.0F) {
         var1.Frame = 0.0F;
         var2 = 0.0F;
      } else {
         var2 = var1.Frame;
      }

    return var2;
   }

   private void prepareToRenderSprite(
      IsoSpriteInstance var1,
      IsoObject var2,
      float var3,
      float var4,
      float var5,
      IsoDirections var6,
      float var7,
      float var8,
      boolean var9,
      int var10,
      Vector2 var11
   ) {
      if (var9) {
         var1.renderprep(var2);
      }

    float var12 = 0.0F;
    float var13 = 0.0F;
      if (globalOffsetX == -1.0F) {
         globalOffsetX = -IsoCamera.frameState.OffX;
         globalOffsetY = -IsoCamera.frameState.OffY;
      }

      if (var2 == nullptr || var2.sx == 0.0F || dynamic_cast<IsoMovingObject*>(var2) != nullptr) {
         var12 = IsoUtils.XToScreen(var3 + var1.offX, var4 + var1.offY, var5 + var1.offZ, 0);
         var13 = IsoUtils.YToScreen(var3 + var1.offX, var4 + var1.offY, var5 + var1.offZ, 0);
         var12 -= var7;
         var13 -= var8;
         if (var2 != nullptr) {
            var2.sx = var12;
            var2.sy = var13;
         }

         var12 += globalOffsetX;
         var13 += globalOffsetY;
         var12 += this.soffX;
         var13 += this.soffY;
      } else if (var2 != nullptr) {
         var12 = var2.sx + globalOffsetX;
         var13 = var2.sy + globalOffsetY;
         var12 += this.soffX;
         var13 += this.soffY;
      } else {
         var12 += globalOffsetX;
         var13 += globalOffsetY;
         var12 += this.soffX;
         var13 += this.soffY;
      }

      if (dynamic_cast<IsoMovingObject*>(var2) != nullptr && this.CurrentAnim != nullptr && this.CurrentAnim.FramesArray[var10].getTexture(var6) != nullptr) {
         var12 -= this.CurrentAnim.FramesArray[var10].getTexture(var6).getWidthOrig() / 2 * var1.getScaleX();
         var13 -= this.CurrentAnim.FramesArray[var10].getTexture(var6).getHeightOrig() * var1.getScaleY();
      }

      if (var9) {
         if (var1.tintr != 1.0F || var1.tintg != 1.0F || var1.tintb != 1.0F) {
            info.r = info.r * var1.tintr;
            info.g = info.g * var1.tintg;
            info.b = info.b * var1.tintb;
         }

         info.a = var1.alpha;
         if (var1.bMultiplyObjectAlpha && var2 != nullptr) {
            info.a = info.a * var2.getAlpha(IsoCamera.frameState.playerIndex);
         }
      }

      if (this.TintMod.r != 1.0F || this.TintMod.g != 1.0F || this.TintMod.b != 1.0F) {
         info.r = info.r * this.TintMod.r;
         info.g = info.g * this.TintMod.g;
         info.b = info.b * this.TintMod.b;
      }

      var11.set(var12, var13);
   }

    void performRenderFrame(IsoSpriteInstance var1, IsoObject var2, IsoDirections var3, int var4, float var5, float var6, Consumer<TextureDraw> var7) {
      if (var4 < this.CurrentAnim.FramesArray.length) {
    IsoDirectionFrame var8 = this.CurrentAnim.FramesArray[var4];
    Texture var9 = var8.getTexture(var3);
         if (var9 != nullptr) {
            if (Core.TileScale == 2 && var9.getWidthOrig() == 64 && var9.getHeightOrig() == 128) {
               var1.setScale(2.0F, 2.0F);
            }

            if (Core.TileScale == 2 && var1.scaleX == 2.0F && var1.scaleY == 2.0F && var9.getWidthOrig() == 128 && var9.getHeightOrig() == 256) {
               var1.setScale(1.0F, 1.0F);
            }

            if (!(var1.scaleX <= 0.0F) && !(var1.scaleY <= 0.0F)) {
    float var10 = var9.getWidth();
    float var11 = var9.getHeight();
    float var12 = var1.scaleX;
    float var13 = var1.scaleY;
               if (var12 != 1.0F) {
                  var5 += var9.getOffsetX() * (var12 - 1.0F);
                  var10 *= var12;
               }

               if (var13 != 1.0F) {
                  var6 += var9.getOffsetY() * (var13 - 1.0F);
                  var11 *= var13;
               }

               if (DebugOptions.instance.IsoSprite.MovingObjectEdges.getValue() && dynamic_cast<IsoMovingObject*>(var2) != nullptr) {
                  this.renderSpriteOutline(var5, var6, var9, var12, var13);
               }

               if (DebugOptions.instance.IsoSprite.DropShadowEdges.getValue() && StringUtils == var9.getName(), "dropshadow")) {
                  this.renderSpriteOutline(var5, var6, var9, var12, var13);
               }

               if (!this.hideForWaterRender || !IsoWater.getInstance().getShaderEnable()) {
                  if (var2 != nullptr && var2.getObjectRenderEffectsToApply() != nullptr) {
                     var8.render(var2.getObjectRenderEffectsToApply(), var5, var6, var10, var11, var3, info, var1.Flip, var7);
                  } else {
                     var8.render(var5, var6, var10, var11, var3, info, var1.Flip, var7);
                  }
               }

               if (var4 < this.CurrentAnim.FramesArray.length && IsoObjectPicker.Instance.wasDirty && IsoCamera.frameState.playerIndex == 0 && var2 != nullptr) {
    bool var14 = var3 == IsoDirections.W || var3 == IsoDirections.SW || var3 == IsoDirections.S;
                  if (var1.Flip) {
                     var14 = !var14;
                  }

                  var5 = var2.sx + globalOffsetX;
                  var6 = var2.sy + globalOffsetY;
                  if (dynamic_cast<IsoMovingObject*>(var2) != nullptr) {
                     var5 -= var9.getWidthOrig() / 2 * var12;
                     var6 -= var9.getHeightOrig() * var13;
                  }

                  IsoObjectPicker.Instance
                     .Add((int)var5, (int)var6, (int)(var9.getWidthOrig() * var12), (int)(var9.getHeightOrig() * var13), var2.square, var2, var14, var12, var13);
               }
            }
         }
      }
   }

    void renderSpriteOutline(float var1, float var2, Texture var3, float var4, float var5) {
      LineDrawer.drawRect(var1, var2, var3.getWidthOrig() * var4, var3.getHeightOrig() * var5, 1.0F, 1.0F, 1.0F, 1.0F, 1);
      LineDrawer.drawRect(
         var1 + var3.getOffsetX() * var4, var2 + var3.getOffsetY() * var5, var3.getWidth() * var4, var3.getHeight() * var5, 1.0F, 1.0F, 1.0F, 1.0F, 1
      );
   }

    void renderActiveModel() {
      if (DebugOptions.instance.IsoSprite.RenderModels.getValue()) {
         this.modelSlot.model.updateLights();
         SpriteRenderer.instance.drawGeneric(((ModelCameraRenderData)ModelCameraRenderData.s_pool.alloc()).init(CharacterModelCamera.instance, this.modelSlot));
         SpriteRenderer.instance.drawModel(this.modelSlot);
      }
   }

    void renderBloodSplat(float var1, float var2, float var3, ColorInfo var4) {
      if (this.CurrentAnim != nullptr && !this.CurrentAnim.Frames.empty()) {
    uint8_t var5 = -8;
    short var6 = -228;
         var5 = 0;
    uint8_t var11 = 0;

         try {
            if (globalOffsetX == -1.0F) {
               globalOffsetX = -IsoCamera.frameState.OffX;
               globalOffsetY = -IsoCamera.frameState.OffY;
            }

    float var7 = IsoUtils.XToScreen(var1, var2, var3, 0);
    float var8 = IsoUtils.YToScreen(var1, var2, var3, 0);
            var7 = (int)var7;
            var8 = (int)var8;
            var7 -= var5;
            var8 -= var11;
            var7 += globalOffsetX;
            var8 += globalOffsetY;
            if (var7 >= IsoCamera.frameState.OffscreenWidth || var7 + 64.0F <= 0.0F) {
               return;
            }

            if (var8 >= IsoCamera.frameState.OffscreenHeight || var8 + 64.0F <= 0.0F) {
               return;
            }

            info.r = var4.r;
            info.g = var4.g;
            info.b = var4.b;
            info.a = var4.a;
            ((IsoDirectionFrame)this.CurrentAnim.Frames.get(0)).render(var7, var8, IsoDirections.N, info, false, nullptr);
         } catch (Exception var9) {
            Logger.getLogger(GameWindow.class.getName()).log(Level.SEVERE, nullptr, var9);
         }
      }
   }

    void renderObjectPicker(IsoSpriteInstance var1, IsoObject var2, IsoDirections var3) {
      if (this.CurrentAnim != nullptr) {
         if (var1 != nullptr) {
            if (IsoPlayer.getInstance() == IsoPlayer.players[0]) {
               if (!this.CurrentAnim.Frames.empty()) {
                  if (var1.Frame >= this.CurrentAnim.Frames.size()) {
                     var1.Frame = 0.0F;
                  }

                  if (((IsoDirectionFrame)this.CurrentAnim.Frames.get((int)var1.Frame)).getTexture(var3) != nullptr) {
    float var4 = var2.sx + globalOffsetX;
    float var5 = var2.sy + globalOffsetY;
                     if (dynamic_cast<IsoMovingObject*>(var2) != nullptr) {
                        var4 -= ((IsoDirectionFrame)this.CurrentAnim.Frames.get((int)var1.Frame)).getTexture(var3).getWidthOrig() / 2 * var1.getScaleX();
                        var5 -= ((IsoDirectionFrame)this.CurrentAnim.Frames.get((int)var1.Frame)).getTexture(var3).getHeightOrig() * var1.getScaleY();
                     }

                     if (var1.Frame < this.CurrentAnim.Frames.size() && IsoObjectPicker.Instance.wasDirty && IsoCamera.frameState.playerIndex == 0) {
    Texture var6 = ((IsoDirectionFrame)this.CurrentAnim.Frames.get((int)var1.Frame)).getTexture(var3);
    bool var7 = var3 == IsoDirections.W || var3 == IsoDirections.SW || var3 == IsoDirections.S;
                        if (var1.Flip) {
                           var7 = !var7;
                        }

                        IsoObjectPicker.Instance
                           .Add(
                              (int)var4,
                              (int)var5,
                              (int)(var6.getWidthOrig() * var1.getScaleX()),
                              (int)(var6.getHeightOrig() * var1.getScaleY()),
                              var2.square,
                              var2,
                              var7,
                              var1.getScaleX(),
                              var1.getScaleY()
                           );
                     }
                  }
               }
            }
         }
      }
   }

    Texture getTextureForFrame(int var1, IsoDirections var2) {
      if (this.CurrentAnim != nullptr && !this.CurrentAnim.Frames.empty()) {
         if (this.CurrentAnim.FramesArray == nullptr) {
            this.CurrentAnim.FramesArray = this.CurrentAnim.Frames.toArray(new IsoDirectionFrame[0]);
         }

         if (this.CurrentAnim.FramesArray.length != this.CurrentAnim.Frames.size()) {
            this.CurrentAnim.FramesArray = this.CurrentAnim.Frames.toArray(this.CurrentAnim.FramesArray);
         }

         if (var1 >= this.CurrentAnim.FramesArray.length) {
            var1 = this.CurrentAnim.FramesArray.length - 1;
         }

         if (var1 < 0) {
            var1 = 0;
         }

         return this.CurrentAnim.FramesArray[var1].getTexture(var2);
      } else {
    return nullptr;
      }
   }

    Texture getTextureForCurrentFrame(IsoDirections var1) {
      this.initSpriteInstance();
      return this.getTextureForFrame((int)this.def.Frame, var1);
   }

    void update() {
      this.update(this.def);
   }

    void update(IsoSpriteInstance var1) {
      if (var1 == nullptr) {
         var1 = IsoSpriteInstance.get(this);
      }

      if (this.CurrentAnim != nullptr) {
         if (this.Animate && !var1.Finished) {
    float var2 = var1.Frame;
            if (!GameTime.isGamePaused()) {
               var1.Frame = var1.Frame + var1.AnimFrameIncrease * (GameTime.instance.getMultipliedSecondsSinceLastUpdate() * 60.0F);
            }

            if ((int)var1.Frame >= this.CurrentAnim.Frames.size() && this.Loop && var1.Looped) {
               var1.Frame = 0.0F;
            }

            if ((int)var2 != (int)var1.Frame) {
               var1.NextFrame = true;
            }

            if ((int)var1.Frame >= this.CurrentAnim.Frames.size() && (!this.Loop || !var1.Looped)) {
               var1.Finished = true;
               var1.Frame = this.CurrentAnim.FinishUnloopedOnFrame;
               if (this.DeleteWhenFinished) {
                  this.Dispose();
                  this.Animate = false;
               }
            }
         }
      }
   }

    void CacheAnims(const std::string& var1) {
      this.name = var1;
    std::stack var2 = new std::stack();

      for (int var3 = 0; var3 < this.AnimStack.size(); var3++) {
    IsoAnim var4 = this.AnimStack.get(var3);
    std::string var5 = var1 + var4.name;
         var2.push_back(var5);
         if (!IsoAnim.GlobalAnimMap.containsKey(var5)) {
            IsoAnim.GlobalAnimMap.put(var5, var4);
         }
      }

      AnimNameSet.put(var1, var2.toArray());
   }

    void LoadCache(const std::string& var1) {
      Object[] var2 = AnimNameSet.get(var1);
      this.name = var1;

      for (int var3 = 0; var3 < var2.length; var3++) {
    std::string var4 = (std::string)var2[var3];
    IsoAnim var5 = (IsoAnim)IsoAnim.GlobalAnimMap.get(var4);
         this.AnimMap.put(var5.name, var5);
         this.AnimStack.push_back(var5);
         this.CurrentAnim = var5;
      }
   }

    IsoSprite setFromCache(const std::string& var1, const std::string& var2, int var3) {
    std::string var4 = var1 + var2;
      if (HasCache(var4)) {
         this.LoadCache(var4);
      } else {
         this.LoadFramesNoDirPage(var1, var2, var3);
         this.CacheAnims(var4);
      }

    return this;
   }

    IsoObjectType getType() {
      return this.type;
   }

    void setType(IsoObjectType var1) {
      this.type = var1;
   }

    void AddProperties(IsoSprite var1) {
      this.getProperties().AddProperties(var1.getProperties());
   }

    int getID() {
      return this.ID;
   }

    std::string getName() {
      return this.name;
   }

    void setName(const std::string& var1) {
      this.name = var1;
   }

    ColorInfo getTintMod() {
      return this.TintMod;
   }

    void setTintMod(ColorInfo var1) {
      this.TintMod.set(var1);
   }

    void setAnimate(bool var1) {
      this.Animate = var1;
   }

    IsoSpriteGrid getSpriteGrid() {
      return this.spriteGrid;
   }

    void setSpriteGrid(IsoSpriteGrid var1) {
      this.spriteGrid = var1;
   }

    bool isMoveWithWind() {
      return this.moveWithWind;
   }

    int getSheetGridIdFromName() {
      return this.name != nullptr ? getSheetGridIdFromName(this.name) : -1;
   }

    static int getSheetGridIdFromName(const std::string& var0) {
      if (var0 != nullptr) {
    int var1 = var0.lastIndexOf(95);
         if (var1 > 0 && var1 + 1 < var0.length()) {
            return int.parseInt(var0.substr(var1 + 1));
         }
      }

      return -1;
   }
}
} // namespace sprite
} // namespace iso
} // namespace zombie
