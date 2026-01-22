#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "java/net/ConnectException.h"
#include "java/net/InetAddress.h"
#include "java/net/UnknownHostException.h"
#include "zombie/GameWindow.h"
#include "zombie/Lua/LuaEventManager.h"
#include "zombie/core/Core.h"
#include "zombie/core/Rand.h"
#include "zombie/core/ThreadGroups.h"
#include "zombie/core/Translator.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/secure/PZcrypt.h"
#include "zombie/core/znet/SteamUser.h"
#include "zombie/core/znet/SteamUtils.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/LogSeverity.h"
#include "zombie/network/ConnectionManager.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/PacketTypes/PacketType.h"
#include "zombie/network/PacketValidator.h"
#include "zombie/network/RequestDataManager.h"
#include "zombie/network/ServerOptions.h"
#include "zombie/network/ServerWorldDatabase.h"
#include <algorithm>
#include <filesystem>

namespace zombie {
namespace core {
namespace raknet {


class UdpEngine {
public:
    int maxConnections = 0;
   private const Map<int64_t, UdpConnection> connectionMap = std::make_unique<std::unordered_map<>>();
   public const List<UdpConnection> connections = std::make_unique<std::vector<>>();
    const RakNetPeerInterface peer;
    const bool bServer;
    Lock bufferLock = std::make_shared<ReentrantLock>();
    ByteBuffer bb = ByteBuffer.allocate(500000);
    ByteBufferWriter bbw = std::make_shared<ByteBufferWriter>(this.bb);
    int port = 0;
    const Thread thread;
    bool bQuit;
   UdpConnection[] connectionArray = new UdpConnection[256];
    ByteBuffer buf = ByteBuffer.allocate(1000000);

    public UdpEngine(int var1, int var2, int var3, const std::string& var4, bool var5) {
      this.port = var1;
      this.peer = std::make_unique<RakNetPeerInterface>();
      DebugLog.Network.println("Initialising RakNet...");
      this.peer.Init(SteamUtils.isSteamModeEnabled());
      this.peer.SetMaximumIncomingConnections(var3);
      this.bServer = var5;
      if (this.bServer) {
         if (GameServer.IPCommandline != nullptr) {
            this.peer.SetServerIP(GameServer.IPCommandline);
         }

         this.peer.SetServerPort(var1, var2);
         this.peer.SetIncomingPassword(this.hashServerPassword(var4));
      } else {
         this.peer.SetClientPort(GameServer.DEFAULT_PORT + Rand.Next(10000) + 1234);
      }

      this.peer.SetOccasionalPing(true);
      this.maxConnections = var3;
    int var6 = this.peer.Startup(var3);
      DebugLog.Network.println("RakNet.Startup() return code: %s (0 means success)", var6);
      if (var6 != 0) {
         throw ConnectException("Connection Startup Failed. Code: " + var6);
      } else {
         if (var5) {
            VoiceManager.instance.InitVMServer();
         }

         this.thread = std::make_shared<Thread>(ThreadGroups.Network, this::threadRun, "UdpEngine");
         this.thread.setDaemon(true);
         this.thread.start();
      }
   }

    void threadRun() {
      while (!this.bQuit) {
    ByteBuffer var1 = this.Receive();
         if (!this.bQuit) {
            try {
               this.decode(var1);
            } catch (Exception var3) {
               DebugLog.Network.printException(var3, "Exception thrown during decode.", LogSeverity.Error);
            }
            continue;
         }
         break;
      }
   }

    void Shutdown() {
      DebugLog.log("waiting for UdpEngine thread termination");
      this.bQuit = true;

      while (this.thread.isAlive()) {
         try {
            Thread.sleep(10L);
         } catch (InterruptedException var2) {
         }
      }

      this.peer.Shutdown();
   }

    void SetServerPassword(const std::string& var1) {
      if (this.peer != nullptr) {
         this.peer.SetIncomingPassword(var1);
      }
   }

    std::string hashServerPassword(const std::string& var1) {
      return PZcrypt.hash(var1, true);
   }

    std::string getServerIP() {
      return this.peer.GetServerIP();
   }

    long getClientSteamID(long var1) {
      return this.peer.GetClientSteamID(var1);
   }

    long getClientOwnerSteamID(long var1) {
      return this.peer.GetClientOwnerSteamID(var1);
   }

    ByteBufferWriter startPacket() {
      this.bufferLock.lock();
      this.bb.clear();
      return this.bbw;
   }

    void endPacketBroadcast(PacketType var1) {
      this.bb.flip();
      this.peer.Send(this.bb, var1.PacketPriority, var1.PacketPriority, (byte)0, -1L, true);
      this.bufferLock.unlock();
   }

    void endPacketBroadcastExcept(int var1, int var2, UdpConnection var3) {
      this.bb.flip();
      this.peer.Send(this.bb, var1, var2, (byte)0, var3.connectedGUID, true);
      this.bufferLock.unlock();
   }

    void connected() {
      VoiceManager.instance.VoiceConnectReq(GameClient.connection.getConnectedGUID());
      if (GameClient.bClient && !GameClient.askPing) {
         GameClient.startAuth = Calendar.getInstance();
    ByteBufferWriter var2 = GameClient.connection.startPacket();
         PacketType.Login.doPacket(var2);
         var2.putUTF(GameClient.username);
         var2.putUTF(PZcrypt.hash(ServerWorldDatabase.encrypt(GameClient.password)));
         var2.putUTF(Core.getInstance().getVersion());
         PacketType.Login.send(GameClient.connection);
         RequestDataManager.getInstance().clear();
         ConnectionManager.log("send-packet", "login", GameClient.connection);
      } else if (GameClient.bClient && GameClient.askPing) {
    ByteBufferWriter var1 = GameClient.connection.startPacket();
         PacketType.Ping.doPacket(var1);
         var1.putUTF(GameClient.ip);
         PacketType.Ping.send(GameClient.connection);
         RequestDataManager.getInstance().clear();
      }
   }

    void decode(ByteBuffer var1) {
    int var2 = var1.get() & 255;
      switch (var2) {
         case 0:
         case 1:
            break;
         case 16:
    int var22 = var1.get() & 255;
    long var25 = this.peer.getGuidOfPacket();
            if (GameClient.bClient) {
               GameClient.connection = this.addConnection(var22, var25);
               ConnectionManager.log("RakNet", "connection-request-accepted", this.connectionArray[var22]);
               if (!SteamUtils.isSteamModeEnabled()) {
                  this.connected();
               } else {
                  GameClient.steamID = SteamUser.GetSteamID();
               }
            } else {
               ConnectionManager.log("RakNet", "connection-request-accepted", this.connectionArray[var22]);
            }
            break;
         case 17:
            ConnectionManager.log("RakNet", "connection-attempt-failed", nullptr);
            if (GameClient.bClient) {
               GameClient.instance.addDisconnectPacket(var2);
            }
            break;
         case 18:
            ConnectionManager.log("RakNet", "already-connected", nullptr);
            if (GameClient.bClient) {
               GameClient.instance.addDisconnectPacket(var2);
            }
            break;
         case 19:
    int var21 = var1.get() & 255;
    long var24 = this.peer.getGuidOfPacket();
            this.addConnection(var21, var24);
            ConnectionManager.log("RakNet", "new-incoming-connection", this.connectionArray[var21]);
            break;
         case 20:
    int var20 = var1.get() & 255;
            ConnectionManager.log("RakNet", "no-free-incoming-connections", this.connectionArray[var20]);
            break;
         case 21:
    int var19 = var1.get() & 255;
    long var23 = this.peer.getGuidOfPacket();
            ConnectionManager.log("RakNet", "disconnection-notification", this.connectionArray[var19]);
            this.removeConnection(var19);
            if (GameClient.bClient) {
               GameClient.instance.addDisconnectPacket(var2);
            }
            break;
         case 22:
    int var18 = var1.get() & 255;
            ConnectionManager.log("RakNet", "connection-lost", this.connectionArray[var18]);
            this.removeConnection(var18);
            break;
         case 23:
    int var17 = var1.get() & 255;
            ConnectionManager.log("RakNet", "connection-banned", this.connectionArray[var17]);
            if (GameClient.bClient) {
               GameClient.instance.addDisconnectPacket(var2);
            }
            break;
         case 24:
    int var16 = var1.get() & 255;
            ConnectionManager.log("RakNet", "invalid-password", this.connectionArray[var16]);
            if (GameClient.bClient) {
               GameClient.instance.addDisconnectPacket(var2);
            }
            break;
         case 25:
            ConnectionManager.log("RakNet", "incompatible-protocol-version", nullptr);
    std::string var15 = GameWindow.ReadString(var1);
            LuaEventManager.triggerEvent("OnConnectionStateChanged", "ClientVersionMismatch", var15);
            break;
         case 31:
    int var14 = var1.get() & 255;
            ConnectionManager.log("RakNet", "remote-disconnection-notification", this.connectionArray[var14]);
            break;
         case 32:
    int var13 = var1.get() & 255;
            ConnectionManager.log("RakNet", "remote-connection-lost", this.connectionArray[var13]);
            if (GameClient.bClient) {
               GameClient.instance.addDisconnectPacket(var2);
            }
            break;
         case 33:
    int var12 = var1.get() & 255;
            ConnectionManager.log("RakNet", "remote-new-incoming-connection", this.connectionArray[var12]);
            break;
         case 44:
    long var11 = this.peer.getGuidOfPacket();
            VoiceManager.instance.VoiceConnectAccept(var11);
            break;
         case 45:
    long var10 = this.peer.getGuidOfPacket();
            VoiceManager.instance.VoiceOpenChannelReply(var10, var1);
            break;
         case 46:
    long var9 = this.peer.getGuidOfPacket();
    UdpConnection var26 = this.connectionMap.get(var9);
            break;
         case 134:
    short var8 = var1.getShort();
            if (GameServer.bServer) {
    long var4 = this.peer.getGuidOfPacket();
    UdpConnection var6 = this.connectionMap.get(var4);
               if (var6 == nullptr) {
                  DebugLog.Network.warn("GOT PACKET FROM UNKNOWN CONNECTION guid=%s packetId=%s", new Object[]{var4, int.valueOf(var8)});
                  return;
               }

               GameServer.addIncoming((short)var8, var1, var6);
            } else {
               GameClient.instance.addIncoming((short)var8, var1);
            }
            break;
         default:
            DebugLog.Network.warn("Received unknown packet: %s", new Object[]{var2});
            if (GameServer.bServer) {
    long var3 = this.peer.getGuidOfPacket();
    UdpConnection var5 = this.connectionMap.get(var3);

               try {
                  if (ServerOptions.instance.AntiCheatProtectionType10.getValue() && PacketValidator.checkUser(var5)) {
                     PacketValidator.doKickUser(var5, std::string.valueOf(var2), "Type10", nullptr);
                  }
               } catch (Exception var7) {
                  var7.printStackTrace();
               }
            }
      }
   }

    void removeConnection(int var1) {
    UdpConnection var2 = this.connectionArray[var1];
      if (var2 != nullptr) {
         this.connectionArray[var1] = nullptr;
         this.connectionMap.remove(var2.getConnectedGUID());
         if (GameClient.bClient) {
            GameClient.instance.connectionLost();
         }

         if (GameServer.bServer) {
            GameServer.addDisconnect(var2);
         }
      }
   }

    UdpConnection addConnection(int var1, long var2) {
    UdpConnection var4 = std::make_shared<UdpConnection>(this, var2, var1);
      this.connectionMap.put(var2, var4);
      this.connectionArray[var1] = var4;
      if (GameServer.bServer) {
         GameServer.addConnection(var4);
      }

    return var4;
   }

    ByteBuffer Receive() {
    bool var1 = false;

      do {
         var1 = this.peer.Receive(this.buf);
         if (var1) {
            return this.buf;
         }

         try {
            Thread.sleep(1L);
         } catch (InterruptedException var3) {
            var3.printStackTrace();
         }
      } while (!this.bQuit && !var1);

      return this.buf;
   }

    UdpConnection getActiveConnection(long var1) {
      return !this.connectionMap.containsKey(var1) ? nullptr : this.connectionMap.get(var1);
   }

    void Connect(const std::string& var1, int var2, const std::string& var3, bool var4) {
      if (var2 == 0 && SteamUtils.isSteamModeEnabled()) {
    long var10 = 0L;

         try {
            var10 = SteamUtils.convertStringToSteamID(var1);
         } catch (NumberFormatException var9) {
            var9.printStackTrace();
            LuaEventManager.triggerEvent("OnConnectFailed", Translator.getText("UI_OnConnectFailed_UnknownHost"));
            return;
         }

         this.peer.ConnectToSteamServer(var10, this.hashServerPassword(var3), var4);
      } else {
    std::string var5;
         try {
    InetAddress var6 = InetAddress.getByName(var1);
            var5 = var6.getHostAddress();
         } catch (UnknownHostException var8) {
            var8.printStackTrace();
            LuaEventManager.triggerEvent("OnConnectFailed", Translator.getText("UI_OnConnectFailed_UnknownHost"));
            return;
         }

         this.peer.Connect(var5, var2, this.hashServerPassword(var3), var4);
      }
   }

    void forceDisconnect(long var1, const std::string& var3) {
      this.peer.disconnect(var1, var3);
      this.removeConnection(var1);
   }

    void removeConnection(long var1) {
    UdpConnection var3 = this.connectionMap.remove(var1);
      if (var3 != nullptr) {
         this.removeConnection(var3.index);
      }
   }

    RakNetPeerInterface getPeer() {
      return this.peer;
   }

    int getMaxConnections() {
      return this.maxConnections;
   }

    std::string getDescription() {
      return "connections=["
         + this.connections.size()
         + "/"
         + this.connectionMap.size()
         + "/"
         + Arrays.stream(this.connectionArray).filter(Objects::nonNull).count()
         + "/"
         + this.peer.GetConnectionsNumber()
         + "]";
   }
}
} // namespace raknet
} // namespace core
} // namespace zombie
