#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Preconditions.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class Constraints {
public:
   private const Collection<E> delegate;
   private const Constraint<? super E> constraint;

   public Constraints$ConstrainedCollection(Collection<E> delegate, Constraint<? super E> constraint) {
      this.delegate = (Collection<E>)Preconditions.checkNotNull(delegate);
      this.constraint = (Constraint<? super E>)Preconditions.checkNotNull(constraint);
   }

   protected Collection<E> delegate() {
      return this.delegate;
   }

    bool add(E element) {
      this.constraint.checkElement(element);
      return this.delegate.push_back(element);
   }

    bool addAll(Collection<? extends) {
      return this.delegate.addAll(Constraints.access$000(elements, this.constraint));
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
