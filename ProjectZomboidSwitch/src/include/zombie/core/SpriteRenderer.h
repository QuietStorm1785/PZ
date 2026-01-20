#pragma once
#include <queue>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameProfiler.h"
#include "zombie/core/SpriteRenderer/RingBuffer.h"
#include "zombie/core/SpriteRenderer/WallShaderTexRender.h"
#include "zombie/core/SpriteRenderer/s_performance.h"
#include "zombie/core/Styles/AbstractStyle.h"
#include "zombie/core/Styles/AdditiveStyle.h"
#include "zombie/core/Styles/Style.h"
#include "zombie/core/Styles/TransparentStyle.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/core/opengl/GLState.h"
#include "zombie/core/opengl/RenderThread.h"
#include "zombie/core/opengl/Shader.h"
#include "zombie/core/skinnedmodel/ModelManager/ModelSlot.h"
#include "zombie/core/sprite/SpriteRenderState.h"
#include "zombie/core/sprite/SpriteRendererStates.h"
#include "zombie/core/textures/Texture.h"
#include "zombie/core/textures/TextureDraw.h"
#include "zombie/core/textures/TextureDraw/GenericDrawer.h"
#include "zombie/core/textures/TextureFBO.h"
#include "zombie/iso/IsoPuddles.h"
#include "zombie/iso/PlayerCamera.h"
#include <algorithm>

namespace zombie {
namespace core {


class SpriteRenderer {
public:
    static const SpriteRenderer instance = std::make_shared<SpriteRenderer>();
    static const int VERTEX_SIZE = 32;
    static const int TEXTURE0_COORD_OFFSET = 8;
    static const int TEXTURE1_COORD_OFFSET = 16;
    static const int TEXTURE2_ATTRIB_OFFSET = 24;
    static const int COLOR_OFFSET = 28;
    static const RingBuffer ringBuffer = std::make_shared<RingBuffer>();
    static const int NUM_RENDER_STATES = 3;
    const SpriteRendererStates m_states = std::make_shared<SpriteRendererStates>();
   private volatile boolean m_waitingForRenderState = false;
    static bool GL_BLENDFUNC_ENABLED = true;

    void create() {
      ringBuffer.create();
   }

    void clearSprites() {
      this.m_states.getPopulating().clear();
   }

    void glDepthMask(bool var1) {
      this.m_states.getPopulatingActiveState().glDepthMask(var1);
   }

   public void renderflipped(
      Texture var1, float var2, float var3, float var4, float var5, float var6, float var7, float var8, float var9, Consumer<TextureDraw> var10
   ) {
      this.m_states.getPopulatingActiveState().renderflipped(var1, var2, var3, var4, var5, var6, var7, var8, var9, var10);
   }

    void drawModel(ModelSlot var1) {
      this.m_states.getPopulatingActiveState().drawModel(var1);
   }

    void drawSkyBox(Shader var1, int var2, int var3, int var4) {
      this.m_states.getPopulatingActiveState().drawSkyBox(var1, var2, var3, var4);
   }

    void drawWater(Shader var1, int var2, int var3, bool var4) {
      this.m_states.getPopulatingActiveState().drawWater(var1, var2, var3, var4);
   }

    void drawPuddles(Shader var1, int var2, int var3, int var4) {
      this.m_states.getPopulatingActiveState().drawPuddles(var1, var2, var3, var4);
   }

    void drawParticles(int var1, int var2, int var3) {
      this.m_states.getPopulatingActiveState().drawParticles(var1, var2, var3);
   }

    void drawGeneric(GenericDrawer var1) {
      this.m_states.getPopulatingActiveState().drawGeneric(var1);
   }

    void glDisable(int var1) {
      this.m_states.getPopulatingActiveState().glDisable(var1);
   }

    void glEnable(int var1) {
      this.m_states.getPopulatingActiveState().glEnable(var1);
   }

    void glStencilMask(int var1) {
      this.m_states.getPopulatingActiveState().glStencilMask(var1);
   }

    void glClear(int var1) {
      this.m_states.getPopulatingActiveState().glClear(var1);
   }

    void glClearColor(int var1, int var2, int var3, int var4) {
      this.m_states.getPopulatingActiveState().glClearColor(var1, var2, var3, var4);
   }

    void glStencilFunc(int var1, int var2, int var3) {
      this.m_states.getPopulatingActiveState().glStencilFunc(var1, var2, var3);
   }

    void glStencilOp(int var1, int var2, int var3) {
      this.m_states.getPopulatingActiveState().glStencilOp(var1, var2, var3);
   }

    void glColorMask(int var1, int var2, int var3, int var4) {
      this.m_states.getPopulatingActiveState().glColorMask(var1, var2, var3, var4);
   }

    void glAlphaFunc(int var1, float var2) {
      this.m_states.getPopulatingActiveState().glAlphaFunc(var1, var2);
   }

    void glBlendFunc(int var1, int var2) {
      this.m_states.getPopulatingActiveState().glBlendFunc(var1, var2);
   }

    void glBlendFuncSeparate(int var1, int var2, int var3, int var4) {
      this.m_states.getPopulatingActiveState().glBlendFuncSeparate(var1, var2, var3, var4);
   }

    void glBlendEquation(int var1) {
      this.m_states.getPopulatingActiveState().glBlendEquation(var1);
   }

   public void render(
      Texture var1,
      double var2,
      double var4,
      double var6,
      double var8,
      double var10,
      double var12,
      double var14,
      double var16,
      float var18,
      float var19,
      float var20,
      float var21,
      Consumer<TextureDraw> var22
   ) {
      this.m_states.getPopulatingActiveState().render(var1, var2, var4, var6, var8, var10, var12, var14, var16, var18, var19, var20, var21, var22);
   }

   public void render(
      Texture var1,
      double var2,
      double var4,
      double var6,
      double var8,
      double var10,
      double var12,
      double var14,
      double var16,
      float var18,
      float var19,
      float var20,
      float var21,
      float var22,
      float var23,
      float var24,
      float var25,
      float var26,
      float var27,
      float var28,
      float var29,
      float var30,
      float var31,
      float var32,
      float var33,
      Consumer<TextureDraw> var34
   ) {
      this.m_states
         .getPopulatingActiveState()
         .render(
            var1,
            var2,
            var4,
            var6,
            var8,
            var10,
            var12,
            var14,
            var16,
            var18,
            var19,
            var20,
            var21,
            var22,
            var23,
            var24,
            var25,
            var26,
            var27,
            var28,
            var29,
            var30,
            var31,
            var32,
            var33,
            var34
         );
   }

   public void renderdebug(
      Texture var1,
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
      float var13,
      float var14,
      float var15,
      float var16,
      float var17,
      float var18,
      float var19,
      float var20,
      float var21,
      float var22,
      float var23,
      float var24,
      float var25,
      Consumer<TextureDraw> var26
   ) {
      this.m_states
         .getPopulatingActiveState()
         .renderdebug(
            var1,
            var2,
            var3,
            var4,
            var5,
            var6,
            var7,
            var8,
            var9,
            var10,
            var11,
            var12,
            var13,
            var14,
            var15,
            var16,
            var17,
            var18,
            var19,
            var20,
            var21,
            var22,
            var23,
            var24,
            var25,
            var26
         );
   }

    void renderline(Texture var1, int var2, int var3, int var4, int var5, float var6, float var7, float var8, float var9, int var10) {
      this.m_states.getPopulatingActiveState().renderline(var1, var2, var3, var4, var5, var6, var7, var8, var9, var10);
   }

    void renderline(Texture var1, int var2, int var3, int var4, int var5, float var6, float var7, float var8, float var9) {
      this.m_states.getPopulatingActiveState().renderline(var1, var2, var3, var4, var5, var6, var7, var8, var9);
   }

   public void render(
      Texture var1, float var2, float var3, float var4, float var5, float var6, float var7, float var8, float var9, int var10, int var11, int var12, int var13
   ) {
      this.m_states.getPopulatingActiveState().render(var1, var2, var3, var4, var5, var6, var7, var8, var9, var10, var11, var12, var13);
   }

    void render(Texture var1, float var2, float var3, float var4, float var5, float var6, float var7, float var8, float var9, Consumer<TextureDraw> var10) {
    float var11 = PZMath.floor(var2);
    float var12 = PZMath.floor(var3);
    float var13 = PZMath.ceil(var2 + var4);
    float var14 = PZMath.ceil(var3 + var5);
      this.m_states.getPopulatingActiveState().render(var1, var11, var12, var13 - var11, var14 - var12, var6, var7, var8, var9, var10);
   }

    void renderi(Texture var1, int var2, int var3, int var4, int var5, float var6, float var7, float var8, float var9, Consumer<TextureDraw> var10) {
      this.m_states.getPopulatingActiveState().render(var1, var2, var3, var4, var5, var6, var7, var8, var9, var10);
   }

   public void renderClamped(
      Texture var1,
      int var2,
      int var3,
      int var4,
      int var5,
      int var6,
      int var7,
      int var8,
      int var9,
      float var10,
      float var11,
      float var12,
      float var13,
      Consumer<TextureDraw> var14
   ) {
    int var15 = PZMath.clamp(var2, var6, var6 + var8);
    int var16 = PZMath.clamp(var3, var7, var7 + var9);
    int var17 = PZMath.clamp(var2 + var4, var6, var6 + var8);
    int var18 = PZMath.clamp(var3 + var5, var7, var7 + var9);
      if (var15 != var17 && var16 != var18) {
    int var19 = var15 - var2;
    int var20 = var2 + var4 - var17;
    int var21 = var16 - var3;
    int var22 = var3 + var5 - var18;
         if (var19 == 0 && var20 == 0 && var21 == 0 && var22 == 0) {
            this.m_states.getPopulatingActiveState().render(var1, var2, var3, var4, var5, var10, var11, var12, var13, var14);
         } else {
    float var23 = 0.0F;
    float var24 = 0.0F;
    float var25 = 1.0F;
    float var26 = 0.0F;
    float var27 = 1.0F;
    float var28 = 1.0F;
    float var29 = 0.0F;
    float var30 = 1.0F;
            if (var1 != nullptr) {
               var23 = (float)var19 / var4;
               var24 = (float)var21 / var5;
               var25 = (float)(var4 - var20) / var4;
               var26 = (float)var21 / var5;
               var27 = (float)(var4 - var20) / var4;
               var28 = (float)(var5 - var22) / var5;
               var29 = (float)var19 / var4;
               var30 = (float)(var5 - var22) / var5;
            }

            var4 = var17 - var15;
            var5 = var18 - var16;
            this.m_states
               .getPopulatingActiveState()
               .render(var1, var15, var16, var4, var5, var10, var11, var12, var13, var23, var24, var25, var26, var27, var28, var29, var30, var14);
         }
      }
   }

    void renderRect(int var1, int var2, int var3, int var4, float var5, float var6, float var7, float var8) {
      this.m_states.getPopulatingActiveState().renderRect(var1, var2, var3, var4, var5, var6, var7, var8);
   }

   public void renderPoly(
      float var1, float var2, float var3, float var4, float var5, float var6, float var7, float var8, float var9, float var10, float var11, float var12
   ) {
      this.m_states.getPopulatingActiveState().renderPoly(var1, var2, var3, var4, var5, var6, var7, var8, var9, var10, var11, var12);
   }

   public void renderPoly(
      Texture var1,
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
      this.m_states.getPopulatingActiveState().renderPoly(var1, var2, var3, var4, var5, var6, var7, var8, var9, var10, var11, var12, var13);
   }

   public void renderPoly(
      Texture var1,
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
      float var13,
      float var14,
      float var15,
      float var16,
      float var17,
      float var18,
      float var19,
      float var20,
      float var21
   ) {
      this.m_states
         .getPopulatingActiveState()
         .renderPoly(var1, var2, var3, var4, var5, var6, var7, var8, var9, var10, var11, var12, var13, var14, var15, var16, var17, var18, var19, var20, var21);
   }

   public void render(
      Texture var1,
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
      float var13,
      float var14,
      float var15,
      float var16,
      float var17
   ) {
      this.m_states
         .getPopulatingActiveState()
         .render(var1, var2, var3, var4, var5, var6, var7, var8, var9, var10, var11, var12, var13, var14, var15, var16, var17, nullptr);
   }

   public void render(
      Texture var1,
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
      float var13,
      float var14,
      float var15,
      float var16,
      float var17,
      Consumer<TextureDraw> var18
   ) {
      this.m_states
         .getPopulatingActiveState()
         .render(var1, var2, var3, var4, var5, var6, var7, var8, var9, var10, var11, var12, var13, var14, var15, var16, var17, var18);
   }

    static void buildDrawBuffer(TextureDraw[] var0, Style[] var1, int var2, RingBuffer var3) {
      for (int var4 = 0; var4 < var2; var4++) {
    TextureDraw var5 = var0[var4];
    Style var6 = var1[var4];
    TextureDraw var7 = nullptr;
         if (var4 > 0) {
            var7 = var0[var4 - 1];
         }

         var3.push_back(var5, var7, var6);
      }
   }

    void prePopulating() {
      this.m_states.getPopulating().prePopulating();
   }

    void postRender() {
    SpriteRenderState var1 = this.m_states.getRendering();
      if (var1.numSprites == 0 && var1.stateUI.numSprites == 0) {
         var1.onRendered();
      } else {
         TextureFBO.reset();
         IsoPuddles.VBOs.startFrame();
         GameProfiler.getInstance().invokeAndMeasure("buildStateUIDrawBuffer(UI)", this, var1, SpriteRenderer::buildStateUIDrawBuffer);
         GameProfiler.getInstance().invokeAndMeasure("buildStateDrawBuffer", this, var1, SpriteRenderer::buildStateDrawBuffer);
         var1.onRendered();
         Core.getInstance().setLastRenderedFBO(var1.fbo);
         this.notifyRenderStateQueue();
      }
   }

    void buildStateDrawBuffer(SpriteRenderState var1) {
      ringBuffer.begin();
      buildDrawBuffer(var1.sprite, var1.style, var1.numSprites, ringBuffer);
      GameProfiler.getInstance().invokeAndMeasure("ringBuffer.render", () -> ringBuffer.render());
   }

    void buildStateUIDrawBuffer(SpriteRenderState var1) {
      if (var1.stateUI.numSprites > 0) {
         ringBuffer.begin();
         var1.stateUI.bActive = true;
         buildDrawBuffer(var1.stateUI.sprite, var1.stateUI.style, var1.stateUI.numSprites, ringBuffer);
         ringBuffer.render();
      }

      var1.stateUI.bActive = false;
   }

    void notifyRenderStateQueue() {
      /* synchronized - TODO: add std::mutex */ (this.m_states) {
         this.m_states.notifyAll();
      }
   }

    void glBuffer(int var1, int var2) {
      this.m_states.getPopulatingActiveState().glBuffer(var1, var2);
   }

    void glDoStartFrame(int var1, int var2, float var3, int var4) {
      this.m_states.getPopulatingActiveState().glDoStartFrame(var1, var2, var3, var4);
   }

    void glDoStartFrame(int var1, int var2, float var3, int var4, bool var5) {
      this.m_states.getPopulatingActiveState().glDoStartFrame(var1, var2, var3, var4, var5);
   }

    void glDoStartFrameFx(int var1, int var2, int var3) {
      this.m_states.getPopulatingActiveState().glDoStartFrameFx(var1, var2, var3);
   }

    void glIgnoreStyles(bool var1) {
      this.m_states.getPopulatingActiveState().glIgnoreStyles(var1);
   }

    void glDoEndFrame() {
      this.m_states.getPopulatingActiveState().glDoEndFrame();
   }

    void glDoEndFrameFx(int var1) {
      this.m_states.getPopulatingActiveState().glDoEndFrameFx(var1);
   }

    void doCoreIntParam(int var1, float var2) {
      this.m_states.getPopulatingActiveState().doCoreIntParam(var1, var2);
   }

    void glTexParameteri(int var1, int var2, int var3) {
      this.m_states.getPopulatingActiveState().glTexParameteri(var1, var2, var3);
   }

    void StartShader(int var1, int var2) {
      this.m_states.getPopulatingActiveState().StartShader(var1, var2);
   }

    void EndShader() {
      this.m_states.getPopulatingActiveState().EndShader();
   }

    void setCutawayTexture(Texture var1, int var2, int var3, int var4, int var5) {
      this.m_states.getPopulatingActiveState().setCutawayTexture(var1, var2, var3, var4, var5);
   }

    void clearCutawayTexture() {
      this.m_states.getPopulatingActiveState().clearCutawayTexture();
   }

    void setUseVertColorsArray(uint8_t var1, int var2, int var3, int var4, int var5) {
      this.m_states.getPopulatingActiveState().setUseVertColorsArray(var1, var2, var3, var4, var5);
   }

    void clearUseVertColorsArray() {
      this.m_states.getPopulatingActiveState().clearUseVertColorsArray();
   }

    void setExtraWallShaderParams(WallShaderTexRender var1) {
      this.m_states.getPopulatingActiveState().setExtraWallShaderParams(var1);
   }

    void ShaderUpdate1i(int var1, int var2, int var3) {
      this.m_states.getPopulatingActiveState().ShaderUpdate1i(var1, var2, var3);
   }

    void ShaderUpdate1f(int var1, int var2, float var3) {
      this.m_states.getPopulatingActiveState().ShaderUpdate1f(var1, var2, var3);
   }

    void ShaderUpdate2f(int var1, int var2, float var3, float var4) {
      this.m_states.getPopulatingActiveState().ShaderUpdate2f(var1, var2, var3, var4);
   }

    void ShaderUpdate3f(int var1, int var2, float var3, float var4, float var5) {
      this.m_states.getPopulatingActiveState().ShaderUpdate3f(var1, var2, var3, var4, var5);
   }

    void ShaderUpdate4f(int var1, int var2, float var3, float var4, float var5, float var6) {
      this.m_states.getPopulatingActiveState().ShaderUpdate4f(var1, var2, var3, var4, var5, var6);
   }

    void glLoadIdentity() {
      this.m_states.getPopulatingActiveState().glLoadIdentity();
   }

    void glGenerateMipMaps(int var1) {
      this.m_states.getPopulatingActiveState().glGenerateMipMaps(var1);
   }

    void glBind(int var1) {
      this.m_states.getPopulatingActiveState().glBind(var1);
   }

    void glViewport(int var1, int var2, int var3, int var4) {
      this.m_states.getPopulatingActiveState().glViewport(var1, var2, var3, var4);
   }

    void startOffscreenUI() {
      this.m_states.getPopulating().stateUI.bActive = true;
      this.m_states.getPopulating().stateUI.defaultStyle = TransparentStyle.instance;
      GLState.startFrame();
   }

    void stopOffscreenUI() {
      this.m_states.getPopulating().stateUI.bActive = false;
   }

    void pushFrameDown() {
      /* synchronized - TODO: add std::mutex */ (this.m_states) {
         this.waitForReadySlotToOpen();
         this.m_states.movePopulatingToReady();
         this.notifyRenderStateQueue();
      }
   }

    SpriteRenderState acquireStateForRendering(BooleanSupplier var1) {
      /* synchronized - TODO: add std::mutex */ (this.m_states) {
         if (!this.waitForReadyState(var1)) {
    return nullptr;
         } else {
            this.m_states.moveReadyToRendering();
            this.notifyRenderStateQueue();
            return this.m_states.getRendering();
         }
      }
   }

    bool waitForReadyState(BooleanSupplier var1) {
    bool var2;
      try {
         s_performance.waitForReadyState.start();
         var2 = this.waitForReadyStateInternal(var1);
      } finally {
         s_performance.waitForReadyState.end();
      }

    return var2;
   }

    bool waitForReadyStateInternal(BooleanSupplier var1) {
      if (RenderThread.isRunning() && this.m_states.getReady() == nullptr) {
         if (!RenderThread.isWaitForRenderState() && !this.isWaitingForRenderState()) {
    return false;
         } else {
            while (this.m_states.getReady() == nullptr) {
               try {
                  if (!var1.getAsBoolean()) {
    return false;
                  }

                  this.m_states.wait();
               } catch (InterruptedException var3) {
               }
            }

    return true;
         }
      } else {
    return true;
      }
   }

    void waitForReadySlotToOpen() {
      try {
         s_performance.waitForReadySlotToOpen.start();
         this.waitForReadySlotToOpenInternal();
      } finally {
         s_performance.waitForReadySlotToOpen.end();
      }
   }

    void waitForReadySlotToOpenInternal() {
      if (this.m_states.getReady() != nullptr && RenderThread.isRunning()) {
         this.m_waitingForRenderState = true;

         while (this.m_states.getReady() != nullptr) {
            try {
               this.m_states.wait();
            } catch (InterruptedException var2) {
            }
         }

         this.m_waitingForRenderState = false;
      }
   }

    int getMainStateIndex() {
      return this.m_states.getPopulatingActiveState().index;
   }

    int getRenderStateIndex() {
      return this.m_states.getRenderingActiveState().index;
   }

    bool getDoAdditive() {
      return this.m_states.getPopulatingActiveState().defaultStyle == AdditiveStyle.instance;
   }

    void setDefaultStyle(AbstractStyle var1) {
      this.m_states.getPopulatingActiveState().defaultStyle = var1;
   }

    void setDoAdditive(bool var1) {
      this.m_states.getPopulatingActiveState().defaultStyle = (AbstractStyle)(var1 ? AdditiveStyle.instance : TransparentStyle.instance);
   }

    void initFromIsoCamera(int var1) {
      this.m_states.getPopulating().playerCamera[var1].initFromIsoCamera(var1);
   }

    void setRenderingPlayerIndex(int var1) {
      this.m_states.getRendering().playerIndex = var1;
   }

    int getRenderingPlayerIndex() {
      return this.m_states.getRendering().playerIndex;
   }

    PlayerCamera getRenderingPlayerCamera(int var1) {
      return this.m_states.getRendering().playerCamera[var1];
   }

    SpriteRenderState getRenderingState() {
      return this.m_states.getRendering();
   }

    SpriteRenderState getPopulatingState() {
      return this.m_states.getPopulating();
   }

    bool isMaxZoomLevel() {
      return this.getPlayerZoomLevel() >= this.getPlayerMaxZoom();
   }

    bool isMinZoomLevel() {
      return this.getPlayerZoomLevel() <= this.getPlayerMinZoom();
   }

    float getPlayerZoomLevel() {
    SpriteRenderState var1 = this.m_states.getRendering();
    int var2 = var1.playerIndex;
      return var1.zoomLevel[var2];
   }

    float getPlayerMaxZoom() {
    SpriteRenderState var1 = this.m_states.getRendering();
      return var1.maxZoomLevel;
   }

    float getPlayerMinZoom() {
    SpriteRenderState var1 = this.m_states.getRendering();
      return var1.minZoomLevel;
   }

    bool isWaitingForRenderState() {
      return this.m_waitingForRenderState;
   }
}
} // namespace core
} // namespace zombie
