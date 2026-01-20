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


class HashBiMap {
public:
   private const HashBiMap<K, V> bimap;

   HashBiMap$InverseSerializedForm(HashBiMap<K, V> bimap) {
      this.bimap = bimap;
   }

    void* readResolve() {
      return this.bimap.inverse();
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
