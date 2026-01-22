#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/Core.h"
#include "zombie/core/textures/MultiTextureFBO2.h"
#include "zombie/core/textures/TextureDraw/GenericDrawer.h"
#include "zombie/core/textures/TextureFBO.h"

namespace zombie {
namespace savefile {


class SavefileThumbnail {
public:
    int m_playerIndex;

   SavefileThumbnail$TakeScreenShotDrawer(int var1) {
      this.m_playerIndex = var1;
   }

    void render() {
    Core var1 = Core.getInstance();
    MultiTextureFBO2 var2 = var1.OffscreenBuffer;
      if (var2.Current == nullptr) {
         Core.getInstance().TakeScreenshot(256, 256, 1029);
      } else if (var1.RenderShader == nullptr) {
         Core.getInstance().getOffscreenBuffer().startDrawing(false, false);
         Core.getInstance().TakeScreenshot(256, 256, TextureFBO.getFuncs().GL_COLOR_ATTACHMENT0());
         Core.getInstance().getOffscreenBuffer().endDrawing();
      } else {
         SavefileThumbnail.createWithRenderShader(this.m_playerIndex);
      }
   }
}
} // namespace savefile
} // namespace zombie
