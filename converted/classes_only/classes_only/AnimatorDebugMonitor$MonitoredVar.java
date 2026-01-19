package zombie.core.skinnedmodel.advancedanimation.debug;

class AnimatorDebugMonitor$MonitoredVar {
   String key;
   String value;
   boolean isFloat;
   float valFloat;
   boolean active;
   boolean updated;
   float[] f_floats;
   int f_index;
   float f_min;
   float f_max;

   private AnimatorDebugMonitor$MonitoredVar(AnimatorDebugMonitor var1) {
      this.this$0 = var1;
      this.key = "";
      this.value = "";
      this.isFloat = false;
      this.active = false;
      this.updated = false;
      this.f_index = 0;
      this.f_min = -1.0F;
      this.f_max = 1.0F;
   }

   public void logFloat(float var1) {
      if (this.f_floats == null) {
         this.f_floats = new float[1024];
      }

      if (var1 != this.valFloat) {
         this.valFloat = var1;
         this.f_floats[this.f_index++] = var1;
         if (var1 < this.f_min) {
            this.f_min = var1;
         }

         if (var1 > this.f_max) {
            this.f_max = var1;
         }

         if (this.f_index >= 1024) {
            this.f_index = 0;
         }
      }
   }
}
