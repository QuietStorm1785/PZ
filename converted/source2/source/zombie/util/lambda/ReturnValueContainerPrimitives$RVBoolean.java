package zombie.util.lambda;

import zombie.util.Pool;
import zombie.util.PooledObject;

public final class ReturnValueContainerPrimitives$RVBoolean extends PooledObject {
   public boolean ReturnVal;
   private static final Pool<ReturnValueContainerPrimitives$RVBoolean> s_pool = new Pool(ReturnValueContainerPrimitives$RVBoolean::new);

   public void onReleased() {
      this.ReturnVal = false;
   }

   public static ReturnValueContainerPrimitives$RVBoolean alloc() {
      return (ReturnValueContainerPrimitives$RVBoolean)s_pool.alloc();
   }
}
