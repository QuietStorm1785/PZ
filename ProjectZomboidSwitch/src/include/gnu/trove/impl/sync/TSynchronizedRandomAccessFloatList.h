#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/list/TFloatList.h"
#include <algorithm>

namespace gnu {
namespace trove {
namespace impl {
namespace sync {


class TSynchronizedRandomAccessFloatList : public TSynchronizedFloatList {
public:
    static const long serialVersionUID = 1530674583602358482L;

    public TSynchronizedRandomAccessFloatList(TFloatList list) {
      super(list);
   }

    public TSynchronizedRandomAccessFloatList(TFloatList list, void* mutex) {
      super(list, mutex);
   }

    TFloatList subList(int fromIndex, int toIndex) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return std::make_shared<TSynchronizedRandomAccessFloatList>(this.list.subList(fromIndex, toIndex), this.mutex);
      }
   }

    void* writeReplace() {
      return std::make_shared<TSynchronizedFloatList>(this.list);
   }
}
} // namespace sync
} // namespace impl
} // namespace trove
} // namespace gnu
