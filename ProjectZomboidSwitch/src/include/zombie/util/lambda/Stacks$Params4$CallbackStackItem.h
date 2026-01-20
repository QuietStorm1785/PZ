#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/util/Pool.h"
#include "zombie/util/lambda/Stacks/Params4/ICallback.h"
#include "zombie/util/lambda/Stacks/Params4/StackItem.h"

namespace zombie {
namespace util {
namespace lambda {


class Stacks {
public:
   private ICallback<T1, T2, T3, T4> callback;
   private static const Pool<Stacks$Params4$CallbackStackItem<Object, Object, Object, Object>> s_pool = std::make_shared<Pool>(Stacks$Params4$CallbackStackItem::new);

    void invoke() {
      this.callback.accept(this, this.val1, this.val2, this.val3, this.val4);
   }

   public static <T1, T2, T3, T4> Stacks$Params4$CallbackStackItem<T1, T2, T3, T4> alloc(T1 var0, T2 var1, T3 var2, T4 var3, ICallback<T1, T2, T3, T4> var4) {
      Stacks$Params4$CallbackStackItem var5 = (Stacks$Params4$CallbackStackItem)s_pool.alloc();
      var5.val1 = var0;
      var5.val2 = var1;
      var5.val3 = var2;
      var5.val4 = var3;
      var5.callback = var4;
    return var5;
   }

    void onReleased() {
      this.val1 = nullptr;
      this.val2 = nullptr;
      this.val3 = nullptr;
      this.val4 = nullptr;
      this.callback = nullptr;
      super.onReleased();
   }
}
} // namespace lambda
} // namespace util
} // namespace zombie
