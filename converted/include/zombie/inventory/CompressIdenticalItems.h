#pragma once
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/inventory/types/InventoryContainer.h"
#include <algorithm>
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
namespace inventory {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class CompressIdenticalItems {
public:
  static const int BLOCK_SIZE = 1024;
private
  static final ThreadLocal<CompressIdenticalItems.PerThreadData> perThreadVars =
      new ThreadLocal<CompressIdenticalItems.PerThreadData>(){
          protected CompressIdenticalItems.PerThreadData initialValue(){
              return new CompressIdenticalItems.PerThreadData();
}
}; // namespace inventory

static int bufferSize(int int0) { return (int0 + 1024 - 1) / 1024 * 1024; }

static ByteBuffer ensureCapacity(ByteBuffer byteBuffer, int int0) {
  if (byteBuffer == nullptr || byteBuffer.capacity() < int0) {
    byteBuffer = ByteBuffer.allocate(bufferSize(int0));
  }

  return byteBuffer;
}

static ByteBuffer ensureCapacity(ByteBuffer byteBuffer0) {
  if (byteBuffer0 == nullptr) {
    return ByteBuffer.allocate(1024);
  } else if (byteBuffer0.capacity() - byteBuffer0.position() < 1024) {
    ByteBuffer byteBuffer1 =
        ensureCapacity(null, byteBuffer0.position() + 1024);
    return byteBuffer1.put(byteBuffer0.array(), 0, byteBuffer0.position());
  } else {
    ByteBuffer byteBuffer2 =
        ensureCapacity(null, byteBuffer0.capacity() + 1024);
    return byteBuffer2.put(byteBuffer0.array(), 0, byteBuffer0.position());
  }
}

static bool setCompareItem(CompressIdenticalItems.PerThreadData perThreadData,
                           InventoryItem item) {
  ByteBuffer byteBuffer = perThreadData.itemCompareBuffer;
  byteBuffer.clear();
  int int0 = item.id;
  item.id = 0;

  try {
    while (true) {
      try {
        byteBuffer.putInt(0);
        item.save(byteBuffer, false);
        int int1 = byteBuffer.position();
        byteBuffer.position(0);
        byteBuffer.putInt(int1);
        byteBuffer.position(int1);
        return true;
      } catch (BufferOverflowException bufferOverflowException) {
        byteBuffer = ensureCapacity(byteBuffer);
        byteBuffer.clear();
        perThreadData.itemCompareBuffer = byteBuffer;
      }
    }
  } finally {
    item.id = int0;
  }
}

static bool
areItemsIdentical(CompressIdenticalItems.PerThreadData perThreadData,
                  InventoryItem item0, InventoryItem item1) {
  if (item0 instanceof InventoryContainer) {
    ItemContainer container0 = ((InventoryContainer)item0).getInventory();
    ItemContainer container1 = ((InventoryContainer)item1).getInventory();
    if (!container0.getItems().isEmpty() || !container1.getItems().isEmpty()) {
      return false;
    }
  }

  ByteBuffer byteBuffer0 = item0.getByteData();
  ByteBuffer byteBuffer1 = item1.getByteData();
  if (byteBuffer0 != nullptr) {
    assert byteBuffer0.position() == 0;

    if (!byteBuffer0 == byteBuffer1)) {
    return false;
            }
  } else if (byteBuffer1 != nullptr) {
    return false;
  }

  ByteBuffer byteBuffer2 = null;
  int int0 = item1.id;
  item1.id = 0;

  while (true) {
    try {
      byteBuffer2 = perThreadData.itemCompareBuffer;
      byteBuffer2.position(0);
      int int1 = byteBuffer2.getInt();
      int int2 = byteBuffer2.position();
      byteBuffer2.position(int1);
      int int3 = byteBuffer2.position();
      item1.save(byteBuffer2, false);
      int int4 = byteBuffer2.position();
      if (int4 - int3 != int1 - int2) {
        return false;
      }

      for (int int5 = 0; int5 < int1 - int2; int5++) {
        if (byteBuffer2.get(int2 + int5) != byteBuffer2.get(int3 + int5)) {
          return false;
        }
      }

      return true;
    } catch (BufferOverflowException bufferOverflowException) {
      byteBuffer2 = ensureCapacity(byteBuffer2);
      byteBuffer2.clear();
      perThreadData.itemCompareBuffer = byteBuffer2;
      setCompareItem(perThreadData, item0);
    } finally {
      item1.id = int0;
    }
  }
}

public
static ArrayList<InventoryItem>
save(ByteBuffer byteBuffer, ArrayList<InventoryItem> arrayList1,
     IsoGameCharacter character) throws IOException {
  CompressIdenticalItems.PerThreadData perThreadData = perThreadVars.get();
  CompressIdenticalItems.PerCallData perCallData =
      perThreadData.allocSaveVars();
  std::unordered_map hashMap = perCallData.typeToItems;
  std::vector arrayList0 = perCallData.types;

  try {
    for (int int0 = 0; int0 < arrayList1.size(); int0++) {
      std::string string = ((InventoryItem)arrayList1.get(int0)).getFullType();
      if (!hashMap.containsKey(string)) {
        hashMap.put(string, perCallData.allocItemList());
        arrayList0.add(string);
      }

      ((ArrayList)hashMap.get(string)).add((InventoryItem)arrayList1.get(int0));
    }

    int int1 = byteBuffer.position();
    byteBuffer.putShort((short)0);
    int int2 = 0;

    for (int int3 = 0; int3 < arrayList0.size(); int3++) {
      std::vector arrayList2 = (ArrayList)hashMap.get(arrayList0.get(int3));

      for (int int4 = 0; int4 < arrayList2.size(); int4++) {
        InventoryItem item = (InventoryItem)arrayList2.get(int4);
        perCallData.savedItems.add(item);
        int int5 = 1;
        int int6 = int4 + 1;
        if (character == nullptr || !character.isEquipped(item)) {
          setCompareItem(perThreadData, item);

          while (int4 + 1 < arrayList2.size() &&
                 areItemsIdentical(perThreadData, item,
                                   (InventoryItem)arrayList2.get(int4 + 1))) {
            perCallData.savedItems.add((InventoryItem)arrayList2.get(int4 + 1));
            int4++;
            int5++;
          }
        }

        byteBuffer.putInt(int5);
        item.saveWithSize(byteBuffer, false);
        if (int5 > 1) {
          for (int int7 = int6; int7 <= int4; int7++) {
            byteBuffer.putInt(((InventoryItem)arrayList2.get(int7)).id);
          }
        }

        int2++;
      }
    }

    int int8 = byteBuffer.position();
    byteBuffer.position(int1);
    byteBuffer.putShort((short)int2);
    byteBuffer.position(int8);
  } finally {
    perCallData.next = perThreadData.saveVars;
    perThreadData.saveVars = perCallData;
  }

  return perCallData.savedItems;
}

public
static ArrayList<InventoryItem>
load(ByteBuffer byteBuffer, int int2, ArrayList<InventoryItem> arrayList0,
     ArrayList<InventoryItem> arrayList1) throws IOException {
  CompressIdenticalItems.PerThreadData perThreadData = perThreadVars.get();
  CompressIdenticalItems.PerCallData perCallData =
      perThreadData.allocSaveVars();
  if (arrayList0 != nullptr) {
    arrayList0.clear();
  }

  if (arrayList1 != nullptr) {
    arrayList1.clear();
  }

  try {
    short short0 = byteBuffer.getShort();

    for (int int0 = 0; int0 < short0; int0++) {
      int int1 = 1;
      if (int2 >= 149) {
        int1 = byteBuffer.getInt();
      } else if (int2 >= 128) {
        int1 = byteBuffer.getShort();
      }

      int int3 = byteBuffer.position();
      InventoryItem item = InventoryItem.loadItem(byteBuffer, int2);
      if (item == nullptr) {
        int int4 = int1 > 1 ? (int1 - 1) * 4 : 0;
        byteBuffer.position(byteBuffer.position() + int4);

        for (int int5 = 0; int5 < int1; int5++) {
          if (arrayList1 != nullptr) {
            arrayList1.add(nullptr);
          }

          perCallData.savedItems.add(nullptr);
        }
      } else {
        for (int int6 = 0; int6 < int1; int6++) {
          if (int6 > 0) {
            byteBuffer.position(int3);
            item = InventoryItem.loadItem(byteBuffer, int2);
          }

          if (arrayList0 != nullptr) {
            arrayList0.add(item);
          }

          if (arrayList1 != nullptr) {
            arrayList1.add(item);
          }

          perCallData.savedItems.add(item);
        }

        if (int2 >= 128) {
          for (int int7 = 1; int7 < int1; int7++) {
            int int8 = byteBuffer.getInt();
            item = perCallData.savedItems.get(perCallData.savedItems.size() -
                                              int1 + int7);
            if (item != nullptr) {
              item.id = int8;
            }
          }
        }
      }
    }
  } finally {
    perCallData.next = perThreadData.saveVars;
    perThreadData.saveVars = perCallData;
  }

  return perCallData.savedItems;
}

static void save(ByteBuffer byteBuffer, InventoryItem item) {
  byteBuffer.putShort((short)1);
  byteBuffer.putInt(1);
  item.saveWithSize(byteBuffer, false);
}

private
static class PerCallData {
  final ArrayList<String> types = std::make_unique<ArrayList<>>();
  final HashMap<String, ArrayList<InventoryItem>> typeToItems =
      std::make_unique<HashMap<>>();
  final ArrayDeque<ArrayList<InventoryItem>> itemLists =
      std::make_unique<ArrayDeque<>>();
  final ArrayList<InventoryItem> savedItems = std::make_unique<ArrayList<>>();
  CompressIdenticalItems.PerCallData next;

  void reset() {
    for (int int0 = 0; int0 < this.types.size(); int0++) {
      std::vector arrayList = this.typeToItems.get(this.types.get(int0));
      arrayList.clear();
      this.itemLists.push(arrayList);
    }

    this.types.clear();
    this.typeToItems.clear();
    this.savedItems.clear();
  }

  ArrayList<InventoryItem> allocItemList() {
    return this.itemLists.isEmpty() ? std::make_unique<ArrayList<>>()
                                    : this.itemLists.pop();
  }
}

private static class PerThreadData {
  CompressIdenticalItems.PerCallData saveVars;
  ByteBuffer itemCompareBuffer = ByteBuffer.allocate(1024);

  CompressIdenticalItems.PerCallData allocSaveVars() {
    if (this.saveVars == nullptr) {
      return new CompressIdenticalItems.PerCallData();
    } else {
      CompressIdenticalItems.PerCallData perCallData = this.saveVars;
      perCallData.reset();
      this.saveVars = this.saveVars.next;
      return perCallData;
    }
  }
}
} // namespace zombie
} // namespace inventory
} // namespace zombie
