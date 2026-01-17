#pragma once
#include "zombie/GameWindow.h"
#include "zombie/network/GameClient.h"
#include <cstdint>
#include <filesystem>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace iso {
namespace areas {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class NonPvpZone {
public:
  int x;
  int y;
  int x2;
  int y2;
  int size;
  std::string title;
public
  static final ArrayList<NonPvpZone> nonPvpZoneList =
      std::make_unique<ArrayList<>>();

public
  NonPvpZone() {}

public
  NonPvpZone(const std::string &_title, int _x, int _y, int _x2, int _y2) {
    if (_x > _x2) {
      int int0 = _x2;
      _x2 = _x;
      _x = int0;
    }

    if (_y > _y2) {
      int int1 = _y2;
      _y2 = _y;
      _y = int1;
    }

    this.setX(_x);
    this.setX2(_x2);
    this.setY(_y);
    this.setY2(_y2);
    this.title = _title;
    this.size = Math.abs(_x - _x2 + (_y - _y2));
  }

  static NonPvpZone addNonPvpZone(const std::string &_title, int _x, int _y,
                                  int _x2, int _y2) {
    NonPvpZone nonPvpZone = new NonPvpZone(_title, _x, _y, _x2, _y2);
    nonPvpZoneList.add(nonPvpZone);
    nonPvpZone.syncNonPvpZone(false);
    return nonPvpZone;
  }

  static void removeNonPvpZone(const std::string &_title) {
    NonPvpZone nonPvpZone = getZoneByTitle(_title);
    if (nonPvpZone != nullptr) {
      nonPvpZoneList.remove(nonPvpZone);
      nonPvpZone.syncNonPvpZone(true);
    }
  }

  static NonPvpZone getZoneByTitle(const std::string &_title) {
    for (int int0 = 0; int0 < nonPvpZoneList.size(); int0++) {
      NonPvpZone nonPvpZone = nonPvpZoneList.get(int0);
      if (nonPvpZone.getTitle() == _title)) {
    return nonPvpZone;
            }
    }

    return null;
  }

  static NonPvpZone getNonPvpZone(int _x, int _y) {
    for (int int0 = 0; int0 < nonPvpZoneList.size(); int0++) {
      NonPvpZone nonPvpZone = nonPvpZoneList.get(int0);
      if (_x >= nonPvpZone.getX() && _x < nonPvpZone.getX2() &&
          _y >= nonPvpZone.getY() && _y < nonPvpZone.getY2()) {
        return nonPvpZone;
      }
    }

    return null;
  }

public
  static ArrayList<NonPvpZone> getAllZones() { return nonPvpZoneList; }

  void syncNonPvpZone(bool remove) {
    if (GameClient.bClient) {
      GameClient.sendNonPvpZone(this, remove);
    }
  }

  void save(ByteBuffer output) {
    output.putInt(this.getX());
    output.putInt(this.getY());
    output.putInt(this.getX2());
    output.putInt(this.getY2());
    output.putInt(this.getSize());
    GameWindow.WriteString(output, this.getTitle());
  }

  void load(ByteBuffer input, int WorldVersion) {
    this.setX(input.getInt());
    this.setY(input.getInt());
    this.setX2(input.getInt());
    this.setY2(input.getInt());
    this.setSize(input.getInt());
    this.setTitle(GameWindow.ReadString(input));
  }

  int getX() { return this.x; }

  void setX(int _x) { this.x = _x; }

  int getY() { return this.y; }

  void setY(int _y) { this.y = _y; }

  int getX2() { return this.x2; }

  void setX2(int _x2) { this.x2 = _x2; }

  int getY2() { return this.y2; }

  void setY2(int _y2) { this.y2 = _y2; }

  std::string getTitle() { return this.title; }

  void setTitle(const std::string &_title) { this.title = _title; }

  int getSize() { return this.size; }

  void setSize(int _size) { this.size = _size; }
}
} // namespace areas
} // namespace iso
} // namespace zombie
