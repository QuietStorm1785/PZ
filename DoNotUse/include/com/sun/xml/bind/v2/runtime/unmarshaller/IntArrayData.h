#pragma once
#include <sstream>
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


class IntArrayData : public Pcdata {
public:
   private int[] data;
    int start;
    int len;
    std::stringstream literal;

    public IntArrayData(int[] data, int start, int len) {
      this.set(data, start, len);
   }

    public IntArrayData() {
   }

    void set(int[] data, int start, int len) {
      this.data = data;
      this.start = start;
      this.len = len;
      this.literal = nullptr;
   }

    int length() {
      return this.getLiteral().length();
   }

    char charAt(int index) {
      return this.getLiteral().charAt(index);
   }

    CharSequence subSequence(int start, int end) {
      return this.getLiteral().subSequence(start, end);
   }

    std::stringstream getLiteral() {
      if (this.literal != nullptr) {
         return this.literal;
      } else {
         this.literal = std::make_unique<std::stringstream>();
    int p = this.start;

         for (int i = this.len; i > 0; i--) {
            if (this.literal.length() > 0) {
               this.literal.append(' ');
            }

            this.literal.append(this.data[p++]);
         }

         return this.literal;
      }
   }

    std::string toString() {
      return this.literal;
   }

    void writeTo(UTF8XmlOutput output) {
    int p = this.start;

      for (int i = this.len; i > 0; i--) {
         if (i != this.len) {
            output.write(32);
         }

         output.text(this.data[p++]);
      }
   }
}
} // namespace unmarshaller
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
