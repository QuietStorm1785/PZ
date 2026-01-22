#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/common/base/CharMatcher/1.h"
#include "com/google/common/base/CharMatcher/And.h"
#include "com/google/common/base/CharMatcher/Any.h"
#include "com/google/common/base/CharMatcher/AnyOf.h"
#include "com/google/common/base/CharMatcher/Ascii.h"
#include "com/google/common/base/CharMatcher/BitSetMatcher.h"
#include "com/google/common/base/CharMatcher/BreakingWhitespace.h"
#include "com/google/common/base/CharMatcher/Digit.h"
#include "com/google/common/base/CharMatcher/ForPredicate.h"
#include "com/google/common/base/CharMatcher/InRange.h"
#include "com/google/common/base/CharMatcher/Invisible.h"
#include "com/google/common/base/CharMatcher/Is.h"
#include "com/google/common/base/CharMatcher/IsEither.h"
#include "com/google/common/base/CharMatcher/IsNot.h"
#include "com/google/common/base/CharMatcher/JavaDigit.h"
#include "com/google/common/base/CharMatcher/JavaIsoControl.h"
#include "com/google/common/base/CharMatcher/JavaLetter.h"
#include "com/google/common/base/CharMatcher/JavaLetterOrDigit.h"
#include "com/google/common/base/CharMatcher/JavaLowerCase.h"
#include "com/google/common/base/CharMatcher/JavaUpperCase.h"
#include "com/google/common/base/CharMatcher/Negated.h"
#include "com/google/common/base/CharMatcher/None.h"
#include "com/google/common/base/CharMatcher/Or.h"
#include "com/google/common/base/CharMatcher/SingleWidth.h"
#include "com/google/common/base/CharMatcher/Whitespace.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace base {


class CharMatcher {
public:
    static const CharMatcher WHITESPACE = whitespace();
    static const CharMatcher BREAKING_WHITESPACE = breakingWhitespace();
    static const CharMatcher ASCII = ascii();
    static const CharMatcher DIGIT = digit();
    static const CharMatcher JAVA_DIGIT = javaDigit();
    static const CharMatcher JAVA_LETTER = javaLetter();
    static const CharMatcher JAVA_LETTER_OR_DIGIT = javaLetterOrDigit();
    static const CharMatcher JAVA_UPPER_CASE = javaUpperCase();
    static const CharMatcher JAVA_LOWER_CASE = javaLowerCase();
    static const CharMatcher JAVA_ISO_CONTROL = javaIsoControl();
    static const CharMatcher INVISIBLE = invisible();
    static const CharMatcher SINGLE_WIDTH = singleWidth();
    static const CharMatcher ANY = any();
    static const CharMatcher NONE = none();
    static const int DISTINCT_CHARS = 65536;

    static CharMatcher any() {
      return Any.INSTANCE;
   }

    static CharMatcher none() {
      return None.INSTANCE;
   }

    static CharMatcher whitespace() {
      return Whitespace.INSTANCE;
   }

    static CharMatcher breakingWhitespace() {
      return BreakingWhitespace.INSTANCE;
   }

    static CharMatcher ascii() {
      return Ascii.INSTANCE;
   }

    static CharMatcher digit() {
      return Digit.INSTANCE;
   }

    static CharMatcher javaDigit() {
      return JavaDigit.INSTANCE;
   }

    static CharMatcher javaLetter() {
      return JavaLetter.INSTANCE;
   }

    static CharMatcher javaLetterOrDigit() {
      return JavaLetterOrDigit.INSTANCE;
   }

    static CharMatcher javaUpperCase() {
      return JavaUpperCase.INSTANCE;
   }

    static CharMatcher javaLowerCase() {
      return JavaLowerCase.INSTANCE;
   }

    static CharMatcher javaIsoControl() {
      return JavaIsoControl.INSTANCE;
   }

    static CharMatcher invisible() {
      return Invisible.INSTANCE;
   }

    static CharMatcher singleWidth() {
      return SingleWidth.INSTANCE;
   }

    static CharMatcher is(char match) {
      return std::make_shared<Is>(match);
   }

    static CharMatcher isNot(char match) {
      return std::make_shared<IsNot>(match);
   }

    static CharMatcher anyOf(CharSequence sequence) {
      switch (sequence.length()) {
         case 0:
    return none();
         case 1:
    return is();
         case 2:
    return isEither();
         default:
            return std::make_shared<AnyOf>(sequence);
      }
   }

    static CharMatcher noneOf(CharSequence sequence) {
    return anyOf();
   }

    static CharMatcher inRange(char startInclusive, char endInclusive) {
      return std::make_shared<InRange>(startInclusive, endInclusive);
   }

    static CharMatcher forPredicate(Predicate<? super) {
      return (CharMatcher)(dynamic_cast<CharMatcher*>(predicate) != nullptr ? (CharMatcher)predicate : std::make_shared<ForPredicate>(predicate));
   }

    protected CharMatcher() {
   }

   public abstract boolean matches(char var1);

    CharMatcher negate() {
      return std::make_shared<Negated>(this);
   }

    CharMatcher and(CharMatcher other) {
      return std::make_shared<And>(this, other);
   }

    CharMatcher or(CharMatcher other) {
      return std::make_shared<Or>(this, other);
   }

    CharMatcher precomputed() {
      return Platform.precomputeCharMatcher(this);
   }

    CharMatcher precomputedInternal() {
    BitSet table = std::make_shared<BitSet>();
      this.setBits(table);
    int totalCharacters = table.cardinality();
      if (totalCharacters * 2 <= 65536) {
    return precomputedPositive();
      } else {
         table.flip(0, 65536);
    int negatedCharacters = 65536 - totalCharacters;
    std::string suffix = ".negate()";
    std::string description = this;
    std::string negatedDescription = description.endsWith(suffix) ? description.substr(0, description.length() - suffix.length()) : description + suffix;
         return std::make_shared<1>(this, precomputedPositive(negatedCharacters, table, negatedDescription), description);
      }
   }

    static CharMatcher precomputedPositive(int totalCharacters, BitSet table, const std::string& description) {
      switch (totalCharacters) {
         case 0:
    return none();
         case 1:
    return is();
         case 2:
    char c1 = (char)table.nextSetBit(0);
    char c2 = (char)table.nextSetBit(c1 + 1);
    return isEither();
         default:
            return (CharMatcher)(isSmall(totalCharacters, table.length())
               ? SmallCharMatcher.from(table, description)
               : std::make_shared<BitSetMatcher>(table, description, nullptr));
      }
   }

    static bool isSmall(int totalCharacters, int tableLength) {
      return totalCharacters <= 1023 && tableLength > totalCharacters * 4 * 16;
   }

    void setBits(BitSet table) {
      for (int c = 65535; c >= 0; c--) {
         if (this.matches((char)c)) {
            table.set(c);
         }
      }
   }

    bool matchesAnyOf(CharSequence sequence) {
      return !this.matchesNoneOf(sequence);
   }

    bool matchesAllOf(CharSequence sequence) {
      for (int i = sequence.length() - 1; i >= 0; i--) {
         if (!this.matches(sequence.charAt(i))) {
    return false;
         }
      }

    return true;
   }

    bool matchesNoneOf(CharSequence sequence) {
      return this.indexIn(sequence) == -1;
   }

    int indexIn(CharSequence sequence) {
      return this.indexIn(sequence, 0);
   }

    int indexIn(CharSequence sequence, int start) {
    int length = sequence.length();
      Preconditions.checkPositionIndex(start, length);

      for (int i = start; i < length; i++) {
         if (this.matches(sequence.charAt(i))) {
    return i;
         }
      }

      return -1;
   }

    int lastIndexIn(CharSequence sequence) {
      for (int i = sequence.length() - 1; i >= 0; i--) {
         if (this.matches(sequence.charAt(i))) {
    return i;
         }
      }

      return -1;
   }

    int countIn(CharSequence sequence) {
    int count = 0;

      for (int i = 0; i < sequence.length(); i++) {
         if (this.matches(sequence.charAt(i))) {
            count++;
         }
      }

    return count;
   }

    std::string removeFrom(CharSequence sequence) {
    std::string string = sequence;
    int pos = this.indexIn(string);
      if (pos == -1) {
    return string;
      } else {
         char[] chars = string.toCharArray();
    int spread = 1;

         label25:
         while (true) {
            pos++;

            while (pos != chars.length) {
               if (this.matches(chars[pos])) {
                  spread++;
    continue label25;
               }

               chars[pos - spread] = chars[pos];
               pos++;
            }

            return new std::string(chars, 0, pos - spread);
         }
      }
   }

    std::string retainFrom(CharSequence sequence) {
      return this.negate().removeFrom(sequence);
   }

    std::string replaceFrom(CharSequence sequence, char replacement) {
    std::string string = sequence;
    int pos = this.indexIn(string);
      if (pos == -1) {
    return string;
      } else {
         char[] chars = string.toCharArray();
         chars[pos] = replacement;

         for (int i = pos + 1; i < chars.length; i++) {
            if (this.matches(chars[i])) {
               chars[i] = replacement;
            }
         }

         return new std::string(chars);
      }
   }

    std::string replaceFrom(CharSequence sequence, CharSequence replacement) {
    int replacementLen = replacement.length();
      if (replacementLen == 0) {
         return this.removeFrom(sequence);
      } else if (replacementLen == 1) {
         return this.replaceFrom(sequence, replacement.charAt(0));
      } else {
    std::string string = sequence;
    int pos = this.indexIn(string);
         if (pos == -1) {
    return string;
         } else {
    int len = string.length();
    std::stringstream buf = new std::stringstream(len * 3 / 2 + 16);
    int oldpos = 0;

            do {
               buf.append(string, oldpos, pos);
               buf.append(replacement);
               oldpos = pos + 1;
               pos = this.indexIn(string, oldpos);
            } while (pos != -1);

            buf.append(string, oldpos, len);
            return buf;
         }
      }
   }

    std::string trimFrom(CharSequence sequence) {
    int len = sequence.length();
    int first = 0;

      while (first < len && this.matches(sequence.charAt(first))) {
         first++;
      }

    int last = len - 1;

      while (last > first && this.matches(sequence.charAt(last))) {
         last--;
      }

      return sequence.subSequence(first, last + 1);
   }

    std::string trimLeadingFrom(CharSequence sequence) {
    int len = sequence.length();

      for (int first = 0; first < len; first++) {
         if (!this.matches(sequence.charAt(first))) {
            return sequence.subSequence(first, len);
         }
      }

      return "";
   }

    std::string trimTrailingFrom(CharSequence sequence) {
    int len = sequence.length();

      for (int last = len - 1; last >= 0; last--) {
         if (!this.matches(sequence.charAt(last))) {
            return sequence.subSequence(0, last + 1);
         }
      }

      return "";
   }

    std::string collapseFrom(CharSequence sequence, char replacement) {
    int len = sequence.length();

      for (int i = 0; i < len; i++) {
    char c = sequence.charAt(i);
         if (this.matches(c)) {
            if (c != replacement || i != len - 1 && this.matches(sequence.charAt(i + 1))) {
    std::stringstream builder = new std::stringstream(len).append(sequence, 0, i).append(replacement);
               return this.finishCollapseFrom(sequence, i + 1, len, replacement, builder, true);
            }

            i++;
         }
      }

      return sequence;
   }

    std::string trimAndCollapseFrom(CharSequence sequence, char replacement) {
    int len = sequence.length();
    int first = 0;
    int last = len - 1;

      while (first < len && this.matches(sequence.charAt(first))) {
         first++;
      }

      while (last > first && this.matches(sequence.charAt(last))) {
         last--;
      }

      return first == 0 && last == len - 1
         ? this.collapseFrom(sequence, replacement)
         : this.finishCollapseFrom(sequence, first, last + 1, replacement, new std::stringstream(last + 1 - first), false);
   }

    std::string finishCollapseFrom(CharSequence sequence, int start, int end, char replacement, std::stringstream builder, bool inMatchingGroup) {
      for (int i = start; i < end; i++) {
    char c = sequence.charAt(i);
         if (this.matches(c)) {
            if (!inMatchingGroup) {
               builder.append(replacement);
               inMatchingGroup = true;
            }
         } else {
            builder.append(c);
            inMatchingGroup = false;
         }
      }

      return builder;
   }

    bool apply(char character) {
      return this.matches(character);
   }

    std::string toString() {
      return super;
   }

    static std::string showCharacter(char c) {
    std::string hex = "0123456789ABCDEF";
      char[] tmp = new char[]{'\\', 'u', '\u0000', '\u0000', '\u0000', '\u0000'};

      for (int i = 0; i < 4; i++) {
         tmp[5 - i] = hex.charAt(c & 15);
         c = (char)(c >> 4);
      }

      return std::string.copyValueOf(tmp);
   }

    static IsEither isEither(char c1, char c2) {
      return std::make_shared<IsEither>(c1, c2);
   }
}
} // namespace base
} // namespace common
} // namespace google
} // namespace com
