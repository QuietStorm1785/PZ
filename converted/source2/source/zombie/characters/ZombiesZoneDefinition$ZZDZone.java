package zombie.characters;

import java.util.ArrayList;
import zombie.characters.ZombiesZoneDefinition.ZZDOutfit;

final class ZombiesZoneDefinition$ZZDZone {
   String name;
   int femaleChance;
   int maleChance;
   int chanceToSpawn;
   int toSpawn;
   final ArrayList<ZZDOutfit> outfits = new ArrayList<>();

   private ZombiesZoneDefinition$ZZDZone() {
   }
}
