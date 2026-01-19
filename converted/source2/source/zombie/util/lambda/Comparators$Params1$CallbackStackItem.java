package zombie.util.lambda;

import java.util.Comparator;
import zombie.util.Pool;
import zombie.util.lambda.Comparators.Params1.ICallback;
import zombie.util.lambda.Comparators.Params1.StackItem;

public final class Comparators$Params1$CallbackStackItem<E, T1> extends StackItem<T1> implements Comparator<E> {
   private ICallback<E, T1> comparator;
   private static final Pool<Comparators$Params1$CallbackStackItem<Object, Object>> s_pool = new Pool(Comparators$Params1$CallbackStackItem::new);

   @Override
   public int compare(E var1, E var2) {
      return this.comparator.compare(var1, var2, this.val1);
   }

   public static <E, T1> Comparators$Params1$CallbackStackItem<E, T1> alloc(T1 var0, ICallback<E, T1> var1) {
      Comparators$Params1$CallbackStackItem var2 = (Comparators$Params1$CallbackStackItem)s_pool.alloc();
      var2.val1 = var0;
      var2.comparator = var1;
      return var2;
   }

   public void onReleased() {
      this.val1 = null;
      this.comparator = null;
   }
}
