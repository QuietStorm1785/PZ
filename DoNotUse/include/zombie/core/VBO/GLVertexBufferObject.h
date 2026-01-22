#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/lwjgl/opengl/ARBMapBufferRange.h"
#include "org/lwjgl/opengl/GL.h"
#include "org/lwjgl/opengl/GL20.h"
#include "org/lwjgl/opengl/GL30.h"
#include "org/lwjglx/opengl/OpenGLException.h"
#include "zombie/core/skinnedmodel/model/VertexBufferObject.h"
#include <filesystem>

namespace zombie {
namespace core {
namespace VBO {


class GLVertexBufferObject {
public:
    static IGLBufferObject funcs;
    long size;
    const int type;
    const int usage;
   private transient int id;
   private transient boolean mapped;
   private transient boolean cleared;
   private transient ByteBuffer buffer;
    int m_vertexAttribArray = -1;

    static void init() {
      if (GL.getCapabilities().OpenGL15) {
         System.out.println("OpenGL 1.5 buffer objects supported");
         funcs = std::make_unique<GLBufferObject15>();
      } else {
         if (!GL.getCapabilities().GL_ARB_vertex_buffer_object) {
            throw RuntimeException("Neither OpenGL 1.5 nor GL_ARB_vertex_buffer_object supported");
         }

         System.out.println("GL_ARB_vertex_buffer_object supported");
         funcs = std::make_unique<GLBufferObjectARB>();
      }

      VertexBufferObject.funcs = funcs;
   }

    public GLVertexBufferObject(long var1, int var3, int var4) {
      this.size = var1;
      this.type = var3;
      this.usage = var4;
   }

    public GLVertexBufferObject(int var1, int var2) {
      this.size = 0L;
      this.type = var1;
      this.usage = var2;
   }

    void create() {
      this.id = funcs.glGenBuffers();
   }

    void clear() {
      if (!this.cleared) {
         funcs.glBufferData(this.type, this.size, this.usage);
         this.cleared = true;
      }
   }

    void doDestroy() {
      if (this.id != 0) {
         this.unmap();
         funcs.glDeleteBuffers(this.id);
         this.id = 0;
      }
   }

    ByteBuffer map(int var1) {
      if (!this.mapped) {
         if (this.size != var1) {
            this.size = var1;
            this.clear();
         }

         if (this.buffer != nullptr && this.buffer.capacity() < var1) {
            this.buffer = nullptr;
         }

    ByteBuffer var2 = this.buffer;
         if (GL.getCapabilities().OpenGL30) {
    uint8_t var3 = 34;
            this.buffer = GL30.glMapBufferRange(this.type, 0L, var1, var3, this.buffer);
         } else if (GL.getCapabilities().GL_ARB_map_buffer_range) {
    uint8_t var4 = 34;
            this.buffer = ARBMapBufferRange.glMapBufferRange(this.type, 0L, var1, var4, this.buffer);
         } else {
            this.buffer = funcs.glMapBuffer(this.type, funcs.GL_WRITE_ONLY(), var1, this.buffer);
         }

         if (this.buffer == nullptr) {
            throw OpenGLException("Failed to map buffer " + this);
         }

         if (this.buffer != var2 && var2 != nullptr) {
         }

         this.buffer.order(ByteOrder.nativeOrder()).clear().limit(var1);
         this.mapped = true;
         this.cleared = false;
      }

      return this.buffer;
   }

    ByteBuffer map() {
      if (!this.mapped) {
         assert this.size > 0L;

         this.clear();
    ByteBuffer var1 = this.buffer;
         if (GL.getCapabilities().OpenGL30) {
    uint8_t var2 = 34;
            this.buffer = GL30.glMapBufferRange(this.type, 0L, this.size, var2, this.buffer);
         } else if (GL.getCapabilities().GL_ARB_map_buffer_range) {
    uint8_t var3 = 34;
            this.buffer = ARBMapBufferRange.glMapBufferRange(this.type, 0L, this.size, var3, this.buffer);
         } else {
            this.buffer = funcs.glMapBuffer(this.type, funcs.GL_WRITE_ONLY(), this.size, this.buffer);
         }

         if (this.buffer == nullptr) {
            throw OpenGLException("Failed to map a buffer " + this.size + " bytes long");
         }

         if (this.buffer != var1 && var1 != nullptr) {
         }

         this.buffer.order(ByteOrder.nativeOrder()).clear().limit((int)this.size);
         this.mapped = true;
         this.cleared = false;
      }

      return this.buffer;
   }

    void orphan() {
      funcs.glMapBuffer(this.type, this.usage, this.size, nullptr);
   }

    bool unmap() {
      if (this.mapped) {
         this.mapped = false;
         return funcs.glUnmapBuffer(this.type);
      } else {
    return true;
      }
   }

    bool isMapped() {
      return this.mapped;
   }

    void bufferData(ByteBuffer var1) {
      funcs.glBufferData(this.type, var1, this.usage);
   }

    std::string toString() {
      return "GLVertexBufferObject[" + this.id + ", " + this.size + "]";
   }

    void bind() {
      funcs.glBindBuffer(this.type, this.id);
   }

    void bindNone() {
      funcs.glBindBuffer(this.type, 0);
   }

    int getID() {
      return this.id;
   }

    void enableVertexAttribArray(int var1) {
      if (this.m_vertexAttribArray != var1) {
         this.disableVertexAttribArray();
         if (var1 >= 0) {
            GL20.glEnableVertexAttribArray(var1);
         }

         this.m_vertexAttribArray = var1 >= 0 ? var1 : -1;
      }
   }

    void disableVertexAttribArray() {
      if (this.m_vertexAttribArray != -1) {
         GL20.glDisableVertexAttribArray(this.m_vertexAttribArray);
         this.m_vertexAttribArray = -1;
      }
   }
}
} // namespace VBO
} // namespace core
} // namespace zombie
