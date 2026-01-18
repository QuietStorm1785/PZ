#include "zombie/worldMap/WorldMapVisited.h"

namespace zombie {
namespace worldMap {

public WorldMapVisited::WorldMapVisited() {
 // TODO: Implement WorldMapVisited
 return nullptr;
}

void WorldMapVisited::setBounds(int minX, int minY, int maxX, int maxY) {
 // TODO: Implement setBounds
}

int WorldMapVisited::getMinX() {
 // TODO: Implement getMinX
 return 0;
}

int WorldMapVisited::getMinY() {
 // TODO: Implement getMinY
 return 0;
}

int WorldMapVisited::getWidthInCells() {
 // TODO: Implement getWidthInCells
 return 0;
}

int WorldMapVisited::getHeightInCells() {
 // TODO: Implement getHeightInCells
 return 0;
}

int WorldMapVisited::calcTextureWidth() {
 // TODO: Implement calcTextureWidth
 return 0;
}

int WorldMapVisited::calcTextureHeight() {
 // TODO: Implement calcTextureHeight
 return 0;
}

void WorldMapVisited::setKnownInCells(int minX, int minY, int maxX, int maxY) {
 // TODO: Implement setKnownInCells
}

void WorldMapVisited::clearKnownInCells(int minX, int minY, int maxX, int maxY) {
 // TODO: Implement clearKnownInCells
}

void WorldMapVisited::setVisitedInCells(int minX, int minY, int maxX, int maxY) {
 // TODO: Implement setVisitedInCells
}

void WorldMapVisited::clearVisitedInCells(int minX, int minY, int maxX, int maxY) {
 // TODO: Implement clearVisitedInCells
}

void WorldMapVisited::setKnownInSquares(int minX, int minY, int maxX, int maxY) {
 // TODO: Implement setKnownInSquares
}

void WorldMapVisited::clearKnownInSquares(int minX, int minY, int maxX, int maxY) {
 // TODO: Implement clearKnownInSquares
}

void WorldMapVisited::setVisitedInSquares(int minX, int minY, int maxX, int maxY) {
 // TODO: Implement setVisitedInSquares
}

void WorldMapVisited::clearVisitedInSquares(int minX, int minY, int maxX, int maxY) {
 // TODO: Implement clearVisitedInSquares
}

void WorldMapVisited::updateVisitedTexture() {
 // TODO: Implement updateVisitedTexture
}

void WorldMapVisited::renderMain() {
 // TODO: Implement renderMain
}

void WorldMapVisited::initShader() {
 // TODO: Implement initShader
}

void WorldMapVisited::render(float renderX, float renderY, int minX, int minY, int maxX, int maxY, float worldScale, bool blur) {
 // TODO: Implement render
}

void WorldMapVisited::renderGrid(float renderX, float renderY, int minX, int minY, int maxX, int maxY, float worldScale, float zoomF) {
 // TODO: Implement renderGrid
}

void WorldMapVisited::destroy() {
 // TODO: Implement destroy
}

void WorldMapVisited::save(ByteBuffer output) {
 // TODO: Implement save
}

void WorldMapVisited::load(ByteBuffer input, int WorldVersion) {
 // TODO: Implement load
}

void WorldMapVisited::save() {
 // TODO: Implement save
}

void WorldMapVisited::load() {
 // TODO: Implement load
}

void WorldMapVisited::setFlags(int int0, int int1, int int2, int int3, int int13) {
 // TODO: Implement setFlags
}

void WorldMapVisited::clearFlags(int int0, int int1, int int2, int int3, int int13) {
 // TODO: Implement clearFlags
}

bool WorldMapVisited::updateTextureData(ByteBuffer byteBuffer, int int2) {
 // TODO: Implement updateTextureData
 return false;
}

void WorldMapVisited::setUnvisitedRGBA(float float0, float float1, float float2, float float3) {
 // TODO: Implement setUnvisitedRGBA
}

void WorldMapVisited::setUnvisitedGridRGBA(float float0, float float1, float float2, float float3) {
 // TODO: Implement setUnvisitedGridRGBA
}

bool WorldMapVisited::hasFlags(int int0, int int1, int int2, int int3, int int13, bool boolean0) {
 // TODO: Implement hasFlags
 return false;
}

bool WorldMapVisited::isCellVisible(int int1, int int0) {
 // TODO: Implement isCellVisible
 return false;
}

WorldMapVisited WorldMapVisited::getInstance() {
 // TODO: Implement getInstance
 return nullptr;
}

void WorldMapVisited::update() {
 // TODO: Implement update
}

void WorldMapVisited::forget() {
 // TODO: Implement forget
}

void WorldMapVisited::SaveAll() {
 // TODO: Implement SaveAll
}

void WorldMapVisited::Reset() {
 // TODO: Implement Reset
}

} // namespace worldMap
} // namespace zombie
