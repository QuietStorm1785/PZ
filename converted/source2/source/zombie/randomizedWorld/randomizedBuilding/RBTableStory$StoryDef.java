package zombie.randomizedWorld.randomizedBuilding;

import java.util.ArrayList;
import zombie.randomizedWorld.randomizedBuilding.RBTableStory.StorySpawnItem;

public class RBTableStory$StoryDef {
   public ArrayList<StorySpawnItem> items;
   public boolean addBlood;
   public ArrayList<String> rooms;

   public RBTableStory$StoryDef(ArrayList<StorySpawnItem> var1, ArrayList var2) {
      this.this$0 = var1;
      this.items = null;
      this.addBlood = false;
      this.rooms = null;
      this.items = var2;
   }

   public RBTableStory$StoryDef(ArrayList<StorySpawnItem> var1, ArrayList<String> var2, ArrayList var3) {
      this.this$0 = var1;
      this.items = null;
      this.addBlood = false;
      this.rooms = null;
      this.items = var2;
      this.rooms = var3;
   }
}
