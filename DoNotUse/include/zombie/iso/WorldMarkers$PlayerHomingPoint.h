#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/Core.h"
#include "zombie/core/textures/Texture.h"

namespace zombie {
namespace iso {


class WorldMarkers {
public:
    int ID;
    Texture texture;
    int x;
    int y;
    float r;
    float g;
    float b;
    float a;
    float angle = 0.0F;
    float targetAngle = 0.0F;
    bool customTargetAngle = false;
    float angleLerpVal = 0.25F;
    float movementLerpVal = 0.25F;
    int dist = 0;
    float targRenderX = Core.getInstance().getScreenWidth() / 2.0F;
    float targRenderY = Core.getInstance().getScreenHeight() / 2.0F;
    float renderX = this.targRenderX;
    float renderY = this.targRenderY;
    float renderOffsetX = 0.0F;
    float renderOffsetY = 50.0F;
    float renderWidth = 32.0F;
    float renderHeight = 32.0F;
    float renderSizeMod = 1.0F;
    float targetScreenX;
    float targetScreenY;
    bool targetOnScreen = false;
    float stickToCharDist = 130.0F;
    bool active;
    bool homeOnTargetInView = true;
    int homeOnTargetDist = 20;
    float homeOnOffsetX = 0.0F;
    float homeOnOffsetY = 0.0F;
    bool isRemoved = false;

   public WorldMarkers$PlayerHomingPoint(int var1) {
      this.ID = WorldMarkers.NextHomingPointID++;
    float var2 = IsoCamera.getScreenLeft(var1);
    float var3 = IsoCamera.getScreenTop(var1);
    float var4 = IsoCamera.getScreenWidth(var1);
    float var5 = IsoCamera.getScreenHeight(var1);
      this.targRenderX = var2 + var4 / 2.0F;
      this.targRenderY = var3 + var5 / 2.0F;
   }

    void setTexture(const std::string& var1) {
      if (var1 == nullptr) {
         var1 = "arrow_triangle";
      }

      this.texture = Texture.getSharedTexture("media/textures/highlights/" + var1 + ".png");
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

    int getHomeOnTargetDist() {
      return this.homeOnTargetDist;
   }

    void setHomeOnTargetDist(int var1) {
      this.homeOnTargetDist = var1;
   }

    int getID() {
      return this.ID;
   }

    float getTargetAngle() {
      return this.targetAngle;
   }

    void setTargetAngle(float var1) {
      this.targetAngle = var1;
   }

    bool isCustomTargetAngle() {
      return this.customTargetAngle;
   }

    void setCustomTargetAngle(bool var1) {
      this.customTargetAngle = var1;
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

    float getAngleLerpVal() {
      return this.angleLerpVal;
   }

    void setAngleLerpVal(float var1) {
      this.angleLerpVal = var1;
   }

    float getMovementLerpVal() {
      return this.movementLerpVal;
   }

    void setMovementLerpVal(float var1) {
      this.movementLerpVal = var1;
   }

    bool isHomeOnTargetInView() {
      return this.homeOnTargetInView;
   }

    void setHomeOnTargetInView(bool var1) {
      this.homeOnTargetInView = var1;
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

    float getStickToCharDist() {
      return this.stickToCharDist;
   }

    void setStickToCharDist(float var1) {
      this.stickToCharDist = var1;
   }

    float getRenderOffsetX() {
      return this.renderOffsetX;
   }

    void setRenderOffsetX(float var1) {
      this.renderOffsetX = var1;
   }

    float getRenderOffsetY() {
      return this.renderOffsetY;
   }

    void setRenderOffsetY(float var1) {
      this.renderOffsetY = var1;
   }

    float getHomeOnOffsetX() {
      return this.homeOnOffsetX;
   }

    void setHomeOnOffsetX(float var1) {
      this.homeOnOffsetX = var1;
   }

    float getHomeOnOffsetY() {
      return this.homeOnOffsetY;
   }

    void setHomeOnOffsetY(float var1) {
      this.homeOnOffsetY = var1;
   }

    void setTableSurface() {
      this.homeOnOffsetY = -30.0F * Core.TileScale;
   }

    void setHighCounter() {
      this.homeOnOffsetY = -50.0F * Core.TileScale;
   }

    void setYOffsetScaled(float var1) {
      this.homeOnOffsetY = var1 * Core.TileScale;
   }

    void setXOffsetScaled(float var1) {
      this.homeOnOffsetX = var1 * Core.TileScale;
   }
}
} // namespace iso
} // namespace zombie
