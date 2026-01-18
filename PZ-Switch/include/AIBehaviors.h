#pragma once
#include <memory>
#include <vector>
#include <cstdlib>
#include <cmath>

namespace zombie {
namespace ai {

struct Vec3 {
 float x, y, z;
 Vec3(float x = 0, float y = 0, float z = 0) : x(x), y(y), z(z) {}
};

enum class BehaviorState {
 IDLE,
 WANDER,
 CHASE,
 ATTACK,
 FLEE,
 HUNT,
 INVESTIGATE
};

class Behavior {
public:
 virtual ~Behavior() = default;
 virtual void onEnter() {}
 virtual void onExit() {}
 virtual void update(float deltaTime) = 0;
 virtual BehaviorState getState() const = 0;
};

class IdleBehavior : public Behavior {
public:
 void update(float deltaTime) override;
 BehaviorState getState() const override { return BehaviorState::IDLE; }
};

class WanderBehavior : public Behavior {
public:
 WanderBehavior(float speed = 1.0f, float range = 20.0f);
 void update(float deltaTime) override;
 BehaviorState getState() const override { return BehaviorState::WANDER; }
 
private:
 float speed;
 float range;
 float wanderTimer;
 Vec3 targetPos;
};

class ChaseBehavior : public Behavior {
public:
 ChaseBehavior(Vec3 target, float speed = 2.0f);
 void update(float deltaTime) override;
 BehaviorState getState() const override { return BehaviorState::CHASE; }
 
 void setTarget(Vec3 t) { targetPos = t; }
 
private:
 Vec3 targetPos;
 float speed;
};

class AttackBehavior : public Behavior {
public:
 AttackBehavior(float damage = 5.0f, float range = 1.5f);
 void update(float deltaTime) override;
 BehaviorState getState() const override { return BehaviorState::ATTACK; }
 
private:
 float damage;
 float attackRange;
 float attackCooldown;
};

class BehaviorTree {
public:
 BehaviorTree();
 ~BehaviorTree() = default;
 
 void pushBehavior(std::shared_ptr<Behavior> behavior);
 void popBehavior();
 void updateBehavior(float deltaTime);
 
 BehaviorState getCurrentState() const;
 
private:
 std::vector<std::shared_ptr<Behavior>> behaviorStack;
};

} // namespace ai
} // namespace zombie
