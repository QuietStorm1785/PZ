#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace core {
namespace sprite {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.

class SpriteRenderStateUI : public GenericSpriteRenderState {
public:
 bool bActive;

 public SpriteRenderStateUI(int index) {
 super(index);
 }

 void clear() {
 try {
 this->bActive = true;
 super.clear();
 } finally {
 this->bActive = false;
 }
 }
}
} // namespace sprite
} // namespace core
} // namespace zombie
