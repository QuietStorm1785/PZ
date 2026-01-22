#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/lwjgl/opengl/ARBVertexBufferObject.h"
#include <filesystem>

namespace zombie {
namespace core {
namespace VBO {


class GLBufferObjectARB {
public:
    int GL_ARRAY_BUFFER() {
    return 34962;
   }

    int GL_ELEMENT_ARRAY_BUFFER() {
    return 34963;
   }

    int GL_STATIC_DRAW() {
    return 35044;
   }

    int GL_STREAM_DRAW() {
    return 35040;
   }

    int GL_BUFFER_SIZE() {
    return 34660;
   }

    int GL_WRITE_ONLY() {
    return 35001;
   }

    int glGenBuffers() {
      return ARBVertexBufferObject.glGenBuffersARB();
   }

    void glBindBuffer(int var1, int var2) {
      ARBVertexBufferObject.glBindBufferARB(var1, var2);
   }

    void glDeleteBuffers(int var1) {
      ARBVertexBufferObject.glDeleteBuffersARB(var1);
   }

    void glBufferData(int var1, ByteBuffer var2, int var3) {
      ARBVertexBufferObject.glBufferDataARB(var1, var2, var3);
   }

    void glBufferData(int var1, long var2, int var4) {
      ARBVertexBufferObject.glBufferDataARB(var1, var2, var4);
   }

    ByteBuffer glMapBuffer(int var1, int var2, long var3, ByteBuffer var5) {
      return ARBVertexBufferObject.glMapBufferARB(var1, var2, var3, var5);
   }

    bool glUnmapBuffer(int var1) {
      return ARBVertexBufferObject.glUnmapBufferARB(var1);
   }

    void glGetBufferParameter(int var1, int var2, IntBuffer var3) {
      ARBVertexBufferObject.glGetBufferParameterivARB(var1, var2, var3);
   }
}
} // namespace VBO
} // namespace core
} // namespace zombie
