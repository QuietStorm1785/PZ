package zombie.util.lambda;

import zombie.util.Pool;
import zombie.util.lambda.Stacks.Params1.ICallback;
import zombie.util.lambda.Stacks.Params1.StackItem;

public final class Stacks$Params1$CallbackStackItem<T1> extends StackItem<T1> {
   private ICallback<T1> callback;
   private static final Pool<Stacks$Params1$CallbackStackItem<Object>> s_pool = new Pool(Stacks$Params1$CallbackStackItem::new);

   public void invoke() {
      this.callback.accept(this, this.val1);
   }

   public static <T1> Stacks$Params1$CallbackStackItem<T1> alloc(T1 var0, ICallback<T1> var1) {
      Stacks$Params1$CallbackStackItem var2 = (Stacks$Params1$CallbackStackItem)s_pool.alloc();
      var2.val1 = var0;
      var2.callback = var1;
      return var2;
   }

   public void onReleased() {
      this.val1 = null;
      this.callback = null;
      super.onReleased();
   }
}
