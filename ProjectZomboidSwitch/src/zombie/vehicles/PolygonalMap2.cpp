#include <vector>
#include "zombie\vehicles/PolygonalMap2.h"

namespace zombie {
namespace vehicles {

void PolygonalMap2::createVehicleCluster(VehicleRect var1, std::vector<VehicleRect> var2, std::vector<VehicleCluster> var3) {
    // TODO: Implement createVehicleCluster
}

void PolygonalMap2::createVehicleClusters() {
    // TODO: Implement createVehicleClusters
}

Node PolygonalMap2::getNodeForSquare(Square var1) {
    // TODO: Implement getNodeForSquare
    return nullptr;
}

VisibilityGraph PolygonalMap2::getVisGraphAt(float var1, float var2, int var3) {
    // TODO: Implement getVisGraphAt
    return nullptr;
}

VisibilityGraph PolygonalMap2::getVisGraphAt(float var1, float var2, int var3, int var4) {
    // TODO: Implement getVisGraphAt
    return nullptr;
}

VisibilityGraph PolygonalMap2::getVisGraphForSquare(Square var1) {
    // TODO: Implement getVisGraphForSquare
    return nullptr;
}

Connection PolygonalMap2::connectTwoNodes(Node var1, Node var2, int var3) {
    // TODO: Implement connectTwoNodes
    return nullptr;
}

Connection PolygonalMap2::connectTwoNodes(Node var1, Node var2) {
    // TODO: Implement connectTwoNodes
    return nullptr;
}

void PolygonalMap2::breakConnection(Connection var1) {
    // TODO: Implement breakConnection
}

void PolygonalMap2::breakConnection(Node var1, Node var2) {
    // TODO: Implement breakConnection
}

void PolygonalMap2::addStairNodes() {
    // TODO: Implement addStairNodes
}

void PolygonalMap2::addCanPathNodes() {
    // TODO: Implement addCanPathNodes
}

Node PolygonalMap2::getOrCreateCanPathNode(Square var1) {
    // TODO: Implement getOrCreateCanPathNode
    return nullptr;
}

Node PolygonalMap2::getPointOutsideObjects(Square var1, float var2, float var3) {
    // TODO: Implement getPointOutsideObjects
    return nullptr;
}

void PolygonalMap2::createVisibilityGraph(VehicleCluster var1) {
    // TODO: Implement createVisibilityGraph
}

void PolygonalMap2::createVisibilityGraphs() {
    // TODO: Implement createVisibilityGraphs
}

bool PolygonalMap2::findPath(PathFindRequest var1, bool var2) {
    // TODO: Implement findPath
    return false;
}

void PolygonalMap2::cleanPath(std::vector<ISearchNode> var1, PathFindRequest var2, bool var3, bool var4, SearchNode var5) {
    // TODO: Implement cleanPath
}

void PolygonalMap2::smoothPath(Path var1) {
    // TODO: Implement smoothPath
}

float PolygonalMap2::getApparentZ(IsoGridSquare var1) {
    // TODO: Implement getApparentZ
    return 0;
}

void PolygonalMap2::render() {
    // TODO: Implement render
}

void PolygonalMap2::squareChanged(IsoGridSquare var1) {
    // TODO: Implement squareChanged
}

void PolygonalMap2::addChunkToWorld(IsoChunk var1) {
    // TODO: Implement addChunkToWorld
}

void PolygonalMap2::removeChunkFromWorld(IsoChunk var1) {
    // TODO: Implement removeChunkFromWorld
}

void PolygonalMap2::addVehicleToWorld(BaseVehicle var1) {
    // TODO: Implement addVehicleToWorld
}

void PolygonalMap2::updateVehicle(BaseVehicle var1) {
    // TODO: Implement updateVehicle
}

void PolygonalMap2::removeVehicleFromWorld(BaseVehicle var1) {
    // TODO: Implement removeVehicleFromWorld
}

Cell PolygonalMap2::getCellFromSquarePos(int var1, int var2) {
    // TODO: Implement getCellFromSquarePos
    return nullptr;
}

Cell PolygonalMap2::getCellFromChunkPos(int var1, int var2) {
    // TODO: Implement getCellFromChunkPos
    return nullptr;
}

Chunk PolygonalMap2::allocChunkIfNeeded(int var1, int var2) {
    // TODO: Implement allocChunkIfNeeded
    return nullptr;
}

Chunk PolygonalMap2::getChunkFromChunkPos(int var1, int var2) {
    // TODO: Implement getChunkFromChunkPos
    return nullptr;
}

Chunk PolygonalMap2::getChunkFromSquarePos(int var1, int var2) {
    // TODO: Implement getChunkFromSquarePos
    return nullptr;
}

Square PolygonalMap2::getSquare(int var1, int var2, int var3) {
    // TODO: Implement getSquare
    return nullptr;
}

bool PolygonalMap2::isBlockedInAllDirections(int var1, int var2, int var3) {
    // TODO: Implement isBlockedInAllDirections
    return false;
}

void PolygonalMap2::init(IsoMetaGrid var1) {
    // TODO: Implement init
}

void PolygonalMap2::stop() {
    // TODO: Implement stop
}

void PolygonalMap2::updateMain() {
    // TODO: Implement updateMain
}

void PolygonalMap2::updateThread() {
    // TODO: Implement updateThread
}

PathFindRequest PolygonalMap2::addRequest(IPathfinder var1, Mover var2, float var3, float var4, float var5, float var6, float var7, float var8) {
    // TODO: Implement addRequest
    return nullptr;
}

void PolygonalMap2::cancelRequest(Mover var1) {
    // TODO: Implement cancelRequest
}

void PolygonalMap2::supercover(float var1, float var2, float var3, float var4, int var5, PointPool var6, std::vector<Point> var7) {
    // TODO: Implement supercover
}

bool PolygonalMap2::lineClearCollide(float var1, float var2, float var3, float var4, int var5) {
    // TODO: Implement lineClearCollide
    return false;
}

bool PolygonalMap2::lineClearCollide(float var1, float var2, float var3, float var4, int var5, IsoMovingObject var6) {
    // TODO: Implement lineClearCollide
    return false;
}

bool PolygonalMap2::lineClearCollide(float var1, float var2, float var3, float var4, int var5, IsoMovingObject var6, bool var7, bool var8) {
    // TODO: Implement lineClearCollide
    return false;
}

bool PolygonalMap2::lineClearCollide(float var1, float var2, float var3, float var4, int var5, IsoMovingObject var6, int var7) {
    // TODO: Implement lineClearCollide
    return false;
}

Vector2 PolygonalMap2::getCollidepoint(float var1, float var2, float var3, float var4, int var5, IsoMovingObject var6, int var7) {
    // TODO: Implement getCollidepoint
    return nullptr;
}

bool PolygonalMap2::canStandAt(float var1, float var2, int var3, IsoMovingObject var4, bool var5, bool var6) {
    // TODO: Implement canStandAt
    return false;
}

bool PolygonalMap2::canStandAt(float var1, float var2, int var3, BaseVehicle var4, int var5) {
    // TODO: Implement canStandAt
    return false;
}

bool PolygonalMap2::intersectLineWithVehicle(float var1, float var2, float var3, float var4, BaseVehicle var5, Vector2 var6) {
    // TODO: Implement intersectLineWithVehicle
    return false;
}

Vector2f PolygonalMap2::resolveCollision(IsoGameCharacter var1, float var2, float var3, Vector2f var4) {
    // TODO: Implement resolveCollision
    return nullptr;
}

} // namespace vehicles
} // namespace zombie
