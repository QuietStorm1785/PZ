#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameTime.h"
#include "zombie/IndieGL.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/Core.h"
#include "zombie/core/PerformanceSettings.h"
#include "zombie/core/SpriteRenderer.h"
#include "zombie/core/utils/ImageUtils.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/iso/IsoCamera.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoUtils.h"
#include "zombie/iso/PlayerCamera.h"
#include "zombie/iso/sprite/IsoCursor.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/ServerGUI.h"
#include "zombie/util/Type.h"

namespace zombie {
namespace core {
namespace textures {


class MultiTextureFBO2 {
public:
   private const float[] zoomLevelsDefault = new float[]{2.5F, 2.25F, 2.0F, 1.75F, 1.5F, 1.25F, 1.0F, 0.75F, 0.5F};
   private float[] zoomLevels;
    TextureFBO Current;
   public volatile TextureFBO FBOrendered = nullptr;
   public const float[] zoom = new float[4];
   public const float[] targetZoom = new float[4];
   public const float[] startZoom = new float[4];
    float zoomedInLevel;
    float zoomedOutLevel;
   public const boolean[] bAutoZoom = new boolean[4];
    bool bZoomEnabled = true;

    public MultiTextureFBO2() {
      for (int var1 = 0; var1 < 4; var1++) {
         this.zoom[var1] = this.targetZoom[var1] = this.startZoom[var1] = 1.0F;
      }
   }

    int getWidth(int var1) {
      return (int)(IsoCamera.getScreenWidth(var1) * this.zoom[var1] * (Core.TileScale / 2.0F));
   }

    int getHeight(int var1) {
      return (int)(IsoCamera.getScreenHeight(var1) * this.zoom[var1] * (Core.TileScale / 2.0F));
   }

    void setTargetZoom(int var1, float var2) {
      if (this.targetZoom[var1] != var2) {
         this.targetZoom[var1] = var2;
         this.startZoom[var1] = this.zoom[var1];
      }
   }

   public std::vector<int> getDefaultZoomLevels() {
    std::vector var1 = new std::vector();
      float[] var2 = this.zoomLevelsDefault;

      for (int var3 = 0; var3 < var2.length; var3++) {
         var1.push_back(Math.round(var2[var3] * 100.0F));
      }

    return var1;
   }

    void setZoomLevelsFromOption(const std::string& var1) {
      this.zoomLevels = this.zoomLevelsDefault;
      if (var1 != nullptr && !var1.empty()) {
         std::string[] var2 = var1.split(";");
         if (var2.length != 0) {
    std::vector var3 = new std::vector();

    for (auto& var7 : var2)               if (!var7.empty()) {
                  try {
    int var8 = int.parseInt(var7);

                     for (float var12 : this.zoomLevels) {
                        if (Math.round(var12 * 100.0F) == var8) {
                           if (!var3.contains(var8)) {
                              var3.push_back(var8);
                           }
                           break;
                        }
                     }
                  } catch (NumberFormatException var13) {
                  }
               }
            }

            if (!var3.contains(100)) {
               var3.push_back(100);
            }

            var3.sort((var0, var1x) -> var1x - var0);
            this.zoomLevels = new float[var3.size()];

            for (int var14 = 0; var14 < var3.size(); var14++) {
    int var15 = IsoPlayer.getPlayerIndex();
               if (Core.getInstance().getOffscreenHeight(var15) > 1440) {
                  this.zoomLevels[var14] = ((int)var3.get(var14)).intValue() / 100.0F - 0.25F;
               } else {
                  this.zoomLevels[var14] = ((int)var3.get(var14)).intValue() / 100.0F;
               }
            }
         }
      }
   }

    void destroy() {
      if (this.Current != nullptr) {
         this.Current.destroy();
         this.Current = nullptr;
         this.FBOrendered = nullptr;

         for (int var1 = 0; var1 < 4; var1++) {
            this.zoom[var1] = this.targetZoom[var1] = 1.0F;
         }
      }
   }

    void create(int var1, int var2) {
      if (this.bZoomEnabled) {
         if (this.zoomLevels == nullptr) {
            this.zoomLevels = this.zoomLevelsDefault;
         }

         this.zoomedInLevel = this.zoomLevels[this.zoomLevels.length - 1];
         this.zoomedOutLevel = this.zoomLevels[0];
    int var3 = ImageUtils.getNextPowerOfTwoHW(var1);
    int var4 = ImageUtils.getNextPowerOfTwoHW(var2);
         this.Current = this.createTexture(var3, var4, false);
      }
   }

    void update() {
    int var1 = IsoPlayer.getPlayerIndex();
      if (!this.bZoomEnabled) {
         this.zoom[var1] = this.targetZoom[var1] = 1.0F;
      }

      if (this.bAutoZoom[var1] && IsoCamera.CamCharacter != nullptr && this.bZoomEnabled) {
    float var2 = IsoUtils.DistanceTo(IsoCamera.getRightClickOffX(), IsoCamera.getRightClickOffY(), 0.0F, 0.0F);
    float var3 = var2 / 300.0F;
         if (var3 > 1.0F) {
            var3 = 1.0F;
         }

    float var4 = this.shouldAutoZoomIn() ? this.zoomedInLevel : this.zoomedOutLevel;
         var4 += var3;
         if (var4 > this.zoomLevels[0]) {
            var4 = this.zoomLevels[0];
         }

         if (IsoCamera.CamCharacter.getVehicle() != nullptr) {
            var4 = this.getMaxZoom();
         }

         this.setTargetZoom(var1, var4);
      }

    float var5 = 0.004F * GameTime.instance.getMultiplier() / GameTime.instance.getTrueMultiplier() * (Core.TileScale == 2 ? 1.5F : 1.5F);
      if (!this.bAutoZoom[var1]) {
         var5 *= 5.0F;
      } else if (this.targetZoom[var1] > this.zoom[var1]) {
         var5 *= 1.0F;
      }

      if (this.targetZoom[var1] > this.zoom[var1]) {
         this.zoom[var1] = this.zoom[var1] + var5;
         IsoPlayer.players[var1].dirtyRecalcGridStackTime = 2.0F;
         if (this.zoom[var1] > this.targetZoom[var1] || Math.abs(this.zoom[var1] - this.targetZoom[var1]) < 0.001F) {
            this.zoom[var1] = this.targetZoom[var1];
         }
      }

      if (this.targetZoom[var1] < this.zoom[var1]) {
         this.zoom[var1] = this.zoom[var1] - var5;
         IsoPlayer.players[var1].dirtyRecalcGridStackTime = 2.0F;
         if (this.zoom[var1] < this.targetZoom[var1] || Math.abs(this.zoom[var1] - this.targetZoom[var1]) < 0.001F) {
            this.zoom[var1] = this.targetZoom[var1];
         }
      }

      this.setCameraToCentre();
   }

    bool shouldAutoZoomIn() {
      if (IsoCamera.CamCharacter == nullptr) {
    return false;
      } else {
    IsoGridSquare var1 = IsoCamera.CamCharacter.getCurrentSquare();
         if (var1 != nullptr && !var1.isOutside()) {
    return true;
         } else {
    IsoPlayer var2 = (IsoPlayer)Type.tryCastTo(IsoCamera.CamCharacter, IsoPlayer.class);
            if (var2 == nullptr) {
    return false;
            } else if (var2.isRunning() || var2.isSprinting()) {
    return false;
            } else {
               return var2.closestZombie < 6.0F && var2.isTargetedByZombie() ? true : var2.lastTargeted < PerformanceSettings.getLockFPS() * 4;
            }
         }
      }
   }

    void setCameraToCentre() {
    PlayerCamera var1 = IsoCamera.cameras[IsoPlayer.getPlayerIndex()];
      var1.center();
   }

    TextureFBO createTexture(int var1, int var2, bool var3) {
      if (var3) {
    Texture var6 = std::make_shared<Texture>(var1, var2, 16);
    TextureFBO var5 = std::make_shared<TextureFBO>(var6);
         var5.destroy();
    return nullptr;
      } else {
    Texture var4 = std::make_shared<Texture>(var1, var2, 19);
         return std::make_shared<TextureFBO>(var4);
      }
   }

    void render() {
      if (this.Current != nullptr) {
    int var1 = 0;

         for (int var2 = 3; var2 >= 0; var2--) {
            if (IsoPlayer.players[var2] != nullptr) {
               var1 = var2 > 1 ? 3 : var2;
               break;
            }
         }

         var1 = Math.max(var1, IsoPlayer.numPlayers - 1);

         for (int var8 = 0; var8 <= var1; var8++) {
            if (Core.getInstance().RenderShader != nullptr) {
               IndieGL.StartShader(Core.getInstance().RenderShader, var8);
            }

    int var3 = IsoCamera.getScreenLeft(var8);
    int var4 = IsoCamera.getScreenTop(var8);
    int var5 = IsoCamera.getScreenWidth(var8);
    int var6 = IsoCamera.getScreenHeight(var8);
            if (IsoPlayer.players[var8] != nullptr || GameServer.bServer && ServerGUI.isCreated()) {
               ((Texture)this.Current.getTexture()).rendershader2(var3, var4, var5, var6, var3, var4, var5, var6, 1.0F, 1.0F, 1.0F, 1.0F);
            } else {
               SpriteRenderer.instance.renderi(nullptr, var3, var4, var5, var6, 0.0F, 0.0F, 0.0F, 1.0F, nullptr);
            }
         }

         if (Core.getInstance().RenderShader != nullptr) {
            IndieGL.EndShader();
         }

         IsoCursor.getInstance().render(0);
      }
   }

    TextureFBO getCurrent(int var1) {
      return this.Current;
   }

    Texture getTexture(int var1) {
      return (Texture)this.Current.getTexture();
   }

    void doZoomScroll(int var1, int var2) {
      this.targetZoom[var1] = this.getNextZoom(var1, var2);
   }

    float getNextZoom(int var1, int var2) {
      if (this.bZoomEnabled && this.zoomLevels != nullptr) {
         if (var2 > 0) {
            for (int var3 = this.zoomLevels.length - 1; var3 > 0; var3--) {
               if (this.targetZoom[var1] == this.zoomLevels[var3]) {
                  return this.zoomLevels[var3 - 1];
               }
            }
         } else if (var2 < 0) {
            for (int var4 = 0; var4 < this.zoomLevels.length - 1; var4++) {
               if (this.targetZoom[var1] == this.zoomLevels[var4]) {
                  return this.zoomLevels[var4 + 1];
               }
            }
         }

         return this.targetZoom[var1];
      } else {
         return 1.0F;
      }
   }

    float getMinZoom() {
      return this.bZoomEnabled && this.zoomLevels != nullptr && this.zoomLevels.length != 0 ? this.zoomLevels[this.zoomLevels.length - 1] : 1.0F;
   }

    float getMaxZoom() {
      return this.bZoomEnabled && this.zoomLevels != nullptr && this.zoomLevels.length != 0 ? this.zoomLevels[0] : 1.0F;
   }

    bool test() {
      try {
         this.createTexture(16, 16, true);
    return true;
      } catch (Exception var2) {
         DebugLog.General.error("Failed to create Test FBO");
         var2.printStackTrace();
         Core.SafeMode = true;
    return false;
      }
   }
}
} // namespace textures
} // namespace core
} // namespace zombie
