#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/CharMatcher/NamedFastMatcher.h"

namespace com {
namespace google {
namespace common {
namespace base {


class CharMatcher {
public:
   static const CharMatcher$None INSTANCE = new CharMatcher$None();

   private CharMatcher$None() {
      super("CharMatcher.none()");
   }

    bool matches(char c) {
    return false;
   }

    int indexIn(CharSequence sequence) {
      Preconditions.checkNotNull(sequence);
      return -1;
   }

    int indexIn(CharSequence sequence, int start) {
    int length = sequence.length();
      Preconditions.checkPositionIndex(start, length);
      return -1;
   }

    int lastIndexIn(CharSequence sequence) {
      Preconditions.checkNotNull(sequence);
      return -1;
   }

    bool matchesAllOf(CharSequence sequence) {
      return sequence.length() == 0;
   }

    bool matchesNoneOf(CharSequence sequence) {
      Preconditions.checkNotNull(sequence);
    return true;
   }

    std::string removeFrom(CharSequence sequence) {
      return sequence;
   }

    std::string replaceFrom(CharSequence sequence, char replacement) {
      return sequence;
   }

    std::string replaceFrom(CharSequence sequence, CharSequence replacement) {
      Preconditions.checkNotNull(replacement);
      return sequence;
   }

    std::string collapseFrom(CharSequence sequence, char replacement) {
      return sequence;
   }

    std::string trimFrom(CharSequence sequence) {
      return sequence;
   }

    std::string trimLeadingFrom(CharSequence sequence) {
      return sequence;
   }

    std::string trimTrailingFrom(CharSequence sequence) {
      return sequence;
   }

    int countIn(CharSequence sequence) {
      Preconditions.checkNotNull(sequence);
    return 0;
   }

    CharMatcher and(CharMatcher other) {
      Preconditions.checkNotNull(other);
    return this;
   }

    CharMatcher or(CharMatcher other) {
      return (CharMatcher)Preconditions.checkNotNull(other);
   }

    CharMatcher negate() {
    return any();
   }
}
} // namespace base
} // namespace common
} // namespace google
} // namespace com
