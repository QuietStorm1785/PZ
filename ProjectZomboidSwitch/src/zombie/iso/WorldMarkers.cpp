#include <string>
#include "zombie\iso/WorldMarkers.h"

namespace zombie {
namespace iso {

private WorldMarkers::WorldMarkers() {
    // TODO: Implement WorldMarkers
    return nullptr;
}

void WorldMarkers::init() {
    // TODO: Implement init
}

void WorldMarkers::reset() {
    // TODO: Implement reset
}

int WorldMarkers::GetDistance(int var1, int var2, int var3, int var4) {
    // TODO: Implement GetDistance
    return 0;
}

float WorldMarkers::getAngle(int var1, int var2, int var3, int var4) {
    // TODO: Implement getAngle
    return 0;
}

float WorldMarkers::angleDegrees(float var1) {
    // TODO: Implement angleDegrees
    return 0;
}

PlayerHomingPoint WorldMarkers::getHomingPoint(int var1) {
    // TODO: Implement getHomingPoint
    return nullptr;
}

PlayerHomingPoint WorldMarkers::addPlayerHomingPoint(IsoPlayer var1, int var2, int var3) {
    // TODO: Implement addPlayerHomingPoint
    return nullptr;
}

PlayerHomingPoint WorldMarkers::addPlayerHomingPoint(IsoPlayer var1, int var2, int var3, float var4, float var5, float var6, float var7) {
    // TODO: Implement addPlayerHomingPoint
    return nullptr;
}

bool WorldMarkers::removeHomingPoint(PlayerHomingPoint var1) {
    // TODO: Implement removeHomingPoint
    return false;
}

bool WorldMarkers::removeHomingPoint(int var1) {
    // TODO: Implement removeHomingPoint
    return false;
}

bool WorldMarkers::removePlayerHomingPoint(IsoPlayer var1, PlayerHomingPoint var2) {
    // TODO: Implement removePlayerHomingPoint
    return false;
}

bool WorldMarkers::removePlayerHomingPoint(IsoPlayer var1, int var2) {
    // TODO: Implement removePlayerHomingPoint
    return false;
}

void WorldMarkers::removeAllHomingPoints(IsoPlayer var1) {
    // TODO: Implement removeAllHomingPoints
}

DirectionArrow WorldMarkers::getDirectionArrow(int var1) {
    // TODO: Implement getDirectionArrow
    return nullptr;
}

DirectionArrow WorldMarkers::addDirectionArrow(IsoPlayer var1, int var2, int var3, int var4, const std::string& var5, float var6, float var7, float var8, float var9) {
    // TODO: Implement addDirectionArrow
    return nullptr;
}

bool WorldMarkers::removeDirectionArrow(DirectionArrow var1) {
    // TODO: Implement removeDirectionArrow
    return false;
}

bool WorldMarkers::removeDirectionArrow(int var1) {
    // TODO: Implement removeDirectionArrow
    return false;
}

bool WorldMarkers::removePlayerDirectionArrow(IsoPlayer var1, DirectionArrow var2) {
    // TODO: Implement removePlayerDirectionArrow
    return false;
}

bool WorldMarkers::removePlayerDirectionArrow(IsoPlayer var1, int var2) {
    // TODO: Implement removePlayerDirectionArrow
    return false;
}

void WorldMarkers::removeAllDirectionArrows(IsoPlayer var1) {
    // TODO: Implement removeAllDirectionArrows
}

void WorldMarkers::update() {
    // TODO: Implement update
}

void WorldMarkers::updateDirectionArrows() {
    // TODO: Implement updateDirectionArrows
}

void WorldMarkers::updateHomingPoints() {
    // TODO: Implement updateHomingPoints
}

void WorldMarkers::updateGridSquareMarkers() {
    // TODO: Implement updateGridSquareMarkers
}

bool WorldMarkers::removeGridSquareMarker(GridSquareMarker var1) {
    // TODO: Implement removeGridSquareMarker
    return false;
}

bool WorldMarkers::removeGridSquareMarker(int var1) {
    // TODO: Implement removeGridSquareMarker
    return false;
}

GridSquareMarker WorldMarkers::getGridSquareMarker(int var1) {
    // TODO: Implement getGridSquareMarker
    return nullptr;
}

GridSquareMarker WorldMarkers::addGridSquareMarker(IsoGridSquare var1, float var2, float var3, float var4, bool var5, float var6) {
    // TODO: Implement addGridSquareMarker
    return nullptr;
}

GridSquareMarker WorldMarkers::addGridSquareMarker(const std::string& var1, const std::string& var2, IsoGridSquare var3, float var4, float var5, float var6, bool var7, float var8) {
    // TODO: Implement addGridSquareMarker
    return nullptr;
}

void WorldMarkers::renderGridSquareMarkers(PerPlayerRender var1, int var2, int var3) {
    // TODO: Implement renderGridSquareMarkers
}

void WorldMarkers::debugRender() {
    // TODO: Implement debugRender
}

void WorldMarkers::render() {
    // TODO: Implement render
}

void WorldMarkers::renderHomingPoint() {
    // TODO: Implement renderHomingPoint
}

void WorldMarkers::renderDirectionArrow(bool var1) {
    // TODO: Implement renderDirectionArrow
}

bool WorldMarkers::intersectLineSegments(Line var0, Line var1, Point var2) {
    // TODO: Implement intersectLineSegments
    return false;
}

} // namespace iso
} // namespace zombie
