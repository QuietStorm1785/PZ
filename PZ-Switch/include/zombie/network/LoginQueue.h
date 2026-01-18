#pragma once
#include <mutex>
#include "zombie/Lua/LuaEventManager.h"
#include "zombie/core/Core.h"
#include "zombie/core/logger/LoggerManager.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/core/utils/UpdateLimit.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/gameStates/LoadingQueueState.h"
#include <cstdint>
#include <filesystem>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace network {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class LoginQueue {
public:

 // Mutexes for synchronized blocks
 static std::mutex LoginQueue_mutex;
private
 static ArrayList<UdpConnection> LoginQueue = std::make_unique<ArrayList<>>();
private
 static ArrayList<UdpConnection> PreferredLoginQueue =
 std::make_unique<ArrayList<>>();
 static UdpConnection currentLoginQueue;
 static UpdateLimit UpdateLimit = new UpdateLimit(3050L);
 static UpdateLimit LoginQueueTimeout = new UpdateLimit(15000L);

 static void receiveClientLoginQueueRequest(ByteBuffer byteBuffer,
 short var1) {
 uint8_t byte0 = byteBuffer.get();
 if (byte0 ==
 LoginQueue.LoginQueueMessageType.ConnectionImmediate.ordinal()) {
 LoadingQueueState.onConnectionImmediate();
 } else if (byte0 ==
 LoginQueue.LoginQueueMessageType.PlaceInQueue.ordinal()) {
 int int0 = byteBuffer.getInt();
 LoadingQueueState.onPlaceInQueue(int0);
 LuaEventManager.triggerEvent("OnConnectionStateChanged", "FormatMessage",
 "PlaceInQueue", int0);
 }

 ConnectionManager.log("receive-packet", "login-queue-request", nullptr);
 }

 static void receiveLoginQueueDone(ByteBuffer byteBuffer,
 UdpConnection udpConnection, short var2) {
 long long0 = byteBuffer.getLong();
 LoggerManager.getLogger("user").write("player " + udpConnection.username +
 " loading time was: " + long0 +
 " ms");
 { std::lock_guard<std::mutex> __sync_lock__(LoginQueue_mutex);
 if (currentLoginQueue == udpConnection) {
 currentLoginQueue = nullptr;
 }

 loadNextPlayer();
 }

 ConnectionManager.log("receive-packet", "login-queue-done", udpConnection);
 udpConnection.validator.sendChecksum(true, false, false);
 }

 static void receiveServerLoginQueueRequest(ByteBuffer var0,
 UdpConnection udpConnection,
 short var2) {
 LoggerManager.getLogger("user").write(
 udpConnection.idStr + " \"" + udpConnection.username +
 "\" attempting to join used " +
 (udpConnection.preferredInQueue ? "preferred " : "") + "queue");
 { std::lock_guard<std::mutex> __sync_lock__(LoginQueue_mutex);
 if (!ServerOptions.getInstance().LoginQueueEnabled.getValue() ||
 !udpConnection.preferredInQueue && currentLoginQueue.empty() &&
 PreferredLoginQueue.empty() && LoginQueue.empty() ||
 udpConnection.preferredInQueue && currentLoginQueue.empty() &&
 PreferredLoginQueue.empty()) {
 if (Core.bDebug) {
 DebugLog.log(
 "receiveServerLoginQueueRequest: ConnectionImmediate (ip:" +
 udpConnection.ip + ")");
 }

 currentLoginQueue = udpConnection;
 currentLoginQueue.wasInLoadingQueue = true;
 LoginQueueTimeout.Reset(
 ServerOptions.getInstance().LoginQueueConnectTimeout.getValue() *
 1000);
 ByteBufferWriter byteBufferWriter = udpConnection.startPacket();
 PacketTypes.PacketType.LoginQueueRequest2.doPacket(byteBufferWriter);
 byteBufferWriter.putByte((byte)LoginQueue.LoginQueueMessageType
 .ConnectionImmediate.ordinal());
 PacketTypes.PacketType.LoginQueueRequest2.send(udpConnection);
 } else {
 if (Core.bDebug) {
 DebugLog.log("receiveServerLoginQueueRequest: PlaceInQueue (ip:" +
 udpConnection.ip + " preferredInQueue:" +
 udpConnection.preferredInQueue + ")");
 }

 if (udpConnection.preferredInQueue) {
 if (!PreferredLoginQueue.contains(udpConnection) {
 PreferredLoginQueue.add(udpConnection);
 }
 } else if (!LoginQueue.contains(udpConnection) {
 LoginQueue.add(udpConnection);
 }

 sendPlaceInTheQueue();
 }
 }

 ConnectionManager.log("receive-packet", "login-queue-request",
 udpConnection);
 }

 static void sendAccessDenied(UdpConnection udpConnection,
 const std::string &string) {
 if (Core.bDebug) {
 DebugLog.log("sendAccessDenied: (ip:" + udpConnection.ip +
 " message:" + string + ")");
 }

 ByteBufferWriter byteBufferWriter = udpConnection.startPacket();
 PacketTypes.PacketType.AccessDenied.doPacket(byteBufferWriter);
 byteBufferWriter.putUTF(string);
 PacketTypes.PacketType.AccessDenied.send(udpConnection);
 ConnectionManager.log("access-denied", "invalid-queue", udpConnection);
 udpConnection.forceDisconnect("queue-" + string);
 }

 static void sendPlaceInTheQueue() {
 for (auto &udpConnection0 : PreferredLoginQueue)
 ByteBufferWriter byteBufferWriter0 = udpConnection0.startPacket();
 PacketTypes.PacketType.LoginQueueRequest2.doPacket(byteBufferWriter0);
 byteBufferWriter0.putByte(
 (byte)LoginQueue.LoginQueueMessageType.PlaceInQueue.ordinal());
 byteBufferWriter0.putInt(PreferredLoginQueue.indexOf(udpConnection0) + 1);
 PacketTypes.PacketType.LoginQueueRequest2.send(udpConnection0);
 }

 for (auto &udpConnection1 : LoginQueue)
 ByteBufferWriter byteBufferWriter1 = udpConnection1.startPacket();
 PacketTypes.PacketType.LoginQueueRequest2.doPacket(byteBufferWriter1);
 byteBufferWriter1.putByte(
 (byte)LoginQueue.LoginQueueMessageType.PlaceInQueue.ordinal());
 byteBufferWriter1.putInt(PreferredLoginQueue.size() +
 LoginQueue.indexOf(udpConnection1) + 1);
 PacketTypes.PacketType.LoginQueueRequest2.send(udpConnection1);
}
}

static void sendConnectRequest(UdpConnection udpConnection) {
 if (Core.bDebug) {
 DebugLog.log("sendApplyRequest: (ip:" + udpConnection.ip + ")");
 }

 ByteBufferWriter byteBufferWriter = udpConnection.startPacket();
 PacketTypes.PacketType.LoginQueueRequest2.doPacket(byteBufferWriter);
 byteBufferWriter.putByte(
 (byte)LoginQueue.LoginQueueMessageType.ConnectionImmediate.ordinal());
 PacketTypes.PacketType.LoginQueueRequest2.send(udpConnection);
 ConnectionManager.log("send-packet", "login-queue-request", udpConnection);
}

static bool receiveLogin(UdpConnection udpConnection) {
 if (!ServerOptions.getInstance().LoginQueueEnabled.getValue()) {
 return true;
 } else {
 if (Core.bDebug) {
 DebugLog.log("receiveLogin: (ip:" + udpConnection.ip + ")");
 }

 if (udpConnection != currentLoginQueue) {
 sendAccessDenied(currentLoginQueue, "QueueNotFound");
 if (Core.bDebug) {
 DebugLog.log("receiveLogin: error");
 }

 return false;
 } else {
 if (Core.bDebug) {
 DebugLog.log("receiveLogin: ok");
 }

 return true;
 }
 }
}

static void disconnect(UdpConnection udpConnection) {
 if (Core.bDebug) {
 DebugLog.log("disconnect: (ip:" + udpConnection.ip + ")");
 }

 { std::lock_guard<std::mutex> __sync_lock__(LoginQueue_mutex);
 if (udpConnection == currentLoginQueue) {
 currentLoginQueue = nullptr;
 } else {
 if (LoginQueue.contains(udpConnection) {
 LoginQueue.remove(udpConnection);
 }

 if (PreferredLoginQueue.contains(udpConnection) {
 PreferredLoginQueue.remove(udpConnection);
 }
 }

 sendPlaceInTheQueue();
 }
}

static bool isInTheQueue(UdpConnection udpConnection) {
 if (!ServerOptions.getInstance().LoginQueueEnabled.getValue()) {
 return false;
 } else {
 { std::lock_guard<std::mutex> __sync_lock__(LoginQueue_mutex);
 return udpConnection = = currentLoginQueue ||
 LoginQueue.contains(udpConnection) ||
 PreferredLoginQueue.contains(udpConnection);
 }
 }
}

static void update() {
 if (ServerOptions.getInstance().LoginQueueEnabled.getValue() &&
 UpdateLimit.Check()) {
 { std::lock_guard<std::mutex> __sync_lock__(LoginQueue_mutex);
 if (currentLoginQueue != nullptr) {
 if (currentLoginQueue.isFullyConnected()) {
 if (Core.bDebug) {
 DebugLog.log(
 "update: isFullyConnected (ip:" + currentLoginQueue.ip + ")");
 }

 currentLoginQueue = nullptr;
 } else if (LoginQueueTimeout.Check()) {
 if (Core.bDebug) {
 DebugLog.log("update: timeout (ip:" + currentLoginQueue.ip + ")");
 }

 currentLoginQueue = nullptr;
 }
 }

 loadNextPlayer();
 }
 }
}

static void loadNextPlayer() {
 if (!PreferredLoginQueue.empty() && currentLoginQueue.empty()) {
 currentLoginQueue = PreferredLoginQueue.remove(0);
 currentLoginQueue.wasInLoadingQueue = true;
 if (Core.bDebug) {
 DebugLog.log(
 "update: Next player from the preferred queue to connect (ip:" +
 currentLoginQueue.ip + ")");
 }

 LoginQueueTimeout.Reset(
 ServerOptions.getInstance().LoginQueueConnectTimeout.getValue() * 1000);
 sendConnectRequest(currentLoginQueue);
 sendPlaceInTheQueue();
 }

 if (!LoginQueue.empty() && currentLoginQueue.empty()) {
 currentLoginQueue = LoginQueue.remove(0);
 currentLoginQueue.wasInLoadingQueue = true;
 if (Core.bDebug) {
 DebugLog.log(
 "update: Next player to connect (ip:" + currentLoginQueue.ip + ")");
 }

 LoginQueueTimeout.Reset(
 ServerOptions.getInstance().LoginQueueConnectTimeout.getValue() * 1000);
 sendConnectRequest(currentLoginQueue);
 sendPlaceInTheQueue();
 }
}

static std::string getDescription() {
 return "queue=[" + LoginQueue.size() + "/" + PreferredLoginQueue.size() +
 "/\"" +
 (currentLoginQueue.empty() ? ""
 : currentLoginQueue.getConnectedGUID()) +
 "\"]";
}

public
static enum LoginQueueMessageType { ConnectionImmediate, PlaceInQueue; }
}
} // namespace network
} // namespace zombie
