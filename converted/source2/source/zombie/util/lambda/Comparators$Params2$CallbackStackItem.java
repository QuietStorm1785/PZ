package zombie.util.lambda;

import java.util.Comparator;
import zombie.util.Pool;
import zombie.util.lambda.Comparators.Params2.ICallback;
import zombie.util.lambda.Comparators.Params2.StackItem;

public final class Comparators$Params2$CallbackStackItem<E, T1, T2> extends StackItem<T1, T2> implements Comparator<E> {
   private ICallback<E, T1, T2> comparator;
   private static final Pool<Comparators$Params2$CallbackStackItem<Object, Object, Object>> s_pool = new Pool(Comparators$Params2$CallbackStackItem::new);

   @Override
   public int compare(E var1, E var2) {
      return this.comparator.compare(var1, var2, this.val1, this.val2);
   }

   public static <E, T1, T2> Comparators$Params2$CallbackStackItem<E, T1, T2> alloc(T1 var0, T2 var1, ICallback<E, T1, T2> var2) {
      Comparators$Params2$CallbackStackItem var3 = (Comparators$Params2$CallbackStackItem)s_pool.alloc();
      var3.val1 = var0;
      var3.val2 = var1;
      var3.comparator = var2;
      return var3;
   }

   public void onReleased() {
      this.val1 = null;
      this.val2 = null;
      this.comparator = null;
   }
}
