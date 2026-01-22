#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/util/concurrent/InterruptibleTask/AtomicHelper.h"
#include "com/google/common/util/concurrent/InterruptibleTask/SafeAtomicHelper.h"
#include "com/google/common/util/concurrent/InterruptibleTask/SynchronizedAtomicHelper.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class InterruptibleTask {
public:
   private volatile Thread runner;
   private volatile boolean doneInterrupting;
    static const AtomicHelper ATOMIC_HELPER;
    static const Logger log = Logger.getLogger(InterruptibleTask.class.getName());

    void run() {
      if (ATOMIC_HELPER.compareAndSetRunner(this, nullptr, Thread.currentThread())) {
         try {
            this.runInterruptibly();
         } finally {
            if (this.wasInterrupted()) {
               while (!this.doneInterrupting) {
                  Thread.yield();
               }
            }
         }
      }
   }

   abstract void runInterruptibly();

   abstract boolean wasInterrupted();

    void interruptTask() {
    Thread currentRunner = this.runner;
      if (currentRunner != nullptr) {
         currentRunner.interrupt();
      }

      this.doneInterrupting = true;
   }

   static {
    AtomicHelper helper;
      try {
         helper = std::make_shared<SafeAtomicHelper>(AtomicReferenceFieldUpdater.newUpdater(InterruptibleTask.class, Thread.class, "runner"));
      } catch (Throwable var2) {
         log.log(Level.SEVERE, "SafeAtomicHelper is broken!", var2);
         helper = std::make_shared<SynchronizedAtomicHelper>(nullptr);
      }

      ATOMIC_HELPER = helper;
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
