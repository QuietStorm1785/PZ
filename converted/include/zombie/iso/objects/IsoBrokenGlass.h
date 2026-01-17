#pragma once
#include "zombie/core/Rand.h"
#include "zombie/core/opengl/Shader.h"
#include "zombie/core/textures/ColorInfo.h"
#include "zombie/iso/IsoCell.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/sprite/IsoSpriteManager.h"
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace iso {
namespace objects {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class IsoBrokenGlass : public IsoObject {
public:
public
  IsoBrokenGlass(IsoCell cell) {
    super(cell);
    int int0 = Rand.Next(4);
    this.sprite = IsoSpriteManager.instance.getSprite("brokenglass_1_" + int0);
  }

  std::string getObjectName() { return "IsoBrokenGlass"; }

  void load(ByteBuffer bb, int WorldVersion, bool IS_DEBUG_SAVE) {
    super.load(bb, WorldVersion, IS_DEBUG_SAVE);
  }

  void save(ByteBuffer bb, bool IS_DEBUG_SAVE) {
    super.save(bb, IS_DEBUG_SAVE);
  }

  void addToWorld() { super.addToWorld(); }

  void removeFromWorld() { super.removeFromWorld(); }

  void render(float x, float y, float z, ColorInfo col, bool bDoChild,
              bool bWallLightingPass, Shader shader) {
    super.render(x, y, z, col, bDoChild, bWallLightingPass, shader);
  }

  void renderObjectPicker(float x, float y, float z, ColorInfo lightInfo) {}
}
} // namespace objects
} // namespace iso
} // namespace zombie
