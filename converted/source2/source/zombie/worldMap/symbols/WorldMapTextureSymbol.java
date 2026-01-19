package zombie.worldMap.symbols;

import java.io.IOException;
import java.nio.ByteBuffer;
import zombie.GameWindow;
import zombie.core.SpriteRenderer;
import zombie.core.textures.Texture;
import zombie.worldMap.UIWorldMap;
import zombie.worldMap.symbols.MapSymbolDefinitions.MapSymbolDefinition;
import zombie.worldMap.symbols.WorldMapSymbols.WorldMapSymbolType;

public final class WorldMapTextureSymbol extends WorldMapBaseSymbol {
   private String m_symbolID;
   Texture m_texture;

   public WorldMapTextureSymbol(WorldMapSymbols var1) {
      super(var1);
   }

   public void setSymbolID(String var1) {
      this.m_symbolID = var1;
   }

   public String getSymbolID() {
      return this.m_symbolID;
   }

   public void checkTexture() {
      if (this.m_texture == null) {
         MapSymbolDefinition var1 = MapSymbolDefinitions.getInstance().getSymbolById(this.getSymbolID());
         if (var1 == null) {
            this.m_width = 18.0F;
            this.m_height = 18.0F;
         } else {
            this.m_texture = Texture.getSharedTexture(var1.getTexturePath());
            this.m_width = var1.getWidth();
            this.m_height = var1.getHeight();
         }

         if (this.m_texture == null) {
            this.m_texture = Texture.getErrorTexture();
         }
      }
   }

   public WorldMapSymbolType getType() {
      return WorldMapSymbolType.Texture;
   }

   public void layout(UIWorldMap var1, WorldMapSymbolCollisions var2, float var3, float var4) {
      this.checkTexture();
      super.layout(var1, var2, var3, var4);
   }

   public void save(ByteBuffer var1) throws IOException {
      super.save(var1);
      GameWindow.WriteString(var1, this.m_symbolID);
   }

   public void load(ByteBuffer var1, int var2, int var3) throws IOException {
      super.load(var1, var2, var3);
      this.m_symbolID = GameWindow.ReadString(var1);
   }

   public void render(UIWorldMap var1, float var2, float var3) {
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
                  null
               );
         } else {
            var1.DrawTextureColor(this.m_texture, var4, var5, this.m_r, this.m_g, this.m_b, this.m_a);
         }
      }
   }

   public void release() {
      this.m_symbolID = null;
      this.m_texture = null;
   }
}
