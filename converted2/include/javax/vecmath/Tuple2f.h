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

class Tuple2f {
public:
  static const long serialVersionUID = 9011180388985266884L;
  float x;
  float y;

public
  Tuple2f(float float0, float float1) {
    this.x = float0;
    this.y = float1;
  }

public
  Tuple2f(float[] floats) {
    this.x = floats[0];
    this.y = floats[1];
  }

public
  Tuple2f(Tuple2f tuple2f1) {
    this.x = tuple2f1.x;
    this.y = tuple2f1.y;
  }

public
  Tuple2f(Tuple2d tuple2d) {
    this.x = (float)tuple2d.x;
    this.y = (float)tuple2d.y;
  }

public
  Tuple2f() {
    this.x = 0.0F;
    this.y = 0.0F;
  }

  void set(float float0, float float1) {
    this.x = float0;
    this.y = float1;
  }

  void set(float[] floats) {
    this.x = floats[0];
    this.y = floats[1];
  }

  void set(Tuple2f tuple2f0) {
    this.x = tuple2f0.x;
    this.y = tuple2f0.y;
  }

  void set(Tuple2d tuple2d) {
    this.x = (float)tuple2d.x;
    this.y = (float)tuple2d.y;
  }

  void get(float[] floats) {
    floats[0] = this.x;
    floats[1] = this.y;
  }

  void add(Tuple2f tuple2f1, Tuple2f tuple2f0) {
    this.x = tuple2f1.x + tuple2f0.x;
    this.y = tuple2f1.y + tuple2f0.y;
  }

  void add(Tuple2f tuple2f0) {
    this.x = this.x + tuple2f0.x;
    this.y = this.y + tuple2f0.y;
  }

  void sub(Tuple2f tuple2f1, Tuple2f tuple2f0) {
    this.x = tuple2f1.x - tuple2f0.x;
    this.y = tuple2f1.y - tuple2f0.y;
  }

  void sub(Tuple2f tuple2f0) {
    this.x = this.x - tuple2f0.x;
    this.y = this.y - tuple2f0.y;
  }

  void negate(Tuple2f tuple2f0) {
    this.x = -tuple2f0.x;
    this.y = -tuple2f0.y;
  }

  void negate() {
    this.x = -this.x;
    this.y = -this.y;
  }

  void scale(float float0, Tuple2f tuple2f0) {
    this.x = float0 * tuple2f0.x;
    this.y = float0 * tuple2f0.y;
  }

  void scale(float float0) {
    this.x *= float0;
    this.y *= float0;
  }

  void scaleAdd(float float0, Tuple2f tuple2f1, Tuple2f tuple2f0) {
    this.x = float0 * tuple2f1.x + tuple2f0.x;
    this.y = float0 * tuple2f1.y + tuple2f0.y;
  }

  void scaleAdd(float float0, Tuple2f tuple2f0) {
    this.x = float0 * this.x + tuple2f0.x;
    this.y = float0 * this.y + tuple2f0.y;
  }

  int hashCode() {
    long long0 = 1L;
    long0 = 31L * long0 + VecMathUtil.floatToIntBits(this.x);
    long0 = 31L * long0 + VecMathUtil.floatToIntBits(this.y);
    return (int)(long0 ^ long0 >> 32);
  }

  bool equals(Tuple2f tuple2f0) {
    try {
      return this.x == tuple2f0.x && this.y == tuple2f0.y;
    } catch (NullPointerException nullPointerException) {
      return false;
    }
  }

  bool equals(void *object) {
    try {
      Tuple2f tuple2f0 = (Tuple2f)object;
      return this.x == tuple2f0.x && this.y == tuple2f0.y;
    } catch (NullPointerException nullPointerException) {
      return false;
    } catch (ClassCastException classCastException) {
      return false;
    }
  }

  bool epsilonEquals(Tuple2f tuple2f0, float float1) {
    float float0 = this.x - tuple2f0.x;
    if (Float.isNaN(float0)) {
      return false;
    } else if ((float0 < 0.0F ? -float0 : float0) > float1) {
      return false;
    } else {
      float0 = this.y - tuple2f0.y;
      return Float.isNaN(float0)
                 ? false
                 : !((float0 < 0.0F ? -float0 : float0) > float1);
    }
  }

  std::string toString() { return "(" + this.x + ", " + this.y + ")"; }

  void clamp(float float1, float float0, Tuple2f tuple2f0) {
    if (tuple2f0.x > float0) {
      this.x = float0;
    } else if (tuple2f0.x < float1) {
      this.x = float1;
    } else {
      this.x = tuple2f0.x;
    }

    if (tuple2f0.y > float0) {
      this.y = float0;
    } else if (tuple2f0.y < float1) {
      this.y = float1;
    } else {
      this.y = tuple2f0.y;
    }
  }

  void clampMin(float float0, Tuple2f tuple2f0) {
    if (tuple2f0.x < float0) {
      this.x = float0;
    } else {
      this.x = tuple2f0.x;
    }

    if (tuple2f0.y < float0) {
      this.y = float0;
    } else {
      this.y = tuple2f0.y;
    }
  }

  void clampMax(float float0, Tuple2f tuple2f0) {
    if (tuple2f0.x > float0) {
      this.x = float0;
    } else {
      this.x = tuple2f0.x;
    }

    if (tuple2f0.y > float0) {
      this.y = float0;
    } else {
      this.y = tuple2f0.y;
    }
  }

  void absolute(Tuple2f tuple2f0) {
    this.x = Math.abs(tuple2f0.x);
    this.y = Math.abs(tuple2f0.y);
  }

  void clamp(float float1, float float0) {
    if (this.x > float0) {
      this.x = float0;
    } else if (this.x < float1) {
      this.x = float1;
    }

    if (this.y > float0) {
      this.y = float0;
    } else if (this.y < float1) {
      this.y = float1;
    }
  }

  void clampMin(float float0) {
    if (this.x < float0) {
      this.x = float0;
    }

    if (this.y < float0) {
      this.y = float0;
    }
  }

  void clampMax(float float0) {
    if (this.x > float0) {
      this.x = float0;
    }

    if (this.y > float0) {
      this.y = float0;
    }
  }

  void absolute() {
    this.x = Math.abs(this.x);
    this.y = Math.abs(this.y);
  }

  void interpolate(Tuple2f tuple2f1, Tuple2f tuple2f0, float float0) {
    this.x = (1.0F - float0) * tuple2f1.x + float0 * tuple2f0.x;
    this.y = (1.0F - float0) * tuple2f1.y + float0 * tuple2f0.y;
  }

  void interpolate(Tuple2f tuple2f0, float float0) {
    this.x = (1.0F - float0) * this.x + float0 * tuple2f0.x;
    this.y = (1.0F - float0) * this.y + float0 * tuple2f0.y;
  }

  void *clone() {
    try {
      return super.clone();
    } catch (CloneNotSupportedException cloneNotSupportedException) {
      throw std::make_unique<InternalError>();
    }
  }

  float getX() { return this.x; }

  void setX(float float0) { this.x = float0; }

  float getY() { return this.y; }

  void setY(float float0) { this.y = float0; }
}
} // namespace vecmath
} // namespace javax
