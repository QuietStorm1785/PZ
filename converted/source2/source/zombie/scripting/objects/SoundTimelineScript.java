package zombie.scripting.objects;

import java.util.HashMap;
import zombie.core.math.PZMath;
import zombie.scripting.ScriptParser;
import zombie.scripting.ScriptParser.Block;
import zombie.scripting.ScriptParser.Value;

public final class SoundTimelineScript extends BaseScriptObject {
   private String eventName;
   private HashMap<String, Integer> positionByName = new HashMap<>();

   public void Load(String var1, String var2) {
      this.eventName = var1;
      Block var3 = ScriptParser.parse(var2);
      var3 = (Block)var3.children.get(0);

      for (Value var5 : var3.values) {
         String var6 = var5.getKey().trim();
         String var7 = var5.getValue().trim();
         this.positionByName.put(var6, PZMath.tryParseInt(var7, 0));
      }
   }

   public String getEventName() {
      return this.eventName;
   }

   public int getPosition(String var1) {
      return this.positionByName.containsKey(var1) ? this.positionByName.get(var1) : -1;
   }

   public void reset() {
      this.positionByName.clear();
   }
}
