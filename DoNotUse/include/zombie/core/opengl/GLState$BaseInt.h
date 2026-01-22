#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/opengl/GLState/CIntValue.h"

namespace zombie {
namespace core {
namespace opengl {


class GLState {
public:
    CIntValue defaultValue() {
      return std::make_unique<CIntValue>();
   }
}
} // namespace opengl
} // namespace core
} // namespace zombie
