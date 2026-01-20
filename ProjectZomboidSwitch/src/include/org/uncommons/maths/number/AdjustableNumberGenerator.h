#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <algorithm>

namespace org {
namespace uncommons {
namespace maths {
namespace number {


class AdjustableNumberGenerator {
public:
    const ReadWriteLock lock = std::make_shared<ReentrantReadWriteLock>();
    T value;

    public AdjustableNumberGenerator(T value) {
      this.value = value;
   }

    void setValue(T value) {
      try {
         this.lock.writeLock().lock();
         this.value = value;
      } finally {
         this.lock.writeLock().unlock();
      }
   }

    T nextValue() {
    Number var1;
      try {
         this.lock.readLock().lock();
         var1 = this.value;
      } finally {
         this.lock.readLock().unlock();
      }

      return (T)var1;
   }
}
} // namespace number
} // namespace maths
} // namespace uncommons
} // namespace org
