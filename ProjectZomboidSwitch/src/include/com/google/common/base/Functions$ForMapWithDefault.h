#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "javax/annotation/Nullable.h"
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace base {


class Functions {
public:
   const Map<K, ? : public V> map;
    const V defaultValue;
    static const long serialVersionUID = 0L;

   Functions$ForMapWithDefault(Map<K, ? : public V> map, @Nullable V defaultValue) {
      this.map = (Map<K, ? : public V>)Preconditions.checkNotNull(map);
      this.defaultValue = defaultValue;
   }

    V apply(@Nullable K) {
    V result = (V)this.map.get(key);
    return result = = nullptr && !this.map.containsKey(key) ? this.defaultValue : result;
   }

    bool equals(@Nullable Object) {
      if (!(dynamic_cast<Functions*>(o) != nullptr$ForMapWithDefault)) {
    return false;
      } else {
         Functions$ForMapWithDefault<?, ?> that = (Functions$ForMapWithDefault<?, ?>)o;
         return this.map == that.map) && Objects.equal(this.defaultValue, that.defaultValue);
      }
   }

    int hashCode() {
      return Objects.hashCode(new Object[]{this.map, this.defaultValue});
   }

    std::string toString() {
      return "Functions.forMap(" + this.map + ", defaultValue=" + this.defaultValue + ")";
   }
}
} // namespace base
} // namespace common
} // namespace google
} // namespace com
