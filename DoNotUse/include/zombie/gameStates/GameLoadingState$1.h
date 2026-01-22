#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameTime.h"
#include "zombie/GameWindow.h"
#include "zombie/Lua/LuaEventManager.h"
#include "zombie/ZomboidFileSystem.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/chat/ChatManager.h"
#include "zombie/chat/ChatUtility.h"
#include "zombie/core/logger/ExceptionLogger.h"
#include "zombie/debug/DebugOptions.h"
#include "zombie/globalObjects/CGlobalObjects.h"
#include "zombie/globalObjects/SGlobalObjects.h"
#include "zombie/iso/IsoObjectPicker.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/weather/ClimateManager.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/ui/TutorialManager.h"
#include "zombie/ui/UIManager.h"
#include "zombie/vehicles/BaseVehicle.h"
#include <fstream>
#include <iostream>

namespace zombie {
namespace gameStates {


class GameLoadingState {
public:
   GameLoadingState$1(GameLoadingState var1) {
      this.this$0 = var1;
   }

    void run() {
      try {
         this.runInner();
      } catch (Throwable var2) {
         GameLoadingState.unexpectedError = true;
         ExceptionLogger.logException(var2);
      }
   }

    void runInner() {
      this.this$0.bWaitForAssetLoadingToFinish1 = true;
      /* synchronized - TODO: add std::mutex */ (this.this$0.assetLock1) {
         while (this.this$0.bWaitForAssetLoadingToFinish1) {
            try {
               this.this$0.assetLock1.wait();
            } catch (InterruptedException var8) {
            }
         }
      }

    bool var11 = std::make_shared<File>(ZomboidFileSystem.instance.getGameModeCacheDir() + File.separator).mkdir();
      BaseVehicle.LoadAllVehicleTextures();
      if (GameClient.bClient) {
         GameClient.instance.GameLoadingRequestData();
      }

      TutorialManager.instance = std::make_unique<TutorialManager>();
      GameTime.setInstance(std::make_unique<GameTime>());
      ClimateManager.setInstance(std::make_unique<ClimateManager>());
      IsoWorld.instance = std::make_unique<IsoWorld>();
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
    bool var3 = !var2.exists();
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
            /* synchronized - TODO: add std::mutex */ (this.this$0.assetLock2) {
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
} // namespace gameStates
} // namespace zombie
