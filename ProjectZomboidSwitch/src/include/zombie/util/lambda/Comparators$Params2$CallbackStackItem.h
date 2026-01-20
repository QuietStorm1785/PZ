#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/util/Pool.h"
#include "zombie/util/lambda/Comparators/Params2/ICallback.h"
#include "zombie/util/lambda/Comparators/Params2/StackItem.h"
#include <algorithm>

namespace zombie {
namespace util {
namespace lambda {


class Comparators {
public:
   private ICallback<E, T1, T2> comparator;
   private static const Pool<Comparators$Params2$CallbackStackItem<Object, Object, Object>> s_pool = std::make_shared<Pool>(Comparators$Params2$CallbackStackItem::new);

    int compare(E var1, E var2) {
      return this.comparator.compare(var1, var2, this.val1, this.val2);
   }

   public static <E, T1, T2> Comparators$Params2$CallbackStackItem<E, T1, T2> alloc(T1 var0, T2 var1, ICallback<E, T1, T2> var2) {
      Comparators$Params2$CallbackStackItem var3 = (Comparators$Params2$CallbackStackItem)s_pool.alloc();
      var3.val1 = var0;
      var3.val2 = var1;
      var3.comparator = var2;
    return var3;
   }

    void onReleased() {
      this.val1 = nullptr;
      this.val2 = nullptr;
      this.comparator = nullptr;
   }
}
} // namespace lambda
} // namespace util
} // namespace zombie
