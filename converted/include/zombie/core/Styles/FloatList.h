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
 * Quickly hacked together expandable list of floats
 */
class FloatList {
public:
 static const long serialVersionUID = 1L;
 private float[] value;
 int count = 0;
 const bool fastExpand;

 /**
 * FloatList constructor comment.
 */
 public FloatList() {
 this(0);
 }

 /**
 * FloatList constructor comment.
 */
 public FloatList(int size) {
 this(true, size);
 }

 /**
 * FloatList constructor comment.
 */
 public FloatList(bool _fastExpand, int size) {
 this->fastExpand = _fastExpand;
 this->value = new float[size];
 }

 /**
 * add method comment.
 */
 float add(float f) {
 if (this->count == this->value.length) {
 float[] floats = this->value;
 if (this->fastExpand) {
 this->value = new float[(floats.length << 1) + 1];
 } else {
 this->value = new float[floats.length + 1];
 }

 System.arraycopy(floats, 0, this->value, 0, floats.length);
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
 float remove(int idx) {
 if (idx < this->count && idx >= 0) {
 float float0 = this->value[idx];
 if (idx < this->count - 1) {
 System.arraycopy(this->value, idx + 1, this->value, idx, this->count - idx - 1);
 }

 this->count--;
 return float0;
 } else {
 throw IndexOutOfBoundsException("Referenced " + idx + ", size=" + this->count);
 }
 }

 void addAll(float[] floats) {
 this->ensureCapacity(this->count + floats.length);
 System.arraycopy(floats, 0, this->value, this->count, floats.length);
 this->count += floats.length;
 }

 /**
 * add method comment.
 */
 void addAll(FloatList f) {
 this->ensureCapacity(this->count + f.count);
 System.arraycopy(f.value, 0, this->value, this->count, f.count);
 this->count = this->count + f.count;
 }

 public float[] array() {
 return this->value;
 }

 /**
 * Insert the method's description here. Creation date: (11/03/2001 17:19:01)
 */
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
 float[] floats = this->value;
 this->value = new float[size];
 System.arraycopy(floats, 0, this->value, 0, floats.length);
 }
 }

 /**
 * get method comment.
 */
 float get(int index) {
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

 void toArray(Object[] objects) {
 System.arraycopy(this->value, 0, objects, 0, this->count);
 }

 /**
 * Pack list to its minimum size.
 */
 void trimToSize() {
 if (this->count != this->value.length) {
 float[] floats = this->value;
 this->value = new float[this->count];
 System.arraycopy(floats, 0, this->value, 0, this->count);
 }
 }
}
} // namespace Styles
} // namespace core
} // namespace zombie
