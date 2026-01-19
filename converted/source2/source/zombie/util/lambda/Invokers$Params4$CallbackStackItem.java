package zombie.util.lambda;

import zombie.util.Pool;
import zombie.util.lambda.Invokers.Params4.ICallback;
import zombie.util.lambda.Invokers.Params4.StackItem;

public final class Invokers$Params4$CallbackStackItem<T1, T2, T3, T4> extends StackItem<T1, T2, T3, T4> implements Runnable {
   private ICallback<T1, T2, T3, T4> invoker;
   private static final Pool<Invokers$Params4$CallbackStackItem<Object, Object, Object, Object>> s_pool = new Pool(Invokers$Params4$CallbackStackItem::new);

   @Override
   public void run() {
      this.invoker.accept(this.val1, this.val2, this.val3, this.val4);
   }

   public static <T1, T2, T3, T4> Invokers$Params4$CallbackStackItem<T1, T2, T3, T4> alloc(T1 var0, T2 var1, T3 var2, T4 var3, ICallback<T1, T2, T3, T4> var4) {
      Invokers$Params4$CallbackStackItem var5 = (Invokers$Params4$CallbackStackItem)s_pool.alloc();
      var5.val1 = var0;
      var5.val2 = var1;
      var5.val3 = var2;
      var5.val4 = var3;
      var5.invoker = var4;
      return var5;
   }

   public void onReleased() {
      this.val1 = null;
      this.val2 = null;
      this.val3 = null;
      this.val4 = null;
      this.invoker = null;
   }
}
