#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameTime.h"
#include "zombie/ai/State.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/characters/skills/PerkFactory.h"
#include "zombie/iso/IsoCell.h"
#include "zombie/iso/IsoDirections.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/SpriteDetails/IsoFlagType.h"
#include "zombie/iso/objects/IsoThumpable.h"
#include "zombie/iso/objects/IsoWindow.h"
#include "zombie/iso/objects/IsoWindowFrame.h"

namespace zombie {
namespace ai {
namespace states {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class ClimbSheetRopeState : public State {
public:
 static const float CLIMB_SPEED = 0.16F;
 static const float CLIMB_SLOWDOWN = 0.5F;
 static const ClimbSheetRopeState _instance = new ClimbSheetRopeState();

 static ClimbSheetRopeState instance() {
 return _instance;
 }

 void enter(IsoGameCharacter owner) {
 owner.setIgnoreMovement(true);
 owner.setbClimbing(true);
 owner.setVariable("ClimbRope", true);
 }

 void execute(IsoGameCharacter owner) {
 std::unordered_map hashMap = owner.getStateMachineParams(this);
 float float0 = 0.0F;
 float float1 = 0.0F;
 if (owner.getCurrentSquare().getProperties().Is(IsoFlagType.climbSheetN) || owner.getCurrentSquare().getProperties().Is(IsoFlagType.climbSheetTopN) {
 owner.setDir(IsoDirections.N);
 float0 = 0.54F;
 float1 = 0.39F;
 }

 if (owner.getCurrentSquare().getProperties().Is(IsoFlagType.climbSheetS) || owner.getCurrentSquare().getProperties().Is(IsoFlagType.climbSheetTopS) {
 owner.setDir(IsoDirections.S);
 float0 = 0.118F;
 float1 = 0.5756F;
 }

 if (owner.getCurrentSquare().getProperties().Is(IsoFlagType.climbSheetW) || owner.getCurrentSquare().getProperties().Is(IsoFlagType.climbSheetTopW) {
 owner.setDir(IsoDirections.W);
 float0 = 0.4F;
 float1 = 0.7F;
 }

 if (owner.getCurrentSquare().getProperties().Is(IsoFlagType.climbSheetE) || owner.getCurrentSquare().getProperties().Is(IsoFlagType.climbSheetTopE) {
 owner.setDir(IsoDirections.E);
 float0 = 0.5417F;
 float1 = 0.3144F;
 }

 float float2 = owner.x - (int)owner.x;
 float float3 = owner.y - (int)owner.y;
 if (float2 != float0) {
 float float4 = (float0 - float2) / 4.0F;
 float2 += float4;
 owner.x = (int)owner.x + float2;
 }

 if (float3 != float1) {
 float float5 = (float1 - float3) / 4.0F;
 float3 += float5;
 owner.y = (int)owner.y + float3;
 }

 owner.nx = owner.x;
 owner.ny = owner.y;
 float float6 = this->getClimbSheetRopeSpeed(owner);
 owner.getSpriteDef().AnimFrameIncrease = float6;
 float float7 = owner.z + float6 / 10.0F * GameTime.instance.getMultiplier();
 float7 = Math.min(float7, 7.0F);

 for (int int0 = (int)owner.z; int0 <= float7; int0++) {
 IsoCell cell = IsoWorld.instance.getCell();
 IsoGridSquare square0 = cell.getGridSquare((double)owner.getX(), (double)owner.getY(), (double)int0);
 if (IsoWindow.isTopOfSheetRopeHere(square0) {
 owner.z = int0;
 owner.setCurrent(square0);
 owner.setCollidable(true);
 IsoGridSquare square1 = square0.nav[owner.dir.index()];
 if (square1 != nullptr) {
 if (!square1.TreatAsSolidFloor()) {
 owner.climbDownSheetRope();
 return;
 }

 IsoWindow window = square0.getWindowTo(square1);
 if (window != nullptr) {
 if (!window.open) {
 window.ToggleWindow(owner);
 }

 if (!window.canClimbThrough(owner) {
 owner.climbDownSheetRope();
 return;
 }

 owner.climbThroughWindow(window, 4);
 return;
 }

 IsoThumpable thumpable = square0.getWindowThumpableTo(square1);
 if (thumpable != nullptr) {
 if (!thumpable.canClimbThrough(owner) {
 owner.climbDownSheetRope();
 return;
 }

 owner.climbThroughWindow(thumpable, 4);
 return;
 }

 thumpable = square0.getHoppableThumpableTo(square1);
 if (thumpable != nullptr) {
 if (!IsoWindow.canClimbThroughHelper(owner, square0, square1, owner.dir == IsoDirections.N || owner.dir == IsoDirections.S) {
 owner.climbDownSheetRope();
 return;
 }

 owner.climbOverFence(owner.dir);
 return;
 }

 IsoObject object0 = square0.getWindowFrameTo(square1);
 if (object0 != nullptr) {
 if (!IsoWindowFrame.canClimbThrough(object0, owner) {
 owner.climbDownSheetRope();
 return;
 }

 owner.climbThroughWindowFrame(object0);
 return;
 }

 IsoObject object1 = square0.getWallHoppableTo(square1);
 if (object1 != nullptr) {
 if (!IsoWindow.canClimbThroughHelper(owner, square0, square1, owner.dir == IsoDirections.N || owner.dir == IsoDirections.S) {
 owner.climbDownSheetRope();
 return;
 }

 owner.climbOverFence(owner.dir);
 return;
 }
 }

 return;
 }
 }

 owner.z = float7;
 if (owner.z >= 7.0F) {
 owner.setCollidable(true);
 owner.clearVariable("ClimbRope");
 }

 if (!IsoWindow.isSheetRopeHere(owner.getCurrentSquare())) {
 owner.setCollidable(true);
 owner.setbClimbing(false);
 owner.setbFalling(true);
 owner.clearVariable("ClimbRope");
 }

 if (owner instanceof IsoPlayer && ((IsoPlayer)owner).isLocalPlayer()) {
 ((IsoPlayer)owner).dirtyRecalcGridStackTime = 2.0F;
 }
 }

 void exit(IsoGameCharacter owner) {
 owner.setIgnoreMovement(false);
 owner.setbClimbing(false);
 owner.clearVariable("ClimbRope");
 }

 float getClimbSheetRopeSpeed(IsoGameCharacter owner) {
 float float0 = 0.16F;
 switch (owner.getPerkLevel(PerkFactory.Perks.Strength) {
 case 0:
 float0 -= 0.12F;
 break;
 case 1:
 case 2:
 case 3:
 float0 -= 0.09F;
 case 4:
 case 5:
 default:
 break;
 case 6:
 case 7:
 float0 += 0.05F;
 break;
 case 8:
 case 9:
 float0 += 0.09F;
 break;
 case 10:
 float0 += 0.12F;
 }

 return float0 * 0.5F;
 }
}
} // namespace states
} // namespace ai
} // namespace zombie
