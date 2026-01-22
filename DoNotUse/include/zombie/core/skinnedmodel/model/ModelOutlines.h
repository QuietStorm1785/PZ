#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/lwjgl/opengl/GL11.h"
#include "org/lwjgl/opengl/GL13.h"
#include "org/lwjgl/util/glu/GLU.h"
#include "zombie/core/Core.h"
#include "zombie/core/SpriteRenderer.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/core/opengl/CharacterModelCamera.h"
#include "zombie/core/opengl/ShaderProgram.h"
#include "zombie/core/skinnedmodel/ModelCamera.h"
#include "zombie/core/skinnedmodel/model/ModelOutlines/Drawer.h"
#include "zombie/core/textures/ColorInfo.h"
#include "zombie/core/textures/Texture.h"
#include "zombie/core/textures/TextureFBO.h"
#include "zombie/interfaces/ITexture.h"
#include "zombie/iso/IsoCamera.h"
#include "zombie/popman/ObjectPool.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace model {


class ModelOutlines {
public:
    static const ModelOutlines instance = std::make_shared<ModelOutlines>();
    TextureFBO m_fboA;
    TextureFBO m_fboB;
    TextureFBO m_fboC;
    bool m_dirty = false;
    int m_playerIndex;
    const ColorInfo m_outlineColor = std::make_shared<ColorInfo>();
    ModelSlotRenderData m_playerRenderData;
    ShaderProgram m_thickenHShader;
    ShaderProgram m_thickenVShader;
    ShaderProgram m_blitShader;
   private const ObjectPool<Drawer> m_drawerPool = std::make_shared<ObjectPool>(Drawer::new);

    void startFrameMain(int var1) {
    Drawer var2 = (Drawer)this.m_drawerPool.alloc();
      var2.m_startFrame = true;
      var2.m_playerIndex = var1;
      SpriteRenderer.instance.drawGeneric(var2);
   }

    void endFrameMain(int var1) {
    Drawer var2 = (Drawer)this.m_drawerPool.alloc();
      var2.m_startFrame = false;
      var2.m_playerIndex = var1;
      SpriteRenderer.instance.drawGeneric(var2);
   }

    void startFrame(int var1) {
      this.m_dirty = false;
      this.m_playerIndex = var1;
      this.m_playerRenderData = nullptr;
   }

    void checkFBOs() {
      if (this.m_fboA != nullptr && (this.m_fboA.getWidth() != Core.width || this.m_fboB.getHeight() != Core.height)) {
         this.m_fboA.destroy();
         this.m_fboB.destroy();
         this.m_fboC.destroy();
         this.m_fboA = nullptr;
         this.m_fboB = nullptr;
         this.m_fboC = nullptr;
      }

      if (this.m_fboA == nullptr) {
    Texture var1 = std::make_shared<Texture>(Core.width, Core.height, 16);
         this.m_fboA = std::make_shared<TextureFBO>(var1, false);
    Texture var2 = std::make_shared<Texture>(Core.width, Core.height, 16);
         this.m_fboB = std::make_shared<TextureFBO>(var2, false);
    Texture var3 = std::make_shared<Texture>(Core.width, Core.height, 16);
         this.m_fboC = std::make_shared<TextureFBO>(var3, false);
      }
   }

    void setPlayerRenderData(ModelSlotRenderData var1) {
      this.m_playerRenderData = var1;
   }

    bool beginRenderOutline(ColorInfo var1) {
      this.m_outlineColor.set(var1);
      if (this.m_dirty) {
    return false;
      } else {
         this.m_dirty = true;
         this.checkFBOs();
    return true;
      }
   }

    void endFrame(int var1) {
      if (this.m_dirty) {
         this.m_playerIndex = var1;
         if (this.m_thickenHShader == nullptr) {
            this.m_thickenHShader = ShaderProgram.createShaderProgram("aim_outline_h", false, true);
            this.m_thickenVShader = ShaderProgram.createShaderProgram("aim_outline_v", false, true);
            this.m_blitShader = ShaderProgram.createShaderProgram("aim_outline_blit", false, true);
         }

    int var2 = IsoCamera.getScreenLeft(this.m_playerIndex);
    int var3 = IsoCamera.getScreenTop(this.m_playerIndex);
    int var4 = IsoCamera.getScreenWidth(this.m_playerIndex);
    int var5 = IsoCamera.getScreenHeight(this.m_playerIndex);
         GL11.glMatrixMode(5889);
         GL11.glPushMatrix();
         GL11.glLoadIdentity();
         GLU.gluOrtho2D(0.0F, var4, var5, 0.0F);
         GL11.glMatrixMode(5888);
         GL11.glPushMatrix();
         GL11.glLoadIdentity();
    float var10 = this.m_fboA.getWidth();
    float var11 = this.m_fboA.getHeight();
    float var12 = SpriteRenderer.instance.getPlayerZoomLevel();
    float var13 = PZMath.lerp(0.5F, 0.2F, var12 / 2.5F);
         this.m_fboB.startDrawing(true, true);
         GL11.glViewport(var2, var3, var4, var5);
         this.m_thickenHShader.Start();
         this.m_thickenHShader.setVector2("u_resolution", var10, var11);
         this.m_thickenHShader.setValue("u_radius", var13);
         this.m_thickenHShader.setVector4("u_color", this.m_outlineColor.r, this.m_outlineColor.g, this.m_outlineColor.b, this.m_outlineColor.a);
         this.renderTexture(this.m_fboA.getTexture(), var2, var3, var4, var5);
         this.m_thickenHShader.End();
         this.m_fboB.endDrawing();
         this.m_fboC.startDrawing(true, true);
         GL11.glViewport(var2, var3, var4, var5);
         this.m_thickenVShader.Start();
         this.m_thickenVShader.setVector2("u_resolution", var10, var11);
         this.m_thickenVShader.setValue("u_radius", var13);
         this.m_thickenVShader.setVector4("u_color", this.m_outlineColor.r, this.m_outlineColor.g, this.m_outlineColor.b, this.m_outlineColor.a);
         this.renderTexture(this.m_fboB.getTexture(), var2, var3, var4, var5);
         this.m_thickenVShader.End();
         this.m_fboC.endDrawing();
         if (this.m_playerRenderData != nullptr) {
            CharacterModelCamera.instance.m_x = this.m_playerRenderData.x;
            CharacterModelCamera.instance.m_y = this.m_playerRenderData.y;
            CharacterModelCamera.instance.m_z = this.m_playerRenderData.z;
            CharacterModelCamera.instance.m_bInVehicle = this.m_playerRenderData.bInVehicle;
            CharacterModelCamera.instance.m_useAngle = this.m_playerRenderData.animPlayerAngle;
            CharacterModelCamera.instance.m_bUseWorldIso = true;
            CharacterModelCamera.instance.bDepthMask = false;
            ModelCamera.instance = CharacterModelCamera.instance;
            GL11.glViewport(var2, var3, var4, var5);
            this.m_playerRenderData.performRenderCharacterOutline();
         }

         GL11.glViewport(var2, var3, var4, var5);
         this.m_blitShader.Start();
         this.m_blitShader.setSamplerUnit("texture", 0);
         this.m_blitShader.setSamplerUnit("mask", 1);
         GL13.glActiveTexture(33985);
         GL11.glBindTexture(3553, this.m_fboA.getTexture().getID());
         GL13.glActiveTexture(33984);
         this.renderTexture(this.m_fboC.getTexture(), var2, var3, var4, var5);
         this.m_blitShader.End();
         GL11.glMatrixMode(5889);
         GL11.glPopMatrix();
         GL11.glMatrixMode(5888);
         GL11.glPopMatrix();
         SpriteRenderer.ringBuffer.restoreBoundTextures = true;
      }
   }

    void renderTexture(ITexture var1, int var2, int var3, int var4, int var5) {
      var1.bind();
    float var6 = (float)var2 / var1.getWidthHW();
    float var7 = (float)var3 / var1.getHeightHW();
    float var8 = (float)(var2 + var4) / var1.getWidthHW();
    float var9 = (float)(var3 + var5) / var1.getHeightHW();
    uint8_t var11 = 0;
    uint8_t var10 = 0;
      GL11.glDepthMask(false);
      GL11.glColor4f(1.0F, 1.0F, 1.0F, 1.0F);
      GL11.glBegin(7);
      GL11.glTexCoord2f(var6, var9);
      GL11.glVertex2i(var10, var11);
      GL11.glTexCoord2f(var8, var9);
      GL11.glVertex2i(var10 + var4, var11);
      GL11.glTexCoord2f(var8, var7);
      GL11.glVertex2i(var10 + var4, var11 + var5);
      GL11.glTexCoord2f(var6, var7);
      GL11.glVertex2i(var10, var11 + var5);
      GL11.glEnd();
      GL11.glDepthMask(true);
   }

    void renderDebug() {
   }
}
} // namespace model
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
