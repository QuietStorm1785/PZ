#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace org {
namespace lwjglx {
namespace util {
namespace glu {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class GLUtessellator {
public:
 virtual ~GLUtessellator() = default;
 void gluDeleteTess();

 void gluTessProperty(int var1, double var2);

 void gluGetTessProperty(int var1, double[] var2, int var3);

 void gluTessNormal(double var1, double var3, double var5);

 void gluTessCallback(int var1, GLUtessellatorCallback var2);

 void gluTessVertex(double[] var1, int var2, void *var3);

 void gluTessBeginPolygon(void *var1);

 void gluTessBeginContour();

 void gluTessEndContour();

 void gluTessEndPolygon();

 void gluBeginPolygon();

 void gluNextContour(int var1);

 void gluEndPolygon();
}
} // namespace glu
} // namespace util
} // namespace lwjglx
} // namespace org
