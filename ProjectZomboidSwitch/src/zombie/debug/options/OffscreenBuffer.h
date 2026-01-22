#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/debug/BooleanDebugOption.h"

namespace zombie {
namespace debug {
namespace options {


class OffscreenBuffer : public OptionGroup {
public:
    const BooleanDebugOption Render = newDebugOnlyOption(this.Group, "Render", true);

    public OffscreenBuffer() {
      super("OffscreenBuffer");
   }
}
} // namespace options
} // namespace debug
} // namespace zombie
