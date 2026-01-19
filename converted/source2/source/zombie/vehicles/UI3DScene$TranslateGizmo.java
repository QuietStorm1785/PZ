package zombie.vehicles;

import org.joml.Matrix4f;
import org.joml.Vector3f;
import org.lwjgl.opengl.GL11;
import org.lwjgl.util.glu.Cylinder;
import zombie.Lua.LuaManager;
import zombie.core.opengl.PZGLUtil;
import zombie.ui.UIManager;
import zombie.vehicles.UI3DScene.Axis;
import zombie.vehicles.UI3DScene.Gizmo;
import zombie.vehicles.UI3DScene.Ray;
import zombie.vehicles.UI3DScene.StateData;
import zombie.vehicles.UI3DScene.TransformMode;

final class UI3DScene$TranslateGizmo extends Gizmo {
   final Matrix4f m_startXfrm;
   final Matrix4f m_startInvXfrm;
   final Vector3f m_startPos;
   final Vector3f m_currentPos;
   Axis m_trackAxis;
   Cylinder cylinder;

   private UI3DScene$TranslateGizmo(UI3DScene var1) {
      super(var1);
      this.this$0 = var1;
      this.m_startXfrm = new Matrix4f();
      this.m_startInvXfrm = new Matrix4f();
      this.m_startPos = new Vector3f();
      this.m_currentPos = new Vector3f();
      this.m_trackAxis = Axis.None;
      this.cylinder = new Cylinder();
   }

   Axis hitTest(float var1, float var2) {
      if (!this.m_visible) {
         return Axis.None;
      } else {
         StateData var3 = this.this$0.stateDataMain();
         Matrix4f var4 = UI3DScene.allocMatrix4f();
         var4.set(var3.m_gizmoParentTransform);
         var4.mul(var3.m_gizmoOriginTransform);
         var4.mul(var3.m_gizmoChildTransform);
         var4.mul(var3.m_gizmoTransform);
         if (this.this$0.m_transformMode == TransformMode.Global) {
            var4.setRotationXYZ(0.0F, 0.0F, 0.0F);
         }

         var2 = this.this$0.screenHeight() - var2;
         Ray var5 = this.this$0.getCameraRay(var1, var2, UI3DScene.allocRay());
         Ray var6 = UI3DScene.allocRay();
         var4.transformPosition(var6.origin.set(0.0F, 0.0F, 0.0F));
         float var7 = this.this$0.m_gizmoScale / var3.zoomMult() * 1000.0F;
         float var8 = this.LENGTH * var7;
         float var9 = this.THICKNESS * var7;
         float var10 = 0.1F * var7;
         var4.transformDirection(var6.direction.set(1.0F, 0.0F, 0.0F)).normalize();
         float var11 = this.this$0.closest_distance_between_lines(var6, var5);
         float var12 = var6.t;
         float var13 = var5.t;
         if (var12 < var10 || var12 >= var10 + var8) {
            var12 = Float.MAX_VALUE;
            var11 = Float.MAX_VALUE;
         }

         float var14 = var6.direction.dot(var5.direction);
         var3.m_translateGizmoRenderData.m_hideX = Math.abs(var14) > 0.9F;
         var4.transformDirection(var6.direction.set(0.0F, 1.0F, 0.0F)).normalize();
         float var15 = this.this$0.closest_distance_between_lines(var6, var5);
         float var16 = var6.t;
         float var17 = var5.t;
         if (var16 < var10 || var16 >= var10 + var8) {
            var16 = Float.MAX_VALUE;
            var15 = Float.MAX_VALUE;
         }

         float var18 = var6.direction.dot(var5.direction);
         var3.m_translateGizmoRenderData.m_hideY = Math.abs(var18) > 0.9F;
         var4.transformDirection(var6.direction.set(0.0F, 0.0F, 1.0F)).normalize();
         float var19 = this.this$0.closest_distance_between_lines(var6, var5);
         float var20 = var6.t;
         float var21 = var5.t;
         if (var20 < var10 || var20 >= var10 + var8) {
            var20 = Float.MAX_VALUE;
            var19 = Float.MAX_VALUE;
         }

         float var22 = var6.direction.dot(var5.direction);
         var3.m_translateGizmoRenderData.m_hideZ = Math.abs(var22) > 0.9F;
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
      this.m_startXfrm.mul(var4.m_gizmoChildTransform);
      this.m_startXfrm.mul(var4.m_gizmoTransform);
      if (this.this$0.m_transformMode == TransformMode.Global) {
         this.m_startXfrm.setRotationXYZ(0.0F, 0.0F, 0.0F);
      }

      this.m_startInvXfrm.set(this.m_startXfrm);
      this.m_startInvXfrm.invert();
      this.m_trackAxis = var3;
      this.getPointOnAxis(var1, var2, var3, this.m_startXfrm, this.m_startPos);
   }

   void updateTracking(float var1, float var2) {
      Vector3f var3 = this.getPointOnAxis(var1, var2, this.m_trackAxis, this.m_startXfrm, UI3DScene.allocVector3f());
      if (this.m_currentPos.equals(var3)) {
         UI3DScene.releaseVector3f(var3);
      } else {
         UI3DScene.releaseVector3f(var3);
         this.m_currentPos.set(var3);
         StateData var4 = this.this$0.stateDataMain();
         Vector3f var5 = new Vector3f(this.m_currentPos).sub(this.m_startPos);
         if (this.this$0.m_transformMode == TransformMode.Global) {
            Vector3f var6 = this.m_startInvXfrm.transformPosition(this.m_startPos, UI3DScene.allocVector3f());
            Vector3f var7 = this.m_startInvXfrm.transformPosition(this.m_currentPos, UI3DScene.allocVector3f());
            Matrix4f var8 = UI3DScene.allocMatrix4f();
            var8.set(var4.m_gizmoParentTransform);
            var8.mul(var4.m_gizmoOriginTransform);
            var8.mul(var4.m_gizmoChildTransform);
            var8.invert();
            var8.transformPosition(var6);
            var8.transformPosition(var7);
            UI3DScene.releaseMatrix4f(var8);
            var5.set(var7).sub(var6);
            UI3DScene.releaseVector3f(var6);
            UI3DScene.releaseVector3f(var7);
         } else {
            Vector3f var9 = this.m_startInvXfrm.transformPosition(this.m_startPos, UI3DScene.allocVector3f());
            Vector3f var10 = this.m_startInvXfrm.transformPosition(this.m_currentPos, UI3DScene.allocVector3f());
            Matrix4f var11 = UI3DScene.allocMatrix4f();
            var11.set(var4.m_gizmoTransform);
            var11.transformPosition(var9);
            var11.transformPosition(var10);
            UI3DScene.releaseMatrix4f(var11);
            var5.set(var10).sub(var9);
            UI3DScene.releaseVector3f(var9);
            UI3DScene.releaseVector3f(var10);
         }

         var5.x = (float)Math.floor(var5.x * this.this$0.gridMult()) / this.this$0.gridMult();
         var5.y = (float)Math.floor(var5.y * this.this$0.gridMult()) / this.this$0.gridMult();
         var5.z = (float)Math.floor(var5.z * this.this$0.gridMult()) / this.this$0.gridMult();
         if (var4.m_selectedAttachmentIsChildAttachment) {
            var5.mul(-1.0F);
         }

         LuaManager.caller.pcall(UIManager.getDefaultThread(), this.this$0.getTable().rawget("onGizmoChanged"), new Object[]{this.this$0.table, var5});
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

         var1.m_modelView.mul(var2, var2);
         PZGLUtil.pushAndLoadMatrix(5888, var2);
         UI3DScene.releaseMatrix4f(var2);
         float var7 = this.this$0.m_gizmoScale / var1.zoomMult() * 1000.0F;
         float var4 = this.THICKNESS * var7;
         float var5 = this.LENGTH * var7;
         float var6 = 0.1F * var7;
         if (!var1.m_translateGizmoRenderData.m_hideX) {
            GL11.glColor3f(var1.m_gizmoAxis == Axis.X ? 1.0F : 0.5F, 0.0F, 0.0F);
            GL11.glRotated(90.0, 0.0, 1.0, 0.0);
            GL11.glTranslatef(0.0F, 0.0F, var6);
            this.cylinder.draw(var4 / 2.0F, var4 / 2.0F, var5, 8, 1);
            GL11.glTranslatef(0.0F, 0.0F, var5);
            this.cylinder.draw(var4 / 2.0F * 2.0F, 0.0F, 0.1F * var7, 8, 1);
            GL11.glTranslatef(0.0F, 0.0F, -var6 - var5);
            GL11.glRotated(-90.0, 0.0, 1.0, 0.0);
         }

         if (!var1.m_translateGizmoRenderData.m_hideY) {
            GL11.glColor3f(0.0F, var1.m_gizmoAxis == Axis.Y ? 1.0F : 0.5F, 0.0F);
            GL11.glRotated(-90.0, 1.0, 0.0, 0.0);
            GL11.glTranslatef(0.0F, 0.0F, var6);
            this.cylinder.draw(var4 / 2.0F, var4 / 2.0F, var5, 8, 1);
            GL11.glTranslatef(0.0F, 0.0F, var5);
            this.cylinder.draw(var4 / 2.0F * 2.0F, 0.0F, 0.1F * var7, 8, 1);
            GL11.glTranslatef(0.0F, 0.0F, -var6 - var5);
            GL11.glRotated(90.0, 1.0, 0.0, 0.0);
         }

         if (!var1.m_translateGizmoRenderData.m_hideZ) {
            GL11.glColor3f(0.0F, 0.0F, var1.m_gizmoAxis == Axis.Z ? 1.0F : 0.5F);
            GL11.glTranslatef(0.0F, 0.0F, var6);
            this.cylinder.draw(var4 / 2.0F, var4 / 2.0F, var5, 8, 1);
            GL11.glTranslatef(0.0F, 0.0F, var5);
            this.cylinder.draw(var4 / 2.0F * 2.0F, 0.0F, 0.1F * var7, 8, 1);
            GL11.glTranslatef(0.0F, 0.0F, -var6 - var5);
         }

         GL11.glColor3f(1.0F, 1.0F, 1.0F);
         PZGLUtil.popMatrix(5888);
         this.renderLineToOrigin();
      }
   }
}
