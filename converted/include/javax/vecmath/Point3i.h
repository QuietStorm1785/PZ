#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <fstream>
#include <iostream>

namespace javax {
namespace vecmath {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class Point3i : public Tuple3i {
public:
 static const long serialVersionUID = 6149289077348153921L;

 public Point3i(int int0, int int1, int int2) {
 super(int0, int1, int2);
 }

 public Point3i(int[] ints) {
 super(ints);
 }

 public Point3i(Tuple3i tuple3i) {
 super(tuple3i);
 }

 public Point3i() {
 }
}
} // namespace vecmath
} // namespace javax
