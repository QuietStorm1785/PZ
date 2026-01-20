#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameWindow.h"
#include "zombie/ZomboidFileSystem.h"
#include "zombie/core/logger/LoggerManager.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/core/raknet/UdpConnection/ChecksumState.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugType.h"
#include "zombie/debug/LogSeverity.h"
#include "zombie/network/NetChecksum/1.h"
#include "zombie/network/NetChecksum/Comparer/State.h"
#include "zombie/network/NetChecksum/GroupOfFiles.h"
#include "zombie/network/PacketTypes/PacketType.h"
#include "zombie/network/Userlog/UserlogType.h"
#include "zombie/scripting/ScriptManager.h"
#include <filesystem>

namespace zombie {
namespace network {


class NetChecksum {
public:
    static const short PacketTotalChecksum = 1;
    static const short PacketGroupChecksum = 2;
    static const short PacketFileChecksums = 3;
    static const short PacketError = 4;
    static const uint8_t FileDifferent = 1;
    static const uint8_t FileNotOnServer = 2;
    static const uint8_t FileNotOnClient = 3;
    static const short NUM_GROUPS_TO_SEND = 10;
    State state = State.Init;
    short currentIndex;
    std::string error;
   private const byte[] checksum = new byte[64];

    void beginCompare() {
      this.error = nullptr;
      this.sendTotalChecksum();
   }

    void sendTotalChecksum() {
      if (GameClient.bClient) {
         NetChecksum.noise("send total checksum");
    ByteBufferWriter var1 = GameClient.connection.startPacket();
         PacketType.Checksum.doPacket(var1);
         var1.putShort((short)1);
         var1.putUTF(GameClient.checksum);
         var1.putUTF(ScriptManager.instance.getChecksum());
         PacketType.Checksum.send(GameClient.connection);
         this.state = State.SentTotalChecksum;
      }
   }

    void sendGroupChecksum() {
      if (GameClient.bClient) {
         if (this.currentIndex >= GroupOfFiles.groups.size()) {
            this.state = State.Success;
         } else {
    short var1 = (short)Math.min(this.currentIndex + 10 - 1, GroupOfFiles.groups.size() - 1);
            NetChecksum.noise("send group checksums " + this.currentIndex + "-" + var1);
    ByteBufferWriter var2 = GameClient.connection.startPacket();
            PacketType.Checksum.doPacket(var2);
            var2.putShort((short)2);
            var2.putShort(this.currentIndex);
            var2.putShort(var1);

            for (short var3 = this.currentIndex; var3 <= var1; var3++) {
    GroupOfFiles var4 = (GroupOfFiles)GroupOfFiles.groups.get(var3);
               var2.putShort((short)var4.totalChecksum.length);
               var2.bb.put(var4.totalChecksum);
            }

            PacketType.Checksum.send(GameClient.connection);
            this.state = State.SentGroupChecksum;
         }
      }
   }

    void sendFileChecksums() {
      if (GameClient.bClient) {
         NetChecksum.noise("send file checksums " + this.currentIndex);
    GroupOfFiles var1 = (GroupOfFiles)GroupOfFiles.groups.get(this.currentIndex);
    ByteBufferWriter var2 = GameClient.connection.startPacket();
         PacketType.Checksum.doPacket(var2);
         var2.putShort((short)3);
         var2.bb.putShort(this.currentIndex);
         var2.putShort(var1.fileCount);

         for (int var3 = 0; var3 < var1.fileCount; var3++) {
            var2.putUTF(var1.relPaths[var3]);
            var2.putByte((byte)var1.checksums[var3].length);
            var2.bb.put(var1.checksums[var3]);
         }

         PacketType.Checksum.send(GameClient.connection);
         this.state = State.SentFileChecksums;
      }
   }

    std::string getReason(uint8_t var1) {
    return switch() {
         case 1 -> "File doesn't match the one on the server";
         case 2 -> "File doesn't exist on the server";
         case 3 -> "File doesn't exist on the client";
         default -> "File status unknown";
      };
   }

    void clientPacket(ByteBuffer var1) {
      if (GameClient.bClient) {
    short var2 = var1.getShort();
         switch (var2) {
            case 1:
               if (this.state != State.SentTotalChecksum) {
                  this.error = "NetChecksum: received PacketTotalChecksum in state " + this.state;
                  this.state = State.Failed;
               } else {
    bool var9 = var1.get() == 1;
    bool var11 = var1.get() == 1;
                  NetChecksum.noise("total checksum lua=" + var9 + " script=" + var11);
                  if (var9 && var11) {
                     this.state = State.Success;
                  } else {
                     this.currentIndex = 0;
                     this.sendGroupChecksum();
                  }
               }
               break;
            case 2:
               if (this.state != State.SentGroupChecksum) {
                  this.error = "NetChecksum: received PacketGroupChecksum in state " + this.state;
                  this.state = State.Failed;
               } else {
    short var8 = var1.getShort();
    bool var10 = var1.get() == 1;
                  if (var8 >= this.currentIndex && var8 < this.currentIndex + 10) {
                     NetChecksum.noise("group checksum " + var8 + " match=" + var10);
                     if (var10) {
                        this.currentIndex = (short)(this.currentIndex + 10);
                        this.sendGroupChecksum();
                     } else {
                        this.currentIndex = var8;
                        this.sendFileChecksums();
                     }
                  } else {
                     this.error = "NetChecksum: expected PacketGroupChecksum " + this.currentIndex + " but got " + var8;
                     this.state = State.Failed;
                  }
               }
               break;
            case 3:
               if (this.state != State.SentFileChecksums) {
                  this.error = "NetChecksum: received PacketFileChecksums in state " + this.state;
                  this.state = State.Failed;
               } else {
    short var3 = var1.getShort();
    std::string var4 = GameWindow.ReadStringUTF(var1);
    std::string var5 = GameWindow.ReadStringUTF(var1);
    uint8_t var6 = var1.get();
                  if (var3 != this.currentIndex) {
                     this.error = "NetChecksum: expected PacketFileChecksums " + this.currentIndex + " but got " + var3;
                     this.state = State.Failed;
                  } else {
                     this.error = this.getReason(var6);
                     if (DebugLog.isLogEnabled(LogSeverity.Debug, DebugType.Checksum)) {
                        LoggerManager.getLogger("checksum").write(std::string.format("%s%s", this.error, NetChecksum.checksummer));
                     }

                     this.error = this.error + ":\n" + var4;
    std::string var7 = ZomboidFileSystem.instance.getString(var4);
                     if (!var7 == var4)) {
                        this.error = this.error + "\nclient: " + var7;
                     }

                     if (!var5 == var4)) {
                        this.error = this.error + "\nserver: " + var5;
                     }

                     this.state = State.Failed;
                  }
               }
               break;
            case 4:
               this.error = GameWindow.ReadStringUTF(var1);
               this.state = State.Failed;
               break;
            default:
               this.error = "NetChecksum: unhandled packet " + var2;
               this.state = State.Failed;
         }
      }
   }

    bool checksumEquals(byte[] var1) {
      if (var1 == nullptr) {
    return false;
      } else if (this.checksum.length < var1.length) {
    return false;
      } else {
         for (int var2 = 0; var2 < var1.length; var2++) {
            if (this.checksum[var2] != var1[var2]) {
    return false;
            }
         }

    return true;
      }
   }

    void sendFileMismatch(UdpConnection var1, short var2, const std::string& var3, uint8_t var4) {
      if (GameServer.bServer) {
    ByteBufferWriter var5 = var1.startPacket();
         PacketType.Checksum.doPacket(var5);
         var5.putShort((short)3);
         var5.putShort(var2);
         var5.putUTF(var3);
         var5.putUTF(ZomboidFileSystem.instance.getString(var3));
         var5.putByte(var4);
         PacketType.Checksum.send(var1);
         if (DebugLog.isLogEnabled(LogSeverity.Debug, DebugType.Checksum)) {
            LoggerManager.getLogger("checksum").write(std::string.format("%s%s", this.getReason(var4), NetChecksum.checksummer));
            LoggerManager.getLogger("checksum-" + var1.idStr).write(this.getReason(var4));
         }
      }
   }

    void sendError(UdpConnection var1, const std::string& var2) {
      NetChecksum.noise(var2);
    ByteBufferWriter var3 = var1.startPacket();
      PacketType.Checksum.doPacket(var3);
      var3.putShort((short)4);
      var3.putUTF(var2);
      PacketType.Checksum.send(var1);
   }

    void serverPacket(ByteBuffer var1, UdpConnection var2) {
      if (GameServer.bServer) {
    short var3 = var1.getShort();
         switch (var3) {
            case 1:
    std::string var13 = GameWindow.ReadString(var1);
    std::string var15 = GameWindow.ReadString(var1);
    bool var19 = var13 == GameServer.checksum);
    bool var21 = var15 == ScriptManager.instance.getChecksum());
               NetChecksum.noise("PacketTotalChecksum lua=" + var19 + " script=" + var21);
               if (var2.accessLevel == 32) {
                  var21 = true;
                  var19 = true;
               }

               var2.checksumState = var19 && var21 ? ChecksumState.Done : ChecksumState.Different;
               var2.checksumTime = System.currentTimeMillis();
               if (!var19 || !var21) {
                  DebugLog.log("user " + var2.username + " will be kicked because Lua/script checksums do not match");
    std::string var24 = "";
                  if (!var19) {
                     var24 = var24 + "Lua";
                  }

                  if (!var21) {
                     var24 = var24 + "Script";
                  }

                  ServerWorldDatabase.instance.addUserlog(var2.username, UserlogType.LuaChecksum, var24, this.getClass().getSimpleName(), 1);
               }

    ByteBufferWriter var25 = var2.startPacket();
               PacketType.Checksum.doPacket(var25);
               var25.putShort((short)1);
               var25.putBoolean(var19);
               var25.putBoolean(var21);
               PacketType.Checksum.send(var2);
               break;
            case 2:
    short var12 = var1.getShort();
    short var14 = var1.getShort();
               if (var12 >= 0 && var14 >= var12 && var14 < var12 + 10) {
    short var17 = var12;

                  while (var17 <= var14) {
    short var20 = var1.getShort();
                     if (var20 < 0 || var20 > this.checksum.length) {
                        this.sendError(var2, "PacketGroupChecksum: numBytes is invalid");
                        return;
                     }

                     var1.get(this.checksum, 0, var20);
                     if (var17 < GroupOfFiles.groups.size()) {
    GroupOfFiles var22 = (GroupOfFiles)GroupOfFiles.groups.get(var17);
                        if (this.checksumEquals(var22.totalChecksum)) {
                           var17++;
                           continue;
                        }
                     }

    ByteBufferWriter var23 = var2.startPacket();
                     PacketType.Checksum.doPacket(var23);
                     var23.putShort((short)2);
                     var23.putShort(var17);
                     var23.putBoolean(false);
                     PacketType.Checksum.send(var2);
                     return;
                  }

    ByteBufferWriter var18 = var2.startPacket();
                  PacketType.Checksum.doPacket(var18);
                  var18.putShort((short)2);
                  var18.putShort(var12);
                  var18.putBoolean(true);
                  PacketType.Checksum.send(var2);
               } else {
                  this.sendError(var2, "PacketGroupChecksum: firstIndex and/or lastIndex are invalid");
               }
               break;
            case 3:
    short var11 = var1.getShort();
    short var5 = var1.getShort();
               if (var11 < 0 || var5 <= 0 || var5 > 20) {
                  this.sendError(var2, "PacketFileChecksums: groupIndex and/or fileCount are invalid");
                  return;
               }

               if (var11 >= GroupOfFiles.groups.size()) {
    std::string var16 = GameWindow.ReadStringUTF(var1);
                  this.sendFileMismatch(var2, var11, var16, (byte)2);
                  return;
               }

    GroupOfFiles var6 = (GroupOfFiles)GroupOfFiles.groups.get(var11);

               for (short var7 = 0; var7 < var5; var7++) {
    std::string var8 = GameWindow.ReadStringUTF(var1);
    uint8_t var9 = var1.get();
                  if (var9 < 0 || var9 > this.checksum.length) {
                     this.sendError(var2, "PacketFileChecksums: numBytes is invalid");
                     return;
                  }

                  if (var7 >= var6.fileCount) {
                     this.sendFileMismatch(var2, var11, var8, (byte)2);
                     return;
                  }

                  if (!var8 == var6.relPaths[var7])) {
    std::string var10 = ZomboidFileSystem.instance.getString(var8);
                     if (var10 == var8)) {
                        this.sendFileMismatch(var2, var11, var8, (byte)2);
                        return;
                     }

                     this.sendFileMismatch(var2, var11, var6.relPaths[var7], (byte)3);
                     return;
                  }

                  if (var9 > var6.checksums[var7].length) {
                     this.sendFileMismatch(var2, var11, var6.relPaths[var7], (byte)1);
                     return;
                  }

                  var1.get(this.checksum, 0, var9);
                  if (!this.checksumEquals(var6.checksums[var7])) {
                     this.sendFileMismatch(var2, var11, var6.relPaths[var7], (byte)1);
                     return;
                  }
               }

               if (var6.fileCount > var5) {
                  this.sendFileMismatch(var2, var11, var6.relPaths[var5], (byte)3);
                  return;
               }

               this.sendError(var2, "PacketFileChecksums: all checks passed when they shouldn't");
               break;
            case 4:
    std::string var4 = GameWindow.ReadStringUTF(var1);
               if (DebugLog.isLogEnabled(LogSeverity.Debug, DebugType.Checksum)) {
                  LoggerManager.getLogger("checksum-" + var2.idStr).write(var4, nullptr, true);
               }
               break;
            default:
               this.sendError(var2, "Unknown packet " + var3);
         }
      }
   }

    void gc() {
      GroupOfFiles.gc();
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
    void update() {
      switch (1.$SwitchMap$zombie$network$NetChecksum$Comparer$State[this.state.ordinal()]) {
         case 1:
         case 2:
         case 3:
         case 4:
         default:
            break;
         case 5:
            this.gc();
            GameClient.checksumValid = true;
            break;
         case 6:
            this.gc();
            GameClient.connection.forceDisconnect("checksum-" + this.error);
            GameWindow.bServerDisconnected = true;
            GameWindow.kickReason = this.error;
      }
   }
}
} // namespace network
} // namespace zombie
