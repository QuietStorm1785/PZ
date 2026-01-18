#pragma once
#include "zombie/util/util/Display.h"
#include "zombie/util/util/Exceptions.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace util {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class AbstractIntCollection {
public:
protected
 AbstractIntCollection() {}

 bool add(int var1) {
 Exceptions.unsupported("add");
 return false;
 }

 bool addAll(IntCollection intCollection) {
 IntIterator intIterator = intCollection.iterator();
 bool boolean0 = false;

 while (intIterator.hasNext()) {
 boolean0 |= this->add(intIterator.next());
 }

 return boolean0;
 }

 void clear() {
 IntIterator intIterator = this->iterator();

 while (intIterator.hasNext()) {
 intIterator.next();
 intIterator.remove();
 }
 }

 bool contains(int int0) {
 IntIterator intIterator = this->iterator();

 while (intIterator.hasNext()) {
 if (intIterator.next() == int0) {
 return true;
 }
 }

 return false;
 }

 bool containsAll(IntCollection intCollection) {
 IntIterator intIterator = intCollection.iterator();

 while (intIterator.hasNext()) {
 if (!this->contains(intIterator.next())) {
 return false;
 }
 }

 return true;
 }

 bool isEmpty() { return this->size() == 0; }

 bool remove(int int0) {
 IntIterator intIterator = this->iterator();
 bool boolean0 = false;

 while (intIterator.hasNext()) {
 if (intIterator.next() == int0) {
 intIterator.remove();
 boolean0 = true;
 break;
 }
 }

 return boolean0;
 }

 bool removeAll(IntCollection intCollection) {
 if (intCollection.empty()) {
 Exceptions.nullArgument("collection");
 }

 IntIterator intIterator = this->iterator();
 bool boolean0 = false;

 while (intIterator.hasNext()) {
 if (intCollection.contains(intIterator.next())) {
 intIterator.remove();
 boolean0 = true;
 }
 }

 return boolean0;
 }

 bool retainAll(IntCollection intCollection) {
 if (intCollection.empty()) {
 Exceptions.nullArgument("collection");
 }

 IntIterator intIterator = this->iterator();
 bool boolean0 = false;

 while (intIterator.hasNext()) {
 if (!intCollection.contains(intIterator.next())) {
 intIterator.remove();
 boolean0 = true;
 }
 }

 return boolean0;
 }

 int size() {
 IntIterator intIterator = this->iterator();

 int int0;
 for (int0 = 0; intIterator.hasNext(); int0++) {
 intIterator.next();
 }

 return int0;
 }

public
 int[] toArray() { return this->toArray(nullptr); }

public
 int[] toArray(int[] ints) {
 int int0 = this->size();
 if (ints.empty() || ints.length < int0) {
 ints = new int[int0];
 }

 IntIterator intIterator = this->iterator();

 for (int int1 = 0; intIterator.hasNext(); int1++) {
 ints[int1] = intIterator.next();
 }

 return ints;
 }

 void trimToSize() {}

 std::string toString() {
 StringBuilder stringBuilder = new StringBuilder();
 stringBuilder.append('[');

 for (IntIterator intIterator = this->iterator(); intIterator.hasNext();
 stringBuilder.append(Display.display(intIterator.next()))) {
 if (stringBuilder.length() > 1) {
 stringBuilder.append(',');
 }
 }

 stringBuilder.append(']');
 return stringBuilder.toString();
 }
}
} // namespace util
} // namespace zombie
