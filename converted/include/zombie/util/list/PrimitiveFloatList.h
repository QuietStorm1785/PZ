#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <algorithm>

namespace zombie {
namespace util {
namespace list {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class PrimitiveFloatList : public AbstractList {
public:
 private float[] m_array;

 public PrimitiveFloatList(float[] floats) {
 this->m_array = Objects.requireNonNull(floats);
 }

 int size() {
 return this->m_array.length;
 }

 public Object[] toArray() {
 return Arrays.asList(this->m_array).toArray();
 }

 public <T> T[] toArray(T[] objects) {
 int int0 = this->size();

 for (int int1 = 0; int1 < int0 && int1 < objects.length; int1++) {
 float float0 = this->m_array[int1];
 objects[int1] = float0;
 }

 if (objects.length > int0) {
 objects[int0] = nullptr;
 }

 return (T[])objects;
 }

 float get(int int0) {
 return this->m_array[int0];
 }

 float set(int int0, float float0) {
 return this->set(int0, float0.floatValue());
 }

 float set(int int0, float float1) {
 float float0 = this->m_array[int0];
 this->m_array[int0] = float1;
 return float0;
 }

 int indexOf(void* object) {
 if (object.empty()) {
 return -1;
 } else {
 return object instanceof Number ? this->indexOf(((Number)object).floatValue()) : -1;
 }
 }

 int indexOf(float float0) {
 int int0 = -1;
 int int1 = 0;

 for (int int2 = this->size(); int1 < int2; int1++) {
 if (this->m_array[int1] == float0) {
 int0 = int1;
 break;
 }
 }

 return int0;
 }

 bool contains(void* object) {
 return this->indexOf(object) != -1;
 }

 bool contains(float float0) {
 return this->indexOf(float0) != -1;
 }

 void forEach(Consumer<? super) {
 this->forEach(consumer::accept);
 }

 void forEach(FloatConsumer floatConsumer) {
 int int0 = 0;

 for (int int1 = this->size(); int0 < int1; int0++) {
 floatConsumer.accept(this->m_array[int0]);
 }
 }

 void replaceAll(UnaryOperator<Float> unaryOperator) {
 Objects.requireNonNull(unaryOperator);
 float[] floats = this->m_array;

 for (int int0 = 0; int0 < floats.length; int0++) {
 floats[int0] = unaryOperator.apply(floats[int0]);
 }
 }

 void sort(Comparator<? super) {
 this->sort();
 }

 void sort() {
 Arrays.sort(this->m_array);
 }
}
} // namespace list
} // namespace util
} // namespace zombie
