package zombie.iso;

import zombie.core.math.PZMath;
import zombie.iso.WorldMarkers.Line;
import zombie.iso.WorldMarkers.Point;

class WorldMarkers$PlayerScreen {
   private float centerX;
   private float centerY;
   private float x;
   private float y;
   private float width;
   private float height;
   private float padTop;
   private float padLeft;
   private float padBot;
   private float padRight;
   private float innerX;
   private float innerY;
   private float innerX2;
   private float innerY2;
   private Line borderTop;
   private Line borderRight;
   private Line borderBot;
   private Line borderLeft;
   private Line[] borders;

   WorldMarkers$PlayerScreen(WorldMarkers var1) {
      this.this$0 = var1;
      this.padTop = 100.0F;
      this.padLeft = 100.0F;
      this.padBot = 100.0F;
      this.padRight = 100.0F;
      this.borderTop = new Line(new Point(0.0F, 0.0F), new Point(0.0F, 0.0F));
      this.borderRight = new Line(new Point(0.0F, 0.0F), new Point(0.0F, 0.0F));
      this.borderBot = new Line(new Point(0.0F, 0.0F), new Point(0.0F, 0.0F));
      this.borderLeft = new Line(new Point(0.0F, 0.0F), new Point(0.0F, 0.0F));
      this.borders = new Line[4];
   }

   private void update(int var1) {
      this.x = 0.0F;
      this.y = 0.0F;
      this.width = IsoCamera.getScreenWidth(var1);
      this.height = IsoCamera.getScreenHeight(var1);
      this.centerX = this.x + this.width / 2.0F;
      this.centerY = this.y + this.height / 2.0F;
      this.innerX = this.x + this.padLeft;
      this.innerY = this.y + this.padTop;
      float var2 = this.width - (this.padLeft + this.padRight);
      float var3 = this.height - (this.padTop + this.padBot);
      this.innerX2 = this.innerX + var2;
      this.innerY2 = this.innerY + var3;
   }

   private Line[] getBorders() {
      this.borders[0] = this.getBorderTop();
      this.borders[1] = this.getBorderRight();
      this.borders[2] = this.getBorderBot();
      this.borders[3] = this.getBorderLeft();
      return this.borders;
   }

   private Line getBorderTop() {
      this.borderTop.s.set(this.innerX, this.innerY);
      this.borderTop.e.set(this.innerX2, this.innerY);
      return this.borderTop;
   }

   private Line getBorderRight() {
      this.borderRight.s.set(this.innerX2, this.innerY);
      this.borderRight.e.set(this.innerX2, this.innerY2);
      return this.borderRight;
   }

   private Line getBorderBot() {
      this.borderBot.s.set(this.innerX, this.innerY2);
      this.borderBot.e.set(this.innerX2, this.innerY2);
      return this.borderBot;
   }

   private Line getBorderLeft() {
      this.borderLeft.s.set(this.innerX, this.innerY);
      this.borderLeft.e.set(this.innerX, this.innerY2);
      return this.borderLeft;
   }

   private float clampToInnerX(float var1) {
      return PZMath.clamp(var1, this.innerX, this.innerX2);
   }

   private float clampToInnerY(float var1) {
      return PZMath.clamp(var1, this.innerY, this.innerY2);
   }

   private boolean isOnScreen(float var1, float var2) {
      return var1 >= this.x && var1 < this.x + this.width && var2 >= this.y && var2 < this.y + this.height;
   }

   private boolean isWithinInner(float var1, float var2) {
      return var1 >= this.innerX && var1 < this.innerX2 && var2 >= this.innerY && var2 < this.innerY2;
   }
}
