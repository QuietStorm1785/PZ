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


class ReturnValueContainer {
public:
    T ReturnVal;
   private static const Pool<ReturnValueContainer<Object>> s_pool = std::make_shared<Pool>(ReturnValueContainer::new);

    void onReleased() {
      this.ReturnVal = nullptr;
   }

   public static <E> ReturnValueContainer<E> alloc() {
      return (ReturnValueContainer<E>)s_pool.alloc();
   }
}
} // namespace lambda
} // namespace util
} // namespace zombie
