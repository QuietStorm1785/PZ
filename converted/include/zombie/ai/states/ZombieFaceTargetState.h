#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/ai/State.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoZombie.h"

namespace zombie {
namespace ai {
namespace states {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class ZombieFaceTargetState : public State {
public:
 static const ZombieFaceTargetState _instance = new ZombieFaceTargetState();

 static ZombieFaceTargetState instance() {
 return _instance;
 }

 void enter(IsoGameCharacter var1) {
 }

 void execute(IsoGameCharacter character) {
 IsoZombie zombie0 = (IsoZombie)character;
 if (zombie0.getTarget() != nullptr) {
 zombie0.faceThisObject(zombie0.getTarget());
 }
 }

 void exit(IsoGameCharacter var1) {
 }
}
} // namespace states
} // namespace ai
} // namespace zombie
