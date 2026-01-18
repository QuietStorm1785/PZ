#pragma once
#include "java/security/MessageDigest.h"
#include "java/security/NoSuchAlgorithmException.h"
#include "org/joml/Matrix4f.h"
#include "org/joml/Vector3f.h"
#include "org/lwjgl/opengl/GL11.h"
#include "org/lwjgl/util/glu/GLU.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/Core.h"
#include "zombie/core/ImmutableColor.h"
#include "zombie/core/SpriteRenderer.h"
#include "zombie/core/logger/ExceptionLogger.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/core/opengl/PZGLUtil.h"
#include "zombie/core/opengl/RenderThread.h"
#include "zombie/core/skinnedmodel/ModelManager.h"
#include "zombie/core/skinnedmodel/population/ClothingItem.h"
#include "zombie/core/skinnedmodel/shader/Shader.h"
#include "zombie/core/skinnedmodel/visual/ItemVisual.h"
#include "zombie/core/textures/Texture.h"
#include "zombie/core/textures/TextureDraw.h"
#include "zombie/core/textures/TextureFBO.h"
#include "zombie/debug/DebugOptions.h"
#include "zombie/input/GameKeyboard.h"
#include "zombie/inventory/InventoryItem.h"
#include "zombie/inventory/types/Clothing.h"
#include "zombie/inventory/types/Food.h"
#include "zombie/inventory/types/HandWeapon.h"
#include "zombie/inventory/types/WeaponPart.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/popman/ObjectPool.h"
#include "zombie/scripting/ScriptManager.h"
#include "zombie/scripting/objects/ModelAttachment.h"
#include "zombie/scripting/objects/ModelScript.h"
#include "zombie/scripting/objects/ModelWeaponPart.h"
#include "zombie/util/StringUtils.h"
#include "zombie/util/Type.h"
#include <algorithm>
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace model {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class WorldItemAtlas {
public:
  static const int ATLAS_SIZE = 512;
  static const int MATRIX_SIZE = 1024;
  static const float MAX_ZOOM = 2.5F;
  TextureFBO fbo;
  static const WorldItemAtlas instance = new WorldItemAtlas();
private
  final HashMap<String, WorldItemAtlas.ItemTexture> itemTextureMap =
      std::make_unique<HashMap<>>();
private
  final ArrayList<WorldItemAtlas.Atlas> AtlasList =
      std::make_unique<ArrayList<>>();
private
  final WorldItemAtlas.ItemParams itemParams = new WorldItemAtlas.ItemParams();
private
  final WorldItemAtlas.Checksummer checksummer =
      new WorldItemAtlas.Checksummer();
private
  static final Stack<WorldItemAtlas.RenderJob> JobPool =
      std::make_unique<Stack<>>();
private
  final ArrayList<WorldItemAtlas.RenderJob> RenderJobs =
      std::make_unique<ArrayList<>>();
private
  final ObjectPool<WorldItemAtlas.ItemTextureDrawer> itemTextureDrawerPool =
      new ObjectPool<>(WorldItemAtlas.ItemTextureDrawer::new);
private
  final ObjectPool<WorldItemAtlas.WeaponPartParams> weaponPartParamPool =
      new ObjectPool<>(WorldItemAtlas.WeaponPartParams::new);
private
  final ArrayList<WeaponPart> m_tempWeaponPartList =
      std::make_unique<ArrayList<>>();
  static const Matrix4f s_attachmentXfrm = new Matrix4f();
  static const ImmutableColor ROTTEN_FOOD_COLOR =
      new ImmutableColor(0.5F, 0.5F, 0.5F);

public
  WorldItemAtlas.ItemTexture getItemTexture(InventoryItem item) {
    return this.itemParams.init(item) ? this.getItemTexture(this.itemParams)
                                      : nullptr;
  }

public
  WorldItemAtlas.ItemTexture getItemTexture(WorldItemAtlas.ItemParams params) {
    std::string string = this.getItemKey(params);
    WorldItemAtlas.ItemTexture itemTexture = this.itemTextureMap.get(string);
    if (itemTexture != nullptr) {
      return itemTexture;
    } else {
      WorldItemAtlas.AtlasEntry atlasEntry = new WorldItemAtlas.AtlasEntry();
      atlasEntry.key = string;
      itemTexture = new WorldItemAtlas.ItemTexture();
      itemTexture.itemParams.copyFrom(params);
      itemTexture.entry = atlasEntry;
      this.itemTextureMap.put(string, itemTexture);
      this.RenderJobs.add(
          WorldItemAtlas.RenderJob.getNew().init(params, atlasEntry));
      return itemTexture;
    }
  }

  void assignEntryToAtlas(WorldItemAtlas.AtlasEntry atlasEntry, int int2,
                          int int1) {
    if (atlasEntry.atlas == nullptr) {
      for (int int0 = 0; int0 < this.AtlasList.size(); int0++) {
        WorldItemAtlas.Atlas atlas0 = this.AtlasList.get(int0);
        if (!atlas0.isFull() && atlas0.ENTRY_WID == int2 &&
            atlas0.ENTRY_HGT == int1) {
          atlas0.addEntry(atlasEntry);
          return;
        }
      }

      WorldItemAtlas.Atlas atlas1 =
          new WorldItemAtlas.Atlas(512, 512, int2, int1);
      atlas1.addEntry(atlasEntry);
      this.AtlasList.add(atlas1);
    }
  }

  std::string getItemKey(WorldItemAtlas.ItemParams itemParamsx) {
    try {
      this.checksummer.reset();
      this.checksummer.update(itemParamsx.m_model.Name);
      if (itemParamsx.m_weaponParts != nullptr) {
        for (int int0 = 0; int0 < itemParamsx.m_weaponParts.size(); int0++) {
          WorldItemAtlas.WeaponPartParams weaponPartParams =
              itemParamsx.m_weaponParts.get(int0);
          this.checksummer.update(weaponPartParams.m_model.Name);
        }
      }

      this.checksummer.update((int)(itemParamsx.worldScale * 1000.0F));
      this.checksummer.update((byte)(itemParamsx.m_tintR * 255.0F));
      this.checksummer.update((byte)(itemParamsx.m_tintG * 255.0F));
      this.checksummer.update((byte)(itemParamsx.m_tintB * 255.0F));
      this.checksummer.update((int)(itemParamsx.m_angle.x * 1000.0F));
      this.checksummer.update((int)(itemParamsx.m_angle.y * 1000.0F));
      this.checksummer.update((int)(itemParamsx.m_angle.z * 1000.0F));
      this.checksummer.update((byte)itemParamsx.m_foodState.ordinal());
      return this.checksummer.checksumToString();
    } catch (Throwable throwable) {
      ExceptionLogger.logException(throwable);
      return "bogus";
    }
  }

  void render() {
    for (int int0 = 0; int0 < this.AtlasList.size(); int0++) {
      WorldItemAtlas.Atlas atlas = this.AtlasList.get(int0);
      if (atlas.clear) {
        SpriteRenderer.instance.drawGeneric(
            new WorldItemAtlas.ClearAtlasTexture(atlas));
      }
    }

    if (!this.RenderJobs.isEmpty()) {
      for (int int1 = 0; int1 < this.RenderJobs.size(); int1++) {
        WorldItemAtlas.RenderJob renderJob = this.RenderJobs.get(int1);
        if (renderJob.done != 1 || renderJob.renderRefCount <= 0) {
          if (renderJob.done == 1 && renderJob.renderRefCount == 0) {
            this.RenderJobs.remove(int1--);

            assert !JobPool.contains(renderJob);

            JobPool.push(renderJob);
          } else {
            renderJob.entry.bRenderMainOK = renderJob.renderMain();
            if (renderJob.entry.bRenderMainOK) {
              renderJob.renderRefCount++;
              SpriteRenderer.instance.drawGeneric(renderJob);
            }
          }
        }
      }
    }
  }

  void renderUI() {
    if (DebugOptions.instance.WorldItemAtlasRender.getValue() &&
        GameKeyboard.isKeyPressed(209)) {
      this.Reset();
    }

    if (DebugOptions.instance.WorldItemAtlasRender.getValue()) {
      int int0 = 512 / Core.TileScale;
      int0 /= 2;
      int int1 = 0;
      int int2 = 0;

      for (int int3 = 0; int3 < this.AtlasList.size(); int3++) {
        WorldItemAtlas.Atlas atlas = this.AtlasList.get(int3);
        SpriteRenderer.instance.renderi(nullptr, int1, int2, int0, int0, 1.0F,
                                        1.0F, 1.0F, 0.75F, nullptr);
        SpriteRenderer.instance.renderi(atlas.tex, int1, int2, int0, int0, 1.0F,
                                        1.0F, 1.0F, 1.0F, nullptr);
        float float0 = (float)int0 / atlas.tex.getWidth();

        for (int int4 = 0; int4 <= atlas.tex.getWidth() / atlas.ENTRY_WID;
             int4++) {
          SpriteRenderer.instance.renderline(
              nullptr, (int)(int1 + int4 * atlas.ENTRY_WID * float0), int2,
              (int)(int1 + int4 * atlas.ENTRY_WID * float0), int2 + int0, 0.5F,
              0.5F, 0.5F, 1.0F);
        }

        for (int int5 = 0; int5 <= atlas.tex.getHeight() / atlas.ENTRY_HGT;
             int5++) {
          SpriteRenderer.instance.renderline(
              nullptr, int1,
              (int)(int2 + int0 - int5 * atlas.ENTRY_HGT * float0), int1 + int0,
              (int)(int2 + int0 - int5 * atlas.ENTRY_HGT * float0), 0.5F, 0.5F,
              0.5F, 1.0F);
        }

        int2 += int0;
        if (int2 + int0 > Core.getInstance().getScreenHeight()) {
          int2 = 0;
          int1 += int0;
        }
      }
    }
  }

  void Reset() {
    if (this.fbo != nullptr) {
      this.fbo.destroyLeaveTexture();
      this.fbo = nullptr;
    }

    this.AtlasList.forEach(WorldItemAtlas.Atlas::Reset);
    this.AtlasList.clear();
    this.itemTextureMap.values().forEach(WorldItemAtlas.ItemTexture::Reset);
    this.itemTextureMap.clear();
    JobPool.forEach(WorldItemAtlas.RenderJob::Reset);
    JobPool.clear();
    this.RenderJobs.clear();
  }

private
  final class Atlas {
    const int ENTRY_WID;
    const int ENTRY_HGT;
    Texture tex;
  public
    final ArrayList<WorldItemAtlas.AtlasEntry> EntryList =
        std::make_unique<ArrayList<>>();
    bool clear = true;

  public
    Atlas(int arg1, int arg2, int arg3, int arg4) {
      this.ENTRY_WID = arg3;
      this.ENTRY_HGT = arg4;
      this.tex = new Texture(arg1, arg2, 16);
      if (WorldItemAtlas.this.fbo == nullptr) {
        WorldItemAtlas.this.fbo = new TextureFBO(this.tex, false);
      }
    }

    bool isFull() {
      int int0 = this.tex.getWidth() / this.ENTRY_WID;
      int int1 = this.tex.getHeight() / this.ENTRY_HGT;
      return this.EntryList.size() >= int0 * int1;
    }

  public
    WorldItemAtlas.AtlasEntry addItem(String arg0) {
      int int0 = this.tex.getWidth() / this.ENTRY_WID;
      int int1 = this.EntryList.size();
      int int2 = int1 % int0;
      int int3 = int1 / int0;
      WorldItemAtlas.AtlasEntry atlasEntry = new WorldItemAtlas.AtlasEntry();
      atlasEntry.atlas = this;
      atlasEntry.key = arg0;
      atlasEntry.x = int2 * this.ENTRY_WID;
      atlasEntry.y = int3 * this.ENTRY_HGT;
      atlasEntry.w = this.ENTRY_WID;
      atlasEntry.h = this.ENTRY_HGT;
      atlasEntry.tex =
          this.tex.split(arg0, atlasEntry.x,
                         this.tex.getHeight() - (atlasEntry.y + this.ENTRY_HGT),
                         atlasEntry.w, atlasEntry.h);
      atlasEntry.tex.setName(arg0);
      this.EntryList.add(atlasEntry);
      return atlasEntry;
    }

    void addEntry(WorldItemAtlas.AtlasEntry arg0) {
      int int0 = this.tex.getWidth() / this.ENTRY_WID;
      int int1 = this.EntryList.size();
      int int2 = int1 % int0;
      int int3 = int1 / int0;
      arg0.atlas = this;
      arg0.x = int2 * this.ENTRY_WID;
      arg0.y = int3 * this.ENTRY_HGT;
      arg0.w = this.ENTRY_WID;
      arg0.h = this.ENTRY_HGT;
      arg0.tex = this.tex.split(
          arg0.key, arg0.x, this.tex.getHeight() - (arg0.y + this.ENTRY_HGT),
          arg0.w, arg0.h);
      arg0.tex.setName(arg0.key);
      this.EntryList.add(arg0);
    }

    void Reset() {
      this.EntryList.forEach(WorldItemAtlas.AtlasEntry::Reset);
      this.EntryList.clear();
      if (!this.tex.isDestroyed()) {
        RenderThread.invokeOnRenderContext(
            ()->GL11.glDeleteTextures(this.tex.getID()));
      }

      this.tex = nullptr;
    }
  }

  private static final class AtlasEntry {
  public
    WorldItemAtlas.Atlas atlas;
    std::string key;
    int x;
    int y;
    int w;
    int h;
    float offsetX;
    float offsetY;
    Texture tex;
    bool ready = false;
    bool bRenderMainOK = false;
    bool bTooBig = false;

    void Reset() {
      this.atlas = nullptr;
      this.tex.destroy();
      this.tex = nullptr;
      this.ready = false;
      this.bRenderMainOK = false;
      this.bTooBig = false;
    }
  }

  private static final class Checksummer {
    MessageDigest md;
    const StringBuilder sb = new StringBuilder();

    void reset() {
      if (this.md == nullptr) {
        this.md = MessageDigest.getInstance("MD5");
      }

      this.md.reset();
    }

    void update(uint8_t arg0) { this.md.update(arg0); }

    void update(bool arg0) { this.md.update((byte)(arg0 ? 1 : 0)); }

    void update(int arg0) {
      this.md.update((byte)(arg0 & 0xFF));
      this.md.update((byte)(arg0 >> 8 & 0xFF));
      this.md.update((byte)(arg0 >> 16 & 0xFF));
      this.md.update((byte)(arg0 >> 24 & 0xFF));
    }

    void update(const std::string &arg0) {
      if (arg0 != nullptr && !arg0.isEmpty()) {
        this.md.update(arg0.getBytes());
      }
    }

    void update(ImmutableColor arg0) {
      this.update((byte)(arg0.r * 255.0F));
      this.update((byte)(arg0.g * 255.0F));
      this.update((byte)(arg0.b * 255.0F));
    }

    void update(IsoGridSquare.ResultLight arg0, float arg1, float arg2,
                float arg3) {
      if (arg0 != nullptr && arg0.radius > 0) {
        this.update((int)(arg0.x - arg1));
        this.update((int)(arg0.y - arg2));
        this.update((int)(arg0.z - arg3));
        this.update((byte)(arg0.r * 255.0F));
        this.update((byte)(arg0.g * 255.0F));
        this.update((byte)(arg0.b * 255.0F));
        this.update((byte)arg0.radius);
      }
    }

    std::string checksumToString() {
      byte[] bytes = this.md.digest();
      this.sb.setLength(0);

      for (int int0 = 0; int0 < bytes.length; int0++) {
        this.sb.append(bytes[int0] & 255);
      }

      return this.sb.toString();
    }
  }

  private static final class ClearAtlasTexture extends
      TextureDraw.GenericDrawer {
    WorldItemAtlas.Atlas m_atlas;

    ClearAtlasTexture(WorldItemAtlas.Atlas atlas) { this.m_atlas = atlas; }

    void render() {
      TextureFBO textureFBO = WorldItemAtlas.instance.fbo;
      if (textureFBO != nullptr && this.m_atlas.tex != nullptr) {
        if (this.m_atlas.clear) {
          if (textureFBO.getTexture() != this.m_atlas.tex) {
            textureFBO.setTexture(this.m_atlas.tex);
          }

          textureFBO.startDrawing(false, false);
          GL11.glPushAttrib(2048);
          GL11.glViewport(0, 0, textureFBO.getWidth(), textureFBO.getHeight());
          GL11.glMatrixMode(5889);
          GL11.glPushMatrix();
          GL11.glLoadIdentity();
          int int0 = this.m_atlas.tex.getWidth();
          int int1 = this.m_atlas.tex.getHeight();
          GLU.gluOrtho2D(0.0F, int0, int1, 0.0F);
          GL11.glMatrixMode(5888);
          GL11.glPushMatrix();
          GL11.glLoadIdentity();
          GL11.glDisable(3089);
          GL11.glClearColor(0.0F, 0.0F, 0.0F, 0.0F);
          GL11.glClear(16640);
          GL11.glClearColor(0.0F, 0.0F, 0.0F, 1.0F);
          textureFBO.endDrawing();
          GL11.glEnable(3089);
          GL11.glMatrixMode(5889);
          GL11.glPopMatrix();
          GL11.glMatrixMode(5888);
          GL11.glPopMatrix();
          GL11.glPopAttrib();
          this.m_atlas.clear = false;
        }
      }
    }
  }

private
  static final class ItemParams {
    float worldScale = 1.0F;
    float worldZRotation = 0.0F;
    WorldItemAtlas.ItemParams.FoodState m_foodState =
        WorldItemAtlas.ItemParams.FoodState.Normal;
    Model m_model;
  private
    ArrayList<WorldItemAtlas.WeaponPartParams> m_weaponParts;
    float m_hue;
    float m_tintR;
    float m_tintG;
    float m_tintB;
    const Vector3f m_angle = new Vector3f();
    const Matrix4f m_transform = new Matrix4f();
    float m_ambientR = 1.0F;
    float m_ambientG = 1.0F;
    float m_ambientB = 1.0F;
    float alpha = 1.0F;

    ItemParams() {}

    void copyFrom(WorldItemAtlas.ItemParams itemParams0) {
      this.worldScale = itemParams0.worldScale;
      this.worldZRotation = itemParams0.worldZRotation;
      this.m_foodState = itemParams0.m_foodState;
      this.m_model = itemParams0.m_model;
      if (this.m_weaponParts != nullptr) {
        WorldItemAtlas.instance.weaponPartParamPool.release(this.m_weaponParts);
        this.m_weaponParts.clear();
      }

      if (itemParams0.m_weaponParts != nullptr) {
        if (this.m_weaponParts == nullptr) {
          this.m_weaponParts = std::make_unique<ArrayList<>>();
        }

        for (int int0 = 0; int0 < itemParams0.m_weaponParts.size(); int0++) {
          WorldItemAtlas.WeaponPartParams weaponPartParams =
              itemParams0.m_weaponParts.get(int0);
          this.m_weaponParts.add(
              WorldItemAtlas.instance.weaponPartParamPool.alloc().init(
                  weaponPartParams));
        }
      }

      this.m_hue = itemParams0.m_hue;
      this.m_tintR = itemParams0.m_tintR;
      this.m_tintG = itemParams0.m_tintG;
      this.m_tintB = itemParams0.m_tintB;
      this.m_angle.set(itemParams0.m_angle);
      this.m_transform.set(itemParams0.m_transform);
    }

    bool init(InventoryItem item) {
      this.Reset();
      this.worldScale = item.worldScale;
      this.worldZRotation = item.worldZRotation;
      float float0 = 0.0F;
      std::string string0 =
          StringUtils.discardNullOrWhitespace(item.getWorldStaticItem());
      if (string0 != nullptr) {
        ModelScript modelScript0 =
            ScriptManager.instance.getModelScript(string0);
        if (modelScript0 == nullptr) {
          return false;
        } else {
          std::string string1 = modelScript0.getMeshName();
          std::string string2 = modelScript0.getTextureName();
          std::string string3 = modelScript0.getShaderName();
          ImmutableColor immutableColor0 = ImmutableColor.white;
          float float1 = 1.0F;
          Food food = Type.tryCastTo(item, Food.class);
          if (food != nullptr) {
            this.m_foodState = this.getFoodState(food);
            if (food.isCooked()) {
              ModelScript modelScript1 = ScriptManager.instance.getModelScript(
                  item.getWorldStaticItem() + "Cooked");
              if (modelScript1 != nullptr) {
                string2 = modelScript1.getTextureName();
                string1 = modelScript1.getMeshName();
                string3 = modelScript1.getShaderName();
                modelScript0 = modelScript1;
              }
            }

            if (food.isBurnt()) {
              ModelScript modelScript2 = ScriptManager.instance.getModelScript(
                  item.getWorldStaticItem() + "Burnt");
              if (modelScript2 != nullptr) {
                string2 = modelScript2.getTextureName();
                string1 = modelScript2.getMeshName();
                string3 = modelScript2.getShaderName();
                modelScript0 = modelScript2;
              }
            }

            if (food.isRotten()) {
              ModelScript modelScript3 = ScriptManager.instance.getModelScript(
                  item.getWorldStaticItem() + "Rotten");
              if (modelScript3 != nullptr) {
                string2 = modelScript3.getTextureName();
                string1 = modelScript3.getMeshName();
                string3 = modelScript3.getShaderName();
                modelScript0 = modelScript3;
              } else {
                immutableColor0 = WorldItemAtlas.ROTTEN_FOOD_COLOR;
              }
            }
          }

          Clothing clothing0 = Type.tryCastTo(item, Clothing.class);
          if (clothing0 != nullptr || item.getClothingItem() != nullptr) {
            std::string string4 = modelScript0.getTextureName(true);
            ItemVisual itemVisual0 = item.getVisual();
            ClothingItem clothingItem0 = item.getClothingItem();
            ImmutableColor immutableColor1 = itemVisual0.getTint(clothingItem0);
            if (string4 == nullptr) {
              if (clothingItem0.textureChoices.isEmpty()) {
                string4 = itemVisual0.getBaseTexture(clothingItem0);
              } else {
                string4 = itemVisual0.getTextureChoice(clothingItem0);
              }
            }

            if (string4 != nullptr) {
              string2 = string4;
              immutableColor0 = immutableColor1;
            }
          }

          bool boolean0 = modelScript0.bStatic;
          Model model0 = ModelManager.instance.tryGetLoadedModel(
              string1, string2, boolean0, string3, true);
          if (model0 == nullptr) {
            ModelManager.instance.loadAdditionalModel(string1, string2,
                                                      boolean0, string3);
          }

          model0 = ModelManager.instance.getLoadedModel(string1, string2,
                                                        boolean0, string3);
          if (model0 != nullptr && model0.isReady() && model0.Mesh != nullptr &&
              model0.Mesh.isReady()) {
            this.init(item, model0, modelScript0, float1, immutableColor0,
                      float0, false);
            if (this.worldScale != 1.0F) {
              this.m_transform.scale(modelScript0.scale * this.worldScale);
            } else if (modelScript0.scale != 1.0F) {
              this.m_transform.scale(modelScript0.scale);
            }

            this.m_angle.x = 0.0F;
            this.m_angle.y = this.worldZRotation;
            this.m_angle.z = 0.0F;
            return true;
          } else {
            return false;
          }
        }
      } else {
        Clothing clothing1 = Type.tryCastTo(item, Clothing.class);
        if (clothing1 == nullptr) {
          HandWeapon weapon = Type.tryCastTo(item, HandWeapon.class);
          if (weapon != nullptr) {
            std::string string5 =
                StringUtils.discardNullOrWhitespace(weapon.getStaticModel());
            if (string5 == nullptr) {
              return false;
            } else {
              ModelScript modelScript4 =
                  ScriptManager.instance.getModelScript(string5);
              if (modelScript4 == nullptr) {
                return false;
              } else {
                std::string string6 = modelScript4.getMeshName();
                std::string string7 = modelScript4.getTextureName();
                std::string string8 = modelScript4.getShaderName();
                bool boolean1 = modelScript4.bStatic;
                Model model1 = ModelManager.instance.tryGetLoadedModel(
                    string6, string7, boolean1, string8, false);
                if (model1 == nullptr) {
                  ModelManager.instance.loadAdditionalModel(string6, string7,
                                                            boolean1, string8);
                }

                model1 = ModelManager.instance.getLoadedModel(
                    string6, string7, boolean1, string8);
                if (model1 != nullptr && model1.isReady() &&
                    model1.Mesh != nullptr && model1.Mesh.isReady()) {
                  float float2 = 1.0F;
                  ImmutableColor immutableColor2 = ImmutableColor.white;
                  this.init(item, model1, modelScript4, float2, immutableColor2,
                            float0, true);
                  if (this.worldScale != 1.0F) {
                    this.m_transform.scale(modelScript4.scale *
                                           this.worldScale);
                  } else if (modelScript4.scale != 1.0F) {
                    this.m_transform.scale(modelScript4.scale);
                  }

                  this.m_angle.x = 0.0F;
                  this.m_angle.y = this.worldZRotation;
                  return this.initWeaponParts(weapon, modelScript4);
                } else {
                  return false;
                }
              }
            }
          } else {
            return false;
          }
        } else {
          ClothingItem clothingItem1 = item.getClothingItem();
          ItemVisual itemVisual1 = item.getVisual();
          bool boolean2 = false;
          std::string string9 = clothingItem1.getModel(boolean2);
          if (clothingItem1 != nullptr && itemVisual1 != nullptr &&
              !StringUtils.isNullOrWhitespace(string9) &&
              "Bip01_Head".equalsIgnoreCase(clothingItem1.m_AttachBone) &&
              (!clothing1.isCosmetic() || "Eyes" == item.getBodyLocation()))) {
              std::string string10 =
                  itemVisual1.getTextureChoice(clothingItem1);
              bool boolean3 = clothingItem1.m_Static;
              std::string string11 = clothingItem1.m_Shader;
              Model model2 = ModelManager.instance.tryGetLoadedModel(
                  string9, string10, boolean3, string11, false);
              if (model2 == nullptr) {
                ModelManager.instance.loadAdditionalModel(string9, string10,
                                                          boolean3, string11);
              }

              model2 = ModelManager.instance.getLoadedModel(string9, string10,
                                                            boolean3, string11);
              if (model2 != nullptr && model2.isReady() &&
                  model2.Mesh != nullptr && model2.Mesh.isReady()) {
                float float3 = itemVisual1.getHue(clothingItem1);
                ImmutableColor immutableColor3 =
                    itemVisual1.getTint(clothingItem1);
                this.init(item, model2, nullptr, float3, immutableColor3,
                          float0, false);
                this.m_angle.x = 180.0F + float0;
                this.m_angle.y = this.worldZRotation;
                this.m_angle.z = -90.0F;
                this.m_transform.translate(-0.08F, 0.0F, 0.05F);
                return true;
              } else {
                return false;
              }
            }
          else {
            return false;
          }
        }
      }
    }

    bool initWeaponParts(HandWeapon weapon, ModelScript modelScript) {
      std::vector arrayList0 = weapon.getModelWeaponPart();
      if (arrayList0 == nullptr) {
        return true;
      } else {
        std::vector arrayList1 = weapon.getAllWeaponParts(
            WorldItemAtlas.instance.m_tempWeaponPartList);

        for (int int0 = 0; int0 < arrayList1.size(); int0++) {
          WeaponPart weaponPart = (WeaponPart)arrayList1.get(int0);

          for (int int1 = 0; int1 < arrayList0.size(); int1++) {
            ModelWeaponPart modelWeaponPart =
                (ModelWeaponPart)arrayList0.get(int1);
            if (weaponPart.getFullType() == modelWeaponPart.partType)) {
                if (!this.initWeaponPart(modelWeaponPart, modelScript)) {
                  return false;
                }
                break;
              }
          }
        }

        return true;
      }
    }

    bool initWeaponPart(ModelWeaponPart modelWeaponPart,
                        ModelScript modelScript1) {
      std::string string0 =
          StringUtils.discardNullOrWhitespace(modelWeaponPart.modelName);
      if (string0 == nullptr) {
        return false;
      } else {
        ModelScript modelScript0 =
            ScriptManager.instance.getModelScript(string0);
        if (modelScript0 == nullptr) {
          return false;
        } else {
          std::string string1 = modelScript0.getMeshName();
          std::string string2 = modelScript0.getTextureName();
          std::string string3 = modelScript0.getShaderName();
          bool boolean0 = modelScript0.bStatic;
          Model model = ModelManager.instance.tryGetLoadedModel(
              string1, string2, boolean0, string3, false);
          if (model == nullptr) {
            ModelManager.instance.loadAdditionalModel(string1, string2,
                                                      boolean0, string3);
          }

          model = ModelManager.instance.getLoadedModel(string1, string2,
                                                       boolean0, string3);
          if (model != nullptr && model.isReady() && model.Mesh != nullptr &&
              model.Mesh.isReady()) {
            WorldItemAtlas.WeaponPartParams weaponPartParams =
                WorldItemAtlas.instance.weaponPartParamPool.alloc();
            weaponPartParams.m_model = model;
            weaponPartParams.m_attachmentNameSelf =
                modelWeaponPart.attachmentNameSelf;
            weaponPartParams.m_attachmentNameParent =
                modelWeaponPart.attachmentParent;
            weaponPartParams.initTransform(modelScript1, modelScript0);
            if (this.m_weaponParts == nullptr) {
              this.m_weaponParts = std::make_unique<ArrayList<>>();
            }

            this.m_weaponParts.add(weaponPartParams);
            return true;
          } else {
            return false;
          }
        }
      }
    }

    void init(InventoryItem var1, Model model, ModelScript modelScript,
              float float0, ImmutableColor immutableColor, float var6,
              bool boolean0) {
      this.m_model = model;
      this.m_tintR = immutableColor.r;
      this.m_tintG = immutableColor.g;
      this.m_tintB = immutableColor.b;
      this.m_hue = float0;
      this.m_angle.set(0.0F);
      this.m_transform.identity();
      this.m_ambientR = this.m_ambientG = this.m_ambientB = 1.0F;
      if (boolean0) {
        this.m_transform.rotateXYZ(0.0F, (float)Math.PI, (float)(Math.PI / 2));
      }

      if (modelScript != nullptr) {
        ModelAttachment modelAttachment =
            modelScript.getAttachmentById("world");
        if (modelAttachment != nullptr) {
          ModelInstanceRenderData.makeAttachmentTransform(
              modelAttachment, WorldItemAtlas.s_attachmentXfrm);
          WorldItemAtlas.s_attachmentXfrm.invert();
          this.m_transform.mul(WorldItemAtlas.s_attachmentXfrm);
        }
      }

      if (model.Mesh != nullptr && model.Mesh.isReady() &&
          model.Mesh.m_transform != nullptr) {
        model.Mesh.m_transform.transpose();
        this.m_transform.mul(model.Mesh.m_transform);
        model.Mesh.m_transform.transpose();
      }
    }

    WorldItemAtlas.ItemParams.FoodState getFoodState(Food food) {
      WorldItemAtlas.ItemParams.FoodState foodState =
          WorldItemAtlas.ItemParams.FoodState.Normal;
      if (food.isCooked()) {
        foodState = WorldItemAtlas.ItemParams.FoodState.Cooked;
      }

      if (food.isBurnt()) {
        foodState = WorldItemAtlas.ItemParams.FoodState.Burnt;
      }

      if (food.isRotten()) {
        foodState = WorldItemAtlas.ItemParams.FoodState.Rotten;
      }

      return foodState;
    }

    bool isStillValid(InventoryItem item) {
      if (item.worldScale == this.worldScale &&
          item.worldZRotation == this.worldZRotation) {
        Food food = Type.tryCastTo(item, Food.class);
        return food = = null || this.getFoodState(food) == this.m_foodState;
      } else {
        return false;
      }
    }

    void Reset() {
      this.m_model = nullptr;
      this.m_foodState = WorldItemAtlas.ItemParams.FoodState.Normal;
      if (this.m_weaponParts != nullptr) {
        WorldItemAtlas.instance.weaponPartParamPool.release(this.m_weaponParts);
        this.m_weaponParts.clear();
      }
    }

    static enum FoodState { Normal, Cooked, Burnt, Rotten; }
  }

  public static final class ItemTexture {
    final WorldItemAtlas.ItemParams itemParams =
        new WorldItemAtlas.ItemParams();
    WorldItemAtlas.AtlasEntry entry;

    bool isStillValid(InventoryItem item) {
      return this.entry == nullptr ? false : this.itemParams.isStillValid(item);
    }

    bool isRenderMainOK() { return this.entry.bRenderMainOK; }

    bool isTooBig() { return this.entry.bTooBig; }

    void render(float x, float y, float r, float g, float b, float a) {
      if (this.entry.ready && this.entry.tex.isReady()) {
        SpriteRenderer.instance.m_states.getPopulatingActiveState().render(
            this.entry.tex,
            x - (this.entry.w / 2.0F - this.entry.offsetX) / 2.5F,
            y - (this.entry.h / 2.0F - this.entry.offsetY) / 2.5F,
            this.entry.w / 2.5F, this.entry.h / 2.5F, r, g, b, a, nullptr);
      } else {
        SpriteRenderer.instance.drawGeneric(
            WorldItemAtlas.instance.itemTextureDrawerPool.alloc().init(
                this, x, y, r, g, b, a));
      }
    }

    void Reset() {
      this.itemParams.Reset();
      this.entry = nullptr;
    }
  }

  private static final class ItemTextureDrawer extends
      TextureDraw.GenericDrawer {
    WorldItemAtlas.ItemTexture itemTexture;
    float x;
    float y;
    float r;
    float g;
    float b;
    float a;

    WorldItemAtlas.ItemTextureDrawer init(
        WorldItemAtlas.ItemTexture itemTexturex, float float0, float float1,
        float float2, float float3, float float4, float float5) {
      this.itemTexture = itemTexturex;
      this.x = float0;
      this.y = float1;
      this.r = float2;
      this.g = float3;
      this.b = float4;
      this.a = float5;
      return this;
    }

    void render() {
      WorldItemAtlas.AtlasEntry atlasEntry = this.itemTexture.entry;
      if (atlasEntry != nullptr && atlasEntry.ready &&
          atlasEntry.tex.isReady()) {
        int int0 =
            (int)(this.x - (atlasEntry.w / 2.0F - atlasEntry.offsetX) / 2.5F);
        int int1 =
            (int)(this.y - (atlasEntry.h / 2.0F - atlasEntry.offsetY) / 2.5F);
        int int2 = (int)(atlasEntry.w / 2.5F);
        int int3 = (int)(atlasEntry.h / 2.5F);
        atlasEntry.tex.bind();
        GL11.glBegin(7);
        GL11.glColor4f(this.r, this.g, this.b, this.a);
        GL11.glTexCoord2f(atlasEntry.tex.xStart, atlasEntry.tex.yStart);
        GL11.glVertex2i(int0, int1);
        GL11.glTexCoord2f(atlasEntry.tex.xEnd, atlasEntry.tex.yStart);
        GL11.glVertex2i(int0 + int2, int1);
        GL11.glTexCoord2f(atlasEntry.tex.xEnd, atlasEntry.tex.yEnd);
        GL11.glVertex2i(int0 + int2, int1 + int3);
        GL11.glTexCoord2f(atlasEntry.tex.xStart, atlasEntry.tex.yEnd);
        GL11.glVertex2i(int0, int1 + int3);
        GL11.glColor4f(1.0F, 1.0F, 1.0F, 1.0F);
        GL11.glEnd();
        SpriteRenderer.ringBuffer.restoreBoundTextures = true;
      }
    }

    void postRender() {
      this.itemTexture = nullptr;
      WorldItemAtlas.instance.itemTextureDrawerPool.release(this);
    }
  }

private
  static final class RenderJob extends TextureDraw.GenericDrawer {
  public
    final WorldItemAtlas.ItemParams itemParams =
        new WorldItemAtlas.ItemParams();
  public
    WorldItemAtlas.AtlasEntry entry;
    int done = 0;
    int renderRefCount;
    bool bClearThisSlotOnly;
    int entryW;
    int entryH;
    final int[] m_viewport = new int[4];
    const Matrix4f m_matri4f = new Matrix4f();
    const Matrix4f m_projection = new Matrix4f();
    const Matrix4f m_modelView = new Matrix4f();
    const Vector3f m_scenePos = new Vector3f();
    final float[] m_bounds = new float[4];
    static const Vector3f tempVector3f = new Vector3f(0.0F, 5.0F, -2.0F);
    static const Matrix4f tempMatrix4f_1 = new Matrix4f();
    static const Matrix4f tempMatrix4f_2 = new Matrix4f();
    static final float[] xs = new float[8];
    static final float[] ys = new float[8];

  public
    static WorldItemAtlas.RenderJob getNew() {
      return WorldItemAtlas.JobPool.isEmpty() ? new WorldItemAtlas.RenderJob()
                                              : WorldItemAtlas.JobPool.pop();
    }

  public
    WorldItemAtlas.RenderJob init(WorldItemAtlas.ItemParams itemParamsx,
                                  WorldItemAtlas.AtlasEntry atlasEntry) {
      this.itemParams.copyFrom(itemParamsx);
      this.entry = atlasEntry;
      this.bClearThisSlotOnly = false;
      this.entryW = 0;
      this.entryH = 0;
      this.done = 0;
      this.renderRefCount = 0;
      return this;
    }

    bool renderMain() {
      Model model = this.itemParams.m_model;
      return model != nullptr && model.isReady() && model.Mesh != nullptr &&
             model.Mesh.isReady();
    }

    void render() {
      if (this.done != 1) {
        Model model = this.itemParams.m_model;
        if (model != nullptr && model.Mesh != nullptr && model.Mesh.isReady()) {
          float float0 = 0.0F;
          float float1 = 0.0F;
          this.calcMatrices(this.m_projection, this.m_modelView, float0,
                            float1);
          this.calcModelBounds(this.m_bounds);
          this.calcModelOffset();
          this.calcEntrySize();
          if (this.entryW > 0 && this.entryH > 0) {
            if (this.entryW <= 512 && this.entryH <= 512) {
              WorldItemAtlas.instance.assignEntryToAtlas(
                  this.entry, this.entryW, this.entryH);
              GL11.glPushAttrib(1048575);
              GL11.glPushClientAttrib(-1);
              GL11.glDepthMask(true);
              GL11.glColorMask(true, true, true, true);
              GL11.glDisable(3089);
              TextureFBO textureFBO = WorldItemAtlas.instance.fbo;
              if (textureFBO.getTexture() != this.entry.atlas.tex) {
                textureFBO.setTexture(this.entry.atlas.tex);
              }

              textureFBO.startDrawing(this.entry.atlas.clear,
                                      this.entry.atlas.clear);
              if (this.entry.atlas.clear) {
                this.entry.atlas.clear = false;
              }

              this.clearColorAndDepth();
              int int0 = this.entry.x - (int)this.entry.offsetX -
                         (1024 - this.entry.w) / 2;
              int int1 = -((int)this.entry.offsetY) - (1024 - this.entry.h) / 2;
              int1 += 512 - (this.entry.y + this.entry.h);
              GL11.glViewport(int0, int1, 1024, 1024);
              bool boolean0 = this.renderModel(this.itemParams.m_model, null);
              if (this.itemParams.m_weaponParts != nullptr &&
                  !this.itemParams.m_weaponParts.isEmpty()) {
                for (int int2 = 0; int2 < this.itemParams.m_weaponParts.size();
                     int2++) {
                  WorldItemAtlas.WeaponPartParams weaponPartParams =
                      this.itemParams.m_weaponParts.get(int2);
                  if (!this.renderModel(weaponPartParams.m_model,
                                        weaponPartParams.m_transform)) {
                    boolean0 = false;
                    break;
                  }
                }
              }

              textureFBO.endDrawing();
              if (!boolean0) {
                GL11.glPopAttrib();
                GL11.glPopClientAttrib();
              } else {
                this.entry.ready = true;
                this.done = 1;
                Texture.lastTextureID = -1;
                SpriteRenderer.ringBuffer.restoreBoundTextures = true;
                SpriteRenderer.ringBuffer.restoreVBOs = true;
                GL11.glPopAttrib();
                GL11.glPopClientAttrib();
              }
            } else {
              this.entry.bTooBig = true;
              this.done = 1;
            }
          }
        }
      }
    }

    void postRender() {
      if (this.entry != nullptr) {
        assert this.renderRefCount > 0;

        this.renderRefCount--;
      }
    }

    void clearColorAndDepth() {
      GL11.glEnable(3089);
      GL11.glScissor(this.entry.x, 512 - (this.entry.y + this.entry.h),
                     this.entry.w, this.entry.h);
      GL11.glClearColor(0.0F, 0.0F, 0.0F, 0.0F);
      GL11.glClear(16640);
      GL11.glClearColor(0.0F, 0.0F, 0.0F, 1.0F);
      this.restoreScreenStencil();
      GL11.glDisable(3089);
    }

    void restoreScreenStencil() {
      int int0 = SpriteRenderer.instance.getRenderingPlayerIndex();
      int int1 = int0 != 0 && int0 != 2
                     ? Core.getInstance().getOffscreenTrueWidth() / 2
                     : 0;
      int int2 = int0 != 0 && int0 != 1
                     ? Core.getInstance().getOffscreenTrueHeight() / 2
                     : 0;
      int int3 = Core.getInstance().getOffscreenTrueWidth();
      int int4 = Core.getInstance().getOffscreenTrueHeight();
      if (IsoPlayer.numPlayers > 1) {
        int3 /= 2;
      }

      if (IsoPlayer.numPlayers > 2) {
        int4 /= 2;
      }

      GL11.glScissor(int1, int2, int3, int4);
    }

    bool renderModel(Model model, Matrix4f matrix4f2) {
      if (!model.bStatic) {
        return false;
      } else {
        if (model.Effect == nullptr) {
          model.CreateShader("basicEffect");
        }

        Shader shader = model.Effect;
        if (shader == nullptr || model.Mesh == nullptr ||
            !model.Mesh.isReady()) {
          return false;
        } else if (model.tex != nullptr && !model.tex.isReady()) {
          return false;
        } else {
          PZGLUtil.pushAndLoadMatrix(5889, this.m_projection);
          Matrix4f matrix4f0 = tempMatrix4f_1.set(this.m_modelView);
          Matrix4f matrix4f1 =
              tempMatrix4f_2.set(this.itemParams.m_transform).invert();
          matrix4f0.mul(matrix4f1);
          PZGLUtil.pushAndLoadMatrix(5888, matrix4f0);
          GL11.glBlendFunc(770, 771);
          GL11.glDepthFunc(513);
          GL11.glDepthMask(true);
          GL11.glDepthRange(0.0, 1.0);
          GL11.glEnable(2929);
          GL11.glColor3f(1.0F, 1.0F, 1.0F);
          shader.Start();
          if (model.tex == nullptr) {
            shader.setTexture(Texture.getErrorTexture(), "Texture", 0);
          } else {
            shader.setTexture(model.tex, "Texture", 0);
          }

          shader.setDepthBias(0.0F);
          shader.setAmbient(this.itemParams.m_ambientR * 0.4F,
                            this.itemParams.m_ambientG * 0.4F,
                            this.itemParams.m_ambientB * 0.4F);
          shader.setLightingAmount(1.0F);
          shader.setHueShift(this.itemParams.m_hue);
          shader.setTint(this.itemParams.m_tintR, this.itemParams.m_tintG,
                         this.itemParams.m_tintB);
          shader.setAlpha(this.itemParams.alpha);

          for (int int0 = 0; int0 < 5; int0++) {
            shader.setLight(int0, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F,
                            Float.NaN, 0.0F, 0.0F, 0.0F, nullptr);
          }

          Vector3f vector3f = tempVector3f;
          vector3f.x = 0.0F;
          vector3f.y = 5.0F;
          vector3f.z = -2.0F;
          vector3f.rotateY(this.itemParams.m_angle.y *
                           (float)(Math.PI / 180.0));
          float float0 = 1.5F;
          shader.setLight(4, vector3f.x, vector3f.z, vector3f.y,
                          this.itemParams.m_ambientR / 4.0F * float0,
                          this.itemParams.m_ambientG / 4.0F * float0,
                          this.itemParams.m_ambientB / 4.0F * float0, 5000.0F,
                          Float.NaN, 0.0F, 0.0F, 0.0F, nullptr);
          if (matrix4f2 == nullptr) {
            shader.setTransformMatrix(this.itemParams.m_transform, false);
          } else {
            tempMatrix4f_1.set(this.itemParams.m_transform);
            tempMatrix4f_1.mul(matrix4f2);
            shader.setTransformMatrix(tempMatrix4f_1, false);
          }

          model.Mesh.Draw(shader);
          shader.End();
          if (Core.bDebug && DebugOptions.instance.ModelRenderAxis.getValue()) {
            Model.debugDrawAxis(0.0F, 0.0F, 0.0F, 0.5F, 1.0F);
          }

          PZGLUtil.popMatrix(5889);
          PZGLUtil.popMatrix(5888);
          return true;
        }
      }
    }

    void calcMatrices(Matrix4f matrix4f0, Matrix4f matrix4f1, float float1,
                      float float2) {
      matrix4f0.setOrtho(-0.26666668F, 0.26666668F, 0.26666668F, -0.26666668F,
                         -10.0F, 10.0F);
      matrix4f1.identity();
      float float0 = 0.047085002F;
      matrix4f1.scale(float0 * Core.TileScale / 2.0F);
      bool boolean0 = true;
      if (boolean0) {
        matrix4f1.rotate((float)(Math.PI / 6), 1.0F, 0.0F, 0.0F);
        matrix4f1.rotate((float)(Math.PI * 3.0 / 4.0), 0.0F, 1.0F, 0.0F);
      } else {
        matrix4f1.rotate((float)(Math.PI / 2), 0.0F, 1.0F, 0.0F);
      }

      matrix4f1.scale(-3.75F, 3.75F, 3.75F);
      matrix4f1.rotateXYZ(this.itemParams.m_angle.x * (float)(Math.PI / 180.0),
                          this.itemParams.m_angle.y * (float)(Math.PI / 180.0),
                          this.itemParams.m_angle.z * (float)(Math.PI / 180.0));
      matrix4f1.translate(float1, 0.0F, float2);
      matrix4f1.mul(this.itemParams.m_transform);
    }

    void calcModelBounds(float[] floats) {
      floats[0] = Float.MAX_VALUE;
      floats[1] = Float.MAX_VALUE;
      floats[2] = -Float.MAX_VALUE;
      floats[3] = -Float.MAX_VALUE;
      this.calcModelBounds(this.itemParams.m_model, this.m_modelView, floats);
      if (this.itemParams.m_weaponParts != nullptr) {
        for (int int0 = 0; int0 < this.itemParams.m_weaponParts.size();
             int0++) {
          WorldItemAtlas.WeaponPartParams weaponPartParams =
              this.itemParams.m_weaponParts.get(int0);
          Matrix4f matrix4f = tempMatrix4f_1.set(this.m_modelView)
                                  .mul(weaponPartParams.m_transform);
          this.calcModelBounds(weaponPartParams.m_model, matrix4f, floats);
        }
      }

      float float0 = 2.0F;
      floats[0] *= float0;
      floats[1] *= float0;
      floats[2] *= float0;
      floats[3] *= float0;
    }

    void calcModelBounds(Model model, Matrix4f matrix4f, float[] floats) {
      Vector3f vector3f0 = model.Mesh.minXYZ;
      Vector3f vector3f1 = model.Mesh.maxXYZ;
      xs[0] = vector3f0.x;
      ys[0] = vector3f0.y;
      xs[1] = vector3f0.x;
      ys[1] = vector3f1.y;
      xs[2] = vector3f1.x;
      ys[2] = vector3f1.y;
      xs[3] = vector3f1.x;
      ys[3] = vector3f0.y;

      for (int int0 = 0; int0 < 4; int0++) {
        this.sceneToUI(xs[int0], ys[int0], vector3f0.z, this.m_projection,
                       matrix4f, this.m_scenePos);
        floats[0] = PZMath.min(floats[0], this.m_scenePos.x);
        floats[2] = PZMath.max(floats[2], this.m_scenePos.x);
        floats[1] = PZMath.min(floats[1], this.m_scenePos.y);
        floats[3] = PZMath.max(floats[3], this.m_scenePos.y);
        this.sceneToUI(xs[int0], ys[int0], vector3f1.z, this.m_projection,
                       matrix4f, this.m_scenePos);
        floats[0] = PZMath.min(floats[0], this.m_scenePos.x);
        floats[2] = PZMath.max(floats[2], this.m_scenePos.x);
        floats[1] = PZMath.min(floats[1], this.m_scenePos.y);
        floats[3] = PZMath.max(floats[3], this.m_scenePos.y);
      }
    }

    void calcModelOffset() {
      float float0 = this.m_bounds[0];
      float float1 = this.m_bounds[1];
      float float2 = this.m_bounds[2];
      float float3 = this.m_bounds[3];
      this.entry.offsetX = float0 + (float2 - float0) / 2.0F - 512.0F;
      this.entry.offsetY = float1 + (float3 - float1) / 2.0F - 512.0F;
    }

    void calcEntrySize() {
      float float0 = this.m_bounds[0];
      float float1 = this.m_bounds[1];
      float float2 = this.m_bounds[2];
      float float3 = this.m_bounds[3];
      float float4 = 2.0F;
      float0 -= float4;
      float1 -= float4;
      float2 += float4;
      float3 += float4;
      uint8_t byte0 = 16;
      float0 = (float)Math.floor(float0 / byte0) * byte0;
      float2 = (float)Math.ceil(float2 / byte0) * byte0;
      float1 = (float)Math.floor(float1 / byte0) * byte0;
      float3 = (float)Math.ceil(float3 / byte0) * byte0;
      this.entryW = (int)(float2 - float0);
      this.entryH = (int)(float3 - float1);
    }

    Vector3f sceneToUI(float float0, float float1, float float2,
                       Matrix4f matrix4f1, Matrix4f matrix4f2,
                       Vector3f vector3f) {
      Matrix4f matrix4f0 = this.m_matri4f;
      matrix4f0.set(matrix4f1);
      matrix4f0.mul(matrix4f2);
      this.m_viewport[0] = 0;
      this.m_viewport[1] = 0;
      this.m_viewport[2] = 512;
      this.m_viewport[3] = 512;
      matrix4f0.project(float0, float1, float2, this.m_viewport, vector3f);
      return vector3f;
    }

    void Reset() {
      this.itemParams.Reset();
      this.entry = nullptr;
    }
  }

private
  static final class WeaponPartParams {
    Model m_model;
    std::string m_attachmentNameSelf;
    std::string m_attachmentNameParent;
    const Matrix4f m_transform = new Matrix4f();

    WorldItemAtlas.WeaponPartParams
    init(WorldItemAtlas.WeaponPartParams weaponPartParams0) {
      this.m_model = weaponPartParams0.m_model;
      this.m_attachmentNameSelf = weaponPartParams0.m_attachmentNameSelf;
      this.m_attachmentNameParent = weaponPartParams0.m_attachmentNameParent;
      this.m_transform.set(weaponPartParams0.m_transform);
      return this;
    }

    void initTransform(ModelScript modelScript0, ModelScript modelScript1) {
      this.m_transform.identity();
      Matrix4f matrix4f = WorldItemAtlas.s_attachmentXfrm;
      ModelAttachment modelAttachment0 =
          modelScript0.getAttachmentById(this.m_attachmentNameParent);
      if (modelAttachment0 != nullptr) {
        ModelInstanceRenderData.makeAttachmentTransform(modelAttachment0,
                                                        matrix4f);
        this.m_transform.mul(matrix4f);
      }

      ModelAttachment modelAttachment1 =
          modelScript1.getAttachmentById(this.m_attachmentNameSelf);
      if (modelAttachment1 != nullptr) {
        ModelInstanceRenderData.makeAttachmentTransform(modelAttachment1,
                                                        matrix4f);
        matrix4f.invert();
        this.m_transform.mul(matrix4f);
      }
    }
  }
}
} // namespace model
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
