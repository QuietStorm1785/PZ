#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/SpriteRenderer.h"
#include "zombie/core/sprite/SpriteRenderState.h"
#include "zombie/core/textures/TextureDraw/GenericDrawer.h"
#include "zombie/iso/IsoCamera.h"
#include "zombie/iso/PlayerCamera.h"

namespace zombie {
namespace savefile {


class SavefileThumbnail {
public:
    int m_playerIndex;
    float m_zoom;
    int m_offscreenWidth;
    int m_offscreenHeight;

   SavefileThumbnail$FixCameraDrawer(int var1) {
    PlayerCamera var2 = IsoCamera.cameras[var1];
      this.m_playerIndex = var1;
      this.m_zoom = var2.zoom;
      this.m_offscreenWidth = var2.OffscreenWidth;
      this.m_offscreenHeight = var2.OffscreenHeight;
   }

    void render() {
    SpriteRenderState var1 = SpriteRenderer.instance.getRenderingState();
      var1.playerCamera[this.m_playerIndex].zoom = this.m_zoom;
      var1.playerCamera[this.m_playerIndex].OffscreenWidth = this.m_offscreenWidth;
      var1.playerCamera[this.m_playerIndex].OffscreenHeight = this.m_offscreenHeight;
      var1.zoomLevel[this.m_playerIndex] = this.m_zoom;
   }
}
} // namespace savefile
} // namespace zombie
