#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <GL/glew.h>
#include "org/lwjgl/system/MemoryUtil.h"
#include "org/lwjgl/util/vector/Matrix4f.h"
#include "zombie/core/utils/BufferUtils.h"
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


class Particles {
public:
    float ParticlesTime;
    static int ParticleSystemsCount = 0;
    static int ParticleSystemsLast = 0;
   public static const std::vector<Particles> ParticleSystems = std::make_unique<std::vector<>>();
    int id;
    int particle_vertex_buffer;
    static IGLBufferObject funcs = nullptr;
    Matrix4f projectionMatrix;
    Matrix4f mvpMatrix;
    FloatBuffer floatBuffer = BufferUtils.createFloatBuffer(16);

   public static /* synchronized - TODO: add std::mutex */ int addParticle(Particles var0) {
      if (ParticleSystems.size() == ParticleSystemsCount) {
         ParticleSystems.push_back(var0);
         ParticleSystemsCount++;
         return ParticleSystems.size() - 1;
      } else {
    int var1 = ParticleSystemsLast;
         if (var1 < ParticleSystems.size()) {
            if (ParticleSystems.get(var1) == nullptr) {
               ParticleSystemsLast = var1;
               ParticleSystems.set(var1, var0);
               ParticleSystemsCount++;
            }

    return var1;
         } else {
    uint8_t var2 = 0;
            if (var2 < ParticleSystemsLast) {
               if (ParticleSystems.get(var2) == nullptr) {
                  ParticleSystemsLast = var2;
                  ParticleSystems.set(var2, var0);
                  ParticleSystemsCount++;
               }

    return var2;
            } else {
               DebugLog.log("ERROR: addParticle has unknown error");
               return -1;
            }
         }
      }
   }

   public static /* synchronized - TODO: add std::mutex */ void deleteParticle(int var0) {
      ParticleSystems.set(var0, nullptr);
      ParticleSystemsCount--;
   }

    static void init() {
      if (funcs == nullptr) {
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
    ByteBuffer var1 = MemoryUtil.memAlloc(48);
      var1.clear();
      var1.putFloat(-1.0F);
      var1.putFloat(-1.0F);
      var1.putFloat(0.0F);
      var1.putFloat(1.0F);
      var1.putFloat(-1.0F);
      var1.putFloat(0.0F);
      var1.putFloat(-1.0F);
      var1.putFloat(1.0F);
      var1.putFloat(0.0F);
      var1.putFloat(1.0F);
      var1.putFloat(1.0F);
      var1.putFloat(0.0F);
      var1.flip();
      this.particle_vertex_buffer = funcs.glGenBuffers();
      funcs.glBindBuffer(34962, this.particle_vertex_buffer);
      funcs.glBufferData(34962, var1, 35044);
      MemoryUtil.memFree(var1);
      this.createParticleBuffers();
   }

    void destroy() {
      deleteParticle(this.id);
      funcs.glDeleteBuffers(this.particle_vertex_buffer);
      this.destroyParticleBuffers();
   }

   public abstract void reloadShader();

    public Particles() {
      RenderThread.invokeOnRenderContext(() -> {
         init();
         this.initBuffers();
         this.projectionMatrix = std::make_unique<Matrix4f>();
      });
      this.reloadShader();
      this.id = addParticle(this);
   }

    static Matrix4f orthogonal(float var0, float var1, float var2, float var3, float var4, float var5) {
    Matrix4f var6 = std::make_shared<Matrix4f>();
      var6.setIdentity();
      var6.m00 = 2.0F / (var1 - var0);
      var6.m11 = 2.0F / (var3 - var2);
      var6.m22 = -2.0F / (var5 - var4);
      var6.m32 = (-var5 - var4) / (var5 - var4);
      var6.m30 = (-var1 - var0) / (var1 - var0);
      var6.m31 = (-var3 - var2) / (var3 - var2);
    return var6;
   }

    void render() {
    int var1 = IsoCamera.frameState.playerIndex;
      this.ParticlesTime = this.ParticlesTime + 0.0166F * GameTime.getInstance().getMultiplier();
      this.updateMVPMatrix();
      SpriteRenderer.instance.drawParticles(var1, 0, 0);
   }

    void updateMVPMatrix() {
      this.projectionMatrix = orthogonal(
         IsoCamera.frameState.OffX,
         IsoCamera.frameState.OffX + IsoCamera.frameState.OffscreenWidth,
         IsoCamera.frameState.OffY + IsoCamera.frameState.OffscreenHeight,
         IsoCamera.frameState.OffY,
         -1.0F,
         1.0F
      );
      this.mvpMatrix = this.projectionMatrix;
   }

    FloatBuffer getMVPMatrix() {
      this.floatBuffer.clear();
      this.floatBuffer.put(this.mvpMatrix.m00);
      this.floatBuffer.put(this.mvpMatrix.m10);
      this.floatBuffer.put(this.mvpMatrix.m20);
      this.floatBuffer.put(this.mvpMatrix.m30);
      this.floatBuffer.put(this.mvpMatrix.m01);
      this.floatBuffer.put(this.mvpMatrix.m11);
      this.floatBuffer.put(this.mvpMatrix.m21);
      this.floatBuffer.put(this.mvpMatrix.m31);
      this.floatBuffer.put(this.mvpMatrix.m02);
      this.floatBuffer.put(this.mvpMatrix.m12);
      this.floatBuffer.put(this.mvpMatrix.m22);
      this.floatBuffer.put(this.mvpMatrix.m32);
      this.floatBuffer.put(this.mvpMatrix.m03);
      this.floatBuffer.put(this.mvpMatrix.m13);
      this.floatBuffer.put(this.mvpMatrix.m23);
      this.floatBuffer.put(this.mvpMatrix.m33);
      this.floatBuffer.flip();
      return this.floatBuffer;
   }

    void getGeometry(int var1) {
      this.updateParticleParams();
      GL20.glEnableVertexAttribArray(0);
      funcs.glBindBuffer(34962, this.particle_vertex_buffer);
      GL20.glVertexAttribPointer(0, 3, 5126, false, 0, 0L);
      GL33.glVertexAttribDivisor(0, 0);
      GL31.glDrawArraysInstanced(5, 0, 4, this.getParticleCount());
   }

    void getGeometryFire(int var1) {
      this.updateParticleParams();
      GL20.glEnableVertexAttribArray(0);
      funcs.glBindBuffer(34962, this.particle_vertex_buffer);
      GL20.glVertexAttribPointer(0, 3, 5126, false, 0, 0L);
      GL33.glVertexAttribDivisor(0, 0);
      GL31.glDrawArraysInstanced(5, 0, 4, this.getParticleCount());
   }

    float getShaderTime() {
      return this.ParticlesTime;
   }

   abstract void createParticleBuffers();

   abstract void destroyParticleBuffers();

   abstract void updateParticleParams();

   abstract int getParticleCount();
}
} // namespace iso
} // namespace zombie
