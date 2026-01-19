package zombie.gameStates;

import java.io.File;
import zombie.GameTime;
import zombie.GameWindow;
import zombie.ZomboidFileSystem;
import zombie.Lua.LuaEventManager;
import zombie.characters.IsoPlayer;
import zombie.chat.ChatManager;
import zombie.chat.ChatUtility;
import zombie.core.logger.ExceptionLogger;
import zombie.debug.DebugOptions;
import zombie.globalObjects.CGlobalObjects;
import zombie.globalObjects.SGlobalObjects;
import zombie.iso.IsoObjectPicker;
import zombie.iso.IsoWorld;
import zombie.iso.weather.ClimateManager;
import zombie.network.GameClient;
import zombie.network.GameServer;
import zombie.ui.TutorialManager;
import zombie.ui.UIManager;
import zombie.vehicles.BaseVehicle;

class GameLoadingState$1 implements Runnable {
   GameLoadingState$1(GameLoadingState var1) {
      this.this$0 = var1;
   }

   @Override
   public void run() {
      try {
         this.runInner();
      } catch (Throwable var2) {
         GameLoadingState.unexpectedError = true;
         ExceptionLogger.logException(var2);
      }
   }

   private void runInner() throws Exception {
      this.this$0.bWaitForAssetLoadingToFinish1 = true;
      synchronized (this.this$0.assetLock1) {
         while (this.this$0.bWaitForAssetLoadingToFinish1) {
            try {
               this.this$0.assetLock1.wait();
            } catch (InterruptedException var8) {
            }
         }
      }

      boolean var11 = new File(ZomboidFileSystem.instance.getGameModeCacheDir() + File.separator).mkdir();
      BaseVehicle.LoadAllVehicleTextures();
      if (GameClient.bClient) {
         GameClient.instance.GameLoadingRequestData();
      }

      TutorialManager.instance = new TutorialManager();
      GameTime.setInstance(new GameTime());
      ClimateManager.setInstance(new ClimateManager());
      IsoWorld.instance = new IsoWorld();
      DebugOptions.testThreadCrash(0);
      IsoWorld.instance.init();
      if (GameWindow.bServerDisconnected) {
         GameLoadingState.bDone = true;
      } else if (!GameLoadingState.playerWrongIP) {
         if (!GameLoadingState.build23Stop) {
            LuaEventManager.triggerEvent("OnGameTimeLoaded");
            SGlobalObjects.initSystems();
            CGlobalObjects.initSystems();
            IsoObjectPicker.Instance.Init();
            TutorialManager.instance.init();
            TutorialManager.instance.CreateQuests();
            File var2 = ZomboidFileSystem.instance.getFileInCurrentSave("map_t.bin");
            if (var2.exists()) {
            }

            if (!GameServer.bServer) {
               var2 = ZomboidFileSystem.instance.getFileInCurrentSave("map_ver.bin");
               boolean var3 = !var2.exists();
               if (var3 || IsoWorld.SavedWorldVersion != 195) {
                  if (!var3 && IsoWorld.SavedWorldVersion != 195) {
                     GameLoadingState.GameLoadingString = "Saving converted world.";
                  }

                  try {
                     GameWindow.save(true);
                  } catch (Throwable var7) {
                     ExceptionLogger.logException(var7);
                  }
               }
            }

            ChatUtility.InitAllowedChatIcons();
            ChatManager.getInstance().init(true, IsoPlayer.getInstance());
            this.this$0.bWaitForAssetLoadingToFinish2 = true;
            synchronized (this.this$0.assetLock2) {
               while (this.this$0.bWaitForAssetLoadingToFinish2) {
                  try {
                     this.this$0.assetLock2.wait();
                  } catch (InterruptedException var6) {
                  }
               }
            }

            UIManager.bSuspend = false;
            GameLoadingState.playerCreated = true;
            GameLoadingState.GameLoadingString = "";
            GameLoadingState.SendDone();
         }
      }
   }
}
