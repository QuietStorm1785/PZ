#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "zombie/core/textures/Texture.h"
#include "zombie/util/Type.h"

namespace zombie {
namespace iso {


class IsoMarkers {
public:
    int ID;
   private std::vector<Texture> textures = std::make_unique<std::vector<>>();
   private std::vector<Texture> overlayTextures = std::make_unique<std::vector<>>();
   private std::vector<IsoObject> tempObjects = std::make_unique<std::vector<>>();
    IsoGridSquare square;
    float x;
    float y;
    float z;
    float r;
    float g;
    float b;
    float a;
    bool doAlpha;
    float fadeSpeed = 0.006F;
    float alpha = 0.0F;
    float alphaMax = 1.0F;
    float alphaMin = 0.3F;
    bool alphaInc = true;
    bool active = true;
    bool isRemoved = false;

   public IsoMarkers$IsoMarker() {
      this.ID = IsoMarkers.NextIsoMarkerID++;
   }

    int getID() {
      return this.ID;
   }

    void remove() {
      this.isRemoved = true;
   }

    bool isRemoved() {
      return this.isRemoved;
   }

    void init(KahluaTable var1, KahluaTable var2, int var3, int var4, int var5, IsoGridSquare var6) {
      this.square = var6;
      if (var1 != nullptr) {
    int var7 = var1.len();

         for (int var8 = 1; var8 <= var7; var8++) {
    std::string var9 = (std::string)Type.tryCastTo(var1.rawget(var8), std::string.class);
    Texture var10 = Texture.trygetTexture(var9);
            if (var10 != nullptr) {
               this.textures.push_back(var10);
               this.setPos(var3, var4, var5);
            }
         }
      }

      if (var2 != nullptr) {
    int var11 = var2.len();

         for (int var12 = 1; var12 <= var11; var12++) {
    std::string var13 = (std::string)Type.tryCastTo(var2.rawget(var12), std::string.class);
    Texture var14 = Texture.trygetTexture(var13);
            if (var14 != nullptr) {
               this.overlayTextures.push_back(var14);
               this.setPos(var3, var4, var5);
            }
         }
      }
   }

    void init(KahluaTable var1, KahluaTable var2, int var3, int var4, int var5, IsoGridSquare var6, bool var7) {
      this.square = var6;
      if (var7) {
         if (var1 != nullptr) {
    int var8 = var1.len();

            for (int var9 = 1; var9 <= var8; var9++) {
    std::string var10 = (std::string)Type.tryCastTo(var1.rawget(var9), std::string.class);
    Texture var11 = Texture.trygetTexture(var10);
               if (var11 != nullptr) {
    IsoObject var12 = std::make_shared<IsoObject>(var6.getCell(), var6, var11.getName());
                  this.tempObjects.push_back(var12);
                  this.addTempSquareObject(var12);
                  this.setPos(var3, var4, var5);
               }
            }
         }
      } else {
         this.init(var1, var2, var3, var4, var5, var6);
      }
   }

    void init(const std::string& var1, int var2, int var3, int var4, IsoGridSquare var5, bool var6) {
      this.square = var5;
      if (var6 && var1 != nullptr) {
    IsoObject var7 = IsoObject.getNew(var5, var1, var1, false);
         this.tempObjects.push_back(var7);
         this.addTempSquareObject(var7);
         this.setPos(var2, var3, var4);
      }
   }

    bool hasTempSquareObject() {
      return this.tempObjects.size() > 0;
   }

    void addTempSquareObject(IsoObject var1) {
      this.square.localTemporaryObjects.push_back(var1);
   }

    void removeTempSquareObjects() {
      this.square.localTemporaryObjects.clear();
   }

    float getX() {
      return this.x;
   }

    float getY() {
      return this.y;
   }

    float getZ() {
      return this.z;
   }

    float getR() {
      return this.r;
   }

    float getG() {
      return this.g;
   }

    float getB() {
      return this.b;
   }

    float getA() {
      return this.a;
   }

    void setR(float var1) {
      this.r = var1;
   }

    void setG(float var1) {
      this.g = var1;
   }

    void setB(float var1) {
      this.b = var1;
   }

    void setA(float var1) {
      this.a = var1;
   }

    float getAlpha() {
      return this.alpha;
   }

    void setAlpha(float var1) {
      this.alpha = var1;
   }

    float getAlphaMax() {
      return this.alphaMax;
   }

    void setAlphaMax(float var1) {
      this.alphaMax = var1;
   }

    float getAlphaMin() {
      return this.alphaMin;
   }

    void setAlphaMin(float var1) {
      this.alphaMin = var1;
   }

    bool isDoAlpha() {
      return this.doAlpha;
   }

    void setDoAlpha(bool var1) {
      this.doAlpha = var1;
   }

    float getFadeSpeed() {
      return this.fadeSpeed;
   }

    void setFadeSpeed(float var1) {
      this.fadeSpeed = var1;
   }

    IsoGridSquare getSquare() {
      return this.square;
   }

    void setSquare(IsoGridSquare var1) {
      this.square = var1;
   }

    void setPos(int var1, int var2, int var3) {
      this.x = var1 + 0.5F;
      this.y = var2 + 0.5F;
      this.z = var3;
   }

    bool isActive() {
      return this.active;
   }

    void setActive(bool var1) {
      this.active = var1;
   }
}
} // namespace iso
} // namespace zombie
