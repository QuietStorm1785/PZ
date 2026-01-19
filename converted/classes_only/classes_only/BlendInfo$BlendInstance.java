package zombie.core.skinnedmodel.advancedanimation;

import zombie.core.skinnedmodel.advancedanimation.BlendInfo.1;

public class BlendInfo$BlendInstance {
   public float current = -1.0F;
   public float target;
   BlendInfo info;

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
   public String GetDebug() {
      String var1 = "Blend: " + this.info.name;
      switch (1.$SwitchMap$zombie$core$skinnedmodel$advancedanimation$BlendType[this.info.Type.ordinal()]) {
         case 1:
            var1 = var1 + ", Linear ";
            break;
         case 2:
            var1 = var1 + ", InverseExponential ";
      }

      return var1 + ", Current " + this.current;
   }

   public BlendInfo$BlendInstance(BlendInfo var1) {
      this.info = var1;
   }

   public void set(float var1) {
      this.target = var1;
      if (this.current == -1.0F) {
         this.current = this.target;
      }
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
   public void update() {
      float var1 = 0.0F;
      if (this.current < this.target) {
         float var2 = 1.0F;
         switch (1.$SwitchMap$zombie$core$skinnedmodel$advancedanimation$BlendType[this.info.Type.ordinal()]) {
            case 2:
               var2 = this.current / 1.0F;
               var2 = 1.0F - var2;
               if (var2 < 0.1F) {
                  var2 = 0.1F;
               }
            case 1:
            default:
               var1 = this.info.inc * var2;
               this.current += var1;
               if (this.current > this.target) {
                  this.current = this.target;
               }
         }
      } else if (this.current > this.target) {
         float var6 = 1.0F;
         switch (1.$SwitchMap$zombie$core$skinnedmodel$advancedanimation$BlendType[this.info.Type.ordinal()]) {
            case 2:
               var6 = this.current / 1.0F;
               var6 = 1.0F - var6;
               if (var6 < 0.1F) {
                  var6 = 0.1F;
               }
            case 1:
            default:
               var1 = -this.info.dec * var6;
               this.current += var1;
               if (this.current < this.target) {
                  this.current = this.target;
               }
         }
      }
   }
}
