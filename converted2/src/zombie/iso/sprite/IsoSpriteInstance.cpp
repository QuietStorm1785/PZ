#include "zombie/iso/sprite/IsoSpriteInstance.h"

namespace zombie {
namespace iso {
namespace sprite {

IsoSpriteInstance IsoSpriteInstance::get(IsoSprite spr) {
  // TODO: Implement get
  return nullptr;
}

void IsoSpriteInstance::reset() {
  // TODO: Implement reset
}

public
IsoSpriteInstance::IsoSpriteInstance() {
  // TODO: Implement IsoSpriteInstance
  return nullptr;
}

void IsoSpriteInstance::setFrameSpeedPerFrame(float perSecond) {
  // TODO: Implement setFrameSpeedPerFrame
}

int IsoSpriteInstance::getID() {
  // TODO: Implement getID
  return 0;
}

std::string IsoSpriteInstance::getName() {
  // TODO: Implement getName
  return "";
}

IsoSprite IsoSpriteInstance::getParentSprite() {
  // TODO: Implement getParentSprite
  return nullptr;
}

public
IsoSpriteInstance::IsoSpriteInstance(IsoSprite spr) {
  // TODO: Implement IsoSpriteInstance
  return nullptr;
}

float IsoSpriteInstance::getTintR() {
  // TODO: Implement getTintR
  return 0;
}

float IsoSpriteInstance::getTintG() {
  // TODO: Implement getTintG
  return 0;
}

float IsoSpriteInstance::getTintB() {
  // TODO: Implement getTintB
  return 0;
}

float IsoSpriteInstance::getAlpha() {
  // TODO: Implement getAlpha
  return 0;
}

float IsoSpriteInstance::getTargetAlpha() {
  // TODO: Implement getTargetAlpha
  return 0;
}

bool IsoSpriteInstance::isCopyTargetAlpha() {
  // TODO: Implement isCopyTargetAlpha
  return false;
}

bool IsoSpriteInstance::isMultiplyObjectAlpha() {
  // TODO: Implement isMultiplyObjectAlpha
  return false;
}

void IsoSpriteInstance::render(IsoObject obj, float x, float y, float z,
                               IsoDirections dir, float offsetX, float offsetY,
                               ColorInfo info2) {
  // TODO: Implement render
}

void IsoSpriteInstance::SetAlpha(float f) {
  // TODO: Implement SetAlpha
}

void IsoSpriteInstance::SetTargetAlpha(float _targetAlpha) {
  // TODO: Implement SetTargetAlpha
}

void IsoSpriteInstance::update() {
  // TODO: Implement update
}

void IsoSpriteInstance::renderprep(IsoObject object) {
  // TODO: Implement renderprep
}

float IsoSpriteInstance::getFrame() {
  // TODO: Implement getFrame
  return 0;
}

bool IsoSpriteInstance::isFinished() {
  // TODO: Implement isFinished
  return false;
}

void IsoSpriteInstance::Dispose() {
  // TODO: Implement Dispose
}

void IsoSpriteInstance::RenderGhostTileColor(int x, int y, int z, float r,
                                             float g, float b, float a) {
  // TODO: Implement RenderGhostTileColor
}

void IsoSpriteInstance::setScale(float _scaleX, float _scaleY) {
  // TODO: Implement setScale
}

float IsoSpriteInstance::getScaleX() {
  // TODO: Implement getScaleX
  return 0;
}

float IsoSpriteInstance::getScaleY() {
  // TODO: Implement getScaleY
  return 0;
}

void IsoSpriteInstance::scaleAspect(float texW, float texH, float width,
                                    float height) {
  // TODO: Implement scaleAspect
}

void IsoSpriteInstance::add(IsoSpriteInstance isoSpriteInstance) {
  // TODO: Implement add
}

} // namespace sprite
} // namespace iso
} // namespace zombie
