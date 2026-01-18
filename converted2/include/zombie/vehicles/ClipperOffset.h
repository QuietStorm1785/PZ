#pragma once
#include <cstdint>
#include <filesystem>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace vehicles {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class ClipperOffset {
public:
  const long address = this.newInstance();

private
  native long newInstance();

public
  native void clear();

public
  native void addPath(int numPoints, ByteBuffer points, int joinType,
                      int endType);

public
  native void execute(double delta);

public
  native int getPolygonCount();

public
  native int getPolygon(int index, ByteBuffer vertices);

public
  static enum EndType {
    etClosedPolygon, etClosedLine, etOpenButt, etOpenSquare, etOpenRound;
  }

  public static enum JoinType { jtSquare, jtRound, jtMiter; }
}
} // namespace vehicles
} // namespace zombie
