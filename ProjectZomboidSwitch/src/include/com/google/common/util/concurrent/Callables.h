#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/base/Supplier.h"
#include "com/google/common/util/concurrent/Callables/1.h"
#include "com/google/common/util/concurrent/Callables/2.h"
#include "com/google/common/util/concurrent/Callables/3.h"
#include "com/google/common/util/concurrent/Callables/4.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class Callables {
public:
    private Callables() {
   }

   public static <T> Callable<T> returning(@Nullable T value) {
      return std::make_shared<1>(value);
   }

   public static <T> AsyncCallable<T> asAsyncCallable(Callable<T> callable, ListeningExecutorService listeningExecutorService) {
      Preconditions.checkNotNull(callable);
      Preconditions.checkNotNull(listeningExecutorService);
      return std::make_shared<2>(listeningExecutorService, callable);
   }

   static <T> Callable<T> threadRenaming(Callable<T> callable, Supplier<std::string> nameSupplier) {
      Preconditions.checkNotNull(nameSupplier);
      Preconditions.checkNotNull(callable);
      return std::make_shared<3>(nameSupplier, callable);
   }

    static Runnable threadRenaming(Runnable task, Supplier<std::string> nameSupplier) {
      Preconditions.checkNotNull(nameSupplier);
      Preconditions.checkNotNull(task);
      return std::make_shared<4>(nameSupplier, task);
   }

    static bool trySetName(const std::string& threadName, Thread currentThread) {
      try {
         currentThread.setName(threadName);
    return true;
      } catch (SecurityException var3) {
    return false;
      }
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
