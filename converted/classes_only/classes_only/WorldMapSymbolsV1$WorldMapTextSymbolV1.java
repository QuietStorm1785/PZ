package zombie.worldMap.symbols;

import zombie.util.StringUtils;
import zombie.worldMap.symbols.WorldMapSymbolsV1.WorldMapBaseSymbolV1;

public class WorldMapSymbolsV1$WorldMapTextSymbolV1 extends WorldMapBaseSymbolV1 {
   WorldMapTextSymbol m_textSymbol;

   WorldMapSymbolsV1$WorldMapTextSymbolV1 init(WorldMapSymbolsV1 var1, WorldMapTextSymbol var2) {
      super.init(var1, var2);
      this.m_textSymbol = var2;
      return this;
   }

   public void setTranslatedText(String var1) {
      if (!StringUtils.isNullOrWhitespace(var1)) {
         this.m_textSymbol.setTranslatedText(var1);
         this.m_owner.m_uiSymbols.invalidateLayout();
      }
   }

   public void setUntranslatedText(String var1) {
      if (!StringUtils.isNullOrWhitespace(var1)) {
         this.m_textSymbol.setUntranslatedText(var1);
         this.m_owner.m_uiSymbols.invalidateLayout();
      }
   }

   public String getTranslatedText() {
      return this.m_textSymbol.getTranslatedText();
   }

   public String getUntranslatedText() {
      return this.m_textSymbol.getUntranslatedText();
   }

   public boolean isText() {
      return true;
   }
}
