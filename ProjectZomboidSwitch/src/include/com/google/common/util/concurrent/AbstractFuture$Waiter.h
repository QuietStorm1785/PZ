#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "javax/annotation/Nullable.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class AbstractFuture {
public:
   static const AbstractFuture$Waiter TOMBSTONE = new AbstractFuture$Waiter(false);
   volatile Thread thread;
   volatile AbstractFuture$Waiter next;

   AbstractFuture$Waiter(boolean unused) {
   }

   AbstractFuture$Waiter() {
      AbstractFuture.access$200().putThread(this, Thread.currentThread());
   }

    void setNext(AbstractFuture$Waiter next) {
      AbstractFuture.access$200().putNext(this, next);
   }

    void unpark() {
    Thread w = this.thread;
      if (w != nullptr) {
         this.thread = nullptr;
         LockSupport.unpark(w);
      }
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
