package zombie.iso;

public class IsoPuddles$PuddlesFloat {
   protected float finalValue;
   private boolean isAdminOverride = false;
   private float adminValue;
   private float min = 0.0F;
   private float max = 1.0F;
   private float delta = 0.01F;
   private int ID;
   private String name;

   public IsoPuddles$PuddlesFloat init(int var1, String var2) {
      this.ID = var1;
      this.name = var2;
      return this;
   }

   public int getID() {
      return this.ID;
   }

   public String getName() {
      return this.name;
   }

   public float getMin() {
      return this.min;
   }

   public float getMax() {
      return this.max;
   }

   public void setEnableAdmin(boolean var1) {
      this.isAdminOverride = var1;
   }

   public boolean isEnableAdmin() {
      return this.isAdminOverride;
   }

   public void setAdminValue(float var1) {
      this.adminValue = Math.max(this.min, Math.min(this.max, var1));
   }

   public float getAdminValue() {
      return this.adminValue;
   }

   public void setFinalValue(float var1) {
      this.finalValue = Math.max(this.min, Math.min(this.max, var1));
   }

   public void addFinalValue(float var1) {
      this.finalValue = Math.max(this.min, Math.min(this.max, this.finalValue + var1));
   }

   public void addFinalValueForMax(float var1, float var2) {
      this.finalValue = Math.max(this.min, Math.min(var2, this.finalValue + var1));
   }

   public float getFinalValue() {
      return this.isAdminOverride ? this.adminValue : this.finalValue;
   }

   public void interpolateFinalValue(float var1) {
      if (Math.abs(this.finalValue - var1) < this.delta) {
         this.finalValue = var1;
      } else if (var1 > this.finalValue) {
         this.finalValue = this.finalValue + this.delta;
      } else {
         this.finalValue = this.finalValue - this.delta;
      }
   }

   private void calculate() {
      if (this.isAdminOverride) {
         this.finalValue = this.adminValue;
      }
   }
}
