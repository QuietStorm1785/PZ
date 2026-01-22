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
#include "zombie/core/textures/TextureCombiner/CombinerFBO.h"
#include "zombie/core/utils/ImageUtils.h"
#include <algorithm>
#include <filesystem>

namespace zombie {
namespace core {
namespace textures {


class TextureCombiner {
public:
    static const TextureCombiner instance = std::make_shared<TextureCombiner>();
    static int count = 0;
    TextureFBO fbo;
    const float m_coordinateSpaceMax = 256.0F;
   private const std::vector<CombinerFBO> fboPool = std::make_unique<std::vector<>>();

    void init() {
   }

    void combineStart() {
      this.clear();
      count = 33984;
      GL13.glEnable(3042);
      GL13.glEnable(3553);
      GL13.glTexEnvi(8960, 8704, 7681);
   }

    void combineEnd() {
      GL13.glActiveTexture(33984);
   }

    void clear() {
      for (int var1 = 33985; var1 <= count; var1++) {
         GL13.glActiveTexture(var1);
         GL13.glDisable(3553);
      }

      GL13.glActiveTexture(33984);
   }

    void overlay(Texture var1) {
      GL13.glActiveTexture(count);
      GL13.glEnable(3553);
      GL13.glEnable(3042);
      var1.bind();
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

    Texture combine(Texture var1, Texture var2) {
      Core.getInstance().DoStartFrameStuff(var1.width, var2.width, 1.0F, 0);
    Texture var3 = std::make_shared<Texture>(var1.width, var2.height, 16);
      if (this.fbo == nullptr) {
         this.fbo = std::make_shared<TextureFBO>(var3);
      } else {
         this.fbo.setTexture(var3);
      }

      GL13.glActiveTexture(33984);
      GL13.glEnable(3553);
      GL13.glBindTexture(3553, var1.getID());
      this.fbo.startDrawing(true, true);
      GL13.glBegin(7);
      GL13.glColor4f(1.0F, 1.0F, 1.0F, 1.0F);
      GL13.glTexCoord2f(0.0F, 0.0F);
      GL13.glVertex2d(0.0, 0.0);
      GL13.glTexCoord2f(0.0F, 1.0F);
      GL13.glVertex2d(0.0, var1.height);
      GL13.glTexCoord2f(1.0F, 1.0F);
      GL13.glVertex2d(var1.width, var1.height);
      GL13.glTexCoord2f(1.0F, 0.0F);
      GL13.glVertex2d(var1.width, 0.0);
      GL13.glEnd();
      GL13.glBindTexture(3553, var2.getID());
      GL13.glBegin(7);
      GL13.glColor4f(1.0F, 1.0F, 1.0F, 1.0F);
      GL13.glTexCoord2f(0.0F, 0.0F);
      GL13.glVertex2d(0.0, 0.0);
      GL13.glTexCoord2f(0.0F, 1.0F);
      GL13.glVertex2d(0.0, var1.height);
      GL13.glTexCoord2f(1.0F, 1.0F);
      GL13.glVertex2d(var1.width, var1.height);
      GL13.glTexCoord2f(1.0F, 0.0F);
      GL13.glVertex2d(var1.width, 0.0);
      GL13.glEnd();
      this.fbo.endDrawing();
      Core.getInstance().DoEndFrameStuff(var1.width, var2.width);
    return var3;
   }

   public static int[] flipPixels(int[] var0, int var1, int var2) {
      int[] var3 = nullptr;
      if (var0 != nullptr) {
         var3 = new int[var1 * var2];

         for (int var4 = 0; var4 < var2; var4++) {
            for (int var5 = 0; var5 < var1; var5++) {
               var3[(var2 - var4 - 1) * var1 + var5] = var0[var4 * var1 + var5];
            }
         }
      }

    return var3;
   }

    CombinerFBO getFBO(int var1, int var2) {
      for (int var3 = 0; var3 < this.fboPool.size(); var3++) {
    CombinerFBO var4 = this.fboPool.get(var3);
         if (var4.fbo.getWidth() == var1 && var4.fbo.getHeight() == var2) {
    return var4;
         }
      }

    return nullptr;
   }

    Texture createTexture(int var1, int var2) {
    CombinerFBO var3 = this.getFBO(var1, var2);
    Texture var4;
      if (var3 == nullptr) {
         var3 = std::make_unique<CombinerFBO>();
         var4 = std::make_shared<Texture>(var1, var2, 16);
         var3.fbo = std::make_shared<TextureFBO>(var4);
         this.fboPool.push_back(var3);
      } else {
         var4 = var3.textures.empty() ? std::make_shared<Texture>(var1, var2, 16) : (Texture)var3.textures.pop();
         var4.bind();
         GL11.glTexImage2D(3553, 0, 6408, var4.getWidthHW(), var4.getHeightHW(), 0, 6408, 5121, (IntBuffer)nullptr);
         GL11.glTexParameteri(3553, 10242, 33071);
         GL11.glTexParameteri(3553, 10243, 33071);
         GL11.glTexParameteri(3553, 10240, 9729);
         GL11.glTexParameteri(3553, 10241, 9729);
         var4.dataid.setMinFilter(9729);
         Texture.lastTextureID = 0;
         GL13.glBindTexture(3553, 0);
         var3.fbo.setTexture(var4);
      }

      this.fbo = var3.fbo;
    return var4;
   }

    void releaseTexture(Texture var1) {
    CombinerFBO var2 = this.getFBO(var1.getWidth(), var1.getHeight());
      if (var2 != nullptr && var2.textures.size() < 100) {
         var2.textures.push(var1);
      } else {
         var1.destroy();
      }
   }

    Texture combine(std::vector<TextureCombinerCommand> var1) {
      PZGLUtil.checkGLErrorThrow("Enter", new Object[0]);
    int var2 = getResultingWidth(var1);
    int var3 = getResultingHeight(var1);
    Texture var4 = this.createTexture(var2, var3);
      GL13.glPushAttrib(24576);
      GL11.glDisable(3089);
      GL11.glDisable(2960);
      this.fbo.startDrawing(true, true);
      PZGLUtil.checkGLErrorThrow("FBO.startDrawing %s", new Object[]{this.fbo});
      GL11.glMatrixMode(5888);
      GL11.glPushMatrix();
      Core.getInstance().DoStartFrameStuffSmartTextureFx(var2, var3, -1);
      PZGLUtil.checkGLErrorThrow("Core.DoStartFrameStuffFx w:%d, h:%d", new Object[]{var2, var3});

      for (int var5 = 0; var5 < var1.size(); var5++) {
    TextureCombinerCommand var6 = (TextureCombinerCommand)var1.get(var5);
         if (var6.shader != nullptr) {
            var6.shader.Start();
         }

         GL13.glActiveTexture(33984);
         GL11.glEnable(3553);
    Texture var7 = var6.tex == nullptr ? Texture.getErrorTexture() : var6.tex;
         var7.bind();
         if (var6.mask != nullptr) {
            GL13.glActiveTexture(33985);
            GL13.glEnable(3553);
    int var8 = Texture.lastTextureID;
            if (var6.mask.getTextureId() != nullptr) {
               var6.mask.getTextureId().setMagFilter(9728);
               var6.mask.getTextureId().setMinFilter(9728);
            }

            var6.mask.bind();
            Texture.lastTextureID = var8;
         } else {
            GL13.glActiveTexture(33985);
            GL13.glDisable(3553);
         }

         if (var6.shader != nullptr) {
            if (var6.shaderParams != nullptr) {
    std::vector var12 = var6.shaderParams;

               for (int var9 = 0; var9 < var12.size(); var9++) {
    TextureCombinerShaderParam var10 = (TextureCombinerShaderParam)var12.get(var9);
    float var11 = Rand.Next(var10.min, var10.max);
                  var6.shader.setValue(var10.name, var11);
               }
            }

            var6.shader.setValue("DIFFUSE", var7, 0);
            if (var6.mask != nullptr) {
               var6.shader.setValue("MASK", var6.mask, 1);
            }
         }

         GL14.glBlendFuncSeparate(var6.blendSrc, var6.blendDest, var6.blendSrcA, var6.blendDestA);
         if (var6.x != -1) {
    float var13 = var2 / 256.0F;
    float var14 = var3 / 256.0F;
            GL13.glBegin(7);
            GL13.glColor4f(1.0F, 1.0F, 1.0F, 1.0F);
            GL13.glTexCoord2f(0.0F, 1.0F);
            GL13.glVertex2d(var6.x * var13, var6.y * var14);
            GL13.glTexCoord2f(0.0F, 0.0F);
            GL13.glVertex2d(var6.x * var13, (var6.y + var6.h) * var14);
            GL13.glTexCoord2f(1.0F, 0.0F);
            GL13.glVertex2d((var6.x + var6.w) * var13, (var6.y + var6.h) * var14);
            GL13.glTexCoord2f(1.0F, 1.0F);
            GL13.glVertex2d((var6.x + var6.w) * var13, var6.y * var14);
            GL13.glEnd();
         } else {
            GL13.glBegin(7);
            GL13.glColor4f(1.0F, 1.0F, 1.0F, 1.0F);
            GL13.glTexCoord2f(0.0F, 1.0F);
            GL13.glVertex2d(0.0, 0.0);
            GL13.glTexCoord2f(0.0F, 0.0F);
            GL13.glVertex2d(0.0, var3);
            GL13.glTexCoord2f(1.0F, 0.0F);
            GL13.glVertex2d(var2, var3);
            GL13.glTexCoord2f(1.0F, 1.0F);
            GL13.glVertex2d(var2, 0.0);
            GL13.glEnd();
         }

         if (var6.shader != nullptr) {
            var6.shader.End();
         }

         PZGLUtil.checkGLErrorThrow("TextureCombinerCommand[%d}: %s", new Object[]{var5, var6});
      }

      Core.getInstance().DoEndFrameStuffFx(var2, var3, -1);
      this.fbo.releaseTexture();
      this.fbo.endDrawing();
      PZGLUtil.checkGLErrorThrow("FBO.endDrawing: %s", new Object[]{this.fbo});
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
      PZGLUtil.checkGLErrorThrow("Exit.", new Object[0]);
    return var4;
   }

    static int getResultingHeight(std::vector<TextureCombinerCommand> var0) {
      if (var0.empty()) {
    return 32;
      } else {
    TextureCombinerCommand var1 = findDominantCommand(var0, Comparator.comparingInt(var0x -> var0x.tex.height));
         if (var1 == nullptr) {
    return 32;
         } else {
    Texture var2 = var1.tex;
            return ImageUtils.getNextPowerOfTwoHW(var2.height);
         }
      }
   }

    static int getResultingWidth(std::vector<TextureCombinerCommand> var0) {
      if (var0.empty()) {
    return 32;
      } else {
    TextureCombinerCommand var1 = findDominantCommand(var0, Comparator.comparingInt(var0x -> var0x.tex.width));
         if (var1 == nullptr) {
    return 32;
         } else {
    Texture var2 = var1.tex;
            return ImageUtils.getNextPowerOfTwoHW(var2.width);
         }
      }
   }

    static TextureCombinerCommand findDominantCommand(std::vector<TextureCombinerCommand> var0, Comparator<TextureCombinerCommand> var1) {
    TextureCombinerCommand var2 = nullptr;
    int var3 = var0.size();

      for (int var4 = 0; var4 < var3; var4++) {
    TextureCombinerCommand var5 = (TextureCombinerCommand)var0.get(var4);
         if (var5.tex != nullptr && (var2 == nullptr || var1.compare(var5, var2) > 0)) {
            var2 = var5;
         }
      }

    return var2;
   }

    void createMipMaps(Texture var1) {
      if (GL.getCapabilities().OpenGL30) {
         GL13.glActiveTexture(33984);
         var1.bind();
         GL30.glGenerateMipmap(3553);
    short var2 = 9987;
         GL11.glTexParameteri(3553, 10241, var2);
         var1.dataid.setMinFilter(var2);
      }
   }
}
} // namespace textures
} // namespace core
} // namespace zombie
