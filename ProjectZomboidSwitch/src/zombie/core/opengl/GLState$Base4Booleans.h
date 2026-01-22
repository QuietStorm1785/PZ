#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/opengl/GLState/C4BooleansValue.h"

namespace zombie {
namespace core {
namespace opengl {


class GLState {
public:
    C4BooleansValue defaultValue() {
      return std::make_unique<C4BooleansValue>();
   }
}
} // namespace opengl
} // namespace core
} // namespace zombie
