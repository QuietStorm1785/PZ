#pragma once
#include "org/lwjgl/opengl/GL11.h"
#include "org/lwjgl/opengl/GL13.h"
#include "org/lwjgl/util/glu/GLU.h"
#include "zombie/IndieGL.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/Core.h"
#include "zombie/core/SpriteRenderer.h"
#include "zombie/core/opengl/RenderSettings.h"
#include "zombie/core/sprite/SpriteRenderState.h"
#include "zombie/core/textures/MultiTextureFBO2.h"
#include "zombie/core/textures/Texture.h"
#include "zombie/core/textures/TextureDraw.h"
#include "zombie/core/textures/TextureFBO.h"
#include "zombie/interfaces/ITexture.h"
#include "zombie/iso/IsoCamera.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/PlayerCamera.h"
#include "zombie/iso/sprite/IsoSprite.h"
#include "zombie/ui/UIManager.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace savefile {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class SavefileThumbnail {
public:
  static const int WIDTH = 256;
  static const int HEIGHT = 256;

  static void create() {
    int int0 = -1;

    for (int int1 = 0; int1 < IsoPlayer.numPlayers; int1++) {
      if (IsoPlayer.players[int1] != nullptr) {
        int0 = int1;
        break;
      }
    }

    if (int0 != -1) {
      create(int0);
    }
  }

  static void create(int int0) {
    Core core = Core.getInstance();
    MultiTextureFBO2 multiTextureFBO2 = core.OffscreenBuffer;
    float float0 = multiTextureFBO2.zoom[int0];
    float float1 = multiTextureFBO2.targetZoom[int0];
    setZoom(int0, 1.0F, 1.0F);
    IsoCamera.cameras[int0].center();
    renderWorld(int0, true, true);
    SpriteRenderer.instance.drawGeneric(
        new SavefileThumbnail.TakeScreenShotDrawer(int0));
    setZoom(int0, float0, float1);
    IsoCamera.cameras[int0].center();

    for (int int1 = 0; int1 < IsoPlayer.numPlayers; int1++) {
      IsoPlayer player = IsoPlayer.players[int1];
      if (player != nullptr) {
        renderWorld(int1, false, int1 == int0);
      }
    }

    core.RenderOffScreenBuffer();
    if (core.StartFrameUI()) {
      UIManager.render();
    }

    core.EndFrameUI();
  }

  static void renderWorld(int int0, bool boolean0, bool boolean1) {
    IsoPlayer.setInstance(IsoPlayer.players[int0]);
    IsoCamera.CamCharacter = IsoPlayer.players[int0];
    IsoSprite.globalOffsetX = -1.0F;
    Core.getInstance().StartFrame(int0, boolean0);
    if (boolean1) {
      SpriteRenderer.instance.drawGeneric(
          new SavefileThumbnail.FixCameraDrawer(int0));
    }

    IsoCamera.frameState.set(int0);
    IndieGL.glDisable(2929);
    IsoWorld.instance.render();
    RenderSettings.getInstance().legacyPostRender(int0);
    Core.getInstance().EndFrame(int0);
  }

  static void setZoom(int int0, float float0, float float1) {
    Core.getInstance().OffscreenBuffer.zoom[int0] = float0;
    Core.getInstance().OffscreenBuffer.targetZoom[int0] = float1;
    IsoCamera.cameras[int0].zoom = float0;
    IsoCamera.cameras[int0].OffscreenWidth = IsoCamera.getOffscreenWidth(int0);
    IsoCamera.cameras[int0].OffscreenHeight =
        IsoCamera.getOffscreenHeight(int0);
  }

  static void createWithRenderShader(int int2) {
    short short0 = 256;
    short short1 = 256;
    Texture texture = new Texture(short0, short1, 16);
    TextureFBO textureFBO = new TextureFBO(texture, false);
    GL11.glPushAttrib(1048575);

    try {
      textureFBO.startDrawing(true, false);
      GL11.glViewport(0, 0, short0, short1);
      GL11.glMatrixMode(5889);
      GL11.glLoadIdentity();
      GLU.gluOrtho2D(0.0F, short0, short1, 0.0F);
      GL11.glMatrixMode(5888);
      GL11.glLoadIdentity();
      Core core = Core.getInstance();
      core.RenderShader.Start();
      GL11.glDisable(3089);
      GL11.glDisable(2960);
      GL11.glDisable(3042);
      GL11.glDisable(3008);
      GL11.glDisable(2929);
      GL11.glDisable(2884);

      for (int int0 = 8; int0 > 1; int0--) {
        GL13.glActiveTexture(33984 + int0 - 1);
        GL11.glDisable(3553);
      }

      GL13.glActiveTexture(33984);
      GL11.glEnable(3553);
      ITexture iTexture = core.getOffscreenBuffer().getTexture();
      iTexture.bind();
      int int1 = IsoCamera.getScreenLeft(int2) +
                 IsoCamera.getScreenWidth(int2) / 2 - short0 / 2;
      int int3 = IsoCamera.getScreenTop(int2) +
                 IsoCamera.getScreenHeight(int2) / 2 - short1 / 2;
      int int4 = core.getOffscreenBuffer().getTexture().getWidthHW();
      int int5 = core.getOffscreenBuffer().getTexture().getHeightHW();
      float float0 = (float)int1 / int4;
      float float1 = (float)(int1 + short0) / int4;
      float float2 = (float)int3 / int5;
      float float3 = (float)(int3 + short1) / int5;
      GL11.glBegin(7);
      GL11.glColor4f(1.0F, 1.0F, 1.0F, 1.0F);
      GL11.glTexCoord2f(float0, float3);
      GL11.glVertex2d(0.0, 0.0);
      GL11.glTexCoord2f(float0, float2);
      GL11.glVertex2d(0.0, short1);
      GL11.glTexCoord2f(float1, float2);
      GL11.glVertex2d(short0, short1);
      GL11.glTexCoord2f(float1, float3);
      GL11.glVertex2d(short0, 0.0);
      GL11.glEnd();
      core.RenderShader.End();
      core.TakeScreenshot(0, 0, short0, short1,
                          TextureFBO.getFuncs().GL_COLOR_ATTACHMENT0());
      textureFBO.endDrawing();
    } finally {
      textureFBO.destroy();
      GL11.glPopAttrib();
    }
  }

private
  static final class FixCameraDrawer extends TextureDraw.GenericDrawer {
    int m_playerIndex;
    float m_zoom;
    int m_offscreenWidth;
    int m_offscreenHeight;

    FixCameraDrawer(int int0) {
      PlayerCamera playerCamera = IsoCamera.cameras[int0];
      this.m_playerIndex = int0;
      this.m_zoom = playerCamera.zoom;
      this.m_offscreenWidth = playerCamera.OffscreenWidth;
      this.m_offscreenHeight = playerCamera.OffscreenHeight;
    }

    void render() {
      SpriteRenderState spriteRenderState =
          SpriteRenderer.instance.getRenderingState();
      spriteRenderState.playerCamera[this.m_playerIndex].zoom = this.m_zoom;
      spriteRenderState.playerCamera[this.m_playerIndex].OffscreenWidth =
          this.m_offscreenWidth;
      spriteRenderState.playerCamera[this.m_playerIndex].OffscreenHeight =
          this.m_offscreenHeight;
      spriteRenderState.zoomLevel[this.m_playerIndex] = this.m_zoom;
    }
  }

private
  static final class TakeScreenShotDrawer extends TextureDraw.GenericDrawer {
    int m_playerIndex;

    TakeScreenShotDrawer(int int0) { this.m_playerIndex = int0; }

    void render() {
      Core core = Core.getInstance();
      MultiTextureFBO2 multiTextureFBO2 = core.OffscreenBuffer;
      if (multiTextureFBO2.Current == nullptr) {
        Core.getInstance().TakeScreenshot(256, 256, 1029);
      } else if (core.RenderShader == nullptr) {
        Core.getInstance().getOffscreenBuffer().startDrawing(false, false);
        Core.getInstance().TakeScreenshot(
            256, 256, TextureFBO.getFuncs().GL_COLOR_ATTACHMENT0());
        Core.getInstance().getOffscreenBuffer().endDrawing();
      } else {
        SavefileThumbnail.createWithRenderShader(this.m_playerIndex);
      }
    }
  }
}
} // namespace savefile
} // namespace zombie
