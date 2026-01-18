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
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class Registry : public Util {
public:
  static const std::string versionString = "1.3";
  static const std::string extensionString =
      "GLU_EXT_nurbs_tessellator GLU_EXT_object_space_tess ";

  static std::string gluGetString(int int0) {
    if (int0 == 100800) {
      return "1.3";
    } else {
      return int0 = =
                 100801 ? "GLU_EXT_nurbs_tessellator GLU_EXT_object_space_tess "
                        : null;
    }
  }

  static bool gluCheckExtension(const std::string &string1,
                                const std::string &string0) {
    return string0 != nullptr && string1 != nullptr
               ? string0.indexOf(string1) != -1
               : false;
  }
}
} // namespace glu
} // namespace util
} // namespace lwjglx
} // namespace org
