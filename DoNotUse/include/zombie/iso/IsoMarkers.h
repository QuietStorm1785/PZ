#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "zombie/GameTime.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/SpriteRenderer.h"
#include "zombie/core/textures/Texture.h"
#include "zombie/debug/LineDrawer.h"
#include "zombie/iso/IsoCell/PerPlayerRender.h"
#include "zombie/iso/IsoMarkers/CircleIsoMarker.h"
#include "zombie/iso/IsoMarkers/IsoMarker.h"
#include "zombie/network/GameServer.h"

namespace zombie {
namespace iso {


class IsoMarkers {
public:
    static const IsoMarkers instance = std::make_shared<IsoMarkers>();
    static int NextIsoMarkerID = 0;
   private const List<IsoMarker> markers = std::make_unique<std::vector<>>();
   private const List<CircleIsoMarker> circlemarkers = std::make_unique<std::vector<>>();
    static int NextCircleIsoMarkerID = 0;

    private IsoMarkers() {
   }

    void init() {
   }

    void reset() {
      this.markers.clear();
      this.circlemarkers.clear();
   }

    void update() {
      if (!GameServer.bServer) {
         this.updateIsoMarkers();
         this.updateCircleIsoMarkers();
      }
   }

    void updateIsoMarkers() {
      if (IsoCamera.frameState.playerIndex == 0) {
         if (this.markers.size() != 0) {
            for (int var1 = this.markers.size() - 1; var1 >= 0; var1--) {
               if (this.markers.get(var1).isRemoved()) {
                  if (this.markers.get(var1).hasTempSquareObject()) {
                     this.markers.get(var1).removeTempSquareObjects();
                  }

                  this.markers.remove(var1);
               }
            }

            for (int var3 = 0; var3 < this.markers.size(); var3++) {
    IsoMarker var2 = this.markers.get(var3);
               if (var2.alphaInc) {
                  var2.alpha = var2.alpha + GameTime.getInstance().getMultiplier() * var2.fadeSpeed;
                  if (var2.alpha > var2.alphaMax) {
                     var2.alphaInc = false;
                     var2.alpha = var2.alphaMax;
                  }
               } else {
                  var2.alpha = var2.alpha - GameTime.getInstance().getMultiplier() * var2.fadeSpeed;
                  if (var2.alpha < var2.alphaMin) {
                     var2.alphaInc = true;
                     var2.alpha = 0.3F;
                  }
               }
            }
         }
      }
   }

    bool removeIsoMarker(IsoMarker var1) {
      return this.removeIsoMarker(var1.getID());
   }

    bool removeIsoMarker(int var1) {
      for (int var2 = this.markers.size() - 1; var2 >= 0; var2--) {
         if (this.markers.get(var2).getID() == var1) {
            this.markers.get(var2).remove();
            this.markers.remove(var2);
    return true;
         }
      }

    return false;
   }

    IsoMarker getIsoMarker(int var1) {
      for (int var2 = 0; var2 < this.markers.size(); var2++) {
         if (this.markers.get(var2).getID() == var1) {
            return this.markers.get(var2);
         }
      }

    return nullptr;
   }

    IsoMarker addIsoMarker(const std::string& var1, IsoGridSquare var2, float var3, float var4, float var5, bool var6, bool var7) {
      if (GameServer.bServer) {
    return nullptr;
      } else {
    IsoMarker var8 = std::make_shared<IsoMarker>();
         var8.setSquare(var2);
         var8.init(var1, var2.x, var2.y, var2.z, var2, var7);
         var8.setR(var3);
         var8.setG(var4);
         var8.setB(var5);
         var8.setA(1.0F);
         var8.setDoAlpha(var6);
         var8.setFadeSpeed(0.006F);
         var8.setAlpha(1.0F);
         var8.setAlphaMin(0.3F);
         var8.setAlphaMax(1.0F);
         this.markers.push_back(var8);
    return var8;
      }
   }

    IsoMarker addIsoMarker(KahluaTable var1, KahluaTable var2, IsoGridSquare var3, float var4, float var5, float var6, bool var7, bool var8) {
      return this.addIsoMarker(var1, var2, var3, var4, var5, var6, var7, var8, 0.006F, 0.3F, 1.0F);
   }

   public IsoMarker addIsoMarker(
      KahluaTable var1,
      KahluaTable var2,
      IsoGridSquare var3,
      float var4,
      float var5,
      float var6,
      boolean var7,
      boolean var8,
      float var9,
      float var10,
      float var11
   ) {
      if (GameServer.bServer) {
    return nullptr;
      } else {
    IsoMarker var12 = std::make_shared<IsoMarker>();
         var12.init(var1, var2, var3.x, var3.y, var3.z, var3, var8);
         var12.setSquare(var3);
         var12.setR(var4);
         var12.setG(var5);
         var12.setB(var6);
         var12.setA(1.0F);
         var12.setDoAlpha(var7);
         var12.setFadeSpeed(var9);
         var12.setAlpha(0.0F);
         var12.setAlphaMin(var10);
         var12.setAlphaMax(var11);
         this.markers.push_back(var12);
    return var12;
      }
   }

    void renderIsoMarkers(PerPlayerRender var1, int var2, int var3) {
      if (!GameServer.bServer && this.markers.size() != 0) {
    IsoPlayer var4 = IsoPlayer.players[var3];
         if (var4 != nullptr) {
            for (int var5 = 0; var5 < this.markers.size(); var5++) {
    IsoMarker var6 = this.markers.get(var5);
               if (var6.z == var2 && var6.z == var4.getZ() && var6.active) {
                  for (int var7 = 0; var7 < var6.textures.size(); var7++) {
    Texture var8 = (Texture)var6.textures.get(var7);
    float var9 = IsoUtils.XToScreen(var6.x, var6.y, var6.z, 0) - IsoCamera.cameras[var3].getOffX() - var8.getWidth() / 2.0F;
    float var10 = IsoUtils.YToScreen(var6.x, var6.y, var6.z, 0) - IsoCamera.cameras[var3].getOffY() - var8.getHeight();
                     SpriteRenderer.instance.render(var8, var9, var10, var8.getWidth(), var8.getHeight(), var6.r, var6.g, var6.b, var6.alpha, nullptr);
                  }
               }
            }
         }
      }
   }

    void renderIsoMarkersDeferred(PerPlayerRender var1, int var2, int var3) {
      if (!GameServer.bServer && this.markers.size() != 0) {
    IsoPlayer var4 = IsoPlayer.players[var3];
         if (var4 != nullptr) {
            for (int var5 = 0; var5 < this.markers.size(); var5++) {
    IsoMarker var6 = this.markers.get(var5);
               if (var6.z == var2 && var6.z == var4.getZ() && var6.active) {
                  for (int var7 = 0; var7 < var6.overlayTextures.size(); var7++) {
    Texture var8 = (Texture)var6.overlayTextures.get(var7);
    float var9 = IsoUtils.XToScreen(var6.x, var6.y, var6.z, 0) - IsoCamera.cameras[var3].getOffX() - var8.getWidth() / 2.0F;
    float var10 = IsoUtils.YToScreen(var6.x, var6.y, var6.z, 0) - IsoCamera.cameras[var3].getOffY() - var8.getHeight();
                     SpriteRenderer.instance.render(var8, var9, var10, var8.getWidth(), var8.getHeight(), var6.r, var6.g, var6.b, var6.alpha, nullptr);
                  }
               }
            }
         }
      }
   }

    void renderIsoMarkersOnSquare(PerPlayerRender var1, int var2, int var3) {
      if (!GameServer.bServer && this.markers.size() != 0) {
    IsoPlayer var4 = IsoPlayer.players[var3];
         if (var4 != nullptr) {
            for (int var5 = 0; var5 < this.markers.size(); var5++) {
    IsoMarker var6 = this.markers.get(var5);
               if (var6.z == var2 && var6.z == var4.getZ() && var6.active) {
                  for (int var7 = 0; var7 < var6.overlayTextures.size(); var7++) {
    Texture var8 = (Texture)var6.overlayTextures.get(var7);
    float var9 = IsoUtils.XToScreen(var6.x, var6.y, var6.z, 0) - IsoCamera.cameras[var3].getOffX() - var8.getWidth() / 2.0F;
    float var10 = IsoUtils.YToScreen(var6.x, var6.y, var6.z, 0) - IsoCamera.cameras[var3].getOffY() - var8.getHeight();
                     SpriteRenderer.instance.render(var8, var9, var10, var8.getWidth(), var8.getHeight(), var6.r, var6.g, var6.b, var6.alpha, nullptr);
                  }
               }
            }
         }
      }
   }

    void updateCircleIsoMarkers() {
      if (IsoCamera.frameState.playerIndex == 0) {
         if (this.circlemarkers.size() != 0) {
            for (int var1 = this.circlemarkers.size() - 1; var1 >= 0; var1--) {
               if (this.circlemarkers.get(var1).isRemoved()) {
                  this.circlemarkers.remove(var1);
               }
            }

            for (int var3 = 0; var3 < this.circlemarkers.size(); var3++) {
    CircleIsoMarker var2 = this.circlemarkers.get(var3);
               if (var2.alphaInc) {
                  var2.alpha = var2.alpha + GameTime.getInstance().getMultiplier() * var2.fadeSpeed;
                  if (var2.alpha > var2.alphaMax) {
                     var2.alphaInc = false;
                     var2.alpha = var2.alphaMax;
                  }
               } else {
                  var2.alpha = var2.alpha - GameTime.getInstance().getMultiplier() * var2.fadeSpeed;
                  if (var2.alpha < var2.alphaMin) {
                     var2.alphaInc = true;
                     var2.alpha = 0.3F;
                  }
               }
            }
         }
      }
   }

    bool removeCircleIsoMarker(CircleIsoMarker var1) {
      return this.removeCircleIsoMarker(var1.getID());
   }

    bool removeCircleIsoMarker(int var1) {
      for (int var2 = this.circlemarkers.size() - 1; var2 >= 0; var2--) {
         if (this.circlemarkers.get(var2).getID() == var1) {
            this.circlemarkers.get(var2).remove();
            this.circlemarkers.remove(var2);
    return true;
         }
      }

    return false;
   }

    CircleIsoMarker getCircleIsoMarker(int var1) {
      for (int var2 = 0; var2 < this.circlemarkers.size(); var2++) {
         if (this.circlemarkers.get(var2).getID() == var1) {
            return this.circlemarkers.get(var2);
         }
      }

    return nullptr;
   }

    CircleIsoMarker addCircleIsoMarker(IsoGridSquare var1, float var2, float var3, float var4, float var5) {
      if (GameServer.bServer) {
    return nullptr;
      } else {
    CircleIsoMarker var6 = std::make_shared<CircleIsoMarker>();
         var6.init(var1.x, var1.y, var1.z, var1);
         var6.setSquare(var1);
         var6.setR(var2);
         var6.setG(var3);
         var6.setB(var4);
         var6.setA(var5);
         var6.setDoAlpha(false);
         var6.setFadeSpeed(0.006F);
         var6.setAlpha(1.0F);
         var6.setAlphaMin(1.0F);
         var6.setAlphaMax(1.0F);
         this.circlemarkers.push_back(var6);
    return var6;
      }
   }

    void renderCircleIsoMarkers(PerPlayerRender var1, int var2, int var3) {
      if (!GameServer.bServer && this.circlemarkers.size() != 0) {
    IsoPlayer var4 = IsoPlayer.players[var3];
         if (var4 != nullptr) {
            for (int var5 = 0; var5 < this.circlemarkers.size(); var5++) {
    CircleIsoMarker var6 = this.circlemarkers.get(var5);
               if (var6.z == var2 && var6.z == var4.getZ() && var6.active) {
                  LineDrawer.DrawIsoCircle(var6.x, var6.y, var6.z, var6.size, 32, var6.r, var6.g, var6.b, var6.a);
               }
            }
         }
      }
   }

    void render() {
      this.update();
   }
}
} // namespace iso
} // namespace zombie
