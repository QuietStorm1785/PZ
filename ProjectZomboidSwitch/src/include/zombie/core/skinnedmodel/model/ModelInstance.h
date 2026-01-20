#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/joml/Math.h"
#include "org/joml/Matrix4f.h"
#include "org/joml/Vector3f.h"
#include "zombie/GameTime.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/opengl/RenderThread.h"
#include "zombie/core/skinnedmodel/animation/AnimationPlayer.h"
#include "zombie/core/skinnedmodel/model/ModelInstance/PlayerData.h"
#include "zombie/core/skinnedmodel/visual/ItemVisual.h"
#include "zombie/core/textures/ColorInfo.h"
#include "zombie/core/textures/SmartTexture.h"
#include "zombie/core/textures/Texture.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/iso/IsoCamera.h"
#include "zombie/iso/IsoMovingObject.h"
#include "zombie/iso/Vector2.h"
#include "zombie/scripting/ScriptManager.h"
#include "zombie/scripting/objects/ModelAttachment.h"
#include "zombie/scripting/objects/ModelScript.h"
#include "zombie/util/StringUtils.h"
#include <algorithm>

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace model {


class ModelInstance {
public:
    static float MODEL_LIGHT_MULT_OUTSIDE = 1.7F;
    static float MODEL_LIGHT_MULT_ROOM = 1.7F;
    Model model;
    AnimationPlayer AnimPlayer;
    SkinningData data;
    Texture tex;
    ModelInstanceTextureInitializer m_textureInitializer;
    IsoGameCharacter character;
    IsoMovingObject object;
    float tintR = 1.0F;
    float tintG = 1.0F;
    float tintB = 1.0F;
    ModelInstance parent;
    int parentBone;
    std::string parentBoneName = nullptr;
    float hue;
    float depthBias;
    ModelInstance matrixModel;
    SoftwareModelMeshInstance softwareMesh;
   public const std::vector<ModelInstance> sub = std::make_unique<std::vector<>>();
    int instanceSkip;
    ItemVisual itemVisual = nullptr;
    bool bResetAfterRender = false;
    void* m_owner = nullptr;
    int renderRefCount;
    static const int INITIAL_SKIP_VALUE = int.MAX_VALUE;
    int skipped = int.MAX_VALUE;
    const void* m_lock = "ModelInstance Thread Lock";
    ModelScript m_modelScript = nullptr;
    std::string attachmentNameSelf = nullptr;
    std::string attachmentNameParent = nullptr;
    float scale = 1.0F;
    std::string maskVariableValue = nullptr;
   public PlayerData[] playerData;
    static const ColorInfo tempColorInfo = std::make_shared<ColorInfo>();
    static const ColorInfo tempColorInfo2 = std::make_shared<ColorInfo>();

    ModelInstance init(Model var1, IsoGameCharacter var2, AnimationPlayer var3) {
      this.data = (SkinningData)var1.Tag;
      this.model = var1;
      this.tex = var1.tex;
      if (!var1.bStatic && var3 == nullptr) {
         var3 = AnimationPlayer.alloc(var1);
      }

      this.AnimPlayer = var3;
      this.character = var2;
      this.object = var2;
    return this;
   }

    bool isRendering() {
      return this.renderRefCount > 0;
   }

    void reset() {
      if (this.dynamic_cast<SmartTexture*>(tex) != nullptr) {
    Texture var1 = this.tex;
         RenderThread.queueInvokeOnRenderContext(var1::destroy);
      }

      this.AnimPlayer = nullptr;
      this.character = nullptr;
      this.data = nullptr;
      this.hue = 0.0F;
      this.itemVisual = nullptr;
      this.matrixModel = nullptr;
      this.model = nullptr;
      this.object = nullptr;
      this.parent = nullptr;
      this.parentBone = 0;
      this.parentBoneName = nullptr;
      this.skipped = int.MAX_VALUE;
      this.sub.clear();
      this.softwareMesh = nullptr;
      this.tex = nullptr;
      if (this.m_textureInitializer != nullptr) {
         this.m_textureInitializer.release();
         this.m_textureInitializer = nullptr;
      }

      this.tintR = 1.0F;
      this.tintG = 1.0F;
      this.tintB = 1.0F;
      this.bResetAfterRender = false;
      this.renderRefCount = 0;
      this.scale = 1.0F;
      this.m_owner = nullptr;
      this.m_modelScript = nullptr;
      this.attachmentNameSelf = nullptr;
      this.attachmentNameParent = nullptr;
      this.maskVariableValue = nullptr;
      if (this.playerData != nullptr) {
         PlayerData.pool.release(this.playerData);
         Arrays.fill(this.playerData, nullptr);
      }
   }

    void LoadTexture(const std::string& var1) {
      if (var1 != nullptr && var1.length() != 0) {
         this.tex = Texture.getSharedTexture("media/textures/" + var1 + ".png");
         if (this.tex == nullptr) {
            if (var1 == "Vest_White")) {
               this.tex = Texture.getSharedTexture("media/textures/Shirt_White.png");
            } else if (var1.contains("Hair")) {
               this.tex = Texture.getSharedTexture("media/textures/F_Hair_White.png");
            } else if (var1.contains("Beard")) {
               this.tex = Texture.getSharedTexture("media/textures/F_Hair_White.png");
            } else {
               DebugLog.log("ERROR: model texture \"" + var1 + "\" wasn't found");
            }
         }
      } else {
         this.tex = nullptr;
      }
   }

    void dismember(int var1) {
      this.AnimPlayer.dismember(var1);
   }

    void UpdateDir() {
      if (this.AnimPlayer != nullptr) {
         this.AnimPlayer.UpdateDir(this.character);
      }
   }

    void Update() {
      if (this.character != nullptr) {
    float var1 = this.character.DistTo(IsoPlayer.getInstance());
         if (!this.character.amputations.empty() && var1 > 0.0F && this.AnimPlayer != nullptr) {
            this.AnimPlayer.dismembered.clear();
    std::vector var2 = this.character.amputations;

            for (int var3 = 0; var3 < var2.size(); var3++) {
    std::string var4 = (std::string)var2.get(var3);
               this.AnimPlayer.dismember((int)this.AnimPlayer.getSkinningData().BoneIndices.get(var4));
            }
         }

         if (Math.abs(this.character.speedMod - 0.5957F) < 1.0E-4F) {
    bool var6 = false;
         }
      }

      this.instanceSkip = 0;
      if (this.AnimPlayer != nullptr) {
         if (this.matrixModel == nullptr) {
            if (this.skipped >= this.instanceSkip) {
               if (this.skipped == int.MAX_VALUE) {
                  this.skipped = 1;
               }

    float var5 = GameTime.instance.getTimeDelta() * this.skipped;
               this.AnimPlayer.Update(var5);
            } else {
               this.AnimPlayer.DoAngles();
            }

            this.AnimPlayer.parentPlayer = nullptr;
         } else {
            this.AnimPlayer.parentPlayer = this.matrixModel.AnimPlayer;
         }
      }

      if (this.skipped >= this.instanceSkip) {
         this.skipped = 0;
      }

      this.skipped++;
   }

    void SetForceDir(Vector2 var1) {
      if (this.AnimPlayer != nullptr) {
         this.AnimPlayer.SetForceDir(var1);
      }
   }

    void setInstanceSkip(int var1) {
      this.instanceSkip = var1;

      for (int var2 = 0; var2 < this.sub.size(); var2++) {
    ModelInstance var3 = this.sub.get(var2);
         var3.instanceSkip = var1;
      }
   }

    void destroySmartTextures() {
      if (this.dynamic_cast<SmartTexture*>(tex) != nullptr) {
         this.tex.destroy();
         this.tex = nullptr;
      }

      for (int var1 = 0; var1 < this.sub.size(); var1++) {
    ModelInstance var2 = this.sub.get(var1);
         var2.destroySmartTextures();
      }
   }

    void updateLights() {
    int var1 = IsoCamera.frameState.playerIndex;
      if (this.playerData == nullptr) {
         this.playerData = new PlayerData[4];
      }

    bool var2 = this.playerData[var1] == nullptr;
      if (this.playerData[var1] == nullptr) {
         this.playerData[var1] = (PlayerData)PlayerData.pool.alloc();
      }

      this.playerData[var1].updateLights(this.character, var2);
   }

    ItemVisual getItemVisual() {
      return this.itemVisual;
   }

    void setItemVisual(ItemVisual var1) {
      this.itemVisual = var1;
   }

    void applyModelScriptScale(const std::string& var1) {
      this.m_modelScript = ScriptManager.instance.getModelScript(var1);
      if (this.m_modelScript != nullptr) {
         this.scale = this.m_modelScript.scale;
      }
   }

    ModelAttachment getAttachment(int var1) {
      return this.m_modelScript == nullptr ? nullptr : this.m_modelScript.getAttachment(var1);
   }

    ModelAttachment getAttachmentById(const std::string& var1) {
      if (StringUtils.isNullOrWhitespace(var1)) {
    return nullptr;
      } else {
         return this.m_modelScript == nullptr ? nullptr : this.m_modelScript.getAttachmentById(var1);
      }
   }

    Matrix4f getAttachmentMatrix(ModelAttachment var1, Matrix4f var2) {
      var2.translation(var1.getOffset());
    Vector3f var3 = var1.getRotate();
      var2.rotateXYZ(var3.x * (float) (java.lang.Math.PI / 180.0), var3.y * (float) (java.lang.Math.PI / 180.0), var3.z * (float) (java.lang.Math.PI / 180.0));
    return var2;
   }

    Matrix4f getAttachmentMatrix(int var1, Matrix4f var2) {
    ModelAttachment var3 = this.getAttachment(var1);
    return var3 = = nullptr ? var2.identity() : this.getAttachmentMatrix(var3, var2);
   }

    Matrix4f getAttachmentMatrixById(const std::string& var1, Matrix4f var2) {
    ModelAttachment var3 = this.getAttachmentById(var1);
    return var3 = = nullptr ? var2.identity() : this.getAttachmentMatrix(var3, var2);
   }

    void setOwner(void* var1) {
      Objects.requireNonNull(var1);

      assert this.m_owner == nullptr;

      this.m_owner = var1;
   }

    void clearOwner(void* var1) {
      Objects.requireNonNull(var1);

      assert this.m_owner == var1;

      this.m_owner = nullptr;
   }

    void* getOwner() {
      return this.m_owner;
   }

    void setTextureInitializer(ModelInstanceTextureInitializer var1) {
      this.m_textureInitializer = var1;
   }

    ModelInstanceTextureInitializer getTextureInitializer() {
      return this.m_textureInitializer;
   }

    bool hasTextureCreator() {
      return this.m_textureInitializer != nullptr && this.m_textureInitializer.isDirty();
   }
}
} // namespace model
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
