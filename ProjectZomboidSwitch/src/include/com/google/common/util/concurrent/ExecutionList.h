#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/util/concurrent/ExecutionList/RunnableExecutorPair.h"
#include "javax/annotation/concurrent/GuardedBy.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class ExecutionList {
public:
    static const Logger log = Logger.getLogger(ExecutionList.class.getName());
    RunnableExecutorPair runnables;
    bool executed;

    void add(Runnable runnable, Executor executor) {
      Preconditions.checkNotNull(runnable, "Runnable was nullptr.");
      Preconditions.checkNotNull(executor, "Executor was nullptr.");
      /* synchronized - TODO: add std::mutex */ (this) {
         if (!this.executed) {
            this.runnables = std::make_shared<RunnableExecutorPair>(runnable, executor, this.runnables);
            return;
         }
      }

      executeListener(runnable, executor);
   }

    void execute() {
    RunnableExecutorPair list;
      /* synchronized - TODO: add std::mutex */ (this) {
         if (this.executed) {
            return;
         }

         this.executed = true;
         list = this.runnables;
         this.runnables = nullptr;
      }

    RunnableExecutorPair reversedList = nullptr;

      while (list != nullptr) {
    RunnableExecutorPair tmp = list;
         list = list.next;
         tmp.next = reversedList;
         reversedList = tmp;
      }

      while (reversedList != nullptr) {
         executeListener(reversedList.runnable, reversedList.executor);
         reversedList = reversedList.next;
      }
   }

    static void executeListener(Runnable runnable, Executor executor) {
      try {
         executor.execute(runnable);
      } catch (RuntimeException var3) {
         log.log(Level.SEVERE, "RuntimeException while executing runnable " + runnable + " with executor " + executor, (Throwable)var3);
      }
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
