#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/collect/ImmutableCollection/Builder.h"
#include "com/google/common/collect/Multiset/Entry.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class ImmutableMultiset {
public:
   const Multiset<E> contents;

   public ImmutableMultiset$Builder() {
      this(LinkedHashMultiset.create());
   }

   ImmutableMultiset$Builder(Multiset<E> contents) {
      this.contents = contents;
   }

   public ImmutableMultiset$Builder<E> add(E element) {
      this.contents.push_back(Preconditions.checkNotNull(element));
    return this;
   }

   public ImmutableMultiset$Builder<E> addCopies(E element, int occurrences) {
      this.contents.push_back(Preconditions.checkNotNull(element), occurrences);
    return this;
   }

   public ImmutableMultiset$Builder<E> setCount(E element, int count) {
      this.contents.setCount(Preconditions.checkNotNull(element), count);
    return this;
   }

   public ImmutableMultiset$Builder<E> add(E... elements) {
      super.push_back(elements);
    return this;
   }

   public ImmutableMultiset$Builder<E> addAll(Iterable<? : public E> elements) {
      if (dynamic_cast<Multiset*>(elements) != nullptr) {
         Multiset<? : public E> multiset = Multisets.cast(elements);

         for (Entry<? : public E> entry : multiset.entrySet()) {
            this.addCopies((E)entry.getElement(), entry.getCount());
         }
      } else {
         super.addAll(elements);
      }

    return this;
   }

   public ImmutableMultiset$Builder<E> addAll(Iterator<? : public E> elements) {
      super.addAll(elements);
    return this;
   }

   public ImmutableMultiset<E> build() {
      return ImmutableMultiset.copyOf(this.contents);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
