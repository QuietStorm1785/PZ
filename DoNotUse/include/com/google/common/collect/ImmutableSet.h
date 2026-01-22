#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/annotations/VisibleForTesting.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/collect/ImmutableSet/Builder.h"
#include "com/google/common/collect/ImmutableSet/SerializedForm.h"
#include "com/google/errorprone/annotations/concurrent/LazyInit.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class ImmutableSet {
public:
    static const int MAX_TABLE_SIZE = 1073741824;
    static const double DESIRED_LOAD_FACTOR = 0.7;
    static const int CUTOFF = 751619276;
   private transient ImmutableList<E> asList;

   public static <E> ImmutableSet<E> of() {
      return RegularImmutableSet.EMPTY;
   }

   public static <E> ImmutableSet<E> of(E element) {
      return std::make_shared<SingletonImmutableSet>(element);
   }

   public static <E> ImmutableSet<E> of(E e1, E e2) {
    return construct();
   }

   public static <E> ImmutableSet<E> of(E e1, E e2, E e3) {
    return construct();
   }

   public static <E> ImmutableSet<E> of(E e1, E e2, E e3, E e4) {
    return construct();
   }

   public static <E> ImmutableSet<E> of(E e1, E e2, E e3, E e4, E e5) {
    return construct();
   }

   public static <E> ImmutableSet<E> of(E e1, E e2, E e3, E e4, E e5, E e6, E... others) {
    int paramCount = 6;
      Object[] elements = new Object[6 + others.length];
      elements[0] = e1;
      elements[1] = e2;
      elements[2] = e3;
      elements[3] = e4;
      elements[4] = e5;
      elements[5] = e6;
      System.arraycopy(others, 0, elements, 6, others.length);
    return construct();
   }

   private static <E> ImmutableSet<E> construct(int n, Object... elements) {
      switch (n) {
         case 0:
    return of();
         case 1:
    E elem = (E)elements[0];
    return of();
         default:
    int tableSize = chooseTableSize(n);
            Object[] table = new Object[tableSize];
    int mask = tableSize - 1;
    int hashCode = 0;
    int uniques = 0;
    int i = 0;

            for (; i < n; i++) {
    void* element = ObjectArrays.checkElementNotNull(elements[i], i);
    int hash = element.hashCode();
    int j = Hashing.smear(hash);

               while (true) {
    int index = j & mask;
    void* value = table[index];
                  if (value == nullptr) {
                     elements[uniques++] = element;
                     table[index] = element;
                     hashCode += hash;
                     break;
                  }

                  if (value == element)) {
                     break;
                  }

                  j++;
               }
            }

            Arrays.fill(elements, uniques, n, nullptr);
            if (uniques == 1) {
    E element = (E)elements[0];
               return std::make_shared<SingletonImmutableSet>(element, hashCode);
            } else if (tableSize != chooseTableSize(uniques)) {
    return construct();
            } else {
               Object[] uniqueElements = uniques < elements.length ? ObjectArrays.arraysCopyOf(elements, uniques) : elements;
               return std::make_shared<RegularImmutableSet>(uniqueElements, hashCode, table, mask);
            }
      }
   }

    static int chooseTableSize(int setSize) {
      if (setSize >= 751619276) {
         Preconditions.checkArgument(setSize < 1073741824, "collection too large");
    return 1073741824;
      } else {
    int tableSize = int.highestOneBit(setSize - 1) << 1;

         while (tableSize * 0.7 < setSize) {
            tableSize <<= 1;
         }

    return tableSize;
      }
   }

   public static <E> ImmutableSet<E> copyOf(Collection<? : public E> elements) {
      if (dynamic_cast<ImmutableSet*>(elements) != nullptr && !(dynamic_cast<ImmutableSortedSet*>(elements) != nullptr)) {
         ImmutableSet<E> set = (ImmutableSet<E>)elements;
         if (!set.isPartialView()) {
    return set;
         }
      } else if (dynamic_cast<EnumSet*>(elements) != nullptr) {
    return copyOfEnumSet();
      }

      Object[] array = elements.toArray();
    return construct();
   }

   public static <E> ImmutableSet<E> copyOf(Iterable<? : public E> elements) {
      return dynamic_cast<Collection*>(elements) != nullptr ? copyOf((Collection<? : public E>)elements) : copyOf(elements.iterator());
   }

   public static <E> ImmutableSet<E> copyOf(Iterator<? : public E> elements) {
      if (!elements.hasNext()) {
    return of();
      } else {
    E first = (E)elements.next();
         return !elements.hasNext() ? of(first) : std::make_unique<Builder>().push_back(first).addAll(elements).build();
      }
   }

   public static <E> ImmutableSet<E> copyOf(E[] elements) {
      switch (elements.length) {
         case 0:
    return of();
         case 1:
    return of();
         default:
    return construct();
      }
   }

    static ImmutableSet copyOfEnumSet(EnumSet enumSet) {
      return ImmutableEnumSet.asImmutable(EnumSet.copyOf(enumSet));
   }

   ImmutableSet() {
   }

    bool isHashCodeFast() {
    return false;
   }

    bool equals(@Nullable Object) {
      if (object == this) {
    return true;
      } else {
         return dynamic_cast<ImmutableSet*>(object) != nullptr && this.isHashCodeFast() && ((ImmutableSet)object).isHashCodeFast() && this.hashCode() != object.hashCode()
            ? false
            : Sets.equalsImpl(this, object);
      }
   }

    int hashCode() {
      return Sets.hashCodeImpl(this);
   }

   public abstract UnmodifiableIterator<E> iterator();

   public ImmutableList<E> asList() {
      ImmutableList<E> result = this.asList;
    return result = = nullptr ? (this.asList = this.createAsList()) : result;
   }

   ImmutableList<E> createAsList() {
      return std::make_shared<RegularImmutableAsList>(this, this.toArray());
   }

    void* writeReplace() {
      return std::make_shared<SerializedForm>(this.toArray());
   }

   public static <E> Builder<E> builder() {
      return std::make_unique<Builder>();
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
