package zombie.iso;

import zombie.core.math.PZMath;

public class SearchMode$SearchModeFloat {
   private final float min;
   private final float max;
   private final float stepsize;
   private float exterior;
   private float targetExterior;
   private float interior;
   private float targetInterior;

   private SearchMode$SearchModeFloat(float var1, float var2, float var3) {
      this.min = var1;
      this.max = var2;
      this.stepsize = var3;
   }

   public void set(float var1, float var2, float var3, float var4) {
      this.setExterior(var1);
      this.setTargetExterior(var2);
      this.setInterior(var3);
      this.setTargetInterior(var4);
   }

   public void setTargets(float var1, float var2) {
      this.setTargetExterior(var1);
      this.setTargetInterior(var2);
   }

   public float getExterior() {
      return this.exterior;
   }

   public void setExterior(float var1) {
      this.exterior = var1;
   }

   public float getTargetExterior() {
      return this.targetExterior;
   }

   public void setTargetExterior(float var1) {
      this.targetExterior = var1;
   }

   public float getInterior() {
      return this.interior;
   }

   public void setInterior(float var1) {
      this.interior = var1;
   }

   public float getTargetInterior() {
      return this.targetInterior;
   }

   public void setTargetInterior(float var1) {
      this.targetInterior = var1;
   }

   public void update(float var1) {
      this.exterior = var1 * this.targetExterior;
      this.interior = var1 * this.targetInterior;
   }

   public void equalise() {
      if (!PZMath.equal(this.exterior, this.targetExterior, 0.001F)) {
         this.exterior = PZMath.lerp(this.exterior, this.targetExterior, 0.01F);
      } else {
         this.exterior = this.targetExterior;
      }

      if (!PZMath.equal(this.interior, this.targetInterior, 0.001F)) {
         this.interior = PZMath.lerp(this.interior, this.targetInterior, 0.01F);
      } else {
         this.interior = this.targetInterior;
      }
   }

   public void reset() {
      this.exterior = 0.0F;
      this.interior = 0.0F;
   }

   public float getMin() {
      return this.min;
   }

   public float getMax() {
      return this.max;
   }

   public float getStepsize() {
      return this.stepsize;
   }
}
