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


class Point2i : public Tuple2i {
public:
 static const long serialVersionUID = 9208072376494084954L;

 public Point2i(int int0, int int1) {
 super(int0, int1);
 }

 public Point2i(int[] ints) {
 super(ints);
 }

 public Point2i(Tuple2i tuple2i) {
 super(tuple2i);
 }

 public Point2i() {
 }
}
} // namespace vecmath
} // namespace javax
