#include <string>
#include <vector>
#include "zombie\iso/IsoMetaGrid$Zone.h"

namespace zombie {
namespace iso {

void IsoMetaGrid$Zone::setX(int var1) {
    // TODO: Implement setX
}

void IsoMetaGrid$Zone::setY(int var1) {
    // TODO: Implement setY
}

void IsoMetaGrid$Zone::setW(int var1) {
    // TODO: Implement setW
}

void IsoMetaGrid$Zone::setH(int var1) {
    // TODO: Implement setH
}

bool IsoMetaGrid$Zone::isPoint() {
    // TODO: Implement isPoint
    return false;
}

bool IsoMetaGrid$Zone::isPolygon() {
    // TODO: Implement isPolygon
    return false;
}

bool IsoMetaGrid$Zone::isPolyline() {
    // TODO: Implement isPolyline
    return false;
}

bool IsoMetaGrid$Zone::isRectangle() {
    // TODO: Implement isRectangle
    return false;
}

void IsoMetaGrid$Zone::setPickedXForZoneStory(int var1) {
    // TODO: Implement setPickedXForZoneStory
}

void IsoMetaGrid$Zone::setPickedYForZoneStory(int var1) {
    // TODO: Implement setPickedYForZoneStory
}

float IsoMetaGrid$Zone::getHoursSinceLastSeen() {
    // TODO: Implement getHoursSinceLastSeen
    return 0;
}

void IsoMetaGrid$Zone::setHourSeenToCurrent() {
    // TODO: Implement setHourSeenToCurrent
}

void IsoMetaGrid$Zone::setHaveConstruction(bool var1) {
    // TODO: Implement setHaveConstruction
}

bool IsoMetaGrid$Zone::haveCons() {
    // TODO: Implement haveCons
    return false;
}

int IsoMetaGrid$Zone::getZombieDensity() {
    // TODO: Implement getZombieDensity
    return 0;
}

bool IsoMetaGrid$Zone::contains(int var1, int var2, int var3) {
    // TODO: Implement contains
    return false;
}

bool IsoMetaGrid$Zone::intersects(int var1, int var2, int var3, int var4, int var5) {
    // TODO: Implement intersects
    return false;
}

bool IsoMetaGrid$Zone::difference(int var1, int var2, int var3, int var4, int var5, std::vector<IsoMetaGrid$Zone> var6) {
    // TODO: Implement difference
    return false;
}

int IsoMetaGrid$Zone::pickRandomTriangle() {
    // TODO: Implement pickRandomTriangle
    return 0;
}

Vector2 IsoMetaGrid$Zone::pickRandomPointInTriangle(int var1, Vector2 var2) {
    // TODO: Implement pickRandomPointInTriangle
    return nullptr;
}

Location IsoMetaGrid$Zone::pickRandomLocation(Location var1) {
    // TODO: Implement pickRandomLocation
    return nullptr;
}

IsoGridSquare IsoMetaGrid$Zone::getRandomSquareInZone() {
    // TODO: Implement getRandomSquareInZone
    return nullptr;
}

IsoGridSquare IsoMetaGrid$Zone::getRandomUnseenSquareInZone() {
    // TODO: Implement getRandomUnseenSquareInZone
    return nullptr;
}

void IsoMetaGrid$Zone::addSquare(IsoGridSquare var1) {
    // TODO: Implement addSquare
}

void IsoMetaGrid$Zone::removeSquare(IsoGridSquare var1) {
    // TODO: Implement removeSquare
}

std::string IsoMetaGrid$Zone::getName() {
    // TODO: Implement getName
    return "";
}

void IsoMetaGrid$Zone::setName(const std::string& var1) {
    // TODO: Implement setName
}

std::string IsoMetaGrid$Zone::getType() {
    // TODO: Implement getType
    return "";
}

void IsoMetaGrid$Zone::setType(const std::string& var1) {
    // TODO: Implement setType
}

int IsoMetaGrid$Zone::getLastActionTimestamp() {
    // TODO: Implement getLastActionTimestamp
    return 0;
}

void IsoMetaGrid$Zone::setLastActionTimestamp(int var1) {
    // TODO: Implement setLastActionTimestamp
}

int IsoMetaGrid$Zone::getX() {
    // TODO: Implement getX
    return 0;
}

int IsoMetaGrid$Zone::getY() {
    // TODO: Implement getY
    return 0;
}

int IsoMetaGrid$Zone::getZ() {
    // TODO: Implement getZ
    return 0;
}

int IsoMetaGrid$Zone::getHeight() {
    // TODO: Implement getHeight
    return 0;
}

int IsoMetaGrid$Zone::getWidth() {
    // TODO: Implement getWidth
    return 0;
}

float IsoMetaGrid$Zone::getTotalArea() {
    // TODO: Implement getTotalArea
    return 0;
}

void IsoMetaGrid$Zone::sendToServer() {
    // TODO: Implement sendToServer
}

std::string IsoMetaGrid$Zone::getOriginalName() {
    // TODO: Implement getOriginalName
    return "";
}

void IsoMetaGrid$Zone::setOriginalName(const std::string& var1) {
    // TODO: Implement setOriginalName
}

int IsoMetaGrid$Zone::getClippedSegmentOfPolyline(int var1, int var2, int var3, int var4, double[] var5) {
    // TODO: Implement getClippedSegmentOfPolyline
    return 0;
}

void IsoMetaGrid$Zone::checkPolylineOutline() {
    // TODO: Implement checkPolylineOutline
}

float IsoMetaGrid$Zone::isLeft(float var1, float var2, float var3, float var4, float var5, float var6) {
    // TODO: Implement isLeft
    return 0;
}

PolygonHit IsoMetaGrid$Zone::isPointInPolygon_WindingNumber(float var1, float var2, int var3) {
    // TODO: Implement isPointInPolygon_WindingNumber
    return nullptr;
}

PolygonHit IsoMetaGrid$Zone::isPointInPolyline_WindingNumber(float var1, float var2, int var3) {
    // TODO: Implement isPointInPolyline_WindingNumber
    return nullptr;
}

bool IsoMetaGrid$Zone::polygonRectIntersect(int var1, int var2, int var3, int var4) {
    // TODO: Implement polygonRectIntersect
    return false;
}

bool IsoMetaGrid$Zone::lineSegmentIntersects(float var1, float var2, float var3, float var4) {
    // TODO: Implement lineSegmentIntersects
    return false;
}

bool IsoMetaGrid$Zone::polylineOutlineRectIntersect(int var1, int var2, int var3, int var4) {
    // TODO: Implement polylineOutlineRectIntersect
    return false;
}

bool IsoMetaGrid$Zone::polylineOutlineSegmentIntersects(float var1, float var2, float var3, float var4) {
    // TODO: Implement polylineOutlineSegmentIntersects
    return false;
}

bool IsoMetaGrid$Zone::isClockwise() {
    // TODO: Implement isClockwise
    return false;
}

float IsoMetaGrid$Zone::triangleArea(float var1, float var2, float var3, float var4, float var5, float var6) {
    // TODO: Implement triangleArea
    return 0;
}

void IsoMetaGrid$Zone::initTriangleAreas() {
    // TODO: Implement initTriangleAreas
}

float IsoMetaGrid$Zone::getPolylineLength() {
    // TODO: Implement getPolylineLength
    return 0;
}

void IsoMetaGrid$Zone::Dispose() {
    // TODO: Implement Dispose
}

} // namespace iso
} // namespace zombie
