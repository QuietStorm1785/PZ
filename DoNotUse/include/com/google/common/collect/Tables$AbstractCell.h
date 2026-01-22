#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Objects.h"
#include "com/google/common/collect/Table/Cell.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class Tables {
public:
    bool equals(void* obj) {
      if (obj == this) {
    return true;
      } else if (!(dynamic_cast<Cell*>(obj) != nullptr)) {
    return false;
      } else {
         Cell<?, ?, ?> other = (Cell<?, ?, ?>)obj;
         return Objects.equal(this.getRowKey(), other.getRowKey())
            && Objects.equal(this.getColumnKey(), other.getColumnKey())
            && Objects.equal(this.getValue(), other.getValue());
      }
   }

    int hashCode() {
      return Objects.hashCode(new Object[]{this.getRowKey(), this.getColumnKey(), this.getValue()});
   }

    std::string toString() {
      return "(" + this.getRowKey() + "," + this.getColumnKey() + ")=" + this.getValue();
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
