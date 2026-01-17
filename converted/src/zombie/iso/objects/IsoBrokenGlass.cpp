#include "zombie/iso/objects/IsoBrokenGlass.h"

namespace zombie {
namespace iso {
namespace objects {

public
IsoBrokenGlass::IsoBrokenGlass(IsoCell cell) {
  // TODO: Implement IsoBrokenGlass
  return nullptr;
}

std::string IsoBrokenGlass::getObjectName() {
  // TODO: Implement getObjectName
  return "";
}

void IsoBrokenGlass::load(ByteBuffer bb, int WorldVersion, bool IS_DEBUG_SAVE) {
  // TODO: Implement load
}

void IsoBrokenGlass::save(ByteBuffer bb, bool IS_DEBUG_SAVE) {
  // TODO: Implement save
}

void IsoBrokenGlass::addToWorld() {
  // TODO: Implement addToWorld
}

void IsoBrokenGlass::removeFromWorld() {
  // TODO: Implement removeFromWorld
}

void IsoBrokenGlass::render(float x, float y, float z, ColorInfo col,
                            bool bDoChild, bool bWallLightingPass,
                            Shader shader) {
  // TODO: Implement render
}

void IsoBrokenGlass::renderObjectPicker(float x, float y, float z,
                                        ColorInfo lightInfo) {
  // TODO: Implement renderObjectPicker
}

} // namespace objects
} // namespace iso
} // namespace zombie
