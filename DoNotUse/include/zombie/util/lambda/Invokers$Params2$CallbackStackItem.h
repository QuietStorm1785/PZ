#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/util/Pool.h"
#include "zombie/util/lambda/Invokers/Params2/ICallback.h"
#include "zombie/util/lambda/Invokers/Params2/StackItem.h"

namespace zombie {
namespace util {
namespace lambda {


class Invokers {
public:
   private ICallback<T1, T2> invoker;
   private static const Pool<Invokers$Params2$CallbackStackItem<Object, Object>> s_pool = std::make_shared<Pool>(Invokers$Params2$CallbackStackItem::new);

    void run() {
      this.invoker.accept(this.val1, this.val2);
   }

   public static <T1, T2> Invokers$Params2$CallbackStackItem<T1, T2> alloc(T1 var0, T2 var1, ICallback<T1, T2> var2) {
      Invokers$Params2$CallbackStackItem var3 = (Invokers$Params2$CallbackStackItem)s_pool.alloc();
      var3.val1 = var0;
      var3.val2 = var1;
      var3.invoker = var2;
    return var3;
   }

    void onReleased() {
      this.val1 = nullptr;
      this.val2 = nullptr;
      this.invoker = nullptr;
   }
}
} // namespace lambda
} // namespace util
} // namespace zombie
