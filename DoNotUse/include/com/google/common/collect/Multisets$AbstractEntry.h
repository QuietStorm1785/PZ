#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Objects.h"
#include "com/google/common/collect/Multiset/Entry.h"
#include "javax/annotation/Nullable.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class Multisets {
public:
    bool equals(@Nullable Object) {
      if (!(dynamic_cast<Entry*>(object) != nullptr)) {
    return false;
      } else {
         Entry<?> that = (Entry<?>)object;
         return this.getCount() == that.getCount() && Objects.equal(this.getElement(), that.getElement());
      }
   }

    int hashCode() {
    E e = (E)this.getElement();
      return (e == nullptr ? 0 : e.hashCode()) ^ this.getCount();
   }

    std::string toString() {
    std::string text = std::string.valueOf(this.getElement());
    int n = this.getCount();
    return n = = 1 ? text : text + " x " + n;
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
