#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/joml/Vector2f.h"
#include "org/joml/Vector4f.h"
#include <GL/glew.h>
#include <GL/glew.h>
#include <GL/glew.h>
#include "zombie/GameTime.h"
#include "zombie/core/PerformanceSettings.h"
#include "zombie/core/SpriteRenderer.h"
#include "zombie/core/opengl/RenderThread.h"
#include "zombie/core/opengl/Shader.h"
#include "zombie/core/textures/Texture.h"
#include "zombie/interfaces/ITexture.h"
#include "zombie/iso/IsoWater/RenderData.h"
#include "zombie/iso/weather/ClimateManager.h"
#include <filesystem>

namespace zombie {
namespace iso {


class IsoWater {
public:
    Shader Effect;
    float WaterTime;
    float WaterWindAngle;
    float WaterWindIntensity;
    float WaterRainIntensity;
    Vector2f WaterParamWindINT;
    Texture texBottom;
    int apiId;
    static IsoWater instance;
    static bool isShaderEnable = false;
   private const RenderData[][] renderData = new RenderData[3][4];
   private const RenderData[][] renderDataShore = new RenderData[3][4];
    static const int BYTES_PER_FLOAT = 4;
    static const int FLOATS_PER_VERTEX = 7;
    static const int BYTES_PER_VERTEX = 28;
    static const int VERTICES_PER_SQUARE = 4;
    const Vector4f shaderOffset = std::make_shared<Vector4f>();

   public static /* synchronized - TODO: add std::mutex */ IsoWater getInstance() {
      if (instance == nullptr) {
         instance = std::make_unique<IsoWater>();
      }

    return instance;
   }

    bool getShaderEnable() {
    return isShaderEnable;
   }

    public IsoWater() {
      this.texBottom = Texture.getSharedTexture("media/textures/river_bottom.png");
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

      for (int var1 = 0; var1 < this.renderData.length; var1++) {
         for (int var2 = 0; var2 < 4; var2++) {
            this.renderData[var1][var2] = std::make_unique<RenderData>();
            this.renderDataShore[var1][var2] = std::make_unique<RenderData>();
         }
      }

      this.applyWaterQuality();
      this.WaterParamWindINT = std::make_shared<Vector2f>(0.0F);
   }

    void applyWaterQuality() {
      if (PerformanceSettings.WaterQuality == 2) {
         isShaderEnable = false;
      }

      if (PerformanceSettings.WaterQuality == 1) {
         isShaderEnable = true;
         RenderThread.invokeOnRenderContext(() -> {
            ARBShaderObjects.glUseProgramObjectARB(0);
            this.Effect = std::make_shared<WaterShader>("water");
            ARBShaderObjects.glUseProgramObjectARB(0);
         });
      }

      if (PerformanceSettings.WaterQuality == 0) {
         isShaderEnable = true;
         RenderThread.invokeOnRenderContext(() -> {
            this.Effect = std::make_shared<WaterShader>("water_hq");
            this.Effect.Start();
            this.Effect.End();
         });
      }
   }

    void render(std::vector<IsoGridSquare> var1, bool var2) {
      if (this.getShaderEnable()) {
    int var3 = IsoCamera.frameState.playerIndex;
    int var4 = SpriteRenderer.instance.getMainStateIndex();
    RenderData var5 = this.renderData[var4][var3];
    RenderData var6 = this.renderDataShore[var4][var3];
         if (var2) {
            if (var6.numSquares > 0) {
               SpriteRenderer.instance.drawWater(this.Effect, var3, this.apiId, true);
            }
         } else {
            var5.clear();
            var6.clear();

            for (int var7 = 0; var7 < var1.size(); var7++) {
    IsoGridSquare var8 = (IsoGridSquare)var1.get(var7);
               if (var8.chunk == nullptr || !var8.chunk.bLightingNeverDone[var3]) {
    IsoWaterGeometry var9 = var8.getWater();
                  if (var9 != nullptr) {
                     if (var9.bShore) {
                        var6.addSquare(var9);
                     } else if (var9.hasWater) {
                        var5.addSquare(var9);
                     }
                  }
               }
            }

            if (var5.numSquares != 0) {
               SpriteRenderer.instance.drawWater(this.Effect, var3, this.apiId, false);
            }
         }
      }
   }

    void waterProjection() {
    int var1 = SpriteRenderer.instance.getRenderingPlayerIndex();
    PlayerCamera var2 = SpriteRenderer.instance.getRenderingPlayerCamera(var1);
      GL11.glOrtho(var2.getOffX(), var2.getOffX() + var2.OffscreenWidth, var2.getOffY() + var2.OffscreenHeight, var2.getOffY(), -1.0, 1.0);
   }

    void waterGeometry(bool var1) {
    long var2 = System.nanoTime();
    int var4 = SpriteRenderer.instance.getRenderStateIndex();
    int var5 = SpriteRenderer.instance.getRenderingPlayerIndex();
    RenderData var6 = var1 ? this.renderDataShore[var4][var5] : this.renderData[var4][var5];
    int var7 = 0;
    int var8 = var6.numSquares;

      while (var8 > 0) {
    int var9 = this.renderSome(var7, var8, var1);
         var7 += var9;
         var8 -= var9;
      }

    long var11 = System.nanoTime();
      SpriteRenderer.ringBuffer.restoreVBOs = true;
   }

    int renderSome(int var1, int var2, bool var3) {
      IsoPuddles.VBOs.next();
    FloatBuffer var4 = IsoPuddles.VBOs.vertices;
    ShortBuffer var5 = IsoPuddles.VBOs.indices;
      GL13.glActiveTexture(33985);
      GL13.glClientActiveTexture(33985);
      GL11.glTexCoordPointer(2, 5126, 28, 8L);
      GL11.glEnableClientState(32888);
      GL13.glActiveTexture(33984);
      GL13.glClientActiveTexture(33984);
      GL11.glTexCoordPointer(2, 5126, 28, 0L);
      GL11.glColorPointer(4, 5121, 28, 24L);
      GL11.glVertexPointer(2, 5126, 28, 16L);
    int var6 = SpriteRenderer.instance.getRenderStateIndex();
    int var7 = SpriteRenderer.instance.getRenderingPlayerIndex();
    RenderData var8 = var3 ? this.renderDataShore[var6][var7] : this.renderData[var6][var7];
    int var9 = Math.min(var2 * 4, IsoPuddles.VBOs.bufferSizeVertices);
      var4.put(var8.data, var1 * 4 * 7, var9 * 7);
    uint8_t var10 = 0;
    uint8_t var11 = 0;

      for (int var12 = 0; var12 < var9 / 4; var12++) {
         var5.put(var10);
         var5.put((short)(var10 + 1));
         var5.put((short)(var10 + 2));
         var5.put(var10);
         var5.put((short)(var10 + 2));
         var5.put((short)(var10 + 3));
         var10 += 4;
         var11 += 6;
      }

      IsoPuddles.VBOs.unmap();
    uint8_t var16 = 0;
    uint8_t var14 = 0;
      GL12.glDrawRangeElements(4, var16, var16 + var10, var11 - var14, 5123, var14 * 2);
      return var9 / 4;
   }

    ITexture getTextureBottom() {
      return this.texBottom;
   }

    float getShaderTime() {
      return this.WaterTime;
   }

    float getRainIntensity() {
      return this.WaterRainIntensity;
   }

    void update(ClimateManager var1) {
      this.WaterWindAngle = var1.getCorrectedWindAngleIntensity();
      this.WaterWindIntensity = var1.getWindIntensity() * 5.0F;
      this.WaterRainIntensity = var1.getRainIntensity();
    float var2 = GameTime.getInstance().getMultiplier();
      this.WaterTime += 0.0166F * var2;
      this.WaterParamWindINT
         .push_back(
            (float)Math.sin(this.WaterWindAngle * 6.0F) * this.WaterWindIntensity * 0.05F * (var2 / 1.6F),
            (float)Math.cos(this.WaterWindAngle * 6.0F) * this.WaterWindIntensity * 0.15F * (var2 / 1.6F)
         );
   }

    float getWaterWindX() {
      return this.WaterParamWindINT.x;
   }

    float getWaterWindY() {
      return this.WaterParamWindINT.y;
   }

    float getWaterWindSpeed() {
      return this.WaterWindIntensity * 2.0F;
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

    void FBOStart() {
    int var1 = IsoCamera.frameState.playerIndex;
   }

    void FBOEnd() {
    int var1 = IsoCamera.frameState.playerIndex;
   }
}
} // namespace iso
} // namespace zombie
