#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace io {


class BaseEncoding {
public:
    int charsUntilSeparator;

   BaseEncoding$4(int var1, Appendable var2, std::string var3) {
      this.val$afterEveryChars = var1;
      this.val$delegate = var2;
      this.val$separator = var3;
      this.charsUntilSeparator = this.val$afterEveryChars;
   }

    Appendable append(char c) {
      if (this.charsUntilSeparator == 0) {
         this.val$delegate.append(this.val$separator);
         this.charsUntilSeparator = this.val$afterEveryChars;
      }

      this.val$delegate.append(c);
      this.charsUntilSeparator--;
    return this;
   }

    Appendable append(CharSequence chars, int off, int len) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    Appendable append(CharSequence chars) {
      throw std::make_unique<UnsupportedOperationException>();
   }
}
} // namespace io
} // namespace common
} // namespace google
} // namespace com
