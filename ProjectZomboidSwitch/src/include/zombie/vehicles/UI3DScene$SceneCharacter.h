#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/joml/Matrix4f.h"
#include "org/joml/Quaternionf.h"
#include "org/lwjgl/util/vector/Vector3f.h"
#include "zombie/core/SpriteRenderer.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/core/skinnedmodel/advancedanimation/AnimatedModel.h"
#include "zombie/core/skinnedmodel/animation/AnimationMultiTrack.h"
#include "zombie/core/skinnedmodel/animation/AnimationPlayer.h"
#include "zombie/core/skinnedmodel/animation/AnimationTrack.h"
#include "zombie/core/skinnedmodel/model/SkinningBone.h"
#include "zombie/core/skinnedmodel/model/SkinningData.h"
#include "zombie/core/skinnedmodel/visual/HumanVisual.h"
#include "zombie/scripting/ScriptManager.h"
#include "zombie/scripting/objects/ModelAttachment.h"
#include "zombie/scripting/objects/ModelScript.h"
#include "zombie/vehicles/UI3DScene/CharacterRenderData.h"
#include "zombie/vehicles/UI3DScene/PositionRotation.h"
#include "zombie/vehicles/UI3DScene/Ray.h"
#include "zombie/vehicles/UI3DScene/SceneObject.h"
#include "zombie/vehicles/UI3DScene/SceneObjectRenderData.h"

namespace zombie {
namespace vehicles {


class UI3DScene {
public:
    const AnimatedModel m_animatedModel;
    bool m_bShowBones = false;
    bool m_bClearDepthBuffer = true;
    bool m_bUseDeferredMovement = false;

   UI3DScene$SceneCharacter(UI3DScene var1, std::string var2) {
      super(var1, var2);
      this.m_animatedModel = std::make_unique<AnimatedModel>();
      this.m_animatedModel.setAnimSetName("player-vehicle");
      this.m_animatedModel.setState("idle");
      this.m_animatedModel.setOutfitName("Naked", false, false);
      this.m_animatedModel.setVisual(std::make_shared<HumanVisual>(this.m_animatedModel));
      this.m_animatedModel.getHumanVisual().setHairModel("Bald");
      this.m_animatedModel.getHumanVisual().setBeardModel("");
      this.m_animatedModel.getHumanVisual().setSkinTextureIndex(0);
      this.m_animatedModel.setAlpha(0.5F);
      this.m_animatedModel.setAnimate(false);
   }

    SceneObjectRenderData renderMain() {
      this.m_animatedModel.update();
    CharacterRenderData var1 = (CharacterRenderData)CharacterRenderData.s_pool.alloc();
      var1.initCharacter(this);
      SpriteRenderer.instance.drawGeneric(var1.m_drawer);
    return var1;
   }

    Matrix4f getLocalTransform(Matrix4f var1) {
      var1.identity();
      var1.rotateY((float) Math.PI);
      var1.translate(-this.m_translate.x, this.m_translate.y, this.m_translate.z);
      var1.scale(-1.5F, 1.5F, 1.5F);
    float var2 = this.m_rotate.y;
      if (this.m_autoRotate) {
         var2 += this.m_autoRotateAngle;
      }

      var1.rotateXYZ(this.m_rotate.x * (float) (Math.PI / 180.0), var2 * (float) (Math.PI / 180.0), this.m_rotate.z * (float) (Math.PI / 180.0));
      if (this.m_animatedModel.getAnimationPlayer().getMultiTrack().getTracks().empty()) {
    return var1;
      } else {
         if (this.m_bUseDeferredMovement) {
    AnimationMultiTrack var3 = this.m_animatedModel.getAnimationPlayer().getMultiTrack();
    float var4 = ((AnimationTrack)var3.getTracks().get(0)).getCurrentDeferredRotation();
    Vector3f var5 = std::make_shared<Vector3f>();
            ((AnimationTrack)var3.getTracks().get(0)).getCurrentDeferredPosition(var5);
            var1.translate(var5.x, var5.y, var5.z);
         }

    return var1;
      }
   }

    Matrix4f getAttachmentTransform(const std::string& var1, Matrix4f var2) {
      var2.identity();
    bool var3 = this.m_animatedModel.isFemale();
    ModelScript var4 = ScriptManager.instance.getModelScript(var3 ? "FemaleBody" : "MaleBody");
      if (var4 == nullptr) {
    return var2;
      } else {
    ModelAttachment var5 = var4.getAttachmentById(var1);
         if (var5 == nullptr) {
    return var2;
         } else {
            var2.translation(var5.getOffset());
            org.joml.Vector3f var6 = var5.getRotate();
            var2.rotateXYZ(var6.x * (float) (Math.PI / 180.0), var6.y * (float) (Math.PI / 180.0), var6.z * (float) (Math.PI / 180.0));
            if (var5.getBone() != nullptr) {
    Matrix4f var7 = this.getBoneMatrix(var5.getBone(), UI3DScene.allocMatrix4f());
               var7.mul(var2, var2);
               UI3DScene.releaseMatrix4f(var7);
            }

    return var2;
         }
      }
   }

    int hitTestBone(int var1, Ray var2, Ray var3, Matrix4f var4) {
    AnimationPlayer var5 = this.m_animatedModel.getAnimationPlayer();
    SkinningData var6 = var5.getSkinningData();
    int var7 = (int)var6.SkeletonHierarchy.get(var1);
      if (var7 == -1) {
         return -1;
      } else {
         org.lwjgl.util.vector.Matrix4f var8 = var5.modelTransforms[var7];
         var2.origin.set(var8.m03, var8.m13, var8.m23);
         var4.transformPosition(var2.origin);
         var8 = var5.modelTransforms[var1];
         org.joml.Vector3f var9 = UI3DScene.allocVector3f();
         var9.set(var8.m03, var8.m13, var8.m23);
         var4.transformPosition(var9);
         var2.direction.set(var9).sub(var2.origin);
    float var10 = var2.direction.length();
         var2.direction.normalize();
         this.m_scene.closest_distance_between_lines(var3, var2);
         float var11 = this.m_scene
            .sceneToUIX(var3.origin.x + var3.direction.x * var3.t, var3.origin.y + var3.direction.y * var3.t, var3.origin.z + var3.direction.z * var3.t);
         float var12 = this.m_scene
            .sceneToUIY(var3.origin.x + var3.direction.x * var3.t, var3.origin.y + var3.direction.y * var3.t, var3.origin.z + var3.direction.z * var3.t);
         float var13 = this.m_scene
            .sceneToUIX(var2.origin.x + var2.direction.x * var2.t, var2.origin.y + var2.direction.y * var2.t, var2.origin.z + var2.direction.z * var2.t);
         float var14 = this.m_scene
            .sceneToUIY(var2.origin.x + var2.direction.x * var2.t, var2.origin.y + var2.direction.y * var2.t, var2.origin.z + var2.direction.z * var2.t);
    int var15 = -1;
    float var16 = 10.0F;
    float var17 = (float)Math.sqrt(Math.pow(var13 - var11, 2.0) + Math.pow(var14 - var12, 2.0));
         if (var17 < var16) {
            if (var2.t >= 0.0F && var2.t < var10 * 0.5F) {
               var15 = var7;
            } else if (var2.t >= var10 * 0.5F && var2.t < var10) {
               var15 = var1;
            }
         }

         UI3DScene.releaseVector3f(var9);
    return var15;
      }
   }

    std::string pickBone(float var1, float var2) {
      if (this.m_animatedModel.getAnimationPlayer().modelTransforms == nullptr) {
         return "";
      } else {
         var2 = this.m_scene.screenHeight() - var2;
    Ray var3 = this.m_scene.getCameraRay(var1, var2, UI3DScene.allocRay());
    Matrix4f var4 = UI3DScene.allocMatrix4f();
         this.getLocalTransform(var4);
    Ray var5 = UI3DScene.allocRay();
    int var6 = -1;

         for (int var7 = 0; var7 < this.m_animatedModel.getAnimationPlayer().modelTransforms.length; var7++) {
            var6 = this.hitTestBone(var7, var5, var3, var4);
            if (var6 != -1) {
               break;
            }
         }

         UI3DScene.releaseRay(var5);
         UI3DScene.releaseRay(var3);
         UI3DScene.releaseMatrix4f(var4);
    return var6 = = -1 ? "" : this.m_animatedModel.getAnimationPlayer().getSkinningData().getBoneAt(var6).Name;
      }
   }

    Matrix4f getBoneMatrix(const std::string& var1, Matrix4f var2) {
      var2.identity();
      if (this.m_animatedModel.getAnimationPlayer().modelTransforms == nullptr) {
    return var2;
      } else {
    SkinningBone var3 = this.m_animatedModel.getAnimationPlayer().getSkinningData().getBone(var1);
         if (var3 == nullptr) {
    return var2;
         } else {
            var2 = PZMath.convertMatrix(this.m_animatedModel.getAnimationPlayer().modelTransforms[var3.Index], var2);
            var2.transpose();
    return var2;
         }
      }
   }

    PositionRotation getBoneAxis(const std::string& var1, PositionRotation var2) {
    Matrix4f var3 = UI3DScene.allocMatrix4f().identity();
      var3.getTranslation(var2.pos);
      UI3DScene.releaseMatrix4f(var3);
    Quaternionf var4 = var3.getUnnormalizedRotation(UI3DScene.allocQuaternionf());
      var4.getEulerAnglesXYZ(var2.rot);
      UI3DScene.releaseQuaternionf(var4);
    return var2;
   }
}
} // namespace vehicles
} // namespace zombie
