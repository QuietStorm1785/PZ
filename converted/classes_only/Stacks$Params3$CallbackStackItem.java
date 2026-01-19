package zombie.util.lambda;

import zombie.util.Pool;
import zombie.util.lambda.Stacks.Params3.ICallback;
import zombie.util.lambda.Stacks.Params3.StackItem;

public final class Stacks$Params3$CallbackStackItem<T1, T2, T3> extends StackItem<T1, T2, T3> {
   private ICallback<T1, T2, T3> callback;
   private static final Pool<Stacks$Params3$CallbackStackItem<Object, Object, Object>> s_pool = new Pool(Stacks$Params3$CallbackStackItem::new);

   public void invoke() {
      this.callback.accept(this, this.val1, this.val2, this.val3);
   }

   public static <T1, T2, T3> Stacks$Params3$CallbackStackItem<T1, T2, T3> alloc(T1 var0, T2 var1, T3 var2, ICallback<T1, T2, T3> var3) {
      Stacks$Params3$CallbackStackItem var4 = (Stacks$Params3$CallbackStackItem)s_pool.alloc();
      var4.val1 = var0;
      var4.val2 = var1;
      var4.val3 = var2;
      var4.callback = var3;
      return var4;
   }

   public void onReleased() {
      this.val1 = null;
      this.val2 = null;
      this.val3 = null;
      this.callback = null;
      super.onReleased();
   }
}
