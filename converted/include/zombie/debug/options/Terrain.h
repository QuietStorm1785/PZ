#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/debug/BooleanDebugOption.h"

namespace zombie {
namespace debug {
namespace options {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class Terrain : public OptionGroup {
public:
 public Terrain.RenderTiles RenderTiles = new Terrain.RenderTiles(this->Group);

 public Terrain() {
 super("Terrain");
 }

 class RenderTiles extends OptionGroup {
 const BooleanDebugOption Enable = newDebugOnlyOption(this->Group, "Enable", true);
 const BooleanDebugOption NewRender = newDebugOnlyOption(this->Group, "NewRender", true);
 const BooleanDebugOption Shadows = newDebugOnlyOption(this->Group, "Shadows", true);
 const BooleanDebugOption BloodDecals = newDebugOnlyOption(this->Group, "BloodDecals", true);
 const BooleanDebugOption Water = newDebugOnlyOption(this->Group, "Water", true);
 const BooleanDebugOption WaterShore = newDebugOnlyOption(this->Group, "WaterShore", true);
 const BooleanDebugOption WaterBody = newDebugOnlyOption(this->Group, "WaterBody", true);
 const BooleanDebugOption Lua = newDebugOnlyOption(this->Group, "Lua", true);
 const BooleanDebugOption VegetationCorpses = newDebugOnlyOption(this->Group, "VegetationCorpses", true);
 const BooleanDebugOption MinusFloorCharacters = newDebugOnlyOption(this->Group, "MinusFloorCharacters", true);
 const BooleanDebugOption RenderGridSquares = newDebugOnlyOption(this->Group, "RenderGridSquares", true);
 const BooleanDebugOption RenderSprites = newDebugOnlyOption(this->Group, "RenderSprites", true);
 const BooleanDebugOption OverlaySprites = newDebugOnlyOption(this->Group, "OverlaySprites", true);
 const BooleanDebugOption AttachedAnimSprites = newDebugOnlyOption(this->Group, "AttachedAnimSprites", true);
 const BooleanDebugOption AttachedChildren = newDebugOnlyOption(this->Group, "AttachedChildren", true);
 const BooleanDebugOption AttachedWallBloodSplats = newDebugOnlyOption(this->Group, "AttachedWallBloodSplats", true);
 const BooleanDebugOption UseShaders = newOption(this->Group, "UseShaders", true);
 const BooleanDebugOption HighContrastBg = newDebugOnlyOption(this->Group, "HighContrastBg", false);
 public Terrain.RenderTiles.IsoGridSquare IsoGridSquare = new Terrain.RenderTiles.IsoGridSquare(this->Group);

 public RenderTiles(IDebugOptionGroup iDebugOptionGroup) {
 super(iDebugOptionGroup, "RenderTiles");
 }

 class IsoGridSquare extends OptionGroup {
 const BooleanDebugOption RenderMinusFloor = newDebugOnlyOption(this->Group, "RenderMinusFloor", true);
 const BooleanDebugOption DoorsAndWalls = newDebugOnlyOption(this->Group, "DoorsAndWalls", true);
 const BooleanDebugOption DoorsAndWalls_SimpleLighting = newDebugOnlyOption(this->Group, "DoorsAndWallsSL", true);
 const BooleanDebugOption Objects = newDebugOnlyOption(this->Group, "Objects", true);
 const BooleanDebugOption MeshCutdown = newDebugOnlyOption(this->Group, "MeshCutDown", true);
 const BooleanDebugOption IsoPadding = newDebugOnlyOption(this->Group, "IsoPadding", true);
 const BooleanDebugOption IsoPaddingDeDiamond = newDebugOnlyOption(this->Group, "IsoPaddingDeDiamond", true);
 const BooleanDebugOption IsoPaddingAttached = newDebugOnlyOption(this->Group, "IsoPaddingAttached", true);
 const BooleanDebugOption ShoreFade = newDebugOnlyOption(this->Group, "ShoreFade", true);
 public Terrain.RenderTiles.IsoGridSquare.Walls Walls = new Terrain.RenderTiles.IsoGridSquare.Walls(this->Group);
 public Terrain.RenderTiles.IsoGridSquare.Floor Floor = new Terrain.RenderTiles.IsoGridSquare.Floor(this->Group);

 public IsoGridSquare(IDebugOptionGroup iDebugOptionGroup) {
 super(iDebugOptionGroup, "IsoGridSquare");
 }

 class Floor extends OptionGroup {
 const BooleanDebugOption Lighting = newDebugOnlyOption(this->Group, "Lighting", true);
 const BooleanDebugOption LightingOld = newDebugOnlyOption(this->Group, "LightingOld", false);
 const BooleanDebugOption LightingDebug = newDebugOnlyOption(this->Group, "LightingDebug", false);

 public Floor(IDebugOptionGroup iDebugOptionGroup) {
 super(iDebugOptionGroup, "Floor");
 }
 }

 class Walls extends OptionGroup {
 const BooleanDebugOption NW = newDebugOnlyOption(this->Group, "NW", true);
 const BooleanDebugOption W = newDebugOnlyOption(this->Group, "W", true);
 const BooleanDebugOption N = newDebugOnlyOption(this->Group, "N", true);
 const BooleanDebugOption Render = newDebugOnlyOption(this->Group, "Render", true);
 const BooleanDebugOption Lighting = newDebugOnlyOption(this->Group, "Lighting", true);
 const BooleanDebugOption LightingDebug = newDebugOnlyOption(this->Group, "LightingDebug", false);
 const BooleanDebugOption LightingOldDebug = newDebugOnlyOption(this->Group, "LightingOldDebug", false);
 const BooleanDebugOption AttachedSprites = newDebugOnlyOption(this->Group, "AttachedSprites", true);

 public Walls(IDebugOptionGroup iDebugOptionGroup) {
 super(iDebugOptionGroup, "Walls");
 }
 }
 }
 }
}
} // namespace options
} // namespace debug
} // namespace zombie
