#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameProfiler.h"
#include "zombie/util/Lambda.h"
#include "zombie/util/lambda/Invokers/Params1/ICallback.h"

namespace zombie {
namespace core {
namespace profiling {


class AbstractPerformanceProfileProbe {
public:
    const std::string Name;
    bool m_isEnabled = true;
    bool m_isRunning = false;
    bool m_isProfilerRunning = false;

    protected AbstractPerformanceProfileProbe(const std::string& var1) {
      this.Name = var1;
   }

   protected abstract void onStart();

   protected abstract void onEnd();

    void start() {
      if (this.m_isRunning) {
         throw RuntimeException("start() already called. " + this.getClass().getSimpleName() + " is Non-reentrant. Please call end() first.");
      } else {
         this.m_isProfilerRunning = this.isEnabled() && GameProfiler.isRunning();
         if (this.m_isProfilerRunning) {
            this.m_isRunning = true;
            this.onStart();
         }
      }
   }

    bool isEnabled() {
      return this.m_isEnabled;
   }

    void setEnabled(bool var1) {
      this.m_isEnabled = var1;
   }

    void end() {
      if (this.m_isProfilerRunning) {
         if (!this.m_isRunning) {
            throw RuntimeException("end() called without calling start().");
         } else {
            this.onEnd();
            this.m_isRunning = false;
         }
      }
   }

    void invokeAndMeasure(Runnable var1) {
      try {
         this.start();
         var1.run();
      } finally {
         this.end();
      }
   }

   public <T1> void invokeAndMeasure(T1 var1, ICallback<T1> var2) {
      Lambda.capture(this, var1, var2, (var0, var1x, var2x, var3) -> var1x.invokeAndMeasure(var0.invoker(var2x, var3)));
   }

   public <T1, T2> void invokeAndMeasure(T1 var1, T2 var2, zombie.util.lambda.Invokers.Params2.ICallback<T1, T2> var3) {
      Lambda.capture(this, var1, var2, var3, (var0, var1x, var2x, var3x, var4) -> var1x.invokeAndMeasure(var0.invoker(var2x, var3x, var4)));
   }
}
} // namespace profiling
} // namespace core
} // namespace zombie
