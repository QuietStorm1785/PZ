package zombie.core.skinnedmodel.model;

import java.nio.ByteBuffer;
import org.lwjglx.BufferUtils;
import zombie.core.skinnedmodel.model.VertexBufferObject.VertexFormat;

public final class VertexBufferObject$VertexArray {
   public final VertexFormat m_format;
   public final int m_numVertices;
   public final ByteBuffer m_buffer;

   public VertexBufferObject$VertexArray(VertexFormat var1, int var2) {
      this.m_format = var1;
      this.m_numVertices = var2;
      this.m_buffer = BufferUtils.createByteBuffer(this.m_numVertices * this.m_format.m_stride);
   }

   public void setElement(int var1, int var2, float var3, float var4) {
      int var5 = var1 * this.m_format.m_stride + this.m_format.m_elements[var2].m_byteOffset;
      this.m_buffer.putFloat(var5, var3);
      var5 += 4;
      this.m_buffer.putFloat(var5, var4);
   }

   public void setElement(int var1, int var2, float var3, float var4, float var5) {
      int var6 = var1 * this.m_format.m_stride + this.m_format.m_elements[var2].m_byteOffset;
      this.m_buffer.putFloat(var6, var3);
      var6 += 4;
      this.m_buffer.putFloat(var6, var4);
      var6 += 4;
      this.m_buffer.putFloat(var6, var5);
   }

   public void setElement(int var1, int var2, float var3, float var4, float var5, float var6) {
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
