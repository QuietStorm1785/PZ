package zombie.characters.BodyDamage;

import java.util.ArrayList;
import zombie.characterTextures.BloodBodyPartType;
import zombie.core.math.PZMath;
import zombie.core.skinnedmodel.visual.ItemVisual;
import zombie.inventory.types.Clothing;
import zombie.iso.weather.Temperature;

public class Thermoregulator_tryouts$ThermalNode {
   private final float distToCore;
   private final float skinSurface;
   private final BodyPartType bodyPartType;
   private final BloodBodyPartType bloodBPT;
   private final BodyPart bodyPart;
   private final boolean isCore;
   private final float insulationLayerMultiplierUI;
   private Thermoregulator_tryouts$ThermalNode upstream;
   private Thermoregulator_tryouts$ThermalNode[] downstream;
   private float insulation;
   private float windresist;
   private float celcius;
   private float skinCelcius;
   private float heatDelta;
   private float primaryDelta;
   private float secondaryDelta;
   private float clothingWetness;
   private float bodyWetness;
   private ArrayList<Clothing> clothing;

   public Thermoregulator_tryouts$ThermalNode(Thermoregulator_tryouts var1, float var2, BodyPart var3, float var4) {
      this(var1, false, var2, var3, var4);
   }

   public Thermoregulator_tryouts$ThermalNode(Thermoregulator_tryouts var1, boolean var2, float var3, BodyPart var4, float var5) {
      this.this$0 = var1;
      this.celcius = 37.0F;
      this.skinCelcius = 33.0F;
      this.heatDelta = 0.0F;
      this.primaryDelta = 0.0F;
      this.secondaryDelta = 0.0F;
      this.clothingWetness = 0.0F;
      this.bodyWetness = 0.0F;
      this.clothing = new ArrayList<>();
      this.isCore = var2;
      this.celcius = var3;
      this.distToCore = BodyPartType.GetDistToCore(var4.Type);
      this.skinSurface = BodyPartType.GetSkinSurface(var4.Type);
      this.bodyPartType = var4.Type;
      this.bloodBPT = BloodBodyPartType.FromIndex(BodyPartType.ToIndex(var4.Type));
      this.bodyPart = var4;
      this.insulationLayerMultiplierUI = var5;
   }

   private void calculateInsulation() {
      int var1 = this.clothing.size();
      this.insulation = 0.0F;
      this.windresist = 0.0F;
      this.clothingWetness = 0.0F;
      this.bodyWetness = this.bodyPart != null ? this.bodyPart.getWetness() * 0.01F : 0.0F;
      this.bodyWetness = PZMath.clamp_01(this.bodyWetness);
      if (var1 > 0) {
         for (int var4 = 0; var4 < var1; var4++) {
            Clothing var2 = this.clothing.get(var4);
            ItemVisual var3 = var2.getVisual();
            float var5 = PZMath.clamp(var2.getWetness() * 0.01F, 0.0F, 1.0F);
            this.clothingWetness += var5;
            boolean var6 = var3.getHole(this.bloodBPT) > 0.0F;
            if (!var6) {
               float var7 = Temperature.getTrueInsulationValue(var2.getInsulation());
               float var8 = Temperature.getTrueWindresistanceValue(var2.getWindresistance());
               float var9 = PZMath.clamp(var2.getCurrentCondition() * 0.01F, 0.0F, 1.0F);
               var9 = 0.5F + 0.5F * var9;
               var7 *= (1.0F - var5 * 0.75F) * var9;
               var8 *= (1.0F - var5 * 0.45F) * var9;
               this.insulation += var7;
               this.windresist += var8;
            }
         }

         this.clothingWetness /= var1;
         this.insulation += var1 * 0.05F;
         this.windresist += var1 * 0.05F;
      }
   }

   public boolean hasUpstream() {
      return this.upstream != null;
   }

   public boolean hasDownstream() {
      return this.downstream != null && this.downstream.length > 0;
   }

   public float getDistToCore() {
      return this.distToCore;
   }

   public float getSkinSurface() {
      return this.skinSurface;
   }

   public boolean isCore() {
      return this.isCore;
   }

   public float getInsulation() {
      return this.insulation;
   }

   public float getWindresist() {
      return this.windresist;
   }

   public float getCelcius() {
      return this.celcius;
   }

   public float getSkinCelcius() {
      return this.skinCelcius;
   }

   public float getHeatDelta() {
      return this.heatDelta;
   }

   public float getPrimaryDelta() {
      return this.primaryDelta;
   }

   public float getSecondaryDelta() {
      return this.secondaryDelta;
   }

   public float getClothingWetness() {
      return this.clothingWetness;
   }

   public float getBodyWetness() {
      return this.bodyWetness;
   }

   public float getBodyResponse() {
      return PZMath.lerp(this.primaryDelta, this.secondaryDelta, 0.5F);
   }

   public float getSkinCelciusUI() {
      float var1 = PZMath.clamp(this.getSkinCelcius(), 20.0F, 42.0F);
      if (var1 < 33.0F) {
         var1 = (var1 - 20.0F) / 13.0F * 0.5F;
      } else {
         var1 = 0.5F + (var1 - 33.0F) / 9.0F;
      }

      return var1;
   }

   public float getHeatDeltaUI() {
      return PZMath.clamp((this.heatDelta * 0.2F + 1.0F) / 2.0F, 0.0F, 1.0F);
   }

   public float getPrimaryDeltaUI() {
      return PZMath.clamp((this.primaryDelta + 1.0F) / 2.0F, 0.0F, 1.0F);
   }

   public float getSecondaryDeltaUI() {
      return PZMath.clamp((this.secondaryDelta + 1.0F) / 2.0F, 0.0F, 1.0F);
   }

   public float getInsulationUI() {
      return PZMath.clamp(this.insulation * this.insulationLayerMultiplierUI, 0.0F, 1.0F);
   }

   public float getWindresistUI() {
      return PZMath.clamp(this.windresist * this.insulationLayerMultiplierUI, 0.0F, 1.0F);
   }

   public float getClothingWetnessUI() {
      return PZMath.clamp(this.clothingWetness, 0.0F, 1.0F);
   }

   public float getBodyWetnessUI() {
      return PZMath.clamp(this.bodyWetness, 0.0F, 1.0F);
   }

   public float getBodyResponseUI() {
      return PZMath.clamp((this.getBodyResponse() + 1.0F) / 2.0F, 0.0F, 1.0F);
   }
}
