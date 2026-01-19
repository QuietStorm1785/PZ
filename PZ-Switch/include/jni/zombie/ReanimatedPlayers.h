#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/ai/states/ZombieIdleState.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/characters/IsoZombie.h"
#include "zombie/core/logger/ExceptionLogger.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/iso/IsoChunk.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/SliceY.h"
#include "zombie/iso/objects/IsoFireManager.h"
#include "zombie/iso/sprite/IsoSpriteInstance.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/ServerMap.h"
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {


class ReanimatedPlayers {
:
    static ReanimatedPlayers instance = new ReanimatedPlayers();
   private ArrayList<IsoZombie> Zombies = std::make_unique<ArrayList<>>();

    static void noise(const std::string& var0) {
      DebugLog.log("reanimate: " + var0);
   }

    void addReanimatedPlayersToChunk(IsoChunk var1) {
    int var2 = var1.wx * 10;
    int var3 = var1.wy * 10;
    int var4 = var2 + 10;
    int var5 = var3 + 10;

      for (int var6 = 0; var6 < this.Zombies.size(); var6++) {
    IsoZombie var7 = this.Zombies.get(var6);
         if (var7.getX() >= var2 && var7.getX() < var4 && var7.getY() >= var3 && var7.getY() < var5) {
    IsoGridSquare var8 = var1.getGridSquare((int)var7.getX() - var2, (int)var7.getY() - var3, (int)var7.getZ());
            if (var8 != nullptr) {
               if (GameServer.bServer) {
                  if (var7.OnlineID != -1) {
                     noise("ERROR? OnlineID != -1 for reanimated player zombie");
                  }

                  var7.OnlineID = ServerMap.instance.getUniqueZombieId();
                  if (var7.OnlineID == -1) {
                     continue;
                  }

                  ServerMap.instance.ZombieMap.put(var7.OnlineID, var7);
               }

               var7.setCurrent(var8);

               assert !IsoWorld.instance.CurrentCell.getObjectList().contains(var7);

               assert !IsoWorld.instance.CurrentCell.getZombieList().contains(var7);

               IsoWorld.instance.CurrentCell.getObjectList().add(var7);
               IsoWorld.instance.CurrentCell.getZombieList().add(var7);
               this.Zombies.remove(var6);
               var6--;
               SharedDescriptors.createPlayerZombieDescriptor(var7);
               noise("added to world " + var7);
            }
         }
      }
   }

    void removeReanimatedPlayerFromWorld(IsoZombie var1) {
      if (var1.isReanimatedPlayer()) {
         if (!GameServer.bServer) {
            var1.setSceneCulled(true);
         }

         if (var1.isOnFire()) {
            IsoFireManager.RemoveBurningCharacter(var1);
            var1.setOnFire(false);
         }

         if (var1.AttachedAnimSprite != nullptr) {
    std::vector var2 = var1.AttachedAnimSprite;

            for (int var3 = 0; var3 < var2.size(); var3++) {
    IsoSpriteInstance var4 = (IsoSpriteInstance)var2.get(var3);
               IsoSpriteInstance.add(var4);
            }

            var1.AttachedAnimSprite.clear();
         }

         if (!GameServer.bServer) {
            for (int var5 = 0; var5 < IsoPlayer.numPlayers; var5++) {
    IsoPlayer var6 = IsoPlayer.players[var5];
               if (var6 != nullptr && var6.ReanimatedCorpse == var1) {
                  var6.ReanimatedCorpse = nullptr;
                  var6.ReanimatedCorpseID = -1;
               }
            }
         }

         if (GameServer.bServer && var1.OnlineID != -1) {
            ServerMap.instance.ZombieMap.remove(var1.OnlineID);
            var1.OnlineID = -1;
         }

         SharedDescriptors.releasePlayerZombieDescriptor(var1);

         assert !VirtualZombieManager.instance.isReused(var1);

         if (!var1.isDead()) {
            if (!GameClient.bClient) {
               if (!this.Zombies.contains(var1)) {
                  this.Zombies.add(var1);
                  noise("added to Zombies " + var1);
                  var1.setStateMachineLocked(false);
                  var1.changeState(ZombieIdleState.instance());
               }
            }
         }
      }
   }

    void saveReanimatedPlayers() {
      if (!GameClient.bClient) {
    std::vector var1 = new ArrayList();

         try {
    ByteBuffer var2 = SliceY.SliceBuffer;
            var2.clear();
            var2.putInt(195);
            var1.addAll(this.Zombies);

            for (IsoZombie var5 : IsoWorld.instance.CurrentCell.getZombieList()) {
               if (var5.isReanimatedPlayer() && !var5.isDead() && !var1.contains(var5)) {
                  var1.add(var5);
               }
            }

            var2.putInt(var1.size());

    for (auto& var10 : var1)               var10.save(var2);
            }

    File var9 = ZomboidFileSystem.instance.getFileInCurrentSave("reanimated.bin");
    FileOutputStream var11 = new FileOutputStream(var9);
    BufferedOutputStream var6 = new BufferedOutputStream(var11);
            var6.write(var2.array(), 0, var2.position());
            var6.flush();
            var6.close();
         } catch (Exception var7) {
            ExceptionLogger.logException(var7);
            return;
         }

         noise("saved " + var1.size() + " zombies");
      }
   }

    void loadReanimatedPlayers() {
      if (!GameClient.bClient) {
         this.Zombies.clear();
    File var1 = ZomboidFileSystem.instance.getFileInCurrentSave("reanimated.bin");

         try (
    FileInputStream var2 = new FileInputStream(var1);
    BufferedInputStream var3 = new BufferedInputStream(var2);
         ) {
            synchronized (SliceY.SliceBufferLock) {
    ByteBuffer var5 = SliceY.SliceBuffer;
               var5.clear();
    int var6 = var3.read(var5.array());
               var5.limit(var6);
               this.loadReanimatedPlayers(var5);
            }
         } catch (FileNotFoundException var13) {
            return;
         } catch (Exception var14) {
            ExceptionLogger.logException(var14);
            return;
         }

         noise("loaded " + this.Zombies.size() + " zombies");
      }
   }

    void loadReanimatedPlayers(ByteBuffer var1) {
    int var2 = var1.getInt();
    int var3 = var1.getInt();

      for (int var4 = 0; var4 < var3; var4++) {
         if (!(IsoObject.factoryFromFileInput(IsoWorld.instance.CurrentCell, var1) instanceof IsoZombie var6)) {
            throw RuntimeException("expected IsoZombie here");
         }

         var6.load(var1, var2);
         var6.getDescriptor().setID(0);
         var6.setReanimatedPlayer(true);
         IsoWorld.instance.CurrentCell.getAddList().remove(var6);
         IsoWorld.instance.CurrentCell.getObjectList().remove(var6);
         IsoWorld.instance.CurrentCell.getZombieList().remove(var6);
         this.Zombies.add(var6);
      }
   }
}
} // namespace zombie
