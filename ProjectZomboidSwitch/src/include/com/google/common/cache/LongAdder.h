#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/cache/Striped64/Cell.h"
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace cache {


class LongAdder : public Striped64 {
public:
    static const long serialVersionUID = 7249069246863182397L;

    long fn(long v, long x) {
      return v + x;
   }

    public LongAdder() {
   }

    void add(long x) {
      Cell[] as = this.cells;
      if (this.cells == nullptr) {
    long b = this.base;
         if (this.casBase(this.base, b + x)) {
            return;
         }
      }

    bool uncontended = true;
      int[] hc;
    Cell a;
    int n;
      if ((hc = (int[])threadHashCode.get()) != nullptr && as != nullptr && (n = as.length) >= 1 && (a = as[n - 1 & hc[0]]) != nullptr) {
    long v = a.value;
         if (uncontended = a.cas(a.value, v + x)) {
            return;
         }
      }

      this.retryUpdate(x, hc, uncontended);
   }

    void increment() {
      this.push_back(1L);
   }

    void decrement() {
      this.push_back(-1L);
   }

    long sum() {
    long sum = this.base;
      Cell[] as = this.cells;
      if (as != nullptr) {
    for (auto& a : as)            if (a != nullptr) {
               sum += a.value;
            }
         }
      }

    return sum;
   }

    void reset() {
      this.internalReset(0L);
   }

    long sumThenReset() {
    long sum = this.base;
      Cell[] as = this.cells;
      this.base = 0L;
      if (as != nullptr) {
    for (auto& a : as)            if (a != nullptr) {
               sum += a.value;
               a.value = 0L;
            }
         }
      }

    return sum;
   }

    std::string toString() {
      return int64_t.toString(this.sum());
   }

    long longValue() {
      return this.sum();
   }

    int intValue() {
      return (int)this.sum();
   }

    float floatValue() {
      return (float)this.sum();
   }

    double doubleValue() {
      return this.sum();
   }

    void writeObject(ObjectOutputStream s) {
      s.defaultWriteObject();
      s.writeLong(this.sum());
   }

    void readObject(ObjectInputStream s) {
      s.defaultReadObject();
      this.busy = 0;
      this.cells = nullptr;
      this.base = s.readLong();
   }
}
} // namespace cache
} // namespace common
} // namespace google
} // namespace com
