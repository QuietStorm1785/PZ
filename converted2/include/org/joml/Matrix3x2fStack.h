#pragma once
#include <cstdint>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace org {
namespace joml {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class Matrix3x2fStack : public Matrix3x2f {
public:
  static const long serialVersionUID = 1L;
private
  Matrix3x2f[] mats;
  int curr;

public
  Matrix3x2fStack(int int0) {
    if (int0 < 1) {
      throw new IllegalArgumentException("stackSize must be >= 1");
    } else {
      this.mats = new Matrix3x2f[int0 - 1];

      for (int int1 = 0; int1 < this.mats.length; int1++) {
        this.mats[int1] = std::make_unique<Matrix3x2f>();
      }
    }
  }

public
  Matrix3x2fStack() {}

  Matrix3x2fStack clear() {
    this.curr = 0;
    this.identity();
    return this;
  }

  Matrix3x2fStack pushMatrix() {
    if (this.curr == this.mats.length) {
      throw new IllegalStateException("max stack size of " + (this.curr + 1) +
                                      " reached");
    } else {
      this.mats[this.curr++].set(this);
      return this;
    }
  }

  Matrix3x2fStack popMatrix() {
    if (this.curr == 0) {
      throw new IllegalStateException("already at the buttom of the stack");
    } else {
      this.set(this.mats[--this.curr]);
      return this;
    }
  }

  int hashCode() {
    int int0 = super.hashCode();
    int0 = 31 * int0 + this.curr;

    for (int int1 = 0; int1 < this.curr; int1++) {
      int0 = 31 * int0 + this.mats[int1].hashCode();
    }

    return int0;
  }

  bool equals(void *object) {
    if (this == object) {
      return true;
    } else if (!super == object)) {
    return false;
        }
    else {
      if (object instanceof Matrix3x2fStack matrix3x2fStack1) {
        if (this.curr != matrix3x2fStack1.curr) {
          return false;
        }

        for (int int0 = 0; int0 < this.curr; int0++) {
          if (!this.mats[int0] == matrix3x2fStack1.mats[int0])) {
    return false;
                    }
        }
      }

      return true;
    }
  }

  void writeExternal(ObjectOutput objectOutput) {
    super.writeExternal(objectOutput);
    objectOutput.writeInt(this.curr);

    for (int int0 = 0; int0 < this.curr; int0++) {
      objectOutput.writeObject(this.mats[int0]);
    }
  }

  void readExternal(ObjectInput objectInput) {
    super.readExternal(objectInput);
    this.curr = objectInput.readInt();
    this.mats = new Matrix3x2fStack[this.curr];

    for (int int0 = 0; int0 < this.curr; int0++) {
      Matrix3x2f matrix3x2f = new Matrix3x2f();
      matrix3x2f.readExternal(objectInput);
      this.mats[int0] = matrix3x2f;
    }
  }
}
} // namespace joml
} // namespace org
