#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/util/Pool.h"
#include "zombie/util/lambda/Predicates/Params2/ICallback.h"
#include "zombie/util/lambda/Predicates/Params2/StackItem.h"
#include <algorithm>

namespace zombie {
namespace util {
namespace lambda {


class Predicates {
public:
   private ICallback<E, T1, T2> predicate;
   private static const Pool<Predicates$Params2$CallbackStackItem<Object, Object, Object>> s_pool = std::make_shared<Pool>(Predicates$Params2$CallbackStackItem::new);

    bool test(E var1) {
      return this.predicate.test(var1, this.val1, this.val2);
   }

   public static <E, T1, T2> Predicates$Params2$CallbackStackItem<E, T1, T2> alloc(T1 var0, T2 var1, ICallback<E, T1, T2> var2) {
      Predicates$Params2$CallbackStackItem var3 = (Predicates$Params2$CallbackStackItem)s_pool.alloc();
      var3.val1 = var0;
      var3.val2 = var1;
      var3.predicate = var2;
    return var3;
   }

    void onReleased() {
      this.val1 = nullptr;
      this.val2 = nullptr;
      this.predicate = nullptr;
   }
}
} // namespace lambda
} // namespace util
} // namespace zombie
