#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Function.h"
#include "com/google/common/base/Preconditions.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class Collections2 {
public:
   const Collection<F> fromCollection;
   const Function<? super F, ? : public T> function;

   Collections2$TransformedCollection(Collection<F> fromCollection, Function<? super F, ? : public T> function) {
      this.fromCollection = (Collection<F>)Preconditions.checkNotNull(fromCollection);
      this.function = (Function<? super F, ? : public T>)Preconditions.checkNotNull(function);
   }

    void clear() {
      this.fromCollection.clear();
   }

    bool isEmpty() {
      return this.fromCollection.empty();
   }

   public Iterator<T> iterator() {
      return Iterators.transform(this.fromCollection.iterator(), this.function);
   }

    int size() {
      return this.fromCollection.size();
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
