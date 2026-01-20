#include <cstdint>
#include <queue>
#include "zombie\core/SpriteRenderer.h"

namespace zombie {
namespace core {

void SpriteRenderer::create() {
    // TODO: Implement create
}

void SpriteRenderer::clearSprites() {
    // TODO: Implement clearSprites
}

void SpriteRenderer::glDepthMask(bool var1) {
    // TODO: Implement glDepthMask
}

void SpriteRenderer::drawModel(ModelSlot var1) {
    // TODO: Implement drawModel
}

void SpriteRenderer::drawSkyBox(Shader var1, int var2, int var3, int var4) {
    // TODO: Implement drawSkyBox
}

void SpriteRenderer::drawWater(Shader var1, int var2, int var3, bool var4) {
    // TODO: Implement drawWater
}

void SpriteRenderer::drawPuddles(Shader var1, int var2, int var3, int var4) {
    // TODO: Implement drawPuddles
}

void SpriteRenderer::drawParticles(int var1, int var2, int var3) {
    // TODO: Implement drawParticles
}

void SpriteRenderer::drawGeneric(GenericDrawer var1) {
    // TODO: Implement drawGeneric
}

void SpriteRenderer::glDisable(int var1) {
    // TODO: Implement glDisable
}

void SpriteRenderer::glEnable(int var1) {
    // TODO: Implement glEnable
}

void SpriteRenderer::glStencilMask(int var1) {
    // TODO: Implement glStencilMask
}

void SpriteRenderer::glClear(int var1) {
    // TODO: Implement glClear
}

void SpriteRenderer::glClearColor(int var1, int var2, int var3, int var4) {
    // TODO: Implement glClearColor
}

void SpriteRenderer::glStencilFunc(int var1, int var2, int var3) {
    // TODO: Implement glStencilFunc
}

void SpriteRenderer::glStencilOp(int var1, int var2, int var3) {
    // TODO: Implement glStencilOp
}

void SpriteRenderer::glColorMask(int var1, int var2, int var3, int var4) {
    // TODO: Implement glColorMask
}

void SpriteRenderer::glAlphaFunc(int var1, float var2) {
    // TODO: Implement glAlphaFunc
}

void SpriteRenderer::glBlendFunc(int var1, int var2) {
    // TODO: Implement glBlendFunc
}

void SpriteRenderer::glBlendFuncSeparate(int var1, int var2, int var3, int var4) {
    // TODO: Implement glBlendFuncSeparate
}

void SpriteRenderer::glBlendEquation(int var1) {
    // TODO: Implement glBlendEquation
}

void SpriteRenderer::renderline(Texture var1, int var2, int var3, int var4, int var5, float var6, float var7, float var8, float var9, int var10) {
    // TODO: Implement renderline
}

void SpriteRenderer::renderline(Texture var1, int var2, int var3, int var4, int var5, float var6, float var7, float var8, float var9) {
    // TODO: Implement renderline
}

void SpriteRenderer::render(Texture var1, float var2, float var3, float var4, float var5, float var6, float var7, float var8, float var9, Consumer<TextureDraw> var10) {
    // TODO: Implement render
}

void SpriteRenderer::renderi(Texture var1, int var2, int var3, int var4, int var5, float var6, float var7, float var8, float var9, Consumer<TextureDraw> var10) {
    // TODO: Implement renderi
}

void SpriteRenderer::renderRect(int var1, int var2, int var3, int var4, float var5, float var6, float var7, float var8) {
    // TODO: Implement renderRect
}

void SpriteRenderer::buildDrawBuffer(TextureDraw[] var0, Style[] var1, int var2, RingBuffer var3) {
    // TODO: Implement buildDrawBuffer
}

void SpriteRenderer::prePopulating() {
    // TODO: Implement prePopulating
}

void SpriteRenderer::postRender() {
    // TODO: Implement postRender
}

void SpriteRenderer::buildStateDrawBuffer(SpriteRenderState var1) {
    // TODO: Implement buildStateDrawBuffer
}

void SpriteRenderer::buildStateUIDrawBuffer(SpriteRenderState var1) {
    // TODO: Implement buildStateUIDrawBuffer
}

void SpriteRenderer::notifyRenderStateQueue() {
    // TODO: Implement notifyRenderStateQueue
}

void SpriteRenderer::glBuffer(int var1, int var2) {
    // TODO: Implement glBuffer
}

void SpriteRenderer::glDoStartFrame(int var1, int var2, float var3, int var4) {
    // TODO: Implement glDoStartFrame
}

void SpriteRenderer::glDoStartFrame(int var1, int var2, float var3, int var4, bool var5) {
    // TODO: Implement glDoStartFrame
}

void SpriteRenderer::glDoStartFrameFx(int var1, int var2, int var3) {
    // TODO: Implement glDoStartFrameFx
}

void SpriteRenderer::glIgnoreStyles(bool var1) {
    // TODO: Implement glIgnoreStyles
}

void SpriteRenderer::glDoEndFrame() {
    // TODO: Implement glDoEndFrame
}

void SpriteRenderer::glDoEndFrameFx(int var1) {
    // TODO: Implement glDoEndFrameFx
}

void SpriteRenderer::doCoreIntParam(int var1, float var2) {
    // TODO: Implement doCoreIntParam
}

void SpriteRenderer::glTexParameteri(int var1, int var2, int var3) {
    // TODO: Implement glTexParameteri
}

void SpriteRenderer::StartShader(int var1, int var2) {
    // TODO: Implement StartShader
}

void SpriteRenderer::EndShader() {
    // TODO: Implement EndShader
}

void SpriteRenderer::setCutawayTexture(Texture var1, int var2, int var3, int var4, int var5) {
    // TODO: Implement setCutawayTexture
}

void SpriteRenderer::clearCutawayTexture() {
    // TODO: Implement clearCutawayTexture
}

void SpriteRenderer::setUseVertColorsArray(uint8_t var1, int var2, int var3, int var4, int var5) {
    // TODO: Implement setUseVertColorsArray
}

void SpriteRenderer::clearUseVertColorsArray() {
    // TODO: Implement clearUseVertColorsArray
}

void SpriteRenderer::setExtraWallShaderParams(WallShaderTexRender var1) {
    // TODO: Implement setExtraWallShaderParams
}

void SpriteRenderer::ShaderUpdate1i(int var1, int var2, int var3) {
    // TODO: Implement ShaderUpdate1i
}

void SpriteRenderer::ShaderUpdate1f(int var1, int var2, float var3) {
    // TODO: Implement ShaderUpdate1f
}

void SpriteRenderer::ShaderUpdate2f(int var1, int var2, float var3, float var4) {
    // TODO: Implement ShaderUpdate2f
}

void SpriteRenderer::ShaderUpdate3f(int var1, int var2, float var3, float var4, float var5) {
    // TODO: Implement ShaderUpdate3f
}

void SpriteRenderer::ShaderUpdate4f(int var1, int var2, float var3, float var4, float var5, float var6) {
    // TODO: Implement ShaderUpdate4f
}

void SpriteRenderer::glLoadIdentity() {
    // TODO: Implement glLoadIdentity
}

void SpriteRenderer::glGenerateMipMaps(int var1) {
    // TODO: Implement glGenerateMipMaps
}

void SpriteRenderer::glBind(int var1) {
    // TODO: Implement glBind
}

void SpriteRenderer::glViewport(int var1, int var2, int var3, int var4) {
    // TODO: Implement glViewport
}

void SpriteRenderer::startOffscreenUI() {
    // TODO: Implement startOffscreenUI
}

void SpriteRenderer::stopOffscreenUI() {
    // TODO: Implement stopOffscreenUI
}

void SpriteRenderer::pushFrameDown() {
    // TODO: Implement pushFrameDown
}

SpriteRenderState SpriteRenderer::acquireStateForRendering(BooleanSupplier var1) {
    // TODO: Implement acquireStateForRendering
    return nullptr;
}

bool SpriteRenderer::waitForReadyState(BooleanSupplier var1) {
    // TODO: Implement waitForReadyState
    return false;
}

bool SpriteRenderer::waitForReadyStateInternal(BooleanSupplier var1) {
    // TODO: Implement waitForReadyStateInternal
    return false;
}

void SpriteRenderer::waitForReadySlotToOpen() {
    // TODO: Implement waitForReadySlotToOpen
}

void SpriteRenderer::waitForReadySlotToOpenInternal() {
    // TODO: Implement waitForReadySlotToOpenInternal
}

int SpriteRenderer::getMainStateIndex() {
    // TODO: Implement getMainStateIndex
    return 0;
}

int SpriteRenderer::getRenderStateIndex() {
    // TODO: Implement getRenderStateIndex
    return 0;
}

bool SpriteRenderer::getDoAdditive() {
    // TODO: Implement getDoAdditive
    return false;
}

void SpriteRenderer::setDefaultStyle(AbstractStyle var1) {
    // TODO: Implement setDefaultStyle
}

void SpriteRenderer::setDoAdditive(bool var1) {
    // TODO: Implement setDoAdditive
}

void SpriteRenderer::initFromIsoCamera(int var1) {
    // TODO: Implement initFromIsoCamera
}

void SpriteRenderer::setRenderingPlayerIndex(int var1) {
    // TODO: Implement setRenderingPlayerIndex
}

int SpriteRenderer::getRenderingPlayerIndex() {
    // TODO: Implement getRenderingPlayerIndex
    return 0;
}

PlayerCamera SpriteRenderer::getRenderingPlayerCamera(int var1) {
    // TODO: Implement getRenderingPlayerCamera
    return nullptr;
}

SpriteRenderState SpriteRenderer::getRenderingState() {
    // TODO: Implement getRenderingState
    return nullptr;
}

SpriteRenderState SpriteRenderer::getPopulatingState() {
    // TODO: Implement getPopulatingState
    return nullptr;
}

bool SpriteRenderer::isMaxZoomLevel() {
    // TODO: Implement isMaxZoomLevel
    return false;
}

bool SpriteRenderer::isMinZoomLevel() {
    // TODO: Implement isMinZoomLevel
    return false;
}

float SpriteRenderer::getPlayerZoomLevel() {
    // TODO: Implement getPlayerZoomLevel
    return 0;
}

float SpriteRenderer::getPlayerMaxZoom() {
    // TODO: Implement getPlayerMaxZoom
    return 0;
}

float SpriteRenderer::getPlayerMinZoom() {
    // TODO: Implement getPlayerMinZoom
    return 0;
}

bool SpriteRenderer::isWaitingForRenderState() {
    // TODO: Implement isWaitingForRenderState
    return false;
}

} // namespace core
} // namespace zombie
