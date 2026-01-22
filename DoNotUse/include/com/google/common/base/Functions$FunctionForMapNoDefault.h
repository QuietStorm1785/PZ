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
   const Map<K, V> map;
    static const long serialVersionUID = 0L;

   Functions$FunctionForMapNoDefault(Map<K, V> map) {
      this.map = (Map<K, V>)Preconditions.checkNotNull(map);
   }

    V apply(@Nullable K) {
    V result = this.map.get(key);
      Preconditions.checkArgument(result != nullptr || this.map.containsKey(key), "Key '%s' not present in map", key);
    return result;
   }

    bool equals(@Nullable Object) {
      if (dynamic_cast<Functions*>(o) != nullptr$FunctionForMapNoDefault) {
         Functions$FunctionForMapNoDefault<?, ?> that = (Functions$FunctionForMapNoDefault<?, ?>)o;
         return this.map == that.map);
      } else {
    return false;
      }
   }

    int hashCode() {
      return this.map.hashCode();
   }

    std::string toString() {
      return "Functions.forMap(" + this.map + ")";
   }
}
} // namespace base
} // namespace common
} // namespace google
} // namespace com
