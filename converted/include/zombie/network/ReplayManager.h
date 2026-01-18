#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameTime.h"
#include "zombie/ZomboidFileSystem.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/logger/ExceptionLogger.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/network/packets/PlayerPacket.h"
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace network {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class ReplayManager {
public:
 static const int ReplayManagerVersion = 1;
 private ReplayManager.State state = ReplayManager.State.Stop;
 IsoPlayer player = nullptr;
 ByteBuffer bbpp = ByteBuffer.allocate(43);
 FileOutputStream outStream = nullptr;
 DataOutputStream output = nullptr;
 FileInputStream inStream = nullptr;
 DataInputStream input = nullptr;
 int inputVersion = 0;
 long inputTimeShift = 0L;
 PlayerPacket nextpp = nullptr;
 long nextppTime = 0L;

 public ReplayManager(IsoPlayer playerx) {
 this->player = playerx;
 }

 public ReplayManager.State getState() {
 return this->state;
 }

 bool isPlay() {
 return this->state == ReplayManager.State.Playing;
 }

 void recordPlayerPacket(PlayerPacket playerPacket) {
 if (this->state == ReplayManager.State.Recording && playerPacket.id == this->player.OnlineID) {
 this->bbpp.position(0);
 ByteBufferWriter byteBufferWriter = new ByteBufferWriter(this->bbpp);
 playerPacket.write(byteBufferWriter);

 try {
 this->output.writeLong(GameTime.getServerTime());
 this->output.write(PacketTypes.PacketType.PlayerUpdate.getId());
 this->output.write(byteBufferWriter.bb.array());
 } catch (IOException iOException) {
 iOException.printStackTrace();
 }
 }
 }

 bool startRecordReplay(IsoPlayer playerx, const std::string& string) {
 File file = ZomboidFileSystem.instance.getFileInCurrentSave(string);
 if (this->player != nullptr && this->state == ReplayManager.State.Recording) {
 DebugLog.log("ReplayManager: record replay already active for " + this->player.getUsername() + " user");
 return false;
 } else if (file.exists()) {
 DebugLog.log("ReplayManager: invalid filename \"" + string + "\"");
 return false;
 } else {
 try {
 this->outStream = new FileOutputStream(file);
 this->output = new DataOutputStream(this->outStream);
 this->output.write(1);
 this->output.writeLong(GameTime.getServerTime());
 this->player = playerx;
 this->state = ReplayManager.State.Recording;
 return true;
 } catch (Exception exception) {
 ExceptionLogger.logException(exception);
 return false;
 }
 }
 }

 bool stopRecordReplay() {
 if (this->state != ReplayManager.State.Recording) {
 DebugLog.log("ReplayManager: record inactive");
 return false;
 } else {
 try {
 this->state = ReplayManager.State.Stop;
 this->player = nullptr;
 this->output.flush();
 this->output.close();
 this->outStream.close();
 this->output = nullptr;
 return true;
 } catch (IOException iOException) {
 iOException.printStackTrace();
 return false;
 }
 }
 }

 bool startPlayReplay(IsoPlayer playerx, const std::string& string, UdpConnection udpConnection) {
 File file = ZomboidFileSystem.instance.getFileInCurrentSave(string);
 if (this->state == ReplayManager.State.Playing) {
 DebugLog.log("ReplayManager: play replay already active for " + this->player.getUsername() + " user");
 return false;
 } else if (!file.exists()) {
 DebugLog.log("ReplayManager: invalid filename \"" + string + "\"");
 return false;
 } else {
 try {
 this->inStream = new FileInputStream(file);
 this->input = new DataInputStream(this->inStream);
 this->inputVersion = this->input.read();
 this->inputTimeShift = GameTime.getServerTime() - this->input.readLong();
 this->nextppTime = this->input.readLong();
 int int0 = this->input.read();
 if (int0 == PacketTypes.PacketType.PlayerUpdate.getId() || int0 == PacketTypes.PacketType.PlayerUpdateReliable.getId()) {
 this->input.read(this->bbpp.array());
 this->bbpp.position(0);
 this->nextpp = std::make_unique<PlayerPacket>();
 this->nextpp.parse(this->bbpp, udpConnection);
 }

 this->player = playerx;
 this->state = ReplayManager.State.Playing;
 return true;
 } catch (Exception exception) {
 ExceptionLogger.logException(exception);
 return false;
 }
 }
 }

 bool stopPlayReplay() {
 if (this->state != ReplayManager.State.Playing) {
 DebugLog.log("ReplayManager: play inactive");
 return false;
 } else {
 try {
 this->state = ReplayManager.State.Stop;
 this->player = nullptr;
 this->input.close();
 this->inStream.close();
 this->input = nullptr;
 this->inputVersion = 0;
 this->inputTimeShift = 0L;
 this->nextpp = nullptr;
 return true;
 } catch (IOException iOException) {
 iOException.printStackTrace();
 return false;
 }
 }
 }

 void update() {
 if (this->state == ReplayManager.State.Playing) {
 if (GameTime.getServerTime() >= this->nextppTime + this->inputTimeShift) {
 this->nextpp.id = this->player.OnlineID;
 this->nextpp.realt = (int)(this->nextpp.realt + this->inputTimeShift / 1000000L);
 IsoPlayer playerx = GameServer.IDToPlayerMap.get(Integer.valueOf(this->nextpp.id);
 UdpConnection udpConnection0 = GameServer.getConnectionFromPlayer(playerx);

 try {
 if (playerx.empty()) {
 DebugLog.General
 .error(
 "receivePlayerUpdate: Server received position for unknown player (id:" + this->nextpp.id + "). Server will ignore this data."
 );
 } else {
 playerx.networkAI.parse(this->nextpp);
 udpConnection0.ReleventPos[playerx.PlayerIndex].x = this->nextpp.realx;
 udpConnection0.ReleventPos[playerx.PlayerIndex].y = this->nextpp.realy;
 udpConnection0.ReleventPos[playerx.PlayerIndex].z = this->nextpp.realz;
 }
 } catch (Exception exception) {
 exception.printStackTrace();
 }

 for (int int0 = 0; int0 < GameServer.udpEngine.connections.size(); int0++) {
 UdpConnection udpConnection1 = GameServer.udpEngine.connections.get(int0);
 if (udpConnection0.getConnectedGUID() != udpConnection1.getConnectedGUID()) {
 ByteBufferWriter byteBufferWriter = udpConnection1.startPacket();
 PacketTypes.PacketType.PlayerUpdate.doPacket(byteBufferWriter);
 this->nextpp.write(byteBufferWriter);
 PacketTypes.PacketType.PlayerUpdate.send(udpConnection1);
 }
 }

 try {
 this->nextppTime = this->input.readLong();
 int int1 = this->input.read();
 if (int1 == PacketTypes.PacketType.PlayerUpdate.getId() || int1 == PacketTypes.PacketType.PlayerUpdateReliable.getId()) {
 this->bbpp.position(0);
 this->input.read(this->bbpp.array());
 this->bbpp.position(0);
 this->nextpp = std::make_unique<PlayerPacket>();
 this->nextpp.parse(this->bbpp, udpConnection0);
 }
 } catch (IOException iOException) {
 DebugLog.log("ReplayManager: stop playing replay");
 this->stopPlayReplay();
 }
 }
 }
 }

 public static enum State {
 Stop,
 Recording,
 Playing;
 }
}
} // namespace network
} // namespace zombie
