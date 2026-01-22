#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/decorator/TDoubleFloatMapDecorator/1/1.h"
#include <algorithm>

namespace gnu {
namespace trove {
namespace decorator {


class TDoubleFloatMapDecorator {
public:
    float val;

   TDoubleFloatMapDecorator$1$1$1(1 var1, float var2, double var3) {
      this.this$2 = var1;
      this.val$v = var2;
      this.val$key = var3;
      this.val = this.val$v;
   }

    bool equals(void* o) {
      return dynamic_cast<Entry*>(o) != nullptr && ((Entry)o).getKey() == this.val$key) && ((Entry)o).getValue() == this.val);
   }

    double getKey() {
      return this.val$key;
   }

    float getValue() {
      return this.val;
   }

    int hashCode() {
      return this.val$key.hashCode() + this.val.hashCode();
   }

    float setValue(float value) {
      this.val = value;
      return this.this$2.this$1.this$0.put(this.val$key, value);
   }
}
} // namespace decorator
} // namespace trove
} // namespace gnu
