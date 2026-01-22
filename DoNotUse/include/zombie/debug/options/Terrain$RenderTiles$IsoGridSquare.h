#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/debug/BooleanDebugOption.h"
#include "zombie/debug/options/Terrain/RenderTiles.h"
#include "zombie/debug/options/Terrain/RenderTiles/IsoGridSquare/Floor.h"
#include "zombie/debug/options/Terrain/RenderTiles/IsoGridSquare/Walls.h"

namespace zombie {
namespace debug {
namespace options {


class Terrain {
public:
    const BooleanDebugOption RenderMinusFloor;
    const BooleanDebugOption DoorsAndWalls;
    const BooleanDebugOption DoorsAndWalls_SimpleLighting;
    const BooleanDebugOption Objects;
    const BooleanDebugOption MeshCutdown;
    const BooleanDebugOption IsoPadding;
    const BooleanDebugOption IsoPaddingDeDiamond;
    const BooleanDebugOption IsoPaddingAttached;
    const BooleanDebugOption ShoreFade;
    const Walls Walls;
    const Floor Floor;

   public Terrain$RenderTiles$IsoGridSquare(RenderTiles var1, IDebugOptionGroup var2) {
      super(var2, "IsoGridSquare");
      this.this$1 = var1;
      this.RenderMinusFloor = newDebugOnlyOption(this.Group, "RenderMinusFloor", true);
      this.DoorsAndWalls = newDebugOnlyOption(this.Group, "DoorsAndWalls", true);
      this.DoorsAndWalls_SimpleLighting = newDebugOnlyOption(this.Group, "DoorsAndWallsSL", true);
      this.Objects = newDebugOnlyOption(this.Group, "Objects", true);
      this.MeshCutdown = newDebugOnlyOption(this.Group, "MeshCutDown", true);
      this.IsoPadding = newDebugOnlyOption(this.Group, "IsoPadding", true);
      this.IsoPaddingDeDiamond = newDebugOnlyOption(this.Group, "IsoPaddingDeDiamond", true);
      this.IsoPaddingAttached = newDebugOnlyOption(this.Group, "IsoPaddingAttached", true);
      this.ShoreFade = newDebugOnlyOption(this.Group, "ShoreFade", true);
      this.Walls = std::make_shared<Walls>(this, this.Group);
      this.Floor = std::make_shared<Floor>(this, this.Group);
   }
}
} // namespace options
} // namespace debug
} // namespace zombie
