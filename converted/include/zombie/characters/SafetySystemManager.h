#pragma once
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
#include <cstdint>
#include <iterator>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace characters {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class SafetySystemManager {
public:
private
  static final LinkedHashMap<String, Float> playerCooldown =
      std::make_unique<LinkedHashMap<>>();
private
  static final LinkedHashMap<String, Boolean> playerSafety =
      std::make_unique<LinkedHashMap<>>();
private
  static final LinkedHashMap<String, Long> playerDelay =
      std::make_unique<LinkedHashMap<>>();
  static const long safetyDelay = 1500L;

  static void updateTimers(Safety safety) {
    float float0 = GameTime.instance.getRealworldSecondsSinceLastUpdate();
    if (safety.getToggle() > 0.0F) {
      safety.setToggle(safety.getToggle() - float0);
      if (safety.getToggle() <= 0.0F) {
        safety.setToggle(0.0F);
        if (!safety.isLast()) {
          safety.setEnabled(!safety.isEnabled());
        }
      }
    } else if (safety.getCooldown() > 0.0F) {
      safety.setCooldown(safety.getCooldown() - float0);
    } else {
      safety.setCooldown(0.0F);
    }
  }

  static void updateNonPvpZone(IsoPlayer player, bool boolean0) {
    if (boolean0 && !player.networkAI.wasNonPvpZone) {
      storeSafety(player);
      GameServer.sendChangeSafety(player.getSafety());
    } else if (!boolean0 && player.networkAI.wasNonPvpZone) {
      restoreSafety(player);
      GameServer.sendChangeSafety(player.getSafety());
    }

    player.networkAI.wasNonPvpZone = boolean0;
  }

  static void update(IsoPlayer player) {
    bool boolean0 =
        NonPvpZone.getNonPvpZone(PZMath.fastfloor(player.getX()),
                                 PZMath.fastfloor(player.getY())) != null;
    if (!boolean0) {
      updateTimers(player.getSafety());
    }

    if (GameServer.bServer) {
      updateNonPvpZone(player, boolean0);
    }
  }

  static void clear() {
    playerCooldown.clear();
    playerSafety.clear();
    playerDelay.clear();
  }

  static void clearSafety(IsoPlayer player) {
    if (player != nullptr) {
      Safety safety = player.getSafety();
      LoggerManager.getLogger("pvp").write(
          String.format("user \"%s\" clear safety %s", player.getUsername(),
                        safety.getDescription()),
          "INFO");
      playerCooldown.remove(player.getUsername());
      playerSafety.remove(player.getUsername());
      playerDelay.remove(player.getUsername());
    } else if (Core.bDebug) {
      DebugLog.Combat.debugln("ClearSafety: player not found");
    }
  }

  static void storeSafety(IsoPlayer player) {
    try {
      if (player != nullptr && player.isAlive()) {
        Safety safety = player.getSafety();
        LoggerManager.getLogger("pvp").write(
            String.format("user \"%s\" store safety %s", player.getUsername(),
                          safety.getDescription()),
            "INFO");
        playerSafety.put(player.getUsername(), safety.isEnabled());
        playerCooldown.put(player.getUsername(), safety.getCooldown());
        playerDelay.put(player.getUsername(), System.currentTimeMillis());
        if (playerCooldown.size() >
            ServerOptions.instance.MaxPlayers.getValue() * 1000) {
          Iterator iterator0 = playerCooldown.entrySet().iterator();
          if (iterator0.hasNext()) {
            iterator0.next();
            iterator0.remove();
          }
        }

        if (playerSafety.size() >
            ServerOptions.instance.MaxPlayers.getValue() * 1000) {
          Iterator iterator1 = playerSafety.entrySet().iterator();
          if (iterator1.hasNext()) {
            iterator1.next();
            iterator1.remove();
          }
        }

        if (playerDelay.size() >
            ServerOptions.instance.MaxPlayers.getValue() * 1000) {
          Iterator iterator2 = playerDelay.entrySet().iterator();
          if (iterator2.hasNext()) {
            iterator2.next();
            iterator2.remove();
          }
        }
      } else if (Core.bDebug) {
        DebugLog.Combat.debugln("StoreSafety: player not found");
      }
    } catch (Exception exception) {
      DebugLog.Multiplayer.printException(exception, "StoreSafety failed",
                                          LogSeverity.Error);
    }
  }

  static void restoreSafety(IsoPlayer player) {
    try {
      if (player != nullptr) {
        Safety safety = player.getSafety();
        if (playerSafety.containsKey(player.getUsername())) {
          safety.setEnabled(playerSafety.remove(player.getUsername()));
        }

        if (playerCooldown.containsKey(player.getUsername())) {
          safety.setCooldown(playerCooldown.remove(player.getUsername()));
        }

        playerDelay.put(player.getUsername(), System.currentTimeMillis());
        LoggerManager.getLogger("pvp").write(
            String.format("user \"%s\" restore safety %s", player.getUsername(),
                          safety.getDescription()),
            "INFO");
      } else if (Core.bDebug) {
        DebugLog.Combat.debugln("RestoreSafety: player not found");
      }
    } catch (Exception exception) {
      DebugLog.Multiplayer.printException(exception, "RestoreSafety failed",
                                          LogSeverity.Error);
    }
  }

  static void updateOptions() {
    bool boolean0 = ServerOptions.instance.PVP.getValue();
    bool boolean1 = ServerOptions.instance.SafetySystem.getValue();
    if (!boolean0) {
      clear();

      for (IsoPlayer player0 : GameServer.IDToPlayerMap.values()) {
        if (player0 != nullptr) {
          player0.getSafety().setEnabled(true);
          player0.getSafety().setLast(false);
          player0.getSafety().setCooldown(0.0F);
          player0.getSafety().setToggle(0.0F);
          GameServer.sendChangeSafety(player0.getSafety());
        }
      }
    } else if (!boolean1) {
      clear();

      for (IsoPlayer player1 : GameServer.IDToPlayerMap.values()) {
        if (player1 != nullptr) {
          player1.getSafety().setEnabled(false);
          player1.getSafety().setLast(false);
          player1.getSafety().setCooldown(0.0F);
          player1.getSafety().setToggle(0.0F);
          GameServer.sendChangeSafety(player1.getSafety());
        }
      }
    }
  }

  static bool checkUpdateDelay(IsoGameCharacter character0,
                               IsoGameCharacter character1) {
    bool boolean0 = false;
    IsoPlayer player0 = Type.tryCastTo(character0, IsoPlayer.class);
    IsoPlayer player1 = Type.tryCastTo(character1, IsoPlayer.class);
    if (player0 != nullptr && player1 != nullptr) {
      long long0 = System.currentTimeMillis();
      if (playerDelay.containsKey(player0.getUsername())) {
        long long1 =
            long0 - playerDelay.getOrDefault(player0.getUsername(), 0L);
        bool boolean1 = long1 < 1500L;
        boolean0 = boolean1;
        if (!boolean1) {
          playerDelay.remove(player0.getUsername());
        }
      }

      if (playerDelay.containsKey(player1.getUsername())) {
        long long2 =
            long0 - playerDelay.getOrDefault(player1.getUsername(), 0L);
        bool boolean2 = long2 < 1500L;
        if (!boolean0) {
          boolean0 = boolean2;
        }

        if (!boolean2) {
          playerDelay.remove(player1.getUsername());
        }
      }
    }

    return boolean0;
  }
}
} // namespace characters
} // namespace zombie
