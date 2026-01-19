package zombie;

import java.util.ArrayList;
import java.util.List;
import zombie.GameProfileRecording.Span;
import zombie.util.IPooledObject;

public class GameProfileRecording$Row {
   long StartTime;
   long EndTime;
   final List<Span> Spans = new ArrayList<>();

   public void reset() {
      IPooledObject.release(this.Spans);
   }
}
