#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/util/StringUtils.h"
#include "zombie/worldMap/symbols/WorldMapSymbolsV1/WorldMapBaseSymbolV1.h"

namespace zombie {
namespace worldMap {
namespace symbols {


class WorldMapSymbolsV1 {
public:
    WorldMapTextSymbol m_textSymbol;

   WorldMapSymbolsV1$WorldMapTextSymbolV1 init(WorldMapSymbolsV1 var1, WorldMapTextSymbol var2) {
      super.init(var1, var2);
      this.m_textSymbol = var2;
    return this;
   }

    void setTranslatedText(const std::string& var1) {
      if (!StringUtils.isNullOrWhitespace(var1)) {
         this.m_textSymbol.setTranslatedText(var1);
         this.m_owner.m_uiSymbols.invalidateLayout();
      }
   }

    void setUntranslatedText(const std::string& var1) {
      if (!StringUtils.isNullOrWhitespace(var1)) {
         this.m_textSymbol.setUntranslatedText(var1);
         this.m_owner.m_uiSymbols.invalidateLayout();
      }
   }

    std::string getTranslatedText() {
      return this.m_textSymbol.getTranslatedText();
   }

    std::string getUntranslatedText() {
      return this.m_textSymbol.getUntranslatedText();
   }

    bool isText() {
    return true;
   }
}
} // namespace symbols
} // namespace worldMap
} // namespace zombie
