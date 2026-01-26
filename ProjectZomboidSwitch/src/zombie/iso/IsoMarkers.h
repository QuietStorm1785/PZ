// --- IsoMarker (nested class) ---
class IsoMarker {
public:
   int ID;
   std::vector<std::shared_ptr<Texture>> textures;
   std::vector<std::shared_ptr<Texture>> overlayTextures;
   std::vector<std::shared_ptr<IsoObject>> tempObjects;
   std::shared_ptr<IsoGridSquare> square;
   float x = 0.0f, y = 0.0f, z = 0.0f;
   float r = 1.0f, g = 1.0f, b = 1.0f, a = 1.0f;
   bool doAlpha = false;
   float fadeSpeed = 0.006f;
   float alpha = 0.0f;
   float alphaMax = 1.0f;
   float alphaMin = 0.3f;
   bool alphaInc = true;
   bool active = true;
   bool removed = false;

   IsoMarker() : ID(IsoMarkers::NextIsoMarkerID++) {}

   int getID() const { return ID; }
   void remove() { removed = true; }
   bool isRemoved() const { return removed; }

   void init(LuaTable* t1, LuaTable* t2, int px, int py, int pz, std::shared_ptr<IsoGridSquare> sq) {
      square = sq;
      // TODO: Fill textures/overlayTextures from LuaTable if needed
      setPos(px, py, pz);
   }
   void init(LuaTable* t1, LuaTable* t2, int px, int py, int pz, std::shared_ptr<IsoGridSquare> sq, bool temp) {
      square = sq;
      // TODO: Fill tempObjects from LuaTable if temp
      setPos(px, py, pz);
   }
   void init(const std::string& name, int px, int py, int pz, std::shared_ptr<IsoGridSquare> sq, bool temp) {
      square = sq;
      // TODO: Fill tempObjects if temp
      setPos(px, py, pz);
   }
   bool hasTempSquareObject() const { return !tempObjects.empty(); }
   void addTempSquareObject(std::shared_ptr<IsoObject> obj) { /* TODO: Add to square->localTemporaryObjects */ }
   void removeTempSquareObjects() { /* TODO: Remove from square->localTemporaryObjects */ }
   float getX() const { return x; }
   float getY() const { return y; }
   float getZ() const { return z; }
   float getR() const { return r; }
   float getG() const { return g; }
   float getB() const { return b; }
   float getA() const { return a; }
   void setR(float v) { r = v; }
   void setG(float v) { g = v; }
   void setB(float v) { b = v; }
   void setA(float v) { a = v; }
   float getAlpha() const { return alpha; }
   void setAlpha(float v) { alpha = v; }
   float getAlphaMax() const { return alphaMax; }
   void setAlphaMax(float v) { alphaMax = v; }
   float getAlphaMin() const { return alphaMin; }
   void setAlphaMin(float v) { alphaMin = v; }
   bool isDoAlpha() const { return doAlpha; }
   void setDoAlpha(bool v) { doAlpha = v; }
   float getFadeSpeed() const { return fadeSpeed; }
   void setFadeSpeed(float v) { fadeSpeed = v; }
   std::shared_ptr<IsoGridSquare> getSquare() const { return square; }
   void setSquare(std::shared_ptr<IsoGridSquare> sq) { square = sq; }
   void setPos(int px, int py, int pz) { x = px + 0.5f; y = py + 0.5f; z = pz; }
   bool isActive() const { return active; }
   void setActive(bool v) { active = v; }
};

// --- CircleIsoMarker (nested class) ---
class CircleIsoMarker {
public:
   int ID;
   std::shared_ptr<IsoGridSquare> square;
   float x = 0.0f, y = 0.0f, z = 0.0f;
   float r = 1.0f, g = 1.0f, b = 1.0f, a = 1.0f;
   float size = 1.0f;
   bool doAlpha = false;
   float fadeSpeed = 0.006f;
   float alpha = 0.0f;
   float alphaMax = 1.0f;
   float alphaMin = 0.3f;
   bool alphaInc = true;
   bool active = true;
   bool removed = false;

   CircleIsoMarker() : ID(IsoMarkers::NextCircleIsoMarkerID++) {}

   int getID() const { return ID; }
   void remove() { removed = true; }
   bool isRemoved() const { return removed; }
   void init(int px, int py, int pz, std::shared_ptr<IsoGridSquare> sq) { square = sq; setPos(px, py, pz); }
   float getX() const { return x; }
   float getY() const { return y; }
   float getZ() const { return z; }
   float getR() const { return r; }
   float getG() const { return g; }
   float getB() const { return b; }
   float getA() const { return a; }
   void setR(float v) { r = v; }
   void setG(float v) { g = v; }
   void setB(float v) { b = v; }
   void setA(float v) { a = v; }
   float getSize() const { return size; }
   void setSize(float v) { size = v; }
   float getAlpha() const { return alpha; }
   void setAlpha(float v) { alpha = v; }
   float getAlphaMax() const { return alphaMax; }
   void setAlphaMax(float v) { alphaMax = v; }
   float getAlphaMin() const { return alphaMin; }
   void setAlphaMin(float v) { alphaMin = v; }
   bool isDoAlpha() const { return doAlpha; }
   void setDoAlpha(bool v) { doAlpha = v; }
   float getFadeSpeed() const { return fadeSpeed; }
   void setFadeSpeed(float v) { fadeSpeed = v; }
   std::shared_ptr<IsoGridSquare> getSquare() const { return square; }
   void setSquare(std::shared_ptr<IsoGridSquare> sq) { square = sq; }
   void setPos(int px, int py, int pz) { x = px; y = py; z = pz; }
   bool isActive() const { return active; }
   void setActive(bool v) { active = v; }
};
#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/lua/LuaTable.h" // Replace with your Lua 5.4.7 table wrapper
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
   // Singleton accessor (not enforced, but matches Java static usage)
   static IsoMarkers& instance();

   // Marker ID counters
   static int NextIsoMarkerID;
   static int NextCircleIsoMarkerID;

   // Initialization/reset
   void init();
   void reset();

   // Update
   void update();
   void updateIsoMarkers();
   void updateCircleIsoMarkers();

   // Marker management
   bool removeIsoMarker(std::shared_ptr<IsoMarker> marker);
   bool removeIsoMarker(int id);
   std::shared_ptr<IsoMarker> getIsoMarker(int id);
   std::shared_ptr<IsoMarker> addIsoMarker(const std::string& name, std::shared_ptr<IsoGridSquare> sq, float r, float g, float b, bool doAlpha, bool temp);
   // LuaTable overloads (use LuaTable for Lua 5.4.7 integration)
   std::shared_ptr<IsoMarker> addIsoMarker(LuaTable* t1, LuaTable* t2, std::shared_ptr<IsoGridSquare> sq, float r, float g, float b, bool doAlpha, bool temp);
   std::shared_ptr<IsoMarker> addIsoMarker(LuaTable* t1, LuaTable* t2, std::shared_ptr<IsoGridSquare> sq, float r, float g, float b, bool doAlpha, bool temp, float fadeSpeed, float alphaMin, float alphaMax);

   // Rendering
   void renderIsoMarkers(std::shared_ptr<PerPlayerRender> render, int z, int playerIdx);
   void renderIsoMarkersDeferred(std::shared_ptr<PerPlayerRender> render, int z, int playerIdx);
   void renderIsoMarkersOnSquare(std::shared_ptr<PerPlayerRender> render, int z, int playerIdx);
   void renderCircleIsoMarkers(std::shared_ptr<PerPlayerRender> render, int z, int playerIdx);
   void render();

   // Circle marker management
   bool removeCircleIsoMarker(std::shared_ptr<CircleIsoMarker> marker);
   bool removeCircleIsoMarker(int id);
   std::shared_ptr<CircleIsoMarker> getCircleIsoMarker(int id);
   std::shared_ptr<CircleIsoMarker> addCircleIsoMarker(std::shared_ptr<IsoGridSquare> sq, float r, float g, float b, float a);

   // Marker containers (public for legacy compatibility, but prefer accessors)
   std::vector<std::shared_ptr<IsoMarker>> markers;
   std::vector<std::shared_ptr<CircleIsoMarker>> circlemarkers;

private:
   IsoMarkers() = default;
   IsoMarkers(const IsoMarkers&) = delete;
   IsoMarkers& operator=(const IsoMarkers&) = delete;
};

// Static member definitions
inline int IsoMarkers::NextIsoMarkerID = 0;
inline int IsoMarkers::NextCircleIsoMarkerID = 0;

inline IsoMarkers& IsoMarkers::instance() {
   static IsoMarkers inst;
   return inst;
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
