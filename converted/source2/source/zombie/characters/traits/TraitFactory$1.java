package zombie.characters.traits;

import java.util.Comparator;
import java.util.Map.Entry;
import zombie.characters.traits.TraitFactory.Trait;

class TraitFactory$1 implements Comparator<Entry<String, Trait>> {
   public int compare(Entry<String, Trait> var1, Entry<String, Trait> var2) {
      return ((Trait)var1.getValue()).name.compareTo(((Trait)var2.getValue()).name);
   }
}
