#include "zombie/worldMap/styles/WorldMapStyleLayer.h"

namespace zombie {
namespace worldMap {
namespace styles {

public
WorldMapStyleLayer::WorldMapStyleLayer(const std::string &id) {
  // TODO: Implement WorldMapStyleLayer
  return nullptr;
}

float WorldMapStyleLayer::evalFloat(
    WorldMapStyleLayer.RenderArgs renderArgs,
    ArrayList<WorldMapStyleLayer.FloatStop> arrayList) {
  // TODO: Implement evalFloat
  return 0;
}

Texture WorldMapStyleLayer::evalTexture(
    WorldMapStyleLayer.RenderArgs renderArgs,
    ArrayList<WorldMapStyleLayer.TextureStop> arrayList) {
  // TODO: Implement evalTexture
  return nullptr;
}

bool WorldMapStyleLayer::filter(WorldMapFeature feature,
                                WorldMapStyleLayer.FilterArgs args) {
  // TODO: Implement filter
  return false;
}

void WorldMapStyleLayer::renderCell(WorldMapStyleLayer.RenderArgs args) {
  // TODO: Implement renderCell
}

public
WorldMapStyleLayer::ColorStop(float float0, int int0, int int1, int int2,
                              int int3) {
  // TODO: Implement ColorStop
  return nullptr;
}

public
WorldMapStyleLayer::FloatStop(float float0, float float1) {
  // TODO: Implement FloatStop
  return nullptr;
}

bool WorldMapStyleLayer::filter(WorldMapFeature feature,
                                WorldMapStyleLayer.FilterArgs args) {
  // TODO: Implement filter
  return false;
}

public
WorldMapStyleLayer::RGBAf() {
  // TODO: Implement RGBAf
  return nullptr;
}

public
WorldMapStyleLayer::TextureStop(float float0, const std::string &string) {
  // TODO: Implement TextureStop
  return nullptr;
}

} // namespace styles
} // namespace worldMap
} // namespace zombie
