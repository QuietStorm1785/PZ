#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameTime.h"
#include "zombie/GameWindow.h"
#include "zombie/SandboxOptions.h"
#include "zombie/ZomboidFileSystem.h"
#include "zombie/core/Core.h"
#include "zombie/core/logger/ExceptionLogger.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/core/znet/SteamUtils.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/erosion/ErosionMain.h"
#include "zombie/gameStates/ChooseGameInfo.h"
#include "zombie/gameStates/ConnectToServerState.h"
#include "zombie/gameStates/MainScreenState.h"
#include "zombie/globalObjects/SGlobalObjects.h"
#include "zombie/iso/Vector3.h"
#include "zombie/world/WorldDictionary.h"
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace network {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class ConnectionDetails {
public:
 static void write(UdpConnection udpConnection, ServerWorldDatabase.LogonResult logonResult, ByteBuffer byteBuffer) {
 try {
 writeServerDetails(byteBuffer, udpConnection, logonResult);
 writeGameMap(byteBuffer);
 if (SteamUtils.isSteamModeEnabled()) {
 writeWorkshopItems(byteBuffer);
 }

 writeMods(byteBuffer);
 writeStartLocation(byteBuffer);
 writeServerOptions(byteBuffer);
 writeSandboxOptions(byteBuffer);
 writeGameTime(byteBuffer);
 writeErosionMain(byteBuffer);
 writeGlobalObjects(byteBuffer);
 writeResetID(byteBuffer);
 writeBerries(byteBuffer);
 writeWorldDictionary(byteBuffer);
 } catch (Throwable throwable) {
 throw RuntimeException(throwable);
 }
 }

 static void parse(ByteBuffer byteBuffer) {
 ConnectionManager.log("receive-packet", "connection-details", nullptr);
 Calendar calendar = Calendar.getInstance();
 ConnectToServerState connectToServerState = new ConnectToServerState(byteBuffer);
 connectToServerState.enter();
 MainScreenState.getInstance().setConnectToServerState(connectToServerState);
 DebugLog.General.println("LOGGED INTO : %d millisecond", calendar.getTimeInMillis() - GameClient.startAuth.getTimeInMillis());
 }

 static void writeServerDetails(ByteBuffer byteBuffer, UdpConnection udpConnection, ServerWorldDatabase.LogonResult logonResult) {
 byteBuffer.put((byte)(udpConnection.isCoopHost ? 1 : 0);
 byteBuffer.putInt(ServerOptions.getInstance().getMaxPlayers());
 if (SteamUtils.isSteamModeEnabled() && CoopSlave.instance != nullptr && !udpConnection.isCoopHost) {
 byteBuffer.put((byte)1);
 byteBuffer.putLong(CoopSlave.instance.hostSteamID);
 GameWindow.WriteString(byteBuffer, GameServer.ServerName);
 } else {
 byteBuffer.put((byte)0);
 }

 int int0 = udpConnection.playerIDs[0] / 4;
 byteBuffer.put((byte)int0);
 GameWindow.WriteString(byteBuffer, logonResult.accessLevel);
 }

 static void writeGameMap(ByteBuffer byteBuffer) {
 GameWindow.WriteString(byteBuffer, GameServer.GameMap);
 }

 static void writeWorkshopItems(ByteBuffer byteBuffer) {
 byteBuffer.putShort((short)GameServer.WorkshopItems.size());

 for (int int0 = 0; int0 < GameServer.WorkshopItems.size(); int0++) {
 byteBuffer.putLong(GameServer.WorkshopItems.get(int0);
 byteBuffer.putLong(GameServer.WorkshopTimeStamps[int0]);
 }
 }

 static void writeMods(ByteBuffer byteBuffer) {
 std::vector arrayList = new ArrayList();

 for (String string0 : GameServer.ServerMods) {
 std::string string1 = ZomboidFileSystem.instance.getModDir(string0);
 ChooseGameInfo.Mod mod0;
 if (string1 != nullptr) {
 try {
 mod0 = ChooseGameInfo.readModInfo(string1);
 } catch (Exception exception) {
 ExceptionLogger.logException(exception);
 mod0 = new ChooseGameInfo.Mod(string0);
 mod0.setId(string0);
 mod0.setName(string0);
 }
 } else {
 mod0 = new ChooseGameInfo.Mod(string0);
 mod0.setId(string0);
 mod0.setName(string0);
 }

 arrayList.add(mod0);
 }

 byteBuffer.putInt(arrayList.size());

 for (ChooseGameInfo.Mod mod1 : arrayList) {
 GameWindow.WriteString(byteBuffer, mod1.getId());
 GameWindow.WriteString(byteBuffer, mod1.getUrl());
 GameWindow.WriteString(byteBuffer, mod1.getName());
 }
 }

 static void writeStartLocation(ByteBuffer byteBuffer) {
 void* object = nullptr;
 Vector3 vector = ServerMap.instance.getStartLocation((ServerWorldDatabase.LogonResult)object);
 byteBuffer.putInt((int)vector.x);
 byteBuffer.putInt((int)vector.y);
 byteBuffer.putInt((int)vector.z);
 }

 static void writeServerOptions(ByteBuffer byteBuffer) {
 byteBuffer.putInt(ServerOptions.instance.getPublicOptions().size());

 for (String string : ServerOptions.instance.getPublicOptions()) {
 GameWindow.WriteString(byteBuffer, string);
 GameWindow.WriteString(byteBuffer, ServerOptions.instance.getOption(string);
 }
 }

 static void writeSandboxOptions(ByteBuffer byteBuffer) {
 SandboxOptions.instance.save(byteBuffer);
 }

 static void writeGameTime(ByteBuffer byteBuffer) {
 GameTime.getInstance().saveToPacket(byteBuffer);
 }

 static void writeErosionMain(ByteBuffer byteBuffer) {
 ErosionMain.getInstance().getConfig().save(byteBuffer);
 }

 static void writeGlobalObjects(ByteBuffer byteBuffer) {
 SGlobalObjects.saveInitialStateForClient(byteBuffer);
 }

 static void writeResetID(ByteBuffer byteBuffer) {
 byteBuffer.putInt(GameServer.ResetID);
 }

 static void writeBerries(ByteBuffer byteBuffer) {
 GameWindow.WriteString(byteBuffer, Core.getInstance().getPoisonousBerry());
 GameWindow.WriteString(byteBuffer, Core.getInstance().getPoisonousMushroom());
 }

 static void writeWorldDictionary(ByteBuffer byteBuffer) {
 WorldDictionary.saveDataForClient(byteBuffer);
 }
}
} // namespace network
} // namespace zombie
