package zombie;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;
import zombie.MapGroups.MapDirectory;
import zombie.core.Translator;
import zombie.modding.ActiveMods;

class MapGroups$MapGroup {
   private LinkedList<MapDirectory> directories;

   private MapGroups$MapGroup(MapGroups var1) {
      this.this$0 = var1;
      this.directories = new LinkedList<>();
   }

   void addDirectory(String var1, String var2) {
      if (!$assertionsDisabled && this.hasDirectory(var1)) {
         throw new AssertionError();
      } else {
         MapDirectory var3 = new MapDirectory(this.this$0, var1, var2);
         this.directories.add(var3);
      }
   }

   void addDirectory(String var1, String var2, ArrayList<String> var3) {
      if (!$assertionsDisabled && this.hasDirectory(var1)) {
         throw new AssertionError();
      } else {
         MapDirectory var4 = new MapDirectory(this.this$0, var1, var2, var3);
         this.directories.add(var4);
      }
   }

   void addDirectory(MapDirectory var1) {
      if (!$assertionsDisabled && this.hasDirectory(var1.name)) {
         throw new AssertionError();
      } else {
         this.directories.add(var1);
      }
   }

   MapDirectory getDirectoryByName(String var1) {
      for (MapDirectory var3 : this.directories) {
         if (var3.name.equals(var1)) {
            return var3;
         }
      }

      return null;
   }

   boolean hasDirectory(String var1) {
      return this.getDirectoryByName(var1) != null;
   }

   boolean hasAnyOfTheseDirectories(ArrayList<MapDirectory> var1) {
      for (MapDirectory var3 : var1) {
         if (this.directories.contains(var3)) {
            return true;
         }
      }

      return false;
   }

   boolean isReferencedByOtherMaps(MapDirectory var1) {
      for (MapDirectory var3 : this.directories) {
         if (var1 != var3 && var3.lotDirs.contains(var1.name)) {
            return true;
         }
      }

      return false;
   }

   void getDirsRecursively(MapDirectory var1, ArrayList<String> var2) {
      if (!var2.contains(var1.name)) {
         var2.add(var1.name);

         for (String var4 : var1.lotDirs) {
            MapDirectory var5 = this.getDirectoryByName(var4);
            if (var5 != null) {
               this.getDirsRecursively(var5, var2);
            }
         }
      }
   }

   void setPriority() {
      for (MapDirectory var3 : new ArrayList<>(this.directories)) {
         if (!this.isReferencedByOtherMaps(var3)) {
            ArrayList var4 = new ArrayList();
            this.getDirsRecursively(var3, var4);
            this.setPriority(var4);
         }
      }
   }

   void setPriority(List<String> var1) {
      ArrayList var2 = new ArrayList(var1.size());

      for (String var4 : var1) {
         if (this.hasDirectory(var4)) {
            var2.add(this.getDirectoryByName(var4));
         }
      }

      for (int var5 = 0; var5 < this.directories.size(); var5++) {
         MapDirectory var6 = this.directories.get(var5);
         if (var1.contains(var6.name)) {
            this.directories.set(var5, (MapDirectory)var2.remove(0));
         }
      }
   }

   void setOrder(ActiveMods var1) {
      if (!var1.getMapOrder().isEmpty()) {
         this.setPriority(var1.getMapOrder());
      }
   }

   boolean checkMapConflicts() {
      HashMap var1 = new HashMap();
      ArrayList var2 = new ArrayList();

      for (MapDirectory var4 : this.directories) {
         var4.conflicts.clear();
         var2.clear();
         var4.getLotHeaders(var2);

         for (String var6 : var2) {
            if (!var1.containsKey(var6)) {
               var1.put(var6, new ArrayList());
            }

            ((ArrayList)var1.get(var6)).add(var4.name);
         }
      }

      boolean var11 = false;

      for (String var13 : var1.keySet()) {
         ArrayList var14 = (ArrayList)var1.get(var13);
         if (var14.size() > 1) {
            for (int var7 = 0; var7 < var14.size(); var7++) {
               MapDirectory var8 = this.getDirectoryByName((String)var14.get(var7));

               for (int var9 = 0; var9 < var14.size(); var9++) {
                  if (var7 != var9) {
                     String var10 = Translator.getText("UI_MapConflict", var8.name, var14.get(var9), var13);
                     var8.conflicts.add(var10);
                     var11 = true;
                  }
               }
            }
         }
      }

      return var11;
   }
}
