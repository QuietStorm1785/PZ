#pragma once
#include "zombie/GameWindow.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/iso/areas/SafeHouse.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/PacketValidator.h"
#include "zombie/network/ServerOptions.h"
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

class SyncSafehousePacket {
public:
 const uint8_t requiredManagerAccessLevel = 56;
 int x;
 int y;
 short w;
 short h;
 std::string ownerUsername;
 ArrayList<String> members = std::make_unique<ArrayList<>>();
 ArrayList<String> membersRespawn = std::make_unique<ArrayList<>>();
 bool remove = false;
 std::string title = "";
 SafeHouse safehouse;
 bool shouldCreateChat;

 void set(SafeHouse safeHouse, bool boolean0) {
 this->x = safeHouse.getX();
 this->y = safeHouse.getY();
 this->w = (short)safeHouse.getW();
 this->h = (short)safeHouse.getH();
 this->ownerUsername = safeHouse.getOwner();
 this->members.clear();
 this->members.addAll(safeHouse.getPlayers());
 this->membersRespawn.clear();
 this->membersRespawn.addAll(safeHouse.playersRespawn);
 this->remove = boolean0;
 this->title = safeHouse.getTitle();
 }

 void parse(ByteBuffer byteBuffer, UdpConnection var2) {
 this->x = byteBuffer.getInt();
 this->y = byteBuffer.getInt();
 this->w = byteBuffer.getShort();
 this->h = byteBuffer.getShort();
 this->ownerUsername = GameWindow.ReadString(byteBuffer);
 short short0 = byteBuffer.getShort();
 this->members.clear();

 for (int int0 = 0; int0 < short0; int0++) {
 this->members.add(GameWindow.ReadString(byteBuffer);
 }

 short short1 = byteBuffer.getShort();

 for (int int1 = 0; int1 < short1; int1++) {
 this->membersRespawn.add(GameWindow.ReadString(byteBuffer);
 }

 this->remove = byteBuffer.get() == 1;
 this->title = GameWindow.ReadString(byteBuffer);
 }

 void write(ByteBufferWriter byteBufferWriter) {
 byteBufferWriter.putInt(this->x);
 byteBufferWriter.putInt(this->y);
 byteBufferWriter.putShort(this->w);
 byteBufferWriter.putShort(this->h);
 byteBufferWriter.putUTF(this->ownerUsername);
 byteBufferWriter.putShort((short)this->members.size());

 for (String string0 : this->members) {
 byteBufferWriter.putUTF(string0);
 }

 byteBufferWriter.putShort((short)this->membersRespawn.size());

 for (String string1 : this->membersRespawn) {
 byteBufferWriter.putUTF(string1);
 }

 byteBufferWriter.putByte((byte)(this->remove ? 1 : 0);
 byteBufferWriter.putUTF(this->title);
 }

 void process() {
 this->safehouse = SafeHouse.getSafeHouse(this->x, this->y, this->w, this->h);
 this->shouldCreateChat = false;
 if (this->safehouse.empty()) {
 this->safehouse =
 SafeHouse.addSafeHouse(this->x, this->y, this->w, this->h,
 this->ownerUsername, GameClient.bClient);
 this->shouldCreateChat = true;
 }

 if (this->safehouse != nullptr) {
 this->safehouse.getPlayers().clear();
 this->safehouse.getPlayers().addAll(this->members);
 this->safehouse.playersRespawn.clear();
 this->safehouse.playersRespawn.addAll(this->membersRespawn);
 this->safehouse.setTitle(this->title);
 this->safehouse.setOwner(this->ownerUsername);
 if (this->remove) {
 SafeHouse.getSafehouseList().remove(this->safehouse);
 DebugLog.log("safehouse: removed " + this->x + "," + this->y + "," +
 this->w + "," + this->h +
 " owner=" + this->safehouse.getOwner());
 }
 }
 }

 bool validate(UdpConnection udpConnection) {
 bool boolean0 = (udpConnection.accessLevel & 56) != 0;
 this->safehouse = SafeHouse.getSafeHouse(this->x, this->y, this->w, this->h);
 if (this->safehouse.empty()) {
 if (udpConnection.accessLevel == 1 &&
 SafeHouse.hasSafehouse(this->ownerUsername) != nullptr) {
 if (ServerOptions.instance.AntiCheatProtectionType19.getValue() &&
 PacketValidator.checkUser(udpConnection) {
 PacketValidator.doKickUser(udpConnection,
 this->getClass().getSimpleName(), "Type19",
 this->getDescription());
 }

 return false;
 } else {
 double double0 =
 100.0 *
 ServerOptions.instance.AntiCheatProtectionType20ThresholdMultiplier
 .getValue();
 if (udpConnection.accessLevel == 1 &&
 (this->h > double0 || this->w > double0) {
 if (ServerOptions.instance.AntiCheatProtectionType20.getValue() &&
 PacketValidator.checkUser(udpConnection) {
 PacketValidator.doKickUser(udpConnection,
 this->getClass().getSimpleName(),
 "Type20", this->getDescription());
 }

 return false;
 } else {
 return true;
 }
 }
 } else {
 return !boolean0 ? true
 : PacketValidator.checkSafehouseAuth(
 udpConnection, this->safehouse.getOwner(),
 this->getClass().getSimpleName());
 }
 }

 std::string getDescription() {
 std::string string = "\n\t" + this->getClass().getSimpleName() + " [";
 string = string + "position=(" + this->x + ", " + this->y + ", " + this->w +
 ", " + this->h + ") | ";
 string = string + "ownerUsername=" + this->ownerUsername + " | ";
 string =
 string + "members=" + Arrays.toString(this->members.toArray()) + " | ";
 string = string + "membersRespawn=" +
 Arrays.toString(this->membersRespawn.toArray()) + " | ";
 string = string + "remove=" + this->remove + " | ";
 return string + "title=" + this->title + "] ";
 }
}
} // namespace packets
} // namespace network
} // namespace zombie
