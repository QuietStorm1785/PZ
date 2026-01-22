#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
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
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace network {
namespace packets {


class SyncClothingPacket {
public:
    IsoPlayer player = nullptr;
    std::string location = "";
    InventoryItem item = nullptr;

    void set(IsoPlayer var1, const std::string& var2, InventoryItem var3) {
      this.player = var1;
      this.location = var2;
      this.item = var3;
   }

    bool isEquals(IsoPlayer var1, const std::string& var2, InventoryItem var3) {
      return this.player.OnlineID == var1.OnlineID && this.location == var2) && this.item == var3;
   }

    void parse(ByteBuffer var1, UdpConnection var2) {
    short var3 = var1.getShort();
      this.location = GameWindow.ReadString(var1);
    uint8_t var4 = var1.get();
      if (var4 == 1) {
         try {
            this.item = InventoryItem.loadItem(var1, 195);
         } catch (Exception var7) {
            var7.printStackTrace();
         }

         if (this.item == nullptr) {
            return;
         }
      }

      if (GameServer.bServer) {
         this.player = (IsoPlayer)GameServer.IDToPlayerMap.get(var3);
      } else {
         this.player = (IsoPlayer)GameClient.IDToPlayerMap.get(var3);
      }

      if (this.player != nullptr) {
         try {
            this.player.getHumanVisual().load(var1, 195);
            this.player.getItemVisuals().load(var1, 195);
         } catch (Throwable var6) {
            ExceptionLogger.logException(var6);
            return;
         }

         if (var4 == 1) {
            this.player.getWornItems().setItem(this.location, this.item);
         }

         if (GameServer.bServer && ServerGUI.isCreated() || GameClient.bClient) {
            this.player.resetModelNextFrame();
         }
      }
   }

    void write(ByteBufferWriter var1) {
      var1.putShort(this.player.OnlineID);
      var1.putUTF(this.location);
      if (this.item == nullptr) {
         var1.putByte((byte)0);
      } else {
         var1.putByte((byte)1);

         try {
            this.item.saveWithSize(var1.bb, false);
         } catch (IOException var4) {
            var4.printStackTrace();
         }
      }

      try {
         this.player.getHumanVisual().save(var1.bb);
    ItemVisuals var2 = std::make_shared<ItemVisuals>();
         this.player.getItemVisuals(var2);
         var2.save(var1.bb);
      } catch (IOException var3) {
         var3.printStackTrace();
      }
   }

    bool isConsistent() {
      return this.player != nullptr;
   }

    std::string getDescription() {
    std::string var1;
      if (this.player == nullptr) {
         var1 = "player=nullptr";
      } else {
         var1 = std::string.format("player=%s(oid:%d)", this.player.username, this.player.OnlineID);
      }

      var1 = var1 + ", location=" + this.location;
      if (this.item == nullptr) {
         var1 = var1 + ", item=nullptr";
      } else {
         var1 = var1 + ", item=" + this.item.getFullType();
      }

    return var1;
   }
}
} // namespace packets
} // namespace network
} // namespace zombie
