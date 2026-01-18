#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/Rand.h"
#include <algorithm>
#include <iterator>

namespace zombie {
namespace network {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class IsoObjectID {
public:
 static const short incorrect = -1;
 private ConcurrentHashMap<Short, T> IDToObjectMap = std::make_unique<ConcurrentHashMap<>>();
 const std::string objectType;
 short nextID = (short)Rand.Next(32766);

 public IsoObjectID(Class<T> clazz) {
 this->objectType = clazz.getSimpleName();
 }

 void put(short short0, T object) {
 if (short0 != -1) {
 this->IDToObjectMap.put(short0, (T)object);
 }
 }

 void remove(short short0) {
 this->IDToObjectMap.remove(short0);
 }

 void remove(T object) {
 this->IDToObjectMap.values().remove(object);
 }

 T get(short short0) {
 return this->IDToObjectMap.get(short0);
 }

 int size() {
 return this->IDToObjectMap.size();
 }

 void clear() {
 this->IDToObjectMap.clear();
 }

 short allocateID() {
 this->nextID++;
 if (this->nextID == -1) {
 this->nextID++;
 }

 return this->nextID;
 }

 public Iterator<T> iterator() {
 return this->IDToObjectMap.values().iterator();
 }

 void getObjects(Collection<T> collection) {
 collection.addAll(this->IDToObjectMap.values());
 }
}
} // namespace network
} // namespace zombie
