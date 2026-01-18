#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <filesystem>

namespace zombie {
namespace core {
namespace VBO {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class IGLBufferObject {
public:
 virtual ~IGLBufferObject() = default;
 int GL_ARRAY_BUFFER();

 int GL_ELEMENT_ARRAY_BUFFER();

 int GL_STATIC_DRAW();

 int GL_STREAM_DRAW();

 int GL_BUFFER_SIZE();

 int GL_WRITE_ONLY();

 int glGenBuffers();

 void glBindBuffer(int target, int buffer);

 void glDeleteBuffers(int buffers);

 void glBufferData(int target, ByteBuffer data, int usage);

 void glBufferData(int target, long data_size, int usage);

 ByteBuffer glMapBuffer(int target, int access, long length, ByteBuffer old_buffer);

 bool glUnmapBuffer(int target);

 void glGetBufferParameter(int target, int pname, IntBuffer params);
}
} // namespace VBO
} // namespace core
} // namespace zombie
