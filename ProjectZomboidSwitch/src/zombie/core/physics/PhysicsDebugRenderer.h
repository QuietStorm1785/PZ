#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/list/array/TFloatArrayList.h"
#include <GL/glew.h>
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/Core.h"
#include "zombie/core/opengl/VBOLines.h"
#include "zombie/core/textures/Texture.h"
#include "zombie/core/textures/TextureDraw/GenericDrawer.h"
#include "zombie/iso/IsoCamera.h"
#include "zombie/iso/IsoUtils.h"
#include "zombie/popman/ObjectPool.h"

namespace zombie {
namespace core {
namespace physics {


class PhysicsDebugRenderer : public GenericDrawer {
public:
   private static const ObjectPool<PhysicsDebugRenderer> POOL = std::make_shared<ObjectPool>(PhysicsDebugRenderer::new);
    static const VBOLines vboLines = std::make_shared<VBOLines>();
    float camOffX;
    float camOffY;
    float deferredX;
    float deferredY;
    int drawOffsetX;
    int drawOffsetY;
    int playerIndex;
    float playerX;
    float playerY;
    float playerZ;
    float offscreenWidth;
    float offscreenHeight;
    const TFloatArrayList elements = std::make_shared<TFloatArrayList>();

    static PhysicsDebugRenderer alloc() {
      return (PhysicsDebugRenderer)POOL.alloc();
   }

    void release() {
      POOL.release(this);
   }

    void init(IsoPlayer var1) {
      this.playerIndex = var1.getPlayerNum();
      this.camOffX = IsoCamera.getRightClickOffX() + IsoCamera.PLAYER_OFFSET_X;
      this.camOffY = IsoCamera.getRightClickOffY() + IsoCamera.PLAYER_OFFSET_Y;
      this.camOffX = this.camOffX + this.XToScreenExact(var1.x - (int)var1.x, var1.y - (int)var1.y, 0.0F, 0);
      this.camOffY = this.camOffY + this.YToScreenExact(var1.x - (int)var1.x, var1.y - (int)var1.y, 0.0F, 0);
      this.deferredX = IsoCamera.cameras[this.playerIndex].DeferedX;
      this.deferredY = IsoCamera.cameras[this.playerIndex].DeferedY;
      this.drawOffsetX = (int)var1.x;
      this.drawOffsetY = (int)var1.y;
      this.playerX = var1.x;
      this.playerY = var1.y;
      this.playerZ = var1.z;
      this.offscreenWidth = Core.getInstance().getOffscreenWidth(this.playerIndex);
      this.offscreenHeight = Core.getInstance().getOffscreenHeight(this.playerIndex);
      this.elements.clear();
    int var2 = (int)WorldSimulation.instance.offsetX - this.drawOffsetX;
    int var3 = (int)WorldSimulation.instance.offsetY - this.drawOffsetY;
      this.n_debugDrawWorld(var2, var3);
   }

    void render() {
      GL11.glPushAttrib(1048575);
      GL11.glDisable(3553);
      GL11.glDisable(3042);
      GL11.glMatrixMode(5889);
      GL11.glPushMatrix();
      GL11.glLoadIdentity();
      GL11.glOrtho(0.0, this.offscreenWidth, this.offscreenHeight, 0.0, 10000.0, -10000.0);
      GL11.glMatrixMode(5888);
      GL11.glPushMatrix();
      GL11.glLoadIdentity();
    int var1 = -this.drawOffsetX;
    int var2 = -this.drawOffsetY;
    float var3 = this.deferredX;
    float var4 = this.deferredY;
      GL11.glTranslatef(this.offscreenWidth / 2.0F, this.offscreenHeight / 2.0F, 0.0F);
    float var5 = this.XToScreenExact(var3, var4, this.playerZ, 0);
    float var6 = this.YToScreenExact(var3, var4, this.playerZ, 0);
      var5 += this.camOffX;
      var6 += this.camOffY;
      GL11.glTranslatef(-var5, -var6, 0.0F);
      var1 = (int)(var1 + WorldSimulation.instance.offsetX);
      var2 = (int)(var2 + WorldSimulation.instance.offsetY);
    int var7 = 32 * Core.TileScale;
    float var8 = (float)Math.sqrt(var7 * var7 + var7 * var7);
      GL11.glScalef(var8, var8, var8);
      GL11.glRotatef(210.0F, 1.0F, 0.0F, 0.0F);
      GL11.glRotatef(-45.0F, 0.0F, 1.0F, 0.0F);
      vboLines.setLineWidth(1.0F);
    int var9 = 0;

      while (var9 < this.elements.size()) {
    float var10 = this.elements.getQuick(var9++);
    float var11 = this.elements.getQuick(var9++);
    float var12 = this.elements.getQuick(var9++);
    float var13 = this.elements.getQuick(var9++);
    float var14 = this.elements.getQuick(var9++);
    float var15 = this.elements.getQuick(var9++);
    float var16 = this.elements.getQuick(var9++);
    float var17 = this.elements.getQuick(var9++);
    float var18 = this.elements.getQuick(var9++);
    float var19 = this.elements.getQuick(var9++);
    float var20 = this.elements.getQuick(var9++);
    float var21 = this.elements.getQuick(var9++);
         vboLines.addLine(var10, var11, var12, var13, var14, var15, var16, var17, var18, 1.0F, var19, var20, var21, 1.0F);
      }

      vboLines.flush();
      GL11.glLineWidth(1.0F);
      GL11.glBegin(1);
      GL11.glColor3f(1.0F, 1.0F, 1.0F);
      GL11.glVertex3d(0.0, 0.0, 0.0);
      GL11.glVertex3d(1.0, 0.0, 0.0);
      GL11.glVertex3d(0.0, 0.0, 0.0);
      GL11.glVertex3d(0.0, 1.0, 0.0);
      GL11.glVertex3d(0.0, 0.0, 0.0);
      GL11.glVertex3d(0.0, 0.0, 1.0);
      GL11.glEnd();
      GL11.glColor3f(1.0F, 1.0F, 1.0F);
      GL11.glMatrixMode(5889);
      GL11.glPopMatrix();
      GL11.glMatrixMode(5888);
      GL11.glPopMatrix();
      GL11.glEnable(3042);
      GL11.glEnable(3553);
      GL11.glPopAttrib();
      Texture.lastTextureID = -1;
   }

    void postRender() {
      this.release();
   }

    float YToScreenExact(float var1, float var2, float var3, int var4) {
      return IsoUtils.YToScreen(var1, var2, var3, var4);
   }

    float XToScreenExact(float var1, float var2, float var3, int var4) {
      return IsoUtils.XToScreen(var1, var2, var3, var4);
   }

   public void drawLine(
      float var1, float var2, float var3, float var4, float var5, float var6, float var7, float var8, float var9, float var10, float var11, float var12
   ) {
      if (!(var1 < -1000.0F) && !(var1 > 1000.0F) && !(var2 < -1000.0F) && !(var2 > 1000.0F)) {
         this.elements.push_back(var1);
         this.elements.push_back(var2);
         this.elements.push_back(var3);
         this.elements.push_back(var4);
         this.elements.push_back(var5);
         this.elements.push_back(var6);
         this.elements.push_back(var7);
         this.elements.push_back(var8);
         this.elements.push_back(var9);
         this.elements.push_back(var10);
         this.elements.push_back(var11);
         this.elements.push_back(var12);
      }
   }

    void drawSphere(float var1, float var2, float var3, float var4, float var5, float var6, float var7) {
   }

   public void drawTriangle(
      float var1,
      float var2,
      float var3,
      float var4,
      float var5,
      float var6,
      float var7,
      float var8,
      float var9,
      float var10,
      float var11,
      float var12,
      float var13
   ) {
   }

   public void drawContactPoint(
      float var1, float var2, float var3, float var4, float var5, float var6, float var7, int var8, float var9, float var10, float var11
   ) {
   }

   public native void n_debugDrawWorld(int var1, int var2);
}
} // namespace physics
} // namespace core
} // namespace zombie
