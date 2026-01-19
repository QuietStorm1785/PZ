package zombie.input;

import zombie.GameWindow;
import zombie.iso.Vector2;

public final class JoypadManager$Joypad {
   String guid;
   String name;
   int ID;
   int player = -1;
   int MovementAxisX = 0;
   boolean MovementAxisXFlipped = false;
   int MovementAxisY = 1;
   boolean MovementAxisYFlipped = false;
   float MovementAxisDeadZone = 0.0F;
   int AimingAxisX = 2;
   boolean AimingAxisXFlipped = false;
   int AimingAxisY = 3;
   boolean AimingAxisYFlipped = false;
   float AimingAxisDeadZone = 0.0F;
   int AButton = 0;
   int BButton = 1;
   int XButton = 2;
   int YButton = 3;
   int DPadUp = -1;
   int DPadDown = -1;
   int DPadLeft = -1;
   int DPadRight = -1;
   int BumperLeft = 4;
   int BumperRight = 5;
   int Back = 6;
   int Start = 7;
   int LeftStickButton = 9;
   int RightStickButton = 10;
   boolean TriggersFlipped = false;
   int TriggerLeft = 4;
   int TriggerRight = 5;
   boolean Disabled = false;
   boolean bConnected = true;
   long lastActivity;
   private static final Vector2 tempVec2 = new Vector2();

   public boolean isDownPressed() {
      return this.DPadDown != -1 ? GameWindow.GameInput.isButtonPressedD(this.DPadDown, this.ID) : GameWindow.GameInput.isControllerDownD(this.ID);
   }

   public boolean isUpPressed() {
      return this.DPadUp != -1 ? GameWindow.GameInput.isButtonPressedD(this.DPadUp, this.ID) : GameWindow.GameInput.isControllerUpD(this.ID);
   }

   public boolean isRightPressed() {
      return this.DPadRight != -1 ? GameWindow.GameInput.isButtonPressedD(this.DPadRight, this.ID) : GameWindow.GameInput.isControllerRightD(this.ID);
   }

   public boolean isLeftPressed() {
      return this.DPadLeft != -1 ? GameWindow.GameInput.isButtonPressedD(this.DPadLeft, this.ID) : GameWindow.GameInput.isControllerLeftD(this.ID);
   }

   public boolean isLBPressed() {
      return GameWindow.GameInput.isButtonPressedD(this.BumperLeft, this.ID);
   }

   public boolean isRBPressed() {
      return GameWindow.GameInput.isButtonPressedD(this.BumperRight, this.ID);
   }

   public boolean isL3Pressed() {
      return GameWindow.GameInput.isButtonPressedD(this.LeftStickButton, this.ID);
   }

   public boolean isR3Pressed() {
      return GameWindow.GameInput.isButtonPressedD(this.RightStickButton, this.ID);
   }

   public boolean isRTPressed() {
      int var1 = this.TriggerRight;
      if (GameWindow.GameInput.getAxisCount(this.ID) <= var1) {
         return this.isRBPressed();
      } else {
         return this.TriggersFlipped ? GameWindow.GameInput.getAxisValue(this.ID, var1) < -0.7F : GameWindow.GameInput.getAxisValue(this.ID, var1) > 0.7F;
      }
   }

   public boolean isLTPressed() {
      int var1 = this.TriggerLeft;
      if (GameWindow.GameInput.getAxisCount(this.ID) <= var1) {
         return this.isLBPressed();
      } else {
         return this.TriggersFlipped ? GameWindow.GameInput.getAxisValue(this.ID, var1) < -0.7F : GameWindow.GameInput.getAxisValue(this.ID, var1) > 0.7F;
      }
   }

   public boolean isAPressed() {
      return GameWindow.GameInput.isButtonPressedD(this.AButton, this.ID);
   }

   public boolean isBPressed() {
      return GameWindow.GameInput.isButtonPressedD(this.BButton, this.ID);
   }

   public boolean isXPressed() {
      return GameWindow.GameInput.isButtonPressedD(this.XButton, this.ID);
   }

   public boolean isYPressed() {
      return GameWindow.GameInput.isButtonPressedD(this.YButton, this.ID);
   }

   public boolean isButtonPressed(int var1) {
      return GameWindow.GameInput.isButtonPressedD(var1, this.ID);
   }

   public boolean wasButtonPressed(int var1) {
      return GameWindow.GameInput.wasButtonPressed(this.ID, var1);
   }

   public boolean isButtonStartPress(int var1) {
      return GameWindow.GameInput.isButtonStartPress(this.ID, var1);
   }

   public boolean isButtonReleasePress(int var1) {
      return GameWindow.GameInput.isButtonReleasePress(this.ID, var1);
   }

   public float getMovementAxisX() {
      if (GameWindow.GameInput.getAxisCount(this.ID) <= this.MovementAxisX) {
         return 0.0F;
      } else {
         this.MovementAxisDeadZone = GameWindow.GameInput.getController(this.ID).getDeadZone(this.MovementAxisX);
         float var1 = this.MovementAxisDeadZone;
         if (var1 > 0.0F && var1 < 1.0F) {
            float var2 = GameWindow.GameInput.getAxisValue(this.ID, this.MovementAxisX);
            float var3 = GameWindow.GameInput.getAxisValue(this.ID, this.MovementAxisY);
            Vector2 var4 = tempVec2.set(var2, var3);
            if (var4.getLength() < var1) {
               var4.set(0.0F, 0.0F);
            } else {
               var4.setLength((var4.getLength() - var1) / (1.0F - var1));
            }

            return this.MovementAxisXFlipped ? -var4.getX() : var4.getX();
         } else {
            return this.MovementAxisXFlipped
               ? -GameWindow.GameInput.getAxisValue(this.ID, this.MovementAxisX)
               : GameWindow.GameInput.getAxisValue(this.ID, this.MovementAxisX);
         }
      }
   }

   public float getMovementAxisY() {
      if (GameWindow.GameInput.getAxisCount(this.ID) <= this.MovementAxisY) {
         return 0.0F;
      } else {
         this.MovementAxisDeadZone = GameWindow.GameInput.getController(this.ID).getDeadZone(this.MovementAxisY);
         float var1 = this.MovementAxisDeadZone;
         if (var1 > 0.0F && var1 < 1.0F) {
            float var2 = GameWindow.GameInput.getAxisValue(this.ID, this.MovementAxisX);
            float var3 = GameWindow.GameInput.getAxisValue(this.ID, this.MovementAxisY);
            Vector2 var4 = tempVec2.set(var2, var3);
            if (var4.getLength() < var1) {
               var4.set(0.0F, 0.0F);
            } else {
               var4.setLength((var4.getLength() - var1) / (1.0F - var1));
            }

            return this.MovementAxisYFlipped ? -var4.getY() : var4.getY();
         } else {
            return this.MovementAxisYFlipped
               ? -GameWindow.GameInput.getAxisValue(this.ID, this.MovementAxisY)
               : GameWindow.GameInput.getAxisValue(this.ID, this.MovementAxisY);
         }
      }
   }

   public float getAimingAxisX() {
      if (GameWindow.GameInput.getAxisCount(this.ID) <= this.AimingAxisX) {
         return 0.0F;
      } else {
         this.AimingAxisDeadZone = GameWindow.GameInput.getController(this.ID).getDeadZone(this.AimingAxisX);
         float var1 = this.AimingAxisDeadZone;
         if (var1 > 0.0F && var1 < 1.0F) {
            float var2 = GameWindow.GameInput.getAxisValue(this.ID, this.AimingAxisX);
            float var3 = GameWindow.GameInput.getAxisValue(this.ID, this.AimingAxisY);
            Vector2 var4 = tempVec2.set(var2, var3);
            if (var4.getLength() < var1) {
               var4.set(0.0F, 0.0F);
            } else {
               var4.setLength((var4.getLength() - var1) / (1.0F - var1));
            }

            return this.AimingAxisXFlipped ? -var4.getX() : var4.getX();
         } else {
            return this.AimingAxisXFlipped
               ? -GameWindow.GameInput.getAxisValue(this.ID, this.AimingAxisX)
               : GameWindow.GameInput.getAxisValue(this.ID, this.AimingAxisX);
         }
      }
   }

   public float getAimingAxisY() {
      if (GameWindow.GameInput.getAxisCount(this.ID) <= this.AimingAxisY) {
         return 0.0F;
      } else {
         this.AimingAxisDeadZone = GameWindow.GameInput.getController(this.ID).getDeadZone(this.AimingAxisY);
         float var1 = this.AimingAxisDeadZone;
         if (var1 > 0.0F && var1 < 1.0F) {
            float var2 = GameWindow.GameInput.getAxisValue(this.ID, this.AimingAxisX);
            float var3 = GameWindow.GameInput.getAxisValue(this.ID, this.AimingAxisY);
            Vector2 var4 = tempVec2.set(var2, var3);
            if (var4.getLength() < var1) {
               var4.set(0.0F, 0.0F);
            } else {
               var4.setLength((var4.getLength() - var1) / (1.0F - var1));
            }

            return this.AimingAxisYFlipped ? -var4.getY() : var4.getY();
         } else {
            return this.AimingAxisYFlipped
               ? -GameWindow.GameInput.getAxisValue(this.ID, this.AimingAxisY)
               : GameWindow.GameInput.getAxisValue(this.ID, this.AimingAxisY);
         }
      }
   }

   public void onPressed(int var1) {
      this.lastActivity = System.currentTimeMillis();
   }

   public void onPressedAxis(int var1) {
      this.lastActivity = System.currentTimeMillis();
   }

   public void onPressedAxisNeg(int var1) {
      this.lastActivity = System.currentTimeMillis();
   }

   public void onPressedTrigger(int var1) {
      this.lastActivity = System.currentTimeMillis();
   }

   public void onPressedPov() {
      this.lastActivity = System.currentTimeMillis();
   }

   public float getDeadZone(int var1) {
      if (var1 >= 0 && var1 < GameWindow.GameInput.getAxisCount(this.ID)) {
         float var2 = GameWindow.GameInput.getController(this.ID).getDeadZone(var1);
         float var3 = 0.0F;
         if ((var1 == this.MovementAxisX || var1 == this.MovementAxisY) && this.MovementAxisDeadZone > 0.0F && this.MovementAxisDeadZone < 1.0F) {
            var3 = this.MovementAxisDeadZone;
         }

         if ((var1 == this.AimingAxisX || var1 == this.AimingAxisY) && this.AimingAxisDeadZone > 0.0F && this.AimingAxisDeadZone < 1.0F) {
            var3 = this.AimingAxisDeadZone;
         }

         return Math.max(var2, var3);
      } else {
         return 0.0F;
      }
   }

   public void setDeadZone(int var1, float var2) {
      if (var1 >= 0 && var1 < GameWindow.GameInput.getAxisCount(this.ID)) {
         GameWindow.GameInput.getController(this.ID).setDeadZone(var1, var2);
      }
   }

   public void setDeadZone(float var1) {
      for (int var2 = 0; var2 < GameWindow.GameInput.getAxisCount(this.ID); var2++) {
         GameWindow.GameInput.getController(this.ID).setDeadZone(var2, var1);
      }
   }

   public int getID() {
      return this.ID;
   }

   public boolean isDisabled() {
      return this.Disabled;
   }

   public int getAButton() {
      return this.AButton;
   }

   public int getBButton() {
      return this.BButton;
   }

   public int getXButton() {
      return this.XButton;
   }

   public int getYButton() {
      return this.YButton;
   }

   public int getLBumper() {
      return this.BumperLeft;
   }

   public int getRBumper() {
      return this.BumperRight;
   }

   public int getL3() {
      return this.LeftStickButton;
   }

   public int getR3() {
      return this.RightStickButton;
   }

   public int getBackButton() {
      return this.Back;
   }

   public int getStartButton() {
      return this.Start;
   }
}
