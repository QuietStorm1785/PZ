#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/joml/Matrix4f.h"
#include "org/joml/Quaternionf.h"
#include "org/joml/Vector3f.h"
#include "org/lwjgl/opengl/GL11.h"
#include "zombie/Lua/LuaManager.h"
#include "zombie/input/Mouse.h"
#include "zombie/iso/IsoUtils.h"
#include "zombie/iso/Vector2.h"
#include "zombie/ui/UIManager.h"
#include "zombie/vehicles/BaseVehicle/Vector3fObjectPool.h"
#include "zombie/vehicles/UI3DScene/1.h"
#include "zombie/vehicles/UI3DScene/Axis.h"
#include "zombie/vehicles/UI3DScene/Circle.h"
#include "zombie/vehicles/UI3DScene/Gizmo.h"
#include "zombie/vehicles/UI3DScene/Ray.h"
#include "zombie/vehicles/UI3DScene/SceneCharacter.h"
#include "zombie/vehicles/UI3DScene/StateData.h"
#include "zombie/vehicles/UI3DScene/TransformMode.h"

namespace zombie {
namespace vehicles {


class UI3DScene {
public:
    Axis m_trackAxis;
    const Circle m_trackCircle;
    const Matrix4f m_startXfrm;
    const Matrix4f m_startInvXfrm;
    const Vector3f m_startPointOnCircle;
    const Vector3f m_currentPointOnCircle;
   const std::vector<Vector3f> m_circlePointsMain;
   const std::vector<Vector3f> m_circlePointsRender;

   private UI3DScene$RotateGizmo(UI3DScene var1) {
      super(var1);
      this.this$0 = var1;
      this.m_trackAxis = Axis.None;
      this.m_trackCircle = std::make_unique<Circle>();
      this.m_startXfrm = std::make_unique<Matrix4f>();
      this.m_startInvXfrm = std::make_unique<Matrix4f>();
      this.m_startPointOnCircle = std::make_unique<Vector3f>();
      this.m_currentPointOnCircle = std::make_unique<Vector3f>();
      this.m_circlePointsMain = std::make_unique<std::vector<>>();
      this.m_circlePointsRender = std::make_unique<std::vector<>>();
   }

    Axis hitTest(float var1, float var2) {
      if (!this.m_visible) {
         return Axis.None;
      } else {
    StateData var3 = this.this$0.stateDataMain();
         var2 = this.this$0.screenHeight() - var2;
    Ray var4 = this.this$0.getCameraRay(var1, var2, UI3DScene.allocRay());
    Matrix4f var5 = UI3DScene.allocMatrix4f();
         var5.set(var3.m_gizmoParentTransform);
         var5.mul(var3.m_gizmoOriginTransform);
         var5.mul(var3.m_gizmoChildTransform);
         var5.mul(var3.m_gizmoTransform);
    Vector3f var6 = var5.getScale(UI3DScene.allocVector3f());
         var5.scale(1.0F / var6.x, 1.0F / var6.y, 1.0F / var6.z);
         UI3DScene.releaseVector3f(var6);
         if (this.this$0.m_transformMode == TransformMode.Global) {
            var5.setRotationXYZ(0.0F, 0.0F, 0.0F);
         }

    float var18 = this.this$0.m_gizmoScale / var3.zoomMult() * 1000.0F;
    float var7 = this.LENGTH * var18;
    Vector3f var8 = var5.transformProject(UI3DScene.allocVector3f().set(0.0F, 0.0F, 0.0F));
    Vector3f var9 = var5.transformDirection(UI3DScene.allocVector3f().set(1.0F, 0.0F, 0.0F)).normalize();
    Vector3f var10 = var5.transformDirection(UI3DScene.allocVector3f().set(0.0F, 1.0F, 0.0F)).normalize();
    Vector3f var11 = var5.transformDirection(UI3DScene.allocVector3f().set(0.0F, 0.0F, 1.0F)).normalize();
    Vector2 var12 = UI3DScene.allocVector2();
         this.getCircleSegments(var8, var7, var10, var11, this.m_circlePointsMain);
    float var13 = this.hitTestCircle(var4, this.m_circlePointsMain, var12);
         ((Vector3fObjectPool)BaseVehicle.TL_vector3f_pool.get()).release(this.m_circlePointsMain);
         this.m_circlePointsMain.clear();
         this.getCircleSegments(var8, var7, var9, var11, this.m_circlePointsMain);
    float var14 = this.hitTestCircle(var4, this.m_circlePointsMain, var12);
         ((Vector3fObjectPool)BaseVehicle.TL_vector3f_pool.get()).release(this.m_circlePointsMain);
         this.m_circlePointsMain.clear();
         this.getCircleSegments(var8, var7, var9, var10, this.m_circlePointsMain);
    float var15 = this.hitTestCircle(var4, this.m_circlePointsMain, var12);
         ((Vector3fObjectPool)BaseVehicle.TL_vector3f_pool.get()).release(this.m_circlePointsMain);
         this.m_circlePointsMain.clear();
         UI3DScene.releaseVector2(var12);
         UI3DScene.releaseVector3f(var9);
         UI3DScene.releaseVector3f(var10);
         UI3DScene.releaseVector3f(var11);
         UI3DScene.releaseVector3f(var8);
         UI3DScene.releaseRay(var4);
         UI3DScene.releaseMatrix4f(var5);
    float var16 = 8.0F;
         if (var13 < var14 && var13 < var15) {
            return var13 <= var16 ? Axis.X : Axis.None;
         } else if (var14 < var13 && var14 < var15) {
            return var14 <= var16 ? Axis.Y : Axis.None;
         } else if (var15 < var13 && var15 < var14) {
            return var15 <= var16 ? Axis.Z : Axis.None;
         } else {
            return Axis.None;
         }
      }
   }

    void startTracking(float var1, float var2, Axis var3) {
    StateData var4 = this.this$0.stateDataMain();
      this.m_startXfrm.set(var4.m_gizmoParentTransform);
      this.m_startXfrm.mul(var4.m_gizmoOriginTransform);
      this.m_startXfrm.mul(var4.m_gizmoChildTransform);
      this.m_startXfrm.mul(var4.m_gizmoTransform);
      if (this.this$0.m_transformMode == TransformMode.Global) {
         this.m_startXfrm.setRotationXYZ(0.0F, 0.0F, 0.0F);
      }

      this.m_startInvXfrm.set(var4.m_gizmoParentTransform);
      this.m_startInvXfrm.mul(var4.m_gizmoOriginTransform);
      this.m_startInvXfrm.mul(var4.m_gizmoChildTransform);
      this.m_startInvXfrm.mul(var4.m_gizmoTransform);
      this.m_startInvXfrm.invert();
      this.m_trackAxis = var3;
      this.getPointOnAxis(var1, var2, var3, this.m_trackCircle, this.m_startXfrm, this.m_startPointOnCircle);
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
    void updateTracking(float var1, float var2) {
    Vector3f var3 = this.getPointOnAxis(var1, var2, this.m_trackAxis, this.m_trackCircle, this.m_startXfrm, UI3DScene.allocVector3f());
      if (this.m_currentPointOnCircle == var3)) {
         UI3DScene.releaseVector3f(var3);
      } else {
         this.m_currentPointOnCircle.set(var3);
         UI3DScene.releaseVector3f(var3);
    float var4 = this.calculateRotation(this.m_startPointOnCircle, this.m_currentPointOnCircle, this.m_trackCircle);
         switch (1.$SwitchMap$zombie$vehicles$UI3DScene$Axis[this.m_trackAxis.ordinal()]) {
            case 1:
               this.m_trackCircle.orientation.set(1.0F, 0.0F, 0.0F);
               break;
            case 2:
               this.m_trackCircle.orientation.set(0.0F, 1.0F, 0.0F);
               break;
            case 3:
               this.m_trackCircle.orientation.set(0.0F, 0.0F, 1.0F);
         }

    Vector3f var5 = UI3DScene.allocVector3f().set(this.m_trackCircle.orientation);
         if (this.this$0.m_transformMode == TransformMode.Global) {
            this.m_startInvXfrm.transformDirection(var5);
         }

    Ray var6 = this.this$0.getCameraRay(var1, var2, UI3DScene.allocRay());
    Vector3f var7 = this.m_startXfrm.transformDirection(UI3DScene.allocVector3f().set(var5)).normalize();
    float var8 = var6.direction.dot(var7);
         UI3DScene.releaseVector3f(var7);
         UI3DScene.releaseRay(var6);
         if (this.this$0.dynamic_cast<SceneCharacter*>(m_gizmoParent) != nullptr) {
            if (var8 > 0.0F) {
               var4 *= -1.0F;
            }
         } else if (var8 < 0.0F) {
            var4 *= -1.0F;
         }

    Quaternionf var9 = UI3DScene.allocQuaternionf().fromAxisAngleDeg(var5, var4);
         UI3DScene.releaseVector3f(var5);
         var7 = var9.getEulerAnglesXYZ(std::make_unique<Vector3f>());
         UI3DScene.releaseQuaternionf(var9);
         var7.x = (float)Math.floor(var7.x * (180.0F / (float)Math.PI) + 0.5F);
         var7.y = (float)Math.floor(var7.y * (180.0F / (float)Math.PI) + 0.5F);
         var7.z = (float)Math.floor(var7.z * (180.0F / (float)Math.PI) + 0.5F);
         LuaManager.caller.pcall(UIManager.getDefaultThread(), this.this$0.getTable().rawget("onGizmoChanged"), new Object[]{this.this$0.table, var7});
      }
   }

    void stopTracking() {
      this.m_trackAxis = Axis.None;
   }

    void render() {
      if (this.m_visible) {
    StateData var1 = this.this$0.stateDataRender();
    Matrix4f var2 = UI3DScene.allocMatrix4f();
         var2.set(var1.m_gizmoParentTransform);
         var2.mul(var1.m_gizmoOriginTransform);
         var2.mul(var1.m_gizmoChildTransform);
         var2.mul(var1.m_gizmoTransform);
    Vector3f var3 = var2.getScale(UI3DScene.allocVector3f());
         var2.scale(1.0F / var3.x, 1.0F / var3.y, 1.0F / var3.z);
         UI3DScene.releaseVector3f(var3);
         if (this.this$0.m_transformMode == TransformMode.Global) {
            var2.setRotationXYZ(0.0F, 0.0F, 0.0F);
         }

    float var16 = Mouse.getXA() - this.this$0.getAbsoluteX().intValue();
    float var4 = Mouse.getYA() - this.this$0.getAbsoluteY().intValue();
    Ray var5 = this.this$0.getCameraRay(var16, this.this$0.screenHeight() - var4, var1.m_projection, var1.m_modelView, UI3DScene.allocRay());
    float var6 = this.this$0.m_gizmoScale / var1.zoomMult() * 1000.0F;
    float var7 = this.LENGTH * var6;
    Vector3f var8 = var2.transformProject(UI3DScene.allocVector3f().set(0.0F, 0.0F, 0.0F));
    Vector3f var9 = var2.transformDirection(UI3DScene.allocVector3f().set(1.0F, 0.0F, 0.0F)).normalize();
    Vector3f var10 = var2.transformDirection(UI3DScene.allocVector3f().set(0.0F, 1.0F, 0.0F)).normalize();
    Vector3f var11 = var2.transformDirection(UI3DScene.allocVector3f().set(0.0F, 0.0F, 1.0F)).normalize();
         GL11.glClear(256);
         GL11.glEnable(2929);
    Axis var12 = this.m_trackAxis == Axis.None ? var1.m_gizmoAxis : this.m_trackAxis;
         if (this.m_trackAxis == Axis.None || this.m_trackAxis == Axis.X) {
    float var13 = var12 == Axis.X ? 1.0F : 0.5F;
    float var14 = 0.0F;
    float var15 = 0.0F;
            this.renderAxis(var8, var7, var10, var11, var13, var14, var15, var5);
         }

         if (this.m_trackAxis == Axis.None || this.m_trackAxis == Axis.Y) {
    float var17 = 0.0F;
    float var19 = var12 == Axis.Y ? 1.0F : 0.5F;
    float var21 = 0.0F;
            this.renderAxis(var8, var7, var9, var11, var17, var19, var21, var5);
         }

         if (this.m_trackAxis == Axis.None || this.m_trackAxis == Axis.Z) {
    float var18 = 0.0F;
    float var20 = 0.0F;
    float var22 = var12 == Axis.Z ? 1.0F : 0.5F;
            this.renderAxis(var8, var7, var9, var10, var18, var20, var22, var5);
         }

         UI3DScene.releaseVector3f(var8);
         UI3DScene.releaseVector3f(var9);
         UI3DScene.releaseVector3f(var10);
         UI3DScene.releaseVector3f(var11);
         UI3DScene.releaseRay(var5);
         UI3DScene.releaseMatrix4f(var2);
         GL11.glColor3f(1.0F, 1.0F, 1.0F);
         this.renderLineToOrigin();
      }
   }

    void getCircleSegments(Vector3f var1, float var2, Vector3f var3, Vector3f var4, std::vector<Vector3f> var5) {
    Vector3f var6 = UI3DScene.allocVector3f();
    Vector3f var7 = UI3DScene.allocVector3f();
    uint8_t var8 = 32;
    double var9 = 0.0 / var8 * (float) (Math.PI / 180.0);
    double var11 = Math.cos(var9);
    double var13 = Math.sin(var9);
      var3.mul((float)var11, var6);
      var4.mul((float)var13, var7);
      var6.push_back(var7).mul(var2);
      var5.push_back(UI3DScene.allocVector3f().set(var1).push_back(var6));

      for (int var15 = 1; var15 <= var8; var15++) {
         var9 = var15 * 360.0 / var8 * (float) (Math.PI / 180.0);
         var11 = Math.cos(var9);
         var13 = Math.sin(var9);
         var3.mul((float)var11, var6);
         var4.mul((float)var13, var7);
         var6.push_back(var7).mul(var2);
         var5.push_back(UI3DScene.allocVector3f().set(var1).push_back(var6));
      }

      UI3DScene.releaseVector3f(var6);
      UI3DScene.releaseVector3f(var7);
   }

    float hitTestCircle(Ray var1, std::vector<Vector3f> var2, Vector2 var3) {
    Ray var4 = UI3DScene.allocRay();
    Vector3f var5 = UI3DScene.allocVector3f();
    float var6 = this.this$0.sceneToUIX(var1.origin.x, var1.origin.y, var1.origin.z);
    float var7 = this.this$0.sceneToUIY(var1.origin.x, var1.origin.y, var1.origin.z);
    float var8 = float.MAX_VALUE;
    Vector3f var9 = (Vector3f)var2.get(0);

      for (int var10 = 1; var10 < var2.size(); var10++) {
    Vector3f var11 = (Vector3f)var2.get(var10);
    float var12 = this.this$0.sceneToUIX(var9.x, var9.y, var9.z);
    float var13 = this.this$0.sceneToUIY(var9.x, var9.y, var9.z);
    float var14 = this.this$0.sceneToUIX(var11.x, var11.y, var11.z);
    float var15 = this.this$0.sceneToUIY(var11.x, var11.y, var11.z);
    double var16 = Math.pow(var14 - var12, 2.0) + Math.pow(var15 - var13, 2.0);
         if (var16 < 0.001) {
            var9 = var11;
         } else {
    double var18 = ((var6 - var12) * (var14 - var12) + (var7 - var13) * (var15 - var13)) / var16;
    double var20 = var12 + var18 * (var14 - var12);
    double var22 = var13 + var18 * (var15 - var13);
            if (var18 <= 0.0) {
               var20 = var12;
               var22 = var13;
            } else if (var18 >= 1.0) {
               var20 = var14;
               var22 = var15;
            }

    float var24 = IsoUtils.DistanceTo2D(var6, var7, (float)var20, (float)var22);
            if (var24 < var8) {
               var8 = var24;
               var3.set((float)var20, (float)var22);
            }

            var9 = var11;
         }
      }

      UI3DScene.releaseVector3f(var5);
      UI3DScene.releaseRay(var4);
    return var8;
   }

    void renderAxis(Vector3f var1, float var2, Vector3f var3, Vector3f var4, float var5, float var6, float var7, Ray var8) {
      UI3DScene.vboLines.flush();
      UI3DScene.vboLines.setLineWidth(6.0F);
      this.getCircleSegments(var1, var2, var3, var4, this.m_circlePointsRender);
    Vector3f var9 = UI3DScene.allocVector3f();
    Vector3f var10 = this.m_circlePointsRender.get(0);

      for (int var11 = 1; var11 < this.m_circlePointsRender.size(); var11++) {
    Vector3f var12 = this.m_circlePointsRender.get(var11);
         var9.set(var12.x - var1.x, var12.y - var1.y, var12.z - var1.z).normalize();
    float var13 = var9.dot(var8.direction);
         if (var13 < 0.1F) {
            UI3DScene.vboLines.addLine(var10.x, var10.y, var10.z, var12.x, var12.y, var12.z, var5, var6, var7, 1.0F);
         } else {
            UI3DScene.vboLines.addLine(var10.x, var10.y, var10.z, var12.x, var12.y, var12.z, var5 / 2.0F, var6 / 2.0F, var7 / 2.0F, 0.25F);
         }

         var10 = var12;
      }

      ((Vector3fObjectPool)BaseVehicle.TL_vector3f_pool.get()).release(this.m_circlePointsRender);
      this.m_circlePointsRender.clear();
      UI3DScene.releaseVector3f(var9);
      UI3DScene.vboLines.flush();
   }

    Vector3f getPointOnAxis(float var1, float var2, Axis var3, Circle var4, Matrix4f var5, Vector3f var6) {
    float var7 = 1.0F;
      var4.radius = this.LENGTH * var7;
      var5.getTranslation(var4.center);
    float var8 = this.this$0.sceneToUIX(var4.center.x, var4.center.y, var4.center.z);
    float var9 = this.this$0.sceneToUIY(var4.center.x, var4.center.y, var4.center.z);
      var4.center.set(var8, var9, 0.0F);
      var4.orientation.set(0.0F, 0.0F, 1.0F);
    Ray var10 = UI3DScene.allocRay();
      var10.origin.set(var1, var2, 0.0F);
      var10.direction.set(0.0F, 0.0F, -1.0F);
      this.this$0.closest_distance_line_circle(var10, var4, var6);
      UI3DScene.releaseRay(var10);
    return var6;
   }

    float calculateRotation(Vector3f var1, Vector3f var2, Circle var3) {
      if (var1 == var2)) {
         return 0.0F;
      } else {
    Vector3f var4 = UI3DScene.allocVector3f().set(var1).sub(var3.center).normalize();
    Vector3f var5 = UI3DScene.allocVector3f().set(var2).sub(var3.center).normalize();
    float var6 = (float)Math.acos(var5.dot(var4));
    Vector3f var7 = var4.cross(var5, UI3DScene.allocVector3f());
    int var8 = (int)Math.signum(var7.dot(var3.orientation));
         UI3DScene.releaseVector3f(var4);
         UI3DScene.releaseVector3f(var5);
         UI3DScene.releaseVector3f(var7);
         return var8 * var6 * (180.0F / (float)Math.PI);
      }
   }
}
} // namespace vehicles
} // namespace zombie
