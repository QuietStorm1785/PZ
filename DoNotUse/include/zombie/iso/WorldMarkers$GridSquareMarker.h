#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/Core.h"
#include "zombie/core/textures/Texture.h"
#include "zombie/iso/sprite/IsoSpriteInstance.h"
#include "zombie/iso/sprite/IsoSpriteManager.h"

namespace zombie {
namespace iso {


class WorldMarkers {
public:
    int ID;
    IsoSpriteInstance sprite;
    IsoSpriteInstance spriteOverlay;
    float orig_x;
    float orig_y;
    float orig_z;
    float x;
    float y;
    float z;
    float scaleRatio;
    float r;
    float g;
    float b;
    float a;
    float size;
    bool doBlink = false;
    bool doAlpha;
    bool bScaleCircleTexture = false;
    float fadeSpeed = 0.006F;
    float alpha = 0.0F;
    float alphaMax = 1.0F;
    float alphaMin = 0.3F;
    bool alphaInc = true;
    bool active = true;
    bool isRemoved = false;

   public WorldMarkers$GridSquareMarker() {
      this.ID = WorldMarkers.NextGridSquareMarkerID++;
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

    void init(const std::string& var1, const std::string& var2, int var3, int var4, int var5, float var6) {
      if (var1 == nullptr) {
         var1 = "circle_center";
      }

    Texture var7 = Texture.getSharedTexture("media/textures/highlights/" + var1 + ".png");
    float var8 = var7.getWidth();
    float var9 = 64.0F * Core.TileScale;
      this.scaleRatio = 1.0F / (var8 / var9);
      this.sprite = std::make_shared<IsoSpriteInstance>(IsoSpriteManager.instance.getSprite("media/textures/highlights/" + var1 + ".png"));
      if (var2 != nullptr) {
         this.spriteOverlay = std::make_shared<IsoSpriteInstance>(IsoSpriteManager.instance.getSprite("media/textures/highlights/" + var2 + ".png"));
      }

      this.setPosAndSize(var3, var4, var5, var6);
   }

    void setPosAndSize(int var1, int var2, int var3, float var4) {
    float var5 = var4 * (this.bScaleCircleTexture ? 1.5F : 1.0F);
    float var6 = this.scaleRatio * var5;
      this.sprite.setScale(var6, var6);
      if (this.spriteOverlay != nullptr) {
         this.spriteOverlay.setScale(var6, var6);
      }

      this.size = var4;
      this.orig_x = var1;
      this.orig_y = var2;
      this.orig_z = var3;
      this.x = var1 - (var5 - 0.5F);
      this.y = var2 + 0.5F;
      this.z = var3;
   }

    void setPos(int var1, int var2, int var3) {
    float var4 = this.size * (this.bScaleCircleTexture ? 1.5F : 1.0F);
      this.orig_x = var1;
      this.orig_y = var2;
      this.orig_z = var3;
      this.x = var1 - (var4 - 0.5F);
      this.y = var2 + 0.5F;
      this.z = var3;
   }

    void setSize(float var1) {
    float var2 = var1 * (this.bScaleCircleTexture ? 1.5F : 1.0F);
    float var3 = this.scaleRatio * var2;
      this.sprite.setScale(var3, var3);
      if (this.spriteOverlay != nullptr) {
         this.spriteOverlay.setScale(var3, var3);
      }

      this.size = var1;
      this.x = this.orig_x - (var2 - 0.5F);
      this.y = this.orig_y + 0.5F;
      this.z = this.orig_z;
   }

    bool isActive() {
      return this.active;
   }

    void setActive(bool var1) {
      this.active = var1;
   }

    float getSize() {
      return this.size;
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

    void setR(float var1) {
      this.r = var1;
   }

    float getG() {
      return this.g;
   }

    void setG(float var1) {
      this.g = var1;
   }

    float getB() {
      return this.b;
   }

    void setB(float var1) {
      this.b = var1;
   }

    float getA() {
      return this.a;
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

    bool isDoBlink() {
      return this.doBlink;
   }

    void setDoBlink(bool var1) {
      this.doBlink = var1;
   }

    bool isScaleCircleTexture() {
      return this.bScaleCircleTexture;
   }

    void setScaleCircleTexture(bool var1) {
      this.bScaleCircleTexture = var1;
    float var2 = this.size * (this.bScaleCircleTexture ? 1.5F : 1.0F);
    float var3 = this.scaleRatio * var2;
      if (this.sprite != nullptr) {
         this.sprite.setScale(var3, var3);
      }

      if (this.spriteOverlay != nullptr) {
         this.spriteOverlay.setScale(var3, var3);
      }

      this.x = this.orig_x - (var2 - 0.5F);
   }
}
} // namespace iso
} // namespace zombie
