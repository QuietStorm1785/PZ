#pragma once
#include <string>
#include <string_view>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/util/StringUtils.h"

namespace zombie {
namespace asset {


class AssetPath {
:
    std::string m_path;

     AssetPath(std::string_view var1) {
      this.m_path = var1;
   }

    bool isValid() {
      return !StringUtils.isNullOrEmpty(this.m_path);
   }

    int getHash() const {
      return this.m_path.hashCode();
   }

    std::string getPath() const {
      return this.m_path;
   }

    std::string toString() {
      return this.getClass().getSimpleName() + "{ \"" + this.getPath() + "\" }";
   }
}
} // namespace asset
} // namespace zombie
