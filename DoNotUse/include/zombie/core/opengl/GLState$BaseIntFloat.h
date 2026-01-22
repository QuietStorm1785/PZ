#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/opengl/GLState/CIntFloatValue.h"

namespace zombie {
namespace core {
namespace opengl {


class GLState {
public:
    CIntFloatValue defaultValue() {
      return std::make_unique<CIntFloatValue>();
   }
}
} // namespace opengl
} // namespace core
} // namespace zombie
