package zombie.characters.traits;

import java.util.ArrayList;
import java.util.Collections;
import java.util.LinkedHashMap;
import java.util.LinkedList;
import java.util.Map.Entry;
import zombie.characters.traits.TraitFactory.1;
import zombie.characters.traits.TraitFactory.Trait;

public final class TraitFactory {
   public static LinkedHashMap<String, Trait> TraitMap = new LinkedHashMap<>();

   public static void init() {
   }

   public static void setMutualExclusive(String var0, String var1) {
      TraitMap.get(var0).MutuallyExclusive.add(var1);
      TraitMap.get(var1).MutuallyExclusive.add(var0);
   }

   public static void sortList() {
      LinkedList var0 = new LinkedList<>(TraitMap.entrySet());
      Collections.sort(var0, new 1());
      LinkedHashMap var1 = new LinkedHashMap();

      for (Entry var3 : var0) {
         var1.put((String)var3.getKey(), (Trait)var3.getValue());
      }

      TraitMap = var1;
   }

   public static Trait addTrait(String var0, String var1, int var2, String var3, boolean var4) {
      Trait var5 = new Trait(var0, var1, var2, var3, var4, false);
      TraitMap.put(var0, var5);
      return var5;
   }

   public static Trait addTrait(String var0, String var1, int var2, String var3, boolean var4, boolean var5) {
      Trait var6 = new Trait(var0, var1, var2, var3, var4, var5);
      TraitMap.put(var0, var6);
      return var6;
   }

   public static ArrayList<Trait> getTraits() {
      ArrayList var0 = new ArrayList();

      for (Trait var2 : TraitMap.values()) {
         var0.add(var2);
      }

      return var0;
   }

   public static Trait getTrait(String var0) {
      return TraitMap.containsKey(var0) ? TraitMap.get(var0) : null;
   }

   public static void Reset() {
      TraitMap.clear();
   }
}
