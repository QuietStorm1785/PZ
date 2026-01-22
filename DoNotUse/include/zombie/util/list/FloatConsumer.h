#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <algorithm>

namespace zombie {
namespace util {
namespace list {


class FloatConsumer {
public:
    virtual ~FloatConsumer() = default;
    void accept(float var1);

   default FloatConsumer andThen(FloatConsumer var1) {
      Objects.requireNonNull(var1);
      return var2 -> {
         this.accept(var2);
         var1.accept(var2);
      };
   }
}
} // namespace list
} // namespace util
} // namespace zombie
