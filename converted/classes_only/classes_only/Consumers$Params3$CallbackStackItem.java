package zombie.util.lambda;

import java.util.function.Consumer;
import zombie.util.Pool;
import zombie.util.lambda.Consumers.Params3.ICallback;
import zombie.util.lambda.Consumers.Params3.StackItem;

public final class Consumers$Params3$CallbackStackItem<E, T1, T2, T3> extends StackItem<T1, T2, T3> implements Consumer<E> {
   private ICallback<E, T1, T2, T3> consumer;
   private static final Pool<Consumers$Params3$CallbackStackItem<Object, Object, Object, Object>> s_pool = new Pool(Consumers$Params3$CallbackStackItem::new);

   @Override
   public void accept(E var1) {
      this.consumer.accept(var1, this.val1, this.val2, this.val3);
   }

   public static <E, T1, T2, T3> Consumers$Params3$CallbackStackItem<E, T1, T2, T3> alloc(T1 var0, T2 var1, T3 var2, ICallback<E, T1, T2, T3> var3) {
      Consumers$Params3$CallbackStackItem var4 = (Consumers$Params3$CallbackStackItem)s_pool.alloc();
      var4.val1 = var0;
      var4.val2 = var1;
      var4.val3 = var2;
      var4.consumer = var3;
      return var4;
   }

   public void onReleased() {
      this.val1 = null;
      this.val2 = null;
      this.val3 = null;
      this.consumer = null;
   }
}
