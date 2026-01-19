package zombie.iso;

import java.nio.FloatBuffer;
import java.nio.ShortBuffer;
import java.util.ArrayList;
import org.joml.Vector2f;
import org.joml.Vector4f;
import org.lwjgl.opengl.GL;
import org.lwjgl.opengl.GL11;
import org.lwjgl.opengl.GL12;
import org.lwjgl.opengl.GL13;
import org.lwjglx.BufferUtils;
import zombie.GameTime;
import zombie.core.Core;
import zombie.core.PerformanceSettings;
import zombie.core.SpriteRenderer;
import zombie.core.opengl.RenderThread;
import zombie.core.opengl.Shader;
import zombie.core.opengl.SharedVertexBufferObjects;
import zombie.core.textures.Texture;
import zombie.debug.DebugLog;
import zombie.debug.DebugOptions;
import zombie.interfaces.ITexture;
import zombie.iso.IsoPuddles.PuddlesFloat;
import zombie.iso.IsoPuddles.RenderData;
import zombie.iso.weather.ClimateManager;
import zombie.network.GameServer;

public final class IsoPuddles {
   public Shader Effect;
   private float PuddlesWindAngle;
   private float PuddlesWindIntensity;
   private float PuddlesTime;
   private final Vector2f PuddlesParamWindINT;
   public static boolean leakingPuddlesInTheRoom = false;
   private Texture texHM;
   private int apiId;
   private static IsoPuddles instance;
   private static boolean isShaderEnable = false;
   static final int BYTES_PER_FLOAT = 4;
   static final int FLOATS_PER_VERTEX = 7;
   static final int BYTES_PER_VERTEX = 28;
   static final int VERTICES_PER_SQUARE = 4;
   public static final SharedVertexBufferObjects VBOs = new SharedVertexBufferObjects(28);
   private final RenderData[][] renderData = new RenderData[3][4];
   private final Vector4f shaderOffset = new Vector4f();
   private final Vector4f shaderOffsetMain = new Vector4f();
   private FloatBuffer floatBuffer = BufferUtils.createFloatBuffer(16);
   public static final int BOOL_MAX = 0;
   public static final int FLOAT_RAIN = 0;
   public static final int FLOAT_WETGROUND = 1;
   public static final int FLOAT_MUDDYPUDDLES = 2;
   public static final int FLOAT_PUDDLESSIZE = 3;
   public static final int FLOAT_RAININTENSITY = 4;
   public static final int FLOAT_MAX = 5;
   private PuddlesFloat rain;
   private PuddlesFloat wetGround;
   private PuddlesFloat muddyPuddles;
   private PuddlesFloat puddlesSize;
   private PuddlesFloat rainIntensity;
   private final PuddlesFloat[] climateFloats = new PuddlesFloat[5];

   public static synchronized IsoPuddles getInstance() {
      if (instance == null) {
         instance = new IsoPuddles();
      }

      return instance;
   }

   public boolean getShaderEnable() {
      return isShaderEnable;
   }

   public IsoPuddles() {
      if (GameServer.bServer) {
         Core.getInstance().setPerfPuddles(3);
         this.applyPuddlesQuality();
         this.PuddlesParamWindINT = new Vector2f(0.0F);
         this.setup();
      } else {
         this.texHM = Texture.getSharedTexture("media/textures/puddles_hm.png");
         RenderThread.invokeOnRenderContext(() -> {
            if (GL.getCapabilities().OpenGL30) {
               this.apiId = 1;
            }

            if (GL.getCapabilities().GL_ARB_framebuffer_object) {
               this.apiId = 2;
            }

            if (GL.getCapabilities().GL_EXT_framebuffer_object) {
               this.apiId = 3;
            }
         });
         this.applyPuddlesQuality();
         this.PuddlesParamWindINT = new Vector2f(0.0F);

         for (int var1 = 0; var1 < this.renderData.length; var1++) {
            for (int var2 = 0; var2 < 4; var2++) {
               this.renderData[var1][var2] = new RenderData();
            }
         }

         this.setup();
      }
   }

   public void applyPuddlesQuality() {
      leakingPuddlesInTheRoom = Core.getInstance().getPerfPuddles() == 0;
      if (Core.getInstance().getPerfPuddles() == 3) {
         isShaderEnable = false;
      } else {
         isShaderEnable = true;
         if (PerformanceSettings.PuddlesQuality == 2) {
            RenderThread.invokeOnRenderContext(() -> {
               this.Effect = new PuddlesShader("puddles_lq");
               this.Effect.Start();
               this.Effect.End();
            });
         }

         if (PerformanceSettings.PuddlesQuality == 1) {
            RenderThread.invokeOnRenderContext(() -> {
               this.Effect = new PuddlesShader("puddles_mq");
               this.Effect.Start();
               this.Effect.End();
            });
         }

         if (PerformanceSettings.PuddlesQuality == 0) {
            RenderThread.invokeOnRenderContext(() -> {
               this.Effect = new PuddlesShader("puddles_hq");
               this.Effect.Start();
               this.Effect.End();
            });
         }
      }
   }

   public Vector4f getShaderOffset() {
      int var1 = SpriteRenderer.instance.getRenderingPlayerIndex();
      PlayerCamera var2 = SpriteRenderer.instance.getRenderingPlayerCamera(var1);
      return this.shaderOffset
         .set(
            var2.getOffX() - IsoCamera.getOffscreenLeft(var1) * var2.zoom,
            var2.getOffY() + IsoCamera.getOffscreenTop(var1) * var2.zoom,
            var2.OffscreenWidth,
            var2.OffscreenHeight
         );
   }

   public Vector4f getShaderOffsetMain() {
      int var1 = IsoCamera.frameState.playerIndex;
      PlayerCamera var2 = IsoCamera.cameras[var1];
      return this.shaderOffsetMain
         .set(
            var2.getOffX() - IsoCamera.getOffscreenLeft(var1) * var2.zoom,
            var2.getOffY() + IsoCamera.getOffscreenTop(var1) * var2.zoom,
            IsoCamera.getOffscreenWidth(var1),
            IsoCamera.getOffscreenHeight(var1)
         );
   }

   public void render(ArrayList<IsoGridSquare> var1, int var2) {
      if (DebugOptions.instance.Weather.WaterPuddles.getValue()) {
         int var3 = SpriteRenderer.instance.getMainStateIndex();
         int var4 = IsoCamera.frameState.playerIndex;
         RenderData var5 = this.renderData[var3][var4];
         if (var2 == 0) {
            var5.clear();
         }

         if (!var1.isEmpty()) {
            if (this.getShaderEnable()) {
               if (Core.getInstance().getUseShaders()) {
                  if (Core.getInstance().getPerfPuddles() != 3) {
                     if (var2 <= 0 || Core.getInstance().getPerfPuddles() <= 0) {
                        if (this.wetGround.getFinalValue() != 0.0 || this.puddlesSize.getFinalValue() != 0.0) {
                           for (int var6 = 0; var6 < var1.size(); var6++) {
                              IsoPuddlesGeometry var7 = ((IsoGridSquare)var1.get(var6)).getPuddles();
                              if (var7 != null && var7.shouldRender()) {
                                 var7.updateLighting(var4);
                                 var5.addSquare(var2, var7);
                              }
                           }

                           if (var5.squaresPerLevel[var2] > 0) {
                              SpriteRenderer.instance.drawPuddles(this.Effect, var4, this.apiId, var2);
                           }
                        }
                     }
                  }
               }
            }
         }
      }
   }

   public void puddlesProjection() {
      int var1 = SpriteRenderer.instance.getRenderingPlayerIndex();
      PlayerCamera var2 = SpriteRenderer.instance.getRenderingPlayerCamera(var1);
      GL11.glOrtho(var2.getOffX(), var2.getOffX() + var2.OffscreenWidth, var2.getOffY() + var2.OffscreenHeight, var2.getOffY(), -1.0, 1.0);
   }

   public void puddlesGeometry(int var1) {
      int var2 = SpriteRenderer.instance.getRenderStateIndex();
      int var3 = SpriteRenderer.instance.getRenderingPlayerIndex();
      RenderData var4 = this.renderData[var2][var3];
      int var5 = 0;

      for (int var6 = 0; var6 < var1; var6++) {
         var5 += var4.squaresPerLevel[var6];
      }

      int var8 = var4.squaresPerLevel[var1];

      while (var8 > 0) {
         int var7 = this.renderSome(var5, var8);
         var5 += var7;
         var8 -= var7;
      }

      SpriteRenderer.ringBuffer.restoreVBOs = true;
   }

   private int renderSome(int var1, int var2) {
      VBOs.next();
      FloatBuffer var3 = VBOs.vertices;
      ShortBuffer var4 = VBOs.indices;
      GL13.glActiveTexture(33985);
      GL13.glClientActiveTexture(33985);
      GL11.glTexCoordPointer(2, 5126, 28, 8L);
      GL11.glEnableClientState(32888);
      GL13.glActiveTexture(33984);
      GL13.glClientActiveTexture(33984);
      GL11.glTexCoordPointer(2, 5126, 28, 0L);
      GL11.glColorPointer(4, 5121, 28, 24L);
      GL11.glVertexPointer(2, 5126, 28, 16L);
      int var5 = SpriteRenderer.instance.getRenderStateIndex();
      int var6 = SpriteRenderer.instance.getRenderingPlayerIndex();
      RenderData var7 = this.renderData[var5][var6];
      int var8 = Math.min(var2 * 4, VBOs.bufferSizeVertices);
      var3.put(var7.data, var1 * 4 * 7, var8 * 7);
      byte var9 = 0;
      byte var10 = 0;

      for (int var11 = 0; var11 < var8 / 4; var11++) {
         var4.put(var9);
         var4.put((short)(var9 + 1));
         var4.put((short)(var9 + 2));
         var4.put(var9);
         var4.put((short)(var9 + 2));
         var4.put((short)(var9 + 3));
         var9 += 4;
         var10 += 6;
      }

      VBOs.unmap();
      byte var15 = 0;
      byte var13 = 0;
      GL12.glDrawRangeElements(4, var15, var15 + var9, var10 - var13, 5123, var13 * 2);
      return var8 / 4;
   }

   public void update(ClimateManager var1) {
      this.PuddlesWindAngle = var1.getCorrectedWindAngleIntensity();
      this.PuddlesWindIntensity = var1.getWindIntensity();
      this.rain.setFinalValue(var1.getRainIntensity());
      float var2 = GameTime.getInstance().getMultiplier() / 1.6F;
      float var3 = 2.0E-5F * var2 * var1.getTemperature();
      float var4 = 2.0E-5F * var2;
      float var5 = 2.0E-4F * var2;
      float var6 = this.rain.getFinalValue();
      var6 = var6 * var6 * 0.05F * var2;
      this.rainIntensity.setFinalValue(this.rain.getFinalValue() * 2.0F);
      this.wetGround.addFinalValue(var6);
      this.muddyPuddles.addFinalValue(var6 * 2.0F);
      this.puddlesSize.addFinalValueForMax(var6 * 0.01F, 0.7F);
      if (var6 == 0.0) {
         this.wetGround.addFinalValue(-var3);
         this.muddyPuddles.addFinalValue(-var5);
      }

      if (this.wetGround.getFinalValue() == 0.0) {
         this.puddlesSize.addFinalValue(-var4);
      }

      this.PuddlesTime = this.PuddlesTime + 0.0166F * GameTime.getInstance().getMultiplier();
      this.PuddlesParamWindINT
         .add(
            (float)Math.sin(this.PuddlesWindAngle * 6.0F) * this.PuddlesWindIntensity * 0.05F,
            (float)Math.cos(this.PuddlesWindAngle * 6.0F) * this.PuddlesWindIntensity * 0.05F
         );
   }

   public float getShaderTime() {
      return this.PuddlesTime;
   }

   public float getPuddlesSize() {
      return this.puddlesSize.getFinalValue();
   }

   public ITexture getHMTexture() {
      return this.texHM;
   }

   public FloatBuffer getPuddlesParams(int var1) {
      this.floatBuffer.clear();
      this.floatBuffer.put(this.PuddlesParamWindINT.x);
      this.floatBuffer.put(this.muddyPuddles.getFinalValue());
      this.floatBuffer.put(0.0F);
      this.floatBuffer.put(0.0F);
      this.floatBuffer.put(this.PuddlesParamWindINT.y);
      this.floatBuffer.put(this.wetGround.getFinalValue());
      this.floatBuffer.put(0.0F);
      this.floatBuffer.put(0.0F);
      this.floatBuffer.put(this.PuddlesWindIntensity * 1.0F);
      this.floatBuffer.put(this.puddlesSize.getFinalValue());
      this.floatBuffer.put(0.0F);
      this.floatBuffer.put(0.0F);
      this.floatBuffer.put(var1);
      this.floatBuffer.put(this.rainIntensity.getFinalValue());
      this.floatBuffer.put(0.0F);
      this.floatBuffer.put(0.0F);
      this.floatBuffer.flip();
      return this.floatBuffer;
   }

   public float getRainIntensity() {
      return this.rainIntensity.getFinalValue();
   }

   public int getFloatMax() {
      return 5;
   }

   public int getBoolMax() {
      return 0;
   }

   public PuddlesFloat getPuddlesFloat(int var1) {
      if (var1 >= 0 && var1 < 5) {
         return this.climateFloats[var1];
      } else {
         DebugLog.log("ERROR: Climate: cannot get float override id.");
         return null;
      }
   }

   private PuddlesFloat initClimateFloat(int var1, String var2) {
      if (var1 >= 0 && var1 < 5) {
         return this.climateFloats[var1].init(var1, var2);
      } else {
         DebugLog.log("ERROR: Climate: cannot get float override id.");
         return null;
      }
   }

   private void setup() {
      for (int var1 = 0; var1 < this.climateFloats.length; var1++) {
         this.climateFloats[var1] = new PuddlesFloat();
      }

      this.rain = this.initClimateFloat(0, "INPUT: RAIN");
      this.wetGround = this.initClimateFloat(1, "Wet Ground");
      this.muddyPuddles = this.initClimateFloat(2, "Muddy Puddles");
      this.puddlesSize = this.initClimateFloat(3, "Puddles Size");
      this.rainIntensity = this.initClimateFloat(4, "Rain Intensity");
   }
}
