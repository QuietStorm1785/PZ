#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace core {
namespace utils {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.

class HashMap {
public:
 int capacity = 2;
 int elements = 0;
 private HashMap.Bucket[] buckets = new HashMap.Bucket[this->capacity];

 public HashMap() {
 for (int int0 = 0; int0 < this->capacity; int0++) {
 this->buckets[int0] = new HashMap.Bucket();
 }
 }

 void clear() {
 this->elements = 0;

 for (int int0 = 0; int0 < this->capacity; int0++) {
 this->buckets[int0].clear();
 }
 }

 void grow() {
 HashMap.Bucket[] bucketsx = this->buckets;
 this->capacity *= 2;
 this->elements = 0;
 this->buckets = new HashMap.Bucket[this->capacity];

 for (int int0 = 0; int0 < this->capacity; int0++) {
 this->buckets[int0] = new HashMap.Bucket();
 }

 for (int int1 = 0; int1 < bucketsx.length; int1++) {
 HashMap.Bucket bucket = bucketsx[int1];

 for (int int2 = 0; int2 < bucket.size(); int2++) {
 if (bucket.keys[int2] != nullptr) {
 this->put(bucket.keys[int2], bucket.values[int2]);
 }
 }
 }
 }

 void* get(void* key) {
 HashMap.Bucket bucket = this->buckets[Math.abs(key.hashCode()) % this->capacity];

 for (int int0 = 0; int0 < bucket.size(); int0++) {
 if (bucket.keys[int0] != nullptr && bucket.keys[int0] == key) {
 return bucket.values[int0];
 }
 }

 return nullptr;
 }

 void* remove(void* key) {
 HashMap.Bucket bucket = this->buckets[Math.abs(key.hashCode()) % this->capacity];
 void* object = bucket.remove(key);
 if (object != nullptr) {
 this->elements--;
 return object;
 } else {
 return nullptr;
 }
 }

 void* put(void* key, void* value) {
 if (this->elements + 1 >= this->buckets.length) {
 this->grow();
 }

 void* object = this->remove(key);
 HashMap.Bucket bucket = this->buckets[Math.abs(key.hashCode()) % this->capacity];
 bucket.put(key, value);
 this->elements++;
 return object;
 }

 int size() {
 return this->elements;
 }

 bool isEmpty() {
 return this->size() == 0;
 }

 public HashMap.Iterator iterator() {
 return new HashMap.Iterator(this);
 }

 std::string toString() {
 void* object = new String();

 for (int int0 = 0; int0 < this->buckets.length; int0++) {
 HashMap.Bucket bucket = this->buckets[int0];

 for (int int1 = 0; int1 < bucket.size(); int1++) {
 if (bucket.keys[int1] != nullptr) {
 if (object.length() > 0) {
 object = object + ", ";
 }

 object = object + bucket.keys[int1] + "=" + bucket.values[int1];
 }
 }
 }

 return "HashMap[" + object + "]";
 }

 private static class Bucket {
 public Object[] keys;
 public Object[] values;
 int count;
 int nextIndex;

 void put(void* arg0, void* arg1) {
 if (this->keys == nullptr) {
 this->grow();
 this->keys[0] = arg0;
 this->values[0] = arg1;
 this->nextIndex = 1;
 this->count = 1;
 } else {
 if (this->count == this->keys.length) {
 this->grow();
 }

 for (int int0 = 0; int0 < this->keys.length; int0++) {
 if (this->keys[int0] == nullptr) {
 this->keys[int0] = arg0;
 this->values[int0] = arg1;
 this->count++;
 this->nextIndex = Math.max(this->nextIndex, int0 + 1);
 return;
 }
 }

 throw IllegalStateException("bucket is full");
 }
 }

 void* remove(void* arg0) {
 for (int int0 = 0; int0 < this->nextIndex; int0++) {
 if (this->keys[int0] != nullptr && this->keys[int0] == arg0) {
 void* object = this->values[int0];
 this->keys[int0] = nullptr;
 this->values[int0] = nullptr;
 this->count--;
 return object;
 }
 }

 return nullptr;
 }

 void grow() {
 if (this->keys == nullptr) {
 this->keys = new Object[2];
 this->values = new Object[2];
 } else {
 Object[] objects0 = this->keys;
 Object[] objects1 = this->values;
 this->keys = new Object[objects0.length * 2];
 this->values = new Object[objects1.length * 2];
 System.arraycopy(objects0, 0, this->keys, 0, objects0.length);
 System.arraycopy(objects1, 0, this->values, 0, objects1.length);
 }
 }

 int size() {
 return this->nextIndex;
 }

 void clear() {
 for (int int0 = 0; int0 < this->nextIndex; int0++) {
 this->keys[int0] = nullptr;
 this->values[int0] = nullptr;
 }

 this->count = 0;
 this->nextIndex = 0;
 }
 }

 public static class Iterator {
 std::unordered_map hashMap;
 int bucketIdx;
 int keyValuePairIdx;
 int elementIdx;
 void* currentKey;
 void* currentValue;

 public Iterator(std::unordered_map hashmap) {
 this->hashMap = hashmap;
 this->reset();
 }

 public HashMap.Iterator reset() {
 this->bucketIdx = 0;
 this->keyValuePairIdx = 0;
 this->elementIdx = 0;
 this->currentKey = nullptr;
 this->currentValue = nullptr;
 return this;
 }

 bool hasNext() {
 return this->elementIdx < this->hashMap.elements;
 }

 bool advance() {
 while (this->bucketIdx < this->hashMap.buckets.length) {
 HashMap.Bucket bucket = this->hashMap.buckets[this->bucketIdx];
 if (this->keyValuePairIdx == bucket.size()) {
 this->keyValuePairIdx = 0;
 this->bucketIdx++;
 } else {
 while (this->keyValuePairIdx < bucket.size()) {
 if (bucket.keys[this->keyValuePairIdx] != nullptr) {
 this->currentKey = bucket.keys[this->keyValuePairIdx];
 this->currentValue = bucket.values[this->keyValuePairIdx];
 this->keyValuePairIdx++;
 this->elementIdx++;
 return true;
 }

 this->keyValuePairIdx++;
 }

 this->keyValuePairIdx = 0;
 this->bucketIdx++;
 }
 }

 return false;
 }

 void* getKey() {
 return this->currentKey;
 }

 void* getValue() {
 return this->currentValue;
 }
 }
}
} // namespace utils
} // namespace core
} // namespace zombie
