#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/util/StringUtils.h"

namespace zombie {
namespace asset {


class AssetPath {
public:
    std::string m_path;

    public AssetPath(const std::string& var1) {
      this.m_path = var1;
   }

    bool isValid() {
      return !StringUtils.isNullOrEmpty(this.m_path);
   }

    int getHash() {
      return this.m_path.hashCode();
   }

    std::string getPath() {
      return this.m_path;
   }

    std::string toString() {
      return this.getClass().getSimpleName() + "{ \"" + this.getPath() + "\" }";
   }
}
} // namespace asset
} // namespace zombie
