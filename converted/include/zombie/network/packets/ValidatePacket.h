#pragma once
#include "zombie/GameWindow.h"
#include "zombie/core/Rand.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugOptions.h"
#include "zombie/debug/LogSeverity.h"
#include "zombie/gameStates/GameLoadingState.h"
#include "zombie/network/ConnectionManager.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/PacketValidator.h"
#include "zombie/scripting/ScriptManager.h"
#include "zombie/scripting/objects/Recipe.h"
#include <algorithm>
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

class ValidatePacket {
public:
  long checksum;
  long checksumFromClient;
  int salt;
  uint8_t flags;

  void setSalt(int int0, bool boolean0, bool boolean1, bool boolean2) {
    this.salt = int0;
    this.flags = 0;
    this.flags = (byte)(this.flags | (boolean0 ? 1 : 0));
    this.flags = (byte)(this.flags | (boolean1 ? 2 : 0));
    this.flags = (byte)(this.flags | (boolean2 ? 4 : 0));
  }

  void process(UdpConnection udpConnection) {
    if (GameClient.bClient) {
      this.checksum = this.calculateChecksum(udpConnection, this.salt);
      GameClient.sendValidatePacket(this);
      if (DebugOptions.instance.MultiplayerFailChecksum.getValue() &&
          (this.flags & 1) != 0) {
        std::vector arrayList = ScriptManager.instance.getAllRecipes();
        Recipe recipe = (Recipe)arrayList.get(Rand.Next(arrayList.size()));
        recipe.TimeToMake = Rand.Next(32767);
        DebugLog.Multiplayer.debugln("Failed recipe \"%s\"",
                                     recipe.getOriginalname());
      }

      if ((this.flags & 2) != 0) {
        GameLoadingState.Done();
      }
    } else if (GameServer.bServer) {
      this.salt = udpConnection.validator.getSalt();
      this.checksum = this.calculateChecksum(udpConnection, this.salt);
      if ((this.flags & 4) == 0) {
        if (this.checksumFromClient != this.checksum) {
          udpConnection.validator.failChecksum();
        }

        if (udpConnection.validator.isFailed()) {
          udpConnection.validator.sendChecksum(false, false, true);
        } else {
          udpConnection.validator.successChecksum();
          if ((this.flags & 1) != 0) {
            udpConnection.validator.sendChecksum(false, true, false);
          }
        }
      }
    }
  }

  long calculateChecksum(UdpConnection udpConnection, int int0) {
    if ((this.flags & 4) != 0) {
      udpConnection.validator.details.clear();
    }

    CRC32 crc320 = new CRC32();
    CRC32 crc321 = new CRC32();
    ByteBuffer byteBuffer = ByteBuffer.allocate(8);
    crc320.update(int0);

    for (Recipe recipe : ScriptManager.instance.getAllRecipes()) {
      crc321.reset();
      byteBuffer.clear();
      crc321.update(recipe.getOriginalname().getBytes());
      crc321.update((int)recipe.TimeToMake);
      if (recipe.skillRequired != nullptr) {
        for (Recipe.RequiredSkill requiredSkill : recipe.skillRequired) {
          crc321.update(requiredSkill.getPerk().index());
          crc321.update(requiredSkill.getLevel());
        }
      }

      for (Recipe.Source source : recipe.getSource()) {
        for (String string : source.getItems()) {
          crc321.update(string.getBytes());
        }
      }

      crc321.update(recipe.getResult().getType().getBytes());
      crc321.update(recipe.getResult().getModule().getBytes());
      crc321.update(recipe.getResult().getCount());
      long long0 = crc321.getValue();
      byteBuffer.putLong(long0);
      byteBuffer.position(0);
      crc320.update(byteBuffer);
      if ((this.flags & 4) != 0) {
        udpConnection.validator.details.put(
            recipe.getOriginalname(),
            new PacketValidator.RecipeDetails(
                recipe.getOriginalname(), long0, (int)recipe.TimeToMake,
                recipe.skillRequired, recipe.getSource(),
                recipe.getResult().getType(), recipe.getResult().getModule(),
                recipe.getResult().getCount()));
      }
    }

    return crc320.getValue();
  }

  void parse(ByteBuffer byteBuffer, UdpConnection udpConnection) {
    try {
      this.flags = byteBuffer.get();
      if (GameClient.bClient) {
        this.salt = byteBuffer.getInt();
      } else if (GameServer.bServer) {
        this.checksumFromClient = byteBuffer.getLong();
        if ((this.flags & 4) != 0) {
          udpConnection.validator.detailsFromClient.clear();
          int int0 = byteBuffer.getInt();

          for (int int1 = 0; int1 < int0; int1++) {
            udpConnection.validator.detailsFromClient.put(
                GameWindow.ReadString(byteBuffer),
                new PacketValidator.RecipeDetails(byteBuffer));
          }
        }
      }
    } catch (Exception exception) {
      DebugLog.Multiplayer.printException(exception,
                                          "Parse error. Probably, \"" +
                                              udpConnection.username +
                                              "\" client is outdated",
                                          LogSeverity.Error);
    }
  }

  void write(ByteBufferWriter byteBufferWriter) {
    byteBufferWriter.putByte(this.flags);
    if (GameServer.bServer) {
      byteBufferWriter.putInt(this.salt);
    } else if (GameClient.bClient) {
      byteBufferWriter.putLong(this.checksum);
      if ((this.flags & 4) != 0) {
        int int0 = GameClient.connection.validator.details.size();
        byteBufferWriter.putInt(int0);

        for (Entry entry : GameClient.connection.validator.details.entrySet()) {
          byteBufferWriter.putUTF((String)entry.getKey());
          ((PacketValidator.RecipeDetails)entry.getValue())
              .write(byteBufferWriter);
        }
      }
    }
  }

  void log(UdpConnection udpConnection, const std::string &string) {
    if (this.flags != 0) {
      ConnectionManager.log(string,
                            String.format("checksum-packet-%d", this.flags),
                            udpConnection);
    }
  }

public
  static enum ValidateState { Request, Success; }
}
} // namespace packets
} // namespace network
} // namespace zombie
