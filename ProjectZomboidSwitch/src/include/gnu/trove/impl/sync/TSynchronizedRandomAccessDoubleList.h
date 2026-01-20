#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/list/TDoubleList.h"
#include <algorithm>

namespace gnu {
namespace trove {
namespace impl {
namespace sync {


class TSynchronizedRandomAccessDoubleList : public TSynchronizedDoubleList {
public:
    static const long serialVersionUID = 1530674583602358482L;

    public TSynchronizedRandomAccessDoubleList(TDoubleList list) {
      super(list);
   }

    public TSynchronizedRandomAccessDoubleList(TDoubleList list, void* mutex) {
      super(list, mutex);
   }

    TDoubleList subList(int fromIndex, int toIndex) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return std::make_shared<TSynchronizedRandomAccessDoubleList>(this.list.subList(fromIndex, toIndex), this.mutex);
      }
   }

    void* writeReplace() {
      return std::make_shared<TSynchronizedDoubleList>(this.list);
   }
}
} // namespace sync
} // namespace impl
} // namespace trove
} // namespace gnu
