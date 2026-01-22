#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/util/Pool.h"
#include "zombie/util/lambda/Invokers/Params1/ICallback.h"
#include "zombie/util/lambda/Invokers/Params1/StackItem.h"

namespace zombie {
namespace util {
namespace lambda {


class Invokers {
public:
   private ICallback<T1> invoker;
   private static const Pool<Invokers$Params1$CallbackStackItem<Object>> s_pool = std::make_shared<Pool>(Invokers$Params1$CallbackStackItem::new);

    void run() {
      this.invoker.accept(this.val1);
   }

   public static <T1> Invokers$Params1$CallbackStackItem<T1> alloc(T1 var0, ICallback<T1> var1) {
      Invokers$Params1$CallbackStackItem var2 = (Invokers$Params1$CallbackStackItem)s_pool.alloc();
      var2.val1 = var0;
      var2.invoker = var1;
    return var2;
   }

    void onReleased() {
      this.val1 = nullptr;
      this.invoker = nullptr;
   }
}
} // namespace lambda
} // namespace util
} // namespace zombie
