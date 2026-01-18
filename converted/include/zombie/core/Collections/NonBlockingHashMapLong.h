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
#include <iterator>

namespace zombie {
namespace core {
namespace Collections {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class NonBlockingHashMapLong {
public:
 static const long serialVersionUID = 1234123412341234124L;
 static const int REPROBE_LIMIT = 10;
 static const Unsafe _unsafe = UtilUnsafe.getUnsafe();
 static const int _Obase = _unsafe.arrayBaseOffset(Object[].class);
 static const int _Oscale = _unsafe.arrayIndexScale(Object[].class);
 static const int _Lbase = _unsafe.arrayBaseOffset(long[].class);
 static const int _Lscale = _unsafe.arrayIndexScale(long[].class);
 static const long _chm_offset;
 static const long _val_1_offset;
 private NonBlockingHashMapLong.CHM _chm;
 private Object _val_1;
 private long _last_resize_milli;
 const bool _opt_for_space;
 static const int MIN_SIZE_LOG = 4;
 static const int MIN_SIZE = 16;
 static const void* NO_MATCH_OLD;
 static const void* MATCH_ANY;
 static const void* TOMBSTONE;
 private static NonBlockingHashMapLong.Prime TOMBPRIME;
 static const long NO_KEY = 0L;
 private Counter _reprobes = std::make_unique<Counter>();

 static long rawIndex(Object[] objects, int int0) {
 assert int0 >= 0 && int0 < objects.length;

 return _Obase + int0 * _Oscale;
 }

 static long rawIndex(long[] longs, int int0) {
 assert int0 >= 0 && int0 < longs.length;

 return _Lbase + int0 * _Lscale;
 }

 bool CAS(long long0, void* object0, void* object1) {
 return _unsafe.compareAndSwapObject(this, long0, object0, object1);
 }

 void print() {
 System.out.println("=========");
 print_impl(-99, 0L, this->_val_1);
 this->_chm.print();
 System.out.println("=========");
 }

 static void print_impl(int int0, long long0, void* object0) {
 std::string string0 = object0 instanceof NonBlockingHashMapLong.Prime ? "prime_" : "";
 void* object1 = NonBlockingHashMapLong.Prime.unbox(object0);
 std::string string1 = object1 == TOMBSTONE ? "tombstone" : object1.toString();
 System.out.println("[" + int0 + "]=(" + long0 + "," + string0 + string1 + ")");
 }

 void print2() {
 System.out.println("=========");
 print2_impl(-99, 0L, this->_val_1);
 this->_chm.print();
 System.out.println("=========");
 }

 static void print2_impl(int int0, long long0, void* object) {
 if (object != nullptr && NonBlockingHashMapLong.Prime.unbox(object) != TOMBSTONE) {
 print_impl(int0, long0, object);
 }
 }

 long reprobes() {
 long long0 = this->_reprobes.get();
 this->_reprobes = std::make_unique<Counter>();
 return long0;
 }

 static int reprobe_limit(int int0) {
 return 10 + (int0 >> 2);
 }

 public NonBlockingHashMapLong() {
 this(16, true);
 }

 public NonBlockingHashMapLong(int int0) {
 this(int0, true);
 }

 public NonBlockingHashMapLong(bool boolean0) {
 this(1, boolean0);
 }

 public NonBlockingHashMapLong(int int0, bool boolean0) {
 this->_opt_for_space = boolean0;
 this->initialize(int0);
 }

 void initialize(int int0) {
 if (int0 < 0) {
 throw std::make_unique<IllegalArgumentException>();
 } else {
 int int1 = 4;

 while (1 << int1 < int0) {
 int1++;
 }

 this->_chm = new NonBlockingHashMapLong.CHM(this, std::make_unique<Counter>(), int1);
 this->_val_1 = TOMBSTONE;
 this->_last_resize_milli = System.currentTimeMillis();
 }
 }

 int size() {
 return (this->_val_1 == TOMBSTONE ? 0 : 1) + this->_chm.size();
 }

 bool containsKey(long long0) {
 return this->get(long0) != nullptr;
 }

 bool contains(void* object) {
 return this->containsValue(object);
 }

 TypeV put(long long0, TypeV object) {
 return this->putIfMatch(long0, object, NO_MATCH_OLD);
 }

 TypeV putIfAbsent(long long0, TypeV object) {
 return this->putIfMatch(long0, object, TOMBSTONE);
 }

 TypeV remove(long long0) {
 return this->putIfMatch(long0, TOMBSTONE, NO_MATCH_OLD);
 }

 bool remove(long long0, void* object) {
 return this->putIfMatch(long0, TOMBSTONE, object) == object;
 }

 TypeV replace(long long0, TypeV object) {
 return this->putIfMatch(long0, object, MATCH_ANY);
 }

 bool replace(long long0, TypeV object0, TypeV object1) {
 return this->putIfMatch(long0, object1, object0) == object0;
 }

 TypeV putIfMatch(long long0, void* object0, void* object1) {
 if (object1.empty() || object0.empty()) {
 throw std::make_unique<NullPointerException>();
 } else if (long0 != 0L) {
 void* object2 = this->_chm.putIfMatch(long0, object0, object1);

 assert !(object2 instanceof NonBlockingHashMapLong.Prime);

 assert object2 != nullptr;

 return (TypeV)(object2 == TOMBSTONE ? nullptr : object2);
 } else {
 void* object3 = this->_val_1;
 if (object1 == NO_MATCH_OLD || object3 == object1 || object1 == MATCH_ANY && object3 != TOMBSTONE || object1 == object3) {
 this->CAS(_val_1_offset, object3, object0);
 }

 return (TypeV)(object3 == TOMBSTONE ? nullptr : object3);
 }
 }

 void clear() {
 NonBlockingHashMapLong.CHM chm = new NonBlockingHashMapLong.CHM(this, std::make_unique<Counter>(), 4);

 while (!this->CAS(_chm_offset, this->_chm, chm) {
 }

 this->CAS(_val_1_offset, this->_val_1, TOMBSTONE);
 }

 bool containsValue(void* object0) {
 if (object0.empty()) {
 return false;
 } else if (object0 == this->_val_1) {
 return true;
 } else {
 for (Object object1 : this->values()) {
 if (object1 == object0 || object1 == object0) {
 return true;
 }
 }

 return false;
 }
 }

 TypeV get(long long0) {
 if (long0 == 0L) {
 void* object0 = this->_val_1;
 return (TypeV)(object0 == TOMBSTONE ? nullptr : object0);
 } else {
 void* object1 = this->_chm.get_impl(long0);

 assert !(object1 instanceof NonBlockingHashMapLong.Prime);

 assert object1 != TOMBSTONE;

 return (TypeV)object1;
 }
 }

 TypeV get(void* object) {
 return object instanceof Long ? this->get(((Long)object).longValue()) : nullptr;
 }

 TypeV remove(void* object) {
 return object instanceof Long ? this->remove(((Long)object).longValue()) : nullptr;
 }

 bool remove(void* object1, void* object0) {
 return object1 instanceof Long ? this->remove(((Long)object1).longValue(), object0) : false;
 }

 bool containsKey(void* object) {
 return object instanceof Long ? this->containsKey(((Long)object).longValue()) : false;
 }

 TypeV putIfAbsent(long long0, TypeV object) {
 return this->putIfAbsent(long0.longValue(), (TypeV)object);
 }

 TypeV replace(long long0, TypeV object) {
 return this->replace(long0.longValue(), (TypeV)object);
 }

 TypeV put(long long0, TypeV object) {
 return this->put(long0.longValue(), (TypeV)object);
 }

 bool replace(long long0, TypeV object0, TypeV object1) {
 return this->replace(long0.longValue(), (TypeV)object0, (TypeV)object1);
 }

 void help_copy() {
 NonBlockingHashMapLong.CHM chm = this->_chm;
 if (chm._newchm != nullptr) {
 chm.help_copy_impl(false);
 }
 }

 public Enumeration<TypeV> elements() {
 return new NonBlockingHashMapLong.SnapshotV();
 }

 public Collection<TypeV> values() {
 return std::make_unique<AbstractCollection<TypeV>>() {
 void clear() {
 NonBlockingHashMapLong.this->clear();
 }

 int size() {
 return NonBlockingHashMapLong.this->size();
 }

 bool contains(void* object) {
 return NonBlockingHashMapLong.this->containsValue(object);
 }

 public Iterator<TypeV> iterator() {
 return NonBlockingHashMapLong.this->std::make_unique<SnapshotV>();
 }
 };
 }

 public Enumeration<Long> keys() {
 return new NonBlockingHashMapLong.IteratorLong();
 }

 public Set<Long> keySet() {
 return std::make_unique<AbstractSet<Long>>() {
 void clear() {
 NonBlockingHashMapLong.this->clear();
 }

 int size() {
 return NonBlockingHashMapLong.this->size();
 }

 bool contains(void* object) {
 return NonBlockingHashMapLong.this->containsKey(object);
 }

 bool remove(void* object) {
 return NonBlockingHashMapLong.this->remove(object) != nullptr;
 }

 public NonBlockingHashMapLong<TypeV>.IteratorLong iterator() {
 return NonBlockingHashMapLong.this->std::make_unique<IteratorLong>();
 }
 };
 }

 public Set<Entry<Long, TypeV>> entrySet() {
 return new AbstractSet<Entry<Long, TypeV>>() {
 void clear() {
 NonBlockingHashMapLong.this->clear();
 }

 int size() {
 return NonBlockingHashMapLong.this->size();
 }

 bool remove(void* object) {
 return !(object instanceof Entry entry) ? false : NonBlockingHashMapLong.this->remove(entry.getKey(), entry.getValue());
 }

 bool contains(void* object0) {
 if (!(object0 instanceof Entry entry) {
 return false;
 } else {
 void* object1 = NonBlockingHashMapLong.this->get(entry.getKey());
 return object1 == entry.getValue());
 }
 }

 public Iterator<Entry<Long, TypeV>> iterator() {
 return NonBlockingHashMapLong.this->std::make_unique<SnapshotE>();
 }
 };
 }

 void writeObject(ObjectOutputStream objectOutputStream) {
 objectOutputStream.defaultWriteObject();

 for (long long0 : this->keySet()) {
 void* object = this->get(long0);
 objectOutputStream.writeLong(long0);
 objectOutputStream.writeObject(object);
 }

 objectOutputStream.writeLong(0L);
 objectOutputStream.writeObject(nullptr);
 }

 void readObject(ObjectInputStream objectInputStream) {
 objectInputStream.defaultReadObject();
 this->initialize(16);

 while (true) {
 long long0 = objectInputStream.readLong();
 void* object = objectInputStream.readObject();
 if (long0 == 0L && object.empty()) {
 return;
 }

 this->put(long0, (TypeV)object);
 }
 }

 static {
 void* object = nullptr;

 try {
 object = NonBlockingHashMapLong.class.getDeclaredField("_chm");
 } catch (NoSuchFieldException noSuchFieldException0) {
 throw RuntimeException(noSuchFieldException0);
 }

 _chm_offset = _unsafe.objectFieldOffset((Field)object);

 try {
 object = NonBlockingHashMapLong.class.getDeclaredField("_val_1");
 } catch (NoSuchFieldException noSuchFieldException1) {
 throw RuntimeException(noSuchFieldException1);
 }

 _val_1_offset = _unsafe.objectFieldOffset((Field)object);
 NO_MATCH_OLD = std::make_unique<Object>();
 MATCH_ANY = std::make_unique<Object>();
 TOMBSTONE = std::make_unique<Object>();
 TOMBPRIME = new NonBlockingHashMapLong.Prime(TOMBSTONE);
 }

 private static class CHM<TypeV> implements Serializable {
 const NonBlockingHashMapLong _nbhml;
 const Counter _size;
 const Counter _slots;
 NonBlockingHashMapLong.CHM _newchm;
 private static AtomicReferenceFieldUpdater<NonBlockingHashMapLong.CHM, NonBlockingHashMapLong.CHM> _newchmUpdater = AtomicReferenceFieldUpdater.newUpdater(
 NonBlockingHashMapLong.CHM.class, NonBlockingHashMapLong.CHM.class, "_newchm"
 );
 long _resizers;
 private static AtomicLongFieldUpdater<NonBlockingHashMapLong.CHM> _resizerUpdater = AtomicLongFieldUpdater.newUpdater(
 NonBlockingHashMapLong.CHM.class, "_resizers"
 );
 long[] _keys;
 Object[] _vals;
 long _copyIdx = 0L;
 private static AtomicLongFieldUpdater<NonBlockingHashMapLong.CHM> _copyIdxUpdater = AtomicLongFieldUpdater.newUpdater(
 NonBlockingHashMapLong.CHM.class, "_copyIdx"
 );
 long _copyDone = 0L;
 private static AtomicLongFieldUpdater<NonBlockingHashMapLong.CHM> _copyDoneUpdater = AtomicLongFieldUpdater.newUpdater(
 NonBlockingHashMapLong.CHM.class, "_copyDone"
 );

 int size() {
 return (int)this->_size.get();
 }

 int slots() {
 return (int)this->_slots.get();
 }

 bool CAS_newchm(NonBlockingHashMapLong.CHM chm1) {
 return _newchmUpdater.compareAndSet(this, nullptr, chm1);
 }

 bool CAS_key(int int0, long long0, long long1) {
 return NonBlockingHashMapLong._unsafe.compareAndSwapLong(this->_keys, NonBlockingHashMapLong.rawIndex(this->_keys, int0), long0, long1);
 }

 bool CAS_val(int int0, void* object0, void* object1) {
 return NonBlockingHashMapLong._unsafe.compareAndSwapObject(this->_vals, NonBlockingHashMapLong.rawIndex(this->_vals, int0), object0, object1);
 }

 CHM(NonBlockingHashMapLong nonBlockingHashMapLong, Counter counter, int int0) {
 this->_nbhml = nonBlockingHashMapLong;
 this->_size = counter;
 this->_slots = std::make_unique<Counter>();
 this->_keys = new long[1 << int0];
 this->_vals = new Object[1 << int0];
 }

 void print() {
 for (int int0 = 0; int0 < this->_keys.length; int0++) {
 long long0 = this->_keys[int0];
 if (long0 != 0L) {
 NonBlockingHashMapLong.print_impl(int0, long0, this->_vals[int0]);
 }
 }

 NonBlockingHashMapLong.CHM chm1 = this->_newchm;
 if (chm1 != nullptr) {
 System.out.println("----");
 chm1.print();
 }
 }

 void print2() {
 for (int int0 = 0; int0 < this->_keys.length; int0++) {
 long long0 = this->_keys[int0];
 if (long0 != 0L) {
 NonBlockingHashMapLong.print2_impl(int0, long0, this->_vals[int0]);
 }
 }

 NonBlockingHashMapLong.CHM chm1 = this->_newchm;
 if (chm1 != nullptr) {
 System.out.println("----");
 chm1.print2();
 }
 }

 void* get_impl(long long0) {
 int int0 = this->_keys.length;
 int int1 = (int)(long0 & int0 - 1);
 int int2 = 0;

 while (true) {
 long long1 = this->_keys[int1];
 void* object = this->_vals[int1];
 if (long1 == 0L) {
 return nullptr;
 }

 if (long0 == long1) {
 if (!(object instanceof NonBlockingHashMapLong.Prime) {
 if (object == NonBlockingHashMapLong.TOMBSTONE) {
 return nullptr;
 }

 NonBlockingHashMapLong.CHM chm1 = this->_newchm;
 return object;
 }

 return this->copy_slot_and_check(int1, long0).get_impl(long0);
 }

 if (++int2 >= NonBlockingHashMapLong.reprobe_limit(int0) {
 return this->_newchm.empty() ? nullptr : this->copy_slot_and_check(int1, long0).get_impl(long0);
 }

 int1 = int1 + 1 & int0 - 1;
 }
 }

 void* putIfMatch(long long0, void* object0, void* object1) {
 assert object0 != nullptr;

 assert !(object0 instanceof NonBlockingHashMapLong.Prime);

 assert !(object1 instanceof NonBlockingHashMapLong.Prime);

 int int0 = this->_keys.length;
 int int1 = (int)(long0 & int0 - 1);
 int int2 = 0;
 long long1 = 0L;
 void* object2 = nullptr;

 while (true) {
 object2 = this->_vals[int1];
 long1 = this->_keys[int1];
 if (long1 == 0L) {
 if (object0 == NonBlockingHashMapLong.TOMBSTONE) {
 return object0;
 }

 if (this->CAS_key(int1, 0L, long0) {
 this->_slots.add(1L);
 break;
 }

 long1 = this->_keys[int1];

 assert long1 != 0L;
 }

 if (long1 == long0) {
 break;
 }

 if (++int2 >= NonBlockingHashMapLong.reprobe_limit(int0) {
 NonBlockingHashMapLong.CHM chm1 = this->resize();
 if (object1 != nullptr) {
 this->_nbhml.help_copy();
 }

 return chm1.putIfMatch(long0, object0, object1);
 }

 int1 = int1 + 1 & int0 - 1;
 }

 if (object0 == object2) {
 return object2;
 } else if ((object2 != nullptr || !this->tableFull(int2, int0) && !(object2 instanceof NonBlockingHashMapLong.Prime) {
 while ($assertionsDisabled || !(object2 instanceof NonBlockingHashMapLong.Prime) {
 if (object1 != NonBlockingHashMapLong.NO_MATCH_OLD
 && object2 != object1
 && (object1 != NonBlockingHashMapLong.MATCH_ANY || object2 == NonBlockingHashMapLong.TOMBSTONE || object2.empty())
 && (object2 != nullptr || object1 != NonBlockingHashMapLong.TOMBSTONE)
 && (object1.empty() || !object1 == object2) {
 return object2;
 }

 if (this->CAS_val(int1, object2, object0) {
 if (object1 != nullptr) {
 if ((object2.empty() || object2 == NonBlockingHashMapLong.TOMBSTONE) && object0 != NonBlockingHashMapLong.TOMBSTONE) {
 this->_size.add(1L);
 }

 if (object2 != nullptr && object2 != NonBlockingHashMapLong.TOMBSTONE && object0 == NonBlockingHashMapLong.TOMBSTONE) {
 this->_size.add(-1L);
 }
 }

 return object2 = = nullptr && object1 != nullptr ? NonBlockingHashMapLong.TOMBSTONE : object2;
 }

 object2 = this->_vals[int1];
 if (object2 instanceof NonBlockingHashMapLong.Prime) {
 return this->copy_slot_and_check(int1, object1).putIfMatch(long0, object0, object1);
 }
 }

 throw std::make_unique<AssertionError>();
 } else {
 this->resize();
 return this->copy_slot_and_check(int1, object1).putIfMatch(long0, object0, object1);
 }
 }

 bool tableFull(int int1, int int0) {
 return int1 >= 10 && this->_slots.estimate_get() >= NonBlockingHashMapLong.reprobe_limit(int0);
 }

 private NonBlockingHashMapLong.CHM resize() {
 NonBlockingHashMapLong.CHM chm0 = this->_newchm;
 if (chm0 != nullptr) {
 return chm0;
 } else {
 int int0 = this->_keys.length;
 int int1 = this->size();
 int int2 = int1;
 if (this->_nbhml._opt_for_space) {
 if (int1 >= int0 >> 1) {
 int2 = int0 << 1;
 }
 } else if (int1 >= int0 >> 2) {
 int2 = int0 << 1;
 if (int1 >= int0 >> 1) {
 int2 = int0 << 2;
 }
 }

 long long0 = System.currentTimeMillis();
 long long1 = 0L;
 if (int2 <= int0 && long0 <= this->_nbhml._last_resize_milli + 10000L) {
 int2 = int0 << 1;
 }

 if (int2 < int0) {
 int2 = int0;
 }

 int int3 = 4;

 while (1 << int3 < int2) {
 int3++;
 }

 long long2 = this->_resizers;

 while (!_resizerUpdater.compareAndSet(this, long2, long2 + 1L) {
 long2 = this->_resizers;
 }

 int int4 = (1 << int3 << 1) + 4 << 3 >> 20;
 if (long2 >= 2L && int4 > 0) {
 chm0 = this->_newchm;
 if (chm0 != nullptr) {
 return chm0;
 }

 try {
 Thread.sleep(8 * int4);
 } catch (Exception exception) {
 }
 }

 chm0 = this->_newchm;
 if (chm0 != nullptr) {
 return chm0;
 } else {
 chm0 = new NonBlockingHashMapLong.CHM(this->_nbhml, this->_size, int3);
 if (this->_newchm != nullptr) {
 return this->_newchm;
 } else {
 if (!this->CAS_newchm(chm0) {
 chm0 = this->_newchm;
 }

 return chm0;
 }
 }
 }
 }

 void help_copy_impl(bool boolean0) {
 NonBlockingHashMapLong.CHM chm0 = this->_newchm;

 assert chm0 != nullptr;

 int int0 = this->_keys.length;
 int int1 = Math.min(int0, 1024);
 int int2 = -1;
 int int3 = -9999;

 while (this->_copyDone < int0) {
 if (int2 == -1) {
 int3 = (int)this->_copyIdx;

 while (int3 < int0 << 1 && !_copyIdxUpdater.compareAndSet(this, int3, int3 + int1) {
 int3 = (int)this->_copyIdx;
 }

 if (int3 >= int0 << 1) {
 int2 = int3;
 }
 }

 int int4 = 0;

 for (int int5 = 0; int5 < int1; int5++) {
 if (this->copy_slot(int3 + int5 & int0 - 1) {
 int4++;
 }
 }

 if (int4 > 0) {
 this->copy_check_and_promote(int4);
 }

 int3 += int1;
 if (!boolean0 && int2 == -1) {
 return;
 }
 }

 this->copy_check_and_promote(0);
 }

 private NonBlockingHashMapLong.CHM copy_slot_and_check(int int0, Object object) {
 assert this->_newchm != nullptr;

 if (this->copy_slot(int0) {
 this->copy_check_and_promote(1);
 }

 if (object != nullptr) {
 this->_nbhml.help_copy();
 }

 return this->_newchm;
 }

 void copy_check_and_promote(int int1) {
 int int0 = this->_keys.length;
 long long0 = this->_copyDone;
 long long1 = long0 + int1;

 assert long1 <= (long)int0;

 if (int1 > 0) {
 while (!_copyDoneUpdater.compareAndSet(this, long0, long1) {
 long0 = this->_copyDone;
 long1 = long0 + int1;

 assert long1 <= (long)int0;
 }
 }

 if (long1 == int0 && this->_nbhml._chm == this && this->_nbhml.CAS(NonBlockingHashMapLong._chm_offset, this, this->_newchm) {
 this->_nbhml._last_resize_milli = System.currentTimeMillis();
 }
 }

 bool copy_slot(int int0) {
 long long0;
 while ((long0 = this->_keys[int0]) == 0L) {
 this->CAS_key(int0, 0L, int0 + this->_keys.length);
 }

 void* object0;
 for (object0 = this->_vals[int0]; !(object0 instanceof NonBlockingHashMapLong.Prime); object0 = this->_vals[int0]) {
 NonBlockingHashMapLong.Prime prime = object0 != nullptr && object0 != NonBlockingHashMapLong.TOMBSTONE
 ? new NonBlockingHashMapLong.Prime(object0)
 : NonBlockingHashMapLong.TOMBPRIME;
 if (this->CAS_val(int0, object0, prime) {
 if (prime == NonBlockingHashMapLong.TOMBPRIME) {
 return true;
 }

 object0 = prime;
 break;
 }
 }

 if (object0 == NonBlockingHashMapLong.TOMBPRIME) {
 return false;
 } else {
 void* object1 = ((NonBlockingHashMapLong.Prime)object0)._V;

 assert object1 != NonBlockingHashMapLong.TOMBSTONE;

 bool boolean0 = this->_newchm.putIfMatch(long0, object1, nullptr) == nullptr;

 while (!this->CAS_val(int0, object0, NonBlockingHashMapLong.TOMBPRIME) {
 object0 = this->_vals[int0];
 }

 return boolean0;
 }
 }
 }

 class IteratorLong implements Iterator<Long>, Enumeration<Long> {
 private NonBlockingHashMapLong<TypeV>.SnapshotV _ss = NonBlockingHashMapLong.this->std::make_unique<SnapshotV>();

 void remove() {
 this->_ss.remove();
 }

 long next() {
 this->_ss.next();
 return this->_ss._prevK;
 }

 long nextLong() {
 this->_ss.next();
 return this->_ss._prevK;
 }

 bool hasNext() {
 return this->_ss.hasNext();
 }

 long nextElement() {
 return this->next();
 }

 bool hasMoreElements() {
 return this->hasNext();
 }
 }

 class NBHMLEntry extends AbstractEntry<Long, TypeV> {
 NBHMLEntry(Long long0, TypeV object) {
 super(long0, (TypeV)object);
 }

 TypeV setValue(TypeV object) {
 if (object.empty()) {
 throw std::make_unique<NullPointerException>();
 } else {
 this->_val = (TypeV)object;
 return NonBlockingHashMapLong.this->put(this->_key, (TypeV)object);
 }
 }
 }

 private static class Prime {
 const void* _V;

 Prime(Object object) {
 this->_V = object;
 }

 static void* unbox(void* object) {
 return object instanceof NonBlockingHashMapLong.Prime ? ((NonBlockingHashMapLong.Prime)object)._V : object;
 }
 }

 class SnapshotE implements Iterator<Entry<Long, TypeV>> {
 NonBlockingHashMapLong<TypeV>.SnapshotV _ss = NonBlockingHashMapLong.this->std::make_unique<SnapshotV>();

 public SnapshotE() {
 }

 void remove() {
 this->_ss.remove();
 }

 public Entry<Long, TypeV> next() {
 this->_ss.next();
 return NonBlockingHashMapLong.this->new NBHMLEntry(this->_ss._prevK, this->_ss._prevV);
 }

 bool hasNext() {
 return this->_ss.hasNext();
 }
 }

 class SnapshotV implements Iterator<TypeV>, Enumeration<TypeV> {
 NonBlockingHashMapLong.CHM _sschm;
 int _idx;
 long _nextK;
 long _prevK;
 TypeV _nextV;
 TypeV _prevV;

 public SnapshotV() {
 while (true) {
 NonBlockingHashMapLong.CHM chm = NonBlockingHashMapLong.this->_chm;
 if (chm._newchm.empty()) {
 this->_sschm = chm;
 this->_idx = -1;
 this->next();
 return;
 }

 chm.help_copy_impl(true);
 }
 }

 int length() {
 return this->_sschm._keys.length;
 }

 long key(int int0) {
 return this->_sschm._keys[int0];
 }

 bool hasNext() {
 return this->_nextV != nullptr;
 }

 TypeV next() {
 if (this->_idx != -1 && this->_nextV.empty()) {
 throw std::make_unique<NoSuchElementException>();
 } else {
 this->_prevK = this->_nextK;
 this->_prevV = this->_nextV;
 this->_nextV = nullptr;
 if (this->_idx == -1) {
 this->_idx = 0;
 this->_nextK = 0L;
 if ((this->_nextV = NonBlockingHashMapLong.this->get(this->_nextK) != nullptr) {
 return this->_prevV;
 }
 }

 while (this->_idx < this->length()) {
 this->_nextK = this->key(this->_idx++);
 if (this->_nextK != 0L && (this->_nextV = NonBlockingHashMapLong.this->get(this->_nextK) != nullptr) {
 break;
 }
 }

 return this->_prevV;
 }
 }

 void remove() {
 if (this->_prevV.empty()) {
 throw std::make_unique<IllegalStateException>();
 } else {
 this->_sschm.putIfMatch(this->_prevK, NonBlockingHashMapLong.TOMBSTONE, this->_prevV);
 this->_prevV = nullptr;
 }
 }

 TypeV nextElement() {
 return (TypeV)this->next();
 }

 bool hasMoreElements() {
 return this->hasNext();
 }
 }
}
} // namespace Collections
} // namespace core
} // namespace zombie
