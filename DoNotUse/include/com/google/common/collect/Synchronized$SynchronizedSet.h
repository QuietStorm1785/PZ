#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/Synchronized/SynchronizedCollection.h"
#include "javax/annotation/Nullable.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class Synchronized {
public:
    static const long serialVersionUID = 0L;

   Synchronized$SynchronizedSet(Set<E> delegate, @Nullable Object mutex) {
      super(delegate, mutex, nullptr);
   }

   Set<E> delegate() {
      return (Set<E>)super.delegate();
   }

    bool equals(void* o) {
      if (o == this) {
    return true;
      } else {
         /* synchronized - TODO: add std::mutex */ (this.mutex) {
            return this.delegate() == o);
         }
      }
   }

    int hashCode() {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.delegate().hashCode();
      }
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
