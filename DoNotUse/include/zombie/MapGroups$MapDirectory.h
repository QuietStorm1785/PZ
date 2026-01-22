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
public:
    std::string name;
    std::string path;
   std::vector<std::string> lotDirs;
   std::vector<std::string> conflicts;

   public MapGroups$MapDirectory(MapGroups var1, std::string var2, std::string var3) {
      this.this$0 = var1;
      this.lotDirs = std::make_unique<std::vector<>>();
      this.conflicts = std::make_unique<std::vector<>>();
      this.name = var2;
      this.path = var3;
   }

   public MapGroups$MapDirectory(std::string var1, std::string var2, std::vector<std::string> var3, std::vector var4) {
      this.this$0 = var1;
      this.lotDirs = std::make_unique<std::vector<>>();
      this.conflicts = std::make_unique<std::vector<>>();
      this.name = var2;
      this.path = var3;
      this.lotDirs.addAll(var4);
   }

    void getLotHeaders(std::vector<std::string> var1) {
    File var2 = std::make_shared<File>(this.path);
      if (var2.isDirectory()) {
         std::string[] var3 = var2.list();
         if (var3 != nullptr) {
            for (int var4 = 0; var4 < var3.length; var4++) {
               if (var3[var4].endsWith(".lotheader")) {
                  var1.push_back(var3[var4]);
               }
            }
         }
      }
   }
}
} // namespace zombie
