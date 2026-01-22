#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/util/Pool.h"
#include "zombie/util/lambda/Stacks/Params1/ICallback.h"
#include "zombie/util/lambda/Stacks/Params1/StackItem.h"

namespace zombie {
namespace util {
namespace lambda {


class Stacks {
public:
   private ICallback<T1> callback;
   private static const Pool<Stacks$Params1$CallbackStackItem<Object>> s_pool = std::make_shared<Pool>(Stacks$Params1$CallbackStackItem::new);

    void invoke() {
      this.callback.accept(this, this.val1);
   }

   public static <T1> Stacks$Params1$CallbackStackItem<T1> alloc(T1 var0, ICallback<T1> var1) {
      Stacks$Params1$CallbackStackItem var2 = (Stacks$Params1$CallbackStackItem)s_pool.alloc();
      var2.val1 = var0;
      var2.callback = var1;
    return var2;
   }

    void onReleased() {
      this.val1 = nullptr;
      this.callback = nullptr;
      super.onReleased();
   }
}
} // namespace lambda
} // namespace util
} // namespace zombie
