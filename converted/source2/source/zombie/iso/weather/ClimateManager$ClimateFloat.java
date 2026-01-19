package zombie.iso.weather;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.nio.ByteBuffer;
import zombie.network.GameClient;

public class ClimateManager$ClimateFloat {
   protected float internalValue;
   protected float finalValue;
   protected boolean isOverride = false;
   protected float override;
   protected float interpolate;
   private boolean isModded = false;
   private float moddedValue;
   private float modInterpolate;
   private boolean isAdminOverride = false;
   private float adminValue;
   private float min = 0.0F;
   private float max = 1.0F;
   private int ID;
   private String name;

   public ClimateManager$ClimateFloat init(int var1, String var2) {
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

   public float getInternalValue() {
      return this.internalValue;
   }

   public float getOverride() {
      return this.override;
   }

   public float getOverrideInterpolate() {
      return this.interpolate;
   }

   public void setOverride(float var1, float var2) {
      this.override = var1;
      this.interpolate = var2;
      this.isOverride = true;
   }

   public void setEnableOverride(boolean var1) {
      this.isOverride = var1;
   }

   public boolean isEnableOverride() {
      return this.isOverride;
   }

   public void setEnableAdmin(boolean var1) {
      this.isAdminOverride = var1;
   }

   public boolean isEnableAdmin() {
      return this.isAdminOverride;
   }

   public void setAdminValue(float var1) {
      this.adminValue = ClimateManager.clamp(this.min, this.max, var1);
   }

   public float getAdminValue() {
      return this.adminValue;
   }

   public void setEnableModded(boolean var1) {
      this.isModded = var1;
   }

   public void setModdedValue(float var1) {
      this.moddedValue = ClimateManager.clamp(this.min, this.max, var1);
   }

   public float getModdedValue() {
      return this.moddedValue;
   }

   public void setModdedInterpolate(float var1) {
      this.modInterpolate = ClimateManager.clamp01(var1);
   }

   public void setFinalValue(float var1) {
      this.finalValue = var1;
   }

   public float getFinalValue() {
      return this.finalValue;
   }

   private void calculate() {
      if (this.isAdminOverride && !GameClient.bClient) {
         this.finalValue = this.adminValue;
      } else {
         if (this.isModded && this.modInterpolate > 0.0F) {
            this.internalValue = ClimateManager.lerp(this.modInterpolate, this.internalValue, this.moddedValue);
         }

         if (this.isOverride && this.interpolate > 0.0F) {
            this.finalValue = ClimateManager.lerp(this.interpolate, this.internalValue, this.override);
         } else {
            this.finalValue = this.internalValue;
         }
      }
   }

   private void writeAdmin(ByteBuffer var1) {
      var1.put((byte)(this.isAdminOverride ? 1 : 0));
      var1.putFloat(this.adminValue);
   }

   private void readAdmin(ByteBuffer var1) {
      this.isAdminOverride = var1.get() == 1;
      this.adminValue = var1.getFloat();
   }

   private void saveAdmin(DataOutputStream var1) throws IOException {
      var1.writeBoolean(this.isAdminOverride);
      var1.writeFloat(this.adminValue);
   }

   private void loadAdmin(DataInputStream var1, int var2) throws IOException {
      this.isAdminOverride = var1.readBoolean();
      this.adminValue = var1.readFloat();
   }
}
