#pragma once
#include "org/lwjgl/util/Rectangle.h"
#include "zombie/core/Color.h"
#include "zombie/core/SpriteRenderer.h"
#include "zombie/core/textures/Texture.h"
#include "zombie/iso/IsoCamera.h"
#include "zombie/iso/Vector2.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace iso {
namespace weather {
namespace fx {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

/**
 * TurboTuTone.
 */
class WeatherParticle {
public:
 ParticleRectangle parent;
 Rectangle bounds;
 Texture texture;
 Color color = Color.white;
 Vector2 position = new Vector2(0.0F, 0.0F);
 Vector2 velocity = new Vector2(0.0F, 0.0F);
 float alpha = 1.0F;
 float speed = 0.0F;
 SteppedUpdateFloat alphaFadeMod =
 new SteppedUpdateFloat(0.0F, 0.1F, 0.0F, 1.0F);
 float renderAlpha = 0.0F;
 float oWidth;
 float oHeight;
 float zoomMultiW = 0.0F;
 float zoomMultiH = 0.0F;
 bool recalcSizeOnZoom = false;
 float lastZoomMod = -1.0F;

public
 WeatherParticle(Texture _texture) {
 this->texture = _texture;
 this->bounds =
 new Rectangle(0, 0, _texture.getWidth(), _texture.getHeight());
 this->oWidth = this->bounds.getWidth();
 this->oHeight = this->bounds.getHeight();
 }

public
 WeatherParticle(Texture _texture, int w, int h) {
 this->texture = _texture;
 this->bounds = new Rectangle(0, 0, w, h);
 this->oWidth = this->bounds.getWidth();
 this->oHeight = this->bounds.getHeight();
 }

 void setParent(ParticleRectangle particleRectangle) {
 this->parent = particleRectangle;
 }

 void update(float delta) { this->update(delta, true); }

 void update(float delta, bool doBounds) {
 this->alphaFadeMod.update(delta);
 if (this->position.x > this->parent.getWidth()) {
 this->position.x =
 this->position.x - (int)(this->position.x / this->parent.getWidth()) *
 this->parent.getWidth();
 } else if (this->position.x < 0.0F) {
 this->position.x =
 this->position.x - (int)((this->position.x - this->parent.getWidth()) /
 this->parent.getWidth()) *
 this->parent.getWidth();
 }

 if (this->position.y > this->parent.getHeight()) {
 this->position.y =
 this->position.y - (int)(this->position.y / this->parent.getHeight()) *
 this->parent.getHeight();
 } else if (this->position.y < 0.0F) {
 this->position.y =
 this->position.y - (int)((this->position.y - this->parent.getHeight()) /
 this->parent.getHeight()) *
 this->parent.getHeight();
 }

 if (doBounds) {
 this->bounds.setLocation((int)this->position.x - this->bounds.getWidth() / 2,
 (int)this->position.y -
 this->bounds.getHeight() / 2);
 }
 }

 bool updateZoomSize() noexcept{
 if (this->recalcSizeOnZoom && this->lastZoomMod != IsoWeatherFX.ZoomMod) {
 this->lastZoomMod = IsoWeatherFX.ZoomMod;
 this->oWidth = this->bounds.getWidth();
 this->oHeight = this->bounds.getHeight();
 if (this->lastZoomMod > 0.0F) {
 this->oWidth =
 this->oWidth * (1.0F + IsoWeatherFX.ZoomMod * this->zoomMultiW);
 this->oHeight =
 this->oHeight * (1.0F + IsoWeatherFX.ZoomMod * this->zoomMultiH);
 }

 return true;
 } else {
 return false;
 }
 }

 bool isOnScreen(float offsetx, float offsety) {
 int int0 = IsoCamera.frameState.OffscreenWidth;
 int int1 = IsoCamera.frameState.OffscreenHeight;
 float float0 = offsetx + this->bounds.getX();
 float float1 = offsety + this->bounds.getY();
 float float2 = float0 + this->oWidth;
 float float3 = float1 + this->oHeight;
 return float0 >= int0 || float2 <= 0.0F
 ? false
 : !(float1 >= int1) && !(float3 <= 0.0F);
 }

 void render(float offsetx, float offsety) {
 SpriteRenderer.instance.render(this->texture, offsetx + this->bounds.getX(),
 offsety + this->bounds.getY(), this->oWidth,
 this->oHeight, this->color.r, this->color.g,
 this->color.b, this->renderAlpha, nullptr);
 }
}
} // namespace fx
} // namespace weather
} // namespace iso
} // namespace zombie
