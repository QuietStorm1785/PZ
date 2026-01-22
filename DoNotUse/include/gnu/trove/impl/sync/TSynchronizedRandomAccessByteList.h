#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/list/TByteList.h"
#include <algorithm>

namespace gnu {
namespace trove {
namespace impl {
namespace sync {


class TSynchronizedRandomAccessByteList : public TSynchronizedByteList {
public:
    static const long serialVersionUID = 1530674583602358482L;

    public TSynchronizedRandomAccessByteList(TByteList list) {
      super(list);
   }

    public TSynchronizedRandomAccessByteList(TByteList list, void* mutex) {
      super(list, mutex);
   }

    TByteList subList(int fromIndex, int toIndex) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return std::make_shared<TSynchronizedRandomAccessByteList>(this.list.subList(fromIndex, toIndex), this.mutex);
      }
   }

    void* writeReplace() {
      return std::make_shared<TSynchronizedByteList>(this.list);
   }
}
} // namespace sync
} // namespace impl
} // namespace trove
} // namespace gnu
