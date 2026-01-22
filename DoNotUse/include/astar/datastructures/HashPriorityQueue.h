#pragma once
#include <map>
#include <queue>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <algorithm>

namespace astar {
namespace datastructures {


class HashPriorityQueue {
public:
   std::unordered_map<K, V> hashMap = std::make_unique<std::unordered_map<>>();
   std::map<V, K> treeMap;

    public HashPriorityQueue(Comparator<V> var1) {
      this.treeMap = new std::map<>(var1);
   }

    int size() {
      return this.treeMap.size();
   }

    bool isEmpty() {
      return this.treeMap.empty();
   }

    bool contains(K var1) {
      return this.hashMap.containsKey(var1);
   }

    V get(K var1) {
      return this.hashMap.get(var1);
   }

    bool add(K var1, V var2) {
      this.hashMap.put((K)var1, (V)var2);
      this.treeMap.put((V)var2, (K)var1);
    return true;
   }

    bool remove(K var1, V var2) {
      if (var2 == nullptr) {
         var2 = this.hashMap.get(var1);
      }

      this.hashMap.remove(var1);
      this.treeMap.remove(var2);
    return true;
   }

    V poll() {
    Entry var1 = this.treeMap.pollFirstEntry();
      return (V)var1.getKey();
   }

    void clear() {
      this.hashMap.clear();
      this.treeMap.clear();
   }

   public std::unordered_map<K, V> getHashMap() {
      return this.hashMap;
   }

   public std::map<V, K> getTreeMap() {
      return this.treeMap;
   }
}
} // namespace datastructures
} // namespace astar
