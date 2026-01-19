#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <fstream>
#include <iostream>

namespace zombie {


class MapGroups {
:
    std::string name;
    std::string path;
   ArrayList<String> lotDirs;
   ArrayList<String> conflicts;

    MapGroups$MapDirectory(MapGroups var1, String var2, String var3) {
      this.this$0 = var1;
      this.lotDirs = std::make_unique<ArrayList<>>();
      this.conflicts = std::make_unique<ArrayList<>>();
      this.name = var2;
      this.path = var3;
   }

    MapGroups$MapDirectory(String var1, String var2, ArrayList<String> var3, ArrayList var4) {
      this.this$0 = var1;
      this.lotDirs = std::make_unique<ArrayList<>>();
      this.conflicts = std::make_unique<ArrayList<>>();
      this.name = var2;
      this.path = var3;
      this.lotDirs.addAll(var4);
   }

    void getLotHeaders(ArrayList<String> var1) {
    File var2 = new File(this.path);
      if (var2.isDirectory()) {
         String[] var3 = var2.list();
         if (var3 != nullptr) {
            for (int var4 = 0; var4 < var3.length; var4++) {
               if (var3[var4].endsWith(".lotheader")) {
                  var1.add(var3[var4]);
               }
            }
         }
      }
   }
}
} // namespace zombie
