#include "zombie/iso/areas/NonPvpZone.h"

namespace zombie {
namespace iso {
namespace areas {

public
NonPvpZone::NonPvpZone() {
  // TODO: Implement NonPvpZone
  return nullptr;
}

public
NonPvpZone::NonPvpZone(const std::string &_title, int _x, int _y, int _x2,
                       int _y2) {
  // TODO: Implement NonPvpZone
  return nullptr;
}

NonPvpZone NonPvpZone::addNonPvpZone(const std::string &_title, int _x, int _y,
                                     int _x2, int _y2) {
  // TODO: Implement addNonPvpZone
  return nullptr;
}

void NonPvpZone::removeNonPvpZone(const std::string &_title) {
  // TODO: Implement removeNonPvpZone
}

NonPvpZone NonPvpZone::getZoneByTitle(const std::string &_title) {
  // TODO: Implement getZoneByTitle
  return nullptr;
}

NonPvpZone NonPvpZone::getNonPvpZone(int _x, int _y) {
  // TODO: Implement getNonPvpZone
  return nullptr;
}

void NonPvpZone::syncNonPvpZone(bool remove) {
  // TODO: Implement syncNonPvpZone
}

void NonPvpZone::save(ByteBuffer output) {
  // TODO: Implement save
}

void NonPvpZone::load(ByteBuffer input, int WorldVersion) {
  // TODO: Implement load
}

int NonPvpZone::getX() {
  // TODO: Implement getX
  return 0;
}

void NonPvpZone::setX(int _x) {
  // TODO: Implement setX
}

int NonPvpZone::getY() {
  // TODO: Implement getY
  return 0;
}

void NonPvpZone::setY(int _y) {
  // TODO: Implement setY
}

int NonPvpZone::getX2() {
  // TODO: Implement getX2
  return 0;
}

void NonPvpZone::setX2(int _x2) {
  // TODO: Implement setX2
}

int NonPvpZone::getY2() {
  // TODO: Implement getY2
  return 0;
}

void NonPvpZone::setY2(int _y2) {
  // TODO: Implement setY2
}

std::string NonPvpZone::getTitle() {
  // TODO: Implement getTitle
  return "";
}

void NonPvpZone::setTitle(const std::string &_title) {
  // TODO: Implement setTitle
}

int NonPvpZone::getSize() {
  // TODO: Implement getSize
  return 0;
}

void NonPvpZone::setSize(int _size) {
  // TODO: Implement setSize
}

} // namespace areas
} // namespace iso
} // namespace zombie
