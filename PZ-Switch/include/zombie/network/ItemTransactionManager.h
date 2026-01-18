#pragma once
#include "zombie/GameTime.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/LogSeverity.h"
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

class ItemTransactionManager {
public:
private
 static HashSet<ItemTransactionManager.ItemRequest> requests =
 std::make_unique<HashSet<>>();

 static void update() {
 requests.removeIf(ItemTransactionManager.ItemRequest::isTimeout);
 }

 static bool isConsistent(int int0, int int1, int int2) {
 return requests.stream()
 .filter(itemRequest->int0 == itemRequest.itemID ||
 int1 == itemRequest.itemID || int2 == itemRequest.itemID ||
 int0 == itemRequest.srcID || int0 == itemRequest.dstID)
 .noneMatch(itemRequest->itemRequest.state == 1);
 }

 static void receiveOnClient(ByteBuffer byteBuffer, short var1) {
 try {
 uint8_t byte0 = byteBuffer.get();
 int int0 = byteBuffer.getInt();
 int int1 = byteBuffer.getInt();
 int int2 = byteBuffer.getInt();
 DebugLog.Multiplayer.debugln("%d [ %d : %d => %d ]", byte0, int0, int1,
 int2);
 requests.stream()
 .filter(itemRequest->int0 == itemRequest.itemID &&
 int1 == itemRequest.srcID && int2 == itemRequest.dstID)
 .forEach(itemRequest->itemRequest.setState(byte0);
 } catch (Exception exception) {
 DebugLog.Multiplayer.printException(exception, "ReceiveOnClient: failed",
 LogSeverity.Error);
 }
 }

 static void receiveOnServer(ByteBuffer byteBuffer,
 UdpConnection udpConnection, short var2) {
 try {
 uint8_t byte0 = byteBuffer.get();
 int int0 = byteBuffer.getInt();
 int int1 = byteBuffer.getInt();
 int int2 = byteBuffer.getInt();
 if (0 == byte0) {
 if (isConsistent(int0, int1, int2) {
 requests.add(
 new ItemTransactionManager.ItemRequest(int0, int1, int2);
 sendItemTransaction(udpConnection, (byte)2, int0, int1, int2);
 DebugLog.Multiplayer.trace("set accepted [ %d : %d => %d ]", int0,
 int1, int2);
 } else {
 sendItemTransaction(udpConnection, (byte)1, int0, int1, int2);
 DebugLog.Multiplayer.trace("set rejected [ %d : %d => %d ]", int0,
 int1, int2);
 }
 } else {
 requests.removeIf(itemRequest->int0 == itemRequest.itemID &&
 int1 == itemRequest.srcID &&
 int2 == itemRequest.dstID);
 DebugLog.Multiplayer.trace("remove processed [ %d : %d => %d ]", int0,
 int1, int2);
 }
 } catch (Exception exception) {
 DebugLog.Multiplayer.printException(exception, "ReceiveOnClient: failed",
 LogSeverity.Error);
 }
 }

 static void createItemTransaction(int int0, int int1, int int2) {
 if (isConsistent(int0, int1, int2) {
 requests.add(new ItemTransactionManager.ItemRequest(int0, int1, int2);
 sendItemTransaction(GameClient.connection, (byte)0, int0, int1, int2);
 }
 }

 static void removeItemTransaction(int int0, int int1, int int2) {
 if (requests.removeIf(itemRequest->int0 == itemRequest.itemID &&
 int1 == itemRequest.srcID &&
 int2 == itemRequest.dstID) {
 sendItemTransaction(GameClient.connection, (byte)2, int0, int1, int2);
 }
 }

 static void sendItemTransaction(UdpConnection udpConnection, uint8_t byte0,
 int int0, int int1, int int2) {
 if (udpConnection != nullptr) {
 ByteBufferWriter byteBufferWriter = udpConnection.startPacket();

 try {
 PacketTypes.PacketType.ItemTransaction.doPacket(byteBufferWriter);
 byteBufferWriter.putByte(byte0);
 byteBufferWriter.putInt(int0);
 byteBufferWriter.putInt(int1);
 byteBufferWriter.putInt(int2);
 PacketTypes.PacketType.ItemTransaction.send(udpConnection);
 } catch (Exception exception) {
 udpConnection.cancelPacket();
 DebugLog.Multiplayer.printException(
 exception, "SendItemTransaction: failed", LogSeverity.Error);
 }
 }
 }

private
 static class ItemRequest {
 static const uint8_t StateUnknown = 0;
 static const uint8_t StateRejected = 1;
 static const uint8_t StateAccepted = 2;
 const int itemID;
 const int srcID;
 const int dstID;
 const long timestamp;
 uint8_t state;

 private
 ItemRequest(int int0, int int1, int int2) {
 this->itemID = int0;
 this->srcID = int1;
 this->dstID = int2;
 this->timestamp = GameTime.getServerTimeMills() + 5000L;
 this->state = (byte)(GameServer.bServer ? 1 : 0);
 }

 void setState(uint8_t byte0) { this->state = byte0; }

 bool isTimeout() { return GameTime.getServerTimeMills() > this->timestamp; }
 }
}
} // namespace network
} // namespace zombie
