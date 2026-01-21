#include <vector>
#include "zombie/vehicles/PolygonalMap2$Obstacle.h"

namespace zombie {
namespace vehicles {

bool PolygonalMap2$Obstacle::hasNode(Node var1) {
    // TODO: Implement hasNode
    return false;
}

bool PolygonalMap2$Obstacle::hasAdjacentNodes(Node var1, Node var2) {
    // TODO: Implement hasAdjacentNodes
    return false;
}

bool PolygonalMap2$Obstacle::isPointInside(float var1, float var2, int var3) {
    // TODO: Implement isPointInside
    return false;
}

bool PolygonalMap2$Obstacle::isPointInside(float var1, float var2) {
    // TODO: Implement isPointInside
    return false;
}

bool PolygonalMap2$Obstacle::lineSegmentIntersects(float var1, float var2, float var3, float var4) {
    // TODO: Implement lineSegmentIntersects
    return false;
}

bool PolygonalMap2$Obstacle::isNodeInsideOf(Node var1) {
    // TODO: Implement isNodeInsideOf
    return false;
}

void PolygonalMap2$Obstacle::getClosestPointOnEdge(float var1, float var2, ClosestPointOnEdge var3) {
    // TODO: Implement getClosestPointOnEdge
}

bool PolygonalMap2$Obstacle::splitEdgeAtNearestPoint(ClosestPointOnEdge var1, int var2, AdjustStartEndNodeData var3) {
    // TODO: Implement splitEdgeAtNearestPoint
    return false;
}

void PolygonalMap2$Obstacle::unsplit(Node var1, std::vector<Edge> var2) {
    // TODO: Implement unsplit
}

void PolygonalMap2$Obstacle::calcBounds() {
    // TODO: Implement calcBounds
}

void PolygonalMap2$Obstacle::render(std::vector<Edge> var1, bool var2) {
    // TODO: Implement render
}

void PolygonalMap2$Obstacle::render() {
    // TODO: Implement render
}

void PolygonalMap2$Obstacle::connectCrawlNodes(VisibilityGraph var1, PolygonalMap2$Obstacle var2) {
    // TODO: Implement connectCrawlNodes
}

void PolygonalMap2$Obstacle::connectCrawlNode(VisibilityGraph var1, PolygonalMap2$Obstacle var2, Node var3, Node var4) {
    // TODO: Implement connectCrawlNode
}

Node PolygonalMap2$Obstacle::getClosestInteriorCrawlNode(float var1, float var2) {
    // TODO: Implement getClosestInteriorCrawlNode
    return nullptr;
}

void PolygonalMap2$Obstacle::release() {
    // TODO: Implement release
}

void PolygonalMap2$Obstacle::releaseAll(std::vector<PolygonalMap2$Obstacle> var0) {
    // TODO: Implement releaseAll
}

} // namespace vehicles
} // namespace zombie
