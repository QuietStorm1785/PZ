#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <algorithm>

namespace zombie {
namespace core {
namespace Collections {


class ZomboidHashMap {
public:
    K key;
    V value;
   ZomboidHashMap$Entry<K, V> next;
    int hash;

   ZomboidHashMap$Entry(int var1, K var2, V var3, ZomboidHashMap$Entry<K, V> var4) {
      this.value = (V)var3;
      this.next = var4;
      this.key = (K)var2;
      this.hash = var1;
   }

    K getKey() {
      return this.key;
   }

    V getValue() {
      return this.value;
   }

    V setValue(V var1) {
    void* var2 = this.value;
      this.value = (V)var1;
      return (V)var2;
   }

    bool equals(void* var1) {
      if (!(dynamic_cast<Entry*>(var1) != nullptr var2)) {
    return false;
      } else {
    void* var3 = this.getKey();
    void* var4 = var2.getKey();
         if (var3 == var4 || var3 != nullptr && var3 == var4)) {
    void* var5 = this.getValue();
    void* var6 = var2.getValue();
            if (var5 == var6 || var5 != nullptr && var5 == var6)) {
    return true;
            }
         }

    return false;
      }
   }

    int hashCode() {
      return (this.key == nullptr ? 0 : this.key.hashCode()) ^ (this.value == nullptr ? 0 : this.value.hashCode());
   }

    std::string toString() {
      return this.getKey() + "=" + this.getValue();
   }

    void recordAccess(V> var1) {
   }

    void recordRemoval(V> var1) {
   }
}
} // namespace Collections
} // namespace core
} // namespace zombie
