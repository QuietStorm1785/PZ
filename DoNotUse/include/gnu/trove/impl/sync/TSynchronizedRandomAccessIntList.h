#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/list/TIntList.h"
#include <algorithm>

namespace gnu {
namespace trove {
namespace impl {
namespace sync {


class TSynchronizedRandomAccessIntList : public TSynchronizedIntList {
public:
    static const long serialVersionUID = 1530674583602358482L;

    public TSynchronizedRandomAccessIntList(TIntList list) {
      super(list);
   }

    public TSynchronizedRandomAccessIntList(TIntList list, void* mutex) {
      super(list, mutex);
   }

    TIntList subList(int fromIndex, int toIndex) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return std::make_shared<TSynchronizedRandomAccessIntList>(this.list.subList(fromIndex, toIndex), this.mutex);
      }
   }

    void* writeReplace() {
      return std::make_shared<TSynchronizedIntList>(this.list);
   }
}
} // namespace sync
} // namespace impl
} // namespace trove
} // namespace gnu
