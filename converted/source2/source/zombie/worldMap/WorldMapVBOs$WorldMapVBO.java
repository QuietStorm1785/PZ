package zombie.worldMap;

import java.nio.ByteBuffer;
import zombie.core.VBO.GLVertexBufferObject;
import zombie.core.VBO.IGLBufferObject;

final class WorldMapVBOs$WorldMapVBO {
   GLVertexBufferObject m_vbo;
   GLVertexBufferObject m_ibo;
   int m_elementCount = 0;

   private WorldMapVBOs$WorldMapVBO() {
   }

   void create() {
      IGLBufferObject var1 = GLVertexBufferObject.funcs;
      this.m_vbo = new GLVertexBufferObject(65520L, var1.GL_ARRAY_BUFFER(), var1.GL_STREAM_DRAW());
      this.m_vbo.create();
      this.m_ibo = new GLVertexBufferObject(4680L, var1.GL_ELEMENT_ARRAY_BUFFER(), var1.GL_STREAM_DRAW());
      this.m_ibo.create();
   }

   void flush(ByteBuffer var1, ByteBuffer var2) {
      this.m_vbo.bind();
      this.m_vbo.bufferData(var1);
      this.m_ibo.bind();
      this.m_ibo.bufferData(var2);
      this.m_elementCount = var2.limit() / 2;
   }
}
