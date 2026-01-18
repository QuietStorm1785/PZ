#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>

namespace org {
namespace lwjglx {
namespace util {
namespace vector {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class Matrix {
public:
 protected Matrix() {
 }

 public Matrix setIdentity();

 public Matrix invert();

 public Matrix load(FloatBuffer var1);

 public Matrix loadTranspose(FloatBuffer var1);

 public Matrix negate();

 public Matrix store(FloatBuffer var1);

 public Matrix storeTranspose(FloatBuffer var1);

 public Matrix transpose();

 public Matrix setZero();

 public float determinant();
}
} // namespace vector
} // namespace util
} // namespace lwjglx
} // namespace org
