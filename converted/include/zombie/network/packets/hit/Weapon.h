#pragma once
#include "zombie/characters/IsoLivingCharacter.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/LogSeverity.h"
#include "zombie/inventory/InventoryItem.h"
#include "zombie/inventory/InventoryItemFactory.h"
#include "zombie/inventory/types/HandWeapon.h"
#include "zombie/network/packets/INetworkPacket.h"
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
namespace packets {
namespace hit {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class Weapon : public Instance {
public:
  InventoryItem item;
  HandWeapon weapon;

  void set(HandWeapon weapon1) {
    super.set(weapon1.getRegistry_id());
    this.item = weapon1;
    this.weapon = weapon1;
  }

  void parse(ByteBuffer byteBuffer, IsoLivingCharacter livingCharacter) {
    bool boolean0 = byteBuffer.get() == 1;
    if (boolean0) {
      this.ID = byteBuffer.getShort();
      byteBuffer.get();
      if (livingCharacter != nullptr) {
        this.item = livingCharacter.getPrimaryHandItem();
        if (this.item == nullptr || this.item.getRegistry_id() != this.ID) {
          this.item = InventoryItemFactory.CreateItem(this.ID);
        }

        if (this.item != nullptr) {
          try {
            this.item.load(byteBuffer, 195);
          } catch (BufferUnderflowException | IOException iOException) {
            DebugLog.Multiplayer.printException(
                iOException, "Weapon load error", LogSeverity.Error);
            this.item = InventoryItemFactory.CreateItem("Base.BareHands");
          }
        }
      }
    } else {
      this.item = InventoryItemFactory.CreateItem("Base.BareHands");
    }

    if (livingCharacter != nullptr) {
      this.weapon = livingCharacter.bareHands;
      if (this.item instanceof HandWeapon) {
        this.weapon = (HandWeapon)this.item;
      }
    }
  }

  void parse(ByteBuffer var1, UdpConnection var2) {
    DebugLog.Multiplayer.error("Weapon.parse is not implemented");
  }

  void write(ByteBufferWriter byteBufferWriter) {
    if (this.item == nullptr) {
      byteBufferWriter.putByte((byte)0);
    } else {
      byteBufferWriter.putByte((byte)1);

      try {
        this.item.save(byteBufferWriter.bb, false);
      } catch (IOException iOException) {
        DebugLog.Multiplayer.printException(iOException, "Item write error",
                                            LogSeverity.Error);
      }
    }
  }

  bool isConsistent() { return super.isConsistent() && this.weapon != nullptr; }

  std::string getDescription() {
    return super.getDescription() + "\n\tWeapon [ weapon=" +
           (this.weapon == nullptr
                ? "?"
                : "\"" + this.weapon.getDisplayName() + "\"") +
           " ]";
  }

  HandWeapon getWeapon() { return this.weapon; }
}
} // namespace hit
} // namespace packets
} // namespace network
} // namespace zombie
