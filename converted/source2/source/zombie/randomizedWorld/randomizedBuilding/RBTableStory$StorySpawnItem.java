package zombie.randomizedWorld.randomizedBuilding;

import java.util.LinkedHashMap;

public class RBTableStory$StorySpawnItem {
   LinkedHashMap<String, Integer> eitherObject;
   String object;
   Integer chanceToSpawn;
   float forcedOffset;

   public RBTableStory$StorySpawnItem(LinkedHashMap<String, Integer> var1, String var2, Integer var3, Integer var4) {
      this.this$0 = var1;
      this.eitherObject = null;
      this.object = null;
      this.chanceToSpawn = null;
      this.forcedOffset = 0.0F;
      this.eitherObject = var2;
      this.object = var3;
      this.chanceToSpawn = var4;
   }

   public RBTableStory$StorySpawnItem(LinkedHashMap<String, Integer> var1, String var2, Integer var3, float var4, float var5) {
      this.this$0 = var1;
      this.eitherObject = null;
      this.object = null;
      this.chanceToSpawn = null;
      this.forcedOffset = 0.0F;
      this.eitherObject = var2;
      this.object = var3;
      this.chanceToSpawn = var4;
      this.forcedOffset = var5;
   }
}
