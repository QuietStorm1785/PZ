package zombie.worldMap.symbols;

import java.io.IOException;
import java.nio.ByteBuffer;
import zombie.core.math.PZMath;
import zombie.worldMap.UIWorldMap;
import zombie.worldMap.symbols.WorldMapSymbols.WorldMapSymbolType;

public abstract class WorldMapBaseSymbol {
   public static float DEFAULT_SCALE = 0.666F;
   WorldMapSymbols m_owner;
   float m_x;
   float m_y;
   float m_width;
   float m_height;
   float m_anchorX = 0.0F;
   float m_anchorY = 0.0F;
   float m_scale = DEFAULT_SCALE;
   float m_r;
   float m_g;
   float m_b;
   float m_a;
   boolean m_collide = false;
   boolean m_collided = false;
   float m_layoutX;
   float m_layoutY;
   boolean m_visible = true;

   public WorldMapBaseSymbol(WorldMapSymbols var1) {
      this.m_owner = var1;
   }

   public abstract WorldMapSymbolType getType();

   public void setAnchor(float var1, float var2) {
      this.m_anchorX = PZMath.clamp(var1, 0.0F, 1.0F);
      this.m_anchorY = PZMath.clamp(var2, 0.0F, 1.0F);
   }

   public void setPosition(float var1, float var2) {
      this.m_x = var1;
      this.m_y = var2;
   }

   public void setCollide(boolean var1) {
      this.m_collide = var1;
   }

   public void setRGBA(float var1, float var2, float var3, float var4) {
      this.m_r = PZMath.clamp_01(var1);
      this.m_g = PZMath.clamp_01(var2);
      this.m_b = PZMath.clamp_01(var3);
      this.m_a = PZMath.clamp_01(var4);
   }

   public void setScale(float var1) {
      this.m_scale = var1;
   }

   public float getDisplayScale(UIWorldMap var1) {
      if (this.m_scale <= 0.0F) {
         return this.m_scale;
      } else {
         return this.m_owner.getMiniMapSymbols() ? PZMath.min(this.m_owner.getLayoutWorldScale(), 1.0F) : this.m_owner.getLayoutWorldScale() * this.m_scale;
      }
   }

   public void layout(UIWorldMap var1, WorldMapSymbolCollisions var2, float var3, float var4) {
      float var5 = var1.getAPI().worldToUIX(this.m_x, this.m_y) - var3;
      float var6 = var1.getAPI().worldToUIY(this.m_x, this.m_y) - var4;
      this.m_layoutX = var5 - this.widthScaled(var1) * this.m_anchorX;
      this.m_layoutY = var6 - this.heightScaled(var1) * this.m_anchorY;
      this.m_collided = var2.addBox(this.m_layoutX, this.m_layoutY, this.widthScaled(var1), this.heightScaled(var1), this.m_collide);
      if (this.m_collided) {
      }
   }

   public float widthScaled(UIWorldMap var1) {
      return this.m_scale <= 0.0F ? this.m_width : this.m_width * this.getDisplayScale(var1);
   }

   public float heightScaled(UIWorldMap var1) {
      return this.m_scale <= 0.0F ? this.m_height : this.m_height * this.getDisplayScale(var1);
   }

   public void setVisible(boolean var1) {
      this.m_visible = var1;
   }

   public boolean isVisible() {
      return this.m_visible;
   }

   public void save(ByteBuffer var1) throws IOException {
      var1.putFloat(this.m_x);
      var1.putFloat(this.m_y);
      var1.putFloat(this.m_anchorX);
      var1.putFloat(this.m_anchorY);
      var1.putFloat(this.m_scale);
      var1.put((byte)(this.m_r * 255.0F));
      var1.put((byte)(this.m_g * 255.0F));
      var1.put((byte)(this.m_b * 255.0F));
      var1.put((byte)(this.m_a * 255.0F));
      var1.put((byte)(this.m_collide ? 1 : 0));
   }

   public void load(ByteBuffer var1, int var2, int var3) throws IOException {
      this.m_x = var1.getFloat();
      this.m_y = var1.getFloat();
      this.m_anchorX = var1.getFloat();
      this.m_anchorY = var1.getFloat();
      this.m_scale = var1.getFloat();
      this.m_r = (var1.get() & 255) / 255.0F;
      this.m_g = (var1.get() & 255) / 255.0F;
      this.m_b = (var1.get() & 255) / 255.0F;
      this.m_a = (var1.get() & 255) / 255.0F;
      this.m_collide = var1.get() == 1;
   }

   public abstract void render(UIWorldMap var1, float var2, float var3);

   void renderCollided(UIWorldMap var1, float var2, float var3) {
      float var4 = var2 + this.m_layoutX + this.widthScaled(var1) / 2.0F;
      float var5 = var3 + this.m_layoutY + this.heightScaled(var1) / 2.0F;
      var1.DrawTextureScaledCol(null, var4 - 3.0F, var5 - 3.0F, 6.0, 6.0, this.m_r, this.m_g, this.m_b, this.m_a);
   }

   public abstract void release();
}
