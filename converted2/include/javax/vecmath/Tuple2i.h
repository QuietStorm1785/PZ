#pragma once
#include <cstdint>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace javax {
namespace vecmath {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class Tuple2i {
public:
  static const long serialVersionUID = -3555701650170169638L;
  int x;
  int y;

public
  Tuple2i(int int0, int int1) {
    this.x = int0;
    this.y = int1;
  }

public
  Tuple2i(int[] ints) {
    this.x = ints[0];
    this.y = ints[1];
  }

public
  Tuple2i(Tuple2i tuple2i1) {
    this.x = tuple2i1.x;
    this.y = tuple2i1.y;
  }

public
  Tuple2i() {
    this.x = 0;
    this.y = 0;
  }

  void set(int int0, int int1) {
    this.x = int0;
    this.y = int1;
  }

  void set(int[] ints) {
    this.x = ints[0];
    this.y = ints[1];
  }

  void set(Tuple2i tuple2i0) {
    this.x = tuple2i0.x;
    this.y = tuple2i0.y;
  }

  void get(int[] ints) {
    ints[0] = this.x;
    ints[1] = this.y;
  }

  void get(Tuple2i tuple2i1) {
    tuple2i1.x = this.x;
    tuple2i1.y = this.y;
  }

  void add(Tuple2i tuple2i1, Tuple2i tuple2i0) {
    this.x = tuple2i1.x + tuple2i0.x;
    this.y = tuple2i1.y + tuple2i0.y;
  }

  void add(Tuple2i tuple2i0) {
    this.x = this.x + tuple2i0.x;
    this.y = this.y + tuple2i0.y;
  }

  void sub(Tuple2i tuple2i1, Tuple2i tuple2i0) {
    this.x = tuple2i1.x - tuple2i0.x;
    this.y = tuple2i1.y - tuple2i0.y;
  }

  void sub(Tuple2i tuple2i0) {
    this.x = this.x - tuple2i0.x;
    this.y = this.y - tuple2i0.y;
  }

  void negate(Tuple2i tuple2i0) {
    this.x = -tuple2i0.x;
    this.y = -tuple2i0.y;
  }

  void negate() {
    this.x = -this.x;
    this.y = -this.y;
  }

  void scale(int int0, Tuple2i tuple2i0) {
    this.x = int0 * tuple2i0.x;
    this.y = int0 * tuple2i0.y;
  }

  void scale(int int0) {
    this.x *= int0;
    this.y *= int0;
  }

  void scaleAdd(int int0, Tuple2i tuple2i1, Tuple2i tuple2i0) {
    this.x = int0 * tuple2i1.x + tuple2i0.x;
    this.y = int0 * tuple2i1.y + tuple2i0.y;
  }

  void scaleAdd(int int0, Tuple2i tuple2i0) {
    this.x = int0 * this.x + tuple2i0.x;
    this.y = int0 * this.y + tuple2i0.y;
  }

  std::string toString() { return "(" + this.x + ", " + this.y + ")"; }

  bool equals(void *object) {
    try {
      Tuple2i tuple2i0 = (Tuple2i)object;
      return this.x == tuple2i0.x && this.y == tuple2i0.y;
    } catch (NullPointerException nullPointerException) {
      return false;
    } catch (ClassCastException classCastException) {
      return false;
    }
  }

  int hashCode() {
    long long0 = 1L;
    long0 = 31L * long0 + this.x;
    long0 = 31L * long0 + this.y;
    return (int)(long0 ^ long0 >> 32);
  }

  void clamp(int int1, int int0, Tuple2i tuple2i0) {
    if (tuple2i0.x > int0) {
      this.x = int0;
    } else if (tuple2i0.x < int1) {
      this.x = int1;
    } else {
      this.x = tuple2i0.x;
    }

    if (tuple2i0.y > int0) {
      this.y = int0;
    } else if (tuple2i0.y < int1) {
      this.y = int1;
    } else {
      this.y = tuple2i0.y;
    }
  }

  void clampMin(int int0, Tuple2i tuple2i0) {
    if (tuple2i0.x < int0) {
      this.x = int0;
    } else {
      this.x = tuple2i0.x;
    }

    if (tuple2i0.y < int0) {
      this.y = int0;
    } else {
      this.y = tuple2i0.y;
    }
  }

  void clampMax(int int0, Tuple2i tuple2i0) {
    if (tuple2i0.x > int0) {
      this.x = int0;
    } else {
      this.x = tuple2i0.x;
    }

    if (tuple2i0.y > int0) {
      this.y = int0;
    } else {
      this.y = tuple2i0.y;
    }
  }

  void absolute(Tuple2i tuple2i0) {
    this.x = Math.abs(tuple2i0.x);
    this.y = Math.abs(tuple2i0.y);
  }

  void clamp(int int1, int int0) {
    if (this.x > int0) {
      this.x = int0;
    } else if (this.x < int1) {
      this.x = int1;
    }

    if (this.y > int0) {
      this.y = int0;
    } else if (this.y < int1) {
      this.y = int1;
    }
  }

  void clampMin(int int0) {
    if (this.x < int0) {
      this.x = int0;
    }

    if (this.y < int0) {
      this.y = int0;
    }
  }

  void clampMax(int int0) {
    if (this.x > int0) {
      this.x = int0;
    }

    if (this.y > int0) {
      this.y = int0;
    }
  }

  void absolute() {
    this.x = Math.abs(this.x);
    this.y = Math.abs(this.y);
  }

  void *clone() {
    try {
      return super.clone();
    } catch (CloneNotSupportedException cloneNotSupportedException) {
      throw std::make_unique<InternalError>();
    }
  }

  int getX() { return this.x; }

  void setX(int int0) { this.x = int0; }

  int getY() { return this.y; }

  void setY(int int0) { this.y = int0; }
}
} // namespace vecmath
} // namespace javax
