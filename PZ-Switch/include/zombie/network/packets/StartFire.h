#pragma once
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/objects/IsoFire.h"
#include "zombie/iso/objects/IsoFireManager.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/PacketValidator.h"
#include "zombie/network/ServerOptions.h"
#include "zombie/network/packets/hit/Square.h"
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

class StartFire {
public:
 const Square square = new Square();
 int fireEnergy;
 bool ignite;
 int life;
 bool smoke;
 int spreadDelay;
 int numParticles;

 void set(IsoGridSquare squarex, bool boolean0, int int0, int int1,
 bool boolean1) {
 this->square.set(squarex);
 this->fireEnergy = int0;
 this->ignite = boolean0;
 this->life = int1;
 this->smoke = boolean1;
 this->spreadDelay = 0;
 this->numParticles = 0;
 }

 void parse(ByteBuffer byteBuffer, UdpConnection udpConnection) {
 this->square.parse(byteBuffer, udpConnection);
 this->fireEnergy = byteBuffer.getInt();
 this->ignite = byteBuffer.get() == 1;
 this->life = byteBuffer.getInt();
 this->smoke = byteBuffer.get() == 1;
 if (GameClient.bClient) {
 this->spreadDelay = byteBuffer.getInt();
 this->numParticles = byteBuffer.getInt();
 }
 }

 void write(ByteBufferWriter byteBufferWriter) {
 this->square.write(byteBufferWriter);
 byteBufferWriter.putInt(this->fireEnergy);
 byteBufferWriter.putBoolean(this->ignite);
 byteBufferWriter.putInt(this->life);
 byteBufferWriter.putBoolean(this->smoke);
 if (GameServer.bServer) {
 byteBufferWriter.putInt(this->spreadDelay);
 byteBufferWriter.putInt(this->numParticles);
 }
 }

 void process() {
 if (GameServer.bServer) {
 IsoFire fire0 = this->smoke
 ? new IsoFire(this->square.getSquare().getCell(),
 this->square.getSquare(), this->ignite,
 this->fireEnergy, this->life, true)
 : new IsoFire(this->square.getSquare().getCell(),
 this->square.getSquare(), this->ignite,
 this->fireEnergy, this->life);
 IsoFireManager.Add(fire0);
 this->spreadDelay = fire0.getSpreadDelay();
 this->numParticles = fire0.numFlameParticles;
 this->square.getSquare().getObjects().add(fire0);
 }

 if (GameClient.bClient) {
 IsoFire fire1 = this->smoke
 ? new IsoFire(IsoWorld.instance.CurrentCell,
 this->square.getSquare(), this->ignite,
 this->fireEnergy, this->life, true)
 : new IsoFire(IsoWorld.instance.CurrentCell,
 this->square.getSquare(), this->ignite,
 this->fireEnergy, this->life);
 fire1.SpreadDelay = this->spreadDelay;
 fire1.numFlameParticles = this->numParticles;
 IsoFireManager.Add(fire1);
 this->square.getSquare().getObjects().add(fire1);
 }
 }

 bool isConsistent() {
 return this->square.getSquare() != nullptr && this->life <= 500;
 }

 bool validate(UdpConnection udpConnection) {
 if (GameServer.bServer && !this->smoke &&
 ServerOptions.instance.NoFire.getValue()) {
 if (ServerOptions.instance.AntiCheatProtectionType16.getValue() &&
 PacketValidator.checkUser(udpConnection) {
 PacketValidator.doKickUser(udpConnection,
 this->getClass().getSimpleName(), "Type16",
 this->getDescription());
 }

 return false;
 } else if (!this->smoke && !IsoFire.CanAddFire(this->square.getSquare(),
 this->ignite, this->smoke) {
 DebugLog.log("not adding fire that on " + this->square.getX() + "," +
 this->square.getY());
 if (ServerOptions.instance.AntiCheatProtectionType17.getValue() &&
 PacketValidator.checkUser(udpConnection) {
 PacketValidator.doKickUser(udpConnection,
 this->getClass().getSimpleName(), "Type17",
 this->getDescription());
 }

 return false;
 } else if (this->smoke &&
 !IsoFire.CanAddSmoke(this->square.getSquare(), this->ignite) {
 if (ServerOptions.instance.AntiCheatProtectionType18.getValue() &&
 PacketValidator.checkUser(udpConnection) {
 PacketValidator.doKickUser(udpConnection,
 this->getClass().getSimpleName(), "Type18",
 this->getDescription());
 }

 return false;
 } else {
 return GameClient.bClient ||
 udpConnection.RelevantTo(this->square.getX(), this->square.getY());
 }
 }

 std::string getDescription() {
 std::string string = "\n\t" + this->getClass().getSimpleName() + " [";
 string = string + "square=" + this->square.getDescription() + " | ";
 string = string + "fireEnergy=" + this->fireEnergy + " | ";
 string = string + "ignite=" + this->ignite + " | ";
 string = string + "life=" + this->life + " | ";
 string = string + "smoke=" + this->smoke + " | ";
 string = string + "spreadDelay=" + this->spreadDelay + " | ";
 return string + "numParticles=" + this->numParticles + "] ";
 }
}
} // namespace packets
} // namespace network
} // namespace zombie
