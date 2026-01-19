package zombie.iso;

import java.nio.ByteBuffer;
import java.nio.FloatBuffer;
import java.util.ArrayList;
import org.lwjgl.opengl.GL20;
import org.lwjgl.opengl.GL33;
import org.lwjglx.BufferUtils;
import zombie.core.Rand;
import zombie.core.opengl.RenderThread;
import zombie.core.opengl.Shader;
import zombie.core.textures.Texture;
import zombie.interfaces.ITexture;
import zombie.iso.ParticlesFire.Particle;
import zombie.iso.ParticlesFire.Zone;
import zombie.iso.ParticlesFire.ZoneType;
import zombie.iso.weather.ClimateManager;

public final class ParticlesFire extends Particles {
   int MaxParticles = 1000000;
   int MaxVortices = 4;
   int particles_data_buffer;
   ByteBuffer particule_data;
   private Texture texFireSmoke;
   private Texture texFlameFire;
   public FireShader EffectFire;
   public SmokeShader EffectSmoke;
   public Shader EffectVape;
   float windX;
   float windY;
   private static ParticlesFire instance;
   private ParticlesArray<Particle> particles;
   private ArrayList<Zone> zones;
   private int intensityFire = 0;
   private int intensitySmoke = 0;
   private int intensitySteam = 0;
   private FloatBuffer floatBuffer = BufferUtils.createFloatBuffer(16);

   public static synchronized ParticlesFire getInstance() {
      if (instance == null) {
         instance = new ParticlesFire();
      }

      return instance;
   }

   public ParticlesFire() {
      this.particles = new ParticlesArray();
      this.zones = new ArrayList<>();
      this.particule_data = BufferUtils.createByteBuffer(this.MaxParticles * 4 * 4);
      this.texFireSmoke = Texture.getSharedTexture("media/textures/FireSmokes.png");
      this.texFlameFire = Texture.getSharedTexture("media/textures/FireFlame.png");
      this.zones.clear();
      float var1 = (int)(IsoCamera.frameState.OffX + IsoCamera.frameState.OffscreenWidth / 2);
      float var2 = (int)(IsoCamera.frameState.OffY + IsoCamera.frameState.OffscreenHeight / 2);
      this.zones.add(new Zone(this, 10, var1 - 30.0F, var2 - 10.0F, var1 + 30.0F, var2 + 10.0F));
      this.zones.add(new Zone(this, 10, var1 - 200.0F, var2, 50.0F));
      this.zones.add(new Zone(this, 40, var1 + 200.0F, var2, 100.0F));
      this.zones.add(new Zone(this, 60, var1 - 150.0F, var2 - 300.0F, var1 + 250.0F, var2 - 300.0F, 10.0F));
      this.zones.add(new Zone(this, 10, var1 - 350.0F, var2 - 200.0F, var1 - 350.0F, var2 - 300.0F, 10.0F));
   }

   private void ParticlesProcess() {
      for (int var1 = 0; var1 < this.zones.size(); var1++) {
         Zone var2 = this.zones.get(var1);
         int var3 = (int)Math.ceil((var2.intensity - var2.currentParticles) * 0.1F);
         if (var2.type == ZoneType.Rectangle) {
            for (int var4 = 0; var4 < var3; var4++) {
               Particle var5 = new Particle(this);
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
               Particle var12 = new Particle(this);
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
               Particle var13 = new Particle(this);
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

   public FloatBuffer getParametersFire() {
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

   public int getFireShaderID() {
      return this.EffectFire.getID();
   }

   public int getSmokeShaderID() {
      return this.EffectSmoke.getID();
   }

   public int getVapeShaderID() {
      return this.EffectVape.getID();
   }

   public ITexture getFireFlameTexture() {
      return this.texFlameFire;
   }

   public ITexture getFireSmokeTexture() {
      return this.texFireSmoke;
   }

   public void reloadShader() {
      RenderThread.invokeOnRenderContext(() -> {
         this.EffectFire = new FireShader("fire");
         this.EffectSmoke = new SmokeShader("smoke");
         this.EffectVape = new Shader("vape");
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
            if (var4 != null) {
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
