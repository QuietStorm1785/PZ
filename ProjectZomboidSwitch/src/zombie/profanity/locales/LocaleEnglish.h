#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/profanity/locales/LocaleEnglish/1.h"
#include "zombie/profanity/locales/LocaleEnglish/10.h"
#include "zombie/profanity/locales/LocaleEnglish/11.h"
#include "zombie/profanity/locales/LocaleEnglish/2.h"
#include "zombie/profanity/locales/LocaleEnglish/3.h"
#include "zombie/profanity/locales/LocaleEnglish/4.h"
#include "zombie/profanity/locales/LocaleEnglish/5.h"
#include "zombie/profanity/locales/LocaleEnglish/6.h"
#include "zombie/profanity/locales/LocaleEnglish/7.h"
#include "zombie/profanity/locales/LocaleEnglish/8.h"
#include "zombie/profanity/locales/LocaleEnglish/9.h"

namespace zombie {
namespace profanity {
namespace locales {


class LocaleEnglish : public Locale {
public:
    public LocaleEnglish(const std::string& var1) {
      super(var1);
   }

    void Init() {
      this.storeVowelsAmount = 3;
      this.addFilterRawWord("ass");
      this.addPhonizer(std::make_shared<1>(this, "strt", "(?<strt>^(?:KN|GN|PN|AE|WR))"));
      this.addPhonizer(std::make_shared<2>(this, "dropY", "(?<dropY>(?<=M)B$)"));
      this.addPhonizer(std::make_shared<3>(this, "dropB", "(?<dropB>(?<=M)B$)"));
      this.addPhonizer(std::make_shared<4>(this, "z", "(?<z>Z)"));
      this.addPhonizer(std::make_shared<5>(this, "ck", "(?<ck>CK)"));
      this.addPhonizer(std::make_shared<6>(this, "q", "(?<q>Q)"));
      this.addPhonizer(std::make_shared<7>(this, "v", "(?<v>V)"));
      this.addPhonizer(std::make_shared<8>(this, "xS", "(?<xS>^X)"));
      this.addPhonizer(std::make_shared<9>(this, "xKS", "(?<xKS>(?<=\\w)X)"));
      this.addPhonizer(std::make_shared<10>(this, "ph", "(?<ph>PH)"));
      this.addPhonizer(std::make_shared<11>(this, "c", "(?<c>C(?=[AUOIE]))"));
   }
}
} // namespace locales
} // namespace profanity
} // namespace zombie
