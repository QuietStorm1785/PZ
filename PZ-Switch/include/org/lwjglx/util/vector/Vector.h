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

class Vector {
public:
protected
 Vector() {}

 float length() { return (float)Math.sqrt(this->lengthSquared()); }

public
 float lengthSquared();

public
 Vector load(FloatBuffer var1);

public
 Vector negate();

 Vector normalise() {
 float float0 = this->length();
 if (float0 != 0.0F) {
 float float1 = 1.0F / float0;
 return this->scale(float1);
 } else {
 throw IllegalStateException("Zero length vector");
 }
 }

public
 Vector store(FloatBuffer var1);

public
 Vector scale(float var1);
}
} // namespace vector
} // namespace util
} // namespace lwjglx
} // namespace org
