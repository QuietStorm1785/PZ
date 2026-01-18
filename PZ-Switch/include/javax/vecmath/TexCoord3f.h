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

class TexCoord3f : public Tuple3f {
public:
 static const long serialVersionUID = -3517736544731446513L;

public
 TexCoord3f(float float0, float float1, float float2) {
 super(float0, float1, float2);
 }

public
 TexCoord3f(float[] floats) { super(floats); }

public
 TexCoord3f(TexCoord3f texCoord3f1) { super(texCoord3f1); }

public
 TexCoord3f(Tuple3f tuple3f) { super(tuple3f); }

public
 TexCoord3f(Tuple3d tuple3d) { super(tuple3d); }

public
 TexCoord3f() {}
}
} // namespace vecmath
} // namespace javax
