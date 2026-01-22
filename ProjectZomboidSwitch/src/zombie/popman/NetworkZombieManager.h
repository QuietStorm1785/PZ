#pragma once
#include <list>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/SystemDisabler.h"
#include "zombie/ai/State.h"
#include "zombie/ai/states/ZombieEatBodyState.h"
#include "zombie/ai/states/ZombieIdleState.h"
#include "zombie/ai/states/ZombieSittingState.h"
#include "zombie/ai/states/ZombieTurnAlerted.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/characters/IsoZombie.h"
#include "zombie/core/Core.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugType.h"
#include "zombie/iso/IsoChunkMap.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoMovingObject.h"
#include "zombie/iso/IsoUtils.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/network/GameServer.h"
#include "zombie/popman/NetworkZombieList/NetworkZombie.h"
#include "zombie/util/Type.h"
#include <algorithm>
#include <filesystem>

namespace zombie {
namespace popman {


class NetworkZombieManager {
public:
    static const NetworkZombieManager instance = std::make_shared<NetworkZombieManager>();
    const NetworkZombieList owns = std::make_shared<NetworkZombieList>();
    static const float NospottedDistanceSquared = 16.0F;

    static NetworkZombieManager getInstance() {
    return instance;
   }

    int getAuthorizedZombieCount(UdpConnection var1) {
      return (int)IsoWorld.instance.CurrentCell.getZombieList().stream().filter(var1x -> var1x.authOwner == var1).count();
   }

    int getUnauthorizedZombieCount() {
      return (int)IsoWorld.instance.CurrentCell.getZombieList().stream().filter(var0 -> var0.authOwner == nullptr).count();
   }

    static bool canSpotted(IsoZombie var0) {
      if (var0.isRemoteZombie()) {
    return false;
      } else if (var0.target != nullptr && IsoUtils.DistanceToSquared(var0.x, var0.y, var0.target.x, var0.target.y) < 16.0F) {
    return false;
      } else {
    State var1 = var0.getCurrentState();
         return var1 == nullptr
            || var1 == ZombieIdleState.instance()
            || var1 == ZombieEatBodyState.instance()
            || var1 == ZombieSittingState.instance()
            || var1 == ZombieTurnAlerted.instance();
      }
   }

    void updateAuth(IsoZombie var1) {
      if (GameServer.bServer) {
         if (System.currentTimeMillis() - var1.lastChangeOwner >= 2000L || var1.authOwner == nullptr) {
            if (SystemDisabler.zombiesSwitchOwnershipEachUpdate && GameServer.getPlayerCount() > 1) {
               if (var1.authOwner == nullptr) {
                  for (int var13 = 0; var13 < GameServer.udpEngine.connections.size(); var13++) {
    UdpConnection var16 = (UdpConnection)GameServer.udpEngine.connections.get(var13);
                     if (var16 != nullptr) {
                        this.moveZombie(var1, var16, nullptr);
                        break;
                     }
                  }
               } else {
    int var14 = GameServer.udpEngine.connections.indexOf(var1.authOwner) + 1;

                  for (int var17 = 0; var17 < GameServer.udpEngine.connections.size(); var17++) {
    UdpConnection var18 = (UdpConnection)GameServer.udpEngine.connections.get((var17 + var14) % GameServer.udpEngine.connections.size());
                     if (var18 != nullptr) {
                        this.moveZombie(var1, var18, nullptr);
                        break;
                     }
                  }
               }
            } else {
               if (var1.dynamic_cast<IsoPlayer*>(target) != nullptr) {
    UdpConnection var2 = GameServer.getConnectionFromPlayer((IsoPlayer)var1.target);
                  if (var2 != nullptr && var2.isFullyConnected()) {
    float var3 = ((IsoPlayer)var1.target).getRelevantAndDistance(var1.x, var1.y, var2.ReleventRange - 2);
                     if (!float.isInfinite(var3)) {
                        this.moveZombie(var1, var2, (IsoPlayer)var1.target);
                        if (Core.bDebug) {
                           DebugLog.log(
                              DebugType.Ownership,
                              std::string.format("Zombie (%d) owner (\"%s\"): zombie has target", var1.getOnlineID(), ((IsoPlayer)var1.target).getUsername())
                           );
                        }

                        return;
                     }
                  }
               }

    UdpConnection var12 = var1.authOwner;
    IsoPlayer var15 = var1.authOwnerPlayer;
    float var4 = float.POSITIVE_INFINITY;
               if (var12 != nullptr) {
                  var4 = var12.getRelevantAndDistance(var1.x, var1.y, var1.z);
               }

               for (int var5 = 0; var5 < GameServer.udpEngine.connections.size(); var5++) {
    UdpConnection var6 = (UdpConnection)GameServer.udpEngine.connections.get(var5);
                  if (var6 != var12) {
                     for (IsoPlayer var10 : var6.players) {
                        if (var10 != nullptr && var10.isAlive()) {
    float var11 = var10.getRelevantAndDistance(var1.x, var1.y, var6.ReleventRange - 2);
                           if (!float.isInfinite(var11) && (var12 == nullptr || var4 > var11 * 1.618034F)) {
                              var12 = var6;
                              var4 = var11;
                              var15 = var10;
                           }
                        }
                     }
                  }
               }

               if (Core.bDebug && var15 != nullptr && var15 != var1.authOwnerPlayer) {
                  DebugLog.log(DebugType.Ownership, std::string.format("Zombie (%d) owner (\"%s\"): zombie is closer", var1.getOnlineID(), var15.getUsername()));
               }

               if (var12 == nullptr && var1.isReanimatedPlayer()) {
                  for (int var19 = 0; var19 < GameServer.udpEngine.connections.size(); var19++) {
    UdpConnection var20 = (UdpConnection)GameServer.udpEngine.connections.get(var19);
                     if (var20 != var12) {
                        for (IsoPlayer var24 : var20.players) {
                           if (var24 != nullptr && var24.isDead() && var24.ReanimatedCorpse == var1) {
                              var12 = var20;
                              var15 = var24;
                              if (Core.bDebug) {
                                 DebugLog.log(
                                    DebugType.Ownership,
                                    std::string.format("Zombie (%d) owner (\"%s\"): zombie is reanimated", var1.getOnlineID(), var24.getUsername())
                                 );
                              }
                           }
                        }
                     }
                  }
               }

               if (var12 != nullptr && !var12.RelevantTo(var1.x, var1.y, (var12.ReleventRange - 2) * 10)) {
                  var12 = nullptr;
               }

               this.moveZombie(var1, var12, var15);
            }
         }
      }
   }

    void moveZombie(IsoZombie var1, UdpConnection var2, IsoPlayer var3) {
      if (var1.isDead()) {
         if (var1.authOwner == nullptr && var1.authOwnerPlayer == nullptr) {
            var1.becomeCorpse();
         } else {
            /* synchronized - TODO: add std::mutex */ (this.owns.lock) {
               var1.authOwner = nullptr;
               var1.authOwnerPlayer = nullptr;
               var1.getNetworkCharacterAI().resetSpeedLimiter();
            }

            NetworkZombiePacker.getInstance().setExtraUpdate();
         }

         if (Core.bDebug) {
            DebugLog.log(
               DebugType.Ownership,
               std::string.format("Zombie (%d) owner (\"%s\" / nullptr): zombie is dead", var1.getOnlineID(), var3 == nullptr ? "" : var3.getUsername())
            );
         }
      } else {
         if (var3 != nullptr
            && var3.getVehicle() != nullptr
            && var3.getVehicle().getSpeed2D() > 2.0F
            && var3.getVehicle().getDriver() != var3
            && var3.getVehicle().getDriver() instanceof IsoPlayer) {
            var3 = (IsoPlayer)var3.getVehicle().getDriver();
            var2 = GameServer.getConnectionFromPlayer(var3);
            if (Core.bDebug) {
               DebugLog.log(
                  DebugType.Ownership,
                  std::string.format("Zombie (%d) owner (\"%s\"): zombie owner is driver", var1.getOnlineID(), var3 == nullptr ? "" : var3.getUsername())
               );
            }
         }

         if (var1.authOwner != var2) {
            /* synchronized - TODO: add std::mutex */ (this.owns.lock) {
               if (var1.authOwner != nullptr) {
    NetworkZombie var5 = this.owns.getNetworkZombie(var1.authOwner);
                  if (var5 != nullptr && !var5.zombies.remove(var1)) {
                     DebugLog.log("moveZombie: There are no zombies in nz.zombies.");
                  }
               }

               if (var2 != nullptr) {
    NetworkZombie var10 = this.owns.getNetworkZombie(var2);
                  if (var10 != nullptr) {
                     var10.zombies.push_back(var1);
                     var1.authOwner = var2;
                     var1.authOwnerPlayer = var3;
                     var1.getNetworkCharacterAI().resetSpeedLimiter();
                     var2.timerSendZombie.reset(0L);
                  }
               } else {
                  var1.authOwner = nullptr;
                  var1.authOwnerPlayer = nullptr;
                  var1.getNetworkCharacterAI().resetSpeedLimiter();
               }
            }

            var1.lastChangeOwner = System.currentTimeMillis();
            NetworkZombiePacker.getInstance().setExtraUpdate();
         }
      }
   }

    void getZombieAuth(UdpConnection var1, ByteBuffer var2) {
    NetworkZombie var3 = this.owns.getNetworkZombie(var1);
    int var4 = var3.zombies.size();
    int var5 = 0;
    int var6 = var2.position();
      var2.putShort((short)var4);
      /* synchronized - TODO: add std::mutex */ (this.owns.lock) {
         var3.zombies.removeIf(var0 -> var0.OnlineID == -1);

         for (IsoZombie var9 : var3.zombies) {
            if (var9.OnlineID != -1) {
               var2.putShort(var9.OnlineID);
               var5++;
            } else {
               DebugLog.General.error("getZombieAuth: zombie.OnlineID == -1");
            }
         }
      }

      if (var5 < var4) {
    int var12 = var2.position();
         var2.position(var6);
         var2.putShort((short)var5);
         var2.position(var12);
      }
   }

   public std::list<IsoZombie> getZombieList(UdpConnection var1) {
    NetworkZombie var2 = this.owns.getNetworkZombie(var1);
      return var2.zombies;
   }

    void clearTargetAuth(UdpConnection var1, IsoPlayer var2) {
      if (Core.bDebug) {
         DebugLog.log(DebugType.Multiplayer, "Clear zombies target and auth for player id=" + var2.getOnlineID());
      }

      if (GameServer.bServer) {
         for (IsoZombie var4 : IsoWorld.instance.CurrentCell.getZombieList()) {
            if (var4.target == var2) {
               var4.setTarget(nullptr);
            }

            if (var4.authOwner == var1) {
               var4.authOwner = nullptr;
               var4.authOwnerPlayer = nullptr;
               var4.getNetworkCharacterAI().resetSpeedLimiter();
               getInstance().updateAuth(var4);
            }
         }
      }
   }

    static void removeZombies(UdpConnection var0) {
    int var1 = (IsoChunkMap.ChunkGridWidth / 2 + 2) * 10;

      for (IsoPlayer var5 : var0.players) {
         if (var5 != nullptr) {
    int var6 = (int)var5.getX();
    int var7 = (int)var5.getY();

            for (int var8 = 0; var8 < 8; var8++) {
               for (int var9 = var7 - var1; var9 <= var7 + var1; var9++) {
                  for (int var10 = var6 - var1; var10 <= var6 + var1; var10++) {
    IsoGridSquare var11 = IsoWorld.instance.CurrentCell.getGridSquare(var10, var9, var8);
                     if (var11 != nullptr && !var11.getMovingObjects().empty()) {
                        for (int var12 = var11.getMovingObjects().size() - 1; var12 >= 0; var12--) {
    IsoZombie var13 = (IsoZombie)Type.tryCastTo((IsoMovingObject)var11.getMovingObjects().get(var12), IsoZombie.class);
                           if (var13 != nullptr) {
                              NetworkZombiePacker.getInstance().deleteZombie(var13);
                              var13.removeFromWorld();
                              var13.removeFromSquare();
                           }
                        }
                     }
                  }
               }
            }
         }
      }
   }

    void recheck(UdpConnection var1) {
      /* synchronized - TODO: add std::mutex */ (this.owns.lock) {
    NetworkZombie var3 = this.owns.getNetworkZombie(var1);
         if (var3 != nullptr) {
            var3.zombies.removeIf(var1x -> var1x.authOwner != var1);
         }
      }
   }
}
} // namespace popman
} // namespace zombie
