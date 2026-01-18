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


/**
 * Quickly hacked together expandable list of shorts
 */
class ShortList {
public:
 static const long serialVersionUID = 1L;
 private short[] value;
 short count = 0;
 const bool fastExpand;

 /**
 * FloatList constructor comment.
 */
 public ShortList() {
 this(0);
 }

 /**
 * FloatList constructor comment.
 */
 public ShortList(int size) {
 this(true, size);
 }

 /**
 * FloatList constructor comment.
 */
 public ShortList(bool _fastExpand, int size) {
 this->fastExpand = _fastExpand;
 this->value = new short[size];
 }

 /**
 * add method comment.
 */
 short add(short f) {
 if (this->count == this->value.length) {
 short[] shorts = this->value;
 if (this->fastExpand) {
 this->value = new short[(shorts.length << 1) + 1];
 } else {
 this->value = new short[shorts.length + 1];
 }

 System.arraycopy(shorts, 0, this->value, 0, shorts.length);
 }

 this->value[this->count] = f;
 return this->count++;
 }

 /**
 * Remove an element and return it.
 * 
 * @param idx The index of the element to remove
 * @return the removed value
 */
 short remove(int idx) {
 if (idx < this->count && idx >= 0) {
 short short0 = this->value[idx];
 if (idx < this->count - 1) {
 System.arraycopy(this->value, idx + 1, this->value, idx, this->count - idx - 1);
 }

 this->count--;
 return short0;
 } else {
 throw IndexOutOfBoundsException("Referenced " + idx + ", size=" + this->count);
 }
 }

 void addAll(short[] shorts) {
 this->ensureCapacity(this->count + shorts.length);
 System.arraycopy(shorts, 0, this->value, this->count, shorts.length);
 this->count = (short)(this->count + shorts.length);
 }

 /**
 * add method comment.
 */
 void addAll(ShortList f) {
 this->ensureCapacity(this->count + f.count);
 System.arraycopy(f.value, 0, this->value, this->count, f.count);
 this->count = (short)(this->count + f.count);
 }

 public short[] array() {
 return this->value;
 }

 int capacity() {
 return this->value.length;
 }

 /**
 * clear method comment.
 */
 void clear() {
 this->count = 0;
 }

 /**
 * Ensure the list is at least 'size' elements big.
 */
 void ensureCapacity(int size) {
 if (this->value.length < size) {
 short[] shorts = this->value;
 this->value = new short[size];
 System.arraycopy(shorts, 0, this->value, 0, shorts.length);
 }
 }

 /**
 * get method comment.
 */
 short get(int index) {
 return this->value[index];
 }

 /**
 * isEmpty method comment.
 */
 bool isEmpty() {
 return this->count == 0;
 }

 /**
 * size method comment.
 */
 int size() {
 return this->count;
 }

 public short[] toArray(short[] shorts) {
 if (shorts == nullptr) {
 shorts = new short[this->count];
 }

 System.arraycopy(this->value, 0, shorts, 0, this->count);
 return shorts;
 }

 /**
 * Pack list to its minimum size.
 */
 void trimToSize() {
 if (this->count != this->value.length) {
 short[] shorts = this->value;
 this->value = new short[this->count];
 System.arraycopy(shorts, 0, this->value, 0, this->count);
 }
 }
}
} // namespace Styles
} // namespace core
} // namespace zombie
