package zombie;

import java.util.ArrayList;
import java.util.List;
import zombie.util.IPooledObject;
import zombie.util.Pool;
import zombie.util.PooledObject;

public class GameProfileRecording$Span extends PooledObject {
   int key;
   int Depth;
   long StartTime;
   long EndTime;
   final List<GameProfileRecording$Span> Children = new ArrayList<>();
   private static final Pool<GameProfileRecording$Span> s_pool = new Pool(GameProfileRecording$Span::new);

   public void onReleased() {
      super.onReleased();
      IPooledObject.release(this.Children);
   }

   public static GameProfileRecording$Span alloc() {
      return (GameProfileRecording$Span)s_pool.alloc();
   }
}
