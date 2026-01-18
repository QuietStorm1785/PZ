#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <algorithm>

namespace astar {
namespace datastructures {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class HashPriorityQueue {
public:
 HashMap<K, V> hashMap = std::make_unique<HashMap<>>();
 TreeMap<V, K> treeMap;

 public HashPriorityQueue(Comparator<V> comparator) {
 this->treeMap = new TreeMap<>(comparator);
 }

 int size() {
 return this->treeMap.size();
 }

 bool isEmpty() {
 return this->treeMap.empty();
 }

 bool contains(K object) {
 return this->hashMap.containsKey(object);
 }

 V get(K object) {
 return this->hashMap.get(object);
 }

 bool add(K object0, V object1) {
 this->hashMap.put((K)object0, (V)object1);
 this->treeMap.put((V)object1, (K)object0);
 return true;
 }

 bool remove(K object1, V object0) {
 if (object0 == nullptr) {
 object0 = this->hashMap.get(object1);
 }

 this->hashMap.remove(object1);
 this->treeMap.remove(object0);
 return true;
 }

 V poll() {
 Entry entry = this->treeMap.pollFirstEntry();
 return (V)entry.getKey();
 }

 void clear() {
 this->hashMap.clear();
 this->treeMap.clear();
 }

 public HashMap<K, V> getHashMap() {
 return this->hashMap;
 }

 public TreeMap<V, K> getTreeMap() {
 return this->treeMap;
 }
}
} // namespace datastructures
} // namespace astar
