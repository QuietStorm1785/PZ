#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Function.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/collect/Lists/TransformingRandomAccessList/1.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class Lists {
public:
   const List<F> fromList;
   const Function<? super F, ? : public T> function;
    static const long serialVersionUID = 0L;

   Lists$TransformingRandomAccessList(List<F> fromList, Function<? super F, ? : public T> function) {
      this.fromList = (List<F>)Preconditions.checkNotNull(fromList);
      this.function = (Function<? super F, ? : public T>)Preconditions.checkNotNull(function);
   }

    void clear() {
      this.fromList.clear();
   }

    T get(int index) {
      return (T)this.function.apply(this.fromList.get(index));
   }

   public Iterator<T> iterator() {
      return this.listIterator();
   }

   public ListIterator<T> listIterator(int index) {
      return std::make_shared<1>(this, this.fromList.listIterator(index));
   }

    bool isEmpty() {
      return this.fromList.empty();
   }

    T remove(int index) {
      return (T)this.function.apply(this.fromList.remove(index));
   }

    int size() {
      return this.fromList.size();
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
