#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/joml/Vector3f.h"
#include "zombie/GameTime.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/skinnedmodel/model/ModelInstance/EffectLight.h"
#include "zombie/core/skinnedmodel/model/ModelInstance/FrameLightBlendStatus.h"
#include "zombie/core/skinnedmodel/model/ModelInstance/FrameLightInfo.h"
#include "zombie/core/textures/ColorInfo.h"
#include "zombie/iso/IsoCamera.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoGridSquare/ILighting.h"
#include "zombie/iso/IsoGridSquare/ResultLight.h"
#include "zombie/iso/IsoUtils.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/weather/ClimateManager.h"
#include "zombie/network/GameClient.h"
#include "zombie/popman/ObjectPool.h"
#include <algorithm>

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace model {


class ModelInstance {
public:
   FrameLightInfo[] frameLights;
   std::vector<ResultLight> chosenLights;
    Vector3f targetAmbient;
    Vector3f currentAmbient;
   EffectLight[] effectLightsMain;
   private static const ObjectPool<ModelInstance$PlayerData> pool = std::make_shared<ObjectPool>(ModelInstance$PlayerData::new);

    void registerFrameLight(ResultLight var1) {
      this.chosenLights.push_back(var1);
   }

    void initFrameLightsForFrame() {
      if (this.frameLights == nullptr) {
         this.effectLightsMain = new EffectLight[5];

         for (int var1 = 0; var1 < 5; var1++) {
            this.effectLightsMain[var1] = std::make_unique<EffectLight>();
         }

         this.frameLights = new FrameLightInfo[5];
         this.chosenLights = std::make_unique<std::vector<>>();
         this.targetAmbient = std::make_unique<Vector3f>();
         this.currentAmbient = std::make_unique<Vector3f>();
      }

      for (EffectLight var4 : this.effectLightsMain) {
         var4.radius = -1;
      }

      this.chosenLights.clear();
   }

    void completeFrameLightsForFrame() {
      for (int var1 = 0; var1 < 5; var1++) {
         if (this.frameLights[var1] != nullptr) {
            this.frameLights[var1].foundThisFrame = false;
         }
      }

      for (int var6 = 0; var6 < this.chosenLights.size(); var6++) {
    ResultLight var2 = this.chosenLights.get(var6);
    bool var3 = false;
    int var4 = 0;

         for (int var5 = 0; var5 < 5; var5++) {
            if (this.frameLights[var5] != nullptr
               && this.frameLights[var5].active
               && (
                  var2.id != -1
                     ? var2.id == this.frameLights[var5].id
                     : this.frameLights[var5].x == var2.x && this.frameLights[var5].y == var2.y && this.frameLights[var5].z == var2.z
               )) {
               var3 = true;
               var4 = var5;
               break;
            }
         }

         if (var3) {
            this.frameLights[var4].foundThisFrame = true;
            this.frameLights[var4].x = var2.x;
            this.frameLights[var4].y = var2.y;
            this.frameLights[var4].z = var2.z;
            this.frameLights[var4].flags = var2.flags;
            this.frameLights[var4].radius = var2.radius;
            this.frameLights[var4].targetColor.x = var2.r;
            this.frameLights[var4].targetColor.y = var2.g;
            this.frameLights[var4].targetColor.z = var2.b;
            this.frameLights[var4].Stage = FrameLightBlendStatus.In;
         } else {
            for (int var10 = 0; var10 < 5; var10++) {
               if (this.frameLights[var10] == nullptr || !this.frameLights[var10].active) {
                  if (this.frameLights[var10] == nullptr) {
                     this.frameLights[var10] = std::make_unique<FrameLightInfo>();
                  }

                  this.frameLights[var10].x = var2.x;
                  this.frameLights[var10].y = var2.y;
                  this.frameLights[var10].z = var2.z;
                  this.frameLights[var10].r = var2.r;
                  this.frameLights[var10].g = var2.g;
                  this.frameLights[var10].b = var2.b;
                  this.frameLights[var10].flags = var2.flags;
                  this.frameLights[var10].radius = var2.radius;
                  this.frameLights[var10].id = var2.id;
                  this.frameLights[var10].currentColor.x = 0.0F;
                  this.frameLights[var10].currentColor.y = 0.0F;
                  this.frameLights[var10].currentColor.z = 0.0F;
                  this.frameLights[var10].targetColor.x = var2.r;
                  this.frameLights[var10].targetColor.y = var2.g;
                  this.frameLights[var10].targetColor.z = var2.b;
                  this.frameLights[var10].Stage = FrameLightBlendStatus.In;
                  this.frameLights[var10].active = true;
                  this.frameLights[var10].foundThisFrame = true;
                  break;
               }
            }
         }
      }

    float var7 = GameTime.getInstance().getMultiplier();

      for (int var8 = 0; var8 < 5; var8++) {
    FrameLightInfo var9 = this.frameLights[var8];
         if (var9 != nullptr && var9.active) {
            if (!var9.foundThisFrame) {
               var9.targetColor.x = 0.0F;
               var9.targetColor.y = 0.0F;
               var9.targetColor.z = 0.0F;
               var9.Stage = FrameLightBlendStatus.Out;
            }

            var9.currentColor.x = this.step(var9.currentColor.x, var9.targetColor.x, Math.signum(var9.targetColor.x - var9.currentColor.x) / (60.0F * var7));
            var9.currentColor.y = this.step(var9.currentColor.y, var9.targetColor.y, Math.signum(var9.targetColor.y - var9.currentColor.y) / (60.0F * var7));
            var9.currentColor.z = this.step(var9.currentColor.z, var9.targetColor.z, Math.signum(var9.targetColor.z - var9.currentColor.z) / (60.0F * var7));
            if (var9.Stage == FrameLightBlendStatus.Out && var9.currentColor.x < 0.01F && var9.currentColor.y < 0.01F && var9.currentColor.z < 0.01F) {
               var9.active = false;
            }
         }
      }
   }

    void sortLights(IsoGameCharacter var1) {
      for (int var2 = 0; var2 < this.frameLights.length; var2++) {
    FrameLightInfo var3 = this.frameLights[var2];
         if (var3 != nullptr) {
            if (!var3.active) {
               var3.distSq = float.MAX_VALUE;
            } else {
               var3.distSq = IsoUtils.DistanceToSquared(var1.x, var1.y, var1.z, var3.x + 0.5F, var3.y + 0.5F, var3.z);
            }
         }
      }

      Arrays.sort(this.frameLights, (var0, var1x) -> {
    bool var2x = var0 == nullptr || var0.radius == -1 || !var0.active;
    bool var3x = var1x == nullptr || var1x.radius == -1 || !var1x.active;
         if (var2x && var3x) {
    return 0;
         } else if (var2x) {
    return 1;
         } else if (var3x) {
            return -1;
         } else if (var0.Stage.ordinal() < var1x.Stage.ordinal()) {
            return -1;
         } else {
            return var0.Stage.ordinal() > var1x.Stage.ordinal() ? 1 : (int)Math.signum(var0.distSq - var1x.distSq);
         }
      });
   }

    void updateLights(IsoGameCharacter var1, bool var2) {
      this.initFrameLightsForFrame();
      if (var1 != nullptr) {
         if (var1.getCurrentSquare() != nullptr) {
    ILighting var3 = var1.getCurrentSquare().lighting[IsoCamera.frameState.playerIndex];
    int var4 = org.joml.Math.min(var3.resultLightCount(), 4);

            for (int var5 = 0; var5 < var4; var5++) {
    ResultLight var6 = var3.getResultLight(var5);
               this.registerFrameLight(var6);
            }

            if (var2) {
               for (int var14 = 0; var14 < this.frameLights.length; var14++) {
                  if (this.frameLights[var14] != nullptr) {
                     this.frameLights[var14].active = false;
                  }
               }
            }

            this.completeFrameLightsForFrame();
            var1.getCurrentSquare().interpolateLight(ModelInstance.tempColorInfo, var1.x % 1.0F, var1.y % 1.0F);
            this.targetAmbient.x = ModelInstance.tempColorInfo.r;
            this.targetAmbient.y = ModelInstance.tempColorInfo.g;
            this.targetAmbient.z = ModelInstance.tempColorInfo.b;
            if (var1.z - (int)var1.z > 0.2F) {
    IsoGridSquare var15 = IsoWorld.instance.CurrentCell.getGridSquare((int)var1.x, (int)var1.y, (int)var1.z + 1);
               if (var15 != nullptr) {
    ColorInfo var17 = ModelInstance.tempColorInfo2;
                  var15.lighting[IsoCamera.frameState.playerIndex].lightInfo();
                  var15.interpolateLight(var17, var1.x % 1.0F, var1.y % 1.0F);
                  ModelInstance.tempColorInfo.interp(var17, (var1.z - ((int)var1.z + 0.2F)) / 0.8F, ModelInstance.tempColorInfo);
                  this.targetAmbient.set(ModelInstance.tempColorInfo.r, ModelInstance.tempColorInfo.g, ModelInstance.tempColorInfo.b);
               }
            }

    float var16 = GameTime.getInstance().getMultiplier();
            this.currentAmbient.x = this.step(this.currentAmbient.x, this.targetAmbient.x, (this.targetAmbient.x - this.currentAmbient.x) / (10.0F * var16));
            this.currentAmbient.y = this.step(this.currentAmbient.y, this.targetAmbient.y, (this.targetAmbient.y - this.currentAmbient.y) / (10.0F * var16));
            this.currentAmbient.z = this.step(this.currentAmbient.z, this.targetAmbient.z, (this.targetAmbient.z - this.currentAmbient.z) / (10.0F * var16));
            if (var2) {
               this.setCurrentToTarget();
            }

            this.sortLights(var1);
    float var18 = 0.7F;

            for (int var7 = 0; var7 < 5; var7++) {
    FrameLightInfo var8 = this.frameLights[var7];
               if (var8 != nullptr && var8.active) {
    EffectLight var9 = this.effectLightsMain[var7];
                  if ((var8.flags & 1) != 0) {
                     var9.set(
                        var1.x, var1.y, (int)var1.z + 1, var8.currentColor.x * var18, var8.currentColor.y * var18, var8.currentColor.z * var18, var8.radius
                     );
                  } else if ((var8.flags & 2) != 0) {
                     if (dynamic_cast<IsoPlayer*>(var1) != nullptr) {
                        if (GameClient.bClient) {
    int var10000 = ((IsoPlayer)var1).OnlineID + 1;
                        } else {
    int var29 = ((IsoPlayer)var1).PlayerIndex + 1;
                        }

    int var11 = ((IsoPlayer)var1).PlayerIndex;
    int var12 = var11 * 4 + 1;
    int var13 = var11 * 4 + 3 + 1;
                        if (var8.id < var12 || var8.id > var13) {
                           var9.set(var8.x, var8.y, var8.z, var8.currentColor.x, var8.currentColor.y, var8.currentColor.z, var8.radius);
                        }
                     } else {
                        var9.set(var8.x, var8.y, var8.z, var8.currentColor.x * 2.0F, var8.currentColor.y, var8.currentColor.z, var8.radius);
                     }
                  } else {
                     var9.set(
                        var8.x + 0.5F,
                        var8.y + 0.5F,
                        var8.z + 0.5F,
                        var8.currentColor.x * var18,
                        var8.currentColor.y * var18,
                        var8.currentColor.z * var18,
                        var8.radius
                     );
                  }
               }
            }

            if (var4 <= 3 && dynamic_cast<IsoPlayer*>(var1) != nullptr && var1.getTorchStrength() > 0.0F) {
               this.effectLightsMain[2]
                  .set(var1.x + var1.getForwardDirection().x * 0.5F, var1.y + var1.getForwardDirection().y * 0.5F, var1.z + 0.25F, 1.0F, 1.0F, 1.0F, 2);
            }

    float var19 = 0.0F;
    float var20 = 1.0F;
    float var21 = this.lerp(var19, var20, this.currentAmbient.x);
    float var10 = this.lerp(var19, var20, this.currentAmbient.y);
    float var26 = this.lerp(var19, var20, this.currentAmbient.z);
            if (var1.getCurrentSquare().isOutside()) {
               var21 *= ModelInstance.MODEL_LIGHT_MULT_OUTSIDE;
               var10 *= ModelInstance.MODEL_LIGHT_MULT_OUTSIDE;
               var26 *= ModelInstance.MODEL_LIGHT_MULT_OUTSIDE;
               this.effectLightsMain[3].set(var1.x - 2.0F, var1.y - 2.0F, var1.z + 1.0F, var21 / 4.0F, var10 / 4.0F, var26 / 4.0F, 5000);
               this.effectLightsMain[4].set(var1.x + 2.0F, var1.y + 2.0F, var1.z + 1.0F, var21 / 4.0F, var10 / 4.0F, var26 / 4.0F, 5000);
            } else if (var1.getCurrentSquare().getRoom() != nullptr) {
               var21 *= ModelInstance.MODEL_LIGHT_MULT_ROOM;
               var10 *= ModelInstance.MODEL_LIGHT_MULT_ROOM;
               var26 *= ModelInstance.MODEL_LIGHT_MULT_ROOM;
               this.effectLightsMain[3].set(var1.x - 2.0F, var1.y - 2.0F, var1.z + 1.0F, var21 / 4.0F, var10 / 4.0F, var26 / 4.0F, 5000);
               this.effectLightsMain[4].set(var1.x + 2.0F, var1.y + 2.0F, var1.z + 1.0F, var21 / 4.0F, var10 / 4.0F, var26 / 4.0F, 5000);
            }
         }
      }
   }

    float lerp(float var1, float var2, float var3) {
      return var1 + (var2 - var1) * var3;
   }

    void setCurrentToTarget() {
      for (int var1 = 0; var1 < this.frameLights.length; var1++) {
    FrameLightInfo var2 = this.frameLights[var1];
         if (var2 != nullptr) {
            var2.currentColor.set(var2.targetColor);
         }
      }

      this.currentAmbient.set(this.targetAmbient);
   }

    float step(float var1, float var2, float var3) {
      if (var1 < var2) {
         return ClimateManager.clamp(0.0F, var2, var1 + var3);
      } else {
         return var1 > var2 ? ClimateManager.clamp(var2, 1.0F, var1 + var3) : var1;
      }
   }
}
} // namespace model
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
