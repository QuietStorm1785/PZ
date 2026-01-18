#include "zombie/iso/IsoMarkers.h"

namespace zombie {
namespace iso {

private
IsoMarkers::IsoMarkers() {
 // TODO: Implement IsoMarkers
 return nullptr;
}

void IsoMarkers::init() {
 // TODO: Implement init
}

void IsoMarkers::reset() {
 // TODO: Implement reset
}

void IsoMarkers::update() {
 // TODO: Implement update
}

void IsoMarkers::updateIsoMarkers() {
 // TODO: Implement updateIsoMarkers
}

bool IsoMarkers::removeIsoMarker(IsoMarkers.IsoMarker marker) {
 // TODO: Implement removeIsoMarker
 return false;
}

bool IsoMarkers::removeIsoMarker(int id) {
 // TODO: Implement removeIsoMarker
 return false;
}

void IsoMarkers::renderIsoMarkers(IsoCell.PerPlayerRender perPlayerRender,
 int zLayer, int playerIndex) {
 // TODO: Implement renderIsoMarkers
}

void IsoMarkers::renderIsoMarkersDeferred(
 IsoCell.PerPlayerRender perPlayerRender, int zLayer, int playerIndex) {
 // TODO: Implement renderIsoMarkersDeferred
}

void IsoMarkers::renderIsoMarkersOnSquare(
 IsoCell.PerPlayerRender perPlayerRender, int zLayer, int playerIndex) {
 // TODO: Implement renderIsoMarkersOnSquare
}

void IsoMarkers::updateCircleIsoMarkers() {
 // TODO: Implement updateCircleIsoMarkers
}

bool IsoMarkers::removeCircleIsoMarker(IsoMarkers.CircleIsoMarker marker) {
 // TODO: Implement removeCircleIsoMarker
 return false;
}

bool IsoMarkers::removeCircleIsoMarker(int id) {
 // TODO: Implement removeCircleIsoMarker
 return false;
}

void IsoMarkers::renderCircleIsoMarkers(IsoCell.PerPlayerRender perPlayerRender,
 int zLayer, int playerIndex) {
 // TODO: Implement renderCircleIsoMarkers
}

void IsoMarkers::render() {
 // TODO: Implement render
}

public
IsoMarkers::CircleIsoMarker() {
 // TODO: Implement CircleIsoMarker
 return nullptr;
}

int IsoMarkers::getID() {
 // TODO: Implement getID
 return 0;
}

void IsoMarkers::remove() {
 // TODO: Implement remove
}

bool IsoMarkers::isRemoved() {
 // TODO: Implement isRemoved
 return false;
}

void IsoMarkers::init(int _x, int _y, int _z, IsoGridSquare gs) {
 // TODO: Implement init
}

float IsoMarkers::getX() {
 // TODO: Implement getX
 return 0;
}

float IsoMarkers::getY() {
 // TODO: Implement getY
 return 0;
}

float IsoMarkers::getZ() {
 // TODO: Implement getZ
 return 0;
}

float IsoMarkers::getR() {
 // TODO: Implement getR
 return 0;
}

float IsoMarkers::getG() {
 // TODO: Implement getG
 return 0;
}

float IsoMarkers::getB() {
 // TODO: Implement getB
 return 0;
}

float IsoMarkers::getA() {
 // TODO: Implement getA
 return 0;
}

void IsoMarkers::setR(float _r) {
 // TODO: Implement setR
}

void IsoMarkers::setG(float _g) {
 // TODO: Implement setG
}

void IsoMarkers::setB(float _b) {
 // TODO: Implement setB
}

void IsoMarkers::setA(float _a) {
 // TODO: Implement setA
}

float IsoMarkers::getSize() {
 // TODO: Implement getSize
 return 0;
}

void IsoMarkers::setSize(float _size) {
 // TODO: Implement setSize
}

float IsoMarkers::getAlpha() {
 // TODO: Implement getAlpha
 return 0;
}

void IsoMarkers::setAlpha(float _alpha) {
 // TODO: Implement setAlpha
}

float IsoMarkers::getAlphaMax() {
 // TODO: Implement getAlphaMax
 return 0;
}

void IsoMarkers::setAlphaMax(float _alphaMax) {
 // TODO: Implement setAlphaMax
}

float IsoMarkers::getAlphaMin() {
 // TODO: Implement getAlphaMin
 return 0;
}

void IsoMarkers::setAlphaMin(float _alphaMin) {
 // TODO: Implement setAlphaMin
}

bool IsoMarkers::isDoAlpha() {
 // TODO: Implement isDoAlpha
 return false;
}

void IsoMarkers::setDoAlpha(bool _doAlpha) {
 // TODO: Implement setDoAlpha
}

float IsoMarkers::getFadeSpeed() {
 // TODO: Implement getFadeSpeed
 return 0;
}

void IsoMarkers::setFadeSpeed(float _fadeSpeed) {
 // TODO: Implement setFadeSpeed
}

IsoGridSquare IsoMarkers::getSquare() {
 // TODO: Implement getSquare
 return nullptr;
}

void IsoMarkers::setSquare(IsoGridSquare _square) {
 // TODO: Implement setSquare
}

void IsoMarkers::setPos(int _x, int _y, int _z) {
 // TODO: Implement setPos
}

bool IsoMarkers::isActive() {
 // TODO: Implement isActive
 return false;
}

void IsoMarkers::setActive(bool _active) {
 // TODO: Implement setActive
}

public
IsoMarkers::IsoMarker() {
 // TODO: Implement IsoMarker
 return nullptr;
}

int IsoMarkers::getID() {
 // TODO: Implement getID
 return 0;
}

void IsoMarkers::remove() {
 // TODO: Implement remove
}

bool IsoMarkers::isRemoved() {
 // TODO: Implement isRemoved
 return false;
}

void IsoMarkers::init(KahluaTable textureTable, KahluaTable textureOverlayTable,
 int _x, int _y, int _z, IsoGridSquare gs) {
 // TODO: Implement init
}

void IsoMarkers::init(KahluaTable textureTable, KahluaTable textureOverlayTable,
 int _x, int _y, int _z, IsoGridSquare gs,
 bool doTempIsoObject) {
 // TODO: Implement init
}

void IsoMarkers::init(const std::string &spriteName, int _x, int _y, int _z,
 IsoGridSquare gs, bool doTempIsoObject) {
 // TODO: Implement init
}

bool IsoMarkers::hasTempSquareObject() {
 // TODO: Implement hasTempSquareObject
 return false;
}

void IsoMarkers::addTempSquareObject(IsoObject tempObject) {
 // TODO: Implement addTempSquareObject
}

void IsoMarkers::removeTempSquareObjects() {
 // TODO: Implement removeTempSquareObjects
}

float IsoMarkers::getX() {
 // TODO: Implement getX
 return 0;
}

float IsoMarkers::getY() {
 // TODO: Implement getY
 return 0;
}

float IsoMarkers::getZ() {
 // TODO: Implement getZ
 return 0;
}

float IsoMarkers::getR() {
 // TODO: Implement getR
 return 0;
}

float IsoMarkers::getG() {
 // TODO: Implement getG
 return 0;
}

float IsoMarkers::getB() {
 // TODO: Implement getB
 return 0;
}

float IsoMarkers::getA() {
 // TODO: Implement getA
 return 0;
}

void IsoMarkers::setR(float _r) {
 // TODO: Implement setR
}

void IsoMarkers::setG(float _g) {
 // TODO: Implement setG
}

void IsoMarkers::setB(float _b) {
 // TODO: Implement setB
}

void IsoMarkers::setA(float _a) {
 // TODO: Implement setA
}

float IsoMarkers::getAlpha() {
 // TODO: Implement getAlpha
 return 0;
}

void IsoMarkers::setAlpha(float _alpha) {
 // TODO: Implement setAlpha
}

float IsoMarkers::getAlphaMax() {
 // TODO: Implement getAlphaMax
 return 0;
}

void IsoMarkers::setAlphaMax(float _alphaMax) {
 // TODO: Implement setAlphaMax
}

float IsoMarkers::getAlphaMin() {
 // TODO: Implement getAlphaMin
 return 0;
}

void IsoMarkers::setAlphaMin(float _alphaMin) {
 // TODO: Implement setAlphaMin
}

bool IsoMarkers::isDoAlpha() {
 // TODO: Implement isDoAlpha
 return false;
}

void IsoMarkers::setDoAlpha(bool _doAlpha) {
 // TODO: Implement setDoAlpha
}

float IsoMarkers::getFadeSpeed() {
 // TODO: Implement getFadeSpeed
 return 0;
}

void IsoMarkers::setFadeSpeed(float _fadeSpeed) {
 // TODO: Implement setFadeSpeed
}

IsoGridSquare IsoMarkers::getSquare() {
 // TODO: Implement getSquare
 return nullptr;
}

void IsoMarkers::setSquare(IsoGridSquare _square) {
 // TODO: Implement setSquare
}

void IsoMarkers::setPos(int _x, int _y, int _z) {
 // TODO: Implement setPos
}

bool IsoMarkers::isActive() {
 // TODO: Implement isActive
 return false;
}

void IsoMarkers::setActive(bool _active) {
 // TODO: Implement setActive
}

} // namespace iso
} // namespace zombie
