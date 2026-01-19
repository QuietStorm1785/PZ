package zombie.ui;

import java.util.ArrayList;
import zombie.GameTime;
import zombie.characters.IsoPlayer;
import zombie.core.Color;
import zombie.core.Core;
import zombie.core.textures.Texture;
import zombie.debug.DebugOptions;
import zombie.inventory.InventoryItem;
import zombie.inventory.types.AlarmClock;
import zombie.inventory.types.AlarmClockClothing;
import zombie.iso.weather.ClimateManager;
import zombie.network.GameClient;

public final class Clock extends UIElement {
   boolean bLargeTextures = false;
   Texture background = null;
   Texture[] digitsLarge;
   Texture[] digitsSmall;
   Texture colon = null;
   Texture slash = null;
   Texture minus = null;
   Texture dot = null;
   Texture tempC = null;
   Texture tempF = null;
   Texture tempE = null;
   Texture texAM = null;
   Texture texPM = null;
   Texture alarmOn = null;
   Texture alarmRinging = null;
   Color displayColour = new Color(100, 200, 210, 255);
   Color ghostColour = new Color(40, 40, 40, 128);
   int uxOriginal;
   int uyOriginal;
   int largeDigitSpacing;
   int smallDigitSpacing;
   int colonSpacing;
   int ampmSpacing;
   int alarmBellSpacing;
   int decimalSpacing;
   int degreeSpacing;
   int slashSpacing;
   int tempDateSpacing;
   int dateOffset;
   int minusOffset;
   int amVerticalSpacing;
   int pmVerticalSpacing;
   int alarmBellVerticalSpacing;
   int displayVerticalSpacing;
   int decimalVerticalSpacing;
   public boolean digital = false;
   public boolean isAlarmSet = false;
   public boolean isAlarmRinging = false;
   private IsoPlayer clockPlayer = null;
   public static Clock instance = null;

   public Clock(int var1, int var2) {
      this.x = var1;
      this.y = var2;
      instance = this;
   }

   public void render() {
      if (this.visible) {
         this.assignTextures(Core.getInstance().getOptionClockSize() == 2);
         this.DrawTexture(this.background, 0.0, 0.0, 0.75);
         this.renderDisplay(true, this.ghostColour);
         this.renderDisplay(false, this.displayColour);
         super.render();
      }
   }

   private void renderDisplay(boolean var1, Color var2) {
      int var3 = this.uxOriginal;
      int var4 = this.uyOriginal;

      for (int var5 = 0; var5 < 4; var5++) {
         int[] var6 = this.timeDigits();
         if (var1) {
            this.DrawTextureCol(this.digitsLarge[8], var3, var4, var2);
         } else {
            this.DrawTextureCol(this.digitsLarge[var6[var5]], var3, var4, var2);
         }

         var3 += this.digitsLarge[0].getWidth();
         if (var5 == 1) {
            var3 += this.colonSpacing;
            this.DrawTextureCol(this.colon, var3, var4, var2);
            var3 += this.colon.getWidth() + this.colonSpacing;
         } else if (var5 < 3) {
            var3 += this.largeDigitSpacing;
         }
      }

      var3 += this.ampmSpacing;
      if (!Core.getInstance().getOptionClock24Hour() || var1) {
         if (var1) {
            this.DrawTextureCol(this.texAM, var3, var4 + this.amVerticalSpacing, var2);
            this.DrawTextureCol(this.texPM, var3, var4 + this.pmVerticalSpacing, var2);
         } else if (GameTime.getInstance().getTimeOfDay() < 12.0F) {
            this.DrawTextureCol(this.texAM, var3, var4 + this.amVerticalSpacing, var2);
         } else {
            this.DrawTextureCol(this.texPM, var3, var4 + this.pmVerticalSpacing, var2);
         }
      }

      if (this.isAlarmRinging || var1) {
         this.DrawTextureCol(this.alarmRinging, var3 + this.texAM.getWidth() + this.alarmBellSpacing, var4 + this.alarmBellVerticalSpacing, var2);
      } else if (this.isAlarmSet) {
         this.DrawTextureCol(this.alarmOn, var3 + this.texAM.getWidth() + this.alarmBellSpacing, var4 + this.alarmBellVerticalSpacing, var2);
      }

      if (this.digital || var1) {
         var3 = this.uxOriginal;
         var4 += this.digitsLarge[0].getHeight() + this.displayVerticalSpacing;
         if (this.clockPlayer == null) {
            var3 += this.dateOffset;
         } else {
            int[] var18 = this.tempDigits();
            if (var18[0] == 1 || var1) {
               this.DrawTextureCol(this.minus, var3, var4, var2);
            }

            var3 += this.minusOffset;
            if (var18[1] == 1 || var1) {
               this.DrawTextureCol(this.digitsSmall[1], var3, var4, var2);
            }

            var3 += this.digitsSmall[0].getWidth() + this.smallDigitSpacing;

            for (int var20 = 2; var20 < 5; var20++) {
               if (var1) {
                  this.DrawTextureCol(this.digitsSmall[8], var3, var4, var2);
               } else {
                  this.DrawTextureCol(this.digitsSmall[var18[var20]], var3, var4, var2);
               }

               var3 += this.digitsSmall[0].getWidth();
               if (var20 == 3) {
                  var3 += this.decimalSpacing;
                  this.DrawTextureCol(this.dot, var3, var4 + this.decimalVerticalSpacing, var2);
                  var3 += this.dot.getWidth() + this.decimalSpacing;
               } else if (var20 < 4) {
                  var3 += this.smallDigitSpacing;
               }
            }

            var3 += this.degreeSpacing;
            this.DrawTextureCol(this.dot, var3, var4, var2);
            var3 += this.dot.getWidth() + this.degreeSpacing;
            if (var1) {
               this.DrawTextureCol(this.tempE, var3, var4, var2);
            } else if (var18[5] == 0) {
               this.DrawTextureCol(this.tempC, var3, var4, var2);
            } else {
               this.DrawTextureCol(this.tempF, var3, var4, var2);
            }

            var3 += this.digitsSmall[0].getWidth() + this.tempDateSpacing;
         }

         int[] var19 = this.dateDigits();

         for (int var21 = 0; var21 < 4; var21++) {
            if (var1) {
               this.DrawTextureCol(this.digitsSmall[8], var3, var4, var2);
            } else {
               this.DrawTextureCol(this.digitsSmall[var19[var21]], var3, var4, var2);
            }

            var3 += this.digitsSmall[0].getWidth();
            if (var21 == 1) {
               var3 += this.slashSpacing;
               this.DrawTextureCol(this.slash, var3, var4, var2);
               var3 += this.slash.getWidth() + this.slashSpacing;
            } else if (var21 < 3) {
               var3 += this.smallDigitSpacing;
            }
         }
      }
   }

   private void assignTextures(boolean var1) {
      if (this.digitsLarge == null || this.bLargeTextures != var1) {
         this.bLargeTextures = var1;
         if (var1) {
            this.background = Texture.getSharedTexture("media/ui/ClockAssets/ClockLargeBackground.png");
         } else {
            this.background = Texture.getSharedTexture("media/ui/ClockAssets/ClockSmallBackground.png");
         }

         String var2 = "Medium";
         String var3 = "Small";
         if (var1) {
            var2 = "Large";
            var3 = "Medium";
            this.assignLargeOffsets();
         } else {
            this.assignSmallOffsets();
         }

         if (this.digitsLarge == null) {
            this.digitsLarge = new Texture[10];
            this.digitsSmall = new Texture[10];
         }

         for (int var4 = 0; var4 < 10; var4++) {
            this.digitsLarge[var4] = Texture.getSharedTexture("media/ui/ClockAssets/ClockDigits" + var2 + var4 + ".png");
            this.digitsSmall[var4] = Texture.getSharedTexture("media/ui/ClockAssets/ClockDigits" + var3 + var4 + ".png");
         }

         this.colon = Texture.getSharedTexture("media/ui/ClockAssets/ClockDivide" + var2 + ".png");
         this.slash = Texture.getSharedTexture("media/ui/ClockAssets/DateDivide" + var3 + ".png");
         this.minus = Texture.getSharedTexture("media/ui/ClockAssets/ClockDigits" + var3 + "Minus.png");
         this.dot = Texture.getSharedTexture("media/ui/ClockAssets/ClockDigits" + var3 + "Dot.png");
         this.tempC = Texture.getSharedTexture("media/ui/ClockAssets/ClockDigits" + var3 + "C.png");
         this.tempF = Texture.getSharedTexture("media/ui/ClockAssets/ClockDigits" + var3 + "F.png");
         this.tempE = Texture.getSharedTexture("media/ui/ClockAssets/ClockDigits" + var3 + "E.png");
         this.texAM = Texture.getSharedTexture("media/ui/ClockAssets/ClockAm" + var2 + ".png");
         this.texPM = Texture.getSharedTexture("media/ui/ClockAssets/ClockPm" + var2 + ".png");
         this.alarmOn = Texture.getSharedTexture("media/ui/ClockAssets/ClockAlarm" + var2 + "Set.png");
         this.alarmRinging = Texture.getSharedTexture("media/ui/ClockAssets/ClockAlarm" + var2 + "Sound.png");
      }
   }

   private void assignSmallOffsets() {
      this.uxOriginal = 3;
      this.uyOriginal = 3;
      this.largeDigitSpacing = 1;
      this.smallDigitSpacing = 1;
      this.colonSpacing = 1;
      this.ampmSpacing = 1;
      this.alarmBellSpacing = 1;
      this.decimalSpacing = 1;
      this.degreeSpacing = 1;
      this.slashSpacing = 1;
      this.tempDateSpacing = 5;
      this.dateOffset = 33;
      this.minusOffset = 0;
      this.amVerticalSpacing = 7;
      this.pmVerticalSpacing = 12;
      this.alarmBellVerticalSpacing = 1;
      this.displayVerticalSpacing = 2;
      this.decimalVerticalSpacing = 6;
   }

   private void assignLargeOffsets() {
      this.uxOriginal = 3;
      this.uyOriginal = 3;
      this.largeDigitSpacing = 2;
      this.smallDigitSpacing = 1;
      this.colonSpacing = 3;
      this.ampmSpacing = 3;
      this.alarmBellSpacing = 5;
      this.decimalSpacing = 2;
      this.degreeSpacing = 2;
      this.slashSpacing = 2;
      this.tempDateSpacing = 8;
      this.dateOffset = 65;
      this.minusOffset = -2;
      this.amVerticalSpacing = 15;
      this.pmVerticalSpacing = 25;
      this.alarmBellVerticalSpacing = 1;
      this.displayVerticalSpacing = 5;
      this.decimalVerticalSpacing = 15;
   }

   private int[] timeDigits() {
      float var1 = GameTime.getInstance().getTimeOfDay();
      if (GameClient.bClient && GameClient.bFastForward) {
         var1 = GameTime.getInstance().ServerTimeOfDay;
      }

      if (!Core.getInstance().getOptionClock24Hour()) {
         if (var1 >= 13.0F) {
            var1 -= 12.0F;
         }

         if (var1 < 1.0F) {
            var1 += 12.0F;
         }
      }

      int var2 = (int)var1;
      float var3 = (var1 - (int)var1) * 60.0F;
      int var4 = var2 / 10;
      int var5 = var2 % 10;
      int var6 = (int)(var3 / 10.0F);
      return new int[]{var4, var5, var6, 0};
   }

   private int[] dateDigits() {
      int var1 = 0;
      int var2 = 0;
      int var3 = 0;
      int var4 = 0;
      var1 = (GameTime.getInstance().getDay() + 1) / 10;
      var2 = (GameTime.getInstance().getDay() + 1) % 10;
      var3 = (GameTime.getInstance().getMonth() + 1) / 10;
      var4 = (GameTime.getInstance().getMonth() + 1) % 10;
      return Core.getInstance().getOptionClockFormat() == 1 ? new int[]{var3, var4, var1, var2} : new int[]{var1, var2, var3, var4};
   }

   private int[] tempDigits() {
      float var1 = ClimateManager.getInstance().getAirTemperatureForCharacter(this.clockPlayer, false);
      byte var2 = 0;
      byte var3 = 0;
      if (!Core.OptionTemperatureDisplayCelsius) {
         var1 = var1 * 1.8F + 32.0F;
         var3 = 1;
      }

      if (var1 < 0.0F) {
         var2 = 1;
         var1 *= -1.0F;
      }

      int var4 = (int)var1 / 100;
      int var5 = (int)(var1 % 100.0F) / 10;
      int var6 = (int)var1 % 10;
      int var7 = (int)(var1 * 10.0F) % 10;
      return new int[]{var2, var4, var5, var6, var7, var3};
   }

   public void resize() {
      this.visible = false;
      this.digital = false;
      this.clockPlayer = null;
      this.isAlarmSet = false;
      this.isAlarmRinging = false;
      if (IsoPlayer.getInstance() != null) {
         for (int var1 = 0; var1 < IsoPlayer.numPlayers; var1++) {
            IsoPlayer var2 = IsoPlayer.players[var1];
            if (var2 != null && !var2.isDead()) {
               for (int var3 = 0; var3 < var2.getWornItems().size(); var3++) {
                  InventoryItem var4 = var2.getWornItems().getItemByIndex(var3);
                  if (var4 instanceof AlarmClock || var4 instanceof AlarmClockClothing) {
                     this.visible = UIManager.VisibleAllUI;
                     this.digital = this.digital | var4.hasTag("Digital");
                     if (var4 instanceof AlarmClock) {
                        if (((AlarmClock)var4).isAlarmSet()) {
                           this.isAlarmSet = true;
                        }

                        if (((AlarmClock)var4).isRinging()) {
                           this.isAlarmRinging = true;
                        }
                     } else {
                        if (((AlarmClockClothing)var4).isAlarmSet()) {
                           this.isAlarmSet = true;
                        }

                        if (((AlarmClockClothing)var4).isRinging()) {
                           this.isAlarmRinging = true;
                        }
                     }

                     this.clockPlayer = var2;
                  }
               }

               if (this.clockPlayer != null) {
                  break;
               }

               ArrayList var6 = var2.getInventory().getItems();

               for (int var7 = 0; var7 < var6.size(); var7++) {
                  InventoryItem var5 = (InventoryItem)var6.get(var7);
                  if (var5 instanceof AlarmClock || var5 instanceof AlarmClockClothing) {
                     this.visible = UIManager.VisibleAllUI;
                     this.digital = this.digital | var5.hasTag("Digital");
                     if (var5 instanceof AlarmClock) {
                        if (((AlarmClock)var5).isAlarmSet()) {
                           this.isAlarmSet = true;
                        }

                        if (((AlarmClock)var5).isRinging()) {
                           this.isAlarmRinging = true;
                        }
                     } else {
                        if (((AlarmClockClothing)var5).isAlarmSet()) {
                           this.isAlarmSet = true;
                        }

                        if (((AlarmClockClothing)var5).isRinging()) {
                           this.isAlarmRinging = true;
                        }
                     }

                     this.clockPlayer = var2;
                  }
               }
            }
         }
      }

      if (DebugOptions.instance.CheatClockVisible.getValue()) {
         this.digital = true;
         this.visible = UIManager.VisibleAllUI;
      }

      if (this.background == null) {
         if (Core.getInstance().getOptionClockSize() == 2) {
            this.background = Texture.getSharedTexture("media/ui/ClockAssets/ClockLargeBackground.png");
         } else {
            this.background = Texture.getSharedTexture("media/ui/ClockAssets/ClockSmallBackground.png");
         }
      }

      this.setHeight(this.background.getHeight());
      this.setWidth(this.background.getWidth());
   }

   public boolean isDateVisible() {
      return this.visible && this.digital;
   }

   public Boolean onMouseDown(double var1, double var3) {
      if (!this.isVisible()) {
         return false;
      } else {
         if (this.isAlarmRinging) {
            if (IsoPlayer.getInstance() != null) {
               for (int var5 = 0; var5 < IsoPlayer.numPlayers; var5++) {
                  IsoPlayer var6 = IsoPlayer.players[var5];
                  if (var6 != null && !var6.isDead()) {
                     for (int var7 = 0; var7 < var6.getWornItems().size(); var7++) {
                        InventoryItem var8 = var6.getWornItems().getItemByIndex(var7);
                        if (var8 instanceof AlarmClock) {
                           ((AlarmClock)var8).stopRinging();
                        } else if (var8 instanceof AlarmClockClothing) {
                           ((AlarmClockClothing)var8).stopRinging();
                        }
                     }

                     for (int var13 = 0; var13 < var6.getInventory().getItems().size(); var13++) {
                        InventoryItem var18 = (InventoryItem)var6.getInventory().getItems().get(var13);
                        if (var18 instanceof AlarmClock) {
                           ((AlarmClock)var18).stopRinging();
                        } else if (var18 instanceof AlarmClockClothing) {
                           ((AlarmClockClothing)var18).stopRinging();
                        }
                     }
                  }
               }
            }
         } else if (this.isAlarmSet) {
            if (IsoPlayer.getInstance() != null) {
               for (int var9 = 0; var9 < IsoPlayer.numPlayers; var9++) {
                  IsoPlayer var11 = IsoPlayer.players[var9];
                  if (var11 != null && !var11.isDead()) {
                     for (int var14 = 0; var14 < var11.getWornItems().size(); var14++) {
                        InventoryItem var19 = var11.getWornItems().getItemByIndex(var14);
                        if (var19 instanceof AlarmClock && ((AlarmClock)var19).isAlarmSet()) {
                           ((AlarmClock)var19).setAlarmSet(false);
                        } else if (var19 instanceof AlarmClockClothing && ((AlarmClockClothing)var19).isAlarmSet()) {
                           ((AlarmClockClothing)var19).setAlarmSet(false);
                        }
                     }

                     for (int var15 = 0; var15 < var11.getInventory().getItems().size(); var15++) {
                        InventoryItem var20 = (InventoryItem)var11.getInventory().getItems().get(var15);
                        if (var20 instanceof AlarmClockClothing && ((AlarmClockClothing)var20).isAlarmSet()) {
                           ((AlarmClockClothing)var20).setAlarmSet(false);
                        }

                        if (var20 instanceof AlarmClock && ((AlarmClock)var20).isAlarmSet()) {
                           ((AlarmClock)var20).setAlarmSet(false);
                        }
                     }
                  }
               }
            }
         } else if (IsoPlayer.getInstance() != null) {
            for (int var10 = 0; var10 < IsoPlayer.numPlayers; var10++) {
               IsoPlayer var12 = IsoPlayer.players[var10];
               if (var12 != null && !var12.isDead()) {
                  for (int var16 = 0; var16 < var12.getWornItems().size(); var16++) {
                     InventoryItem var21 = var12.getWornItems().getItemByIndex(var16);
                     if (var21 instanceof AlarmClock && ((AlarmClock)var21).isDigital() && !((AlarmClock)var21).isAlarmSet()) {
                        ((AlarmClock)var21).setAlarmSet(true);
                        if (this.isAlarmSet) {
                           return true;
                        }
                     }

                     if (var21 instanceof AlarmClockClothing && ((AlarmClockClothing)var21).isDigital() && !((AlarmClockClothing)var21).isAlarmSet()) {
                        ((AlarmClockClothing)var21).setAlarmSet(true);
                        if (this.isAlarmSet) {
                           return true;
                        }
                     }
                  }

                  for (int var17 = 0; var17 < var12.getInventory().getItems().size(); var17++) {
                     InventoryItem var22 = (InventoryItem)var12.getInventory().getItems().get(var17);
                     if (var22 instanceof AlarmClock && ((AlarmClock)var22).isDigital() && !((AlarmClock)var22).isAlarmSet()) {
                        ((AlarmClock)var22).setAlarmSet(true);
                        if (this.isAlarmSet) {
                           return true;
                        }
                     }

                     if (var22 instanceof AlarmClockClothing && ((AlarmClockClothing)var22).isDigital() && !((AlarmClockClothing)var22).isAlarmSet()) {
                        ((AlarmClockClothing)var22).setAlarmSet(true);
                        if (this.isAlarmSet) {
                           return true;
                        }
                     }
                  }
               }
            }
         }

         return true;
      }
   }
}
