package zombie.util.lambda;

import java.util.function.Consumer;
import zombie.util.Pool;
import zombie.util.lambda.Consumers.Params4.ICallback;
import zombie.util.lambda.Consumers.Params4.StackItem;

public final class Consumers$Params4$CallbackStackItem<E, T1, T2, T3, T4> extends StackItem<T1, T2, T3, T4> implements Consumer<E> {
   private ICallback<E, T1, T2, T3, T4> consumer;
   private static final Pool<Consumers$Params4$CallbackStackItem<Object, Object, Object, Object, Object>> s_pool = new Pool(
      Consumers$Params4$CallbackStackItem::new
   );

   @Override
   public void accept(E var1) {
      this.consumer.accept(var1, this.val1, this.val2, this.val3, this.val4);
   }

   public static <E, T1, T2, T3, T4> Consumers$Params4$CallbackStackItem<E, T1, T2, T3, T4> alloc(
      T1 var0, T2 var1, T3 var2, T4 var3, ICallback<E, T1, T2, T3, T4> var4
   ) {
      Consumers$Params4$CallbackStackItem var5 = (Consumers$Params4$CallbackStackItem)s_pool.alloc();
      var5.val1 = var0;
      var5.val2 = var1;
      var5.val3 = var2;
      var5.val4 = var3;
      var5.consumer = var4;
      return var5;
   }

   public void onReleased() {
      this.val1 = null;
      this.val2 = null;
      this.val3 = null;
      this.val4 = null;
      this.consumer = null;
   }
}
