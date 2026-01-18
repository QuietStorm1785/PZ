#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/lwjgl/opengl/GL11.h"
#include "org/lwjgl/opengl/GL12.h"
#include "org/lwjgl/opengl/GL13.h"
#include "org/lwjgl/opengl/GL20.h"
#include "zombie/GameProfiler.h"
#include "zombie/asset/Asset.h"
#include "zombie/core/Styles/AbstractStyle.h"
#include "zombie/core/Styles/AdditiveStyle.h"
#include "zombie/core/Styles/AlphaOp.h"
#include "zombie/core/Styles/LightingStyle.h"
#include "zombie/core/Styles/Style.h"
#include "zombie/core/Styles/TransparentStyle.h"
#include "zombie/core/VBO/GLVertexBufferObject.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/core/opengl/GLState.h"
#include "zombie/core/opengl/RenderThread.h"
#include "zombie/core/opengl/Shader.h"
#include "zombie/core/profiling/PerformanceProfileProbe.h"
#include "zombie/core/skinnedmodel/ModelManager.h"
#include "zombie/core/sprite/SpriteRenderState.h"
#include "zombie/core/sprite/SpriteRendererStates.h"
#include "zombie/core/textures/Texture.h"
#include "zombie/core/textures/TextureAssetManager.h"
#include "zombie/core/textures/TextureDraw.h"
#include "zombie/core/textures/TextureFBO.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugOptions.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoPuddles.h"
#include "zombie/iso/PlayerCamera.h"
#include "zombie/util/list/PZArrayUtil.h"
#include <algorithm>
#include <filesystem>

namespace zombie {
namespace core {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class SpriteRenderer {
public:
 static const SpriteRenderer instance = new SpriteRenderer();
 static const int VERTEX_SIZE = 32;
 static const int TEXTURE0_COORD_OFFSET = 8;
 static const int TEXTURE1_COORD_OFFSET = 16;
 static const int TEXTURE2_ATTRIB_OFFSET = 24;
 static const int COLOR_OFFSET = 28;
 public static SpriteRenderer.RingBuffer ringBuffer = new SpriteRenderer.RingBuffer();
 static const int NUM_RENDER_STATES = 3;
 const SpriteRendererStates m_states = new SpriteRendererStates();
 private boolean m_waitingForRenderState = false;
 static bool GL_BLENDFUNC_ENABLED = true;

 void create() {
 ringBuffer.create();
 }

 void clearSprites() {
 this->m_states.getPopulating().clear();
 }

 void glDepthMask(bool b) {
 this->m_states.getPopulatingActiveState().glDepthMask(b);
 }

 void renderflipped(Texture tex, float x, float y, float width, float height, float r, float g, float b, float a, Consumer<TextureDraw> texdModifier) {
 this->m_states.getPopulatingActiveState().renderflipped(tex, x, y, width, height, r, g, b, a, texdModifier);
 }

 void drawModel(ModelManager.ModelSlot model) {
 this->m_states.getPopulatingActiveState().drawModel(model);
 }

 void drawSkyBox(Shader shader, int playerIndex, int apiId, int bufferId) {
 this->m_states.getPopulatingActiveState().drawSkyBox(shader, playerIndex, apiId, bufferId);
 }

 void drawWater(Shader shader, int playerIndex, int apiId, bool bShore) {
 this->m_states.getPopulatingActiveState().drawWater(shader, playerIndex, apiId, bShore);
 }

 void drawPuddles(Shader shader, int playerIndex, int apiId, int z) {
 this->m_states.getPopulatingActiveState().drawPuddles(shader, playerIndex, apiId, z);
 }

 void drawParticles(int playerIndex, int var1, int var2) {
 this->m_states.getPopulatingActiveState().drawParticles(playerIndex, var1, var2);
 }

 void drawGeneric(TextureDraw.GenericDrawer gd) {
 this->m_states.getPopulatingActiveState().drawGeneric(gd);
 }

 void glDisable(int a) {
 this->m_states.getPopulatingActiveState().glDisable(a);
 }

 void glEnable(int a) {
 this->m_states.getPopulatingActiveState().glEnable(a);
 }

 void glStencilMask(int a) {
 this->m_states.getPopulatingActiveState().glStencilMask(a);
 }

 void glClear(int a) {
 this->m_states.getPopulatingActiveState().glClear(a);
 }

 void glClearColor(int r, int g, int b, int a) {
 this->m_states.getPopulatingActiveState().glClearColor(r, g, b, a);
 }

 void glStencilFunc(int a, int b, int c) {
 this->m_states.getPopulatingActiveState().glStencilFunc(a, b, c);
 }

 void glStencilOp(int a, int b, int c) {
 this->m_states.getPopulatingActiveState().glStencilOp(a, b, c);
 }

 void glColorMask(int a, int b, int c, int d) {
 this->m_states.getPopulatingActiveState().glColorMask(a, b, c, d);
 }

 void glAlphaFunc(int a, float b) {
 this->m_states.getPopulatingActiveState().glAlphaFunc(a, b);
 }

 void glBlendFunc(int a, int b) {
 this->m_states.getPopulatingActiveState().glBlendFunc(a, b);
 }

 void glBlendFuncSeparate(int a, int b, int c, int d) {
 this->m_states.getPopulatingActiveState().glBlendFuncSeparate(a, b, c, d);
 }

 void glBlendEquation(int a) {
 this->m_states.getPopulatingActiveState().glBlendEquation(a);
 }

 public void render(
 Texture tex,
 double x1,
 double y1,
 double x2,
 double y2,
 double x3,
 double y3,
 double x4,
 double y4,
 float r,
 float g,
 float b,
 float a,
 Consumer<TextureDraw> texdModifier
 ) {
 this->m_states.getPopulatingActiveState().render(tex, x1, y1, x2, y2, x3, y3, x4, y4, r, g, b, a, texdModifier);
 }

 public void render(
 Texture tex,
 double x1,
 double y1,
 double x2,
 double y2,
 double x3,
 double y3,
 double x4,
 double y4,
 float r1,
 float g1,
 float b1,
 float a1,
 float r2,
 float g2,
 float b2,
 float a2,
 float r3,
 float g3,
 float b3,
 float a3,
 float r4,
 float g4,
 float b4,
 float a4,
 Consumer<TextureDraw> texdModifier
 ) {
 this->m_states
 .getPopulatingActiveState()
 .render(tex, x1, y1, x2, y2, x3, y3, x4, y4, r1, g1, b1, a1, r2, g2, b2, a2, r3, g3, b3, a3, r4, g4, b4, a4, texdModifier);
 }

 public void renderdebug(
 Texture tex,
 float x1,
 float y1,
 float x2,
 float y2,
 float x3,
 float y3,
 float x4,
 float y4,
 float r1,
 float g1,
 float b1,
 float a1,
 float r2,
 float g2,
 float b2,
 float a2,
 float r3,
 float g3,
 float b3,
 float a3,
 float r4,
 float g4,
 float b4,
 float a4,
 Consumer<TextureDraw> texdModifier
 ) {
 this->m_states
 .getPopulatingActiveState()
 .renderdebug(tex, x1, y1, x2, y2, x3, y3, x4, y4, r1, g1, b1, a1, r2, g2, b2, a2, r3, g3, b3, a3, r4, g4, b4, a4, texdModifier);
 }

 void renderline(Texture tex, int x1, int y1, int x2, int y2, float r, float g, float b, float a, int thickness) {
 this->m_states.getPopulatingActiveState().renderline(tex, x1, y1, x2, y2, r, g, b, a, thickness);
 }

 void renderline(Texture tex, int x1, int y1, int x2, int y2, float r, float g, float b, float a) {
 this->m_states.getPopulatingActiveState().renderline(tex, x1, y1, x2, y2, r, g, b, a);
 }

 void render(Texture tex, float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, int c1, int c2, int c3, int c4) {
 this->m_states.getPopulatingActiveState().render(tex, x1, y1, x2, y2, x3, y3, x4, y4, c1, c2, c3, c4);
 }

 void render(Texture tex, float x, float y, float width, float height, float r, float g, float b, float a, Consumer<TextureDraw> texdModifier) {
 float float0 = PZMath.floor(x);
 float float1 = PZMath.floor(y);
 float float2 = PZMath.ceil(x + width);
 float float3 = PZMath.ceil(y + height);
 this->m_states.getPopulatingActiveState().render(tex, float0, float1, float2 - float0, float3 - float1, r, g, b, a, texdModifier);
 }

 void renderi(Texture tex, int x, int y, int width, int height, float r, float g, float b, float a, Consumer<TextureDraw> texdModifier) {
 this->m_states.getPopulatingActiveState().render(tex, x, y, width, height, r, g, b, a, texdModifier);
 }

 public void renderClamped(
 Texture tex,
 int x,
 int y,
 int width,
 int height,
 int clampX,
 int clampY,
 int clampW,
 int clampH,
 float r,
 float g,
 float b,
 float a,
 Consumer<TextureDraw> texdModifier
 ) {
 int int0 = PZMath.clamp(x, clampX, clampX + clampW);
 int int1 = PZMath.clamp(y, clampY, clampY + clampH);
 int int2 = PZMath.clamp(x + width, clampX, clampX + clampW);
 int int3 = PZMath.clamp(y + height, clampY, clampY + clampH);
 if (int0 != int2 && int1 != int3) {
 int int4 = int0 - x;
 int int5 = x + width - int2;
 int int6 = int1 - y;
 int int7 = y + height - int3;
 if (int4 == 0 && int5 == 0 && int6 == 0 && int7 == 0) {
 this->m_states.getPopulatingActiveState().render(tex, x, y, width, height, r, g, b, a, texdModifier);
 } else {
 float float0 = 0.0F;
 float float1 = 0.0F;
 float float2 = 1.0F;
 float float3 = 0.0F;
 float float4 = 1.0F;
 float float5 = 1.0F;
 float float6 = 0.0F;
 float float7 = 1.0F;
 if (tex != nullptr) {
 float0 = (float)int4 / width;
 float1 = (float)int6 / height;
 float2 = (float)(width - int5) / width;
 float3 = (float)int6 / height;
 float4 = (float)(width - int5) / width;
 float5 = (float)(height - int7) / height;
 float6 = (float)int4 / width;
 float7 = (float)(height - int7) / height;
 }

 width = int2 - int0;
 height = int3 - int1;
 this->m_states
 .getPopulatingActiveState()
 .render(tex, int0, int1, width, height, r, g, b, a, float0, float1, float2, float3, float4, float5, float6, float7, texdModifier);
 }
 }
 }

 void renderRect(int x, int y, int width, int height, float r, float g, float b, float a) {
 this->m_states.getPopulatingActiveState().renderRect(x, y, width, height, r, g, b, a);
 }

 void renderPoly(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, float r, float g, float b, float a) {
 this->m_states.getPopulatingActiveState().renderPoly(x1, y1, x2, y2, x3, y3, x4, y4, r, g, b, a);
 }

 void renderPoly(Texture tex, float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, float r, float g, float b, float a) {
 this->m_states.getPopulatingActiveState().renderPoly(tex, x1, y1, x2, y2, x3, y3, x4, y4, r, g, b, a);
 }

 public void renderPoly(
 Texture tex,
 float x1,
 float y1,
 float x2,
 float y2,
 float x3,
 float y3,
 float x4,
 float y4,
 float r,
 float g,
 float b,
 float a,
 float u1,
 float v1,
 float u2,
 float v2,
 float u3,
 float v3,
 float u4,
 float v4
 ) {
 this->m_states.getPopulatingActiveState().renderPoly(tex, x1, y1, x2, y2, x3, y3, x4, y4, r, g, b, a, u1, v1, u2, v2, u3, v3, u4, v4);
 }

 public void render(
 Texture tex,
 float x,
 float y,
 float width,
 float height,
 float r,
 float g,
 float b,
 float a,
 float u1,
 float v1,
 float u2,
 float v2,
 float u3,
 float v3,
 float u4,
 float v4
 ) {
 this->m_states.getPopulatingActiveState().render(tex, x, y, width, height, r, g, b, a, u1, v1, u2, v2, u3, v3, u4, v4, nullptr);
 }

 public void render(
 Texture tex,
 float x,
 float y,
 float width,
 float height,
 float r,
 float g,
 float b,
 float a,
 float u1,
 float v1,
 float u2,
 float v2,
 float u3,
 float v3,
 float u4,
 float v4,
 Consumer<TextureDraw> texdModifier
 ) {
 this->m_states.getPopulatingActiveState().render(tex, x, y, width, height, r, g, b, a, u1, v1, u2, v2, u3, v3, u4, v4, texdModifier);
 }

 static void buildDrawBuffer(TextureDraw[] textureDraws, Style[] styles, int int1, SpriteRenderer.RingBuffer ringBufferx) {
 for (int int0 = 0; int0 < int1; int0++) {
 TextureDraw textureDraw0 = textureDraws[int0];
 Style style = styles[int0];
 TextureDraw textureDraw1 = nullptr;
 if (int0 > 0) {
 textureDraw1 = textureDraws[int0 - 1];
 }

 ringBufferx.add(textureDraw0, textureDraw1, style);
 }
 }

 void prePopulating() {
 this->m_states.getPopulating().prePopulating();
 }

 void postRender() {
 SpriteRenderState spriteRenderState = this->m_states.getRendering();
 if (spriteRenderState.numSprites == 0 && spriteRenderState.stateUI.numSprites == 0) {
 spriteRenderState.onRendered();
 } else {
 TextureFBO.reset();
 IsoPuddles.VBOs.startFrame();
 GameProfiler.getInstance().invokeAndMeasure("buildStateUIDrawBuffer(UI)", this, spriteRenderState, SpriteRenderer::buildStateUIDrawBuffer);
 GameProfiler.getInstance().invokeAndMeasure("buildStateDrawBuffer", this, spriteRenderState, SpriteRenderer::buildStateDrawBuffer);
 spriteRenderState.onRendered();
 Core.getInstance().setLastRenderedFBO(spriteRenderState.fbo);
 this->notifyRenderStateQueue();
 }
 }

 void buildStateDrawBuffer(SpriteRenderState spriteRenderState) {
 ringBuffer.begin();
 buildDrawBuffer(spriteRenderState.sprite, spriteRenderState.style, spriteRenderState.numSprites, ringBuffer);
 GameProfiler.getInstance().invokeAndMeasure("ringBuffer.render", () -> ringBuffer.render());
 }

 void buildStateUIDrawBuffer(SpriteRenderState spriteRenderState) {
 if (spriteRenderState.stateUI.numSprites > 0) {
 ringBuffer.begin();
 spriteRenderState.stateUI.bActive = true;
 buildDrawBuffer(spriteRenderState.stateUI.sprite, spriteRenderState.stateUI.style, spriteRenderState.stateUI.numSprites, ringBuffer);
 ringBuffer.render();
 }

 spriteRenderState.stateUI.bActive = false;
 }

 void notifyRenderStateQueue() {
 synchronized (this->m_states) {
 this->m_states.notifyAll();
 }
 }

 void glBuffer(int i, int p) {
 this->m_states.getPopulatingActiveState().glBuffer(i, p);
 }

 void glDoStartFrame(int w, int h, float zoom, int player) {
 this->m_states.getPopulatingActiveState().glDoStartFrame(w, h, zoom, player);
 }

 void glDoStartFrame(int w, int h, float zoom, int player, bool isTextFrame) {
 this->m_states.getPopulatingActiveState().glDoStartFrame(w, h, zoom, player, isTextFrame);
 }

 void glDoStartFrameFx(int w, int h, int player) {
 this->m_states.getPopulatingActiveState().glDoStartFrameFx(w, h, player);
 }

 void glIgnoreStyles(bool b) {
 this->m_states.getPopulatingActiveState().glIgnoreStyles(b);
 }

 void glDoEndFrame() {
 this->m_states.getPopulatingActiveState().glDoEndFrame();
 }

 void glDoEndFrameFx(int player) {
 this->m_states.getPopulatingActiveState().glDoEndFrameFx(player);
 }

 void doCoreIntParam(int id, float val) {
 this->m_states.getPopulatingActiveState().doCoreIntParam(id, val);
 }

 void glTexParameteri(int a, int b, int c) {
 this->m_states.getPopulatingActiveState().glTexParameteri(a, b, c);
 }

 void StartShader(int iD, int playerIndex) {
 this->m_states.getPopulatingActiveState().StartShader(iD, playerIndex);
 }

 void EndShader() {
 this->m_states.getPopulatingActiveState().EndShader();
 }

 void setCutawayTexture(Texture tex, int x, int y, int w, int h) {
 this->m_states.getPopulatingActiveState().setCutawayTexture(tex, x, y, w, h);
 }

 void clearCutawayTexture() {
 this->m_states.getPopulatingActiveState().clearCutawayTexture();
 }

 void setUseVertColorsArray(uint8_t whichShader, int c0, int c1, int c2, int c3) {
 this->m_states.getPopulatingActiveState().setUseVertColorsArray(whichShader, c0, c1, c2, c3);
 }

 void clearUseVertColorsArray() {
 this->m_states.getPopulatingActiveState().clearUseVertColorsArray();
 }

 void setExtraWallShaderParams(SpriteRenderer.WallShaderTexRender wallTexRender) {
 this->m_states.getPopulatingActiveState().setExtraWallShaderParams(wallTexRender);
 }

 void ShaderUpdate1i(int shaderID, int uniform, int uniformValue) {
 this->m_states.getPopulatingActiveState().ShaderUpdate1i(shaderID, uniform, uniformValue);
 }

 void ShaderUpdate1f(int shaderID, int uniform, float uniformValue) {
 this->m_states.getPopulatingActiveState().ShaderUpdate1f(shaderID, uniform, uniformValue);
 }

 void ShaderUpdate2f(int shaderID, int uniform, float value1, float value2) {
 this->m_states.getPopulatingActiveState().ShaderUpdate2f(shaderID, uniform, value1, value2);
 }

 void ShaderUpdate3f(int shaderID, int uniform, float value1, float value2, float value3) {
 this->m_states.getPopulatingActiveState().ShaderUpdate3f(shaderID, uniform, value1, value2, value3);
 }

 void ShaderUpdate4f(int shaderID, int uniform, float value1, float value2, float value3, float value4) {
 this->m_states.getPopulatingActiveState().ShaderUpdate4f(shaderID, uniform, value1, value2, value3, value4);
 }

 void glLoadIdentity() {
 this->m_states.getPopulatingActiveState().glLoadIdentity();
 }

 void glGenerateMipMaps(int a) {
 this->m_states.getPopulatingActiveState().glGenerateMipMaps(a);
 }

 void glBind(int a) {
 this->m_states.getPopulatingActiveState().glBind(a);
 }

 void glViewport(int x, int y, int width, int height) {
 this->m_states.getPopulatingActiveState().glViewport(x, y, width, height);
 }

 void startOffscreenUI() {
 this->m_states.getPopulating().stateUI.bActive = true;
 this->m_states.getPopulating().stateUI.defaultStyle = TransparentStyle.instance;
 GLState.startFrame();
 }

 void stopOffscreenUI() {
 this->m_states.getPopulating().stateUI.bActive = false;
 }

 void pushFrameDown() {
 synchronized (this->m_states) {
 this->waitForReadySlotToOpen();
 this->m_states.movePopulatingToReady();
 this->notifyRenderStateQueue();
 }
 }

 SpriteRenderState acquireStateForRendering(BooleanSupplier waitCallback) {
 synchronized (this->m_states) {
 if (!this->waitForReadyState(waitCallback) {
 return nullptr;
 } else {
 this->m_states.moveReadyToRendering();
 this->notifyRenderStateQueue();
 return this->m_states.getRendering();
 }
 }
 }

 bool waitForReadyState(BooleanSupplier booleanSupplier) {
 bool boolean0;
 try {
 SpriteRenderer.s_performance.waitForReadyState.start();
 boolean0 = this->waitForReadyStateInternal(booleanSupplier);
 } finally {
 SpriteRenderer.s_performance.waitForReadyState.end();
 }

 return boolean0;
 }

 bool waitForReadyStateInternal(BooleanSupplier booleanSupplier) {
 if (RenderThread.isRunning() && this->m_states.getReady() == nullptr) {
 if (!RenderThread.isWaitForRenderState() && !this->isWaitingForRenderState()) {
 return false;
 } else {
 while (this->m_states.getReady() == nullptr) {
 try {
 if (!booleanSupplier.getAsBoolean()) {
 return false;
 }

 this->m_states.wait();
 } catch (InterruptedException interruptedException) {
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
 SpriteRenderer.s_performance.waitForReadySlotToOpen.start();
 this->waitForReadySlotToOpenInternal();
 } finally {
 SpriteRenderer.s_performance.waitForReadySlotToOpen.end();
 }
 }

 void waitForReadySlotToOpenInternal() {
 if (this->m_states.getReady() != nullptr && RenderThread.isRunning()) {
 this->m_waitingForRenderState = true;

 while (this->m_states.getReady() != nullptr) {
 try {
 this->m_states.wait();
 } catch (InterruptedException interruptedException) {
 }
 }

 this->m_waitingForRenderState = false;
 }
 }

 int getMainStateIndex() {
 return this->m_states.getPopulatingActiveState().index;
 }

 int getRenderStateIndex() {
 return this->m_states.getRenderingActiveState().index;
 }

 bool getDoAdditive() {
 return this->m_states.getPopulatingActiveState().defaultStyle == AdditiveStyle.instance;
 }

 void setDefaultStyle(AbstractStyle style) {
 this->m_states.getPopulatingActiveState().defaultStyle = style;
 }

 void setDoAdditive(bool bDoAdditive) {
 this->m_states.getPopulatingActiveState().defaultStyle = (AbstractStyle)(bDoAdditive ? AdditiveStyle.instance : TransparentStyle.instance);
 }

 void initFromIsoCamera(int nPlayer) {
 this->m_states.getPopulating().playerCamera[nPlayer].initFromIsoCamera(nPlayer);
 }

 void setRenderingPlayerIndex(int player) {
 this->m_states.getRendering().playerIndex = player;
 }

 int getRenderingPlayerIndex() {
 return this->m_states.getRendering().playerIndex;
 }

 PlayerCamera getRenderingPlayerCamera(int userId) {
 return this->m_states.getRendering().playerCamera[userId];
 }

 SpriteRenderState getRenderingState() {
 return this->m_states.getRendering();
 }

 SpriteRenderState getPopulatingState() {
 return this->m_states.getPopulating();
 }

 bool isMaxZoomLevel() {
 return this->getPlayerZoomLevel() >= this->getPlayerMaxZoom();
 }

 bool isMinZoomLevel() {
 return this->getPlayerZoomLevel() <= this->getPlayerMinZoom();
 }

 float getPlayerZoomLevel() {
 SpriteRenderState spriteRenderState = this->m_states.getRendering();
 int int0 = spriteRenderState.playerIndex;
 return spriteRenderState.zoomLevel[int0];
 }

 float getPlayerMaxZoom() {
 SpriteRenderState spriteRenderState = this->m_states.getRendering();
 return spriteRenderState.maxZoomLevel;
 }

 float getPlayerMinZoom() {
 SpriteRenderState spriteRenderState = this->m_states.getRendering();
 return spriteRenderState.minZoomLevel;
 }

 bool isWaitingForRenderState() {
 return this->m_waitingForRenderState;
 }

 public static class RingBuffer {
 GLVertexBufferObject[] vbo;
 GLVertexBufferObject[] ibo;
 long bufferSize;
 long bufferSizeInVertices;
 long indexBufferSize;
 int numBuffers;
 int sequence = -1;
 int mark = -1;
 FloatBuffer currentVertices;
 ShortBuffer currentIndices;
 FloatBuffer[] vertices;
 ByteBuffer[] verticesBytes;
 ShortBuffer[] indices;
 ByteBuffer[] indicesBytes;
 Texture lastRenderedTexture0;
 Texture currentTexture0;
 Texture lastRenderedTexture1;
 Texture currentTexture1;
 bool shaderChangedTexture1 = false;
 uint8_t lastUseAttribArray;
 uint8_t currentUseAttribArray;
 Style lastRenderedStyle;
 Style currentStyle;
 SpriteRenderer.RingBuffer.StateRun[] stateRun;
 bool restoreVBOs;
 bool restoreBoundTextures;
 int vertexCursor;
 int indexCursor;
 int numRuns;
 SpriteRenderer.RingBuffer.StateRun currentRun;
 static bool IGNORE_STYLES = false;

 RingBuffer() {
 }

 void create() {
 GL11.glEnableClientState(32884);
 GL11.glEnableClientState(32886);
 GL11.glEnableClientState(32888);
 this->bufferSize = 65536L;
 this->numBuffers = Core.bDebug ? 256 : 128;
 this->bufferSizeInVertices = this->bufferSize / 32L;
 this->indexBufferSize = this->bufferSizeInVertices * 3L;
 this->vertices = new FloatBuffer[this->numBuffers];
 this->verticesBytes = new ByteBuffer[this->numBuffers];
 this->indices = new ShortBuffer[this->numBuffers];
 this->indicesBytes = new ByteBuffer[this->numBuffers];
 this->stateRun = new SpriteRenderer.RingBuffer.StateRun[5000];

 for (int int0 = 0; int0 < 5000; int0++) {
 this->stateRun[int0] = new SpriteRenderer.RingBuffer.StateRun();
 }

 this->vbo = new GLVertexBufferObject[this->numBuffers];
 this->ibo = new GLVertexBufferObject[this->numBuffers];

 for (int int1 = 0; int1 < this->numBuffers; int1++) {
 this->vbo[int1] = new GLVertexBufferObject(
 this->bufferSize, GLVertexBufferObject.funcs.GL_ARRAY_BUFFER(), GLVertexBufferObject.funcs.GL_STREAM_DRAW()
 );
 this->vbo[int1].create();
 this->ibo[int1] = new GLVertexBufferObject(
 this->indexBufferSize, GLVertexBufferObject.funcs.GL_ELEMENT_ARRAY_BUFFER(), GLVertexBufferObject.funcs.GL_STREAM_DRAW()
 );
 this->ibo[int1].create();
 }
 }

 void add(TextureDraw textureDraw0, TextureDraw textureDraw1, Style style) {
 if (style != nullptr) {
 if (this->vertexCursor + 4 > this->bufferSizeInVertices || this->indexCursor + 6 > this->indexBufferSize) {
 this->render();
 this->next();
 }

 if (this->prepareCurrentRun(textureDraw0, textureDraw1, style) {
 FloatBuffer floatBuffer = this->currentVertices;
 AlphaOp alphaOp = style.getAlphaOp();
 floatBuffer.put(textureDraw0.x0);
 floatBuffer.put(textureDraw0.y0);
 if (textureDraw0.tex.empty()) {
 floatBuffer.put(0.0F);
 floatBuffer.put(0.0F);
 } else {
 if (textureDraw0.flipped) {
 floatBuffer.put(textureDraw0.u1);
 } else {
 floatBuffer.put(textureDraw0.u0);
 }

 floatBuffer.put(textureDraw0.v0);
 }

 if (textureDraw0.tex1.empty()) {
 floatBuffer.put(0.0F);
 floatBuffer.put(0.0F);
 } else {
 floatBuffer.put(textureDraw0.tex1_u0);
 floatBuffer.put(textureDraw0.tex1_v0);
 }

 floatBuffer.put(Float.intBitsToFloat(textureDraw0.useAttribArray != -1 ? textureDraw0.tex1_col0 : 0);
 int int0 = textureDraw0.getColor(0);
 alphaOp.op(int0, 255, floatBuffer);
 floatBuffer.put(textureDraw0.x1);
 floatBuffer.put(textureDraw0.y1);
 if (textureDraw0.tex.empty()) {
 floatBuffer.put(0.0F);
 floatBuffer.put(0.0F);
 } else {
 if (textureDraw0.flipped) {
 floatBuffer.put(textureDraw0.u0);
 } else {
 floatBuffer.put(textureDraw0.u1);
 }

 floatBuffer.put(textureDraw0.v1);
 }

 if (textureDraw0.tex1.empty()) {
 floatBuffer.put(0.0F);
 floatBuffer.put(0.0F);
 } else {
 floatBuffer.put(textureDraw0.tex1_u1);
 floatBuffer.put(textureDraw0.tex1_v1);
 }

 floatBuffer.put(Float.intBitsToFloat(textureDraw0.useAttribArray != -1 ? textureDraw0.tex1_col1 : 0);
 int0 = textureDraw0.getColor(1);
 alphaOp.op(int0, 255, floatBuffer);
 floatBuffer.put(textureDraw0.x2);
 floatBuffer.put(textureDraw0.y2);
 if (textureDraw0.tex.empty()) {
 floatBuffer.put(0.0F);
 floatBuffer.put(0.0F);
 } else {
 if (textureDraw0.flipped) {
 floatBuffer.put(textureDraw0.u3);
 } else {
 floatBuffer.put(textureDraw0.u2);
 }

 floatBuffer.put(textureDraw0.v2);
 }

 if (textureDraw0.tex1.empty()) {
 floatBuffer.put(0.0F);
 floatBuffer.put(0.0F);
 } else {
 floatBuffer.put(textureDraw0.tex1_u2);
 floatBuffer.put(textureDraw0.tex1_v2);
 }

 floatBuffer.put(Float.intBitsToFloat(textureDraw0.useAttribArray != -1 ? textureDraw0.tex1_col2 : 0);
 int0 = textureDraw0.getColor(2);
 alphaOp.op(int0, 255, floatBuffer);
 floatBuffer.put(textureDraw0.x3);
 floatBuffer.put(textureDraw0.y3);
 if (textureDraw0.tex.empty()) {
 floatBuffer.put(0.0F);
 floatBuffer.put(0.0F);
 } else {
 if (textureDraw0.flipped) {
 floatBuffer.put(textureDraw0.u2);
 } else {
 floatBuffer.put(textureDraw0.u3);
 }

 floatBuffer.put(textureDraw0.v3);
 }

 if (textureDraw0.tex1.empty()) {
 floatBuffer.put(0.0F);
 floatBuffer.put(0.0F);
 } else {
 floatBuffer.put(textureDraw0.tex1_u3);
 floatBuffer.put(textureDraw0.tex1_v3);
 }

 floatBuffer.put(Float.intBitsToFloat(textureDraw0.useAttribArray != -1 ? textureDraw0.tex1_col3 : 0);
 int0 = textureDraw0.getColor(3);
 alphaOp.op(int0, 255, floatBuffer);
 this->currentIndices.put((short)this->vertexCursor);
 this->currentIndices.put((short)(this->vertexCursor + 1);
 this->currentIndices.put((short)(this->vertexCursor + 2);
 this->currentIndices.put((short)this->vertexCursor);
 this->currentIndices.put((short)(this->vertexCursor + 2);
 this->currentIndices.put((short)(this->vertexCursor + 3);
 this->indexCursor += 6;
 this->vertexCursor += 4;
 this->currentRun.endIndex += 6;
 this->currentRun.length += 4;
 }
 }
 }

 bool prepareCurrentRun(TextureDraw textureDraw0, TextureDraw textureDraw1, Style style) {
 Texture texture0 = textureDraw0.tex;
 Texture texture1 = textureDraw0.tex1;
 uint8_t byte0 = textureDraw0.useAttribArray;
 if (this->isStateChanged(textureDraw0, textureDraw1, style, texture0, texture1, byte0) {
 this->currentRun = this->stateRun[this->numRuns];
 this->currentRun.start = this->vertexCursor;
 this->currentRun.length = 0;
 this->currentRun.style = style;
 this->currentRun.texture0 = texture0;
 this->currentRun.texture1 = texture1;
 this->currentRun.useAttribArray = byte0;
 this->currentRun.indices = this->currentIndices;
 this->currentRun.startIndex = this->indexCursor;
 this->currentRun.endIndex = this->indexCursor;
 this->numRuns++;
 if (this->numRuns == this->stateRun.length) {
 this->growStateRuns();
 }

 this->currentStyle = style;
 this->currentTexture0 = texture0;
 this->currentTexture1 = texture1;
 this->currentUseAttribArray = byte0;
 }

 if (textureDraw0.type != TextureDraw.Type.glDraw) {
 this->currentRun.ops.add(textureDraw0);
 return false;
 } else {
 return true;
 }
 }

 bool isStateChanged(TextureDraw textureDraw0, TextureDraw textureDraw1, Style style, Texture texture0, Texture texture1, uint8_t byte0) {
 if (this->currentRun.empty()) {
 return true;
 } else if (textureDraw0.type == TextureDraw.Type.DrawModel) {
 return true;
 } else if (byte0 != this->currentUseAttribArray) {
 return true;
 } else if (texture0 != this->currentTexture0) {
 return true;
 } else if (texture1 != this->currentTexture1) {
 return true;
 } else {
 if (textureDraw1 != nullptr) {
 if (textureDraw1.type == TextureDraw.Type.DrawModel) {
 return true;
 }

 if (textureDraw0.type == TextureDraw.Type.glDraw && textureDraw1.type != TextureDraw.Type.glDraw) {
 return true;
 }

 if (textureDraw0.type != TextureDraw.Type.glDraw && textureDraw1.type == TextureDraw.Type.glDraw) {
 return true;
 }
 }

 if (style != this->currentStyle) {
 if (this->currentStyle.empty()) {
 return true;
 }

 if (style.getStyleID() != this->currentStyle.getStyleID()) {
 return true;
 }
 }

 return false;
 }
 }

 void next() {
 this->sequence++;
 if (this->sequence == this->numBuffers) {
 this->sequence = 0;
 }

 if (this->sequence == this->mark) {
 DebugLog.General.error("Buffer overrun.");
 }

 this->vbo[this->sequence].bind();
 ByteBuffer byteBuffer0 = this->vbo[this->sequence].map();
 if (this->vertices[this->sequence] == nullptr || this->verticesBytes[this->sequence] != byteBuffer0) {
 this->verticesBytes[this->sequence] = byteBuffer0;
 this->vertices[this->sequence] = byteBuffer0.asFloatBuffer();
 }

 this->ibo[this->sequence].bind();
 ByteBuffer byteBuffer1 = this->ibo[this->sequence].map();
 if (this->indices[this->sequence] == nullptr || this->indicesBytes[this->sequence] != byteBuffer1) {
 this->indicesBytes[this->sequence] = byteBuffer1;
 this->indices[this->sequence] = byteBuffer1.asShortBuffer();
 }

 this->currentVertices = this->vertices[this->sequence];
 this->currentVertices.clear();
 this->currentIndices = this->indices[this->sequence];
 this->currentIndices.clear();
 this->vertexCursor = 0;
 this->indexCursor = 0;
 this->numRuns = 0;
 this->currentRun = nullptr;
 }

 void begin() {
 this->currentStyle = nullptr;
 this->currentTexture0 = nullptr;
 this->currentTexture1 = nullptr;
 this->currentUseAttribArray = -1;
 this->next();
 this->mark = this->sequence;
 }

 void render() {
 this->vbo[this->sequence].unmap();
 this->ibo[this->sequence].unmap();
 this->restoreVBOs = true;

 for (int int0 = 0; int0 < this->numRuns; int0++) {
 this->stateRun[int0].render();
 }
 }

 void growStateRuns() {
 SpriteRenderer.RingBuffer.StateRun[] stateRuns = new SpriteRenderer.RingBuffer.StateRun[(int)(this->stateRun.length * 1.5F)];
 System.arraycopy(this->stateRun, 0, stateRuns, 0, this->stateRun.length);

 for (int int0 = this->numRuns; int0 < stateRuns.length; int0++) {
 stateRuns[int0] = new SpriteRenderer.RingBuffer.StateRun();
 }

 this->stateRun = stateRuns;
 }

 void shaderChangedTexture1() {
 this->shaderChangedTexture1 = true;
 }

 void checkShaderChangedTexture1() {
 if (this->shaderChangedTexture1) {
 this->shaderChangedTexture1 = false;
 this->lastRenderedTexture1 = nullptr;
 GL13.glActiveTexture(33985);
 GL13.glClientActiveTexture(33985);
 GL11.glDisable(3553);
 GL13.glActiveTexture(33984);
 GL13.glClientActiveTexture(33984);
 }
 }

 void debugBoundTexture(Texture texture0, int _unit) {
 if (GL11.glGetInteger(34016) == _unit) {
 int int0 = GL11.glGetInteger(32873);
 std::string string = nullptr;
 if (texture0.empty() && int0 != 0) {
 for (Asset asset0 : TextureAssetManager.instance.getAssetTable().values()) {
 Texture _texture0 = (Texture)asset0;
 if (_texture0.getID() == int0) {
 string = _texture0.getPath().getPath();
 break;
 }
 }

 DebugLog.General.error("SpriteRenderer.lastBoundTexture0=nullptr doesn't match OpenGL texture id=" + int0 + " " + string);
 } else if (texture0 != nullptr && texture0.getID() != -1 && int0 != texture0.getID()) {
 for (Asset asset1 : TextureAssetManager.instance.getAssetTable().values()) {
 Texture texture1 = (Texture)asset1;
 if (texture1.getID() == int0) {
 string = texture1.getName();
 break;
 }
 }

 DebugLog.General
 .error("SpriteRenderer.lastBoundTexture0 id=" + texture0.getID() + " doesn't match OpenGL texture id=" + int0 + " " + string);
 }
 }
 }

 class StateRun {
 Texture texture0;
 Texture texture1;
 uint8_t useAttribArray = -1;
 Style style;
 int start;
 int length;
 ShortBuffer indices;
 int startIndex;
 int endIndex;
 ArrayList<TextureDraw> ops = std::make_unique<ArrayList<>>();

 std::string toString() {
 std::string string = System.lineSeparator();
 return this->getClass().getSimpleName()
 + "{ "
 + string
 + " ops:"
 + PZArrayUtil.arrayToString(this->ops, "{", "}", ", ")
 + string
 + " texture0:"
 + this->texture0
 + string
 + " texture1:"
 + this->texture1
 + string
 + " useAttribArray:"
 + this->useAttribArray
 + string
 + " style:"
 + this->style
 + string
 + " start:"
 + this->start
 + string
 + " length:"
 + this->length
 + string
 + " indices:"
 + this->indices
 + string
 + " startIndex:"
 + this->startIndex
 + string
 + " endIndex:"
 + this->endIndex
 + string
 + "}";
 }

 void render() {
 if (this->style != nullptr) {
 int int0 = this->ops.size();
 if (int0 > 0) {
 for (int int1 = 0; int1 < int0; int1++) {
 this->ops.get(int1).run();
 }

 this->ops.clear();
 } else {
 if (this->style != RingBuffer.this->lastRenderedStyle) {
 if (RingBuffer.this->lastRenderedStyle != nullptr
 && (
 !SpriteRenderer.RingBuffer.IGNORE_STYLES
 || RingBuffer.this->lastRenderedStyle != AdditiveStyle.instance
 && RingBuffer.this->lastRenderedStyle != TransparentStyle.instance
 && RingBuffer.this->lastRenderedStyle != LightingStyle.instance
 )) {
 RingBuffer.this->lastRenderedStyle.resetState();
 }

 if (this->style != nullptr
 && (
 !SpriteRenderer.RingBuffer.IGNORE_STYLES
 || this->style != AdditiveStyle.instance
 && this->style != TransparentStyle.instance
 && this->style != LightingStyle.instance
 )) {
 this->style.setupState();
 }

 RingBuffer.this->lastRenderedStyle = this->style;
 }

 if (RingBuffer.this->lastRenderedTexture0 != nullptr && RingBuffer.this->lastRenderedTexture0.getID() != Texture.lastTextureID) {
 RingBuffer.this->restoreBoundTextures = true;
 }

 if (RingBuffer.this->restoreBoundTextures) {
 Texture.lastTextureID = 0;
 GL11.glBindTexture(3553, 0);
 if (this->texture0.empty()) {
 GL11.glDisable(3553);
 }

 RingBuffer.this->lastRenderedTexture0 = nullptr;
 RingBuffer.this->lastRenderedTexture1 = nullptr;
 RingBuffer.this->restoreBoundTextures = false;
 }

 if (this->texture0 != RingBuffer.this->lastRenderedTexture0) {
 if (this->texture0 != nullptr) {
 if (RingBuffer.this->lastRenderedTexture0.empty()) {
 GL11.glEnable(3553);
 }

 this->texture0.bind();
 } else {
 GL11.glDisable(3553);
 Texture.lastTextureID = 0;
 GL11.glBindTexture(3553, 0);
 }

 RingBuffer.this->lastRenderedTexture0 = this->texture0;
 }

 if (DebugOptions.instance.Checks.BoundTextures.getValue()) {
 RingBuffer.this->debugBoundTexture(RingBuffer.this->lastRenderedTexture0, 33984);
 }

 if (this->texture1 != RingBuffer.this->lastRenderedTexture1) {
 GL13.glActiveTexture(33985);
 GL13.glClientActiveTexture(33985);
 if (this->texture1 != nullptr) {
 GL11.glBindTexture(3553, this->texture1.getID());
 } else {
 GL11.glDisable(3553);
 }

 GL13.glActiveTexture(33984);
 GL13.glClientActiveTexture(33984);
 RingBuffer.this->lastRenderedTexture1 = this->texture1;
 }

 if (this->useAttribArray != RingBuffer.this->lastUseAttribArray) {
 if (this->useAttribArray != -1) {
 if (this->useAttribArray == 1) {
 int int2 = IsoGridSquare.CircleStencilShader.instance.a_wallShadeColor;
 if (int2 != -1) {
 GL20.glEnableVertexAttribArray(int2);
 }
 }

 if (this->useAttribArray == 2) {
 int int3 = IsoGridSquare.NoCircleStencilShader.instance.a_wallShadeColor;
 if (int3 != -1) {
 GL20.glEnableVertexAttribArray(int3);
 }
 }
 } else {
 if (RingBuffer.this->lastUseAttribArray == 1) {
 int int4 = IsoGridSquare.CircleStencilShader.instance.a_wallShadeColor;
 if (int4 != -1) {
 GL20.glDisableVertexAttribArray(int4);
 }
 }

 if (RingBuffer.this->lastUseAttribArray == 2) {
 int int5 = IsoGridSquare.NoCircleStencilShader.instance.a_wallShadeColor;
 if (int5 != -1) {
 GL20.glDisableVertexAttribArray(int5);
 }
 }
 }

 RingBuffer.this->lastUseAttribArray = this->useAttribArray;
 }

 if (this->length != 0) {
 if (this->length == -1) {
 RingBuffer.this->restoreVBOs = true;
 } else {
 if (RingBuffer.this->restoreVBOs) {
 RingBuffer.this->restoreVBOs = false;
 RingBuffer.this->vbo[RingBuffer.this->sequence].bind();
 RingBuffer.this->ibo[RingBuffer.this->sequence].bind();
 GL11.glVertexPointer(2, 5126, 32, 0L);
 GL11.glTexCoordPointer(2, 5126, 32, 8L);
 GL11.glColorPointer(4, 5121, 32, 28L);
 GL13.glActiveTexture(33985);
 GL13.glClientActiveTexture(33985);
 GL11.glTexCoordPointer(2, 5126, 32, 16L);
 GL11.glEnableClientState(32888);
 int int6 = IsoGridSquare.CircleStencilShader.instance.a_wallShadeColor;
 if (int6 != -1) {
 GL20.glVertexAttribPointer(int6, 4, 5121, true, 32, 24L);
 }

 int6 = IsoGridSquare.NoCircleStencilShader.instance.a_wallShadeColor;
 if (int6 != -1) {
 GL20.glVertexAttribPointer(int6, 4, 5121, true, 32, 24L);
 }

 GL13.glActiveTexture(33984);
 GL13.glClientActiveTexture(33984);
 }

 assert GL11.glGetInteger(34964) == RingBuffer.this->vbo[RingBuffer.this->sequence].getID();

 if (this->useAttribArray == 1) {
 RingBuffer.this->vbo[RingBuffer.this->sequence]
 .enableVertexAttribArray(IsoGridSquare.CircleStencilShader.instance.a_wallShadeColor);

 assert GL20.glGetVertexAttribi(IsoGridSquare.CircleStencilShader.instance.a_wallShadeColor, 34975) != 0;
 } else if (this->useAttribArray == 2) {
 RingBuffer.this->vbo[RingBuffer.this->sequence]
 .enableVertexAttribArray(IsoGridSquare.NoCircleStencilShader.instance.a_wallShadeColor);
 } else {
 RingBuffer.this->vbo[RingBuffer.this->sequence].disableVertexAttribArray();
 }

 if (this->style.getRenderSprite()) {
 GL12.glDrawRangeElements(
 4, this->start, this->start + this->length, this->endIndex - this->startIndex, 5123, this->startIndex * 2L
 );
 } else {
 this->style.render(this->start, this->startIndex);
 }
 }
 }
 }
 }
 }
 }
 }

 public static enum WallShaderTexRender {
 All,
 LeftOnly,
 RightOnly;
 }

 private static class s_performance {
 static const PerformanceProfileProbe waitForReadyState = new PerformanceProfileProbe("waitForReadyState");
 static const PerformanceProfileProbe waitForReadySlotToOpen = new PerformanceProfileProbe("waitForReadySlotToOpen");
 }
}
} // namespace core
} // namespace zombie
