#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/base/Preconditions.h"
#include "javax/annotation/Nullable.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class ForwardingSet {
public:
    protected ForwardingSet() {
   }

   protected abstract Set<E> delegate();

    bool equals(@Nullable Object) {
    return object = = this || this.delegate() == object);
   }

    int hashCode() {
      return this.delegate().hashCode();
   }

    bool standardRemoveAll(Collection<?> collection) {
      return Sets.removeAllImpl(this, (Collection)Preconditions.checkNotNull(collection));
   }

    bool standardEquals(@Nullable Object) {
      return Sets.equalsImpl(this, object);
   }

    int standardHashCode() {
      return Sets.hashCodeImpl(this);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
