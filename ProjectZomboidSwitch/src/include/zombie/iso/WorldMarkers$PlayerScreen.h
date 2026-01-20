#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/math/PZMath.h"
#include "zombie/iso/WorldMarkers/Line.h"
#include "zombie/iso/WorldMarkers/Point.h"

namespace zombie {
namespace iso {


class WorldMarkers {
public:
    float centerX;
    float centerY;
    float x;
    float y;
    float width;
    float height;
    float padTop;
    float padLeft;
    float padBot;
    float padRight;
    float innerX;
    float innerY;
    float innerX2;
    float innerY2;
    Line borderTop;
    Line borderRight;
    Line borderBot;
    Line borderLeft;
   private Line[] borders;

   WorldMarkers$PlayerScreen(WorldMarkers var1) {
      this.this$0 = var1;
      this.padTop = 100.0F;
      this.padLeft = 100.0F;
      this.padBot = 100.0F;
      this.padRight = 100.0F;
      this.borderTop = std::make_shared<Line>(std::make_shared<Point>(0.0F, 0.0F), std::make_shared<Point>(0.0F, 0.0F));
      this.borderRight = std::make_shared<Line>(std::make_shared<Point>(0.0F, 0.0F), std::make_shared<Point>(0.0F, 0.0F));
      this.borderBot = std::make_shared<Line>(std::make_shared<Point>(0.0F, 0.0F), std::make_shared<Point>(0.0F, 0.0F));
      this.borderLeft = std::make_shared<Line>(std::make_shared<Point>(0.0F, 0.0F), std::make_shared<Point>(0.0F, 0.0F));
      this.borders = new Line[4];
   }

    void update(int var1) {
      this.x = 0.0F;
      this.y = 0.0F;
      this.width = IsoCamera.getScreenWidth(var1);
      this.height = IsoCamera.getScreenHeight(var1);
      this.centerX = this.x + this.width / 2.0F;
      this.centerY = this.y + this.height / 2.0F;
      this.innerX = this.x + this.padLeft;
      this.innerY = this.y + this.padTop;
    float var2 = this.width - (this.padLeft + this.padRight);
    float var3 = this.height - (this.padTop + this.padBot);
      this.innerX2 = this.innerX + var2;
      this.innerY2 = this.innerY + var3;
   }

   private Line[] getBorders() {
      this.borders[0] = this.getBorderTop();
      this.borders[1] = this.getBorderRight();
      this.borders[2] = this.getBorderBot();
      this.borders[3] = this.getBorderLeft();
      return this.borders;
   }

    Line getBorderTop() {
      this.borderTop.s.set(this.innerX, this.innerY);
      this.borderTop.e.set(this.innerX2, this.innerY);
      return this.borderTop;
   }

    Line getBorderRight() {
      this.borderRight.s.set(this.innerX2, this.innerY);
      this.borderRight.e.set(this.innerX2, this.innerY2);
      return this.borderRight;
   }

    Line getBorderBot() {
      this.borderBot.s.set(this.innerX, this.innerY2);
      this.borderBot.e.set(this.innerX2, this.innerY2);
      return this.borderBot;
   }

    Line getBorderLeft() {
      this.borderLeft.s.set(this.innerX, this.innerY);
      this.borderLeft.e.set(this.innerX, this.innerY2);
      return this.borderLeft;
   }

    float clampToInnerX(float var1) {
      return PZMath.clamp(var1, this.innerX, this.innerX2);
   }

    float clampToInnerY(float var1) {
      return PZMath.clamp(var1, this.innerY, this.innerY2);
   }

    bool isOnScreen(float var1, float var2) {
      return var1 >= this.x && var1 < this.x + this.width && var2 >= this.y && var2 < this.y + this.height;
   }

    bool isWithinInner(float var1, float var2) {
      return var1 >= this.innerX && var1 < this.innerX2 && var2 >= this.innerY && var2 < this.innerY2;
   }
}
} // namespace iso
} // namespace zombie
