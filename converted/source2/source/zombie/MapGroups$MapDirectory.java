package zombie;

import java.io.File;
import java.util.ArrayList;

class MapGroups$MapDirectory {
   String name;
   String path;
   ArrayList<String> lotDirs;
   ArrayList<String> conflicts;

   public MapGroups$MapDirectory(MapGroups var1, String var2, String var3) {
      this.this$0 = var1;
      this.lotDirs = new ArrayList<>();
      this.conflicts = new ArrayList<>();
      this.name = var2;
      this.path = var3;
   }

   public MapGroups$MapDirectory(String var1, String var2, ArrayList<String> var3, ArrayList var4) {
      this.this$0 = var1;
      this.lotDirs = new ArrayList<>();
      this.conflicts = new ArrayList<>();
      this.name = var2;
      this.path = var3;
      this.lotDirs.addAll(var4);
   }

   public void getLotHeaders(ArrayList<String> var1) {
      File var2 = new File(this.path);
      if (var2.isDirectory()) {
         String[] var3 = var2.list();
         if (var3 != null) {
            for (int var4 = 0; var4 < var3.length; var4++) {
               if (var3[var4].endsWith(".lotheader")) {
                  var1.add(var3[var4]);
               }
            }
         }
      }
   }
}
