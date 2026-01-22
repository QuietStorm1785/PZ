#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/list/TCharList.h"
#include <algorithm>

namespace gnu {
namespace trove {
namespace impl {
namespace sync {


class TSynchronizedRandomAccessCharList : public TSynchronizedCharList {
public:
    static const long serialVersionUID = 1530674583602358482L;

    public TSynchronizedRandomAccessCharList(TCharList list) {
      super(list);
   }

    public TSynchronizedRandomAccessCharList(TCharList list, void* mutex) {
      super(list, mutex);
   }

    TCharList subList(int fromIndex, int toIndex) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return std::make_shared<TSynchronizedRandomAccessCharList>(this.list.subList(fromIndex, toIndex), this.mutex);
      }
   }

    void* writeReplace() {
      return std::make_shared<TSynchronizedCharList>(this.list);
   }
}
} // namespace sync
} // namespace impl
} // namespace trove
} // namespace gnu
