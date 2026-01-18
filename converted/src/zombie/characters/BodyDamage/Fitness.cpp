#include "zombie/characters/BodyDamage/Fitness.h"

namespace zombie {
namespace characters {
namespace BodyDamage {

public Fitness::Fitness(IsoGameCharacter _parent) {
 // TODO: Implement Fitness
 return nullptr;
}

void Fitness::update() {
 // TODO: Implement update
}

void Fitness::decreaseRegularity() {
 // TODO: Implement decreaseRegularity
}

void Fitness::increasePain(const std::string& string) {
 // TODO: Implement increasePain
}

void Fitness::setCurrentExercise(const std::string& type) {
 // TODO: Implement setCurrentExercise
}

void Fitness::exerciseRepeat() {
 // TODO: Implement exerciseRepeat
}

void Fitness::updateExeTimer() {
 // TODO: Implement updateExeTimer
}

void Fitness::incRegularity() {
 // TODO: Implement incRegularity
}

void Fitness::reduceEndurance() {
 // TODO: Implement reduceEndurance
}

void Fitness::incFutureStiffness() {
 // TODO: Implement incFutureStiffness
}

void Fitness::incStats() {
 // TODO: Implement incStats
}

void Fitness::resetValues() {
 // TODO: Implement resetValues
}

void Fitness::removeStiffnessValue(const std::string& type) {
 // TODO: Implement removeStiffnessValue
}

void Fitness::save(ByteBuffer output) {
 // TODO: Implement save
}

void Fitness::load(ByteBuffer input, int WorldVersion) {
 // TODO: Implement load
}

bool Fitness::onGoingStiffness() {
 // TODO: Implement onGoingStiffness
 return false;
}

int Fitness::getCurrentExeStiffnessTimer(const std::string& type) {
 // TODO: Implement getCurrentExeStiffnessTimer
 return 0;
}

float Fitness::getCurrentExeStiffnessInc(const std::string& type) {
 // TODO: Implement getCurrentExeStiffnessInc
 return 0;
}

IsoGameCharacter Fitness::getParent() {
 // TODO: Implement getParent
 return nullptr;
}

void Fitness::setParent(IsoGameCharacter _parent) {
 // TODO: Implement setParent
}

float Fitness::getRegularity(const std::string& type) {
 // TODO: Implement getRegularity
 return 0;
}

void Fitness::setRegularityMap(Float> _regularityMap) {
 // TODO: Implement setRegularityMap
}

void Fitness::init() {
 // TODO: Implement init
}

void Fitness::initRegularityMapProfession() {
 // TODO: Implement initRegularityMapProfession
}

public Fitness::FitnessExercise(KahluaTableImpl exeDatas) {
 // TODO: Implement FitnessExercise
 return nullptr;
}

} // namespace BodyDamage
} // namespace characters
} // namespace zombie
