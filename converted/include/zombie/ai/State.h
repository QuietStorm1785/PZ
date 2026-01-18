#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/ai/permission/DefaultStatePermissions.h"
#include "zombie/ai/permission/IStatePermissions.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/MoveDeltaModifiers.h"
#include "zombie/core/skinnedmodel/advancedanimation/AnimEvent.h"

namespace zombie {
namespace ai {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class State {
public:
 void enter(IsoGameCharacter owner) {
 }

 void execute(IsoGameCharacter owner) {
 }

 void exit(IsoGameCharacter owner) {
 }

 void animEvent(IsoGameCharacter owner, AnimEvent event) {
 }

 /**
 * Return TRUE if the owner is currently attacking. Defaults to FALSE
 */
 bool isAttacking(IsoGameCharacter owner) {
 return false;
 }

 /**
 * Return TRUE if the owner is currently moving. Defaults to FALSE
 */
 bool isMoving(IsoGameCharacter owner) {
 return false;
 }

 /**
 * @return TRUE if this state handles the "Cancel Action" key or the B controller button.
 */
 bool isDoingActionThatCanBeCancelled() {
 return false;
 }

 void getDeltaModifiers(IsoGameCharacter owner, MoveDeltaModifiers modifiers) {
 }

 /**
 * Return TRUE if the owner should ignore collisions when passing between two squares. Defaults to FALSE
 */
 bool isIgnoreCollide(IsoGameCharacter owner, int fromX, int fromY, int fromZ, int toX, int toY, int toZ) {
 return false;
 }

 std::string getName() {
 return this->getClass().getSimpleName();
 }

 IStatePermissions getStatePermissions() {
 return DefaultStatePermissions.Instance;
 }
}
} // namespace ai
} // namespace zombie
