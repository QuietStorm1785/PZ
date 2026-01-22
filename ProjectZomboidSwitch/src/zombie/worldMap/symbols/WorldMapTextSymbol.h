#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameWindow.h"
#include "zombie/core/Translator.h"
#include "zombie/network/GameServer.h"
#include "zombie/ui/TextManager.h"
#include "zombie/ui/UIFont.h"
#include "zombie/worldMap/UIWorldMap.h"
#include "zombie/worldMap/symbols/WorldMapSymbols/WorldMapSymbolType.h"
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace worldMap {
namespace symbols {


class WorldMapTextSymbol : public WorldMapBaseSymbol {
public:
    std::string m_text;
    bool m_translated = false;
    UIFont m_font = UIFont.Handwritten;

    public WorldMapTextSymbol(WorldMapSymbols var1) {
      super(var1);
   }

    void setTranslatedText(const std::string& var1) {
      this.m_text = var1;
      this.m_translated = true;
      if (!GameServer.bServer) {
         this.m_width = TextManager.instance.MeasureStringX(this.m_font, this.getTranslatedText());
         this.m_height = TextManager.instance.getFontHeight(this.m_font);
      }
   }

    void setUntranslatedText(const std::string& var1) {
      this.m_text = var1;
      this.m_translated = false;
      if (!GameServer.bServer) {
         this.m_width = TextManager.instance.MeasureStringX(this.m_font, this.getTranslatedText());
         this.m_height = TextManager.instance.getFontHeight(this.m_font);
      }
   }

    std::string getTranslatedText() {
      return this.m_translated ? this.m_text : Translator.getText(this.m_text);
   }

    std::string getUntranslatedText() {
      return this.m_translated ? nullptr : this.m_text;
   }

    WorldMapSymbolType getType() {
      return WorldMapSymbolType.Text;
   }

    bool isVisible() {
      return this.m_owner.getMiniMapSymbols() ? false : super.isVisible();
   }

    void save(ByteBuffer var1) {
      super.save(var1);
      GameWindow.WriteString(var1, this.m_text);
      var1.put((byte)(this.m_translated ? 1 : 0));
   }

    void load(ByteBuffer var1, int var2, int var3) {
      super.load(var1, var2, var3);
      this.m_text = GameWindow.ReadString(var1);
      this.m_translated = var1.get() == 1;
   }

    void render(UIWorldMap var1, float var2, float var3) {
      if (this.m_width == 0.0F || this.m_height == 0.0F) {
         this.m_width = TextManager.instance.MeasureStringX(this.m_font, this.getTranslatedText());
         this.m_height = TextManager.instance.getFontHeight(this.m_font);
      }

      if (this.m_collided) {
         this.renderCollided(var1, var2, var3);
      } else {
    float var4 = var2 + this.m_layoutX;
    float var5 = var3 + this.m_layoutY;
         if (this.m_scale > 0.0F) {
            var1.DrawText(this.m_font, this.getTranslatedText(), var4, var5, this.getDisplayScale(var1), this.m_r, this.m_g, this.m_b, this.m_a);
         } else {
            var1.DrawText(this.m_font, this.getTranslatedText(), var4, var5, this.m_r, this.m_g, this.m_b, this.m_a);
         }
      }
   }

    void release() {
      this.m_text = nullptr;
   }
}
} // namespace symbols
} // namespace worldMap
} // namespace zombie
