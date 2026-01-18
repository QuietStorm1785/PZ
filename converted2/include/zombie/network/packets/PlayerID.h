#pragma once
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/packets/hit/Instance.h"
#include <cstdint>
#include <filesystem>
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

class PlayerID : public Instance {
public:
  IsoPlayer player;
  uint8_t playerIndex;

  void set(IsoPlayer playerx) {
    super.set(playerx.OnlineID);
    this.playerIndex = playerx.isLocal() ? (byte)playerx.getPlayerNum() : -1;
    this.player = playerx;
  }

  void parsePlayer(UdpConnection udpConnection) {
    if (GameServer.bServer) {
      if (udpConnection != nullptr && this.playerIndex != -1) {
        this.player =
            GameServer.getPlayerFromConnection(udpConnection, this.playerIndex);
      } else {
        this.player = GameServer.IDToPlayerMap.get(this.ID);
      }
    } else if (GameClient.bClient) {
      this.player = GameClient.IDToPlayerMap.get(this.ID);
    }
  }

  void parse(ByteBuffer byteBuffer, UdpConnection udpConnection) {
    super.parse(byteBuffer, udpConnection);
    this.playerIndex = byteBuffer.get();
  }

  void write(ByteBufferWriter byteBufferWriter) {
    super.write(byteBufferWriter);
    byteBufferWriter.putByte(this.playerIndex);
  }

  bool isConsistent() {
    return super.isConsistent() && this.getCharacter() != nullptr;
  }

  std::string getDescription() {
    return super.getDescription() + "\n\tPlayer [ player " +
           (this.player == nullptr ? "?"
                                   : "\"" + this.player.getUsername() + "\"") +
           " ]";
  }

  IsoPlayer getCharacter() { return this.player; }
}
} // namespace packets
} // namespace network
} // namespace zombie
