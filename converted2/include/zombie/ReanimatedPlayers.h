#pragma once
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
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class ReanimatedPlayers {
public:
  static ReanimatedPlayers instance = new ReanimatedPlayers();
private
  final ArrayList<IsoZombie> Zombies = std::make_unique<ArrayList<>>();

  static void noise(const std::string &string) {
    DebugLog.log("reanimate: " + string);
  }

  void addReanimatedPlayersToChunk(IsoChunk chunk) {
    int int0 = chunk.wx * 10;
    int int1 = chunk.wy * 10;
    int int2 = int0 + 10;
    int int3 = int1 + 10;

    for (int int4 = 0; int4 < this.Zombies.size(); int4++) {
      IsoZombie zombie0 = this.Zombies.get(int4);
      if (zombie0.getX() >= int0 && zombie0.getX() < int2 &&
          zombie0.getY() >= int1 && zombie0.getY() < int3) {
        IsoGridSquare square = chunk.getGridSquare((int)zombie0.getX() - int0,
                                                   (int)zombie0.getY() - int1,
                                                   (int)zombie0.getZ());
        if (square != nullptr) {
          if (GameServer.bServer) {
            if (zombie0.OnlineID != -1) {
              noise("ERROR? OnlineID != -1 for reanimated player zombie");
            }

            zombie0.OnlineID = ServerMap.instance.getUniqueZombieId();
            if (zombie0.OnlineID == -1) {
              continue;
            }

            ServerMap.instance.ZombieMap.put(zombie0.OnlineID, zombie0);
          }

          zombie0.setCurrent(square);

          assert !IsoWorld.instance.CurrentCell.getObjectList().contains(
              zombie0);

          assert !IsoWorld.instance.CurrentCell.getZombieList().contains(
              zombie0);

          IsoWorld.instance.CurrentCell.getObjectList().add(zombie0);
          IsoWorld.instance.CurrentCell.getZombieList().add(zombie0);
          this.Zombies.remove(int4);
          int4--;
          SharedDescriptors.createPlayerZombieDescriptor(zombie0);
          noise("added to world " + zombie0);
        }
      }
    }
  }

  void removeReanimatedPlayerFromWorld(IsoZombie zombie0) {
    if (zombie0.isReanimatedPlayer()) {
      if (!GameServer.bServer) {
        zombie0.setSceneCulled(true);
      }

      if (zombie0.isOnFire()) {
        IsoFireManager.RemoveBurningCharacter(zombie0);
        zombie0.setOnFire(false);
      }

      if (zombie0.AttachedAnimSprite != nullptr) {
        std::vector arrayList = zombie0.AttachedAnimSprite;

        for (int int0 = 0; int0 < arrayList.size(); int0++) {
          IsoSpriteInstance spriteInstance =
              (IsoSpriteInstance)arrayList.get(int0);
          IsoSpriteInstance.add(spriteInstance);
        }

        zombie0.AttachedAnimSprite.clear();
      }

      if (!GameServer.bServer) {
        for (int int1 = 0; int1 < IsoPlayer.numPlayers; int1++) {
          IsoPlayer player = IsoPlayer.players[int1];
          if (player != nullptr && player.ReanimatedCorpse == zombie0) {
            player.ReanimatedCorpse = nullptr;
            player.ReanimatedCorpseID = -1;
          }
        }
      }

      if (GameServer.bServer && zombie0.OnlineID != -1) {
        ServerMap.instance.ZombieMap.remove(zombie0.OnlineID);
        zombie0.OnlineID = -1;
      }

      SharedDescriptors.releasePlayerZombieDescriptor(zombie0);

      assert !VirtualZombieManager.instance.isReused(zombie0);

      if (!zombie0.isDead()) {
        if (!GameClient.bClient) {
          if (!this.Zombies.contains(zombie0)) {
            this.Zombies.add(zombie0);
            noise("added to Zombies " + zombie0);
            zombie0.setStateMachineLocked(false);
            zombie0.changeState(ZombieIdleState.instance());
          }
        }
      }
    }
  }

  void saveReanimatedPlayers() {
    if (!GameClient.bClient) {
      std::vector arrayList = new ArrayList();

      try {
        ByteBuffer byteBuffer = SliceY.SliceBuffer;
        byteBuffer.clear();
        byteBuffer.putInt(195);
        arrayList.addAll(this.Zombies);

        for (IsoZombie zombie0 :
             IsoWorld.instance.CurrentCell.getZombieList()) {
          if (zombie0.isReanimatedPlayer() && !zombie0.isDead() &&
              !arrayList.contains(zombie0)) {
            arrayList.add(zombie0);
          }
        }

        byteBuffer.putInt(arrayList.size());

        for (auto &zombie1 : arrayList)
          zombie1.save(byteBuffer);
      }

      File file =
          ZomboidFileSystem.instance.getFileInCurrentSave("reanimated.bin");
      FileOutputStream fileOutputStream = new FileOutputStream(file);
      BufferedOutputStream bufferedOutputStream =
          new BufferedOutputStream(fileOutputStream);
      bufferedOutputStream.write(byteBuffer.array(), 0, byteBuffer.position());
      bufferedOutputStream.flush();
      bufferedOutputStream.close();
    }
    catch (Exception exception) {
      ExceptionLogger.logException(exception);
      return;
    }

    noise("saved " + arrayList.size() + " zombies");
  }
}

    void loadReanimatedPlayers() {
  if (!GameClient.bClient) {
    this.Zombies.clear();
    File file =
        ZomboidFileSystem.instance.getFileInCurrentSave("reanimated.bin");

    try(FileInputStream fileInputStream = new FileInputStream(file);
        BufferedInputStream bufferedInputStream =
            new BufferedInputStream(fileInputStream);) {
      synchronized(SliceY.SliceBufferLock) {
        ByteBuffer byteBuffer = SliceY.SliceBuffer;
        byteBuffer.clear();
        int int0 = bufferedInputStream.read(byteBuffer.array());
        byteBuffer.limit(int0);
        this.loadReanimatedPlayers(byteBuffer);
      }
    }
    catch (FileNotFoundException fileNotFoundException) {
      return;
    }
    catch (Exception exception) {
      ExceptionLogger.logException(exception);
      return;
    }

    noise("loaded " + this.Zombies.size() + " zombies");
  }
}

void loadReanimatedPlayers(ByteBuffer byteBuffer) {
  int int0 = byteBuffer.getInt();
  int int1 = byteBuffer.getInt();

  for (int int2 = 0; int2 < int1; int2++) {
    if (!(IsoObject.factoryFromFileInput(IsoWorld.instance.CurrentCell,
                                         byteBuffer)
              instanceof IsoZombie zombie0)) {
      throw new RuntimeException("expected IsoZombie here");
    }

    zombie0.load(byteBuffer, int0);
    zombie0.getDescriptor().setID(0);
    zombie0.setReanimatedPlayer(true);
    IsoWorld.instance.CurrentCell.getAddList().remove(zombie0);
    IsoWorld.instance.CurrentCell.getObjectList().remove(zombie0);
    IsoWorld.instance.CurrentCell.getZombieList().remove(zombie0);
    this.Zombies.add(zombie0);
  }
}
}
} // namespace zombie
