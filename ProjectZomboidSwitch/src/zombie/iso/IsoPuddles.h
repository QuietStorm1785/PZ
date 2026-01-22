#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/joml/Vector2f.h"
#include "org/joml/Vector4f.h"
#include "org/lwjgl/opengl/GL.h"
#include "org/lwjgl/opengl/GL11.h"
#include "org/lwjgl/opengl/GL12.h"
#include "org/lwjgl/opengl/GL13.h"
#include "org/lwjglx/BufferUtils.h"
#include "zombie/GameTime.h"
#include "zombie/core/Core.h"
#include "zombie/core/PerformanceSettings.h"
#include "zombie/core/SpriteRenderer.h"
#include "zombie/core/opengl/RenderThread.h"
#include "zombie/core/opengl/Shader.h"
#include "zombie/core/opengl/SharedVertexBufferObjects.h"
#include "zombie/core/textures/Texture.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugOptions.h"
#include "zombie/interfaces/ITexture.h"
#include "zombie/iso/IsoPuddles/PuddlesFloat.h"
#include "zombie/iso/IsoPuddles/RenderData.h"
#include "zombie/iso/weather/ClimateManager.h"
#include "zombie/network/GameServer.h"
#include <filesystem>

namespace zombie {
namespace iso {


class IsoPuddles {
public:
    Shader Effect;
    float PuddlesWindAngle;
    float PuddlesWindIntensity;
    float PuddlesTime;
    const Vector2f PuddlesParamWindINT;
    static bool leakingPuddlesInTheRoom = false;
    Texture texHM;
    int apiId;
    static IsoPuddles instance;
    static bool isShaderEnable = false;
    static const int BYTES_PER_FLOAT = 4;
    static const int FLOATS_PER_VERTEX = 7;
    static const int BYTES_PER_VERTEX = 28;
    static const int VERTICES_PER_SQUARE = 4;
    static const SharedVertexBufferObjects VBOs = std::make_shared<SharedVertexBufferObjects>(28);
   private const RenderData[][] renderData = new RenderData[3][4];
    const Vector4f shaderOffset = std::make_shared<Vector4f>();
    const Vector4f shaderOffsetMain = std::make_shared<Vector4f>();
    FloatBuffer floatBuffer = BufferUtils.createFloatBuffer(16);
    static const int BOOL_MAX = 0;
    static const int FLOAT_RAIN = 0;
    static const int FLOAT_WETGROUND = 1;
    static const int FLOAT_MUDDYPUDDLES = 2;
    static const int FLOAT_PUDDLESSIZE = 3;
    static const int FLOAT_RAININTENSITY = 4;
    static const int FLOAT_MAX = 5;
    PuddlesFloat rain;
    PuddlesFloat wetGround;
    PuddlesFloat muddyPuddles;
    PuddlesFloat puddlesSize;
    PuddlesFloat rainIntensity;
   private const PuddlesFloat[] climateFloats = new PuddlesFloat[5];

   public static /* synchronized - TODO: add std::mutex */ IsoPuddles getInstance() {
      if (instance == nullptr) {
         instance = std::make_unique<IsoPuddles>();
      }

    return instance;
   }

    bool getShaderEnable() {
    return isShaderEnable;
   }

    public IsoPuddles() {
      if (GameServer.bServer) {
         Core.getInstance().setPerfPuddles(3);
         this.applyPuddlesQuality();
         this.PuddlesParamWindINT = std::make_shared<Vector2f>(0.0F);
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
         this.PuddlesParamWindINT = std::make_shared<Vector2f>(0.0F);

         for (int var1 = 0; var1 < this.renderData.length; var1++) {
            for (int var2 = 0; var2 < 4; var2++) {
               this.renderData[var1][var2] = std::make_unique<RenderData>();
            }
         }

         this.setup();
      }
   }

    void applyPuddlesQuality() {
      leakingPuddlesInTheRoom = Core.getInstance().getPerfPuddles() == 0;
      if (Core.getInstance().getPerfPuddles() == 3) {
         isShaderEnable = false;
      } else {
         isShaderEnable = true;
         if (PerformanceSettings.PuddlesQuality == 2) {
            RenderThread.invokeOnRenderContext(() -> {
               this.Effect = std::make_shared<PuddlesShader>("puddles_lq");
               this.Effect.Start();
               this.Effect.End();
            });
         }

         if (PerformanceSettings.PuddlesQuality == 1) {
            RenderThread.invokeOnRenderContext(() -> {
               this.Effect = std::make_shared<PuddlesShader>("puddles_mq");
               this.Effect.Start();
               this.Effect.End();
            });
         }

         if (PerformanceSettings.PuddlesQuality == 0) {
            RenderThread.invokeOnRenderContext(() -> {
               this.Effect = std::make_shared<PuddlesShader>("puddles_hq");
               this.Effect.Start();
               this.Effect.End();
            });
         }
      }
   }

    Vector4f getShaderOffset() {
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

    Vector4f getShaderOffsetMain() {
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

    void render(std::vector<IsoGridSquare> var1, int var2) {
      if (DebugOptions.instance.Weather.WaterPuddles.getValue()) {
    int var3 = SpriteRenderer.instance.getMainStateIndex();
    int var4 = IsoCamera.frameState.playerIndex;
    RenderData var5 = this.renderData[var3][var4];
         if (var2 == 0) {
            var5.clear();
         }

         if (!var1.empty()) {
            if (this.getShaderEnable()) {
               if (Core.getInstance().getUseShaders()) {
                  if (Core.getInstance().getPerfPuddles() != 3) {
                     if (var2 <= 0 || Core.getInstance().getPerfPuddles() <= 0) {
                        if (this.wetGround.getFinalValue() != 0.0 || this.puddlesSize.getFinalValue() != 0.0) {
                           for (int var6 = 0; var6 < var1.size(); var6++) {
    IsoPuddlesGeometry var7 = ((IsoGridSquare)var1.get(var6)).getPuddles();
                              if (var7 != nullptr && var7.shouldRender()) {
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

    void puddlesProjection() {
    int var1 = SpriteRenderer.instance.getRenderingPlayerIndex();
    PlayerCamera var2 = SpriteRenderer.instance.getRenderingPlayerCamera(var1);
      GL11.glOrtho(var2.getOffX(), var2.getOffX() + var2.OffscreenWidth, var2.getOffY() + var2.OffscreenHeight, var2.getOffY(), -1.0, 1.0);
   }

    void puddlesGeometry(int var1) {
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

    int renderSome(int var1, int var2) {
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
    uint8_t var9 = 0;
    uint8_t var10 = 0;

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
    uint8_t var15 = 0;
    uint8_t var13 = 0;
      GL12.glDrawRangeElements(4, var15, var15 + var9, var10 - var13, 5123, var13 * 2);
      return var8 / 4;
   }

    void update(ClimateManager var1) {
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
         .push_back(
            (float)Math.sin(this.PuddlesWindAngle * 6.0F) * this.PuddlesWindIntensity * 0.05F,
            (float)Math.cos(this.PuddlesWindAngle * 6.0F) * this.PuddlesWindIntensity * 0.05F
         );
   }

    float getShaderTime() {
      return this.PuddlesTime;
   }

    float getPuddlesSize() {
      return this.puddlesSize.getFinalValue();
   }

    ITexture getHMTexture() {
      return this.texHM;
   }

    FloatBuffer getPuddlesParams(int var1) {
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

    float getRainIntensity() {
      return this.rainIntensity.getFinalValue();
   }

    int getFloatMax() {
    return 5;
   }

    int getBoolMax() {
    return 0;
   }

    PuddlesFloat getPuddlesFloat(int var1) {
      if (var1 >= 0 && var1 < 5) {
         return this.climateFloats[var1];
      } else {
         DebugLog.log("ERROR: Climate: cannot get float override id.");
    return nullptr;
      }
   }

    PuddlesFloat initClimateFloat(int var1, const std::string& var2) {
      if (var1 >= 0 && var1 < 5) {
         return this.climateFloats[var1].init(var1, var2);
      } else {
         DebugLog.log("ERROR: Climate: cannot get float override id.");
    return nullptr;
      }
   }

    void setup() {
      for (int var1 = 0; var1 < this.climateFloats.length; var1++) {
         this.climateFloats[var1] = std::make_unique<PuddlesFloat>();
      }

      this.rain = this.initClimateFloat(0, "INPUT: RAIN");
      this.wetGround = this.initClimateFloat(1, "Wet Ground");
      this.muddyPuddles = this.initClimateFloat(2, "Muddy Puddles");
      this.puddlesSize = this.initClimateFloat(3, "Puddles Size");
      this.rainIntensity = this.initClimateFloat(4, "Rain Intensity");
   }
}
} // namespace iso
} // namespace zombie
