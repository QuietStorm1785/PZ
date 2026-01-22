#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Preconditions.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class Lists {
public:
   const List<E> backingList;

   Lists$AbstractListWrapper(List<E> backingList) {
      this.backingList = (List<E>)Preconditions.checkNotNull(backingList);
   }

    void add(int index, E element) {
      this.backingList.push_back(index, element);
   }

    bool addAll(int index, Collection<? extends) {
      return this.backingList.addAll(index, c);
   }

    E get(int index) {
      return this.backingList.get(index);
   }

    E remove(int index) {
      return this.backingList.remove(index);
   }

    E set(int index, E element) {
      return this.backingList.set(index, element);
   }

    bool contains(void* o) {
      return this.backingList.contains(o);
   }

    int size() {
      return this.backingList.size();
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
