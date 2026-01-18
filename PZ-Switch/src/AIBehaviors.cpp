#include "AIBehaviors.h"

namespace zombie {
namespace ai {

void IdleBehavior::update(float deltaTime) {
 // Idle state - do nothing
}

WanderBehavior::WanderBehavior(float speed, float range)
 : speed(speed), range(range), wanderTimer(0.0f) {
 targetPos = Vec3(0, 0, 0);
}

void WanderBehavior::update(float deltaTime) {
 wanderTimer += deltaTime;
 if (wanderTimer > 2.0f) {
 wanderTimer = 0.0f;
 // Pick new random target
 targetPos = Vec3(
 (rand() % (int)range) - range / 2,
 (rand() % (int)range) - range / 2,
 0
 );
 }
}

ChaseBehavior::ChaseBehavior(Vec3 target, float speed)
 : targetPos(target), speed(speed) {
}

void ChaseBehavior::update(float deltaTime) {
 // Chase target position
}

AttackBehavior::AttackBehavior(float damage, float range)
 : damage(damage), attackRange(range), attackCooldown(0.0f) {
}

void AttackBehavior::update(float deltaTime) {
 if (attackCooldown > 0.0f) {
 attackCooldown -= deltaTime;
 }
}

BehaviorTree::BehaviorTree() {
}

void BehaviorTree::pushBehavior(std::shared_ptr<Behavior> behavior) {
 if (behavior) {
 behavior->onEnter();
 behaviorStack.push_back(behavior);
 }
}

void BehaviorTree::popBehavior() {
 if (!behaviorStack.empty()) {
 behaviorStack.back()->onExit();
 behaviorStack.pop_back();
 }
}

void BehaviorTree::updateBehavior(float deltaTime) {
 if (!behaviorStack.empty()) {
 behaviorStack.back()->update(deltaTime);
 }
}

BehaviorState BehaviorTree::getCurrentState() const {
 if (!behaviorStack.empty()) {
 return behaviorStack.back()->getState();
 }
 return BehaviorState::IDLE;
}

} // namespace ai
} // namespace zombie
