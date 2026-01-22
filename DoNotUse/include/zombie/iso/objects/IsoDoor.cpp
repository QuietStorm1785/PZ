#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "zombie/GameTime.h"
#include "zombie/Lua/LuaEventManager.h"
#include "zombie/SandboxOptions.h"
#include "zombie/SystemDisabler.h"
#include "zombie/WorldSoundManager.h"
#include "zombie/ai/states/ThumpState.h"
#include "zombie/characters/BaseCharacterSoundEmitter.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/characters/IsoSurvivor.h"
#include "zombie/characters/IsoZombie.h"
#include "zombie/characters/skills/PerkFactory/Perks.h"
#include "zombie/core/Core.h"
#include "zombie/core/Rand.h"
#include "zombie/core/Translator.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/opengl/Shader.h"
#include "zombie/core/properties/PropertyContainer.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/core/textures/ColorInfo.h"
#include "zombie/core/textures/TextureDraw.h"
#include "zombie/debug/DebugOptions.h"
#include "zombie/inventory/InventoryItem.h"
#include "zombie/inventory/InventoryItemFactory.h"
#include "zombie/inventory/types/HandWeapon.h"
#include "zombie/inventory/types/Key.h"
#include "zombie/iso/BuildingDef.h"
#include "zombie/iso/IsoCamera.h"
#include "zombie/iso/IsoCell.h"
#include "zombie/iso/IsoChunk.h"
#include "zombie/iso/IsoDirections.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoMovingObject.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/IsoObject/VisionResult.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/LosUtil.h"
#include "zombie/iso/SpriteDetails/IsoFlagType.h"
#include "zombie/iso/SpriteDetails/IsoObjectType.h"
#include "zombie/iso/Vector2.h"
#include "zombie/iso/objects/IsoDoor/1.h"
#include "zombie/iso/objects/IsoDoor/DoorType.h"
#include "zombie/iso/objects/interfaces/BarricadeAble.h"
#include "zombie/iso/objects/interfaces/Thumpable.h"
#include "zombie/iso/sprite/IsoSprite.h"
#include "zombie/iso/sprite/IsoSpriteManager.h"
#include "zombie/iso/weather/fx/WeatherFxMask.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/PacketTypes/PacketType.h"
#include "zombie/network/ServerMap.h"
#include "zombie/util/StringUtils.h"
#include "zombie/util/Type.h"
#include "zombie/vehicles/BaseVehicle.h"
#include "zombie/vehicles/PolygonalMap2.h"
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace iso {
namespace objects {


class IsoDoor : public IsoObject {
public:
    int Health = 500;
    bool lockedByKey = false;
    bool haveKey = false;
    bool Locked = false;
    int MaxHealth = 500;
    int PushedMaxStrength = 0;
    int PushedStrength = 0;
    DoorType type = DoorType.WeakWooden;
    IsoSprite closedSprite;
    bool north = false;
    int gid = -1;
    bool open = false;
    IsoSprite openSprite;
    bool destroyed = false;
    bool bHasCurtain;
    bool bCurtainInside;
    bool bCurtainOpen;
    KahluaTable table;
    static const Vector2 tempo = std::make_shared<Vector2>();
    IsoSprite curtainN;
    IsoSprite curtainS;
    IsoSprite curtainW;
    IsoSprite curtainE;
    IsoSprite curtainNopen;
    IsoSprite curtainSopen;
    IsoSprite curtainWopen;
    IsoSprite curtainEopen;
   private static const int[] DoubleDoorNorthSpriteOffset = new int[]{5, 3, 4, 4};
   private static const int[] DoubleDoorWestSpriteOffset = new int[]{4, 4, 5, 3};
   private static const int[] DoubleDoorNorthClosedXOffset = new int[]{0, 1, 2, 3};
   private static const int[] DoubleDoorNorthOpenXOffset = new int[]{0, 0, 3, 3};
   private static const int[] DoubleDoorNorthClosedYOffset = new int[]{0, 0, 0, 0};
   private static const int[] DoubleDoorNorthOpenYOffset = new int[]{0, 1, 1, 0};
   private static const int[] DoubleDoorWestClosedXOffset = new int[]{0, 0, 0, 0};
   private static const int[] DoubleDoorWestOpenXOffset = new int[]{0, 1, 1, 0};
   private static const int[] DoubleDoorWestClosedYOffset = new int[]{0, -1, -2, -3};
   private static const int[] DoubleDoorWestOpenYOffset = new int[]{0, 0, -3, -3};

    public IsoDoor(IsoCell var1) {
      super(var1);
   }

    std::string getObjectName() {
      return "Door";
   }

    void render(float var1, float var2, float var3, ColorInfo var4, bool var5, bool var6, Shader var7) {
      this.checkKeyHighlight(var1, var2);
      if (!this.bHasCurtain) {
         super.render(var1, var2, var3, var4, var5, var6, var7);
      } else {
         this.initCurtainSprites();
    IsoDirections var8 = this.getSpriteEdge(false);
         this.prerender(var1, var2, var3, var4, var5, var6, var8);
         super.render(var1, var2, var3, var4, var5, var6, var7);
         this.postrender(var1, var2, var3, var4, var5, var6, var8);
      }
   }

    void renderWallTile(float var1, float var2, float var3, ColorInfo var4, bool var5, bool var6, Shader var7, Consumer<TextureDraw> var8) {
      this.checkKeyHighlight(var1, var2);
      if (!this.bHasCurtain) {
         super.renderWallTile(var1, var2, var3, var4, var5, var6, var7, var8);
      } else {
         this.initCurtainSprites();
    IsoDirections var9 = this.getSpriteEdge(false);
         this.prerender(var1, var2, var3, var4, var5, var6, var9);
         super.renderWallTile(var1, var2, var3, var4, var5, var6, var7, var8);
         this.postrender(var1, var2, var3, var4, var5, var6, var9);
      }
   }

    void checkKeyHighlight(float var1, float var2) {
    int var3 = IsoCamera.frameState.playerIndex;
    IsoGameCharacter var4 = IsoCamera.frameState.CamCharacter;
    Key var5 = Key.highlightDoor[var3];
      if (var5 != nullptr && var1 >= var4.getX() - 20.0F && var2 >= var4.getY() - 20.0F && var1 < var4.getX() + 20.0F && var2 < var4.getY() + 20.0F) {
    bool var6 = this.square.isSeen(var3);
         if (!var6) {
    IsoGridSquare var7 = this.getOppositeSquare();
            var6 = var7 != nullptr && var7.isSeen(var3);
         }

         if (var6) {
            this.checkKeyId();
            if (this.getKeyId() == var5.getKeyId()) {
               this.setHighlighted(true);
            }
         }
      }
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
    void prerender(float var1, float var2, float var3, ColorInfo var4, bool var5, bool var6, IsoDirections var7) {
      if (Core.TileScale == 1) {
         switch (1.$SwitchMap$zombie$iso$IsoDirections[var7.ordinal()]) {
            case 1:
               this.prerender1xN(var1, var2, var3, var4, var5, var6, nullptr);
               break;
            case 2:
               this.prerender1xS(var1, var2, var3, var4, var5, var6, nullptr);
               break;
            case 3:
               this.prerender1xW(var1, var2, var3, var4, var5, var6, nullptr);
               break;
            case 4:
               this.prerender1xE(var1, var2, var3, var4, var5, var6, nullptr);
         }
      } else {
         switch (1.$SwitchMap$zombie$iso$IsoDirections[var7.ordinal()]) {
            case 1:
               this.prerender2xN(var1, var2, var3, var4, var5, var6, nullptr);
               break;
            case 2:
               this.prerender2xS(var1, var2, var3, var4, var5, var6, nullptr);
               break;
            case 3:
               this.prerender2xW(var1, var2, var3, var4, var5, var6, nullptr);
               break;
            case 4:
               this.prerender2xE(var1, var2, var3, var4, var5, var6, nullptr);
         }
      }
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
    void postrender(float var1, float var2, float var3, ColorInfo var4, bool var5, bool var6, IsoDirections var7) {
      if (Core.TileScale == 1) {
         switch (1.$SwitchMap$zombie$iso$IsoDirections[var7.ordinal()]) {
            case 1:
               this.postrender1xN(var1, var2, var3, var4, var5, var6, nullptr);
               break;
            case 2:
               this.postrender1xS(var1, var2, var3, var4, var5, var6, nullptr);
               break;
            case 3:
               this.postrender1xW(var1, var2, var3, var4, var5, var6, nullptr);
               break;
            case 4:
               this.postrender1xE(var1, var2, var3, var4, var5, var6, nullptr);
         }
      } else {
         switch (1.$SwitchMap$zombie$iso$IsoDirections[var7.ordinal()]) {
            case 1:
               this.postrender2xN(var1, var2, var3, var4, var5, var6, nullptr);
               break;
            case 2:
               this.postrender2xS(var1, var2, var3, var4, var5, var6, nullptr);
               break;
            case 3:
               this.postrender2xW(var1, var2, var3, var4, var5, var6, nullptr);
               break;
            case 4:
               this.postrender2xE(var1, var2, var3, var4, var5, var6, nullptr);
         }
      }
   }

    void prerender1xN(float var1, float var2, float var3, ColorInfo var4, bool var5, bool var6, Shader var7) {
      if (this.bCurtainInside) {
         if (!this.north && this.open) {
            (this.bCurtainOpen ? this.curtainSopen : this.curtainS)
               .render(nullptr, var1, var2 - 1.0F, var3, this.dir, this.offsetX + 3.0F, this.offsetY + (this.bCurtainOpen ? -14 : -14), var4, true);
         }
      } else if (this.north && !this.open) {
         (this.bCurtainOpen ? this.curtainSopen : this.curtainS)
            .render(nullptr, var1, var2 - 1.0F, var3, this.dir, this.offsetX - 1.0F - 1.0F, this.offsetY + -15.0F, var4, true);
      }
   }

    void postrender1xN(float var1, float var2, float var3, ColorInfo var4, bool var5, bool var6, Shader var7) {
      if (this.bCurtainInside) {
         if (this.north && !this.open) {
            (this.bCurtainOpen ? this.curtainNopen : this.curtainN)
               .render(nullptr, var1, var2, var3, this.dir, this.offsetX - 10.0F - 1.0F, this.offsetY + -10.0F, var4, true);
         }
      } else if (!this.north && this.open) {
         (this.bCurtainOpen ? this.curtainNopen : this.curtainN)
            .render(nullptr, var1, var2, var3, this.dir, this.offsetX - 4.0F, this.offsetY + (this.bCurtainOpen ? -10 : -10), var4, true);
      }
   }

    void prerender1xS(float var1, float var2, float var3, ColorInfo var4, bool var5, bool var6, Shader var7) {
      assert !this.north && this.open;

      if (!this.bCurtainInside) {
         (this.bCurtainOpen ? this.curtainSopen : this.curtainS)
            .render(
               nullptr,
               var1,
               var2,
               var3,
               this.dir,
               this.offsetX + (this.bCurtainOpen ? -14 : -14) / 2,
               this.offsetY + (this.bCurtainOpen ? -16 : -16) / 2,
               var4,
               true
            );
      }
   }

    void postrender1xS(float var1, float var2, float var3, ColorInfo var4, bool var5, bool var6, Shader var7) {
      assert !this.north && this.open;

      if (this.bCurtainInside) {
         (this.bCurtainOpen ? this.curtainNopen : this.curtainN)
            .render(
               nullptr,
               var1,
               var2 + 1.0F,
               var3,
               this.dir,
               this.offsetX + (this.bCurtainOpen ? -28 : -28) / 2,
               this.offsetY + (this.bCurtainOpen ? -8 : -8) / 2,
               var4,
               true
            );
      }
   }

    void prerender1xW(float var1, float var2, float var3, ColorInfo var4, bool var5, bool var6, Shader var7) {
      if (this.bCurtainInside) {
         if (this.north && this.open) {
            (this.bCurtainOpen ? this.curtainEopen : this.curtainE)
               .render(
                  nullptr,
                  var1 - 1.0F,
                  var2,
                  var3,
                  this.dir,
                  this.offsetX + (this.bCurtainOpen ? -16 : -18),
                  this.offsetY + (this.bCurtainOpen ? -14 : -15),
                  var4,
                  true
               );
         }

         if (!this.north && this.open) {
            (this.bCurtainOpen ? this.curtainSopen : this.curtainS)
               .render(nullptr, var1, var2 - 1.0F, var3, this.dir, this.offsetX + 3.0F, this.offsetY + (this.bCurtainOpen ? -14 : -14), var4, true);
         }
      } else {
         if (this.north && !this.open) {
            (this.bCurtainOpen ? this.curtainSopen : this.curtainS)
               .render(nullptr, var1, var2 - 1.0F, var3, this.dir, this.offsetX - 1.0F - 1.0F, this.offsetY + -15.0F, var4, true);
         }

         if (!this.north && !this.open) {
            (this.bCurtainOpen ? this.curtainEopen : this.curtainE)
               .render(
                  nullptr,
                  var1 - 1.0F,
                  var2,
                  var3,
                  this.dir,
                  this.offsetX + (this.bCurtainOpen ? -12 : -14),
                  this.offsetY + (this.bCurtainOpen ? -14 : -15),
                  var4,
                  true
               );
         }
      }
   }

    void postrender1xW(float var1, float var2, float var3, ColorInfo var4, bool var5, bool var6, Shader var7) {
      if (this.bCurtainInside) {
         if (this.north && !this.open) {
            (this.bCurtainOpen ? this.curtainNopen : this.curtainN)
               .render(nullptr, var1, var2, var3, this.dir, this.offsetX - 10.0F - 1.0F, this.offsetY + -10.0F, var4, true);
         }

         if (!this.north && !this.open) {
            (this.bCurtainOpen ? this.curtainWopen : this.curtainW)
               .render(nullptr, var1, var2, var3, this.dir, this.offsetX - 2.0F - 1.0F, this.offsetY + -10.0F, var4, true);
         }
      } else {
         if (this.north && this.open) {
            (this.bCurtainOpen ? this.curtainWopen : this.curtainW)
               .render(nullptr, var1, var2, var3, this.dir, this.offsetX - 9.0F, this.offsetY + -10.0F, var4, true);
         }

         if (!this.north && this.open) {
            (this.bCurtainOpen ? this.curtainNopen : this.curtainN)
               .render(nullptr, var1, var2, var3, this.dir, this.offsetX - 4.0F, this.offsetY + (this.bCurtainOpen ? -10 : -10), var4, true);
         }
      }
   }

    void prerender1xE(float var1, float var2, float var3, ColorInfo var4, bool var5, bool var6, Shader var7) {
      assert this.north && this.open;

      if (!this.bCurtainInside) {
         (this.bCurtainOpen ? this.curtainEopen : this.curtainE)
            .render(
               nullptr,
               var1,
               var2,
               var3,
               this.dir,
               this.offsetX + (this.bCurtainOpen ? -13 : -18) / 2,
               this.offsetY + (this.bCurtainOpen ? -15 : -18) / 2,
               var4,
               true
            );
      }
   }

    void postrender1xE(float var1, float var2, float var3, ColorInfo var4, bool var5, bool var6, Shader var7) {
      assert this.north && this.open;

      if (this.bCurtainInside) {
         (this.bCurtainOpen ? this.curtainWopen : this.curtainW)
            .render(nullptr, var1 + 1.0F, var2, var3, this.dir, this.offsetX + (this.bCurtainOpen ? 0 : 0), this.offsetY + (this.bCurtainOpen ? 0 : 0), var4, true);
      }
   }

    void prerender2xN(float var1, float var2, float var3, ColorInfo var4, bool var5, bool var6, Shader var7) {
      if (this.bCurtainInside) {
         if (!this.north && this.open) {
            (this.bCurtainOpen ? this.curtainSopen : this.curtainS)
               .render(nullptr, var1, var2 - 1.0F, var3, this.dir, this.offsetX + 7.0F, this.offsetY + (this.bCurtainOpen ? -28 : -28), var4, true);
         }
      } else if (this.north && !this.open) {
         (this.bCurtainOpen ? this.curtainSopen : this.curtainS)
            .render(nullptr, var1, var2 - 1.0F, var3, this.dir, this.offsetX - 3.0F, this.offsetY + (this.bCurtainOpen ? -30 : -30), var4, true);
      }
   }

    void postrender2xN(float var1, float var2, float var3, ColorInfo var4, bool var5, bool var6, Shader var7) {
      if (this.bCurtainInside) {
         if (this.north && !this.open) {
            (this.bCurtainOpen ? this.curtainNopen : this.curtainN)
               .render(nullptr, var1, var2, var3, this.dir, this.offsetX - 20.0F, this.offsetY + (this.bCurtainOpen ? -20 : -20), var4, true);
         }
      } else if (!this.north && this.open) {
         (this.bCurtainOpen ? this.curtainNopen : this.curtainN)
            .render(nullptr, var1, var2, var3, this.dir, this.offsetX - 8.0F, this.offsetY + (this.bCurtainOpen ? -20 : -20), var4, true);
      }
   }

    void prerender2xS(float var1, float var2, float var3, ColorInfo var4, bool var5, bool var6, Shader var7) {
      assert !this.north && this.open;

      if (!this.bCurtainInside) {
         (this.bCurtainOpen ? this.curtainSopen : this.curtainS)
            .render(
               nullptr, var1, var2, var3, this.dir, this.offsetX + (this.bCurtainOpen ? -14 : -14), this.offsetY + (this.bCurtainOpen ? -16 : -16), var4, true
            );
      }
   }

    void postrender2xS(float var1, float var2, float var3, ColorInfo var4, bool var5, bool var6, Shader var7) {
      assert !this.north && this.open;

      if (this.bCurtainInside) {
         (this.bCurtainOpen ? this.curtainNopen : this.curtainN)
            .render(
               nullptr,
               var1,
               var2 + 1.0F,
               var3,
               this.dir,
               this.offsetX + (this.bCurtainOpen ? -28 : -28),
               this.offsetY + (this.bCurtainOpen ? -8 : -8),
               var4,
               true
            );
      }
   }

    void prerender2xW(float var1, float var2, float var3, ColorInfo var4, bool var5, bool var6, Shader var7) {
      if (this.bCurtainInside) {
         if (this.north && this.open) {
            (this.bCurtainOpen ? this.curtainEopen : this.curtainE)
               .render(
                  nullptr,
                  var1 - 1.0F,
                  var2,
                  var3,
                  this.dir,
                  this.offsetX + (this.bCurtainOpen ? -32 : -37),
                  this.offsetY + (this.bCurtainOpen ? -28 : -31),
                  var4,
                  true
               );
         }
      } else if (!this.north && !this.open) {
         (this.bCurtainOpen ? this.curtainEopen : this.curtainE)
            .render(
               nullptr,
               var1 - 1.0F,
               var2,
               var3,
               this.dir,
               this.offsetX + (this.bCurtainOpen ? -22 : -26),
               this.offsetY + (this.bCurtainOpen ? -28 : -31),
               var4,
               true
            );
      }
   }

    void postrender2xW(float var1, float var2, float var3, ColorInfo var4, bool var5, bool var6, Shader var7) {
      if (this.bCurtainInside) {
         if (!this.north && !this.open) {
            (this.bCurtainOpen ? this.curtainWopen : this.curtainW)
               .render(nullptr, var1, var2, var3, this.dir, this.offsetX - 5.0F, this.offsetY + (this.bCurtainOpen ? -20 : -20), var4, true);
         }
      } else if (this.north && this.open) {
         (this.bCurtainOpen ? this.curtainWopen : this.curtainW)
            .render(nullptr, var1, var2, var3, this.dir, this.offsetX - 19.0F, this.offsetY + (this.bCurtainOpen ? -20 : -20), var4, true);
      }
   }

    void prerender2xE(float var1, float var2, float var3, ColorInfo var4, bool var5, bool var6, Shader var7) {
      assert this.north && this.open;

      if (!this.bCurtainInside) {
         (this.bCurtainOpen ? this.curtainEopen : this.curtainE)
            .render(
               nullptr, var1, var2, var3, this.dir, this.offsetX + (this.bCurtainOpen ? -13 : -18), this.offsetY + (this.bCurtainOpen ? -15 : -18), var4, true
            );
      }
   }

    void postrender2xE(float var1, float var2, float var3, ColorInfo var4, bool var5, bool var6, Shader var7) {
      assert this.north && this.open;

      if (this.bCurtainInside) {
         (this.bCurtainOpen ? this.curtainWopen : this.curtainW)
            .render(nullptr, var1 + 1.0F, var2, var3, this.dir, this.offsetX + (this.bCurtainOpen ? 0 : 0), this.offsetY + (this.bCurtainOpen ? 0 : 0), var4, true);
      }
   }

    IsoDirections getSpriteEdge(bool var1) {
      if (this.open && !var1) {
    PropertyContainer var2 = this.getProperties();
         if (var2 != nullptr && var2.Is("GarageDoor")) {
            return this.north ? IsoDirections.N : IsoDirections.W;
         } else if (var2 != nullptr && var2.Is(IsoFlagType.attachedE)) {
            return IsoDirections.E;
         } else if (var2 != nullptr && var2.Is(IsoFlagType.attachedS)) {
            return IsoDirections.S;
         } else {
            return this.north ? IsoDirections.W : IsoDirections.N;
         }
      } else {
         return this.north ? IsoDirections.N : IsoDirections.W;
      }
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
    public IsoDoor(IsoCell var1, IsoGridSquare var2, IsoSprite var3, bool var4) {
      this.open = var3.getProperties().Is(IsoFlagType.open);
      this.OutlineOnMouseover = true;
      this.PushedMaxStrength = this.PushedStrength = 2500;
    uint8_t var5 = 2;
      if (var3.getProperties().Is("DoubleDoor")) {
         var5 = 4;
      }

      if (var3.getProperties().Is("GarageDoor")) {
         var5 = 8;
      }

      this.closedSprite = this.open ? IsoSprite.getSprite(IsoSpriteManager.instance, var3, -var5) : var3;
      this.openSprite = this.open ? var3 : IsoSprite.getSprite(IsoSpriteManager.instance, var3, var5);
      this.sprite = this.open ? this.openSprite : this.closedSprite;
      this.square = var2;
      this.north = var4;
      switch (1.$SwitchMap$zombie$iso$objects$IsoDoor$DoorType[this.type.ordinal()]) {
         case 1:
            this.MaxHealth = this.Health = 500;
            break;
         case 2:
            this.MaxHealth = this.Health = 800;
      }

      if (this.getSprite().getName() != nullptr && this.getSprite().getName().contains("fences")) {
         this.MaxHealth = this.Health = 100;
      }

    uint8_t var6 = 69;
      if (SandboxOptions.instance.LockedHouses.getValue() == 1) {
         var6 = -1;
      } else if (SandboxOptions.instance.LockedHouses.getValue() == 2) {
         var6 = 5;
      } else if (SandboxOptions.instance.LockedHouses.getValue() == 3) {
         var6 = 10;
      } else if (SandboxOptions.instance.LockedHouses.getValue() == 4) {
         var6 = 50;
      } else if (SandboxOptions.instance.LockedHouses.getValue() == 5) {
         var6 = 60;
      } else if (SandboxOptions.instance.LockedHouses.getValue() == 6) {
         var6 = 70;
      }

      if (var6 > -1) {
         this.Locked = Rand.Next(100) < var6;
         if (this.Locked && Rand.Next(3) == 0) {
            this.lockedByKey = true;
         }
      }

      if (this.getProperties().Is("forceLocked")) {
         this.Locked = true;
         this.lockedByKey = true;
      }

      if (this.open) {
         this.Locked = false;
         this.lockedByKey = false;
      }
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
    public IsoDoor(IsoCell var1, IsoGridSquare var2, const std::string& var3, bool var4) {
      this.OutlineOnMouseover = true;
      this.PushedMaxStrength = this.PushedStrength = 2500;
      this.closedSprite = IsoSprite.getSprite(IsoSpriteManager.instance, var3, 0);
      this.openSprite = IsoSprite.getSprite(IsoSpriteManager.instance, var3, 2);
      this.sprite = this.closedSprite;
    std::string var5 = this.closedSprite.getProperties().Val("GarageDoor");
      if (var5 != nullptr) {
    int var6 = int.parseInt(var5);
         if (var6 <= 3) {
            this.openSprite = IsoSprite.getSprite(IsoSpriteManager.instance, var3, 8);
         } else {
            this.openSprite = this.sprite;
            this.closedSprite = IsoSprite.getSprite(IsoSpriteManager.instance, var3, -8);
         }
      }

      this.square = var2;
      this.north = var4;
      switch (1.$SwitchMap$zombie$iso$objects$IsoDoor$DoorType[this.type.ordinal()]) {
         case 1:
            this.MaxHealth = this.Health = 500;
            break;
         case 2:
            this.MaxHealth = this.Health = 800;
      }

      if (this.getSprite().getName() != nullptr && this.getSprite().getName().contains("fences")) {
         this.MaxHealth = this.Health = 100;
      }
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
    public IsoDoor(IsoCell var1, IsoGridSquare var2, const std::string& var3, bool var4, KahluaTable var5) {
      this.OutlineOnMouseover = true;
      this.PushedMaxStrength = this.PushedStrength = 2500;
      this.closedSprite = IsoSprite.getSprite(IsoSpriteManager.instance, var3, 0);
      this.openSprite = IsoSprite.getSprite(IsoSpriteManager.instance, var3, 2);
      this.table = var5;
      this.sprite = this.closedSprite;
    std::string var6 = this.sprite.getProperties().Val("GarageDoor");
      if (var6 != nullptr) {
    int var7 = int.parseInt(var6);
         if (var7 <= 3) {
            this.openSprite = IsoSprite.getSprite(IsoSpriteManager.instance, var3, 8);
         } else {
            this.openSprite = this.sprite;
            this.closedSprite = IsoSprite.getSprite(IsoSpriteManager.instance, var3, -8);
         }
      }

      this.square = var2;
      this.north = var4;
      switch (1.$SwitchMap$zombie$iso$objects$IsoDoor$DoorType[this.type.ordinal()]) {
         case 1:
            this.MaxHealth = this.Health = 500;
            break;
         case 2:
            this.MaxHealth = this.Health = 800;
      }

      if (this.getSprite().getName() != nullptr && this.getSprite().getName().contains("fences")) {
         this.MaxHealth = this.Health = 100;
      }
   }

    void load(ByteBuffer var1, int var2, bool var3) {
      super.load(var1, var2, var3);
      this.open = var1.get() == 1;
      this.Locked = var1.get() == 1;
      this.north = var1.get() == 1;
      this.Health = var1.getInt();
      this.MaxHealth = var1.getInt();
      this.closedSprite = IsoSprite.getSprite(IsoSpriteManager.instance, var1.getInt());
      this.openSprite = IsoSprite.getSprite(IsoSpriteManager.instance, var1.getInt());
      this.OutlineOnMouseover = true;
      this.PushedMaxStrength = this.PushedStrength = 2500;
      if (var2 >= 57) {
         this.keyId = var1.getInt();
         this.lockedByKey = var1.get() == 1;
      }

      if (var2 >= 80) {
    uint8_t var4 = var1.get();
         if ((var4 & 1) != 0) {
            this.bHasCurtain = true;
            this.bCurtainOpen = (var4 & 2) != 0;
            this.bCurtainInside = (var4 & 4) != 0;
         }
      }

      if (SystemDisabler.doObjectStateSyncEnable && GameClient.bClient) {
         GameClient.instance.objectSyncReq.putRequestLoad(this.square);
      }
   }

    void save(ByteBuffer var1, bool var2) {
      super.save(var1, var2);
      var1.put((byte)(this.open ? 1 : 0));
      var1.put((byte)(this.Locked ? 1 : 0));
      var1.put((byte)(this.north ? 1 : 0));
      var1.putInt(this.Health);
      var1.putInt(this.MaxHealth);
      var1.putInt(this.closedSprite.ID);
      var1.putInt(this.openSprite.ID);
      var1.putInt(this.getKeyId());
      var1.put((byte)(this.isLockedByKey() ? 1 : 0));
    uint8_t var3 = 0;
      if (this.bHasCurtain) {
         var3 = (byte)(var3 | 1);
         if (this.bCurtainOpen) {
            var3 = (byte)(var3 | 2);
         }

         if (this.bCurtainInside) {
            var3 = (byte)(var3 | 4);
         }
      }

      var1.put(var3);
   }

    void saveState(ByteBuffer var1) {
      var1.put((byte)(this.open ? 1 : 0));
      var1.put((byte)(this.Locked ? 1 : 0));
      var1.put((byte)(this.lockedByKey ? 1 : 0));
   }

    void loadState(ByteBuffer var1) {
    bool var2 = var1.get() == 1;
    bool var3 = var1.get() == 1;
    bool var4 = var1.get() == 1;
      if (var2 != this.open) {
         this.open = var2;
         this.sprite = var2 ? this.openSprite : this.closedSprite;
      }

      if (var3 != this.Locked) {
         this.Locked = var3;
      }

      if (var4 != this.lockedByKey) {
         this.lockedByKey = var4;
      }
   }

    bool isDestroyed() {
      return this.destroyed;
   }

    bool IsOpen() {
      return this.open;
   }

    bool IsStrengthenedByPushedItems() {
    return false;
   }

    bool onMouseLeftClick(int var1, int var2) {
    return false;
   }

    bool TestPathfindCollide(IsoMovingObject var1, IsoGridSquare var2, IsoGridSquare var3) {
    bool var4 = this.north;
      if (!this.isBarricaded()) {
    return false;
      } else if (dynamic_cast<IsoSurvivor*>(var1) != nullptr && ((IsoSurvivor)var1).getInventory().contains("Hammer")) {
    return false;
      } else {
         if (this.open) {
            var4 = !var4;
         }

         if (var2 == this.square) {
            if (var4 && var3.getY() < var2.getY()) {
    return true;
            }

            if (!var4 && var3.getX() < var2.getX()) {
    return true;
            }
         } else {
            if (var4 && var3.getY() > var2.getY()) {
    return true;
            }

            if (!var4 && var3.getX() > var2.getX()) {
    return true;
            }
         }

    return false;
      }
   }

    bool TestCollide(IsoMovingObject var1, IsoGridSquare var2, IsoGridSquare var3) {
    bool var4 = this.north;
      if (this.open) {
    return false;
      } else {
         if (var2 == this.square) {
            if (var4 && var3.getY() < var2.getY()) {
               if (var1 != nullptr) {
                  var1.collideWith(this);
               }

    return true;
            }

            if (!var4 && var3.getX() < var2.getX()) {
               if (var1 != nullptr) {
                  var1.collideWith(this);
               }

    return true;
            }
         } else {
            if (var4 && var3.getY() > var2.getY()) {
               if (var1 != nullptr) {
                  var1.collideWith(this);
               }

    return true;
            }

            if (!var4 && var3.getX() > var2.getX()) {
               if (var1 != nullptr) {
                  var1.collideWith(this);
               }

    return true;
            }
         }

    return false;
      }
   }

    VisionResult TestVision(IsoGridSquare var1, IsoGridSquare var2) {
    bool var3 = this.sprite != nullptr && this.sprite.getProperties().Is("doorTrans");
      if (this.sprite != nullptr && this.sprite.getProperties().Is("GarageDoor") && this.open) {
         var3 = true;
      }

      if (this.open) {
         var3 = true;
      } else if (this.bHasCurtain && !this.bCurtainOpen) {
         var3 = false;
      }

    bool var4 = this.north;
      if (this.open) {
         var4 = !var4;
      }

      if (var2.getZ() != var1.getZ()) {
         return VisionResult.NoEffect;
      } else {
         if (var1 == this.square) {
            if (var4 && var2.getY() < var1.getY()) {
               if (var3) {
                  return VisionResult.Unblocked;
               }

               return VisionResult.Blocked;
            }

            if (!var4 && var2.getX() < var1.getX()) {
               if (var3) {
                  return VisionResult.Unblocked;
               }

               return VisionResult.Blocked;
            }
         } else {
            if (var4 && var2.getY() > var1.getY()) {
               if (var3) {
                  return VisionResult.Unblocked;
               }

               return VisionResult.Blocked;
            }

            if (!var4 && var2.getX() > var1.getX()) {
               if (var3) {
                  return VisionResult.Unblocked;
               }

               return VisionResult.Blocked;
            }
         }

         return VisionResult.NoEffect;
      }
   }

    void Thump(IsoMovingObject var1) {
      if (!this.isDestroyed()) {
         if (dynamic_cast<IsoGameCharacter*>(var1) != nullptr) {
    Thumpable var2 = this.getThumpableFor((IsoGameCharacter)var1);
            if (var2 == nullptr) {
               return;
            }

            if (var2 != this) {
               var2.Thump(var1);
               return;
            }
         }

         if (dynamic_cast<IsoZombie*>(var1) != nullptr) {
            if (((IsoZombie)var1).cognition == 1
               && !this.open
               && (!this.Locked || var1.getCurrentSquare() != nullptr && !var1.getCurrentSquare().Is(IsoFlagType.exterior))) {
               this.ToggleDoor((IsoGameCharacter)var1);
               if (this.open) {
                  return;
               }
            }

    int var5 = var1.getCurrentSquare().getMovingObjects().size();
            if (var1.getCurrentSquare().getW() != nullptr) {
               var5 += var1.getCurrentSquare().getW().getMovingObjects().size();
            }

            if (var1.getCurrentSquare().getE() != nullptr) {
               var5 += var1.getCurrentSquare().getE().getMovingObjects().size();
            }

            if (var1.getCurrentSquare().getS() != nullptr) {
               var5 += var1.getCurrentSquare().getS().getMovingObjects().size();
            }

            if (var1.getCurrentSquare().getN() != nullptr) {
               var5 += var1.getCurrentSquare().getN().getMovingObjects().size();
            }

    int var3 = ThumpState.getFastForwardDamageMultiplier();
    int var4 = ((IsoZombie)var1).strength;
            if (var5 >= 2) {
               this.DirtySlice();
               this.Damage(((IsoZombie)var1).strength * var3);
               if (SandboxOptions.instance.Lore.Strength.getValue() == 1) {
                  this.Damage(var5 * 2 * var3);
               }
            }

            if (Core.GameMode == "LastStand")) {
               this.Damage(1 * var3);
            }

            WorldSoundManager.instance.addSound(var1, this.square.getX(), this.square.getY(), this.square.getZ(), 20, 20, true, 4.0F, 15.0F);
            this.setRenderEffect(RenderEffectType.Hit_Door, true);
         }

         if (this.Health <= 0) {
            if (this.getSquare().getBuilding() != nullptr) {
               this.getSquare().getBuilding().forceAwake();
            }

            this.playDoorSound(((IsoGameCharacter)var1).getEmitter(), "Break");
            if (GameServer.bServer) {
               GameServer.PlayWorldSoundServer((IsoGameCharacter)var1, "BreakDoor", false, var1.getCurrentSquare(), 0.2F, 20.0F, 1.1F, true);
            }

            WorldSoundManager.instance.addSound(nullptr, this.square.getX(), this.square.getY(), this.square.getZ(), 10, 20, true, 4.0F, 15.0F);
            var1.setThumpTarget(nullptr);
            if (destroyDoubleDoor(this)) {
               return;
            }

            if (destroyGarageDoor(this)) {
               return;
            }

            this.destroy();
         }
      }
   }

    Thumpable getThumpableFor(IsoGameCharacter var1) {
    IsoBarricade var2 = this.getBarricadeForCharacter(var1);
      if (var2 != nullptr) {
    return var2;
      } else {
         var2 = this.getBarricadeOppositeCharacter(var1);
         if (var2 != nullptr) {
    return var2;
         } else {
            return !this.isDestroyed() && !this.IsOpen() ? this : nullptr;
         }
      }
   }

    float getThumpCondition() {
      return this.getMaxHealth() <= 0 ? 0.0F : (float)PZMath.clamp(this.getHealth(), 0, this.getMaxHealth()) / this.getMaxHealth();
   }

    void WeaponHit(IsoGameCharacter var1, HandWeapon var2) {
    IsoPlayer var3 = (IsoPlayer)Type.tryCastTo(var1, IsoPlayer.class);
      if (GameClient.bClient) {
         if (var3 != nullptr) {
            GameClient.instance.sendWeaponHit(var3, var2, this);
         }

         this.setRenderEffect(RenderEffectType.Hit_Door, true);
      } else {
    Thumpable var4 = this.getThumpableFor(var1);
         if (var4 != nullptr) {
            if (dynamic_cast<IsoBarricade*>(var4) != nullptr) {
               ((IsoBarricade)var4).WeaponHit(var1, var2);
            } else {
               LuaEventManager.triggerEvent("OnWeaponHitThumpable", var1, var2, this);
               if (!this.open) {
                  if (!this.isDestroyed()) {
    int var5 = var1.getPerkLevel(Perks.Strength);
    float var6 = 1.0F;
                     if (var5 == 0) {
                        var6 = 0.5F;
                     } else if (var5 == 1) {
                        var6 = 0.63F;
                     } else if (var5 == 2) {
                        var6 = 0.76F;
                     } else if (var5 == 3) {
                        var6 = 0.89F;
                     } else if (var5 == 4) {
                        var6 = 1.02F;
                     }

                     if (var5 == 6) {
                        var6 = 1.15F;
                     } else if (var5 == 7) {
                        var6 = 1.27F;
                     } else if (var5 == 8) {
                        var6 = 1.3F;
                     } else if (var5 == 9) {
                        var6 = 1.45F;
                     } else if (var5 == 10) {
                        var6 = 1.7F;
                     }

                     this.Damage((int)(var2.getDoorDamage() * 2.0F * var6));
                     this.setRenderEffect(RenderEffectType.Hit_Door, true);
                     if (Rand.Next(10) == 0) {
                        this.Damage((int)(var2.getDoorDamage() * 6.0F * var6));
                     }

    float var7 = GameTime.getInstance().getMultiplier() / 1.6F;
                     switch (var1.getPerkLevel(Perks.Fitness)) {
                        case 0:
                           var1.exert(0.01F * var7);
                           break;
                        case 1:
                           var1.exert(0.007F * var7);
                           break;
                        case 2:
                           var1.exert(0.0065F * var7);
                           break;
                        case 3:
                           var1.exert(0.006F * var7);
                           break;
                        case 4:
                           var1.exert(0.005F * var7);
                           break;
                        case 5:
                           var1.exert(0.004F * var7);
                           break;
                        case 6:
                           var1.exert(0.0035F * var7);
                           break;
                        case 7:
                           var1.exert(0.003F * var7);
                           break;
                        case 8:
                           var1.exert(0.0025F * var7);
                           break;
                        case 9:
                           var1.exert(0.002F * var7);
                     }

                     this.DirtySlice();
                     if (var2.getDoorHitSound() != nullptr) {
                        if (var3 != nullptr) {
                           var3.setMeleeHitSurface(this.getSoundPrefix());
                        }

                        var1.getEmitter().playSound(var2.getDoorHitSound(), this);
                        if (GameServer.bServer) {
                           GameServer.PlayWorldSoundServer(var1, var2.getDoorHitSound(), false, this.getSquare(), 1.0F, 20.0F, 2.0F, false);
                        }
                     }

                     WorldSoundManager.instance.addSound(var1, this.square.getX(), this.square.getY(), this.square.getZ(), 20, 20, false, 0.0F, 15.0F);
                     if (!this.IsStrengthenedByPushedItems() && this.Health <= 0
                        || this.IsStrengthenedByPushedItems() && this.Health <= -this.PushedMaxStrength) {
                        this.playDoorSound(var1.getEmitter(), "Break");
                        if (GameServer.bServer) {
                           GameServer.PlayWorldSoundServer(var1, "BreakDoor", false, this.getSquare(), 0.2F, 20.0F, 1.1F, true);
                        }

                        WorldSoundManager.instance.addSound(var1, this.square.getX(), this.square.getY(), this.square.getZ(), 20, 20, false, 0.0F, 15.0F);
                        if (destroyDoubleDoor(this)) {
                           return;
                        }

                        if (destroyGarageDoor(this)) {
                           return;
                        }

                        this.destroy();
                        LuaEventManager.triggerEvent("OnContainerUpdate");
                     }
                  }
               }
            }
         }
      }
   }

    void destroy() {
      if (this.sprite != nullptr && this.sprite.getProperties().Is("GarageDoor")) {
         this.destroyed = true;
         this.square.transmitRemoveItemFromSquare(this);
      } else {
    PropertyContainer var1 = this.getProperties();
         if (var1 != nullptr) {
    std::string var2 = var1.Val("Material");
    std::string var3 = var1.Val("Material2");
    std::string var4 = var1.Val("Material3");
            if (StringUtils.isNullOrEmpty(var2) && StringUtils.isNullOrEmpty(var3) && StringUtils.isNullOrEmpty(var4)) {
    int var5 = Rand.Next(2) + 1;

               for (int var6 = 0; var6 < var5; var6++) {
                  this.square.AddWorldInventoryItem("Base.Plank", 0.0F, 0.0F, 0.0F);
               }
            } else {
               this.addItemsFromProperties();
            }

    InventoryItem var8 = InventoryItemFactory.CreateItem("Base.Doorknob");
            var8.setKeyId(this.checkKeyId());
            this.square.AddWorldInventoryItem(var8, 0.0F, 0.0F, 0.0F);
    int var9 = Rand.Next(3);

            for (int var7 = 0; var7 < var9; var7++) {
               this.square.AddWorldInventoryItem("Base.Hinge", 0.0F, 0.0F, 0.0F);
            }

            if (this.bHasCurtain) {
               this.square.AddWorldInventoryItem("Base.Sheet", 0.0F, 0.0F, 0.0F);
            }

            this.destroyed = true;
            this.square.transmitRemoveItemFromSquare(this);
         }
      }
   }

    IsoGridSquare getOtherSideOfDoor(IsoGameCharacter var1) {
      if (this.north) {
         return var1.getCurrentSquare().getRoom() == this.square.getRoom()
            ? IsoWorld.instance.CurrentCell.getGridSquare(this.square.getX(), this.square.getY() - 1, this.square.getZ())
            : IsoWorld.instance.CurrentCell.getGridSquare(this.square.getX(), this.square.getY(), this.square.getZ());
      } else {
         return var1.getCurrentSquare().getRoom() == this.square.getRoom()
            ? IsoWorld.instance.CurrentCell.getGridSquare(this.square.getX() - 1, this.square.getY(), this.square.getZ())
            : IsoWorld.instance.CurrentCell.getGridSquare(this.square.getX(), this.square.getY(), this.square.getZ());
      }
   }

    bool isExteriorDoor(IsoGameCharacter var1) {
      return this.isExterior();
   }

    bool isExterior() {
    IsoGridSquare var1 = this.getSquare();
    IsoGridSquare var2 = this.getOppositeSquare();
      if (var2 == nullptr) {
    return false;
      } else {
         return var1.Is(IsoFlagType.exterior) && var2.getBuilding() != nullptr && var2.getBuilding().getDef() != nullptr
            ? true
            : var1.getBuilding() != nullptr && var1.getBuilding().getDef() != nullptr && var2.Is(IsoFlagType.exterior);
      }
   }

    bool isHoppable() {
      if (this.IsOpen()) {
    return false;
      } else if (this.closedSprite == nullptr) {
    return false;
      } else {
    PropertyContainer var1 = this.closedSprite.getProperties();
         return var1.Is(IsoFlagType.HoppableN) || var1.Is(IsoFlagType.HoppableW);
      }
   }

    bool canClimbOver(IsoGameCharacter var1) {
      if (this.square == nullptr) {
    return false;
      } else {
         return !this.isHoppable() ? false : var1 == nullptr || IsoWindow.canClimbThroughHelper(var1, this.getSquare(), this.getOppositeSquare(), this.north);
      }
   }

    void ToggleDoorActual(IsoGameCharacter var1) {
      if (Core.bDebug && DebugOptions.instance.CheatDoorUnlock.getValue()) {
         this.Locked = false;
         this.setLockedByKey(false);
      }

      if (this.isHoppable()) {
         this.Locked = false;
         this.setLockedByKey(false);
      }

      if (this.isBarricaded()) {
         if (var1 != nullptr) {
            this.playDoorSound(var1.getEmitter(), "Blocked");
            var1.setHaloNote(Translator.getText("IGUI_PlayerText_DoorBarricaded"), 255, 255, 255, 256.0F);
            this.setRenderEffect(RenderEffectType.Hit_Door, true);
         }
      } else {
         this.checkKeyId();
         if (this.Locked && !this.lockedByKey && this.getKeyId() != -1) {
            this.lockedByKey = true;
         }

         if (!this.open && dynamic_cast<IsoPlayer*>(var1) != nullptr) {
            ((IsoPlayer)var1).TimeSinceOpenDoor = 0.0F;
         }

         this.DirtySlice();
         IsoGridSquare.RecalcLightTime = -1;
         GameTime.instance.lightSourceUpdate = 100.0F;
         this.square.InvalidateSpecialObjectPaths();
         if (this.isLockedByKey()
            && var1 != nullptr
            && dynamic_cast<IsoPlayer*>(var1) != nullptr
            && (
               var1.getCurrentSquare().Is(IsoFlagType.exterior)
                  || this.getProperties().Is("forceLocked")
                  || this.getModData().rawget("CustomLock") != nullptr
                     && this.getModData().rawget("CustomLock") instanceof bool
                     && (bool)this.getModData().rawget("CustomLock")
            )
            && !this.open) {
            if (var1.getInventory().haveThisKeyId(this.getKeyId()) == nullptr) {
               this.playDoorSound(var1.getEmitter(), "Locked");
               this.setRenderEffect(RenderEffectType.Hit_Door, true);
               return;
            }

            this.playDoorSound(var1.getEmitter(), "Unlock");
            this.playDoorSound(var1.getEmitter(), "Open");
            this.Locked = false;
            this.setLockedByKey(false);
         }

    bool var2 = dynamic_cast<IsoPlayer*>(var1) != nullptr && !var1.getCurrentSquare().isOutside();
         if ("Tutorial" == Core.getInstance().getGameMode()) && this.isLockedByKey()) {
            var2 = false;
         }

         if (dynamic_cast<IsoPlayer*>(var1) != nullptr && this.getSprite().getProperties().Is("GarageDoor")) {
    bool var3 = this.getSprite().getProperties().Is("InteriorSide");
            if (var3) {
               var2 = this.north ? var1.getY() >= this.getY() : var1.getX() >= this.getX();
            } else {
               var2 = this.north ? var1.getY() < this.getY() : var1.getX() < this.getX();
            }
         }

         if (this.Locked && !var2 && !this.open) {
            this.playDoorSound(var1.getEmitter(), "Locked");
            this.setRenderEffect(RenderEffectType.Hit_Door, true);
         } else if (this.getSprite().getProperties().Is("DoubleDoor")) {
            if (isDoubleDoorObstructed(this)) {
               if (var1 != nullptr) {
                  this.playDoorSound(var1.getEmitter(), "Blocked");
                  var1.setHaloNote(Translator.getText("IGUI_PlayerText_DoorBlocked"), 255, 255, 255, 256.0F);
               }
            } else {
    bool var6 = this.open;
               toggleDoubleDoor(this, true);
               if (var6 != this.open) {
                  this.playDoorSound(var1.getEmitter(), this.open ? "Open" : "Close");
               }
            }
         } else if (this.getSprite().getProperties().Is("GarageDoor")) {
            if (isGarageDoorObstructed(this)) {
               if (var1 != nullptr) {
                  this.playDoorSound(var1.getEmitter(), "Blocked");
                  var1.setHaloNote(Translator.getText("IGUI_PlayerText_DoorBlocked"), 255, 255, 255, 256.0F);
               }
            } else {
    bool var5 = this.open;
               toggleGarageDoor(this, true);
               if (var5 != this.open) {
                  this.playDoorSound(var1.getEmitter(), this.open ? "Open" : "Close");
               }
            }
         } else if (this.isObstructed()) {
            if (var1 != nullptr) {
               this.playDoorSound(var1.getEmitter(), "Blocked");
               var1.setHaloNote(Translator.getText("IGUI_PlayerText_DoorBlocked"), 255, 255, 255, 256.0F);
            }
         } else {
            this.Locked = false;
            this.setLockedByKey(false);
            if (dynamic_cast<IsoPlayer*>(var1) != nullptr) {
               for (int var4 = 0; var4 < IsoPlayer.numPlayers; var4++) {
                  LosUtil.cachecleared[var4] = true;
               }

               IsoGridSquare.setRecalcLightTime(-1);
            }

            this.open = !this.open;
            WeatherFxMask.forceMaskUpdateAll();
            this.sprite = this.closedSprite;
            if (this.open) {
               if (var1 != nullptr) {
                  this.playDoorSound(var1.getEmitter(), "Open");
               }

               this.sprite = this.openSprite;
            } else if (var1 != nullptr) {
               this.playDoorSound(var1.getEmitter(), "Close");
            }

            this.square.RecalcProperties();
            this.syncIsoObject(false, (byte)(this.open ? 1 : 0), nullptr, nullptr);
            PolygonalMap2.instance.squareChanged(this.square);
            LuaEventManager.triggerEvent("OnContainerUpdate");
         }
      }
   }

    void syncIsoObjectSend(ByteBufferWriter var1) {
      var1.putInt(this.square.getX());
      var1.putInt(this.square.getY());
      var1.putInt(this.square.getZ());
    uint8_t var2 = (byte)this.square.getObjects().indexOf(this);
      var1.putByte(var2);
      var1.putByte((byte)1);
      var1.putByte((byte)0);
      var1.putBoolean(this.open);
      var1.putBoolean(this.Locked);
      var1.putBoolean(this.lockedByKey);
   }

    void syncIsoObject(bool var1, uint8_t var2, UdpConnection var3, ByteBuffer var4) {
      if (this.square == nullptr) {
         System.out.println("ERROR: " + this.getClass().getSimpleName() + " square is nullptr");
      } else if (this.getObjectIndex() == -1) {
         System.out
            .println(
               "ERROR: " + this.getClass().getSimpleName() + " not found on square " + this.square.getX() + "," + this.square.getY() + "," + this.square.getZ()
            );
      } else {
    bool var5 = var4 != nullptr && var4.get() == 1;
    bool var6 = var4 != nullptr && var4.get() == 1;
    bool var7 = var4 != nullptr && var4.get() == 1;
    short var8 = -1;
         if ((GameServer.bServer || GameClient.bClient) && var4 != nullptr) {
            var8 = var4.getShort();
         }

         if (GameClient.bClient && !var1) {
            var8 = IsoPlayer.getInstance().getOnlineID();
    ByteBufferWriter var15 = GameClient.connection.startPacket();
            PacketType.SyncIsoObject.doPacket(var15);
            this.syncIsoObjectSend(var15);
            var15.putShort(var8);
            PacketType.SyncIsoObject.send(GameClient.connection);
         } else if (GameServer.bServer && !var1) {
            for (UdpConnection var17 : GameServer.udpEngine.connections) {
    ByteBufferWriter var18 = var17.startPacket();
               PacketType.SyncIsoObject.doPacket(var18);
               this.syncIsoObjectSend(var18);
               var18.putShort(var8);
               PacketType.SyncIsoObject.send(var17);
            }
         } else if (var1) {
            if (GameClient.bClient && var8 != -1) {
    IsoPlayer var9 = (IsoPlayer)GameClient.IDToPlayerMap.get(var8);
               if (var9 != nullptr) {
                  var9.networkAI.setNoCollision(1000L);
               }
            }

            if (getDoubleDoorIndex(this) != -1) {
               if (var5 != this.open) {
                  toggleDoubleDoor(this, false);
               }
            } else if (var5) {
               this.open = true;
               this.sprite = this.openSprite;
            } else {
               this.open = false;
               this.sprite = this.closedSprite;
            }

            this.Locked = var6;
            this.lockedByKey = var7;
            if (GameServer.bServer) {
               for (UdpConnection var10 : GameServer.udpEngine.connections) {
                  if (var3 != nullptr && var10.getConnectedGUID() != var3.getConnectedGUID() || var3 == nullptr) {
    ByteBufferWriter var11 = var10.startPacket();
                     PacketType.SyncIsoObject.doPacket(var11);
                     this.syncIsoObjectSend(var11);
                     var11.putShort(var8);
                     PacketType.SyncIsoObject.send(var10);
                  }
               }
            }
         }

         this.square.InvalidateSpecialObjectPaths();
         this.square.RecalcProperties();
         this.square.RecalcAllWithNeighbours(true);

         for (int var16 = 0; var16 < IsoPlayer.numPlayers; var16++) {
            LosUtil.cachecleared[var16] = true;
         }

         IsoGridSquare.setRecalcLightTime(-1);
         GameTime.instance.lightSourceUpdate = 100.0F;
         LuaEventManager.triggerEvent("OnContainerUpdate");
         WeatherFxMask.forceMaskUpdateAll();
      }
   }

    void ToggleDoor(IsoGameCharacter var1) {
      this.ToggleDoorActual(var1);
   }

    void ToggleDoorSilent() {
      if (!this.isBarricaded()) {
         this.square.InvalidateSpecialObjectPaths();

         for (int var1 = 0; var1 < IsoPlayer.numPlayers; var1++) {
            LosUtil.cachecleared[var1] = true;
         }

         IsoGridSquare.setRecalcLightTime(-1);
         this.open = !this.open;
         this.sprite = this.closedSprite;
         if (this.open) {
            this.sprite = this.openSprite;
         }
      }
   }

    void Damage(int var1) {
      this.DirtySlice();
      this.Health -= var1;
   }

    IsoBarricade getBarricadeOnSameSquare() {
      return IsoBarricade.GetBarricadeOnSquare(this.square, this.north ? IsoDirections.N : IsoDirections.W);
   }

    IsoBarricade getBarricadeOnOppositeSquare() {
      return IsoBarricade.GetBarricadeOnSquare(this.getOppositeSquare(), this.north ? IsoDirections.S : IsoDirections.E);
   }

    bool isBarricaded() {
    IsoBarricade var1 = this.getBarricadeOnSameSquare();
      if (var1 == nullptr) {
         var1 = this.getBarricadeOnOppositeSquare();
      }

      return var1 != nullptr;
   }

    bool isBarricadeAllowed() {
      return this.getSprite() != nullptr && !this.getSprite().getProperties().Is("DoubleDoor") && !this.getSprite().getProperties().Is("GarageDoor");
   }

    IsoBarricade getBarricadeForCharacter(IsoGameCharacter var1) {
      return IsoBarricade.GetBarricadeForCharacter(this, var1);
   }

    IsoBarricade getBarricadeOppositeCharacter(IsoGameCharacter var1) {
      return IsoBarricade.GetBarricadeOppositeCharacter(this, var1);
   }

    bool isLocked() {
      return this.Locked;
   }

    void setLocked(bool var1) {
      this.Locked = var1;
   }

    bool getNorth() {
      return this.north;
   }

    Vector2 getFacingPosition(Vector2 var1) {
      if (this.square == nullptr) {
         return var1.set(0.0F, 0.0F);
      } else {
         return this.north ? var1.set(this.getX() + 0.5F, this.getY()) : var1.set(this.getX(), this.getY() + 0.5F);
      }
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
    Vector2 getFacingPositionAlt(Vector2 var1) {
      if (this.square == nullptr) {
         return var1.set(0.0F, 0.0F);
      } else {
         switch (1.$SwitchMap$zombie$iso$IsoDirections[this.getSpriteEdge(false).ordinal()]) {
            case 1:
               return var1.set(this.getX() + 0.5F, this.getY());
            case 2:
               return var1.set(this.getX() + 0.5F, this.getY() + 1.0F);
            case 3:
               return var1.set(this.getX(), this.getY() + 0.5F);
            case 4:
               return var1.set(this.getX() + 1.0F, this.getY() + 0.5F);
            default:
               throw std::make_unique<IllegalStateException>();
         }
      }
   }

    void setIsLocked(bool var1) {
      this.Locked = var1;
   }

    IsoSprite getOpenSprite() {
      return this.openSprite;
   }

    void setOpenSprite(IsoSprite var1) {
      this.openSprite = var1;
   }

    int getKeyId() {
      return this.keyId;
   }

    void syncDoorKey() {
    ByteBufferWriter var1 = GameClient.connection.startPacket();
      PacketType.SyncDoorKey.doPacket(var1);
      var1.putInt(this.square.getX());
      var1.putInt(this.square.getY());
      var1.putInt(this.square.getZ());
    uint8_t var2 = (byte)this.square.getObjects().indexOf(this);
      if (var2 == -1) {
         System.out.println("ERROR: Door not found on square " + this.square.getX() + ", " + this.square.getY() + ", " + this.square.getZ());
         GameClient.connection.cancelPacket();
      } else {
         var1.putByte(var2);
         var1.putInt(this.getKeyId());
         PacketType.SyncDoorKey.send(GameClient.connection);
      }
   }

    void setKeyId(int var1) {
      if (this.keyId != var1 && GameClient.bClient) {
         this.keyId = var1;
         this.syncDoorKey();
      } else {
         this.keyId = var1;
      }
   }

    bool isLockedByKey() {
      return this.lockedByKey;
   }

    void setLockedByKey(bool var1) {
    bool var2 = var1 != this.lockedByKey;
      this.lockedByKey = var1;
      this.Locked = var1;
      if (!GameServer.bServer && var2) {
         if (var1) {
            this.syncIsoObject(false, (byte)3, nullptr, nullptr);
         } else {
            this.syncIsoObject(false, (byte)4, nullptr, nullptr);
         }
      }
   }

    bool haveKey() {
      return this.haveKey;
   }

    void setHaveKey(bool var1) {
      this.haveKey = var1;
      if (!GameServer.bServer) {
         if (var1) {
            this.syncIsoObject(false, (byte)-1, nullptr, nullptr);
         } else {
            this.syncIsoObject(false, (byte)-2, nullptr, nullptr);
         }
      }
   }

    IsoGridSquare getOppositeSquare() {
      return this.getNorth()
         ? this.getCell().getGridSquare(this.getX(), this.getY() - 1.0F, this.getZ())
         : this.getCell().getGridSquare(this.getX() - 1.0F, this.getY(), this.getZ());
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
    bool isAdjacentToSquare(IsoGridSquare var1) {
    IsoGridSquare var2 = this.getSquare();
      if (var2 != nullptr && var1 != nullptr) {
    bool var3 = !this.IsOpen();
    IsoGridSquare var4 = var2.getAdjacentSquare(IsoDirections.NW);
    IsoGridSquare var5 = var2.getAdjacentSquare(IsoDirections.N);
    IsoGridSquare var6 = var2.getAdjacentSquare(IsoDirections.NE);
    IsoGridSquare var7 = var2.getAdjacentSquare(IsoDirections.W);
    IsoGridSquare var8 = var2.getAdjacentSquare(IsoDirections.E);
    IsoGridSquare var9 = var2.getAdjacentSquare(IsoDirections.SW);
    IsoGridSquare var10 = var2.getAdjacentSquare(IsoDirections.S);
    IsoGridSquare var11 = var2.getAdjacentSquare(IsoDirections.SE);
         switch (1.$SwitchMap$zombie$iso$IsoDirections[this.getSpriteEdge(false).ordinal()]) {
            case 1:
               if (var1 == var4) {
                  if (!var4.isWallTo(var5)
                     && !var4.isWindowTo(var5)
                     && !var4.hasDoorOnEdge(IsoDirections.E, false)
                     && !var5.hasDoorOnEdge(IsoDirections.W, false)) {
                     if (var5.hasDoorOnEdge(IsoDirections.S, false)) {
    return false;
                     }

                     if (this.IsOpen() && var2.hasClosedDoorOnEdge(IsoDirections.N)) {
    return false;
                     }

    return true;
                  }

    return false;
               }

               if (var1 == var5) {
                  if (var5.hasDoorOnEdge(IsoDirections.S, false)) {
    return false;
                  }

                  if (this.IsOpen() && var2.hasClosedDoorOnEdge(IsoDirections.N)) {
    return false;
                  }

    return true;
               }

               if (var1 == var6) {
                  if (!var6.isWallTo(var5)
                     && !var6.isWindowTo(var5)
                     && !var6.hasDoorOnEdge(IsoDirections.W, false)
                     && !var5.hasDoorOnEdge(IsoDirections.E, false)) {
                     if (var5.hasDoorOnEdge(IsoDirections.S, false)) {
    return false;
                     }

                     if (this.IsOpen() && var2.hasClosedDoorOnEdge(IsoDirections.N)) {
    return false;
                     }

    return true;
                  }

    return false;
               }

               if (var1 == var7) {
                  if (!var7.isWallTo(var2)
                     && !var7.isWindowTo(var2)
                     && !var7.hasDoorOnEdge(IsoDirections.E, false)
                     && !var2.hasDoorOnEdge(IsoDirections.W, false)) {
                     if (var3 && var2.hasOpenDoorOnEdge(IsoDirections.N)) {
    return false;
                     }

    return true;
                  }

    return false;
               }

               if (var1 == var2) {
                  if (var3 && var2.hasOpenDoorOnEdge(IsoDirections.N)) {
    return false;
                  }

    return true;
               }

               if (var1 == var8) {
                  if (!var8.isWallTo(var2)
                     && !var8.isWindowTo(var2)
                     && !var8.hasDoorOnEdge(IsoDirections.W, false)
                     && !var2.hasDoorOnEdge(IsoDirections.E, false)) {
                     if (var3 && var2.hasOpenDoorOnEdge(IsoDirections.N)) {
    return false;
                     }

    return true;
                  }

    return false;
               }
               break;
            case 2:
               if (var1 == var7) {
                  if (!var7.isWallTo(var2)
                     && !var7.isWindowTo(var2)
                     && !var7.hasDoorOnEdge(IsoDirections.E, false)
                     && !var2.hasDoorOnEdge(IsoDirections.W, false)) {
                     if (var3 && var2.hasOpenDoorOnEdge(IsoDirections.S)) {
    return false;
                     }

    return true;
                  }

    return false;
               }

               if (var1 == var2) {
                  if (var3 && var2.hasOpenDoorOnEdge(IsoDirections.S)) {
    return false;
                  }

    return true;
               }

               if (var1 == var8) {
                  if (!var8.isWallTo(var2)
                     && !var8.isWindowTo(var2)
                     && !var8.hasDoorOnEdge(IsoDirections.W, false)
                     && !var2.hasDoorOnEdge(IsoDirections.E, false)) {
                     if (var3 && var2.hasOpenDoorOnEdge(IsoDirections.S)) {
    return false;
                     }

    return true;
                  }

    return false;
               }

               if (var1 == var9) {
                  if (!var9.isWallTo(var10)
                     && !var9.isWindowTo(var10)
                     && !var9.hasDoorOnEdge(IsoDirections.E, false)
                     && !var10.hasDoorOnEdge(IsoDirections.W, false)) {
                     if (var10.hasDoorOnEdge(IsoDirections.N, false)) {
    return false;
                     }

    return true;
                  }

    return false;
               }

               if (var1 == var10) {
                  if (var10.hasDoorOnEdge(IsoDirections.N, false)) {
    return false;
                  }

    return true;
               }

               if (var1 == var11) {
                  if (!var11.isWallTo(var10)
                     && !var11.isWindowTo(var10)
                     && !var11.hasDoorOnEdge(IsoDirections.W, false)
                     && !var10.hasDoorOnEdge(IsoDirections.E, false)) {
                     if (var10.hasDoorOnEdge(IsoDirections.N, false)) {
    return false;
                     }

    return true;
                  }

    return false;
               }
               break;
            case 3:
               if (var1 == var4) {
                  if (!var4.isWallTo(var7)
                     && !var4.isWindowTo(var7)
                     && !var4.hasDoorOnEdge(IsoDirections.S, false)
                     && !var7.hasDoorOnEdge(IsoDirections.N, false)) {
                     if (var3 && var7.hasDoorOnEdge(IsoDirections.E, false)) {
    return false;
                     }

                     if (this.IsOpen() && var2.hasClosedDoorOnEdge(IsoDirections.W)) {
    return false;
                     }

    return true;
                  }

    return false;
               }

               if (var1 == var7) {
                  if (var3 && var7.hasDoorOnEdge(IsoDirections.E, false)) {
    return false;
                  }

                  if (this.IsOpen() && var2.hasClosedDoorOnEdge(IsoDirections.W)) {
    return false;
                  }

    return true;
               }

               if (var1 == var9) {
                  if (!var9.isWallTo(var7)
                     && !var9.isWindowTo(var7)
                     && !var9.hasDoorOnEdge(IsoDirections.N, false)
                     && !var7.hasDoorOnEdge(IsoDirections.S, false)) {
                     if (var3 && var7.hasDoorOnEdge(IsoDirections.E, false)) {
    return false;
                     }

                     if (this.IsOpen() && var2.hasClosedDoorOnEdge(IsoDirections.W)) {
    return false;
                     }

    return true;
                  }

    return false;
               }

               if (var1 == var5) {
                  if (!var5.isWallTo(var2)
                     && !var5.isWindowTo(var2)
                     && !var5.hasDoorOnEdge(IsoDirections.S, false)
                     && !var2.hasDoorOnEdge(IsoDirections.N, false)) {
                     if (var3 && var2.hasOpenDoorOnEdge(IsoDirections.W)) {
    return false;
                     }

    return true;
                  }

    return false;
               }

               if (var1 == var2) {
                  if (var3 && var2.hasOpenDoorOnEdge(IsoDirections.W)) {
    return false;
                  }

    return true;
               }

               if (var1 == var10) {
                  if (!var10.isWallTo(var2)
                     && !var10.isWindowTo(var2)
                     && !var10.hasDoorOnEdge(IsoDirections.N, false)
                     && !var2.hasDoorOnEdge(IsoDirections.S, false)) {
                     if (var3 && var2.hasOpenDoorOnEdge(IsoDirections.W)) {
    return false;
                     }

    return true;
                  }

    return false;
               }
               break;
            case 4:
               if (var1 == var5) {
                  if (!var5.isWallTo(var2)
                     && !var5.isWindowTo(var2)
                     && !var5.hasDoorOnEdge(IsoDirections.S, false)
                     && !var2.hasDoorOnEdge(IsoDirections.N, false)) {
                     if (var3 && var2.hasOpenDoorOnEdge(IsoDirections.E)) {
    return false;
                     }

    return true;
                  }

    return false;
               }

               if (var1 == var2) {
                  if (var3 && var2.hasOpenDoorOnEdge(IsoDirections.E)) {
    return false;
                  }

    return true;
               }

               if (var1 == var10) {
                  if (!var10.isWallTo(var2)
                     && !var10.isWindowTo(var2)
                     && !var10.hasDoorOnEdge(IsoDirections.N, false)
                     && !var2.hasDoorOnEdge(IsoDirections.S, false)) {
                     if (var3 && var2.hasOpenDoorOnEdge(IsoDirections.E)) {
    return false;
                     }

    return true;
                  }

    return false;
               }

               if (var1 == var6) {
                  if (!var6.isWallTo(var8)
                     && !var6.isWindowTo(var8)
                     && !var6.hasDoorOnEdge(IsoDirections.S, false)
                     && !var7.hasDoorOnEdge(IsoDirections.N, false)) {
                     if (var8.hasDoorOnEdge(IsoDirections.W, false)) {
    return false;
                     }

    return true;
                  }

    return false;
               }

               if (var1 == var8) {
                  if (var8.hasDoorOnEdge(IsoDirections.W, false)) {
    return false;
                  }

    return true;
               }

               if (var1 == var11) {
                  if (!var11.isWallTo(var8)
                     && !var11.isWindowTo(var8)
                     && !var11.hasDoorOnEdge(IsoDirections.N, false)
                     && !var8.hasDoorOnEdge(IsoDirections.S, false)) {
                     if (var8.hasDoorOnEdge(IsoDirections.E, false)) {
    return false;
                     }

    return true;
                  }

    return false;
               }
               break;
            default:
    return false;
         }

    return false;
      } else {
    return false;
      }
   }

    int checkKeyId() {
      if (this.getKeyId() != -1) {
         return this.getKeyId();
      } else {
    IsoGridSquare var1 = this.getSquare();
    IsoGridSquare var2 = this.getOppositeSquare();
         if (var1 != nullptr && var2 != nullptr) {
    BuildingDef var3 = var1.getBuilding() == nullptr ? nullptr : var1.getBuilding().getDef();
    BuildingDef var4 = var2.getBuilding() == nullptr ? nullptr : var2.getBuilding().getDef();
            if (var3 == nullptr && var4 != nullptr) {
               this.setKeyId(var4.getKeyId());
            } else if (var3 != nullptr && var4 == nullptr) {
               this.setKeyId(var3.getKeyId());
            } else if (this.getProperties().Is("forceLocked") && var3 != nullptr) {
               this.setKeyId(var3.getKeyId());
            }

            if (this.Locked && !this.lockedByKey && this.getKeyId() != -1) {
               this.lockedByKey = true;
            }

            return this.getKeyId();
         } else {
            return -1;
         }
      }
   }

    void setHealth(int var1) {
      this.Health = var1;
   }

    void initCurtainSprites() {
      if (this.curtainN == nullptr) {
         this.curtainW = IsoSprite.CreateSprite(IsoSpriteManager.instance);
         this.curtainW.LoadFramesNoDirPageSimple("fixtures_windows_curtains_01_16");
         this.curtainW.def.setScale(0.8F, 0.8F);
         this.curtainWopen = IsoSprite.CreateSprite(IsoSpriteManager.instance);
         this.curtainWopen.LoadFramesNoDirPageSimple("fixtures_windows_curtains_01_20");
         this.curtainWopen.def.setScale(0.8F, 0.8F);
         this.curtainE = IsoSprite.CreateSprite(IsoSpriteManager.instance);
         this.curtainE.LoadFramesNoDirPageSimple("fixtures_windows_curtains_01_17");
         this.curtainE.def.setScale(0.8F, 0.8F);
         this.curtainEopen = IsoSprite.CreateSprite(IsoSpriteManager.instance);
         this.curtainEopen.LoadFramesNoDirPageSimple("fixtures_windows_curtains_01_21");
         this.curtainEopen.def.setScale(0.8F, 0.8F);
         this.curtainN = IsoSprite.CreateSprite(IsoSpriteManager.instance);
         this.curtainN.LoadFramesNoDirPageSimple("fixtures_windows_curtains_01_18");
         this.curtainN.def.setScale(0.8F, 0.8F);
         this.curtainNopen = IsoSprite.CreateSprite(IsoSpriteManager.instance);
         this.curtainNopen.LoadFramesNoDirPageSimple("fixtures_windows_curtains_01_22");
         this.curtainNopen.def.setScale(0.8F, 0.8F);
         this.curtainS = IsoSprite.CreateSprite(IsoSpriteManager.instance);
         this.curtainS.LoadFramesNoDirPageSimple("fixtures_windows_curtains_01_19");
         this.curtainS.def.setScale(0.8F, 0.8F);
         this.curtainSopen = IsoSprite.CreateSprite(IsoSpriteManager.instance);
         this.curtainSopen.LoadFramesNoDirPageSimple("fixtures_windows_curtains_01_23");
         this.curtainSopen.def.setScale(0.8F, 0.8F);
      }
   }

    IsoDoor HasCurtains() {
      return this.bHasCurtain ? this : nullptr;
   }

    bool isCurtainOpen() {
      return this.bHasCurtain && this.bCurtainOpen;
   }

    void setCurtainOpen(bool var1) {
      if (this.bHasCurtain) {
         this.bCurtainOpen = var1;
         if (!GameServer.bServer) {
            for (int var2 = 0; var2 < IsoPlayer.numPlayers; var2++) {
               LosUtil.cachecleared[var2] = true;
            }

            GameTime.instance.lightSourceUpdate = 100.0F;
            IsoGridSquare.setRecalcLightTime(-1);
            if (this.square != nullptr) {
               this.square.RecalcProperties();
               this.square.RecalcAllWithNeighbours(true);
            }
         }
      }
   }

    void transmitSetCurtainOpen(bool var1) {
      if (this.bHasCurtain) {
         if (GameServer.bServer) {
            this.sendObjectChange("setCurtainOpen", new Object[]{"open", var1});
         }

         if (GameClient.bClient) {
            GameClient.instance
               .sendClientCommandV(
                  nullptr,
                  "object",
                  "openCloseCurtain",
                  new Object[]{"x", this.getX(), "y", this.getY(), "z", this.getZ(), "index", this.getObjectIndex(), "open", !this.bCurtainOpen}
               );
         }
      }
   }

    void toggleCurtain() {
      if (this.bHasCurtain) {
         if (GameClient.bClient) {
            this.transmitSetCurtainOpen(!this.isCurtainOpen());
         } else {
            this.setCurtainOpen(!this.isCurtainOpen());
            if (GameServer.bServer) {
               this.transmitSetCurtainOpen(this.isCurtainOpen());
            }
         }
      }
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
    void addSheet(IsoGameCharacter var1) {
      if (!this.bHasCurtain && var1 != nullptr && var1.getCurrentSquare() != nullptr) {
    IsoGridSquare var2 = var1.getCurrentSquare();
    IsoGridSquare var3 = this.getSquare();

         this.addSheet(switch (1.$SwitchMap$zombie$iso$IsoDirections[this.getSpriteEdge(false).ordinal()]) {
            case 1 -> this.north == var2.getY() >= var3.getY();
            case 2 -> var2.getY() > var3.getY();
            case 3 -> this.north == var2.getX() < var3.getX();
            case 4 -> var2.getX() > var3.getX();
            default -> throw std::make_unique<IllegalStateException>();
         }, var1);
      }
   }

    void addSheet(bool var1, IsoGameCharacter var2) {
      if (!this.bHasCurtain) {
         this.bHasCurtain = true;
         this.bCurtainInside = var1;
         this.bCurtainOpen = true;
         if (GameServer.bServer) {
            this.sendObjectChange("addSheet", new Object[]{"inside", var1});
            if (var2 != nullptr) {
               var2.sendObjectChange("removeOneOf", new Object[]{"type", "Sheet"});
            }
         } else if (var2 != nullptr) {
            var2.getInventory().RemoveOneOf("Sheet");

            for (int var3 = 0; var3 < IsoPlayer.numPlayers; var3++) {
               LosUtil.cachecleared[var3] = true;
            }

            GameTime.instance.lightSourceUpdate = 100.0F;
            IsoGridSquare.setRecalcLightTime(-1);
            if (this.square != nullptr) {
               this.square.RecalcProperties();
            }
         }
      }
   }

    void removeSheet(IsoGameCharacter var1) {
      if (this.bHasCurtain) {
         this.bHasCurtain = false;
         if (GameServer.bServer) {
            this.sendObjectChange("removeSheet");
            if (var1 != nullptr) {
               var1.sendObjectChange("addItemOfType", new Object[]{"type", "Base.Sheet"});
            }
         } else if (var1 != nullptr) {
            var1.getInventory().AddItem("Base.Sheet");

            for (int var2 = 0; var2 < IsoPlayer.numPlayers; var2++) {
               LosUtil.cachecleared[var2] = true;
            }

            GameTime.instance.lightSourceUpdate = 100.0F;
            IsoGridSquare.setRecalcLightTime(-1);
            if (this.square != nullptr) {
               this.square.RecalcProperties();
            }
         }
      }
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
    IsoGridSquare getAddSheetSquare(IsoGameCharacter var1) {
      if (var1 != nullptr && var1.getCurrentSquare() != nullptr) {
    IsoGridSquare var2 = var1.getCurrentSquare();
    IsoGridSquare var3 = this.getSquare();
         switch (1.$SwitchMap$zombie$iso$IsoDirections[this.getSpriteEdge(false).ordinal()]) {
            case 1:
               return var2.getY() >= var3.getY() ? var3 : this.getCell().getGridSquare(var3.x, var3.y - 1, var3.z);
            case 2:
               return var2.getY() <= var3.getY() ? var3 : this.getCell().getGridSquare(var3.x, var3.y + 1, var3.z);
            case 3:
               return var2.getX() >= var3.getX() ? var3 : this.getCell().getGridSquare(var3.x - 1, var3.y, var3.z);
            case 4:
               return var2.getX() <= var3.getX() ? var3 : this.getCell().getGridSquare(var3.x + 1, var3.y, var3.z);
            default:
               throw std::make_unique<IllegalStateException>();
         }
      } else {
    return nullptr;
      }
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
    IsoGridSquare getSheetSquare() {
      if (!this.bHasCurtain) {
    return nullptr;
      } else {
         switch (1.$SwitchMap$zombie$iso$IsoDirections[this.getSpriteEdge(false).ordinal()]) {
            case 1:
               if (this.open) {
                  return this.bCurtainInside ? this.getCell().getGridSquare(this.getX(), this.getY() - 1.0F, this.getZ()) : this.getSquare();
               }

               return this.bCurtainInside ? this.getSquare() : this.getCell().getGridSquare(this.getX(), this.getY() - 1.0F, this.getZ());
            case 2:
               return this.bCurtainInside ? this.getCell().getGridSquare(this.getX(), this.getY() + 1.0F, this.getZ()) : this.getSquare();
            case 3:
               if (this.open) {
                  return this.bCurtainInside ? this.getCell().getGridSquare(this.getX() - 1.0F, this.getY(), this.getZ()) : this.getSquare();
               }

               return this.bCurtainInside ? this.getSquare() : this.getCell().getGridSquare(this.getX() - 1.0F, this.getY(), this.getZ());
            case 4:
               return this.bCurtainInside ? this.getCell().getGridSquare(this.getX() + 1.0F, this.getY(), this.getZ()) : this.getSquare();
            default:
               throw std::make_unique<IllegalStateException>();
         }
      }
   }

    int getHealth() {
      return this.Health;
   }

    int getMaxHealth() {
      return this.MaxHealth;
   }

    bool isFacingSheet(IsoGameCharacter var1) {
      if (this.bHasCurtain && var1 != nullptr && var1.getCurrentSquare() == this.getSheetSquare()) {
    IsoDirections var2;
         if (this.bCurtainInside) {
            if (this.open) {
               if (this.north) {
                  var2 = IsoDirections.E;
               } else {
                  var2 = IsoDirections.S;
               }
            } else if (this.north) {
               var2 = IsoDirections.N;
            } else {
               var2 = IsoDirections.W;
            }
         } else if (this.open) {
            if (this.north) {
               var2 = IsoDirections.W;
            } else {
               var2 = IsoDirections.N;
            }
         } else if (this.north) {
            var2 = IsoDirections.S;
         } else {
            var2 = IsoDirections.E;
         }

    IsoDirections var3 = this.getSpriteEdge(false);
         if (var3 == IsoDirections.E) {
            var2 = this.bCurtainInside ? IsoDirections.W : IsoDirections.E;
         }

         if (var3 == IsoDirections.S) {
            var2 = this.bCurtainInside ? IsoDirections.N : IsoDirections.S;
         }

         return var1.getDir() == var2 || var1.getDir() == IsoDirections.RotLeft(var2) || var1.getDir() == IsoDirections.RotRight(var2);
      } else {
    return false;
      }
   }

    void saveChange(const std::string& var1, KahluaTable var2, ByteBuffer var3) {
      if ("addSheet" == var1)) {
         if (var2 != nullptr && var2.rawget("inside") instanceof bool) {
            var3.put((byte)(var2.rawget("inside") ? 1 : 0));
         }
      } else if (!"removeSheet" == var1)) {
         if ("setCurtainOpen" == var1)) {
            if (var2 != nullptr && var2.rawget("open") instanceof bool) {
               var3.put((byte)(var2.rawget("open") ? 1 : 0));
            }
         } else {
            super.saveChange(var1, var2, var3);
         }
      }
   }

    void loadChange(const std::string& var1, ByteBuffer var2) {
      if ("addSheet" == var1)) {
         this.addSheet(var2.get() == 1, nullptr);
      } else if ("removeSheet" == var1)) {
         this.removeSheet(nullptr);
      } else if ("setCurtainOpen" == var1)) {
         this.setCurtainOpen(var2.get() == 1);
      } else {
         super.loadChange(var1, var2);
      }
   }

    void addRandomBarricades() {
    IsoGridSquare var1 = this.square.getRoom() == nullptr ? this.square : this.getOppositeSquare();
      if (var1 != nullptr && var1.getRoom() == nullptr) {
    bool var2 = var1 != this.square;
    IsoBarricade var3 = IsoBarricade.AddBarricadeToObject(this, var2);
         if (var3 != nullptr) {
    int var4 = Rand.Next(1, 4);

            for (int var5 = 0; var5 < var4; var5++) {
               var3.addPlank(nullptr, nullptr);
            }
         }
      }
   }

    bool isObstructed() {
    return isDoorObstructed();
   }

    static bool isDoorObstructed(IsoObject var0) {
    IsoDoor var1 = dynamic_cast<IsoDoor*>(var0) != nullptr ? (IsoDoor)var0 : nullptr;
    IsoThumpable var2 = dynamic_cast<IsoThumpable*>(var0) != nullptr ? (IsoThumpable)var0 : nullptr;
      if (var1 == nullptr && var2 == nullptr) {
    return false;
      } else {
    IsoGridSquare var3 = var0.getSquare();
         if (var3 == nullptr) {
    return false;
         } else if (!var3.isSolid() && !var3.isSolidTrans() && !var3.Has(IsoObjectType.tree)) {
    int var4 = (var3.x - 1) / 10;
    int var5 = (var3.y - 1) / 10;
    int var6 = (int)Math.ceil((var3.x + 1.0F) / 10.0F);
    int var7 = (int)Math.ceil((var3.y + 1.0F) / 10.0F);

            for (int var8 = var5; var8 <= var7; var8++) {
               for (int var9 = var4; var9 <= var6; var9++) {
    IsoChunk var10 = GameServer.bServer ? ServerMap.instance.getChunk(var9, var8) : IsoWorld.instance.CurrentCell.getChunk(var9, var8);
                  if (var10 != nullptr) {
                     for (int var11 = 0; var11 < var10.vehicles.size(); var11++) {
    BaseVehicle var12 = (BaseVehicle)var10.vehicles.get(var11);
                        if (var12.isIntersectingSquareWithShadow(var3.x, var3.y, var3.z)) {
    return true;
                        }
                     }
                  }
               }
            }

    return false;
         } else {
    return true;
         }
      }
   }

    static void toggleDoubleDoor(IsoObject var0, bool var1) {
    int var2 = getDoubleDoorIndex(var0);
      if (var2 != -1) {
    IsoDoor var3 = dynamic_cast<IsoDoor*>(var0) != nullptr ? (IsoDoor)var0 : nullptr;
    IsoThumpable var4 = dynamic_cast<IsoThumpable*>(var0) != nullptr ? (IsoThumpable)var0 : nullptr;
         if (var3 != nullptr) {
            ;
         }

    bool var6 = var3 == nullptr ? var4.open : var3.open;
    IsoObject var7 = getDoubleDoorObject(var0, 1);
    IsoObject var8 = getDoubleDoorObject(var0, 2);
    IsoObject var9 = getDoubleDoorObject(var0, 3);
    IsoObject var10 = getDoubleDoorObject(var0, 4);
         if (var7 != nullptr) {
            toggleDoubleDoorObject(var7);
         }

         if (var8 != nullptr) {
            toggleDoubleDoorObject(var8);
         }

         if (var9 != nullptr) {
            toggleDoubleDoorObject(var9);
         }

         if (var10 != nullptr) {
            toggleDoubleDoorObject(var10);
         }

         LuaEventManager.triggerEvent("OnContainerUpdate");
         if (var1) {
            if (var7 != nullptr) {
               var7.syncIsoObject(false, (byte)(var6 ? 1 : 0), nullptr, nullptr);
            } else if (var10 != nullptr) {
               var10.syncIsoObject(false, (byte)(var6 ? 1 : 0), nullptr, nullptr);
            }
         }
      }
   }

    static void toggleDoubleDoorObject(IsoObject var0) {
    int var1 = getDoubleDoorIndex(var0);
      if (var1 != -1) {
    IsoDoor var2 = dynamic_cast<IsoDoor*>(var0) != nullptr ? (IsoDoor)var0 : nullptr;
    IsoThumpable var3 = dynamic_cast<IsoThumpable*>(var0) != nullptr ? (IsoThumpable)var0 : nullptr;
    bool var4 = var2 == nullptr ? var3.north : var2.north;
    bool var5 = var2 == nullptr ? var3.open : var2.open;
    int var6 = -1;
         if (var2 != nullptr) {
            var2.open = !var5;
            var2.setLockedByKey(false);
            var6 = var2.checkKeyId();
         }

         if (var3 != nullptr) {
            var3.open = !var5;
            var3.setLockedByKey(false);
            var6 = var3.getKeyId();
         }

    IsoSprite var7 = var0.getSprite();
    int var8 = var4 ? DoubleDoorNorthSpriteOffset[var1 - 1] : DoubleDoorWestSpriteOffset[var1 - 1];
         if (var5) {
            var8 *= -1;
         }

         var0.sprite = IsoSprite.getSprite(IsoSpriteManager.instance, var7.getName(), var8);
         var0.getSquare().RecalcAllWithNeighbours(true);
         if (var1 != 2 && var1 != 3) {
            PolygonalMap2.instance.squareChanged(var0.getSquare());
         } else {
    IsoGridSquare var9 = var0.getSquare();
            int[] var10;
            int[] var11;
            int[] var12;
            int[] var13;
            if (var4) {
               if (var5) {
                  var10 = DoubleDoorNorthOpenXOffset;
                  var11 = DoubleDoorNorthOpenYOffset;
                  var12 = DoubleDoorNorthClosedXOffset;
                  var13 = DoubleDoorNorthClosedYOffset;
               } else {
                  var10 = DoubleDoorNorthClosedXOffset;
                  var11 = DoubleDoorNorthClosedYOffset;
                  var12 = DoubleDoorNorthOpenXOffset;
                  var13 = DoubleDoorNorthOpenYOffset;
               }
            } else if (var5) {
               var10 = DoubleDoorWestOpenXOffset;
               var11 = DoubleDoorWestOpenYOffset;
               var12 = DoubleDoorWestClosedXOffset;
               var13 = DoubleDoorWestClosedYOffset;
            } else {
               var10 = DoubleDoorWestClosedXOffset;
               var11 = DoubleDoorWestClosedYOffset;
               var12 = DoubleDoorWestOpenXOffset;
               var13 = DoubleDoorWestOpenYOffset;
            }

    int var14 = var9.getX() - var10[var1 - 1];
    int var15 = var9.getY() - var11[var1 - 1];
    int var16 = var14 + var12[var1 - 1];
    int var17 = var15 + var13[var1 - 1];
            var9.RemoveTileObject(var0);
            PolygonalMap2.instance.squareChanged(var9);
            var9 = IsoWorld.instance.CurrentCell.getGridSquare(var16, var17, var9.getZ());
            if (var9 == nullptr) {
               return;
            }

            if (var3 != nullptr) {
    IsoThumpable var18 = std::make_shared<IsoThumpable>(var9.getCell(), var9, var0.getSprite().getName(), var4, var3.getTable());
               var18.setModData(var3.getModData());
               var18.setCanBeLockByPadlock(var3.canBeLockByPadlock());
               var18.setCanBePlastered(var3.canBePlastered());
               var18.setIsHoppable(var3.isHoppable());
               var18.setIsDismantable(var3.isDismantable());
               var18.setName(var3.getName());
               var18.setIsDoor(true);
               var18.setIsThumpable(var3.isThumpable());
               var18.setThumpDmg(var3.getThumpDmg());
               var18.setThumpSound(var3.getThumpSound());
               var18.open = !var5;
               var18.keyId = var6;
               var9.AddSpecialObject(var18);
            } else {
    IsoDoor var20 = std::make_shared<IsoDoor>(var9.getCell(), var9, var0.getSprite().getName(), var4);
               var20.open = !var5;
               var20.keyId = var6;
               var9.getObjects().push_back(var20);
               var9.getSpecialObjects().push_back(var20);
               var9.RecalcProperties();
            }

            if (!GameClient.bClient) {
               var9.restackSheetRope();
            }

            PolygonalMap2.instance.squareChanged(var9);
         }
      }
   }

    static int getDoubleDoorIndex(IsoObject var0) {
      if (var0 != nullptr && var0.getSquare() != nullptr) {
    PropertyContainer var1 = var0.getProperties();
         if (var1 != nullptr && var1.Is("DoubleDoor")) {
    int var2 = int.parseInt(var1.Val("DoubleDoor"));
            if (var2 >= 1 && var2 <= 8) {
    IsoDoor var3 = dynamic_cast<IsoDoor*>(var0) != nullptr ? (IsoDoor)var0 : nullptr;
    IsoThumpable var4 = dynamic_cast<IsoThumpable*>(var0) != nullptr ? (IsoThumpable)var0 : nullptr;
               if (var3 == nullptr && var4 == nullptr) {
                  return -1;
               } else {
    bool var5 = var3 == nullptr ? var4.open : var3.open;
                  if (!var5) {
    return var2;
                  } else {
                     return var2 >= 5 ? var2 - 4 : -1;
                  }
               }
            } else {
               return -1;
            }
         } else {
            return -1;
         }
      } else {
         return -1;
      }
   }

    static IsoObject getDoubleDoorObject(IsoObject var0, int var1) {
    int var2 = getDoubleDoorIndex(var0);
      if (var2 == -1) {
    return nullptr;
      } else {
    IsoDoor var3 = dynamic_cast<IsoDoor*>(var0) != nullptr ? (IsoDoor)var0 : nullptr;
    IsoThumpable var4 = dynamic_cast<IsoThumpable*>(var0) != nullptr ? (IsoThumpable)var0 : nullptr;
    bool var5 = var3 == nullptr ? var4.north : var3.north;
    bool var6 = var3 == nullptr ? var4.open : var3.open;
    IsoGridSquare var7 = var0.getSquare();
         int[] var8;
         int[] var9;
         if (var5) {
            if (var6) {
               var8 = DoubleDoorNorthOpenXOffset;
               var9 = DoubleDoorNorthOpenYOffset;
            } else {
               var8 = DoubleDoorNorthClosedXOffset;
               var9 = DoubleDoorNorthClosedYOffset;
            }
         } else if (var6) {
            var8 = DoubleDoorWestOpenXOffset;
            var9 = DoubleDoorWestOpenYOffset;
         } else {
            var8 = DoubleDoorWestClosedXOffset;
            var9 = DoubleDoorWestClosedYOffset;
         }

    int var10 = var7.getX() - var8[var2 - 1];
    int var11 = var7.getY() - var9[var2 - 1];
    int var12 = var10 + var8[var1 - 1];
    int var13 = var11 + var9[var1 - 1];
         var7 = IsoWorld.instance.CurrentCell.getGridSquare(var12, var13, var7.getZ());
         if (var7 == nullptr) {
    return nullptr;
         } else {
    std::vector var14 = var7.getSpecialObjects();
            if (var3 != nullptr) {
               for (int var15 = 0; var15 < var14.size(); var15++) {
    IsoObject var16 = (IsoObject)var14.get(var15);
                  if (dynamic_cast<IsoDoor*>(var16) != nullptr && ((IsoDoor)var16).north == var5 && getDoubleDoorIndex(var16) == var1) {
    return var16;
                  }
               }
            }

            if (var4 != nullptr) {
               for (int var18 = 0; var18 < var14.size(); var18++) {
    IsoObject var19 = (IsoObject)var14.get(var18);
                  if (dynamic_cast<IsoThumpable*>(var19) != nullptr && ((IsoThumpable)var19).north == var5 && getDoubleDoorIndex(var19) == var1) {
    return var19;
                  }
               }
            }

    return nullptr;
         }
      }
   }

    static bool isDoubleDoorObstructed(IsoObject var0) {
    int var1 = getDoubleDoorIndex(var0);
      if (var1 == -1) {
    return false;
      } else {
    IsoDoor var2 = dynamic_cast<IsoDoor*>(var0) != nullptr ? (IsoDoor)var0 : nullptr;
    IsoThumpable var3 = dynamic_cast<IsoThumpable*>(var0) != nullptr ? (IsoThumpable)var0 : nullptr;
    bool var4 = var2 == nullptr ? var3.north : var2.north;
    bool var5 = var2 == nullptr ? var3.open : var2.open;
    IsoGridSquare var6 = var0.getSquare();
         int[] var7;
         int[] var8;
         if (var4) {
            if (var5) {
               var7 = DoubleDoorNorthOpenXOffset;
               var8 = DoubleDoorNorthOpenYOffset;
            } else {
               var7 = DoubleDoorNorthClosedXOffset;
               var8 = DoubleDoorNorthClosedYOffset;
            }
         } else if (var5) {
            var7 = DoubleDoorWestOpenXOffset;
            var8 = DoubleDoorWestOpenYOffset;
         } else {
            var7 = DoubleDoorWestClosedXOffset;
            var8 = DoubleDoorWestClosedYOffset;
         }

    int var9 = var6.getX() - var7[var1 - 1];
    int var10 = var6.getY() - var8[var1 - 1];
    int var11 = var9;
    int var12 = var10 + (var4 ? 0 : -3);
    int var13 = var9 + (var4 ? 4 : 2);
    int var14 = var12 + (var4 ? 2 : 4);
    int var15 = var6.getZ();

         for (int var16 = var12; var16 < var14; var16++) {
            for (int var17 = var11; var17 < var13; var17++) {
    IsoGridSquare var18 = IsoWorld.instance.CurrentCell.getGridSquare(var17, var16, var15);
               if (var18 != nullptr && (var18.isSolid() || var18.isSolidTrans() || var18.Has(IsoObjectType.tree))) {
    return true;
               }
            }
         }

         if (var4) {
            if (hasSomething4x4(var9, var10, var9 + 1, var10 + 1, var15)) {
    return true;
            }

            if (hasSomething4x4(var9 + 2, var10, var9 + 3, var10 + 1, var15)) {
    return true;
            }
         } else {
            if (hasSomething4x4(var9, var10 - 1, var9 + 1, var10, var15)) {
    return true;
            }

            if (hasSomething4x4(var9, var10 - 3, var9 + 1, var10 - 2, var15)) {
    return true;
            }
         }

    int var27 = (var11 - 4) / 10;
    int var28 = (var12 - 4) / 10;
    int var29 = (int)Math.ceil((var13 + 4) / 10);
    int var19 = (int)Math.ceil((var14 + 4) / 10);

         for (int var20 = var28; var20 <= var19; var20++) {
            for (int var21 = var27; var21 <= var29; var21++) {
    IsoChunk var22 = GameServer.bServer ? ServerMap.instance.getChunk(var21, var20) : IsoWorld.instance.CurrentCell.getChunk(var21, var20);
               if (var22 != nullptr) {
                  for (int var23 = 0; var23 < var22.vehicles.size(); var23++) {
    BaseVehicle var24 = (BaseVehicle)var22.vehicles.get(var23);

                     for (int var25 = var12; var25 < var14; var25++) {
                        for (int var26 = var11; var26 < var13; var26++) {
                           if (var24.isIntersectingSquare(var26, var25, var15)) {
    return true;
                           }
                        }
                     }
                  }
               }
            }
         }

    return false;
      }
   }

    static bool isSomethingTo(IsoGridSquare var0, IsoGridSquare var1) {
      if (var0 != nullptr && var1 != nullptr) {
         if (var1 != var0.getAdjacentSquare(IsoDirections.E)
            || !var0.hasDoorOnEdge(IsoDirections.E, false) && !var1.hasDoorOnEdge(IsoDirections.W, false) && !var1.getProperties().Is(IsoFlagType.DoorWallW)) {
            if (var1 != var0.getAdjacentSquare(IsoDirections.SE)
               || !var0.hasDoorOnEdge(IsoDirections.E, false)
                  && !var0.hasDoorOnEdge(IsoDirections.S, false)
                  && !var1.hasDoorOnEdge(IsoDirections.W, false)
                  && !var1.hasDoorOnEdge(IsoDirections.N, false)
                  && !var1.getProperties().Is(IsoFlagType.DoorWallN)
                  && !var1.getProperties().Is(IsoFlagType.DoorWallW)) {
               return var1 != var0.getAdjacentSquare(IsoDirections.S)
                     || !var0.hasDoorOnEdge(IsoDirections.S, false)
                        && !var1.hasDoorOnEdge(IsoDirections.N, false)
                        && !var1.getProperties().Is(IsoFlagType.DoorWallN)
                  ? var0.isWallTo(var1) || var0.isWindowTo(var1)
                  : true;
            } else {
    return true;
            }
         } else {
    return true;
         }
      } else {
    return false;
      }
   }

    static bool hasSomething4x4(int var0, int var1, int var2, int var3, int var4) {
    IsoGridSquare var5 = IsoWorld.instance.CurrentCell.getGridSquare(var0, var1, var4);
    IsoGridSquare var6 = IsoWorld.instance.CurrentCell.getGridSquare(var2, var1, var4);
    IsoGridSquare var7 = IsoWorld.instance.CurrentCell.getGridSquare(var2, var3, var4);
    IsoGridSquare var8 = IsoWorld.instance.CurrentCell.getGridSquare(var0, var3, var4);
      if (isSomethingTo(var5, var6)) {
    return true;
      } else {
    return isSomethingTo();
      }
   }

    static bool destroyDoubleDoor(IsoObject var0) {
    int var1 = getDoubleDoorIndex(var0);
      if (var1 == -1) {
    return false;
      } else {
         if (var1 == 1 || var1 == 4) {
    IsoObject var2 = getDoubleDoorObject(var0, var1 == 1 ? 2 : 3);
            if (dynamic_cast<IsoDoor*>(var2) != nullptr) {
               ((IsoDoor)var2).destroy();
            } else if (dynamic_cast<IsoThumpable*>(var2) != nullptr) {
               ((IsoThumpable)var2).destroy();
            }
         }

         if (dynamic_cast<IsoDoor*>(var0) != nullptr) {
            ((IsoDoor)var0).destroy();
         } else if (dynamic_cast<IsoThumpable*>(var0) != nullptr) {
            ((IsoThumpable)var0).destroy();
         }

         LuaEventManager.triggerEvent("OnContainerUpdate");
    return true;
      }
   }

    static int getGarageDoorIndex(IsoObject var0) {
      if (var0 != nullptr && var0.getSquare() != nullptr) {
    PropertyContainer var1 = var0.getProperties();
         if (var1 != nullptr && var1.Is("GarageDoor")) {
    int var2 = int.parseInt(var1.Val("GarageDoor"));
            if (var2 >= 1 && var2 <= 6) {
    IsoDoor var3 = dynamic_cast<IsoDoor*>(var0) != nullptr ? (IsoDoor)var0 : nullptr;
    IsoThumpable var4 = dynamic_cast<IsoThumpable*>(var0) != nullptr ? (IsoThumpable)var0 : nullptr;
               if (var3 == nullptr && var4 == nullptr) {
                  return -1;
               } else {
    bool var5 = var3 == nullptr ? var4.open : var3.open;
                  if (!var5) {
    return var2;
                  } else {
                     return var2 >= 4 ? var2 - 3 : -1;
                  }
               }
            } else {
               return -1;
            }
         } else {
            return -1;
         }
      } else {
         return -1;
      }
   }

    static IsoObject getGarageDoorPrev(IsoObject var0) {
    int var1 = getGarageDoorIndex(var0);
      if (var1 == -1) {
    return nullptr;
      } else if (var1 == 1) {
    return nullptr;
      } else {
    IsoDoor var2 = dynamic_cast<IsoDoor*>(var0) != nullptr ? (IsoDoor)var0 : nullptr;
    IsoThumpable var3 = dynamic_cast<IsoThumpable*>(var0) != nullptr ? (IsoThumpable)var0 : nullptr;
    bool var4 = var2 == nullptr ? var3.north : var2.north;
    IsoGridSquare var5 = var0.getSquare();
    int var6 = var5.x - (var4 ? 1 : 0);
    int var7 = var5.y + (var4 ? 0 : 1);
         var5 = IsoWorld.instance.CurrentCell.getGridSquare(var6, var7, var5.getZ());
         if (var5 == nullptr) {
    return nullptr;
         } else {
    std::vector var8 = var5.getSpecialObjects();
            if (var2 != nullptr) {
               for (int var9 = 0; var9 < var8.size(); var9++) {
    IsoObject var10 = (IsoObject)var8.get(var9);
                  if (dynamic_cast<IsoDoor*>(var10) != nullptr && ((IsoDoor)var10).north == var4 && getGarageDoorIndex(var10) <= var1) {
    return var10;
                  }
               }
            }

            if (var3 != nullptr) {
               for (int var12 = 0; var12 < var8.size(); var12++) {
    IsoObject var13 = (IsoObject)var8.get(var12);
                  if (dynamic_cast<IsoThumpable*>(var13) != nullptr && ((IsoThumpable)var13).north == var4 && getGarageDoorIndex(var13) <= var1) {
    return var13;
                  }
               }
            }

    return nullptr;
         }
      }
   }

    static IsoObject getGarageDoorNext(IsoObject var0) {
    int var1 = getGarageDoorIndex(var0);
      if (var1 == -1) {
    return nullptr;
      } else if (var1 == 3) {
    return nullptr;
      } else {
    IsoDoor var2 = dynamic_cast<IsoDoor*>(var0) != nullptr ? (IsoDoor)var0 : nullptr;
    IsoThumpable var3 = dynamic_cast<IsoThumpable*>(var0) != nullptr ? (IsoThumpable)var0 : nullptr;
    bool var4 = var2 == nullptr ? var3.north : var2.north;
    IsoGridSquare var5 = var0.getSquare();
    int var6 = var5.x + (var4 ? 1 : 0);
    int var7 = var5.y - (var4 ? 0 : 1);
         var5 = IsoWorld.instance.CurrentCell.getGridSquare(var6, var7, var5.getZ());
         if (var5 == nullptr) {
    return nullptr;
         } else {
    std::vector var8 = var5.getSpecialObjects();
            if (var2 != nullptr) {
               for (int var9 = 0; var9 < var8.size(); var9++) {
    IsoObject var10 = (IsoObject)var8.get(var9);
                  if (dynamic_cast<IsoDoor*>(var10) != nullptr && ((IsoDoor)var10).north == var4 && getGarageDoorIndex(var10) >= var1) {
    return var10;
                  }
               }
            }

            if (var3 != nullptr) {
               for (int var12 = 0; var12 < var8.size(); var12++) {
    IsoObject var13 = (IsoObject)var8.get(var12);
                  if (dynamic_cast<IsoThumpable*>(var13) != nullptr && ((IsoThumpable)var13).north == var4 && getGarageDoorIndex(var13) >= var1) {
    return var13;
                  }
               }
            }

    return nullptr;
         }
      }
   }

    static IsoObject getGarageDoorFirst(IsoObject var0) {
    int var1 = getGarageDoorIndex(var0);
      if (var1 == -1) {
    return nullptr;
      } else if (var1 == 1) {
    return var0;
      } else {
         for (IsoObject var2 = getGarageDoorPrev(var0); var2 != nullptr; var2 = getGarageDoorPrev(var2)) {
            if (getGarageDoorIndex(var2) == 1) {
    return var2;
            }
         }

    return var0;
      }
   }

    static void toggleGarageDoorObject(IsoObject var0) {
    int var1 = getGarageDoorIndex(var0);
      if (var1 != -1) {
    IsoDoor var2 = dynamic_cast<IsoDoor*>(var0) != nullptr ? (IsoDoor)var0 : nullptr;
    IsoThumpable var3 = dynamic_cast<IsoThumpable*>(var0) != nullptr ? (IsoThumpable)var0 : nullptr;
    bool var4 = var2 == nullptr ? var3.open : var2.open;
         if (var2 != nullptr) {
            var2.open = !var4;
            var2.setLockedByKey(false);
            var2.sprite = var2.open ? var2.openSprite : var2.closedSprite;
         }

         if (var3 != nullptr) {
            var3.open = !var4;
            var3.setLockedByKey(false);
            var3.sprite = var3.open ? var3.openSprite : var3.closedSprite;
         }

         var0.getSquare().RecalcAllWithNeighbours(true);
         var0.syncIsoObject(false, (byte)(var4 ? 0 : 1), nullptr, nullptr);
         PolygonalMap2.instance.squareChanged(var0.getSquare());
      }
   }

    static void toggleGarageDoor(IsoObject var0, bool var1) {
    int var2 = getGarageDoorIndex(var0);
      if (var2 != -1) {
         toggleGarageDoorObject(var0);

         for (IsoObject var3 = getGarageDoorPrev(var0); var3 != nullptr; var3 = getGarageDoorPrev(var3)) {
            toggleGarageDoorObject(var3);
         }

         for (IsoObject var4 = getGarageDoorNext(var0); var4 != nullptr; var4 = getGarageDoorNext(var4)) {
            toggleGarageDoorObject(var4);
         }

         for (int var5 = 0; var5 < IsoPlayer.numPlayers; var5++) {
            LosUtil.cachecleared[var5] = true;
         }

         IsoGridSquare.setRecalcLightTime(-1);
         LuaEventManager.triggerEvent("OnContainerUpdate");
      }
   }

    static bool isGarageDoorObstructed(IsoObject var0) {
    int var1 = getGarageDoorIndex(var0);
      if (var1 == -1) {
    return false;
      } else {
    IsoDoor var2 = dynamic_cast<IsoDoor*>(var0) != nullptr ? (IsoDoor)var0 : nullptr;
    IsoThumpable var3 = dynamic_cast<IsoThumpable*>(var0) != nullptr ? (IsoThumpable)var0 : nullptr;
    bool var4 = var2 == nullptr ? var3.north : var2.north;
    bool var5 = var2 == nullptr ? var3.open : var2.open;
         if (!var5) {
    return false;
         } else {
    int var6 = var0.square.x;
    int var7 = var0.square.y;
    int var8 = var6;
    int var9 = var7;
            if (var4) {
               for (IsoObject var10 = getGarageDoorPrev(var0); var10 != nullptr; var10 = getGarageDoorPrev(var10)) {
                  var6--;
               }

               for (IsoObject var11 = getGarageDoorNext(var0); var11 != nullptr; var11 = getGarageDoorNext(var11)) {
                  var8++;
               }
            } else {
               for (IsoObject var22 = getGarageDoorPrev(var0); var22 != nullptr; var22 = getGarageDoorPrev(var22)) {
                  var9++;
               }

               for (IsoObject var24 = getGarageDoorNext(var0); var24 != nullptr; var24 = getGarageDoorNext(var24)) {
                  var7--;
               }
            }

    int var23 = (var6 - 4) / 10;
    int var25 = (var7 - 4) / 10;
    int var12 = (int)Math.ceil((var8 + 4) / 10);
    int var13 = (int)Math.ceil((var9 + 4) / 10);
    int var14 = var0.square.z;

            for (int var15 = var25; var15 <= var13; var15++) {
               for (int var16 = var23; var16 <= var12; var16++) {
    IsoChunk var17 = GameServer.bServer ? ServerMap.instance.getChunk(var16, var15) : IsoWorld.instance.CurrentCell.getChunk(var16, var15);
                  if (var17 != nullptr) {
                     for (int var18 = 0; var18 < var17.vehicles.size(); var18++) {
    BaseVehicle var19 = (BaseVehicle)var17.vehicles.get(var18);

                        for (int var20 = var7; var20 <= var9; var20++) {
                           for (int var21 = var6; var21 <= var8; var21++) {
                              if (var19.isIntersectingSquare(var21, var20, var14)
                                 && var19.isIntersectingSquare(var21 - (var4 ? 0 : 1), var20 - (var4 ? 1 : 0), var14)) {
    return true;
                              }
                           }
                        }
                     }
                  }
               }
            }

    return false;
         }
      }
   }

    static bool destroyGarageDoor(IsoObject var0) {
    int var1 = getGarageDoorIndex(var0);
      if (var1 == -1) {
    return false;
      } else {
    IsoObject var2 = getGarageDoorPrev(var0);

         while (var2 != nullptr) {
    IsoObject var3 = getGarageDoorPrev(var2);
            if (dynamic_cast<IsoDoor*>(var2) != nullptr) {
               ((IsoDoor)var2).destroy();
            } else if (dynamic_cast<IsoThumpable*>(var2) != nullptr) {
               ((IsoThumpable)var2).destroy();
            }

            var2 = var3;
         }

    IsoObject var5 = getGarageDoorNext(var0);

         while (var5 != nullptr) {
    IsoObject var4 = getGarageDoorNext(var5);
            if (dynamic_cast<IsoDoor*>(var5) != nullptr) {
               ((IsoDoor)var5).destroy();
            } else if (dynamic_cast<IsoThumpable*>(var5) != nullptr) {
               ((IsoThumpable)var5).destroy();
            }

            var5 = var4;
         }

         if (dynamic_cast<IsoDoor*>(var0) != nullptr) {
            ((IsoDoor)var0).destroy();
         } else if (dynamic_cast<IsoThumpable*>(var0) != nullptr) {
            ((IsoThumpable)var0).destroy();
         }

         LuaEventManager.triggerEvent("OnContainerUpdate");
    return true;
      }
   }

    IsoObject getRenderEffectMaster() {
    int var1 = getDoubleDoorIndex(this);
      if (var1 != -1) {
    IsoObject var2 = nullptr;
         if (var1 == 2) {
            var2 = getDoubleDoorObject(this, 1);
         } else if (var1 == 3) {
            var2 = getDoubleDoorObject(this, 4);
         }

         if (var2 != nullptr) {
    return var2;
         }
      } else {
    IsoObject var3 = getGarageDoorFirst(this);
         if (var3 != nullptr) {
    return var3;
         }
      }

    return this;
   }

    std::string getThumpSound() {
    std::string var1 = this.getSoundPrefix();
      switch (var1) {
         case "GarageDoor":
            return "ZombieThumpGarageDoor";
         case "MetalDoor":
         case "MetalGate":
         case "PrisonMetalDoor":
            return "ZombieThumpMetal";
         case "SlidingGlassDoor":
            return "ZombieThumpWindow";
         default:
            return "ZombieThumpGeneric";
      }
   }

    std::string getSoundPrefix() {
      if (this.closedSprite == nullptr) {
         return "WoodDoor";
      } else {
    PropertyContainer var1 = this.closedSprite.getProperties();
         return var1.Is("DoorSound") ? var1.Val("DoorSound") : "WoodDoor";
      }
   }

    void playDoorSound(BaseCharacterSoundEmitter var1, const std::string& var2) {
      var1.playSound(this.getSoundPrefix() + var2, this);
   }
}
} // namespace objects
} // namespace iso
} // namespace zombie
