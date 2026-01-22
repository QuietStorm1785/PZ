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
    int ReturnVal;
   private static const Pool<ReturnValueContainerPrimitives$RVInt> s_pool = std::make_shared<Pool>(ReturnValueContainerPrimitives$RVInt::new);

    void onReleased() {
      this.ReturnVal = 0;
   }

   public static ReturnValueContainerPrimitives$RVInt alloc() {
      return (ReturnValueContainerPrimitives$RVInt)s_pool.alloc();
   }
}
} // namespace lambda
} // namespace util
} // namespace zombie
