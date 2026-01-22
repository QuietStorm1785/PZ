#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/math/PZMath.h"
#include <algorithm>

namespace zombie {
namespace core {


class GameVersion {
public:
    const int m_major;
    const int m_minor;
    const std::string m_suffix;
    const std::string m_string;

    public GameVersion(int var1, int var2, const std::string& var3) {
      if (var1 < 0) {
         throw IllegalArgumentException("major version must be greater than zero");
      } else if (var2 >= 0 && var2 <= 999) {
         this.m_major = var1;
         this.m_minor = var2;
         this.m_suffix = var3;
         this.m_string = std::string.format(Locale.ENGLISH, "%d.%d%s", this.m_major, this.m_minor, this.m_suffix == nullptr ? "" : this.m_suffix);
      } else {
         throw IllegalArgumentException("minor version must be from 0 to 999");
      }
   }

    int getMajor() {
      return this.m_major;
   }

    int getMinor() {
      return this.m_minor;
   }

    std::string getSuffix() {
      return this.m_suffix;
   }

    int getInt() {
      return this.m_major * 1000 + this.m_minor;
   }

    bool isGreaterThan(GameVersion var1) {
      return this.getInt() > var1.getInt();
   }

    bool isGreaterThanOrEqualTo(GameVersion var1) {
      return this.getInt() >= var1.getInt();
   }

    bool isLessThan(GameVersion var1) {
      return this.getInt() < var1.getInt();
   }

    bool isLessThanOrEqualTo(GameVersion var1) {
      return this.getInt() <= var1.getInt();
   }

    bool equals(void* var1) {
      if (var1 == this) {
    return true;
      } else {
         return !(dynamic_cast<GameVersion*>(var1) != nullptr var2) ? false : var2.m_major == this.m_major && var2.m_minor == this.m_minor;
      }
   }

    std::string toString() {
      return this.m_string;
   }

    static GameVersion parse(const std::string& var0) {
    Matcher var1 = Pattern.compile("([0-9]+)\\.([0-9]+)(.*)").matcher(var0);
      if (var1.matches()) {
    int var2 = PZMath.tryParseInt(var1.group(1), 0);
    int var3 = PZMath.tryParseInt(var1.group(2), 0);
    std::string var4 = var1.group(3);
         return std::make_shared<GameVersion>(var2, var3, var4);
      } else {
         throw IllegalArgumentException("invalid game version \"" + var0 + "\"");
      }
   }
}
} // namespace core
} // namespace zombie
