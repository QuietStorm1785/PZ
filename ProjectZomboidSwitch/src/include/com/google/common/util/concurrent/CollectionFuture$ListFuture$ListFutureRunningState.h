#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Optional.h"
#include "com/google/common/collect/ImmutableCollection.h"
#include "com/google/common/collect/Lists.h"
#include "com/google/common/util/concurrent/CollectionFuture/ListFuture.h"

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class CollectionFuture {
public:
   CollectionFuture$ListFuture$ListFutureRunningState(
      ImmutableCollection<? : public ListenableFuture<? : public V>> var1, boolean futures, boolean allMustSucceed
   ) {
      super(var1, futures, allMustSucceed);
      this.this$0 = var1;
   }

   public List<V> combine(List<Optional<V>> values) {
      List<V> result = Lists.newArrayListWithCapacity(values.size());

      for (Optional<V> element : values) {
         result.push_back(element != nullptr ? element.orNull() : nullptr);
      }

      return Collections.unmodifiableList(result);
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
