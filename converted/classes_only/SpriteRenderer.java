package zombie.core;

import java.util.function.BooleanSupplier;
import java.util.function.Consumer;
import zombie.GameProfiler;
import zombie.core.SpriteRenderer.RingBuffer;
import zombie.core.SpriteRenderer.WallShaderTexRender;
import zombie.core.SpriteRenderer.s_performance;
import zombie.core.Styles.AbstractStyle;
import zombie.core.Styles.AdditiveStyle;
import zombie.core.Styles.Style;
import zombie.core.Styles.TransparentStyle;
import zombie.core.math.PZMath;
import zombie.core.opengl.GLState;
import zombie.core.opengl.RenderThread;
import zombie.core.opengl.Shader;
import zombie.core.skinnedmodel.ModelManager.ModelSlot;
import zombie.core.sprite.SpriteRenderState;
import zombie.core.sprite.SpriteRendererStates;
import zombie.core.textures.Texture;
import zombie.core.textures.TextureDraw;
import zombie.core.textures.TextureFBO;
import zombie.core.textures.TextureDraw.GenericDrawer;
import zombie.iso.IsoPuddles;
import zombie.iso.PlayerCamera;

public final class SpriteRenderer {
   public static final SpriteRenderer instance = new SpriteRenderer();
   static final int VERTEX_SIZE = 32;
   static final int TEXTURE0_COORD_OFFSET = 8;
   static final int TEXTURE1_COORD_OFFSET = 16;
   static final int TEXTURE2_ATTRIB_OFFSET = 24;
   static final int COLOR_OFFSET = 28;
   public static final RingBuffer ringBuffer = new RingBuffer();
   public static final int NUM_RENDER_STATES = 3;
   public final SpriteRendererStates m_states = new SpriteRendererStates();
   private volatile boolean m_waitingForRenderState = false;
   public static boolean GL_BLENDFUNC_ENABLED = true;

   public void create() {
      ringBuffer.create();
   }

   public void clearSprites() {
      this.m_states.getPopulating().clear();
   }

   public void glDepthMask(boolean var1) {
      this.m_states.getPopulatingActiveState().glDepthMask(var1);
   }

   public void renderflipped(
      Texture var1, float var2, float var3, float var4, float var5, float var6, float var7, float var8, float var9, Consumer<TextureDraw> var10
   ) {
      this.m_states.getPopulatingActiveState().renderflipped(var1, var2, var3, var4, var5, var6, var7, var8, var9, var10);
   }

   public void drawModel(ModelSlot var1) {
      this.m_states.getPopulatingActiveState().drawModel(var1);
   }

   public void drawSkyBox(Shader var1, int var2, int var3, int var4) {
      this.m_states.getPopulatingActiveState().drawSkyBox(var1, var2, var3, var4);
   }

   public void drawWater(Shader var1, int var2, int var3, boolean var4) {
      this.m_states.getPopulatingActiveState().drawWater(var1, var2, var3, var4);
   }

   public void drawPuddles(Shader var1, int var2, int var3, int var4) {
      this.m_states.getPopulatingActiveState().drawPuddles(var1, var2, var3, var4);
   }

   public void drawParticles(int var1, int var2, int var3) {
      this.m_states.getPopulatingActiveState().drawParticles(var1, var2, var3);
   }

   public void drawGeneric(GenericDrawer var1) {
      this.m_states.getPopulatingActiveState().drawGeneric(var1);
   }

   public void glDisable(int var1) {
      this.m_states.getPopulatingActiveState().glDisable(var1);
   }

   public void glEnable(int var1) {
      this.m_states.getPopulatingActiveState().glEnable(var1);
   }

   public void glStencilMask(int var1) {
      this.m_states.getPopulatingActiveState().glStencilMask(var1);
   }

   public void glClear(int var1) {
      this.m_states.getPopulatingActiveState().glClear(var1);
   }

   public void glClearColor(int var1, int var2, int var3, int var4) {
      this.m_states.getPopulatingActiveState().glClearColor(var1, var2, var3, var4);
   }

   public void glStencilFunc(int var1, int var2, int var3) {
      this.m_states.getPopulatingActiveState().glStencilFunc(var1, var2, var3);
   }

   public void glStencilOp(int var1, int var2, int var3) {
      this.m_states.getPopulatingActiveState().glStencilOp(var1, var2, var3);
   }

   public void glColorMask(int var1, int var2, int var3, int var4) {
      this.m_states.getPopulatingActiveState().glColorMask(var1, var2, var3, var4);
   }

   public void glAlphaFunc(int var1, float var2) {
      this.m_states.getPopulatingActiveState().glAlphaFunc(var1, var2);
   }

   public void glBlendFunc(int var1, int var2) {
      this.m_states.getPopulatingActiveState().glBlendFunc(var1, var2);
   }

   public void glBlendFuncSeparate(int var1, int var2, int var3, int var4) {
      this.m_states.getPopulatingActiveState().glBlendFuncSeparate(var1, var2, var3, var4);
   }

   public void glBlendEquation(int var1) {
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

   public void renderline(Texture var1, int var2, int var3, int var4, int var5, float var6, float var7, float var8, float var9, int var10) {
      this.m_states.getPopulatingActiveState().renderline(var1, var2, var3, var4, var5, var6, var7, var8, var9, var10);
   }

   public void renderline(Texture var1, int var2, int var3, int var4, int var5, float var6, float var7, float var8, float var9) {
      this.m_states.getPopulatingActiveState().renderline(var1, var2, var3, var4, var5, var6, var7, var8, var9);
   }

   public void render(
      Texture var1, float var2, float var3, float var4, float var5, float var6, float var7, float var8, float var9, int var10, int var11, int var12, int var13
   ) {
      this.m_states.getPopulatingActiveState().render(var1, var2, var3, var4, var5, var6, var7, var8, var9, var10, var11, var12, var13);
   }

   public void render(Texture var1, float var2, float var3, float var4, float var5, float var6, float var7, float var8, float var9, Consumer<TextureDraw> var10) {
      float var11 = PZMath.floor(var2);
      float var12 = PZMath.floor(var3);
      float var13 = PZMath.ceil(var2 + var4);
      float var14 = PZMath.ceil(var3 + var5);
      this.m_states.getPopulatingActiveState().render(var1, var11, var12, var13 - var11, var14 - var12, var6, var7, var8, var9, var10);
   }

   public void renderi(Texture var1, int var2, int var3, int var4, int var5, float var6, float var7, float var8, float var9, Consumer<TextureDraw> var10) {
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
            if (var1 != null) {
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

   public void renderRect(int var1, int var2, int var3, int var4, float var5, float var6, float var7, float var8) {
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
         .render(var1, var2, var3, var4, var5, var6, var7, var8, var9, var10, var11, var12, var13, var14, var15, var16, var17, null);
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

   private static void buildDrawBuffer(TextureDraw[] var0, Style[] var1, int var2, RingBuffer var3) {
      for (int var4 = 0; var4 < var2; var4++) {
         TextureDraw var5 = var0[var4];
         Style var6 = var1[var4];
         TextureDraw var7 = null;
         if (var4 > 0) {
            var7 = var0[var4 - 1];
         }

         var3.add(var5, var7, var6);
      }
   }

   public void prePopulating() {
      this.m_states.getPopulating().prePopulating();
   }

   public void postRender() {
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

   protected void buildStateDrawBuffer(SpriteRenderState var1) {
      ringBuffer.begin();
      buildDrawBuffer(var1.sprite, var1.style, var1.numSprites, ringBuffer);
      GameProfiler.getInstance().invokeAndMeasure("ringBuffer.render", () -> ringBuffer.render());
   }

   protected void buildStateUIDrawBuffer(SpriteRenderState var1) {
      if (var1.stateUI.numSprites > 0) {
         ringBuffer.begin();
         var1.stateUI.bActive = true;
         buildDrawBuffer(var1.stateUI.sprite, var1.stateUI.style, var1.stateUI.numSprites, ringBuffer);
         ringBuffer.render();
      }

      var1.stateUI.bActive = false;
   }

   public void notifyRenderStateQueue() {
      synchronized (this.m_states) {
         this.m_states.notifyAll();
      }
   }

   public void glBuffer(int var1, int var2) {
      this.m_states.getPopulatingActiveState().glBuffer(var1, var2);
   }

   public void glDoStartFrame(int var1, int var2, float var3, int var4) {
      this.m_states.getPopulatingActiveState().glDoStartFrame(var1, var2, var3, var4);
   }

   public void glDoStartFrame(int var1, int var2, float var3, int var4, boolean var5) {
      this.m_states.getPopulatingActiveState().glDoStartFrame(var1, var2, var3, var4, var5);
   }

   public void glDoStartFrameFx(int var1, int var2, int var3) {
      this.m_states.getPopulatingActiveState().glDoStartFrameFx(var1, var2, var3);
   }

   public void glIgnoreStyles(boolean var1) {
      this.m_states.getPopulatingActiveState().glIgnoreStyles(var1);
   }

   public void glDoEndFrame() {
      this.m_states.getPopulatingActiveState().glDoEndFrame();
   }

   public void glDoEndFrameFx(int var1) {
      this.m_states.getPopulatingActiveState().glDoEndFrameFx(var1);
   }

   public void doCoreIntParam(int var1, float var2) {
      this.m_states.getPopulatingActiveState().doCoreIntParam(var1, var2);
   }

   public void glTexParameteri(int var1, int var2, int var3) {
      this.m_states.getPopulatingActiveState().glTexParameteri(var1, var2, var3);
   }

   public void StartShader(int var1, int var2) {
      this.m_states.getPopulatingActiveState().StartShader(var1, var2);
   }

   public void EndShader() {
      this.m_states.getPopulatingActiveState().EndShader();
   }

   public void setCutawayTexture(Texture var1, int var2, int var3, int var4, int var5) {
      this.m_states.getPopulatingActiveState().setCutawayTexture(var1, var2, var3, var4, var5);
   }

   public void clearCutawayTexture() {
      this.m_states.getPopulatingActiveState().clearCutawayTexture();
   }

   public void setUseVertColorsArray(byte var1, int var2, int var3, int var4, int var5) {
      this.m_states.getPopulatingActiveState().setUseVertColorsArray(var1, var2, var3, var4, var5);
   }

   public void clearUseVertColorsArray() {
      this.m_states.getPopulatingActiveState().clearUseVertColorsArray();
   }

   public void setExtraWallShaderParams(WallShaderTexRender var1) {
      this.m_states.getPopulatingActiveState().setExtraWallShaderParams(var1);
   }

   public void ShaderUpdate1i(int var1, int var2, int var3) {
      this.m_states.getPopulatingActiveState().ShaderUpdate1i(var1, var2, var3);
   }

   public void ShaderUpdate1f(int var1, int var2, float var3) {
      this.m_states.getPopulatingActiveState().ShaderUpdate1f(var1, var2, var3);
   }

   public void ShaderUpdate2f(int var1, int var2, float var3, float var4) {
      this.m_states.getPopulatingActiveState().ShaderUpdate2f(var1, var2, var3, var4);
   }

   public void ShaderUpdate3f(int var1, int var2, float var3, float var4, float var5) {
      this.m_states.getPopulatingActiveState().ShaderUpdate3f(var1, var2, var3, var4, var5);
   }

   public void ShaderUpdate4f(int var1, int var2, float var3, float var4, float var5, float var6) {
      this.m_states.getPopulatingActiveState().ShaderUpdate4f(var1, var2, var3, var4, var5, var6);
   }

   public void glLoadIdentity() {
      this.m_states.getPopulatingActiveState().glLoadIdentity();
   }

   public void glGenerateMipMaps(int var1) {
      this.m_states.getPopulatingActiveState().glGenerateMipMaps(var1);
   }

   public void glBind(int var1) {
      this.m_states.getPopulatingActiveState().glBind(var1);
   }

   public void glViewport(int var1, int var2, int var3, int var4) {
      this.m_states.getPopulatingActiveState().glViewport(var1, var2, var3, var4);
   }

   public void startOffscreenUI() {
      this.m_states.getPopulating().stateUI.bActive = true;
      this.m_states.getPopulating().stateUI.defaultStyle = TransparentStyle.instance;
      GLState.startFrame();
   }

   public void stopOffscreenUI() {
      this.m_states.getPopulating().stateUI.bActive = false;
   }

   public void pushFrameDown() {
      synchronized (this.m_states) {
         this.waitForReadySlotToOpen();
         this.m_states.movePopulatingToReady();
         this.notifyRenderStateQueue();
      }
   }

   public SpriteRenderState acquireStateForRendering(BooleanSupplier var1) {
      synchronized (this.m_states) {
         if (!this.waitForReadyState(var1)) {
            return null;
         } else {
            this.m_states.moveReadyToRendering();
            this.notifyRenderStateQueue();
            return this.m_states.getRendering();
         }
      }
   }

   private boolean waitForReadyState(BooleanSupplier var1) {
      boolean var2;
      try {
         s_performance.waitForReadyState.start();
         var2 = this.waitForReadyStateInternal(var1);
      } finally {
         s_performance.waitForReadyState.end();
      }

      return var2;
   }

   private boolean waitForReadyStateInternal(BooleanSupplier var1) {
      if (RenderThread.isRunning() && this.m_states.getReady() == null) {
         if (!RenderThread.isWaitForRenderState() && !this.isWaitingForRenderState()) {
            return false;
         } else {
            while (this.m_states.getReady() == null) {
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

   private void waitForReadySlotToOpen() {
      try {
         s_performance.waitForReadySlotToOpen.start();
         this.waitForReadySlotToOpenInternal();
      } finally {
         s_performance.waitForReadySlotToOpen.end();
      }
   }

   private void waitForReadySlotToOpenInternal() {
      if (this.m_states.getReady() != null && RenderThread.isRunning()) {
         this.m_waitingForRenderState = true;

         while (this.m_states.getReady() != null) {
            try {
               this.m_states.wait();
            } catch (InterruptedException var2) {
            }
         }

         this.m_waitingForRenderState = false;
      }
   }

   public int getMainStateIndex() {
      return this.m_states.getPopulatingActiveState().index;
   }

   public int getRenderStateIndex() {
      return this.m_states.getRenderingActiveState().index;
   }

   public boolean getDoAdditive() {
      return this.m_states.getPopulatingActiveState().defaultStyle == AdditiveStyle.instance;
   }

   public void setDefaultStyle(AbstractStyle var1) {
      this.m_states.getPopulatingActiveState().defaultStyle = var1;
   }

   public void setDoAdditive(boolean var1) {
      this.m_states.getPopulatingActiveState().defaultStyle = (AbstractStyle)(var1 ? AdditiveStyle.instance : TransparentStyle.instance);
   }

   public void initFromIsoCamera(int var1) {
      this.m_states.getPopulating().playerCamera[var1].initFromIsoCamera(var1);
   }

   public void setRenderingPlayerIndex(int var1) {
      this.m_states.getRendering().playerIndex = var1;
   }

   public int getRenderingPlayerIndex() {
      return this.m_states.getRendering().playerIndex;
   }

   public PlayerCamera getRenderingPlayerCamera(int var1) {
      return this.m_states.getRendering().playerCamera[var1];
   }

   public SpriteRenderState getRenderingState() {
      return this.m_states.getRendering();
   }

   public SpriteRenderState getPopulatingState() {
      return this.m_states.getPopulating();
   }

   public boolean isMaxZoomLevel() {
      return this.getPlayerZoomLevel() >= this.getPlayerMaxZoom();
   }

   public boolean isMinZoomLevel() {
      return this.getPlayerZoomLevel() <= this.getPlayerMinZoom();
   }

   public float getPlayerZoomLevel() {
      SpriteRenderState var1 = this.m_states.getRendering();
      int var2 = var1.playerIndex;
      return var1.zoomLevel[var2];
   }

   public float getPlayerMaxZoom() {
      SpriteRenderState var1 = this.m_states.getRendering();
      return var1.maxZoomLevel;
   }

   public float getPlayerMinZoom() {
      SpriteRenderState var1 = this.m_states.getRendering();
      return var1.minZoomLevel;
   }

   public boolean isWaitingForRenderState() {
      return this.m_waitingForRenderState;
   }
}
