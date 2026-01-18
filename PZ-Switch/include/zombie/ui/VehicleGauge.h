#pragma once
#include "zombie/core/SpriteRenderer.h"
#include "zombie/core/textures/Texture.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace ui {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class VehicleGauge : public UIElement {
public:
 int needleX;
 int needleY;
 float minAngle;
 float maxAngle;
 float value;
 Texture texture;
 int needleWidth = 45;

public
 VehicleGauge(Texture _texture, int _needleX, int _needleY, float _minAngle,
 float _maxAngle) {
 this->texture = _texture;
 this->needleX = _needleX;
 this->needleY = _needleY;
 this->minAngle = _minAngle;
 this->maxAngle = _maxAngle;
 this->width = _texture.getWidth();
 this->height = _texture.getHeight();
 }

 void setNeedleWidth(int newSize) { this->needleWidth = newSize; }

 void render() {
 if (this->isVisible()) {
 super.render();
 this->DrawTexture(this->texture, 0.0, 0.0, 1.0);
 double double0 =
 this->minAngle < this->maxAngle
 ? Math.toRadians(this->minAngle +
 (this->maxAngle - this->minAngle) * this->value)
 : Math.toRadians(this->maxAngle + (this->maxAngle - this->minAngle) *
 (1.0F - this->value);
 double double1 = this->needleX;
 double double2 = this->needleY;
 double double3 = this->needleX + this->needleWidth * Math.cos(double0);
 double double4 =
 Math.ceil(this->needleY + this->needleWidth * Math.sin(double0);
 int int0 = this->getAbsoluteX().intValue();
 int int1 = this->getAbsoluteY().intValue();
 SpriteRenderer.instance.renderline(
 nullptr, int0 + (int)double1, int1 + (int)double2,
 int0 + (int)double3, int1 + (int)double4, 1.0F, 0.0F, 0.0F, 1.0F);
 }
 }

 void setValue(float _value) { this->value = Math.min(_value, 1.0F); }

 void setTexture(Texture newText) { this->texture = newText; }
}
} // namespace ui
} // namespace zombie
