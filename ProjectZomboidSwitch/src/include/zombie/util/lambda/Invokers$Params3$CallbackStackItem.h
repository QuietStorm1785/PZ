#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/util/Pool.h"
#include "zombie/util/lambda/Invokers/Params3/ICallback.h"
#include "zombie/util/lambda/Invokers/Params3/StackItem.h"

namespace zombie {
namespace util {
namespace lambda {


class Invokers {
public:
   private ICallback<T1, T2, T3> invoker;
   private static const Pool<Invokers$Params3$CallbackStackItem<Object, Object, Object>> s_pool = std::make_shared<Pool>(Invokers$Params3$CallbackStackItem::new);

    void run() {
      this.invoker.accept(this.val1, this.val2, this.val3);
   }

   public static <T1, T2, T3> Invokers$Params3$CallbackStackItem<T1, T2, T3> alloc(T1 var0, T2 var1, T3 var2, ICallback<T1, T2, T3> var3) {
      Invokers$Params3$CallbackStackItem var4 = (Invokers$Params3$CallbackStackItem)s_pool.alloc();
      var4.val1 = var0;
      var4.val2 = var1;
      var4.val3 = var2;
      var4.invoker = var3;
    return var4;
   }

    void onReleased() {
      this.val1 = nullptr;
      this.val2 = nullptr;
      this.val3 = nullptr;
      this.invoker = nullptr;
   }
}
} // namespace lambda
} // namespace util
} // namespace zombie
