package zombie.util.lambda;

import zombie.util.Pool;
import zombie.util.lambda.Stacks.Params4.ICallback;
import zombie.util.lambda.Stacks.Params4.StackItem;

public final class Stacks$Params4$CallbackStackItem<T1, T2, T3, T4> extends StackItem<T1, T2, T3, T4> {
   private ICallback<T1, T2, T3, T4> callback;
   private static final Pool<Stacks$Params4$CallbackStackItem<Object, Object, Object, Object>> s_pool = new Pool(Stacks$Params4$CallbackStackItem::new);

   public void invoke() {
      this.callback.accept(this, this.val1, this.val2, this.val3, this.val4);
   }

   public static <T1, T2, T3, T4> Stacks$Params4$CallbackStackItem<T1, T2, T3, T4> alloc(T1 var0, T2 var1, T3 var2, T4 var3, ICallback<T1, T2, T3, T4> var4) {
      Stacks$Params4$CallbackStackItem var5 = (Stacks$Params4$CallbackStackItem)s_pool.alloc();
      var5.val1 = var0;
      var5.val2 = var1;
      var5.val3 = var2;
      var5.val4 = var3;
      var5.callback = var4;
      return var5;
   }

   public void onReleased() {
      this.val1 = null;
      this.val2 = null;
      this.val3 = null;
      this.val4 = null;
      this.callback = null;
      super.onReleased();
   }
}
