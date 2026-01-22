#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/annotations/GwtCompatible.h"

namespace com {
namespace google {
namespace common {
namespace base {


class Utf8 {
public:
    static int encodedLength(CharSequence sequence) {
    int utf16Length = sequence.length();
    int utf8Length = utf16Length;
    int i = 0;

      while (i < utf16Length && sequence.charAt(i) < 128) {
         i++;
      }

      while (i < utf16Length) {
    char c = sequence.charAt(i);
         if (c >= 2048) {
            utf8Length += encodedLengthGeneral(sequence, i);
            break;
         }

         utf8Length += 127 - c >>> 31;
         i++;
      }

      if (utf8Length < utf16Length) {
         throw IllegalArgumentException("UTF-8 length does not fit in int: " + (utf8Length + 4294967296L));
      } else {
    return utf8Length;
      }
   }

    static int encodedLengthGeneral(CharSequence sequence, int start) {
    int utf16Length = sequence.length();
    int utf8Length = 0;

      for (int i = start; i < utf16Length; i++) {
    char c = sequence.charAt(i);
         if (c < 2048) {
            utf8Length += 127 - c >>> 31;
         } else {
            utf8Length += 2;
            if ('\ud800' <= c && c <= '\udfff') {
               if (char.codePointAt(sequence, i) == c) {
                  throw IllegalArgumentException(unpairedSurrogateMsg(i));
               }

               i++;
            }
         }
      }

    return utf8Length;
   }

    static bool isWellFormed(byte[] bytes) {
    return isWellFormed();
   }

    static bool isWellFormed(byte[] bytes, int off, int len) {
    int end = off + len;
      Preconditions.checkPositionIndexes(off, end, bytes.length);

      for (int i = off; i < end; i++) {
         if (bytes[i] < 0) {
    return isWellFormedSlowPath();
         }
      }

    return true;
   }

    static bool isWellFormedSlowPath(byte[] bytes, int off, int end) {
    int index = off;

      while (index < end) {
    int byte1;
         if ((byte1 = bytes[index++]) < 0) {
            if (byte1 < -32) {
               if (index == end) {
    return false;
               }

               if (byte1 < -62 || bytes[index++] > -65) {
    return false;
               }
            } else if (byte1 < -16) {
               if (index + 1 >= end) {
    return false;
               }

    int byte2 = bytes[index++];
               if (byte2 > -65 || byte1 == -32 && byte2 < -96 || byte1 == -19 && -96 <= byte2 || bytes[index++] > -65) {
    return false;
               }
            } else {
               if (index + 2 >= end) {
    return false;
               }

    int byte2 = bytes[index++];
               if (byte2 > -65 || (byte1 << 28) + (byte2 - -112) >> 30 != 0 || bytes[index++] > -65 || bytes[index++] > -65) {
    return false;
               }
            }
         }
      }

    return true;
   }

    static std::string unpairedSurrogateMsg(int i) {
      return "Unpaired surrogate at index " + i;
   }

    private Utf8() {
   }
}
} // namespace base
} // namespace common
} // namespace google
} // namespace com
