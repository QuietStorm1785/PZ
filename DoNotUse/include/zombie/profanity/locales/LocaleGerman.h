#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/profanity/locales/LocaleGerman/1.h"

namespace zombie {
namespace profanity {
namespace locales {


class LocaleGerman : public LocaleEnglish {
public:
    public LocaleGerman(const std::string& var1) {
      super(var1);
   }

    void Init() {
      this.storeVowelsAmount = 3;
      super.Init();
      this.addPhonizer(std::make_shared<1>(this, "ringelS", "(?<ringelS>ÃŸ)"));
   }
}
} // namespace locales
} // namespace profanity
} // namespace zombie
