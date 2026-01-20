#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace iso {

class IsoMarkers {
public:
    int ID;
    IsoGridSquare square;
    float x;
    float y;
    float z;
    float r;
    float g;
    float b;
    float a;
    float size;
    bool doAlpha;
    float fadeSpeed = 0.006F;
    float alpha = 0.0F;
    float alphaMax = 1.0F;
    float alphaMin = 0.3F;
    bool alphaInc = true;
    bool active = true;
    bool isRemoved = false;

   public IsoMarkers$CircleIsoMarker() {
      this.ID = IsoMarkers.NextCircleIsoMarkerID++;
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

    void init(int var1, int var2, int var3, IsoGridSquare var4) {
      this.square = var4;
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

    float getSize() {
      return this.size;
   }

    void setSize(float var1) {
      this.size = var1;
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
      this.x = var1;
      this.y = var2;
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
