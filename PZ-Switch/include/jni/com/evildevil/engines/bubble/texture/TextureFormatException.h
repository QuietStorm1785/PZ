#pragma once
#include <string>
#include <string_view>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace com {
namespace evildevil {
namespace engines {
namespace bubble {
namespace texture {

class TextureFormatException :  Exception {
:
    static const long serialVersionUID = 24L;

     TextureFormatException() {
   }

     TextureFormatException(std::string_view var1) {
      super(var1);
   }
}
} // namespace texture
} // namespace bubble
} // namespace engines
} // namespace evildevil
} // namespace com
