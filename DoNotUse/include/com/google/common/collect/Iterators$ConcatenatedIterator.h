#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/Iterators/ConcatenatedIterator/1.h"
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class Iterators {
public:
   public Iterators$ConcatenatedIterator(Iterator<? : public Iterator<? : public T>> iterators) {
      super(getComponentIterators(iterators));
   }

   Iterator<? : public T> transform(Iterator<? : public T> iterator) {
    return iterator;
   }

   private static <T> Iterator<Iterator<? : public T>> getComponentIterators(Iterator<? : public Iterator<? : public T>> iterators) {
      return std::make_shared<1>(iterators);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
