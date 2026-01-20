#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameTime.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/Core.h"
#include "zombie/core/SpriteRenderer.h"
#include "zombie/core/opengl/RenderThread.h"
#include "zombie/core/textures/Texture.h"
#include "zombie/input/Mouse.h"
#include "zombie/iso/IsoCamera.h"
#include "zombie/iso/sprite/IsoCursor/IsoCursorShader.h"

namespace zombie {
namespace iso {
namespace sprite {


class IsoCursor {
public:
    static IsoCursor instance = nullptr;
    IsoCursorShader m_shader = nullptr;

    static IsoCursor getInstance() {
      if (instance == nullptr) {
         instance = std::make_unique<IsoCursor>();
      }

    return instance;
   }

    private IsoCursor() {
      RenderThread.invokeOnRenderContext(this::createShader);
      if (this.m_shader != nullptr) {
         this.m_shader.m_textureCursor = Texture.getSharedTexture("media/ui/isocursor.png");
      }
   }

    void createShader() {
      this.m_shader = std::make_unique<IsoCursorShader>();
   }

    void render(int var1) {
      if (Core.getInstance().getOffscreenBuffer() != nullptr) {
    IsoPlayer var2 = IsoPlayer.players[var1];
         if (var2 != nullptr && !var2.isDead() && var2.isAiming() && var2.PlayerIndex == 0 && var2.JoypadBind == -1) {
            if (!GameTime.isGamePaused()) {
               if (this.m_shader != nullptr && this.m_shader.isCompiled()) {
    float var3 = 1.0F / Core.getInstance().getZoom(var1);
    int var4 = (int)(this.m_shader.m_textureCursor.getWidth() * Core.TileScale / 2.0F * var3);
    int var5 = (int)(this.m_shader.m_textureCursor.getHeight() * Core.TileScale / 2.0F * var3);
                  this.m_shader.m_screenX = Mouse.getXA() - var4 / 2;
                  this.m_shader.m_screenY = Mouse.getYA() - var5 / 2;
                  this.m_shader.width = var4;
                  this.m_shader.height = var5;
    int var6 = IsoCamera.getScreenLeft(var1);
    int var7 = IsoCamera.getScreenTop(var1);
    int var8 = IsoCamera.getScreenWidth(var1);
    int var9 = IsoCamera.getScreenHeight(var1);
                  SpriteRenderer.instance.StartShader(this.m_shader.getID(), var1);
                  SpriteRenderer.instance
                     .renderClamped(
                        this.m_shader.m_textureCursor,
                        this.m_shader.m_screenX,
                        this.m_shader.m_screenY,
                        var4,
                        var5,
                        var6,
                        var7,
                        var8,
                        var9,
                        1.0F,
                        1.0F,
                        1.0F,
                        1.0F,
                        this.m_shader
                     );
                  SpriteRenderer.instance.EndShader();
               }
            }
         }
      }
   }
}
} // namespace sprite
} // namespace iso
} // namespace zombie
