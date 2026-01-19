package zombie.core;

import java.util.ArrayList;
import java.util.HashMap;

final class Translator$News {
   String version;
   final ArrayList<String> sectionNames = new ArrayList<>();
   final HashMap<String, ArrayList<String>> sectionLists = new HashMap<>();

   Translator$News(String var1) {
      this.version = var1;
   }

   ArrayList<String> getOrCreateSectionList(String var1) {
      if (this.sectionNames.contains(var1)) {
         return this.sectionLists.get(var1);
      } else {
         this.sectionNames.add(var1);
         ArrayList var2 = new ArrayList();
         this.sectionLists.put(var1, var2);
         return var2;
      }
   }

   String toRichText() {
      StringBuilder var1 = new StringBuilder("");

      for (String var3 : this.sectionNames) {
         ArrayList var4 = this.sectionLists.get(var3);
         if (!var4.isEmpty()) {
            var1.append("<LINE> <LEFT> <SIZE:medium> %s <LINE> <LINE> ".formatted(var3));

            for (String var6 : var4) {
               var1.append(var6);
            }
         }
      }

      return var1.toString();
   }
}
