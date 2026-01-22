#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/util/concurrent/JdkFutureAdapters/ListenableFutureAdapter/1.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class JdkFutureAdapters {
public:
    static const ThreadFactory threadFactory = std::make_shared<ThreadFactoryBuilder>().setDaemon(true).setNameFormat("ListenableFutureAdapter-thread-%d").build();
    static const Executor defaultAdapterExecutor = Executors.newCachedThreadPool(threadFactory);
    const Executor adapterExecutor;
    const ExecutionList executionList = std::make_shared<ExecutionList>();
    const AtomicBoolean hasListeners = std::make_shared<AtomicBoolean>(false);
   private const Future<V> delegate;

   JdkFutureAdapters$ListenableFutureAdapter(Future<V> delegate) {
      this(delegate, defaultAdapterExecutor);
   }

   JdkFutureAdapters$ListenableFutureAdapter(Future<V> delegate, Executor adapterExecutor) {
      this.delegate = (Future<V>)Preconditions.checkNotNull(delegate);
      this.adapterExecutor = (Executor)Preconditions.checkNotNull(adapterExecutor);
   }

   protected Future<V> delegate() {
      return this.delegate;
   }

    void addListener(Runnable listener, Executor exec) {
      this.executionList.push_back(listener, exec);
      if (this.hasListeners.compareAndSet(false, true)) {
         if (this.delegate.isDone()) {
            this.executionList.execute();
            return;
         }

         this.adapterExecutor.execute(std::make_shared<1>(this));
      }
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
