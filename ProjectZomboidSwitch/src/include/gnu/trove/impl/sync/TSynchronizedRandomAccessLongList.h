#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/list/TLongList.h"
#include <algorithm>

namespace gnu {
namespace trove {
namespace impl {
namespace sync {


class TSynchronizedRandomAccessLongList : public TSynchronizedLongList {
public:
    static const long serialVersionUID = 1530674583602358482L;

    public TSynchronizedRandomAccessLongList(TLongList list) {
      super(list);
   }

    public TSynchronizedRandomAccessLongList(TLongList list, void* mutex) {
      super(list, mutex);
   }

    TLongList subList(int fromIndex, int toIndex) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return std::make_shared<TSynchronizedRandomAccessLongList>(this.list.subList(fromIndex, toIndex), this.mutex);
      }
   }

    void* writeReplace() {
      return std::make_shared<TSynchronizedLongList>(this.list);
   }
}
} // namespace sync
} // namespace impl
} // namespace trove
} // namespace gnu
