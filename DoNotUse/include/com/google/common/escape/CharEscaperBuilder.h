#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/escape/CharEscaperBuilder/CharArrayDecorator.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace escape {


class CharEscaperBuilder {
public:
   private const Map<char, std::string> map;
    int max = -1;

    public CharEscaperBuilder() {
      this.map = std::make_unique<std::unordered_map<>>();
   }

    CharEscaperBuilder addEscape(char c, const std::string& r) {
      this.map.put(c, (std::string)Preconditions.checkNotNull(r));
      if (c > this.max) {
         this.max = c;
      }

    return this;
   }

    CharEscaperBuilder addEscapes(char[] cs, const std::string& r) {
      Preconditions.checkNotNull(r);

    for (auto& c : cs)         this.addEscape(c, r);
      }

    return this;
   }

   public char[][] toArray() {
      char[][] result = new char[this.max + 1][];

      for (Entry<char, std::string> entry : this.map.entrySet()) {
         result[entry.getKey()] = entry.getValue().toCharArray();
      }

    return result;
   }

    Escaper toEscaper() {
      return std::make_shared<CharArrayDecorator>(this.toArray());
   }
}
} // namespace escape
} // namespace common
} // namespace google
} // namespace com
