#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "javax/annotation/Nullable.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class Multimaps {
public:
   abstract Multimap<K, V> multimap();

    int size() {
      return this.multimap().size();
   }

    bool contains(@Nullable Object) {
      if (dynamic_cast<Entry*>(o) != nullptr) {
         Entry<?, ?> entry = (Entry<?, ?>)o;
         return this.multimap().containsEntry(entry.getKey(), entry.getValue());
      } else {
    return false;
      }
   }

    bool remove(@Nullable Object) {
      if (dynamic_cast<Entry*>(o) != nullptr) {
         Entry<?, ?> entry = (Entry<?, ?>)o;
         return this.multimap().remove(entry.getKey(), entry.getValue());
      } else {
    return false;
      }
   }

    void clear() {
      this.multimap().clear();
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
