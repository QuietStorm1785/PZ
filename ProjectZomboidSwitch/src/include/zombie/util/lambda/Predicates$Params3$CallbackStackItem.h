#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/util/Pool.h"
#include "zombie/util/lambda/Predicates/Params3/ICallback.h"
#include "zombie/util/lambda/Predicates/Params3/StackItem.h"
#include <algorithm>

namespace zombie {
namespace util {
namespace lambda {


class Predicates {
public:
   private ICallback<E, T1, T2, T3> predicate;
   private static const Pool<Predicates$Params3$CallbackStackItem<Object, Object, Object, Object>> s_pool = std::make_shared<Pool>(Predicates$Params3$CallbackStackItem::new);

    bool test(E var1) {
      return this.predicate.test(var1, this.val1, this.val2, this.val3);
   }

   public static <E, T1, T2, T3> Predicates$Params3$CallbackStackItem<E, T1, T2, T3> alloc(T1 var0, T2 var1, T3 var2, ICallback<E, T1, T2, T3> var3) {
      Predicates$Params3$CallbackStackItem var4 = (Predicates$Params3$CallbackStackItem)s_pool.alloc();
      var4.val1 = var0;
      var4.val2 = var1;
      var4.val3 = var2;
      var4.predicate = var3;
    return var4;
   }

    void onReleased() {
      this.val1 = nullptr;
      this.val2 = nullptr;
      this.val3 = nullptr;
      this.predicate = nullptr;
   }
}
} // namespace lambda
} // namespace util
} // namespace zombie
