package zombie.characters;

import java.util.LinkedHashMap;
import java.util.Map.Entry;

class NetworkCharacterAI$1 extends LinkedHashMap<Integer, String> {
   NetworkCharacterAI$1(NetworkCharacterAI var1) {
      this.this$0 = var1;
   }

   @Override
   protected boolean removeEldestEntry(Entry<Integer, String> var1) {
      return this.size() > 10;
   }
}
