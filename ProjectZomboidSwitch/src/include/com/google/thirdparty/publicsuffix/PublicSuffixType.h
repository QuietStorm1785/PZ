#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"

namespace com {
namespace google {
namespace thirdparty {
namespace publicsuffix {


enum class PublicSuffixType {
   PRIVATE(':', ','),
   ICANN('!', '?');

    const char innerNodeCode;
    const char leafNodeCode;

    private PublicSuffixType(char innerNodeCode, char leafNodeCode) {
      this.innerNodeCode = innerNodeCode;
      this.leafNodeCode = leafNodeCode;
   }

    char getLeafNodeCode() {
      return this.leafNodeCode;
   }

    char getInnerNodeCode() {
      return this.innerNodeCode;
   }

    static PublicSuffixType fromCode(char code) {
      for (PublicSuffixType value : values()) {
         if (value.getInnerNodeCode() == code || value.getLeafNodeCode() == code) {
    return value;
         }
      }

      throw IllegalArgumentException("No enum corresponding to given code: " + code);
   }

    static PublicSuffixType fromIsPrivate(bool isPrivate) {
      return isPrivate ? PRIVATE : ICANN;
   }
}
} // namespace publicsuffix
} // namespace thirdparty
} // namespace google
} // namespace com
