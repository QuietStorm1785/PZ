#pragma once
#include "fmod/fmod/FMODManager.h"
#include "org/lwjgl/opengl/ARBShaderObjects.h"
#include "zombie/GameTime.h"
#include "zombie/IndieGL.h"
#include "zombie/Lua/LuaEventManager.h"
#include "zombie/WorldSoundManager.h"
#include "zombie/audio/BaseSoundEmitter.h"
#include "zombie/audio/parameters/ParameterMeleeHitSurface.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/Core.h"
#include "zombie/core/Rand.h"
#include "zombie/core/SpriteRenderer.h"
#include "zombie/core/opengl/RenderThread.h"
#include "zombie/core/opengl/Shader.h"
#include "zombie/core/opengl/ShaderProgram.h"
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
#include "zombie/iso/sprite/IsoSprite.h"
#include "zombie/iso/sprite/IsoSpriteInstance.h"
#include "zombie/util/list/PZArrayUtil.h"
#include "zombie/vehicles/BaseVehicle.h"
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

class IsoTree : public IsoObject {
public:
  static const int MAX_SIZE = 6;
  int LogYield = 1;
  int damage = 500;
  int size = 4;
  bool bRenderFlag;
  float fadeAlpha;
private
  static final IsoGameCharacter.Location[] s_chopTreeLocation =
      new IsoGameCharacter.Location[4];
private
  static final ArrayList<IsoGridSquare> s_chopTreeIndicators =
      std::make_unique<ArrayList<>>();
  static IsoTree s_chopTreeHighlighted = null;

  static IsoTree getNew() {
    synchronized(CellLoader.isoTreeCache) {
      if (CellLoader.isoTreeCache.isEmpty()) {
        return std::make_unique<IsoTree>();
      } else {
        IsoTree tree = CellLoader.isoTreeCache.pop();
        tree.sx = 0.0F;
        return tree;
      }
    }
  }

public
  IsoTree() {}

public
  IsoTree(IsoCell cell) { super(cell); }

  void save(ByteBuffer output, bool IS_DEBUG_SAVE) {
    super.save(output, IS_DEBUG_SAVE);
    output.put((byte)this.LogYield);
    output.put((byte)(this.damage / 10));
  }

  void load(ByteBuffer input, int WorldVersion, bool IS_DEBUG_SAVE) {
    super.load(input, WorldVersion, IS_DEBUG_SAVE);
    this.LogYield = input.get();
    this.damage = input.get() * 10;
    if (this.sprite != nullptr &&
        this.sprite.getProperties().Val("tree") != nullptr) {
      this.size = Integer.parseInt(this.sprite.getProperties().Val("tree"));
      if (this.size < 1) {
        this.size = 1;
      }

      if (this.size > 6) {
        this.size = 6;
      }
    }
  }

  void checkMoveWithWind() { this.checkMoveWithWind(true); }

  void reset() { super.reset(); }

public
  IsoTree(IsoGridSquare sq, const std::string &gid) {
    super(sq, gid, false);
    this.initTree();
  }

public
  IsoTree(IsoGridSquare sq, IsoSprite gid) {
    super(sq.getCell(), sq, gid);
    this.initTree();
  }

  void initTree() {
    this.setType(IsoObjectType.tree);
    if (this.sprite.getProperties().Val("tree") != nullptr) {
      this.size = Integer.parseInt(this.sprite.getProperties().Val("tree"));
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

  std::string getObjectName() { return "Tree"; }

  void Damage(float amount) {
    float float0 = amount * 0.05F;
    this.damage = (int)(this.damage - float0);
    if (this.damage <= 0) {
      this.square.transmitRemoveItemFromSquare(this);
      this.square.RecalcAllWithNeighbours(true);
      int int0 = this.LogYield;

      for (int int1 = 0; int1 < int0; int1++) {
        this.square.AddWorldInventoryItem("Base.Log", 0.0F, 0.0F, 0.0F);
        if (Rand.Next(4) == 0) {
          this.square.AddWorldInventoryItem("Base.TreeBranch", 0.0F, 0.0F,
                                            0.0F);
        }

        if (Rand.Next(4) == 0) {
          this.square.AddWorldInventoryItem("Base.Twigs", 0.0F, 0.0F, 0.0F);
        }
      }

      this.reset();
      CellLoader.isoTreeCache.add(this);

      for (int int2 = 0; int2 < IsoPlayer.numPlayers; int2++) {
        LosUtil.cachecleared[int2] = true;
      }

      IsoGridSquare.setRecalcLightTime(-1);
      GameTime.instance.lightSourceUpdate = 100.0F;
      LuaEventManager.triggerEvent("OnContainerUpdate");
    }
  }

  void HitByVehicle(BaseVehicle vehicle, float amount) {
    BaseSoundEmitter baseSoundEmitter = IsoWorld.instance.getFreeEmitter(
        this.square.x + 0.5F, this.square.y + 0.5F, this.square.z);
    long long0 = baseSoundEmitter.playSound("VehicleHitTree");
    baseSoundEmitter.setParameterValue(
        long0, FMODManager.instance.getParameterDescription("VehicleSpeed"),
        vehicle.getCurrentSpeedKmHour());
    WorldSoundManager.instance.addSound(nullptr, this.square.getX(),
                                        this.square.getY(), this.square.getZ(),
                                        20, 20, true, 4.0F, 15.0F);
    this.Damage(this.damage);
  }

  void WeaponHit(IsoGameCharacter owner, HandWeapon weapon) {
    int int0 = weapon.getConditionLowerChance() * 2 + owner.getMaintenanceMod();
    if (!weapon.getCategories().contains("Axe")) {
      int0 = weapon.getConditionLowerChance() / 2 + owner.getMaintenanceMod();
    }

    if (Rand.NextBool(int0)) {
      weapon.setCondition(weapon.getCondition() - 1);
    }

    if (owner instanceof IsoPlayer) {
      ((IsoPlayer)owner)
          .setMeleeHitSurface(ParameterMeleeHitSurface.Material.Tree);
      owner.getEmitter().playSound(weapon.getZombieHitSound());
    } else {
      owner.getEmitter().playSound("ChopTree");
    }

    WorldSoundManager.instance.addSound(nullptr, this.square.getX(),
                                        this.square.getY(), this.square.getZ(),
                                        20, 20, true, 4.0F, 15.0F);
    this.setRenderEffect(RenderEffectType.Hit_Tree_Shudder, true);
    float float0 = weapon.getTreeDamage();
    if (owner.Traits.Axeman.isSet() && weapon.getCategories().contains("Axe")) {
      float0 *= 1.5F;
    }

    this.damage = (int)(this.damage - float0);
    if (this.damage <= 0) {
      this.square.transmitRemoveItemFromSquare(this);
      owner.getEmitter().playSound("FallingTree");
      this.square.RecalcAllWithNeighbours(true);
      int int1 = this.LogYield;

      for (int int2 = 0; int2 < int1; int2++) {
        this.square.AddWorldInventoryItem("Base.Log", 0.0F, 0.0F, 0.0F);
        if (Rand.Next(4) == 0) {
          this.square.AddWorldInventoryItem("Base.TreeBranch", 0.0F, 0.0F,
                                            0.0F);
        }

        if (Rand.Next(4) == 0) {
          this.square.AddWorldInventoryItem("Base.Twigs", 0.0F, 0.0F, 0.0F);
        }
      }

      this.reset();
      CellLoader.isoTreeCache.add(this);

      for (int int3 = 0; int3 < IsoPlayer.numPlayers; int3++) {
        LosUtil.cachecleared[int3] = true;
      }

      IsoGridSquare.setRecalcLightTime(-1);
      GameTime.instance.lightSourceUpdate = 100.0F;
      LuaEventManager.triggerEvent("OnContainerUpdate");
    }

    LuaEventManager.triggerEvent("OnWeaponHitTree", owner, weapon);
  }

  void setHealth(int health) { this.damage = Math.max(health, 0); }

  int getHealth() { return this.damage; }

  int getMaxHealth() { return this.LogYield * 80; }

  int getSize() { return this.size; }

  float getSlowFactor(IsoMovingObject chr) {
    float float0 = 1.0F;
    if (chr instanceof IsoGameCharacter) {
      if ("parkranger" ==
          ((IsoGameCharacter)chr).getDescriptor().getProfession())) {
                float0 = 1.5F;
            }

      if ("lumberjack" ==
          ((IsoGameCharacter)chr).getDescriptor().getProfession())) {
                float0 = 1.2F;
            }
    }

    if (this.size == 1 || this.size == 2) {
      return 0.8F * float0;
    } else {
      return this.size != 3 && this.size != 4 ? 0.3F * float0 : 0.5F * float0;
    }
  }

  void render(float x, float y, float z, ColorInfo col, bool bDoAttached,
              bool bWallLightingPass, Shader shader) {
    if (this.isHighlighted()) {
      if (this.square != nullptr) {
        s_chopTreeHighlighted = this;
      }
    } else {
      int int0 = IsoCamera.frameState.playerIndex;
      if (!this.bRenderFlag && !(this.fadeAlpha < this.getTargetAlpha(int0))) {
        this.renderInner(x, y, z, col, bDoAttached, false);
      } else {
        IndieGL.enableStencilTest();
        IndieGL.glStencilFunc(517, 128, 128);
        this.renderInner(x, y, z, col, bDoAttached, false);
        float float0 =
            0.044999998F * (GameTime.getInstance().getMultiplier() / 1.6F);
        if (this.bRenderFlag && this.fadeAlpha > 0.25F) {
          this.fadeAlpha -= float0;
          if (this.fadeAlpha < 0.25F) {
            this.fadeAlpha = 0.25F;
          }
        }

        if (!this.bRenderFlag) {
          float float1 = this.getTargetAlpha(int0);
          if (this.fadeAlpha < float1) {
            this.fadeAlpha += float0;
            if (this.fadeAlpha > float1) {
              this.fadeAlpha = float1;
            }
          }
        }

        float float2 = this.getAlpha(int0);
        float float3 = this.getTargetAlpha(int0);
        this.setAlphaAndTarget(int0, this.fadeAlpha);
        IndieGL.glStencilFunc(514, 128, 128);
        this.renderInner(x, y, z, col, true, false);
        this.setAlpha(int0, float2);
        this.setTargetAlpha(int0, float3);
        if (IsoTree.TreeShader.instance.StartShader()) {
          IsoTree.TreeShader.instance.setOutlineColor(0.1F, 0.1F, 0.1F,
                                                      1.0F - this.fadeAlpha);
          this.renderInner(x, y, z, col, true, true);
          IndieGL.EndShader();
        }

        IndieGL.glStencilFunc(519, 255, 255);
      }

      this.checkChopTreeIndicator(x, y, z);
    }
  }

  void renderInner(float float4, float float5, float float6,
                   ColorInfo colorInfo, bool var5, bool boolean0) {
    if (this.sprite != nullptr && this.sprite.name != nullptr &&
        this.sprite.name.contains("JUMBO")) {
      float float0 = this.offsetX;
      float float1 = this.offsetY;
      this.offsetX = 384 * Core.TileScale / 2 - 96 * Core.TileScale;
      this.offsetY = 256 * Core.TileScale - 32 * Core.TileScale;
      if (this.offsetX != float0 || this.offsetY != float1) {
        this.sx = 0.0F;
      }
    } else {
      float float2 = this.offsetX;
      float float3 = this.offsetY;
      this.offsetX = 32 * Core.TileScale;
      this.offsetY = 96 * Core.TileScale;
      if (this.offsetX != float2 || this.offsetY != float3) {
        this.sx = 0.0F;
      }
    }

    if (boolean0 && this.sprite != nullptr) {
      Texture texture = this.sprite.getTextureForCurrentFrame(this.dir);
      if (texture != nullptr) {
        IsoTree.TreeShader.instance.setStepSize(0.25F, texture.getWidth(),
                                                texture.getHeight());
      }
    }

    super.render(float4, float5, float6, colorInfo, false, false, nullptr);
    if (this.AttachedAnimSprite != nullptr) {
      int int0 = this.AttachedAnimSprite.size();

      for (int int1 = 0; int1 < int0; int1++) {
        IsoSpriteInstance spriteInstance = this.AttachedAnimSprite.get(int1);
        int int2 = IsoCamera.frameState.playerIndex;
        float float7 = this.getTargetAlpha(int2);
        this.setTargetAlpha(int2, 1.0F);
        spriteInstance.render(
            this, float4, float5, float6, this.dir, this.offsetX, this.offsetY,
            this.isHighlighted() ? this.getHighlightColor() : colorInfo);
        this.setTargetAlpha(int2, float7);
        spriteInstance.update();
      }
    }
  }

  /**
   *
   * @param sprite the sprite to set
   */
  void setSprite(IsoSprite sprite) {
    super.setSprite(sprite);
    this.initTree();
  }

  bool isMaskClicked(int x, int y, bool flip) {
    if (super.isMaskClicked(x, y, flip)) {
      return true;
    } else if (this.AttachedAnimSprite == nullptr) {
      return false;
    } else {
      for (int int0 = 0; int0 < this.AttachedAnimSprite.size(); int0++) {
        if (this.AttachedAnimSprite.get(int0).parentSprite.isMaskClicked(
                this.dir, x, y, flip)) {
          return true;
        }
      }

      return false;
    }
  }

  static void setChopTreeCursorLocation(int playerIndex, int x, int y, int z) {
    if (s_chopTreeLocation[playerIndex] == nullptr) {
      s_chopTreeLocation[playerIndex] =
          new IsoGameCharacter.Location(-1, -1, -1);
    }

    IsoGameCharacter.Location location = s_chopTreeLocation[playerIndex];
    location.x = x;
    location.y = y;
    location.z = z;
  }

  void checkChopTreeIndicator(float var1, float var2, float var3) {
    if (!this.isHighlighted()) {
      int int0 = IsoCamera.frameState.playerIndex;
      IsoGameCharacter.Location location = s_chopTreeLocation[int0];
      if (location != nullptr && location.x != -1 && this.square != nullptr) {
        if (this.getCell().getDrag(int0) == nullptr) {
          location.x = -1;
        } else {
          if (IsoUtils.DistanceToSquared(
                  this.square.x + 0.5F, this.square.y + 0.5F, location.x + 0.5F,
                  location.y + 0.5F) < 12.25F) {
            s_chopTreeIndicators.add(this.square);
          }
        }
      }
    }
  }

  static void renderChopTreeIndicators() {
    if (!s_chopTreeIndicators.isEmpty()) {
      PZArrayUtil.forEach(s_chopTreeIndicators,
                          IsoTree::renderChopTreeIndicator);
      s_chopTreeIndicators.clear();
    }

    if (s_chopTreeHighlighted != nullptr) {
      IsoTree tree = s_chopTreeHighlighted;
      s_chopTreeHighlighted = nullptr;
      tree.renderInner(tree.square.x, tree.square.y, tree.square.z,
                       tree.getHighlightColor(), false, false);
    }
  }

  static void renderChopTreeIndicator(IsoGridSquare square) {
    Texture texture = Texture.getSharedTexture("media/ui/chop_tree.png");
    if (texture != nullptr && texture.isReady()) {
      float float0 = square.x;
      float float1 = square.y;
      float float2 = square.z;
      float float3 = IsoUtils.XToScreen(float0, float1, float2, 0) +
                     IsoSprite.globalOffsetX;
      float float4 = IsoUtils.YToScreen(float0, float1, float2, 0) +
                     IsoSprite.globalOffsetY;
      float3 -= 32 * Core.TileScale;
      float4 -= 96 * Core.TileScale;
      SpriteRenderer.instance.render(texture, float3, float4,
                                     64 * Core.TileScale, 128 * Core.TileScale,
                                     0.0F, 0.5F, 0.0F, 0.75F, nullptr);
    }
  }

public
  static class TreeShader {
  public
    static final IsoTree.TreeShader instance = new IsoTree.TreeShader();
    ShaderProgram shaderProgram;
    int stepSize;
    int outlineColor;

    void initShader() {
      this.shaderProgram =
          ShaderProgram.createShaderProgram("tree", false, true);
      if (this.shaderProgram.isCompiled()) {
        this.stepSize = ARBShaderObjects.glGetUniformLocationARB(
            this.shaderProgram.getShaderID(), "stepSize");
        this.outlineColor = ARBShaderObjects.glGetUniformLocationARB(
            this.shaderProgram.getShaderID(), "outlineColor");
        ARBShaderObjects.glUseProgramObjectARB(
            this.shaderProgram.getShaderID());
        ARBShaderObjects.glUniform2fARB(this.stepSize, 0.001F, 0.001F);
        ARBShaderObjects.glUseProgramObjectARB(0);
      }
    }

    void setOutlineColor(float float0, float float1, float float2,
                         float float3) {
      SpriteRenderer.instance.ShaderUpdate4f(this.shaderProgram.getShaderID(),
                                             this.outlineColor, float0, float1,
                                             float2, float3);
    }

    void setStepSize(float float0, int int1, int int0) {
      SpriteRenderer.instance.ShaderUpdate2f(this.shaderProgram.getShaderID(),
                                             this.stepSize, float0 / int1,
                                             float0 / int0);
    }

    bool StartShader() {
      if (this.shaderProgram == nullptr) {
        RenderThread.invokeOnRenderContext(this ::initShader);
      }

      if (this.shaderProgram.isCompiled()) {
        IndieGL.StartShader(this.shaderProgram.getShaderID(), 0);
        return true;
      } else {
        return false;
      }
    }
  }
}
} // namespace objects
} // namespace iso
} // namespace zombie
