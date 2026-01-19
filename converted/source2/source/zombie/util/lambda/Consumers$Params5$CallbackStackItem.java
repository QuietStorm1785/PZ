package zombie.util.lambda;

import java.util.function.Consumer;
import zombie.util.Pool;
import zombie.util.lambda.Consumers.Params5.ICallback;
import zombie.util.lambda.Consumers.Params5.StackItem;

public final class Consumers$Params5$CallbackStackItem<E, T1, T2, T3, T4, T5> extends StackItem<T1, T2, T3, T4, T5> implements Consumer<E> {
   private ICallback<E, T1, T2, T3, T4, T5> consumer;
   private static final Pool<Consumers$Params5$CallbackStackItem<Object, Object, Object, Object, Object, Object>> s_pool = new Pool(
      Consumers$Params5$CallbackStackItem::new
   );

   @Override
   public void accept(E var1) {
      this.consumer.accept(var1, this.val1, this.val2, this.val3, this.val4, this.val5);
   }

   public static <E, T1, T2, T3, T4, T5> Consumers$Params5$CallbackStackItem<E, T1, T2, T3, T4, T5> alloc(
      T1 var0, T2 var1, T3 var2, T4 var3, T5 var4, ICallback<E, T1, T2, T3, T4, T5> var5
   ) {
      Consumers$Params5$CallbackStackItem var6 = (Consumers$Params5$CallbackStackItem)s_pool.alloc();
      var6.val1 = var0;
      var6.val2 = var1;
      var6.val3 = var2;
      var6.val4 = var3;
      var6.val5 = var4;
      var6.consumer = var5;
      return var6;
   }

   public void onReleased() {
      this.val1 = null;
      this.val2 = null;
      this.val3 = null;
      this.val4 = null;
      this.val5 = null;
      this.consumer = null;
   }
}
