#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/MapGroups/MapDirectory.h"
#include "zombie/core/Translator.h"
#include "zombie/modding/ActiveMods.h"
#include <algorithm>

namespace zombie {


class MapGroups {
public:
   private LinkedList<MapDirectory> directories;

   private MapGroups$MapGroup(MapGroups var1) {
      this.this$0 = var1;
      this.directories = std::make_unique<LinkedList<>>();
   }

    void addDirectory(const std::string& var1, const std::string& var2) {
      if (!$assertionsDisabled && this.hasDirectory(var1)) {
         throw std::make_unique<AssertionError>();
      } else {
    auto var3 = std::make_shared<MapDirectory>(this.this$0, var1, var2);
         this.directories.add(var3);
      }
   }

    void addDirectory(const std::string& var1, const std::string& var2, ArrayList<String> var3) {
      if (!$assertionsDisabled && this.hasDirectory(var1)) {
         throw std::make_unique<AssertionError>();
      } else {
    auto var4 = std::make_shared<MapDirectory>(this.this$0, var1, var2, var3);
         this.directories.add(var4);
      }
   }

    void addDirectory(MapDirectory var1) {
      if (!$assertionsDisabled && this.hasDirectory(var1.name)) {
         throw std::make_unique<AssertionError>();
      } else {
         this.directories.add(var1);
      }
   }

    MapDirectory getDirectoryByName(const std::string& var1) {
      for (MapDirectory var3 : this.directories) {
         if (var3.name == var1)) {
    return var3;
         }
      }

    return null;
   }

    bool hasDirectory(const std::string& var1) {
      return this.getDirectoryByName(var1) != nullptr;
   }

    bool hasAnyOfTheseDirectories(ArrayList<MapDirectory> var1) {
    for (auto& var3 : var1)         if (this.directories.contains(var3)) {
    return true;
         }
      }

    return false;
   }

    bool isReferencedByOtherMaps(MapDirectory var1) {
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
            if (var5 != nullptr) {
               this.getDirsRecursively(var5, var2);
            }
         }
      }
   }

    void setPriority() {
      for (MapDirectory var3 : new ArrayList<>(this.directories)) {
         if (!this.isReferencedByOtherMaps(var3)) {
    std::vector var4 = new ArrayList();
            this.getDirsRecursively(var3, var4);
            this.setPriority(var4);
         }
      }
   }

    void setPriority(List<String> var1) {
    std::vector var2 = new ArrayList(var1.size());

    for (auto& var4 : var1)         if (this.hasDirectory(var4)) {
            var2.add(this.getDirectoryByName(var4));
         }
      }

      for (int var5 = 0; var5 < this.directories.size(); var5++) {
    MapDirectory var6 = this.directories.get(var5);
         if (var1.contains(var6.name)) {
            this.directories.set(var5, static_cast<MapDirectory>(var2).remove(0));
         }
      }
   }

    void setOrder(ActiveMods var1) {
      if (!var1.getMapOrder().isEmpty()) {
         this.setPriority(var1.getMapOrder());
      }
   }

    bool checkMapConflicts() {
    std::unordered_map var1 = new HashMap();
    std::vector var2 = new ArrayList();

      for (MapDirectory var4 : this.directories) {
         var4.conflicts.clear();
         var2.clear();
         var4.getLotHeaders(var2);

    for (auto& var6 : var2)            if (!var1.containsKey(var6)) {
               var1.put(var6, std::make_unique<ArrayList>());
            }

            (static_cast<ArrayList>(var1).get(var6)).add(var4.name);
         }
      }

    bool var11 = false;

      for (String var13 : var1.keySet()) {
    std::vector var14 = static_cast<ArrayList>(var1).get(var13);
         if (var14.size() > 1) {
            for (int var7 = 0; var7 < var14.size(); var7++) {
    MapDirectory var8 = this.getDirectoryByName(static_cast<String>(var14).get(var7));

               for (int var9 = 0; var9 < var14.size(); var9++) {
                  if (var7 != var9) {
    std::string var10 = Translator.getText("UI_MapConflict", var8.name, var14.get(var9), var13);
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
} // namespace zombie
