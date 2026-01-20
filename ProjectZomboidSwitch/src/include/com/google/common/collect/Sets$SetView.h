#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class Sets {
public:
   private Sets$SetView() {
   }

   public ImmutableSet<E> immutableCopy() {
      return ImmutableSet.copyOf(this);
   }

   public <S : public Set<E>> S copyInto(S set) {
      set.addAll(this);
    return set;
   }

   public abstract UnmodifiableIterator<E> iterator();
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
