package zombie.characters.professions;

import java.util.ArrayList;
import java.util.LinkedHashMap;
import zombie.characters.professions.ProfessionFactory.Profession;

public final class ProfessionFactory {
   public static LinkedHashMap<String, Profession> ProfessionMap = new LinkedHashMap<>();

   public static void init() {
   }

   public static Profession addProfession(String var0, String var1, String var2, int var3) {
      Profession var4 = new Profession(var0, var1, var2, var3, "");
      ProfessionMap.put(var0, var4);
      return var4;
   }

   public static Profession getProfession(String var0) {
      for (Profession var2 : ProfessionMap.values()) {
         if (var2.type.equals(var0)) {
            return var2;
         }
      }

      return null;
   }

   public static ArrayList<Profession> getProfessions() {
      ArrayList var0 = new ArrayList();

      for (Profession var2 : ProfessionMap.values()) {
         var0.add(var2);
      }

      return var0;
   }

   public static void Reset() {
      ProfessionMap.clear();
   }
}
