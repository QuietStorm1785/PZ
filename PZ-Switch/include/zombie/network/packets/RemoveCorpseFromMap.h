#pragma once
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/iso/objects/IsoDeadBody.h"
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

class RemoveCorpseFromMap {
public:
 short id;
 IsoDeadBody deadBody = nullptr;

 void set(IsoDeadBody deadBodyx) {
 this->id = deadBodyx.getObjectID();
 this->deadBody = deadBodyx;
 }

 void parse(ByteBuffer byteBuffer, UdpConnection var2) {
 this->id = byteBuffer.getShort();
 this->deadBody = IsoDeadBody.getDeadBody(this->id);
 }

 void write(ByteBufferWriter byteBufferWriter) {
 byteBufferWriter.putShort(this->id);
 }

 void process() {
 if (this->isConsistent()) {
 IsoDeadBody.removeDeadBody(this->id);
 }
 }

 std::string getDescription() {
 return String.format(this->getClass().getSimpleName() + " id=%d", this->id);
 }

 bool isConsistent() {
 return this->deadBody != nullptr && this->deadBody.getSquare() != nullptr;
 }

 bool isRelevant(UdpConnection udpConnection) {
 return udpConnection.RelevantTo(this->deadBody.getX(), this->deadBody.getY());
 }
}
} // namespace packets
} // namespace network
} // namespace zombie
