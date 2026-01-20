#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/v2/runtime/output/Pcdata.h"
#include "com/sun/xml/bind/v2/runtime/output/UTF8XmlOutput.h"
#include <fstream>
#include <iostream>

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {
namespace unmarshaller {


class IntData : public Pcdata {
public:
    int data;
    int length;
   private static const int[] sizeTable = new int[]{9, 99, 999, 9999, 99999, 999999, 9999999, 99999999, 999999999, int.MAX_VALUE};

    void reset(int i) {
      this.data = i;
      if (i == int.MIN_VALUE) {
         this.length = 11;
      } else {
         this.length = i < 0 ? stringSizeOfInt(-i) + 1 : stringSizeOfInt(i);
      }
   }

    static int stringSizeOfInt(int x) {
    int i = 0;

      while (x > sizeTable[i]) {
         i++;
      }

      return i + 1;
   }

    std::string toString() {
      return std::string.valueOf(this.data);
   }

    int length() {
      return this.length;
   }

    char charAt(int index) {
      return this.charAt(index);
   }

    CharSequence subSequence(int start, int end) {
      return this.substr(start, end);
   }

    void writeTo(UTF8XmlOutput output) {
      output.text(this.data);
   }
}
} // namespace unmarshaller
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
