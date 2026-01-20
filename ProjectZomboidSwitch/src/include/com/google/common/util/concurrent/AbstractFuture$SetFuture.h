#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {

class AbstractFuture {
public:
   const AbstractFuture<V> owner;
   const ListenableFuture<? : public V> future;

   AbstractFuture$SetFuture(AbstractFuture<V> owner, ListenableFuture<? : public V> future) {
      this.owner = owner;
      this.future = future;
   }

    void run() {
      if (AbstractFuture.access$300(this.owner) == this) {
    void* valueToSet = AbstractFuture.access$400(this.future);
         if (AbstractFuture.access$200().casValue(this.owner, this, valueToSet)) {
            AbstractFuture.access$500(this.owner);
         }
      }
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
