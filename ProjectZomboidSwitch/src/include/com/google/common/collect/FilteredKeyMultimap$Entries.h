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


class FilteredKeyMultimap {
public:
   FilteredKeyMultimap$Entries(FilteredKeyMultimap var1) {
      this.this$0 = var1;
   }

   protected Collection<Entry<K, V>> delegate() {
      return Collections2.filter(this.this$0.unfiltered.entries(), this.this$0.entryPredicate());
   }

    bool remove(@Nullable Object) {
      if (dynamic_cast<Entry*>(o) != nullptr) {
         Entry<?, ?> entry = (Entry<?, ?>)o;
         if (this.this$0.unfiltered.containsKey(entry.getKey()) && this.this$0.keyPredicate.apply(entry.getKey())) {
            return this.this$0.unfiltered.remove(entry.getKey(), entry.getValue());
         }
      }

    return false;
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
