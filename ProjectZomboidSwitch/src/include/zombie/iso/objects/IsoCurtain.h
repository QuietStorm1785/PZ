#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameTime.h"
#include "zombie/Lua/LuaEventManager.h"
#include "zombie/SystemDisabler.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/opengl/Shader.h"
#include "zombie/core/properties/PropertyContainer.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/core/textures/ColorInfo.h"
#include "zombie/iso/IsoCamera.h"
#include "zombie/iso/IsoCell.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/IsoObject/VisionResult.h"
#include "zombie/iso/LosUtil.h"
#include "zombie/iso/SpriteDetails/IsoObjectType.h"
#include "zombie/iso/Vector2.h"
#include "zombie/iso/objects/interfaces/BarricadeAble.h"
#include "zombie/iso/sprite/IsoSprite.h"
#include "zombie/iso/sprite/IsoSpriteManager.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/PacketTypes/PacketType.h"
#include "zombie/util/Type.h"
#include "zombie/util/list/PZArrayList.h"
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace iso {
namespace objects {


class IsoCurtain : public IsoObject {
public:
    bool Barricaded = false;
    int BarricideMaxStrength = 0;
    int BarricideStrength = 0;
    int Health = 1000;
    bool Locked = false;
    int MaxHealth = 1000;
    int PushedMaxStrength = 0;
    int PushedStrength = 0;
    IsoSprite closedSprite;
    bool north = false;
    bool open = false;
    IsoSprite openSprite;
    bool destroyed = false;

    void removeSheet(IsoGameCharacter var1) {
      this.square.transmitRemoveItemFromSquare(this);
      if (GameServer.bServer) {
         var1.sendObjectChange("addItemOfType", new Object[]{"type", "Base.Sheet"});
      } else {
         var1.getInventory().AddItem("Base.Sheet");
      }

      for (int var2 = 0; var2 < IsoPlayer.numPlayers; var2++) {
         LosUtil.cachecleared[var2] = true;
      }

      GameTime.instance.lightSourceUpdate = 100.0F;
      IsoGridSquare.setRecalcLightTime(-1);
   }

    public IsoCurtain(IsoCell var1, IsoGridSquare var2, IsoSprite var3, bool var4, bool var5) {
      this.OutlineOnMouseover = true;
      this.PushedMaxStrength = this.PushedStrength = 2500;
      if (var5) {
         this.openSprite = IsoSprite.getSprite(IsoSpriteManager.instance, var3, 4);
         this.closedSprite = var3;
      } else {
         this.closedSprite = IsoSprite.getSprite(IsoSpriteManager.instance, var3, -4);
         this.openSprite = var3;
      }

      this.open = true;
      this.sprite = this.openSprite;
      this.square = var2;
      this.north = var4;
      this.DirtySlice();
   }

    public IsoCurtain(IsoCell var1, IsoGridSquare var2, const std::string& var3, bool var4) {
      this.OutlineOnMouseover = true;
      this.PushedMaxStrength = this.PushedStrength = 2500;
      this.closedSprite = IsoSprite.getSprite(IsoSpriteManager.instance, var3, -4);
      this.openSprite = IsoSprite.getSprite(IsoSpriteManager.instance, var3, 0);
      this.open = true;
      this.sprite = this.openSprite;
      this.square = var2;
      this.north = var4;
      this.DirtySlice();
   }

    public IsoCurtain(IsoCell var1) {
      super(var1);
   }

    std::string getObjectName() {
      return "Curtain";
   }

    Vector2 getFacingPosition(Vector2 var1) {
      if (this.square == nullptr) {
         return var1.set(0.0F, 0.0F);
      } else if (this.getType() == IsoObjectType.curtainS) {
         return var1.set(this.getX() + 0.5F, this.getY() + 1.0F);
      } else if (this.getType() == IsoObjectType.curtainE) {
         return var1.set(this.getX() + 1.0F, this.getY() + 0.5F);
      } else {
         return this.north ? var1.set(this.getX() + 0.5F, this.getY()) : var1.set(this.getX(), this.getY() + 0.5F);
      }
   }

    void load(ByteBuffer var1, int var2, bool var3) {
      super.load(var1, var2, var3);
      this.open = var1.get() == 1;
      this.north = var1.get() == 1;
      this.Health = var1.getInt();
      this.BarricideStrength = var1.getInt();
      if (this.open) {
         this.closedSprite = IsoSprite.getSprite(IsoSpriteManager.instance, var1.getInt());
         this.openSprite = this.sprite;
      } else {
         this.openSprite = IsoSprite.getSprite(IsoSpriteManager.instance, var1.getInt());
         this.closedSprite = this.sprite;
      }

      if (SystemDisabler.doObjectStateSyncEnable && GameClient.bClient) {
         GameClient.instance.objectSyncReq.putRequestLoad(this.square);
      }
   }

    void save(ByteBuffer var1, bool var2) {
      super.save(var1, var2);
      var1.put((byte)(this.open ? 1 : 0));
      var1.put((byte)(this.north ? 1 : 0));
      var1.putInt(this.Health);
      var1.putInt(this.BarricideStrength);
      if (this.open) {
         var1.putInt(this.closedSprite.ID);
      } else {
         var1.putInt(this.openSprite.ID);
      }
   }

    bool getNorth() {
      return this.north;
   }

    bool IsOpen() {
      return this.open;
   }

    bool onMouseLeftClick(int var1, int var2) {
    return false;
   }

    bool canInteractWith(IsoGameCharacter var1) {
      if (var1 != nullptr && var1.getCurrentSquare() != nullptr) {
    IsoGridSquare var2 = var1.getCurrentSquare();
         return (this.isAdjacentToSquare(var2) || var2 == this.getOppositeSquare()) && !this.getSquare().isBlockedTo(var2);
      } else {
    return false;
      }
   }

    IsoGridSquare getOppositeSquare() {
      if (this.getType() == IsoObjectType.curtainN) {
         return this.getCell().getGridSquare(this.getX(), this.getY() - 1.0F, this.getZ());
      } else if (this.getType() == IsoObjectType.curtainS) {
         return this.getCell().getGridSquare(this.getX(), this.getY() + 1.0F, this.getZ());
      } else if (this.getType() == IsoObjectType.curtainW) {
         return this.getCell().getGridSquare(this.getX() - 1.0F, this.getY(), this.getZ());
      } else {
         return this.getType() == IsoObjectType.curtainE ? this.getCell().getGridSquare(this.getX() + 1.0F, this.getY(), this.getZ()) : nullptr;
      }
   }

    bool isAdjacentToSquare(IsoGridSquare var1, IsoGridSquare var2) {
      if (var1 != nullptr && var2 != nullptr) {
         return this.getType() != IsoObjectType.curtainN && this.getType() != IsoObjectType.curtainS
            ? var1.x == var2.x && Math.abs(var1.y - var2.y) <= 1
            : var1.y == var2.y && Math.abs(var1.x - var2.x) <= 1;
      } else {
    return false;
      }
   }

    bool isAdjacentToSquare(IsoGridSquare var1) {
      return this.isAdjacentToSquare(this.getSquare(), var1);
   }

    VisionResult TestVision(IsoGridSquare var1, IsoGridSquare var2) {
      if (var2.getZ() != var1.getZ()) {
         return VisionResult.NoEffect;
      } else {
         if (var1 == this.square && (this.getType() == IsoObjectType.curtainW || this.getType() == IsoObjectType.curtainN)
            || var1 != this.square && (this.getType() == IsoObjectType.curtainE || this.getType() == IsoObjectType.curtainS)) {
            if (this.north && var2.getY() < var1.getY() && !this.open) {
               return VisionResult.Blocked;
            }

            if (!this.north && var2.getX() < var1.getX() && !this.open) {
               return VisionResult.Blocked;
            }
         } else {
            if (this.north && var2.getY() > var1.getY() && !this.open) {
               return VisionResult.Blocked;
            }

            if (!this.north && var2.getX() > var1.getX() && !this.open) {
               return VisionResult.Blocked;
            }
         }

         return VisionResult.NoEffect;
      }
   }

    void ToggleDoor(IsoGameCharacter var1) {
      if (!this.Barricaded) {
         this.DirtySlice();
         if (!this.Locked || var1 == nullptr || var1.getCurrentSquare().getRoom() != nullptr || this.open) {
            this.open = !this.open;
            this.sprite = this.closedSprite;
            if (this.open) {
               this.sprite = this.openSprite;
               if (var1 != nullptr) {
                  var1.playSound(this.getSoundPrefix() + "Open");
               }
            } else if (var1 != nullptr) {
               var1.playSound(this.getSoundPrefix() + "Close");
            }

            this.syncIsoObject(false, (byte)(this.open ? 1 : 0), nullptr);
         }
      }
   }

    void ToggleDoorSilent() {
      if (!this.Barricaded) {
         this.DirtySlice();

         for (int var1 = 0; var1 < IsoPlayer.numPlayers; var1++) {
            LosUtil.cachecleared[var1] = true;
         }

         GameTime.instance.lightSourceUpdate = 100.0F;
         IsoGridSquare.setRecalcLightTime(-1);
         this.open = !this.open;
         this.sprite = this.closedSprite;
         if (this.open) {
            this.sprite = this.openSprite;
         }

         this.syncIsoObject(false, (byte)(this.open ? 1 : 0), nullptr);
      }
   }

    void render(float var1, float var2, float var3, ColorInfo var4, bool var5, bool var6, Shader var7) {
    int var8 = IsoCamera.frameState.playerIndex;
    IsoObject var9 = this.getObjectAttachedTo();
      if (var9 != nullptr && this.getSquare().getTargetDarkMulti(var8) <= var9.getSquare().getTargetDarkMulti(var8)) {
         var4 = var9.getSquare().lighting[var8].lightInfo();
         this.setTargetAlpha(var8, var9.getTargetAlpha(var8));
      }

      super.render(var1, var2, var3, var4, var5, var6, var7);
   }

    void syncIsoObjectSend(ByteBufferWriter var1) {
      var1.putInt(this.square.getX());
      var1.putInt(this.square.getY());
      var1.putInt(this.square.getZ());
    uint8_t var2 = (byte)this.square.getObjects().indexOf(this);
      var1.putByte(var2);
      var1.putByte((byte)1);
      var1.putByte((byte)(this.open ? 1 : 0));
   }

    void syncIsoObject(bool var1, uint8_t var2, UdpConnection var3, ByteBuffer var4) {
      this.syncIsoObject(var1, var2, var3);
   }

    void syncIsoObject(bool var1, uint8_t var2, UdpConnection var3) {
      if (this.square == nullptr) {
         System.out.println("ERROR: " + this.getClass().getSimpleName() + " square is nullptr");
      } else if (this.getObjectIndex() == -1) {
         System.out
            .println(
               "ERROR: " + this.getClass().getSimpleName() + " not found on square " + this.square.getX() + "," + this.square.getY() + "," + this.square.getZ()
            );
      } else {
         if (GameClient.bClient && !var1) {
    ByteBufferWriter var7 = GameClient.connection.startPacket();
            PacketType.SyncIsoObject.doPacket(var7);
            this.syncIsoObjectSend(var7);
            PacketType.SyncIsoObject.send(GameClient.connection);
         } else if (var1) {
            if (var2 == 1) {
               this.open = true;
               this.sprite = this.openSprite;
            } else {
               this.open = false;
               this.sprite = this.closedSprite;
            }

            if (GameServer.bServer) {
               for (UdpConnection var5 : GameServer.udpEngine.connections) {
                  if (var3 != nullptr && var5.getConnectedGUID() != var3.getConnectedGUID()) {
    ByteBufferWriter var6 = var5.startPacket();
                     PacketType.SyncIsoObject.doPacket(var6);
                     this.syncIsoObjectSend(var6);
                     PacketType.SyncIsoObject.send(var5);
                  }
               }
            }
         }

         this.square.RecalcProperties();
         this.square.RecalcAllWithNeighbours(true);

         for (int var8 = 0; var8 < IsoPlayer.numPlayers; var8++) {
            LosUtil.cachecleared[var8] = true;
         }

         IsoGridSquare.setRecalcLightTime(-1);
         GameTime.instance.lightSourceUpdate = 100.0F;
         LuaEventManager.triggerEvent("OnContainerUpdate");
         if (this.square != nullptr) {
            this.square.RecalcProperties();
         }
      }
   }

    IsoObject getObjectAttachedTo() {
    int var1 = this.getObjectIndex();
      if (var1 == -1) {
    return nullptr;
      } else {
    PZArrayList var2 = this.getSquare().getObjects();
         if (this.getType() != IsoObjectType.curtainW && this.getType() != IsoObjectType.curtainN) {
            if (this.getType() == IsoObjectType.curtainE || this.getType() == IsoObjectType.curtainS) {
    IsoGridSquare var8 = this.getOppositeSquare();
               if (var8 != nullptr) {
    bool var9 = this.getType() == IsoObjectType.curtainS;
                  var2 = var8.getObjects();

                  for (int var10 = var2.size() - 1; var10 >= 0; var10--) {
    BarricadeAble var6 = (BarricadeAble)Type.tryCastTo((IsoObject)var2.get(var10), BarricadeAble.class);
                     if (var6 != nullptr && var9 == var6.getNorth()) {
                        return (IsoObject)var2.get(var10);
                     }
                  }
               }
            }
         } else {
    bool var3 = this.getType() == IsoObjectType.curtainN;

            for (int var4 = var1 - 1; var4 >= 0; var4--) {
    BarricadeAble var5 = (BarricadeAble)Type.tryCastTo((IsoObject)var2.get(var4), BarricadeAble.class);
               if (var5 != nullptr && var3 == var5.getNorth()) {
                  return (IsoObject)var2.get(var4);
               }
            }
         }

    return nullptr;
      }
   }

    std::string getSoundPrefix() {
      if (this.closedSprite == nullptr) {
         return "CurtainShort";
      } else {
    PropertyContainer var1 = this.closedSprite.getProperties();
         return var1.Is("CurtainSound") ? "Curtain" + var1.Val("CurtainSound") : "CurtainShort";
      }
   }

    static bool isSheet(IsoObject var0) {
      if (dynamic_cast<IsoDoor*>(var0) != nullptr) {
         var0 = ((IsoDoor)var0).HasCurtains();
      }

      if (dynamic_cast<IsoThumpable*>(var0) != nullptr) {
         var0 = ((IsoThumpable)var0).HasCurtains();
      }

      if (dynamic_cast<IsoWindow*>(var0) != nullptr) {
         var0 = ((IsoWindow)var0).HasCurtains();
      }

      if (var0 != nullptr && var0.getSprite() != nullptr) {
    IsoSprite var1 = var0.getSprite();
         return var1.getProperties().Is("CurtainSound") ? "Sheet" == var1.getProperties().Val("CurtainSound")) : false;
      } else {
    return false;
      }
   }
}
} // namespace objects
} // namespace iso
} // namespace zombie
