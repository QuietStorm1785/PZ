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

class Point4i : public Tuple4i {
public:
 static const long serialVersionUID = 620124780244617983L;

public
 Point4i(int int0, int int1, int int2, int int3) {
 super(int0, int1, int2, int3);
 }

public
 Point4i(int[] ints) { super(ints); }

public
 Point4i(Tuple4i tuple4i) { super(tuple4i); }

public
 Point4i() {}
}
} // namespace vecmath
} // namespace javax
