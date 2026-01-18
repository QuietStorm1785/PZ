#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/audio/FMODLocalParameter.h"
#include "zombie/characters/IsoGameCharacter.h"

namespace zombie {
namespace audio {
namespace parameters {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class ParameterMeleeHitSurface : public FMODLocalParameter {
public:
 const IsoGameCharacter character;
 private ParameterMeleeHitSurface.Material material = ParameterMeleeHitSurface.Material.Default;

 public ParameterMeleeHitSurface(IsoGameCharacter _character) {
 super("MeleeHitSurface");
 this->character = _character;
 }

 float calculateCurrentValue() {
 return this->getMaterial().label;
 }

 private ParameterMeleeHitSurface.Material getMaterial() {
 return this->material;
 }

 void setMaterial(ParameterMeleeHitSurface.Material _material) {
 this->material = _material;
 }

 public static enum Material {
 Default(0),
 Body(1),
 Fabric(2),
 Glass(3),
 Head(4),
 Metal(5),
 Plastic(6),
 Stone(7),
 Wood(8),
 GarageDoor(9),
 MetalDoor(10),
 MetalGate(11),
 PrisonMetalDoor(12),
 SlidingGlassDoor(13),
 WoodDoor(14),
 WoodGate(15),
 Tree(16);

 const int label;

 private Material(int int1) {
 this->label = int1;
 }
 }
}
} // namespace parameters
} // namespace audio
} // namespace zombie
