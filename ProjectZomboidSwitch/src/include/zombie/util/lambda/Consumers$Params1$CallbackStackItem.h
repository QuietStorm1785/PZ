#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/util/Pool.h"
#include "zombie/util/lambda/Consumers/Params1/ICallback.h"
#include "zombie/util/lambda/Consumers/Params1/StackItem.h"
#include <algorithm>

namespace zombie {
namespace util {
namespace lambda {


class Consumers {
public:
   private ICallback<E, T1> consumer;
   private static const Pool<Consumers$Params1$CallbackStackItem<Object, Object>> s_pool = std::make_shared<Pool>(Consumers$Params1$CallbackStackItem::new);

    void accept(E var1) {
      this.consumer.accept(var1, this.val1);
   }

   public static <E, T1> Consumers$Params1$CallbackStackItem<E, T1> alloc(T1 var0, ICallback<E, T1> var1) {
      Consumers$Params1$CallbackStackItem var2 = (Consumers$Params1$CallbackStackItem)s_pool.alloc();
      var2.val1 = var0;
      var2.consumer = var1;
    return var2;
   }

    void onReleased() {
      this.val1 = nullptr;
      this.consumer = nullptr;
   }
}
} // namespace lambda
} // namespace util
} // namespace zombie
