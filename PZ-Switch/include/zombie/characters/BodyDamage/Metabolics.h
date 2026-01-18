#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace characters {
namespace BodyDamage {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

/**
 * TurboTuTone.
 */
enum class Metabolics {
 Sleeping(0.8F), SeatedResting(1.0F), StandingAtRest(1.2F),
 SedentaryActivity(1.2F), Default(1.6F), DrivingCar(1.4F), LightDomestic(1.9F),
 HeavyDomestic(2.9F), DefaultExercise(3.0F), UsingTools(3.4F), LightWork(4.3F),
 MediumWork(5.4F), DiggingSpade(6.5F), HeavyWork(7.0F), ForestryAxe(8.5F),
 Walking2kmh(1.9F), Walking5kmh(3.1F), Running10kmh(6.5F), Running15kmh(9.5F),
 JumpFence(4.0F), ClimbRope(8.0F), Fitness(6.0F), FitnessHeavy(9.0F),
 MAX(10.3F);

 const float met;

 private Metabolics(float float0){this->met = float0;}

float getMet() { return this->met; }

float getWm2() { return MetToWm2(); }

float getW() { return MetToW(); }

float getBtuHr() { return MetToBtuHr(); }

static float MetToWm2(float _met) { return 58.0F * _met; }

static float MetToW(float _met) { return MetToWm2(); }

static float MetToBtuHr(float _met) { return 356.0F * _met; }
} // namespace BodyDamage
} // namespace characters
} // namespace zombie
} // namespace zombie
