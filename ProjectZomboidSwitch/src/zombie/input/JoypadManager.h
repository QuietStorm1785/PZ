
// SDL2-based JoypadManager for handling multiple controllers
#pragma once
#include <vector>
#include <string>
#include <unordered_set>
#include <cstdint>
#include <SDL2/SDL.h>

class JoypadManager {
public:
   JoypadManager();
   ~JoypadManager();
   void update();
   int getNumJoypads() const;
   SDL_GameController* getJoypad(int idx) const;
   std::string getJoypadName(int idx) const;
   void handleEvent(const SDL_Event& event);

private:
   static constexpr int MAX_JOYPADS = 16;
   SDL_GameController* joypads_[MAX_JOYPADS] = {nullptr};
   int numJoypads_ = 0;
   void openControllers();
   void closeControllers();
};
};
                        var1.MovementAxisX = int.parseInt(var7[1]);
                     } else if (var7[0] == "MovementAxisXFlipped")) {
                        var1.MovementAxisXFlipped = var7[1] == "true");
                     } else if (var7[0] == "MovementAxisY")) {
                        var1.MovementAxisY = int.parseInt(var7[1]);
                     } else if (var7[0] == "MovementAxisYFlipped")) {
                        var1.MovementAxisYFlipped = var7[1] == "true");
                     } else if (var7[0] == "MovementAxisDeadZone")) {
                        var1.MovementAxisDeadZone = float.parseFloat(var7[1]);
                     } else if (var7[0] == "AimingAxisX")) {
                        var1.AimingAxisX = int.parseInt(var7[1]);
                     } else if (var7[0] == "AimingAxisXFlipped")) {
                        var1.AimingAxisXFlipped = var7[1] == "true");
                     } else if (var7[0] == "AimingAxisY")) {
                        var1.AimingAxisY = int.parseInt(var7[1]);
                     } else if (var7[0] == "AimingAxisYFlipped")) {
                        var1.AimingAxisYFlipped = var7[1] == "true");
                     } else if (var7[0] == "AimingAxisDeadZone")) {
                        var1.AimingAxisDeadZone = float.parseFloat(var7[1]);
                     } else if (var7[0] == "AButton")) {
                        var1.AButton = int.parseInt(var7[1]);
                     } else if (var7[0] == "BButton")) {
                        var1.BButton = int.parseInt(var7[1]);
                     } else if (var7[0] == "XButton")) {
                        var1.XButton = int.parseInt(var7[1]);
                     } else if (var7[0] == "YButton")) {
                        var1.YButton = int.parseInt(var7[1]);
                     } else if (var7[0] == "LBumper")) {
                        var1.BumperLeft = int.parseInt(var7[1]);
                     } else if (var7[0] == "RBumper")) {
                        var1.BumperRight = int.parseInt(var7[1]);
                     } else if (var7[0] == "L3")) {
                        var1.LeftStickButton = int.parseInt(var7[1]);
                     } else if (var7[0] == "R3")) {
                        var1.RightStickButton = int.parseInt(var7[1]);
                     } else if (var7[0] == "Back")) {
                        var1.Back = int.parseInt(var7[1]);
                     } else if (var7[0] == "Start")) {
                        var1.Start = int.parseInt(var7[1]);
                     } else if (var7[0] == "DPadUp")) {
                        var1.DPadUp = int.parseInt(var7[1]);
                     } else if (var7[0] == "DPadDown")) {
                        var1.DPadDown = int.parseInt(var7[1]);
                     } else if (var7[0] == "DPadLeft")) {
                        var1.DPadLeft = int.parseInt(var7[1]);
                     } else if (var7[0] == "DPadRight")) {
                        var1.DPadRight = int.parseInt(var7[1]);
                     } else if (var7[0] == "TriggersFlipped")) {
                        var1.TriggersFlipped = var7[1] == "true");
                     } else if (var7[0] == "TriggerLeft")) {
                        var1.TriggerLeft = int.parseInt(var7[1]);
                     } else if (var7[0] == "TriggerRight")) {
                        var1.TriggerRight = int.parseInt(var7[1]);
                     } else if (var7[0] == "Disabled")) {
                        var1.Disabled = var7[1] == "true");
                     } else if (var7[0] == "Sensitivity")) {
                        var1.setDeadZone(float.parseFloat(var7[1]));
                     }
                  }
               }
            }
         } catch (Exception var11) {
            ExceptionLogger.logException(var11);
         }
      } catch (FileNotFoundException var14) {
         if (!this.ActiveControllerGUIDs.contains(var1.guid)) {
            this.ActiveControllerGUIDs.push_back(var1.guid);

            try {
               Core.getInstance().saveOptions();
            } catch (Exception var8) {
               ExceptionLogger.logException(var8);
            }
         }
      } catch (IOException var15) {
         ExceptionLogger.logException(var15);
      }

      this.saveFile(var1);
   }

    void saveFile(Joypad var1) {
    File var2 = std::make_shared<File>(ZomboidFileSystem.instance.getCacheDir() + File.separator + "joypads");
      if (!var2.exists()) {
         var2.mkdir();
      }

      var2 = std::make_shared<File>(ZomboidFileSystem.instance.getCacheDirSub("joypads" + File.separator + var1.guid + ".config"));

      try (
    FileWriter var3 = std::make_shared<FileWriter>(var2.getAbsolutePath());
    BufferedWriter var4 = std::make_shared<BufferedWriter>(var3);
      ) {
    std::string var5 = System.getProperty("line.separator");
         var4.write("Version=2" + var5);
         var4.write("Name=" + var1.name + var5);
         var4.write("MovementAxisX=" + var1.MovementAxisX + var5);
         var4.write("MovementAxisXFlipped=" + var1.MovementAxisXFlipped + var5);
         var4.write("MovementAxisY=" + var1.MovementAxisY + var5);
         var4.write("MovementAxisYFlipped=" + var1.MovementAxisYFlipped + var5);
         var4.write("// Set the dead zone to the smallest number between 0.0 and 1.0." + var5);
         var4.write("// This is to fix \"loose sticks\"." + var5);
         var4.write("MovementAxisDeadZone=" + var1.MovementAxisDeadZone + var5);
         var4.write("AimingAxisX=" + var1.AimingAxisX + var5);
         var4.write("AimingAxisXFlipped=" + var1.AimingAxisXFlipped + var5);
         var4.write("AimingAxisY=" + var1.AimingAxisY + var5);
         var4.write("AimingAxisYFlipped=" + var1.AimingAxisYFlipped + var5);
         var4.write("AimingAxisDeadZone=" + var1.AimingAxisDeadZone + var5);
         var4.write("AButton=" + var1.AButton + var5);
         var4.write("BButton=" + var1.BButton + var5);
         var4.write("XButton=" + var1.XButton + var5);
         var4.write("YButton=" + var1.YButton + var5);
         var4.write("LBumper=" + var1.BumperLeft + var5);
         var4.write("RBumper=" + var1.BumperRight + var5);
         var4.write("L3=" + var1.LeftStickButton + var5);
         var4.write("R3=" + var1.RightStickButton + var5);
         var4.write("Back=" + var1.Back + var5);
         var4.write("Start=" + var1.Start + var5);
         var4.write("// Normally the D-pad is treated as a single axis (the POV Hat), and these should be -1." + var5);
         var4.write("// If your D-pad is actually 4 separate buttons, set the button numbers here." + var5);
         var4.write("DPadUp=" + var1.DPadUp + var5);
         var4.write("DPadDown=" + var1.DPadDown + var5);
         var4.write("DPadLeft=" + var1.DPadLeft + var5);
         var4.write("DPadRight=" + var1.DPadRight + var5);
         var4.write("TriggersFlipped=" + var1.TriggersFlipped + var5);
         var4.write("// If your triggers are buttons, set the button numbers here." + var5);
         var4.write("// If these are set to something other than -1, then Triggers= is ignored." + var5);
         var4.write("TriggerLeft=" + var1.TriggerLeft + var5);
         var4.write("TriggerRight=" + var1.TriggerRight + var5);
         var4.write("Disabled=" + var1.Disabled + var5);
         var4.write("Sensitivity=" + var1.getDeadZone(0) + var5);
      } catch (IOException var11) {
         ExceptionLogger.logException(var11);
      }
   }

    void reloadControllerFiles() {
      for (int var1 = 0; var1 < GameWindow.GameInput.getControllerCount(); var1++) {
    Controller var2 = GameWindow.GameInput.getController(var1);
         if (var2 != nullptr) {
            if (this.JoypadsController[var1] == nullptr) {
               this.addJoypad(var1, var2.getGUID(), var2.getGamepadName());
            } else {
               this.doControllerFile(this.JoypadsController[var1]);
            }
         }
      }
   }

    void assignJoypad(int var1, int var2) {
      this.checkJoypad(var1);
      this.Joypads[var2] = this.JoypadsController[var1];
      this.Joypads[var2].player = var2;
   }

    Joypad getFromPlayer(int var1) {
      return this.Joypads[var1];
   }

    Joypad getFromControllerID(int var1) {
      return this.JoypadsController[var1];
   }

    void onPressed(int var1, int var2) {
      this.checkJoypad(var1);
      this.JoypadsController[var1].onPressed(var2);
   }

    bool isDownPressed(int var1) {
      this.checkJoypad(var1);
      return this.JoypadsController[var1].isDownPressed();
   }

    bool isUpPressed(int var1) {
      this.checkJoypad(var1);
      return this.JoypadsController[var1].isUpPressed();
   }

    bool isRightPressed(int var1) {
      this.checkJoypad(var1);
      return this.JoypadsController[var1].isRightPressed();
   }

    bool isLeftPressed(int var1) {
      this.checkJoypad(var1);
      return this.JoypadsController[var1].isLeftPressed();
   }

    bool isLBPressed(int var1) {
      if (var1 < 0) {
         for (int var2 = 0; var2 < this.JoypadList.size(); var2++) {
            if (this.JoypadList.get(var2).isLBPressed()) {
    return true;
            }
         }

    return false;
      } else {
         this.checkJoypad(var1);
         return this.JoypadsController[var1].isLBPressed();
      }
   }

    bool isRBPressed(int var1) {
      if (var1 < 0) {
         for (int var2 = 0; var2 < this.JoypadList.size(); var2++) {
            if (this.JoypadList.get(var2).isRBPressed()) {
    return true;
            }
         }

    return false;
      } else {
         this.checkJoypad(var1);
         return this.JoypadsController[var1].isRBPressed();
      }
   }

    bool isL3Pressed(int var1) {
      if (var1 < 0) {
         for (int var2 = 0; var2 < this.JoypadList.size(); var2++) {
            if (this.JoypadList.get(var2).isL3Pressed()) {
    return true;
            }
         }

    return false;
      } else {
         this.checkJoypad(var1);
         return this.JoypadsController[var1].isL3Pressed();
      }
   }

    bool isR3Pressed(int var1) {
      if (var1 < 0) {
         for (int var2 = 0; var2 < this.JoypadList.size(); var2++) {
            if (this.JoypadList.get(var2).isR3Pressed()) {
    return true;
            }
         }

    return false;
      } else {
         this.checkJoypad(var1);
         return this.JoypadsController[var1].isR3Pressed();
      }
   }

    bool isRTPressed(int var1) {
      if (var1 < 0) {
         for (int var2 = 0; var2 < this.JoypadList.size(); var2++) {
            if (this.JoypadList.get(var2).isRTPressed()) {
    return true;
            }
         }

    return false;
      } else {
         this.checkJoypad(var1);
         return this.JoypadsController[var1].isRTPressed();
      }
   }

    bool isLTPressed(int var1) {
      if (var1 < 0) {
         for (int var2 = 0; var2 < this.JoypadList.size(); var2++) {
            if (this.JoypadList.get(var2).isLTPressed()) {
    return true;
            }
         }

    return false;
      } else {
         this.checkJoypad(var1);
         return this.JoypadsController[var1].isLTPressed();
      }
   }

    bool isAPressed(int var1) {
      if (var1 < 0) {
         for (int var2 = 0; var2 < this.JoypadList.size(); var2++) {
            if (this.JoypadList.get(var2).isAPressed()) {
    return true;
            }
         }

    return false;
      } else {
         this.checkJoypad(var1);
         return this.JoypadsController[var1].isAPressed();
      }
   }

    bool isBPressed(int var1) {
      if (var1 < 0) {
         for (int var2 = 0; var2 < this.JoypadList.size(); var2++) {
            if (this.JoypadList.get(var2).isBPressed()) {
    return true;
            }
         }

    return false;
      } else {
         this.checkJoypad(var1);
         return this.JoypadsController[var1].isBPressed();
      }
   }

    bool isXPressed(int var1) {
      if (var1 < 0) {
         for (int var2 = 0; var2 < this.JoypadList.size(); var2++) {
            if (this.JoypadList.get(var2).isXPressed()) {
    return true;
            }
         }

    return false;
      } else {
         this.checkJoypad(var1);
         return this.JoypadsController[var1].isXPressed();
      }
   }

    bool isYPressed(int var1) {
      if (var1 < 0) {
         for (int var2 = 0; var2 < this.JoypadList.size(); var2++) {
            if (this.JoypadList.get(var2).isYPressed()) {
    return true;
            }
         }

    return false;
      } else {
         this.checkJoypad(var1);
         return this.JoypadsController[var1].isYPressed();
      }
   }

    bool isButtonStartPress(int var1, int var2) {
    Joypad var3 = this.checkJoypad(var1);
      return var3.isButtonStartPress(var2);
   }

    bool isButtonReleasePress(int var1, int var2) {
    Joypad var3 = this.checkJoypad(var1);
      return var3.isButtonReleasePress(var2);
   }

    bool isAButtonStartPress(int var1) {
    Joypad var2 = this.checkJoypad(var1);
      return this.isButtonStartPress(var1, var2.getAButton());
   }

    bool isBButtonStartPress(int var1) {
    Joypad var2 = this.checkJoypad(var1);
      return var2.isButtonStartPress(var2.getBButton());
   }

    bool isXButtonStartPress(int var1) {
    Joypad var2 = this.checkJoypad(var1);
      return var2.isButtonStartPress(var2.getXButton());
   }

    bool isYButtonStartPress(int var1) {
    Joypad var2 = this.checkJoypad(var1);
      return var2.isButtonStartPress(var2.getYButton());
   }

    bool isAButtonReleasePress(int var1) {
    Joypad var2 = this.checkJoypad(var1);
      return var2.isButtonReleasePress(var2.getAButton());
   }

    bool isBButtonReleasePress(int var1) {
    Joypad var2 = this.checkJoypad(var1);
      return var2.isButtonReleasePress(var2.getBButton());
   }

    bool isXButtonReleasePress(int var1) {
    Joypad var2 = this.checkJoypad(var1);
      return var2.isButtonReleasePress(var2.getXButton());
   }

    bool isYButtonReleasePress(int var1) {
    Joypad var2 = this.checkJoypad(var1);
      return var2.isButtonReleasePress(var2.getYButton());
   }

    float getMovementAxisX(int var1) {
      this.checkJoypad(var1);
      return this.JoypadsController[var1].getMovementAxisX();
   }

    float getMovementAxisY(int var1) {
      this.checkJoypad(var1);
      return this.JoypadsController[var1].getMovementAxisY();
   }

    float getAimingAxisX(int var1) {
      this.checkJoypad(var1);
      return this.JoypadsController[var1].getAimingAxisX();
   }

    float getAimingAxisY(int var1) {
      this.checkJoypad(var1);
      return this.JoypadsController[var1].getAimingAxisY();
   }

    void onPressedAxis(int var1, int var2) {
      this.checkJoypad(var1);
      this.JoypadsController[var1].onPressedAxis(var2);
   }

    void onPressedAxisNeg(int var1, int var2) {
      this.checkJoypad(var1);
      this.JoypadsController[var1].onPressedAxisNeg(var2);
   }

    void onPressedTrigger(int var1, int var2) {
      this.checkJoypad(var1);
      this.JoypadsController[var1].onPressedTrigger(var2);
   }

    void onPressedPov(int var1) {
      this.checkJoypad(var1);
      this.JoypadsController[var1].onPressedPov();
   }

    float getDeadZone(int var1, int var2) {
      this.checkJoypad(var1);
      return this.JoypadsController[var1].getDeadZone(var2);
   }

    void setDeadZone(int var1, int var2, float var3) {
      this.checkJoypad(var1);
      this.JoypadsController[var1].setDeadZone(var2, var3);
   }

    void saveControllerSettings(int var1) {
      this.checkJoypad(var1);
      this.saveFile(this.JoypadsController[var1]);
   }

    long getLastActivity(int var1) {
      return this.JoypadsController[var1] == nullptr ? 0L : this.JoypadsController[var1].lastActivity;
   }

    void setControllerActive(const std::string& var1, bool var2) {
      if (var2) {
         this.ActiveControllerGUIDs.push_back(var1);
      } else {
         this.ActiveControllerGUIDs.remove(var1);
      }

      this.syncActiveControllers();
   }

    void syncActiveControllers() {
      this.JoypadList.clear();

      for (int var1 = 0; var1 < this.JoypadsController.length; var1++) {
    Joypad var2 = this.JoypadsController[var1];
         if (var2 != nullptr && !var2.isDisabled() && this.ActiveControllerGUIDs.contains(var2.guid)) {
            this.JoypadList.push_back(var2);
         }
      }
   }

    bool isJoypadConnected(int var1) {
      if (var1 >= 0 && var1 < 16) {
         assert Thread.currentThread() == GameWindow.GameThread;

         return GameWindow.GameInput.getController(var1) != nullptr;
      } else {
    return false;
      }
   }

    void onControllerConnected(Controller var1) {
    Joypad var2 = this.JoypadsController[var1.getID()];
      if (var2 != nullptr) {
         LuaEventManager.triggerEvent("OnJoypadBeforeReactivate", BoxedStaticValues.toDouble(var2.getID()));
         var2.bConnected = true;
         LuaEventManager.triggerEvent("OnJoypadReactivate", BoxedStaticValues.toDouble(var2.getID()));
      }
   }

    void onControllerDisconnected(Controller var1) {
    Joypad var2 = this.JoypadsController[var1.getID()];
      if (var2 != nullptr) {
         LuaEventManager.triggerEvent("OnJoypadBeforeDeactivate", BoxedStaticValues.toDouble(var2.getID()));
         var2.bConnected = false;
         LuaEventManager.triggerEvent("OnJoypadDeactivate", BoxedStaticValues.toDouble(var2.getID()));
      }
   }

    void revertToKeyboardAndMouse() {
      for (int var1 = 0; var1 < this.JoypadList.size(); var1++) {
    Joypad var2 = this.JoypadList.get(var1);
         if (var2.player == 0) {
            if (GameWindow.ActivatedJoyPad == var2) {
               GameWindow.ActivatedJoyPad = nullptr;
            }

    IsoPlayer var3 = IsoPlayer.players[0];
            if (var3 != nullptr) {
               var3.JoypadBind = -1;
            }

            this.JoypadsController[var2.getID()] = nullptr;
            this.Joypads[0] = nullptr;
            this.JoypadList.remove(var1);
            break;
         }
      }
   }

    void renderUI() {
      assert Thread.currentThread() == GameWindow.GameThread;

      if (DebugOptions.instance.JoypadRenderUI.getValue()) {
         if (!GameWindow.DrawReloadingLua) {
            LuaEventManager.triggerEvent("OnJoypadRenderUI");
         }
      }
   }

    void Reset() {
      for (int var1 = 0; var1 < this.Joypads.length; var1++) {
         this.Joypads[var1] = nullptr;
      }
   }
}
} // namespace input
} // namespace zombie
