#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/textures/Texture.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace Texture {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class Texture2D {
public:
 Texture tex;

 public Texture2D(Texture texture) {
 this->tex = texture;
 }

 int getWidth() {
 return this->tex.getWidth();
 }

 int getHeight() {
 return this->tex.getHeight();
 }

 int getTexture() {
 return this->tex.getID();
 }

 void Apply() {
 }
}
} // namespace Texture
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
