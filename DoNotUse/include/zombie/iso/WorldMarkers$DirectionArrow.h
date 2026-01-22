#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/Core.h"
#include "zombie/core/textures/Texture.h"
#include "zombie/iso/WorldMarkers/DirectionArrow/DebugStuff.h"

namespace zombie {
namespace iso {


class WorldMarkers {
public:
    static const bool doDebug = false;
    DebugStuff debugStuff;
    int ID;
    bool active;
    bool isRemoved;
    bool isDrawOnWorld;
    Texture renderTexture;
    Texture texture;
    Texture texStairsUp;
    Texture texStairsDown;
    Texture texDown;
    int x;
    int y;
    int z;
    float r;
    float g;
    float b;
    float a;
    float renderWidth;
    float renderHeight;
    float angle;
    float angleLerpVal;
    bool lastWasWithinView;
    float renderScreenX;
    float renderScreenY;
    bool renderWithAngle;
    float renderSizeMod;

   public WorldMarkers$DirectionArrow(WorldMarkers var1, int var2) {
      this.this$0 = var1;
      this.active = true;
      this.isRemoved = false;
      this.isDrawOnWorld = false;
      this.renderWidth = 32.0F;
      this.renderHeight = 32.0F;
      this.angleLerpVal = 0.25F;
      this.lastWasWithinView = true;
      this.renderWithAngle = true;
      this.renderSizeMod = 1.0F;
      if (Core.bDebug) {
      }

      this.ID = WorldMarkers.NextHomingPointID++;
   }

    void setTexture(const std::string& var1) {
      if (var1 == nullptr) {
         var1 = "dir_arrow_up";
      }

      this.texture = Texture.getSharedTexture("media/textures/highlights/" + var1 + ".png");
   }

    void setTexDown(const std::string& var1) {
      this.texDown = Texture.getSharedTexture("media/textures/highlights/" + var1 + ".png");
   }

    void setTexStairsDown(const std::string& var1) {
      this.texStairsDown = Texture.getSharedTexture("media/textures/highlights/" + var1 + ".png");
   }

    void setTexStairsUp(const std::string& var1) {
      this.texStairsUp = Texture.getSharedTexture("media/textures/highlights/" + var1 + ".png");
   }

    void remove() {
      this.isRemoved = true;
   }

    bool isRemoved() {
      return this.isRemoved;
   }

    bool isActive() {
      return this.active;
   }

    void setActive(bool var1) {
      this.active = var1;
   }

    float getR() {
      return this.r;
   }

    void setR(float var1) {
      this.r = var1;
   }

    float getB() {
      return this.b;
   }

    void setB(float var1) {
      this.b = var1;
   }

    float getG() {
      return this.g;
   }

    void setG(float var1) {
      this.g = var1;
   }

    float getA() {
      return this.a;
   }

    void setA(float var1) {
      this.a = var1;
   }

    void setRGBA(float var1, float var2, float var3, float var4) {
      this.r = var1;
      this.g = var2;
      this.b = var3;
      this.a = var4;
   }

    int getID() {
      return this.ID;
   }

    int getX() {
      return this.x;
   }

    void setX(int var1) {
      this.x = var1;
   }

    int getY() {
      return this.y;
   }

    void setY(int var1) {
      this.y = var1;
   }

    int getZ() {
      return this.z;
   }

    void setZ(int var1) {
      this.z = var1;
   }

    float getRenderWidth() {
      return this.renderWidth;
   }

    void setRenderWidth(float var1) {
      this.renderWidth = var1;
   }

    float getRenderHeight() {
      return this.renderHeight;
   }

    void setRenderHeight(float var1) {
      this.renderHeight = var1;
   }
}
} // namespace iso
} // namespace zombie
