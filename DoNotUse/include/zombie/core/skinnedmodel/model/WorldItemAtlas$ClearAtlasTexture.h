#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/lwjgl/opengl/GL11.h"
#include "org/lwjgl/util/glu/GLU.h"
#include "zombie/core/skinnedmodel/model/WorldItemAtlas/Atlas.h"
#include "zombie/core/textures/TextureDraw/GenericDrawer.h"
#include "zombie/core/textures/TextureFBO.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace model {


class WorldItemAtlas {
public:
    Atlas m_atlas;

   WorldItemAtlas$ClearAtlasTexture(Atlas var1) {
      this.m_atlas = var1;
   }

    void render() {
    TextureFBO var1 = WorldItemAtlas.instance.fbo;
      if (var1 != nullptr && this.m_atlas.tex != nullptr) {
         if (this.m_atlas.clear) {
            if (var1.getTexture() != this.m_atlas.tex) {
               var1.setTexture(this.m_atlas.tex);
            }

            var1.startDrawing(false, false);
            GL11.glPushAttrib(2048);
            GL11.glViewport(0, 0, var1.getWidth(), var1.getHeight());
            GL11.glMatrixMode(5889);
            GL11.glPushMatrix();
            GL11.glLoadIdentity();
    int var2 = this.m_atlas.tex.getWidth();
    int var3 = this.m_atlas.tex.getHeight();
            GLU.gluOrtho2D(0.0F, var2, var3, 0.0F);
            GL11.glMatrixMode(5888);
            GL11.glPushMatrix();
            GL11.glLoadIdentity();
            GL11.glDisable(3089);
            GL11.glClearColor(0.0F, 0.0F, 0.0F, 0.0F);
            GL11.glClear(16640);
            GL11.glClearColor(0.0F, 0.0F, 0.0F, 1.0F);
            var1.endDrawing();
            GL11.glEnable(3089);
            GL11.glMatrixMode(5889);
            GL11.glPopMatrix();
            GL11.glMatrixMode(5888);
            GL11.glPopMatrix();
            GL11.glPopAttrib();
            this.m_atlas.clear = false;
         }
      }
   }
}
} // namespace model
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
