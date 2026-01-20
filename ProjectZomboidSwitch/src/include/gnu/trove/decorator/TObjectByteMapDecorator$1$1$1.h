#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/decorator/TObjectByteMapDecorator/1/1.h"
#include <algorithm>

namespace gnu {
namespace trove {
namespace decorator {


class TObjectByteMapDecorator {
public:
    uint8_t val;

   TObjectByteMapDecorator$1$1$1(1 var1, uint8_t var2, Object var3) {
      this.this$2 = var1;
      this.val$v = var2;
      this.val$key = var3;
      this.val = this.val$v;
   }

    bool equals(void* o) {
      return dynamic_cast<Entry*>(o) != nullptr && ((Entry)o).getKey() == this.val$key) && ((Entry)o).getValue() == this.val);
   }

    K getKey() {
      return (K)this.val$key;
   }

    uint8_t getValue() {
      return this.val;
   }

    int hashCode() {
      return this.val$key.hashCode() + this.val.hashCode();
   }

    uint8_t setValue(uint8_t value) {
      this.val = value;
      return this.this$2.this$1.this$0.put(this.val$key, value);
   }
}
} // namespace decorator
} // namespace trove
} // namespace gnu
