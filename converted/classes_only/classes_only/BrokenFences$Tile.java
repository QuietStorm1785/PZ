package zombie.iso;

import java.util.ArrayList;
import zombie.util.list.PZArrayUtil;

final class BrokenFences$Tile {
   ArrayList<String> self = null;
   ArrayList<String> left = null;
   ArrayList<String> right = null;
   ArrayList<String> debrisN = null;
   ArrayList<String> debrisS = null;
   ArrayList<String> debrisW = null;
   ArrayList<String> debrisE = null;

   private BrokenFences$Tile() {
   }

   String pickRandom(ArrayList<String> var1) {
      return var1 == null ? null : (String)PZArrayUtil.pickRandom(var1);
   }
}
