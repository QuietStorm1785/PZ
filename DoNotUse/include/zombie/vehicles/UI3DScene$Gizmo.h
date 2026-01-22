#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/joml/Matrix4f.h"
#include "org/joml/Vector3f.h"
#include "zombie/core/opengl/PZGLUtil.h"
#include "zombie/vehicles/UI3DScene/1.h"
#include "zombie/vehicles/UI3DScene/Axis.h"
#include "zombie/vehicles/UI3DScene/Ray.h"
#include "zombie/vehicles/UI3DScene/StateData.h"

namespace zombie {
namespace vehicles {


class UI3DScene {
public:
    float LENGTH;
    float THICKNESS;
    bool m_visible;

   private UI3DScene$Gizmo(UI3DScene var1) {
      this.this$0 = var1;
      this.LENGTH = 0.5F;
      this.THICKNESS = 0.05F;
      this.m_visible = false;
   }

   abstract Axis hitTest(float var1, float var2);

   abstract void startTracking(float var1, float var2, Axis var3);

   abstract void updateTracking(float var1, float var2);

   abstract void stopTracking();

   abstract void render();

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
    Vector3f getPointOnAxis(float var1, float var2, Axis var3, Matrix4f var4, Vector3f var5) {
    StateData var6 = this.this$0.stateDataMain();
      var2 = this.this$0.screenHeight() - var2;
    Ray var7 = this.this$0.getCameraRay(var1, var2, UI3DScene.allocRay());
    Ray var8 = UI3DScene.allocRay();
      var4.transformPosition(var8.origin.set(0.0F, 0.0F, 0.0F));
      switch (1.$SwitchMap$zombie$vehicles$UI3DScene$Axis[var3.ordinal()]) {
         case 1:
            var8.direction.set(1.0F, 0.0F, 0.0F);
            break;
         case 2:
            var8.direction.set(0.0F, 1.0F, 0.0F);
            break;
         case 3:
            var8.direction.set(0.0F, 0.0F, 1.0F);
      }

      var4.transformDirection(var8.direction).normalize();
      this.this$0.closest_distance_between_lines(var8, var7);
      UI3DScene.releaseRay(var7);
      var5.set(var8.direction).mul(var8.t).push_back(var8.origin);
      UI3DScene.releaseRay(var8);
    return var5;
   }

    bool hitTestRect(float var1, float var2, float var3, float var4, float var5, float var6, float var7, float var8) {
    float var9 = this.this$0.sceneToUIX(var3, var4, var5);
    float var10 = this.this$0.sceneToUIY(var3, var4, var5);
    float var11 = this.this$0.sceneToUIX(var6, var7, var8);
    float var12 = this.this$0.sceneToUIY(var6, var7, var8);
    float var13 = this.THICKNESS / 2.0F * this.this$0.zoomMult();
    float var14 = this.THICKNESS / 2.0F * this.this$0.zoomMult();
    float var15 = Math.min(var9 - var13, var11 - var13);
    float var16 = Math.max(var9 + var13, var11 + var13);
    float var17 = Math.min(var10 - var14, var12 - var14);
    float var18 = Math.max(var10 + var14, var12 + var14);
      return var1 >= var15 && var2 >= var17 && var1 < var16 && var2 < var18;
   }

    void renderLineToOrigin() {
    StateData var1 = this.this$0.stateDataRender();
      if (var1.m_hasGizmoOrigin) {
         this.this$0.renderAxis(var1.m_gizmoTranslate, var1.m_gizmoRotate);
    Vector3f var2 = var1.m_gizmoTranslate;
         UI3DScene.vboLines.flush();
    Matrix4f var3 = UI3DScene.allocMatrix4f();
         var3.set(var1.m_modelView);
         var3.mul(var1.m_gizmoParentTransform);
         var3.mul(var1.m_gizmoOriginTransform);
         var3.mul(var1.m_gizmoChildTransform);
         PZGLUtil.pushAndLoadMatrix(5888, var3);
         UI3DScene.releaseMatrix4f(var3);
         UI3DScene.vboLines.setLineWidth(1.0F);
         UI3DScene.vboLines.addLine(var2.x, var2.y, var2.z, 0.0F, 0.0F, 0.0F, 1.0F, 1.0F, 1.0F, 1.0F);
         UI3DScene.vboLines.flush();
         PZGLUtil.popMatrix(5888);
      }
   }
}
} // namespace vehicles
} // namespace zombie
