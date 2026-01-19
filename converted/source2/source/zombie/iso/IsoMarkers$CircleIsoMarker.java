package zombie.iso;

public final class IsoMarkers$CircleIsoMarker {
   private int ID;
   private IsoGridSquare square;
   private float x;
   private float y;
   private float z;
   private float r;
   private float g;
   private float b;
   private float a;
   private float size;
   private boolean doAlpha;
   private float fadeSpeed = 0.006F;
   private float alpha = 0.0F;
   private float alphaMax = 1.0F;
   private float alphaMin = 0.3F;
   private boolean alphaInc = true;
   private boolean active = true;
   private boolean isRemoved = false;

   public IsoMarkers$CircleIsoMarker() {
      this.ID = IsoMarkers.NextCircleIsoMarkerID++;
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

   public void init(int var1, int var2, int var3, IsoGridSquare var4) {
      this.square = var4;
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

   public float getG() {
      return this.g;
   }

   public float getB() {
      return this.b;
   }

   public float getA() {
      return this.a;
   }

   public void setR(float var1) {
      this.r = var1;
   }

   public void setG(float var1) {
      this.g = var1;
   }

   public void setB(float var1) {
      this.b = var1;
   }

   public void setA(float var1) {
      this.a = var1;
   }

   public float getSize() {
      return this.size;
   }

   public void setSize(float var1) {
      this.size = var1;
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

   public IsoGridSquare getSquare() {
      return this.square;
   }

   public void setSquare(IsoGridSquare var1) {
      this.square = var1;
   }

   public void setPos(int var1, int var2, int var3) {
      this.x = var1;
      this.y = var2;
      this.z = var3;
   }

   public boolean isActive() {
      return this.active;
   }

   public void setActive(boolean var1) {
      this.active = var1;
   }
}
