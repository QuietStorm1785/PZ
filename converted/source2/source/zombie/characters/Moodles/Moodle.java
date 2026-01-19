package zombie.characters.Moodles;

import zombie.characters.IsoGameCharacter;
import zombie.characters.IsoPlayer;
import zombie.characters.BodyDamage.Thermoregulator;
import zombie.core.Color;
import zombie.iso.weather.Temperature;
import zombie.ui.MoodlesUI;

public final class Moodle {
   MoodleType Type;
   private int Level;
   IsoGameCharacter Parent;
   private int painTimer = 0;
   private Color chevronColor = Color.white;
   private boolean chevronIsUp = true;
   private int chevronCount = 0;
   private int chevronMax = 0;
   private static Color colorNeg = new Color(0.88235295F, 0.15686275F, 0.15686275F);
   private static Color colorPos = new Color(0.15686275F, 0.88235295F, 0.15686275F);
   private int cantSprintTimer = 300;

   public Moodle(MoodleType var1, IsoGameCharacter var2) {
      this(var1, var2, 0);
   }

   public Moodle(MoodleType var1, IsoGameCharacter var2, int var3) {
      this.Parent = var2;
      this.Type = var1;
      this.Level = 0;
      this.chevronMax = var3;
   }

   public int getChevronCount() {
      return this.chevronCount;
   }

   public boolean isChevronIsUp() {
      return this.chevronIsUp;
   }

   public Color getChevronColor() {
      return this.chevronColor;
   }

   public boolean chevronDifference(int var1, boolean var2, Color var3) {
      return var1 != this.chevronCount || var2 != this.chevronIsUp || var3 != this.chevronColor;
   }

   public void setChevron(int var1, boolean var2, Color var3) {
      if (var1 < 0) {
         var1 = 0;
      }

      if (var1 > this.chevronMax) {
         var1 = this.chevronMax;
      }

      this.chevronCount = var1;
      this.chevronIsUp = var2;
      this.chevronColor = var3 != null ? var3 : Color.white;
   }

   public int getLevel() {
      return this.Level;
   }

   public void SetLevel(int var1) {
      if (var1 < 0) {
         var1 = 0;
      }

      if (var1 > 4) {
         var1 = 4;
      }

      this.Level = var1;
   }

   public boolean Update() {
      boolean var1 = false;
      if (this.Parent.isDead()) {
         byte var2 = 0;
         if (this.Type != MoodleType.Dead && this.Type != MoodleType.Zombie) {
            var2 = 0;
            if (var2 != this.getLevel()) {
               this.SetLevel(var2);
               var1 = true;
            }

            return var1;
         }
      }

      if (this.Type == MoodleType.CantSprint) {
         byte var7 = 0;
         if (((IsoPlayer)this.Parent).MoodleCantSprint) {
            var7 = 1;
            this.cantSprintTimer--;
            MoodlesUI.getInstance().wiggle(MoodleType.CantSprint);
            if (this.cantSprintTimer == 0) {
               var7 = 0;
               this.cantSprintTimer = 300;
               ((IsoPlayer)this.Parent).MoodleCantSprint = false;
            }
         }

         if (var7 != this.getLevel()) {
            this.SetLevel(var7);
            var1 = true;
         }
      }

      if (this.Type == MoodleType.Endurance) {
         byte var8 = 0;
         if (this.Parent.getBodyDamage().getHealth() != 0.0F) {
            if (this.Parent.getStats().endurance > 0.75F) {
               var8 = 0;
            } else if (this.Parent.getStats().endurance > 0.5F) {
               var8 = 1;
            } else if (this.Parent.getStats().endurance > 0.25F) {
               var8 = 2;
            } else if (this.Parent.getStats().endurance > 0.1F) {
               var8 = 3;
            } else {
               var8 = 4;
            }
         }

         if (var8 != this.getLevel()) {
            this.SetLevel(var8);
            var1 = true;
         }
      }

      if (this.Type == MoodleType.Angry) {
         byte var9 = 0;
         if (this.Parent.getStats().Anger > 0.75F) {
            var9 = 4;
         } else if (this.Parent.getStats().Anger > 0.5F) {
            var9 = 3;
         } else if (this.Parent.getStats().Anger > 0.25F) {
            var9 = 2;
         } else if (this.Parent.getStats().Anger > 0.1F) {
            var9 = 1;
         }

         if (var9 != this.getLevel()) {
            this.SetLevel(var9);
            var1 = true;
         }
      }

      if (this.Type == MoodleType.Tired) {
         byte var10 = 0;
         if (this.Parent.getBodyDamage().getHealth() != 0.0F) {
            if (this.Parent.getStats().fatigue > 0.6F) {
               var10 = 1;
            }

            if (this.Parent.getStats().fatigue > 0.7F) {
               var10 = 2;
            }

            if (this.Parent.getStats().fatigue > 0.8F) {
               var10 = 3;
            }

            if (this.Parent.getStats().fatigue > 0.9F) {
               var10 = 4;
            }
         }

         if (var10 != this.getLevel()) {
            this.SetLevel(var10);
            var1 = true;
         }
      }

      if (this.Type == MoodleType.Hungry) {
         byte var11 = 0;
         if (this.Parent.getBodyDamage().getHealth() != 0.0F) {
            if (this.Parent.getStats().hunger > 0.15F) {
               var11 = 1;
            }

            if (this.Parent.getStats().hunger > 0.25F) {
               var11 = 2;
            }

            if (this.Parent.getStats().hunger > 0.45F) {
               var11 = 3;
            }

            if (this.Parent.getStats().hunger > 0.7F) {
               var11 = 4;
            }
         }

         if (var11 != this.getLevel()) {
            this.SetLevel(var11);
            var1 = true;
         }
      }

      if (this.Type == MoodleType.Panic) {
         byte var12 = 0;
         if (this.Parent.getBodyDamage().getHealth() != 0.0F) {
            if (this.Parent.getStats().Panic > 6.0F) {
               var12 = 1;
            }

            if (this.Parent.getStats().Panic > 30.0F) {
               var12 = 2;
            }

            if (this.Parent.getStats().Panic > 65.0F) {
               var12 = 3;
            }

            if (this.Parent.getStats().Panic > 80.0F) {
               var12 = 4;
            }
         }

         if (var12 != this.getLevel()) {
            this.SetLevel(var12);
            var1 = true;
         }
      }

      if (this.Type == MoodleType.Sick) {
         byte var13 = 0;
         if (this.Parent.getBodyDamage().getHealth() != 0.0F) {
            this.Parent.getStats().Sickness = this.Parent.getBodyDamage().getApparentInfectionLevel() / 100.0F;
            if (this.Parent.getStats().Sickness > 0.25F) {
               var13 = 1;
            }

            if (this.Parent.getStats().Sickness > 0.5F) {
               var13 = 2;
            }

            if (this.Parent.getStats().Sickness > 0.75F) {
               var13 = 3;
            }

            if (this.Parent.getStats().Sickness > 0.9F) {
               var13 = 4;
            }
         }

         if (var13 != this.getLevel()) {
            this.SetLevel(var13);
            var1 = true;
         }
      }

      if (this.Type == MoodleType.Bored) {
         byte var14 = 0;
         if (this.Parent.getBodyDamage().getHealth() != 0.0F) {
            this.Parent.getStats().Boredom = this.Parent.getBodyDamage().getBoredomLevel() / 100.0F;
            if (this.Parent.getStats().Boredom > 0.25F) {
               var14 = 1;
            }

            if (this.Parent.getStats().Boredom > 0.5F) {
               var14 = 2;
            }

            if (this.Parent.getStats().Boredom > 0.75F) {
               var14 = 3;
            }

            if (this.Parent.getStats().Boredom > 0.9F) {
               var14 = 4;
            }
         }

         if (var14 != this.getLevel()) {
            this.SetLevel(var14);
            var1 = true;
         }
      }

      if (this.Type == MoodleType.Unhappy) {
         byte var15 = 0;
         if (this.Parent.getBodyDamage().getHealth() != 0.0F) {
            if (this.Parent.getBodyDamage().getUnhappynessLevel() > 20.0F) {
               var15 = 1;
            }

            if (this.Parent.getBodyDamage().getUnhappynessLevel() > 45.0F) {
               var15 = 2;
            }

            if (this.Parent.getBodyDamage().getUnhappynessLevel() > 60.0F) {
               var15 = 3;
            }

            if (this.Parent.getBodyDamage().getUnhappynessLevel() > 80.0F) {
               var15 = 4;
            }
         }

         if (var15 != this.getLevel()) {
            this.SetLevel(var15);
            var1 = true;
         }
      }

      if (this.Type == MoodleType.Stress) {
         byte var16 = 0;
         if (this.Parent.getStats().getStress() > 0.9F) {
            var16 = 4;
         } else if (this.Parent.getStats().getStress() > 0.75F) {
            var16 = 3;
         } else if (this.Parent.getStats().getStress() > 0.5F) {
            var16 = 2;
         } else if (this.Parent.getStats().getStress() > 0.25F) {
            var16 = 1;
         }

         if (var16 != this.getLevel()) {
            this.SetLevel(var16);
            var1 = true;
         }
      }

      if (this.Type == MoodleType.Thirst) {
         byte var17 = 0;
         if (this.Parent.getStats().thirst > 0.12F) {
            var17 = 1;
         }

         if (this.Parent.getStats().thirst > 0.25F) {
            var17 = 2;
         }

         if (this.Parent.getStats().thirst > 0.7F) {
            var17 = 3;
         }

         if (this.Parent.getStats().thirst > 0.84F) {
            var17 = 4;
         }

         if (var17 != this.getLevel()) {
            this.SetLevel(var17);
            var1 = true;
         }
      }

      if (this.Type == MoodleType.Bleeding) {
         int var18 = 0;
         if (this.Parent.getBodyDamage().getHealth() != 0.0F) {
            var18 = this.Parent.getBodyDamage().getNumPartsBleeding();
            if (var18 > 4) {
               var18 = 4;
            }
         }

         if (var18 != this.getLevel()) {
            this.SetLevel(var18);
            var1 = true;
         }
      }

      if (this.Type == MoodleType.Wet) {
         byte var19 = 0;
         if (this.Parent.getBodyDamage().getHealth() != 0.0F) {
            if (this.Parent.getBodyDamage().getWetness() > 15.0F) {
               var19 = 1;
            }

            if (this.Parent.getBodyDamage().getWetness() > 40.0F) {
               var19 = 2;
            }

            if (this.Parent.getBodyDamage().getWetness() > 70.0F) {
               var19 = 3;
            }

            if (this.Parent.getBodyDamage().getWetness() > 90.0F) {
               var19 = 4;
            }
         }

         if (var19 != this.getLevel()) {
            this.SetLevel(var19);
            var1 = true;
         }
      }

      if (this.Type == MoodleType.HasACold) {
         byte var20 = 0;
         if (this.Parent.getBodyDamage().getHealth() != 0.0F) {
            if (this.Parent.getBodyDamage().getColdStrength() > 20.0F) {
               var20 = 1;
            }

            if (this.Parent.getBodyDamage().getColdStrength() > 40.0F) {
               var20 = 2;
            }

            if (this.Parent.getBodyDamage().getColdStrength() > 60.0F) {
               var20 = 3;
            }

            if (this.Parent.getBodyDamage().getColdStrength() > 75.0F) {
               var20 = 4;
            }
         }

         if (var20 != this.getLevel()) {
            this.SetLevel(var20);
            var1 = true;
         }
      }

      if (this.Type == MoodleType.Injured) {
         byte var21 = 0;
         if (this.Parent.getBodyDamage().getHealth() != 0.0F) {
            if (100.0F - this.Parent.getBodyDamage().getHealth() > 20.0F) {
               var21 = 1;
            }

            if (100.0F - this.Parent.getBodyDamage().getHealth() > 40.0F) {
               var21 = 2;
            }

            if (100.0F - this.Parent.getBodyDamage().getHealth() > 60.0F) {
               var21 = 3;
            }

            if (100.0F - this.Parent.getBodyDamage().getHealth() > 75.0F) {
               var21 = 4;
            }
         }

         if (var21 != this.getLevel()) {
            this.SetLevel(var21);
            var1 = true;
         }
      }

      if (this.Type == MoodleType.Pain) {
         this.painTimer++;
         if (this.painTimer < 120) {
            return false;
         }

         this.painTimer = 0;
         byte var22 = 0;
         if (this.Parent.getBodyDamage().getHealth() != 0.0F) {
            if (this.Parent.getStats().Pain > 10.0F) {
               var22 = 1;
            }

            if (this.Parent.getStats().Pain > 20.0F) {
               var22 = 2;
            }

            if (this.Parent.getStats().Pain > 50.0F) {
               var22 = 3;
            }

            if (this.Parent.getStats().Pain > 75.0F) {
               var22 = 4;
            }
         }

         if (var22 != this.getLevel()) {
            this.SetLevel(var22);
            var1 = true;
         }
      }

      if (this.Type == MoodleType.HeavyLoad) {
         byte var23 = 0;
         float var3 = this.Parent.getInventory().getCapacityWeight();
         float var4 = this.Parent.getMaxWeight();
         float var5 = var3 / var4;
         if (this.Parent.getBodyDamage().getHealth() != 0.0F) {
            if (var5 >= 1.75) {
               var23 = 4;
            } else if (var5 >= 1.5) {
               var23 = 3;
            } else if (var5 >= 1.25) {
               var23 = 2;
            } else if (var5 > 1.0F) {
               var23 = 1;
            }
         }

         if (var23 != this.getLevel()) {
            this.SetLevel(var23);
            var1 = true;
         }
      }

      if (this.Type == MoodleType.Drunk) {
         byte var24 = 0;
         if (this.Parent.getBodyDamage().getHealth() != 0.0F) {
            if (this.Parent.getStats().Drunkenness > 10.0F) {
               var24 = 1;
            }

            if (this.Parent.getStats().Drunkenness > 30.0F) {
               var24 = 2;
            }

            if (this.Parent.getStats().Drunkenness > 50.0F) {
               var24 = 3;
            }

            if (this.Parent.getStats().Drunkenness > 70.0F) {
               var24 = 4;
            }
         }

         if (var24 != this.getLevel()) {
            this.SetLevel(var24);
            var1 = true;
         }
      }

      if (this.Type == MoodleType.Dead) {
         byte var25 = 0;
         if (this.Parent.isDead()) {
            var25 = 4;
            if (!this.Parent.getBodyDamage().IsFakeInfected() && this.Parent.getBodyDamage().getInfectionLevel() >= 0.001F) {
               var25 = 0;
            }
         }

         if (var25 != this.getLevel()) {
            this.SetLevel(var25);
            var1 = true;
         }
      }

      if (this.Type == MoodleType.Zombie) {
         byte var26 = 0;
         if (this.Parent.isDead() && !this.Parent.getBodyDamage().IsFakeInfected() && this.Parent.getBodyDamage().getInfectionLevel() >= 0.001F) {
            var26 = 4;
         }

         if (var26 != this.getLevel()) {
            this.SetLevel(var26);
            var1 = true;
         }
      }

      if (this.Type == MoodleType.FoodEaten) {
         byte var27 = 0;
         if (this.Parent.getBodyDamage().getHealth() != 0.0F) {
            if (this.Parent.getBodyDamage().getHealthFromFoodTimer() > 0.0F) {
               var27 = 1;
            }

            if (this.Parent.getBodyDamage().getHealthFromFoodTimer() > this.Parent.getBodyDamage().getStandardHealthFromFoodTime()) {
               var27 = 2;
            }

            if (this.Parent.getBodyDamage().getHealthFromFoodTimer() > this.Parent.getBodyDamage().getStandardHealthFromFoodTime() * 2.0F) {
               var27 = 3;
            }

            if (this.Parent.getBodyDamage().getHealthFromFoodTimer() > this.Parent.getBodyDamage().getStandardHealthFromFoodTime() * 3.0F) {
               var27 = 4;
            }
         }

         if (var27 != this.getLevel()) {
            this.SetLevel(var27);
            var1 = true;
         }
      }

      int var28 = this.chevronCount;
      boolean var30 = this.chevronIsUp;
      Color var31 = this.chevronColor;
      if ((this.Type == MoodleType.Hyperthermia || this.Type == MoodleType.Hypothermia) && this.Parent instanceof IsoPlayer) {
         if (!(this.Parent.getBodyDamage().getTemperature() < 36.5F) && !(this.Parent.getBodyDamage().getTemperature() > 37.5F)) {
            var28 = 0;
         } else {
            Thermoregulator var32 = this.Parent.getBodyDamage().getThermoregulator();
            if (var32 == null) {
               var28 = 0;
            } else {
               var30 = var32.thermalChevronUp();
               var28 = var32.thermalChevronCount();
            }
         }
      }

      if (this.Type == MoodleType.Hyperthermia) {
         byte var33 = 0;
         if (var28 > 0) {
            var31 = var30 ? colorNeg : colorPos;
         }

         if (this.Parent.getBodyDamage().getTemperature() != 0.0F) {
            if (this.Parent.getBodyDamage().getTemperature() > 37.5F) {
               var33 = 1;
            }

            if (this.Parent.getBodyDamage().getTemperature() > 39.0F) {
               var33 = 2;
            }

            if (this.Parent.getBodyDamage().getTemperature() > 40.0F) {
               var33 = 3;
            }

            if (this.Parent.getBodyDamage().getTemperature() > 41.0F) {
               var33 = 4;
            }
         }

         if (var33 != this.getLevel() || var33 > 0 && this.chevronDifference(var28, var30, var31)) {
            this.SetLevel(var33);
            this.setChevron(var28, var30, var31);
            var1 = true;
         }
      }

      if (this.Type == MoodleType.Hypothermia) {
         byte var34 = 0;
         if (var28 > 0) {
            var31 = var30 ? colorPos : colorNeg;
         }

         if (this.Parent.getBodyDamage().getTemperature() != 0.0F) {
            if (this.Parent.getBodyDamage().getTemperature() < 36.5F && this.Parent.getStats().Drunkenness <= 30.0F) {
               var34 = 1;
            }

            if (this.Parent.getBodyDamage().getTemperature() < 35.0F && this.Parent.getStats().Drunkenness <= 70.0F) {
               var34 = 2;
            }

            if (this.Parent.getBodyDamage().getTemperature() < 30.0F) {
               var34 = 3;
            }

            if (this.Parent.getBodyDamage().getTemperature() < 25.0F) {
               var34 = 4;
            }
         }

         if (var34 != this.getLevel() || var34 > 0 && this.chevronDifference(var28, var30, var31)) {
            this.SetLevel(var34);
            this.setChevron(var28, var30, var31);
            var1 = true;
         }
      }

      if (this.Type == MoodleType.Windchill) {
         byte var35 = 0;
         if (this.Parent instanceof IsoPlayer) {
            float var6 = Temperature.getWindChillAmountForPlayer((IsoPlayer)this.Parent);
            if (var6 > 5.0F) {
               var35 = 1;
            }

            if (var6 > 10.0F) {
               var35 = 2;
            }

            if (var6 > 15.0F) {
               var35 = 3;
            }

            if (var6 > 20.0F) {
               var35 = 4;
            }
         }

         if (var35 != this.getLevel()) {
            this.SetLevel(var35);
            var1 = true;
         }
      }

      return var1;
   }
}
