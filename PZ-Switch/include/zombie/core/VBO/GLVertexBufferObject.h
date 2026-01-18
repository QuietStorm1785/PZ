#pragma once
#include "org/lwjgl/opengl/ARBMapBufferRange.h"
#include "org/lwjgl/opengl/GL.h"
#include "org/lwjgl/opengl/GL20.h"
#include "org/lwjgl/opengl/GL30.h"
#include "org/lwjglx/opengl/OpenGLException.h"
#include "zombie/core/skinnedmodel/model/VertexBufferObject.h"
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

/**
 * Vertex buffer object wrapper
 */
class GLVertexBufferObject {
public:
 static IGLBufferObject funcs;
 long size;
 const int type;
 const int usage;
private
 int id;
private
 boolean mapped;
private
 boolean cleared;
private
 ByteBuffer buffer;
 int m_vertexAttribArray = -1;

 static void init() {
 if (GL.getCapabilities().OpenGL15) {
 System.out.println("OpenGL 1.5 buffer objects supported");
 funcs = std::make_unique<GLBufferObject15>();
 } else {
 if (!GL.getCapabilities().GL_ARB_vertex_buffer_object) {
 throw RuntimeException(
 "Neither OpenGL 1.5 nor GL_ARB_vertex_buffer_object supported");
 }

 System.out.println("GL_ARB_vertex_buffer_object supported");
 funcs = std::make_unique<GLBufferObjectARB>();
 }

 VertexBufferObject.funcs = funcs;
 }

 /**
 * C'tor
 */
public
 GLVertexBufferObject(long _size, int _type, int _usage) {
 this->size = _size;
 this->type = _type;
 this->usage = _usage;
 }

 /**
 * C'tor
 */
public
 GLVertexBufferObject(int _type, int _usage) {
 this->size = 0L;
 this->type = _type;
 this->usage = _usage;
 }

 void create() { this->id = funcs.glGenBuffers(); }

 /**
 * Tells the driver we don't care about the data in our buffer any more (may
 * improve performance before mapping)
 */
 void clear() {
 if (!this->cleared) {
 funcs.glBufferData(this->type, this->size, this->usage);
 this->cleared = true;
 }
 }

 void doDestroy() {
 if (this->id != 0) {
 this->unmap();
 funcs.glDeleteBuffers(this->id);
 this->id = 0;
 }
 }

 ByteBuffer map(int _size) {
 if (!this->mapped) {
 if (this->size != _size) {
 this->size = _size;
 this->clear();
 }

 if (this->buffer != nullptr && this->buffer.capacity() < _size) {
 this->buffer = nullptr;
 }

 ByteBuffer byteBuffer = this->buffer;
 if (GL.getCapabilities().OpenGL30) {
 uint8_t byte0 = 34;
 this->buffer =
 GL30.glMapBufferRange(this->type, 0L, _size, byte0, this->buffer);
 } else if (GL.getCapabilities().GL_ARB_map_buffer_range) {
 uint8_t byte1 = 34;
 this->buffer = ARBMapBufferRange.glMapBufferRange(this->type, 0L, _size,
 byte1, this->buffer);
 } else {
 this->buffer = funcs.glMapBuffer(this->type, funcs.GL_WRITE_ONLY(), _size,
 this->buffer);
 }

 if (this->buffer.empty()) {
 throw OpenGLException("Failed to map buffer " + this);
 }

 if (this->buffer != byteBuffer && byteBuffer != nullptr) {
 }

 this->buffer.order(ByteOrder.nativeOrder()).clear().limit(_size);
 this->mapped = true;
 this->cleared = false;
 }

 return this->buffer;
 }

 ByteBuffer map() {
 if (!this->mapped) {
 assert this->size > 0L;

 this->clear();
 ByteBuffer byteBuffer = this->buffer;
 if (GL.getCapabilities().OpenGL30) {
 uint8_t byte0 = 34;
 this->buffer =
 GL30.glMapBufferRange(this->type, 0L, this->size, byte0, this->buffer);
 } else if (GL.getCapabilities().GL_ARB_map_buffer_range) {
 uint8_t byte1 = 34;
 this->buffer = ARBMapBufferRange.glMapBufferRange(
 this->type, 0L, this->size, byte1, this->buffer);
 } else {
 this->buffer = funcs.glMapBuffer(this->type, funcs.GL_WRITE_ONLY(),
 this->size, this->buffer);
 }

 if (this->buffer.empty()) {
 throw OpenGLException("Failed to map a buffer " + this->size +
 " bytes long");
 }

 if (this->buffer != byteBuffer && byteBuffer != nullptr) {
 }

 this->buffer.order(ByteOrder.nativeOrder()).clear().limit((int)this->size);
 this->mapped = true;
 this->cleared = false;
 }

 return this->buffer;
 }

 void orphan() {
 funcs.glMapBuffer(this->type, this->usage, this->size, nullptr);
 }

 bool unmap() {
 if (this->mapped) {
 this->mapped = false;
 return funcs.glUnmapBuffer(this->type);
 } else {
 return true;
 }
 }

 bool isMapped() { return this->mapped; }

 void bufferData(ByteBuffer data) {
 funcs.glBufferData(this->type, data, this->usage);
 }

 std::string toString() {
 return "GLVertexBufferObject[" + this->id + ", " + this->size + "]";
 }

 void bind() { funcs.glBindBuffer(this->type, this->id); }

 void bindNone() { funcs.glBindBuffer(this->type, 0); }

 int getID() { return this->id; }

 void enableVertexAttribArray(int index) {
 if (this->m_vertexAttribArray != index) {
 this->disableVertexAttribArray();
 if (index >= 0) {
 GL20.glEnableVertexAttribArray(index);
 }

 this->m_vertexAttribArray = index >= 0 ? index : -1;
 }
 }

 void disableVertexAttribArray() {
 if (this->m_vertexAttribArray != -1) {
 GL20.glDisableVertexAttribArray(this->m_vertexAttribArray);
 this->m_vertexAttribArray = -1;
 }
 }
}
} // namespace VBO
} // namespace core
} // namespace zombie
