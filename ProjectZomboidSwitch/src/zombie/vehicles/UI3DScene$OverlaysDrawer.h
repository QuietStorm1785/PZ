#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <GL/glew.h>
#include "zombie/core/Core.h"
#include "zombie/core/opengl/PZGLUtil.h"
#include "zombie/core/textures/TextureDraw/GenericDrawer.h"
#include "zombie/vehicles/UI3DScene/AABB.h"
#include "zombie/vehicles/UI3DScene/Box3D.h"
#include "zombie/vehicles/UI3DScene/PositionRotation.h"
#include "zombie/vehicles/UI3DScene/StateData.h"

namespace zombie {
namespace vehicles {


class UI3DScene {
public:
   private UI3DScene$OverlaysDrawer(UI3DScene var1) {
      this.this$0 = var1;
   }

    void init() {
    StateData var1 = this.this$0.stateDataMain();
      UI3DScene.s_aabbPool.release(var1.m_aabb);
      var1.m_aabb.clear();

      for (int var2 = 0; var2 < this.this$0.m_aabb.size(); var2++) {
    AABB var3 = (AABB)this.this$0.m_aabb.get(var2);
         var1.m_aabb.push_back(((AABB)UI3DScene.s_aabbPool.alloc()).set(var3));
      }

      UI3DScene.s_box3DPool.release(var1.m_box3D);
      var1.m_box3D.clear();

      for (int var4 = 0; var4 < this.this$0.m_box3D.size(); var4++) {
    Box3D var6 = (Box3D)this.this$0.m_box3D.get(var4);
         var1.m_box3D.push_back(((Box3D)UI3DScene.s_box3DPool.alloc()).set(var6));
      }

      UI3DScene.s_posRotPool.release(var1.m_axes);
      var1.m_axes.clear();

      for (int var5 = 0; var5 < this.this$0.m_axes.size(); var5++) {
    PositionRotation var7 = (PositionRotation)this.this$0.m_axes.get(var5);
         var1.m_axes.push_back(((PositionRotation)UI3DScene.s_posRotPool.alloc()).set(var7));
      }
   }

    void render() {
    StateData var1 = this.this$0.stateDataRender();
      PZGLUtil.pushAndLoadMatrix(5889, var1.m_projection);
      PZGLUtil.pushAndLoadMatrix(5888, var1.m_modelView);
      GL11.glPushAttrib(2048);
      GL11.glViewport(
         this.this$0.getAbsoluteX().intValue(),
         Core.getInstance().getScreenHeight() - this.this$0.getAbsoluteY().intValue() - this.this$0.getHeight().intValue(),
         this.this$0.getWidth().intValue(),
         this.this$0.getHeight().intValue()
      );
      UI3DScene.vboLines.setOffset(0.0F, 0.0F, 0.0F);
      if (this.this$0.m_bDrawGrid) {
         this.this$0.renderGrid();
      }

      for (int var2 = 0; var2 < var1.m_aabb.size(); var2++) {
    AABB var3 = (AABB)var1.m_aabb.get(var2);
         this.this$0.renderAABB(var3.x, var3.y, var3.z, var3.w, var3.h, var3.L, var3.r, var3.g, var3.b);
      }

      for (int var4 = 0; var4 < var1.m_box3D.size(); var4++) {
    Box3D var6 = (Box3D)var1.m_box3D.get(var4);
         this.this$0.renderBox3D(var6.x, var6.y, var6.z, var6.w, var6.h, var6.L, var6.rx, var6.ry, var6.rz, var6.r, var6.g, var6.b);
      }

      for (int var5 = 0; var5 < var1.m_axes.size(); var5++) {
         this.this$0.renderAxis((PositionRotation)var1.m_axes.get(var5));
      }

      UI3DScene.vboLines.flush();
      if (var1.m_gizmo != nullptr) {
         var1.m_gizmo.render();
      }

      UI3DScene.vboLines.flush();
      GL11.glPopAttrib();
      PZGLUtil.popMatrix(5889);
      PZGLUtil.popMatrix(5888);
   }
}
} // namespace vehicles
} // namespace zombie
