#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <GL/glew.h>
#include "zombie/asset/Asset.h"
#include "zombie/core/SpriteRenderer/RingBuffer/StateRun.h"
#include "zombie/core/Styles/AlphaOp.h"
#include "zombie/core/Styles/Style.h"
#include "zombie/core/VBO/GLVertexBufferObject.h"
#include "zombie/core/textures/Texture.h"
#include "zombie/core/textures/TextureAssetManager.h"
#include "zombie/core/textures/TextureDraw.h"
#include "zombie/core/textures/TextureDraw/Type.h"
#include "zombie/debug/DebugLog.h"
#include <filesystem>

namespace zombie {
namespace core {


class SpriteRenderer {
public:
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
   StateRun[] stateRun;
    bool restoreVBOs;
    bool restoreBoundTextures;
    int vertexCursor;
    int indexCursor;
    int numRuns;
    StateRun currentRun;
    static bool IGNORE_STYLES = false;

   SpriteRenderer$RingBuffer() {
   }

    void create() {
      GL11.glEnableClientState(32884);
      GL11.glEnableClientState(32886);
      GL11.glEnableClientState(32888);
      this.bufferSize = 65536L;
      this.numBuffers = Core.bDebug ? 256 : 128;
      this.bufferSizeInVertices = this.bufferSize / 32L;
      this.indexBufferSize = this.bufferSizeInVertices * 3L;
      this.vertices = new FloatBuffer[this.numBuffers];
      this.verticesBytes = new ByteBuffer[this.numBuffers];
      this.indices = new ShortBuffer[this.numBuffers];
      this.indicesBytes = new ByteBuffer[this.numBuffers];
      this.stateRun = new StateRun[5000];

      for (int var1 = 0; var1 < 5000; var1++) {
         this.stateRun[var1] = std::make_shared<StateRun>(this);
      }

      this.vbo = new GLVertexBufferObject[this.numBuffers];
      this.ibo = new GLVertexBufferObject[this.numBuffers];

      for (int var2 = 0; var2 < this.numBuffers; var2++) {
         this.vbo[var2] = std::make_shared<GLVertexBufferObject>(this.bufferSize, GLVertexBufferObject.funcs.GL_ARRAY_BUFFER(), GLVertexBufferObject.funcs.GL_STREAM_DRAW());
         this.vbo[var2].create();
         this.ibo[var2] = std::make_shared<GLVertexBufferObject>(
            this.indexBufferSize, GLVertexBufferObject.funcs.GL_ELEMENT_ARRAY_BUFFER(), GLVertexBufferObject.funcs.GL_STREAM_DRAW()
         );
         this.ibo[var2].create();
      }
   }

    void add(TextureDraw var1, TextureDraw var2, Style var3) {
      if (var3 != nullptr) {
         if (this.vertexCursor + 4 > this.bufferSizeInVertices || this.indexCursor + 6 > this.indexBufferSize) {
            this.render();
            this.next();
         }

         if (this.prepareCurrentRun(var1, var2, var3)) {
    FloatBuffer var4 = this.currentVertices;
    AlphaOp var5 = var3.getAlphaOp();
            var4.put(var1.x0);
            var4.put(var1.y0);
            if (var1.tex == nullptr) {
               var4.put(0.0F);
               var4.put(0.0F);
            } else {
               if (var1.flipped) {
                  var4.put(var1.u1);
               } else {
                  var4.put(var1.u0);
               }

               var4.put(var1.v0);
            }

            if (var1.tex1 == nullptr) {
               var4.put(0.0F);
               var4.put(0.0F);
            } else {
               var4.put(var1.tex1_u0);
               var4.put(var1.tex1_v0);
            }

            var4.put(float.intBitsToFloat(var1.useAttribArray != -1 ? var1.tex1_col0 : 0));
    int var6 = var1.getColor(0);
            var5.op(var6, 255, var4);
            var4.put(var1.x1);
            var4.put(var1.y1);
            if (var1.tex == nullptr) {
               var4.put(0.0F);
               var4.put(0.0F);
            } else {
               if (var1.flipped) {
                  var4.put(var1.u0);
               } else {
                  var4.put(var1.u1);
               }

               var4.put(var1.v1);
            }

            if (var1.tex1 == nullptr) {
               var4.put(0.0F);
               var4.put(0.0F);
            } else {
               var4.put(var1.tex1_u1);
               var4.put(var1.tex1_v1);
            }

            var4.put(float.intBitsToFloat(var1.useAttribArray != -1 ? var1.tex1_col1 : 0));
            var6 = var1.getColor(1);
            var5.op(var6, 255, var4);
            var4.put(var1.x2);
            var4.put(var1.y2);
            if (var1.tex == nullptr) {
               var4.put(0.0F);
               var4.put(0.0F);
            } else {
               if (var1.flipped) {
                  var4.put(var1.u3);
               } else {
                  var4.put(var1.u2);
               }

               var4.put(var1.v2);
            }

            if (var1.tex1 == nullptr) {
               var4.put(0.0F);
               var4.put(0.0F);
            } else {
               var4.put(var1.tex1_u2);
               var4.put(var1.tex1_v2);
            }

            var4.put(float.intBitsToFloat(var1.useAttribArray != -1 ? var1.tex1_col2 : 0));
            var6 = var1.getColor(2);
            var5.op(var6, 255, var4);
            var4.put(var1.x3);
            var4.put(var1.y3);
            if (var1.tex == nullptr) {
               var4.put(0.0F);
               var4.put(0.0F);
            } else {
               if (var1.flipped) {
                  var4.put(var1.u2);
               } else {
                  var4.put(var1.u3);
               }

               var4.put(var1.v3);
            }

            if (var1.tex1 == nullptr) {
               var4.put(0.0F);
               var4.put(0.0F);
            } else {
               var4.put(var1.tex1_u3);
               var4.put(var1.tex1_v3);
            }

            var4.put(float.intBitsToFloat(var1.useAttribArray != -1 ? var1.tex1_col3 : 0));
            var6 = var1.getColor(3);
            var5.op(var6, 255, var4);
            this.currentIndices.put((short)this.vertexCursor);
            this.currentIndices.put((short)(this.vertexCursor + 1));
            this.currentIndices.put((short)(this.vertexCursor + 2));
            this.currentIndices.put((short)this.vertexCursor);
            this.currentIndices.put((short)(this.vertexCursor + 2));
            this.currentIndices.put((short)(this.vertexCursor + 3));
            this.indexCursor += 6;
            this.vertexCursor += 4;
            this.currentRun.endIndex += 6;
            this.currentRun.length += 4;
         }
      }
   }

    bool prepareCurrentRun(TextureDraw var1, TextureDraw var2, Style var3) {
    Texture var4 = var1.tex;
    Texture var5 = var1.tex1;
    uint8_t var6 = var1.useAttribArray;
      if (this.isStateChanged(var1, var2, var3, var4, var5, var6)) {
         this.currentRun = this.stateRun[this.numRuns];
         this.currentRun.start = this.vertexCursor;
         this.currentRun.length = 0;
         this.currentRun.style = var3;
         this.currentRun.texture0 = var4;
         this.currentRun.texture1 = var5;
         this.currentRun.useAttribArray = var6;
         this.currentRun.indices = this.currentIndices;
         this.currentRun.startIndex = this.indexCursor;
         this.currentRun.endIndex = this.indexCursor;
         this.numRuns++;
         if (this.numRuns == this.stateRun.length) {
            this.growStateRuns();
         }

         this.currentStyle = var3;
         this.currentTexture0 = var4;
         this.currentTexture1 = var5;
         this.currentUseAttribArray = var6;
      }

      if (var1.type != Type.glDraw) {
         this.currentRun.ops.push_back(var1);
    return false;
      } else {
    return true;
      }
   }

    bool isStateChanged(TextureDraw var1, TextureDraw var2, Style var3, Texture var4, Texture var5, uint8_t var6) {
      if (this.currentRun == nullptr) {
    return true;
      } else if (var1.type == Type.DrawModel) {
    return true;
      } else if (var6 != this.currentUseAttribArray) {
    return true;
      } else if (var4 != this.currentTexture0) {
    return true;
      } else if (var5 != this.currentTexture1) {
    return true;
      } else {
         if (var2 != nullptr) {
            if (var2.type == Type.DrawModel) {
    return true;
            }

            if (var1.type == Type.glDraw && var2.type != Type.glDraw) {
    return true;
            }

            if (var1.type != Type.glDraw && var2.type == Type.glDraw) {
    return true;
            }
         }

         if (var3 != this.currentStyle) {
            if (this.currentStyle == nullptr) {
    return true;
            }

            if (var3.getStyleID() != this.currentStyle.getStyleID()) {
    return true;
            }
         }

    return false;
      }
   }

    void next() {
      this.sequence++;
      if (this.sequence == this.numBuffers) {
         this.sequence = 0;
      }

      if (this.sequence == this.mark) {
         DebugLog.General.error("Buffer overrun.");
      }

      this.vbo[this.sequence].bind();
    ByteBuffer var1 = this.vbo[this.sequence].map();
      if (this.vertices[this.sequence] == nullptr || this.verticesBytes[this.sequence] != var1) {
         this.verticesBytes[this.sequence] = var1;
         this.vertices[this.sequence] = var1.asFloatBuffer();
      }

      this.ibo[this.sequence].bind();
    ByteBuffer var2 = this.ibo[this.sequence].map();
      if (this.indices[this.sequence] == nullptr || this.indicesBytes[this.sequence] != var2) {
         this.indicesBytes[this.sequence] = var2;
         this.indices[this.sequence] = var2.asShortBuffer();
      }

      this.currentVertices = this.vertices[this.sequence];
      this.currentVertices.clear();
      this.currentIndices = this.indices[this.sequence];
      this.currentIndices.clear();
      this.vertexCursor = 0;
      this.indexCursor = 0;
      this.numRuns = 0;
      this.currentRun = nullptr;
   }

    void begin() {
      this.currentStyle = nullptr;
      this.currentTexture0 = nullptr;
      this.currentTexture1 = nullptr;
      this.currentUseAttribArray = -1;
      this.next();
      this.mark = this.sequence;
   }

    void render() {
      this.vbo[this.sequence].unmap();
      this.ibo[this.sequence].unmap();
      this.restoreVBOs = true;

      for (int var1 = 0; var1 < this.numRuns; var1++) {
         this.stateRun[var1].render();
      }
   }

    void growStateRuns() {
      StateRun[] var1 = new StateRun[(int)(this.stateRun.length * 1.5F)];
      System.arraycopy(this.stateRun, 0, var1, 0, this.stateRun.length);

      for (int var2 = this.numRuns; var2 < var1.length; var2++) {
         var1[var2] = std::make_shared<StateRun>(this);
      }

      this.stateRun = var1;
   }

    void shaderChangedTexture1() {
      this.shaderChangedTexture1 = true;
   }

    void checkShaderChangedTexture1() {
      if (this.shaderChangedTexture1) {
         this.shaderChangedTexture1 = false;
         this.lastRenderedTexture1 = nullptr;
         GL13.glActiveTexture(33985);
         GL13.glClientActiveTexture(33985);
         GL11.glDisable(3553);
         GL13.glActiveTexture(33984);
         GL13.glClientActiveTexture(33984);
      }
   }

    void debugBoundTexture(Texture var1, int var2) {
      if (GL11.glGetInteger(34016) == var2) {
    int var3 = GL11.glGetInteger(32873);
    std::string var4 = nullptr;
         if (var1 == nullptr && var3 != 0) {
            for (Asset var9 : TextureAssetManager.instance.getAssetTable().values()) {
    Texture var10 = (Texture)var9;
               if (var10.getID() == var3) {
                  var4 = var10.getPath().getPath();
                  break;
               }
            }

            DebugLog.General.error("SpriteRenderer.lastBoundTexture0=nullptr doesn't match OpenGL texture id=" + var3 + " " + var4);
         } else if (var1 != nullptr && var1.getID() != -1 && var3 != var1.getID()) {
            for (Asset var6 : TextureAssetManager.instance.getAssetTable().values()) {
    Texture var7 = (Texture)var6;
               if (var7.getID() == var3) {
                  var4 = var7.getName();
                  break;
               }
            }

            DebugLog.General.error("SpriteRenderer.lastBoundTexture0 id=" + var1.getID() + " doesn't match OpenGL texture id=" + var3 + " " + var4);
         }
      }
   }
}
} // namespace core
} // namespace zombie
