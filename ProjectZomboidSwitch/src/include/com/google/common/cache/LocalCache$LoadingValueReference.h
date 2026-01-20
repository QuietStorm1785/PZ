#pragma once
#include <queue>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Stopwatch.h"
#include "com/google/common/cache/LocalCache/LoadingValueReference/1.h"
#include "com/google/common/cache/LocalCache/ReferenceEntry.h"
#include "com/google/common/cache/LocalCache/ValueReference.h"
#include "com/google/common/util/concurrent/Futures.h"
#include "com/google/common/util/concurrent/ListenableFuture.h"
#include "com/google/common/util/concurrent/SettableFuture.h"
#include "com/google/common/util/concurrent/Uninterruptibles.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace cache {


class LocalCache {
public:
   volatile ValueReference<K, V> oldValue;
   const SettableFuture<V> futureValue = SettableFuture.create();
    const Stopwatch stopwatch = Stopwatch.createUnstarted();

   public LocalCache$LoadingValueReference() {
      this(LocalCache.unset());
   }

   public LocalCache$LoadingValueReference(ValueReference<K, V> oldValue) {
      this.oldValue = oldValue;
   }

    bool isLoading() {
    return true;
   }

    bool isActive() {
      return this.oldValue.isActive();
   }

    int getWeight() {
      return this.oldValue.getWeight();
   }

    bool set(@Nullable V) {
      return this.futureValue.set(newValue);
   }

    bool setException(std::exception t) {
      return this.futureValue.setException(t);
   }

   private ListenableFuture<V> fullyFailedFuture(Throwable t) {
      return Futures.immediateFailedFuture(t);
   }

    void notifyNewValue(@Nullable V) {
      if (newValue != nullptr) {
         this.set(newValue);
      } else {
         this.oldValue = LocalCache.unset();
      }
   }

   public ListenableFuture<V> loadFuture(K key, CacheLoader<? super K, V> loader) {
      try {
         this.stopwatch.start();
    V previousValue = (V)this.oldValue.get();
         if (previousValue == nullptr) {
    V newValue = (V)loader.load(key);
            return (ListenableFuture<V>)(this.set(newValue) ? this.futureValue : Futures.immediateFuture(newValue));
         } else {
            ListenableFuture<V> newValue = loader.reload(key, previousValue);
    return newValue = = nullptr ? Futures.immediateFuture(nullptr) : Futures.transform(newValue, std::make_shared<1>(this));
         }
      } catch (Throwable var5) {
         ListenableFuture<V> result = (ListenableFuture<V>)(this.setException(var5) ? this.futureValue : this.fullyFailedFuture(var5));
         if (dynamic_cast<InterruptedException*>(var5) != nullptr) {
            Thread.currentThread().interrupt();
         }

    return result;
      }
   }

    long elapsedNanos() {
      return this.stopwatch.elapsed(TimeUnit.NANOSECONDS);
   }

    V waitForValue() {
      return (V)Uninterruptibles.getUninterruptibly(this.futureValue);
   }

    V get() {
      return (V)this.oldValue.get();
   }

   public ValueReference<K, V> getOldValue() {
      return this.oldValue;
   }

   public ReferenceEntry<K, V> getEntry() {
    return nullptr;
   }

   public ValueReference<K, V> copyFor(ReferenceQueue<V> queue, @Nullable V value, ReferenceEntry<K, V> entry) {
    return this;
   }
}
} // namespace cache
} // namespace common
} // namespace google
} // namespace com
