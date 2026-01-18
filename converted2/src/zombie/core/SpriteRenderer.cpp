#include "zombie/core/SpriteRenderer.h"

namespace zombie {
namespace core {

void SpriteRenderer::create() {
  // TODO: Implement create
}

void SpriteRenderer::clearSprites() {
  // TODO: Implement clearSprites
}

void SpriteRenderer::glDepthMask(bool b) {
  // TODO: Implement glDepthMask
}

void SpriteRenderer::renderflipped(Texture tex, float x, float y, float width,
                                   float height, float r, float g, float b,
                                   float a,
                                   Consumer<TextureDraw> texdModifier) {
  // TODO: Implement renderflipped
}

void SpriteRenderer::drawModel(ModelManager.ModelSlot model) {
  // TODO: Implement drawModel
}

void SpriteRenderer::drawSkyBox(Shader shader, int playerIndex, int apiId,
                                int bufferId) {
  // TODO: Implement drawSkyBox
}

void SpriteRenderer::drawWater(Shader shader, int playerIndex, int apiId,
                               bool bShore) {
  // TODO: Implement drawWater
}

void SpriteRenderer::drawPuddles(Shader shader, int playerIndex, int apiId,
                                 int z) {
  // TODO: Implement drawPuddles
}

void SpriteRenderer::drawParticles(int playerIndex, int var1, int var2) {
  // TODO: Implement drawParticles
}

void SpriteRenderer::drawGeneric(TextureDraw.GenericDrawer gd) {
  // TODO: Implement drawGeneric
}

void SpriteRenderer::glDisable(int a) {
  // TODO: Implement glDisable
}

void SpriteRenderer::glEnable(int a) {
  // TODO: Implement glEnable
}

void SpriteRenderer::glStencilMask(int a) {
  // TODO: Implement glStencilMask
}

void SpriteRenderer::glClear(int a) {
  // TODO: Implement glClear
}

void SpriteRenderer::glClearColor(int r, int g, int b, int a) {
  // TODO: Implement glClearColor
}

void SpriteRenderer::glStencilFunc(int a, int b, int c) {
  // TODO: Implement glStencilFunc
}

void SpriteRenderer::glStencilOp(int a, int b, int c) {
  // TODO: Implement glStencilOp
}

void SpriteRenderer::glColorMask(int a, int b, int c, int d) {
  // TODO: Implement glColorMask
}

void SpriteRenderer::glAlphaFunc(int a, float b) {
  // TODO: Implement glAlphaFunc
}

void SpriteRenderer::glBlendFunc(int a, int b) {
  // TODO: Implement glBlendFunc
}

void SpriteRenderer::glBlendFuncSeparate(int a, int b, int c, int d) {
  // TODO: Implement glBlendFuncSeparate
}

void SpriteRenderer::glBlendEquation(int a) {
  // TODO: Implement glBlendEquation
}

void SpriteRenderer::renderline(Texture tex, int x1, int y1, int x2, int y2,
                                float r, float g, float b, float a,
                                int thickness) {
  // TODO: Implement renderline
}

void SpriteRenderer::renderline(Texture tex, int x1, int y1, int x2, int y2,
                                float r, float g, float b, float a) {
  // TODO: Implement renderline
}

void SpriteRenderer::render(Texture tex, float x1, float y1, float x2, float y2,
                            float x3, float y3, float x4, float y4, int c1,
                            int c2, int c3, int c4) {
  // TODO: Implement render
}

void SpriteRenderer::render(Texture tex, float x, float y, float width,
                            float height, float r, float g, float b, float a,
                            Consumer<TextureDraw> texdModifier) {
  // TODO: Implement render
}

void SpriteRenderer::renderi(Texture tex, int x, int y, int width, int height,
                             float r, float g, float b, float a,
                             Consumer<TextureDraw> texdModifier) {
  // TODO: Implement renderi
}

void SpriteRenderer::renderRect(int x, int y, int width, int height, float r,
                                float g, float b, float a) {
  // TODO: Implement renderRect
}

void SpriteRenderer::renderPoly(float x1, float y1, float x2, float y2,
                                float x3, float y3, float x4, float y4, float r,
                                float g, float b, float a) {
  // TODO: Implement renderPoly
}

void SpriteRenderer::renderPoly(Texture tex, float x1, float y1, float x2,
                                float y2, float x3, float y3, float x4,
                                float y4, float r, float g, float b, float a) {
  // TODO: Implement renderPoly
}

void SpriteRenderer::buildDrawBuffer(TextureDraw[] textureDraws, Style[] styles,
                                     int int1,
                                     SpriteRenderer.RingBuffer ringBufferx) {
  // TODO: Implement buildDrawBuffer
}

void SpriteRenderer::prePopulating() {
  // TODO: Implement prePopulating
}

void SpriteRenderer::postRender() {
  // TODO: Implement postRender
}

void SpriteRenderer::buildStateDrawBuffer(SpriteRenderState spriteRenderState) {
  // TODO: Implement buildStateDrawBuffer
}

void SpriteRenderer::buildStateUIDrawBuffer(
    SpriteRenderState spriteRenderState) {
  // TODO: Implement buildStateUIDrawBuffer
}

void SpriteRenderer::notifyRenderStateQueue() {
  // TODO: Implement notifyRenderStateQueue
}

void SpriteRenderer::glBuffer(int i, int p) {
  // TODO: Implement glBuffer
}

void SpriteRenderer::glDoStartFrame(int w, int h, float zoom, int player) {
  // TODO: Implement glDoStartFrame
}

void SpriteRenderer::glDoStartFrame(int w, int h, float zoom, int player,
                                    bool isTextFrame) {
  // TODO: Implement glDoStartFrame
}

void SpriteRenderer::glDoStartFrameFx(int w, int h, int player) {
  // TODO: Implement glDoStartFrameFx
}

void SpriteRenderer::glIgnoreStyles(bool b) {
  // TODO: Implement glIgnoreStyles
}

void SpriteRenderer::glDoEndFrame() {
  // TODO: Implement glDoEndFrame
}

void SpriteRenderer::glDoEndFrameFx(int player) {
  // TODO: Implement glDoEndFrameFx
}

void SpriteRenderer::doCoreIntParam(int id, float val) {
  // TODO: Implement doCoreIntParam
}

void SpriteRenderer::glTexParameteri(int a, int b, int c) {
  // TODO: Implement glTexParameteri
}

void SpriteRenderer::StartShader(int iD, int playerIndex) {
  // TODO: Implement StartShader
}

void SpriteRenderer::EndShader() {
  // TODO: Implement EndShader
}

void SpriteRenderer::setCutawayTexture(Texture tex, int x, int y, int w,
                                       int h) {
  // TODO: Implement setCutawayTexture
}

void SpriteRenderer::clearCutawayTexture() {
  // TODO: Implement clearCutawayTexture
}

void SpriteRenderer::setUseVertColorsArray(uint8_t whichShader, int c0, int c1,
                                           int c2, int c3) {
  // TODO: Implement setUseVertColorsArray
}

void SpriteRenderer::clearUseVertColorsArray() {
  // TODO: Implement clearUseVertColorsArray
}

void SpriteRenderer::setExtraWallShaderParams(
    SpriteRenderer.WallShaderTexRender wallTexRender) {
  // TODO: Implement setExtraWallShaderParams
}

void SpriteRenderer::ShaderUpdate1i(int shaderID, int uniform,
                                    int uniformValue) {
  // TODO: Implement ShaderUpdate1i
}

void SpriteRenderer::ShaderUpdate1f(int shaderID, int uniform,
                                    float uniformValue) {
  // TODO: Implement ShaderUpdate1f
}

void SpriteRenderer::ShaderUpdate2f(int shaderID, int uniform, float value1,
                                    float value2) {
  // TODO: Implement ShaderUpdate2f
}

void SpriteRenderer::ShaderUpdate3f(int shaderID, int uniform, float value1,
                                    float value2, float value3) {
  // TODO: Implement ShaderUpdate3f
}

void SpriteRenderer::ShaderUpdate4f(int shaderID, int uniform, float value1,
                                    float value2, float value3, float value4) {
  // TODO: Implement ShaderUpdate4f
}

void SpriteRenderer::glLoadIdentity() {
  // TODO: Implement glLoadIdentity
}

void SpriteRenderer::glGenerateMipMaps(int a) {
  // TODO: Implement glGenerateMipMaps
}

void SpriteRenderer::glBind(int a) {
  // TODO: Implement glBind
}

void SpriteRenderer::glViewport(int x, int y, int width, int height) {
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

SpriteRenderState
SpriteRenderer::acquireStateForRendering(BooleanSupplier waitCallback) {
  // TODO: Implement acquireStateForRendering
  return nullptr;
}

bool SpriteRenderer::waitForReadyState(BooleanSupplier booleanSupplier) {
  // TODO: Implement waitForReadyState
  return false;
}

bool SpriteRenderer::waitForReadyStateInternal(
    BooleanSupplier booleanSupplier) {
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

void SpriteRenderer::setDefaultStyle(AbstractStyle style) {
  // TODO: Implement setDefaultStyle
}

void SpriteRenderer::setDoAdditive(bool bDoAdditive) {
  // TODO: Implement setDoAdditive
}

void SpriteRenderer::initFromIsoCamera(int nPlayer) {
  // TODO: Implement initFromIsoCamera
}

void SpriteRenderer::setRenderingPlayerIndex(int player) {
  // TODO: Implement setRenderingPlayerIndex
}

int SpriteRenderer::getRenderingPlayerIndex() {
  // TODO: Implement getRenderingPlayerIndex
  return 0;
}

PlayerCamera SpriteRenderer::getRenderingPlayerCamera(int userId) {
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

void SpriteRenderer::create() {
  // TODO: Implement create
}

void SpriteRenderer::add(TextureDraw textureDraw0, TextureDraw textureDraw1,
                         Style style) {
  // TODO: Implement add
}

bool SpriteRenderer::prepareCurrentRun(TextureDraw textureDraw0,
                                       TextureDraw textureDraw1, Style style) {
  // TODO: Implement prepareCurrentRun
  return false;
}

bool SpriteRenderer::isStateChanged(TextureDraw textureDraw0,
                                    TextureDraw textureDraw1, Style style,
                                    Texture texture0, Texture texture1,
                                    uint8_t byte0) {
  // TODO: Implement isStateChanged
  return false;
}

void SpriteRenderer::next() {
  // TODO: Implement next
}

void SpriteRenderer::begin() {
  // TODO: Implement begin
}

void SpriteRenderer::render() {
  // TODO: Implement render
}

void SpriteRenderer::growStateRuns() {
  // TODO: Implement growStateRuns
}

void SpriteRenderer::shaderChangedTexture1() {
  // TODO: Implement shaderChangedTexture1
}

void SpriteRenderer::checkShaderChangedTexture1() {
  // TODO: Implement checkShaderChangedTexture1
}

void SpriteRenderer::debugBoundTexture(Texture texture0, int _unit) {
  // TODO: Implement debugBoundTexture
}

std::string SpriteRenderer::toString() {
  // TODO: Implement toString
  return "";
}

void SpriteRenderer::render() {
  // TODO: Implement render
}

} // namespace core
} // namespace zombie
