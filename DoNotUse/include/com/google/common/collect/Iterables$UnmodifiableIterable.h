#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class Iterables {
public:
   private const Iterable<? : public T> iterable;

   private Iterables$UnmodifiableIterable(Iterable<? : public T> iterable) {
      this.iterable = iterable;
   }

   public Iterator<T> iterator() {
      return Iterators.unmodifiableIterator(this.iterable.iterator());
   }

    std::string toString() {
      return this.iterable;
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
