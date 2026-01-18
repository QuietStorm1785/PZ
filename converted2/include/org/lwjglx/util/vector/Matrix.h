#pragma once
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace org {
namespace lwjglx {
namespace util {
namespace vector {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class Matrix {
public:
protected
  Matrix() {}

public
  abstract Matrix setIdentity();

public
  abstract Matrix invert();

public
  abstract Matrix load(FloatBuffer var1);

public
  abstract Matrix loadTranspose(FloatBuffer var1);

public
  abstract Matrix negate();

public
  abstract Matrix store(FloatBuffer var1);

public
  abstract Matrix storeTranspose(FloatBuffer var1);

public
  abstract Matrix transpose();

public
  abstract Matrix setZero();

public
  abstract float determinant();
}
} // namespace vector
} // namespace util
} // namespace lwjglx
} // namespace org
