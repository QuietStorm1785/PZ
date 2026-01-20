#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class ListeningExecutorService {
public:
    virtual ~ListeningExecutorService() = default;
   <T> ListenableFuture<T> submit(Callable<T> var1);

   ListenableFuture<?> submit(Runnable var1);

   <T> ListenableFuture<T> submit(Runnable var1, T var2);

   <T> List<Future<T>> invokeAll(Collection<? : public Callable<T>> var1) throws InterruptedException;

   <T> List<Future<T>> invokeAll(Collection<? : public Callable<T>> var1, long var2, TimeUnit var4) throws InterruptedException;
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
