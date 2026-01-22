#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameTime.h"
#include "zombie/ZomboidFileSystem.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/logger/ExceptionLogger.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/network/PacketTypes/PacketType.h"
#include "zombie/network/ReplayManager/State.h"
#include "zombie/network/packets/PlayerPacket.h"
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace network {


class ReplayManager {
public:
    static const int ReplayManagerVersion = 1;
    State state = State.Stop;
    IsoPlayer player = nullptr;
    ByteBuffer bbpp = ByteBuffer.allocate(43);
    FileOutputStream outStream = nullptr;
    DataOutputStream output = nullptr;
    FileInputStream inStream = nullptr;
    DataInputStream input = nullptr;
    int inputVersion = 0;
    long inputTimeShift = 0L;
    PlayerPacket nextpp = nullptr;
    long nextppTime = 0L;

    public ReplayManager(IsoPlayer var1) {
      this.player = var1;
   }

    State getState() {
      return this.state;
   }

    bool isPlay() {
      return this.state == State.Playing;
   }

    void recordPlayerPacket(PlayerPacket var1) {
      if (this.state == State.Recording && var1.id == this.player.OnlineID) {
         this.bbpp.position(0);
    ByteBufferWriter var2 = std::make_shared<ByteBufferWriter>(this.bbpp);
         var1.write(var2);

         try {
            this.output.writeLong(GameTime.getServerTime());
            this.output.write(PacketType.PlayerUpdate.getId());
            this.output.write(var2.bb.array());
         } catch (IOException var4) {
            var4.printStackTrace();
         }
      }
   }

    bool startRecordReplay(IsoPlayer var1, const std::string& var2) {
    File var3 = ZomboidFileSystem.instance.getFileInCurrentSave(var2);
      if (this.player != nullptr && this.state == State.Recording) {
         DebugLog.log("ReplayManager: record replay already active for " + this.player.getUsername() + " user");
    return false;
      } else if (var3.exists()) {
         DebugLog.log("ReplayManager: invalid filename \"" + var2 + "\"");
    return false;
      } else {
         try {
            this.outStream = std::make_shared<FileOutputStream>(var3);
            this.output = std::make_shared<DataOutputStream>(this.outStream);
            this.output.write(1);
            this.output.writeLong(GameTime.getServerTime());
            this.player = var1;
            this.state = State.Recording;
    return true;
         } catch (Exception var5) {
            ExceptionLogger.logException(var5);
    return false;
         }
      }
   }

    bool stopRecordReplay() {
      if (this.state != State.Recording) {
         DebugLog.log("ReplayManager: record inactive");
    return false;
      } else {
         try {
            this.state = State.Stop;
            this.player = nullptr;
            this.output.flush();
            this.output.close();
            this.outStream.close();
            this.output = nullptr;
    return true;
         } catch (IOException var2) {
            var2.printStackTrace();
    return false;
         }
      }
   }

    bool startPlayReplay(IsoPlayer var1, const std::string& var2, UdpConnection var3) {
    File var4 = ZomboidFileSystem.instance.getFileInCurrentSave(var2);
      if (this.state == State.Playing) {
         DebugLog.log("ReplayManager: play replay already active for " + this.player.getUsername() + " user");
    return false;
      } else if (!var4.exists()) {
         DebugLog.log("ReplayManager: invalid filename \"" + var2 + "\"");
    return false;
      } else {
         try {
            this.inStream = std::make_shared<FileInputStream>(var4);
            this.input = std::make_shared<DataInputStream>(this.inStream);
            this.inputVersion = this.input.read();
            this.inputTimeShift = GameTime.getServerTime() - this.input.readLong();
            this.nextppTime = this.input.readLong();
    int var5 = this.input.read();
            if (var5 == PacketType.PlayerUpdate.getId() || var5 == PacketType.PlayerUpdateReliable.getId()) {
               this.input.read(this.bbpp.array());
               this.bbpp.position(0);
               this.nextpp = std::make_unique<PlayerPacket>();
               this.nextpp.parse(this.bbpp, var3);
            }

            this.player = var1;
            this.state = State.Playing;
    return true;
         } catch (Exception var6) {
            ExceptionLogger.logException(var6);
    return false;
         }
      }
   }

    bool stopPlayReplay() {
      if (this.state != State.Playing) {
         DebugLog.log("ReplayManager: play inactive");
    return false;
      } else {
         try {
            this.state = State.Stop;
            this.player = nullptr;
            this.input.close();
            this.inStream.close();
            this.input = nullptr;
            this.inputVersion = 0;
            this.inputTimeShift = 0L;
            this.nextpp = nullptr;
    return true;
         } catch (IOException var2) {
            var2.printStackTrace();
    return false;
         }
      }
   }

    void update() {
      if (this.state == State.Playing) {
         if (GameTime.getServerTime() >= this.nextppTime + this.inputTimeShift) {
            this.nextpp.id = this.player.OnlineID;
            this.nextpp.realt = (int)(this.nextpp.realt + this.inputTimeShift / 1000000L);
    IsoPlayer var1 = (IsoPlayer)GameServer.IDToPlayerMap.get(int.valueOf(this.nextpp.id));
    UdpConnection var2 = GameServer.getConnectionFromPlayer(var1);

            try {
               if (var1 == nullptr) {
                  DebugLog.General
                     .error("receivePlayerUpdate: Server received position for unknown player (id:" + this.nextpp.id + "). Server will ignore this data.");
               } else {
                  var1.networkAI.parse(this.nextpp);
                  var2.ReleventPos[var1.PlayerIndex].x = this.nextpp.realx;
                  var2.ReleventPos[var1.PlayerIndex].y = this.nextpp.realy;
                  var2.ReleventPos[var1.PlayerIndex].z = this.nextpp.realz;
               }
            } catch (Exception var6) {
               var6.printStackTrace();
            }

            for (int var3 = 0; var3 < GameServer.udpEngine.connections.size(); var3++) {
    UdpConnection var4 = (UdpConnection)GameServer.udpEngine.connections.get(var3);
               if (var2.getConnectedGUID() != var4.getConnectedGUID()) {
    ByteBufferWriter var5 = var4.startPacket();
                  PacketType.PlayerUpdate.doPacket(var5);
                  this.nextpp.write(var5);
                  PacketType.PlayerUpdate.send(var4);
               }
            }

            try {
               this.nextppTime = this.input.readLong();
    int var8 = this.input.read();
               if (var8 == PacketType.PlayerUpdate.getId() || var8 == PacketType.PlayerUpdateReliable.getId()) {
                  this.bbpp.position(0);
                  this.input.read(this.bbpp.array());
                  this.bbpp.position(0);
                  this.nextpp = std::make_unique<PlayerPacket>();
                  this.nextpp.parse(this.bbpp, var2);
               }
            } catch (IOException var7) {
               DebugLog.log("ReplayManager: stop playing replay");
               this.stopPlayReplay();
            }
         }
      }
   }
}
} // namespace network
} // namespace zombie
