package zombie.worldMap.symbols;

import java.util.ArrayList;
import java.util.Objects;
import zombie.Lua.LuaManager.Exposer;
import zombie.ui.UIFont;
import zombie.util.Pool;
import zombie.util.Type;
import zombie.worldMap.UIWorldMap;
import zombie.worldMap.symbols.WorldMapSymbolsV1.WorldMapBaseSymbolV1;
import zombie.worldMap.symbols.WorldMapSymbolsV1.WorldMapTextSymbolV1;
import zombie.worldMap.symbols.WorldMapSymbolsV1.WorldMapTextureSymbolV1;

public class WorldMapSymbolsV1 {
   private static final Pool<WorldMapTextSymbolV1> s_textPool = new Pool(WorldMapTextSymbolV1::new);
   private static final Pool<WorldMapTextureSymbolV1> s_texturePool = new Pool(WorldMapTextureSymbolV1::new);
   private final UIWorldMap m_ui;
   private final WorldMapSymbols m_uiSymbols;
   private final ArrayList<WorldMapBaseSymbolV1> m_symbols = new ArrayList<>();

   public WorldMapSymbolsV1(UIWorldMap var1, WorldMapSymbols var2) {
      Objects.requireNonNull(var1);
      this.m_ui = var1;
      this.m_uiSymbols = var2;
      this.reinit();
   }

   public WorldMapTextSymbolV1 addTranslatedText(String var1, UIFont var2, float var3, float var4) {
      WorldMapTextSymbol var5 = this.m_uiSymbols.addTranslatedText(var1, var2, var3, var4, 1.0F, 1.0F, 1.0F, 1.0F);
      WorldMapTextSymbolV1 var6 = ((WorldMapTextSymbolV1)s_textPool.alloc()).init(this, var5);
      this.m_symbols.add(var6);
      return var6;
   }

   public WorldMapTextSymbolV1 addUntranslatedText(String var1, UIFont var2, float var3, float var4) {
      WorldMapTextSymbol var5 = this.m_uiSymbols.addUntranslatedText(var1, var2, var3, var4, 1.0F, 1.0F, 1.0F, 1.0F);
      WorldMapTextSymbolV1 var6 = ((WorldMapTextSymbolV1)s_textPool.alloc()).init(this, var5);
      this.m_symbols.add(var6);
      return var6;
   }

   public WorldMapTextureSymbolV1 addTexture(String var1, float var2, float var3) {
      WorldMapTextureSymbol var4 = this.m_uiSymbols.addTexture(var1, var2, var3, 1.0F, 1.0F, 1.0F, 1.0F);
      WorldMapTextureSymbolV1 var5 = ((WorldMapTextureSymbolV1)s_texturePool.alloc()).init(this, var4);
      this.m_symbols.add(var5);
      return var5;
   }

   public int hitTest(float var1, float var2) {
      return this.m_uiSymbols.hitTest(this.m_ui, var1, var2);
   }

   public int getSymbolCount() {
      return this.m_symbols.size();
   }

   public WorldMapBaseSymbolV1 getSymbolByIndex(int var1) {
      return this.m_symbols.get(var1);
   }

   public void removeSymbolByIndex(int var1) {
      this.m_uiSymbols.removeSymbolByIndex(var1);
      this.m_symbols.remove(var1).release();
   }

   public void clear() {
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
         if (var3 != null) {
            WorldMapTextSymbolV1 var4 = ((WorldMapTextSymbolV1)s_textPool.alloc()).init(this, var3);
            this.m_symbols.add(var4);
         }

         WorldMapTextureSymbol var7 = (WorldMapTextureSymbol)Type.tryCastTo(var2, WorldMapTextureSymbol.class);
         if (var7 != null) {
            WorldMapTextureSymbolV1 var5 = ((WorldMapTextureSymbolV1)s_texturePool.alloc()).init(this, var7);
            this.m_symbols.add(var5);
         }
      }
   }

   public static void setExposed(Exposer var0) {
      var0.setExposed(WorldMapSymbolsV1.class);
      var0.setExposed(WorldMapTextSymbolV1.class);
      var0.setExposed(WorldMapTextureSymbolV1.class);
   }
}
