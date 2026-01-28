#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/utils/BufferUtils.h"
#include "zombie/core/skinnedmodel/model/VertexBufferObject/VertexFormat.h"
#include <filesystem>

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace model {


class VertexBufferObject {
public:
    const VertexFormat m_format;
    const int m_numVertices;
    const ByteBuffer m_buffer;

   public VertexBufferObject$VertexArray(VertexFormat var1, int var2) {
      this.m_format = var1;
      this.m_numVertices = var2;
      this.m_buffer = BufferUtils::createByteBuffer(this.m_numVertices * this.m_format.m_stride);
   }

    void setElement(int var1, int var2, float var3, float var4) {
    int var5 = var1 * this.m_format.m_stride + this.m_format.m_elements[var2].m_byteOffset;
      this.m_buffer.putFloat(var5, var3);
      var5 += 4;
      this.m_buffer.putFloat(var5, var4);
   }

    void setElement(int var1, int var2, float var3, float var4, float var5) {
    int var6 = var1 * this.m_format.m_stride + this.m_format.m_elements[var2].m_byteOffset;
      this.m_buffer.putFloat(var6, var3);
      var6 += 4;
      this.m_buffer.putFloat(var6, var4);
      var6 += 4;
      this.m_buffer.putFloat(var6, var5);
   }

    void setElement(int var1, int var2, float var3, float var4, float var5, float var6) {
    int var7 = var1 * this.m_format.m_stride + this.m_format.m_elements[var2].m_byteOffset;
      this.m_buffer.putFloat(var7, var3);
      var7 += 4;
      this.m_buffer.putFloat(var7, var4);
      var7 += 4;
      this.m_buffer.putFloat(var7, var5);
      var7 += 4;
      this.m_buffer.putFloat(var7, var6);
   }

    float getElementFloat(int var1, int var2, int var3) {
    int var4 = var1 * this.m_format.m_stride + this.m_format.m_elements[var2].m_byteOffset + var3 * 4;
      return this.m_buffer.getFloat(var4);
   }
}
} // namespace model
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
