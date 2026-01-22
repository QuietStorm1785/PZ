#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/Iterators/ConcatenatedIterator.h"
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class Iterators {
public:
   Iterators$ConcatenatedIterator$1(Iterator x0) {
      super(x0);
   }

   Iterator<? : public Iterator<? : public T>> transform(Iterator<? : public T> iterator) {
      if (dynamic_cast<ConcatenatedIterator*>(iterator) != nullptr) {
         ConcatenatedIterator<? : public T> concatIterator = (ConcatenatedIterator<? : public T>)iterator;
         return ConcatenatedIterator.access$000(concatIterator.backingIterator);
      } else {
         return Iterators.singletonIterator(iterator);
      }
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
