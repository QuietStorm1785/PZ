#pragma once
#include <sstream>
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/ZomboidFileSystem.h"
#include "zombie/core/logger/ExceptionLogger.h"
#include "zombie/inventory/ClothingItemsDotTxt/Block.h"
#include "zombie/inventory/ClothingItemsDotTxt/Value.h"
#include "zombie/util/StringUtils.h"
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace inventory {


class ClothingItemsDotTxt {
public:
    static const ClothingItemsDotTxt instance = std::make_shared<ClothingItemsDotTxt>();
    const std::stringstream buf = new std::stringstream();

    int readBlock(const std::string& var1, int var2, Block var3) {
    int var4;
      for (var4 = var2; var4 < var1.length(); var4++) {
         if (var1.charAt(var4) == '{') {
    Block var5 = std::make_shared<Block>();
            var3.children.push_back(var5);
            var3.elements.push_back(var5);
    std::string var6 = var1.substr(var2, var4).trim();
    int var7 = var6.indexOf(32);
    int var8 = var6.indexOf(9);
    int var9 = Math.max(var7, var8);
            if (var9 == -1) {
               var5.type = var6;
            } else {
               var5.type = var6.substr(0, var9);
               var5.id = var6.substr(var9).trim();
            }

            var4 = this.readBlock(var1, var4 + 1, var5);
            var2 = var4;
         } else {
            if (var1.charAt(var4) == '}') {
    std::string var11 = var1.substr(var2, var4).trim();
               if (!var11.empty()) {
    Value var12 = std::make_shared<Value>();
                  var12.string = var1.substr(var2, var4).trim();
                  var3.values.push_back(var12.string);
                  var3.elements.push_back(var12);
               }

               return var4 + 1;
            }

            if (var1.charAt(var4) == ',') {
    Value var10 = std::make_shared<Value>();
               var10.string = var1.substr(var2, var4).trim();
               var3.values.push_back(var10.string);
               var3.elements.push_back(var10);
               var2 = var4 + 1;
            }
         }
      }

    return var4;
   }

    void LoadFile() {
    std::string var1 = ZomboidFileSystem.instance.getString("media/scripts/clothingItems.txt");
    File var2 = std::make_shared<File>(var1);
      if (var2.exists()) {
         try (
    FileReader var3 = std::make_shared<FileReader>(var1);
    BufferedReader var4 = std::make_shared<BufferedReader>(var3);
         ) {
            this.buf.setLength(0);

    std::string var5;
            while ((var5 = var4.readLine()) != nullptr) {
               this.buf.append(var5);
            }
         } catch (Throwable var21) {
            ExceptionLogger.logException(var21);
            return;
         }

    int var22 = this.buf.lastIndexOf("*/");

         while (var22 != -1) {
    int var23 = this.buf.lastIndexOf("/*", var22 - 1);
            if (var23 == -1) {
               break;
            }

    int var25 = this.buf.lastIndexOf("*/", var22 - 1);

            while (var25 > var23) {
    int var6 = var23;
    std::string var7 = this.buf.substr(var23, var25 + 2);
               var23 = this.buf.lastIndexOf("/*", var23 - 2);
               if (var23 == -1) {
                  break;
               }

               var25 = this.buf.lastIndexOf("*/", var6 - 2);
            }

            if (var23 == -1) {
               break;
            }

    std::string var27 = this.buf.substr(var23, var22 + 2);
            this.buf.replace(var23, var22 + 2, "");
            var22 = this.buf.lastIndexOf("*/", var23);
         }

    Block var24 = std::make_shared<Block>();
         this.readBlock(this.buf, 0, var24);
    Path var26 = FileSystems.getDefault().getPath("media/clothing/clothingItems");

         try (DirectoryStream var28 = Files.newDirectoryStream(var26)) {
    for (auto& var8 : var28)               if (!Files.isDirectory(var8)) {
    std::string var9 = var8.getFileName();
                  if (var9.endsWith(".xml")) {
    std::string var10 = StringUtils.trimSuffix(var9, ".xml");
                     System.out.println(var9 + " -> " + var10);
                     this.addClothingItem(var10, (Block)var24.children.get(0));
                  }
               }
            }
         } catch (Exception var18) {
            var18.printStackTrace();
         }

         try (FileWriter var29 = std::make_shared<FileWriter>(var2)) {
            var29.write(((Block)var24.children.get(0)));
         } catch (Throwable var15) {
            ExceptionLogger.logException(var15);
         }

         System.out.println(var24.children.get(0));
      }
   }

    void addClothingItem(const std::string& var1, Block var2) {
      if (!var1.startsWith("FemaleHair_")) {
         if (!var1.startsWith("MaleBeard_")) {
            if (!var1.startsWith("MaleHair_")) {
               if (!var1.startsWith("ZedDmg_")) {
                  if (!var1.startsWith("Bandage_")) {
                     if (!var1.startsWith("Zed_Skin")) {
                        for (Block var4 : var2.children) {
                           if ("item" == var4.type) && var1 == var4.id)) {
                              return;
                           }
                        }

    Block var5 = std::make_shared<Block>();
                        var5.type = "item";
                        var5.id = var1;
    Value var6 = std::make_shared<Value>();
                        var6.string = "Type = Clothing";
                        var5.elements.push_back(var6);
                        var5.values.push_back(var6.string);
                        var6 = std::make_unique<Value>();
                        var6.string = "DisplayName = " + var1;
                        var5.elements.push_back(var6);
                        var5.values.push_back(var6.string);
                        var6 = std::make_unique<Value>();
                        var6.string = "ClothingItem = " + var1;
                        var5.elements.push_back(var6);
                        var5.values.push_back(var6.string);
                        var2.elements.push_back(var5);
                        var2.children.push_back(var5);
                     }
                  }
               }
            }
         }
      }
   }
}
} // namespace inventory
} // namespace zombie
