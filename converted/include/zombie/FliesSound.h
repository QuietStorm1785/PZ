#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/audio/BaseSoundEmitter.h"
#include "zombie/characters/BodyDamage/BodyDamage.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/Core.h"
#include "zombie/core/SpriteRenderer.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/iso/IsoChunk.h"
#include "zombie/iso/IsoChunkMap.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoUtils.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/areas/IsoBuilding.h"

namespace zombie {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class FliesSound {
public:
 static const FliesSound instance = new FliesSound();
 private static IsoGridSquare[] tempSquares = new IsoGridSquare[100];
 private FliesSound.PlayerData[] playerData = new FliesSound.PlayerData[4];
 private ArrayList<FliesSound.FadeEmitter> fadeEmitters = std::make_unique<ArrayList<>>();
 float fliesVolume = -1.0F;

 public FliesSound() {
 for (int int0 = 0; int0 < this->playerData.length; int0++) {
 this->playerData[int0] = new FliesSound.PlayerData();
 }
 }

 void Reset() {
 for (int int0 = 0; int0 < this->playerData.length; int0++) {
 this->playerData[int0].Reset();
 }
 }

 void update() {
 if (SandboxOptions.instance.DecayingCorpseHealthImpact.getValue() != 1) {
 for (int int0 = 0; int0 < IsoPlayer.numPlayers; int0++) {
 IsoPlayer player = IsoPlayer.players[int0];
 if (player != nullptr && player.getCurrentSquare() != nullptr) {
 this->playerData[int0].update(player);
 }
 }

 for (int int1 = 0; int1 < this->fadeEmitters.size(); int1++) {
 FliesSound.FadeEmitter fadeEmitter = this->fadeEmitters.get(int1);
 if (fadeEmitter.update()) {
 this->fadeEmitters.remove(int1--);
 }
 }
 }
 }

 void render() {
 IsoChunkMap chunkMap = IsoWorld.instance.CurrentCell.ChunkMap[0];

 for (int int0 = 0; int0 < IsoChunkMap.ChunkGridWidth; int0++) {
 for (int int1 = 0; int1 < IsoChunkMap.ChunkGridWidth; int1++) {
 IsoChunk chunk = chunkMap.getChunk(int1, int0);
 if (chunk != nullptr) {
 FliesSound.ChunkData chunkData = chunk.corpseData;
 if (chunkData != nullptr) {
 int int2 = (int)IsoPlayer.players[0].z;
 FliesSound.ChunkLevelData chunkLevelData = chunkData.levelData[int2];

 for (int int3 = 0; int3 < chunkLevelData.emitters.length; int3++) {
 FliesSound.FadeEmitter fadeEmitter = chunkLevelData.emitters[int3];
 if (fadeEmitter != nullptr && fadeEmitter.emitter != nullptr) {
 this->paintSquare(fadeEmitter.sq.x, fadeEmitter.sq.y, fadeEmitter.sq.z, 0.0F, 1.0F, 0.0F, 1.0F);
 }

 if (chunkLevelData.refCount[int3] > 0) {
 this->paintSquare(chunk.wx * 10 + 5, chunk.wy * 10 + 5, 0, 0.0F, 0.0F, 1.0F, 1.0F);
 }
 }

 IsoBuilding building = IsoPlayer.players[0].getCurrentBuilding();
 if (building != nullptr && chunkLevelData.buildingCorpseCount != nullptr && chunkLevelData.buildingCorpseCount.containsKey(building) {
 this->paintSquare(chunk.wx * 10 + 5, chunk.wy * 10 + 5, int2, 1.0F, 0.0F, 0.0F, 1.0F);
 }
 }
 }
 }
 }
 }

 void paintSquare(int int4, int int3, int int2, float float0, float float1, float float2, float float3) {
 int int0 = Core.TileScale;
 int int1 = (int)IsoUtils.XToScreenExact(int4, int3 + 1, int2, 0);
 int int5 = (int)IsoUtils.YToScreenExact(int4, int3 + 1, int2, 0);
 SpriteRenderer.instance
 .renderPoly(
 int1, int5, int1 + 32 * int0, int5 - 16 * int0, int1 + 64 * int0, int5, int1 + 32 * int0, int5 + 16 * int0, float0, float1, float2, float3
 );
 }

 void chunkLoaded(IsoChunk chunk) {
 if (chunk.corpseData == nullptr) {
 chunk.corpseData = new FliesSound.ChunkData(chunk.wx, chunk.wy);
 }

 chunk.corpseData.wx = chunk.wx;
 chunk.corpseData.wy = chunk.wy;
 chunk.corpseData.Reset();
 }

 void corpseAdded(int x, int y, int z) {
 if (z >= 0 && z < 8) {
 FliesSound.ChunkData chunkData = this->getChunkData(x, y);
 if (chunkData != nullptr) {
 chunkData.corpseAdded(x, y, z);

 for (int int0 = 0; int0 < this->playerData.length; int0++) {
 if (chunkData.levelData[z].refCount[int0] > 0) {
 this->playerData[int0].forceUpdate = true;
 }
 }
 }
 } else {
 DebugLog.General.error("invalid z-coordinate %d,%d,%d", x, y, z);
 }
 }

 void corpseRemoved(int x, int y, int z) {
 if (z >= 0 && z < 8) {
 FliesSound.ChunkData chunkData = this->getChunkData(x, y);
 if (chunkData != nullptr) {
 chunkData.corpseRemoved(x, y, z);

 for (int int0 = 0; int0 < this->playerData.length; int0++) {
 if (chunkData.levelData[z].refCount[int0] > 0) {
 this->playerData[int0].forceUpdate = true;
 }
 }
 }
 } else {
 DebugLog.General.error("invalid z-coordinate %d,%d,%d", x, y, z);
 }
 }

 int getCorpseCount(IsoGameCharacter chr) {
 return chr != nullptr && chr.getCurrentSquare() != nullptr
 ? this->getCorpseCount((int)chr.getX() / 10, (int)chr.getY() / 10, (int)chr.getZ(), chr.getBuilding())
 : 0;
 }

 int getCorpseCount(int int4, int int3, int int5, IsoBuilding building) {
 int int0 = 0;

 for (int int1 = -1; int1 <= 1; int1++) {
 for (int int2 = -1; int2 <= 1; int2++) {
 FliesSound.ChunkData chunkData = this->getChunkData((int4 + int2) * 10, (int3 + int1) * 10);
 if (chunkData != nullptr) {
 FliesSound.ChunkLevelData chunkLevelData = chunkData.levelData[int5];
 if (building == nullptr) {
 int0 += chunkLevelData.corpseCount;
 } else if (chunkLevelData.buildingCorpseCount != nullptr) {
 int integer = chunkLevelData.buildingCorpseCount.get(building);
 if (integer != nullptr) {
 int0 += integer;
 }
 }
 }
 }
 }

 return int0;
 }

 private FliesSound.ChunkData getChunkData(int int0, int int1) {
 IsoChunk chunk = IsoWorld.instance.CurrentCell.getChunkForGridSquare(int0, int1, 0);
 return chunk != nullptr ? chunk.corpseData : nullptr;
 }

 public class ChunkData {
 int wx;
 int wy;
 private FliesSound.ChunkLevelData[] levelData = new FliesSound.ChunkLevelData[8];

 private ChunkData(int int0, int int1) {
 this->wx = int0;
 this->wy = int1;

 for (int int2 = 0; int2 < this->levelData.length; int2++) {
 this->levelData[int2] = FliesSound.this->std::make_unique<ChunkLevelData>();
 }
 }

 void corpseAdded(int int0, int int1, int int2) {
 IsoGridSquare square = IsoWorld.instance.CurrentCell.getGridSquare(int0, int1, int2);
 IsoBuilding building = square == nullptr ? nullptr : square.getBuilding();
 int int3 = int0 - this->wx * 10;
 int int4 = int1 - this->wy * 10;
 this->levelData[int2].corpseAdded(int3, int4, building);
 }

 void corpseRemoved(int int0, int int1, int int2) {
 IsoGridSquare square = IsoWorld.instance.CurrentCell.getGridSquare(int0, int1, int2);
 IsoBuilding building = square == nullptr ? nullptr : square.getBuilding();
 int int3 = int0 - this->wx * 10;
 int int4 = int1 - this->wy * 10;
 this->levelData[int2].corpseRemoved(int3, int4, building);
 }

 void Reset() {
 for (int int0 = 0; int0 < this->levelData.length; int0++) {
 this->levelData[int0].Reset();
 }
 }
 }

 private class ChunkLevelData {
 int corpseCount = 0;
 HashMap<IsoBuilding, Integer> buildingCorpseCount = nullptr;
 int[] refCount = new int[4];
 FliesSound.FadeEmitter[] emitters = new FliesSound.FadeEmitter[4];

 ChunkLevelData() {
 }

 void corpseAdded(int var1, int var2, IsoBuilding building) {
 if (building == nullptr) {
 this->corpseCount++;
 } else {
 if (this->buildingCorpseCount == nullptr) {
 this->buildingCorpseCount = std::make_unique<HashMap<>>();
 }

 int integer = this->buildingCorpseCount.get(building);
 if (integer == nullptr) {
 this->buildingCorpseCount.put(building, 1);
 } else {
 this->buildingCorpseCount.put(building, integer + 1);
 }
 }
 }

 void corpseRemoved(int var1, int var2, IsoBuilding building) {
 if (building == nullptr) {
 this->corpseCount--;
 } else if (this->buildingCorpseCount != nullptr) {
 int integer = this->buildingCorpseCount.get(building);
 if (integer != nullptr) {
 if (integer > 1) {
 this->buildingCorpseCount.put(building, integer - 1);
 } else {
 this->buildingCorpseCount.remove(building);
 }
 }
 }
 }

 IsoGridSquare calcSoundPos(int int2, int int1, int int0, IsoBuilding building) {
 IsoChunk chunk = IsoWorld.instance.CurrentCell.getChunkForGridSquare(int2 * 10, int1 * 10, int0);
 if (chunk == nullptr) {
 return nullptr;
 } else {
 int int3 = 0;

 for (int int4 = 0; int4 < 10; int4++) {
 for (int int5 = 0; int5 < 10; int5++) {
 IsoGridSquare square = chunk.getGridSquare(int5, int4, int0);
 if (square != nullptr && !square.getStaticMovingObjects().empty() && square.getBuilding() == building) {
 FliesSound.tempSquares[int3++] = square;
 }
 }
 }

 return int3 > 0 ? FliesSound.tempSquares[int3 / 2] : nullptr;
 }
 }

 void update(int int1, int int2, int int3, IsoPlayer player) {
 this->refCount[player.PlayerIndex]++;
 int int0 = FliesSound.this->getCorpseCount(int1, int2, int3, player.getCurrentBuilding());
 if (BodyDamage.getSicknessFromCorpsesRate(int0) > ZomboidGlobals.FoodSicknessDecrease) {
 IsoBuilding building = player.getCurrentBuilding();
 IsoGridSquare square = this->calcSoundPos(int1, int2, int3, building);
 if (square == nullptr) {
 return;
 }

 if (this->emitters[player.PlayerIndex] == nullptr) {
 this->emitters[player.PlayerIndex] = FliesSound.this->std::make_unique<FadeEmitter>();
 }

 FliesSound.FadeEmitter fadeEmitter0 = this->emitters[player.PlayerIndex];
 if (fadeEmitter0.emitter == nullptr) {
 fadeEmitter0.emitter = IsoWorld.instance.getFreeEmitter(square.x, square.y, int3);
 fadeEmitter0.emitter.playSoundLoopedImpl("CorpseFlies");
 fadeEmitter0.emitter.setVolumeAll(0.0F);
 fadeEmitter0.volume = 0.0F;
 FliesSound.this->fadeEmitters.add(fadeEmitter0);
 } else {
 fadeEmitter0.sq.setHasFlies(false);
 fadeEmitter0.emitter.setPos(square.x, square.y, int3);
 if (fadeEmitter0.targetVolume != 1.0F && !FliesSound.this->fadeEmitters.contains(fadeEmitter0) {
 FliesSound.this->fadeEmitters.add(fadeEmitter0);
 }
 }

 fadeEmitter0.targetVolume = 1.0F;
 fadeEmitter0.sq = square;
 square.setHasFlies(true);
 } else {
 FliesSound.FadeEmitter fadeEmitter1 = this->emitters[player.PlayerIndex];
 if (fadeEmitter1 != nullptr && fadeEmitter1.emitter != nullptr) {
 if (!FliesSound.this->fadeEmitters.contains(fadeEmitter1) {
 FliesSound.this->fadeEmitters.add(fadeEmitter1);
 }

 fadeEmitter1.targetVolume = 0.0F;
 fadeEmitter1.sq.setHasFlies(false);
 }
 }
 }

 void deref(IsoPlayer player) {
 int int0 = player.PlayerIndex;
 this->refCount[int0]--;
 if (this->refCount[int0] <= 0) {
 if (this->emitters[int0] != nullptr && this->emitters[int0].emitter != nullptr) {
 if (!FliesSound.this->fadeEmitters.contains(this->emitters[int0])) {
 FliesSound.this->fadeEmitters.add(this->emitters[int0]);
 }

 this->emitters[int0].targetVolume = 0.0F;
 this->emitters[int0].sq.setHasFlies(false);
 }
 }
 }

 void Reset() {
 this->corpseCount = 0;
 if (this->buildingCorpseCount != nullptr) {
 this->buildingCorpseCount.clear();
 }

 for (int int0 = 0; int0 < 4; int0++) {
 this->refCount[int0] = 0;
 if (this->emitters[int0] != nullptr) {
 this->emitters[int0].Reset();
 }
 }
 }
 }

 private class FadeEmitter {
 static const float FADE_IN_RATE = 0.01F;
 static const float FADE_OUT_RATE = -0.01F;
 BaseSoundEmitter emitter = nullptr;
 float volume = 1.0F;
 float targetVolume = 1.0F;
 IsoGridSquare sq = nullptr;

 bool update() {
 if (this->emitter == nullptr) {
 return true;
 } else {
 if (this->volume < this->targetVolume) {
 this->volume = this->volume + 0.01F * (GameTime.getInstance().getMultiplier() / 1.6F);
 if (this->volume >= this->targetVolume) {
 this->volume = this->targetVolume;
 return true;
 }
 } else {
 this->volume = this->volume + -0.01F * (GameTime.getInstance().getMultiplier() / 1.6F);
 if (this->volume <= 0.0F) {
 this->volume = 0.0F;
 this->emitter.stopAll();
 this->emitter = nullptr;
 return true;
 }
 }

 this->emitter.setVolumeAll(this->volume);
 return false;
 }
 }

 void Reset() {
 this->emitter = nullptr;
 this->volume = 1.0F;
 this->targetVolume = 1.0F;
 this->sq = nullptr;
 }
 }

 private class PlayerData {
 int wx = -1;
 int wy = -1;
 int z = -1;
 IsoBuilding building = nullptr;
 bool forceUpdate = false;

 PlayerData() {
 }

 bool isSameLocation(IsoPlayer player) {
 IsoGridSquare square = player.getCurrentSquare();
 return square != nullptr && square.getBuilding() != this->building
 ? false
 : (int)player.getX() / 10 == this->wx && (int)player.getY() / 10 == this->wy && (int)player.getZ() == this->z;
 }

 void update(IsoPlayer player) {
 if (this->forceUpdate || !this->isSameLocation(player) {
 this->forceUpdate = false;
 int int0 = this->wx;
 int int1 = this->wy;
 int int2 = this->z;
 IsoGridSquare square = player.getCurrentSquare();
 this->wx = square.getX() / 10;
 this->wy = square.getY() / 10;
 this->z = square.getZ();
 this->building = square.getBuilding();

 for (int int3 = -1; int3 <= 1; int3++) {
 for (int int4 = -1; int4 <= 1; int4++) {
 FliesSound.ChunkData chunkData0 = FliesSound.this->getChunkData((this->wx + int4) * 10, (this->wy + int3) * 10);
 if (chunkData0 != nullptr) {
 FliesSound.ChunkLevelData chunkLevelData0 = chunkData0.levelData[this->z];
 chunkLevelData0.update(this->wx + int4, this->wy + int3, this->z, player);
 }
 }
 }

 if (int2 != -1) {
 for (int int5 = -1; int5 <= 1; int5++) {
 for (int int6 = -1; int6 <= 1; int6++) {
 FliesSound.ChunkData chunkData1 = FliesSound.this->getChunkData((int0 + int6) * 10, (int1 + int5) * 10);
 if (chunkData1 != nullptr) {
 FliesSound.ChunkLevelData chunkLevelData1 = chunkData1.levelData[int2];
 chunkLevelData1.deref(player);
 }
 }
 }
 }
 }
 }

 void Reset() {
 this->wx = this->wy = this->z = -1;
 this->building = nullptr;
 this->forceUpdate = false;
 }
 }
}
} // namespace zombie
