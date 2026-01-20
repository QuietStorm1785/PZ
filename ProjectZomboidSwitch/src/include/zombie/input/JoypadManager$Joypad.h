#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameWindow.h"
#include "zombie/iso/Vector2.h"

namespace zombie {
namespace input {


class JoypadManager {
public:
    std::string guid;
    std::string name;
    int ID;
    int player = -1;
    int MovementAxisX = 0;
    bool MovementAxisXFlipped = false;
    int MovementAxisY = 1;
    bool MovementAxisYFlipped = false;
    float MovementAxisDeadZone = 0.0F;
    int AimingAxisX = 2;
    bool AimingAxisXFlipped = false;
    int AimingAxisY = 3;
    bool AimingAxisYFlipped = false;
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
    bool TriggersFlipped = false;
    int TriggerLeft = 4;
    int TriggerRight = 5;
    bool Disabled = false;
    bool bConnected = true;
    long lastActivity;
    static const Vector2 tempVec2 = std::make_shared<Vector2>();

    bool isDownPressed() {
      return this.DPadDown != -1 ? GameWindow.GameInput.isButtonPressedD(this.DPadDown, this.ID) : GameWindow.GameInput.isControllerDownD(this.ID);
   }

    bool isUpPressed() {
      return this.DPadUp != -1 ? GameWindow.GameInput.isButtonPressedD(this.DPadUp, this.ID) : GameWindow.GameInput.isControllerUpD(this.ID);
   }

    bool isRightPressed() {
      return this.DPadRight != -1 ? GameWindow.GameInput.isButtonPressedD(this.DPadRight, this.ID) : GameWindow.GameInput.isControllerRightD(this.ID);
   }

    bool isLeftPressed() {
      return this.DPadLeft != -1 ? GameWindow.GameInput.isButtonPressedD(this.DPadLeft, this.ID) : GameWindow.GameInput.isControllerLeftD(this.ID);
   }

    bool isLBPressed() {
      return GameWindow.GameInput.isButtonPressedD(this.BumperLeft, this.ID);
   }

    bool isRBPressed() {
      return GameWindow.GameInput.isButtonPressedD(this.BumperRight, this.ID);
   }

    bool isL3Pressed() {
      return GameWindow.GameInput.isButtonPressedD(this.LeftStickButton, this.ID);
   }

    bool isR3Pressed() {
      return GameWindow.GameInput.isButtonPressedD(this.RightStickButton, this.ID);
   }

    bool isRTPressed() {
    int var1 = this.TriggerRight;
      if (GameWindow.GameInput.getAxisCount(this.ID) <= var1) {
         return this.isRBPressed();
      } else {
         return this.TriggersFlipped ? GameWindow.GameInput.getAxisValue(this.ID, var1) < -0.7F : GameWindow.GameInput.getAxisValue(this.ID, var1) > 0.7F;
      }
   }

    bool isLTPressed() {
    int var1 = this.TriggerLeft;
      if (GameWindow.GameInput.getAxisCount(this.ID) <= var1) {
         return this.isLBPressed();
      } else {
         return this.TriggersFlipped ? GameWindow.GameInput.getAxisValue(this.ID, var1) < -0.7F : GameWindow.GameInput.getAxisValue(this.ID, var1) > 0.7F;
      }
   }

    bool isAPressed() {
      return GameWindow.GameInput.isButtonPressedD(this.AButton, this.ID);
   }

    bool isBPressed() {
      return GameWindow.GameInput.isButtonPressedD(this.BButton, this.ID);
   }

    bool isXPressed() {
      return GameWindow.GameInput.isButtonPressedD(this.XButton, this.ID);
   }

    bool isYPressed() {
      return GameWindow.GameInput.isButtonPressedD(this.YButton, this.ID);
   }

    bool isButtonPressed(int var1) {
      return GameWindow.GameInput.isButtonPressedD(var1, this.ID);
   }

    bool wasButtonPressed(int var1) {
      return GameWindow.GameInput.wasButtonPressed(this.ID, var1);
   }

    bool isButtonStartPress(int var1) {
      return GameWindow.GameInput.isButtonStartPress(this.ID, var1);
   }

    bool isButtonReleasePress(int var1) {
      return GameWindow.GameInput.isButtonReleasePress(this.ID, var1);
   }

    float getMovementAxisX() {
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

    float getMovementAxisY() {
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

    float getAimingAxisX() {
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

    float getAimingAxisY() {
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

    void onPressed(int var1) {
      this.lastActivity = System.currentTimeMillis();
   }

    void onPressedAxis(int var1) {
      this.lastActivity = System.currentTimeMillis();
   }

    void onPressedAxisNeg(int var1) {
      this.lastActivity = System.currentTimeMillis();
   }

    void onPressedTrigger(int var1) {
      this.lastActivity = System.currentTimeMillis();
   }

    void onPressedPov() {
      this.lastActivity = System.currentTimeMillis();
   }

    float getDeadZone(int var1) {
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

    void setDeadZone(int var1, float var2) {
      if (var1 >= 0 && var1 < GameWindow.GameInput.getAxisCount(this.ID)) {
         GameWindow.GameInput.getController(this.ID).setDeadZone(var1, var2);
      }
   }

    void setDeadZone(float var1) {
      for (int var2 = 0; var2 < GameWindow.GameInput.getAxisCount(this.ID); var2++) {
         GameWindow.GameInput.getController(this.ID).setDeadZone(var2, var1);
      }
   }

    int getID() {
      return this.ID;
   }

    bool isDisabled() {
      return this.Disabled;
   }

    int getAButton() {
      return this.AButton;
   }

    int getBButton() {
      return this.BButton;
   }

    int getXButton() {
      return this.XButton;
   }

    int getYButton() {
      return this.YButton;
   }

    int getLBumper() {
      return this.BumperLeft;
   }

    int getRBumper() {
      return this.BumperRight;
   }

    int getL3() {
      return this.LeftStickButton;
   }

    int getR3() {
      return this.RightStickButton;
   }

    int getBackButton() {
      return this.Back;
   }

    int getStartButton() {
      return this.Start;
   }
}
} // namespace input
} // namespace zombie
