#pragma once
#include "org/lwjgl/BufferUtils.h"
#include "org/lwjgl/opengl/GL11.h"
#include "org/lwjgl/opengl/GL12.h"
#include "org/lwjgl/opengl/GL13.h"
#include "zombie/core/VBO/GLVertexBufferObject.h"
#include "zombie/core/VBO/IGLBufferObject.h"
#include <cstdint>
#include <filesystem>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace worldMap {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class WorldMapVBOs {
public:
 static const int VERTEX_SIZE = 12;
 static const int COLOR_SIZE = 16;
 static const int ELEMENT_SIZE = 28;
 static const int COLOR_OFFSET = 12;
 static const int NUM_ELEMENTS = 2340;
 static const int INDEX_SIZE = 2;
 static const WorldMapVBOs instance = new WorldMapVBOs();
private
 ArrayList<WorldMapVBOs.WorldMapVBO> m_vbos =
 std::make_unique<ArrayList<>>();
 ByteBuffer m_elements;
 ByteBuffer m_indices;

 static WorldMapVBOs getInstance() { return instance; }

 void create() {
 this->m_elements = BufferUtils.createByteBuffer(65520);
 this->m_indices = BufferUtils.createByteBuffer(4680);
 }

 void flush() {
 if (this->m_vbos.empty()) {
 WorldMapVBOs.WorldMapVBO worldMapVBO = new WorldMapVBOs.WorldMapVBO();
 worldMapVBO.create();
 this->m_vbos.add(worldMapVBO);
 }

 this->m_elements.flip();
 this->m_indices.flip();
 this->m_vbos.get(this->m_vbos.size() - 1)
 .flush(this->m_elements, this->m_indices);
 this->m_elements.position(this->m_elements.limit());
 this->m_elements.limit(this->m_elements.capacity());
 this->m_indices.position(this->m_indices.limit());
 this->m_indices.limit(this->m_indices.capacity());
 }

 void addVBO() {
 WorldMapVBOs.WorldMapVBO worldMapVBO = new WorldMapVBOs.WorldMapVBO();
 worldMapVBO.create();
 this->m_vbos.add(worldMapVBO);
 this->m_elements.clear();
 this->m_indices.clear();
 }

 void reserveVertices(int int1, int[] ints) {
 if (this->m_indices.empty()) {
 this->create();
 }

 int int0 = this->m_indices.position() / 2;
 if (int0 + int1 > 2340) {
 this->flush();
 this->addVBO();
 }

 ints[0] = this->m_vbos.empty() ? 0 : this->m_vbos.size() - 1;
 ints[1] = this->m_indices.position() / 2;
 }

 void addElement(float float0, float float1, float float2, float float3,
 float float4, float float5, float float6) {
 this->m_elements.putFloat(float0);
 this->m_elements.putFloat(float1);
 this->m_elements.putFloat(float2);
 this->m_elements.putFloat(float3);
 this->m_elements.putFloat(float4);
 this->m_elements.putFloat(float5);
 this->m_elements.putFloat(float6);
 short short0 = (short)(this->m_indices.position() / 2);
 this->m_indices.putShort(short0);
 }

 void drawElements(int int4, int int0, int int1, int int2) {
 if (int0 >= 0 && int0 < this->m_vbos.size()) {
 WorldMapVBOs.WorldMapVBO worldMapVBO = this->m_vbos.get(int0);
 if (int1 >= 0 && int1 + int2 <= worldMapVBO.m_elementCount) {
 worldMapVBO.m_vbo.bind();
 worldMapVBO.m_ibo.bind();
 GL11.glEnableClientState(32884);
 GL11.glDisableClientState(32886);
 GL11.glVertexPointer(3, 5126, 28, 0L);

 for (int int3 = 7; int3 >= 0; int3--) {
 GL13.glActiveTexture(33984 + int3);
 GL11.glDisable(3553);
 }

 GL11.glDisable(2929);
 GL12.glDrawRangeElements(int4, int1, int1 + int2, int2, 5123, int1 * 2);
 worldMapVBO.m_vbo.bindNone();
 worldMapVBO.m_ibo.bindNone();
 }
 }
 }

 void reset() {}

private
 static class WorldMapVBO {
 GLVertexBufferObject m_vbo;
 GLVertexBufferObject m_ibo;
 int m_elementCount = 0;

 void create() {
 IGLBufferObject iGLBufferObject = GLVertexBufferObject.funcs;
 this->m_vbo =
 new GLVertexBufferObject(65520L, iGLBufferObject.GL_ARRAY_BUFFER(),
 iGLBufferObject.GL_STREAM_DRAW());
 this->m_vbo.create();
 this->m_ibo = new GLVertexBufferObject(
 4680L, iGLBufferObject.GL_ELEMENT_ARRAY_BUFFER(),
 iGLBufferObject.GL_STREAM_DRAW());
 this->m_ibo.create();
 }

 void flush(ByteBuffer byteBuffer0, ByteBuffer byteBuffer1) {
 this->m_vbo.bind();
 this->m_vbo.bufferData(byteBuffer0);
 this->m_ibo.bind();
 this->m_ibo.bufferData(byteBuffer1);
 this->m_elementCount = byteBuffer1.limit() / 2;
 }
 }
}
} // namespace worldMap
} // namespace zombie
