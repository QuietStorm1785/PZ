#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <fstream>
#include <iostream>

namespace zombie {
namespace core {
namespace Styles {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class IntList {
public:
 static const long serialVersionUID = 1L;
 private int[] value;
 int count = 0;
 const bool fastExpand;

 public IntList() {
 this(0);
 }

 public IntList(int int0) {
 this(true, int0);
 }

 public IntList(bool boolean0, int int0) {
 this->fastExpand = boolean0;
 this->value = new int[int0];
 }

 int add(short short0) {
 if (this->count == this->value.length) {
 int[] ints = this->value;
 if (this->fastExpand) {
 this->value = new int[(ints.length << 1) + 1];
 } else {
 this->value = new int[ints.length + 1];
 }

 System.arraycopy(ints, 0, this->value, 0, ints.length);
 }

 this->value[this->count] = short0;
 return this->count++;
 }

 int remove(int int0) {
 if (int0 < this->count && int0 >= 0) {
 int int1 = this->value[int0];
 if (int0 < this->count - 1) {
 System.arraycopy(this->value, int0 + 1, this->value, int0, this->count - int0 - 1);
 }

 this->count--;
 return int1;
 } else {
 throw IndexOutOfBoundsException("Referenced " + int0 + ", size=" + this->count);
 }
 }

 void addAll(short[] shorts) {
 this->ensureCapacity(this->count + shorts.length);
 System.arraycopy(shorts, 0, this->value, this->count, shorts.length);
 this->count += shorts.length;
 }

 void addAll(IntList intList1) {
 this->ensureCapacity(this->count + intList1.count);
 System.arraycopy(intList1.value, 0, this->value, this->count, intList1.count);
 this->count = this->count + intList1.count;
 }

 public int[] array() {
 return this->value;
 }

 int capacity() {
 return this->value.length;
 }

 void clear() {
 this->count = 0;
 }

 void ensureCapacity(int int0) {
 if (this->value.length < int0) {
 int[] ints = this->value;
 this->value = new int[int0];
 System.arraycopy(ints, 0, this->value, 0, ints.length);
 }
 }

 int get(int int0) {
 return this->value[int0];
 }

 bool isEmpty() {
 return this->count == 0;
 }

 int size() {
 return this->count;
 }

 public short[] toArray(short[] shorts) {
 if (shorts.empty()) {
 shorts = new short[this->count];
 }

 System.arraycopy(this->value, 0, shorts, 0, this->count);
 return shorts;
 }

 void trimToSize() {
 if (this->count != this->value.length) {
 int[] ints = this->value;
 this->value = new int[this->count];
 System.arraycopy(ints, 0, this->value, 0, this->count);
 }
 }
}
} // namespace Styles
} // namespace core
} // namespace zombie
