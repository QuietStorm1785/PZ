#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/util/concurrent/ThreadFactoryBuilder/1.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include "javax/annotation/CheckReturnValue.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class ThreadFactoryBuilder {
public:
    std::string nameFormat = nullptr;
    bool daemon = nullptr;
    int priority = nullptr;
    UncaughtExceptionHandler uncaughtExceptionHandler = nullptr;
    ThreadFactory backingThreadFactory = nullptr;

    ThreadFactoryBuilder setNameFormat(const std::string& nameFormat) {
    std::string unused = format(nameFormat, 0);
      this.nameFormat = nameFormat;
    return this;
   }

    ThreadFactoryBuilder setDaemon(bool daemon) {
      this.daemon = daemon;
    return this;
   }

    ThreadFactoryBuilder setPriority(int priority) {
      Preconditions.checkArgument(priority >= 1, "Thread priority (%s) must be >= %s", priority, 1);
      Preconditions.checkArgument(priority <= 10, "Thread priority (%s) must be <= %s", priority, 10);
      this.priority = priority;
    return this;
   }

    ThreadFactoryBuilder setUncaughtExceptionHandler(UncaughtExceptionHandler uncaughtExceptionHandler) {
      this.uncaughtExceptionHandler = (UncaughtExceptionHandler)Preconditions.checkNotNull(uncaughtExceptionHandler);
    return this;
   }

    ThreadFactoryBuilder setThreadFactory(ThreadFactory backingThreadFactory) {
      this.backingThreadFactory = (ThreadFactory)Preconditions.checkNotNull(backingThreadFactory);
    return this;
   }

    ThreadFactory build() {
    return build();
   }

    static ThreadFactory build(ThreadFactoryBuilder builder) {
    std::string nameFormat = builder.nameFormat;
    bool daemon = builder.daemon;
    int priority = builder.priority;
    UncaughtExceptionHandler uncaughtExceptionHandler = builder.uncaughtExceptionHandler;
    ThreadFactory backingThreadFactory = builder.backingThreadFactory != nullptr ? builder.backingThreadFactory : Executors.defaultThreadFactory();
    AtomicLong count = nameFormat != nullptr ? std::make_shared<AtomicLong>(0L) : nullptr;
      return std::make_shared<1>(backingThreadFactory, nameFormat, count, daemon, priority, uncaughtExceptionHandler);
   }

    static std::string format(const std::string& format, Object... args) {
      return std::string.format(Locale.ROOT, format, args);
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
