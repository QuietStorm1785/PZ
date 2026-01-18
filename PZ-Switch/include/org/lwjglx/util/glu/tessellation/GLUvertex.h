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
namespace tessellation {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class GLUvertex {
public:
 GLUvertex next;
 GLUvertex prev;
 GLUhalfEdge anEdge;
 void *data;
public
 double[] coords = new double[3];
 double s;
 double t;
 int pqHandle;
}
} // namespace tessellation
} // namespace glu
} // namespace util
} // namespace lwjglx
} // namespace org
