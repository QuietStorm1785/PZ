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

class SpriteRenderStateUI : public GenericSpriteRenderState {
public:
    bool bActive;

    public SpriteRenderStateUI(int var1) {
      super(var1);
   }

    void clear() {
      try {
         this.bActive = true;
         super.clear();
      } finally {
         this.bActive = false;
      }
   }
}
} // namespace sprite
} // namespace core
} // namespace zombie
