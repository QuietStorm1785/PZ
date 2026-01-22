#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/escape/Escapers/1.h"
#include "com/google/common/escape/Escapers/2.h"
#include "com/google/common/escape/Escapers/Builder.h"

namespace com {
namespace google {
namespace common {
namespace escape {


class Escapers {
public:
    static const Escaper NULL_ESCAPER = std::make_shared<1>();

    private Escapers() {
   }

    static Escaper nullEscaper() {
    return NULL_ESCAPER;
   }

    static Builder builder() {
      return std::make_shared<Builder>(nullptr);
   }

    static UnicodeEscaper asUnicodeEscaper(Escaper escaper) {
      Preconditions.checkNotNull(escaper);
      if (dynamic_cast<UnicodeEscaper*>(escaper) != nullptr) {
         return (UnicodeEscaper)escaper;
      } else if (dynamic_cast<CharEscaper*>(escaper) != nullptr) {
    return wrap();
      } else {
         throw IllegalArgumentException("Cannot create a UnicodeEscaper from: " + escaper.getClass().getName());
      }
   }

    static std::string computeReplacement(CharEscaper escaper, char c) {
    return stringOrNull();
   }

    static std::string computeReplacement(UnicodeEscaper escaper, int cp) {
    return stringOrNull();
   }

    static std::string stringOrNull(char[] in) {
    return in = = nullptr ? nullptr : new std::string(in);
   }

    static UnicodeEscaper wrap(CharEscaper escaper) {
      return std::make_shared<2>(escaper);
   }
}
} // namespace escape
} // namespace common
} // namespace google
} // namespace com
