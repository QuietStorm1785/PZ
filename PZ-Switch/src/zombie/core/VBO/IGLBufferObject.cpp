#include "zombie/core/VBO/IGLBufferObject.h"

namespace zombie {
namespace core {
namespace VBO {

int IGLBufferObject::GL_ARRAY_BUFFER() {
 // TODO: Implement GL_ARRAY_BUFFER
 return 0;
}

int IGLBufferObject::GL_ELEMENT_ARRAY_BUFFER() {
 // TODO: Implement GL_ELEMENT_ARRAY_BUFFER
 return 0;
}

int IGLBufferObject::GL_STATIC_DRAW() {
 // TODO: Implement GL_STATIC_DRAW
 return 0;
}

int IGLBufferObject::GL_STREAM_DRAW() {
 // TODO: Implement GL_STREAM_DRAW
 return 0;
}

int IGLBufferObject::GL_BUFFER_SIZE() {
 // TODO: Implement GL_BUFFER_SIZE
 return 0;
}

int IGLBufferObject::GL_WRITE_ONLY() {
 // TODO: Implement GL_WRITE_ONLY
 return 0;
}

int IGLBufferObject::glGenBuffers() {
 // TODO: Implement glGenBuffers
 return 0;
}

void IGLBufferObject::glBindBuffer(int target, int buffer) {
 // TODO: Implement glBindBuffer
}

void IGLBufferObject::glDeleteBuffers(int buffers) {
 // TODO: Implement glDeleteBuffers
}

void IGLBufferObject::glBufferData(int target, ByteBuffer data, int usage) {
 // TODO: Implement glBufferData
}

void IGLBufferObject::glBufferData(int target, long data_size, int usage) {
 // TODO: Implement glBufferData
}

ByteBuffer IGLBufferObject::glMapBuffer(int target, int access, long length,
 ByteBuffer old_buffer) {
 // TODO: Implement glMapBuffer
 return nullptr;
}

bool IGLBufferObject::glUnmapBuffer(int target) {
 // TODO: Implement glUnmapBuffer
 return false;
}

void IGLBufferObject::glGetBufferParameter(int target, int pname,
 IntBuffer params) {
 // TODO: Implement glGetBufferParameter
}

} // namespace VBO
} // namespace core
} // namespace zombie
