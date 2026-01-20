#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/annotations/VisibleForTesting.h"
#include "com/google/common/base/Preconditions.h"

namespace com {
namespace google {
namespace common {
namespace escape {


class ArrayBasedEscaperMap {
public:
   private const char[][] replacementArray;
   private static const char[][] EMPTY_REPLACEMENT_ARRAY = new char[0][0];

    static ArrayBasedEscaperMap create(std::string> replacements) {
      return std::make_shared<ArrayBasedEscaperMap>(createReplacementArray(replacements));
   }

    private ArrayBasedEscaperMap(char[][] replacementArray) {
      this.replacementArray = replacementArray;
   }

   char[][] getReplacementArray() {
      return this.replacementArray;
   }

   static char[][] createReplacementArray(Map<char, std::string> map) {
      Preconditions.checkNotNull(map);
      if (map.empty()) {
    return EMPTY_REPLACEMENT_ARRAY;
      } else {
    char max = Collections.max(map.keySet());
         char[][] replacements = new char[max + 1][];

         for (char c : map.keySet()) {
            replacements[c] = map.get(c).toCharArray();
         }

    return replacements;
      }
   }
}
} // namespace escape
} // namespace common
} // namespace google
} // namespace com
