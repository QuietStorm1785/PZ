#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <GL/glew.h>
#include "org/lwjgl/util/glu/GLU.h"
#include "zombie/IndieGL.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/Core.h"
#include "zombie/core/SpriteRenderer.h"
#include "zombie/core/opengl/RenderSettings.h"
#include "zombie/core/textures/MultiTextureFBO2.h"
#include "zombie/core/textures/Texture.h"
#include "zombie/core/textures/TextureFBO.h"
#include "zombie/interfaces/ITexture.h"
#include "zombie/iso/IsoCamera.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/sprite/IsoSprite.h"
#include "zombie/savefile/SavefileThumbnail/FixCameraDrawer.h"
#include "zombie/savefile/SavefileThumbnail/TakeScreenShotDrawer.h"
#include "zombie/ui/UIManager.h"

namespace zombie {
namespace savefile {


class SavefileThumbnail {
public:
    static const int WIDTH = 256;
    static const int HEIGHT = 256;

    static void create() {
    int var0 = -1;

      for (int var1 = 0; var1 < IsoPlayer.numPlayers; var1++) {
         if (IsoPlayer.players[var1] != nullptr) {
            var0 = var1;
            break;
         }
      }

      if (var0 != -1) {
         create(var0);
      }
   }

    static void create(int var0) {
    Core var1 = Core.getInstance();
    MultiTextureFBO2 var2 = var1.OffscreenBuffer;
    float var3 = var2.zoom[var0];
    float var4 = var2.targetZoom[var0];
      setZoom(var0, 1.0F, 1.0F);
      IsoCamera.cameras[var0].center();
      renderWorld(var0, true, true);
      SpriteRenderer.instance.drawGeneric(std::make_shared<TakeScreenShotDrawer>(var0));
      setZoom(var0, var3, var4);
      IsoCamera.cameras[var0].center();

      for (int var5 = 0; var5 < IsoPlayer.numPlayers; var5++) {
    IsoPlayer var6 = IsoPlayer.players[var5];
         if (var6 != nullptr) {
            renderWorld(var5, false, var5 == var0);
         }
      }

      var1.RenderOffScreenBuffer();
      if (var1.StartFrameUI()) {
         UIManager.render();
      }

      var1.EndFrameUI();
   }

    static void renderWorld(int var0, bool var1, bool var2) {
      IsoPlayer.setInstance(IsoPlayer.players[var0]);
      IsoCamera.CamCharacter = IsoPlayer.players[var0];
      IsoSprite.globalOffsetX = -1.0F;
      Core.getInstance().StartFrame(var0, var1);
      if (var2) {
         SpriteRenderer.instance.drawGeneric(std::make_shared<FixCameraDrawer>(var0));
      }

      IsoCamera.frameState.set(var0);
      IndieGL.glDisable(2929);
      IsoWorld.instance.render();
      RenderSettings.getInstance().legacyPostRender(var0);
      Core.getInstance().EndFrame(var0);
   }

    static void setZoom(int var0, float var1, float var2) {
      Core.getInstance().OffscreenBuffer.zoom[var0] = var1;
      Core.getInstance().OffscreenBuffer.targetZoom[var0] = var2;
      IsoCamera.cameras[var0].zoom = var1;
      IsoCamera.cameras[var0].OffscreenWidth = IsoCamera.getOffscreenWidth(var0);
      IsoCamera.cameras[var0].OffscreenHeight = IsoCamera.getOffscreenHeight(var0);
   }

    static void createWithRenderShader(int var0) {
    short var1 = 256;
    short var2 = 256;
    Texture var3 = std::make_shared<Texture>(var1, var2, 16);
    TextureFBO var4 = std::make_shared<TextureFBO>(var3, false);
      GL11.glPushAttrib(1048575);

      try {
         var4.startDrawing(true, false);
         GL11.glViewport(0, 0, var1, var2);
         GL11.glMatrixMode(5889);
         GL11.glLoadIdentity();
         GLU.gluOrtho2D(0.0F, var1, var2, 0.0F);
         GL11.glMatrixMode(5888);
         GL11.glLoadIdentity();
    Core var5 = Core.getInstance();
         var5.RenderShader.Start();
         GL11.glDisable(3089);
         GL11.glDisable(2960);
         GL11.glDisable(3042);
         GL11.glDisable(3008);
         GL11.glDisable(2929);
         GL11.glDisable(2884);

         for (int var6 = 8; var6 > 1; var6--) {
            GL13.glActiveTexture(33984 + var6 - 1);
            GL11.glDisable(3553);
         }

         GL13.glActiveTexture(33984);
         GL11.glEnable(3553);
    ITexture var18 = var5.getOffscreenBuffer().getTexture();
         var18.bind();
    int var7 = IsoCamera.getScreenLeft(var0) + IsoCamera.getScreenWidth(var0) / 2 - var1 / 2;
    int var8 = IsoCamera.getScreenTop(var0) + IsoCamera.getScreenHeight(var0) / 2 - var2 / 2;
    int var9 = var5.getOffscreenBuffer().getTexture().getWidthHW();
    int var10 = var5.getOffscreenBuffer().getTexture().getHeightHW();
    float var11 = (float)var7 / var9;
    float var12 = (float)(var7 + var1) / var9;
    float var13 = (float)var8 / var10;
    float var14 = (float)(var8 + var2) / var10;
         GL11.glBegin(7);
         GL11.glColor4f(1.0F, 1.0F, 1.0F, 1.0F);
         GL11.glTexCoord2f(var11, var14);
         GL11.glVertex2d(0.0, 0.0);
         GL11.glTexCoord2f(var11, var13);
         GL11.glVertex2d(0.0, var2);
         GL11.glTexCoord2f(var12, var13);
         GL11.glVertex2d(var1, var2);
         GL11.glTexCoord2f(var12, var14);
         GL11.glVertex2d(var1, 0.0);
         GL11.glEnd();
         var5.RenderShader.End();
         var5.TakeScreenshot(0, 0, var1, var2, TextureFBO.getFuncs().GL_COLOR_ATTACHMENT0());
         var4.endDrawing();
      } finally {
         var4.destroy();
         GL11.glPopAttrib();
      }
   }
}
} // namespace savefile
} // namespace zombie
