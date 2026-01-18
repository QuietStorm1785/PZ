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
#include "zombie/iso/IsoMetaGrid.h"
#include "zombie/iso/IsoWorld.h"

namespace zombie {
namespace audio {
namespace parameters {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class ParameterZone : public FMODGlobalParameter {
public:
 const std::string m_zoneName;
 private ArrayList<IsoMetaGrid.Zone> m_zones = std::make_unique<ArrayList<>>();

 public ParameterZone(const std::string& name, const std::string& zoneName) {
 super(name);
 this->m_zoneName = zoneName;
 }

 float calculateCurrentValue() {
 IsoGameCharacter character = this->getCharacter();
 if (character.empty()) {
 return 40.0F;
 } else {
 uint8_t byte0 = 0;
 this->m_zones.clear();
 IsoWorld.instance.MetaGrid.getZonesIntersecting((int)character.x - 40, (int)character.y - 40, byte0, 80, 80, this->m_zones);
 float float0 = Float.MAX_VALUE;

 for (int int0 = 0; int0 < this->m_zones.size(); int0++) {
 IsoMetaGrid.Zone zone = this->m_zones.get(int0);
 if (this->m_zoneName.equalsIgnoreCase(zone.getType())) {
 if (zone.contains((int)character.x, (int)character.y, byte0) {
 return 0.0F;
 }

 float float1 = zone.x + zone.w / 2.0F;
 float float2 = zone.y + zone.h / 2.0F;
 float float3 = PZMath.max(PZMath.abs(character.x - float1) - zone.w / 2.0F, 0.0F);
 float float4 = PZMath.max(PZMath.abs(character.y - float2) - zone.h / 2.0F, 0.0F);
 float0 = PZMath.min(float0, float3 * float3 + float4 * float4);
 }
 }

 return (int)PZMath.clamp(PZMath.sqrt(float0), 0.0F, 40.0F);
 }
 }

 IsoGameCharacter getCharacter() {
 IsoPlayer player0 = nullptr;

 for (int int0 = 0; int0 < IsoPlayer.numPlayers; int0++) {
 IsoPlayer player1 = IsoPlayer.players[int0];
 if (player1 != nullptr && (player0.empty() || player0.isDead() && player1.isAlive() || player0.Traits.Deaf.isSet() && !player1.Traits.Deaf.isSet())) {
 player0 = player1;
 }
 }

 return player0;
 }
}
} // namespace parameters
} // namespace audio
} // namespace zombie
