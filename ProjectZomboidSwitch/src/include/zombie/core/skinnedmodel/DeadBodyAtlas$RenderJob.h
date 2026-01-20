#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/joml/Matrix4f.h"
#include "org/joml/Vector3f.h"
#include "org/lwjgl/opengl/GL11.h"
#include "zombie/core/Core.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/core/skinnedmodel/DeadBodyAtlas/AtlasEntry.h"
#include "zombie/core/skinnedmodel/DeadBodyAtlas/BodyParams.h"
#include "zombie/core/skinnedmodel/DeadBodyAtlas/RenderJob/L_getCameraRay.h"
#include "zombie/core/skinnedmodel/DeadBodyAtlas/RenderJob/L_uiToScene.h"
#include "zombie/core/skinnedmodel/advancedanimation/AnimatedModel.h"
#include "zombie/core/textures/TextureDraw/GenericDrawer.h"
#include "zombie/vehicles/UI3DScene.h"
#include "zombie/vehicles/UI3DScene/Plane.h"
#include "zombie/vehicles/UI3DScene/Ray.h"

namespace zombie {
namespace core {
namespace skinnedmodel {


class DeadBodyAtlas {
public:
    static float SIZEV = 42.75F;
    const BodyParams body = std::make_shared<BodyParams>();
    AtlasEntry entry;
    AnimatedModel animatedModel;
    float m_animPlayerAngle;
    int done = 0;
    int renderRefCount;
    bool bClearThisSlotOnly;
    int entryW;
    int entryH;
   const int[] m_viewport = new int[4];
    const Matrix4f m_matri4f = std::make_shared<Matrix4f>();
    const Matrix4f m_projection = std::make_shared<Matrix4f>();
    const Matrix4f m_modelView = std::make_shared<Matrix4f>();
    const Vector3f m_scenePos = std::make_shared<Vector3f>();
   const float[] m_bounds = new float[4];
   const float[] m_offset = new float[2];

   private DeadBodyAtlas$RenderJob() {
   }

   public static DeadBodyAtlas$RenderJob getNew() {
      return DeadBodyAtlas.JobPool.empty() ? new DeadBodyAtlas$RenderJob() : (DeadBodyAtlas$RenderJob)DeadBodyAtlas.JobPool.pop();
   }

   public DeadBodyAtlas$RenderJob init(BodyParams var1, AtlasEntry var2) {
      this.body.init(var1);
      this.entry = var2;
      if (this.animatedModel == nullptr) {
         this.animatedModel = std::make_unique<AnimatedModel>();
         this.animatedModel.setAnimate(false);
      }

      this.animatedModel.setAnimSetName(var1.animSetName);
      this.animatedModel.setState(var1.stateName);
      this.animatedModel.setPrimaryHandModelName(var1.primaryHandItem);
      this.animatedModel.setSecondaryHandModelName(var1.secondaryHandItem);
      this.animatedModel.setAttachedModelNames(var1.attachedModelNames);
      this.animatedModel.setAmbient(var1.ambient, var1.bOutside, var1.bRoom);
      this.animatedModel.setLights(var1.lights, var1.x, var1.y, var1.z);
      this.animatedModel.setModelData(var1.humanVisual, var1.itemVisuals);
      this.animatedModel.setAngle(DeadBodyAtlas.tempVector2.setLengthAndDirection(var1.angle, 1.0F));
      this.animatedModel.setVariable("FallOnFront", var1.fallOnFront);
      var1.variables.forEach((var1x, var2x) -> this.animatedModel.setVariable(var1x, var2x));
      this.animatedModel.setTrackTime(var1.trackTime);
      this.animatedModel.update();
      this.bClearThisSlotOnly = false;
      this.done = 0;
      this.renderRefCount = 0;
    return this;
   }

    bool renderMain() {
      if (this.animatedModel.isReadyToRender()) {
         this.animatedModel.renderMain();
         this.m_animPlayerAngle = this.animatedModel.getAnimationPlayer().getRenderedAngle();
    return true;
      } else {
    return false;
      }
   }

    void render() {
      if (this.done != 1) {
         GL11.glDepthMask(true);
         GL11.glColorMask(true, true, true, true);
         GL11.glDisable(3089);
         GL11.glPushAttrib(2048);
         ModelManager.instance.bitmap.startDrawing(true, true);
         GL11.glViewport(0, 0, ModelManager.instance.bitmap.getWidth(), ModelManager.instance.bitmap.getHeight());
         this.calcModelOffset(this.m_offset);
         this.animatedModel.setOffset(this.m_offset[0], 0.0F, this.m_offset[1]);
         this.animatedModel
            .DoRender(
               0, 0, ModelManager.instance.bitmap.getTexture().getWidth(), ModelManager.instance.bitmap.getTexture().getHeight(), SIZEV, this.m_animPlayerAngle
            );
         if (this.animatedModel.isRendered()) {
            this.renderAABB();
         }

         ModelManager.instance.bitmap.endDrawing();
         GL11.glPopAttrib();
         if (this.animatedModel.isRendered()) {
            DeadBodyAtlas.instance.assignEntryToAtlas(this.entry, this.entryW, this.entryH);
            DeadBodyAtlas.instance.toBodyAtlas(this);
         }
      }
   }

    void postRender() {
      if (this.animatedModel != nullptr) {
         this.animatedModel.postRender(this.done == 1);
         if (!$assertionsDisabled && this.renderRefCount <= 0) {
            throw std::make_unique<AssertionError>();
         } else {
            this.renderRefCount--;
         }
      }
   }

    void calcMatrices(Matrix4f var1, Matrix4f var2, float var3, float var4) {
    int var5 = ModelManager.instance.bitmap.getWidth();
    int var6 = ModelManager.instance.bitmap.getHeight();
    float var7 = SIZEV;
    float var8 = (float)var5 / var6;
    bool var9 = true;
      var1.identity();
      if (var9) {
         var1.ortho(-var7 * var8, var7 * var8, var7, -var7, -100.0F, 100.0F);
      } else {
         var1.ortho(-var7 * var8, var7 * var8, -var7, var7, -100.0F, 100.0F);
      }

    float var10 = (float)Math.sqrt(2048.0);
      var1.scale(-var10, var10, var10);
      var2.identity();
    bool var11 = true;
      if (var11) {
         var2.rotate((float) (Math.PI / 6), 1.0F, 0.0F, 0.0F);
         var2.rotate(this.m_animPlayerAngle + (float) (Math.PI / 4), 0.0F, 1.0F, 0.0F);
      } else {
         var2.rotate(this.m_animPlayerAngle, 0.0F, 1.0F, 0.0F);
      }

      var2.translate(var3, 0.0F, var4);
   }

    void calcModelBounds(float[] var1) {
    float var2 = float.MAX_VALUE;
    float var3 = float.MAX_VALUE;
    float var4 = -float.MAX_VALUE;
    float var5 = -float.MAX_VALUE;

      for (int var6 = 0; var6 < this.animatedModel.getAnimationPlayer().modelTransforms.length; var6++) {
         if (var6 != 44) {
            org.lwjgl.util.vector.Matrix4f var7 = this.animatedModel.getAnimationPlayer().modelTransforms[var6];
            this.sceneToUI(var7.m03, var7.m13, var7.m23, this.m_projection, this.m_modelView, this.m_scenePos);
            var2 = PZMath.min(var2, this.m_scenePos.x);
            var4 = PZMath.max(var4, this.m_scenePos.x);
            var3 = PZMath.min(var3, this.m_scenePos.y);
            var5 = PZMath.max(var5, this.m_scenePos.y);
         }
      }

      var1[0] = var2;
      var1[1] = var3;
      var1[2] = var4;
      var1[3] = var5;
   }

    void calcModelOffset(float[] var1) {
    int var2 = ModelManager.instance.bitmap.getWidth();
    int var3 = ModelManager.instance.bitmap.getHeight();
    float var4 = 0.0F;
    float var5 = this.body.bStanding ? -0.0F : 0.0F;
      this.calcMatrices(this.m_projection, this.m_modelView, var4, var5);
      this.calcModelBounds(this.m_bounds);
    float var6 = this.m_bounds[0];
    float var7 = this.m_bounds[1];
    float var8 = this.m_bounds[2];
    float var9 = this.m_bounds[3];
      this.uiToScene(this.m_projection, this.m_modelView, var6, var7, this.m_scenePos);
    float var10 = this.m_scenePos.x;
    float var11 = this.m_scenePos.z;
    float var12 = (var2 - (var8 - var6)) / 2.0F;
    float var13 = (var3 - (var9 - var7)) / 2.0F;
      this.uiToScene(this.m_projection, this.m_modelView, var12, var13, this.m_scenePos);
      var4 += this.m_scenePos.x - var10;
      var5 += this.m_scenePos.z - var11;
      var1[0] = 1.0F * var4 + 0.0F;
      var1[1] = 1.0F * var5 + 0.0F;
      this.entry.offsetX = (var12 - var6) / (8.0F / Core.TileScale);
      this.entry.offsetY = (var13 - var7) / (8.0F / Core.TileScale);
   }

    void renderAABB() {
      this.calcMatrices(this.m_projection, this.m_modelView, this.m_offset[0], this.m_offset[1]);
      this.calcModelBounds(this.m_bounds);
    float var1 = this.m_bounds[0];
    float var2 = this.m_bounds[1];
    float var3 = this.m_bounds[2];
    float var4 = this.m_bounds[3];
    int var5 = ModelManager.instance.bitmap.getWidth();
    int var6 = ModelManager.instance.bitmap.getHeight();
    float var7 = 128.0F;
      var1 -= var7;
      var2 -= var7;
      var3 += var7;
      var4 += var7;
      var1 = (float)Math.floor(var1 / 128.0F) * 128.0F;
      var3 = (float)Math.ceil(var3 / 128.0F) * 128.0F;
      var2 = (float)Math.floor(var2 / 128.0F) * 128.0F;
      var4 = (float)Math.ceil(var4 / 128.0F) * 128.0F;
      this.entryW = (int)(var3 - var1) / (8 / Core.TileScale);
      this.entryH = (int)(var4 - var2) / (8 / Core.TileScale);
   }

    Ray getCameraRay(float var1, float var2, Matrix4f var3, Matrix4f var4, Ray var5) {
    Matrix4f var6 = L_getCameraRay.matrix4f;
      var6.set(var3);
      var6.mul(var4);
      var6.invert();
      this.m_viewport[0] = 0;
      this.m_viewport[1] = 0;
      this.m_viewport[2] = ModelManager.instance.bitmap.getWidth();
      this.m_viewport[3] = ModelManager.instance.bitmap.getHeight();
    Vector3f var7 = var6.unprojectInv(var1, var2, 0.0F, this.m_viewport, L_getCameraRay.ray_start);
    Vector3f var8 = var6.unprojectInv(var1, var2, 1.0F, this.m_viewport, L_getCameraRay.ray_end);
      var5.origin.set(var7);
      var5.direction.set(var8.sub(var7).normalize());
    return var5;
   }

    Vector3f sceneToUI(float var1, float var2, float var3, Matrix4f var4, Matrix4f var5, Vector3f var6) {
    Matrix4f var7 = this.m_matri4f;
      var7.set(var4);
      var7.mul(var5);
      this.m_viewport[0] = 0;
      this.m_viewport[1] = 0;
      this.m_viewport[2] = ModelManager.instance.bitmap.getWidth();
      this.m_viewport[3] = ModelManager.instance.bitmap.getHeight();
      var7.project(var1, var2, var3, this.m_viewport, var6);
    return var6;
   }

    Vector3f uiToScene(Matrix4f var1, Matrix4f var2, float var3, float var4, Vector3f var5) {
    Plane var6 = L_uiToScene.plane;
      var6.point.set(0.0F);
      var6.normal.set(0.0F, 1.0F, 0.0F);
    Ray var7 = this.getCameraRay(var3, var4, var1, var2, L_uiToScene.ray);
      if (UI3DScene.intersect_ray_plane(var6, var7, var5) != 1) {
         var5.set(0.0F);
      }

    return var5;
   }

    void Reset() {
      this.body.Reset();
      this.entry = nullptr;
      if (this.animatedModel != nullptr) {
         this.animatedModel.releaseAnimationPlayer();
         this.animatedModel = nullptr;
      }
   }
}
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
