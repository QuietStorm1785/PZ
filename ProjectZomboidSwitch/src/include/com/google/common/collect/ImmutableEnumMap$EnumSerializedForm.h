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

namespace com {
namespace google {
namespace common {
namespace collect {


class ImmutableEnumMap {
public:
   const EnumMap<K, V> delegate;
    static const long serialVersionUID = 0L;

   ImmutableEnumMap$EnumSerializedForm(EnumMap<K, V> delegate) {
      this.delegate = delegate;
   }

    void* readResolve() {
      return std::make_shared<ImmutableEnumMap>(this.delegate, nullptr);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
