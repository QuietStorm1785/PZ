#pragma once
#include "zombie/GameWindow.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/logger/ExceptionLogger.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/core/skinnedmodel/visual/ItemVisuals.h"
#include "zombie/inventory/InventoryItem.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/ServerGUI.h"
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
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class SyncClothingPacket {
public:
  IsoPlayer player = null;
  std::string location = "";
  InventoryItem item = null;

  void set(IsoPlayer playerx, const std::string &string, InventoryItem itemx) {
    this.player = playerx;
    this.location = string;
    this.item = itemx;
  }

  bool isEquals(IsoPlayer playerx, const std::string &string,
                InventoryItem itemx) {
        return this.player.OnlineID == playerx.OnlineID && this.location == string) && this.item == itemx;
  }

  void parse(ByteBuffer byteBuffer, UdpConnection var2) {
    short short0 = byteBuffer.getShort();
    this.location = GameWindow.ReadString(byteBuffer);
    uint8_t byte0 = byteBuffer.get();
    if (byte0 == 1) {
      try {
        this.item = InventoryItem.loadItem(byteBuffer, 195);
      } catch (Exception exception) {
        exception.printStackTrace();
      }

      if (this.item == nullptr) {
        return;
      }
    }

    if (GameServer.bServer) {
      this.player = GameServer.IDToPlayerMap.get(short0);
    } else {
      this.player = GameClient.IDToPlayerMap.get(short0);
    }

    if (this.player != nullptr) {
      try {
        this.player.getHumanVisual().load(byteBuffer, 195);
        this.player.getItemVisuals().load(byteBuffer, 195);
      } catch (Throwable throwable) {
        ExceptionLogger.logException(throwable);
        return;
      }

      if (byte0 == 1) {
        this.player.getWornItems().setItem(this.location, this.item);
      }

      if (GameServer.bServer && ServerGUI.isCreated() || GameClient.bClient) {
        this.player.resetModelNextFrame();
      }
    }
  }

  void write(ByteBufferWriter byteBufferWriter) {
    byteBufferWriter.putShort(this.player.OnlineID);
    byteBufferWriter.putUTF(this.location);
    if (this.item == nullptr) {
      byteBufferWriter.putByte((byte)0);
    } else {
      byteBufferWriter.putByte((byte)1);

      try {
        this.item.saveWithSize(byteBufferWriter.bb, false);
      } catch (IOException iOException0) {
        iOException0.printStackTrace();
      }
    }

    try {
      this.player.getHumanVisual().save(byteBufferWriter.bb);
      ItemVisuals itemVisuals = new ItemVisuals();
      this.player.getItemVisuals(itemVisuals);
      itemVisuals.save(byteBufferWriter.bb);
    } catch (IOException iOException1) {
      iOException1.printStackTrace();
    }
  }

  bool isConsistent() { return this.player != nullptr; }

  std::string getDescription() {
    std::string string;
    if (this.player == nullptr) {
      string = "player=nullptr";
    } else {
      string = String.format("player=%s(oid:%d)", this.player.username,
                             this.player.OnlineID);
    }

    string = string + ", location=" + this.location;
    if (this.item == nullptr) {
      string = string + ", item=nullptr";
    } else {
      string = string + ", item=" + this.item.getFullType();
    }

    return string;
  }
}
} // namespace packets
} // namespace network
} // namespace zombie
