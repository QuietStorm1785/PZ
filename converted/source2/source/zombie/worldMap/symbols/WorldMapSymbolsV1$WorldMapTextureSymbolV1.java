package zombie.worldMap.symbols;

import zombie.worldMap.symbols.WorldMapSymbolsV1.WorldMapBaseSymbolV1;

public class WorldMapSymbolsV1$WorldMapTextureSymbolV1 extends WorldMapBaseSymbolV1 {
   WorldMapTextureSymbol m_textureSymbol;

   WorldMapSymbolsV1$WorldMapTextureSymbolV1 init(WorldMapSymbolsV1 var1, WorldMapTextureSymbol var2) {
      super.init(var1, var2);
      this.m_textureSymbol = var2;
      return this;
   }

   public String getSymbolID() {
      return this.m_textureSymbol.getSymbolID();
   }

   public boolean isTexture() {
      return true;
   }
}
