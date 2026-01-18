#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/lwjgl/opengl/GL.h"
#include "org/lwjgl/opengl/GL20.h"
#include "org/lwjgl/opengl/GL31.h"
#include "org/lwjgl/opengl/GL33.h"
#include "org/lwjgl/system/MemoryUtil.h"
#include "org/lwjgl/util/vector/Matrix4f.h"
#include "org/lwjglx/BufferUtils.h"
#include "zombie/GameTime.h"
#include "zombie/core/SpriteRenderer.h"
#include "zombie/core/VBO/GLBufferObject15.h"
#include "zombie/core/VBO/GLBufferObjectARB.h"
#include "zombie/core/VBO/IGLBufferObject.h"
#include "zombie/core/opengl/RenderThread.h"
#include "zombie/debug/DebugLog.h"
#include <filesystem>

namespace zombie {
namespace iso {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class Particles {
public:
 float ParticlesTime;
 static int ParticleSystemsCount = 0;
 static int ParticleSystemsLast = 0;
 public static ArrayList<Particles> ParticleSystems = std::make_unique<ArrayList<>>();
 int id;
 int particle_vertex_buffer;
 static IGLBufferObject funcs = nullptr;
 Matrix4f projectionMatrix;
 Matrix4f mvpMatrix;
 FloatBuffer floatBuffer = BufferUtils.createFloatBuffer(16);

 public static synchronized int addParticle(Particles particles) {
 if (ParticleSystems.size() == ParticleSystemsCount) {
 ParticleSystems.add(particles);
 ParticleSystemsCount++;
 return ParticleSystems.size() - 1;
 } else {
 int int0 = ParticleSystemsLast;
 if (int0 < ParticleSystems.size()) {
 if (ParticleSystems.get(int0) == nullptr) {
 ParticleSystemsLast = int0;
 ParticleSystems.set(int0, particles);
 ParticleSystemsCount++;
 }

 return int0;
 } else {
 uint8_t byte0 = 0;
 if (byte0 < ParticleSystemsLast) {
 if (ParticleSystems.get(byte0) == nullptr) {
 ParticleSystemsLast = byte0;
 ParticleSystems.set(byte0, particles);
 ParticleSystemsCount++;
 }

 return byte0;
 } else {
 DebugLog.log("ERROR: addParticle has unknown error");
 return -1;
 }
 }
 }
 }

 public static synchronized void deleteParticle(int int0) {
 ParticleSystems.set(int0, nullptr);
 ParticleSystemsCount--;
 }

 static void init() {
 if (funcs.empty()) {
 if (!GL.getCapabilities().OpenGL33) {
 System.out.println("OpenGL 3.3 don't supported");
 }

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
 }
 }

 void initBuffers() {
 ByteBuffer byteBuffer = MemoryUtil.memAlloc(48);
 byteBuffer.clear();
 byteBuffer.putFloat(-1.0F);
 byteBuffer.putFloat(-1.0F);
 byteBuffer.putFloat(0.0F);
 byteBuffer.putFloat(1.0F);
 byteBuffer.putFloat(-1.0F);
 byteBuffer.putFloat(0.0F);
 byteBuffer.putFloat(-1.0F);
 byteBuffer.putFloat(1.0F);
 byteBuffer.putFloat(0.0F);
 byteBuffer.putFloat(1.0F);
 byteBuffer.putFloat(1.0F);
 byteBuffer.putFloat(0.0F);
 byteBuffer.flip();
 this->particle_vertex_buffer = funcs.glGenBuffers();
 funcs.glBindBuffer(34962, this->particle_vertex_buffer);
 funcs.glBufferData(34962, byteBuffer, 35044);
 MemoryUtil.memFree(byteBuffer);
 this->createParticleBuffers();
 }

 void destroy() {
 deleteParticle(this->id);
 funcs.glDeleteBuffers(this->particle_vertex_buffer);
 this->destroyParticleBuffers();
 }

 public void reloadShader();

 public Particles() {
 RenderThread.invokeOnRenderContext(() -> {
 init();
 this->initBuffers();
 this->projectionMatrix = std::make_unique<Matrix4f>();
 });
 this->reloadShader();
 this->id = addParticle(this);
 }

 static Matrix4f orthogonal(float float1, float float0, float float3, float float2, float float5, float float4) {
 Matrix4f matrix4f = new Matrix4f();
 matrix4f.setIdentity();
 matrix4f.m00 = 2.0F / (float0 - float1);
 matrix4f.m11 = 2.0F / (float2 - float3);
 matrix4f.m22 = -2.0F / (float4 - float5);
 matrix4f.m32 = (-float4 - float5) / (float4 - float5);
 matrix4f.m30 = (-float0 - float1) / (float0 - float1);
 matrix4f.m31 = (-float2 - float3) / (float2 - float3);
 return matrix4f;
 }

 void render() {
 int int0 = IsoCamera.frameState.playerIndex;
 this->ParticlesTime = this->ParticlesTime + 0.0166F * GameTime.getInstance().getMultiplier();
 this->updateMVPMatrix();
 SpriteRenderer.instance.drawParticles(int0, 0, 0);
 }

 void updateMVPMatrix() {
 this->projectionMatrix = orthogonal(
 IsoCamera.frameState.OffX,
 IsoCamera.frameState.OffX + IsoCamera.frameState.OffscreenWidth,
 IsoCamera.frameState.OffY + IsoCamera.frameState.OffscreenHeight,
 IsoCamera.frameState.OffY,
 -1.0F,
 1.0F
 );
 this->mvpMatrix = this->projectionMatrix;
 }

 FloatBuffer getMVPMatrix() {
 this->floatBuffer.clear();
 this->floatBuffer.put(this->mvpMatrix.m00);
 this->floatBuffer.put(this->mvpMatrix.m10);
 this->floatBuffer.put(this->mvpMatrix.m20);
 this->floatBuffer.put(this->mvpMatrix.m30);
 this->floatBuffer.put(this->mvpMatrix.m01);
 this->floatBuffer.put(this->mvpMatrix.m11);
 this->floatBuffer.put(this->mvpMatrix.m21);
 this->floatBuffer.put(this->mvpMatrix.m31);
 this->floatBuffer.put(this->mvpMatrix.m02);
 this->floatBuffer.put(this->mvpMatrix.m12);
 this->floatBuffer.put(this->mvpMatrix.m22);
 this->floatBuffer.put(this->mvpMatrix.m32);
 this->floatBuffer.put(this->mvpMatrix.m03);
 this->floatBuffer.put(this->mvpMatrix.m13);
 this->floatBuffer.put(this->mvpMatrix.m23);
 this->floatBuffer.put(this->mvpMatrix.m33);
 this->floatBuffer.flip();
 return this->floatBuffer;
 }

 void getGeometry(int var1) {
 this->updateParticleParams();
 GL20.glEnableVertexAttribArray(0);
 funcs.glBindBuffer(34962, this->particle_vertex_buffer);
 GL20.glVertexAttribPointer(0, 3, 5126, false, 0, 0L);
 GL33.glVertexAttribDivisor(0, 0);
 GL31.glDrawArraysInstanced(5, 0, 4, this->getParticleCount());
 }

 void getGeometryFire(int var1) {
 this->updateParticleParams();
 GL20.glEnableVertexAttribArray(0);
 funcs.glBindBuffer(34962, this->particle_vertex_buffer);
 GL20.glVertexAttribPointer(0, 3, 5126, false, 0, 0L);
 GL33.glVertexAttribDivisor(0, 0);
 GL31.glDrawArraysInstanced(5, 0, 4, this->getParticleCount());
 }

 float getShaderTime() {
 return this->ParticlesTime;
 }

 void createParticleBuffers();

 void destroyParticleBuffers();

 void updateParticleParams();

 int getParticleCount();
}
} // namespace iso
} // namespace zombie
