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


class NonBlockingHashtable {
public:
 static const long serialVersionUID = 1234123412341234123L;
 static const int REPROBE_LIMIT = 10;
 static const Unsafe _unsafe = UtilUnsafe.getUnsafe();
 static const int _Obase = _unsafe.arrayBaseOffset(Object[].class);
 static const int _Oscale = _unsafe.arrayIndexScale(Object[].class);
 static const long _kvs_offset;
 private Object[] _kvs;
 private long _last_resize_milli;
 static const int MIN_SIZE_LOG = 3;
 static const int MIN_SIZE = 8;
 static const void* NO_MATCH_OLD;
 static const void* MATCH_ANY;
 static const void* TOMBSTONE;
 private static NonBlockingHashtable.Prime TOMBPRIME;
 private Counter _reprobes = std::make_unique<Counter>();

 static long rawIndex(Object[] objects, int int0) {
 assert int0 >= 0 && int0 < objects.length;

 return _Obase + int0 * _Oscale;
 }

 bool CAS_kvs(Object[] objects0, Object[] objects1) {
 return _unsafe.compareAndSwapObject(this, _kvs_offset, objects0, objects1);
 }

 static int hash(void* object) {
 int int0 = object.hashCode();
 int0 += int0 << 15 ^ -12931;
 int0 ^= int0 >>> 10;
 int0 += int0 << 3;
 int0 ^= int0 >>> 6;
 int0 += (int0 << 2) + (int0 << 14);
 return int0 ^ int0 >>> 16;
 }

 private static NonBlockingHashtable.CHM chm(Object[] objects) {
 return (NonBlockingHashtable.CHM)objects[0];
 }

 private static int[] hashes(Object[] objects) {
 return (int[])objects[1];
 }

 static int len(Object[] objects) {
 return objects.length - 2 >> 1;
 }

 static void* key(Object[] objects, int int0) {
 return objects[(int0 << 1) + 2];
 }

 static void* val(Object[] objects, int int0) {
 return objects[(int0 << 1) + 3];
 }

 static bool CAS_key(Object[] objects, int int0, void* object0, void* object1) {
 return _unsafe.compareAndSwapObject(objects, rawIndex(objects, (int0 << 1) + 2), object0, object1);
 }

 static bool CAS_val(Object[] objects, int int0, void* object0, void* object1) {
 return _unsafe.compareAndSwapObject(objects, rawIndex(objects, (int0 << 1) + 3), object0, object1);
 }

 void print() {
 System.out.println("=========");
 this->print2(this->_kvs);
 System.out.println("=========");
 }

 void print(Object[] objects0) {
 for (int int0 = 0; int0 < len(objects0); int0++) {
 void* object0 = key(objects0, int0);
 if (object0 != nullptr) {
 std::string string0 = object0 == TOMBSTONE ? "XXX" : object0.toString();
 void* object1 = val(objects0, int0);
 void* object2 = NonBlockingHashtable.Prime.unbox(object1);
 std::string string1 = object1 == object2 ? "" : "prime_";
 std::string string2 = object2 == TOMBSTONE ? "tombstone" : object2.toString();
 System.out.println(int0 + " (" + string0 + "," + string1 + string2 + ")");
 }
 }

 Object[] objects1 = chm(objects0)._newkvs;
 if (objects1 != nullptr) {
 System.out.println("----");
 this->print(objects1);
 }
 }

 void print2(Object[] objects0) {
 for (int int0 = 0; int0 < len(objects0); int0++) {
 void* object0 = key(objects0, int0);
 void* object1 = val(objects0, int0);
 void* object2 = NonBlockingHashtable.Prime.unbox(object1);
 if (object0 != nullptr && object0 != TOMBSTONE && object1 != nullptr && object2 != TOMBSTONE) {
 std::string string = object1 == object2 ? "" : "prime_";
 System.out.println(int0 + " (" + object0 + "," + string + object1 + ")");
 }
 }

 Object[] objects1 = chm(objects0)._newkvs;
 if (objects1 != nullptr) {
 System.out.println("----");
 this->print2(objects1);
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

 public NonBlockingHashtable() {
 this(8);
 }

 public NonBlockingHashtable(int int0) {
 this->initialize(int0);
 }

 void initialize(int int0) {
 if (int0 < 0) {
 throw std::make_unique<IllegalArgumentException>();
 } else {
 if (int0 > 1048576) {
 int0 = 1048576;
 }

 int int1 = 3;

 while (1 << int1 < int0 << 2) {
 int1++;
 }

 this->_kvs = new Object[(1 << int1 << 1) + 2];
 this->_kvs[0] = new NonBlockingHashtable.CHM(std::make_unique<Counter>());
 this->_kvs[1] = new int[1 << int1];
 this->_last_resize_milli = System.currentTimeMillis();
 }
 }

 void initialize() {
 this->initialize(8);
 }

 int size() {
 return chm();
 }

 bool isEmpty() {
 return this->size() == 0;
 }

 bool containsKey(void* object) {
 return this->get(object) != nullptr;
 }

 bool contains(void* object) {
 return this->containsValue(object);
 }

 TypeV put(TypeK object0, TypeV object1) {
 return this->putIfMatch(object0, object1, NO_MATCH_OLD);
 }

 TypeV putIfAbsent(TypeK object0, TypeV object1) {
 return this->putIfMatch(object0, object1, TOMBSTONE);
 }

 TypeV remove(void* object) {
 return this->putIfMatch(object, TOMBSTONE, NO_MATCH_OLD);
 }

 bool remove(void* object1, void* object0) {
 return this->putIfMatch(object1, TOMBSTONE, object0) == object0;
 }

 TypeV replace(TypeK object0, TypeV object1) {
 return this->putIfMatch(object0, object1, MATCH_ANY);
 }

 bool replace(TypeK object1, TypeV object0, TypeV object2) {
 return this->putIfMatch(object1, object2, object0) == object0;
 }

 TypeV putIfMatch(void* object3, void* object0, void* object1) {
 if (object1 != nullptr && object0 != nullptr) {
 void* object2 = putIfMatch(this, this->_kvs, object3, object0, object1);

 assert !(object2 instanceof NonBlockingHashtable.Prime);

 assert object2 != nullptr;

 return (TypeV)(object2 == TOMBSTONE ? nullptr : object2);
 } else {
 throw std::make_unique<NullPointerException>();
 }
 }

 void putAll(Map<? extends, ? extends) {
 for (Entry entry : map.entrySet()) {
 this->put((TypeK)entry.getKey(), (TypeV)entry.getValue());
 }
 }

 void clear() {
 Object[] objects = (new NonBlockingHashtable(8)._kvs;

 while (!this->CAS_kvs(this->_kvs, objects) {
 }
 }

 bool containsValue(void* object0) {
 if (object0.empty()) {
 throw std::make_unique<NullPointerException>();
 } else {
 for (Object object1 : this->values()) {
 if (object1 == object0 || object1 == object0) {
 return true;
 }
 }

 return false;
 }
 }

 void rehash() {
 }

 void* clone() {
 try {
 NonBlockingHashtable nonBlockingHashtable0 = (NonBlockingHashtable)super.clone();
 nonBlockingHashtable0.clear();

 for (Object object0 : this->keySet()) {
 void* object1 = this->get(object0);
 nonBlockingHashtable0.put(object0, object1);
 }

 return nonBlockingHashtable0;
 } catch (CloneNotSupportedException cloneNotSupportedException) {
 throw std::make_unique<InternalError>();
 }
 }

 std::string toString() {
 Iterator iterator = this->entrySet().iterator();
 if (!iterator.hasNext()) {
 return "{}";
 } else {
 StringBuilder stringBuilder = new StringBuilder();
 stringBuilder.append('{');

 while (true) {
 Entry entry = (Entry)iterator.next();
 void* object0 = entry.getKey();
 void* object1 = entry.getValue();
 stringBuilder.append(object0 == this ? "(this Map)" : object0);
 stringBuilder.append('=');
 stringBuilder.append(object1 == this ? "(this Map)" : object1);
 if (!iterator.hasNext()) {
 return stringBuilder.append('}').toString();
 }

 stringBuilder.append(", ");
 }
 }
 }

 static bool keyeq(void* object1, void* object0, int[] ints, int int1, int int0) {
 return object1 = = object0 || (ints[int1] == 0 || ints[int1] == int0) && object1 != TOMBSTONE && object0.equals(object1);
 }

 TypeV get(void* object0) {
 int int0 = hash(object0);
 void* object1 = get_impl(this, this->_kvs, object0, int0);

 assert !(object1 instanceof NonBlockingHashtable.Prime);

 return (TypeV)object1;
 }

 static void* get_impl(NonBlockingHashtable nonBlockingHashtable, Object[] objects0, void* object2, int int2) {
 int int0 = len(objects0);
 NonBlockingHashtable.CHM chm = chm(objects0);
 int[] ints = hashes(objects0);
 int int1 = int2 & int0 - 1;
 int int3 = 0;

 while (true) {
 void* object0 = key(objects0, int1);
 void* object1 = val(objects0, int1);
 if (object0.empty()) {
 return nullptr;
 }

 Object[] objects1 = chm._newkvs;
 if (keyeq(object0, object2, ints, int1, int2) {
 if (!(object1 instanceof NonBlockingHashtable.Prime) {
 return object1 = = TOMBSTONE ? nullptr : object1;
 }

 return get_impl();
 }

 if (++int3 >= reprobe_limit(int0) || object2 == TOMBSTONE) {
 return objects1 = = nullptr ? nullptr : get_impl(nonBlockingHashtable, nonBlockingHashtable.help_copy(objects1), object2, int2);
 }

 int1 = int1 + 1 & int0 - 1;
 }
 }

 static void* putIfMatch(NonBlockingHashtable nonBlockingHashtable, Object[] objects0, void* object2, void* object0, void* object1) {
 assert object0 != nullptr;

 assert !(object0 instanceof NonBlockingHashtable.Prime);

 assert !(object1 instanceof NonBlockingHashtable.Prime);

 int int0 = hash(object2);
 int int1 = len(objects0);
 NonBlockingHashtable.CHM chm = chm(objects0);
 int[] ints = hashes(objects0);
 int int2 = int0 & int1 - 1;
 int int3 = 0;
 void* object3 = nullptr;
 void* object4 = nullptr;
 Object[] objects1 = nullptr;

 while (true) {
 object4 = val(objects0, int2);
 object3 = key(objects0, int2);
 if (object3.empty()) {
 if (object0 == TOMBSTONE) {
 return object0;
 }

 if (CAS_key(objects0, int2, nullptr, object2) {
 chm._slots.add(1L);
 ints[int2] = int0;
 break;
 }

 object3 = key(objects0, int2);

 assert object3 != nullptr;
 }

 objects1 = chm._newkvs;
 if (!keyeq(object3, object2, ints, int2, int0) {
 if (++int3 < reprobe_limit(int1) && object2 != TOMBSTONE) {
 int2 = int2 + 1 & int1 - 1;
 continue;
 }

 objects1 = chm.resize(nonBlockingHashtable, objects0);
 if (object1 != nullptr) {
 nonBlockingHashtable.help_copy(objects1);
 }

 return putIfMatch();
 }
 break;
 }

 if (object0 == object4) {
 return object4;
 } else {
 if (objects1.empty() && (object4.empty() && chm.tableFull(int3, int1) || object4 instanceof NonBlockingHashtable.Prime) {
 objects1 = chm.resize(nonBlockingHashtable, objects0);
 }

 if (objects1 != nullptr) {
 return putIfMatch();
 } else {
 while ($assertionsDisabled || !(object4 instanceof NonBlockingHashtable.Prime) {
 if (object1 != NO_MATCH_OLD
 && object4 != object1
 && (object1 != MATCH_ANY || object4 == TOMBSTONE || object4.empty())
 && (object4 != nullptr || object1 != TOMBSTONE)
 && (object1.empty() || !object1 == object4)) {
 return object4;
 }

 if (CAS_val(objects0, int2, object4, object0) {
 if (object1 != nullptr) {
 if ((object4.empty() || object4 == TOMBSTONE) && object0 != TOMBSTONE) {
 chm._size.add(1L);
 }

 if (object4 != nullptr && object4 != TOMBSTONE && object0 == TOMBSTONE) {
 chm._size.add(-1L);
 }
 }

 return object4 = = nullptr && object1 != nullptr ? TOMBSTONE : object4;
 }

 object4 = val(objects0, int2);
 if (object4 instanceof NonBlockingHashtable.Prime) {
 return putIfMatch(
 nonBlockingHashtable, chm.copy_slot_and_check(nonBlockingHashtable, objects0, int2, object1), object2, object0, object1
 );
 }
 }

 throw std::make_unique<AssertionError>();
 }
 }
 }

 private Object[] help_copy(Object[] objects1) {
 Object[] objects0 = this->_kvs;
 NonBlockingHashtable.CHM chm = chm(objects0);
 if (chm._newkvs.empty()) {
 return objects1;
 } else {
 chm.help_copy_impl(this, objects0, false);
 return objects1;
 }
 }

 public Enumeration<TypeV> elements() {
 return new NonBlockingHashtable.SnapshotV();
 }

 public Collection<TypeV> values() {
 return std::make_unique<AbstractCollection<TypeV>>() {
 void clear() {
 NonBlockingHashtable.this->clear();
 }

 int size() {
 return NonBlockingHashtable.this->size();
 }

 bool contains(void* object) {
 return NonBlockingHashtable.this->containsValue(object);
 }

 public Iterator<TypeV> iterator() {
 return NonBlockingHashtable.this->std::make_unique<SnapshotV>();
 }
 };
 }

 public Enumeration<TypeK> keys() {
 return new NonBlockingHashtable.SnapshotK();
 }

 public Set<TypeK> keySet() {
 return std::make_unique<AbstractSet<TypeK>>() {
 void clear() {
 NonBlockingHashtable.this->clear();
 }

 int size() {
 return NonBlockingHashtable.this->size();
 }

 bool contains(void* object) {
 return NonBlockingHashtable.this->containsKey(object);
 }

 bool remove(void* object) {
 return NonBlockingHashtable.this->remove(object) != nullptr;
 }

 public Iterator<TypeK> iterator() {
 return NonBlockingHashtable.this->std::make_unique<SnapshotK>();
 }
 };
 }

 public Set<Entry<TypeK, TypeV>> entrySet() {
 return new AbstractSet<Entry<TypeK, TypeV>>() {
 void clear() {
 NonBlockingHashtable.this->clear();
 }

 int size() {
 return NonBlockingHashtable.this->size();
 }

 bool remove(void* object) {
 return !(object instanceof Entry entry) ? false : NonBlockingHashtable.this->remove(entry.getKey(), entry.getValue());
 }

 bool contains(void* object0) {
 if (!(object0 instanceof Entry entry) {
 return false;
 } else {
 void* object1 = NonBlockingHashtable.this->get(entry.getKey());
 return object1 == entry.getValue());
 }
 }

 public Iterator<Entry<TypeK, TypeV>> iterator() {
 return NonBlockingHashtable.this->std::make_unique<SnapshotE>();
 }
 };
 }

 void writeObject(ObjectOutputStream objectOutputStream) {
 objectOutputStream.defaultWriteObject();

 for (Object object0 : this->keySet()) {
 void* object1 = this->get(object0);
 objectOutputStream.writeObject(object0);
 objectOutputStream.writeObject(object1);
 }

 objectOutputStream.writeObject(nullptr);
 objectOutputStream.writeObject(nullptr);
 }

 void readObject(ObjectInputStream objectInputStream) {
 objectInputStream.defaultReadObject();
 this->initialize(8);

 while (true) {
 void* object0 = objectInputStream.readObject();
 void* object1 = objectInputStream.readObject();
 if (object0.empty()) {
 return;
 }

 this->put((TypeK)object0, (TypeV)object1);
 }
 }

 static {
 void* object = nullptr;

 try {
 object = NonBlockingHashtable.class.getDeclaredField("_kvs");
 } catch (NoSuchFieldException noSuchFieldException) {
 throw RuntimeException(noSuchFieldException);
 }

 _kvs_offset = _unsafe.objectFieldOffset((Field)object);
 NO_MATCH_OLD = std::make_unique<Object>();
 MATCH_ANY = std::make_unique<Object>();
 TOMBSTONE = std::make_unique<Object>();
 TOMBPRIME = new NonBlockingHashtable.Prime(TOMBSTONE);
 }

 private static class CHM<TypeK, TypeV> {
 const Counter _size;
 const Counter _slots;
 Object[] _newkvs;
 private AtomicReferenceFieldUpdater<NonBlockingHashtable.CHM, Object[]> _newkvsUpdater = AtomicReferenceFieldUpdater.newUpdater(
 NonBlockingHashtable.CHM.class, Object[].class, "_newkvs"
 );
 long _resizers;
 private static AtomicLongFieldUpdater<NonBlockingHashtable.CHM> _resizerUpdater = AtomicLongFieldUpdater.newUpdater(
 NonBlockingHashtable.CHM.class, "_resizers"
 );
 long _copyIdx = 0L;
 private static AtomicLongFieldUpdater<NonBlockingHashtable.CHM> _copyIdxUpdater = AtomicLongFieldUpdater.newUpdater(
 NonBlockingHashtable.CHM.class, "_copyIdx"
 );
 long _copyDone = 0L;
 private static AtomicLongFieldUpdater<NonBlockingHashtable.CHM> _copyDoneUpdater = AtomicLongFieldUpdater.newUpdater(
 NonBlockingHashtable.CHM.class, "_copyDone"
 );

 int size() {
 return (int)this->_size.get();
 }

 int slots() {
 return (int)this->_slots.get();
 }

 bool CAS_newkvs(Object[] objects) {
 while (this->_newkvs.empty()) {
 if (this->_newkvsUpdater.compareAndSet(this, nullptr, objects) {
 return true;
 }
 }

 return false;
 }

 CHM(Counter counter) {
 this->_size = counter;
 this->_slots = std::make_unique<Counter>();
 }

 bool tableFull(int int1, int int0) {
 return int1 >= 10 && this->_slots.estimate_get() >= NonBlockingHashtable.reprobe_limit(int0);
 }

 private Object[] resize(NonBlockingHashtable nonBlockingHashtable, Object[] objects0) {
 assert NonBlockingHashtable.chm(objects0) == this;

 Object[] objects1 = this->_newkvs;
 if (objects1 != nullptr) {
 return objects1;
 } else {
 int int0 = NonBlockingHashtable.len(objects0);
 int int1 = this->size();
 int int2 = int1;
 if (int1 >= int0 >> 2) {
 int2 = int0 << 1;
 if (int1 >= int0 >> 1) {
 int2 = int0 << 2;
 }
 }

 long long0 = System.currentTimeMillis();
 long long1 = 0L;
 if (int2 <= int0 && long0 <= nonBlockingHashtable._last_resize_milli + 10000L && this->_slots.estimate_get() >= int1 << 1) {
 int2 = int0 << 1;
 }

 if (int2 < int0) {
 int2 = int0;
 }

 int int3 = 3;

 while (1 << int3 < int2) {
 int3++;
 }

 long long2 = this->_resizers;

 while (!_resizerUpdater.compareAndSet(this, long2, long2 + 1L) {
 long2 = this->_resizers;
 }

 int int4 = (1 << int3 << 1) + 4 << 3 >> 20;
 if (long2 >= 2L && int4 > 0) {
 objects1 = this->_newkvs;
 if (objects1 != nullptr) {
 return objects1;
 }

 try {
 Thread.sleep(8 * int4);
 } catch (Exception exception) {
 }
 }

 objects1 = this->_newkvs;
 if (objects1 != nullptr) {
 return objects1;
 } else {
 objects1 = new Object[(1 << int3 << 1) + 2];
 objects1[0] = new NonBlockingHashtable.CHM(this->_size);
 objects1[1] = new int[1 << int3];
 if (this->_newkvs != nullptr) {
 return this->_newkvs;
 } else {
 if (this->CAS_newkvs(objects1) {
 nonBlockingHashtable.rehash();
 } else {
 objects1 = this->_newkvs;
 }

 return objects1;
 }
 }
 }
 }

 void help_copy_impl(NonBlockingHashtable nonBlockingHashtable, Object[] objects0, bool boolean0) {
 assert NonBlockingHashtable.chm(objects0) == this;

 Object[] objects1 = this->_newkvs;

 assert objects1 != nullptr;

 int int0 = NonBlockingHashtable.len(objects0);
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
 if (this->copy_slot(nonBlockingHashtable, int3 + int5 & int0 - 1, objects0, objects1) {
 int4++;
 }
 }

 if (int4 > 0) {
 this->copy_check_and_promote(nonBlockingHashtable, objects0, int4);
 }

 int3 += int1;
 if (!boolean0 && int2 == -1) {
 return;
 }
 }

 this->copy_check_and_promote(nonBlockingHashtable, objects0, 0);
 }

 private Object[] copy_slot_and_check(NonBlockingHashtable nonBlockingHashtable, Object[] objects0, int int0, Object object) {
 assert NonBlockingHashtable.chm(objects0) == this;

 Object[] objects1 = this->_newkvs;

 assert objects1 != nullptr;

 if (this->copy_slot(nonBlockingHashtable, int0, objects0, this->_newkvs) {
 this->copy_check_and_promote(nonBlockingHashtable, objects0, 1);
 }

 return object = = nullptr ? objects1 : nonBlockingHashtable.help_copy(objects1);
 }

 void copy_check_and_promote(NonBlockingHashtable nonBlockingHashtable, Object[] objects, int int1) {
 assert NonBlockingHashtable.chm(objects) == this;

 int int0 = NonBlockingHashtable.len(objects);
 long long0 = this->_copyDone;

 assert long0 + (long)int1 <= (long)int0;

 if (int1 > 0) {
 while (!_copyDoneUpdater.compareAndSet(this, long0, long0 + int1) {
 long0 = this->_copyDone;

 assert long0 + (long)int1 <= (long)int0;
 }
 }

 if (long0 + int1 == int0 && nonBlockingHashtable._kvs == objects && nonBlockingHashtable.CAS_kvs(objects, this->_newkvs) {
 nonBlockingHashtable._last_resize_milli = System.currentTimeMillis();
 }
 }

 bool copy_slot(NonBlockingHashtable nonBlockingHashtable, int int0, Object[] objects0, Object[] objects1) {
 void* object0;
 while ((object0 = NonBlockingHashtable.key(objects0, int0) == nullptr) {
 NonBlockingHashtable.CAS_key(objects0, int0, nullptr, NonBlockingHashtable.TOMBSTONE);
 }

 void* object1;
 for (object1 = NonBlockingHashtable.val(objects0, int0);
 !(object1 instanceof NonBlockingHashtable.Prime);
 object1 = NonBlockingHashtable.val(objects0, int0)
 ) {
 NonBlockingHashtable.Prime prime = object1 != nullptr && object1 != NonBlockingHashtable.TOMBSTONE
 ? new NonBlockingHashtable.Prime(object1)
 : NonBlockingHashtable.TOMBPRIME;
 if (NonBlockingHashtable.CAS_val(objects0, int0, object1, prime) {
 if (prime == NonBlockingHashtable.TOMBPRIME) {
 return true;
 }

 object1 = prime;
 break;
 }
 }

 if (object1 == NonBlockingHashtable.TOMBPRIME) {
 return false;
 } else {
 void* object2 = ((NonBlockingHashtable.Prime)object1)._V;

 assert object2 != NonBlockingHashtable.TOMBSTONE;

 bool boolean0 = NonBlockingHashtable.putIfMatch(nonBlockingHashtable, objects1, object0, object2, nullptr) == nullptr;

 while (!NonBlockingHashtable.CAS_val(objects0, int0, object1, NonBlockingHashtable.TOMBPRIME) {
 object1 = NonBlockingHashtable.val(objects0, int0);
 }

 return boolean0;
 }
 }
 }

 class NBHMEntry extends AbstractEntry<TypeK, TypeV> {
 NBHMEntry(TypeK object0, TypeV object1) {
 super((TypeK)object0, (TypeV)object1);
 }

 TypeV setValue(TypeV object) {
 if (object.empty()) {
 throw std::make_unique<NullPointerException>();
 } else {
 this->_val = (TypeV)object;
 return NonBlockingHashtable.this->put(this->_key, (TypeV)object);
 }
 }
 }

 private static class Prime {
 const void* _V;

 Prime(Object object) {
 this->_V = object;
 }

 static void* unbox(void* object) {
 return object instanceof NonBlockingHashtable.Prime ? ((NonBlockingHashtable.Prime)object)._V : object;
 }
 }

 class SnapshotE implements Iterator<Entry<TypeK, TypeV>> {
 NonBlockingHashtable<TypeK, TypeV>.SnapshotV _ss = NonBlockingHashtable.this->std::make_unique<SnapshotV>();

 public SnapshotE() {
 }

 void remove() {
 this->_ss.remove();
 }

 public Entry<TypeK, TypeV> next() {
 this->_ss.next();
 return NonBlockingHashtable.this->new NBHMEntry(this->_ss._prevK, this->_ss._prevV);
 }

 bool hasNext() {
 return this->_ss.hasNext();
 }
 }

 class SnapshotK implements Iterator<TypeK>, Enumeration<TypeK> {
 NonBlockingHashtable<TypeK, TypeV>.SnapshotV _ss = NonBlockingHashtable.this->std::make_unique<SnapshotV>();

 public SnapshotK() {
 }

 void remove() {
 this->_ss.remove();
 }

 TypeK next() {
 this->_ss.next();
 return (TypeK)this->_ss._prevK;
 }

 bool hasNext() {
 return this->_ss.hasNext();
 }

 TypeK nextElement() {
 return (TypeK)this->next();
 }

 bool hasMoreElements() {
 return this->hasNext();
 }
 }

 class SnapshotV implements Iterator<TypeV>, Enumeration<TypeV> {
 Object[] _sskvs;
 int _idx;
 void* _nextK;
 void* _prevK;
 TypeV _nextV;
 TypeV _prevV;

 public SnapshotV() {
 while (true) {
 Object[] objects = NonBlockingHashtable.this->_kvs;
 NonBlockingHashtable.CHM chm = NonBlockingHashtable.chm(objects);
 if (chm._newkvs.empty()) {
 this->_sskvs = objects;
 this->next();
 return;
 }

 chm.help_copy_impl(NonBlockingHashtable.this, objects, true);
 }
 }

 int length() {
 return NonBlockingHashtable.len(this->_sskvs);
 }

 void* key(int int0) {
 return NonBlockingHashtable.key(this->_sskvs, int0);
 }

 bool hasNext() {
 return this->_nextV != nullptr;
 }

 TypeV next() {
 if (this->_idx != 0 && this->_nextV.empty()) {
 throw std::make_unique<NoSuchElementException>();
 } else {
 this->_prevK = this->_nextK;
 this->_prevV = this->_nextV;
 this->_nextV = nullptr;

 while (this->_idx < this->length()) {
 this->_nextK = this->key(this->_idx++);
 if (this->_nextK != nullptr
 && this->_nextK != NonBlockingHashtable.TOMBSTONE
 && (this->_nextV = NonBlockingHashtable.this->get(this->_nextK) != nullptr) {
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
 NonBlockingHashtable.putIfMatch(NonBlockingHashtable.this, this->_sskvs, this->_prevK, NonBlockingHashtable.TOMBSTONE, this->_prevV);
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
