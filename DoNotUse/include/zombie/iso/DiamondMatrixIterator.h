#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/joml/Vector2i.h"

namespace zombie {
namespace iso {


class DiamondMatrixIterator {
public:
    int size;
    int lineSize;
    int line;
    int column;

    public DiamondMatrixIterator(int var1) {
      this.size = var1;
      this.lineSize = 1;
      this.line = 0;
      this.column = 0;
   }

    DiamondMatrixIterator reset(int var1) {
      this.size = var1;
      this.lineSize = 1;
      this.line = 0;
      this.column = 0;
    return this;
   }

    void reset() {
      this.lineSize = 1;
      this.line = 0;
      this.column = 0;
   }

    bool next(Vector2i var1) {
      if (this.lineSize == 0) {
         var1.x = 0;
         var1.y = 0;
    return false;
      } else if (this.line == 0 && this.column == 0) {
         var1.set(0, 0);
         this.column++;
    return true;
      } else {
         if (this.column < this.lineSize) {
            var1.x++;
            var1.y--;
            this.column++;
         } else {
            this.column = 1;
            this.line++;
            if (this.line < this.size) {
               this.lineSize++;
               var1.x = 0;
               var1.y = this.line;
            } else {
               this.lineSize--;
               var1.x = this.line - this.size + 1;
               var1.y = this.size - 1;
            }
         }

         if (this.lineSize == 0) {
            var1.x = 0;
            var1.y = 0;
    return false;
         } else {
    return true;
         }
      }
   }

    Vector2i i2line(int var1) {
    int var2 = 0;

      for (int var3 = 1; var3 < this.size + 1; var3++) {
         var2 += var3;
         if (var1 + 1 <= var2) {
            return std::make_shared<Vector2i>(var1 - var2 + var3, var3 - 1);
         }
      }

      for (int var4 = this.size + 1; var4 < this.size * 2; var4++) {
         var2 += this.size * 2 - var4;
         if (var1 + 1 <= var2) {
            return std::make_shared<Vector2i>(var1 - var2 + this.size * 2 - var4, var4 - 1);
         }
      }

    return nullptr;
   }

    Vector2i line2coord(Vector2i var1) {
      if (var1 == nullptr) {
    return nullptr;
      } else if (var1.y < this.size) {
    Vector2i var4 = std::make_shared<Vector2i>(0, var1.y);

         for (int var5 = 0; var5 < var1.x; var5++) {
            var4.x++;
            var4.y--;
         }

    return var4;
      } else {
    Vector2i var2 = std::make_shared<Vector2i>(var1.y - this.size + 1, this.size - 1);

         for (int var3 = 0; var3 < var1.x; var3++) {
            var2.x++;
            var2.y--;
         }

    return var2;
      }
   }
}
} // namespace iso
} // namespace zombie
