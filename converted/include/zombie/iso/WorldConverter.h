#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/Lua/LuaEventManager.h"
#include "zombie/ZomboidFileSystem.h"
#include "zombie/core/Core.h"
#include "zombie/core/Rand.h"
#include "zombie/core/znet/SteamUtils.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/erosion/ErosionRegions.h"
#include "zombie/erosion/season/ErosionIceQueen.h"
#include "zombie/gameStates/GameLoadingState.h"
#include "zombie/gameStates/IngameState.h"
#include "zombie/globalObjects/GlobalObjectLookup.h"
#include "zombie/iso/sprite/IsoSprite.h"
#include "zombie/iso/sprite/IsoSpriteManager.h"
#include "zombie/network/CoopSlave.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/ServerMap.h"
#include "zombie/network/ServerOptions.h"
#include "zombie/vehicles/VehicleManager.h"
#include "zombie/world/WorldDictionary.h"
#include "zombie/world/WorldDictionaryException.h"
#include <fstream>
#include <iostream>

namespace zombie {
namespace iso {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class WorldConverter {
public:
 static const WorldConverter instance = new WorldConverter();
 static bool converting;
 public HashMap<Integer, Integer> TilesetConversions = nullptr;
 int oldID = 0;

 void convert(const std::string& string, IsoSpriteManager var2) {
 File file = new File(ZomboidFileSystem.instance.getGameModeCacheDir() + File.separator + string + File.separator + "map_ver.bin");
 if (file.exists()) {
 converting = true;
 FileInputStream fileInputStream = new FileInputStream(file);
 DataInputStream dataInputStream = new DataInputStream(fileInputStream);
 int int0 = dataInputStream.readInt();
 dataInputStream.close();
 if (int0 < 195) {
 if (int0 < 24) {
 GameLoadingState.build23Stop = true;
 return;
 }

 try {
 this->convert(string, int0, 195);
 } catch (Exception exception) {
 IngameState.createWorld(string);
 IngameState.copyWorld(string + "_backup", string);
 exception.printStackTrace();
 }
 }

 converting = false;
 }
 }

 void convert(const std::string& string1, int int0, int int1) {
 if (!GameClient.bClient) {
 GameLoadingState.convertingWorld = true;
 std::string string0 = Core.GameSaveWorld;
 IngameState.createWorld(string1 + "_backup");
 IngameState.copyWorld(string1, Core.GameSaveWorld);
 Core.GameSaveWorld = string0;
 if (int1 >= 14 && int0 < 14) {
 try {
 this->convertchunks(string1, 25, 25);
 } catch (IOException iOException0) {
 iOException0.printStackTrace();
 }
 } else if (int0 == 7) {
 try {
 this->convertchunks(string1);
 } catch (IOException iOException1) {
 iOException1.printStackTrace();
 }
 }

 if (int0 <= 4) {
 this->loadconversionmap(int0, "tiledefinitions");
 this->loadconversionmap(int0, "newtiledefinitions");

 try {
 this->convertchunks(string1);
 } catch (IOException iOException2) {
 iOException2.printStackTrace();
 }
 }

 GameLoadingState.convertingWorld = false;
 }
 }

 void convertchunks(const std::string& string0) {
 IsoCell cell = new IsoCell(300, 300);
 IsoChunkMap chunkMap = new IsoChunkMap(cell);
 File file = new File(ZomboidFileSystem.instance.getGameModeCacheDir() + File.separator + string0 + File.separator);
 if (!file.exists()) {
 file.mkdir();
 }

 String[] strings0 = file.list();

 for (auto& string1 : strings0) if (string1.contains(".bin")
 && !string1 == "map.bin")
 && !string1 == "map_p.bin")
 && !string1.matches("map_p[0-9]+\\.bin")
 && !string1 == "map_t.bin")
 && !string1 == "map_c.bin")
 && !string1 == "map_ver.bin")
 && !string1 == "map_sand.bin")
 && !string1 == "map_mov.bin")
 && !string1 == "map_meta.bin")
 && !string1 == "map_cm.bin")
 && !string1 == "pc.bin")
 && !string1.startsWith("zpop_")
 && !string1.startsWith("chunkdata_")) {
 String[] strings1 = string1.replace(".bin", "").replace("map_", "").split("_");
 int int0 = Integer.parseInt(strings1[0]);
 int int1 = Integer.parseInt(strings1[1]);
 chunkMap.LoadChunkForLater(int0, int1, 0, 0);
 chunkMap.SwapChunkBuffers();
 chunkMap.getChunk(0, 0).Save(true);
 }
 }
 }

 void convertchunks(const std::string& string0, int int0, int int1) {
 IsoCell cell = new IsoCell(300, 300);
 new IsoChunkMap();
 File file0 = new File(ZomboidFileSystem.instance.getGameModeCacheDir() + File.separator + string0 + File.separator);
 if (!file0.exists()) {
 file0.mkdir();
 }

 String[] strings0 = file0.list();
 IsoWorld.saveoffsetx = int0;
 IsoWorld.saveoffsety = int1;
 IsoWorld.instance.MetaGrid.Create();
 WorldStreamer.instance.create();

 for (auto& string1 : strings0) if (string1.contains(".bin")
 && !string1 == "map.bin")
 && !string1 == "map_p.bin")
 && !string1.matches("map_p[0-9]+\\.bin")
 && !string1 == "map_t.bin")
 && !string1 == "map_c.bin")
 && !string1 == "map_ver.bin")
 && !string1 == "map_sand.bin")
 && !string1 == "map_mov.bin")
 && !string1 == "map_meta.bin")
 && !string1 == "map_cm.bin")
 && !string1 == "pc.bin")
 && !string1.startsWith("zpop_")
 && !string1.startsWith("chunkdata_")) {
 String[] strings1 = string1.replace(".bin", "").replace("map_", "").split("_");
 int int2 = Integer.parseInt(strings1[0]);
 int int3 = Integer.parseInt(strings1[1]);
 IsoChunk chunk = new IsoChunk(cell);
 chunk.refs.add(cell.ChunkMap[0]);
 WorldStreamer.instance.addJobConvert(chunk, 0, 0, int2, int3);

 while (!chunk.bLoaded) {
 try {
 Thread.sleep(20L);
 } catch (InterruptedException interruptedException0) {
 interruptedException0.printStackTrace();
 }
 }

 chunk.wx += int0 * 30;
 chunk.wy += int1 * 30;
 chunk.jobType = IsoChunk.JobType.Convert;
 chunk.Save(true);
 File file1 = new File(ZomboidFileSystem.instance.getGameModeCacheDir() + File.separator + string0 + File.separator + string1);

 while (!ChunkSaveWorker.instance.toSaveQueue.empty()) {
 try {
 Thread.sleep(13L);
 } catch (InterruptedException interruptedException1) {
 interruptedException1.printStackTrace();
 }
 }

 file1.delete();
 }
 }
 }

 void loadconversionmap(int int0, const std::string& string1) {
 std::string string0 = "media/" + string1 + "_" + int0 + ".tiles";
 File file = new File(string0);
 if (file.exists()) {
 try {
 RandomAccessFile randomAccessFile = new RandomAccessFile(file.getAbsolutePath(), "r");
 int int1 = IsoWorld.readInt(randomAccessFile);

 for (int int2 = 0; int2 < int1; int2++) {
 Thread.sleep(4L);
 std::string string2 = IsoWorld.readString(randomAccessFile);
 std::string string3 = string2.trim();
 IsoWorld.readString(randomAccessFile);
 int int3 = IsoWorld.readInt(randomAccessFile);
 int int4 = IsoWorld.readInt(randomAccessFile);
 int int5 = IsoWorld.readInt(randomAccessFile);

 for (int int6 = 0; int6 < int5; int6++) {
 IsoSprite sprite = IsoSpriteManager.instance.NamedMap.get(string3 + "_" + int6);
 if (this->TilesetConversions == nullptr) {
 this->TilesetConversions = std::make_unique<HashMap<>>();
 }

 this->TilesetConversions.put(this->oldID, sprite.ID);
 this->oldID++;
 int int7 = IsoWorld.readInt(randomAccessFile);

 for (int int8 = 0; int8 < int7; int8++) {
 string2 = IsoWorld.readString(randomAccessFile);
 std::string string4 = string2.trim();
 string2 = IsoWorld.readString(randomAccessFile);
 std::string string5 = string2.trim();
 }
 }
 }
 } catch (Exception exception) {
 }
 }
 }

 void softreset() {
 std::string string0 = GameServer.ServerName;
 Core.GameSaveWorld = string0;
 IsoCell cell = new IsoCell(300, 300);
 IsoChunk chunk = new IsoChunk(cell);
 File file = new File(ZomboidFileSystem.instance.getGameModeCacheDir() + File.separator + string0 + File.separator);
 if (!file.exists()) {
 file.mkdir();
 }

 String[] strings0 = file.list();
 if (CoopSlave.instance != nullptr) {
 CoopSlave.instance.sendMessage("softreset-count", nullptr, Integer.toString(strings0.length);
 }

 IsoWorld.instance.MetaGrid.Create();
 ServerMap.instance.init(IsoWorld.instance.MetaGrid);
 new ErosionIceQueen();
 ErosionRegions.init();
 WorldStreamer.instance.create();
 VehicleManager.instance = std::make_unique<VehicleManager>();
 WorldDictionary.init();
 GlobalObjectLookup.init(IsoWorld.instance.getMetaGrid());
 LuaEventManager.triggerEvent("OnSGlobalObjectSystemInit");
 int int0 = strings0.length;
 DebugLog.log("processing " + int0 + " files");

 for (auto& string1 : strings0) int0--;
 if (string1.startsWith("zpop_")) {
 deleteFile(string1);
 } else if (string1 == "map_t.bin")) {
 deleteFile(string1);
 } else if (string1 == "map_meta.bin") || string1 == "map_zone.bin")) {
 deleteFile(string1);
 } else if (string1 == "reanimated.bin")) {
 deleteFile(string1);
 } else if (string1.matches("map_[0-9]+_[0-9]+\\.bin")) {
 System.out.println("Soft clearing chunk: " + string1);
 String[] strings1 = string1.replace(".bin", "").replace("map_", "").split("_");
 int int1 = Integer.parseInt(strings1[0]);
 int int2 = Integer.parseInt(strings1[1]);
 chunk.refs.add(cell.ChunkMap[0]);
 chunk.wx = int1;
 chunk.wy = int2;
 ServerMap.instance.setSoftResetChunk(chunk);
 WorldStreamer.instance.addJobWipe(chunk, 0, 0, int1, int2);

 while (!chunk.bLoaded) {
 try {
 Thread.sleep(20L);
 } catch (InterruptedException interruptedException) {
 interruptedException.printStackTrace();
 }
 }

 chunk.jobType = IsoChunk.JobType.Convert;
 chunk.FloorBloodSplats.clear();

 try {
 chunk.Save(true);
 } catch (Exception exception) {
 exception.printStackTrace();
 }

 ServerMap.instance.clearSoftResetChunk(chunk);
 chunk.doReuseGridsquares();
 IsoChunkMap.chunkStore.remove(chunk);
 if (int0 % 100 == 0) {
 DebugLog.log(int0 + " files to go");
 }

 if (CoopSlave.instance != nullptr && int0 % 10 == 0) {
 CoopSlave.instance.sendMessage("softreset-remaining", nullptr, Integer.toString(int0);
 }
 }
 }

 GameServer.ResetID = Rand.Next(10000000);
 ServerOptions.instance.putSaveOption("ResetID", String.valueOf(GameServer.ResetID);
 IsoWorld.instance.CurrentCell = nullptr;
 DebugLog.log("soft-reset complete, server terminated");
 if (CoopSlave.instance != nullptr) {
 CoopSlave.instance.sendMessage("softreset-finished", nullptr, "");
 }

 SteamUtils.shutdown();
 System.exit(0);
 }

 static void deleteFile(const std::string& string) {
 File file = new File(ZomboidFileSystem.instance.getGameModeCacheDir() + File.separator + GameServer.ServerName + File.separator + string);
 file.delete();
 }
}
} // namespace iso
} // namespace zombie
