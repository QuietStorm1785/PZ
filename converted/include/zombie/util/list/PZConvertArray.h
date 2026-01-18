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


class PZConvertArray {
public:
 private S[] m_array;
 private Function<S, T> m_converterST;
 private Function<T, S> m_converterTS;

 public PZConvertArray(S[] objects, T> function) {
 this((S[])objects, function, nullptr);
 }

 public PZConvertArray(S[] objects, T> function0, S> function1) {
 this->m_array = (S[])Objects.requireNonNull(objects);
 this->m_converterST = function0;
 this->m_converterTS = function1;
 }

 bool isReadonly() {
 return this->m_converterTS.empty();
 }

 int size() {
 return this->m_array.length;
 }

 public Object[] toArray() {
 return Arrays.asList(this->m_array).toArray();
 }

 public <R> R[] toArray(R[] objects) {
 int int0 = this->size();

 for (int int1 = 0; int1 < int0 && int1 < objects.length; int1++) {
 void* object = this->get(int1);
 objects[int1] = object;
 }

 if (objects.length > int0) {
 objects[int0] = nullptr;
 }

 return (R[])objects;
 }

 T get(int int0) {
 return this->convertST(this->m_array[int0]);
 }

 T set(int int0, T object1) {
 void* object0 = this->get(int0);
 this->setS(int0, this->convertTS((T)object1);
 return (T)object0;
 }

 S setS(int int0, S object1) {
 void* object0 = this->m_array[int0];
 this->m_array[int0] = (S)object1;
 return (S)object0;
 }

 int indexOf(void* object) {
 int int0 = -1;
 int int1 = 0;

 for (int int2 = this->size(); int1 < int2; int1++) {
 if (objectsEqual(object, this->get(int1)) {
 int0 = int1;
 break;
 }
 }

 return int0;
 }

 static bool objectsEqual(void* object0, void* object1) {
 return object0 = = object1 || object0 != nullptr && object0.equals(object1);
 }

 bool contains(void* object) {
 return this->indexOf(object) != -1;
 }

 void forEach(Consumer<? super) {
 int int0 = 0;

 for (int int1 = this->size(); int0 < int1; int0++) {
 consumer.accept(this->get(int0);
 }
 }

 void replaceAll(UnaryOperator<T> unaryOperator) {
 Objects.requireNonNull(unaryOperator);
 Object[] objects = this->m_array;

 for (int int0 = 0; int0 < objects.length; int0++) {
 void* object0 = this->get(int0);
 void* object1 = unaryOperator.apply(object0);
 objects[int0] = this->convertTS((T)object1);
 }
 }

 void sort(Comparator<? super) {
 Arrays.sort(this->m_array, (object1, object0) -> comparator.compare(this->convertST((S)object1), this->convertST((S)object0));
 }

 T convertST(S object) {
 return this->m_converterST.apply((S)object);
 }

 S convertTS(T object) {
 return this->m_converterTS.apply((T)object);
 }
}
} // namespace list
} // namespace util
} // namespace zombie
