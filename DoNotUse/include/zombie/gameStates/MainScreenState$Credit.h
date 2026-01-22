#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/textures/Texture.h"

namespace zombie {
namespace gameStates {


class MainScreenState {
public:
    int disappearDelay;
    Texture name;
    float nameAlpha;
    float nameAppearDelay;
    float nameTargetAlpha;
    Texture title;
    float titleAlpha;
    float titleTargetAlpha;

   public MainScreenState$Credit(MainScreenState var1, Texture var2, Texture var3) {
      this.this$0 = var1;
      this.disappearDelay = 200;
      this.nameAppearDelay = 40.0F;
      this.titleTargetAlpha = 1.0F;
      this.titleAlpha = 0.0F;
      this.nameTargetAlpha = 0.0F;
      this.nameAlpha = 0.0F;
      this.title = var2;
      this.name = var3;
   }
}
} // namespace gameStates
} // namespace zombie
