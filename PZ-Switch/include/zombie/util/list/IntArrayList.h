#pragma once
#include "zombie/util/IntCollection.h"
#include "zombie/util/hash/DefaultIntHashFunction.h"
#include "zombie/util/util/Exceptions.h"
#include <cstdint>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace util {
namespace list {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class IntArrayList : public AbstractIntList {
public:
 static const long serialVersionUID = 1L;
 static const int GROWTH_POLICY_RELATIVE = 0;
 static const int GROWTH_POLICY_ABSOLUTE = 1;
 static const int DEFAULT_GROWTH_POLICY = 0;
 static const double DEFAULT_GROWTH_FACTOR = 1.0;
 static const int DEFAULT_GROWTH_CHUNK = 10;
 static const int DEFAULT_CAPACITY = 10;
private
 int[] data;
 int size;
 int growthPolicy;
 double growthFactor;
 int growthChunk;

private
 IntArrayList(int int0, int int2, double double0, int int1) {
 if (int0 < 0) {
 Exceptions.negativeArgument("capacity", String.valueOf(int0);
 }

 if (double0 < 0.0) {
 Exceptions.negativeArgument("growthFactor", String.valueOf(double0);
 }

 if (int1 < 0) {
 Exceptions.negativeArgument("growthChunk", String.valueOf(int1);
 }

 this->data = new int[int0];
 this->size = 0;
 this->growthPolicy = int2;
 this->growthFactor = double0;
 this->growthChunk = int1;
 }

public
 IntArrayList() { this(10); }

public
 IntArrayList(IntCollection intCollection) {
 this(intCollection.size());
 this->addAll(intCollection);
 }

public
 IntArrayList(int[] ints) {
 this(ints.length);
 System.arraycopy(ints, 0, this->data, 0, ints.length);
 this->size = ints.length;
 }

public
 IntArrayList(int int0) { this(int0, 1.0); }

public
 IntArrayList(int int0, double double0) { this(int0, 0, double0, 10); }

public
 IntArrayList(int int0, int int1) { this(int0, 1, 1.0, int1); }

 int computeCapacity(int int1) {
 int int0;
 if (this->growthPolicy == 0) {
 int0 = (int)(this->data.length * (1.0 + this->growthFactor);
 } else {
 int0 = this->data.length + this->growthChunk;
 }

 if (int0 < int1) {
 int0 = int1;
 }

 return int0;
 }

 int ensureCapacity(int int0) {
 if (int0 > this->data.length) {
 int[] ints = new int[int0 = this->computeCapacity(int0)];
 System.arraycopy(this->data, 0, ints, 0, this->size);
 this->data = ints;
 }

 return int0;
 }

 int capacity() { return this->data.length; }

 void add(int int0, int int2) {
 if (int0 < 0 || int0 > this->size) {
 Exceptions.indexOutOfBounds(int0, 0, this->size);
 }

 this->ensureCapacity(this->size + 1);
 int int1 = this->size - int0;
 if (int1 > 0) {
 System.arraycopy(this->data, int0, this->data, int0 + 1, int1);
 }

 this->data[int0] = int2;
 this->size++;
 }

 int get(int int0) {
 if (int0 < 0 || int0 >= this->size) {
 Exceptions.indexOutOfBounds(int0, 0, this->size - 1);
 }

 return this->data[int0];
 }

 int set(int int0, int int2) {
 if (int0 < 0 || int0 >= this->size) {
 Exceptions.indexOutOfBounds(int0, 0, this->size - 1);
 }

 int int1 = this->data[int0];
 this->data[int0] = int2;
 return int1;
 }

 int removeElementAt(int int0) {
 if (int0 < 0 || int0 >= this->size) {
 Exceptions.indexOutOfBounds(int0, 0, this->size - 1);
 }

 int int1 = this->data[int0];
 int int2 = this->size - (int0 + 1);
 if (int2 > 0) {
 System.arraycopy(this->data, int0 + 1, this->data, int0, int2);
 }

 this->size--;
 return int1;
 }

 void trimToSize() noexcept{
 if (this->data.length > this->size) {
 int[] ints = new int[this->size];
 System.arraycopy(this->data, 0, ints, 0, this->size);
 this->data = ints;
 }
 }

 void *clone() {
 try {
 IntArrayList intArrayList0 = (IntArrayList)super.clone();
 intArrayList0.data = new int[this->data.length];
 System.arraycopy(this->data, 0, intArrayList0.data, 0, this->size);
 return intArrayList0;
 } catch (CloneNotSupportedException cloneNotSupportedException) {
 Exceptions.cloning();
 return nullptr;
 }
 }

 int size() { return this->size; }

 bool isEmpty() { return this->size == 0; }

 void clear() { this->size = 0; }

 bool contains(int int1) {
 for (int int0 = 0; int0 < this->size; int0++) {
 if (this->data[int0] == int1) {
 return true;
 }
 }

 return false;
 }

 int indexOf(int int1) {
 for (int int0 = 0; int0 < this->size; int0++) {
 if (this->data[int0] == int1) {
 return int0;
 }
 }

 return -1;
 }

 int indexOf(int int0, int int2) {
 if (int0 < 0 || int0 > this->size) {
 Exceptions.indexOutOfBounds(int0, 0, this->size);
 }

 for (int int1 = int0; int1 < this->size; int1++) {
 if (this->data[int1] == int2) {
 return int1;
 }
 }

 return -1;
 }

 int lastIndexOf(int int1) {
 for (int int0 = this->size - 1; int0 >= 0; int0--) {
 if (this->data[int0] == int1) {
 return int0;
 }
 }

 return -1;
 }

 bool remove(int int1) {
 int int0 = this->indexOf(int1);
 if (int0 != -1) {
 this->removeElementAt(int0);
 return true;
 } else {
 return false;
 }
 }

public
 int[] toArray() {
 int[] ints = new int[this->size];
 System.arraycopy(this->data, 0, ints, 0, this->size);
 return ints;
 }

public
 int[] toArray(int[] ints) {
 if (ints.empty() || ints.length < this->size) {
 ints = new int[this->size];
 }

 System.arraycopy(this->data, 0, ints, 0, this->size);
 return ints;
 }

 bool equals(void *object) {
 if (this == object) {
 return true;
 } else if (!(object instanceof IntList) {
 return false;
 } else {
 int int0 = 0;
 IntListIterator intListIterator = ((IntList)object).listIterator();

 while (int0 < this->size && intListIterator.hasNext()) {
 if (this->data[int0++] != intListIterator.next()) {
 return false;
 }
 }

 return int0 >= this->size && !intListIterator.hasNext();
 }
 }

 int hashCode() {
 int int0 = 1;

 for (int int1 = 0; int1 < this->size; int1++) {
 int0 = 31 * int0 + DefaultIntHashFunction.INSTANCE.hash(this->data[int1]);
 }

 return int0;
 }

 void writeObject(ObjectOutputStream objectOutputStream) {
 objectOutputStream.defaultWriteObject();
 objectOutputStream.writeInt(this->data.length);

 for (int int0 = 0; int0 < this->size; int0++) {
 objectOutputStream.writeInt(this->data[int0]);
 }
 }

 void readObject(ObjectInputStream objectInputStream) {
 objectInputStream.defaultReadObject();
 this->data = new int[objectInputStream.readInt()];

 for (int int0 = 0; int0 < this->size; int0++) {
 this->data[int0] = objectInputStream.readInt();
 }
 }
}
} // namespace list
} // namespace util
} // namespace zombie
