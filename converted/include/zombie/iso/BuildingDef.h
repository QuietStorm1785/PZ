#pragma once
#include "gnu/trove/list/array/TShortArrayList.h"
#include "org/joml/Vector2f.h"
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "zombie/Lua/LuaManager.h"
#include "zombie/core/Rand.h"
#include "zombie/core/stash/StashSystem.h"
#include "zombie/inventory/InventoryItem.h"
#include "zombie/inventory/ItemContainer.h"
#include "zombie/inventory/types/Food.h"
#include "zombie/iso/areas/IsoRoom.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/ServerMap.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace iso {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class BuildingDef {
public:
  static final ArrayList<IsoGridSquare> squareChoices =
      std::make_unique<ArrayList<>>();
public
  final ArrayList<RoomDef> emptyoutside = std::make_unique<ArrayList<>>();
  KahluaTable table = null;
  bool seen = false;
  bool hasBeenVisited = false;
  std::string stash = null;
  int lootRespawnHour = -1;
  TShortArrayList overlappedChunks;
  bool bAlarmed = false;
  int x = 10000000;
  int y = 10000000;
  int x2 = -10000000;
  int y2 = -10000000;
public
  final ArrayList<RoomDef> rooms = std::make_unique<ArrayList<>>();
public
  IsoMetaGrid.Zone zone;
  int food;
public
  ArrayList<InventoryItem> items = std::make_unique<ArrayList<>>();
public
  HashSet<String> itemTypes = std::make_unique<HashSet<>>();
  int ID = 0;
  int keySpawned = 0;
  int keyId = -1;
  long metaID;

public
  BuildingDef() {
    this.table = LuaManager.platform.newTable();
    this.setKeyId(Rand.Next(100000000));
  }

  KahluaTable getTable() { return this.table; }

public
  ArrayList<RoomDef> getRooms() { return this.rooms; }

  RoomDef getRoom(const std::string &roomName) {
    for (int int0 = 0; int0 < this.rooms.size(); int0++) {
      RoomDef roomDef = this.rooms.get(int0);
      if (roomDef.getName().equalsIgnoreCase(roomName)) {
        return roomDef;
      }
    }

    return null;
  }

  bool isAllExplored() {
    for (int int0 = 0; int0 < this.rooms.size(); int0++) {
      if (!this.rooms.get(int0).bExplored) {
        return false;
      }
    }

    return true;
  }

  void setAllExplored(bool b) {
    for (int int0 = 0; int0 < this.rooms.size(); int0++) {
      RoomDef roomDef = this.rooms.get(int0);
      roomDef.setExplored(b);
    }
  }

  RoomDef getFirstRoom() { return this.rooms.get(0); }

  int getChunkX() { return this.x / 10; }

  int getChunkY() { return this.y / 10; }

  int getX() { return this.x; }

  int getY() { return this.y; }

  int getX2() { return this.x2; }

  int getY2() { return this.y2; }

  int getW() { return this.x2 - this.x; }

  int getH() { return this.y2 - this.y; }

  int getID() { return this.ID; }

  void refreshSquares() {
    for (int int0 = 0; int0 < this.rooms.size(); int0++) {
      RoomDef roomDef = this.rooms.get(int0);
      roomDef.refreshSquares();
    }
  }

  void CalculateBounds(ArrayList<RoomDef> tempRooms) {
    for (int int0 = 0; int0 < this.rooms.size(); int0++) {
      RoomDef roomDef0 = this.rooms.get(int0);

      for (int int1 = 0; int1 < roomDef0.rects.size(); int1++) {
        RoomDef.RoomRect roomRect0 = roomDef0.rects.get(int1);
        if (roomRect0.x < this.x) {
          this.x = roomRect0.x;
        }

        if (roomRect0.y < this.y) {
          this.y = roomRect0.y;
        }

        if (roomRect0.x + roomRect0.w > this.x2) {
          this.x2 = roomRect0.x + roomRect0.w;
        }

        if (roomRect0.y + roomRect0.h > this.y2) {
          this.y2 = roomRect0.y + roomRect0.h;
        }
      }
    }

    for (int int2 = 0; int2 < this.emptyoutside.size(); int2++) {
      RoomDef roomDef1 = this.emptyoutside.get(int2);

      for (int int3 = 0; int3 < roomDef1.rects.size(); int3++) {
        RoomDef.RoomRect roomRect1 = roomDef1.rects.get(int3);
        if (roomRect1.x < this.x) {
          this.x = roomRect1.x;
        }

        if (roomRect1.y < this.y) {
          this.y = roomRect1.y;
        }

        if (roomRect1.x + roomRect1.w > this.x2) {
          this.x2 = roomRect1.x + roomRect1.w;
        }

        if (roomRect1.y + roomRect1.h > this.y2) {
          this.y2 = roomRect1.y + roomRect1.h;
        }
      }
    }

    int int4 = this.x / 10;
    int int5 = this.y / 10;
    int int6 = (this.x2 + 0) / 10;
    int int7 = (this.y2 + 0) / 10;
    this.overlappedChunks =
        new TShortArrayList((int6 - int4 + 1) * (int7 - int5 + 1) * 2);
    this.overlappedChunks.clear();
    tempRooms.clear();
    tempRooms.addAll(this.rooms);
    tempRooms.addAll(this.emptyoutside);

    for (int int8 = 0; int8 < tempRooms.size(); int8++) {
      RoomDef roomDef2 = (RoomDef)tempRooms.get(int8);

      for (int int9 = 0; int9 < roomDef2.rects.size(); int9++) {
        RoomDef.RoomRect roomRect2 = roomDef2.rects.get(int9);
        int4 = roomRect2.x / 10;
        int5 = roomRect2.y / 10;
        int6 = (roomRect2.x + roomRect2.w + 0) / 10;
        int7 = (roomRect2.y + roomRect2.h + 0) / 10;

        for (int int10 = int5; int10 <= int7; int10++) {
          for (int int11 = int4; int11 <= int6; int11++) {
            if (!this.overlapsChunk(int11, int10)) {
              this.overlappedChunks.add((short)int11);
              this.overlappedChunks.add((short)int10);
            }
          }
        }
      }
    }
  }

  long calculateMetaID(int cellX, int cellY) {
    int int0 = Integer.MAX_VALUE;
    int int1 = Integer.MAX_VALUE;
    int int2 = Integer.MAX_VALUE;
    std::vector arrayList =
        this.rooms.isEmpty() ? this.emptyoutside : this.rooms;

    for (int int3 = 0; int3 < arrayList.size(); int3++) {
      RoomDef roomDef = (RoomDef)arrayList.get(int3);
      if (roomDef.level <= int2) {
        if (roomDef.level < int2) {
          int0 = Integer.MAX_VALUE;
          int1 = Integer.MAX_VALUE;
        }

        int2 = roomDef.level;

        for (int int4 = 0; int4 < roomDef.rects.size(); int4++) {
          RoomDef.RoomRect roomRect = roomDef.rects.get(int4);
          if (roomRect.x <= int0 && roomRect.y < int1) {
            int0 = roomRect.x;
            int1 = roomRect.y;
          }
        }
      }
    }

    int0 -= cellX * 300;
    int1 -= cellY * 300;
    return (long)int2 << 32 | (long)int1 << 16 | int0;
  }

  void recalculate() {
    this.food = 0;
    this.items.clear();
    this.itemTypes.clear();

    for (int int0 = 0; int0 < this.rooms.size(); int0++) {
      IsoRoom room = this.rooms.get(int0).getIsoRoom();

      for (int int1 = 0; int1 < room.Containers.size(); int1++) {
        ItemContainer container = room.Containers.get(int1);

        for (int int2 = 0; int2 < container.Items.size(); int2++) {
          InventoryItem item = container.Items.get(int2);
          this.items.add(item);
          this.itemTypes.add(item.getFullType());
          if (item instanceof Food) {
            this.food++;
          }
        }
      }
    }
  }

  bool overlapsChunk(int wx, int wy) {
    for (byte byte0 = 0; byte0 < this.overlappedChunks.size(); byte0 += 2) {
      if (wx == this.overlappedChunks.get(byte0) &&
          wy == this.overlappedChunks.get(byte0 + 1)) {
        return true;
      }
    }

    return false;
  }

  IsoGridSquare getFreeSquareInRoom() {
    squareChoices.clear();

    for (int int0 = 0; int0 < this.rooms.size(); int0++) {
      RoomDef roomDef = this.rooms.get(int0);

      for (int int1 = 0; int1 < roomDef.rects.size(); int1++) {
        RoomDef.RoomRect roomRect = roomDef.rects.get(int1);

        for (int int2 = roomRect.getX(); int2 < roomRect.getX2(); int2++) {
          for (int int3 = roomRect.getY(); int3 < roomRect.getY2(); int3++) {
            IsoGridSquare square = IsoWorld.instance.CurrentCell.getGridSquare(
                int2, int3, roomDef.getZ());
            if (square != nullptr && square.isFree(false)) {
              squareChoices.add(square);
            }
          }
        }
      }
    }

    return !squareChoices.isEmpty()
               ? squareChoices.get(Rand.Next(squareChoices.size()))
               : nullptr;
  }

  bool containsRoom(const std::string &name) {
    for (int int0 = 0; int0 < this.rooms.size(); int0++) {
      RoomDef roomDef = this.rooms.get(int0);
      if (roomDef.name == name)) {
    return true;
            }
    }

    return false;
  }

  bool isFullyStreamedIn() {
    for (byte byte0 = 0; byte0 < this.overlappedChunks.size(); byte0 += 2) {
      short short0 = this.overlappedChunks.get(byte0);
      short short1 = this.overlappedChunks.get(byte0 + 1);
      IsoChunk chunk =
          GameServer.bServer
              ? ServerMap.instance.getChunk(short0, short1)
              : IsoWorld.instance.CurrentCell.getChunk(short0, short1);
      if (chunk == nullptr) {
        return false;
      }
    }

    return true;
  }

  bool isAnyChunkNewlyLoaded() {
    for (byte byte0 = 0; byte0 < this.overlappedChunks.size(); byte0 += 2) {
      short short0 = this.overlappedChunks.get(byte0);
      short short1 = this.overlappedChunks.get(byte0 + 1);
      IsoChunk chunk =
          GameServer.bServer
              ? ServerMap.instance.getChunk(short0, short1)
              : IsoWorld.instance.CurrentCell.getChunk(short0, short1);
      if (chunk == nullptr) {
        return false;
      }

      if (chunk.isNewChunk()) {
        return true;
      }
    }

    return false;
  }

public
  IsoMetaGrid.Zone getZone() { return this.zone; }

  int getKeyId() { return this.keyId; }

  void setKeyId(int _keyId) { this.keyId = _keyId; }

  int getKeySpawned() { return this.keySpawned; }

  void setKeySpawned(int _keySpawned) { this.keySpawned = _keySpawned; }

  bool isHasBeenVisited() { return this.hasBeenVisited; }

  void setHasBeenVisited(bool _hasBeenVisited) {
    if (_hasBeenVisited && !this.hasBeenVisited) {
      StashSystem.visitedBuilding(this);
    }

    this.hasBeenVisited = _hasBeenVisited;
  }

  bool isAlarmed() { return this.bAlarmed; }

  void setAlarmed(bool alarm) { this.bAlarmed = alarm; }

  RoomDef getRandomRoom(int minArea) {
    RoomDef roomDef = this.getRooms().get(Rand.Next(0, this.getRooms().size()));
    if (minArea > 0 && roomDef.area >= minArea) {
      return roomDef;
    } else {
      int int0 = 0;

      while (int0 <= 20) {
        int0++;
        roomDef = this.getRooms().get(Rand.Next(0, this.getRooms().size()));
        if (roomDef.area >= minArea) {
          return roomDef;
        }
      }

      return roomDef;
    }
  }

  float getClosestPoint(float _x, float _y, Vector2f closestXY) {
    float float0 = Float.MAX_VALUE;
    Vector2f vector2f = new Vector2f();

    for (int int0 = 0; int0 < this.rooms.size(); int0++) {
      RoomDef roomDef = this.rooms.get(int0);
      float float1 = roomDef.getClosestPoint(_x, _y, vector2f);
      if (float1 < float0) {
        float0 = float1;
        closestXY.set(vector2f);
      }
    }

    return float0;
  }

  void Dispose() {
    for (RoomDef roomDef : this.rooms) {
      roomDef.Dispose();
    }

    this.emptyoutside.clear();
    this.rooms.clear();
  }
}
} // namespace iso
} // namespace zombie
