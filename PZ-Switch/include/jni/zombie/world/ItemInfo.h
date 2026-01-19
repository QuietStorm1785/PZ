#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameWindow.h"
#include "zombie/core/utils/Bits.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/scripting/objects/Item.h"
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace world {


class ItemInfo {
:
    std::string itemName;
    std::string moduleName;
    std::string fullType;
    short registryID;
    bool existsAsVanilla = false;
    bool isModded = false;
    std::string modID;
    bool obsolete = false;
    bool removed = false;
    bool isLoaded = false;
   protected List<String> modOverrides;
    Item scriptItem;

    std::string getFullType() const {
      return this.fullType;
   }

    short getRegistryID() const {
      return this.registryID;
   }

    bool isExistsAsVanilla() {
      return this.existsAsVanilla;
   }

    bool isModded() {
      return this.isModded;
   }

    std::string getModID() const {
      return this.modID;
   }

    bool isObsolete() {
      return this.obsolete;
   }

    bool isRemoved() {
      return this.removed;
   }

    bool isLoaded() {
      return this.isLoaded;
   }

    Item getScriptItem() const {
      return this.scriptItem;
   }

    List<String> getModOverrides() {
      return this.modOverrides;
   }

    ItemInfo copy() {
    ItemInfo var1 = new ItemInfo();
      var1.fullType = this.fullType;
      var1.registryID = this.registryID;
      var1.existsAsVanilla = this.existsAsVanilla;
      var1.isModded = this.isModded;
      var1.modID = this.modID;
      var1.obsolete = this.obsolete;
      var1.removed = this.removed;
      var1.isLoaded = this.isLoaded;
      var1.scriptItem = this.scriptItem;
      if (this.modOverrides != nullptr) {
         var1.modOverrides = std::make_unique<ArrayList<>>();
         var1.modOverrides.addAll(this.modOverrides);
      }

    return var1;
   }

    bool isValid() {
      return !this.obsolete && !this.removed && this.isLoaded;
   }

    void DebugPrint() {
      DebugLog.log(this.GetDebugString());
   }

    std::string GetDebugString() {
      String var1 = "=== Dictionary Item Debug Print ===\nregistryID = "
         + this.registryID
         + ",\nfulltype = \""
         + this.fullType
         + "\",\nmodID = \""
         + this.modID
         + "\",\nexistsAsVanilla = "
         + this.existsAsVanilla
         + ",\nisModded = "
         + this.isModded
         + ",\nobsolete = "
         + this.obsolete
         + ",\nremoved = "
         + this.removed
         + ",\nisModdedOverride = "
         + (this.modOverrides != nullptr ? this.modOverrides.size() : 0)
         + ",\n";
      if (this.modOverrides != nullptr) {
         var1 = var1 + "modOverrides = { ";
         if (this.existsAsVanilla) {
            var1 = var1 + "PZ-Vanilla, ";
         }

         for (int var2 = 0; var2 < this.modOverrides.size(); var2++) {
            var1 = var1 + "\"" + this.modOverrides.get(var2) + "\"";
            if (var2 < this.modOverrides.size() - 1) {
               var1 = var1 + ", ";
            }
         }

         var1 = var1 + " },\n";
      }

      return var1 + "===================================\n";
   }

    std::string ToString() {
      return "registryID = "
         + this.registryID
         + ",fulltype = \""
         + this.fullType
         + "\",modID = \""
         + this.modID
         + "\",existsAsVanilla = "
         + this.existsAsVanilla
         + ",isModded = "
         + this.isModded
         + ",obsolete = "
         + this.obsolete
         + ",removed = "
         + this.removed
         + ",modOverrides = "
         + (this.modOverrides != nullptr ? this.modOverrides.size() : 0)
         + ",";
   }

    void saveAsText(FileWriter var1, const std::string& var2) {
      var1.write(var2 + "registryID = " + this.registryID + "," + System.lineSeparator());
      var1.write(var2 + "fulltype = \"" + this.fullType + "\"," + System.lineSeparator());
      var1.write(var2 + "modID = \"" + this.modID + "\"," + System.lineSeparator());
      var1.write(var2 + "existsAsVanilla = " + this.existsAsVanilla + "," + System.lineSeparator());
      var1.write(var2 + "isModded = " + this.isModded + "," + System.lineSeparator());
      var1.write(var2 + "obsolete = " + this.obsolete + "," + System.lineSeparator());
      var1.write(var2 + "removed = " + this.removed + "," + System.lineSeparator());
      if (this.modOverrides != nullptr) {
    std::string var3 = "modOverrides = { ";

         for (int var4 = 0; var4 < this.modOverrides.size(); var4++) {
            var3 = var3 + "\"" + this.modOverrides.get(var4) + "\"";
            if (var4 < this.modOverrides.size() - 1) {
               var3 = var3 + ", ";
            }
         }

         var3 = var3 + " },";
         var1.write(var2 + var3 + System.lineSeparator());
      }
   }

    void save(ByteBuffer var1, List<String> var2, List<String> var3) {
      var1.putShort(this.registryID);
      if (var3.size() > 127) {
         var1.putShort((short)var3.indexOf(this.moduleName));
      } else {
         var1.put((byte)var3.indexOf(this.moduleName));
      }

      GameWindow.WriteString(var1, this.itemName);
    uint8_t var4 = 0;
    int var5 = var1.position();
      var1.put((byte)0);
      if (this.isModded) {
         var4 = Bits.addFlags(var4, 1);
         if (var2.size() > 127) {
            var1.putShort((short)var2.indexOf(this.modID));
         } else {
            var1.put((byte)var2.indexOf(this.modID));
         }
      }

      if (this.existsAsVanilla) {
         var4 = Bits.addFlags(var4, 2);
      }

      if (this.obsolete) {
         var4 = Bits.addFlags(var4, 4);
      }

      if (this.removed) {
         var4 = Bits.addFlags(var4, 8);
      }

      if (this.modOverrides != nullptr) {
         var4 = Bits.addFlags(var4, 16);
         if (this.modOverrides.size() == 1) {
            if (var2.size() > 127) {
               var1.putShort((short)var2.indexOf(this.modOverrides.get(0)));
            } else {
               var1.put((byte)var2.indexOf(this.modOverrides.get(0)));
            }
         } else {
            var4 = Bits.addFlags(var4, 32);
            var1.put((byte)this.modOverrides.size());

            for (int var6 = 0; var6 < this.modOverrides.size(); var6++) {
               if (var2.size() > 127) {
                  var1.putShort((short)var2.indexOf(this.modOverrides.get(var6)));
               } else {
                  var1.put((byte)var2.indexOf(this.modOverrides.get(var6)));
               }
            }
         }
      }

    int var7 = var1.position();
      var1.position(var5);
      var1.put(var4);
      var1.position(var7);
   }

    void load(ByteBuffer var1, int var2, List<String> var3, List<String> var4) {
      this.registryID = var1.getShort();
      this.moduleName = (String)var4.get(var4.size() > 127 ? var1.getShort() : var1.get());
      this.itemName = GameWindow.ReadString(var1);
      this.fullType = this.moduleName + "." + this.itemName;
    uint8_t var5 = var1.get();
      if (Bits.hasFlags(var5, 1)) {
         this.modID = (String)var3.get(var3.size() > 127 ? var1.getShort() : var1.get());
         this.isModded = true;
      } else {
         this.modID = "pz-vanilla";
         this.isModded = false;
      }

      this.existsAsVanilla = Bits.hasFlags(var5, 2);
      this.obsolete = Bits.hasFlags(var5, 4);
      this.removed = Bits.hasFlags(var5, 8);
      if (Bits.hasFlags(var5, 16)) {
         if (this.modOverrides == nullptr) {
            this.modOverrides = std::make_unique<ArrayList<>>();
         }

         this.modOverrides.clear();
         if (!Bits.hasFlags(var5, 32)) {
            this.modOverrides.add((String)var3.get(var3.size() > 127 ? var1.getShort() : var1.get()));
         } else {
    uint8_t var6 = var1.get();

            for (int var7 = 0; var7 < var6; var7++) {
               this.modOverrides.add((String)var3.get(var3.size() > 127 ? var1.getShort() : var1.get()));
            }
         }
      }
   }
}
} // namespace world
} // namespace zombie
