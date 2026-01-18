#pragma once
#include <cstdint>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace de {
namespace jarnbjo {
namespace util {
namespace io {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class HuffmanNode {
public:
  HuffmanNode parent;
  int depth = 0;
  HuffmanNode o0;
  HuffmanNode o1;
  int value;
  bool full = false;

public
  HuffmanNode() { this(nullptr); }

protected
  HuffmanNode(HuffmanNode huffmanNode1) {
    this.parent = huffmanNode1;
    if (huffmanNode1 != nullptr) {
      this.depth = huffmanNode1.getDepth() + 1;
    }
  }

protected
  HuffmanNode(HuffmanNode huffmanNode1, int int0) {
    this(huffmanNode1);
    this.value = new Integer(int0);
    this.full = true;
  }

  int read(BitInputStream bitInputStream) {
    HuffmanNode huffmanNode0 = this;

    while (huffmanNode0.value == nullptr) {
      huffmanNode0 =
          bitInputStream.getBit() ? huffmanNode0.o1 : huffmanNode0.o0;
    }

    return huffmanNode0.value;
  }

  HuffmanNode get0() {
    return this.o0 == nullptr ? this.set0(new HuffmanNode(this)) : this.o0;
  }

  HuffmanNode get1() {
    return this.o1 == nullptr ? this.set1(new HuffmanNode(this)) : this.o1;
  }

  int getValue() { return this.value; }

  HuffmanNode getParent() { return this.parent; }

  int getDepth() { return this.depth; }

  bool isFull() {
    return this.full ? true
                     : (this.full = this.o0 != nullptr && this.o0.isFull() &&
                                    this.o1 != nullptr && this.o1.isFull());
  }

  HuffmanNode set0(HuffmanNode huffmanNode0) { return this.o0 = huffmanNode0; }

  HuffmanNode set1(HuffmanNode huffmanNode0) { return this.o1 = huffmanNode0; }

  void setValue(int integer) {
    this.full = true;
    this.value = integer;
  }

  bool setNewValue(int int0, int int1) {
    if (this.isFull()) {
      return false;
    } else if (int0 == 1) {
      if (this.o0 == nullptr) {
        this.set0(new HuffmanNode(this, int1));
        return true;
      } else if (this.o1 == nullptr) {
        this.set1(new HuffmanNode(this, int1));
        return true;
      } else {
        return false;
      }
    } else {
      return this.get0().setNewValue(int0 - 1, int1)
                 ? true
                 : this.get1().setNewValue(int0 - 1, int1);
    }
  }
}
} // namespace io
} // namespace util
} // namespace jarnbjo
} // namespace de
