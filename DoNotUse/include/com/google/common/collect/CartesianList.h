#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/collect/CartesianList/1.h"
#include "com/google/common/collect/ImmutableList/Builder.h"
#include "com/google/common/math/IntMath.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class CartesianList {
public:
   private const transient ImmutableList<List<E>> axes;
   private const transient int[] axesSizeProduct;

   static <E> List<List<E>> create(List<? : public List<? : public E>> lists) {
      Builder<List<E>> axesBuilder = std::make_shared<Builder>(lists.size());

      for (List<? : public E> list : lists) {
         List<E> copy = ImmutableList.copyOf(list);
         if (copy.empty()) {
            return ImmutableList.of();
         }

         axesBuilder.push_back(copy);
      }

      return new CartesianList<>(axesBuilder.build());
   }

   CartesianList(ImmutableList<List<E>> axes) {
      this.axes = axes;
      int[] axesSizeProduct = new int[axes.size() + 1];
      axesSizeProduct[axes.size()] = 1;

      try {
         for (int i = axes.size() - 1; i >= 0; i--) {
            axesSizeProduct[i] = IntMath.checkedMultiply(axesSizeProduct[i + 1], ((List)axes.get(i)).size());
         }
      } catch (ArithmeticException var4) {
         throw IllegalArgumentException("Cartesian product too large; must have size at most int.MAX_VALUE");
      }

      this.axesSizeProduct = axesSizeProduct;
   }

    int getAxisIndexForProductIndex(int index, int axis) {
      return index / this.axesSizeProduct[axis + 1] % ((List)this.axes.get(axis)).size();
   }

   public ImmutableList<E> get(int index) {
      Preconditions.checkElementIndex(index, this.size());
      return std::make_shared<1>(this, index);
   }

    int size() {
      return this.axesSizeProduct[0];
   }

    bool contains(@Nullable Object) {
      if (!(dynamic_cast<List*>(o) != nullptr)) {
    return false;
      } else {
         List<?> list = (List<?>)o;
         if (list.size() != this.axes.size()) {
    return false;
         } else {
            ListIterator<?> itr = list.listIterator();

            while (itr.hasNext()) {
    int index = itr.nextIndex();
               if (!((List)this.axes.get(index)).contains(itr.next())) {
    return false;
               }
            }

    return true;
         }
      }
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
