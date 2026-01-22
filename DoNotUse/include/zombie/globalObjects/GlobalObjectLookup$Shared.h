#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/globalObjects/GlobalObjectLookup/Cell.h"
#include "zombie/iso/IsoMetaGrid.h"

namespace zombie {
namespace globalObjects {


class GlobalObjectLookup {
public:
   Cell[] cells;

   private GlobalObjectLookup$Shared() {
   }

    void init(IsoMetaGrid var1) {
      this.cells = new Cell[var1.getWidth() * var1.getHeight()];
   }

    void reset() {
      if (this.cells != nullptr) {
         for (int var1 = 0; var1 < this.cells.length; var1++) {
    Cell var2 = this.cells[var1];
            if (var2 != nullptr) {
               var2.Reset();
            }
         }

         this.cells = nullptr;
      }
   }
}
} // namespace globalObjects
} // namespace zombie
