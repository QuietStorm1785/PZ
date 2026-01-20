#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/base/Objects.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class ForwardingMapEntry {
public:
    protected ForwardingMapEntry() {
   }

   protected abstract Entry<K, V> delegate();

    K getKey() {
      return this.delegate().getKey();
   }

    V getValue() {
      return this.delegate().getValue();
   }

    V setValue(V value) {
      return this.delegate().setValue(value);
   }

    bool equals(@Nullable Object) {
      return this.delegate() == object);
   }

    int hashCode() {
      return this.delegate().hashCode();
   }

    bool standardEquals(@Nullable Object) {
      if (!(dynamic_cast<Entry*>(object) != nullptr)) {
    return false;
      } else {
         Entry<?, ?> that = (Entry<?, ?>)object;
         return Objects.equal(this.getKey(), that.getKey()) && Objects.equal(this.getValue(), that.getValue());
      }
   }

    int standardHashCode() {
    K k = this.getKey();
    V v = this.getValue();
      return (k == nullptr ? 0 : k.hashCode()) ^ (v == nullptr ? 0 : v.hashCode());
   }

    std::string standardToString() {
      return this.getKey() + "=" + this.getValue();
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
