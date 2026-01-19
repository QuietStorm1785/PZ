package zombie.util.lambda;

import zombie.util.Pool;
import zombie.util.lambda.Invokers.Params2.ICallback;
import zombie.util.lambda.Invokers.Params2.StackItem;

public final class Invokers$Params2$CallbackStackItem<T1, T2> extends StackItem<T1, T2> implements Runnable {
   private ICallback<T1, T2> invoker;
   private static final Pool<Invokers$Params2$CallbackStackItem<Object, Object>> s_pool = new Pool(Invokers$Params2$CallbackStackItem::new);

   @Override
   public void run() {
      this.invoker.accept(this.val1, this.val2);
   }

   public static <T1, T2> Invokers$Params2$CallbackStackItem<T1, T2> alloc(T1 var0, T2 var1, ICallback<T1, T2> var2) {
      Invokers$Params2$CallbackStackItem var3 = (Invokers$Params2$CallbackStackItem)s_pool.alloc();
      var3.val1 = var0;
      var3.val2 = var1;
      var3.invoker = var2;
      return var3;
   }

   public void onReleased() {
      this.val1 = null;
      this.val2 = null;
      this.invoker = null;
   }
}
