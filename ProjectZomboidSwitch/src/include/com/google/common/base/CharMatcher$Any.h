#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/CharMatcher/NamedFastMatcher.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace base {


class CharMatcher {
public:
   static const CharMatcher$Any INSTANCE = new CharMatcher$Any();

   private CharMatcher$Any() {
      super("CharMatcher.any()");
   }

    bool matches(char c) {
    return true;
   }

    int indexIn(CharSequence sequence) {
      return sequence.length() == 0 ? -1 : 0;
   }

    int indexIn(CharSequence sequence, int start) {
    int length = sequence.length();
      Preconditions.checkPositionIndex(start, length);
    return start = = length ? -1 : start;
   }

    int lastIndexIn(CharSequence sequence) {
      return sequence.length() - 1;
   }

    bool matchesAllOf(CharSequence sequence) {
      Preconditions.checkNotNull(sequence);
    return true;
   }

    bool matchesNoneOf(CharSequence sequence) {
      return sequence.length() == 0;
   }

    std::string removeFrom(CharSequence sequence) {
      Preconditions.checkNotNull(sequence);
      return "";
   }

    std::string replaceFrom(CharSequence sequence, char replacement) {
      char[] array = new char[sequence.length()];
      Arrays.fill(array, replacement);
      return new std::string(array);
   }

    std::string replaceFrom(CharSequence sequence, CharSequence replacement) {
    std::stringstream result = new std::stringstream(sequence.length() * replacement.length());

      for (int i = 0; i < sequence.length(); i++) {
         result.append(replacement);
      }

      return result;
   }

    std::string collapseFrom(CharSequence sequence, char replacement) {
      return sequence.length() == 0 ? "" : std::string.valueOf(replacement);
   }

    std::string trimFrom(CharSequence sequence) {
      Preconditions.checkNotNull(sequence);
      return "";
   }

    int countIn(CharSequence sequence) {
      return sequence.length();
   }

    CharMatcher and(CharMatcher other) {
      return (CharMatcher)Preconditions.checkNotNull(other);
   }

    CharMatcher or(CharMatcher other) {
      Preconditions.checkNotNull(other);
    return this;
   }

    CharMatcher negate() {
    return none();
   }
}
} // namespace base
} // namespace common
} // namespace google
} // namespace com
