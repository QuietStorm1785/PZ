package zombie.util.lambda;

import java.util.function.Consumer;
import zombie.util.Pool;
import zombie.util.lambda.Consumers.Params1.ICallback;
import zombie.util.lambda.Consumers.Params1.StackItem;

public final class Consumers$Params1$CallbackStackItem<E, T1> extends StackItem<T1> implements Consumer<E> {
   private ICallback<E, T1> consumer;
   private static final Pool<Consumers$Params1$CallbackStackItem<Object, Object>> s_pool = new Pool(Consumers$Params1$CallbackStackItem::new);

   @Override
   public void accept(E var1) {
      this.consumer.accept(var1, this.val1);
   }

   public static <E, T1> Consumers$Params1$CallbackStackItem<E, T1> alloc(T1 var0, ICallback<E, T1> var1) {
      Consumers$Params1$CallbackStackItem var2 = (Consumers$Params1$CallbackStackItem)s_pool.alloc();
      var2.val1 = var0;
      var2.consumer = var1;
      return var2;
   }

   public void onReleased() {
      this.val1 = null;
      this.consumer = null;
   }
}
