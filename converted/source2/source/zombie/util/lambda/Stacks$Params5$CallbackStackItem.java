package zombie.util.lambda;

import zombie.util.Pool;
import zombie.util.lambda.Stacks.Params5.ICallback;
import zombie.util.lambda.Stacks.Params5.StackItem;

public final class Stacks$Params5$CallbackStackItem<T1, T2, T3, T4, T5> extends StackItem<T1, T2, T3, T4, T5> {
   private ICallback<T1, T2, T3, T4, T5> callback;
   private static final Pool<Stacks$Params5$CallbackStackItem<Object, Object, Object, Object, Object>> s_pool = new Pool(Stacks$Params5$CallbackStackItem::new);

   public void invoke() {
      this.callback.accept(this, this.val1, this.val2, this.val3, this.val4, this.val5);
   }

   public static <T1, T2, T3, T4, T5> Stacks$Params5$CallbackStackItem<T1, T2, T3, T4, T5> alloc(
      T1 var0, T2 var1, T3 var2, T4 var3, T5 var4, ICallback<T1, T2, T3, T4, T5> var5
   ) {
      Stacks$Params5$CallbackStackItem var6 = (Stacks$Params5$CallbackStackItem)s_pool.alloc();
      var6.val1 = var0;
      var6.val2 = var1;
      var6.val3 = var2;
      var6.val4 = var3;
      var6.val5 = var4;
      var6.callback = var5;
      return var6;
   }

   public void onReleased() {
      this.val1 = null;
      this.val2 = null;
      this.val3 = null;
      this.val4 = null;
      this.val5 = null;
      this.callback = null;
      super.onReleased();
   }
}
