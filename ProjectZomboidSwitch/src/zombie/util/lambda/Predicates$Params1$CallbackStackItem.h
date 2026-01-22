#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/util/Pool.h"
#include "zombie/util/lambda/Predicates/Params1/ICallback.h"
#include "zombie/util/lambda/Predicates/Params1/StackItem.h"
#include <algorithm>

namespace zombie {
namespace util {
namespace lambda {


class Predicates {
public:
   private ICallback<E, T1> predicate;
   private static const Pool<Predicates$Params1$CallbackStackItem<Object, Object>> s_pool = std::make_shared<Pool>(Predicates$Params1$CallbackStackItem::new);

    bool test(E var1) {
      return this.predicate.test(var1, this.val1);
   }

   public static <E, T1> Predicates$Params1$CallbackStackItem<E, T1> alloc(T1 var0, ICallback<E, T1> var1) {
      Predicates$Params1$CallbackStackItem var2 = (Predicates$Params1$CallbackStackItem)s_pool.alloc();
      var2.val1 = var0;
      var2.predicate = var1;
    return var2;
   }

    void onReleased() {
      this.val1 = nullptr;
      this.predicate = nullptr;
   }
}
} // namespace lambda
} // namespace util
} // namespace zombie
