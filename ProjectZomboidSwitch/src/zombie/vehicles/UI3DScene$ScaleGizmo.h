#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <GL/glew.h>
#include "org/lwjgl/util/glu/Cylinder.h"
#include "zombie/Lua/LuaManager.h"
#include "zombie/core/opengl/PZGLUtil.h"
#include "zombie/ui/UIManager.h"
#include "zombie/vehicles/UI3DScene/Axis.h"
#include "zombie/vehicles/UI3DScene/Gizmo.h"
#include "zombie/vehicles/UI3DScene/Ray.h"
#include "zombie/vehicles/UI3DScene/StateData.h"
#include "zombie/vehicles/UI3DScene/TransformMode.h"

namespace zombie {
namespace vehicles {


class UI3DScene {
public:
    const Matrix4f m_startXfrm;
    const Matrix4f m_startInvXfrm;
    const Vector3f m_startPos;
    const Vector3f m_currentPos;
    Axis m_trackAxis;
    bool m_hideX;
    bool m_hideY;
    bool m_hideZ;
    const Cylinder cylinder;

   private UI3DScene$ScaleGizmo(UI3DScene var1) {
      super(var1);
      this.this$0 = var1;
      this.m_startXfrm = std::make_unique<Matrix4f>();
      this.m_startInvXfrm = std::make_unique<Matrix4f>();
      this.m_startPos = std::make_unique<Vector3f>();
      this.m_currentPos = std::make_unique<Vector3f>();
      this.m_trackAxis = Axis.None;
      this.cylinder = std::make_unique<Cylinder>();
   }

    Axis hitTest(float var1, float var2) {
      if (!this.m_visible) {
         return Axis.None;
      } else {
    StateData var3 = this.this$0.stateDataMain();
    Matrix4f var4 = UI3DScene.allocMatrix4f();
         var4.set(var3.m_gizmoParentTransform);
         var4.mul(var3.m_gizmoOriginTransform);
         var4.mul(var3.m_gizmoTransform);
         if (this.this$0.m_transformMode == TransformMode.Global) {
            var4.setRotationXYZ(0.0F, 0.0F, 0.0F);
         }

         var2 = this.this$0.screenHeight() - var2;
    Ray var5 = this.this$0.getCameraRay(var1, var2, UI3DScene.allocRay());
    Ray var6 = UI3DScene.allocRay();
         var4.transformProject(var6.origin.set(0.0F, 0.0F, 0.0F));
    float var7 = this.this$0.m_gizmoScale / var3.zoomMult() * 1000.0F;
    float var8 = this.LENGTH * var7;
    float var9 = this.THICKNESS * var7;
    float var10 = 0.1F * var7;
         var4.transformDirection(var6.direction.set(1.0F, 0.0F, 0.0F)).normalize();
    float var11 = this.this$0.closest_distance_between_lines(var6, var5);
    float var12 = var6.t;
    float var13 = var5.t;
         if (var12 < var10 || var12 >= var10 + var8) {
            var12 = float.MAX_VALUE;
            var11 = float.MAX_VALUE;
         }

    float var14 = var6.direction.dot(var5.direction);
         this.m_hideX = Math.abs(var14) > 0.9F;
         var4.transformDirection(var6.direction.set(0.0F, 1.0F, 0.0F)).normalize();
    float var15 = this.this$0.closest_distance_between_lines(var6, var5);
    float var16 = var6.t;
    float var17 = var5.t;
         if (var16 < var10 || var16 >= var10 + var8) {
            var16 = float.MAX_VALUE;
            var15 = float.MAX_VALUE;
         }

    float var18 = var6.direction.dot(var5.direction);
         this.m_hideY = Math.abs(var18) > 0.9F;
         var4.transformDirection(var6.direction.set(0.0F, 0.0F, 1.0F)).normalize();
    float var19 = this.this$0.closest_distance_between_lines(var6, var5);
    float var20 = var6.t;
    float var21 = var5.t;
         if (var20 < var10 || var20 >= var10 + var8) {
            var20 = float.MAX_VALUE;
            var19 = float.MAX_VALUE;
         }

    float var22 = var6.direction.dot(var5.direction);
         this.m_hideZ = Math.abs(var22) > 0.9F;
         UI3DScene.releaseRay(var6);
         UI3DScene.releaseRay(var5);
         UI3DScene.releaseMatrix4f(var4);
         if (var12 >= var10 && var12 < var10 + var8 && var11 < var15 && var11 < var19) {
            return var11 <= var9 / 2.0F ? Axis.X : Axis.None;
         } else if (var16 >= var10 && var16 < var10 + var8 && var15 < var11 && var15 < var19) {
            return var15 <= var9 / 2.0F ? Axis.Y : Axis.None;
         } else if (var20 >= var10 && var20 < var10 + var8 && var19 < var11 && var19 < var15) {
            return var19 <= var9 / 2.0F ? Axis.Z : Axis.None;
         } else {
            return Axis.None;
         }
      }
   }

    void startTracking(float var1, float var2, Axis var3) {
    StateData var4 = this.this$0.stateDataMain();
      this.m_startXfrm.set(var4.m_gizmoParentTransform);
      this.m_startXfrm.mul(var4.m_gizmoOriginTransform);
      this.m_startXfrm.mul(var4.m_gizmoTransform);
      this.m_startXfrm.setRotationXYZ(0.0F, 0.0F, 0.0F);
      this.m_startInvXfrm.set(this.m_startXfrm);
      this.m_startInvXfrm.invert();
      this.m_trackAxis = var3;
      this.getPointOnAxis(var1, var2, var3, this.m_startXfrm, this.m_startPos);
   }

    void updateTracking(float var1, float var2) {
    Vector3f var3 = this.getPointOnAxis(var1, var2, this.m_trackAxis, this.m_startXfrm, UI3DScene.allocVector3f());
      if (this.m_currentPos == var3)) {
         UI3DScene.releaseVector3f(var3);
      } else {
         UI3DScene.releaseVector3f(var3);
         this.m_currentPos.set(var3);
    StateData var4 = this.this$0.stateDataMain();
    Vector3f var5 = std::make_shared<Vector3f>(this.m_currentPos).sub(this.m_startPos);
         if (this.this$0.m_transformMode == TransformMode.Global) {
    Vector3f var6 = this.m_startInvXfrm.transformPosition(this.m_startPos, std::make_shared<Vector3f>());
    Vector3f var7 = this.m_startInvXfrm.transformPosition(this.m_currentPos, std::make_shared<Vector3f>());
    Matrix4f var8 = std::make_shared<Matrix4f>(var4.m_gizmoParentTransform).invert();
            var8.transformPosition(var6);
            var8.transformPosition(var7);
            var5.set(var7).sub(var6);
         } else {
    Vector3f var9 = this.m_startInvXfrm.transformPosition(this.m_startPos, std::make_shared<Vector3f>());
    Vector3f var10 = this.m_startInvXfrm.transformPosition(this.m_currentPos, std::make_shared<Vector3f>());
            var5.set(var10).sub(var9);
         }

         var5.x = (float)Math.floor(var5.x * this.this$0.gridMult()) / this.this$0.gridMult();
         var5.y = (float)Math.floor(var5.y * this.this$0.gridMult()) / this.this$0.gridMult();
         var5.z = (float)Math.floor(var5.z * this.this$0.gridMult()) / this.this$0.gridMult();
         LuaManager.caller.pcall(UIManager.getDefaultThread(), this.this$0.getTable().rawget("onGizmoChanged"), new Object[]{this.this$0.table, var5});
      }
   }

    void stopTracking() {
      this.m_trackAxis = Axis.None;
   }

    void render() {
      if (this.m_visible) {
    StateData var1 = this.this$0.stateDataRender();
    float var2 = this.this$0.m_gizmoScale / var1.zoomMult() * 1000.0F;
    float var3 = this.LENGTH * var2;
    float var4 = this.THICKNESS * var2;
    float var5 = 0.1F * var2;
    Matrix4f var6 = UI3DScene.allocMatrix4f();
         var6.set(var1.m_gizmoParentTransform);
         var6.mul(var1.m_gizmoOriginTransform);
         var6.mul(var1.m_gizmoChildTransform);
         var6.mul(var1.m_gizmoTransform);
         if (this.this$0.m_transformMode == TransformMode.Global) {
            var6.setRotationXYZ(0.0F, 0.0F, 0.0F);
         }

         var1.m_modelView.mul(var6, var6);
         PZGLUtil.pushAndLoadMatrix(5888, var6);
         UI3DScene.releaseMatrix4f(var6);
         if (!this.m_hideX) {
            GL11.glColor3f(var1.m_gizmoAxis == Axis.X ? 1.0F : 0.5F, 0.0F, 0.0F);
            GL11.glRotated(90.0, 0.0, 1.0, 0.0);
            GL11.glTranslatef(0.0F, 0.0F, var5);
            this.cylinder.draw(var4 / 2.0F, var4 / 2.0F, var3, 8, 1);
            GL11.glTranslatef(0.0F, 0.0F, var3);
            this.cylinder.draw(var4, var4, 0.1F * var2, 8, 1);
            GL11.glTranslatef(0.0F, 0.0F, -var5 - var3);
            GL11.glRotated(-90.0, 0.0, 1.0, 0.0);
         }

         if (!this.m_hideY) {
            GL11.glColor3f(0.0F, var1.m_gizmoAxis == Axis.Y ? 1.0F : 0.5F, 0.0F);
            GL11.glRotated(-90.0, 1.0, 0.0, 0.0);
            GL11.glTranslatef(0.0F, 0.0F, var5);
            this.cylinder.draw(var4 / 2.0F, var4 / 2.0F, var3, 8, 1);
            GL11.glTranslatef(0.0F, 0.0F, var3);
            this.cylinder.draw(var4, var4, 0.1F * var2, 8, 1);
            GL11.glTranslatef(0.0F, 0.0F, -var5 - var3);
            GL11.glRotated(90.0, 1.0, 0.0, 0.0);
         }

         if (!this.m_hideZ) {
            GL11.glColor3f(0.0F, 0.0F, var1.m_gizmoAxis == Axis.Z ? 1.0F : 0.5F);
            GL11.glTranslatef(0.0F, 0.0F, var5);
            this.cylinder.draw(var4 / 2.0F, var4 / 2.0F, var3, 8, 1);
            GL11.glTranslatef(0.0F, 0.0F, var3);
            this.cylinder.draw(var4, var4, 0.1F * var2, 8, 1);
            GL11.glTranslatef(0.0F, 0.0F, -0.1F - var3);
         }

         GL11.glColor3f(1.0F, 1.0F, 1.0F);
         PZGLUtil.popMatrix(5888);
         this.renderLineToOrigin();
      }
   }
}
} // namespace vehicles
} // namespace zombie
