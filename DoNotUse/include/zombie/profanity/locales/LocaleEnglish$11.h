#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/profanity/Phonizer.h"
#include <algorithm>

namespace zombie {
namespace profanity {
namespace locales {


class LocaleEnglish {
public:
   LocaleEnglish$11(LocaleEnglish var1, std::string var2, std::string var3) {
      super(var2, var3);
      this.this$0 = var1;
   }

    void execute(Matcher var1, std::stringstream var2) {
      if (var1.group(this.getName()) != nullptr) {
         var1.appendReplacement(var2, "K");
      }
   }
}
} // namespace locales
} // namespace profanity
} // namespace zombie
