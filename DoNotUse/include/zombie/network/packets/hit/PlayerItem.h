#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/LogSeverity.h"
#include "zombie/inventory/InventoryItem.h"
#include "zombie/inventory/InventoryItemFactory.h"
#include "zombie/network/packets/INetworkPacket.h"
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace network {
namespace packets {
namespace hit {


class PlayerItem : public Instance {
public:
    int itemId;
    InventoryItem item;

    void set(InventoryItem var1) {
      super.set(var1.getRegistry_id());
      this.item = var1;
      this.itemId = this.item.getID();
   }

    void parse(ByteBuffer var1, UdpConnection var2) {
    bool var3 = var1.get() == 1;
      if (var3) {
         this.ID = var1.getShort();
         var1.get();

         try {
            this.item = InventoryItemFactory.CreateItem(this.ID);
            if (this.item != nullptr) {
               this.item.load(var1, 195);
            }
         } catch (BufferUnderflowException | IOException var5) {
            DebugLog.Multiplayer.printException(var5, "Item load error", LogSeverity.Error);
            this.item = nullptr;
         }
      } else {
         this.item = nullptr;
      }
   }

    void write(ByteBufferWriter var1) {
      if (this.item == nullptr) {
         var1.putByte((byte)0);
      } else {
         var1.putByte((byte)1);

         try {
            this.item.save(var1.bb, false);
         } catch (IOException var3) {
            DebugLog.Multiplayer.printException(var3, "Item write error", LogSeverity.Error);
         }
      }
   }

    bool isConsistent() {
      return super.isConsistent() && this.item != nullptr;
   }

    std::string getDescription() {
      return super.getDescription() + "\n\tItem [ Item=" + (this.item == nullptr ? "?" : "\"" + this.item.getDisplayName() + "\"") + " ]";
   }

    InventoryItem getItem() {
      return this.item;
   }
}
} // namespace hit
} // namespace packets
} // namespace network
} // namespace zombie
