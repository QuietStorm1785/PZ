#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/lwjglx/BufferUtils.h"
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
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


/**
 * Created by LEMMYPC on 10/01/14.
 */
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
 Lock sendLock = std::make_unique<ReentrantLock>();

 static void init() {
 mainThread = Thread.currentThread();
 }

 public void Init(boolean steamMode);

 private int Startup(int var1, String var2);

 int Startup(int maxConnections) {
 return this->Startup(maxConnections, Core.getInstance().getVersion());
 }

 public void Shutdown();

 public void SetServerIP(String ip);

 public void SetServerPort(int port, int UDPPort);

 public void SetClientPort(int port);

 public int Connect(String var1, int var2, String var3, boolean var4);

 public int ConnectToSteamServer(long var1, String var3, boolean var4);

 public String GetServerIP();

 public long GetClientSteamID(long guid);

 public long GetClientOwnerSteamID(long guid);

 public void SetIncomingPassword(String password);

 public void SetTimeoutTime(int time);

 public void SetMaximumIncomingConnections(int num);

 public void SetOccasionalPing(boolean bPing);

 public void SetUnreliableTimeout(int timeout);

 private boolean TryReceive();

 private int nativeGetData(ByteBuffer var1);

 bool Receive(ByteBuffer buffer) {
 if (this->TryReceive()) {
 try {
 buffer.clear();
 this->receiveBuf.clear();
 int int0 = this->nativeGetData(this->receiveBuf);
 buffer.put(this->receiveBuf);
 buffer.flip();
 return true;
 } catch (Exception exception) {
 exception.printStackTrace();
 return false;
 }
 } else {
 return false;
 }
 }

 int Send(ByteBuffer data, int PacketPriority, int PacketReliability, uint8_t orderingChannel, long guid, bool broadcast) {
 this->sendLock.lock();
 this->sendBuf.clear();
 if (data.remaining() > this->sendBuf.remaining()) {
 System.out.println("Packet data too big.");
 this->sendLock.unlock();
 return 0;
 } else {
 try {
 this->sendBuf.put(data);
 this->sendBuf.flip();
 int int0 = this->sendNative(this->sendBuf, this->sendBuf.remaining(), PacketPriority, PacketReliability, orderingChannel, guid, broadcast);
 this->sendLock.unlock();
 return int0;
 } catch (Exception exception) {
 System.out.println("Other weird packet data error.");
 exception.printStackTrace();
 this->sendLock.unlock();
 return 0;
 }
 }
 }

 int SendRaw(ByteBuffer data, int PacketPriority, int PacketReliability, uint8_t orderingChannel, long guid, bool broadcast) {
 try {
 return this->sendNative(data, data.remaining(), PacketPriority, PacketReliability, orderingChannel, guid, broadcast);
 } catch (Exception exception) {
 System.out.println("Other weird packet data error.");
 exception.printStackTrace();
 return 0;
 }
 }

 private int sendNative(ByteBuffer var1, int var2, int var3, int var4, byte var5, long var6, boolean var8);

 public long getGuidFromIndex(int id);

 public long getGuidOfPacket();

 public String getIPFromGUID(long guid);

 public void disconnect(long connectedGUID, String message);

 void connectionStateChangedCallback(const std::string& string0, const std::string& string1) {
 Thread thread = Thread.currentThread();
 if (thread == mainThread) {
 LuaEventManager.triggerEvent("OnConnectionStateChanged", string0, string1);
 } else {
 DebugLog.Multiplayer.debugln("state=\"%s\", message=\"%s\", thread=%s", string0, string1, thread);
 }

 if (GameClient.bClient && "Connected" == string0) {
 GameClient.instance.udpEngine.connected();
 }
 }

 public ZNetStatistics GetNetStatistics(long guid);

 public int GetAveragePing(long guid);

 public int GetLastPing(long guid);

 public int GetLowestPing(long guid);

 public int GetMTUSize(long guid);

 public int GetConnectionsNumber();

 public byte GetConnectionType(long guid);
}
} // namespace raknet
} // namespace core
} // namespace zombie
