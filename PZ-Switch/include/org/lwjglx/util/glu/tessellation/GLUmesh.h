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

class GLUmesh {
public:
 GLUvertex vHead = std::make_unique<GLUvertex>();
 GLUface fHead = std::make_unique<GLUface>();
 GLUhalfEdge eHead = new GLUhalfEdge(true);
 GLUhalfEdge eHeadSym = new GLUhalfEdge(false);
}
} // namespace tessellation
} // namespace glu
} // namespace util
} // namespace lwjglx
} // namespace org
