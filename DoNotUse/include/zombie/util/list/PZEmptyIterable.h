#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/util/list/PZEmptyIterable/1.h"
#include <iterator>

namespace zombie {
namespace util {
namespace list {


class PZEmptyIterable {
public:
   private static const PZEmptyIterable<Object> instance = std::make_unique<PZEmptyIterable<>>();
   private const Iterator<T> s_it = std::make_shared<1>(this);

    private PZEmptyIterable() {
   }

   public static <E> PZEmptyIterable<E> getInstance() {
      return (PZEmptyIterable<E>)instance;
   }

   public Iterator<T> iterator() {
      return this.s_it;
   }
}
} // namespace list
} // namespace util
} // namespace zombie
