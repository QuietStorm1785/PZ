#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/inventory/CompressIdenticalItems.h"
#include "zombie/inventory/InventoryItem.h"
#include "zombie/inventory/ItemContainer.h"
#include "zombie/inventory/ItemPickerJava.h"
#include "zombie/iso/BuildingDef.h"
#include "zombie/iso/IsoChunk.h"
#include "zombie/iso/IsoChunkMap.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoMetaGrid/Zone.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/objects/IsoCompost.h"
#include "zombie/iso/objects/IsoDeadBody.h"
#include "zombie/iso/objects/IsoThumpable.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/PacketTypes/PacketType.h"
#include "zombie/network/ServerMap.h"
#include "zombie/network/ServerMap/ServerCell.h"
#include "zombie/network/ServerOptions.h"

namespace zombie {


class LootRespawn {
public:
    static int LastRespawnHour = -1;
   private static final ArrayList<InventoryItem> existingItems = std::make_unique<ArrayList<>>();
   private static final ArrayList<InventoryItem> newItems = std::make_unique<ArrayList<>>();

    static void update() {
      if (!GameClient.bClient) {
    int var0 = getRespawnInterval();
         if (var0 > 0) {
    int var1 = 7 + (int)(GameTime.getInstance().getWorldAgeHours() / var0) * var0;
            if (LastRespawnHour < var1) {
               LastRespawnHour = var1;
               if (GameServer.bServer) {
                  for (int var2 = 0; var2 < ServerMap.instance.LoadedCells.size(); var2++) {
    ServerCell var3 = static_cast<ServerCell>(ServerMap).instance.LoadedCells.get(var2);
                     if (var3.bLoaded) {
                        for (int var4 = 0; var4 < 5; var4++) {
                           for (int var5 = 0; var5 < 5; var5++) {
    IsoChunk var6 = var3.chunks[var5][var4];
                              checkChunk(var6);
                           }
                        }
                     }
                  }
               } else {
                  for (int var7 = 0; var7 < IsoPlayer.numPlayers; var7++) {
    IsoChunkMap var8 = IsoWorld.instance.CurrentCell.ChunkMap[var7];
                     if (!var8.ignore) {
                        for (int var9 = 0; var9 < IsoChunkMap.ChunkGridWidth; var9++) {
                           for (int var10 = 0; var10 < IsoChunkMap.ChunkGridWidth; var10++) {
    IsoChunk var11 = var8.getChunk(var10, var9);
                              checkChunk(var11);
                           }
                        }
                     }
                  }
               }
            }
         }
      }
   }

    static void Reset() {
      LastRespawnHour = -1;
   }

    static void chunkLoaded(IsoChunk var0) {
      if (!GameClient.bClient) {
         checkChunk(var0);
      }
   }

    static void checkChunk(IsoChunk var0) {
      if (var0 != nullptr) {
    int var1 = getRespawnInterval();
         if (var1 > 0) {
            if (!(GameTime.getInstance().getWorldAgeHours() < var1)) {
    int var2 = 7 + (int)(GameTime.getInstance().getWorldAgeHours() / var1) * var1;
               if (var0.lootRespawnHour > var2) {
                  var0.lootRespawnHour = var2;
               }

               if (var0.lootRespawnHour < var2) {
                  var0.lootRespawnHour = var2;
                  respawnInChunk(var0);
               }
            }
         }
      }
   }

    static int getRespawnInterval() {
      if (GameServer.bServer) {
         return ServerOptions.instance.HoursForLootRespawn.getValue();
      } else {
         if (!GameClient.bClient) {
    int var0 = SandboxOptions.instance.LootRespawn.getValue();
            if (var0 == 1) {
    return 0;
            }

            if (var0 == 2) {
    return 24;
            }

            if (var0 == 3) {
    return 168;
            }

            if (var0 == 4) {
    return 720;
            }

            if (var0 == 5) {
    return 1440;
            }
         }

    return 0;
      }
   }

    static void respawnInChunk(IsoChunk var0) {
    bool var1 = GameServer.bServer && ServerOptions.instance.ConstructionPreventsLootRespawn.getValue();
    int var2 = SandboxOptions.instance.SeenHoursPreventLootRespawn.getValue();
    double var3 = GameTime.getInstance().getWorldAgeHours();

      for (int var5 = 0; var5 < 10; var5++) {
         for (int var6 = 0; var6 < 10; var6++) {
    IsoGridSquare var7 = var0.getGridSquare(var6, var5, 0);
    Zone var8 = var7 == null ? null : var7.getZone();
            if (var8 != nullptr
               && ("TownZone" == var8.getType()) || "TownZones" == var8.getType()) || "TrailerPark" == var8.getType()))
               && (!var1 || !var8.haveConstruction)
               && (var2 <= 0 || !(var8.getHoursSinceLastSeen() <= var2))) {
               if (var7.getBuilding() != nullptr) {
    BuildingDef var9 = var7.getBuilding().getDef();
                  if (var9 != nullptr) {
                     if (var9.lootRespawnHour > var3) {
                        var9.lootRespawnHour = 0;
                     }

                     if (var9.lootRespawnHour < var0.lootRespawnHour) {
                        var9.setKeySpawned(0);
                        var9.lootRespawnHour = var0.lootRespawnHour;
                     }
                  }
               }

               for (int var17 = 0; var17 < 8; var17++) {
                  var7 = var0.getGridSquare(var6, var5, var17);
                  if (var7 != nullptr) {
    int var10 = var7.getObjects().size();
                     std::vector<IsoObject> var11 = (IsoObject[])var7.getObjects().getElements();

                     for (int var12 = 0; var12 < var10; var12++) {
    IsoObject var13 = var11[var12];
                        if (!(var13 instanceof IsoDeadBody) && !(var13 instanceof IsoThumpable) && !(var13 instanceof IsoCompost)) {
                           for (int var14 = 0; var14 < var13.getContainerCount(); var14++) {
    ItemContainer var15 = var13.getContainerByIndex(var14);
                              if (var15.bExplored && var15.isHasBeenLooted()) {
                                 respawnInContainer(var13, var15);
                              }
                           }
                        }
                     }
                  }
               }
            }
         }
      }
   }

    static void respawnInContainer(IsoObject var0, ItemContainer var1) {
      if (var1 != nullptr && var1.getItems() != nullptr) {
    int var2 = var1.getItems().size();
    int var3 = 5;
         if (GameServer.bServer) {
            var3 = ServerOptions.instance.MaxItemsForLootRespawn.getValue();
         }

         if (var2 < var3) {
            existingItems.clear();
            existingItems.addAll(var1.getItems());
            ItemPickerJava.fillContainer(var1, nullptr);
    std::vector var4 = var1.getItems();
            if (var4 != nullptr && var2 != var4.size()) {
               var1.setHasBeenLooted(false);
               newItems.clear();

               for (int var5 = 0; var5 < var4.size(); var5++) {
    InventoryItem var6 = static_cast<InventoryItem>(var4).get(var5);
                  if (!existingItems.contains(var6)) {
                     newItems.add(var6);
                     var6.setAge(0.0F);
                  }
               }

               ItemPickerJava.updateOverlaySprite(var0);
               if (GameServer.bServer) {
                  for (int var10 = 0; var10 < GameServer.udpEngine.connections.size(); var10++) {
    UdpConnection var11 = static_cast<UdpConnection>(GameServer).udpEngine.connections.get(var10);
                     if (var11.RelevantTo(var0.square.x, var0.square.y)) {
    ByteBufferWriter var7 = var11.startPacket();
                        PacketType.AddInventoryItemToContainer.doPacket(var7);
                        var7.putShort((short)2);
                        var7.putInt((int)var0.getX());
                        var7.putInt((int)var0.getY());
                        var7.putInt((int)var0.getZ());
                        var7.putByte((byte)var0.getObjectIndex());
                        var7.putByte((byte)var0.getContainerIndex(var1));

                        try {
                           CompressIdenticalItems.save(var7.bb, newItems, nullptr);
                        } catch (Exception var9) {
                           var9.printStackTrace();
                        }

                        PacketType.AddInventoryItemToContainer.send(var11);
                     }
                  }
               }
            }
         }
      }
   }
}
} // namespace zombie
