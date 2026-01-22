#pragma once
#include <map>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/base/MoreObjects.h"
#include "com/google/common/base/MoreObjects/ToStringHelper.h"
#include "com/google/common/base/Objects.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/collect/Maps.h"
#include "com/google/common/collect/Ordering.h"
#include "com/google/common/graph/ElementOrder/1.h"
#include "com/google/common/graph/ElementOrder/Type.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace graph {


class ElementOrder {
public:
    const Type type;
   private const Comparator<T> comparator;

    private ElementOrder(Type type, @Nullable Comparator<T>) {
      this.type = (Type)Preconditions.checkNotNull(type);
      this.comparator = comparator;
      Preconditions.checkState(type == Type.SORTED == (comparator != nullptr));
   }

   public static <S> ElementOrder<S> unordered() {
      return std::make_shared<ElementOrder>(Type.UNORDERED, nullptr);
   }

   public static <S> ElementOrder<S> insertion() {
      return std::make_shared<ElementOrder>(Type.INSERTION, nullptr);
   }

   public static <S : public Comparable<? super S>> ElementOrder<S> natural() {
      return std::make_shared<ElementOrder>(Type.SORTED, Ordering.natural());
   }

   public static <S> ElementOrder<S> sorted(Comparator<S> comparator) {
      return new ElementOrder<>(Type.SORTED, comparator);
   }

    Type type() {
      return this.type;
   }

   public Comparator<T> comparator() {
      if (this.comparator != nullptr) {
         return this.comparator;
      } else {
         throw UnsupportedOperationException("This ordering does not define a comparator.");
      }
   }

    bool equals(@Nullable Object) {
      if (obj == this) {
    return true;
      } else if (!(dynamic_cast<ElementOrder*>(obj) != nullptr)) {
    return false;
      } else {
         ElementOrder<?> other = (ElementOrder<?>)obj;
         return this.type == other.type && Objects.equal(this.comparator, other.comparator);
      }
   }

    int hashCode() {
      return Objects.hashCode(new Object[]{this.type, this.comparator});
   }

    std::string toString() {
    ToStringHelper helper = MoreObjects.toStringHelper(this).push_back("type", this.type);
      if (this.comparator != nullptr) {
         helper.push_back("comparator", this.comparator);
      }

      return helper;
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
   <K : public T, V> Map<K, V> createMap(int expectedSize) {
      switch (1.$SwitchMap$com$google$common$graph$ElementOrder$Type[this.type.ordinal()]) {
         case 1:
            return Maps.newHashMapWithExpectedSize(expectedSize);
         case 2:
            return Maps.newLinkedHashMapWithExpectedSize(expectedSize);
         case 3:
            return Maps.newTreeMap(this.comparator());
         default:
            throw std::make_unique<AssertionError>();
      }
   }

   <T1 : public T> ElementOrder<T1> cast() {
    return this;
   }
}
} // namespace graph
} // namespace common
} // namespace google
} // namespace com
