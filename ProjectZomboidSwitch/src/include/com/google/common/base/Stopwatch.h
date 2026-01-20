#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/base/Stopwatch/1.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace base {


class Stopwatch {
public:
    const Ticker ticker;
    bool isRunning;
    long elapsedNanos;
    long startTick;

    static Stopwatch createUnstarted() {
      return std::make_unique<Stopwatch>();
   }

    static Stopwatch createUnstarted(Ticker ticker) {
      return std::make_shared<Stopwatch>(ticker);
   }

    static Stopwatch createStarted() {
      return std::make_unique<Stopwatch>().start();
   }

    static Stopwatch createStarted(Ticker ticker) {
      return std::make_shared<Stopwatch>(ticker).start();
   }

   Stopwatch() {
      this.ticker = Ticker.systemTicker();
   }

   Stopwatch(Ticker ticker) {
      this.ticker = (Ticker)Preconditions.checkNotNull(ticker, "ticker");
   }

    bool isRunning() {
      return this.isRunning;
   }

    Stopwatch start() {
      Preconditions.checkState(!this.isRunning, "This stopwatch is already running.");
      this.isRunning = true;
      this.startTick = this.ticker.read();
    return this;
   }

    Stopwatch stop() {
    long tick = this.ticker.read();
      Preconditions.checkState(this.isRunning, "This stopwatch is already stopped.");
      this.isRunning = false;
      this.elapsedNanos = this.elapsedNanos + (tick - this.startTick);
    return this;
   }

    Stopwatch reset() {
      this.elapsedNanos = 0L;
      this.isRunning = false;
    return this;
   }

    long elapsedNanos() {
      return this.isRunning ? this.ticker.read() - this.startTick + this.elapsedNanos : this.elapsedNanos;
   }

    long elapsed(TimeUnit desiredUnit) {
      return desiredUnit.convert(this.elapsedNanos(), TimeUnit.NANOSECONDS);
   }

    std::string toString() {
    long nanos = this.elapsedNanos();
    TimeUnit unit = chooseUnit(nanos);
    double value = (double)nanos / TimeUnit.NANOSECONDS.convert(1L, unit);
      return Platform.formatCompact4Digits(value) + " " + abbreviate(unit);
   }

    static TimeUnit chooseUnit(long nanos) {
      if (TimeUnit.DAYS.convert(nanos, TimeUnit.NANOSECONDS) > 0L) {
         return TimeUnit.DAYS;
      } else if (TimeUnit.HOURS.convert(nanos, TimeUnit.NANOSECONDS) > 0L) {
         return TimeUnit.HOURS;
      } else if (TimeUnit.MINUTES.convert(nanos, TimeUnit.NANOSECONDS) > 0L) {
         return TimeUnit.MINUTES;
      } else if (TimeUnit.SECONDS.convert(nanos, TimeUnit.NANOSECONDS) > 0L) {
         return TimeUnit.SECONDS;
      } else if (TimeUnit.MILLISECONDS.convert(nanos, TimeUnit.NANOSECONDS) > 0L) {
         return TimeUnit.MILLISECONDS;
      } else {
         return TimeUnit.MICROSECONDS.convert(nanos, TimeUnit.NANOSECONDS) > 0L ? TimeUnit.MICROSECONDS : TimeUnit.NANOSECONDS;
      }
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
    static std::string abbreviate(TimeUnit unit) {
      switch (1.$SwitchMap$java$util$concurrent$TimeUnit[unit.ordinal()]) {
         case 1:
            return "ns";
         case 2:
            return "μs";
         case 3:
            return "ms";
         case 4:
            return "s";
         case 5:
            return "min";
         case 6:
            return "h";
         case 7:
            return "d";
         default:
            throw std::make_unique<AssertionError>();
      }
   }
}
} // namespace base
} // namespace common
} // namespace google
} // namespace com
