#include "zombie/network/ServerGUI.h"

namespace zombie {
namespace network {

bool ServerGUI::isCreated() {
  // TODO: Implement isCreated
  return false;
}

void ServerGUI::init() {
  // TODO: Implement init
}

void ServerGUI::init2() {
  // TODO: Implement init2
}

void ServerGUI::shutdown() {
  // TODO: Implement shutdown
}

void ServerGUI::update() {
  // TODO: Implement update
}

IsoPlayer ServerGUI::getPlayerToFollow() {
  // TODO: Implement getPlayerToFollow
  return nullptr;
}

void ServerGUI::updateCamera(IsoPlayer player) {
  // TODO: Implement updateCamera
}

void ServerGUI::renderWorld() {
  // TODO: Implement renderWorld
}

void ServerGUI::RenderTiles() {
  // TODO: Implement RenderTiles
}

int ServerGUI::renderFloor(IsoGridSquare square) {
  // TODO: Implement renderFloor
  return 0;
}

bool ServerGUI::isSpriteOnSouthOrEastWall(IsoObject object) {
  // TODO: Implement isSpriteOnSouthOrEastWall
  return false;
}

int ServerGUI::DoWallLightingN(IsoGridSquare square, IsoObject object,
                               int int0) {
  // TODO: Implement DoWallLightingN
  return 0;
}

int ServerGUI::DoWallLightingW(IsoGridSquare square, IsoObject object,
                               int int0) {
  // TODO: Implement DoWallLightingW
  return 0;
}

int ServerGUI::DoWallLightingNW(IsoGridSquare square, IsoObject object,
                                int int0) {
  // TODO: Implement DoWallLightingNW
  return 0;
}

bool ServerGUI::renderMinusFloor(IsoGridSquare square0, bool boolean0,
                                 bool boolean4) {
  // TODO: Implement renderMinusFloor
  return false;
}

void ServerGUI::renderCharacters(IsoGridSquare square, bool boolean0) {
  // TODO: Implement renderCharacters
}

void ServerGUI::renderUI() {
  // TODO: Implement renderUI
}

} // namespace network
} // namespace zombie
