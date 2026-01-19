package zombie.util.lambda;

import java.util.function.Predicate;
import zombie.util.Pool;
import zombie.util.lambda.Predicates.Params2.ICallback;
import zombie.util.lambda.Predicates.Params2.StackItem;

public final class Predicates$Params2$CallbackStackItem<E, T1, T2> extends StackItem<T1, T2> implements Predicate<E> {
   private ICallback<E, T1, T2> predicate;
   private static final Pool<Predicates$Params2$CallbackStackItem<Object, Object, Object>> s_pool = new Pool(Predicates$Params2$CallbackStackItem::new);

   @Override
   public boolean test(E var1) {
      return this.predicate.test(var1, this.val1, this.val2);
   }

   public static <E, T1, T2> Predicates$Params2$CallbackStackItem<E, T1, T2> alloc(T1 var0, T2 var1, ICallback<E, T1, T2> var2) {
      Predicates$Params2$CallbackStackItem var3 = (Predicates$Params2$CallbackStackItem)s_pool.alloc();
      var3.val1 = var0;
      var3.val2 = var1;
      var3.predicate = var2;
      return var3;
   }

   public void onReleased() {
      this.val1 = null;
      this.val2 = null;
      this.predicate = null;
   }
}
