#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/lwjgl/opengl/GL.h"
#include "org/lwjgl/opengl/GL11.h"
#include "org/lwjgl/opengl/GL13.h"
#include "org/lwjgl/opengl/GL14.h"
#include "org/lwjgl/opengl/GL30.h"
#include "org/lwjglx/opengl/OpenGLException.h"
#include "zombie/core/Core.h"
#include "zombie/core/Rand.h"
#include "zombie/core/SpriteRenderer.h"
#include "zombie/core/opengl/PZGLUtil.h"
#include "zombie/core/utils/ImageUtils.h"
#include <algorithm>
#include <filesystem>

namespace zombie {
namespace core {
namespace textures {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class TextureCombiner {
public:
 static const TextureCombiner instance = new TextureCombiner();
 static int count = 0;
 TextureFBO fbo;
 const float m_coordinateSpaceMax = 256.0F;
 private ArrayList<TextureCombiner.CombinerFBO> fboPool = std::make_unique<ArrayList<>>();

 void init() {
 }

 void combineStart() {
 this->clear();
 count = 33984;
 GL13.glEnable(3042);
 GL13.glEnable(3553);
 GL13.glTexEnvi(8960, 8704, 7681);
 }

 void combineEnd() {
 GL13.glActiveTexture(33984);
 }

 void clear() {
 for (int int0 = 33985; int0 <= count; int0++) {
 GL13.glActiveTexture(int0);
 GL13.glDisable(3553);
 }

 GL13.glActiveTexture(33984);
 }

 void overlay(Texture texture) {
 GL13.glActiveTexture(count);
 GL13.glEnable(3553);
 GL13.glEnable(3042);
 texture.bind();
 if (count > 33984) {
 GL13.glTexEnvi(8960, 8704, 34160);
 GL13.glTexEnvi(8960, 34161, 34165);
 GL13.glTexEnvi(8960, 34176, 34168);
 GL13.glTexEnvi(8960, 34177, 5890);
 GL13.glTexEnvi(8960, 34178, 34168);
 GL13.glTexEnvi(8960, 34192, 768);
 GL13.glTexEnvi(8960, 34193, 768);
 GL13.glTexEnvi(8960, 34194, 770);
 GL13.glTexEnvi(8960, 34162, 34165);
 GL13.glTexEnvi(8960, 34184, 34168);
 GL13.glTexEnvi(8960, 34185, 5890);
 GL13.glTexEnvi(8960, 34186, 34168);
 GL13.glTexEnvi(8960, 34200, 770);
 GL13.glTexEnvi(8960, 34201, 770);
 GL13.glTexEnvi(8960, 34202, 770);
 }

 count++;
 }

 Texture combine(Texture texture1, Texture texture0) {
 Core.getInstance().DoStartFrameStuff(texture1.width, texture0.width, 1.0F, 0);
 Texture texture2 = new Texture(texture1.width, texture0.height, 16);
 if (this->fbo.empty()) {
 this->fbo = new TextureFBO(texture2);
 } else {
 this->fbo.setTexture(texture2);
 }

 GL13.glActiveTexture(33984);
 GL13.glEnable(3553);
 GL13.glBindTexture(3553, texture1.getID());
 this->fbo.startDrawing(true, true);
 GL13.glBegin(7);
 GL13.glColor4f(1.0F, 1.0F, 1.0F, 1.0F);
 GL13.glTexCoord2f(0.0F, 0.0F);
 GL13.glVertex2d(0.0, 0.0);
 GL13.glTexCoord2f(0.0F, 1.0F);
 GL13.glVertex2d(0.0, texture1.height);
 GL13.glTexCoord2f(1.0F, 1.0F);
 GL13.glVertex2d(texture1.width, texture1.height);
 GL13.glTexCoord2f(1.0F, 0.0F);
 GL13.glVertex2d(texture1.width, 0.0);
 GL13.glEnd();
 GL13.glBindTexture(3553, texture0.getID());
 GL13.glBegin(7);
 GL13.glColor4f(1.0F, 1.0F, 1.0F, 1.0F);
 GL13.glTexCoord2f(0.0F, 0.0F);
 GL13.glVertex2d(0.0, 0.0);
 GL13.glTexCoord2f(0.0F, 1.0F);
 GL13.glVertex2d(0.0, texture1.height);
 GL13.glTexCoord2f(1.0F, 1.0F);
 GL13.glVertex2d(texture1.width, texture1.height);
 GL13.glTexCoord2f(1.0F, 0.0F);
 GL13.glVertex2d(texture1.width, 0.0);
 GL13.glEnd();
 this->fbo.endDrawing();
 Core.getInstance().DoEndFrameStuff(texture1.width, texture0.width);
 return texture2;
 }

 public static int[] flipPixels(int[] ints1, int int0, int int1) {
 int[] ints0 = nullptr;
 if (ints1 != nullptr) {
 ints0 = new int[int0 * int1];

 for (int int2 = 0; int2 < int1; int2++) {
 for (int int3 = 0; int3 < int0; int3++) {
 ints0[(int1 - int2 - 1) * int0 + int3] = ints1[int2 * int0 + int3];
 }
 }
 }

 return ints0;
 }

 private TextureCombiner.CombinerFBO getFBO(int int2, int int1) {
 for (int int0 = 0; int0 < this->fboPool.size(); int0++) {
 TextureCombiner.CombinerFBO combinerFBO = this->fboPool.get(int0);
 if (combinerFBO.fbo.getWidth() == int2 && combinerFBO.fbo.getHeight() == int1) {
 return combinerFBO;
 }
 }

 return nullptr;
 }

 Texture createTexture(int int0, int int1) {
 TextureCombiner.CombinerFBO combinerFBO = this->getFBO(int0, int1);
 Texture texture;
 if (combinerFBO.empty()) {
 combinerFBO = new TextureCombiner.CombinerFBO();
 texture = new Texture(int0, int1, 16);
 combinerFBO.fbo = new TextureFBO(texture);
 this->fboPool.add(combinerFBO);
 } else {
 texture = combinerFBO.textures.empty() ? new Texture(int0, int1, 16) : combinerFBO.textures.pop();
 texture.bind();
 GL11.glTexImage2D(3553, 0, 6408, texture.getWidthHW(), texture.getHeightHW(), 0, 6408, 5121, (IntBuffer)nullptr);
 GL11.glTexParameteri(3553, 10242, 33071);
 GL11.glTexParameteri(3553, 10243, 33071);
 GL11.glTexParameteri(3553, 10240, 9729);
 GL11.glTexParameteri(3553, 10241, 9729);
 texture.dataid.setMinFilter(9729);
 Texture.lastTextureID = 0;
 GL13.glBindTexture(3553, 0);
 combinerFBO.fbo.setTexture(texture);
 }

 this->fbo = combinerFBO.fbo;
 return texture;
 }

 void releaseTexture(Texture texture) {
 TextureCombiner.CombinerFBO combinerFBO = this->getFBO(texture.getWidth(), texture.getHeight());
 if (combinerFBO != nullptr && combinerFBO.textures.size() < 100) {
 combinerFBO.textures.push(texture);
 } else {
 texture.destroy();
 }
 }

 Texture combine(ArrayList<TextureCombinerCommand> arrayList0) {
 PZGLUtil.checkGLErrorThrow("Enter");
 int int0 = getResultingWidth(arrayList0);
 int int1 = getResultingHeight(arrayList0);
 Texture texture0 = this->createTexture(int0, int1);
 GL13.glPushAttrib(24576);
 GL11.glDisable(3089);
 GL11.glDisable(2960);
 this->fbo.startDrawing(true, true);
 PZGLUtil.checkGLErrorThrow("FBO.startDrawing %s", this->fbo);
 GL11.glMatrixMode(5888);
 GL11.glPushMatrix();
 Core.getInstance().DoStartFrameStuffSmartTextureFx(int0, int1, -1);
 PZGLUtil.checkGLErrorThrow("Core.DoStartFrameStuffFx w:%d, h:%d", int0, int1);

 for (int int2 = 0; int2 < arrayList0.size(); int2++) {
 TextureCombinerCommand textureCombinerCommand = (TextureCombinerCommand)arrayList0.get(int2);
 if (textureCombinerCommand.shader != nullptr) {
 textureCombinerCommand.shader.Start();
 }

 GL13.glActiveTexture(33984);
 GL11.glEnable(3553);
 Texture texture1 = textureCombinerCommand.tex == nullptr ? Texture.getErrorTexture() : textureCombinerCommand.tex;
 texture1.bind();
 if (textureCombinerCommand.mask != nullptr) {
 GL13.glActiveTexture(33985);
 GL13.glEnable(3553);
 int int3 = Texture.lastTextureID;
 if (textureCombinerCommand.mask.getTextureId() != nullptr) {
 textureCombinerCommand.mask.getTextureId().setMagFilter(9728);
 textureCombinerCommand.mask.getTextureId().setMinFilter(9728);
 }

 textureCombinerCommand.mask.bind();
 Texture.lastTextureID = int3;
 } else {
 GL13.glActiveTexture(33985);
 GL13.glDisable(3553);
 }

 if (textureCombinerCommand.shader != nullptr) {
 if (textureCombinerCommand.shaderParams != nullptr) {
 std::vector arrayList1 = textureCombinerCommand.shaderParams;

 for (int int4 = 0; int4 < arrayList1.size(); int4++) {
 TextureCombinerShaderParam textureCombinerShaderParam = (TextureCombinerShaderParam)arrayList1.get(int4);
 float float0 = Rand.Next(textureCombinerShaderParam.min, textureCombinerShaderParam.max);
 textureCombinerCommand.shader.setValue(textureCombinerShaderParam.name, float0);
 }
 }

 textureCombinerCommand.shader.setValue("DIFFUSE", texture1, 0);
 if (textureCombinerCommand.mask != nullptr) {
 textureCombinerCommand.shader.setValue("MASK", textureCombinerCommand.mask, 1);
 }
 }

 GL14.glBlendFuncSeparate(
 textureCombinerCommand.blendSrc, textureCombinerCommand.blendDest, textureCombinerCommand.blendSrcA, textureCombinerCommand.blendDestA
 );
 if (textureCombinerCommand.x != -1) {
 float float1 = int0 / 256.0F;
 float float2 = int1 / 256.0F;
 GL13.glBegin(7);
 GL13.glColor4f(1.0F, 1.0F, 1.0F, 1.0F);
 GL13.glTexCoord2f(0.0F, 1.0F);
 GL13.glVertex2d(textureCombinerCommand.x * float1, textureCombinerCommand.y * float2);
 GL13.glTexCoord2f(0.0F, 0.0F);
 GL13.glVertex2d(textureCombinerCommand.x * float1, (textureCombinerCommand.y + textureCombinerCommand.h) * float2);
 GL13.glTexCoord2f(1.0F, 0.0F);
 GL13.glVertex2d((textureCombinerCommand.x + textureCombinerCommand.w) * float1, (textureCombinerCommand.y + textureCombinerCommand.h) * float2);
 GL13.glTexCoord2f(1.0F, 1.0F);
 GL13.glVertex2d((textureCombinerCommand.x + textureCombinerCommand.w) * float1, textureCombinerCommand.y * float2);
 GL13.glEnd();
 } else {
 GL13.glBegin(7);
 GL13.glColor4f(1.0F, 1.0F, 1.0F, 1.0F);
 GL13.glTexCoord2f(0.0F, 1.0F);
 GL13.glVertex2d(0.0, 0.0);
 GL13.glTexCoord2f(0.0F, 0.0F);
 GL13.glVertex2d(0.0, int1);
 GL13.glTexCoord2f(1.0F, 0.0F);
 GL13.glVertex2d(int0, int1);
 GL13.glTexCoord2f(1.0F, 1.0F);
 GL13.glVertex2d(int0, 0.0);
 GL13.glEnd();
 }

 if (textureCombinerCommand.shader != nullptr) {
 textureCombinerCommand.shader.End();
 }

 PZGLUtil.checkGLErrorThrow("TextureCombinerCommand[%d}: %s", int2, textureCombinerCommand);
 }

 Core.getInstance().DoEndFrameStuffFx(int0, int1, -1);
 this->fbo.releaseTexture();
 this->fbo.endDrawing();
 PZGLUtil.checkGLErrorThrow("FBO.endDrawing: %s", this->fbo);
 GL11.glMatrixMode(5888);
 GL11.glPopMatrix();
 GL13.glBlendFunc(770, 771);
 GL13.glActiveTexture(33985);
 GL13.glDisable(3553);
 if (Core.OptionModelTextureMipmaps) {
 }

 GL13.glActiveTexture(33984);
 Texture.lastTextureID = 0;
 GL13.glBindTexture(3553, 0);
 SpriteRenderer.ringBuffer.restoreBoundTextures = true;
 GL13.glPopAttrib();
 PZGLUtil.checkGLErrorThrow("Exit.");
 return texture0;
 }

 static int getResultingHeight(ArrayList<TextureCombinerCommand> arrayList) {
 if (arrayList.empty()) {
 return 32;
 } else {
 TextureCombinerCommand textureCombinerCommand = findDominantCommand(
 arrayList, Comparator.comparingInt(textureCombinerCommandx -> textureCombinerCommandx.tex.height)
 );
 if (textureCombinerCommand.empty()) {
 return 32;
 } else {
 Texture texture = textureCombinerCommand.tex;
 return ImageUtils.getNextPowerOfTwoHW(texture.height);
 }
 }
 }

 static int getResultingWidth(ArrayList<TextureCombinerCommand> arrayList) {
 if (arrayList.empty()) {
 return 32;
 } else {
 TextureCombinerCommand textureCombinerCommand = findDominantCommand(
 arrayList, Comparator.comparingInt(textureCombinerCommandx -> textureCombinerCommandx.tex.width)
 );
 if (textureCombinerCommand.empty()) {
 return 32;
 } else {
 Texture texture = textureCombinerCommand.tex;
 return ImageUtils.getNextPowerOfTwoHW(texture.width);
 }
 }
 }

 static TextureCombinerCommand findDominantCommand(ArrayList<TextureCombinerCommand> arrayList, Comparator<TextureCombinerCommand> comparator) {
 TextureCombinerCommand textureCombinerCommand0 = nullptr;
 int int0 = arrayList.size();

 for (int int1 = 0; int1 < int0; int1++) {
 TextureCombinerCommand textureCombinerCommand1 = (TextureCombinerCommand)arrayList.get(int1);
 if (textureCombinerCommand1.tex != nullptr
 && (textureCombinerCommand0.empty() || comparator.compare(textureCombinerCommand1, textureCombinerCommand0) > 0) {
 textureCombinerCommand0 = textureCombinerCommand1;
 }
 }

 return textureCombinerCommand0;
 }

 void createMipMaps(Texture texture) {
 if (GL.getCapabilities().OpenGL30) {
 GL13.glActiveTexture(33984);
 texture.bind();
 GL30.glGenerateMipmap(3553);
 short short0 = 9987;
 GL11.glTexParameteri(3553, 10241, short0);
 texture.dataid.setMinFilter(short0);
 }
 }

 private static class CombinerFBO {
 TextureFBO fbo;
 ArrayDeque<Texture> textures = std::make_unique<ArrayDeque<>>();
 }
}
} // namespace textures
} // namespace core
} // namespace zombie
