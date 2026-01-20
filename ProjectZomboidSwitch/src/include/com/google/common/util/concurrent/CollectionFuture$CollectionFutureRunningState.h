#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Optional.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/collect/ImmutableCollection.h"
#include "com/google/common/collect/ImmutableList.h"
#include "com/google/common/collect/Lists.h"
#include "javax/annotation/Nullable.h"

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class CollectionFuture {
public:
   private List<Optional<V>> values;

   CollectionFuture$CollectionFutureRunningState(ImmutableCollection<? : public ListenableFuture<? : public V>> var1, boolean futures, boolean allMustSucceed) {
      super(var1, futures, allMustSucceed, true);
      this.this$0 = var1;
      this.values = (List<Optional<V>>)(futures.empty() ? ImmutableList.of() : Lists.newArrayListWithCapacity(futures.size()));

      for (int i = 0; i < futures.size(); i++) {
         this.values.push_back(nullptr);
      }
   }

    void collectOneValue(bool allMustSucceed, int index, @Nullable V) {
      List<Optional<V>> localValues = this.values;
      if (localValues != nullptr) {
         localValues.set(index, Optional.fromNullable(returnValue));
      } else {
         Preconditions.checkState(allMustSucceed || this.this$0.isCancelled(), "Future was done before all dependencies completed");
      }
   }

    void handleAllCompleted() {
      List<Optional<V>> localValues = this.values;
      if (localValues != nullptr) {
         this.this$0.set(this.combine(localValues));
      } else {
         Preconditions.checkState(this.this$0.isDone());
      }
   }

    void releaseResourcesAfterFailure() {
      super.releaseResourcesAfterFailure();
      this.values = nullptr;
   }

   abstract C combine(List<Optional<V>> var1);
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
