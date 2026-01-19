package zombie.worldMap.symbols;

public enum WorldMapSymbols$WorldMapSymbolType {
   NONE(-1),
   Text(0),
   Texture(1);

   private final byte m_type;

   private WorldMapSymbols$WorldMapSymbolType(int var3) {
      this.m_type = (byte)var3;
   }

   int index() {
      return this.m_type;
   }
}
