#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/joml/Matrix4f.h"
#include "org/joml/Vector3f.h"
#include <GL/glew.h>
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/Core.h"
#include "zombie/core/SpriteRenderer.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/core/opengl/PZGLUtil.h"
#include "zombie/core/skinnedmodel/model/WorldItemAtlas/AtlasEntry.h"
#include "zombie/core/skinnedmodel/model/WorldItemAtlas/ItemParams.h"
#include "zombie/core/skinnedmodel/model/WorldItemAtlas/WeaponPartParams.h"
#include "zombie/core/skinnedmodel/shader/Shader.h"
#include "zombie/core/textures/Texture.h"
#include "zombie/core/textures/TextureDraw/GenericDrawer.h"
#include "zombie/core/textures/TextureFBO.h"
#include "zombie/debug/DebugOptions.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace model {


class WorldItemAtlas {
public:
    const ItemParams itemParams = std::make_shared<ItemParams>();
    AtlasEntry entry;
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
    static const Vector3f tempVector3f = std::make_shared<Vector3f>(0.0F, 5.0F, -2.0F);
    static const Matrix4f tempMatrix4f_1 = std::make_shared<Matrix4f>();
    static const Matrix4f tempMatrix4f_2 = std::make_shared<Matrix4f>();
   static const float[] xs = new float[8];
   static const float[] ys = new float[8];

   private WorldItemAtlas$RenderJob() {
   }

   public static WorldItemAtlas$RenderJob getNew() {
      return WorldItemAtlas.JobPool.empty() ? new WorldItemAtlas$RenderJob() : (WorldItemAtlas$RenderJob)WorldItemAtlas.JobPool.pop();
   }

   public WorldItemAtlas$RenderJob init(ItemParams var1, AtlasEntry var2) {
      this.itemParams.copyFrom(var1);
      this.entry = var2;
      this.bClearThisSlotOnly = false;
      this.entryW = 0;
      this.entryH = 0;
      this.done = 0;
      this.renderRefCount = 0;
    return this;
   }

    bool renderMain() {
    Model var1 = this.itemParams.m_model;
      return var1 != nullptr && var1.isReady() && var1.Mesh != nullptr && var1.Mesh.isReady();
   }

    void render() {
      if (this.done != 1) {
    Model var1 = this.itemParams.m_model;
         if (var1 != nullptr && var1.Mesh != nullptr && var1.Mesh.isReady()) {
    float var2 = 0.0F;
    float var3 = 0.0F;
            this.calcMatrices(this.m_projection, this.m_modelView, var2, var3);
            this.calcModelBounds(this.m_bounds);
            this.calcModelOffset();
            this.calcEntrySize();
            if (this.entryW > 0 && this.entryH > 0) {
               if (this.entryW <= 512 && this.entryH <= 512) {
                  WorldItemAtlas.instance.assignEntryToAtlas(this.entry, this.entryW, this.entryH);
                  GL11.glPushAttrib(1048575);
                  GL11.glPushClientAttrib(-1);
                  GL11.glDepthMask(true);
                  GL11.glColorMask(true, true, true, true);
                  GL11.glDisable(3089);
    TextureFBO var4 = WorldItemAtlas.instance.fbo;
                  if (var4.getTexture() != this.entry.atlas.tex) {
                     var4.setTexture(this.entry.atlas.tex);
                  }

                  var4.startDrawing(this.entry.atlas.clear, this.entry.atlas.clear);
                  if (this.entry.atlas.clear) {
                     this.entry.atlas.clear = false;
                  }

                  this.clearColorAndDepth();
    int var5 = this.entry.x - (int)this.entry.offsetX - (1024 - this.entry.w) / 2;
    int var6 = -((int)this.entry.offsetY) - (1024 - this.entry.h) / 2;
                  var6 += 512 - (this.entry.y + this.entry.h);
                  GL11.glViewport(var5, var6, 1024, 1024);
    bool var7 = this.renderModel(this.itemParams.m_model, nullptr);
                  if (this.itemParams.m_weaponParts != nullptr && !this.itemParams.m_weaponParts.empty()) {
                     for (int var8 = 0; var8 < this.itemParams.m_weaponParts.size(); var8++) {
    WeaponPartParams var9 = (WeaponPartParams)this.itemParams.m_weaponParts.get(var8);
                        if (!this.renderModel(var9.m_model, var9.m_transform)) {
                           var7 = false;
                           break;
                        }
                     }
                  }

                  var4.endDrawing();
                  if (!var7) {
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
         if (!$assertionsDisabled && this.renderRefCount <= 0) {
            throw std::make_unique<AssertionError>();
         } else {
            this.renderRefCount--;
         }
      }
   }

    void clearColorAndDepth() {
      GL11.glEnable(3089);
      GL11.glScissor(this.entry.x, 512 - (this.entry.y + this.entry.h), this.entry.w, this.entry.h);
      GL11.glClearColor(0.0F, 0.0F, 0.0F, 0.0F);
      GL11.glClear(16640);
      GL11.glClearColor(0.0F, 0.0F, 0.0F, 1.0F);
      this.restoreScreenStencil();
      GL11.glDisable(3089);
   }

    void restoreScreenStencil() {
    int var1 = SpriteRenderer.instance.getRenderingPlayerIndex();
    int var2 = var1 != 0 && var1 != 2 ? Core.getInstance().getOffscreenTrueWidth() / 2 : 0;
    int var3 = var1 != 0 && var1 != 1 ? Core.getInstance().getOffscreenTrueHeight() / 2 : 0;
    int var4 = Core.getInstance().getOffscreenTrueWidth();
    int var5 = Core.getInstance().getOffscreenTrueHeight();
      if (IsoPlayer.numPlayers > 1) {
         var4 /= 2;
      }

      if (IsoPlayer.numPlayers > 2) {
         var5 /= 2;
      }

      GL11.glScissor(var2, var3, var4, var5);
   }

    bool renderModel(Model var1, Matrix4f var2) {
      if (!var1.bStatic) {
    return false;
      } else {
         if (var1.Effect == nullptr) {
            var1.CreateShader("basicEffect");
         }

    Shader var3 = var1.Effect;
         if (var3 == nullptr || var1.Mesh == nullptr || !var1.Mesh.isReady()) {
    return false;
         } else if (var1.tex != nullptr && !var1.tex.isReady()) {
    return false;
         } else {
            PZGLUtil.pushAndLoadMatrix(5889, this.m_projection);
    Matrix4f var4 = tempMatrix4f_1.set(this.m_modelView);
    Matrix4f var5 = tempMatrix4f_2.set(this.itemParams.m_transform).invert();
            var4.mul(var5);
            PZGLUtil.pushAndLoadMatrix(5888, var4);
            GL11.glBlendFunc(770, 771);
            GL11.glDepthFunc(513);
            GL11.glDepthMask(true);
            GL11.glDepthRange(0.0, 1.0);
            GL11.glEnable(2929);
            GL11.glColor3f(1.0F, 1.0F, 1.0F);
            var3.Start();
            if (var1.tex == nullptr) {
               var3.setTexture(Texture.getErrorTexture(), "Texture", 0);
            } else {
               var3.setTexture(var1.tex, "Texture", 0);
            }

            var3.setDepthBias(0.0F);
            var3.setAmbient(this.itemParams.m_ambientR * 0.4F, this.itemParams.m_ambientG * 0.4F, this.itemParams.m_ambientB * 0.4F);
            var3.setLightingAmount(1.0F);
            var3.setHueShift(this.itemParams.m_hue);
            var3.setTint(this.itemParams.m_tintR, this.itemParams.m_tintG, this.itemParams.m_tintB);
            var3.setAlpha(this.itemParams.alpha);

            for (int var6 = 0; var6 < 5; var6++) {
               var3.setLight(var6, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, float.NaN, 0.0F, 0.0F, 0.0F, nullptr);
            }

    Vector3f var8 = tempVector3f;
            var8.x = 0.0F;
            var8.y = 5.0F;
            var8.z = -2.0F;
            var8.rotateY(this.itemParams.m_angle.y * (float) (Math.PI / 180.0));
    float var7 = 1.5F;
            var3.setLight(
               4,
               var8.x,
               var8.z,
               var8.y,
               this.itemParams.m_ambientR / 4.0F * var7,
               this.itemParams.m_ambientG / 4.0F * var7,
               this.itemParams.m_ambientB / 4.0F * var7,
               5000.0F,
               float.NaN,
               0.0F,
               0.0F,
               0.0F,
               nullptr
            );
            if (var2 == nullptr) {
               var3.setTransformMatrix(this.itemParams.m_transform, false);
            } else {
               tempMatrix4f_1.set(this.itemParams.m_transform);
               tempMatrix4f_1.mul(var2);
               var3.setTransformMatrix(tempMatrix4f_1, false);
            }

            var1.Mesh.Draw(var3);
            var3.End();
            if (Core.bDebug && DebugOptions.instance.ModelRenderAxis.getValue()) {
               Model.debugDrawAxis(0.0F, 0.0F, 0.0F, 0.5F, 1.0F);
            }

            PZGLUtil.popMatrix(5889);
            PZGLUtil.popMatrix(5888);
    return true;
         }
      }
   }

    void calcMatrices(Matrix4f var1, Matrix4f var2, float var3, float var4) {
      var1.setOrtho(-0.26666668F, 0.26666668F, 0.26666668F, -0.26666668F, -10.0F, 10.0F);
      var2.identity();
    float var5 = 0.047085002F;
      var2.scale(var5 * Core.TileScale / 2.0F);
    bool var6 = true;
      if (var6) {
         var2.rotate((float) (Math.PI / 6), 1.0F, 0.0F, 0.0F);
         var2.rotate((float) (Math.PI * 3.0 / 4.0), 0.0F, 1.0F, 0.0F);
      } else {
         var2.rotate((float) (Math.PI / 2), 0.0F, 1.0F, 0.0F);
      }

      var2.scale(-3.75F, 3.75F, 3.75F);
      var2.rotateXYZ(
         this.itemParams.m_angle.x * (float) (Math.PI / 180.0),
         this.itemParams.m_angle.y * (float) (Math.PI / 180.0),
         this.itemParams.m_angle.z * (float) (Math.PI / 180.0)
      );
      var2.translate(var3, 0.0F, var4);
      var2.mul(this.itemParams.m_transform);
   }

    void calcModelBounds(float[] var1) {
      var1[0] = float.MAX_VALUE;
      var1[1] = float.MAX_VALUE;
      var1[2] = -float.MAX_VALUE;
      var1[3] = -float.MAX_VALUE;
      this.calcModelBounds(this.itemParams.m_model, this.m_modelView, var1);
      if (this.itemParams.m_weaponParts != nullptr) {
         for (int var2 = 0; var2 < this.itemParams.m_weaponParts.size(); var2++) {
    WeaponPartParams var3 = (WeaponPartParams)this.itemParams.m_weaponParts.get(var2);
    Matrix4f var4 = tempMatrix4f_1.set(this.m_modelView).mul(var3.m_transform);
            this.calcModelBounds(var3.m_model, var4, var1);
         }
      }

    float var5 = 2.0F;
      var1[0] *= var5;
      var1[1] *= var5;
      var1[2] *= var5;
      var1[3] *= var5;
   }

    void calcModelBounds(Model var1, Matrix4f var2, float[] var3) {
    Vector3f var4 = var1.Mesh.minXYZ;
    Vector3f var5 = var1.Mesh.maxXYZ;
      xs[0] = var4.x;
      ys[0] = var4.y;
      xs[1] = var4.x;
      ys[1] = var5.y;
      xs[2] = var5.x;
      ys[2] = var5.y;
      xs[3] = var5.x;
      ys[3] = var4.y;

      for (int var6 = 0; var6 < 4; var6++) {
         this.sceneToUI(xs[var6], ys[var6], var4.z, this.m_projection, var2, this.m_scenePos);
         var3[0] = PZMath.min(var3[0], this.m_scenePos.x);
         var3[2] = PZMath.max(var3[2], this.m_scenePos.x);
         var3[1] = PZMath.min(var3[1], this.m_scenePos.y);
         var3[3] = PZMath.max(var3[3], this.m_scenePos.y);
         this.sceneToUI(xs[var6], ys[var6], var5.z, this.m_projection, var2, this.m_scenePos);
         var3[0] = PZMath.min(var3[0], this.m_scenePos.x);
         var3[2] = PZMath.max(var3[2], this.m_scenePos.x);
         var3[1] = PZMath.min(var3[1], this.m_scenePos.y);
         var3[3] = PZMath.max(var3[3], this.m_scenePos.y);
      }
   }

    void calcModelOffset() {
    float var1 = this.m_bounds[0];
    float var2 = this.m_bounds[1];
    float var3 = this.m_bounds[2];
    float var4 = this.m_bounds[3];
      this.entry.offsetX = var1 + (var3 - var1) / 2.0F - 512.0F;
      this.entry.offsetY = var2 + (var4 - var2) / 2.0F - 512.0F;
   }

    void calcEntrySize() {
    float var1 = this.m_bounds[0];
    float var2 = this.m_bounds[1];
    float var3 = this.m_bounds[2];
    float var4 = this.m_bounds[3];
    float var5 = 2.0F;
      var1 -= var5;
      var2 -= var5;
      var3 += var5;
      var4 += var5;
    uint8_t var6 = 16;
      var1 = (float)Math.floor(var1 / var6) * var6;
      var3 = (float)Math.ceil(var3 / var6) * var6;
      var2 = (float)Math.floor(var2 / var6) * var6;
      var4 = (float)Math.ceil(var4 / var6) * var6;
      this.entryW = (int)(var3 - var1);
      this.entryH = (int)(var4 - var2);
   }

    Vector3f sceneToUI(float var1, float var2, float var3, Matrix4f var4, Matrix4f var5, Vector3f var6) {
    Matrix4f var7 = this.m_matri4f;
      var7.set(var4);
      var7.mul(var5);
      this.m_viewport[0] = 0;
      this.m_viewport[1] = 0;
      this.m_viewport[2] = 512;
      this.m_viewport[3] = 512;
      var7.project(var1, var2, var3, this.m_viewport, var6);
    return var6;
   }

    void Reset() {
      this.itemParams.Reset();
      this.entry = nullptr;
   }
}
} // namespace model
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
