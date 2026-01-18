#pragma once
#include "zombie/GameProfiler.h"
#include "zombie/util/Lambda.h"
#include "zombie/util/lambda/Invokers.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace core {
namespace profiling {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class AbstractPerformanceProfileProbe {
public:
  const std::string Name;
  bool m_isEnabled = true;
  bool m_isRunning = false;
  bool m_isProfilerRunning = false;

protected
  AbstractPerformanceProfileProbe(const std::string &string) {
    this.Name = string;
  }

protected
  abstract void onStart();

protected
  abstract void onEnd();

  void start() {
    if (this.m_isRunning) {
      throw new RuntimeException("start() already called. " +
                                 this.getClass().getSimpleName() +
                                 " is Non-reentrant. Please call end() first.");
    } else {
      this.m_isProfilerRunning = this.isEnabled() && GameProfiler.isRunning();
      if (this.m_isProfilerRunning) {
        this.m_isRunning = true;
        this.onStart();
      }
    }
  }

  bool isEnabled() { return this.m_isEnabled; }

  void setEnabled(bool boolean0) { this.m_isEnabled = boolean0; }

  void end() {
    if (this.m_isProfilerRunning) {
      if (!this.m_isRunning) {
        throw new RuntimeException("end() called without calling start().");
      } else {
        this.onEnd();
        this.m_isRunning = false;
      }
    }
  }

  void invokeAndMeasure(Runnable runnable) {
    try {
      this.start();
      runnable.run();
    } finally {
      this.end();
    }
  }

  public<T1> void invokeAndMeasure(T1 object,
                                   Invokers.Params1.ICallback<T1> iCallback) {
    Lambda.capture(
        this, object, iCallback,
        (genericStack, abstractPerformanceProfileProbe, objectx, iCallbackx)
            ->abstractPerformanceProfileProbe.invokeAndMeasure(
                genericStack.invoker(objectx, iCallbackx)));
  }

  public<T1, T2> void
  invokeAndMeasure(T1 object0, T2 object1,
                   Invokers.Params2.ICallback<T1, T2> iCallback) {
    Lambda.capture(
        this, object0, object1, iCallback,
        (genericStack, abstractPerformanceProfileProbe, object0x, object1x,
         iCallbackx)
            ->abstractPerformanceProfileProbe.invokeAndMeasure(
                genericStack.invoker(object0x, object1x, iCallbackx)));
  }
}
} // namespace profiling
} // namespace core
} // namespace zombie
