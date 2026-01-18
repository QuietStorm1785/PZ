#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "fmod/fmod/FMODManager.h"
#include "zombie/audio/FMODLocalParameter.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/properties/PropertyContainer.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/SpriteDetails/IsoFlagType.h"
#include "zombie/iso/objects/IsoWorldInventoryObject.h"
#include "zombie/util/list/PZArrayList.h"

namespace zombie {
namespace audio {
namespace parameters {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class ParameterFootstepMaterial : public FMODLocalParameter {
public:
 const IsoGameCharacter character;

 public ParameterFootstepMaterial(IsoGameCharacter _character) {
 super("FootstepMaterial");
 this->character = _character;
 }

 float calculateCurrentValue() {
 return this->getMaterial().label;
 }

 private ParameterFootstepMaterial.FootstepMaterial getMaterial() {
 if (FMODManager.instance.getNumListeners() == 1) {
 for (int int0 = 0; int0 < IsoPlayer.numPlayers; int0++) {
 IsoPlayer player = IsoPlayer.players[int0];
 if (player != nullptr && player != this->character && !player.Traits.Deaf.isSet()) {
 if ((int)player.getZ() < (int)this->character.getZ()) {
 return ParameterFootstepMaterial.FootstepMaterial.Upstairs;
 }
 break;
 }
 }
 }

 void* object0 = nullptr;
 IsoObject object1 = nullptr;
 IsoGridSquare square = this->character.getCurrentSquare();
 if (square != nullptr) {
 PZArrayList pZArrayList = square.getObjects();

 for (int int1 = 0; int1 < pZArrayList.size(); int1++) {
 IsoObject object2 = (IsoObject)pZArrayList.get(int1);
 if (!(object2 instanceof IsoWorldInventoryObject) {
 PropertyContainer propertyContainer = object2.getProperties();
 if (propertyContainer != nullptr) {
 if (propertyContainer.Is(IsoFlagType.solidfloor) {
 ;
 }

 if (propertyContainer.Is("FootstepMaterial")) {
 object1 = object2;
 }
 }
 }
 }
 }

 if (object1 != nullptr) {
 try {
 std::string string = object1.getProperties().Val("FootstepMaterial");
 return ParameterFootstepMaterial.FootstepMaterial.valueOf(string);
 } catch (IllegalArgumentException illegalArgumentException) {
 bool boolean0 = true;
 }
 }

 return ParameterFootstepMaterial.FootstepMaterial.Concrete;
 }

 static enum FootstepMaterial {
 Upstairs(0),
 BrokenGlass(1),
 Concrete(2),
 Grass(3),
 Gravel(4),
 Puddle(5),
 Snow(6),
 Wood(7),
 Carpet(8),
 Dirt(9),
 Sand(10),
 Ceramic(11),
 Metal(12);

 const int label;

 private FootstepMaterial(int int1) {
 this->label = int1;
 }
 }
}
} // namespace parameters
} // namespace audio
} // namespace zombie
