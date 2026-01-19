package zombie.debug;

class LineDrawer$DrawableLine {
   public boolean bLine = false;
   String name;
   float red;
   float green;
   float blue;
   float alpha;
   float xstart;
   float ystart;
   float zstart;
   float xend;
   float yend;
   float zend;
   int yPixelOffset;

   public LineDrawer$DrawableLine init(float var1, float var2, float var3, float var4, float var5, float var6, float var7, float var8, float var9, String var10) {
      this.xstart = var1;
      this.ystart = var2;
      this.zstart = var3;
      this.xend = var4;
      this.yend = var5;
      this.zend = var6;
      this.red = var7;
      this.green = var8;
      this.blue = var9;
      this.alpha = 1.0F;
      this.name = var10;
      this.yPixelOffset = 0;
      return this;
   }

   public LineDrawer$DrawableLine init(
      float var1, float var2, float var3, float var4, float var5, float var6, float var7, float var8, float var9, String var10, boolean var11
   ) {
      this.xstart = var1;
      this.ystart = var2;
      this.zstart = var3;
      this.xend = var4;
      this.yend = var5;
      this.zend = var6;
      this.red = var7;
      this.green = var8;
      this.blue = var9;
      this.alpha = 1.0F;
      this.name = var10;
      this.bLine = var11;
      this.yPixelOffset = 0;
      return this;
   }

   public LineDrawer$DrawableLine init(float var1, float var2, float var3, float var4, float var5, float var6, float var7, float var8, float var9, float var10) {
      this.xstart = var1;
      this.ystart = var2;
      this.zstart = var3;
      this.xend = var4;
      this.yend = var5;
      this.zend = var6;
      this.red = var7;
      this.green = var8;
      this.blue = var9;
      this.alpha = var10;
      this.name = null;
      this.bLine = true;
      this.yPixelOffset = 0;
      return this;
   }

   @Override
   public boolean equals(Object var1) {
      return var1 instanceof LineDrawer$DrawableLine ? ((LineDrawer$DrawableLine)var1).name.equals(this.name) : var1.equals(this);
   }
}
