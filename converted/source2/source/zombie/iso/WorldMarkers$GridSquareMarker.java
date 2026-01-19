package zombie.iso;

import zombie.core.Core;
import zombie.core.textures.Texture;
import zombie.iso.sprite.IsoSpriteInstance;
import zombie.iso.sprite.IsoSpriteManager;

public final class WorldMarkers$GridSquareMarker {
   private int ID;
   private IsoSpriteInstance sprite;
   private IsoSpriteInstance spriteOverlay;
   private float orig_x;
   private float orig_y;
   private float orig_z;
   private float x;
   private float y;
   private float z;
   private float scaleRatio;
   private float r;
   private float g;
   private float b;
   private float a;
   private float size;
   private boolean doBlink = false;
   private boolean doAlpha;
   private boolean bScaleCircleTexture = false;
   private float fadeSpeed = 0.006F;
   private float alpha = 0.0F;
   private float alphaMax = 1.0F;
   private float alphaMin = 0.3F;
   private boolean alphaInc = true;
   private boolean active = true;
   private boolean isRemoved = false;

   public WorldMarkers$GridSquareMarker() {
      this.ID = WorldMarkers.NextGridSquareMarkerID++;
   }

   public int getID() {
      return this.ID;
   }

   public void remove() {
      this.isRemoved = true;
   }

   public boolean isRemoved() {
      return this.isRemoved;
   }

   public void init(String var1, String var2, int var3, int var4, int var5, float var6) {
      if (var1 == null) {
         var1 = "circle_center";
      }

      Texture var7 = Texture.getSharedTexture("media/textures/highlights/" + var1 + ".png");
      float var8 = var7.getWidth();
      float var9 = 64.0F * Core.TileScale;
      this.scaleRatio = 1.0F / (var8 / var9);
      this.sprite = new IsoSpriteInstance(IsoSpriteManager.instance.getSprite("media/textures/highlights/" + var1 + ".png"));
      if (var2 != null) {
         this.spriteOverlay = new IsoSpriteInstance(IsoSpriteManager.instance.getSprite("media/textures/highlights/" + var2 + ".png"));
      }

      this.setPosAndSize(var3, var4, var5, var6);
   }

   public void setPosAndSize(int var1, int var2, int var3, float var4) {
      float var5 = var4 * (this.bScaleCircleTexture ? 1.5F : 1.0F);
      float var6 = this.scaleRatio * var5;
      this.sprite.setScale(var6, var6);
      if (this.spriteOverlay != null) {
         this.spriteOverlay.setScale(var6, var6);
      }

      this.size = var4;
      this.orig_x = var1;
      this.orig_y = var2;
      this.orig_z = var3;
      this.x = var1 - (var5 - 0.5F);
      this.y = var2 + 0.5F;
      this.z = var3;
   }

   public void setPos(int var1, int var2, int var3) {
      float var4 = this.size * (this.bScaleCircleTexture ? 1.5F : 1.0F);
      this.orig_x = var1;
      this.orig_y = var2;
      this.orig_z = var3;
      this.x = var1 - (var4 - 0.5F);
      this.y = var2 + 0.5F;
      this.z = var3;
   }

   public void setSize(float var1) {
      float var2 = var1 * (this.bScaleCircleTexture ? 1.5F : 1.0F);
      float var3 = this.scaleRatio * var2;
      this.sprite.setScale(var3, var3);
      if (this.spriteOverlay != null) {
         this.spriteOverlay.setScale(var3, var3);
      }

      this.size = var1;
      this.x = this.orig_x - (var2 - 0.5F);
      this.y = this.orig_y + 0.5F;
      this.z = this.orig_z;
   }

   public boolean isActive() {
      return this.active;
   }

   public void setActive(boolean var1) {
      this.active = var1;
   }

   public float getSize() {
      return this.size;
   }

   public float getX() {
      return this.x;
   }

   public float getY() {
      return this.y;
   }

   public float getZ() {
      return this.z;
   }

   public float getR() {
      return this.r;
   }

   public void setR(float var1) {
      this.r = var1;
   }

   public float getG() {
      return this.g;
   }

   public void setG(float var1) {
      this.g = var1;
   }

   public float getB() {
      return this.b;
   }

   public void setB(float var1) {
      this.b = var1;
   }

   public float getA() {
      return this.a;
   }

   public void setA(float var1) {
      this.a = var1;
   }

   public float getAlpha() {
      return this.alpha;
   }

   public void setAlpha(float var1) {
      this.alpha = var1;
   }

   public float getAlphaMax() {
      return this.alphaMax;
   }

   public void setAlphaMax(float var1) {
      this.alphaMax = var1;
   }

   public float getAlphaMin() {
      return this.alphaMin;
   }

   public void setAlphaMin(float var1) {
      this.alphaMin = var1;
   }

   public boolean isDoAlpha() {
      return this.doAlpha;
   }

   public void setDoAlpha(boolean var1) {
      this.doAlpha = var1;
   }

   public float getFadeSpeed() {
      return this.fadeSpeed;
   }

   public void setFadeSpeed(float var1) {
      this.fadeSpeed = var1;
   }

   public boolean isDoBlink() {
      return this.doBlink;
   }

   public void setDoBlink(boolean var1) {
      this.doBlink = var1;
   }

   public boolean isScaleCircleTexture() {
      return this.bScaleCircleTexture;
   }

   public void setScaleCircleTexture(boolean var1) {
      this.bScaleCircleTexture = var1;
      float var2 = this.size * (this.bScaleCircleTexture ? 1.5F : 1.0F);
      float var3 = this.scaleRatio * var2;
      if (this.sprite != null) {
         this.sprite.setScale(var3, var3);
      }

      if (this.spriteOverlay != null) {
         this.spriteOverlay.setScale(var3, var3);
      }

      this.x = this.orig_x - (var2 - 0.5F);
   }
}
