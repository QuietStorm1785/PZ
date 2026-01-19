package zombie.util.lambda;

import java.util.function.Consumer;
import zombie.util.Pool;
import zombie.util.lambda.Consumers.Params2.ICallback;
import zombie.util.lambda.Consumers.Params2.StackItem;

public final class Consumers$Params2$CallbackStackItem<E, T1, T2> extends StackItem<T1, T2> implements Consumer<E> {
   private ICallback<E, T1, T2> consumer;
   private static final Pool<Consumers$Params2$CallbackStackItem<Object, Object, Object>> s_pool = new Pool(Consumers$Params2$CallbackStackItem::new);

   @Override
   public void accept(E var1) {
      this.consumer.accept(var1, this.val1, this.val2);
   }

   public static <E, T1, T2> Consumers$Params2$CallbackStackItem<E, T1, T2> alloc(T1 var0, T2 var1, ICallback<E, T1, T2> var2) {
      Consumers$Params2$CallbackStackItem var3 = (Consumers$Params2$CallbackStackItem)s_pool.alloc();
      var3.val1 = var0;
      var3.val2 = var1;
      var3.consumer = var2;
      return var3;
   }

   public void onReleased() {
      this.val1 = null;
      this.val2 = null;
      this.consumer = null;
   }
}
