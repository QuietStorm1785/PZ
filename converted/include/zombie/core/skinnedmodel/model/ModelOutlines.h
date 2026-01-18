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
#include "zombie/core/textures/ColorInfo.h"
#include "zombie/core/textures/Texture.h"
#include "zombie/core/textures/TextureDraw.h"
#include "zombie/core/textures/TextureFBO.h"
#include "zombie/interfaces/ITexture.h"
#include "zombie/iso/IsoCamera.h"
#include "zombie/popman/ObjectPool.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace model {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class ModelOutlines {
public:
 static const ModelOutlines instance = new ModelOutlines();
 TextureFBO m_fboA;
 TextureFBO m_fboB;
 TextureFBO m_fboC;
 bool m_dirty = false;
 int m_playerIndex;
 const ColorInfo m_outlineColor = new ColorInfo();
 ModelSlotRenderData m_playerRenderData;
 ShaderProgram m_thickenHShader;
 ShaderProgram m_thickenVShader;
 ShaderProgram m_blitShader;
 private ObjectPool<ModelOutlines.Drawer> m_drawerPool = new ObjectPool<>(ModelOutlines.Drawer::new);

 void startFrameMain(int int0) {
 ModelOutlines.Drawer drawer = this->m_drawerPool.alloc();
 drawer.m_startFrame = true;
 drawer.m_playerIndex = int0;
 SpriteRenderer.instance.drawGeneric(drawer);
 }

 void endFrameMain(int int0) {
 ModelOutlines.Drawer drawer = this->m_drawerPool.alloc();
 drawer.m_startFrame = false;
 drawer.m_playerIndex = int0;
 SpriteRenderer.instance.drawGeneric(drawer);
 }

 void startFrame(int int0) {
 this->m_dirty = false;
 this->m_playerIndex = int0;
 this->m_playerRenderData = nullptr;
 }

 void checkFBOs() {
 if (this->m_fboA != nullptr && (this->m_fboA.getWidth() != Core.width || this->m_fboB.getHeight() != Core.height) {
 this->m_fboA.destroy();
 this->m_fboB.destroy();
 this->m_fboC.destroy();
 this->m_fboA = nullptr;
 this->m_fboB = nullptr;
 this->m_fboC = nullptr;
 }

 if (this->m_fboA == nullptr) {
 Texture texture0 = new Texture(Core.width, Core.height, 16);
 this->m_fboA = new TextureFBO(texture0, false);
 Texture texture1 = new Texture(Core.width, Core.height, 16);
 this->m_fboB = new TextureFBO(texture1, false);
 Texture texture2 = new Texture(Core.width, Core.height, 16);
 this->m_fboC = new TextureFBO(texture2, false);
 }
 }

 void setPlayerRenderData(ModelSlotRenderData modelSlotRenderData) {
 this->m_playerRenderData = modelSlotRenderData;
 }

 bool beginRenderOutline(ColorInfo colorInfo) {
 this->m_outlineColor.set(colorInfo);
 if (this->m_dirty) {
 return false;
 } else {
 this->m_dirty = true;
 this->checkFBOs();
 return true;
 }
 }

 void endFrame(int int0) {
 if (this->m_dirty) {
 this->m_playerIndex = int0;
 if (this->m_thickenHShader == nullptr) {
 this->m_thickenHShader = ShaderProgram.createShaderProgram("aim_outline_h", false, true);
 this->m_thickenVShader = ShaderProgram.createShaderProgram("aim_outline_v", false, true);
 this->m_blitShader = ShaderProgram.createShaderProgram("aim_outline_blit", false, true);
 }

 int int1 = IsoCamera.getScreenLeft(this->m_playerIndex);
 int int2 = IsoCamera.getScreenTop(this->m_playerIndex);
 int int3 = IsoCamera.getScreenWidth(this->m_playerIndex);
 int int4 = IsoCamera.getScreenHeight(this->m_playerIndex);
 GL11.glMatrixMode(5889);
 GL11.glPushMatrix();
 GL11.glLoadIdentity();
 GLU.gluOrtho2D(0.0F, int3, int4, 0.0F);
 GL11.glMatrixMode(5888);
 GL11.glPushMatrix();
 GL11.glLoadIdentity();
 float float0 = this->m_fboA.getWidth();
 float float1 = this->m_fboA.getHeight();
 float float2 = SpriteRenderer.instance.getPlayerZoomLevel();
 float float3 = PZMath.lerp(0.5F, 0.2F, float2 / 2.5F);
 this->m_fboB.startDrawing(true, true);
 GL11.glViewport(int1, int2, int3, int4);
 this->m_thickenHShader.Start();
 this->m_thickenHShader.setVector2("u_resolution", float0, float1);
 this->m_thickenHShader.setValue("u_radius", float3);
 this->m_thickenHShader.setVector4("u_color", this->m_outlineColor.r, this->m_outlineColor.g, this->m_outlineColor.b, this->m_outlineColor.a);
 this->renderTexture(this->m_fboA.getTexture(), int1, int2, int3, int4);
 this->m_thickenHShader.End();
 this->m_fboB.endDrawing();
 this->m_fboC.startDrawing(true, true);
 GL11.glViewport(int1, int2, int3, int4);
 this->m_thickenVShader.Start();
 this->m_thickenVShader.setVector2("u_resolution", float0, float1);
 this->m_thickenVShader.setValue("u_radius", float3);
 this->m_thickenVShader.setVector4("u_color", this->m_outlineColor.r, this->m_outlineColor.g, this->m_outlineColor.b, this->m_outlineColor.a);
 this->renderTexture(this->m_fboB.getTexture(), int1, int2, int3, int4);
 this->m_thickenVShader.End();
 this->m_fboC.endDrawing();
 if (this->m_playerRenderData != nullptr) {
 CharacterModelCamera.instance.m_x = this->m_playerRenderData.x;
 CharacterModelCamera.instance.m_y = this->m_playerRenderData.y;
 CharacterModelCamera.instance.m_z = this->m_playerRenderData.z;
 CharacterModelCamera.instance.m_bInVehicle = this->m_playerRenderData.bInVehicle;
 CharacterModelCamera.instance.m_useAngle = this->m_playerRenderData.animPlayerAngle;
 CharacterModelCamera.instance.m_bUseWorldIso = true;
 CharacterModelCamera.instance.bDepthMask = false;
 ModelCamera.instance = CharacterModelCamera.instance;
 GL11.glViewport(int1, int2, int3, int4);
 this->m_playerRenderData.performRenderCharacterOutline();
 }

 GL11.glViewport(int1, int2, int3, int4);
 this->m_blitShader.Start();
 this->m_blitShader.setSamplerUnit("texture", 0);
 this->m_blitShader.setSamplerUnit("mask", 1);
 GL13.glActiveTexture(33985);
 GL11.glBindTexture(3553, this->m_fboA.getTexture().getID());
 GL13.glActiveTexture(33984);
 this->renderTexture(this->m_fboC.getTexture(), int1, int2, int3, int4);
 this->m_blitShader.End();
 GL11.glMatrixMode(5889);
 GL11.glPopMatrix();
 GL11.glMatrixMode(5888);
 GL11.glPopMatrix();
 SpriteRenderer.ringBuffer.restoreBoundTextures = true;
 }
 }

 void renderTexture(ITexture iTexture, int int0, int int1, int int2, int int3) {
 iTexture.bind();
 float float0 = (float)int0 / iTexture.getWidthHW();
 float float1 = (float)int1 / iTexture.getHeightHW();
 float float2 = (float)(int0 + int2) / iTexture.getWidthHW();
 float float3 = (float)(int1 + int3) / iTexture.getHeightHW();
 uint8_t byte0 = 0;
 uint8_t byte1 = 0;
 GL11.glDepthMask(false);
 GL11.glColor4f(1.0F, 1.0F, 1.0F, 1.0F);
 GL11.glBegin(7);
 GL11.glTexCoord2f(float0, float3);
 GL11.glVertex2i(byte1, byte0);
 GL11.glTexCoord2f(float2, float3);
 GL11.glVertex2i(byte1 + int2, byte0);
 GL11.glTexCoord2f(float2, float1);
 GL11.glVertex2i(byte1 + int2, byte0 + int3);
 GL11.glTexCoord2f(float0, float1);
 GL11.glVertex2i(byte1, byte0 + int3);
 GL11.glEnd();
 GL11.glDepthMask(true);
 }

 void renderDebug() {
 }

 public static class Drawer extends TextureDraw.GenericDrawer {
 bool m_startFrame;
 int m_playerIndex;

 void render() {
 if (this->m_startFrame) {
 ModelOutlines.instance.startFrame(this->m_playerIndex);
 } else {
 ModelOutlines.instance.endFrame(this->m_playerIndex);
 }
 }

 void postRender() {
 ModelOutlines.instance.m_drawerPool.release(this);
 }
 }
}
} // namespace model
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
