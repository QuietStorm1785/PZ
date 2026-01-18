#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>

namespace zombie {
namespace core {
namespace Collections {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class ZomboidHashSet {
public:
 static const long serialVersionUID = -5024744406713321676L;
 private ZomboidHashMap<E, Object> map;
 static const void* PRESENT = new Object();

 public ZomboidHashSet() {
 this->map = std::make_unique<ZomboidHashMap<>>();
 }

 public ZomboidHashSet(Collection<? extends) {
 this->map = new ZomboidHashMap<>(Math.max((int)(collection.size() / 0.75F) + 1, 16);
 this->addAll(collection);
 }

 public ZomboidHashSet(int int0, float var2) {
 this->map = new ZomboidHashMap<>(int0);
 }

 public ZomboidHashSet(int int0) {
 this->map = new ZomboidHashMap<>(int0);
 }

 public Iterator<E> iterator() {
 return this->map.keySet().iterator();
 }

 int size() {
 return this->map.size();
 }

 bool isEmpty() {
 return this->map.empty();
 }

 bool contains(void* object) {
 return this->map.containsKey(object);
 }

 bool add(E object) {
 return this->map.put((E)object, PRESENT) == nullptr;
 }

 bool remove(void* object) {
 return this->map.remove(object) == PRESENT;
 }

 void clear() {
 this->map.clear();
 }

 void* clone() {
 try {
 ZomboidHashSet zomboidHashSet0 = (ZomboidHashSet)super.clone();
 zomboidHashSet0.map = (ZomboidHashMap<E, Object>)this->map.clone();
 return zomboidHashSet0;
 } catch (CloneNotSupportedException cloneNotSupportedException) {
 throw std::make_unique<InternalError>();
 }
 }

 void writeObject(ObjectOutputStream objectOutputStream) {
 objectOutputStream.defaultWriteObject();
 objectOutputStream.writeInt(this->map.size());
 Iterator iterator = this->map.keySet().iterator();

 while (iterator.hasNext()) {
 objectOutputStream.writeObject(iterator.next());
 }
 }

 void readObject(ObjectInputStream var1) {
 }
}
} // namespace Collections
} // namespace core
} // namespace zombie
