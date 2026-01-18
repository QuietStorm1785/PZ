#include "zombie/worldMap/UIWorldMap.h"

namespace zombie {
namespace worldMap {

public
UIWorldMap::UIWorldMap(KahluaTable table) {
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

void UIWorldMap::setMapItem(MapItem mapItem) {
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

bool UIWorldMap::shouldShowRemotePlayer(
 WorldMapRemotePlayer worldMapRemotePlayer) {
 // TODO: Implement shouldShowRemotePlayer
 return false;
}

bool UIWorldMap::isAdminSeeRemotePlayers() {
 // TODO: Implement isAdminSeeRemotePlayers
 return false;
}

bool UIWorldMap::isInSameFaction(IsoPlayer player,
 WorldMapRemotePlayer worldMapRemotePlayer) {
 // TODO: Implement isInSameFaction
 return false;
}

bool UIWorldMap::isInSameSafehouse(IsoPlayer player,
 WorldMapRemotePlayer worldMapRemotePlayer) {
 // TODO: Implement isInSameSafehouse
 return false;
}

void UIWorldMap::renderPlayer(float float4, float float5) {
 // TODO: Implement renderPlayer
}

void UIWorldMap::renderPlayerName(float float4, float float5,
 const std::string &string) {
 // TODO: Implement renderPlayerName
}

void UIWorldMap::update() {
 // TODO: Implement update
}

bool UIWorldMap::onMouseDown(double x, double y) {
 // TODO: Implement onMouseDown
 return false;
}

bool UIWorldMap::onMouseUp(double x, double y) {
 // TODO: Implement onMouseUp
 return false;
}

void UIWorldMap::onMouseUpOutside(double x, double y) {
 // TODO: Implement onMouseUpOutside
}

bool UIWorldMap::onMouseMove(double dx, double dy) {
 // TODO: Implement onMouseMove
 return false;
}

bool UIWorldMap::onMouseWheel(double delta) {
 // TODO: Implement onMouseWheel
 return false;
}

void UIWorldMap::setExposed(LuaManager.Exposer exposer) {
 // TODO: Implement setExposed
}

void UIWorldMap::renderBuildingsWithoutFeatures() {
 // TODO: Implement renderBuildingsWithoutFeatures
}

void UIWorldMap::debugRenderBuilding(BuildingDef buildingDef, float float7,
 float float6, float float5, float float4) {
 // TODO: Implement debugRenderBuilding
}

} // namespace worldMap
} // namespace zombie
