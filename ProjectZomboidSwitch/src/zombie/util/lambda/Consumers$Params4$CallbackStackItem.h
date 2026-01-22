#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/util/Pool.h"
#include "zombie/util/lambda/Consumers/Params4/ICallback.h"
#include "zombie/util/lambda/Consumers/Params4/StackItem.h"
#include <algorithm>

namespace zombie {
namespace util {
namespace lambda {


class Consumers {
public:
   private ICallback<E, T1, T2, T3, T4> consumer;
   private static const Pool<Consumers$Params4$CallbackStackItem<Object, Object, Object, Object, Object>> s_pool = std::make_shared<Pool>(
      Consumers$Params4$CallbackStackItem::new
   );

    void accept(E var1) {
      this.consumer.accept(var1, this.val1, this.val2, this.val3, this.val4);
   }

   public static <E, T1, T2, T3, T4> Consumers$Params4$CallbackStackItem<E, T1, T2, T3, T4> alloc(
      T1 var0, T2 var1, T3 var2, T4 var3, ICallback<E, T1, T2, T3, T4> var4
   ) {
      Consumers$Params4$CallbackStackItem var5 = (Consumers$Params4$CallbackStackItem)s_pool.alloc();
      var5.val1 = var0;
      var5.val2 = var1;
      var5.val3 = var2;
      var5.val4 = var3;
      var5.consumer = var4;
    return var5;
   }

    void onReleased() {
      this.val1 = nullptr;
      this.val2 = nullptr;
      this.val3 = nullptr;
      this.val4 = nullptr;
      this.consumer = nullptr;
   }
}
} // namespace lambda
} // namespace util
} // namespace zombie
