#pragma once
#include "zombie/audio/FMODLocalParameter.h"
#include "zombie/characters/IsoGameCharacter.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace audio {
namespace parameters {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class ParameterEquippedBaggageContainer : public FMODLocalParameter {
public:
 const IsoGameCharacter character;
private
 ParameterEquippedBaggageContainer.ContainerType containerType =
 ParameterEquippedBaggageContainer.ContainerType.None;

public
 ParameterEquippedBaggageContainer(IsoGameCharacter _character) {
 super("EquippedBaggageContainer");
 this->character = _character;
 }

 float calculateCurrentValue() { return this->containerType.label; }

 void setContainerType(
 ParameterEquippedBaggageContainer.ContainerType _containerType) {
 this->containerType = _containerType;
 }

 void setContainerType(const std::string &_containerType) {
 if (_containerType != nullptr) {
 try {
 this->containerType =
 ParameterEquippedBaggageContainer.ContainerType.valueOf(
 _containerType);
 } catch (IllegalArgumentException illegalArgumentException) {
 }
 }
 }

public
 static enum ContainerType {
 None(0), HikingBag(1), DuffleBag(2), PlasticBag(3), SchoolBag(4),
 ToteBag(5), GarbageBag(6);

 const int label;

 private ContainerType(int int1){this->label = int1;}
}
} // namespace parameters
} // namespace audio
} // namespace zombie
} // namespace zombie
