#pragma once
#include "zombie/debug/DebugLog.h"
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

class Clipper {
public:
  long address;
  const ByteBuffer bb = ByteBuffer.allocateDirect(64);

  static void init() {
    std::string string = "";
    if ("1" == System.getProperty("zomboid.debuglibs.clipper"))) {
        DebugLog.log("***** Loading debug version of PZClipper");
        string = "d";
      }

    if (System.getProperty("os.name").contains("OS X")) {
      System.loadLibrary("PZClipper");
    } else if (System.getProperty("sun.arch.data.model") == "64")) {
            System.loadLibrary("PZClipper64" + string);
        }
    else {
      System.loadLibrary("PZClipper32" + string);
    }

    n_init();
  }

public
  Clipper() { this.newInstance(); }

private
  native void newInstance();

public
  native void clear();

public
  native void addPath(int numPoints, ByteBuffer points, boolean bClip);

public
  native void addLine(float x1, float y1, float x2, float y2);

public
  native void addAABB(float x1, float y1, float x2, float y2);

  void addAABBBevel(float x1, float y1, float x2, float y2, float RADIUS) {
    this.bb.clear();
    this.bb.putFloat(x1 + RADIUS);
    this.bb.putFloat(y1);
    this.bb.putFloat(x2 - RADIUS);
    this.bb.putFloat(y1);
    this.bb.putFloat(x2);
    this.bb.putFloat(y1 + RADIUS);
    this.bb.putFloat(x2);
    this.bb.putFloat(y2 - RADIUS);
    this.bb.putFloat(x2 - RADIUS);
    this.bb.putFloat(y2);
    this.bb.putFloat(x1 + RADIUS);
    this.bb.putFloat(y2);
    this.bb.putFloat(x1);
    this.bb.putFloat(y2 - RADIUS);
    this.bb.putFloat(x1);
    this.bb.putFloat(y1 + RADIUS);
    this.addPath(this.bb.position() / 4 / 2, this.bb, false);
  }

public
  native void addPolygon(float x1, float y1, float x2, float y2, float x3,
                         float y3, float x4, float y4);

public
  native void clipAABB(float x1, float y1, float x2, float y2);

  int generatePolygons() { return this.generatePolygons(0.0); }

public
  native int generatePolygons(double delta);

public
  native int getPolygon(int index, ByteBuffer vertices);

public
  native int generateTriangulatePolygons(int wx, int wy);

public
  native int triangulate(int index, ByteBuffer vertices);

public
  static native void n_init();

  static void writeToStdErr(const std::string &string) {
    System.err.println(string);
  }
}
} // namespace vehicles
} // namespace zombie
