#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/common/util/concurrent/ForwardingListenableFuture/SimpleForwardingListenableFuture.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class AbstractCheckedFuture {
public:
    protected AbstractCheckedFuture(ListenableFuture<V> delegate) {
      super(delegate);
   }

   protected abstract X mapException(Exception var1);

    V checkedGet() {
      try {
         return (V)this.get();
      } catch (InterruptedException var2) {
         Thread.currentThread().interrupt();
         throw this.mapException(var2);
      } catch (CancellationException var3) {
         throw this.mapException(var3);
      } catch (ExecutionException var4) {
         throw this.mapException(var4);
      }
   }

    V checkedGet(long timeout, TimeUnit unit) {
      try {
         return (V)this.get(timeout, unit);
      } catch (InterruptedException var5) {
         Thread.currentThread().interrupt();
         throw this.mapException(var5);
      } catch (CancellationException var6) {
         throw this.mapException(var6);
      } catch (ExecutionException var7) {
         throw this.mapException(var7);
      }
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
