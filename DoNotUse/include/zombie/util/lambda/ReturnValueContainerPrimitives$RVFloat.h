#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/util/Pool.h"
#include "zombie/util/PooledObject.h"

namespace zombie {
namespace util {
namespace lambda {


class ReturnValueContainerPrimitives {
public:
    float ReturnVal;
   private static const Pool<ReturnValueContainerPrimitives$RVFloat> s_pool = std::make_shared<Pool>(ReturnValueContainerPrimitives$RVFloat::new);

    void onReleased() {
      this.ReturnVal = 0.0F;
   }

   public static ReturnValueContainerPrimitives$RVFloat alloc() {
      return (ReturnValueContainerPrimitives$RVFloat)s_pool.alloc();
   }
}
} // namespace lambda
} // namespace util
} // namespace zombie
