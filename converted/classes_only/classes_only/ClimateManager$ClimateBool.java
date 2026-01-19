package zombie.iso.weather;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.nio.ByteBuffer;
import zombie.network.GameClient;

public class ClimateManager$ClimateBool {
   protected boolean internalValue;
   protected boolean finalValue;
   protected boolean isOverride;
   protected boolean override;
   private boolean isModded = false;
   private boolean moddedValue;
   private boolean isAdminOverride = false;
   private boolean adminValue;
   private int ID;
   private String name;

   public ClimateManager$ClimateBool init(int var1, String var2) {
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

   public boolean getInternalValue() {
      return this.internalValue;
   }

   public boolean getOverride() {
      return this.override;
   }

   public void setOverride(boolean var1) {
      this.isOverride = true;
      this.override = var1;
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

   public void setAdminValue(boolean var1) {
      this.adminValue = var1;
   }

   public boolean getAdminValue() {
      return this.adminValue;
   }

   public void setEnableModded(boolean var1) {
      this.isModded = var1;
   }

   public void setModdedValue(boolean var1) {
      this.moddedValue = var1;
   }

   public boolean getModdedValue() {
      return this.moddedValue;
   }

   public void setFinalValue(boolean var1) {
      this.finalValue = var1;
   }

   private void calculate() {
      if (this.isAdminOverride && !GameClient.bClient) {
         this.finalValue = this.adminValue;
      } else if (this.isModded) {
         this.finalValue = this.moddedValue;
      } else {
         this.finalValue = this.isOverride ? this.override : this.internalValue;
      }
   }

   private void writeAdmin(ByteBuffer var1) {
      var1.put((byte)(this.isAdminOverride ? 1 : 0));
      var1.put((byte)(this.adminValue ? 1 : 0));
   }

   private void readAdmin(ByteBuffer var1) {
      this.isAdminOverride = var1.get() == 1;
      this.adminValue = var1.get() == 1;
   }

   private void saveAdmin(DataOutputStream var1) throws IOException {
      var1.writeBoolean(this.isAdminOverride);
      var1.writeBoolean(this.adminValue);
   }

   private void loadAdmin(DataInputStream var1, int var2) throws IOException {
      this.isAdminOverride = var1.readBoolean();
      this.adminValue = var1.readBoolean();
   }
}
