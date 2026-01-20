#include <string>
#include "zombie\iso\objects/IsoTree.h"

namespace zombie {
namespace iso {
namespace objects {

IsoTree IsoTree::getNew() {
    // TODO: Implement getNew
    return nullptr;
}

public IsoTree::IsoTree() {
    // TODO: Implement IsoTree
    return nullptr;
}

public IsoTree::IsoTree(IsoCell var1) {
    // TODO: Implement IsoTree
    return nullptr;
}

void IsoTree::save(ByteBuffer var1, bool var2) {
    // TODO: Implement save
}

void IsoTree::load(ByteBuffer var1, int var2, bool var3) {
    // TODO: Implement load
}

void IsoTree::checkMoveWithWind() {
    // TODO: Implement checkMoveWithWind
}

void IsoTree::reset() {
    // TODO: Implement reset
}

public IsoTree::IsoTree(IsoGridSquare var1, const std::string& var2) {
    // TODO: Implement IsoTree
    return nullptr;
}

public IsoTree::IsoTree(IsoGridSquare var1, IsoSprite var2) {
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

void IsoTree::Damage(float var1) {
    // TODO: Implement Damage
}

void IsoTree::HitByVehicle(BaseVehicle var1, float var2) {
    // TODO: Implement HitByVehicle
}

void IsoTree::WeaponHit(IsoGameCharacter var1, HandWeapon var2) {
    // TODO: Implement WeaponHit
}

void IsoTree::setHealth(int var1) {
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

float IsoTree::getSlowFactor(IsoMovingObject var1) {
    // TODO: Implement getSlowFactor
    return 0;
}

void IsoTree::render(float var1, float var2, float var3, ColorInfo var4, bool var5, bool var6, Shader var7) {
    // TODO: Implement render
}

void IsoTree::renderInner(float var1, float var2, float var3, ColorInfo var4, bool var5, bool var6) {
    // TODO: Implement renderInner
}

void IsoTree::setSprite(IsoSprite var1) {
    // TODO: Implement setSprite
}

bool IsoTree::isMaskClicked(int var1, int var2, bool var3) {
    // TODO: Implement isMaskClicked
    return false;
}

void IsoTree::setChopTreeCursorLocation(int var0, int var1, int var2, int var3) {
    // TODO: Implement setChopTreeCursorLocation
}

void IsoTree::checkChopTreeIndicator(float var1, float var2, float var3) {
    // TODO: Implement checkChopTreeIndicator
}

void IsoTree::renderChopTreeIndicators() {
    // TODO: Implement renderChopTreeIndicators
}

void IsoTree::renderChopTreeIndicator(IsoGridSquare var0) {
    // TODO: Implement renderChopTreeIndicator
}

} // namespace objects
} // namespace iso
} // namespace zombie
