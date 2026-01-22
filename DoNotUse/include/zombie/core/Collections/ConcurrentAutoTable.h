#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/Collections/ConcurrentAutoTable/CAT.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace zombie {
namespace core {
namespace Collections {


class ConcurrentAutoTable {
public:
   private volatile CAT _cat = std::make_shared<CAT>(nullptr, 4, 0L);
   private static const AtomicReferenceFieldUpdater<ConcurrentAutoTable, CAT> _catUpdater = AtomicReferenceFieldUpdater.newUpdater(
      ConcurrentAutoTable.class, CAT.class, "_cat"
   );

    void add(long var1) {
      this.add_if_mask(var1, 0L);
   }

    void decrement() {
      this.add_if_mask(-1L, 0L);
   }

    void increment() {
      this.add_if_mask(1L, 0L);
   }

    void set(long var1) {
    CAT var3 = std::make_shared<CAT>(nullptr, 4, var1);

      while (!this.CAS_cat(this._cat, var3)) {
      }
   }

    long get() {
      return this._cat.sum(0L);
   }

    int intValue() {
      return (int)this._cat.sum(0L);
   }

    long longValue() {
      return this._cat.sum(0L);
   }

    long estimate_get() {
      return this._cat.estimate_sum(0L);
   }

    std::string toString() {
      return this._cat.toString(0L);
   }

    void print() {
      this._cat.print();
   }

    int internal_size() {
      return this._cat._t.length;
   }

    long add_if_mask(long var1, long var3) {
      return this._cat.add_if_mask(var1, var3, hash(), this);
   }

    bool CAS_cat(CAT var1, CAT var2) {
      return _catUpdater.compareAndSet(this, var1, var2);
   }

    static int hash() {
    int var0 = System.identityHashCode(Thread.currentThread());
      var0 ^= var0 >>> 20 ^ var0 >>> 12;
      var0 ^= var0 >>> 7 ^ var0 >>> 4;
      return var0 << 2;
   }
}
} // namespace Collections
} // namespace core
} // namespace zombie
