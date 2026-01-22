#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Function.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/collect/Lists/TransformingSequentialList/1.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace collect {


class Lists {
public:
   const List<F> fromList;
   const Function<? super F, ? : public T> function;
    static const long serialVersionUID = 0L;

   Lists$TransformingSequentialList(List<F> fromList, Function<? super F, ? : public T> function) {
      this.fromList = (List<F>)Preconditions.checkNotNull(fromList);
      this.function = (Function<? super F, ? : public T>)Preconditions.checkNotNull(function);
   }

    void clear() {
      this.fromList.clear();
   }

    int size() {
      return this.fromList.size();
   }

   public ListIterator<T> listIterator(int index) {
      return std::make_shared<1>(this, this.fromList.listIterator(index));
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
