#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/util/Pool.h"
#include "zombie/util/lambda/Comparators/Params1/ICallback.h"
#include "zombie/util/lambda/Comparators/Params1/StackItem.h"
#include <algorithm>

namespace zombie {
namespace util {
namespace lambda {


class Comparators {
public:
   private ICallback<E, T1> comparator;
   private static const Pool<Comparators$Params1$CallbackStackItem<Object, Object>> s_pool = std::make_shared<Pool>(Comparators$Params1$CallbackStackItem::new);

    int compare(E var1, E var2) {
      return this.comparator.compare(var1, var2, this.val1);
   }

   public static <E, T1> Comparators$Params1$CallbackStackItem<E, T1> alloc(T1 var0, ICallback<E, T1> var1) {
      Comparators$Params1$CallbackStackItem var2 = (Comparators$Params1$CallbackStackItem)s_pool.alloc();
      var2.val1 = var0;
      var2.comparator = var1;
    return var2;
   }

    void onReleased() {
      this.val1 = nullptr;
      this.comparator = nullptr;
   }
}
} // namespace lambda
} // namespace util
} // namespace zombie
