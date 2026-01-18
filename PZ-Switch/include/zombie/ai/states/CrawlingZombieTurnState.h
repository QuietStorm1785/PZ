#pragma once
#include "zombie/ai/State.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoZombie.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/core/skinnedmodel/advancedanimation/AnimEvent.h"
#include "zombie/iso/IsoDirections.h"
#include "zombie/iso/Vector2.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace ai {
namespace states {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class CrawlingZombieTurnState : public State {
public:
 static const CrawlingZombieTurnState _instance =
 new CrawlingZombieTurnState();
 static const Vector2 tempVector2_1 = new Vector2();
 static const Vector2 tempVector2_2 = new Vector2();

 static CrawlingZombieTurnState instance() { return _instance; }

 void enter(IsoGameCharacter owner) {}

 void execute(IsoGameCharacter owner) {}

 void exit(IsoGameCharacter owner) {
 ((IsoZombie)owner).AllowRepathDelay = 0.0F;
 }

 void animEvent(IsoGameCharacter owner, AnimEvent event) {
 if (event.m_EventName.equalsIgnoreCase("TurnSome")) {
 Vector2 vector0 = tempVector2_1.set(owner.dir.ToVector());
 Vector2 vector1 =
 "left".equalsIgnoreCase(event.m_ParameterValue)
 ? IsoDirections.fromIndex(owner.dir.index() + 1).ToVector()
 : IsoDirections.fromIndex(owner.dir.index() - 1).ToVector();
 Vector2 vector2 =
 PZMath.lerp(tempVector2_2, vector0, vector1, event.m_TimePc);
 owner.setForwardDirection(vector2);
 } else {
 if (event.m_EventName.equalsIgnoreCase("TurnComplete")) {
 if ("left".equalsIgnoreCase(event.m_ParameterValue) {
 owner.dir = IsoDirections.fromIndex(owner.dir.index() + 1);
 } else {
 owner.dir = IsoDirections.fromIndex(owner.dir.index() - 1);
 }

 owner.getVectorFromDirection(owner.getForwardDirection());
 }
 }
 }

 static bool calculateDir(IsoGameCharacter owner, IsoDirections targetDir) {
 return targetDir.index() > owner.dir.index()
 ? targetDir.index() - owner.dir.index() <= 4
 : targetDir.index() - owner.dir.index() < -4;
 }
}
} // namespace states
} // namespace ai
} // namespace zombie
