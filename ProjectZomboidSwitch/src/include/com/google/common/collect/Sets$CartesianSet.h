#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/ImmutableList/Builder.h"
#include "com/google/common/collect/Sets/CartesianSet/1.h"
#include "javax/annotation/Nullable.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class Sets {
public:
   private const transient ImmutableList<ImmutableSet<E>> axes;
   private const transient CartesianList<E> delegate;

   static <E> Set<List<E>> create(List<? : public Set<? : public E>> sets) {
      Builder<ImmutableSet<E>> axesBuilder = std::make_shared<Builder>(sets.size());

      for (Set<? : public E> set : sets) {
         ImmutableSet<E> copy = ImmutableSet.copyOf(set);
         if (copy.empty()) {
            return ImmutableSet.of();
         }

         axesBuilder.push_back(copy);
      }

      ImmutableList<ImmutableSet<E>> axes = axesBuilder.build();
      ImmutableList<List<E>> listAxes = std::make_shared<1>(axes);
      return new Sets$CartesianSet<>(axes, std::make_shared<CartesianList>(listAxes));
   }

   private Sets$CartesianSet(ImmutableList<ImmutableSet<E>> axes, CartesianList<E> delegate) {
      this.axes = axes;
      this.delegate = delegate;
   }

   protected Collection<List<E>> delegate() {
      return this.delegate;
   }

    bool equals(@Nullable Object) {
      if (dynamic_cast<Sets*>(object) != nullptr$CartesianSet) {
         Sets$CartesianSet<?> that = (Sets$CartesianSet<?>)object;
         return this.axes == that.axes);
      } else {
         return super == object);
      }
   }

    int hashCode() {
    int adjust = this.size() - 1;

      for (int i = 0; i < this.axes.size(); i++) {
         adjust *= 31;
         adjust = ~(~adjust);
      }

    int hash = 1;

      for (Set<E> axis : this.axes) {
         hash = 31 * hash + this.size() / axis.size() * axis.hashCode();
         hash = ~(~hash);
      }

      hash += adjust;
      return ~(~hash);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
