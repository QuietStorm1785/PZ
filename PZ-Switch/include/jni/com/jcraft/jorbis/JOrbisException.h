#pragma once
#include <string>
#include <string_view>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace com {
namespace jcraft {
namespace jorbis {

class JOrbisException :  Exception {
:
    static const long serialVersionUID = 1L;

     JOrbisException() {
   }

     JOrbisException(std::string_view var1) {
      super("JOrbis: " + var1);
   }
}
} // namespace jorbis
} // namespace jcraft
} // namespace com
