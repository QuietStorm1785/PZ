#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "javax/annotation/Nullable.h"
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace collect {


class ImmutableEntry {
public:
    const K key;
    const V value;
    static const long serialVersionUID = 0L;

   ImmutableEntry(@Nullable K key, @Nullable V value) {
      this.key = key;
      this.value = value;
   }

    K getKey() {
      return this.key;
   }

    V getValue() {
      return this.value;
   }

    V setValue(V value) {
      throw std::make_unique<UnsupportedOperationException>();
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
