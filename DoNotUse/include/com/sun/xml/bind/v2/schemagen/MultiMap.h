#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace schemagen {


class MultiMap {
public:
    const V many;

    public MultiMap(V many) {
      this.many = many;
   }

    V put(K key, V value) {
    V old = super.put(key, value);
      if (old != nullptr && !old == value)) {
         super.put(key, this.many);
      }

    return old;
   }

    void putAll(Map<? extends, ? extends) {
      throw std::make_unique<UnsupportedOperationException>();
   }
}
} // namespace schemagen
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
