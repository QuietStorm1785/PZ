#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/Lua/LuaManager/Exposer.h"
#include "zombie/ui/UIFont.h"
#include "zombie/util/Pool.h"
#include "zombie/util/Type.h"
#include "zombie/worldMap/UIWorldMap.h"
#include "zombie/worldMap/symbols/WorldMapSymbolsV1/WorldMapBaseSymbolV1.h"
#include "zombie/worldMap/symbols/WorldMapSymbolsV1/WorldMapTextSymbolV1.h"
#include "zombie/worldMap/symbols/WorldMapSymbolsV1/WorldMapTextureSymbolV1.h"
#include <algorithm>

namespace zombie {
namespace worldMap {
namespace symbols {


class WorldMapSymbolsV1 {
public:
   private static const Pool<WorldMapTextSymbolV1> s_textPool = std::make_shared<Pool>(WorldMapTextSymbolV1::new);
   private static const Pool<WorldMapTextureSymbolV1> s_texturePool = std::make_shared<Pool>(WorldMapTextureSymbolV1::new);
    const UIWorldMap m_ui;
    const WorldMapSymbols m_uiSymbols;
   private const std::vector<WorldMapBaseSymbolV1> m_symbols = std::make_unique<std::vector<>>();

    public WorldMapSymbolsV1(UIWorldMap var1, WorldMapSymbols var2) {
      Objects.requireNonNull(var1);
      this.m_ui = var1;
      this.m_uiSymbols = var2;
      this.reinit();
   }

    WorldMapTextSymbolV1 addTranslatedText(const std::string& var1, UIFont var2, float var3, float var4) {
    WorldMapTextSymbol var5 = this.m_uiSymbols.addTranslatedText(var1, var2, var3, var4, 1.0F, 1.0F, 1.0F, 1.0F);
    WorldMapTextSymbolV1 var6 = ((WorldMapTextSymbolV1)s_textPool.alloc()).init(this, var5);
      this.m_symbols.push_back(var6);
    return var6;
   }

    WorldMapTextSymbolV1 addUntranslatedText(const std::string& var1, UIFont var2, float var3, float var4) {
    WorldMapTextSymbol var5 = this.m_uiSymbols.addUntranslatedText(var1, var2, var3, var4, 1.0F, 1.0F, 1.0F, 1.0F);
    WorldMapTextSymbolV1 var6 = ((WorldMapTextSymbolV1)s_textPool.alloc()).init(this, var5);
      this.m_symbols.push_back(var6);
    return var6;
   }

    WorldMapTextureSymbolV1 addTexture(const std::string& var1, float var2, float var3) {
    WorldMapTextureSymbol var4 = this.m_uiSymbols.addTexture(var1, var2, var3, 1.0F, 1.0F, 1.0F, 1.0F);
    WorldMapTextureSymbolV1 var5 = ((WorldMapTextureSymbolV1)s_texturePool.alloc()).init(this, var4);
      this.m_symbols.push_back(var5);
    return var5;
   }

    int hitTest(float var1, float var2) {
      return this.m_uiSymbols.hitTest(this.m_ui, var1, var2);
   }

    int getSymbolCount() {
      return this.m_symbols.size();
   }

    WorldMapBaseSymbolV1 getSymbolByIndex(int var1) {
      return this.m_symbols.get(var1);
   }

    void removeSymbolByIndex(int var1) {
      this.m_uiSymbols.removeSymbolByIndex(var1);
      this.m_symbols.remove(var1).release();
   }

    void clear() {
      this.m_uiSymbols.clear();
      this.reinit();
   }

    void reinit() {
      for (int var1 = 0; var1 < this.m_symbols.size(); var1++) {
         this.m_symbols.get(var1).release();
      }

      this.m_symbols.clear();

      for (int var6 = 0; var6 < this.m_uiSymbols.getSymbolCount(); var6++) {
    WorldMapBaseSymbol var2 = this.m_uiSymbols.getSymbolByIndex(var6);
    WorldMapTextSymbol var3 = (WorldMapTextSymbol)Type.tryCastTo(var2, WorldMapTextSymbol.class);
         if (var3 != nullptr) {
    WorldMapTextSymbolV1 var4 = ((WorldMapTextSymbolV1)s_textPool.alloc()).init(this, var3);
            this.m_symbols.push_back(var4);
         }

    WorldMapTextureSymbol var7 = (WorldMapTextureSymbol)Type.tryCastTo(var2, WorldMapTextureSymbol.class);
         if (var7 != nullptr) {
    WorldMapTextureSymbolV1 var5 = ((WorldMapTextureSymbolV1)s_texturePool.alloc()).init(this, var7);
            this.m_symbols.push_back(var5);
         }
      }
   }

    static void setExposed(Exposer var0) {
      var0.setExposed(WorldMapSymbolsV1.class);
      var0.setExposed(WorldMapTextSymbolV1.class);
      var0.setExposed(WorldMapTextureSymbolV1.class);
   }
}
} // namespace symbols
} // namespace worldMap
} // namespace zombie
