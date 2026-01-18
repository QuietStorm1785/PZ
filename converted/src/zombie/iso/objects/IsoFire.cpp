#include "zombie/iso/objects/IsoFire.h"

namespace zombie {
namespace iso {
namespace objects {

public IsoFire::IsoFire(IsoCell cell) {
 // TODO: Implement IsoFire
 return nullptr;
}

public IsoFire::IsoFire(IsoCell cell, IsoGridSquare gridSquare) {
 // TODO: Implement IsoFire
 return nullptr;
}

std::string IsoFire::getObjectName() {
 // TODO: Implement getObjectName
 return "";
}

void IsoFire::save(ByteBuffer output, bool IS_DEBUG_SAVE) {
 // TODO: Implement save
}

void IsoFire::load(ByteBuffer b, int WorldVersion, bool IS_DEBUG_SAVE) {
 // TODO: Implement load
}

public IsoFire::IsoFire(IsoCell cell, IsoGridSquare gridSquare, bool CanBurnAnywhere, int StartingEnergy, int SetLife, bool isSmoke) {
 // TODO: Implement IsoFire
 return nullptr;
}

public IsoFire::IsoFire(IsoCell cell, IsoGridSquare gridSquare, bool CanBurnAnywhere, int StartingEnergy, int SetLife) {
 // TODO: Implement IsoFire
 return nullptr;
}

public IsoFire::IsoFire(IsoCell cell, IsoGridSquare gridSquare, bool CanBurnAnywhere, int StartingEnergy) {
 // TODO: Implement IsoFire
 return nullptr;
}

bool IsoFire::CanAddSmoke(IsoGridSquare gridSquare, bool CanBurnAnywhere) {
 // TODO: Implement CanAddSmoke
 return false;
}

return IsoFire::CanAddFire() {
 // TODO: Implement CanAddFire
 return nullptr;
}

bool IsoFire::CanAddFire(IsoGridSquare gridSquare, bool CanBurnAnywhere) {
 // TODO: Implement CanAddFire
 return false;
}

return IsoFire::CanAddFire() {
 // TODO: Implement CanAddFire
 return nullptr;
}

bool IsoFire::CanAddFire(IsoGridSquare gridSquare, bool CanBurnAnywhere, bool smoke) {
 // TODO: Implement CanAddFire
 return false;
}

bool IsoFire::Fire_IsSquareFlamable(IsoGridSquare gridSquare) {
 // TODO: Implement Fire_IsSquareFlamable
 return false;
}

bool IsoFire::HasTooltip() {
 // TODO: Implement HasTooltip
 return false;
}

void IsoFire::Spread() {
 // TODO: Implement Spread
}

bool IsoFire::TestCollide(IsoMovingObject obj, IsoGridSquare PassedObjectSquare) {
 // TODO: Implement TestCollide
 return false;
}

void IsoFire::update() {
 // TODO: Implement update
}

void IsoFire::render(float x, float y, float z, ColorInfo col, bool bDoChild, bool bWallLightingPass, Shader shader) {
 // TODO: Implement render
}

void IsoFire::extinctFire() {
 // TODO: Implement extinctFire
}

int IsoFire::getSquaresEnergyRequirement(IsoGridSquare square) {
 // TODO: Implement getSquaresEnergyRequirement
 return 0;
}

void IsoFire::setSpreadDelay(int _SpreadDelay) {
 // TODO: Implement setSpreadDelay
}

int IsoFire::getSpreadDelay() {
 // TODO: Implement getSpreadDelay
 return 0;
}

void IsoFire::setLife(int _Life) {
 // TODO: Implement setLife
}

int IsoFire::getLife() {
 // TODO: Implement getLife
 return 0;
}

int IsoFire::getEnergy() {
 // TODO: Implement getEnergy
 return 0;
}

bool IsoFire::isPermanent() {
 // TODO: Implement isPermanent
 return false;
}

void IsoFire::setLifeStage(int lifeStage) {
 // TODO: Implement setLifeStage
}

void IsoFire::setLightRadius(int radius) {
 // TODO: Implement setLightRadius
}

int IsoFire::getLightRadius() {
 // TODO: Implement getLightRadius
 return 0;
}

void IsoFire::addToWorld() {
 // TODO: Implement addToWorld
}

void IsoFire::removeFromWorld() {
 // TODO: Implement removeFromWorld
}

void IsoFire::saveChange(const std::string& change, KahluaTable tbl, ByteBuffer bb) {
 // TODO: Implement saveChange
}

void IsoFire::loadChange(const std::string& change, ByteBuffer bb) {
 // TODO: Implement loadChange
}

bool IsoFire::isCampfire() {
 // TODO: Implement isCampfire
 return false;
}

} // namespace objects
} // namespace iso
} // namespace zombie
