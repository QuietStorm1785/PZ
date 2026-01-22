#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/util/StringUtils.h"

namespace zombie {
namespace characters {
namespace traits {


class TraitCollection {
public:
    const std::string Name;
    bool m_isSet;

   private TraitCollection$TraitSlot(TraitCollection var1, std::string var2) {
      this.this$0 = var1;
      this.Name = var2;
      this.m_isSet = false;
   }

    bool isName(const std::string& var1) {
      return StringUtils.equalsIgnoreCase(this.Name, var1);
   }

    bool isSet() {
      return this.m_isSet;
   }

    void set(bool var1) {
      if (this.m_isSet != var1) {
         this.this$0.set(this.Name, var1);
      }
   }

    std::string toString() {
      return "TraitSlot(" + this.Name + ":" + this.m_isSet + ")";
   }
}
} // namespace traits
} // namespace characters
} // namespace zombie
