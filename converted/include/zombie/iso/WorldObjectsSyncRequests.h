#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/PacketTypes.h"
#include <filesystem>

namespace zombie {
namespace iso {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class WorldObjectsSyncRequests {
public:
 public ArrayList<WorldObjectsSyncRequests.SyncData> requests = std::make_unique<ArrayList<>>();
 long timeout = 1000L;

 void putRequest(IsoChunk chunk) {
 WorldObjectsSyncRequests.SyncData syncData = new WorldObjectsSyncRequests.SyncData();
 syncData.x = chunk.wx;
 syncData.y = chunk.wy;
 syncData.hashCodeWorldObjects = chunk.getHashCodeObjects();
 syncData.reqTime = 0L;
 syncData.reqCount = 0;
 synchronized (this->requests) {
 this->requests.add(syncData);
 }
 }

 void sendRequests(UdpConnection udpConnection) {
 if (this->requests.size() != 0) {
 ByteBufferWriter byteBufferWriter = udpConnection.startPacket();
 PacketTypes.PacketType.SyncWorldObjectsReq.doPacket(byteBufferWriter);
 ByteBuffer byteBuffer = byteBufferWriter.bb;
 int int0 = byteBuffer.position();
 byteBufferWriter.putShort((short)0);
 int int1 = 0;
 synchronized (this->requests) {
 for (int int2 = 0; int2 < this->requests.size(); int2++) {
 WorldObjectsSyncRequests.SyncData syncData = this->requests.get(int2);
 if (syncData.reqCount > 2) {
 this->requests.remove(int2);
 int2--;
 } else {
 if (syncData.reqTime == 0L) {
 syncData.reqTime = System.currentTimeMillis();
 int1++;
 byteBuffer.putInt(syncData.x);
 byteBuffer.putInt(syncData.y);
 byteBuffer.putLong(syncData.hashCodeWorldObjects);
 syncData.reqCount++;
 }

 if (System.currentTimeMillis() - syncData.reqTime >= this->timeout) {
 syncData.reqTime = System.currentTimeMillis();
 int1++;
 byteBuffer.putInt(syncData.x);
 byteBuffer.putInt(syncData.y);
 byteBuffer.putLong(syncData.hashCodeWorldObjects);
 syncData.reqCount++;
 }

 if (int1 >= 50) {
 break;
 }
 }
 }
 }

 if (int1 == 0) {
 GameClient.connection.cancelPacket();
 } else {
 int int3 = byteBuffer.position();
 byteBuffer.position(int0);
 byteBuffer.putShort((short)int1);
 byteBuffer.position(int3);
 PacketTypes.PacketType.SyncWorldObjectsReq.send(GameClient.connection);
 }
 }
 }

 void receiveIsoSync(int int2, int int1) {
 synchronized (this->requests) {
 for (int int0 = 0; int0 < this->requests.size(); int0++) {
 WorldObjectsSyncRequests.SyncData syncData = this->requests.get(int0);
 if (syncData.x == int2 && syncData.y == int1) {
 this->requests.remove(int0);
 }
 }
 }
 }

 class SyncData {
 int x;
 int y;
 long hashCodeWorldObjects;
 long reqTime;
 int reqCount;
 }
}
} // namespace iso
} // namespace zombie
