#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/SharedDescriptors/Descriptor.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoZombie.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/core/skinnedmodel/visual/ItemVisual.h"
#include "zombie/core/skinnedmodel/visual/ItemVisuals.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/PacketTypes/PacketType.h"
#include "zombie/util/Type.h"

namespace zombie {


class SharedDescriptors {
public:
    static const int DESCRIPTOR_COUNT = 500;
    static const int DESCRIPTOR_ID_START = 500;
   private static final std::vector<byte> DESCRIPTOR_MAGIC = std::make_shared<std::vector<byte>>(){68, 69, 83, 67};
    static const int VERSION_1 = 1;
    static const int VERSION_2 = 2;
    static const int VERSION = 2;
   private static std::vector<Descriptor> PlayerZombieDescriptors = std::make_shared<std::array<Descriptor, 10>>();
    static const int FIRST_PLAYER_ZOMBIE_DESCRIPTOR_ID = 1000;

    static void initSharedDescriptors() {
      if (GameServer.bServer) {
         ;
      }
   }

    static void noise(const std::string& var0) {
      DebugLog.log("shared-descriptor: " + var0);
   }

    static void createPlayerZombieDescriptor(IsoZombie var0) {
      if (GameServer.bServer) {
         if (var0.isReanimatedPlayer()) {
            if (var0.getDescriptor().getID() == 0) {
    int var1 = -1;

               for (int var2 = 0; var2 < PlayerZombieDescriptors.length; var2++) {
                  if (PlayerZombieDescriptors[var2] == nullptr) {
                     var1 = var2;
                     break;
                  }
               }

               if (var1 == -1) {
                  std::vector<Descriptor> var10 = new Descriptor[PlayerZombieDescriptors.length + 10];
                  System.arraycopy(PlayerZombieDescriptors, 0, var10, 0, PlayerZombieDescriptors.length);
                  var1 = PlayerZombieDescriptors.length;
                  PlayerZombieDescriptors = var10;
                  noise("resized PlayerZombieDescriptors array size=" + PlayerZombieDescriptors.length);
               }

               var0.getDescriptor().setID(1000 + var1);
    int var11 = PersistentOutfits.instance.pickOutfit("ReanimatedPlayer", var0.isFemale());
               var11 = var11 & -65536 | var1 + 1;
               var0.setPersistentOutfitID(var11);
    auto var3 = std::make_shared<Descriptor>();
               var3.bFemale = var0.isFemale();
               var3.bZombie = false;
               var3.ID = 1000 + var1;
               var3.persistentOutfitID = var11;
               var3.getHumanVisual().copyFrom(var0.getHumanVisual());
    auto var4 = std::make_shared<ItemVisuals>();
               var0.getItemVisuals(var4);

               for (int var5 = 0; var5 < var4.size(); var5++) {
    auto var6 = std::make_shared<ItemVisual>(static_cast<ItemVisual>(var4).get(var5));
                  var3.itemVisuals.add(var6);
               }

               PlayerZombieDescriptors[var1] = var3;
               noise("added id=" + var3.getID());

               for (int var13 = 0; var13 < GameServer.udpEngine.connections.size(); var13++) {
    UdpConnection var14 = static_cast<UdpConnection>(GameServer).udpEngine.connections.get(var13);
    ByteBufferWriter var7 = var14.startPacket();

                  try {
                     PacketType.ZombieDescriptors.doPacket(var7);
                     var3.save(var7.bb);
                     PacketType.ZombieDescriptors.send(var14);
                  } catch (Exception var9) {
                     var9.printStackTrace();
                     var14.cancelPacket();
                  }
               }
            }
         }
      }
   }

    static void releasePlayerZombieDescriptor(IsoZombie var0) {
      if (GameServer.bServer) {
         if (var0.isReanimatedPlayer()) {
    int var1 = var0.getDescriptor().getID() - 1000;
            if (var1 >= 0 && var1 < PlayerZombieDescriptors.length) {
               noise("released id=" + var0.getDescriptor().getID());
               var0.getDescriptor().setID(0);
               PlayerZombieDescriptors[var1] = nullptr;
            }
         }
      }
   }

   public static Descriptor[] getPlayerZombieDescriptors() {
    return PlayerZombieDescriptors;
   }

    static void registerPlayerZombieDescriptor(Descriptor var0) {
      if (GameClient.bClient) {
    int var1 = var0.getID() - 1000;
         if (var1 >= 0 && var1 < 32767) {
            if (PlayerZombieDescriptors.length <= var1) {
    int var2 = (var1 + 10) / 10 * 10;
               std::vector<Descriptor> var3 = new Descriptor[var2];
               System.arraycopy(PlayerZombieDescriptors, 0, var3, 0, PlayerZombieDescriptors.length);
               PlayerZombieDescriptors = var3;
               noise("resized PlayerZombieDescriptors array size=" + PlayerZombieDescriptors.length);
            }

            PlayerZombieDescriptors[var1] = var0;
            noise("registered id=" + var0.getID());
         }
      }
   }

    static void ApplyReanimatedPlayerOutfit(int var0, const std::string& var1, IsoGameCharacter var2) {
    IsoZombie var3 = static_cast<IsoZombie>(Type).tryCastTo(var2, IsoZombie.class);
      if (var3 != nullptr) {
    short var4 = (short)(var0 & 65535);
         if (var4 >= 1 && var4 <= PlayerZombieDescriptors.length) {
    Descriptor var5 = PlayerZombieDescriptors[var4 - 1];
            if (var5 != nullptr) {
               var3.useDescriptor(var5);
            }
         }
      }
   }
}
} // namespace zombie
