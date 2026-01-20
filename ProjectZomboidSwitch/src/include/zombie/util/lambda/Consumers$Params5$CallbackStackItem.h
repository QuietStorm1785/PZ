#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/util/Pool.h"
#include "zombie/util/lambda/Consumers/Params5/ICallback.h"
#include "zombie/util/lambda/Consumers/Params5/StackItem.h"
#include <algorithm>

namespace zombie {
namespace util {
namespace lambda {


class Consumers {
public:
   private ICallback<E, T1, T2, T3, T4, T5> consumer;
   private static const Pool<Consumers$Params5$CallbackStackItem<Object, Object, Object, Object, Object, Object>> s_pool = std::make_shared<Pool>(
      Consumers$Params5$CallbackStackItem::new
   );

    void accept(E var1) {
      this.consumer.accept(var1, this.val1, this.val2, this.val3, this.val4, this.val5);
   }

   public static <E, T1, T2, T3, T4, T5> Consumers$Params5$CallbackStackItem<E, T1, T2, T3, T4, T5> alloc(
      T1 var0, T2 var1, T3 var2, T4 var3, T5 var4, ICallback<E, T1, T2, T3, T4, T5> var5
   ) {
      Consumers$Params5$CallbackStackItem var6 = (Consumers$Params5$CallbackStackItem)s_pool.alloc();
      var6.val1 = var0;
      var6.val2 = var1;
      var6.val3 = var2;
      var6.val4 = var3;
      var6.val5 = var4;
      var6.consumer = var5;
    return var6;
   }

    void onReleased() {
      this.val1 = nullptr;
      this.val2 = nullptr;
      this.val3 = nullptr;
      this.val4 = nullptr;
      this.val5 = nullptr;
      this.consumer = nullptr;
   }
}
} // namespace lambda
} // namespace util
} // namespace zombie
