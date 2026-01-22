#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/IsoLivingCharacter.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/LogSeverity.h"
#include "zombie/inventory/InventoryItem.h"
#include "zombie/inventory/InventoryItemFactory.h"
#include "zombie/inventory/types/HandWeapon.h"
#include "zombie/network/packets/INetworkPacket.h"
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace network {
namespace packets {
namespace hit {


class Weapon : public Instance {
public:
    InventoryItem item;
    HandWeapon weapon;

    void set(HandWeapon var1) {
      super.set(var1.getRegistry_id());
      this.item = var1;
      this.weapon = var1;
   }

    void parse(ByteBuffer var1, IsoLivingCharacter var2) {
    bool var3 = var1.get() == 1;
      if (var3) {
         this.ID = var1.getShort();
         var1.get();
         if (var2 != nullptr) {
            this.item = var2.getPrimaryHandItem();
            if (this.item == nullptr || this.item.getRegistry_id() != this.ID) {
               this.item = InventoryItemFactory.CreateItem(this.ID);
            }

            if (this.item != nullptr) {
               try {
                  this.item.load(var1, 195);
               } catch (BufferUnderflowException | IOException var5) {
                  DebugLog.Multiplayer.printException(var5, "Weapon load error", LogSeverity.Error);
                  this.item = InventoryItemFactory.CreateItem("Base.BareHands");
               }
            }
         }
      } else {
         this.item = InventoryItemFactory.CreateItem("Base.BareHands");
      }

      if (var2 != nullptr) {
         this.weapon = var2.bareHands;
         if (this.dynamic_cast<HandWeapon*>(item) != nullptr) {
            this.weapon = (HandWeapon)this.item;
         }
      }
   }

    void parse(ByteBuffer var1, UdpConnection var2) {
      DebugLog.Multiplayer.error("Weapon.parse is not implemented");
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
      return super.isConsistent() && this.weapon != nullptr;
   }

    std::string getDescription() {
      return super.getDescription() + "\n\tWeapon [ weapon=" + (this.weapon == nullptr ? "?" : "\"" + this.weapon.getDisplayName() + "\"") + " ]";
   }

    HandWeapon getWeapon() {
      return this.weapon;
   }
}
} // namespace hit
} // namespace packets
} // namespace network
} // namespace zombie
