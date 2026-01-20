#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/annotations/VisibleForTesting.h"
#include "javax/annotation/Nullable.h"

namespace com {
namespace google {
namespace common {
namespace base {


class Strings {
public:
    private Strings() {
   }

    static std::string nullToEmpty(@Nullable std::string) {
    return string = = nullptr ? "" : string;
   }

    static std::string emptyToNull(@Nullable std::string) {
    return isNullOrEmpty();
   }

    static bool isNullOrEmpty(@Nullable std::string) {
      return Platform.stringIsNullOrEmpty(string);
   }

    static std::string padStart(const std::string& string, int minLength, char padChar) {
      Preconditions.checkNotNull(string);
      if (string.length() >= minLength) {
    return string;
      } else {
    std::stringstream sb = new std::stringstream(minLength);

         for (int i = string.length(); i < minLength; i++) {
            sb.append(padChar);
         }

         sb.append(string);
         return sb;
      }
   }

    static std::string padEnd(const std::string& string, int minLength, char padChar) {
      Preconditions.checkNotNull(string);
      if (string.length() >= minLength) {
    return string;
      } else {
    std::stringstream sb = new std::stringstream(minLength);
         sb.append(string);

         for (int i = string.length(); i < minLength; i++) {
            sb.append(padChar);
         }

         return sb;
      }
   }

    static std::string repeat(const std::string& string, int count) {
      Preconditions.checkNotNull(string);
      if (count <= 1) {
         Preconditions.checkArgument(count >= 0, "invalid count: %s", count);
    return count = = 0 ? "" : string;
      } else {
    int len = string.length();
    long longSize = (long)len * count;
    int size = (int)longSize;
         if (size != longSize) {
            throw ArrayIndexOutOfBoundsException("Required array size too large: " + longSize);
         } else {
            char[] array = new char[size];
            string.getChars(0, len, array, 0);

    int n;
            for (n = len; n < size - n; n <<= 1) {
               System.arraycopy(array, 0, array, n, n);
            }

            System.arraycopy(array, 0, array, n, size - n);
            return new std::string(array);
         }
      }
   }

    static std::string commonPrefix(CharSequence a, CharSequence b) {
      Preconditions.checkNotNull(a);
      Preconditions.checkNotNull(b);
    int maxPrefixLength = Math.min(a.length(), b.length());
    int p = 0;

      while (p < maxPrefixLength && a.charAt(p) == b.charAt(p)) {
         p++;
      }

      if (validSurrogatePairAt(a, p - 1) || validSurrogatePairAt(b, p - 1)) {
         p--;
      }

      return a.subSequence(0, p);
   }

    static std::string commonSuffix(CharSequence a, CharSequence b) {
      Preconditions.checkNotNull(a);
      Preconditions.checkNotNull(b);
    int maxSuffixLength = Math.min(a.length(), b.length());
    int s = 0;

      while (s < maxSuffixLength && a.charAt(a.length() - s - 1) == b.charAt(b.length() - s - 1)) {
         s++;
      }

      if (validSurrogatePairAt(a, a.length() - s - 1) || validSurrogatePairAt(b, b.length() - s - 1)) {
         s--;
      }

      return a.subSequence(a.length() - s, a.length());
   }

    static bool validSurrogatePairAt(CharSequence string, int index) {
      return index >= 0
         && index <= string.length() - 2
         && char.isHighSurrogate(string.charAt(index))
         && char.isLowSurrogate(string.charAt(index + 1));
   }
}
} // namespace base
} // namespace common
} // namespace google
} // namespace com
