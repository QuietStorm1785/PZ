#pragma once
#include "se/krka/kahlua/j2se/KahluaTableImpl.h"
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "se/krka/kahlua/vm/KahluaTableIterator.h"
#include "zombie/GameWindow.h"
#include "zombie/Lua/LuaManager.h"
#include "zombie/inventory/InventoryItem.h"
#include "zombie/iso/IsoDirections.h"
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace network {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class TableNetworkUtils {
public:
  static const uint8_t SBYT_NO_SAVE = -1;
  static const uint8_t SBYT_STRING = 0;
  static const uint8_t SBYT_DOUBLE = 1;
  static const uint8_t SBYT_TABLE = 2;
  static const uint8_t SBYT_BOOLEAN = 3;
  static const uint8_t SBYT_ITEM = 4;
  static const uint8_t SBYT_DIRECTION = 5;

  static void save(KahluaTable table, ByteBuffer byteBuffer) {
    KahluaTableIterator kahluaTableIterator = table.iterator();
    int int0 = 0;

    while (kahluaTableIterator.advance()) {
      if (canSave(kahluaTableIterator.getKey(),
                  kahluaTableIterator.getValue())) {
        int0++;
      }
    }

    kahluaTableIterator = table.iterator();
    byteBuffer.putInt(int0);

    while (kahluaTableIterator.advance()) {
      uint8_t byte0 = getKeyByte(kahluaTableIterator.getKey());
      uint8_t byte1 = getValueByte(kahluaTableIterator.getValue());
      if (byte0 != -1 && byte1 != -1) {
        save(byteBuffer, byte0, kahluaTableIterator.getKey());
        save(byteBuffer, byte1, kahluaTableIterator.getValue());
      }
    }
  }

    static void saveSome(KahluaTable table, ByteBuffer byteBuffer, HashSet<? extends) {
      KahluaTableIterator kahluaTableIterator = table.iterator();
      int int0 = 0;

      while (kahluaTableIterator.advance()) {
        if (hashSet.contains(kahluaTableIterator.getKey()) &&
            canSave(kahluaTableIterator.getKey(),
                    kahluaTableIterator.getValue())) {
          int0++;
        }
      }

      kahluaTableIterator = table.iterator();
      byteBuffer.putInt(int0);

      while (kahluaTableIterator.advance()) {
        if (hashSet.contains(kahluaTableIterator.getKey())) {
          uint8_t byte0 = getKeyByte(kahluaTableIterator.getKey());
          uint8_t byte1 = getValueByte(kahluaTableIterator.getValue());
          if (byte0 != -1 && byte1 != -1) {
            save(byteBuffer, byte0, kahluaTableIterator.getKey());
            save(byteBuffer, byte1, kahluaTableIterator.getValue());
          }
        }
      }
    }

    static void save(ByteBuffer byteBuffer, uint8_t byte0, void *object) {
      byteBuffer.put(byte0);
      if (byte0 == 0) {
        GameWindow.WriteString(byteBuffer, (String)object);
      } else if (byte0 == 1) {
        byteBuffer.putDouble((Double)object);
      } else if (byte0 == 3) {
        byteBuffer.put((byte)((Boolean)object ? 1 : 0));
      } else if (byte0 == 2) {
        save((KahluaTable)object, byteBuffer);
      } else if (byte0 == 4) {
        ((InventoryItem)object).saveWithSize(byteBuffer, false);
      } else {
        if (byte0 != 5) {
          throw new RuntimeException("invalid lua table type " + byte0);
        }

        byteBuffer.put((byte)((IsoDirections)object).index());
      }
    }

    static void load(KahluaTable table, ByteBuffer byteBuffer) {
      int int0 = byteBuffer.getInt();
      table.wipe();

      for (int int1 = 0; int1 < int0; int1++) {
        uint8_t byte0 = byteBuffer.get();
        void *object0 = load(byteBuffer, byte0);
        uint8_t byte1 = byteBuffer.get();
        void *object1 = load(byteBuffer, byte1);
        table.rawset(object0, object1);
      }
    }

    static void *load(ByteBuffer byteBuffer, uint8_t byte0) {
      if (byte0 == 0) {
        return GameWindow.ReadString(byteBuffer);
      } else if (byte0 == 1) {
        return byteBuffer.getDouble();
      } else if (byte0 == 3) {
        return byteBuffer.get() == 1;
      } else if (byte0 == 2) {
        KahluaTableImpl kahluaTableImpl =
            (KahluaTableImpl)LuaManager.platform.newTable();
        load(kahluaTableImpl, byteBuffer);
        return kahluaTableImpl;
      } else if (byte0 == 4) {
        InventoryItem item = null;

        try {
          item = InventoryItem.loadItem(byteBuffer, 195);
        } catch (Exception exception) {
          exception.printStackTrace();
        }

        return item;
      } else if (byte0 == 5) {
        return IsoDirections.fromIndex(byteBuffer.get());
      } else {
        throw new RuntimeException("invalid lua table type " + byte0);
      }
    }

    static uint8_t getKeyByte(void *object) {
      if (object instanceof String) {
        return 0;
      } else {
        return (byte)(object instanceof Double ? 1 : -1);
      }
    }

    static uint8_t getValueByte(void *object) {
      if (object instanceof String) {
        return 0;
      } else if (object instanceof Double) {
        return 1;
      } else if (object instanceof Boolean) {
        return 3;
      } else if (object instanceof KahluaTableImpl) {
        return 2;
      } else if (object instanceof InventoryItem) {
        return 4;
      } else {
        return (byte)(object instanceof IsoDirections ? 5 : -1);
      }
    }

    static bool canSave(void *object1, void *object0) { return getKeyByte(); }
}
} // namespace network
} // namespace zombie
