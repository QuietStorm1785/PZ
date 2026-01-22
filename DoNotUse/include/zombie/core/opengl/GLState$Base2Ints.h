#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/opengl/GLState/C2IntsValue.h"

namespace zombie {
namespace core {
namespace opengl {


class GLState {
public:
    C2IntsValue defaultValue() {
      return std::make_unique<C2IntsValue>();
   }
}
} // namespace opengl
} // namespace core
} // namespace zombie
