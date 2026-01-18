#include "zombie/core/sprite/GenericSpriteRenderState.h"

namespace zombie {
namespace core {
namespace sprite {

protected
GenericSpriteRenderState::GenericSpriteRenderState(int int0) {
  // TODO: Implement GenericSpriteRenderState
  return nullptr;
}

void GenericSpriteRenderState::onRendered() {
  // TODO: Implement onRendered
}

void GenericSpriteRenderState::onRenderAcquired() {
  // TODO: Implement onRenderAcquired
}

bool GenericSpriteRenderState::isRendering() {
  // TODO: Implement isRendering
  return false;
}

void GenericSpriteRenderState::onReady() {
  // TODO: Implement onReady
}

bool GenericSpriteRenderState::isReady() {
  // TODO: Implement isReady
  return false;
}

bool GenericSpriteRenderState::isRendered() {
  // TODO: Implement isRendered
  return false;
}

void GenericSpriteRenderState::CheckSpriteSlots() {
  // TODO: Implement CheckSpriteSlots
}

void GenericSpriteRenderState::clearSprites(List<TextureDraw> _postRender) {
  // TODO: Implement clearSprites
}

void GenericSpriteRenderState::clear() {
  // TODO: Implement clear
}

void GenericSpriteRenderState::glDepthMask(bool b) {
  // TODO: Implement glDepthMask
}

void GenericSpriteRenderState::renderflipped(
    Texture tex, float x, float y, float width, float height, float r, float g,
    float b, float a, Consumer<TextureDraw> texdModifier) {
  // TODO: Implement renderflipped
}

void GenericSpriteRenderState::drawSkyBox(Shader shader, int playerIndex,
                                          int apiId, int bufferId) {
  // TODO: Implement drawSkyBox
}

void GenericSpriteRenderState::drawWater(Shader shader, int playerIndex,
                                         int apiId, bool bShore) {
  // TODO: Implement drawWater
}

void GenericSpriteRenderState::drawPuddles(Shader shader, int playerIndex,
                                           int apiId, int z) {
  // TODO: Implement drawPuddles
}

void GenericSpriteRenderState::drawParticles(int playerIndex, int var1,
                                             int var2) {
  // TODO: Implement drawParticles
}

void GenericSpriteRenderState::glDisable(int a) {
  // TODO: Implement glDisable
}

void GenericSpriteRenderState::glEnable(int a) {
  // TODO: Implement glEnable
}

void GenericSpriteRenderState::glStencilMask(int a) {
  // TODO: Implement glStencilMask
}

void GenericSpriteRenderState::glClear(int a) {
  // TODO: Implement glClear
}

void GenericSpriteRenderState::glClearColor(int r, int g, int b, int a) {
  // TODO: Implement glClearColor
}

void GenericSpriteRenderState::glStencilFunc(int a, int b, int c) {
  // TODO: Implement glStencilFunc
}

void GenericSpriteRenderState::glStencilOp(int a, int b, int c) {
  // TODO: Implement glStencilOp
}

void GenericSpriteRenderState::glColorMask(int a, int b, int c, int d) {
  // TODO: Implement glColorMask
}

void GenericSpriteRenderState::glAlphaFunc(int a, float b) {
  // TODO: Implement glAlphaFunc
}

void GenericSpriteRenderState::glBlendFunc(int a, int b) {
  // TODO: Implement glBlendFunc
}

void GenericSpriteRenderState::glBlendFuncSeparate(int a, int b, int c, int d) {
  // TODO: Implement glBlendFuncSeparate
}

void GenericSpriteRenderState::glBlendEquation(int a) {
  // TODO: Implement glBlendEquation
}

void GenericSpriteRenderState::setUseVertColorsArray(uint8_t whichShader,
                                                     int c0, int c1, int c2,
                                                     int c3) {
  // TODO: Implement setUseVertColorsArray
}

void GenericSpriteRenderState::clearUseVertColorsArray() {
  // TODO: Implement clearUseVertColorsArray
}

void GenericSpriteRenderState::renderline(Texture tex, float x1, float y1,
                                          float x2, float y2, float r, float g,
                                          float b, float a, int thickness) {
  // TODO: Implement renderline
}

void GenericSpriteRenderState::renderline(Texture tex, int x1, int y1, int x2,
                                          int y2, float r, float g, float b,
                                          float a) {
  // TODO: Implement renderline
}

void GenericSpriteRenderState::render(Texture tex, float x1, float y1, float x2,
                                      float y2, float x3, float y3, float x4,
                                      float y4, int c1, int c2, int c3,
                                      int c4) {
  // TODO: Implement render
}

void GenericSpriteRenderState::render(Texture tex, float x, float y,
                                      float width, float height, float r,
                                      float g, float b, float a,
                                      Consumer<TextureDraw> texdModifier) {
  // TODO: Implement render
}

void GenericSpriteRenderState::renderRect(int x, int y, int width, int height,
                                          float r, float g, float b, float a) {
  // TODO: Implement renderRect
}

void GenericSpriteRenderState::renderPoly(float x1, float y1, float x2,
                                          float y2, float x3, float y3,
                                          float x4, float y4, float r, float g,
                                          float b, float a) {
  // TODO: Implement renderPoly
}

void GenericSpriteRenderState::renderPoly(Texture tex, float x1, float y1,
                                          float x2, float y2, float x3,
                                          float y3, float x4, float y4, float r,
                                          float g, float b, float a) {
  // TODO: Implement renderPoly
}

void GenericSpriteRenderState::glBuffer(int i, int p) {
  // TODO: Implement glBuffer
}

void GenericSpriteRenderState::glDoStartFrame(int w, int h, float zoom,
                                              int player) {
  // TODO: Implement glDoStartFrame
}

void GenericSpriteRenderState::glDoStartFrame(int w, int h, float zoom,
                                              int player, bool isTextFrame) {
  // TODO: Implement glDoStartFrame
}

void GenericSpriteRenderState::glDoStartFrameFx(int w, int h, int player) {
  // TODO: Implement glDoStartFrameFx
}

void GenericSpriteRenderState::glIgnoreStyles(bool b) {
  // TODO: Implement glIgnoreStyles
}

void GenericSpriteRenderState::glDoEndFrame() {
  // TODO: Implement glDoEndFrame
}

void GenericSpriteRenderState::glDoEndFrameFx(int player) {
  // TODO: Implement glDoEndFrameFx
}

void GenericSpriteRenderState::doCoreIntParam(int id, float val) {
  // TODO: Implement doCoreIntParam
}

void GenericSpriteRenderState::glTexParameteri(int a, int b, int c) {
  // TODO: Implement glTexParameteri
}

void GenericSpriteRenderState::setCutawayTexture(Texture tex, int x, int y,
                                                 int w, int h) {
  // TODO: Implement setCutawayTexture
}

void GenericSpriteRenderState::clearCutawayTexture() {
  // TODO: Implement clearCutawayTexture
}

void GenericSpriteRenderState::setExtraWallShaderParams(
    SpriteRenderer.WallShaderTexRender wallTexRender) {
  // TODO: Implement setExtraWallShaderParams
}

void GenericSpriteRenderState::ShaderUpdate1i(int shaderID, int uniform,
                                              int uniformValue) {
  // TODO: Implement ShaderUpdate1i
}

void GenericSpriteRenderState::ShaderUpdate1f(int shaderID, int uniform,
                                              float uniformValue) {
  // TODO: Implement ShaderUpdate1f
}

void GenericSpriteRenderState::ShaderUpdate2f(int shaderID, int uniform,
                                              float value1, float value2) {
  // TODO: Implement ShaderUpdate2f
}

void GenericSpriteRenderState::ShaderUpdate3f(int shaderID, int uniform,
                                              float value1, float value2,
                                              float value3) {
  // TODO: Implement ShaderUpdate3f
}

void GenericSpriteRenderState::ShaderUpdate4f(int shaderID, int uniform,
                                              float value1, float value2,
                                              float value3, float value4) {
  // TODO: Implement ShaderUpdate4f
}

void GenericSpriteRenderState::glLoadIdentity() {
  // TODO: Implement glLoadIdentity
}

void GenericSpriteRenderState::glGenerateMipMaps(int a) {
  // TODO: Implement glGenerateMipMaps
}

void GenericSpriteRenderState::glBind(int a) {
  // TODO: Implement glBind
}

void GenericSpriteRenderState::glViewport(int x, int y, int width, int height) {
  // TODO: Implement glViewport
}

void GenericSpriteRenderState::drawModel(ModelManager.ModelSlot model) {
  // TODO: Implement drawModel
}

void GenericSpriteRenderState::drawGeneric(TextureDraw.GenericDrawer gd) {
  // TODO: Implement drawGeneric
}

void GenericSpriteRenderState::StartShader(int iD, int playerIndex) {
  // TODO: Implement StartShader
}

void GenericSpriteRenderState::EndShader() {
  // TODO: Implement EndShader
}

} // namespace sprite
} // namespace core
} // namespace zombie
