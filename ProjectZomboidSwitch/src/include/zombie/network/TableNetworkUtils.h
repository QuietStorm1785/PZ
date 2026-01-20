#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "se/krka/kahlua/j2se/KahluaTableImpl.h"
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "se/krka/kahlua/vm/KahluaTableIterator.h"
#include "zombie/GameWindow.h"
#include "zombie/Lua/LuaManager.h"
#include "zombie/inventory/InventoryItem.h"
#include "zombie/iso/IsoDirections.h"
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace network {


class TableNetworkUtils {
public:
    static const uint8_t SBYT_NO_SAVE = -1;
    static const uint8_t SBYT_STRING = 0;
    static const uint8_t SBYT_DOUBLE = 1;
    static const uint8_t SBYT_TABLE = 2;
    static const uint8_t SBYT_BOOLEAN = 3;
    static const uint8_t SBYT_ITEM = 4;
    static const uint8_t SBYT_DIRECTION = 5;

    static void save(KahluaTable var0, ByteBuffer var1) {
    KahluaTableIterator var2 = var0.iterator();
    int var3 = 0;

      while (var2.advance()) {
         if (canSave(var2.getKey(), var2.getValue())) {
            var3++;
         }
      }

      var2 = var0.iterator();
      var1.putInt(var3);

      while (var2.advance()) {
    uint8_t var4 = getKeyByte(var2.getKey());
    uint8_t var5 = getValueByte(var2.getValue());
         if (var4 != -1 && var5 != -1) {
            save(var1, var4, var2.getKey());
            save(var1, var5, var2.getValue());
         }
      }
   }

    static void saveSome(KahluaTable var0, ByteBuffer var1, std::unordered_set<? extends) {
    KahluaTableIterator var3 = var0.iterator();
    int var4 = 0;

      while (var3.advance()) {
         if (var2.contains(var3.getKey()) && canSave(var3.getKey(), var3.getValue())) {
            var4++;
         }
      }

      var3 = var0.iterator();
      var1.putInt(var4);

      while (var3.advance()) {
         if (var2.contains(var3.getKey())) {
    uint8_t var5 = getKeyByte(var3.getKey());
    uint8_t var6 = getValueByte(var3.getValue());
            if (var5 != -1 && var6 != -1) {
               save(var1, var5, var3.getKey());
               save(var1, var6, var3.getValue());
            }
         }
      }
   }

    static void save(ByteBuffer var0, uint8_t var1, void* var2) {
      var0.put(var1);
      if (var1 == 0) {
         GameWindow.WriteString(var0, (std::string)var2);
      } else if (var1 == 1) {
         var0.putDouble((double)var2);
      } else if (var1 == 3) {
         var0.put((byte)((bool)var2 ? 1 : 0));
      } else if (var1 == 2) {
         save((KahluaTable)var2, var0);
      } else if (var1 == 4) {
         ((InventoryItem)var2).saveWithSize(var0, false);
      } else {
         if (var1 != 5) {
            throw RuntimeException("invalid lua table type " + var1);
         }

         var0.put((byte)((IsoDirections)var2).index());
      }
   }

    static void load(KahluaTable var0, ByteBuffer var1) {
    int var2 = var1.getInt();
      var0.wipe();

      for (int var3 = 0; var3 < var2; var3++) {
    uint8_t var4 = var1.get();
    void* var5 = load(var1, var4);
    uint8_t var6 = var1.get();
    void* var7 = load(var1, var6);
         var0.rawset(var5, var7);
      }
   }

    static void* load(ByteBuffer var0, uint8_t var1) {
      if (var1 == 0) {
         return GameWindow.ReadString(var0);
      } else if (var1 == 1) {
         return var0.getDouble();
      } else if (var1 == 3) {
         return var0.get() == 1;
      } else if (var1 == 2) {
    KahluaTableImpl var5 = (KahluaTableImpl)LuaManager.platform.newTable();
         load(var5, var0);
    return var5;
      } else if (var1 == 4) {
    InventoryItem var2 = nullptr;

         try {
            var2 = InventoryItem.loadItem(var0, 195);
         } catch (Exception var4) {
            var4.printStackTrace();
         }

    return var2;
      } else if (var1 == 5) {
         return IsoDirections.fromIndex(var0.get());
      } else {
         throw RuntimeException("invalid lua table type " + var1);
      }
   }

    static uint8_t getKeyByte(void* var0) {
      if (dynamic_cast<std*>(var0) != nullptr::string) {
    return 0;
      } else {
         return (byte)(dynamic_cast<double*>(var0) != nullptr ? 1 : -1);
      }
   }

    static uint8_t getValueByte(void* var0) {
      if (dynamic_cast<std*>(var0) != nullptr::string) {
    return 0;
      } else if (dynamic_cast<double*>(var0) != nullptr) {
    return 1;
      } else if (dynamic_cast<bool*>(var0) != nullptr) {
    return 3;
      } else if (dynamic_cast<KahluaTableImpl*>(var0) != nullptr) {
    return 2;
      } else if (dynamic_cast<InventoryItem*>(var0) != nullptr) {
    return 4;
      } else {
         return (byte)(dynamic_cast<IsoDirections*>(var0) != nullptr ? 5 : -1);
      }
   }

    static bool canSave(void* var0, void* var1) {
    return getKeyByte();
   }
}
} // namespace network
} // namespace zombie
