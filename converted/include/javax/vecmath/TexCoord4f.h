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

class TexCoord4f : public Tuple4f {
public:
  static const long serialVersionUID = -3517736544731446513L;

public
  TexCoord4f(float float0, float float1, float float2, float float3) {
    super(float0, float1, float2, float3);
  }

public
  TexCoord4f(float[] floats) { super(floats); }

public
  TexCoord4f(TexCoord4f texCoord4f1) { super(texCoord4f1); }

public
  TexCoord4f(Tuple4f tuple4f) { super(tuple4f); }

public
  TexCoord4f(Tuple4d tuple4d) { super(tuple4d); }

public
  TexCoord4f() {}
}
} // namespace vecmath
} // namespace javax
