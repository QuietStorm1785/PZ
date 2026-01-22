#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/base/Objects.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class AbstractMapEntry {
public:
   public abstract K getKey();

   public abstract V getValue();

    V setValue(V value) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool equals(@Nullable Object) {
      if (!(dynamic_cast<Entry*>(object) != nullptr)) {
    return false;
      } else {
         Entry<?, ?> that = (Entry<?, ?>)object;
         return Objects.equal(this.getKey(), that.getKey()) && Objects.equal(this.getValue(), that.getValue());
      }
   }

    int hashCode() {
    K k = this.getKey();
    V v = this.getValue();
      return (k == nullptr ? 0 : k.hashCode()) ^ (v == nullptr ? 0 : v.hashCode());
   }

    std::string toString() {
      return this.getKey() + "=" + this.getValue();
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
