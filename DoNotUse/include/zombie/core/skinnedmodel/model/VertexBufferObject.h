#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/lwjgl/opengl/GL20.h"
#include "org/lwjgl/system/MemoryUtil.h"
#include "org/lwjglx/BufferUtils.h"
#include "zombie/core/VBO/IGLBufferObject.h"
#include "zombie/core/opengl/RenderThread.h"
#include "zombie/core/skinnedmodel/model/VertexBufferObject/1.h"
#include "zombie/core/skinnedmodel/model/VertexBufferObject/BeginMode.h"
#include "zombie/core/skinnedmodel/model/VertexBufferObject/Vbo.h"
#include "zombie/core/skinnedmodel/model/VertexBufferObject/VertexArray.h"
#include "zombie/core/skinnedmodel/model/VertexBufferObject/VertexElement.h"
#include "zombie/core/skinnedmodel/model/VertexBufferObject/VertexFormat.h"
#include "zombie/core/skinnedmodel/model/VertexBufferObject/VertexType.h"
#include "zombie/core/skinnedmodel/shader/Shader.h"
#include "zombie/debug/DebugOptions.h"
#include <filesystem>

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace model {


class VertexBufferObject {
public:
    static IGLBufferObject funcs;
   int[] elements;
    Vbo _handle;
    const VertexFormat m_vertexFormat;
    BeginMode _beginMode;
    bool bStatic = false;

    public VertexBufferObject() {
      this.bStatic = false;
      this.m_vertexFormat = std::make_shared<VertexFormat>(4);
      this.m_vertexFormat.setElement(0, VertexType.VertexArray, 12);
      this.m_vertexFormat.setElement(1, VertexType.NormalArray, 12);
      this.m_vertexFormat.setElement(2, VertexType.ColorArray, 4);
      this.m_vertexFormat.setElement(3, VertexType.TextureCoordArray, 8);
      this.m_vertexFormat.calculate();
      this._beginMode = BeginMode.Triangles;
   }

    public VertexBufferObject(VertexPositionNormalTangentTexture[] var1, int[] var2) {
      this.elements = var2;
      this.bStatic = true;
      RenderThread.invokeOnRenderContext(this, var1, var2, (var1x, var2x, var3) -> var1x._handle = this.LoadVBO(var2x, var3));
      this.m_vertexFormat = std::make_shared<VertexFormat>(4);
      this.m_vertexFormat.setElement(0, VertexType.VertexArray, 12);
      this.m_vertexFormat.setElement(1, VertexType.NormalArray, 12);
      this.m_vertexFormat.setElement(2, VertexType.TangentArray, 12);
      this.m_vertexFormat.setElement(3, VertexType.TextureCoordArray, 8);
      this.m_vertexFormat.calculate();
      this._beginMode = BeginMode.Triangles;
   }

    public VertexBufferObject(VertexPositionNormalTangentTextureSkin[] var1, int[] var2, bool var3) {
      this.elements = var2;
      if (var3) {
         int[] var4 = new int[var2.length];
    uint8_t var5 = 0;

         for (int var6 = var2.length - 1 - 2; var6 >= 0; var6 -= 3) {
            var4[var5] = var2[var6];
            var4[var5 + 1] = var2[var6 + 1];
            var4[var5 + 2] = var2[var6 + 2];
            var5 += 3;
         }

         var2 = var4;
      }

      this.bStatic = false;
      this._handle = this.LoadVBO(var1, var2);
      this.m_vertexFormat = std::make_shared<VertexFormat>(6);
      this.m_vertexFormat.setElement(0, VertexType.VertexArray, 12);
      this.m_vertexFormat.setElement(1, VertexType.NormalArray, 12);
      this.m_vertexFormat.setElement(2, VertexType.TangentArray, 12);
      this.m_vertexFormat.setElement(3, VertexType.TextureCoordArray, 8);
      this.m_vertexFormat.setElement(4, VertexType.BlendWeightArray, 16);
      this.m_vertexFormat.setElement(5, VertexType.BlendIndexArray, 16);
      this.m_vertexFormat.calculate();
      this._beginMode = BeginMode.Triangles;
   }

    public VertexBufferObject(VertexArray var1, int[] var2) {
      this.m_vertexFormat = var1.m_format;
      this.elements = var2;
      this.bStatic = true;
      RenderThread.invokeOnRenderContext(this, var1, var2, (var1x, var2x, var3) -> var1x._handle = this.LoadVBO(var2x, var3));
      this._beginMode = BeginMode.Triangles;
   }

    public VertexBufferObject(VertexArray var1, int[] var2, bool var3) {
      this.m_vertexFormat = var1.m_format;
      if (var3) {
         int[] var4 = new int[var2.length];
    uint8_t var5 = 0;

         for (int var6 = var2.length - 1 - 2; var6 >= 0; var6 -= 3) {
            var4[var5] = var2[var6];
            var4[var5 + 1] = var2[var6 + 1];
            var4[var5 + 2] = var2[var6 + 2];
            var5 += 3;
         }

         var2 = var4;
      }

      this.elements = var2;
      this.bStatic = false;
      this._handle = this.LoadVBO(var1, var2);
      this._beginMode = BeginMode.Triangles;
   }

    Vbo LoadVBO(VertexPositionNormalTangentTextureSkin[] var1, int[] var2) {
    Vbo var3 = std::make_shared<Vbo>();
    int var4 = 0;
    uint8_t var5 = 76;
      var3.FaceDataOnly = false;
    ByteBuffer var6 = BufferUtils.createByteBuffer(var1.length * var5);
    ByteBuffer var7 = BufferUtils.createByteBuffer(var2.length * 4);

      for (int var8 = 0; var8 < var1.length; var8++) {
         var1[var8].put(var6);
      }

      for (int var11 = 0; var11 < var2.length; var11++) {
         var7.putInt(var2[var11]);
      }

      var6.flip();
      var7.flip();
      var3.VboID = funcs.glGenBuffers();
      funcs.glBindBuffer(funcs.GL_ARRAY_BUFFER(), var3.VboID);
      funcs.glBufferData(funcs.GL_ARRAY_BUFFER(), var6, funcs.GL_STATIC_DRAW());
      funcs.glGetBufferParameter(funcs.GL_ARRAY_BUFFER(), funcs.GL_BUFFER_SIZE(), var3.b);
      var4 = var3.b.get();
      if (var1.length * var5 != var4) {
         throw RuntimeException("Vertex data not uploaded correctly");
      } else {
         var3.EboID = funcs.glGenBuffers();
         funcs.glBindBuffer(funcs.GL_ELEMENT_ARRAY_BUFFER(), var3.EboID);
         funcs.glBufferData(funcs.GL_ELEMENT_ARRAY_BUFFER(), var7, funcs.GL_STATIC_DRAW());
         var3.b.clear();
         funcs.glGetBufferParameter(funcs.GL_ELEMENT_ARRAY_BUFFER(), funcs.GL_BUFFER_SIZE(), var3.b);
         var4 = var3.b.get();
         if (var2.length * 4 != var4) {
            throw RuntimeException("Element data not uploaded correctly");
         } else {
            var3.NumElements = var2.length;
            var3.VertexStride = var5;
    return var3;
         }
      }
   }

    Vbo LoadSoftwareVBO(ByteBuffer var1, Vbo var2, int[] var3) {
    Vbo var4 = var2;
    bool var5 = false;
    ByteBuffer var6 = nullptr;
      if (var2 == nullptr) {
         var5 = true;
         var4 = std::make_unique<Vbo>();
         var4.VboID = funcs.glGenBuffers();
    ByteBuffer var7 = BufferUtils.createByteBuffer(var3.length * 4);

         for (int var8 = 0; var8 < var3.length; var8++) {
            var7.putInt(var3[var8]);
         }

         var7.flip();
         var6 = var7;
         var4.VertexStride = 36;
         var4.NumElements = var3.length;
      } else {
         var2.b.clear();
      }

      var4.FaceDataOnly = false;
      funcs.glBindBuffer(funcs.GL_ARRAY_BUFFER(), var4.VboID);
      funcs.glBufferData(funcs.GL_ARRAY_BUFFER(), var1, funcs.GL_STATIC_DRAW());
      funcs.glGetBufferParameter(funcs.GL_ARRAY_BUFFER(), funcs.GL_BUFFER_SIZE(), var4.b);
      if (var6 != nullptr) {
         var4.EboID = funcs.glGenBuffers();
         funcs.glBindBuffer(funcs.GL_ELEMENT_ARRAY_BUFFER(), var4.EboID);
         funcs.glBufferData(funcs.GL_ELEMENT_ARRAY_BUFFER(), var6, funcs.GL_STATIC_DRAW());
      }

    return var4;
   }

    Vbo LoadVBO(VertexPositionNormalTangentTexture[] var1, int[] var2) {
    Vbo var3 = std::make_shared<Vbo>();
    int var4 = 0;
    uint8_t var5 = 44;
      var3.FaceDataOnly = false;
    ByteBuffer var6 = BufferUtils.createByteBuffer(var1.length * var5);
    ByteBuffer var7 = BufferUtils.createByteBuffer(var2.length * 4);

      for (int var8 = 0; var8 < var1.length; var8++) {
         var1[var8].put(var6);
      }

      for (int var11 = 0; var11 < var2.length; var11++) {
         var7.putInt(var2[var11]);
      }

      var6.flip();
      var7.flip();
      var3.VboID = funcs.glGenBuffers();
      funcs.glBindBuffer(funcs.GL_ARRAY_BUFFER(), var3.VboID);
      funcs.glBufferData(funcs.GL_ARRAY_BUFFER(), var6, funcs.GL_STATIC_DRAW());
      funcs.glGetBufferParameter(funcs.GL_ARRAY_BUFFER(), funcs.GL_BUFFER_SIZE(), var3.b);
      var4 = var3.b.get();
      if (var1.length * var5 != var4) {
         throw RuntimeException("Vertex data not uploaded correctly");
      } else {
         var3.EboID = funcs.glGenBuffers();
         funcs.glBindBuffer(funcs.GL_ELEMENT_ARRAY_BUFFER(), var3.EboID);
         funcs.glBufferData(funcs.GL_ELEMENT_ARRAY_BUFFER(), var7, funcs.GL_STATIC_DRAW());
         var3.b.clear();
         funcs.glGetBufferParameter(funcs.GL_ELEMENT_ARRAY_BUFFER(), funcs.GL_BUFFER_SIZE(), var3.b);
         var4 = var3.b.get();
         if (var2.length * 4 != var4) {
            throw RuntimeException("Element data not uploaded correctly");
         } else {
            var3.NumElements = var2.length;
            var3.VertexStride = var5;
    return var3;
         }
      }
   }

    Vbo LoadVBO(VertexArray var1, int[] var2) {
    Vbo var3 = std::make_shared<Vbo>();
      var3.FaceDataOnly = false;
    ByteBuffer var4 = MemoryUtil.memAlloc(var2.length * 4);

      for (int var5 = 0; var5 < var2.length; var5++) {
         var4.putInt(var2[var5]);
      }

      var1.m_buffer.position(0);
      var1.m_buffer.limit(var1.m_numVertices * var1.m_format.m_stride);
      var4.flip();
      var3.VboID = funcs.glGenBuffers();
      funcs.glBindBuffer(funcs.GL_ARRAY_BUFFER(), var3.VboID);
      funcs.glBufferData(funcs.GL_ARRAY_BUFFER(), var1.m_buffer, funcs.GL_STATIC_DRAW());
      funcs.glGetBufferParameter(funcs.GL_ARRAY_BUFFER(), funcs.GL_BUFFER_SIZE(), var3.b);
    int var6 = var3.b.get();
      if (var1.m_numVertices * var1.m_format.m_stride != var6) {
         throw RuntimeException("Vertex data not uploaded correctly");
      } else {
         var3.EboID = funcs.glGenBuffers();
         funcs.glBindBuffer(funcs.GL_ELEMENT_ARRAY_BUFFER(), var3.EboID);
         funcs.glBufferData(funcs.GL_ELEMENT_ARRAY_BUFFER(), var4, funcs.GL_STATIC_DRAW());
         MemoryUtil.memFree(var4);
         var3.b.clear();
         funcs.glGetBufferParameter(funcs.GL_ELEMENT_ARRAY_BUFFER(), funcs.GL_BUFFER_SIZE(), var3.b);
         var6 = var3.b.get();
         if (var2.length * 4 != var6) {
            throw RuntimeException("Element data not uploaded correctly");
         } else {
            var3.NumElements = var2.length;
            var3.VertexStride = var1.m_format.m_stride;
    return var3;
         }
      }
   }

    void clear() {
      if (this._handle != nullptr) {
         if (this._handle.VboID > 0) {
            funcs.glDeleteBuffers(this._handle.VboID);
            this._handle.VboID = -1;
         }

         if (this._handle.EboID > 0) {
            funcs.glDeleteBuffers(this._handle.EboID);
            this._handle.EboID = -1;
         }

         this._handle = nullptr;
      }
   }

    void Draw(Shader var1) {
      Draw(this._handle, this.m_vertexFormat, var1, 4);
   }

    void DrawStrip(Shader var1) {
      Draw(this._handle, this.m_vertexFormat, var1, 5);
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
    static void Draw(Vbo var0, VertexFormat var1, Shader var2, int var3) {
      if (var0 != nullptr) {
         if (!DebugOptions.instance.DebugDraw_SkipVBODraw.getValue()) {
    int var4 = 33984;
    bool var5 = false;
            if (!var0.FaceDataOnly) {
               funcs.glBindBuffer(funcs.GL_ARRAY_BUFFER(), var0.VboID);

               for (int var6 = 0; var6 < var1.m_elements.length; var6++) {
    VertexElement var7 = var1.m_elements[var6];
                  switch (1.$SwitchMap$zombie$core$skinnedmodel$model$VertexBufferObject$VertexType[var7.m_type.ordinal()]) {
                     case 1:
                        GL20.glVertexPointer(3, 5126, var0.VertexStride, var7.m_byteOffset);
                        GL20.glEnableClientState(32884);
                        break;
                     case 2:
                        GL20.glNormalPointer(5126, var0.VertexStride, var7.m_byteOffset);
                        GL20.glEnableClientState(32885);
                        break;
                     case 3:
                        GL20.glColorPointer(3, 5121, var0.VertexStride, var7.m_byteOffset);
                        GL20.glEnableClientState(32886);
                        break;
                     case 4:
                        GL20.glActiveTexture(var4);
                        GL20.glClientActiveTexture(var4);
                        GL20.glTexCoordPointer(2, 5126, var0.VertexStride, var7.m_byteOffset);
                        var4++;
                        GL20.glEnableClientState(32888);
                     case 5:
                     default:
                        break;
                     case 6:
    int var8 = var2.BoneWeightsAttrib;
                        GL20.glVertexAttribPointer(var8, 4, 5126, false, var0.VertexStride, var7.m_byteOffset);
                        GL20.glEnableVertexAttribArray(var8);
                        var5 = true;
                        break;
                     case 7:
    int var9 = var2.BoneIndicesAttrib;
                        GL20.glVertexAttribPointer(var9, 4, 5126, false, var0.VertexStride, var7.m_byteOffset);
                        GL20.glEnableVertexAttribArray(var9);
                  }
               }
            }

            funcs.glBindBuffer(funcs.GL_ELEMENT_ARRAY_BUFFER(), var0.EboID);
            GL20.glDrawElements(var3, var0.NumElements, 5125, 0L);
            GL20.glDisableClientState(32885);
            if (var5 && var2 != nullptr) {
    int var10 = var2.BoneWeightsAttrib;
               GL20.glDisableVertexAttribArray(var10);
               var10 = var2.BoneIndicesAttrib;
               GL20.glDisableVertexAttribArray(var10);
            }
         }
      }
   }
}
} // namespace model
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
