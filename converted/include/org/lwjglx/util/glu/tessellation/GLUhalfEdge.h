#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace org {
namespace lwjglx {
namespace util {
namespace glu {
namespace tessellation {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.

class GLUhalfEdge {
public:
 GLUhalfEdge next;
 GLUhalfEdge Sym;
 GLUhalfEdge Onext;
 GLUhalfEdge Lnext;
 GLUvertex Org;
 GLUface Lface;
 ActiveRegion activeRegion;
 int winding;
 bool first;

 GLUhalfEdge(boolean boolean0) {
 this->first = boolean0;
 }
}
} // namespace tessellation
} // namespace glu
} // namespace util
} // namespace lwjglx
} // namespace org
