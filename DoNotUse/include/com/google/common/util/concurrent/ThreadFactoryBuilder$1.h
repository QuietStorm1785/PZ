#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class ThreadFactoryBuilder {
public:
   ThreadFactoryBuilder$1(ThreadFactory var1, std::string var2, AtomicLong var3, bool var4, int var5, UncaughtExceptionHandler var6) {
      this.val$backingThreadFactory = var1;
      this.val$nameFormat = var2;
      this.val$count = var3;
      this.val$daemon = var4;
      this.val$priority = var5;
      this.val$uncaughtExceptionHandler = var6;
   }

    Thread newThread(Runnable runnable) {
    Thread thread = this.val$backingThreadFactory.newThread(runnable);
      if (this.val$nameFormat != nullptr) {
         thread.setName(ThreadFactoryBuilder.access$000(this.val$nameFormat, new Object[]{this.val$count.getAndIncrement()}));
      }

      if (this.val$daemon != nullptr) {
         thread.setDaemon(this.val$daemon);
      }

      if (this.val$priority != nullptr) {
         thread.setPriority(this.val$priority);
      }

      if (this.val$uncaughtExceptionHandler != nullptr) {
         thread.setUncaughtExceptionHandler(this.val$uncaughtExceptionHandler);
      }

    return thread;
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
