#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/util/Pool.h"
#include "zombie/util/lambda/Stacks/Params6/ICallback.h"
#include "zombie/util/lambda/Stacks/Params6/StackItem.h"

namespace zombie {
namespace util {
namespace lambda {


class Stacks {
public:
   private ICallback<T1, T2, T3, T4, T5, T6> callback;
   private static const Pool<Stacks$Params6$CallbackStackItem<Object, Object, Object, Object, Object, Object>> s_pool = std::make_shared<Pool>(
      Stacks$Params6$CallbackStackItem::new
   );

    void invoke() {
      this.callback.accept(this, this.val1, this.val2, this.val3, this.val4, this.val5, this.val6);
   }

   public static <T1, T2, T3, T4, T5, T6> Stacks$Params6$CallbackStackItem<T1, T2, T3, T4, T5, T6> alloc(
      T1 var0, T2 var1, T3 var2, T4 var3, T5 var4, T6 var5, ICallback<T1, T2, T3, T4, T5, T6> var6
   ) {
      Stacks$Params6$CallbackStackItem var7 = (Stacks$Params6$CallbackStackItem)s_pool.alloc();
      var7.val1 = var0;
      var7.val2 = var1;
      var7.val3 = var2;
      var7.val4 = var3;
      var7.val5 = var4;
      var7.val6 = var5;
      var7.callback = var6;
    return var7;
   }

    void onReleased() {
      this.val1 = nullptr;
      this.val2 = nullptr;
      this.val3 = nullptr;
      this.val4 = nullptr;
      this.val5 = nullptr;
      this.val6 = nullptr;
      this.callback = nullptr;
      super.onReleased();
   }
}
} // namespace lambda
} // namespace util
} // namespace zombie
