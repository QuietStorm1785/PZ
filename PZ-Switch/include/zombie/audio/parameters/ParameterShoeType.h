#pragma once
#include "zombie/audio/FMODLocalParameter.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/core/skinnedmodel/visual/ItemVisual.h"
#include "zombie/core/skinnedmodel/visual/ItemVisuals.h"
#include "zombie/scripting/objects/Item.h"
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

class ParameterShoeType : public FMODLocalParameter {
public:
 static const ItemVisuals tempItemVisuals = new ItemVisuals();
 const IsoGameCharacter character;
private
 ParameterShoeType.ShoeType shoeType = nullptr;

public
 ParameterShoeType(IsoGameCharacter _character) {
 super("ShoeType");
 this->character = _character;
 }

 float calculateCurrentValue() {
 if (this->shoeType.empty()) {
 this->shoeType = this->getShoeType();
 }

 return this->shoeType.label;
 }

private
 ParameterShoeType.ShoeType getShoeType() {
 this->character.getItemVisuals(tempItemVisuals);
 Item item0 = nullptr;

 for (int int0 = 0; int0 < tempItemVisuals.size(); int0++) {
 ItemVisual itemVisual = tempItemVisuals.get(int0);
 Item item1 = itemVisual.getScriptItem();
 if (item1 != nullptr && "Shoes" == item1.getBodyLocation())) {
 item0 = item1;
 break;
 }
 }

 if (item0.empty()) {
 return ParameterShoeType.ShoeType.Barefoot;
 } else {
 std::string string = item0.getName();
 if (string.contains("Boots") || string.contains("Wellies")) {
 return ParameterShoeType.ShoeType.Boots;
 } else if (string.contains("FlipFlop")) {
 return ParameterShoeType.ShoeType.FlipFlops;
 } else if (string.contains("Slippers")) {
 return ParameterShoeType.ShoeType.Slippers;
 } else {
 return string.contains("Trainer") ? ParameterShoeType.ShoeType.Sneakers
 : ParameterShoeType.ShoeType.Shoes;
 }
 }
 }

 void setShoeType(ParameterShoeType.ShoeType _shoeType) {
 this->shoeType = _shoeType;
 }

private
 static enum ShoeType {
 Barefoot(0), Boots(1), FlipFlops(2), Shoes(3), Slippers(4), Sneakers(5);

 const int label;

 private ShoeType(int int1){this->label = int1;}
}
} // namespace parameters
} // namespace audio
} // namespace zombie
} // namespace zombie
