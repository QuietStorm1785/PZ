package zombie.util.lambda;

import zombie.util.Pool;
import zombie.util.lambda.Invokers.Params1.ICallback;
import zombie.util.lambda.Invokers.Params1.StackItem;

public final class Invokers$Params1$CallbackStackItem<T1> extends StackItem<T1> implements Runnable {
   private ICallback<T1> invoker;
   private static final Pool<Invokers$Params1$CallbackStackItem<Object>> s_pool = new Pool(Invokers$Params1$CallbackStackItem::new);

   @Override
   public void run() {
      this.invoker.accept(this.val1);
   }

   public static <T1> Invokers$Params1$CallbackStackItem<T1> alloc(T1 var0, ICallback<T1> var1) {
      Invokers$Params1$CallbackStackItem var2 = (Invokers$Params1$CallbackStackItem)s_pool.alloc();
      var2.val1 = var0;
      var2.invoker = var1;
      return var2;
   }

   public void onReleased() {
      this.val1 = null;
      this.invoker = null;
   }
}
