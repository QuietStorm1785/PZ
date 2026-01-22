#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameTime.h"
#include "zombie/core/Core.h"
#include "zombie/core/logger/LoggerManager.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/LogSeverity.h"
#include "zombie/iso/areas/NonPvpZone.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/ServerOptions.h"
#include "zombie/util/Type.h"
#include <algorithm>
#include <iterator>

namespace zombie {
namespace characters {


class SafetySystemManager {
public:
   private static const LinkedHashMap<std::string, float> playerCooldown = std::make_unique<LinkedHashMap<>>();
   private static const LinkedHashMap<std::string, bool> playerSafety = std::make_unique<LinkedHashMap<>>();
   private static const LinkedHashMap<std::string, int64_t> playerDelay = std::make_unique<LinkedHashMap<>>();
    static const long safetyDelay = 1500L;

    static void updateTimers(Safety var0) {
    float var1 = GameTime.instance.getRealworldSecondsSinceLastUpdate();
      if (var0.getToggle() > 0.0F) {
         var0.setToggle(var0.getToggle() - var1);
         if (var0.getToggle() <= 0.0F) {
            var0.setToggle(0.0F);
            if (!var0.isLast()) {
               var0.setEnabled(!var0.isEnabled());
            }
         }
      } else if (var0.getCooldown() > 0.0F) {
         var0.setCooldown(var0.getCooldown() - var1);
      } else {
         var0.setCooldown(0.0F);
      }
   }

    static void updateNonPvpZone(IsoPlayer var0, bool var1) {
      if (var1 && !var0.networkAI.wasNonPvpZone) {
         storeSafety(var0);
         GameServer.sendChangeSafety(var0.getSafety());
      } else if (!var1 && var0.networkAI.wasNonPvpZone) {
         restoreSafety(var0);
         GameServer.sendChangeSafety(var0.getSafety());
      }

      var0.networkAI.wasNonPvpZone = var1;
   }

    static void update(IsoPlayer var0) {
    bool var1 = NonPvpZone.getNonPvpZone(PZMath.fastfloor(var0.getX()), PZMath.fastfloor(var0.getY())) != nullptr;
      if (!var1) {
         updateTimers(var0.getSafety());
      }

      if (GameServer.bServer) {
         updateNonPvpZone(var0, var1);
      }
   }

    static void clear() {
      playerCooldown.clear();
      playerSafety.clear();
      playerDelay.clear();
   }

    static void clearSafety(IsoPlayer var0) {
      if (var0 != nullptr) {
    Safety var1 = var0.getSafety();
         LoggerManager.getLogger("pvp").write(std::string.format("user \"%s\" clear safety %s", var0.getUsername(), var1.getDescription()), "INFO");
         playerCooldown.remove(var0.getUsername());
         playerSafety.remove(var0.getUsername());
         playerDelay.remove(var0.getUsername());
      } else if (Core.bDebug) {
         DebugLog.Combat.debugln("ClearSafety: player not found");
      }
   }

    static void storeSafety(IsoPlayer var0) {
      try {
         if (var0 != nullptr && var0.isAlive()) {
    Safety var1 = var0.getSafety();
            LoggerManager.getLogger("pvp").write(std::string.format("user \"%s\" store safety %s", var0.getUsername(), var1.getDescription()), "INFO");
            playerSafety.put(var0.getUsername(), var1.isEnabled());
            playerCooldown.put(var0.getUsername(), var1.getCooldown());
            playerDelay.put(var0.getUsername(), System.currentTimeMillis());
            if (playerCooldown.size() > ServerOptions.instance.MaxPlayers.getValue() * 1000) {
    Iterator var2 = playerCooldown.entrySet().iterator();
               if (var2.hasNext()) {
                  var2.next();
                  var2.remove();
               }
            }

            if (playerSafety.size() > ServerOptions.instance.MaxPlayers.getValue() * 1000) {
    Iterator var4 = playerSafety.entrySet().iterator();
               if (var4.hasNext()) {
                  var4.next();
                  var4.remove();
               }
            }

            if (playerDelay.size() > ServerOptions.instance.MaxPlayers.getValue() * 1000) {
    Iterator var5 = playerDelay.entrySet().iterator();
               if (var5.hasNext()) {
                  var5.next();
                  var5.remove();
               }
            }
         } else if (Core.bDebug) {
            DebugLog.Combat.debugln("StoreSafety: player not found");
         }
      } catch (Exception var3) {
         DebugLog.Multiplayer.printException(var3, "StoreSafety failed", LogSeverity.Error);
      }
   }

    static void restoreSafety(IsoPlayer var0) {
      try {
         if (var0 != nullptr) {
    Safety var1 = var0.getSafety();
            if (playerSafety.containsKey(var0.getUsername())) {
               var1.setEnabled(playerSafety.remove(var0.getUsername()));
            }

            if (playerCooldown.containsKey(var0.getUsername())) {
               var1.setCooldown(playerCooldown.remove(var0.getUsername()));
            }

            playerDelay.put(var0.getUsername(), System.currentTimeMillis());
            LoggerManager.getLogger("pvp").write(std::string.format("user \"%s\" restore safety %s", var0.getUsername(), var1.getDescription()), "INFO");
         } else if (Core.bDebug) {
            DebugLog.Combat.debugln("RestoreSafety: player not found");
         }
      } catch (Exception var2) {
         DebugLog.Multiplayer.printException(var2, "RestoreSafety failed", LogSeverity.Error);
      }
   }

    static void updateOptions() {
    bool var0 = ServerOptions.instance.PVP.getValue();
    bool var1 = ServerOptions.instance.SafetySystem.getValue();
      if (!var0) {
         clear();

         for (IsoPlayer var3 : GameServer.IDToPlayerMap.values()) {
            if (var3 != nullptr) {
               var3.getSafety().setEnabled(true);
               var3.getSafety().setLast(false);
               var3.getSafety().setCooldown(0.0F);
               var3.getSafety().setToggle(0.0F);
               GameServer.sendChangeSafety(var3.getSafety());
            }
         }
      } else if (!var1) {
         clear();

         for (IsoPlayer var5 : GameServer.IDToPlayerMap.values()) {
            if (var5 != nullptr) {
               var5.getSafety().setEnabled(false);
               var5.getSafety().setLast(false);
               var5.getSafety().setCooldown(0.0F);
               var5.getSafety().setToggle(0.0F);
               GameServer.sendChangeSafety(var5.getSafety());
            }
         }
      }
   }

    static bool checkUpdateDelay(IsoGameCharacter var0, IsoGameCharacter var1) {
    bool var2 = false;
    IsoPlayer var3 = (IsoPlayer)Type.tryCastTo(var0, IsoPlayer.class);
    IsoPlayer var4 = (IsoPlayer)Type.tryCastTo(var1, IsoPlayer.class);
      if (var3 != nullptr && var4 != nullptr) {
    long var5 = System.currentTimeMillis();
         if (playerDelay.containsKey(var3.getUsername())) {
    long var7 = var5 - playerDelay.getOrDefault(var3.getUsername(), 0L);
    bool var9 = var7 < 1500L;
            var2 = var9;
            if (!var9) {
               playerDelay.remove(var3.getUsername());
            }
         }

         if (playerDelay.containsKey(var4.getUsername())) {
    long var10 = var5 - playerDelay.getOrDefault(var4.getUsername(), 0L);
    bool var11 = var10 < 1500L;
            if (!var2) {
               var2 = var11;
            }

            if (!var11) {
               playerDelay.remove(var4.getUsername());
            }
         }
      }

    return var2;
   }
}
} // namespace characters
} // namespace zombie
