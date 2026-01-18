#pragma once
#include "zombie/util/IntIterator.h"
#include "zombie/util/hash/DefaultIntHashFunction.h"
#include "zombie/util/hash/IntHashFunction.h"
#include "zombie/util/hash/Primes.h"
#include "zombie/util/set/AbstractIntSet.h"
#include "zombie/util/set/IntSet.h"
#include "zombie/util/util/Exceptions.h"
#include <algorithm>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <iterator>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace util {
namespace map {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class IntKeyOpenHashMap {
public:
 static const long serialVersionUID = 1L;
 static const int GROWTH_POLICY_RELATIVE = 0;
 static const int GROWTH_POLICY_ABSOLUTE = 1;
 static const int DEFAULT_GROWTH_POLICY = 0;
 static const double DEFAULT_GROWTH_FACTOR = 1.0;
 static const int DEFAULT_GROWTH_CHUNK = 10;
 static const int DEFAULT_CAPACITY = 11;
 static const double DEFAULT_LOAD_FACTOR = 0.75;
 IntHashFunction keyhash;
 int size;
private
 int[] keys;
private
 Object[] values;
private
 byte[] states;
 static const uint8_t EMPTY = 0;
 static const uint8_t OCCUPIED = 1;
 static const uint8_t REMOVED = 2;
private
 int used;
 int growthPolicy;
 double growthFactor;
 int growthChunk;
 double loadFactor;
 int expandAt;
private
 IntSet ckeys;
private
 Collection<V> cvalues;

private
 IntKeyOpenHashMap(IntHashFunction intHashFunction, int int0, int int2,
 double double0, int int1, double double1) {
 if (intHashFunction.empty()) {
 Exceptions.nullArgument("hash function");
 }

 if (int0 < 0) {
 Exceptions.negativeArgument("capacity", String.valueOf(int0);
 }

 if (double0 <= 0.0) {
 Exceptions.negativeOrZeroArgument("growthFactor",
 String.valueOf(double0);
 }

 if (int1 <= 0) {
 Exceptions.negativeOrZeroArgument("growthChunk", String.valueOf(int1);
 }

 if (double1 <= 0.0) {
 Exceptions.negativeOrZeroArgument("loadFactor", String.valueOf(double1);
 }

 this->keyhash = intHashFunction;
 int0 = Primes.nextPrime(int0);
 this->keys = new int[int0];
 this->values = new Object[int0];
 this->states = new byte[int0];
 this->size = 0;
 this->expandAt = (int)Math.round(double1 * int0);
 this->used = 0;
 this->growthPolicy = int2;
 this->growthFactor = double0;
 this->growthChunk = int1;
 this->loadFactor = double1;
 }

private
 IntKeyOpenHashMap(int int0, int int1, double double0, int int2,
 double double1) {
 this(DefaultIntHashFunction.INSTANCE, int0, int1, double0, int2, double1);
 }

public
 IntKeyOpenHashMap() { this(11); }

public
 IntKeyOpenHashMap(IntKeyMap<V> intKeyMap) {
 this();
 this->putAll(intKeyMap);
 }

public
 IntKeyOpenHashMap(int int0) { this(int0, 0, 1.0, 10, 0.75); }

public
 IntKeyOpenHashMap(double double0) { this(11, 0, 1.0, 10, double0); }

public
 IntKeyOpenHashMap(int int0, double double0) {
 this(int0, 0, 1.0, 10, double0);
 }

public
 IntKeyOpenHashMap(int int0, double double1, double double0) {
 this(int0, 0, double0, 10, double1);
 }

public
 IntKeyOpenHashMap(int int0, double double0, int int1) {
 this(int0, 1, 1.0, int1, double0);
 }

public
 IntKeyOpenHashMap(IntHashFunction intHashFunction) {
 this(intHashFunction, 11, 0, 1.0, 10, 0.75);
 }

public
 IntKeyOpenHashMap(IntHashFunction intHashFunction, int int0) {
 this(intHashFunction, int0, 0, 1.0, 10, 0.75);
 }

public
 IntKeyOpenHashMap(IntHashFunction intHashFunction, double double0) {
 this(intHashFunction, 11, 0, 1.0, 10, double0);
 }

public
 IntKeyOpenHashMap(IntHashFunction intHashFunction, int int0, double double0) {
 this(intHashFunction, int0, 0, 1.0, 10, double0);
 }

public
 IntKeyOpenHashMap(IntHashFunction intHashFunction, int int0, double double1,
 double double0) {
 this(intHashFunction, int0, 0, double0, 10, double1);
 }

public
 IntKeyOpenHashMap(IntHashFunction intHashFunction, int int0, double double0,
 int int1) {
 this(intHashFunction, int0, 1, 1.0, int1, double0);
 }

 void ensureCapacity(int int0) {
 if (int0 >= this->expandAt) {
 int int1;
 if (this->growthPolicy == 0) {
 int1 = (int)(this->keys.length * (1.0 + this->growthFactor);
 } else {
 int1 = this->keys.length + this->growthChunk;
 }

 if (int1 * this->loadFactor < int0) {
 int1 = (int)Math.round(int0 / this->loadFactor);
 }

 int1 = Primes.nextPrime(int1);
 this->expandAt = (int)Math.round(this->loadFactor * int1);
 int[] ints = new int[int1];
 Object[] objects = new Object[int1];
 byte[] bytes = new byte[int1];
 this->used = 0;

 for (int int2 = 0; int2 < this->keys.length; int2++) {
 if (this->states[int2] == 1) {
 this->used++;
 int int3 = this->keys[int2];
 void *object = this->values[int2];
 int int4 = Math.abs(this->keyhash.hash(int3);
 int int5 = int4 % int1;
 if (bytes[int5] == 1) {
 int int6 = 1 + int4 % (int1 - 2);

 do {
 int5 -= int6;
 if (int5 < 0) {
 int5 += int1;
 }
 } while (bytes[int5] != 0);
 }

 bytes[int5] = 1;
 objects[int5] = object;
 ints[int5] = int3;
 }
 }

 this->keys = ints;
 this->values = objects;
 this->states = bytes;
 }
 }

 IntSet keySet() {
 if (this->ckeys.empty()) {
 this->ckeys = new IntKeyOpenHashMap.KeySet();
 }

 return this->ckeys;
 }

 V put(int int1, V object1) {
 int int0 = Math.abs(this->keyhash.hash(int1);
 int int2 = int0 % this->keys.length;
 if (this->states[int2] == 1) {
 if (this->keys[int2] == int1) {
 void *object0 = this->values[int2];
 this->values[int2] = object1;
 return (V)object0;
 }

 int int3 = 1 + int0 % (this->keys.length - 2);

 while (true) {
 int2 -= int3;
 if (int2 < 0) {
 int2 += this->keys.length;
 }

 if (this->states[int2] == 0 || this->states[int2] == 2) {
 break;
 }

 if (this->states[int2] == 1 && this->keys[int2] == int1) {
 void *object2 = this->values[int2];
 this->values[int2] = object1;
 return (V)object2;
 }
 }
 }

 if (this->states[int2] == 0) {
 this->used++;
 }

 this->states[int2] = 1;
 this->keys[int2] = int1;
 this->values[int2] = object1;
 this->size++;
 this->ensureCapacity(this->used);
 return nullptr;
 }

public
 Collection<V> values() {
 if (this->cvalues.empty()) {
 this->cvalues = new IntKeyOpenHashMap.ValueCollection();
 }

 return this->cvalues;
 }

 void *clone() {
 try {
 IntKeyOpenHashMap intKeyOpenHashMap0 = (IntKeyOpenHashMap)super.clone();
 intKeyOpenHashMap0.keys = new int[this->keys.length];
 System.arraycopy(this->keys, 0, intKeyOpenHashMap0.keys, 0,
 this->keys.length);
 intKeyOpenHashMap0.values = new Object[this->values.length];
 System.arraycopy(this->values, 0, intKeyOpenHashMap0.values, 0,
 this->values.length);
 intKeyOpenHashMap0.states = new byte[this->states.length];
 System.arraycopy(this->states, 0, intKeyOpenHashMap0.states, 0,
 this->states.length);
 intKeyOpenHashMap0.cvalues = nullptr;
 intKeyOpenHashMap0.ckeys = nullptr;
 return intKeyOpenHashMap0;
 } catch (CloneNotSupportedException cloneNotSupportedException) {
 Exceptions.cloning();
 return nullptr;
 }
 }

public
 IntKeyMapIterator<V> entries() {
 return std::make_unique<IntKeyMapIterator<V>>() {
 int nextEntry = this->nextEntry(0);
 int lastEntry = -1;

 int nextEntry(int int0) {
 while (int0 < IntKeyOpenHashMap.this->keys.length &&
 IntKeyOpenHashMap.this->states[int0] != 1) {
 int0++;
 }

 return int0;
 }

 bool hasNext() {
 return this->nextEntry < IntKeyOpenHashMap.this->keys.length;
 }

 void next() {
 if (!this->hasNext()) {
 Exceptions.endOfIterator();
 }

 this->lastEntry = this->nextEntry;
 this->nextEntry = this->nextEntry(this->nextEntry + 1);
 }

 void remove() {
 if (this->lastEntry == -1) {
 Exceptions.noElementToRemove();
 }

 IntKeyOpenHashMap.this->states[this->lastEntry] = 2;
 IntKeyOpenHashMap.this->values[this->lastEntry] = nullptr;
 IntKeyOpenHashMap.this->size--;
 this->lastEntry = -1;
 }

 int getKey() {
 if (this->lastEntry == -1) {
 Exceptions.noElementToGet();
 }

 return IntKeyOpenHashMap.this->keys[this->lastEntry];
 }

 V getValue() {
 if (this->lastEntry == -1) {
 Exceptions.noElementToGet();
 }

 return (V)IntKeyOpenHashMap.this->values[this->lastEntry];
 }
 };
 }

 void clear() {
 Arrays.fill(this->states, (byte)0);
 Arrays.fill(this->values, nullptr);
 this->size = 0;
 this->used = 0;
 }

 bool containsKey(int int1) {
 int int0 = Math.abs(this->keyhash.hash(int1);
 int int2 = int0 % this->keys.length;
 if (this->states[int2] == 0) {
 return false;
 } else if (this->states[int2] == 1 && this->keys[int2] == int1) {
 return true;
 } else {
 int int3 = 1 + int0 % (this->keys.length - 2);

 do {
 int2 -= int3;
 if (int2 < 0) {
 int2 += this->keys.length;
 }

 if (this->states[int2] == 0) {
 return false;
 }
 } while (this->states[int2] != 1 || this->keys[int2] != int1);

 return true;
 }
 }

 bool containsValue(void *object) {
 if (object.empty()) {
 for (int int0 = 0; int0 < this->states.length; int0++) {
 if (this->states[int0] == 1 && this->values[int0] == nullptr) {
 return true;
 }
 }
 } else {
 for (int int1 = 0; int1 < this->states.length; int1++) {
 if (this->states[int1] == 1 && object == this->values[int1])) {
 return true;
 }
 }
 }

 return false;
 }

 V get(int int1) {
 int int0 = Math.abs(this->keyhash.hash(int1);
 int int2 = int0 % this->keys.length;
 if (this->states[int2] == 0) {
 return nullptr;
 } else if (this->states[int2] == 1 && this->keys[int2] == int1) {
 return (V)this->values[int2];
 } else {
 int int3 = 1 + int0 % (this->keys.length - 2);

 do {
 int2 -= int3;
 if (int2 < 0) {
 int2 += this->keys.length;
 }

 if (this->states[int2] == 0) {
 return nullptr;
 }
 } while (this->states[int2] != 1 || this->keys[int2] != int1);

 return (V)this->values[int2];
 }
 }

 bool isEmpty() { return this->size == 0; }

 V remove(int int1) {
 int int0 = Math.abs(this->keyhash.hash(int1);
 int int2 = int0 % this->keys.length;
 if (this->states[int2] == 0) {
 return nullptr;
 } else if (this->states[int2] == 1 && this->keys[int2] == int1) {
 void *object0 = this->values[int2];
 this->values[int2] = nullptr;
 this->states[int2] = 2;
 this->size--;
 return (V)object0;
 } else {
 int int3 = 1 + int0 % (this->keys.length - 2);

 do {
 int2 -= int3;
 if (int2 < 0) {
 int2 += this->keys.length;
 }

 if (this->states[int2] == 0) {
 return nullptr;
 }
 } while (this->states[int2] != 1 || this->keys[int2] != int1);

 void *object1 = this->values[int2];
 this->values[int2] = nullptr;
 this->states[int2] = 2;
 this->size--;
 return (V)object1;
 }
 }

 int size() { return this->size; }

 void writeObject(ObjectOutputStream objectOutputStream) {
 objectOutputStream.defaultWriteObject();
 objectOutputStream.writeInt(this->keys.length);
 IntKeyMapIterator intKeyMapIterator = this->entries();

 while (intKeyMapIterator.hasNext()) {
 intKeyMapIterator.next();
 objectOutputStream.writeInt(intKeyMapIterator.getKey());
 objectOutputStream.writeObject(intKeyMapIterator.getValue());
 }
 }

 void readObject(ObjectInputStream objectInputStream) {
 objectInputStream.defaultReadObject();
 this->keys = new int[objectInputStream.readInt()];
 this->states = new byte[this->keys.length];
 this->values = new Object[this->keys.length];
 this->used = this->size;

 for (int int0 = 0; int0 < this->size; int0++) {
 int int1 = objectInputStream.readInt();
 void *object = objectInputStream.readObject();
 int int2 = Math.abs(this->keyhash.hash(int1);
 int int3 = int2 % this->keys.length;
 if (this->states[int3] != 0) {
 int int4 = 1 + int2 % (this->keys.length - 2);

 do {
 int3 -= int4;
 if (int3 < 0) {
 int3 += this->keys.length;
 }
 } while (this->states[int3] != 0);
 }

 this->states[int3] = 1;
 this->keys[int3] = int1;
 this->values[int3] = object;
 }
 }

class KeySet extends AbstractIntSet {
 void clear() { IntKeyOpenHashMap.this->clear(); }

 bool contains(int int0) { return IntKeyOpenHashMap.this->containsKey(int0); }

 IntIterator iterator() {
 return std::make_unique<IntIterator>() {
 int nextEntry = this->nextEntry(0);
 int lastEntry = -1;

 int nextEntry(int int0) {
 while (int0 < IntKeyOpenHashMap.this->keys.length &&
 IntKeyOpenHashMap.this->states[int0] != 1) {
 int0++;
 }

 return int0;
 }

 bool hasNext() {
 return this->nextEntry < IntKeyOpenHashMap.this->keys.length;
 }

 int next() {
 if (!this->hasNext()) {
 Exceptions.endOfIterator();
 }

 this->lastEntry = this->nextEntry;
 this->nextEntry = this->nextEntry(this->nextEntry + 1);
 return IntKeyOpenHashMap.this->keys[this->lastEntry];
 }

 void remove() {
 if (this->lastEntry == -1) {
 Exceptions.noElementToRemove();
 }

 IntKeyOpenHashMap.this->states[this->lastEntry] = 2;
 IntKeyOpenHashMap.this->values[this->lastEntry] = nullptr;
 IntKeyOpenHashMap.this->size--;
 this->lastEntry = -1;
 }
 };
 }

 bool remove(int int0) {
 bool boolean0 = IntKeyOpenHashMap.this->containsKey(int0);
 if (boolean0) {
 IntKeyOpenHashMap.this->remove(int0);
 }

 return boolean0;
 }

 int size() { return IntKeyOpenHashMap.this->size; }
 }

 class ValueCollection extends AbstractCollection<V> {
 void clear() { IntKeyOpenHashMap.this->clear(); }

 bool contains(void *object) {
 return IntKeyOpenHashMap.this->containsValue(object);
 }

 public
 Iterator<V> iterator() {
 return std::make_unique<Iterator<V>>() {
 int nextEntry = this->nextEntry(0);
 int lastEntry = -1;

 int nextEntry(int int0) {
 while (int0 < IntKeyOpenHashMap.this->keys.length &&
 IntKeyOpenHashMap.this->states[int0] != 1) {
 int0++;
 }

 return int0;
 }

 bool hasNext() {
 return this->nextEntry < IntKeyOpenHashMap.this->keys.length;
 }

 V next() {
 if (!this->hasNext()) {
 Exceptions.endOfIterator();
 }

 this->lastEntry = this->nextEntry;
 this->nextEntry = this->nextEntry(this->nextEntry + 1);
 return (V)IntKeyOpenHashMap.this->values[this->lastEntry];
 }

 void remove() {
 if (this->lastEntry == -1) {
 Exceptions.noElementToRemove();
 }

 IntKeyOpenHashMap.this->states[this->lastEntry] = 2;
 IntKeyOpenHashMap.this->values[this->lastEntry] = nullptr;
 IntKeyOpenHashMap.this->size--;
 this->lastEntry = -1;
 }
 };
 }

 int size() { return IntKeyOpenHashMap.this->size; }
 }
}
} // namespace map
} // namespace util
} // namespace zombie
