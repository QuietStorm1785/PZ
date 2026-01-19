package zombie.iso.weather;

import zombie.GameTime.AnimTimer;
import zombie.core.Rand;

public class ThunderStorm$ThunderCloud {
   private int currentX;
   private int currentY;
   private int startX;
   private int startY;
   private int endX;
   private int endY;
   private double startTime;
   private double endTime;
   private double duration;
   private float strength;
   private float angle;
   private float radius;
   private float eventFrequency;
   private float thunderRatio;
   private float percentageOffset;
   private boolean isRunning = false;
   private AnimTimer suspendTimer = new AnimTimer();

   public int getCurrentX() {
      return this.currentX;
   }

   public int getCurrentY() {
      return this.currentY;
   }

   public float getRadius() {
      return this.radius;
   }

   public boolean isRunning() {
      return this.isRunning;
   }

   public float getStrength() {
      return this.strength;
   }

   public double lifeTime() {
      return (this.startTime - this.endTime) / this.duration;
   }

   public void setCenter(int var1, int var2, float var3) {
      int var4 = ThunderStorm.getMapDiagonal();
      float var5 = ThunderStorm.addToAngle(var3, 180.0F);
      int var6 = var4 + Rand.Next(1500, 7500);
      int var7 = (int)(var1 + var6 * Math.cos(Math.toRadians(var5)));
      int var8 = (int)(var2 + var6 * Math.sin(Math.toRadians(var5)));
      var6 = var4 + Rand.Next(1500, 7500);
      int var9 = (int)(var1 + var6 * Math.cos(Math.toRadians(var3)));
      int var10 = (int)(var2 + var6 * Math.sin(Math.toRadians(var3)));
      this.startX = var7;
      this.startY = var8;
      this.endX = var9;
      this.endY = var10;
      this.currentX = var7;
      this.currentY = var8;
   }
}
