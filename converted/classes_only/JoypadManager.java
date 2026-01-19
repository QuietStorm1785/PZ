package zombie.input;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.HashSet;
import org.lwjglx.input.Controller;
import zombie.GameWindow;
import zombie.ZomboidFileSystem;
import zombie.Lua.LuaEventManager;
import zombie.characters.IsoPlayer;
import zombie.core.BoxedStaticValues;
import zombie.core.Core;
import zombie.core.logger.ExceptionLogger;
import zombie.debug.DebugLog;
import zombie.debug.DebugOptions;
import zombie.input.JoypadManager.Joypad;

public final class JoypadManager {
   public static final JoypadManager instance = new JoypadManager();
   public final Joypad[] Joypads = new Joypad[4];
   public final Joypad[] JoypadsController = new Joypad[16];
   public final ArrayList<Joypad> JoypadList = new ArrayList<>();
   public final HashSet<String> ActiveControllerGUIDs = new HashSet<>();
   private static final int VERSION_1 = 1;
   private static final int VERSION_2 = 2;
   private static final int VERSION_LATEST = 2;

   public Joypad addJoypad(int var1, String var2, String var3) {
      Joypad var4 = new Joypad();
      var4.ID = var1;
      var4.guid = var2;
      var4.name = var3;
      this.JoypadsController[var1] = var4;
      this.doControllerFile(var4);
      if (!var4.isDisabled() && this.ActiveControllerGUIDs.contains(var2)) {
         this.JoypadList.add(var4);
      }

      return var4;
   }

   private Joypad checkJoypad(int var1) {
      if (this.JoypadsController[var1] == null) {
         Controller var2 = GameWindow.GameInput.getController(var1);
         this.addJoypad(var1, var2.getGUID(), var2.getGamepadName());
      }

      return this.JoypadsController[var1];
   }

   private void doControllerFile(Joypad var1) {
      File var2 = new File(ZomboidFileSystem.instance.getCacheDirSub("joypads"));
      if (!var2.exists()) {
         var2.mkdir();
      }

      var2 = new File(ZomboidFileSystem.instance.getCacheDirSub("joypads" + File.separator + var1.guid + ".config"));

      try (
         FileReader var3 = new FileReader(var2.getAbsolutePath());
         BufferedReader var4 = new BufferedReader(var3);
      ) {
         System.out.println("reloading " + var2.getAbsolutePath());
         int var5 = -1;

         try {
            String var6 = "";

            while (var6 != null) {
               var6 = var4.readLine();
               if (var6 != null && var6.trim().length() != 0 && !var6.trim().startsWith("//")) {
                  String[] var7 = var6.split("=");
                  if (var7.length == 2) {
                     var7[0] = var7[0].trim();
                     var7[1] = var7[1].trim();
                     if (var7[0].equals("Version")) {
                        var5 = Integer.parseInt(var7[1]);
                        if (var5 < 1 || var5 > 2) {
                           DebugLog.General.warn("Unknown version %d in %s", new Object[]{var5, var2.getAbsolutePath()});
                           break;
                        }

                        if (var5 == 1) {
                           DebugLog.General.warn("Obsolete version %d in %s.  Using default values.", new Object[]{var5, var2.getAbsolutePath()});
                           break;
                        }
                     }

                     if (var5 == -1) {
                        DebugLog.General.warn("Ignoring %s=%s because Version is missing", new Object[]{var7[0], var7[1]});
                     } else if (var7[0].equals("MovementAxisX")) {
                        var1.MovementAxisX = Integer.parseInt(var7[1]);
                     } else if (var7[0].equals("MovementAxisXFlipped")) {
                        var1.MovementAxisXFlipped = var7[1].equals("true");
                     } else if (var7[0].equals("MovementAxisY")) {
                        var1.MovementAxisY = Integer.parseInt(var7[1]);
                     } else if (var7[0].equals("MovementAxisYFlipped")) {
                        var1.MovementAxisYFlipped = var7[1].equals("true");
                     } else if (var7[0].equals("MovementAxisDeadZone")) {
                        var1.MovementAxisDeadZone = Float.parseFloat(var7[1]);
                     } else if (var7[0].equals("AimingAxisX")) {
                        var1.AimingAxisX = Integer.parseInt(var7[1]);
                     } else if (var7[0].equals("AimingAxisXFlipped")) {
                        var1.AimingAxisXFlipped = var7[1].equals("true");
                     } else if (var7[0].equals("AimingAxisY")) {
                        var1.AimingAxisY = Integer.parseInt(var7[1]);
                     } else if (var7[0].equals("AimingAxisYFlipped")) {
                        var1.AimingAxisYFlipped = var7[1].equals("true");
                     } else if (var7[0].equals("AimingAxisDeadZone")) {
                        var1.AimingAxisDeadZone = Float.parseFloat(var7[1]);
                     } else if (var7[0].equals("AButton")) {
                        var1.AButton = Integer.parseInt(var7[1]);
                     } else if (var7[0].equals("BButton")) {
                        var1.BButton = Integer.parseInt(var7[1]);
                     } else if (var7[0].equals("XButton")) {
                        var1.XButton = Integer.parseInt(var7[1]);
                     } else if (var7[0].equals("YButton")) {
                        var1.YButton = Integer.parseInt(var7[1]);
                     } else if (var7[0].equals("LBumper")) {
                        var1.BumperLeft = Integer.parseInt(var7[1]);
                     } else if (var7[0].equals("RBumper")) {
                        var1.BumperRight = Integer.parseInt(var7[1]);
                     } else if (var7[0].equals("L3")) {
                        var1.LeftStickButton = Integer.parseInt(var7[1]);
                     } else if (var7[0].equals("R3")) {
                        var1.RightStickButton = Integer.parseInt(var7[1]);
                     } else if (var7[0].equals("Back")) {
                        var1.Back = Integer.parseInt(var7[1]);
                     } else if (var7[0].equals("Start")) {
                        var1.Start = Integer.parseInt(var7[1]);
                     } else if (var7[0].equals("DPadUp")) {
                        var1.DPadUp = Integer.parseInt(var7[1]);
                     } else if (var7[0].equals("DPadDown")) {
                        var1.DPadDown = Integer.parseInt(var7[1]);
                     } else if (var7[0].equals("DPadLeft")) {
                        var1.DPadLeft = Integer.parseInt(var7[1]);
                     } else if (var7[0].equals("DPadRight")) {
                        var1.DPadRight = Integer.parseInt(var7[1]);
                     } else if (var7[0].equals("TriggersFlipped")) {
                        var1.TriggersFlipped = var7[1].equals("true");
                     } else if (var7[0].equals("TriggerLeft")) {
                        var1.TriggerLeft = Integer.parseInt(var7[1]);
                     } else if (var7[0].equals("TriggerRight")) {
                        var1.TriggerRight = Integer.parseInt(var7[1]);
                     } else if (var7[0].equals("Disabled")) {
                        var1.Disabled = var7[1].equals("true");
                     } else if (var7[0].equals("Sensitivity")) {
                        var1.setDeadZone(Float.parseFloat(var7[1]));
                     }
                  }
               }
            }
         } catch (Exception var11) {
            ExceptionLogger.logException(var11);
         }
      } catch (FileNotFoundException var14) {
         if (!this.ActiveControllerGUIDs.contains(var1.guid)) {
            this.ActiveControllerGUIDs.add(var1.guid);

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

   private void saveFile(Joypad var1) {
      File var2 = new File(ZomboidFileSystem.instance.getCacheDir() + File.separator + "joypads");
      if (!var2.exists()) {
         var2.mkdir();
      }

      var2 = new File(ZomboidFileSystem.instance.getCacheDirSub("joypads" + File.separator + var1.guid + ".config"));

      try (
         FileWriter var3 = new FileWriter(var2.getAbsolutePath());
         BufferedWriter var4 = new BufferedWriter(var3);
      ) {
         String var5 = System.getProperty("line.separator");
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

   public void reloadControllerFiles() {
      for (int var1 = 0; var1 < GameWindow.GameInput.getControllerCount(); var1++) {
         Controller var2 = GameWindow.GameInput.getController(var1);
         if (var2 != null) {
            if (this.JoypadsController[var1] == null) {
               this.addJoypad(var1, var2.getGUID(), var2.getGamepadName());
            } else {
               this.doControllerFile(this.JoypadsController[var1]);
            }
         }
      }
   }

   public void assignJoypad(int var1, int var2) {
      this.checkJoypad(var1);
      this.Joypads[var2] = this.JoypadsController[var1];
      this.Joypads[var2].player = var2;
   }

   public Joypad getFromPlayer(int var1) {
      return this.Joypads[var1];
   }

   public Joypad getFromControllerID(int var1) {
      return this.JoypadsController[var1];
   }

   public void onPressed(int var1, int var2) {
      this.checkJoypad(var1);
      this.JoypadsController[var1].onPressed(var2);
   }

   public boolean isDownPressed(int var1) {
      this.checkJoypad(var1);
      return this.JoypadsController[var1].isDownPressed();
   }

   public boolean isUpPressed(int var1) {
      this.checkJoypad(var1);
      return this.JoypadsController[var1].isUpPressed();
   }

   public boolean isRightPressed(int var1) {
      this.checkJoypad(var1);
      return this.JoypadsController[var1].isRightPressed();
   }

   public boolean isLeftPressed(int var1) {
      this.checkJoypad(var1);
      return this.JoypadsController[var1].isLeftPressed();
   }

   public boolean isLBPressed(int var1) {
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

   public boolean isRBPressed(int var1) {
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

   public boolean isL3Pressed(int var1) {
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

   public boolean isR3Pressed(int var1) {
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

   public boolean isRTPressed(int var1) {
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

   public boolean isLTPressed(int var1) {
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

   public boolean isAPressed(int var1) {
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

   public boolean isBPressed(int var1) {
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

   public boolean isXPressed(int var1) {
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

   public boolean isYPressed(int var1) {
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

   public boolean isButtonStartPress(int var1, int var2) {
      Joypad var3 = this.checkJoypad(var1);
      return var3.isButtonStartPress(var2);
   }

   public boolean isButtonReleasePress(int var1, int var2) {
      Joypad var3 = this.checkJoypad(var1);
      return var3.isButtonReleasePress(var2);
   }

   public boolean isAButtonStartPress(int var1) {
      Joypad var2 = this.checkJoypad(var1);
      return this.isButtonStartPress(var1, var2.getAButton());
   }

   public boolean isBButtonStartPress(int var1) {
      Joypad var2 = this.checkJoypad(var1);
      return var2.isButtonStartPress(var2.getBButton());
   }

   public boolean isXButtonStartPress(int var1) {
      Joypad var2 = this.checkJoypad(var1);
      return var2.isButtonStartPress(var2.getXButton());
   }

   public boolean isYButtonStartPress(int var1) {
      Joypad var2 = this.checkJoypad(var1);
      return var2.isButtonStartPress(var2.getYButton());
   }

   public boolean isAButtonReleasePress(int var1) {
      Joypad var2 = this.checkJoypad(var1);
      return var2.isButtonReleasePress(var2.getAButton());
   }

   public boolean isBButtonReleasePress(int var1) {
      Joypad var2 = this.checkJoypad(var1);
      return var2.isButtonReleasePress(var2.getBButton());
   }

   public boolean isXButtonReleasePress(int var1) {
      Joypad var2 = this.checkJoypad(var1);
      return var2.isButtonReleasePress(var2.getXButton());
   }

   public boolean isYButtonReleasePress(int var1) {
      Joypad var2 = this.checkJoypad(var1);
      return var2.isButtonReleasePress(var2.getYButton());
   }

   public float getMovementAxisX(int var1) {
      this.checkJoypad(var1);
      return this.JoypadsController[var1].getMovementAxisX();
   }

   public float getMovementAxisY(int var1) {
      this.checkJoypad(var1);
      return this.JoypadsController[var1].getMovementAxisY();
   }

   public float getAimingAxisX(int var1) {
      this.checkJoypad(var1);
      return this.JoypadsController[var1].getAimingAxisX();
   }

   public float getAimingAxisY(int var1) {
      this.checkJoypad(var1);
      return this.JoypadsController[var1].getAimingAxisY();
   }

   public void onPressedAxis(int var1, int var2) {
      this.checkJoypad(var1);
      this.JoypadsController[var1].onPressedAxis(var2);
   }

   public void onPressedAxisNeg(int var1, int var2) {
      this.checkJoypad(var1);
      this.JoypadsController[var1].onPressedAxisNeg(var2);
   }

   public void onPressedTrigger(int var1, int var2) {
      this.checkJoypad(var1);
      this.JoypadsController[var1].onPressedTrigger(var2);
   }

   public void onPressedPov(int var1) {
      this.checkJoypad(var1);
      this.JoypadsController[var1].onPressedPov();
   }

   public float getDeadZone(int var1, int var2) {
      this.checkJoypad(var1);
      return this.JoypadsController[var1].getDeadZone(var2);
   }

   public void setDeadZone(int var1, int var2, float var3) {
      this.checkJoypad(var1);
      this.JoypadsController[var1].setDeadZone(var2, var3);
   }

   public void saveControllerSettings(int var1) {
      this.checkJoypad(var1);
      this.saveFile(this.JoypadsController[var1]);
   }

   public long getLastActivity(int var1) {
      return this.JoypadsController[var1] == null ? 0L : this.JoypadsController[var1].lastActivity;
   }

   public void setControllerActive(String var1, boolean var2) {
      if (var2) {
         this.ActiveControllerGUIDs.add(var1);
      } else {
         this.ActiveControllerGUIDs.remove(var1);
      }

      this.syncActiveControllers();
   }

   public void syncActiveControllers() {
      this.JoypadList.clear();

      for (int var1 = 0; var1 < this.JoypadsController.length; var1++) {
         Joypad var2 = this.JoypadsController[var1];
         if (var2 != null && !var2.isDisabled() && this.ActiveControllerGUIDs.contains(var2.guid)) {
            this.JoypadList.add(var2);
         }
      }
   }

   public boolean isJoypadConnected(int var1) {
      if (var1 >= 0 && var1 < 16) {
         assert Thread.currentThread() == GameWindow.GameThread;

         return GameWindow.GameInput.getController(var1) != null;
      } else {
         return false;
      }
   }

   public void onControllerConnected(Controller var1) {
      Joypad var2 = this.JoypadsController[var1.getID()];
      if (var2 != null) {
         LuaEventManager.triggerEvent("OnJoypadBeforeReactivate", BoxedStaticValues.toDouble(var2.getID()));
         var2.bConnected = true;
         LuaEventManager.triggerEvent("OnJoypadReactivate", BoxedStaticValues.toDouble(var2.getID()));
      }
   }

   public void onControllerDisconnected(Controller var1) {
      Joypad var2 = this.JoypadsController[var1.getID()];
      if (var2 != null) {
         LuaEventManager.triggerEvent("OnJoypadBeforeDeactivate", BoxedStaticValues.toDouble(var2.getID()));
         var2.bConnected = false;
         LuaEventManager.triggerEvent("OnJoypadDeactivate", BoxedStaticValues.toDouble(var2.getID()));
      }
   }

   public void revertToKeyboardAndMouse() {
      for (int var1 = 0; var1 < this.JoypadList.size(); var1++) {
         Joypad var2 = this.JoypadList.get(var1);
         if (var2.player == 0) {
            if (GameWindow.ActivatedJoyPad == var2) {
               GameWindow.ActivatedJoyPad = null;
            }

            IsoPlayer var3 = IsoPlayer.players[0];
            if (var3 != null) {
               var3.JoypadBind = -1;
            }

            this.JoypadsController[var2.getID()] = null;
            this.Joypads[0] = null;
            this.JoypadList.remove(var1);
            break;
         }
      }
   }

   public void renderUI() {
      assert Thread.currentThread() == GameWindow.GameThread;

      if (DebugOptions.instance.JoypadRenderUI.getValue()) {
         if (!GameWindow.DrawReloadingLua) {
            LuaEventManager.triggerEvent("OnJoypadRenderUI");
         }
      }
   }

   public void Reset() {
      for (int var1 = 0; var1 < this.Joypads.length; var1++) {
         this.Joypads[var1] = null;
      }
   }
}
