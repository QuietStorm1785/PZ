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
    bool ReturnVal;
   private static const Pool<ReturnValueContainerPrimitives$RVBoolean> s_pool = std::make_shared<Pool>(ReturnValueContainerPrimitives$RVBoolean::new);

    void onReleased() {
      this.ReturnVal = false;
   }

   public static ReturnValueContainerPrimitives$RVBoolean alloc() {
      return (ReturnValueContainerPrimitives$RVBoolean)s_pool.alloc();
   }
}
} // namespace lambda
} // namespace util
} // namespace zombie
