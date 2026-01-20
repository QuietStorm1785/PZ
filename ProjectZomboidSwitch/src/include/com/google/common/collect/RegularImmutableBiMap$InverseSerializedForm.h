#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace collect {


class RegularImmutableBiMap {
public:
   private const ImmutableBiMap<K, V> forward;
    static const long serialVersionUID = 1L;

   RegularImmutableBiMap$InverseSerializedForm(ImmutableBiMap<K, V> forward) {
      this.forward = forward;
   }

    void* readResolve() {
      return this.forward.inverse();
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
