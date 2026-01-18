#pragma once
#include "zombie/characters/BodyDamage/BodyPartType.h"
#include "zombie/core/textures/Texture.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class ZombieTemplateManager {
public:
  Texture addOverlayToTexture(ArrayList<ZombieTemplateManager.BodyOverlay> var1,
                              Texture var2) {
    return null;
  }

public
  class BodyOverlay {
    BodyPartType location;
  public
    ZombieTemplateManager.OverlayType type;
  }

  public static enum OverlayType {
    BloodLight, BloodMedium, BloodHeavy;
  }

  public class ZombieTemplate {
    Texture tex;
  }
}
} // namespace zombie
