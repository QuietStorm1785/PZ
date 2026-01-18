#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/BodyDamage/BodyPartType.h"
#include "zombie/core/textures/Texture.h"

namespace zombie {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class ZombieTemplateManager {
public:
 Texture addOverlayToTexture(ArrayList<ZombieTemplateManager.BodyOverlay> var1, Texture var2) {
 return nullptr;
 }

 class BodyOverlay {
 BodyPartType location;
 public ZombieTemplateManager.OverlayType type;
 }

 public static enum OverlayType {
 BloodLight,
 BloodMedium,
 BloodHeavy;
 }

 class ZombieTemplate {
 Texture tex;
 }
}
} // namespace zombie
