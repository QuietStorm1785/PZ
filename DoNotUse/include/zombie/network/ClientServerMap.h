#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/Core.h"
#include "zombie/core/SpriteRenderer.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/core/textures/Texture.h"
#include "zombie/iso/IsoChunk.h"
#include "zombie/iso/IsoChunkMap.h"
#include "zombie/iso/IsoUtils.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/network/PacketTypes/PacketType.h"
#include "zombie/network/ServerMap/ServerCell.h"
#include <algorithm>
#include <filesystem>

namespace zombie {
namespace network {


class ClientServerMap {
public:
    static const int ChunksPerServerCell = 5;
    static const int SquaresPerServerCell = 50;
    int playerIndex;
    int centerX;
    int centerY;
    int chunkGridWidth;
    int width;
   boolean[] loaded;
   private static boolean[] isLoaded;
    static Texture trafficCone;

    public ClientServerMap(int var1, int var2, int var3, int var4) {
      this.playerIndex = var1;
      this.centerX = var2;
      this.centerY = var3;
      this.chunkGridWidth = var4;
      this.width = (var4 - 1) * 10 / 50;
      if ((var4 - 1) * 10 % 50 != 0) {
         this.width++;
      }

      this.width++;
      this.loaded = new boolean[this.width * this.width];
   }

    int getMinX() {
      return (this.centerX / 10 - this.chunkGridWidth / 2) / 5;
   }

    int getMinY() {
      return (this.centerY / 10 - this.chunkGridWidth / 2) / 5;
   }

    int getMaxX() {
      return this.getMinX() + this.width - 1;
   }

    int getMaxY() {
      return this.getMinY() + this.width - 1;
   }

    bool isValidCell(int var1, int var2) {
      return var1 >= 0 && var2 >= 0 && var1 < this.width && var2 < this.width;
   }

    bool setLoaded() {
      if (!GameServer.bServer) {
    return false;
      } else {
    int var1 = ServerMap.instance.getMinX();
    int var2 = ServerMap.instance.getMinY();
    int var3 = this.getMinX();
    int var4 = this.getMinY();
    bool var5 = false;

         for (int var6 = 0; var6 < this.width; var6++) {
            for (int var7 = 0; var7 < this.width; var7++) {
    ServerCell var8 = ServerMap.instance.getCell(var3 + var7 - var1, var4 + var6 - var2);
    bool var9 = var8 == nullptr ? false : var8.bLoaded;
               var5 |= this.loaded[var7 + var6 * this.width] != var9;
               this.loaded[var7 + var6 * this.width] = var9;
            }
         }

    return var5;
      }
   }

    bool setPlayerPosition(int var1, int var2) {
      if (!GameServer.bServer) {
    return false;
      } else {
    int var3 = this.getMinX();
    int var4 = this.getMinY();
         this.centerX = var1;
         this.centerY = var2;
         return this.setLoaded() || var3 != this.getMinX() || var4 != this.getMinY();
      }
   }

    static bool isChunkLoaded(int var0, int var1) {
      if (!GameClient.bClient) {
    return false;
      } else if (var0 >= 0 && var1 >= 0) {
         for (int var2 = 0; var2 < IsoPlayer.numPlayers; var2++) {
    ClientServerMap var3 = GameClient.loadedCells[var2];
            if (var3 != nullptr) {
    int var4 = var0 / 5 - var3.getMinX();
    int var5 = var1 / 5 - var3.getMinY();
               if (var3.isValidCell(var4, var5) && var3.loaded[var4 + var5 * var3.width]) {
    return true;
               }
            }
         }

    return false;
      } else {
    return false;
      }
   }

    static void characterIn(UdpConnection var0, int var1) {
      if (GameServer.bServer) {
    ClientServerMap var2 = var0.loadedCells[var1];
         if (var2 != nullptr) {
    IsoPlayer var3 = var0.players[var1];
            if (var3 != nullptr) {
               if (var2.setPlayerPosition((int)var3.x, (int)var3.y)) {
                  var2.sendPacket(var0);
               }
            }
         }
      }
   }

    void sendPacket(UdpConnection var1) {
      if (GameServer.bServer) {
    ByteBufferWriter var2 = var1.startPacket();
         PacketType.ServerMap.doPacket(var2);
         var2.putByte((byte)this.playerIndex);
         var2.putInt(this.centerX);
         var2.putInt(this.centerY);

         for (int var3 = 0; var3 < this.width; var3++) {
            for (int var4 = 0; var4 < this.width; var4++) {
               var2.putBoolean(this.loaded[var4 + var3 * this.width]);
            }
         }

         PacketType.ServerMap.send(var1);
      }
   }

    static void receivePacket(ByteBuffer var0) {
      if (GameClient.bClient) {
    uint8_t var1 = var0.get();
    int var2 = var0.getInt();
    int var3 = var0.getInt();
    ClientServerMap var4 = GameClient.loadedCells[var1];
         if (var4 == nullptr) {
            var4 = GameClient.loadedCells[var1] = std::make_shared<ClientServerMap>(var1, var2, var3, IsoChunkMap.ChunkGridWidth);
         }

         var4.centerX = var2;
         var4.centerY = var3;

         for (int var5 = 0; var5 < var4.width; var5++) {
            for (int var6 = 0; var6 < var4.width; var6++) {
               var4.loaded[var6 + var5 * var4.width] = var0.get() == 1;
            }
         }
      }
   }

    static void render(int var0) {
      if (GameClient.bClient) {
    IsoChunkMap var1 = IsoWorld.instance.CurrentCell.getChunkMap(var0);
         if (var1 != nullptr && !var1.ignore) {
    int var2 = Core.TileScale;
    uint8_t var3 = 10;
    float var4 = 0.1F;
    float var5 = 0.1F;
    float var6 = 0.1F;
    float var7 = 0.75F;
    float var8 = 0.0F;
            if (trafficCone == nullptr) {
               trafficCone = Texture.getSharedTexture("street_decoration_01_26");
            }

    Texture var9 = trafficCone;
            if (isLoaded == nullptr || isLoaded.length < IsoChunkMap.ChunkGridWidth * IsoChunkMap.ChunkGridWidth) {
               isLoaded = new boolean[IsoChunkMap.ChunkGridWidth * IsoChunkMap.ChunkGridWidth];
            }

            for (int var10 = 0; var10 < IsoChunkMap.ChunkGridWidth; var10++) {
               for (int var11 = 0; var11 < IsoChunkMap.ChunkGridWidth; var11++) {
    IsoChunk var12 = var1.getChunk(var11, var10);
                  if (var12 != nullptr) {
                     isLoaded[var11 + var10 * IsoChunkMap.ChunkGridWidth] = isChunkLoaded(var12.wx, var12.wy);
                  }
               }
            }

            for (int var21 = 0; var21 < IsoChunkMap.ChunkGridWidth; var21++) {
               for (int var22 = 0; var22 < IsoChunkMap.ChunkGridWidth; var22++) {
    IsoChunk var23 = var1.getChunk(var22, var21);
                  if (var23 != nullptr) {
    bool var13 = isLoaded[var22 + var21 * IsoChunkMap.ChunkGridWidth];
                     if (var13 && var9 != nullptr) {
    IsoChunk var14 = var1.getChunk(var22, var21 - 1);
                        if (var14 != nullptr && !isLoaded[var22 + (var21 - 1) * IsoChunkMap.ChunkGridWidth]) {
                           for (int var15 = 0; var15 < var3; var15++) {
    float var16 = IsoUtils.XToScreenExact(var23.wx * var3 + var15, var23.wy * var3, var8, 0);
    float var17 = IsoUtils.YToScreenExact(var23.wx * var3 + var15, var23.wy * var3, var8, 0);
                              SpriteRenderer.instance
                                 .render(var9, var16 - var9.getWidth() / 2, var17, var9.getWidth(), var9.getHeight(), 1.0F, 1.0F, 1.0F, 1.0F, nullptr);
                           }
                        }

    IsoChunk var25 = var1.getChunk(var22, var21 + 1);
                        if (var25 != nullptr && !isLoaded[var22 + (var21 + 1) * IsoChunkMap.ChunkGridWidth]) {
                           for (int var27 = 0; var27 < var3; var27++) {
    float var30 = IsoUtils.XToScreenExact(var23.wx * var3 + var27, var23.wy * var3 + (var3 - 1), var8, 0);
    float var18 = IsoUtils.YToScreenExact(var23.wx * var3 + var27, var23.wy * var3 + (var3 - 1), var8, 0);
                              SpriteRenderer.instance
                                 .render(var9, var30 - var9.getWidth() / 2, var18, var9.getWidth(), var9.getHeight(), 1.0F, 1.0F, 1.0F, 1.0F, nullptr);
                           }
                        }

    IsoChunk var28 = var1.getChunk(var22 - 1, var21);
                        if (var28 != nullptr && !isLoaded[var22 - 1 + var21 * IsoChunkMap.ChunkGridWidth]) {
                           for (int var31 = 0; var31 < var3; var31++) {
    float var34 = IsoUtils.XToScreenExact(var23.wx * var3, var23.wy * var3 + var31, var8, 0);
    float var19 = IsoUtils.YToScreenExact(var23.wx * var3, var23.wy * var3 + var31, var8, 0);
                              SpriteRenderer.instance
                                 .render(var9, var34 - var9.getWidth() / 2, var19, var9.getWidth(), var9.getHeight(), 1.0F, 1.0F, 1.0F, 1.0F, nullptr);
                           }
                        }

    IsoChunk var32 = var1.getChunk(var22 + 1, var21);
                        if (var32 != nullptr && !isLoaded[var22 + 1 + var21 * IsoChunkMap.ChunkGridWidth]) {
                           for (int var35 = 0; var35 < var3; var35++) {
    float var36 = IsoUtils.XToScreenExact(var23.wx * var3 + (var3 - 1), var23.wy * var3 + var35, var8, 0);
    float var20 = IsoUtils.YToScreenExact(var23.wx * var3 + (var3 - 1), var23.wy * var3 + var35, var8, 0);
                              SpriteRenderer.instance
                                 .render(var9, var36 - var9.getWidth() / 2, var20, var9.getWidth(), var9.getHeight(), 1.0F, 1.0F, 1.0F, 1.0F, nullptr);
                           }
                        }
                     }

                     if (!var13) {
    float var24 = var23.wx * var3;
    float var26 = var23.wy * var3;
    float var29 = IsoUtils.XToScreenExact(var24, var26 + var3, var8, 0);
    float var33 = IsoUtils.YToScreenExact(var24, var26 + var3, var8, 0);
                        SpriteRenderer.instance
                           .renderPoly(
                              (int)var29,
                              (int)var33,
                              (int)(var29 + var3 * 64 / 2 * var2),
                              (int)(var33 - var3 * 32 / 2 * var2),
                              (int)(var29 + var3 * 64 * var2),
                              (int)var33,
                              (int)(var29 + var3 * 64 / 2 * var2),
                              (int)(var33 + var3 * 32 / 2 * var2),
                              var4,
                              var5,
                              var6,
                              var7
                           );
                     }
                  }
               }
            }
         }
      }
   }

    static void Reset() {
      Arrays.fill(GameClient.loadedCells, nullptr);
      trafficCone = nullptr;
   }
}
} // namespace network
} // namespace zombie
