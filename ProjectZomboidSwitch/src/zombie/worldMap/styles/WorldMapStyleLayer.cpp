#include <string>
#include <vector>
#include "zombie\worldMap\styles/WorldMapStyleLayer.h"

namespace zombie {
namespace worldMap {
namespace styles {

public WorldMapStyleLayer::WorldMapStyleLayer(const std::string& var1) {
    // TODO: Implement WorldMapStyleLayer
    return nullptr;
}

RGBAf WorldMapStyleLayer::evalColor(RenderArgs var1, std::vector<ColorStop> var2) {
    // TODO: Implement evalColor
    return nullptr;
}

float WorldMapStyleLayer::evalFloat(RenderArgs var1, std::vector<FloatStop> var2) {
    // TODO: Implement evalFloat
    return 0;
}

Texture WorldMapStyleLayer::evalTexture(RenderArgs var1, std::vector<TextureStop> var2) {
    // TODO: Implement evalTexture
    return nullptr;
}

bool WorldMapStyleLayer::filter(WorldMapFeature var1, FilterArgs var2) {
    // TODO: Implement filter
    return false;
}

void WorldMapStyleLayer::renderCell(RenderArgs var1) {
    // TODO: Implement renderCell
}

} // namespace styles
} // namespace worldMap
} // namespace zombie
