#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <filesystem>

namespace zombie {
namespace vehicles {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class ClipperOffset {
public:
 const long address = this->newInstance();

 private long newInstance();

 public void clear();

 public void addPath(int numPoints, ByteBuffer points, int joinType, int endType);

 public void execute(double delta);

 public int getPolygonCount();

 public int getPolygon(int index, ByteBuffer vertices);

 public static enum EndType {
 etClosedPolygon,
 etClosedLine,
 etOpenButt,
 etOpenSquare,
 etOpenRound;
 }

 public static enum JoinType {
 jtSquare,
 jtRound,
 jtMiter;
 }
}
} // namespace vehicles
} // namespace zombie
