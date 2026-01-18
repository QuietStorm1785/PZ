#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/VBO/GLVertexBufferObject.h"
#include "zombie/debug/DebugLog.h"
#include <filesystem>

namespace zombie {
namespace core {
namespace opengl {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class SharedVertexBufferObjects {
public:
 const int bufferSizeBytes = 65536;
 const int indexBufferSizeBytes;
 const int bufferSizeVertices;
 private GLVertexBufferObject[] vbo = new GLVertexBufferObject[48];
 private GLVertexBufferObject[] ibo = new GLVertexBufferObject[48];
 FloatBuffer vertices;
 ShortBuffer indices;
 int sequence = -1;
 int mark;

 public SharedVertexBufferObjects(int BYTES_PER_VERTEX) {
 this->bufferSizeVertices = 65536 / BYTES_PER_VERTEX;
 this->indexBufferSizeBytes = this->bufferSizeVertices * 3;
 }

 void startFrame() {
 bool boolean0 = true;
 if (boolean0) {
 this->sequence = -1;
 }

 this->mark = this->sequence;
 }

 void next() {
 this->sequence++;
 if (this->sequence == this->vbo.length) {
 this->sequence = 0;
 }

 if (this->sequence == this->mark) {
 DebugLog.General.error("SharedVertexBufferObject overrun.");
 }

 if (this->vbo[this->sequence] == nullptr) {
 this->vbo[this->sequence] = new GLVertexBufferObject(
 65536L, GLVertexBufferObject.funcs.GL_ARRAY_BUFFER(), GLVertexBufferObject.funcs.GL_STREAM_DRAW()
 );
 this->vbo[this->sequence].create();
 this->ibo[this->sequence] = new GLVertexBufferObject(
 this->indexBufferSizeBytes, GLVertexBufferObject.funcs.GL_ELEMENT_ARRAY_BUFFER(), GLVertexBufferObject.funcs.GL_STREAM_DRAW()
 );
 this->ibo[this->sequence].create();
 }

 this->vbo[this->sequence].bind();
 this->vertices = this->vbo[this->sequence].map().asFloatBuffer();
 this->vertices.clear();
 this->ibo[this->sequence].bind();
 this->indices = this->ibo[this->sequence].map().asShortBuffer();
 this->indices.clear();
 }

 void unmap() {
 this->vbo[this->sequence].unmap();
 this->ibo[this->sequence].unmap();
 }
}
} // namespace opengl
} // namespace core
} // namespace zombie
