#pragma once
#include "org/lwjgl/opengl/ARBVertexBufferObject.h"
#include <cstdint>
#include <filesystem>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace core {
namespace VBO {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class GLBufferObjectARB {
public:
  int GL_ARRAY_BUFFER() { return 34962; }

  int GL_ELEMENT_ARRAY_BUFFER() { return 34963; }

  int GL_STATIC_DRAW() { return 35044; }

  int GL_STREAM_DRAW() { return 35040; }

  int GL_BUFFER_SIZE() { return 34660; }

  int GL_WRITE_ONLY() { return 35001; }

  int glGenBuffers() { return ARBVertexBufferObject.glGenBuffersARB(); }

  void glBindBuffer(int int0, int int1) {
    ARBVertexBufferObject.glBindBufferARB(int0, int1);
  }

  void glDeleteBuffers(int int0) {
    ARBVertexBufferObject.glDeleteBuffersARB(int0);
  }

  void glBufferData(int int0, ByteBuffer byteBuffer, int int1) {
    ARBVertexBufferObject.glBufferDataARB(int0, byteBuffer, int1);
  }

  void glBufferData(int int0, long long0, int int1) {
    ARBVertexBufferObject.glBufferDataARB(int0, long0, int1);
  }

  ByteBuffer glMapBuffer(int int0, int int1, long long0,
                         ByteBuffer byteBuffer) {
    return ARBVertexBufferObject.glMapBufferARB(int0, int1, long0, byteBuffer);
  }

  bool glUnmapBuffer(int int0) {
    return ARBVertexBufferObject.glUnmapBufferARB(int0);
  }

  void glGetBufferParameter(int int0, int int1, IntBuffer intBuffer) {
    ARBVertexBufferObject.glGetBufferParameterivARB(int0, int1, intBuffer);
  }
}
} // namespace VBO
} // namespace core
} // namespace zombie
