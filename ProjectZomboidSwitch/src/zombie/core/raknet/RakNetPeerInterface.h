#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/utils/BufferUtils.h"
#include "zombie/Lua/LuaEventManager.h"
#include "zombie/core/Core.h"
#include "zombie/core/znet/ZNetStatistics.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/network/GameClient.h"
#include <algorithm>
#include <filesystem>

namespace zombie {
namespace core {
namespace raknet {


class RakNetPeerInterface {
public:
    static Thread mainThread;
    static const int ID_NEW_INCOMING_CONNECTION = 19;
    static const int ID_DISCONNECTION_NOTIFICATION = 21;
    static const int ID_INCOMPATIBLE_PROTOCOL_VERSION = 25;
    static const int ID_CONNECTED_PING = 0;
    static const int ID_UNCONNECTED_PING = 1;
    static const int ID_CONNECTION_LOST = 22;
    static const int ID_ALREADY_CONNECTED = 18;
    static const int ID_REMOTE_DISCONNECTION_NOTIFICATION = 31;
    static const int ID_REMOTE_CONNECTION_LOST = 32;
    static const int ID_REMOTE_NEW_INCOMING_CONNECTION = 33;
    static const int ID_CONNECTION_BANNED = 23;
    static const int ID_CONNECTION_ATTEMPT_FAILED = 17;
    static const int ID_NO_FREE_INCOMING_CONNECTIONS = 20;
    static const int ID_CONNECTION_REQUEST_ACCEPTED = 16;
    static const int ID_INVALID_PASSWORD = 24;
    static const int ID_PING = 28;
    static const int ID_RAKVOICE_OPEN_CHANNEL_REQUEST = 44;
    static const int ID_RAKVOICE_OPEN_CHANNEL_REPLY = 45;
    static const int ID_RAKVOICE_CLOSE_CHANNEL = 46;
    static const int ID_USER_PACKET_ENUM = 134;
    static const int PacketPriority_IMMEDIATE = 0;
    static const int PacketPriority_HIGH = 1;
    static const int PacketPriority_MEDIUM = 2;
    static const int PacketPriority_LOW = 3;
    static const int PacketReliability_UNRELIABLE = 0;
    static const int PacketReliability_UNRELIABLE_SEQUENCED = 1;
    static const int PacketReliability_RELIABLE = 2;
    static const int PacketReliability_RELIABLE_ORDERED = 3;
    static const int PacketReliability_RELIABLE_SEQUENCED = 4;
    static const int PacketReliability_UNRELIABLE_WITH_ACK_RECEIPT = 5;
    static const int PacketReliability_RELIABLE_WITH_ACK_RECEIPT = 6;
    static const int PacketReliability_RELIABLE_ORDERED_WITH_ACK_RECEIPT = 7;
    static const uint8_t ConnectionType_Disconnected = 0;
    static const uint8_t ConnectionType_UDPRakNet = 1;
    static const uint8_t ConnectionType_Steam = 2;
    ByteBuffer receiveBuf = BufferUtils.createByteBuffer(1000000);
    ByteBuffer sendBuf = BufferUtils.createByteBuffer(1000000);
    Lock sendLock = std::make_shared<ReentrantLock>();

    static void init() {
      mainThread = Thread.currentThread();
   }

   public native void Init(boolean var1);

   private native int Startup(int var1, std::string var2);

    int Startup(int var1) {
      return this.Startup(var1, Core.getInstance().getVersion());
   }

   public native void Shutdown();

   public native void SetServerIP(std::string var1);

   public native void SetServerPort(int var1, int var2);

   public native void SetClientPort(int var1);

   public native int Connect(std::string var1, int var2, std::string var3, boolean var4);

   public native int ConnectToSteamServer(long var1, std::string var3, boolean var4);

   public native std::string GetServerIP();

   public native long GetClientSteamID(long var1);

   public native long GetClientOwnerSteamID(long var1);

   public native void SetIncomingPassword(std::string var1);

   public native void SetTimeoutTime(int var1);

   public native void SetMaximumIncomingConnections(int var1);

   public native void SetOccasionalPing(boolean var1);

   public native void SetUnreliableTimeout(int var1);

   private native boolean TryReceive();

   private native int nativeGetData(ByteBuffer var1);

    bool Receive(ByteBuffer var1) {
      if (this.TryReceive()) {
         try {
            var1.clear();
            this.receiveBuf.clear();
    int var2 = this.nativeGetData(this.receiveBuf);
            var1.put(this.receiveBuf);
            var1.flip();
    return true;
         } catch (Exception var3) {
            var3.printStackTrace();
    return false;
         }
      } else {
    return false;
      }
   }

    int Send(ByteBuffer var1, int var2, int var3, uint8_t var4, long var5, bool var7) {
      this.sendLock.lock();
      this.sendBuf.clear();
      if (var1.remaining() > this.sendBuf.remaining()) {
         System.out.println("Packet data too big.");
         this.sendLock.unlock();
    return 0;
      } else {
         try {
            this.sendBuf.put(var1);
            this.sendBuf.flip();
    int var8 = this.sendNative(this.sendBuf, this.sendBuf.remaining(), var2, var3, var4, var5, var7);
            this.sendLock.unlock();
    return var8;
         } catch (Exception var9) {
            System.out.println("Other weird packet data error.");
            var9.printStackTrace();
            this.sendLock.unlock();
    return 0;
         }
      }
   }

    int SendRaw(ByteBuffer var1, int var2, int var3, uint8_t var4, long var5, bool var7) {
      try {
         return this.sendNative(var1, var1.remaining(), var2, var3, var4, var5, var7);
      } catch (Exception var9) {
         System.out.println("Other weird packet data error.");
         var9.printStackTrace();
    return 0;
      }
   }

   private native int sendNative(ByteBuffer var1, int var2, int var3, int var4, byte var5, long var6, boolean var8);

   public native long getGuidFromIndex(int var1);

   public native long getGuidOfPacket();

   public native std::string getIPFromGUID(long var1);

   public native void disconnect(long var1, std::string var3);

    void connectionStateChangedCallback(const std::string& var1, const std::string& var2) {
    Thread var3 = Thread.currentThread();
      if (var3 == mainThread) {
         LuaEventManager.triggerEvent("OnConnectionStateChanged", var1, var2);
      } else {
         DebugLog.Multiplayer.debugln("state=\"%s\", message=\"%s\", thread=%s", var1, var2, var3);
      }

      if (GameClient.bClient && "Connected" == var1)) {
         GameClient.instance.udpEngine.connected();
      }
   }

   public native ZNetStatistics GetNetStatistics(long var1);

   public native int GetAveragePing(long var1);

   public native int GetLastPing(long var1);

   public native int GetLowestPing(long var1);

   public native int GetMTUSize(long var1);

   public native int GetConnectionsNumber();

   public native byte GetConnectionType(long var1);
}
} // namespace raknet
} // namespace core
} // namespace zombie
