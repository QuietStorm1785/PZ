#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameTime.h"
#include "zombie/ai/State.h"
#include "zombie/audio/parameters/ParameterZombieState.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoZombie.h"
#include "zombie/core/Core.h"
#include "zombie/core/Rand.h"
#include "zombie/core/skinnedmodel/animation/AnimationPlayer.h"
#include "zombie/core/skinnedmodel/model/Model.h"
#include "zombie/iso/Vector3.h"
#include "zombie/iso/objects/IsoDeadBody.h"
#include "zombie/network/GameClient.h"

namespace zombie {
namespace ai {
namespace states {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class ZombieOnGroundState : public State {
public:
 static const ZombieOnGroundState _instance = new ZombieOnGroundState();
 static Vector3 tempVector = std::make_unique<Vector3>();
 static Vector3 tempVectorBonePos = std::make_unique<Vector3>();

 static ZombieOnGroundState instance() {
 return _instance;
 }

 void enter(IsoGameCharacter owner) {
 IsoZombie zombie0 = (IsoZombie)owner;
 owner.setCollidable(false);
 if (!owner.isDead()) {
 owner.setOnFloor(true);
 }

 if (owner.isDead() || zombie0.isFakeDead()) {
 owner.die();
 } else if (!zombie0.isBecomeCrawler()) {
 if (!"Tutorial" == Core.GameMode) {
 owner.setReanimateTimer(Rand.Next(60) + 30);
 }

 if (GameClient.bClient && zombie0.isReanimatedPlayer()) {
 IsoDeadBody.removeDeadBody(zombie0.networkAI.reanimatedBodyID);
 }

 zombie0.parameterZombieState.setState(ParameterZombieState.State.Idle);
 }
 }

 void execute(IsoGameCharacter owner) {
 IsoZombie zombie0 = (IsoZombie)owner;
 if (owner.isDead() || zombie0.isFakeDead()) {
 owner.die();
 } else if (zombie0.isBecomeCrawler()) {
 if (!zombie0.isBeingSteppedOn() && !zombie0.isUnderVehicle()) {
 zombie0.setCrawler(true);
 zombie0.setCanWalk(false);
 zombie0.setReanimate(true);
 zombie0.setBecomeCrawler(false);
 }
 } else {
 if (owner.hasAnimationPlayer()) {
 owner.getAnimationPlayer().setTargetToAngle();
 }

 owner.setReanimateTimer(owner.getReanimateTimer() - GameTime.getInstance().getMultiplier() / 1.6F);
 if (owner.getReanimateTimer() <= 2.0F) {
 if (GameClient.bClient) {
 if (owner.isBeingSteppedOn() && !zombie0.isReanimatedPlayer()) {
 owner.setReanimateTimer(Rand.Next(60) + 30);
 }
 } else if (owner.isBeingSteppedOn() && zombie0.getReanimatedPlayer() == nullptr) {
 owner.setReanimateTimer(Rand.Next(60) + 30);
 }
 }
 }
 }

 static bool isCharacterStandingOnOther(IsoGameCharacter chrStanding, IsoGameCharacter chrProne) {
 AnimationPlayer animationPlayer = chrProne.getAnimationPlayer();
 int int0 = DoCollisionBoneCheck(chrStanding, chrProne, animationPlayer.getSkinningBoneIndex("Bip01_Spine", -1), 0.32F);
 if (int0 == -1) {
 int0 = DoCollisionBoneCheck(chrStanding, chrProne, animationPlayer.getSkinningBoneIndex("Bip01_L_Calf", -1), 0.18F);
 }

 if (int0 == -1) {
 int0 = DoCollisionBoneCheck(chrStanding, chrProne, animationPlayer.getSkinningBoneIndex("Bip01_R_Calf", -1), 0.18F);
 }

 if (int0 == -1) {
 int0 = DoCollisionBoneCheck(chrStanding, chrProne, animationPlayer.getSkinningBoneIndex("Bip01_Head", -1), 0.28F);
 }

 return int0 > -1;
 }

 static int DoCollisionBoneCheck(IsoGameCharacter character1, IsoGameCharacter character0, int int0, float float2) {
 float float0 = 0.3F;
 Model.BoneToWorldCoords(character0, int0, tempVectorBonePos);

 for (int int1 = 1; int1 <= 10; int1++) {
 float float1 = int1 / 10.0F;
 tempVector.x = character1.x;
 tempVector.y = character1.y;
 tempVector.z = character1.z;
 tempVector.x = tempVector.x + character1.getForwardDirection().x * float0 * float1;
 tempVector.y = tempVector.y + character1.getForwardDirection().y * float0 * float1;
 tempVector.x = tempVectorBonePos.x - tempVector.x;
 tempVector.y = tempVectorBonePos.y - tempVector.y;
 tempVector.z = 0.0F;
 bool boolean0 = tempVector.getLength() < float2;
 if (boolean0) {
 return int0;
 }
 }

 return -1;
 }

 void exit(IsoGameCharacter owner) {
 }
}
} // namespace states
} // namespace ai
} // namespace zombie
