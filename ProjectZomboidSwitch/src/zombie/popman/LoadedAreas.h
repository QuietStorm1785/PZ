#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/iso/IsoChunkMap.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/Vector3.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/ServerMap.h"
#include "zombie/network/ServerMap/ServerCell.h"

namespace zombie {
namespace popman {


class LoadedAreas {
public:
    static const int MAX_AREAS = 64;
   public int[] areas = new int[256];
    int count;
    bool changed;
   public int[] prevAreas = new int[256];
    int prevCount;
    bool serverCells;

    public LoadedAreas(bool var1) {
      this.serverCells = var1;
   }

    bool set() {
      this.setPrev();
      this.clear();
      if (GameServer.bServer) {
         if (this.serverCells) {
            for (int var1 = 0; var1 < ServerMap.instance.LoadedCells.size(); var1++) {
    ServerCell var2 = (ServerCell)ServerMap.instance.LoadedCells.get(var1);
               this.push_back(var2.WX * 5, var2.WY * 5, 5, 5);
            }
         } else {
            for (int var6 = 0; var6 < GameServer.Players.size(); var6++) {
    IsoPlayer var9 = (IsoPlayer)GameServer.Players.get(var6);
    int var3 = (int)var9.x / 10;
    int var4 = (int)var9.y / 10;
               this.push_back(var3 - var9.OnlineChunkGridWidth / 2, var4 - var9.OnlineChunkGridWidth / 2, var9.OnlineChunkGridWidth, var9.OnlineChunkGridWidth);
            }

            for (int var7 = 0; var7 < GameServer.udpEngine.connections.size(); var7++) {
    UdpConnection var10 = (UdpConnection)GameServer.udpEngine.connections.get(var7);

               for (int var12 = 0; var12 < 4; var12++) {
    Vector3 var13 = var10.connectArea[var12];
                  if (var13 != nullptr) {
    int var5 = (int)var13.z;
                     this.push_back((int)var13.x - var5 / 2, (int)var13.y - var5 / 2, var5, var5);
                  }
               }
            }
         }
      } else {
         for (int var8 = 0; var8 < IsoPlayer.numPlayers; var8++) {
    IsoChunkMap var11 = IsoWorld.instance.CurrentCell.ChunkMap[var8];
            if (!var11.ignore) {
               this.push_back(var11.getWorldXMin(), var11.getWorldYMin(), IsoChunkMap.ChunkGridWidth, IsoChunkMap.ChunkGridWidth);
            }
         }
      }

      return this.changed = this.compareWithPrev();
   }

    void add(int var1, int var2, int var3, int var4) {
      if (this.count < 64) {
    int var5 = this.count * 4;
         this.areas[var5++] = var1;
         this.areas[var5++] = var2;
         this.areas[var5++] = var3;
         this.areas[var5++] = var4;
         this.count++;
      }
   }

    void clear() {
      this.count = 0;
      this.changed = false;
   }

    void copy(LoadedAreas var1) {
      this.count = var1.count;

      for (int var2 = 0; var2 < this.count; var2++) {
    int var3 = var2 * 4;
         this.areas[var3] = var1.areas[var3++];
         this.areas[var3] = var1.areas[var3++];
         this.areas[var3] = var1.areas[var3++];
         this.areas[var3] = var1.areas[var3++];
      }
   }

    void setPrev() {
      this.prevCount = this.count;

      for (int var1 = 0; var1 < this.count; var1++) {
    int var2 = var1 * 4;
         this.prevAreas[var2] = this.areas[var2++];
         this.prevAreas[var2] = this.areas[var2++];
         this.prevAreas[var2] = this.areas[var2++];
         this.prevAreas[var2] = this.areas[var2++];
      }
   }

    bool compareWithPrev() {
      if (this.prevCount != this.count) {
    return true;
      } else {
         for (int var1 = 0; var1 < this.count; var1++) {
    int var2 = var1 * 4;
            if (this.prevAreas[var2] != this.areas[var2++]) {
    return true;
            }

            if (this.prevAreas[var2] != this.areas[var2++]) {
    return true;
            }

            if (this.prevAreas[var2] != this.areas[var2++]) {
    return true;
            }

            if (this.prevAreas[var2] != this.areas[var2++]) {
    return true;
            }
         }

    return false;
      }
   }

    bool isOnEdge(int var1, int var2) {
      if (var1 % 10 != 0 && (var1 + 1) % 10 != 0 && var2 % 10 != 0 && (var2 + 1) % 10 != 0) {
    return false;
      } else {
    int var3 = 0;

         while (var3 < this.count) {
    int var4 = var3 * 4;
    int var5 = this.areas[var4++] * 10;
    int var6 = this.areas[var4++] * 10;
    int var7 = var5 + this.areas[var4++] * 10;
    int var8 = var6 + this.areas[var4++] * 10;
    bool var9 = var1 >= var5 && var1 < var7;
    bool var10 = var2 >= var6 && var2 < var8;
            if (!var9 || var2 != var6 && var2 != var8 - 1) {
               if (!var10 || var1 != var5 && var1 != var7 - 1) {
                  var3++;
                  continue;
               }

    return true;
            }

    return true;
         }

    return false;
      }
   }
}
} // namespace popman
} // namespace zombie
