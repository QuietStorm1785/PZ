#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/ImmutableSet/Indexed.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class ImmutableSet {
public:
   ImmutableSet$Indexed$1(Indexed var1) {
      this.this$0 = var1;
   }

    E get(int index) {
      return (E)this.this$0.get(index);
   }

   Indexed<E> delegateCollection() {
      return this.this$0;
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
