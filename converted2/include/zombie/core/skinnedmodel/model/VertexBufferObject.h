#pragma once
#include "org/lwjgl/opengl/GL20.h"
#include "org/lwjgl/system/MemoryUtil.h"
#include "org/lwjglx/BufferUtils.h"
#include "zombie/core/VBO/IGLBufferObject.h"
#include "zombie/core/opengl/RenderThread.h"
#include "zombie/core/skinnedmodel/shader/Shader.h"
#include "zombie/debug/DebugOptions.h"
#include "zombie/util/list/PZArrayUtil.h"
#include <cstdint>
#include <filesystem>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace model {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

/**
 * Created by LEMMYATI on 03/01/14.
 */
class VertexBufferObject {
public:
  static IGLBufferObject funcs;
  int[] elements;
  VertexBufferObject.Vbo _handle;
private
  final VertexBufferObject.VertexFormat m_vertexFormat;
private
  VertexBufferObject.BeginMode _beginMode;
  bool bStatic = false;

public
  VertexBufferObject() {
    this.bStatic = false;
    this.m_vertexFormat = new VertexBufferObject.VertexFormat(4);
    this.m_vertexFormat.setElement(0, VertexBufferObject.VertexType.VertexArray,
                                   12);
    this.m_vertexFormat.setElement(1, VertexBufferObject.VertexType.NormalArray,
                                   12);
    this.m_vertexFormat.setElement(2, VertexBufferObject.VertexType.ColorArray,
                                   4);
    this.m_vertexFormat.setElement(
        3, VertexBufferObject.VertexType.TextureCoordArray, 8);
    this.m_vertexFormat.calculate();
    this._beginMode = VertexBufferObject.BeginMode.Triangles;
  }

public
  VertexBufferObject(
      VertexPositionNormalTangentTexture[] vertexPositionNormalTangentTextures,
      int[] ints) {
    this.elements = ints;
    this.bStatic = true;
    RenderThread.invokeOnRenderContext(
        this, vertexPositionNormalTangentTextures, ints,
        (vertexBufferObject1, vertexPositionNormalTangentTexturesx, intsx)
            ->vertexBufferObject1._handle =
            this.LoadVBO(vertexPositionNormalTangentTexturesx, intsx));
    this.m_vertexFormat = new VertexBufferObject.VertexFormat(4);
    this.m_vertexFormat.setElement(0, VertexBufferObject.VertexType.VertexArray,
                                   12);
    this.m_vertexFormat.setElement(1, VertexBufferObject.VertexType.NormalArray,
                                   12);
    this.m_vertexFormat.setElement(
        2, VertexBufferObject.VertexType.TangentArray, 12);
    this.m_vertexFormat.setElement(
        3, VertexBufferObject.VertexType.TextureCoordArray, 8);
    this.m_vertexFormat.calculate();
    this._beginMode = VertexBufferObject.BeginMode.Triangles;
  }

public
  VertexBufferObject(VertexPositionNormalTangentTextureSkin
                         [] vertexPositionNormalTangentTextureSkins,
                     int[] ints0, bool boolean0) {
    this.elements = ints0;
    if (boolean0) {
      int[] ints1 = new int[ints0.length];
      uint8_t byte0 = 0;

      for (int int0 = ints0.length - 1 - 2; int0 >= 0; int0 -= 3) {
        ints1[byte0] = ints0[int0];
        ints1[byte0 + 1] = ints0[int0 + 1];
        ints1[byte0 + 2] = ints0[int0 + 2];
        byte0 += 3;
      }

      ints0 = ints1;
    }

    this.bStatic = false;
    this._handle = this.LoadVBO(vertexPositionNormalTangentTextureSkins, ints0);
    this.m_vertexFormat = new VertexBufferObject.VertexFormat(6);
    this.m_vertexFormat.setElement(0, VertexBufferObject.VertexType.VertexArray,
                                   12);
    this.m_vertexFormat.setElement(1, VertexBufferObject.VertexType.NormalArray,
                                   12);
    this.m_vertexFormat.setElement(
        2, VertexBufferObject.VertexType.TangentArray, 12);
    this.m_vertexFormat.setElement(
        3, VertexBufferObject.VertexType.TextureCoordArray, 8);
    this.m_vertexFormat.setElement(
        4, VertexBufferObject.VertexType.BlendWeightArray, 16);
    this.m_vertexFormat.setElement(
        5, VertexBufferObject.VertexType.BlendIndexArray, 16);
    this.m_vertexFormat.calculate();
    this._beginMode = VertexBufferObject.BeginMode.Triangles;
  }

public
  VertexBufferObject(VertexBufferObject.VertexArray vertexArray, int[] ints) {
    this.m_vertexFormat = vertexArray.m_format;
    this.elements = ints;
    this.bStatic = true;
    RenderThread.invokeOnRenderContext(
        this, vertexArray, ints,
        (vertexBufferObject1, vertexArrayx, intsx)
            ->vertexBufferObject1._handle = this.LoadVBO(vertexArrayx, intsx));
    this._beginMode = VertexBufferObject.BeginMode.Triangles;
  }

public
  VertexBufferObject(VertexBufferObject.VertexArray vertexArray, int[] ints1,
                     bool boolean0) {
    this.m_vertexFormat = vertexArray.m_format;
    if (boolean0) {
      int[] ints0 = new int[ints1.length];
      uint8_t byte0 = 0;

      for (int int0 = ints1.length - 1 - 2; int0 >= 0; int0 -= 3) {
        ints0[byte0] = ints1[int0];
        ints0[byte0 + 1] = ints1[int0 + 1];
        ints0[byte0 + 2] = ints1[int0 + 2];
        byte0 += 3;
      }

      ints1 = ints0;
    }

    this.elements = ints1;
    this.bStatic = false;
    this._handle = this.LoadVBO(vertexArray, ints1);
    this._beginMode = VertexBufferObject.BeginMode.Triangles;
  }

private
  VertexBufferObject.Vbo LoadVBO(VertexPositionNormalTangentTextureSkin
                                     [] vertexPositionNormalTangentTextureSkins,
                                 int[] ints) {
    VertexBufferObject.Vbo vbo = new VertexBufferObject.Vbo();
    int int0 = 0;
    uint8_t byte0 = 76;
    vbo.FaceDataOnly = false;
    ByteBuffer byteBuffer0 = BufferUtils.createByteBuffer(
        vertexPositionNormalTangentTextureSkins.length * byte0);
    ByteBuffer byteBuffer1 = BufferUtils.createByteBuffer(ints.length * 4);

    for (int int1 = 0; int1 < vertexPositionNormalTangentTextureSkins.length;
         int1++) {
      vertexPositionNormalTangentTextureSkins[int1].put(byteBuffer0);
    }

    for (int int2 = 0; int2 < ints.length; int2++) {
      byteBuffer1.putInt(ints[int2]);
    }

    byteBuffer0.flip();
    byteBuffer1.flip();
    vbo.VboID = funcs.glGenBuffers();
    funcs.glBindBuffer(funcs.GL_ARRAY_BUFFER(), vbo.VboID);
    funcs.glBufferData(funcs.GL_ARRAY_BUFFER(), byteBuffer0,
                       funcs.GL_STATIC_DRAW());
    funcs.glGetBufferParameter(funcs.GL_ARRAY_BUFFER(), funcs.GL_BUFFER_SIZE(),
                               vbo.b);
    int0 = vbo.b.get();
    if (vertexPositionNormalTangentTextureSkins.length * byte0 != int0) {
      throw new RuntimeException("Vertex data not uploaded correctly");
    } else {
      vbo.EboID = funcs.glGenBuffers();
      funcs.glBindBuffer(funcs.GL_ELEMENT_ARRAY_BUFFER(), vbo.EboID);
      funcs.glBufferData(funcs.GL_ELEMENT_ARRAY_BUFFER(), byteBuffer1,
                         funcs.GL_STATIC_DRAW());
      vbo.b.clear();
      funcs.glGetBufferParameter(funcs.GL_ELEMENT_ARRAY_BUFFER(),
                                 funcs.GL_BUFFER_SIZE(), vbo.b);
      int0 = vbo.b.get();
      if (ints.length * 4 != int0) {
        throw new RuntimeException("Element data not uploaded correctly");
      } else {
        vbo.NumElements = ints.length;
        vbo.VertexStride = byte0;
        return vbo;
      }
    }
  }

public
  VertexBufferObject.Vbo LoadSoftwareVBO(ByteBuffer byteBuffer2,
                                         VertexBufferObject.Vbo vbo1,
                                         int[] ints) {
    VertexBufferObject.Vbo vbo0 = vbo1;
    bool boolean0 = false;
    ByteBuffer byteBuffer0 = null;
    if (vbo1 == nullptr) {
      boolean0 = true;
      vbo0 = new VertexBufferObject.Vbo();
      vbo0.VboID = funcs.glGenBuffers();
      ByteBuffer byteBuffer1 = BufferUtils.createByteBuffer(ints.length * 4);

      for (int int0 = 0; int0 < ints.length; int0++) {
        byteBuffer1.putInt(ints[int0]);
      }

      byteBuffer1.flip();
      byteBuffer0 = byteBuffer1;
      vbo0.VertexStride = 36;
      vbo0.NumElements = ints.length;
    } else {
      vbo1.b.clear();
    }

    vbo0.FaceDataOnly = false;
    funcs.glBindBuffer(funcs.GL_ARRAY_BUFFER(), vbo0.VboID);
    funcs.glBufferData(funcs.GL_ARRAY_BUFFER(), byteBuffer2,
                       funcs.GL_STATIC_DRAW());
    funcs.glGetBufferParameter(funcs.GL_ARRAY_BUFFER(), funcs.GL_BUFFER_SIZE(),
                               vbo0.b);
    if (byteBuffer0 != nullptr) {
      vbo0.EboID = funcs.glGenBuffers();
      funcs.glBindBuffer(funcs.GL_ELEMENT_ARRAY_BUFFER(), vbo0.EboID);
      funcs.glBufferData(funcs.GL_ELEMENT_ARRAY_BUFFER(), byteBuffer0,
                         funcs.GL_STATIC_DRAW());
    }

    return vbo0;
  }

private
  VertexBufferObject.Vbo LoadVBO(
      VertexPositionNormalTangentTexture[] vertexPositionNormalTangentTextures,
      int[] ints) {
    VertexBufferObject.Vbo vbo = new VertexBufferObject.Vbo();
    int int0 = 0;
    uint8_t byte0 = 44;
    vbo.FaceDataOnly = false;
    ByteBuffer byteBuffer0 = BufferUtils.createByteBuffer(
        vertexPositionNormalTangentTextures.length * byte0);
    ByteBuffer byteBuffer1 = BufferUtils.createByteBuffer(ints.length * 4);

    for (int int1 = 0; int1 < vertexPositionNormalTangentTextures.length;
         int1++) {
      vertexPositionNormalTangentTextures[int1].put(byteBuffer0);
    }

    for (int int2 = 0; int2 < ints.length; int2++) {
      byteBuffer1.putInt(ints[int2]);
    }

    byteBuffer0.flip();
    byteBuffer1.flip();
    vbo.VboID = funcs.glGenBuffers();
    funcs.glBindBuffer(funcs.GL_ARRAY_BUFFER(), vbo.VboID);
    funcs.glBufferData(funcs.GL_ARRAY_BUFFER(), byteBuffer0,
                       funcs.GL_STATIC_DRAW());
    funcs.glGetBufferParameter(funcs.GL_ARRAY_BUFFER(), funcs.GL_BUFFER_SIZE(),
                               vbo.b);
    int0 = vbo.b.get();
    if (vertexPositionNormalTangentTextures.length * byte0 != int0) {
      throw new RuntimeException("Vertex data not uploaded correctly");
    } else {
      vbo.EboID = funcs.glGenBuffers();
      funcs.glBindBuffer(funcs.GL_ELEMENT_ARRAY_BUFFER(), vbo.EboID);
      funcs.glBufferData(funcs.GL_ELEMENT_ARRAY_BUFFER(), byteBuffer1,
                         funcs.GL_STATIC_DRAW());
      vbo.b.clear();
      funcs.glGetBufferParameter(funcs.GL_ELEMENT_ARRAY_BUFFER(),
                                 funcs.GL_BUFFER_SIZE(), vbo.b);
      int0 = vbo.b.get();
      if (ints.length * 4 != int0) {
        throw new RuntimeException("Element data not uploaded correctly");
      } else {
        vbo.NumElements = ints.length;
        vbo.VertexStride = byte0;
        return vbo;
      }
    }
  }

private
  VertexBufferObject.Vbo LoadVBO(VertexBufferObject.VertexArray vertexArray,
                                 int[] ints) {
    VertexBufferObject.Vbo vbo = new VertexBufferObject.Vbo();
    vbo.FaceDataOnly = false;
    ByteBuffer byteBuffer = MemoryUtil.memAlloc(ints.length * 4);

    for (int int0 = 0; int0 < ints.length; int0++) {
      byteBuffer.putInt(ints[int0]);
    }

    vertexArray.m_buffer.position(0);
    vertexArray.m_buffer.limit(vertexArray.m_numVertices *
                               vertexArray.m_format.m_stride);
    byteBuffer.flip();
    vbo.VboID = funcs.glGenBuffers();
    funcs.glBindBuffer(funcs.GL_ARRAY_BUFFER(), vbo.VboID);
    funcs.glBufferData(funcs.GL_ARRAY_BUFFER(), vertexArray.m_buffer,
                       funcs.GL_STATIC_DRAW());
    funcs.glGetBufferParameter(funcs.GL_ARRAY_BUFFER(), funcs.GL_BUFFER_SIZE(),
                               vbo.b);
    int int1 = vbo.b.get();
    if (vertexArray.m_numVertices * vertexArray.m_format.m_stride != int1) {
      throw new RuntimeException("Vertex data not uploaded correctly");
    } else {
      vbo.EboID = funcs.glGenBuffers();
      funcs.glBindBuffer(funcs.GL_ELEMENT_ARRAY_BUFFER(), vbo.EboID);
      funcs.glBufferData(funcs.GL_ELEMENT_ARRAY_BUFFER(), byteBuffer,
                         funcs.GL_STATIC_DRAW());
      MemoryUtil.memFree(byteBuffer);
      vbo.b.clear();
      funcs.glGetBufferParameter(funcs.GL_ELEMENT_ARRAY_BUFFER(),
                                 funcs.GL_BUFFER_SIZE(), vbo.b);
      int1 = vbo.b.get();
      if (ints.length * 4 != int1) {
        throw new RuntimeException("Element data not uploaded correctly");
      } else {
        vbo.NumElements = ints.length;
        vbo.VertexStride = vertexArray.m_format.m_stride;
        return vbo;
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

  void Draw(Shader shader) {
    Draw(this._handle, this.m_vertexFormat, shader, 4);
  }

  void DrawStrip(Shader shader) {
    Draw(this._handle, this.m_vertexFormat, shader, 5);
  }

  static void Draw(VertexBufferObject.Vbo vbo,
                   VertexBufferObject.VertexFormat vertexFormat, Shader shader,
                   int int4) {
    if (vbo != nullptr) {
      if (!DebugOptions.instance.DebugDraw_SkipVBODraw.getValue()) {
        int int0 = 33984;
        bool boolean0 = false;
        if (!vbo.FaceDataOnly) {
          funcs.glBindBuffer(funcs.GL_ARRAY_BUFFER(), vbo.VboID);

          for (int int1 = 0; int1 < vertexFormat.m_elements.length; int1++) {
            VertexBufferObject.VertexElement vertexElement =
                vertexFormat.m_elements[int1];
            switch (vertexElement.m_type) {
            case VertexArray:
              GL20.glVertexPointer(3, 5126, vbo.VertexStride,
                                   vertexElement.m_byteOffset);
              GL20.glEnableClientState(32884);
              break;
            case NormalArray:
              GL20.glNormalPointer(5126, vbo.VertexStride,
                                   vertexElement.m_byteOffset);
              GL20.glEnableClientState(32885);
              break;
            case ColorArray:
              GL20.glColorPointer(3, 5121, vbo.VertexStride,
                                  vertexElement.m_byteOffset);
              GL20.glEnableClientState(32886);
              break;
            case TextureCoordArray:
              GL20.glActiveTexture(int0);
              GL20.glClientActiveTexture(int0);
              GL20.glTexCoordPointer(2, 5126, vbo.VertexStride,
                                     vertexElement.m_byteOffset);
              int0++;
              GL20.glEnableClientState(32888);
            case TangentArray:
            default:
              break;
            case BlendWeightArray:
              int int2 = shader.BoneWeightsAttrib;
              GL20.glVertexAttribPointer(int2, 4, 5126, false, vbo.VertexStride,
                                         vertexElement.m_byteOffset);
              GL20.glEnableVertexAttribArray(int2);
              boolean0 = true;
              break;
            case BlendIndexArray:
              int int3 = shader.BoneIndicesAttrib;
              GL20.glVertexAttribPointer(int3, 4, 5126, false, vbo.VertexStride,
                                         vertexElement.m_byteOffset);
              GL20.glEnableVertexAttribArray(int3);
            }
          }
        }

        funcs.glBindBuffer(funcs.GL_ELEMENT_ARRAY_BUFFER(), vbo.EboID);
        GL20.glDrawElements(int4, vbo.NumElements, 5125, 0L);
        GL20.glDisableClientState(32885);
        if (boolean0 && shader != nullptr) {
          int int5 = shader.BoneWeightsAttrib;
          GL20.glDisableVertexAttribArray(int5);
          int5 = shader.BoneIndicesAttrib;
          GL20.glDisableVertexAttribArray(int5);
        }
      }
    }
  }

public
  static enum BeginMode { Triangles; }

  public static final class Vbo {
    const IntBuffer b = BufferUtils.createIntBuffer(4);
    int VboID;
    int EboID;
    int NumElements;
    int VertexStride;
    bool FaceDataOnly;
  }

  public static final class VertexArray {
  public
    final VertexBufferObject.VertexFormat m_format;
    const int m_numVertices;
    const ByteBuffer m_buffer;

  public
    VertexArray(VertexBufferObject.VertexFormat format, int numVertices) {
      this.m_format = format;
      this.m_numVertices = numVertices;
      this.m_buffer = BufferUtils.createByteBuffer(this.m_numVertices *
                                                   this.m_format.m_stride);
    }

    void setElement(int vertex, int element, float v1, float v2) {
      int int0 = vertex * this.m_format.m_stride +
                 this.m_format.m_elements[element].m_byteOffset;
      this.m_buffer.putFloat(int0, v1);
      int0 += 4;
      this.m_buffer.putFloat(int0, v2);
    }

    void setElement(int vertex, int element, float v1, float v2, float v3) {
      int int0 = vertex * this.m_format.m_stride +
                 this.m_format.m_elements[element].m_byteOffset;
      this.m_buffer.putFloat(int0, v1);
      int0 += 4;
      this.m_buffer.putFloat(int0, v2);
      int0 += 4;
      this.m_buffer.putFloat(int0, v3);
    }

    void setElement(int vertex, int element, float v1, float v2, float v3,
                    float v4) {
      int int0 = vertex * this.m_format.m_stride +
                 this.m_format.m_elements[element].m_byteOffset;
      this.m_buffer.putFloat(int0, v1);
      int0 += 4;
      this.m_buffer.putFloat(int0, v2);
      int0 += 4;
      this.m_buffer.putFloat(int0, v3);
      int0 += 4;
      this.m_buffer.putFloat(int0, v4);
    }

    float getElementFloat(int int3, int int2, int int1) {
      int int0 = int3 * this.m_format.m_stride +
                 this.m_format.m_elements[int2].m_byteOffset + int1 * 4;
      return this.m_buffer.getFloat(int0);
    }
  }

  public static final class VertexElement {
  public
    VertexBufferObject.VertexType m_type;
    int m_byteSize;
    int m_byteOffset;
  }

  public static final class VertexFormat {
    final VertexBufferObject.VertexElement[] m_elements;
    int m_stride;

  public
    VertexFormat(int numElements) {
      this.m_elements = PZArrayUtil.newInstance(
          VertexBufferObject.VertexElement.class, numElements,
          VertexBufferObject.VertexElement::new);
    }

    void setElement(int index, VertexBufferObject.VertexType type,
                    int byteSize) {
      this.m_elements[index].m_type = type;
      this.m_elements[index].m_byteSize = byteSize;
    }

    void calculate() {
      this.m_stride = 0;

      for (int int0 = 0; int0 < this.m_elements.length; int0++) {
        this.m_elements[int0].m_byteOffset = this.m_stride;
        this.m_stride = this.m_stride + this.m_elements[int0].m_byteSize;
      }
    }
  }

  public static enum VertexType {
    VertexArray,
    NormalArray,
    ColorArray,
    IndexArray,
    TextureCoordArray,
    TangentArray,
    BlendWeightArray,
    BlendIndexArray;
  }
}
} // namespace model
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
