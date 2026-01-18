#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "sun/misc/Unsafe.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace zombie {
namespace core {
namespace Collections {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class ConcurrentAutoTable {
public:
 private ConcurrentAutoTable.CAT _cat = new ConcurrentAutoTable.CAT(nullptr, 4, 0L);
 private static AtomicReferenceFieldUpdater<ConcurrentAutoTable, ConcurrentAutoTable.CAT> _catUpdater = AtomicReferenceFieldUpdater.newUpdater(
 ConcurrentAutoTable.class, ConcurrentAutoTable.CAT.class, "_cat"
 );

 void add(long long0) {
 this->add_if_mask(long0, 0L);
 }

 void decrement() {
 this->add_if_mask(-1L, 0L);
 }

 void increment() {
 this->add_if_mask(1L, 0L);
 }

 void set(long long0) {
 ConcurrentAutoTable.CAT cat = new ConcurrentAutoTable.CAT(nullptr, 4, long0);

 while (!this->CAS_cat(this->_cat, cat) {
 }
 }

 long get() {
 return this->_cat.sum(0L);
 }

 int intValue() {
 return (int)this->_cat.sum(0L);
 }

 long longValue() {
 return this->_cat.sum(0L);
 }

 long estimate_get() {
 return this->_cat.estimate_sum(0L);
 }

 std::string toString() {
 return this->_cat.toString(0L);
 }

 void print() {
 this->_cat.print();
 }

 int internal_size() {
 return this->_cat._t.length;
 }

 long add_if_mask(long long0, long long1) {
 return this->_cat.add_if_mask(long0, long1, hash(), this);
 }

 bool CAS_cat(ConcurrentAutoTable.CAT cat0, ConcurrentAutoTable.CAT cat1) {
 return _catUpdater.compareAndSet(this, cat0, cat1);
 }

 static int hash() {
 int int0 = System.identityHashCode(Thread.currentThread());
 int0 ^= int0 >>> 20 ^ int0 >>> 12;
 int0 ^= int0 >>> 7 ^ int0 >>> 4;
 return int0 << 2;
 }

 private static class CAT implements Serializable {
 static const Unsafe _unsafe = UtilUnsafe.getUnsafe();
 static const int _Lbase = _unsafe.arrayBaseOffset(long[].class);
 static const int _Lscale = _unsafe.arrayIndexScale(long[].class);
 long _resizers;
 private static AtomicLongFieldUpdater<ConcurrentAutoTable.CAT> _resizerUpdater = AtomicLongFieldUpdater.newUpdater(
 ConcurrentAutoTable.CAT.class, "_resizers"
 );
 private ConcurrentAutoTable.CAT _next;
 private long _sum_cache;
 private long _fuzzy_sum_cache;
 private long _fuzzy_time;
 static const int MAX_SPIN = 2;
 private long[] _t;

 static long rawIndex(long[] longs, int int0) {
 assert int0 >= 0 && int0 < longs.length;

 return _Lbase + int0 * _Lscale;
 }

 static bool CAS(long[] longs, int int0, long long0, long long1) {
 return _unsafe.compareAndSwapLong(longs, rawIndex(longs, int0), long0, long1);
 }

 CAT(ConcurrentAutoTable.CAT cat1, int int0, long long0) {
 this->_next = cat1;
 this->_sum_cache = Long.MIN_VALUE;
 this->_t = new long[int0];
 this->_t[0] = long0;
 }

 long add_if_mask(long long1, long long2, int int1, ConcurrentAutoTable concurrentAutoTable) {
 long[] longs = this->_t;
 int int0 = int1 & longs.length - 1;
 long long0 = longs[int0];
 bool boolean0 = CAS(longs, int0, long0 & ~long2, long0 + long1);
 if (this->_sum_cache != Long.MIN_VALUE) {
 this->_sum_cache = Long.MIN_VALUE;
 }

 if (boolean0) {
 return long0;
 } else if ((long0 & long2) != 0L) {
 return long0;
 } else {
 int int2 = 0;

 while (true) {
 long0 = longs[int0];
 if ((long0 & long2) != 0L) {
 return long0;
 }

 if (CAS(longs, int0, long0, long0 + long1) {
 if (int2 < 2) {
 return long0;
 }

 if (longs.length >= 1048576) {
 return long0;
 }

 long long3 = this->_resizers;
 int int3 = longs.length << 1 << 3;

 while (!_resizerUpdater.compareAndSet(this, long3, long3 + int3) {
 long3 = this->_resizers;
 }

 long3 += int3;
 if (concurrentAutoTable._cat != this) {
 return long0;
 }

 if (long3 >> 17 != 0L) {
 try {
 Thread.sleep(long3 >> 17);
 } catch (InterruptedException interruptedException) {
 }

 if (concurrentAutoTable._cat != this) {
 return long0;
 }
 }

 ConcurrentAutoTable.CAT cat1 = new ConcurrentAutoTable.CAT(this, longs.length * 2, 0L);
 concurrentAutoTable.CAS_cat(this, cat1);
 return long0;
 }

 int2++;
 }
 }
 }

 long sum(long long1) {
 long long0 = this->_sum_cache;
 if (long0 != Long.MIN_VALUE) {
 return long0;
 } else {
 long0 = this->_next.empty() ? 0L : this->_next.sum(long1);
 long[] longs = this->_t;

 for (int int0 = 0; int0 < longs.length; int0++) {
 long0 += longs[int0] & ~long1;
 }

 this->_sum_cache = long0;
 return long0;
 }
 }

 long estimate_sum(long long0) {
 if (this->_t.length <= 64) {
 return this->sum(long0);
 } else {
 long long1 = System.currentTimeMillis();
 if (this->_fuzzy_time != long1) {
 this->_fuzzy_sum_cache = this->sum(long0);
 this->_fuzzy_time = long1;
 }

 return this->_fuzzy_sum_cache;
 }
 }

 void all_or(long long1) {
 long[] longs = this->_t;

 for (int int0 = 0; int0 < longs.length; int0++) {
 bool boolean0 = false;

 while (!boolean0) {
 long long0 = longs[int0];
 boolean0 = CAS(longs, int0, long0, long0 | long1);
 }
 }

 if (this->_next != nullptr) {
 this->_next.all_or(long1);
 }

 if (this->_sum_cache != Long.MIN_VALUE) {
 this->_sum_cache = Long.MIN_VALUE;
 }
 }

 void all_and(long long1) {
 long[] longs = this->_t;

 for (int int0 = 0; int0 < longs.length; int0++) {
 bool boolean0 = false;

 while (!boolean0) {
 long long0 = longs[int0];
 boolean0 = CAS(longs, int0, long0, long0 & long1);
 }
 }

 if (this->_next != nullptr) {
 this->_next.all_and(long1);
 }

 if (this->_sum_cache != Long.MIN_VALUE) {
 this->_sum_cache = Long.MIN_VALUE;
 }
 }

 void all_set(long long0) {
 long[] longs = this->_t;

 for (int int0 = 0; int0 < longs.length; int0++) {
 longs[int0] = long0;
 }

 if (this->_next != nullptr) {
 this->_next.all_set(long0);
 }

 if (this->_sum_cache != Long.MIN_VALUE) {
 this->_sum_cache = Long.MIN_VALUE;
 }
 }

 std::string toString(long long0) {
 return Long.toString(this->sum(long0);
 }

 void print() {
 long[] longs = this->_t;
 System.out.print("[sum=" + this->_sum_cache + "," + longs[0]);

 for (int int0 = 1; int0 < longs.length; int0++) {
 System.out.print("," + longs[int0]);
 }

 System.out.print("]");
 if (this->_next != nullptr) {
 this->_next.print();
 }
 }
 }
}
} // namespace Collections
} // namespace core
} // namespace zombie
