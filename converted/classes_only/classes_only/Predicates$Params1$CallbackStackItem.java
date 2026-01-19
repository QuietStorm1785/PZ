package zombie.util.lambda;

import java.util.function.Predicate;
import zombie.util.Pool;
import zombie.util.lambda.Predicates.Params1.ICallback;
import zombie.util.lambda.Predicates.Params1.StackItem;

public final class Predicates$Params1$CallbackStackItem<E, T1> extends StackItem<T1> implements Predicate<E> {
   private ICallback<E, T1> predicate;
   private static final Pool<Predicates$Params1$CallbackStackItem<Object, Object>> s_pool = new Pool(Predicates$Params1$CallbackStackItem::new);

   @Override
   public boolean test(E var1) {
      return this.predicate.test(var1, this.val1);
   }

   public static <E, T1> Predicates$Params1$CallbackStackItem<E, T1> alloc(T1 var0, ICallback<E, T1> var1) {
      Predicates$Params1$CallbackStackItem var2 = (Predicates$Params1$CallbackStackItem)s_pool.alloc();
      var2.val1 = var0;
      var2.predicate = var1;
      return var2;
   }

   public void onReleased() {
      this.val1 = null;
      this.predicate = null;
   }
}
