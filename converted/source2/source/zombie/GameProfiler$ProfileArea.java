package zombie;

import java.util.ArrayList;
import java.util.List;
import zombie.util.IPooledObject;
import zombie.util.Pool;
import zombie.util.PooledObject;

public class GameProfiler$ProfileArea extends PooledObject {
   public String Key;
   public long StartTime;
   public long EndTime;
   public long Total;
   public int Depth;
   public float r = 1.0F;
   public float g = 1.0F;
   public float b = 1.0F;
   public final List<GameProfiler$ProfileArea> Children = new ArrayList<>();
   private static final Pool<GameProfiler$ProfileArea> s_pool = new Pool(GameProfiler$ProfileArea::new);

   public void onReleased() {
      super.onReleased();
      this.clear();
   }

   public void clear() {
      this.StartTime = 0L;
      this.EndTime = 0L;
      this.Total = 0L;
      this.Depth = 0;
      IPooledObject.release(this.Children);
   }

   public static GameProfiler$ProfileArea alloc() {
      return (GameProfiler$ProfileArea)s_pool.alloc();
   }
}
