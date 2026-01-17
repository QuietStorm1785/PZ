#pragma once
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
#include "zombie/core/textures/TextureDraw.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/gameStates/GameLoadingState.h"
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
#include "zombie/iso/IsoMetaGrid.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/IsoUtils.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/SliceY.h"
#include "zombie/iso/sprite/IsoSprite.h"
#include "zombie/iso/sprite/IsoSpriteManager.h"
#include "zombie/network/GameServer.h"
#include "zombie/scripting/ScriptManager.h"
#include "zombie/scripting/objects/MannequinScript.h"
#include "zombie/scripting/objects/ModelScript.h"
#include "zombie/util/StringUtils.h"
#include "zombie/util/list/PZArrayUtil.h"
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace iso {
namespace objects {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class IsoMannequin : public IsoObject {
public:
  static const ColorInfo inf = new ColorInfo();
  bool bInit = false;
  bool bFemale = false;
  bool bZombie = false;
  bool bSkeleton = false;
  std::string mannequinScriptName = null;
  std::string modelScriptName = null;
  std::string textureName = null;
  std::string animSet = null;
  std::string animState = null;
  std::string pose = null;
  std::string outfit = null;
  const HumanVisual humanVisual = new HumanVisual(this);
  const ItemVisuals itemVisuals = new ItemVisuals();
  const WornItems wornItems;
  MannequinScript mannequinScript = null;
  ModelScript modelScript = null;
private
  final IsoMannequin.PerPlayer[] perPlayer = new IsoMannequin.PerPlayer[4];
  bool bAnimate = false;
  AnimatedModel animatedModel = null;
private
  IsoMannequin.Drawer[] drawers = nullptr;
  float screenX;
  float screenY;
private
  static final IsoMannequin.StaticPerPlayer[] staticPerPlayer =
      new IsoMannequin.StaticPerPlayer[4];

public
  IsoMannequin(IsoCell cell) {
    super(cell);
    this.wornItems = new WornItems(BodyLocations.getGroup("Human"));

    for (int int0 = 0; int0 < 4; int0++) {
      this.perPlayer[int0] = new IsoMannequin.PerPlayer();
    }
  }

public
  IsoMannequin(IsoCell cell, IsoGridSquare square, IsoSprite sprite) {
    super(cell, square, sprite);
    this.wornItems = new WornItems(BodyLocations.getGroup("Human"));

    for (int int0 = 0; int0 < 4; int0++) {
      this.perPlayer[int0] = new IsoMannequin.PerPlayer();
    }
  }

  std::string getObjectName() { return "Mannequin"; }

  HumanVisual getHumanVisual() { return this.humanVisual; }

  void getItemVisuals(ItemVisuals _itemVisuals) {
    this.wornItems.getItemVisuals(_itemVisuals);
  }

  bool isFemale() { return this.bFemale; }

  bool isZombie() { return this.bZombie; }

  bool isSkeleton() { return this.bSkeleton; }

  bool isItemAllowedInContainer(ItemContainer container, InventoryItem item) {
    return item instanceof
        Clothing && !StringUtils.isNullOrWhitespace(
                        ((Clothing)item).getBodyLocation())
            ? true
            : item instanceof
        InventoryContainer && !StringUtils.isNullOrWhitespace(
                                  ((InventoryContainer)item).canBeEquipped());
  }

  std::string getMannequinScriptName() { return this.mannequinScriptName; }

  void setMannequinScriptName(const std::string &name) {
    if (!StringUtils.isNullOrWhitespace(name)) {
      if (ScriptManager.instance.getMannequinScript(name) != nullptr) {
        this.mannequinScriptName = name;
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
          Outfit outfitx =
              OutfitManager.instance.GetRandomNonProfessionalOutfit(
                  this.bFemale);
          this.humanVisual.dressInNamedOutfit(outfitx.m_Name, this.itemVisuals);
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

  std::string getPose() { return this.pose; }

  void setRenderDirection(IsoDirections newDir) {
    int int0 = IsoCamera.frameState.playerIndex;
    if (newDir != this.perPlayer[int0].renderDirection) {
      this.perPlayer[int0].renderDirection = newDir;
    }
  }

  void rotate(IsoDirections newDir) {
    if (newDir != nullptr && newDir != IsoDirections.Max) {
      this.dir = newDir;

      for (int int0 = 0; int0 < 4; int0++) {
        this.perPlayer[int0].atlasTex = nullptr;
      }

      if (GameServer.bServer) {
        this.sendObjectChange("rotate");
      }
    }
  }

  void saveChange(const std::string &change, KahluaTable tbl, ByteBuffer bb) {
    if ("rotate" == change)) {
            bb.put((byte)this.dir.index());
        }
    else {
      super.saveChange(change, tbl, bb);
    }
  }

  void loadChange(const std::string &change, ByteBuffer bb) {
    if ("rotate" == change)) {
        uint8_t byte0 = bb.get();
        this.rotate(IsoDirections.fromIndex(byte0));
      }
    else {
      super.loadChange(change, bb);
    }
  }

  void getVariables(String > vars) {
    vars.put("Female", this.bFemale ? "true" : "false");
    vars.put("Pose", this.getPose());
  }

  void load(ByteBuffer input, int WorldVersion, bool IS_DEBUG_SAVE) {
    super.load(input, WorldVersion, IS_DEBUG_SAVE);
    this.dir = IsoDirections.fromIndex(input.get());
    this.bInit = input.get() == 1;
    this.bFemale = input.get() == 1;
    this.bZombie = input.get() == 1;
    this.bSkeleton = input.get() == 1;
    if (WorldVersion >= 191) {
      this.mannequinScriptName = GameWindow.ReadString(input);
    }

    this.pose = GameWindow.ReadString(input);
    this.humanVisual.load(input, WorldVersion);
    this.textureName = this.humanVisual.getSkinTexture();
    this.wornItems.clear();
    if (this.container == nullptr) {
      this.container = new ItemContainer("mannequin", this.getSquare(), this);
      this.container.setExplored(true);
    }

    this.container.clear();
    if (input.get() == 1) {
      try {
        this.container.ID = input.getInt();
        std::vector arrayList = this.container.load(input, WorldVersion);
        uint8_t byte0 = input.get();

        for (int int0 = 0; int0 < byte0; int0++) {
          std::string string = GameWindow.ReadString(input);
          short short0 = input.getShort();
          if (short0 >= 0 && short0 < arrayList.size() &&
              this.wornItems.getBodyLocationGroup().getLocation(string) !=
                  nullptr) {
            this.wornItems.setItem(string,
                                   (InventoryItem)arrayList.get(short0));
          }
        }
      } catch (Exception exception) {
        if (this.container != nullptr) {
          DebugLog.log("Failed to stream in container ID: " +
                       this.container.ID);
        }
      }
    }
  }

  void save(ByteBuffer output, bool IS_DEBUG_SAVE) {
    ItemContainer container = this.container;
    this.container = nullptr;
    super.save(output, IS_DEBUG_SAVE);
    this.container = container;
    output.put((byte)this.dir.index());
    output.put((byte)(this.bInit ? 1 : 0));
    output.put((byte)(this.bFemale ? 1 : 0));
    output.put((byte)(this.bZombie ? 1 : 0));
    output.put((byte)(this.bSkeleton ? 1 : 0));
    GameWindow.WriteString(output, this.mannequinScriptName);
    GameWindow.WriteString(output, this.pose);
    this.humanVisual.save(output);
    if (container != nullptr) {
      output.put((byte)1);
      output.putInt(container.ID);
      std::vector arrayList = container.save(output);
      if (this.wornItems.size() > 127) {
        throw new RuntimeException("too many worn items");
      }

      output.put((byte)this.wornItems.size());
      this.wornItems.forEach(wornItem->{
        GameWindow.WriteString(output, wornItem.getLocation());
        output.putShort((short)arrayList.indexOf(wornItem.getItem()));
      });
    } else {
      output.put((byte)0);
    }
  }

  void saveState(ByteBuffer output) {
    if (!this.bInit) {
      this.initOutfit();
    }

    this.save(output);
  }

  void loadState(ByteBuffer input) {
    input.get();
    input.get();
    this.load(input, 195);
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
      this.mannequinScript =
          ScriptManager.instance.getMannequinScript(this.mannequinScriptName);
    }

    if (this.mannequinScript == nullptr) {
      this.modelScriptName = this.bFemale ? "FemaleBody" : "MaleBody";
      this.textureName =
          this.bFemale ? "F_Mannequin_White" : "M_Mannequin_White";
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
      this.modelScript =
          ScriptManager.instance.getModelScript(this.modelScriptName);
    }
  }

  void validateSkinTexture() {}

  void validatePose() {
    AnimationSet animationSet =
        AnimationSet.GetAnimationSet(this.animSet, false);
    if (animationSet == nullptr) {
      DebugLog.General.warn("ERROR: mannequin AnimSet \"%s\" doesn't exist",
                            this.animSet);
      this.pose = "Invalid";
    } else {
      AnimState animStatex = animationSet.GetState(this.animState);
      if (animStatex == nullptr) {
        DebugLog.General.warn(
            "ERROR: mannequin AnimSet \"%s\" state \"%s\" doesn't exist",
            this.animSet, this.animState);
        this.pose = "Invalid";
      } else {
        for (AnimNode animNode0 : animStatex.m_Nodes) {
          if (animNode0.m_Name.equalsIgnoreCase(this.pose)) {
            return;
          }
        }

        if (animStatex.m_Nodes == nullptr) {
          DebugLog.General.warn("ERROR: mannequin AnimSet \"%s\" state \"%s\" "
                                "node \"%s\" doesn't exist",
                                this.animSet, this.animState, this.pose);
          this.pose = "Invalid";
        } else {
          AnimNode animNode1 = PZArrayUtil.pickRandom(animStatex.m_Nodes);
          this.pose = animNode1.m_Name;
        }
      }
    }
  }

  void render(float x, float y, float z, ColorInfo col, bool bDoChild,
              bool bWallLightingPass, Shader shader) {
    int int0 = IsoCamera.frameState.playerIndex;
    x += 0.5F;
    y += 0.5F;
    this.calcScreenPos(x, y, z);
    this.renderShadow(x, y, z);
    if (this.bAnimate) {
      this.animatedModel.update();
      IsoMannequin.Drawer drawer =
          this.drawers[SpriteRenderer.instance.getMainStateIndex()];
      drawer.init(x, y, z);
      SpriteRenderer.instance.drawGeneric(drawer);
    } else {
      IsoDirections directions = this.dir;
      IsoMannequin.PerPlayer perPlayerx = this.perPlayer[int0];
      if (perPlayerx.renderDirection != nullptr &&
          perPlayerx.renderDirection != IsoDirections.Max) {
        this.dir = perPlayerx.renderDirection;
        perPlayerx.renderDirection = nullptr;
        perPlayerx.bWasRenderDirection = true;
        perPlayerx.atlasTex = nullptr;
      } else if (perPlayerx.bWasRenderDirection) {
        perPlayerx.bWasRenderDirection = false;
        perPlayerx.atlasTex = nullptr;
      }

      if (perPlayerx.atlasTex == nullptr) {
        perPlayerx.atlasTex = DeadBodyAtlas.instance.getBodyTexture(this);
        DeadBodyAtlas.instance.render();
      }

      this.dir = directions;
      if (perPlayerx.atlasTex != nullptr) {
        if (this.isHighlighted()) {
          inf.r = this.getHighlightColor().r;
          inf.g = this.getHighlightColor().g;
          inf.b = this.getHighlightColor().b;
          inf.a = this.getHighlightColor().a;
        } else {
          inf.r = col.r;
          inf.g = col.g;
          inf.b = col.b;
          inf.a = col.a;
        }

        col = inf;
        if (!this.isHighlighted() &&
            PerformanceSettings.LightingFrameSkip < 3) {
          this.square.interpolateLight(col, x - this.square.getX(),
                                       y - this.square.getY());
        }

        perPlayerx.atlasTex.render((int)this.screenX, (int)this.screenY, col.r,
                                   col.g, col.b, this.getAlpha(int0));
        if (Core.bDebug) {
        }
      }
    }
  }

  void renderFxMask(float x, float y, float z, bool bDoAttached) {}

  void calcScreenPos(float float0, float float1, float float2) {
    if (IsoSprite.globalOffsetX == -1.0F) {
      IsoSprite.globalOffsetX = -IsoCamera.frameState.OffX;
      IsoSprite.globalOffsetY = -IsoCamera.frameState.OffY;
    }

    this.screenX = IsoUtils.XToScreen(float0, float1, float2, 0);
    this.screenY = IsoUtils.YToScreen(float0, float1, float2, 0);
    this.sx = this.screenX;
    this.sy = this.screenY;
    this.screenX = this.sx + IsoSprite.globalOffsetX;
    this.screenY = this.sy + IsoSprite.globalOffsetY;
    IsoObject[] objects = this.square.getObjects().getElements();

    for (int int0 = 0; int0 < this.square.getObjects().size(); int0++) {
      IsoObject object = objects[int0];
      if (object.isTableSurface()) {
        this.screenY =
            this.screenY - (object.getSurfaceOffset() + 1.0F) * Core.TileScale;
      }
    }
  }

  void renderShadow(float var1, float var2, float var3) {
    Texture texture = Texture.getSharedTexture("dropshadow");
    int int0 = IsoCamera.frameState.playerIndex;
    float float0 = 0.8F * this.getAlpha(int0);
    ColorInfo colorInfo = this.square.lighting[int0].lightInfo();
    float0 *= (colorInfo.r + colorInfo.g + colorInfo.b) / 3.0F;
    float0 *= 0.8F;
    float float1 = this.screenX - texture.getWidth() / 2.0F * Core.TileScale;
    float float2 = this.screenY - texture.getHeight() / 2.0F * Core.TileScale;
    SpriteRenderer.instance.render(texture, float1, float2,
                                   (float)texture.getWidth() * Core.TileScale,
                                   (float)texture.getHeight() * Core.TileScale,
                                   1.0F, 1.0F, 1.0F, float0, nullptr);
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
        Outfit outfitx =
            OutfitManager.instance.GetRandomNonProfessionalOutfit(this.bFemale);
        this.humanVisual.dressInNamedOutfit(outfitx.m_Name, this.itemVisuals);
      } else if (!"none".equalsIgnoreCase(this.outfit)) {
        this.humanVisual.dressInNamedOutfit(this.outfit, this.itemVisuals);
      }

      this.humanVisual.setHairModel("");
      this.humanVisual.setBeardModel("");
      this.createInventory(this.itemVisuals);
    }
  }

  void getPropertiesFromSprite() {
    std::string string = this.sprite.name;
    switch (string) {
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
      IsoMetaCell metaCell = IsoWorld.instance.getMetaGrid().getCellData(
          this.square.x / 300, this.square.y / 300);
      if (metaCell != nullptr && metaCell.mannequinZones != nullptr) {
        std::vector arrayList = metaCell.mannequinZones;
        IsoMannequin.MannequinZone mannequinZone = nullptr;

        for (int int0 = 0; int0 < arrayList.size(); int0++) {
          mannequinZone = (IsoMannequin.MannequinZone)arrayList.get(int0);
          if (mannequinZone.contains(this.square.x, this.square.y,
                                     this.square.z)) {
            break;
          }

          mannequinZone = nullptr;
        }

        if (mannequinZone != nullptr) {
          if (mannequinZone.bFemale != -1) {
            this.bFemale = mannequinZone.bFemale == 1;
          }

          if (mannequinZone.dir != IsoDirections.Max) {
            this.dir = mannequinZone.dir;
          }

          if (mannequinZone.mannequinScript != nullptr) {
            this.mannequinScriptName = mannequinZone.mannequinScript;
          }

          if (mannequinZone.skin != nullptr) {
            this.textureName = mannequinZone.skin;
          }

          if (mannequinZone.pose != nullptr) {
            this.pose = mannequinZone.pose;
          }

          if (mannequinZone.outfit != nullptr) {
            this.outfit = mannequinZone.outfit;
          }
        }
      }
    }
  }

  void syncModel() {
    this.humanVisual.setForceModelScript(this.modelScriptName);
    std::string string = this.modelScriptName;
    switch (string) {
    case "FemaleBody":
      this.humanVisual.setForceModel(ModelManager.instance.m_femaleModel);
      break;
    case "MaleBody":
      this.humanVisual.setForceModel(ModelManager.instance.m_maleModel);
      break;
    default:
      this.humanVisual.setForceModel(
          ModelManager.instance.getLoadedModel(this.modelScriptName));
    }

    this.humanVisual.setSkinTextureName(this.textureName);
    this.wornItems.getItemVisuals(this.itemVisuals);

    for (int int0 = 0; int0 < 4; int0++) {
      this.perPlayer[int0].atlasTex = nullptr;
    }

    if (this.bAnimate) {
      if (this.animatedModel == nullptr) {
        this.animatedModel = std::make_unique<AnimatedModel>();
        this.drawers = new IsoMannequin.Drawer[3];

        for (int int1 = 0; int1 < this.drawers.length; int1++) {
          this.drawers[int1] = new IsoMannequin.Drawer();
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

  void createInventory(ItemVisuals itemVisualsx) {
    if (this.container == nullptr) {
      this.container = new ItemContainer("mannequin", this.getSquare(), this);
      this.container.setExplored(true);
    }

    this.container.clear();
    this.wornItems.setFromItemVisuals(itemVisualsx);
    this.wornItems.addItemsToItemContainer(this.container);
  }

  void wearItem(InventoryItem item, IsoGameCharacter chr) {
    if (this.container.contains(item)) {
      ItemVisual itemVisual = item.getVisual();
      if (itemVisual != nullptr) {
        if (item instanceof
            Clothing && !StringUtils.isNullOrWhitespace(
                            ((Clothing)item).getBodyLocation())) {
          this.wornItems.setItem(((Clothing)item).getBodyLocation(), item);
        } else {
          if (!(item instanceof InventoryContainer) ||
              StringUtils.isNullOrWhitespace(
                  ((InventoryContainer)item).canBeEquipped())) {
            return;
          }

          this.wornItems.setItem(((InventoryContainer)item).canBeEquipped(),
                                 item);
        }

        if (chr != nullptr) {
          std::vector arrayList = this.container.getItems();

          for (int int0 = 0; int0 < arrayList.size(); int0++) {
            InventoryItem _item = (InventoryItem)arrayList.get(int0);
            if (!this.wornItems.contains(_item)) {
              this.container.removeItemOnServer(_item);
              this.container.Remove(_item);
              chr.getInventory().AddItem(_item);
              int0--;
            }
          }
        }

        this.syncModel();
      }
    }
  }

  void checkClothing(InventoryItem removedItem) {
    for (int int0 = 0; int0 < this.wornItems.size(); int0++) {
      InventoryItem item = this.wornItems.getItemByIndex(int0);
      if (this.container == nullptr ||
          this.container.getItems().indexOf(item) == -1) {
        this.wornItems.remove(item);
        this.syncModel();
        int0--;
      }
    }
  }

  std::string getAnimSetName() { return this.animSet; }

  std::string getAnimStateName() { return this.animState; }

  void getCustomSettingsFromItem(InventoryItem item) {
    if (item instanceof Moveable) {
      ByteBuffer byteBuffer = item.getByteData();
      if (byteBuffer == nullptr) {
        return;
      }

      byteBuffer.rewind();
      int int0 = byteBuffer.getInt();
      byteBuffer.get();
      byteBuffer.get();
      this.load(byteBuffer, int0);
    }
  }

  void setCustomSettingsToItem(InventoryItem item) {
    if (item instanceof Moveable) {
      synchronized(SliceY.SliceBufferLock) {
        ByteBuffer byteBuffer = SliceY.SliceBuffer;
        byteBuffer.clear();
        byteBuffer.putInt(195);
        this.save(byteBuffer);
        byteBuffer.flip();
        item.byteData = ByteBuffer.allocate(byteBuffer.limit());
        item.byteData.put(byteBuffer);
      }

      if (this.container != nullptr) {
        item.setActualWeight(item.getActualWeight() +
                             this.container.getContentsWeight());
      }
    }
  }

  static bool isMannequinSprite(IsoSprite sprite) {
        return "Mannequin" == sprite.getProperties().Val("CustomName"));
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

  static void renderMoveableItem(Moveable item, int x, int y, int z,
                                 IsoDirections dir) {
    int int0 = IsoCamera.frameState.playerIndex;
    IsoMannequin.StaticPerPlayer staticPerPlayerx = staticPerPlayer[int0];
    if (staticPerPlayerx == nullptr) {
      staticPerPlayerx = staticPerPlayer[int0] =
          new IsoMannequin.StaticPerPlayer(int0);
    }

    staticPerPlayerx.renderMoveableItem(item, x, y, z, dir);
  }

  static void renderMoveableObject(IsoMannequin mannequin, int x, int y, int z,
                                   IsoDirections dir) {
    mannequin.setRenderDirection(dir);
  }

  static IsoDirections getDirectionFromItem(Moveable item, int playerIndex) {
    IsoMannequin.StaticPerPlayer staticPerPlayerx =
        staticPerPlayer[playerIndex];
    if (staticPerPlayerx == nullptr) {
      staticPerPlayerx = staticPerPlayer[playerIndex] =
          new IsoMannequin.StaticPerPlayer(playerIndex);
    }

    return staticPerPlayerx.getDirectionFromItem(item);
  }

private
  final class Drawer extends TextureDraw.GenericDrawer {
    float x;
    float y;
    float z;
    float m_animPlayerAngle;
    bool bRendered;

    void init(float arg0, float arg1, float arg2) {
      this.x = arg0;
      this.y = arg1;
      this.z = arg2;
      this.bRendered = false;
      IsoMannequin.this.animatedModel.renderMain();
      this.m_animPlayerAngle =
          IsoMannequin.this.animatedModel.getAnimationPlayer()
              .getRenderedAngle();
    }

    void render() {
      IsoMannequin.this.animatedModel.DoRenderToWorld(this.x, this.y, this.z,
                                                      this.m_animPlayerAngle);
      this.bRendered = true;
    }

    void postRender() {
      IsoMannequin.this.animatedModel.postRender(this.bRendered);
    }
  }

public
  static final class MannequinZone extends IsoMetaGrid.Zone {
    int bFemale = -1;
    IsoDirections dir = IsoDirections.Max;
    std::string mannequinScript = null;
    std::string pose = null;
    std::string skin = null;
    std::string outfit = null;

  public
    MannequinZone(const std::string &string0, const std::string &string1,
                  int int0, int int1, int int2, int int3, int int4,
                  KahluaTable table) {
      super(string0, string1, int0, int1, int2, int3, int4);
      if (table != nullptr) {
        void *object = table.rawget("Female");
        if (object instanceof Boolean) {
          this.bFemale = object == Boolean.TRUE ? 1 : 0;
        }

        object = table.rawget("Direction");
        if (object instanceof String) {
          this.dir = IsoDirections.valueOf((String)object);
        }

        object = table.rawget("Outfit");
        if (object instanceof String) {
          this.outfit = (String)object;
        }

        object = table.rawget("Script");
        if (object instanceof String) {
          this.mannequinScript = (String)object;
        }

        object = table.rawget("Skin");
        if (object instanceof String) {
          this.skin = (String)object;
        }

        object = table.rawget("Pose");
        if (object instanceof String) {
          this.pose = (String)object;
        }
      }
    }
  }

private
  static final class PerPlayer {
  private
    DeadBodyAtlas.BodyTexture atlasTex = nullptr;
    IsoDirections renderDirection = null;
    bool bWasRenderDirection = false;
  }

  private static final class StaticPerPlayer {
    const int playerIndex;
    Moveable _moveable = null;
    Moveable _failedItem = null;
    IsoMannequin _mannequin = null;

    StaticPerPlayer(int int0) { this.playerIndex = int0; }

    void renderMoveableItem(Moveable moveable, int int0, int int1, int int2,
                            IsoDirections directions) {
      if (this.checkItem(moveable)) {
        if (this._moveable != moveable) {
          this._moveable = moveable;

          try {
            this._mannequin.getCustomSettingsFromItem(this._moveable);
          } catch (IOException iOException) {
          }

          this._mannequin.initOutfit();
          this._mannequin.validateSkinTexture();
          this._mannequin.validatePose();
          this._mannequin.syncModel();
          this._mannequin.perPlayer[this.playerIndex].atlasTex = nullptr;
        }

        this._mannequin.square =
            IsoWorld.instance.CurrentCell.getGridSquare(int0, int1, int2);
        if (this._mannequin.square != nullptr) {
          this._mannequin.perPlayer[this.playerIndex].renderDirection =
              directions;
          IsoMannequin.inf.set(1.0F, 1.0F, 1.0F, 1.0F);
          this._mannequin.render(int0, int1, int2, IsoMannequin.inf, false,
                                 false, nullptr);
        }
      }
    }

    IsoDirections getDirectionFromItem(Moveable moveable) {
      if (!this.checkItem(moveable)) {
        return IsoDirections.S;
      } else {
        this._moveable = nullptr;

        try {
          this._mannequin.getCustomSettingsFromItem(moveable);
          return this._mannequin.getDir();
        } catch (Exception exception) {
          return IsoDirections.S;
        }
      }
    }

    bool checkItem(Moveable moveable) {
      if (moveable == nullptr) {
        return false;
      } else {
        std::string string = moveable.getWorldSprite();
        IsoSprite sprite = IsoSpriteManager.instance.getSprite(string);
        if (sprite == nullptr || !IsoMannequin.isMannequinSprite(sprite)) {
          return false;
        } else if (moveable.getByteData() == nullptr) {
          Thread thread = Thread.currentThread();
          if (thread != GameWindow.GameThread &&
              thread != GameLoadingState.loader &&
              thread == GameServer.MainThread) {
            return false;
          } else {
            if (this._mannequin == nullptr ||
                this._mannequin.getCell() != IsoWorld.instance.CurrentCell) {
              this._mannequin = new IsoMannequin(IsoWorld.instance.CurrentCell);
            }

            if (this._failedItem == moveable) {
              return false;
            } else {
              try {
                this._mannequin.resetMannequin();
                this._mannequin.sprite = sprite;
                this._mannequin.initOutfit();
                this._mannequin.validateSkinTexture();
                this._mannequin.validatePose();
                this._mannequin.syncModel();
                this._mannequin.setCustomSettingsToItem(moveable);
                return true;
              } catch (IOException iOException) {
                this._failedItem = moveable;
                return false;
              }
            }
          }
        } else {
          if (this._mannequin == nullptr ||
              this._mannequin.getCell() != IsoWorld.instance.CurrentCell) {
            this._mannequin = new IsoMannequin(IsoWorld.instance.CurrentCell);
          }

          return true;
        }
      }
    }
  }
}
} // namespace objects
} // namespace iso
} // namespace zombie
