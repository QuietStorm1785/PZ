package zombie.util.lambda;

import zombie.util.Pool;
import zombie.util.lambda.Stacks.Params6.ICallback;
import zombie.util.lambda.Stacks.Params6.StackItem;

public final class Stacks$Params6$CallbackStackItem<T1, T2, T3, T4, T5, T6> extends StackItem<T1, T2, T3, T4, T5, T6> {
   private ICallback<T1, T2, T3, T4, T5, T6> callback;
   private static final Pool<Stacks$Params6$CallbackStackItem<Object, Object, Object, Object, Object, Object>> s_pool = new Pool(
      Stacks$Params6$CallbackStackItem::new
   );

   public void invoke() {
      this.callback.accept(this, this.val1, this.val2, this.val3, this.val4, this.val5, this.val6);
   }

   public static <T1, T2, T3, T4, T5, T6> Stacks$Params6$CallbackStackItem<T1, T2, T3, T4, T5, T6> alloc(
      T1 var0, T2 var1, T3 var2, T4 var3, T5 var4, T6 var5, ICallback<T1, T2, T3, T4, T5, T6> var6
   ) {
      Stacks$Params6$CallbackStackItem var7 = (Stacks$Params6$CallbackStackItem)s_pool.alloc();
      var7.val1 = var0;
      var7.val2 = var1;
      var7.val3 = var2;
      var7.val4 = var3;
      var7.val5 = var4;
      var7.val6 = var5;
      var7.callback = var6;
      return var7;
   }

   public void onReleased() {
      this.val1 = null;
      this.val2 = null;
      this.val3 = null;
      this.val4 = null;
      this.val5 = null;
      this.val6 = null;
      this.callback = null;
      super.onReleased();
   }
}
