#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace com {
namespace google {
namespace common {
namespace escape {

class Escapers {
public:
   Escapers$2(CharEscaper var1) {
      this.val$escaper = var1;
   }

   protected char[] escape(int cp) {
      if (cp < 65536) {
         return this.val$escaper.escape((char)cp);
      } else {
         char[] surrogateChars = new char[2];
         char.toChars(cp, surrogateChars, 0);
         char[] hiChars = this.val$escaper.escape(surrogateChars[0]);
         char[] loChars = this.val$escaper.escape(surrogateChars[1]);
         if (hiChars == nullptr && loChars == nullptr) {
    return nullptr;
         } else {
    int hiCount = hiChars != nullptr ? hiChars.length : 1;
    int loCount = loChars != nullptr ? loChars.length : 1;
            char[] output = new char[hiCount + loCount];
            if (hiChars != nullptr) {
               for (int n = 0; n < hiChars.length; n++) {
                  output[n] = hiChars[n];
               }
            } else {
               output[0] = surrogateChars[0];
            }

            if (loChars != nullptr) {
               for (int n = 0; n < loChars.length; n++) {
                  output[hiCount + n] = loChars[n];
               }
            } else {
               output[hiCount] = surrogateChars[1];
            }

    return output;
         }
      }
   }
}
} // namespace escape
} // namespace common
} // namespace google
} // namespace com
