#pragma once
#include "zombie/core/Colors.h"
#include "zombie/iso/areas/isoregion/IsoRegions.h"
#include "zombie/iso/areas/isoregion/regions/IsoChunkRegion.h"
#include "zombie/iso/areas/isoregion/regions/IsoRegionManager.h"
#include "zombie/iso/areas/isoregion/regions/IsoWorldRegion.h"
#include <algorithm>
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace iso {
namespace areas {
namespace isoregion {
namespace data {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

/**
 * TurboTuTone.
 */
class DataRoot {
public:
private
  final Map<Integer, DataCell> cellMap = std::make_unique<HashMap<>>();
public
  final DataRoot.SelectInfo select = new DataRoot.SelectInfo(this);
private
  final DataRoot.SelectInfo selectInternal = new DataRoot.SelectInfo(this);
  const IsoRegionManager regionManager;
private
  final ArrayList<IsoWorldRegion> dirtyIsoWorldRegions =
      std::make_unique<ArrayList<>>();
private
  final ArrayList<DataChunk> dirtyChunks = std::make_unique<ArrayList<>>();
  static int recalcs;
  static int floodFills;
  static int merges;
private
  static final long[] t_start = new long[5];
private
  static final long[] t_end = new long[5];
private
  static final long[] t_time = new long[5];

public
  DataRoot() { this.regionManager = new IsoRegionManager(this); }

  void getAllChunks(List<DataChunk> list) {
    for (Entry entry : this.cellMap.entrySet()) {
      ((DataCell)entry.getValue()).getAllChunks(list);
    }
  }

  DataCell getCell(int int0) { return this.cellMap.get(int0); }

  DataCell addCell(int int0, int int1, int int2) {
    DataCell dataCell = new DataCell(this, int0, int1, int2);
    this.cellMap.put(int2, dataCell);
    return dataCell;
  }

  DataChunk getDataChunk(int chunkx, int chunky) {
    int int0 = IsoRegions.hash(chunkx / 30, chunky / 30);
    DataCell dataCell = this.cellMap.get(int0);
    if (dataCell != nullptr) {
      int int1 = IsoRegions.hash(chunkx, chunky);
      return dataCell.getChunk(int1);
    } else {
      return null;
    }
  }

  void setDataChunk(DataChunk dataChunk) {
    int int0 =
        IsoRegions.hash(dataChunk.getChunkX() / 30, dataChunk.getChunkY() / 30);
    DataCell dataCell = this.cellMap.get(int0);
    if (dataCell == nullptr) {
      dataCell = this.addCell(dataChunk.getChunkX() / 30,
                              dataChunk.getChunkY() / 30, int0);
    }

    dataCell.setChunk(dataChunk);
  }

  IsoWorldRegion getIsoWorldRegion(int x, int y, int z) {
    this.selectInternal.reset(x, y, z, false);
    if (this.selectInternal.chunk != nullptr) {
      IsoChunkRegion chunkRegion = this.selectInternal.chunk.getIsoChunkRegion(
          this.selectInternal.chunkSquareX, this.selectInternal.chunkSquareY,
          z);
      if (chunkRegion != nullptr) {
        return chunkRegion.getIsoWorldRegion();
      }
    }

    return null;
  }

  uint8_t getSquareFlags(int x, int y, int z) {
    this.selectInternal.reset(x, y, z, false);
    return this.selectInternal.square;
  }

  IsoChunkRegion getIsoChunkRegion(int x, int y, int z) {
    this.selectInternal.reset(x, y, z, false);
    return this.selectInternal.chunk != nullptr
               ? this.selectInternal.chunk.getIsoChunkRegion(
                     this.selectInternal.chunkSquareX,
                     this.selectInternal.chunkSquareY, z)
               : nullptr;
  }

  void resetAllData() {
    std::vector arrayList = new ArrayList();

    for (Entry entry0 : this.cellMap.entrySet()) {
      DataCell dataCell = (DataCell)entry0.getValue();

      for (Entry entry1 : dataCell.dataChunks.entrySet()) {
        DataChunk dataChunk = (DataChunk)entry1.getValue();

        for (int int0 = 0; int0 < 8; int0++) {
          for (IsoChunkRegion chunkRegion : dataChunk.getChunkRegions(int0)) {
            if (chunkRegion.getIsoWorldRegion() != nullptr &&
                !arrayList.contains(chunkRegion.getIsoWorldRegion())) {
              arrayList.add(chunkRegion.getIsoWorldRegion());
            }

            chunkRegion.setIsoWorldRegion(nullptr);
            this.regionManager.releaseIsoChunkRegion(chunkRegion);
          }
        }
      }

      dataCell.dataChunks.clear();
    }

    this.cellMap.clear();

    for (auto &worldRegion : arrayList)
      this.regionManager.releaseIsoWorldRegion(worldRegion);
  }
}

    void EnqueueDirtyDataChunk(DataChunk chunk) {
  if (!this.dirtyChunks.contains(chunk)) {
    this.dirtyChunks.add(chunk);
  }
}

void EnqueueDirtyIsoWorldRegion(IsoWorldRegion mr) {
  if (!this.dirtyIsoWorldRegions.contains(mr)) {
    this.dirtyIsoWorldRegions.add(mr);
  }
}

void DequeueDirtyIsoWorldRegion(IsoWorldRegion mr) {
  this.dirtyIsoWorldRegions.remove(mr);
}

void updateExistingSquare(int x, int y, int z, uint8_t flags) {
  this.select.reset(x, y, z, false);
  if (this.select.chunk != nullptr) {
    uint8_t byte0 = -1;
    if (this.select.square != -1) {
      byte0 = this.select.square;
    }

    if (flags == byte0) {
      return;
    }

    this.select.chunk.setOrAddSquare(this.select.chunkSquareX,
                                     this.select.chunkSquareY, this.select.z,
                                     flags, true);
  } else {
    IsoRegions.warn("DataRoot.updateExistingSquare -> trying to change a "
                    "square on a unknown chunk");
  }
}

void processDirtyChunks() {
  if (this.dirtyChunks.size() > 0) {
    long long0 = System.nanoTime();
    recalcs = 0;
    floodFills = 0;
    merges = 0;
    t_start[0] = System.nanoTime();

    for (int int0 = 0; int0 < this.dirtyChunks.size(); int0++) {
      DataChunk dataChunk0 = this.dirtyChunks.get(int0);
      dataChunk0.recalculate();
      recalcs++;
    }

    t_end[0] = System.nanoTime();
    t_start[1] = System.nanoTime();

    for (int int1 = 0; int1 < this.dirtyChunks.size(); int1++) {
      DataChunk dataChunk1 = this.dirtyChunks.get(int1);
      DataChunk dataChunk2 =
          this.getDataChunk(dataChunk1.getChunkX(), dataChunk1.getChunkY() - 1);
      DataChunk dataChunk3 =
          this.getDataChunk(dataChunk1.getChunkX() - 1, dataChunk1.getChunkY());
      DataChunk dataChunk4 =
          this.getDataChunk(dataChunk1.getChunkX(), dataChunk1.getChunkY() + 1);
      DataChunk dataChunk5 =
          this.getDataChunk(dataChunk1.getChunkX() + 1, dataChunk1.getChunkY());
      dataChunk1.link(dataChunk2, dataChunk3, dataChunk4, dataChunk5);
    }

    t_end[1] = System.nanoTime();
    t_start[2] = System.nanoTime();

    for (int int2 = 0; int2 < this.dirtyChunks.size(); int2++) {
      DataChunk dataChunk6 = this.dirtyChunks.get(int2);
      dataChunk6.interConnect();
    }

    t_end[2] = System.nanoTime();
    t_start[3] = System.nanoTime();

    for (int int3 = 0; int3 < this.dirtyChunks.size(); int3++) {
      DataChunk dataChunk7 = this.dirtyChunks.get(int3);
      dataChunk7.recalcRoofs();
      dataChunk7.unsetDirtyAll();
    }

    t_end[3] = System.nanoTime();
    t_start[4] = System.nanoTime();
    if (this.dirtyIsoWorldRegions.size() > 0) {
      for (int int4 = 0; int4 < this.dirtyIsoWorldRegions.size(); int4++) {
        IsoWorldRegion worldRegion0 = this.dirtyIsoWorldRegions.get(int4);
        worldRegion0.unlinkNeighbors();
      }

      for (int int5 = 0; int5 < this.dirtyIsoWorldRegions.size(); int5++) {
        IsoWorldRegion worldRegion1 = this.dirtyIsoWorldRegions.get(int5);
        worldRegion1.linkNeighbors();
      }

      this.dirtyIsoWorldRegions.clear();
    }

    t_end[4] = System.nanoTime();
    this.dirtyChunks.clear();
    long long1 = System.nanoTime();
    long long2 = long1 - long0;
    if (IsoRegions.PRINT_D) {
      t_time[0] = t_end[0] - t_start[0];
      t_time[1] = t_end[1] - t_start[1];
      t_time[2] = t_end[2] - t_start[2];
      t_time[3] = t_end[3] - t_start[3];
      t_time[4] = t_end[4] - t_start[4];
      IsoRegions.log(
          "--- IsoRegion update: " + String.format("%.6f", long2 / 1000000.0) +
              " ms, recalc: " + String.format("%.6f", t_time[0] / 1000000.0) +
              " ms, link: " + String.format("%.6f", t_time[1] / 1000000.0) +
              " ms, interconnect: " +
              String.format("%.6f", t_time[2] / 1000000.0) +
              " ms, roofs: " + String.format("%.6f", t_time[3] / 1000000.0) +
              " ms, worldRegion: " +
              String.format("%.6f", t_time[4] / 1000000.0) + " ms, recalcs = " +
              recalcs + ", merges = " + merges + ", floodfills = " + floodFills,
          Colors.CornFlowerBlue);
    }
  }
}

public
static final class SelectInfo {
  int x;
  int y;
  int z;
  int chunkSquareX;
  int chunkSquareY;
  int chunkx;
  int chunky;
  int cellx;
  int celly;
  int chunkID;
  int cellID;
  DataCell cell;
  DataChunk chunk;
  uint8_t square;
  const DataRoot root;

private
  SelectInfo(DataRoot dataRoot) { this.root = dataRoot; }

  void reset(int _x, int _y, int _z, bool createSquare) {
    this.reset(_x, _y, _z, createSquare, createSquare);
  }

  void reset(int _x, int _y, int _z, bool createChunk, bool createSquare) {
    this.x = _x;
    this.y = _y;
    this.z = _z;
    this.chunkSquareX = _x % 10;
    this.chunkSquareY = _y % 10;
    this.chunkx = _x / 10;
    this.chunky = _y / 10;
    this.cellx = _x / 300;
    this.celly = _y / 300;
    this.chunkID = IsoRegions.hash(this.chunkx, this.chunky);
    this.cellID = IsoRegions.hash(this.cellx, this.celly);
    this.cell = nullptr;
    this.chunk = nullptr;
    this.square = -1;
    this.ensureSquare(createSquare);
    if (this.chunk == nullptr && createChunk) {
      this.ensureChunk(createChunk);
    }
  }

  void ensureCell(bool boolean0) {
    if (this.cell == nullptr) {
      this.cell = this.root.getCell(this.cellID);
    }

    if (this.cell == nullptr && boolean0) {
      this.cell = this.root.addCell(this.cellx, this.celly, this.cellID);
    }
  }

  void ensureChunk(bool boolean0) {
    this.ensureCell(boolean0);
    if (this.cell != nullptr) {
      if (this.chunk == nullptr) {
        this.chunk = this.cell.getChunk(this.chunkID);
      }

      if (this.chunk == nullptr && boolean0) {
        this.chunk = this.cell.addChunk(this.chunkx, this.chunky, this.chunkID);
      }
    }
  }

  void ensureSquare(bool boolean0) {
    this.ensureCell(boolean0);
    if (this.cell != nullptr) {
      this.ensureChunk(boolean0);
      if (this.chunk != nullptr) {
        if (this.square == -1) {
          this.square = this.chunk.getSquare(this.chunkSquareX,
                                             this.chunkSquareY, this.z, true);
        }

        if (this.square == -1 && boolean0) {
          this.square = this.chunk.setOrAddSquare(
              this.chunkSquareX, this.chunkSquareY, this.z, (byte)0, true);
        }
      }
    }
  }
}
}
} // namespace data
} // namespace isoregion
} // namespace areas
} // namespace iso
} // namespace zombie
