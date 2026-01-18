#include "zombie/iso/objects/IsoTree.h"

namespace zombie {
namespace iso {
namespace objects {

IsoTree IsoTree::getNew() {
  // TODO: Implement getNew
  return nullptr;
}

public
IsoTree::IsoTree() {
  // TODO: Implement IsoTree
  return nullptr;
}

public
IsoTree::IsoTree(IsoCell cell) {
  // TODO: Implement IsoTree
  return nullptr;
}

void IsoTree::save(ByteBuffer output, bool IS_DEBUG_SAVE) {
  // TODO: Implement save
}

void IsoTree::load(ByteBuffer input, int WorldVersion, bool IS_DEBUG_SAVE) {
  // TODO: Implement load
}

void IsoTree::checkMoveWithWind() {
  // TODO: Implement checkMoveWithWind
}

void IsoTree::reset() {
  // TODO: Implement reset
}

public
IsoTree::IsoTree(IsoGridSquare sq, const std::string &gid) {
  // TODO: Implement IsoTree
  return nullptr;
}

public
IsoTree::IsoTree(IsoGridSquare sq, IsoSprite gid) {
  // TODO: Implement IsoTree
  return nullptr;
}

void IsoTree::initTree() {
  // TODO: Implement initTree
}

std::string IsoTree::getObjectName() {
  // TODO: Implement getObjectName
  return "";
}

void IsoTree::Damage(float amount) {
  // TODO: Implement Damage
}

void IsoTree::HitByVehicle(BaseVehicle vehicle, float amount) {
  // TODO: Implement HitByVehicle
}

void IsoTree::WeaponHit(IsoGameCharacter owner, HandWeapon weapon) {
  // TODO: Implement WeaponHit
}

void IsoTree::setHealth(int health) {
  // TODO: Implement setHealth
}

int IsoTree::getHealth() {
  // TODO: Implement getHealth
  return 0;
}

int IsoTree::getMaxHealth() {
  // TODO: Implement getMaxHealth
  return 0;
}

int IsoTree::getSize() {
  // TODO: Implement getSize
  return 0;
}

float IsoTree::getSlowFactor(IsoMovingObject chr) {
  // TODO: Implement getSlowFactor
  return 0;
}

void IsoTree::render(float x, float y, float z, ColorInfo col, bool bDoAttached,
                     bool bWallLightingPass, Shader shader) {
  // TODO: Implement render
}

void IsoTree::renderInner(float float4, float float5, float float6,
                          ColorInfo colorInfo, bool var5, bool boolean0) {
  // TODO: Implement renderInner
}

void IsoTree::setSprite(IsoSprite sprite) {
  // TODO: Implement setSprite
}

bool IsoTree::isMaskClicked(int x, int y, bool flip) {
  // TODO: Implement isMaskClicked
  return false;
}

void IsoTree::setChopTreeCursorLocation(int playerIndex, int x, int y, int z) {
  // TODO: Implement setChopTreeCursorLocation
}

void IsoTree::checkChopTreeIndicator(float var1, float var2, float var3) {
  // TODO: Implement checkChopTreeIndicator
}

void IsoTree::renderChopTreeIndicators() {
  // TODO: Implement renderChopTreeIndicators
}

void IsoTree::renderChopTreeIndicator(IsoGridSquare square) {
  // TODO: Implement renderChopTreeIndicator
}

void IsoTree::initShader() {
  // TODO: Implement initShader
}

void IsoTree::setOutlineColor(float float0, float float1, float float2,
                              float float3) {
  // TODO: Implement setOutlineColor
}

void IsoTree::setStepSize(float float0, int int1, int int0) {
  // TODO: Implement setStepSize
}

bool IsoTree::StartShader() {
  // TODO: Implement StartShader
  return false;
}

} // namespace objects
} // namespace iso
} // namespace zombie
