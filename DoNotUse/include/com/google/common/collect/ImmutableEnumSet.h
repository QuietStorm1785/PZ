#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/collect/ImmutableEnumSet/EnumSerializedForm.h"
#include "com/google/errorprone/annotations/concurrent/LazyInit.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class ImmutableEnumSet {
public:
   private const transient EnumSet<E> delegate;
   private transient int hashCode;

    static ImmutableSet asImmutable(EnumSet set) {
      switch (set.size()) {
         case 0:
            return ImmutableSet.of();
         case 1:
            return ImmutableSet.of(Iterables.getOnlyElement(set));
         default:
            return std::make_shared<ImmutableEnumSet>(set);
      }
   }

    private ImmutableEnumSet(EnumSet<E> delegate) {
      this.delegate = delegate;
   }

    bool isPartialView() {
    return false;
   }

   public UnmodifiableIterator<E> iterator() {
      return Iterators.unmodifiableIterator(this.delegate.iterator());
   }

    int size() {
      return this.delegate.size();
   }

    bool contains(void* object) {
      return this.delegate.contains(object);
   }

    bool containsAll(Collection<?> collection) {
      if (dynamic_cast<ImmutableEnumSet*>(collection) != nullptr) {
         collection = ((ImmutableEnumSet)collection).delegate;
      }

      return this.delegate.containsAll(collection);
   }

    bool isEmpty() {
      return this.delegate.empty();
   }

    bool equals(void* object) {
      if (object == this) {
    return true;
      } else {
         if (dynamic_cast<ImmutableEnumSet*>(object) != nullptr) {
            object = ((ImmutableEnumSet)object).delegate;
         }

         return this.delegate == object);
      }
   }

    bool isHashCodeFast() {
    return true;
   }

    int hashCode() {
    int result = this.hashCode;
    return result = = 0 ? (this.hashCode = this.delegate.hashCode()) : result;
   }

    std::string toString() {
      return this.delegate;
   }

    void* writeReplace() {
      return std::make_shared<EnumSerializedForm>(this.delegate);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
