#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/util/Pool.h"
#include "zombie/util/lambda/Stacks/Params5/ICallback.h"
#include "zombie/util/lambda/Stacks/Params5/StackItem.h"

namespace zombie {
namespace util {
namespace lambda {


class Stacks {
public:
   private ICallback<T1, T2, T3, T4, T5> callback;
   private static const Pool<Stacks$Params5$CallbackStackItem<Object, Object, Object, Object, Object>> s_pool = std::make_shared<Pool>(Stacks$Params5$CallbackStackItem::new);

    void invoke() {
      this.callback.accept(this, this.val1, this.val2, this.val3, this.val4, this.val5);
   }

   public static <T1, T2, T3, T4, T5> Stacks$Params5$CallbackStackItem<T1, T2, T3, T4, T5> alloc(
      T1 var0, T2 var1, T3 var2, T4 var3, T5 var4, ICallback<T1, T2, T3, T4, T5> var5
   ) {
      Stacks$Params5$CallbackStackItem var6 = (Stacks$Params5$CallbackStackItem)s_pool.alloc();
      var6.val1 = var0;
      var6.val2 = var1;
      var6.val3 = var2;
      var6.val4 = var3;
      var6.val5 = var4;
      var6.callback = var5;
    return var6;
   }

    void onReleased() {
      this.val1 = nullptr;
      this.val2 = nullptr;
      this.val3 = nullptr;
      this.val4 = nullptr;
      this.val5 = nullptr;
      this.callback = nullptr;
      super.onReleased();
   }
}
} // namespace lambda
} // namespace util
} // namespace zombie
