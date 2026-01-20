#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/debug/BooleanDebugOption.h"
#include "zombie/debug/options/Terrain/RenderTiles/IsoGridSquare.h"

namespace zombie {
namespace debug {
namespace options {


class Terrain {
public:
    const BooleanDebugOption Enable;
    const BooleanDebugOption NewRender;
    const BooleanDebugOption Shadows;
    const BooleanDebugOption BloodDecals;
    const BooleanDebugOption Water;
    const BooleanDebugOption WaterShore;
    const BooleanDebugOption WaterBody;
    const BooleanDebugOption Lua;
    const BooleanDebugOption VegetationCorpses;
    const BooleanDebugOption MinusFloorCharacters;
    const BooleanDebugOption RenderGridSquares;
    const BooleanDebugOption RenderSprites;
    const BooleanDebugOption OverlaySprites;
    const BooleanDebugOption AttachedAnimSprites;
    const BooleanDebugOption AttachedChildren;
    const BooleanDebugOption AttachedWallBloodSplats;
    const BooleanDebugOption UseShaders;
    const BooleanDebugOption HighContrastBg;
    const IsoGridSquare IsoGridSquare;

   public Terrain$RenderTiles(Terrain var1, IDebugOptionGroup var2) {
      super(var2, "RenderTiles");
      this.this$0 = var1;
      this.Enable = newDebugOnlyOption(this.Group, "Enable", true);
      this.NewRender = newDebugOnlyOption(this.Group, "NewRender", true);
      this.Shadows = newDebugOnlyOption(this.Group, "Shadows", true);
      this.BloodDecals = newDebugOnlyOption(this.Group, "BloodDecals", true);
      this.Water = newDebugOnlyOption(this.Group, "Water", true);
      this.WaterShore = newDebugOnlyOption(this.Group, "WaterShore", true);
      this.WaterBody = newDebugOnlyOption(this.Group, "WaterBody", true);
      this.Lua = newDebugOnlyOption(this.Group, "Lua", true);
      this.VegetationCorpses = newDebugOnlyOption(this.Group, "VegetationCorpses", true);
      this.MinusFloorCharacters = newDebugOnlyOption(this.Group, "MinusFloorCharacters", true);
      this.RenderGridSquares = newDebugOnlyOption(this.Group, "RenderGridSquares", true);
      this.RenderSprites = newDebugOnlyOption(this.Group, "RenderSprites", true);
      this.OverlaySprites = newDebugOnlyOption(this.Group, "OverlaySprites", true);
      this.AttachedAnimSprites = newDebugOnlyOption(this.Group, "AttachedAnimSprites", true);
      this.AttachedChildren = newDebugOnlyOption(this.Group, "AttachedChildren", true);
      this.AttachedWallBloodSplats = newDebugOnlyOption(this.Group, "AttachedWallBloodSplats", true);
      this.UseShaders = newOption(this.Group, "UseShaders", true);
      this.HighContrastBg = newDebugOnlyOption(this.Group, "HighContrastBg", false);
      this.IsoGridSquare = std::make_shared<IsoGridSquare>(this, this.Group);
   }
}
} // namespace options
} // namespace debug
} // namespace zombie
