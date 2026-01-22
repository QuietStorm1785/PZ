#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/iso/areas/isoregion/IsoRegions.h"

namespace zombie {
namespace iso {
namespace areas {
namespace isoregion {
namespace data {


class DataRoot {
public:
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

   private DataRoot$SelectInfo(DataRoot var1) {
      this.root = var1;
   }

    void reset(int var1, int var2, int var3, bool var4) {
      this.reset(var1, var2, var3, var4, var4);
   }

    void reset(int var1, int var2, int var3, bool var4, bool var5) {
      this.x = var1;
      this.y = var2;
      this.z = var3;
      this.chunkSquareX = var1 % 10;
      this.chunkSquareY = var2 % 10;
      this.chunkx = var1 / 10;
      this.chunky = var2 / 10;
      this.cellx = var1 / 300;
      this.celly = var2 / 300;
      this.chunkID = IsoRegions.hash(this.chunkx, this.chunky);
      this.cellID = IsoRegions.hash(this.cellx, this.celly);
      this.cell = nullptr;
      this.chunk = nullptr;
      this.square = -1;
      this.ensureSquare(var5);
      if (this.chunk == nullptr && var4) {
         this.ensureChunk(var4);
      }
   }

    void ensureCell(bool var1) {
      if (this.cell == nullptr) {
         this.cell = this.root.getCell(this.cellID);
      }

      if (this.cell == nullptr && var1) {
         this.cell = this.root.addCell(this.cellx, this.celly, this.cellID);
      }
   }

    void ensureChunk(bool var1) {
      this.ensureCell(var1);
      if (this.cell != nullptr) {
         if (this.chunk == nullptr) {
            this.chunk = this.cell.getChunk(this.chunkID);
         }

         if (this.chunk == nullptr && var1) {
            this.chunk = this.cell.addChunk(this.chunkx, this.chunky, this.chunkID);
         }
      }
   }

    void ensureSquare(bool var1) {
      this.ensureCell(var1);
      if (this.cell != nullptr) {
         this.ensureChunk(var1);
         if (this.chunk != nullptr) {
            if (this.square == -1) {
               this.square = this.chunk.getSquare(this.chunkSquareX, this.chunkSquareY, this.z, true);
            }

            if (this.square == -1 && var1) {
               this.square = this.chunk.setOrAddSquare(this.chunkSquareX, this.chunkSquareY, this.z, (byte)0, true);
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
