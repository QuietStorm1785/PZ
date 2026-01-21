#include <string>
#include "zombie/worldMap/UIWorldMap.h"

namespace zombie {
namespace worldMap {

public UIWorldMap::UIWorldMap(KahluaTable var1) {
    // TODO: Implement UIWorldMap
    return nullptr;
}

UIWorldMapV1 UIWorldMap::getAPI() {
    // TODO: Implement getAPI
    return nullptr;
}

UIWorldMapV1 UIWorldMap::getAPIv1() {
    // TODO: Implement getAPIv1
    return nullptr;
}

void UIWorldMap::setMapItem(MapItem var1) {
    // TODO: Implement setMapItem
}

void UIWorldMap::render() {
    // TODO: Implement render
}

void UIWorldMap::renderLocalPlayers() {
    // TODO: Implement renderLocalPlayers
}

void UIWorldMap::renderRemotePlayers() {
    // TODO: Implement renderRemotePlayers
}

bool UIWorldMap::shouldShowRemotePlayer(WorldMapRemotePlayer var1) {
    // TODO: Implement shouldShowRemotePlayer
    return false;
}

bool UIWorldMap::isAdminSeeRemotePlayers() {
    // TODO: Implement isAdminSeeRemotePlayers
    return false;
}

bool UIWorldMap::isInSameFaction(IsoPlayer var1, WorldMapRemotePlayer var2) {
    // TODO: Implement isInSameFaction
    return false;
}

bool UIWorldMap::isInSameSafehouse(IsoPlayer var1, WorldMapRemotePlayer var2) {
    // TODO: Implement isInSameSafehouse
    return false;
}

void UIWorldMap::renderPlayer(float var1, float var2) {
    // TODO: Implement renderPlayer
}

void UIWorldMap::renderPlayerName(float var1, float var2, const std::string& var3) {
    // TODO: Implement renderPlayerName
}

void UIWorldMap::update() {
    // TODO: Implement update
}

bool UIWorldMap::onMouseDown(double var1, double var3) {
    // TODO: Implement onMouseDown
    return false;
}

bool UIWorldMap::onMouseUp(double var1, double var3) {
    // TODO: Implement onMouseUp
    return false;
}

void UIWorldMap::onMouseUpOutside(double var1, double var3) {
    // TODO: Implement onMouseUpOutside
}

bool UIWorldMap::onMouseMove(double var1, double var3) {
    // TODO: Implement onMouseMove
    return false;
}

bool UIWorldMap::onMouseWheel(double var1) {
    // TODO: Implement onMouseWheel
    return false;
}

void UIWorldMap::setExposed(Exposer var0) {
    // TODO: Implement setExposed
}

void UIWorldMap::renderBuildingsWithoutFeatures() {
    // TODO: Implement renderBuildingsWithoutFeatures
}

void UIWorldMap::debugRenderBuilding(BuildingDef var1, float var2, float var3, float var4, float var5) {
    // TODO: Implement debugRenderBuilding
}

} // namespace worldMap
} // namespace zombie
