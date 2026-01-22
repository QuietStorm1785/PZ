#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/opengl/GLState/CBooleanValue.h"

namespace zombie {
namespace core {
namespace opengl {


class GLState {
public:
    CBooleanValue defaultValue() {
      return std::make_shared<CBooleanValue>(true);
   }
}
} // namespace opengl
} // namespace core
} // namespace zombie
