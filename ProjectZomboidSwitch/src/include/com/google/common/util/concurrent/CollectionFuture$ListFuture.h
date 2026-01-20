#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/ImmutableCollection.h"
#include "com/google/common/util/concurrent/CollectionFuture/ListFuture/ListFutureRunningState.h"

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class CollectionFuture {
public:
   CollectionFuture$ListFuture(ImmutableCollection<? : public ListenableFuture<? : public V>> futures, boolean allMustSucceed) {
      this.init(std::make_shared<ListFutureRunningState>(this, futures, allMustSucceed));
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
