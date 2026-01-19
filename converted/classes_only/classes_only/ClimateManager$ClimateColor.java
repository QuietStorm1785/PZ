package zombie.iso.weather;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.nio.ByteBuffer;
import zombie.network.GameClient;

public class ClimateManager$ClimateColor {
   protected ClimateColorInfo internalValue = new ClimateColorInfo();
   protected ClimateColorInfo finalValue = new ClimateColorInfo();
   protected boolean isOverride = false;
   protected ClimateColorInfo override = new ClimateColorInfo();
   protected float interpolate;
   private boolean isModded = false;
   private ClimateColorInfo moddedValue = new ClimateColorInfo();
   private float modInterpolate;
   private boolean isAdminOverride = false;
   private ClimateColorInfo adminValue = new ClimateColorInfo();
   private int ID;
   private String name;

   public ClimateManager$ClimateColor init(int var1, String var2) {
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

   public ClimateColorInfo getInternalValue() {
      return this.internalValue;
   }

   public ClimateColorInfo getOverride() {
      return this.override;
   }

   public float getOverrideInterpolate() {
      return this.interpolate;
   }

   public void setOverride(ClimateColorInfo var1, float var2) {
      this.override.setTo(var1);
      this.interpolate = var2;
      this.isOverride = true;
   }

   public void setOverride(ByteBuffer var1, float var2) {
      this.override.read(var1);
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

   public void setAdminValue(float var1, float var2, float var3, float var4, float var5, float var6, float var7, float var8) {
      this.adminValue.getExterior().r = var1;
      this.adminValue.getExterior().g = var2;
      this.adminValue.getExterior().b = var3;
      this.adminValue.getExterior().a = var4;
      this.adminValue.getInterior().r = var5;
      this.adminValue.getInterior().g = var6;
      this.adminValue.getInterior().b = var7;
      this.adminValue.getInterior().a = var8;
   }

   public void setAdminValueExterior(float var1, float var2, float var3, float var4) {
      this.adminValue.getExterior().r = var1;
      this.adminValue.getExterior().g = var2;
      this.adminValue.getExterior().b = var3;
      this.adminValue.getExterior().a = var4;
   }

   public void setAdminValueInterior(float var1, float var2, float var3, float var4) {
      this.adminValue.getInterior().r = var1;
      this.adminValue.getInterior().g = var2;
      this.adminValue.getInterior().b = var3;
      this.adminValue.getInterior().a = var4;
   }

   public void setAdminValue(ClimateColorInfo var1) {
      this.adminValue.setTo(var1);
   }

   public ClimateColorInfo getAdminValue() {
      return this.adminValue;
   }

   public void setEnableModded(boolean var1) {
      this.isModded = var1;
   }

   public void setModdedValue(ClimateColorInfo var1) {
      this.moddedValue.setTo(var1);
   }

   public ClimateColorInfo getModdedValue() {
      return this.moddedValue;
   }

   public void setModdedInterpolate(float var1) {
      this.modInterpolate = ClimateManager.clamp01(var1);
   }

   public void setFinalValue(ClimateColorInfo var1) {
      this.finalValue.setTo(var1);
   }

   public ClimateColorInfo getFinalValue() {
      return this.finalValue;
   }

   private void calculate() {
      if (this.isAdminOverride && !GameClient.bClient) {
         this.finalValue.setTo(this.adminValue);
      } else {
         if (this.isModded && this.modInterpolate > 0.0F) {
            this.internalValue.interp(this.moddedValue, this.modInterpolate, this.internalValue);
         }

         if (this.isOverride && this.interpolate > 0.0F) {
            this.internalValue.interp(this.override, this.interpolate, this.finalValue);
         } else {
            this.finalValue.setTo(this.internalValue);
         }
      }
   }

   private void writeAdmin(ByteBuffer var1) {
      var1.put((byte)(this.isAdminOverride ? 1 : 0));
      this.adminValue.write(var1);
   }

   private void readAdmin(ByteBuffer var1) {
      this.isAdminOverride = var1.get() == 1;
      this.adminValue.read(var1);
   }

   private void saveAdmin(DataOutputStream var1) throws IOException {
      var1.writeBoolean(this.isAdminOverride);
      this.adminValue.save(var1);
   }

   private void loadAdmin(DataInputStream var1, int var2) throws IOException {
      this.isAdminOverride = var1.readBoolean();
      if (var2 < 143) {
         this.adminValue.getInterior().r = var1.readFloat();
         this.adminValue.getInterior().g = var1.readFloat();
         this.adminValue.getInterior().b = var1.readFloat();
         this.adminValue.getInterior().a = var1.readFloat();
         this.adminValue.getExterior().r = this.adminValue.getInterior().r;
         this.adminValue.getExterior().g = this.adminValue.getInterior().g;
         this.adminValue.getExterior().b = this.adminValue.getInterior().b;
         this.adminValue.getExterior().a = this.adminValue.getInterior().a;
      } else {
         this.adminValue.load(var1, var2);
      }
   }
}
