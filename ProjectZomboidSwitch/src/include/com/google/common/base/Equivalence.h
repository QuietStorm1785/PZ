#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/base/Equivalence/Equals.h"
#include "com/google/common/base/Equivalence/EquivalentToPredicate.h"
#include "com/google/common/base/Equivalence/Identity.h"
#include "com/google/common/base/Equivalence/Wrapper.h"
#include "javax/annotation/Nullable.h"

namespace com {
namespace google {
namespace common {
namespace base {


class Equivalence {
public:
    protected Equivalence() {
   }

    bool equivalent(@Nullable T, @Nullable T) {
      if (a == b) {
    return true;
      } else {
         return a != nullptr && b != nullptr ? this.doEquivalent(a, b) : false;
      }
   }

   protected abstract boolean doEquivalent(T var1, T var2);

    int hash(@Nullable T) {
    return t = = nullptr ? 0 : this.doHash(t);
   }

   protected abstract int doHash(T var1);

   public const <F> Equivalence<F> onResultOf(Function<F, ? : public T> function) {
      return std::make_shared<FunctionalEquivalence>(function, this);
   }

   public const <S : public T> Wrapper<S> wrap(@Nullable S reference) {
      return std::make_shared<Wrapper>(this, reference, nullptr);
   }

   public const <S : public T> Equivalence<Iterable<S>> pairwise() {
      return std::make_shared<PairwiseEquivalence>(this);
   }

   public const Predicate<T> equivalentTo(@Nullable T target) {
      return std::make_shared<EquivalentToPredicate>(this, target);
   }

   public static Equivalence<Object> equals() {
      return Equals.INSTANCE;
   }

   public static Equivalence<Object> identity() {
      return Identity.INSTANCE;
   }
}
} // namespace base
} // namespace common
} // namespace google
} // namespace com
