#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/lwjgl/opengl/GL20.h"
#include "org/lwjgl/opengl/GL33.h"
#include "org/lwjglx/BufferUtils.h"
#include "zombie/core/Rand.h"
#include "zombie/core/opengl/RenderThread.h"
#include "zombie/core/opengl/Shader.h"
#include "zombie/core/textures/Texture.h"
#include "zombie/interfaces/ITexture.h"
#include "zombie/iso/ParticlesFire/Particle.h"
#include "zombie/iso/ParticlesFire/Zone.h"
#include "zombie/iso/ParticlesFire/ZoneType.h"
#include "zombie/iso/weather/ClimateManager.h"
#include <filesystem>

namespace zombie {
namespace iso {


class ParticlesFire : public Particles {
public:
    int MaxParticles = 1000000;
    int MaxVortices = 4;
    int particles_data_buffer;
    ByteBuffer particule_data;
    Texture texFireSmoke;
    Texture texFlameFire;
    FireShader EffectFire;
    SmokeShader EffectSmoke;
    Shader EffectVape;
    float windX;
    float windY;
    static ParticlesFire instance;
   private ParticlesArray<Particle> particles;
   private std::vector<Zone> zones;
    int intensityFire = 0;
    int intensitySmoke = 0;
    int intensitySteam = 0;
    FloatBuffer floatBuffer = BufferUtils.createFloatBuffer(16);

   public static /* synchronized - TODO: add std::mutex */ ParticlesFire getInstance() {
      if (instance == nullptr) {
         instance = std::make_unique<ParticlesFire>();
      }

    return instance;
   }

    public ParticlesFire() {
      this.particles = std::make_unique<ParticlesArray>();
      this.zones = std::make_unique<std::vector<>>();
      this.particule_data = BufferUtils.createByteBuffer(this.MaxParticles * 4 * 4);
      this.texFireSmoke = Texture.getSharedTexture("media/textures/FireSmokes.png");
      this.texFlameFire = Texture.getSharedTexture("media/textures/FireFlame.png");
      this.zones.clear();
    float var1 = (int)(IsoCamera.frameState.OffX + IsoCamera.frameState.OffscreenWidth / 2);
    float var2 = (int)(IsoCamera.frameState.OffY + IsoCamera.frameState.OffscreenHeight / 2);
      this.zones.push_back(std::make_shared<Zone>(this, 10, var1 - 30.0F, var2 - 10.0F, var1 + 30.0F, var2 + 10.0F));
      this.zones.push_back(std::make_shared<Zone>(this, 10, var1 - 200.0F, var2, 50.0F));
      this.zones.push_back(std::make_shared<Zone>(this, 40, var1 + 200.0F, var2, 100.0F));
      this.zones.push_back(std::make_shared<Zone>(this, 60, var1 - 150.0F, var2 - 300.0F, var1 + 250.0F, var2 - 300.0F, 10.0F));
      this.zones.push_back(std::make_shared<Zone>(this, 10, var1 - 350.0F, var2 - 200.0F, var1 - 350.0F, var2 - 300.0F, 10.0F));
   }

    void ParticlesProcess() {
      for (int var1 = 0; var1 < this.zones.size(); var1++) {
    Zone var2 = this.zones.get(var1);
    int var3 = (int)Math.ceil((var2.intensity - var2.currentParticles) * 0.1F);
         if (var2.type == ZoneType.Rectangle) {
            for (int var4 = 0; var4 < var3; var4++) {
    Particle var5 = std::make_shared<Particle>(this);
               var5.x = Rand.Next(var2.x0, var2.x1);
               var5.y = Rand.Next(var2.y0, var2.y1);
               var5.vx = Rand.Next(-3.0F, 3.0F);
               var5.vy = Rand.Next(1.0F, 5.0F);
               var5.tShift = 0.0F;
               var5.id = Rand.Next(-1000000.0F, 1000000.0F);
               var5.zone = var2;
               var2.currentParticles++;
               this.particles.addParticle(var5);
            }
         }

         if (var2.type == ZoneType.Circle) {
            for (int var9 = 0; var9 < var3; var9++) {
    Particle var12 = std::make_shared<Particle>(this);
    float var6 = Rand.Next(0.0F, (float) (Math.PI * 2));
    float var7 = Rand.Next(0.0F, var2.r);
               var12.x = (float)(var2.x0 + var7 * Math.cos(var6));
               var12.y = (float)(var2.y0 + var7 * Math.sin(var6));
               var12.vx = Rand.Next(-3.0F, 3.0F);
               var12.vy = Rand.Next(1.0F, 5.0F);
               var12.tShift = 0.0F;
               var12.id = Rand.Next(-1000000.0F, 1000000.0F);
               var12.zone = var2;
               var2.currentParticles++;
               this.particles.addParticle(var12);
            }
         }

         if (var2.type == ZoneType.Line) {
            for (int var10 = 0; var10 < var3; var10++) {
    Particle var13 = std::make_shared<Particle>(this);
    float var14 = Rand.Next(0.0F, (float) (Math.PI * 2));
    float var15 = Rand.Next(0.0F, var2.r);
    float var8 = Rand.Next(0.0F, 1.0F);
               var13.x = (float)(var2.x0 * var8 + var2.x1 * (1.0F - var8) + var15 * Math.cos(var14));
               var13.y = (float)(var2.y0 * var8 + var2.y1 * (1.0F - var8) + var15 * Math.sin(var14));
               var13.vx = Rand.Next(-3.0F, 3.0F);
               var13.vy = Rand.Next(1.0F, 5.0F);
               var13.tShift = 0.0F;
               var13.id = Rand.Next(-1000000.0F, 1000000.0F);
               var13.zone = var2;
               var2.currentParticles++;
               this.particles.addParticle(var13);
            }
         }

         if (var3 < 0) {
            for (int var11 = 0; var11 < -var3; var11++) {
               var2.currentParticles--;
               this.particles.deleteParticle(Rand.Next(0, this.particles.getCount() + 1));
            }
         }
      }
   }

    FloatBuffer getParametersFire() {
      this.floatBuffer.clear();
      this.floatBuffer.put(this.windX);
      this.floatBuffer.put(this.intensityFire);
      this.floatBuffer.put(0.0F);
      this.floatBuffer.put(this.windY);
      this.floatBuffer.put(0.0F);
      this.floatBuffer.put(0.0F);
      this.floatBuffer.put(0.0F);
      this.floatBuffer.put(0.0F);
      this.floatBuffer.put(0.0F);
      this.floatBuffer.put(0.0F);
      this.floatBuffer.put(0.0F);
      this.floatBuffer.put(0.0F);
      this.floatBuffer.flip();
      return this.floatBuffer;
   }

    int getFireShaderID() {
      return this.EffectFire.getID();
   }

    int getSmokeShaderID() {
      return this.EffectSmoke.getID();
   }

    int getVapeShaderID() {
      return this.EffectVape.getID();
   }

    ITexture getFireFlameTexture() {
      return this.texFlameFire;
   }

    ITexture getFireSmokeTexture() {
      return this.texFireSmoke;
   }

    void reloadShader() {
      RenderThread.invokeOnRenderContext(() -> {
         this.EffectFire = std::make_shared<FireShader>("fire");
         this.EffectSmoke = std::make_shared<SmokeShader>("smoke");
         this.EffectVape = std::make_shared<Shader>("vape");
      });
   }

    void createParticleBuffers() {
      this.particles_data_buffer = funcs.glGenBuffers();
      funcs.glBindBuffer(34962, this.particles_data_buffer);
      funcs.glBufferData(34962, this.MaxParticles * 4 * 4, 35044);
   }

    void destroyParticleBuffers() {
      funcs.glDeleteBuffers(this.particles_data_buffer);
   }

    void updateParticleParams() {
    float var1 = ClimateManager.getInstance().getWindAngleIntensity();
    float var2 = ClimateManager.getInstance().getWindIntensity();
      this.windX = (float)Math.sin(var1 * 6.0F) * var2;
      this.windY = (float)Math.cos(var1 * 6.0F) * var2;
      this.ParticlesProcess();
      if (this.particles.getNeedToUpdate()) {
         this.particles.defragmentParticle();
         this.particule_data.clear();

         for (int var3 = 0; var3 < this.particles.size(); var3++) {
    Particle var4 = (Particle)this.particles.get(var3);
            if (var4 != nullptr) {
               this.particule_data.putFloat(var4.x);
               this.particule_data.putFloat(var4.y);
               this.particule_data.putFloat(var4.id);
               this.particule_data.putFloat((float)var3 / this.particles.size());
            }
         }

         this.particule_data.flip();
      }

      funcs.glBindBuffer(34962, this.particles_data_buffer);
      funcs.glBufferData(34962, this.particule_data, 35040);
      GL20.glEnableVertexAttribArray(1);
      funcs.glBindBuffer(34962, this.particles_data_buffer);
      GL20.glVertexAttribPointer(1, 4, 5126, false, 0, 0L);
      GL33.glVertexAttribDivisor(1, 1);
   }

    int getParticleCount() {
      return this.particles.getCount();
   }
}
} // namespace iso
} // namespace zombie
