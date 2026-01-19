package zombie.util.lambda;

import zombie.util.Pool;
import zombie.util.PooledObject;

public final class ReturnValueContainerPrimitives$RVInt extends PooledObject {
   public int ReturnVal;
   private static final Pool<ReturnValueContainerPrimitives$RVInt> s_pool = new Pool(ReturnValueContainerPrimitives$RVInt::new);

   public void onReleased() {
      this.ReturnVal = 0;
   }

   public static ReturnValueContainerPrimitives$RVInt alloc() {
      return (ReturnValueContainerPrimitives$RVInt)s_pool.alloc();
   }
}
