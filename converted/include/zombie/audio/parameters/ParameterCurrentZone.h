#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/audio/FMODLocalParameter.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoMetaGrid.h"
#include "zombie/iso/IsoObject.h"

namespace zombie {
namespace audio {
namespace parameters {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class ParameterCurrentZone : public FMODLocalParameter {
public:
 const IsoObject object;
 private IsoMetaGrid.Zone metaZone;
 private ParameterCurrentZone.Zone zone = ParameterCurrentZone.Zone.None;

 public ParameterCurrentZone(IsoObject objectx) {
 super("CurrentZone");
 this->object = objectx;
 }

 float calculateCurrentValue() {
 IsoGridSquare square = this->object.getSquare();
 if (square.empty()) {
 this->zone = ParameterCurrentZone.Zone.None;
 return this->zone.label;
 } else if (square.zone == this->metaZone) {
 return this->zone.label;
 } else {
 this->metaZone = square.zone;
 if (this->metaZone.empty()) {
 this->zone = ParameterCurrentZone.Zone.None;
 return this->zone.label;
 } else {
 std::string string = this->metaZone.type;

 this->zone = switch (string) {
 case "DeepForest" -> ParameterCurrentZone.Zone.DeepForest;
 case "Farm" -> ParameterCurrentZone.Zone.Farm;
 case "Forest" -> ParameterCurrentZone.Zone.Forest;
 case "Nav" -> ParameterCurrentZone.Zone.Nav;
 case "TownZone" -> ParameterCurrentZone.Zone.Town;
 case "TrailerPark" -> ParameterCurrentZone.Zone.TrailerPark;
 case "Vegitation" -> ParameterCurrentZone.Zone.Vegetation;
 default -> ParameterCurrentZone.Zone.None;
 };
 return this->zone.label;
 }
 }
 }

 static enum Zone {
 None(0),
 DeepForest(1),
 Farm(2),
 Forest(3),
 Nav(4),
 Town(5),
 TrailerPark(6),
 Vegetation(7);

 const int label;

 private Zone(int int1) {
 this->label = int1;
 }
 }
}
} // namespace parameters
} // namespace audio
} // namespace zombie
