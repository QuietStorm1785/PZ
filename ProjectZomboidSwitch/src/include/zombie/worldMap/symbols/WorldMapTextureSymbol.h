#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameWindow.h"
#include "zombie/core/SpriteRenderer.h"
#include "zombie/core/textures/Texture.h"
#include "zombie/worldMap/UIWorldMap.h"
#include "zombie/worldMap/symbols/MapSymbolDefinitions/MapSymbolDefinition.h"
#include "zombie/worldMap/symbols/WorldMapSymbols/WorldMapSymbolType.h"
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace worldMap {
namespace symbols {


class WorldMapTextureSymbol : public WorldMapBaseSymbol {
public:
    std::string m_symbolID;
    Texture m_texture;

    public WorldMapTextureSymbol(WorldMapSymbols var1) {
      super(var1);
   }

    void setSymbolID(const std::string& var1) {
      this.m_symbolID = var1;
   }

    std::string getSymbolID() {
      return this.m_symbolID;
   }

    void checkTexture() {
      if (this.m_texture == nullptr) {
    MapSymbolDefinition var1 = MapSymbolDefinitions.getInstance().getSymbolById(this.getSymbolID());
         if (var1 == nullptr) {
            this.m_width = 18.0F;
            this.m_height = 18.0F;
         } else {
            this.m_texture = Texture.getSharedTexture(var1.getTexturePath());
            this.m_width = var1.getWidth();
            this.m_height = var1.getHeight();
         }

         if (this.m_texture == nullptr) {
            this.m_texture = Texture.getErrorTexture();
         }
      }
   }

    WorldMapSymbolType getType() {
      return WorldMapSymbolType.Texture;
   }

    void layout(UIWorldMap var1, WorldMapSymbolCollisions var2, float var3, float var4) {
      this.checkTexture();
      super.layout(var1, var2, var3, var4);
   }

    void save(ByteBuffer var1) {
      super.save(var1);
      GameWindow.WriteString(var1, this.m_symbolID);
   }

    void load(ByteBuffer var1, int var2, int var3) {
      super.load(var1, var2, var3);
      this.m_symbolID = GameWindow.ReadString(var1);
   }

    void render(UIWorldMap var1, float var2, float var3) {
      if (this.m_collided) {
         this.renderCollided(var1, var2, var3);
      } else {
         this.checkTexture();
    float var4 = var2 + this.m_layoutX;
    float var5 = var3 + this.m_layoutY;
         if (this.m_scale > 0.0F) {
    float var6 = this.getDisplayScale(var1);
            SpriteRenderer.instance
               .m_states
               .getPopulatingActiveState()
               .render(
                  this.m_texture,
                  var1.getAbsoluteX().intValue() + var4,
                  var1.getAbsoluteY().intValue() + var5,
                  this.m_texture.getWidth() * var6,
                  this.m_texture.getHeight() * var6,
                  this.m_r,
                  this.m_g,
                  this.m_b,
                  this.m_a,
                  nullptr
               );
         } else {
            var1.DrawTextureColor(this.m_texture, var4, var5, this.m_r, this.m_g, this.m_b, this.m_a);
         }
      }
   }

    void release() {
      this.m_symbolID = nullptr;
      this.m_texture = nullptr;
   }
}
} // namespace symbols
} // namespace worldMap
} // namespace zombie
