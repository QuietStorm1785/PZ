#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/audio/FMODGlobalParameter.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/iso/IsoChunk.h"
#include "zombie/iso/IsoChunkMap.h"
#include "zombie/iso/IsoWorld.h"

namespace zombie {
namespace audio {
namespace parameters {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class ParameterZoneWaterSide : public FMODGlobalParameter {
public:
 int m_playerX = -1;
 int m_playerY = -1;
 int m_distance = 40;

 public ParameterZoneWaterSide() {
 super("ZoneWaterSide");
 }

 float calculateCurrentValue() {
 IsoGameCharacter character = this->getCharacter();
 if (character == nullptr) {
 return 40.0F;
 } else {
 int int0 = (int)character.getX();
 int int1 = (int)character.getY();
 if (int0 != this->m_playerX || int1 != this->m_playerY) {
 this->m_playerX = int0;
 this->m_playerY = int1;
 this->m_distance = this->calculate(character);
 if (this->m_distance < 40) {
 this->m_distance = PZMath.clamp(this->m_distance - 5, 0, 40);
 }
 }

 return this->m_distance;
 }
 }

 int calculate(IsoGameCharacter character) {
 if (IsoWorld.instance != nullptr && IsoWorld.instance.CurrentCell != nullptr && IsoWorld.instance.CurrentCell.ChunkMap[0] != nullptr) {
 IsoChunkMap chunkMap = IsoWorld.instance.CurrentCell.ChunkMap[0];
 float float0 = Float.MAX_VALUE;

 for (int int0 = 0; int0 < IsoChunkMap.ChunkGridWidth; int0++) {
 for (int int1 = 0; int1 < IsoChunkMap.ChunkGridWidth; int1++) {
 IsoChunk chunk = chunkMap.getChunk(int1, int0);
 if (chunk != nullptr && chunk.getNumberOfWaterTiles() == 100) {
 float float1 = chunk.wx * 10 + 5.0F;
 float float2 = chunk.wy * 10 + 5.0F;
 float float3 = character.x - float1;
 float float4 = character.y - float2;
 if (float3 * float3 + float4 * float4 < float0) {
 float0 = float3 * float3 + float4 * float4;
 }
 }
 }
 }

 return (int)PZMath.clamp(PZMath.sqrt(float0), 0.0F, 40.0F);
 } else {
 return 40;
 }
 }

 IsoGameCharacter getCharacter() {
 IsoPlayer player0 = nullptr;

 for (int int0 = 0; int0 < IsoPlayer.numPlayers; int0++) {
 IsoPlayer player1 = IsoPlayer.players[int0];
 if (player1 != nullptr && (player0 == nullptr || player0.isDead() && player1.isAlive() || player0.Traits.Deaf.isSet() && !player1.Traits.Deaf.isSet())) {
 player0 = player1;
 }
 }

 return player0;
 }
}
} // namespace parameters
} // namespace audio
} // namespace zombie
