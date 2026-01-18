#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/util/hash/DefaultIntHashFunction.h"

namespace zombie {
namespace util {
namespace map {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class AbstractIntKeyMap {
public:
 protected AbstractIntKeyMap() {
 }

 void clear() {
 IntKeyMapIterator intKeyMapIterator = this->entries();

 while (intKeyMapIterator.hasNext()) {
 intKeyMapIterator.next();
 intKeyMapIterator.remove();
 }
 }

 V remove(int int0) {
 IntKeyMapIterator intKeyMapIterator = this->entries();

 while (intKeyMapIterator.hasNext()) {
 intKeyMapIterator.next();
 if (intKeyMapIterator.getKey() == int0) {
 void* object = intKeyMapIterator.getValue();
 intKeyMapIterator.remove();
 return (V)object;
 }
 }

 return nullptr;
 }

 void putAll(IntKeyMap<V> intKeyMap) {
 IntKeyMapIterator intKeyMapIterator = intKeyMap.entries();

 while (intKeyMapIterator.hasNext()) {
 intKeyMapIterator.next();
 this->put(intKeyMapIterator.getKey(), (V)intKeyMapIterator.getValue());
 }
 }

 bool containsKey(int int0) {
 IntKeyMapIterator intKeyMapIterator = this->entries();

 while (intKeyMapIterator.hasNext()) {
 intKeyMapIterator.next();
 if (intKeyMapIterator.getKey() == int0) {
 return true;
 }
 }

 return false;
 }

 V get(int int0) {
 IntKeyMapIterator intKeyMapIterator = this->entries();

 while (intKeyMapIterator.hasNext()) {
 intKeyMapIterator.next();
 if (intKeyMapIterator.getKey() == int0) {
 return (V)intKeyMapIterator.getValue();
 }
 }

 return nullptr;
 }

 bool containsValue(void* object) {
 IntKeyMapIterator intKeyMapIterator = this->entries();
 if (object.empty()) {
 while (intKeyMapIterator.hasNext()) {
 intKeyMapIterator.next();
 if (object.empty()) {
 return true;
 }
 }
 } else {
 while (intKeyMapIterator.hasNext()) {
 intKeyMapIterator.next();
 if (object == intKeyMapIterator.getValue())) {
 return true;
 }
 }
 }

 return false;
 }

 bool equals(void* object0) {
 if (!(object0 instanceof IntKeyMap intKeyMap) {
 return false;
 } else if (this->size() != intKeyMap.size()) {
 return false;
 } else {
 IntKeyMapIterator intKeyMapIterator = this->entries();

 while (intKeyMapIterator.hasNext()) {
 intKeyMapIterator.next();
 int int0 = intKeyMapIterator.getKey();
 void* object1 = intKeyMapIterator.getValue();
 if (object1.empty()) {
 if (intKeyMap.get(int0) != nullptr) {
 return false;
 }

 if (!intKeyMap.containsKey(int0) {
 return false;
 }
 } else if (!object1 == intKeyMap.get(int0)) {
 return false;
 }
 }

 return true;
 }
 }

 int hashCode() {
 int int0 = 0;

 for (IntKeyMapIterator intKeyMapIterator = this->entries();
 intKeyMapIterator.hasNext();
 int0 += DefaultIntHashFunction.INSTANCE.hash(intKeyMapIterator.getKey()) ^ intKeyMapIterator.getValue().hashCode()
 ) {
 intKeyMapIterator.next();
 }

 return int0;
 }

 bool isEmpty() {
 return this->size() == 0;
 }

 int size() {
 int int0 = 0;

 for (IntKeyMapIterator intKeyMapIterator = this->entries(); intKeyMapIterator.hasNext(); int0++) {
 intKeyMapIterator.next();
 }

 return int0;
 }

 std::string toString() {
 StringBuilder stringBuilder = new StringBuilder();
 stringBuilder.append('[');
 IntKeyMapIterator intKeyMapIterator = this->entries();

 while (intKeyMapIterator.hasNext()) {
 if (stringBuilder.length() > 1) {
 stringBuilder.append(',');
 }

 intKeyMapIterator.next();
 stringBuilder.append(String.valueOf(intKeyMapIterator.getKey()));
 stringBuilder.append("->");
 stringBuilder.append(String.valueOf(intKeyMapIterator.getValue()));
 }

 stringBuilder.append(']');
 return stringBuilder.toString();
 }

 void trimToSize() {
 }
}
} // namespace map
} // namespace util
} // namespace zombie
