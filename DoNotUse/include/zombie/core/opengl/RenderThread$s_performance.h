#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/profiling/PerformanceProfileFrameProbe.h"
#include "zombie/core/profiling/PerformanceProfileProbe.h"

namespace zombie {
namespace core {
namespace opengl {


class RenderThread {
public:
    static const PerformanceProfileFrameProbe renderStep = std::make_shared<PerformanceProfileFrameProbe>("RenderThread.renderStep");
    static const PerformanceProfileProbe displayUpdate = std::make_shared<PerformanceProfileProbe>("Display.update(true)");
    static const PerformanceProfileProbe spriteRendererPostRender = std::make_shared<PerformanceProfileProbe>("SpriteRenderer.postRender");

   private RenderThread$s_performance() {
   }
}
} // namespace opengl
} // namespace core
} // namespace zombie
