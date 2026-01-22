#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/Lua/LuaEventManager.h"
#include "zombie/SystemDisabler.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/core/raknet/UdpEngine.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/inventory/ItemContainer.h"
#include "zombie/iso/ObjectsSyncRequests/SyncIsoChunk.h"
#include "zombie/iso/ObjectsSyncRequests/SyncIsoGridSquare.h"
#include "zombie/iso/ObjectsSyncRequests/SyncIsoObject.h"
#include "zombie/iso/objects/IsoLightSwitch.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/PacketTypes/PacketType.h"
#include "zombie/network/ServerMap.h"
#include "zombie/network/WorldItemTypes.h"
#include <filesystem>

namespace zombie {
namespace iso {


class ObjectsSyncRequests {
public:
    static const short ClientSendChunkHashes = 1;
    static const short ServerSendGridSquareHashes = 2;
    static const short ClientSendGridSquareRequest = 3;
    static const short ServerSendGridSquareObjectsHashes = 4;
    static const short ClientSendObjectRequests = 5;
    static const short ServerSendObject = 6;
   public std::vector<SyncIsoChunk> requestsSyncIsoChunk;
   public std::vector<SyncIsoGridSquare> requestsSyncIsoGridSquare;
   public std::vector<SyncIsoObject> requestsSyncIsoObject;
    long timeout = 1000L;

    public ObjectsSyncRequests(bool var1) {
      if (var1) {
         this.requestsSyncIsoChunk = std::make_unique<std::vector<>>();
         this.requestsSyncIsoGridSquare = std::make_unique<std::vector<>>();
         this.requestsSyncIsoObject = std::make_unique<std::vector<>>();
      } else {
         this.requestsSyncIsoGridSquare = std::make_unique<std::vector<>>();
      }
   }

    static int getObjectInsertIndex(long[] var0, long[] var1, long var2) {
      if (var2 == var1[0]) {
    return 0;
      } else {
         for (int var4 = 0; var4 < var0.length; var4++) {
            if (var0[var4] == var2) {
               return -1;
            }
         }

    int var6 = 0;

         for (int var5 = 0; var5 < var1.length; var5++) {
            if (var6 < var0.length && var1[var5] == var0[var6]) {
               var6++;
            }

            if (var1[var5] == var2) {
    return var6;
            }
         }

         return -1;
      }
   }

    void putRequestSyncIsoChunk(IsoChunk var1) {
      if (!GameClient.bClient || SystemDisabler.doWorldSyncEnable) {
    SyncIsoChunk var2 = std::make_shared<SyncIsoChunk>(this);
         var2.x = var1.wx;
         var2.y = var1.wy;
         var2.hashCodeObjects = var1.getHashCodeObjects();
         var2.reqTime = 0L;
         var2.reqCount = 0;
         /* synchronized - TODO: add std::mutex */ (this.requestsSyncIsoChunk) {
            this.requestsSyncIsoChunk.push_back(var2);
         }
      }
   }

    void putRequestSyncItemContainer(ItemContainer var1) {
      if (var1 != nullptr && var1.parent != nullptr && var1.parent.square != nullptr) {
         this.putRequestSyncIsoGridSquare(var1.parent.square);
      }
   }

    void putRequestSyncIsoGridSquare(IsoGridSquare var1) {
      if (var1 != nullptr) {
    SyncIsoGridSquare var2 = std::make_shared<SyncIsoGridSquare>(this);
         var2.x = var1.x;
         var2.y = var1.y;
         var2.z = var1.z;
         var2.reqTime = 0L;
         var2.reqCount = 0;
         /* synchronized - TODO: add std::mutex */ (this.requestsSyncIsoGridSquare) {
            if (!this.requestsSyncIsoGridSquare.contains(var1)) {
               this.requestsSyncIsoGridSquare.push_back(var2);
            } else {
               DebugLog.log("Warning: [putRequestSyncIsoGridSquare] Tryed to add dublicate object.");
            }
         }
      }
   }

    void sendRequests(UdpConnection var1) {
      if (SystemDisabler.doWorldSyncEnable) {
         if (this.requestsSyncIsoChunk != nullptr && this.requestsSyncIsoChunk.size() != 0) {
    ByteBufferWriter var2 = var1.startPacket();
            PacketType.SyncObjects.doPacket(var2);
            var2.putShort((short)1);
    ByteBuffer var3 = var2.bb;
    int var4 = var3.position();
            var2.putShort((short)0);
    int var5 = 0;
            /* synchronized - TODO: add std::mutex */ (this.requestsSyncIsoChunk) {
               for (int var7 = this.requestsSyncIsoChunk.size() - 1; var7 >= 0; var7--) {
    SyncIsoChunk var8 = this.requestsSyncIsoChunk.get(var7);
                  if (var8.reqCount > 3) {
                     this.requestsSyncIsoChunk.remove(var7);
                  } else {
                     if (var8.reqTime == 0L) {
                        var8.reqTime = System.currentTimeMillis();
                        var5++;
                        var3.putInt(var8.x);
                        var3.putInt(var8.y);
                        var3.putLong(var8.hashCodeObjects);
                        var8.reqCount++;
                     }

                     if (System.currentTimeMillis() - var8.reqTime >= this.timeout) {
                        var8.reqTime = System.currentTimeMillis();
                        var5++;
                        var3.putInt(var8.x);
                        var3.putInt(var8.y);
                        var3.putLong(var8.hashCodeObjects);
                        var8.reqCount++;
                     }

                     if (var5 >= 5) {
                        break;
                     }
                  }
               }
            }

            if (var5 == 0) {
               GameClient.connection.cancelPacket();
               return;
            }

    int var23 = var3.position();
            var3.position(var4);
            var3.putShort((short)var5);
            var3.position(var23);
            PacketType.SyncObjects.send(GameClient.connection);
         }

         if (this.requestsSyncIsoGridSquare != nullptr && this.requestsSyncIsoGridSquare.size() != 0) {
    ByteBufferWriter var15 = var1.startPacket();
            PacketType.SyncObjects.doPacket(var15);
            var15.putShort((short)3);
    ByteBuffer var17 = var15.bb;
    int var19 = var17.position();
            var15.putShort((short)0);
    int var21 = 0;
            /* synchronized - TODO: add std::mutex */ (this.requestsSyncIsoGridSquare) {
               for (int var28 = 0; var28 < this.requestsSyncIsoGridSquare.size(); var28++) {
    SyncIsoGridSquare var30 = this.requestsSyncIsoGridSquare.get(var28);
                  if (var30.reqCount > 3) {
                     this.requestsSyncIsoGridSquare.remove(var28);
                     var28--;
                  } else {
                     if (var30.reqTime == 0L) {
                        var30.reqTime = System.currentTimeMillis();
                        var21++;
                        var17.putInt(var30.x);
                        var17.putInt(var30.y);
                        var17.put((byte)var30.z);
                        var30.reqCount++;
                     }

                     if (System.currentTimeMillis() - var30.reqTime >= this.timeout) {
                        var30.reqTime = System.currentTimeMillis();
                        var21++;
                        var17.putInt(var30.x);
                        var17.putInt(var30.y);
                        var17.put((byte)var30.z);
                        var30.reqCount++;
                     }

                     if (var21 >= 100) {
                        break;
                     }
                  }
               }
            }

            if (var21 == 0) {
               GameClient.connection.cancelPacket();
               return;
            }

    int var25 = var17.position();
            var17.position(var19);
            var17.putShort((short)var21);
            var17.position(var25);
            PacketType.SyncObjects.send(GameClient.connection);
         }

         if (this.requestsSyncIsoObject != nullptr && this.requestsSyncIsoObject.size() != 0) {
    ByteBufferWriter var16 = var1.startPacket();
            PacketType.SyncObjects.doPacket(var16);
            var16.putShort((short)5);
    ByteBuffer var18 = var16.bb;
    int var20 = var18.position();
            var16.putShort((short)0);
    int var22 = 0;
            /* synchronized - TODO: add std::mutex */ (this.requestsSyncIsoObject) {
               for (int var29 = 0; var29 < this.requestsSyncIsoObject.size(); var29++) {
    SyncIsoObject var31 = this.requestsSyncIsoObject.get(var29);
                  if (var31.reqCount > 3) {
                     this.requestsSyncIsoObject.remove(var29);
                     var29--;
                  } else {
                     if (var31.reqTime == 0L) {
                        var31.reqTime = System.currentTimeMillis();
                        var22++;
                        var18.putInt(var31.x);
                        var18.putInt(var31.y);
                        var18.put((byte)var31.z);
                        var18.putLong(var31.hash);
                        var31.reqCount++;
                     }

                     if (System.currentTimeMillis() - var31.reqTime >= this.timeout) {
                        var31.reqTime = System.currentTimeMillis();
                        var22++;
                        var18.putInt(var31.x);
                        var18.putInt(var31.y);
                        var18.put((byte)var31.z);
                        var18.putLong(var31.hash);
                        var31.reqCount++;
                     }

                     if (var22 >= 100) {
                        break;
                     }
                  }
               }
            }

            if (var22 == 0) {
               GameClient.connection.cancelPacket();
               return;
            }

    int var27 = var18.position();
            var18.position(var20);
            var18.putShort((short)var22);
            var18.position(var27);
            PacketType.SyncObjects.send(GameClient.connection);
         }
      }
   }

    void receiveSyncIsoChunk(int var1, int var2) {
      /* synchronized - TODO: add std::mutex */ (this.requestsSyncIsoChunk) {
         for (int var4 = 0; var4 < this.requestsSyncIsoChunk.size(); var4++) {
    SyncIsoChunk var5 = this.requestsSyncIsoChunk.get(var4);
            if (var5.x == var1 && var5.y == var2) {
               this.requestsSyncIsoChunk.remove(var4);
               return;
            }
         }
      }
   }

    void receiveSyncIsoGridSquare(int var1, int var2, int var3) {
      /* synchronized - TODO: add std::mutex */ (this.requestsSyncIsoGridSquare) {
         for (int var5 = 0; var5 < this.requestsSyncIsoGridSquare.size(); var5++) {
    SyncIsoGridSquare var6 = this.requestsSyncIsoGridSquare.get(var5);
            if (var6.x == var1 && var6.y == var2 && var6.z == var3) {
               this.requestsSyncIsoGridSquare.remove(var5);
               return;
            }
         }
      }
   }

    void receiveSyncIsoObject(int var1, int var2, int var3, long var4) {
      /* synchronized - TODO: add std::mutex */ (this.requestsSyncIsoObject) {
         for (int var7 = 0; var7 < this.requestsSyncIsoObject.size(); var7++) {
    SyncIsoObject var8 = this.requestsSyncIsoObject.get(var7);
            if (var8.x == var1 && var8.y == var2 && var8.z == var3 && var8.hash == var4) {
               this.requestsSyncIsoObject.remove(var7);
               return;
            }
         }
      }
   }

    void receiveGridSquareHashes(ByteBuffer var1) {
    short var2 = var1.getShort();

      for (int var3 = 0; var3 < var2; var3++) {
    short var4 = var1.getShort();
    short var5 = var1.getShort();
    long var6 = var1.getLong();
    short var8 = var1.getShort();

         for (int var9 = 0; var9 < var8; var9++) {
    int var10 = var1.get() + var4 * 10;
    int var11 = var1.get() + var5 * 10;
    uint8_t var12 = var1.get();
    int var13 = var1.getInt();
    IsoGridSquare var14 = IsoWorld.instance.CurrentCell.getGridSquare(var10, var11, var12);
            if (var14 != nullptr) {
    int var15 = var14.getHashCodeObjectsInt();
               if (var15 != var13) {
    SyncIsoGridSquare var16 = std::make_shared<SyncIsoGridSquare>(this);
                  var16.x = var10;
                  var16.y = var11;
                  var16.z = var12;
                  var16.reqTime = 0L;
                  var16.reqCount = 0;
                  /* synchronized - TODO: add std::mutex */ (this.requestsSyncIsoGridSquare) {
                     this.requestsSyncIsoGridSquare.push_back(var16);
                  }
               }
            }
         }

         this.receiveSyncIsoChunk(var4, var5);
      }
   }

    void receiveGridSquareObjectHashes(ByteBuffer var1) {
    short var2 = var1.getShort();

      for (int var3 = 0; var3 < var2; var3++) {
    int var4 = var1.getInt();
    int var5 = var1.getInt();
    uint8_t var6 = var1.get();
         this.receiveSyncIsoGridSquare(var4, var5, var6);
    IsoGridSquare var7 = IsoWorld.instance.CurrentCell.getGridSquare(var4, var5, var6);
         if (var7 == nullptr) {
            return;
         }

    uint8_t var8 = var1.get();
    int var9 = var1.getInt() - 3;
         long[] var10 = new long[var8];

         for (int var11 = 0; var11 < var8; var11++) {
            var10[var11] = var1.getLong();
         }

         try {
            boolean[] var21 = new boolean[var7.getObjects().size()];
            boolean[] var12 = new boolean[var8];

            for (int var13 = 0; var13 < var8; var13++) {
               var12[var13] = true;
            }

            for (int var22 = 0; var22 < var7.getObjects().size(); var22++) {
               var21[var22] = false;
    long var14 = ((IsoObject)var7.getObjects().get(var22)).customHashCode();
    bool var16 = false;

               for (int var17 = 0; var17 < var8; var17++) {
                  if (var10[var17] == var14) {
                     var16 = true;
                     var12[var17] = false;
                     break;
                  }
               }

               if (!var16) {
                  var21[var22] = true;
               }
            }

            for (int var23 = var7.getObjects().size() - 1; var23 >= 0; var23--) {
               if (var21[var23]) {
                  ((IsoObject)var7.getObjects().get(var23)).removeFromWorld();
                  ((IsoObject)var7.getObjects().get(var23)).removeFromSquare();
               }
            }

            for (int var24 = 0; var24 < var8; var24++) {
               if (var12[var24]) {
    SyncIsoObject var25 = std::make_shared<SyncIsoObject>(this);
                  var25.x = var4;
                  var25.y = var5;
                  var25.z = var6;
                  var25.hash = var10[var24];
                  var25.reqTime = 0L;
                  var25.reqCount = 0;
                  /* synchronized - TODO: add std::mutex */ (this.requestsSyncIsoObject) {
                     this.requestsSyncIsoObject.push_back(var25);
                  }
               }
            }
         } catch (Throwable var20) {
            DebugLog.log("ERROR: receiveGridSquareObjects " + var20.getMessage());
         }

         var7.RecalcAllWithNeighbours(true);
         IsoWorld.instance.CurrentCell.checkHaveRoof(var7.getX(), var7.getY());
         var1.position(var9);
      }

      LuaEventManager.triggerEvent("OnContainerUpdate");
   }

    void receiveObject(ByteBuffer var1) {
    int var2 = var1.getInt();
    int var3 = var1.getInt();
    uint8_t var4 = var1.get();
    long var5 = var1.getLong();
      this.receiveSyncIsoObject(var2, var3, var4, var5);
    IsoGridSquare var7 = IsoWorld.instance.CurrentCell.getGridSquare(var2, var3, var4);
      if (var7 != nullptr) {
    uint8_t var8 = var1.get();
         long[] var9 = new long[var8];

         for (int var10 = 0; var10 < var8; var10++) {
            var9[var10] = var1.getLong();
         }

         long[] var14 = new long[var7.getObjects().size()];

         for (int var11 = 0; var11 < var7.getObjects().size(); var11++) {
            var14[var11] = ((IsoObject)var7.getObjects().get(var11)).customHashCode();
         }

    int var15 = var7.getObjects().size();
    int var12 = getObjectInsertIndex(var14, var9, var5);
         if (var12 == -1) {
            DebugLog.log("ERROR: ObjectsSyncRequest.receiveObject OBJECT EXIST (" + var2 + ", " + var3 + ", " + var4 + ") hash=" + var5);
         } else {
    IsoObject var13 = WorldItemTypes.createFromBuffer(var1);
            if (var13 != nullptr) {
               var13.loadFromRemoteBuffer(var1, false);
               var7.getObjects().push_back(var12, var13);
               if (dynamic_cast<IsoLightSwitch*>(var13) != nullptr) {
                  ((IsoLightSwitch)var13).addLightSourceFromSprite();
               }

               var13.addToWorld();
            }

            var7.RecalcAllWithNeighbours(true);
            IsoWorld.instance.CurrentCell.checkHaveRoof(var7.getX(), var7.getY());
            LuaEventManager.triggerEvent("OnContainerUpdate");
         }
      }
   }

    void serverSendRequests(UdpEngine var1) {
      for (int var2 = 0; var2 < var1.connections.size(); var2++) {
         this.serverSendRequests((UdpConnection)var1.connections.get(var2));
      }

      /* synchronized - TODO: add std::mutex */ (this.requestsSyncIsoGridSquare) {
         for (int var3 = 0; var3 < this.requestsSyncIsoGridSquare.size(); var3++) {
            this.requestsSyncIsoGridSquare.remove(0);
         }
      }
   }

    void serverSendRequests(UdpConnection var1) {
      if (this.requestsSyncIsoGridSquare.size() != 0) {
    ByteBufferWriter var2 = var1.startPacket();
         PacketType.SyncObjects.doPacket(var2);
         var2.putShort((short)4);
    int var3 = var2.bb.position();
         var2.putShort((short)0);
    int var4 = 0;

         for (int var5 = 0; var5 < this.requestsSyncIsoGridSquare.size(); var5++) {
    SyncIsoGridSquare var6 = this.requestsSyncIsoGridSquare.get(var5);
            if (var1.RelevantTo(var6.x, var6.y, 100.0F)) {
    IsoGridSquare var7 = ServerMap.instance.getGridSquare(var6.x, var6.y, var6.z);
               if (var7 != nullptr) {
                  var4++;
                  var2.putInt(var7.x);
                  var2.putInt(var7.y);
                  var2.putByte((byte)var7.z);
                  var2.putByte((byte)var7.getObjects().size());
                  var2.putInt(0);
    int var8 = var2.bb.position();

                  for (int var9 = 0; var9 < var7.getObjects().size(); var9++) {
                     var2.putLong(((IsoObject)var7.getObjects().get(var9)).customHashCode());
                  }

    int var11 = var2.bb.position();
                  var2.bb.position(var8 - 4);
                  var2.putInt(var11);
                  var2.bb.position(var11);
               }
            }
         }

    int var10 = var2.bb.position();
         var2.bb.position(var3);
         var2.putShort((short)var4);
         var2.bb.position(var10);
         PacketType.SyncObjects.send(GameClient.connection);
      }
   }
}
} // namespace iso
} // namespace zombie
