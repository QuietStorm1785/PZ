#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "fmod/fmod/Audio.h"
#include "zombie/GameTime.h"
#include "zombie/Lua/LuaEventManager.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/PerformanceSettings.h"
#include "zombie/core/Rand.h"
#include "zombie/core/textures/ColorInfo.h"
#include "zombie/iso/IsoCell.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/SpriteDetails/IsoFlagType.h"
#include "zombie/iso/weather/ClimateManager.h"
#include "zombie/network/GameServer.h"
#include <algorithm>

namespace zombie {
namespace iso {
namespace objects {


class RainManager {
public:
    static bool IsRaining = false;
    static int NumActiveRainSplashes = 0;
    static int NumActiveRaindrops = 0;
    static int MaxRainSplashObjects = 500;
    static int MaxRaindropObjects = 500;
    static float RainSplashAnimDelay = 0.2F;
    static int AddNewSplashesDelay = 30;
    static int AddNewSplashesTimer = AddNewSplashesDelay;
    static float RaindropGravity = 0.065F;
    static float GravModMin = 0.28F;
    static float GravModMax = 0.5F;
    static float RaindropStartDistance = 850.0F;
   public static IsoGridSquare[] PlayerLocation = new IsoGridSquare[4];
   public static IsoGridSquare[] PlayerOldLocation = new IsoGridSquare[4];
    static bool PlayerMoved = true;
    static int RainRadius = 18;
    static Audio RainAmbient;
    static Audio ThunderAmbient = nullptr;
    static ColorInfo RainSplashTintMod = std::make_shared<ColorInfo>(0.8F, 0.9F, 1.0F, 0.3F);
    static ColorInfo RaindropTintMod = std::make_shared<ColorInfo>(0.8F, 0.9F, 1.0F, 0.3F);
    static ColorInfo DarkRaindropTintMod = std::make_shared<ColorInfo>(0.8F, 0.9F, 1.0F, 0.3F);
   public static std::vector<IsoRainSplash> RainSplashStack = new std::vector<>(1600);
   public static std::vector<IsoRaindrop> RaindropStack = new std::vector<>(1600);
   public static std::stack<IsoRainSplash> RainSplashReuseStack = std::make_unique<std::stack<>>();
   public static std::stack<IsoRaindrop> RaindropReuseStack = std::make_unique<std::stack<>>();
    static float RainChangeTimer = 1.0F;
    static float RainChangeRate = 0.01F;
    static float RainChangeRateMin = 0.006F;
    static float RainChangeRateMax = 0.01F;
    static float RainIntensity = 1.0F;
    static float RainDesiredIntensity = 1.0F;
    static int randRain = 0;
    static int randRainMin = 0;
    static int randRainMax = 0;
    static bool stopRain = false;
    static Audio OutsideAmbient = nullptr;
    static Audio OutsideNightAmbient = nullptr;
    static ColorInfo AdjustedRainSplashTintMod = std::make_shared<ColorInfo>();

    static void reset() {
      RainSplashStack.clear();
      RaindropStack.clear();
      RaindropReuseStack.clear();
      RainSplashReuseStack.clear();
      NumActiveRainSplashes = 0;
      NumActiveRaindrops = 0;

      for (int var0 = 0; var0 < 4; var0++) {
         PlayerLocation[var0] = nullptr;
         PlayerOldLocation[var0] = nullptr;
      }

      RainAmbient = nullptr;
      ThunderAmbient = nullptr;
      IsRaining = false;
      stopRain = false;
   }

    static void AddRaindrop(IsoRaindrop var0) {
      if (NumActiveRaindrops < MaxRaindropObjects) {
         RaindropStack.push_back(var0);
         NumActiveRaindrops++;
      } else {
    IsoRaindrop var1 = nullptr;
    int var2 = -1;

         for (int var3 = 0; var3 < RaindropStack.size(); var3++) {
            if (RaindropStack.get(var3).Life > var2) {
               var2 = RaindropStack.get(var3).Life;
               var1 = RaindropStack.get(var3);
            }
         }

         if (var1 != nullptr) {
            RemoveRaindrop(var1);
            RaindropStack.push_back(var0);
            NumActiveRaindrops++;
         }
      }
   }

    static void AddRainSplash(IsoRainSplash var0) {
      if (NumActiveRainSplashes < MaxRainSplashObjects) {
         RainSplashStack.push_back(var0);
         NumActiveRainSplashes++;
      } else {
    IsoRainSplash var1 = nullptr;
    int var2 = -1;

         for (int var3 = 0; var3 < RainSplashStack.size(); var3++) {
            if (RainSplashStack.get(var3).Age > var2) {
               var2 = RainSplashStack.get(var3).Age;
               var1 = RainSplashStack.get(var3);
            }
         }

         RemoveRainSplash(var1);
         RainSplashStack.push_back(var0);
         NumActiveRainSplashes++;
      }
   }

    static void AddSplashes() {
      if (AddNewSplashesTimer > 0) {
         AddNewSplashesTimer--;
      } else {
         AddNewSplashesTimer = (int)(AddNewSplashesDelay * (PerformanceSettings.getLockFPS() / 30.0F));
    void* var0 = nullptr;
         if (!stopRain) {
            if (PlayerMoved) {
               for (int var1 = RainSplashStack.size() - 1; var1 >= 0; var1--) {
    IsoRainSplash var2 = RainSplashStack.get(var1);
                  if (!inBounds(var2.square)) {
                     RemoveRainSplash(var2);
                  }
               }

               for (int var10 = RaindropStack.size() - 1; var10 >= 0; var10--) {
    IsoRaindrop var14 = RaindropStack.get(var10);
                  if (!inBounds(var14.square)) {
                     RemoveRaindrop(var14);
                  }
               }
            }

    int var11 = 0;

            for (int var15 = 0; var15 < IsoPlayer.numPlayers; var15++) {
               if (IsoPlayer.players[var15] != nullptr) {
                  var11++;
               }
            }

    int var16 = RainRadius * 2 * RainRadius * 2;
    int var3 = var16 / (randRain + 1);
            var3 = Math.min(MaxRainSplashObjects, var3);

            while (NumActiveRainSplashes > var3 * var11) {
               RemoveRainSplash(RainSplashStack.get(0));
            }

            while (NumActiveRaindrops > var3 * var11) {
               RemoveRaindrop(RaindropStack.get(0));
            }

    IsoCell var4 = IsoWorld.instance.CurrentCell;

            for (int var5 = 0; var5 < IsoPlayer.numPlayers; var5++) {
               if (IsoPlayer.players[var5] != nullptr && PlayerLocation[var5] != nullptr) {
                  for (int var6 = 0; var6 < var3; var6++) {
    int var7 = Rand.Next(-RainRadius, RainRadius);
    int var8 = Rand.Next(-RainRadius, RainRadius);
                     var0 = var4.getGridSquare(PlayerLocation[var5].getX() + var7, PlayerLocation[var5].getY() + var8, 0);
                     if (var0 != nullptr && var0.isSeen(var5) && !var0.getProperties().Is(IsoFlagType.vegitation) && var0.getProperties().Is(IsoFlagType.exterior)
                        )
                      {
                        StartRainSplash(var4, (IsoGridSquare)var0, true);
                     }
                  }
               }
            }
         }

         PlayerMoved = false;
         if (!stopRain) {
            randRain--;
            if (randRain < randRainMin) {
               randRain = randRainMin;
            }
         } else {
            randRain = (int)(randRain - 1.0F * GameTime.instance.getMultiplier());
            if (randRain < randRainMin) {
               removeAll();
               randRain = randRainMin;
            } else {
               for (int var12 = RainSplashStack.size() - 1; var12 >= 0; var12--) {
                  if (Rand.Next(randRain) == 0) {
    IsoRainSplash var17 = RainSplashStack.get(var12);
                     RemoveRainSplash(var17);
                  }
               }

               for (int var13 = RaindropStack.size() - 1; var13 >= 0; var13--) {
                  if (Rand.Next(randRain) == 0) {
    IsoRaindrop var18 = RaindropStack.get(var13);
                     RemoveRaindrop(var18);
                  }
               }
            }
         }
      }
   }

    static void RemoveRaindrop(IsoRaindrop var0) {
      if (var0.square != nullptr) {
         var0.square.getProperties().UnSet(IsoFlagType.HasRaindrop);
         var0.square.setRainDrop(nullptr);
         var0.square = nullptr;
      }

      RaindropStack.remove(var0);
      NumActiveRaindrops--;
      RaindropReuseStack.push(var0);
   }

    static void RemoveRainSplash(IsoRainSplash var0) {
      if (var0.square != nullptr) {
         var0.square.getProperties().UnSet(IsoFlagType.HasRainSplashes);
         var0.square.setRainSplash(nullptr);
         var0.square = nullptr;
      }

      RainSplashStack.remove(var0);
      NumActiveRainSplashes--;
      RainSplashReuseStack.push(var0);
   }

    static void SetPlayerLocation(int var0, IsoGridSquare var1) {
      PlayerOldLocation[var0] = PlayerLocation[var0];
      PlayerLocation[var0] = var1;
      if (PlayerOldLocation[var0] != PlayerLocation[var0]) {
         PlayerMoved = true;
      }
   }

    static bool isRaining() {
      return ClimateManager.getInstance().isRaining();
   }

    static void stopRaining() {
      stopRain = true;
      randRain = randRainMax;
      RainDesiredIntensity = 0.0F;
      if (GameServer.bServer) {
         GameServer.stopRain();
      }

      LuaEventManager.triggerEvent("OnRainStop");
   }

    static void startRaining() {
   }

    static void StartRaindrop(IsoCell var0, IsoGridSquare var1, bool var2) {
      if (!var1.getProperties().Is(IsoFlagType.HasRaindrop)) {
    IsoRaindrop var3 = nullptr;
         if (!RaindropReuseStack.empty()) {
            if (var2) {
               if (var1.getRainDrop() != nullptr) {
                  return;
               }

               var3 = RaindropReuseStack.pop();
               var3.Reset(var1, var2);
               var1.setRainDrop(var3);
            }
         } else if (var2) {
            if (var1.getRainDrop() != nullptr) {
               return;
            }

            var3 = std::make_shared<IsoRaindrop>(var0, var1, var2);
            var1.setRainDrop(var3);
         }
      }
   }

    static void StartRainSplash(IsoCell var0, IsoGridSquare var1, bool var2) {
   }

    static void Update() {
      IsRaining = ClimateManager.getInstance().isRaining();
      RainIntensity = IsRaining ? ClimateManager.getInstance().getPrecipitationIntensity() : 0.0F;
      if (IsoPlayer.getInstance() != nullptr) {
         if (IsoPlayer.getInstance().getCurrentSquare() != nullptr) {
            if (!GameServer.bServer) {
               AddSplashes();
            }
         }
      }
   }

    static void UpdateServer() {
   }

    static void setRandRainMax(int var0) {
      randRainMax = var0;
      randRain = randRainMax;
   }

    static void setRandRainMin(int var0) {
      randRainMin = var0;
   }

    static bool inBounds(IsoGridSquare var0) {
      if (var0 == nullptr) {
    return false;
      } else {
         for (int var1 = 0; var1 < IsoPlayer.numPlayers; var1++) {
    IsoPlayer var2 = IsoPlayer.players[var1];
            if (var2 != nullptr && PlayerLocation[var1] != nullptr) {
               if (var0.getX() < PlayerLocation[var1].getX() - RainRadius || var0.getX() >= PlayerLocation[var1].getX() + RainRadius) {
    return true;
               }

               if (var0.getY() < PlayerLocation[var1].getY() - RainRadius || var0.getY() >= PlayerLocation[var1].getY() + RainRadius) {
    return true;
               }
            }
         }

    return false;
      }
   }

    static void RemoveAllOn(IsoGridSquare var0) {
      if (var0.getRainDrop() != nullptr) {
         RemoveRaindrop(var0.getRainDrop());
      }

      if (var0.getRainSplash() != nullptr) {
         RemoveRainSplash(var0.getRainSplash());
      }
   }

    static float getRainIntensity() {
      return ClimateManager.getInstance().getPrecipitationIntensity();
   }

    static void removeAll() {
      for (int var0 = RainSplashStack.size() - 1; var0 >= 0; var0--) {
    IsoRainSplash var1 = RainSplashStack.get(var0);
         RemoveRainSplash(var1);
      }

      for (int var2 = RaindropStack.size() - 1; var2 >= 0; var2--) {
    IsoRaindrop var3 = RaindropStack.get(var2);
         RemoveRaindrop(var3);
      }

      RaindropStack.clear();
      RainSplashStack.clear();
      NumActiveRainSplashes = 0;
      NumActiveRaindrops = 0;
   }

    static bool interruptSleep(IsoPlayer var0) {
      if (var0.isAsleep() && var0.isOutside() && var0.getBed() != nullptr && !var0.getBed().getName() == "Tent")) {
    IsoObject var1 = var0.getBed();
         if (var1.getCell().getGridSquare(var1.getX(), var1.getY(), var1.getZ() + 1.0F) == nullptr
            || var1.getCell().getGridSquare(var1.getX(), var1.getY(), var1.getZ() + 1.0F).getFloor() == nullptr) {
    return true;
         }
      }

    return false;
   }
}
} // namespace objects
} // namespace iso
} // namespace zombie
