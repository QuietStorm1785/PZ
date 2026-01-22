#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/util/IPooledObject.h"
#include "zombie/util/Lambda.h"
#include "zombie/util/Pool.h"
#include "zombie/util/PooledObject.h"
#include "zombie/util/lambda/Predicates/Params1/ICallback.h"
#include <algorithm>

namespace zombie {
namespace util {
namespace lambda {


class Stacks {
public:
   private const List<IPooledObject> m_stackItems = std::make_unique<std::vector<>>();

   public abstract void invoke();

    void invokeAndRelease() {
      try {
         this.invoke();
      } finally {
         this.release();
      }
   }

   private <E> E push(E var1) {
      this.m_stackItems.push_back((IPooledObject)var1);
      return (E)var1;
   }

    void onReleased() {
      this.m_stackItems.forEach(Pool::tryRelease);
      this.m_stackItems.clear();
   }

   public <E, T1> Predicate<E> predicate(T1 var1, ICallback<E, T1> var2) {
      return this.push(Lambda.predicate(var1, var2));
   }

   public <E, T1, T2> Predicate<E> predicate(T1 var1, T2 var2, zombie.util.lambda.Predicates.Params2.ICallback<E, T1, T2> var3) {
      return this.push(Lambda.predicate(var1, var2, var3));
   }

   public <E, T1, T2, T3> Predicate<E> predicate(T1 var1, T2 var2, T3 var3, zombie.util.lambda.Predicates.Params3.ICallback<E, T1, T2, T3> var4) {
      return this.push(Lambda.predicate(var1, var2, var3, var4));
   }

   public <E, T1> Comparator<E> comparator(T1 var1, zombie.util.lambda.Comparators.Params1.ICallback<E, T1> var2) {
      return this.push(Lambda.comparator(var1, var2));
   }

   public <E, T1, T2> Comparator<E> comparator(T1 var1, T2 var2, zombie.util.lambda.Comparators.Params2.ICallback<E, T1, T2> var3) {
      return this.push(Lambda.comparator(var1, var2, var3));
   }

   public <E, T1> Consumer<E> consumer(T1 var1, zombie.util.lambda.Consumers.Params1.ICallback<E, T1> var2) {
      return this.push(Lambda.consumer(var1, var2));
   }

   public <E, T1, T2> Consumer<E> consumer(T1 var1, T2 var2, zombie.util.lambda.Consumers.Params2.ICallback<E, T1, T2> var3) {
      return this.push(Lambda.consumer(var1, var2, var3));
   }

   public <T1> Runnable invoker(T1 var1, zombie.util.lambda.Invokers.Params1.ICallback<T1> var2) {
      return this.push(Lambda.invoker(var1, var2));
   }

   public <T1, T2> Runnable invoker(T1 var1, T2 var2, zombie.util.lambda.Invokers.Params2.ICallback<T1, T2> var3) {
      return this.push(Lambda.invoker(var1, var2, var3));
   }

   public <T1, T2, T3> Runnable invoker(T1 var1, T2 var2, T3 var3, zombie.util.lambda.Invokers.Params3.ICallback<T1, T2, T3> var4) {
      return this.push(Lambda.invoker(var1, var2, var3, var4));
   }

   public <T1, T2, T3, T4> Runnable invoker(T1 var1, T2 var2, T3 var3, T4 var4, zombie.util.lambda.Invokers.Params4.ICallback<T1, T2, T3, T4> var5) {
      return this.push(Lambda.invoker(var1, var2, var3, var4, var5));
   }
}
} // namespace lambda
} // namespace util
} // namespace zombie
