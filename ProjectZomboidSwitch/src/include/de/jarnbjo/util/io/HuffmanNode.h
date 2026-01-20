#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <fstream>
#include <iostream>

namespace de {
namespace jarnbjo {
namespace util {
namespace io {


class HuffmanNode {
public:
    HuffmanNode parent;
    int depth = 0;
    HuffmanNode o0;
    HuffmanNode o1;
    int value;
    bool full = false;

    public HuffmanNode() {
      this(nullptr);
   }

    protected HuffmanNode(HuffmanNode var1) {
      this.parent = var1;
      if (var1 != nullptr) {
         this.depth = var1.getDepth() + 1;
      }
   }

    protected HuffmanNode(HuffmanNode var1, int var2) {
      this(var1);
      this.value = std::make_shared<int>(var2);
      this.full = true;
   }

    int read(BitInputStream var1) {
    HuffmanNode var2 = this;

      while (var2.value == nullptr) {
         var2 = var1.getBit() ? var2.o1 : var2.o0;
      }

      return var2.value;
   }

    HuffmanNode get0() {
      return this.o0 == nullptr ? this.set0(std::make_shared<HuffmanNode>(this)) : this.o0;
   }

    HuffmanNode get1() {
      return this.o1 == nullptr ? this.set1(std::make_shared<HuffmanNode>(this)) : this.o1;
   }

    int getValue() {
      return this.value;
   }

    HuffmanNode getParent() {
      return this.parent;
   }

    int getDepth() {
      return this.depth;
   }

    bool isFull() {
      return this.full ? true : (this.full = this.o0 != nullptr && this.o0.isFull() && this.o1 != nullptr && this.o1.isFull());
   }

    HuffmanNode set0(HuffmanNode var1) {
      return this.o0 = var1;
   }

    HuffmanNode set1(HuffmanNode var1) {
      return this.o1 = var1;
   }

    void setValue(int var1) {
      this.full = true;
      this.value = var1;
   }

    bool setNewValue(int var1, int var2) {
      if (this.isFull()) {
    return false;
      } else if (var1 == 1) {
         if (this.o0 == nullptr) {
            this.set0(std::make_shared<HuffmanNode>(this, var2));
    return true;
         } else if (this.o1 == nullptr) {
            this.set1(std::make_shared<HuffmanNode>(this, var2));
    return true;
         } else {
    return false;
         }
      } else {
         return this.get0().setNewValue(var1 - 1, var2) ? true : this.get1().setNewValue(var1 - 1, var2);
      }
   }
}
} // namespace io
} // namespace util
} // namespace jarnbjo
} // namespace de
