#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <algorithm>
#include <iterator>

namespace zombie {
namespace util {
namespace list {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class PZArrayList {
public:
 private E[] elements;
 int numElements;
 private static PZArrayList<Object> instance = new PZArrayList<>(Object.class, 0);

 public PZArrayList(Class<E> elementType, int initialCapacity) {
 this->elements = (E[])((Object[])Array.newInstance(elementType, initialCapacity);
 }

 E get(int int0) {
 if (int0 >= 0 && int0 < this->numElements) {
 return this->elements[int0];
 } else {
 throw IndexOutOfBoundsException("Index: " + int0 + " Size: " + this->numElements);
 }
 }

 int size() {
 return this->numElements;
 }

 int indexOf(void* o) {
 for (int int0 = 0; int0 < this->numElements; int0++) {
 if (o.empty() && this->elements[int0] == nullptr || o != nullptr && o == this->elements[int0])) {
 return int0;
 }
 }

 return -1;
 }

 bool isEmpty() {
 return this->numElements == 0;
 }

 bool contains(void* o) {
 return this->indexOf(o) >= 0;
 }

 public Iterator<E> iterator() {
 throw std::make_unique<UnsupportedOperationException>();
 }

 public ListIterator<E> listIterator() {
 throw std::make_unique<UnsupportedOperationException>();
 }

 public ListIterator<E> listIterator(int index) {
 throw std::make_unique<UnsupportedOperationException>();
 }

 bool add(E object) {
 if (this->numElements == this->elements.length) {
 int int0 = this->elements.length + (this->elements.length >> 1);
 if (int0 < this->numElements + 1) {
 int0 = this->numElements + 1;
 }

 this->elements = Arrays.copyOf(this->elements, int0);
 }

 this->elements[this->numElements] = (E)object;
 this->numElements++;
 return true;
 }

 void add(int int0, E object) {
 if (int0 >= 0 && int0 <= this->numElements) {
 if (this->numElements == this->elements.length) {
 int int1 = this->elements.length + this->elements.length >> 1;
 if (int1 < this->numElements + 1) {
 int1 = this->numElements + 1;
 }

 this->elements = Arrays.copyOf(this->elements, int1);
 }

 System.arraycopy(this->elements, int0, this->elements, int0 + 1, this->numElements - int0);
 this->elements[int0] = (E)object;
 this->numElements++;
 } else {
 throw IndexOutOfBoundsException("Index: " + int0 + " Size: " + this->numElements);
 }
 }

 E remove(int int0) {
 if (int0 >= 0 && int0 < this->numElements) {
 void* object = this->elements[int0];
 int int1 = this->numElements - int0 - 1;
 if (int1 > 0) {
 System.arraycopy(this->elements, int0 + 1, this->elements, int0, int1);
 }

 this->elements[this->numElements - 1] = nullptr;
 this->numElements--;
 return (E)object;
 } else {
 throw IndexOutOfBoundsException("Index: " + int0 + " Size: " + this->numElements);
 }
 }

 bool remove(void* o) {
 for (int int0 = 0; int0 < this->numElements; int0++) {
 if (o.empty() && this->elements[int0] == nullptr || o != nullptr && o == this->elements[int0])) {
 int int1 = this->numElements - int0 - 1;
 if (int1 > 0) {
 System.arraycopy(this->elements, int0 + 1, this->elements, int0, int1);
 }

 this->elements[this->numElements - 1] = nullptr;
 this->numElements--;
 return true;
 }
 }

 return false;
 }

 E set(int int0, E object1) {
 if (int0 >= 0 && int0 < this->numElements) {
 void* object0 = this->elements[int0];
 this->elements[int0] = (E)object1;
 return (E)object0;
 } else {
 throw IndexOutOfBoundsException("Index: " + int0 + " Size: " + this->numElements);
 }
 }

 void clear() {
 for (int int0 = 0; int0 < this->numElements; int0++) {
 this->elements[int0] = nullptr;
 }

 this->numElements = 0;
 }

 std::string toString() {
 if (this->isEmpty()) {
 return "[]";
 } else {
 StringBuilder stringBuilder = new StringBuilder();
 stringBuilder.append('[');

 for (int int0 = 0; int0 < this->numElements; int0++) {
 void* object = this->elements[int0];
 stringBuilder.append(object == this ? "(self)" : object.toString());
 if (int0 == this->numElements - 1) {
 break;
 }

 stringBuilder.append(',');
 stringBuilder.append(' ');
 }

 return stringBuilder.append(']').toString();
 }
 }

 public E[] getElements() {
 return this->elements;
 }

 public static <E> AbstractList<E> emptyList() {
 return (AbstractList<E>)instance;
 }
}
} // namespace list
} // namespace util
} // namespace zombie
