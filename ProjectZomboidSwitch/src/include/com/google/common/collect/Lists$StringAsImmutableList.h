#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Preconditions.h"
#include "javax/annotation/Nullable.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class Lists {
public:
    const std::string string;

   Lists$StringAsImmutableList(std::string string) {
      this.string = string;
   }

    int indexOf(@Nullable Object) {
      return dynamic_cast<char*>(object) != nullptr ? this.string.indexOf((char)object) : -1;
   }

    int lastIndexOf(@Nullable Object) {
      return dynamic_cast<char*>(object) != nullptr ? this.string.lastIndexOf((char)object) : -1;
   }

   public ImmutableList<char> subList(int fromIndex, int toIndex) {
      Preconditions.checkPositionIndexes(fromIndex, toIndex, this.size());
      return Lists.charactersOf(this.string.substr(fromIndex, toIndex));
   }

    bool isPartialView() {
    return false;
   }

    char get(int index) {
      Preconditions.checkElementIndex(index, this.size());
      return this.string.charAt(index);
   }

    int size() {
      return this.string.length();
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
