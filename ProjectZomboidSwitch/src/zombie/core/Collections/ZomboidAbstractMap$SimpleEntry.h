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

namespace zombie {
namespace core {
namespace Collections {


class ZomboidAbstractMap {
public:
    static const long serialVersionUID = -8499721149061103585L;
    const K key;
    V value;

   public ZomboidAbstractMap$SimpleEntry(K var1, V var2) {
      this.key = (K)var1;
      this.value = (V)var2;
   }

   public ZomboidAbstractMap$SimpleEntry(Entry<? : public K, ? : public V> var1) {
      this.key = (K)var1.getKey();
      this.value = (V)var1.getValue();
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
      return !(dynamic_cast<Entry*>(var1) != nullptr var2) ? false : ZomboidAbstractMap.eq(this.key, var2.getKey()) && ZomboidAbstractMap.eq(this.value, var2.getValue());
   }

    int hashCode() {
      return (this.key == nullptr ? 0 : this.key.hashCode()) ^ (this.value == nullptr ? 0 : this.value.hashCode());
   }

    std::string toString() {
      return this.key + "=" + this.value;
   }
}
} // namespace Collections
} // namespace core
} // namespace zombie
