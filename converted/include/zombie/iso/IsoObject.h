#pragma once
#include "fmod/fmod/FMODManager.h"
#include "org/lwjgl/opengl/ARBShaderObjects.h"
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "zombie/GameTime.h"
#include "zombie/GameWindow.h"
#include "zombie/IndieGL.h"
#include "zombie/Lua/LuaEventManager.h"
#include "zombie/Lua/LuaManager.h"
#include "zombie/SandboxOptions.h"
#include "zombie/SoundManager.h"
#include "zombie/SystemDisabler.h"
#include "zombie/WorldSoundManager.h"
#include "zombie/ai/states/ThumpState.h"
#include "zombie/audio/BaseSoundEmitter.h"
#include "zombie/audio/ObjectAmbientEmitters.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoLivingCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/characters/IsoSurvivor.h"
#include "zombie/characters/IsoZombie.h"
#include "zombie/core/Color.h"
#include "zombie/core/Core.h"
#include "zombie/core/Rand.h"
#include "zombie/core/SpriteRenderer.h"
#include "zombie/core/logger/ExceptionLogger.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/opengl/RenderSettings.h"
#include "zombie/core/opengl/RenderThread.h"
#include "zombie/core/opengl/Shader.h"
#include "zombie/core/opengl/ShaderProgram.h"
#include "zombie/core/properties/PropertyContainer.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/core/textures/ColorInfo.h"
#include "zombie/core/textures/Texture.h"
#include "zombie/core/textures/TextureDraw.h"
#include "zombie/core/utils/Bits.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugOptions.h"
#include "zombie/debug/LineDrawer.h"
#include "zombie/inventory/InventoryItem.h"
#include "zombie/inventory/InventoryItemFactory.h"
#include "zombie/inventory/ItemContainer.h"
#include "zombie/inventory/ItemPickerJava.h"
#include "zombie/inventory/types/HandWeapon.h"
#include "zombie/iso/SpriteDetails/IsoFlagType.h"
#include "zombie/iso/SpriteDetails/IsoObjectType.h"
#include "zombie/iso/areas/isoregion/IsoRegions.h"
#include "zombie/iso/objects/BSFurnace.h"
#include "zombie/iso/objects/IsoBarbecue.h"
#include "zombie/iso/objects/IsoBarricade.h"
#include "zombie/iso/objects/IsoBrokenGlass.h"
#include "zombie/iso/objects/IsoCarBatteryCharger.h"
#include "zombie/iso/objects/IsoClothingDryer.h"
#include "zombie/iso/objects/IsoClothingWasher.h"
#include "zombie/iso/objects/IsoCombinationWasherDryer.h"
#include "zombie/iso/objects/IsoCompost.h"
#include "zombie/iso/objects/IsoCurtain.h"
#include "zombie/iso/objects/IsoDeadBody.h"
#include "zombie/iso/objects/IsoDoor.h"
#include "zombie/iso/objects/IsoFire.h"
#include "zombie/iso/objects/IsoFireplace.h"
#include "zombie/iso/objects/IsoGenerator.h"
#include "zombie/iso/objects/IsoJukebox.h"
#include "zombie/iso/objects/IsoLightSwitch.h"
#include "zombie/iso/objects/IsoMannequin.h"
#include "zombie/iso/objects/IsoMolotovCocktail.h"
#include "zombie/iso/objects/IsoRadio.h"
#include "zombie/iso/objects/IsoStackedWasherDryer.h"
#include "zombie/iso/objects/IsoStove.h"
#include "zombie/iso/objects/IsoTelevision.h"
#include "zombie/iso/objects/IsoThumpable.h"
#include "zombie/iso/objects/IsoTrap.h"
#include "zombie/iso/objects/IsoTree.h"
#include "zombie/iso/objects/IsoWheelieBin.h"
#include "zombie/iso/objects/IsoWindow.h"
#include "zombie/iso/objects/IsoWindowFrame.h"
#include "zombie/iso/objects/IsoWorldInventoryObject.h"
#include "zombie/iso/objects/IsoZombieGiblets.h"
#include "zombie/iso/objects/ObjectRenderEffects.h"
#include "zombie/iso/objects/RenderEffectType.h"
#include "zombie/iso/objects/interfaces/Thumpable.h"
#include "zombie/iso/sprite/IsoSprite.h"
#include "zombie/iso/sprite/IsoSpriteGrid.h"
#include "zombie/iso/sprite/IsoSpriteInstance.h"
#include "zombie/iso/sprite/IsoSpriteManager.h"
#include "zombie/iso/sprite/shapers/FloorShaper.h"
#include "zombie/iso/sprite/shapers/WallShaper.h"
#include "zombie/iso/sprite/shapers/WallShaperN.h"
#include "zombie/iso/sprite/shapers/WallShaperW.h"
#include "zombie/iso/sprite/shapers/WallShaperWhole.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/PacketTypes.h"
#include "zombie/network/ServerOptions.h"
#include "zombie/spnetwork/SinglePlayerServer.h"
#include "zombie/ui/ObjectTooltip.h"
#include "zombie/util/StringUtils.h"
#include "zombie/util/Type.h"
#include "zombie/util/io/BitHeader.h"
#include "zombie/util/io/BitHeaderRead.h"
#include "zombie/util/io/BitHeaderWrite.h"
#include "zombie/util/list/PZArrayList.h"
#include "zombie/vehicles/BaseVehicle.h"
#include "zombie/world/WorldDictionary.h"
#include <algorithm>
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
namespace iso {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class IsoObject {
public:
  static const uint8_t OBF_Highlighted = 1;
  static const uint8_t OBF_HighlightRenderOnce = 2;
  static const uint8_t OBF_Blink = 4;
  static const int MAX_WALL_SPLATS = 32;
  static const std::string PropMoveWithWind = "MoveWithWind";
  static IsoObject lastRendered = null;
  static IsoObject lastRenderedRendered = null;
  static const ColorInfo stCol = new ColorInfo();
  static float rmod;
  static float gmod;
  static float bmod;
  static bool LowLightingQualityHack = false;
  static int DefaultCondition = 0;
  static const ColorInfo stCol2 = new ColorInfo();
  static const ColorInfo colFxMask = new ColorInfo(1.0F, 1.0F, 1.0F, 1.0F);
  uint8_t highlightFlags;
  int keyId = -1;
  BaseSoundEmitter emitter;
  float sheetRopeHealth = 100.0F;
  bool sheetRope = false;
  bool bNeverDoneAlpha = true;
  bool bAlphaForced = false;
public
  ArrayList<IsoSpriteInstance> AttachedAnimSprite;
public
  ArrayList<IsoWallBloodSplat> wallBloodSplats;
  ItemContainer container = null;
  IsoDirections dir = IsoDirections.N;
  short Damage = 100;
  float partialThumpDmg = 0.0F;
  bool NoPicking = false;
  float offsetX = (float)(32 * Core.TileScale);
  float offsetY = (float)(96 * Core.TileScale);
  bool OutlineOnMouseover = false;
  IsoObject rerouteMask = null;
  IsoSprite sprite = null;
  IsoSprite overlaySprite = null;
  ColorInfo overlaySpriteColor = null;
  IsoGridSquare square;
private
  final float[] alpha = new float[4];
private
  final float[] targetAlpha = new float[4];
  IsoObject rerouteCollide = null;
  KahluaTable table = null;
  std::string name = null;
  float tintr = 1.0F;
  float tintg = 1.0F;
  float tintb = 1.0F;
  std::string spriteName = null;
  float sx;
  float sy;
  bool doNotSync = false;
  ObjectRenderEffects windRenderEffects;
  ObjectRenderEffects objectRenderEffects;
  IsoObject externalWaterSource = null;
  bool usesExternalWaterSource = false;
  ArrayList<IsoObject> Children;
  std::string tile;
  bool specialTooltip = false;
  ColorInfo highlightColor = new ColorInfo(0.9F, 1.0F, 0.0F, 1.0F);
private
  ArrayList<ItemContainer> secondaryContainers;
  ColorInfo customColor = null;
  float renderYOffset = 0.0F;
  uint8_t isOutlineHighlight = 0;
  uint8_t isOutlineHlAttached = 0;
  uint8_t isOutlineHlBlink = 0;
protected
  final int[] outlineHighlightCol = new int[4];
  float outlineThickness = 0.15F;
  bool bMovedThumpable = false;
private
  static final Map<Byte, IsoObject.IsoObjectFactory> byteToObjectMap =
      std::make_unique<HashMap<>>();
private
  static final Map<Integer, IsoObject.IsoObjectFactory> hashCodeToObjectMap =
      std::make_unique<HashMap<>>();
private
  static final Map<String, IsoObject.IsoObjectFactory> nameToObjectMap =
      std::make_unique<HashMap<>>();
private
  static IsoObject.IsoObjectFactory factoryIsoObject;
private
  static IsoObject.IsoObjectFactory factoryVehicle;

public
  IsoObject(IsoCell cell) { this(); }

public
  IsoObject() {
    for (int int0 = 0; int0 < 4; int0++) {
      this.setAlphaAndTarget(int0, 1.0F);
      this.outlineHighlightCol[int0] = -1;
    }
  }

public
  IsoObject(IsoCell cell, IsoGridSquare _square, IsoSprite spr) {
    this();
    this.sprite = spr;
    this.square = _square;
  }

public
  IsoObject(IsoCell cell, IsoGridSquare _square, const std::string &gid) {
    this();
    this.sprite = IsoSpriteManager.instance.getSprite(gid);
    this.square = _square;
    this.tile = gid;
  }

public
  IsoObject(IsoGridSquare _square, const std::string &_tile,
            const std::string &_name) {
    this();
    this.sprite = IsoSpriteManager.instance.getSprite(_tile);
    this.square = _square;
    this.tile = _tile;
    this.spriteName = _tile;
    this.name = _name;
  }

public
  IsoObject(IsoGridSquare _square, const std::string &_tile,
            const std::string &_name, bool bShareTilesWithMap) {
    this();
    if (bShareTilesWithMap) {
      this.sprite = IsoSprite.CreateSprite(IsoSpriteManager.instance);
      this.sprite.LoadFramesNoDirPageSimple(_tile);
    } else {
      this.sprite = IsoSpriteManager.instance.NamedMap.get(_tile);
    }

    this.tile = _tile;
    this.square = _square;
    this.name = _name;
  }

  bool isFloor() {
    return this.getProperties() != nullptr
               ? this.getProperties().Is(IsoFlagType.solidfloor)
               : false;
  }

public
  IsoObject(IsoGridSquare _square, const std::string &_tile,
            bool bShareTilesWithMap) {
    this();
    if (bShareTilesWithMap) {
      this.sprite = IsoSprite.CreateSprite(IsoSpriteManager.instance);
      this.sprite.LoadFramesNoDirPageSimple(_tile);
    } else {
      this.sprite = IsoSpriteManager.instance.NamedMap.get(_tile);
    }

    this.tile = _tile;
    this.square = _square;
  }

public
  IsoObject(IsoGridSquare _square, const std::string &_tile) {
    this();
    this.sprite = IsoSprite.CreateSprite(IsoSpriteManager.instance);
    this.sprite.LoadFramesNoDirPageSimple(_tile);
    this.square = _square;
  }

  static IsoObject getNew(IsoGridSquare sq, const std::string &_spriteName,
                          const std::string &_name, bool bShareTilesWithMap) {
    IsoObject object = null;
    synchronized(CellLoader.isoObjectCache) {
      if (CellLoader.isoObjectCache.isEmpty()) {
        object = new IsoObject(sq, _spriteName, _name, bShareTilesWithMap);
      } else {
        object = CellLoader.isoObjectCache.pop();
        object.reset();
        object.tile = _spriteName;
      }
    }

    if (bShareTilesWithMap) {
      object.sprite = IsoSprite.CreateSprite(IsoSpriteManager.instance);
      object.sprite.LoadFramesNoDirPageSimple(object.tile);
    } else {
      object.sprite = IsoSpriteManager.instance.NamedMap.get(object.tile);
    }

    object.square = sq;
    object.name = _name;
    return object;
  }

  /**
   * @return the lastRendered
   */
  static IsoObject getLastRendered() { return lastRendered; }

  /**
   *
   * @param aLastRendered the lastRendered to set
   */
  static void setLastRendered(IsoObject aLastRendered) {
    lastRendered = aLastRendered;
  }

  /**
   * @return the lastRenderedRendered
   */
  static IsoObject getLastRenderedRendered() { return lastRenderedRendered; }

  /**
   *
   * @param aLastRenderedRendered the lastRenderedRendered to set
   */
  static void setLastRenderedRendered(IsoObject aLastRenderedRendered) {
    lastRenderedRendered = aLastRenderedRendered;
  }

  static void setDefaultCondition(int i) { DefaultCondition = i; }

  static IsoObject getNew() {
    synchronized(CellLoader.isoObjectCache) {
      return CellLoader.isoObjectCache.isEmpty()
                 ? std::make_unique<IsoObject>()
                 : CellLoader.isoObjectCache.pop();
    }
  }

private
  static IsoObject.IsoObjectFactory
  addIsoObjectFactory(IsoObject.IsoObjectFactory objectFactory) {
    if (byteToObjectMap.containsKey(objectFactory.classID)) {
      throw new RuntimeException("Class id already exists, " +
                                 objectFactory.objectName);
    } else {
      byteToObjectMap.put(objectFactory.classID, objectFactory);
      if (hashCodeToObjectMap.containsKey(objectFactory.hashCode)) {
        throw new RuntimeException("Hashcode already exists, " +
                                   objectFactory.objectName);
      } else {
        hashCodeToObjectMap.put(objectFactory.hashCode, objectFactory);
        if (nameToObjectMap.containsKey(objectFactory.objectName)) {
          throw new RuntimeException("ObjectName already exists, " +
                                     objectFactory.objectName);
        } else {
          nameToObjectMap.put(objectFactory.objectName, objectFactory);
          return objectFactory;
        }
      }
    }
  }

public
  static IsoObject.IsoObjectFactory getFactoryVehicle() {
    return factoryVehicle;
  }

  static void initFactory() {
        factoryIsoObject = addIsoObjectFactory(new IsoObject.IsoObjectFactory((byte)0, "IsoObject") {
    IsoObject InstantiateObject(IsoCell var1) {
    IsoObject object = IsoObject.getNew();
                object.sx = 0.0F;
    return object;
  }
        });
        addIsoObjectFactory(new IsoObject.IsoObjectFactory((byte)1, "Player") {
    IsoObject InstantiateObject(IsoCell cell) {
                return new IsoPlayer(cell);
        } // namespace iso
        } // namespace zombie
);
        addIsoObjectFactory(new IsoObject.IsoObjectFactory((byte)2, "Survivor") {
    IsoObject InstantiateObject(IsoCell cell) {
                return new IsoSurvivor(cell);
        }
        });
        addIsoObjectFactory(new IsoObject.IsoObjectFactory((byte)3, "Zombie") {
    IsoObject InstantiateObject(IsoCell cell) {
                return new IsoZombie(cell);
        }
        });
        addIsoObjectFactory(new IsoObject.IsoObjectFactory((byte)4, "Pushable") {
    IsoObject InstantiateObject(IsoCell cell) {
                return new IsoPushableObject(cell);
        }
        });
        addIsoObjectFactory(new IsoObject.IsoObjectFactory((byte)5, "WheelieBin") {
    IsoObject InstantiateObject(IsoCell cell) {
                return new IsoWheelieBin(cell);
        }
        });
        addIsoObjectFactory(new IsoObject.IsoObjectFactory((byte)6, "WorldInventoryItem") {
    IsoObject InstantiateObject(IsoCell cell) {
                return new IsoWorldInventoryObject(cell);
        }
        });
        addIsoObjectFactory(new IsoObject.IsoObjectFactory((byte)7, "Jukebox") {
    IsoObject InstantiateObject(IsoCell cell) {
                return new IsoJukebox(cell);
        }
        });
        addIsoObjectFactory(new IsoObject.IsoObjectFactory((byte)8, "Curtain") {
    IsoObject InstantiateObject(IsoCell cell) {
                return new IsoCurtain(cell);
        }
        });
        addIsoObjectFactory(new IsoObject.IsoObjectFactory((byte)9, "Radio") {
    IsoObject InstantiateObject(IsoCell cell) {
                return new IsoRadio(cell);
        }
        });
        addIsoObjectFactory(new IsoObject.IsoObjectFactory((byte)10, "Television") {
    IsoObject InstantiateObject(IsoCell cell) {
                return new IsoTelevision(cell);
        }
        });
        addIsoObjectFactory(new IsoObject.IsoObjectFactory((byte)11, "DeadBody") {
    IsoObject InstantiateObject(IsoCell cell) {
                return new IsoDeadBody(cell);
        }
        });
        addIsoObjectFactory(new IsoObject.IsoObjectFactory((byte)12, "Barbecue") {
    IsoObject InstantiateObject(IsoCell cell) {
                return new IsoBarbecue(cell);
        }
        });
        addIsoObjectFactory(new IsoObject.IsoObjectFactory((byte)13, "ClothingDryer") {
    IsoObject InstantiateObject(IsoCell cell) {
                return new IsoClothingDryer(cell);
        }
        });
        addIsoObjectFactory(new IsoObject.IsoObjectFactory((byte)14, "ClothingWasher") {
    IsoObject InstantiateObject(IsoCell cell) {
                return new IsoClothingWasher(cell);
        }
        });
        addIsoObjectFactory(new IsoObject.IsoObjectFactory((byte)15, "Fireplace") {
    IsoObject InstantiateObject(IsoCell cell) {
                return new IsoFireplace(cell);
        }
        });
        addIsoObjectFactory(new IsoObject.IsoObjectFactory((byte)16, "Stove") {
    IsoObject InstantiateObject(IsoCell cell) {
                return new IsoStove(cell);
        }
        });
        addIsoObjectFactory(new IsoObject.IsoObjectFactory((byte)17, "Door") {
    IsoObject InstantiateObject(IsoCell cell) {
                return new IsoDoor(cell);
        }
        });
        addIsoObjectFactory(new IsoObject.IsoObjectFactory((byte)18, "Thumpable") {
    IsoObject InstantiateObject(IsoCell cell) {
                return new IsoThumpable(cell);
        }
        });
        addIsoObjectFactory(new IsoObject.IsoObjectFactory((byte)19, "IsoTrap") {
    IsoObject InstantiateObject(IsoCell cell) {
                return new IsoTrap(cell);
        }
        });
        addIsoObjectFactory(new IsoObject.IsoObjectFactory((byte)20, "IsoBrokenGlass") {
    IsoObject InstantiateObject(IsoCell cell) {
                return new IsoBrokenGlass(cell);
        }
        });
        addIsoObjectFactory(new IsoObject.IsoObjectFactory((byte)21, "IsoCarBatteryCharger") {
    IsoObject InstantiateObject(IsoCell cell) {
                return new IsoCarBatteryCharger(cell);
        }
        });
        addIsoObjectFactory(new IsoObject.IsoObjectFactory((byte)22, "IsoGenerator") {
    IsoObject InstantiateObject(IsoCell cell) {
                return new IsoGenerator(cell);
        }
        });
        addIsoObjectFactory(new IsoObject.IsoObjectFactory((byte)23, "IsoCompost") {
    IsoObject InstantiateObject(IsoCell cell) {
                return new IsoCompost(cell);
        }
        });
        addIsoObjectFactory(new IsoObject.IsoObjectFactory((byte)24, "Mannequin") {
    IsoObject InstantiateObject(IsoCell cell) {
                return new IsoMannequin(cell);
        }
        });
        addIsoObjectFactory(new IsoObject.IsoObjectFactory((byte)25, "StoneFurnace") {
    IsoObject InstantiateObject(IsoCell cell) {
                return new BSFurnace(cell);
        }
        });
        addIsoObjectFactory(new IsoObject.IsoObjectFactory((byte)26, "Window") {
    IsoObject InstantiateObject(IsoCell cell) {
                return new IsoWindow(cell);
        }
        });
        addIsoObjectFactory(new IsoObject.IsoObjectFactory((byte)27, "Barricade") {
    IsoObject InstantiateObject(IsoCell cell) {
                return new IsoBarricade(cell);
        }
        });
        addIsoObjectFactory(new IsoObject.IsoObjectFactory((byte)28, "Tree") {
    IsoObject InstantiateObject(IsoCell var1) {
                return IsoTree.getNew();
        }
        });
        addIsoObjectFactory(new IsoObject.IsoObjectFactory((byte)29, "LightSwitch") {
    IsoObject InstantiateObject(IsoCell cell) {
                return new IsoLightSwitch(cell);
        }
        });
        addIsoObjectFactory(new IsoObject.IsoObjectFactory((byte)30, "ZombieGiblets") {
    IsoObject InstantiateObject(IsoCell cell) {
                return new IsoZombieGiblets(cell);
        }
        });
        addIsoObjectFactory(new IsoObject.IsoObjectFactory((byte)31, "MolotovCocktail") {
    IsoObject InstantiateObject(IsoCell cell) {
                return new IsoMolotovCocktail(cell);
        }
        });
        addIsoObjectFactory(new IsoObject.IsoObjectFactory((byte)32, "Fire") {
    IsoObject InstantiateObject(IsoCell cell) {
                return new IsoFire(cell);
        }
        });
        factoryVehicle = addIsoObjectFactory(new IsoObject.IsoObjectFactory((byte)33, "Vehicle") {
    IsoObject InstantiateObject(IsoCell cell) {
                return new BaseVehicle(cell);
        }
        });
        addIsoObjectFactory(new IsoObject.IsoObjectFactory((byte)34, "CombinationWasherDryer") {
    IsoObject InstantiateObject(IsoCell cell) {
                return new IsoCombinationWasherDryer(cell);
        }
        });
        addIsoObjectFactory(new IsoObject.IsoObjectFactory((byte)35, "StackedWasherDryer") {
    IsoObject InstantiateObject(IsoCell cell) {
                return new IsoStackedWasherDryer(cell);
        }
        });
        }

        static uint8_t factoryGetClassID(const std::string &_name) {
          IsoObject.IsoObjectFactory objectFactory =
              hashCodeToObjectMap.get(_name.hashCode());
          return objectFactory != nullptr ? objectFactory.classID
                                          : factoryIsoObject.classID;
        }

        static IsoObject factoryFromFileInput(IsoCell cell, uint8_t classID) {
          IsoObject.IsoObjectFactory objectFactory =
              byteToObjectMap.get(classID);
          if (objectFactory == nullptr || objectFactory.objectName == "Vehicle") && GameClient.bClient) {
              if (objectFactory == nullptr && Core.bDebug) {
                throw new RuntimeException(
                    "Cannot get IsoObject from classID: " + classID);
              } else {
                return new IsoObject(cell);
              }
            }
          else {
            return objectFactory.InstantiateObject(cell);
          }
        }

        static IsoObject factoryFromFileInput_OLD(IsoCell cell, int classID) {
          if (classID == "IsoObject".hashCode()) {
            IsoObject object = getNew();
            object.sx = 0.0F;
            return object;
          } else if (classID == "Player".hashCode()) {
            return new IsoPlayer(cell);
          } else if (classID == "Survivor".hashCode()) {
            return new IsoSurvivor(cell);
          } else if (classID == "Zombie".hashCode()) {
            return new IsoZombie(cell);
          } else if (classID == "Pushable".hashCode()) {
            return new IsoPushableObject(cell);
          } else if (classID == "WheelieBin".hashCode()) {
            return new IsoWheelieBin(cell);
          } else if (classID == "WorldInventoryItem".hashCode()) {
            return new IsoWorldInventoryObject(cell);
          } else if (classID == "Jukebox".hashCode()) {
            return new IsoJukebox(cell);
          } else if (classID == "Curtain".hashCode()) {
            return new IsoCurtain(cell);
          } else if (classID == "Radio".hashCode()) {
            return new IsoRadio(cell);
          } else if (classID == "Television".hashCode()) {
            return new IsoTelevision(cell);
          } else if (classID == "DeadBody".hashCode()) {
            return new IsoDeadBody(cell);
          } else if (classID == "Barbecue".hashCode()) {
            return new IsoBarbecue(cell);
          } else if (classID == "ClothingDryer".hashCode()) {
            return new IsoClothingDryer(cell);
          } else if (classID == "ClothingWasher".hashCode()) {
            return new IsoClothingWasher(cell);
          } else if (classID == "Fireplace".hashCode()) {
            return new IsoFireplace(cell);
          } else if (classID == "Stove".hashCode()) {
            return new IsoStove(cell);
          } else if (classID == "Door".hashCode()) {
            return new IsoDoor(cell);
          } else if (classID == "Thumpable".hashCode()) {
            return new IsoThumpable(cell);
          } else if (classID == "IsoTrap".hashCode()) {
            return new IsoTrap(cell);
          } else if (classID == "IsoBrokenGlass".hashCode()) {
            return new IsoBrokenGlass(cell);
          } else if (classID == "IsoCarBatteryCharger".hashCode()) {
            return new IsoCarBatteryCharger(cell);
          } else if (classID == "IsoGenerator".hashCode()) {
            return new IsoGenerator(cell);
          } else if (classID == "IsoCompost".hashCode()) {
            return new IsoCompost(cell);
          } else if (classID == "Mannequin".hashCode()) {
            return new IsoMannequin(cell);
          } else if (classID == "StoneFurnace".hashCode()) {
            return new BSFurnace(cell);
          } else if (classID == "Window".hashCode()) {
            return new IsoWindow(cell);
          } else if (classID == "Barricade".hashCode()) {
            return new IsoBarricade(cell);
          } else if (classID == "Tree".hashCode()) {
            return IsoTree.getNew();
          } else if (classID == "LightSwitch".hashCode()) {
            return new IsoLightSwitch(cell);
          } else if (classID == "ZombieGiblets".hashCode()) {
            return new IsoZombieGiblets(cell);
          } else if (classID == "MolotovCocktail".hashCode()) {
            return new IsoMolotovCocktail(cell);
          } else if (classID == "Fire".hashCode()) {
            return new IsoFire(cell);
          } else {
            return (IsoObject)(classID == "Vehicle".hashCode() &&
                                       !GameClient.bClient
                                   ? new BaseVehicle(cell)
                                   : new IsoObject(cell));
          }
        }

        static Class factoryClassFromFileInput(IsoCell cell, int classID) {
          if (classID == "IsoObject".hashCode()) {
            return IsoObject.class;
          } else if (classID == "Player".hashCode()) {
            return IsoPlayer.class;
          } else if (classID == "Survivor".hashCode()) {
            return IsoSurvivor.class;
          } else if (classID == "Zombie".hashCode()) {
            return IsoZombie.class;
          } else if (classID == "Pushable".hashCode()) {
            return IsoPushableObject.class;
          } else if (classID == "WheelieBin".hashCode()) {
            return IsoWheelieBin.class;
          } else if (classID == "WorldInventoryItem".hashCode()) {
            return IsoWorldInventoryObject.class;
          } else if (classID == "Jukebox".hashCode()) {
            return IsoJukebox.class;
          } else if (classID == "Curtain".hashCode()) {
            return IsoCurtain.class;
          } else if (classID == "Radio".hashCode()) {
            return IsoRadio.class;
          } else if (classID == "Television".hashCode()) {
            return IsoTelevision.class;
          } else if (classID == "DeadBody".hashCode()) {
            return IsoDeadBody.class;
          } else if (classID == "Barbecue".hashCode()) {
            return IsoBarbecue.class;
          } else if (classID == "ClothingDryer".hashCode()) {
            return IsoClothingDryer.class;
          } else if (classID == "ClothingWasher".hashCode()) {
            return IsoClothingWasher.class;
          } else if (classID == "Fireplace".hashCode()) {
            return IsoFireplace.class;
          } else if (classID == "Stove".hashCode()) {
            return IsoStove.class;
          } else if (classID == "Mannequin".hashCode()) {
            return IsoMannequin.class;
          } else if (classID == "Door".hashCode()) {
            return IsoDoor.class;
          } else if (classID == "Thumpable".hashCode()) {
            return IsoThumpable.class;
          } else if (classID == "Window".hashCode()) {
            return IsoWindow.class;
          } else if (classID == "Barricade".hashCode()) {
            return IsoBarricade.class;
          } else if (classID == "Tree".hashCode()) {
            return IsoTree.class;
          } else if (classID == "LightSwitch".hashCode()) {
            return IsoLightSwitch.class;
          } else if (classID == "ZombieGiblets".hashCode()) {
            return IsoZombieGiblets.class;
          } else if (classID == "MolotovCocktail".hashCode()) {
            return IsoMolotovCocktail.class;
          } else {
            return classID = = "Vehicle".hashCode() ? BaseVehicle.class
                                                    : IsoObject.class;
          }
        }

        static IsoObject factoryFromFileInput(IsoCell cell,
                                              DataInputStream dataInputStream) {
          bool boolean0 = dataInputStream.readBoolean();
          if (!boolean0) {
            return null;
          } else {
            uint8_t byte0 = dataInputStream.readByte();
            return factoryFromFileInput();
          }
        }

        static IsoObject factoryFromFileInput(IsoCell cell, ByteBuffer b) {
          bool boolean0 = b.get() != 0;
          if (!boolean0) {
            return null;
          } else {
            uint8_t byte0 = b.get();
            return factoryFromFileInput();
          }
        }

        void syncIsoObject(bool bRemote, uint8_t val, UdpConnection source,
                           ByteBuffer bb) {}

        void syncIsoObjectSend(ByteBufferWriter bb) {
          bb.putInt(this.square.getX());
          bb.putInt(this.square.getY());
          bb.putInt(this.square.getZ());
          bb.putByte((byte)this.square.getObjects().indexOf(this));
          bb.putByte((byte)0);
          bb.putByte((byte)0);
        }

        std::string getTextureName() {
          return this.sprite == nullptr ? nullptr : this.sprite.name;
        }

        bool Serialize() { return true; }

        KahluaTable getModData() {
          if (this.table == nullptr) {
            this.table = LuaManager.platform.newTable();
          }

          return this.table;
        }

        bool hasModData() {
          return this.table != nullptr && !this.table.isEmpty();
        }

        IsoGridSquare getSquare() { return this.square; }

        /**
         *
         * @param _square the square to set
         */
        void setSquare(IsoGridSquare _square) { this.square = _square; }

        IsoChunk getChunk() {
          IsoGridSquare squarex = this.getSquare();
          return squarex = = null ? null : squarex.getChunk();
        }

        void update() {}

        void renderlast() {}

        void DirtySlice() {}

        std::string getObjectName() {
          if (this.name != nullptr) {
            return this.name;
          } else {
            return this.sprite != nullptr &&
                           this.sprite.getParentObjectName() != nullptr
                       ? this.sprite.getParentObjectName()
                       : "IsoObject";
          }
        }

        void load(ByteBuffer input, int WorldVersion) {
          this.load(input, WorldVersion, false);
        }

        void load(ByteBuffer input, int WorldVersion, bool IS_DEBUG_SAVE) {
          int int0 = input.getInt();
          int0 = IsoChunk.Fix2x(this.square, int0);
          this.sprite = IsoSprite.getSprite(IsoSpriteManager.instance, int0);
          if (int0 == -1) {
            this.sprite = IsoSpriteManager.instance.getSprite("");

            assert this.sprite != nullptr;

            assert this.sprite.ID == -1;
          }

          BitHeaderRead bitHeaderRead0 =
              BitHeader.allocRead(BitHeader.HeaderSize.Byte, input);
          if (!bitHeaderRead0 == 0)) {
              if (bitHeaderRead0.hasFlags(1)) {
                int int1;
                if (bitHeaderRead0.hasFlags(2)) {
                  int1 = 1;
                } else {
                  int1 = input.get() & 255;
                }

                if (IS_DEBUG_SAVE) {
                  std::string string0 = GameWindow.ReadStringUTF(input);
                  DebugLog.log(string0 + ", read = " + int1);
                }

                for (int int2 = 0; int2 < int1; int2++) {
                  if (this.AttachedAnimSprite == nullptr) {
                    this.AttachedAnimSprite = std::make_unique<ArrayList<>>();
                  }

                  int int3 = input.getInt();
                  IsoSprite spritex =
                      IsoSprite.getSprite(IsoSpriteManager.instance, int3);
                  IsoSpriteInstance spriteInstance = null;
                  if (spritex != nullptr) {
                    spriteInstance = spritex.newInstance();
                  } else if (Core.bDebug) {
                    DebugLog.General.warn("discarding attached sprite because "
                                          "it has no tile properties");
                  }

                  uint8_t byte0 = input.get();
                  bool boolean0 = false;
                  bool boolean1 = false;
                  if ((byte0 & 2) != 0) {
                    boolean0 = true;
                  }

                  if ((byte0 & 4) != 0 && spriteInstance != nullptr) {
                    spriteInstance.Flip = true;
                  }

                  if ((byte0 & 8) != 0 && spriteInstance != nullptr) {
                    spriteInstance.bCopyTargetAlpha = true;
                  }

                  if ((byte0 & 16) != 0) {
                    boolean1 = true;
                    if (spriteInstance != nullptr) {
                      spriteInstance.bMultiplyObjectAlpha = true;
                    }
                  }

                  if (boolean0) {
                    float float0 = input.getFloat();
                    float float1 = input.getFloat();
                    float float2 = input.getFloat();
                    float float3 = Bits.unpackByteToFloatUnit(input.get());
                    float float4 = Bits.unpackByteToFloatUnit(input.get());
                    float float5 = Bits.unpackByteToFloatUnit(input.get());
                    if (spriteInstance != nullptr) {
                      spriteInstance.offX = float0;
                      spriteInstance.offY = float1;
                      spriteInstance.offZ = float2;
                      spriteInstance.tintr = float3;
                      spriteInstance.tintg = float4;
                      spriteInstance.tintb = float5;
                    }
                  } else if (spriteInstance != nullptr) {
                    spriteInstance.offX = 0.0F;
                    spriteInstance.offY = 0.0F;
                    spriteInstance.offZ = 0.0F;
                    spriteInstance.tintr = 1.0F;
                    spriteInstance.tintg = 1.0F;
                    spriteInstance.tintb = 1.0F;
                    spriteInstance.alpha = 1.0F;
                    spriteInstance.targetAlpha = 1.0F;
                  }

                  if (boolean1) {
                    float float6 = input.getFloat();
                    if (spriteInstance != nullptr) {
                      spriteInstance.alpha = float6;
                    }
                  }

                  if (spritex != nullptr) {
                    if (spritex.name != nullptr &&
                        spritex.name.startsWith("overlay_blood_")) {
                      float float7 =
                          (float)GameTime.getInstance().getWorldAgeHours();
                      IsoWallBloodSplat wallBloodSplat0 =
                          new IsoWallBloodSplat(float7, spritex);
                      if (this.wallBloodSplats == nullptr) {
                        this.wallBloodSplats = std::make_unique<ArrayList<>>();
                      }

                      this.wallBloodSplats.add(wallBloodSplat0);
                    } else {
                      this.AttachedAnimSprite.add(spriteInstance);
                    }
                  }
                }
              }

              if (bitHeaderRead0.hasFlags(4)) {
                if (IS_DEBUG_SAVE) {
                  std::string string1 = GameWindow.ReadStringUTF(input);
                  DebugLog.log(string1);
                }

                uint8_t byte1 = input.get();
                if ((byte1 & 2) != 0) {
                  this.name = "Grass";
                } else if ((byte1 & 4) != 0) {
                  this.name = WorldDictionary.getObjectNameFromID(input.get());
                } else if ((byte1 & 8) != 0) {
                  this.name = GameWindow.ReadString(input);
                }

                if ((byte1 & 16) != 0) {
                  this.spriteName =
                      WorldDictionary.getSpriteNameFromID(input.getInt());
                } else if ((byte1 & 32) != 0) {
                  this.spriteName = GameWindow.ReadString(input);
                }
              }

              if (bitHeaderRead0.hasFlags(8)) {
                float float8 = Bits.unpackByteToFloatUnit(input.get());
                float float9 = Bits.unpackByteToFloatUnit(input.get());
                float float10 = Bits.unpackByteToFloatUnit(input.get());
                this.customColor = new ColorInfo(float8, float9, float10, 1.0F);
              }

              this.doNotSync = bitHeaderRead0.hasFlags(16);
              this.setOutlineOnMouseover(bitHeaderRead0.hasFlags(32));
              if (bitHeaderRead0.hasFlags(64)) {
                BitHeaderRead bitHeaderRead1 =
                    BitHeader.allocRead(BitHeader.HeaderSize.Short, input);
                if (bitHeaderRead1.hasFlags(1)) {
                  uint8_t byte2 = input.get();
                  if (byte2 > 0) {
                    if (this.wallBloodSplats == nullptr) {
                      this.wallBloodSplats = std::make_unique<ArrayList<>>();
                    }

                    int int4 = 0;
                    if (GameClient.bClient || GameServer.bServer) {
                      int4 = ServerOptions.getInstance()
                                 .BloodSplatLifespanDays.getValue();
                    }

                    float float11 =
                        (float)GameTime.getInstance().getWorldAgeHours();

                    for (int int5 = 0; int5 < byte2; int5++) {
                      IsoWallBloodSplat wallBloodSplat1 =
                          new IsoWallBloodSplat();
                      wallBloodSplat1.load(input, WorldVersion);
                      if (wallBloodSplat1.worldAge > float11) {
                        wallBloodSplat1.worldAge = float11;
                      }

                      if (int4 <= 0 ||
                          !(float11 - wallBloodSplat1.worldAge >= int4 * 24)) {
                        this.wallBloodSplats.add(wallBloodSplat1);
                      }
                    }
                  }
                }

                if (bitHeaderRead1.hasFlags(2)) {
                  if (IS_DEBUG_SAVE) {
                    std::string string2 = GameWindow.ReadStringUTF(input);
                    DebugLog.log(string2);
                  }

                  uint8_t byte3 = input.get();

                  for (int int6 = 0; int6 < byte3; int6++) {
                    try {
                      ItemContainer containerx = new ItemContainer();
                      containerx.ID = 0;
                      containerx.parent = this;
                      containerx.parent.square = this.square;
                      containerx.SourceGrid = this.square;
                      containerx.load(input, WorldVersion);
                      if (int6 == 0) {
                        if (this instanceof IsoDeadBody) {
                          containerx.Capacity = 8;
                        }

                        this.container = containerx;
                      } else {
                        this.addSecondaryContainer(containerx);
                      }
                    } catch (Exception exception) {
                      if (this.container != nullptr) {
                        DebugLog.log("Failed to stream in container ID: " +
                                     this.container.ID);
                      }

                      throw new RuntimeException(exception);
                    }
                  }
                }

                if (bitHeaderRead1.hasFlags(4)) {
                  if (this.table == nullptr) {
                    this.table = LuaManager.platform.newTable();
                  }

                  this.table.load(input, WorldVersion);
                }

                this.setSpecialTooltip(bitHeaderRead1.hasFlags(8));
                if (bitHeaderRead1.hasFlags(16)) {
                  this.keyId = input.getInt();
                }

                this.usesExternalWaterSource = bitHeaderRead1.hasFlags(32);
                if (bitHeaderRead1.hasFlags(64)) {
                  this.sheetRope = true;
                  this.sheetRopeHealth = input.getFloat();
                } else {
                  this.sheetRope = false;
                }

                if (bitHeaderRead1.hasFlags(128)) {
                  this.renderYOffset = input.getFloat();
                }

                if (bitHeaderRead1.hasFlags(256)) {
                  void *object = null;
                  if (bitHeaderRead1.hasFlags(512)) {
                    object = GameWindow.ReadString(input);
                  } else {
                    object =
                        WorldDictionary.getSpriteNameFromID(input.getInt());
                  }

                  if (object != nullptr && !object.isEmpty()) {
                    this.overlaySprite =
                        IsoSpriteManager.instance.getSprite((String)object);
                    this.overlaySprite.name = (String)object;
                  }
                }

                if (bitHeaderRead1.hasFlags(1024)) {
                  float float12 = Bits.unpackByteToFloatUnit(input.get());
                  float float13 = Bits.unpackByteToFloatUnit(input.get());
                  float float14 = Bits.unpackByteToFloatUnit(input.get());
                  float float15 = Bits.unpackByteToFloatUnit(input.get());
                  if (this.overlaySprite != nullptr) {
                    this.setOverlaySpriteColor(float12, float13, float14,
                                               float15);
                  }
                }

                this.setMovedThumpable(bitHeaderRead1.hasFlags(2048));
                bitHeaderRead1.release();
              }
            }

          bitHeaderRead0.release();
          if (this.sprite == nullptr) {
            this.sprite = IsoSprite.CreateSprite(IsoSpriteManager.instance);
            this.sprite.LoadFramesNoDirPageSimple(this.spriteName);
          }
        }

        void save(ByteBuffer output) { this.save(output, false); }

        void save(ByteBuffer output, bool IS_DEBUG_SAVE) {
          output.put((byte)(this.Serialize() ? 1 : 0));
          if (this.Serialize()) {
            output.put(factoryGetClassID(this.getObjectName()));
            output.putInt(this.sprite == nullptr ? -1 : this.sprite.ID);
            BitHeaderWrite bitHeaderWrite0 =
                BitHeader.allocWrite(BitHeader.HeaderSize.Byte, output);
            if (this.AttachedAnimSprite != nullptr) {
              bitHeaderWrite0.addFlags(1);
              if (this.AttachedAnimSprite.size() == 1) {
                bitHeaderWrite0.addFlags(2);
              }

              int int0 = this.AttachedAnimSprite.size() > 255
                             ? 255
                             : this.AttachedAnimSprite.size();
              if (int0 != 1) {
                output.put((byte)int0);
              }

              if (IS_DEBUG_SAVE) {
                GameWindow.WriteString(output, "Writing attached sprites (" +
                                                   int0 + ")");
              }

              for (int int1 = 0; int1 < int0; int1++) {
                IsoSpriteInstance spriteInstance =
                    this.AttachedAnimSprite.get(int1);
                output.putInt(spriteInstance.getID());
                uint8_t byte0 = 0;
                bool boolean0 = false;
                if (spriteInstance.offX != 0.0F ||
                    spriteInstance.offY != 0.0F ||
                    spriteInstance.offZ != 0.0F ||
                    spriteInstance.tintr != 1.0F ||
                    spriteInstance.tintg != 1.0F ||
                    spriteInstance.tintb != 1.0F) {
                  byte0 = (byte)(byte0 | 2);
                  boolean0 = true;
                }

                if (spriteInstance.Flip) {
                  byte0 = (byte)(byte0 | 4);
                }

                if (spriteInstance.bCopyTargetAlpha) {
                  byte0 = (byte)(byte0 | 8);
                }

                if (spriteInstance.bMultiplyObjectAlpha) {
                  byte0 = (byte)(byte0 | 16);
                }

                output.put(byte0);
                if (boolean0) {
                  output.putFloat(spriteInstance.offX);
                  output.putFloat(spriteInstance.offY);
                  output.putFloat(spriteInstance.offZ);
                  output.put(Bits.packFloatUnitToByte(spriteInstance.tintr));
                  output.put(Bits.packFloatUnitToByte(spriteInstance.tintg));
                  output.put(Bits.packFloatUnitToByte(spriteInstance.tintb));
                }

                if (spriteInstance.bMultiplyObjectAlpha) {
                  output.putFloat(spriteInstance.alpha);
                }
              }
            }

            if (this.name != nullptr || this.spriteName != nullptr) {
              bitHeaderWrite0.addFlags(4);
              if (IS_DEBUG_SAVE) {
                GameWindow.WriteString(output, "Writing name");
              }

              uint8_t byte1 = 0;
              uint8_t byte2 = -1;
              int int2 = -1;
              if (this.name != nullptr) {
                if (this.name == "Grass")) {
                        byte1 = (byte)(byte1 | 2);
                    }
                else {
                  byte2 = WorldDictionary.getIdForObjectName(this.name);
                  if (byte2 >= 0) {
                    byte1 = (byte)(byte1 | 4);
                  } else {
                    byte1 = (byte)(byte1 | 8);
                  }
                }
              }

              if (this.spriteName != nullptr) {
                int2 = WorldDictionary.getIdForSpriteName(this.spriteName);
                if (int2 >= 0) {
                  byte1 = (byte)(byte1 | 16);
                } else {
                  byte1 = (byte)(byte1 | 32);
                }
              }

              output.put(byte1);
              if (this.name != nullptr && !this.name == "Grass")) {
                  if (byte2 >= 0) {
                    output.put(byte2);
                  } else {
                    GameWindow.WriteString(output, this.name);
                  }
                }

              if (this.spriteName != nullptr) {
                if (int2 >= 0) {
                  output.putInt(int2);
                } else {
                  GameWindow.WriteString(output, this.spriteName);
                }
              }
            }

            if (this.customColor != nullptr) {
              bitHeaderWrite0.addFlags(8);
              output.put(Bits.packFloatUnitToByte(this.customColor.r));
              output.put(Bits.packFloatUnitToByte(this.customColor.g));
              output.put(Bits.packFloatUnitToByte(this.customColor.b));
            }

            if (this.doNotSync) {
              bitHeaderWrite0.addFlags(16);
            }

            if (this.isOutlineOnMouseover()) {
              bitHeaderWrite0.addFlags(32);
            }

            BitHeaderWrite bitHeaderWrite1 =
                BitHeader.allocWrite(BitHeader.HeaderSize.Short, output);
            if (this.wallBloodSplats != nullptr) {
              bitHeaderWrite1.addFlags(1);
              int int3 = Math.min(this.wallBloodSplats.size(), 32);
              int int4 = this.wallBloodSplats.size() - int3;
              output.put((byte)int3);

              for (int int5 = int4; int5 < this.wallBloodSplats.size();
                   int5++) {
                this.wallBloodSplats.get(int5).save(output);
              }
            }

            if (this.getContainerCount() > 0) {
              bitHeaderWrite1.addFlags(2);
              if (IS_DEBUG_SAVE) {
                GameWindow.WriteString(output, "Writing container");
              }

              output.put((byte)this.getContainerCount());

              for (int int6 = 0; int6 < this.getContainerCount(); int6++) {
                this.getContainerByIndex(int6).save(output);
              }
            }

            if (this.table != nullptr && !this.table.isEmpty()) {
              bitHeaderWrite1.addFlags(4);
              this.table.save(output);
            }

            if (this.haveSpecialTooltip()) {
              bitHeaderWrite1.addFlags(8);
            }

            if (this.getKeyId() != -1) {
              bitHeaderWrite1.addFlags(16);
              output.putInt(this.getKeyId());
            }

            if (this.usesExternalWaterSource) {
              bitHeaderWrite1.addFlags(32);
            }

            if (this.sheetRope) {
              bitHeaderWrite1.addFlags(64);
              output.putFloat(this.sheetRopeHealth);
            }

            if (this.renderYOffset != 0.0F) {
              bitHeaderWrite1.addFlags(128);
              output.putFloat(this.renderYOffset);
            }

            if (this.getOverlaySprite() != nullptr) {
              bitHeaderWrite1.addFlags(256);
              int int7 = WorldDictionary.getIdForSpriteName(
                  this.getOverlaySprite().name);
              if (int7 < 0) {
                bitHeaderWrite1.addFlags(512);
                GameWindow.WriteString(output, this.getOverlaySprite().name);
              } else {
                output.putInt(int7);
              }

              if (this.getOverlaySpriteColor() != nullptr) {
                bitHeaderWrite1.addFlags(1024);
                output.put(
                    Bits.packFloatUnitToByte(this.getOverlaySpriteColor().r));
                output.put(
                    Bits.packFloatUnitToByte(this.getOverlaySpriteColor().g));
                output.put(
                    Bits.packFloatUnitToByte(this.getOverlaySpriteColor().b));
                output.put(
                    Bits.packFloatUnitToByte(this.getOverlaySpriteColor().a));
              }
            }

            if (this.isMovedThumpable()) {
              bitHeaderWrite1.addFlags(2048);
            }

            if (!bitHeaderWrite1 == 0)) {
                bitHeaderWrite0.addFlags(64);
                bitHeaderWrite1.write();
              }
            else {
              output.position(bitHeaderWrite1.getStartPosition());
            }

            bitHeaderWrite0.write();
            bitHeaderWrite0.release();
            bitHeaderWrite1.release();
          }
        }

        void saveState(ByteBuffer bb) {}

        void loadState(ByteBuffer bb) {}

        void softReset() {
          if (this.container != nullptr) {
            this.container.Items.clear();
            this.container.bExplored = false;
            this.setOverlaySprite(nullptr, -1.0F, -1.0F, -1.0F, -1.0F, false);
          }

          if (this.AttachedAnimSprite != nullptr &&
              !this.AttachedAnimSprite.isEmpty()) {
            for (int int0 = 0; int0 < this.AttachedAnimSprite.size(); int0++) {
              IsoSprite spritex =
                  this.AttachedAnimSprite.get(int0).parentSprite;
              if (spritex.name != nullptr && spritex.name.contains("blood")) {
                this.AttachedAnimSprite.remove(int0);
                int0--;
              }
            }
          }
        }

        void AttackObject(IsoGameCharacter owner) {
          this.Damage = (short)(this.Damage - 10);
          HandWeapon weapon = (HandWeapon)owner.getPrimaryHandItem();
          SoundManager.instance.PlaySound(weapon.getDoorHitSound(), false,
                                          2.0F);
          WorldSoundManager.instance.addSound(
              owner, this.square.getX(), this.square.getY(), this.square.getZ(),
              20, 20, false, 0.0F, 15.0F);
          if (this.Damage <= 0) {
            this.square.getObjects().remove(this);
            this.square.RecalcAllWithNeighbours(true);
            if (this.getType() == IsoObjectType.stairsBN ||
                this.getType() == IsoObjectType.stairsMN ||
                this.getType() == IsoObjectType.stairsTN ||
                this.getType() == IsoObjectType.stairsBW ||
                this.getType() == IsoObjectType.stairsMW ||
                this.getType() == IsoObjectType.stairsTW) {
              this.square.RemoveAllWith(IsoFlagType.attachtostairs);
            }

            uint8_t byte0 = 1;

            for (int int0 = 0; int0 < byte0; int0++) {
              InventoryItem item = this.square.AddWorldInventoryItem(
                  "Base.Plank", Rand.Next(-1.0F, 1.0F), Rand.Next(-1.0F, 1.0F),
                  0.0F);
              item.setUses(1);
            }
          }
        }

        void onMouseRightClick(int lx, int ly) {}

        void onMouseRightReleased() {}

        void Hit(Vector2 collision, IsoObject obj, float damage) {
          if (obj instanceof BaseVehicle) {
            this.HitByVehicle((BaseVehicle)obj, damage);
            if (this.Damage <= 0 &&
                BrokenFences.getInstance().isBreakableObject(this)) {
              PropertyContainer propertyContainer = this.getProperties();
              IsoDirections directions;
              if (propertyContainer.Is(IsoFlagType.collideN) &&
                  propertyContainer.Is(IsoFlagType.collideW)) {
                directions = obj.getY() >= this.getY() ? IsoDirections.N
                                                       : IsoDirections.S;
              } else if (propertyContainer.Is(IsoFlagType.collideN)) {
                directions = obj.getY() >= this.getY() ? IsoDirections.N
                                                       : IsoDirections.S;
              } else {
                directions = obj.getX() >= this.getX() ? IsoDirections.W
                                                       : IsoDirections.E;
              }

              BrokenFences.getInstance().destroyFence(this, directions);
            }
          }
        }

        void Damage(float amount) {
          this.Damage = (short)(this.Damage - amount * 0.1);
        }

        void HitByVehicle(BaseVehicle vehicle, float amount) {
          short short0 = this.Damage;
          this.Damage = (short)(this.Damage - amount * 0.1);
          BaseSoundEmitter baseSoundEmitter = IsoWorld.instance.getFreeEmitter(
              this.square.x + 0.5F, this.square.y + 0.5F, this.square.z);
          long long0 = baseSoundEmitter.playSound("VehicleHitObject");
          baseSoundEmitter.setParameterValue(
              long0,
              FMODManager.instance.getParameterDescription("VehicleSpeed"),
              vehicle.getCurrentSpeedKmHour());
          WorldSoundManager.instance.addSound(
              nullptr, this.square.getX(), this.square.getY(),
              this.square.getZ(), 20, 20, true, 4.0F, 15.0F);
          if (this.getProperties().Is("HitByCar") &&
              this.getSprite().getProperties().Val("DamagedSprite") !=
                  nullptr &&
              !this.getSprite().getProperties().Val("DamagedSprite") == "")
            && this.Damage <= 90
            && short0 > 90) {
              this.setSprite(IsoSpriteManager.instance.getSprite(
                  this.getSprite().getProperties().Val("DamagedSprite")));
              if (this.getSprite().getProperties().Is("StopCar")) {
                this.getSprite().setType(IsoObjectType.isMoveAbleObject);
              } else {
                this.getSprite().setType(IsoObjectType.MAX);
              }

              if (this instanceof IsoThumpable) {
                ((IsoThumpable)this).setBlockAllTheSquare(false);
              }

              if (GameServer.bServer) {
                this.transmitUpdatedSpriteToClients();
              }

              this.getSquare().RecalcProperties();
              this.Damage = 50;
            }

          if (this.Damage <= 40 && this.getProperties().Is("HitByCar") &&
              !BrokenFences.getInstance().isBreakableObject(this)) {
            this.getSquare().transmitRemoveItemFromSquare(this);
          }
        }

        void Collision(Vector2 collision, IsoObject object) {
          if (object instanceof BaseVehicle) {
            if (this.getProperties().Is("CarSlowFactor")) {
              int int0 =
                  Integer.parseInt(this.getProperties().Val("CarSlowFactor"));
              BaseVehicle vehicle0 = (BaseVehicle)object;
              vehicle0.ApplyImpulse(this,
                                    Math.abs(vehicle0.getFudgedMass() *
                                             vehicle0.getCurrentSpeedKmHour() *
                                             int0 / 100.0F));
            }

            if (this.getProperties().Is("HitByCar")) {
              BaseVehicle vehicle1 = (BaseVehicle)object;
              std::string string =
                  this.getSprite().getProperties().Val("MinimumCarSpeedDmg");
              if (string == nullptr) {
                string = "150";
              }

              if (Math.abs(vehicle1.getCurrentSpeedKmHour()) >
                  Integer.parseInt(string)) {
                this.HitByVehicle(vehicle1,
                                  Math.abs(vehicle1.getFudgedMass() *
                                           vehicle1.getCurrentSpeedKmHour()) /
                                      300.0F);
                if (this.Damage <= 0 &&
                    BrokenFences.getInstance().isBreakableObject(this)) {
                  PropertyContainer propertyContainer = this.getProperties();
                  IsoDirections directions;
                  if (propertyContainer.Is(IsoFlagType.collideN) &&
                      propertyContainer.Is(IsoFlagType.collideW)) {
                    directions = vehicle1.getY() >= this.getY()
                                     ? IsoDirections.N
                                     : IsoDirections.S;
                  } else if (propertyContainer.Is(IsoFlagType.collideN)) {
                    directions = vehicle1.getY() >= this.getY()
                                     ? IsoDirections.N
                                     : IsoDirections.S;
                  } else {
                    directions = vehicle1.getX() >= this.getX()
                                     ? IsoDirections.W
                                     : IsoDirections.E;
                  }

                  BrokenFences.getInstance().destroyFence(this, directions);
                }
              } else if (!this.square.getProperties().Is(
                             IsoFlagType.collideN) &&
                         !this.square.getProperties().Is(
                             IsoFlagType.collideW)) {
                vehicle1.ApplyImpulse(
                    this, Math.abs(vehicle1.getFudgedMass() *
                                   vehicle1.getCurrentSpeedKmHour() * 10.0F /
                                   200.0F));
                if (vehicle1.getCurrentSpeedKmHour() > 3.0F) {
                  vehicle1.ApplyImpulse(
                      this, Math.abs(vehicle1.getFudgedMass() *
                                     vehicle1.getCurrentSpeedKmHour() * 10.0F /
                                     150.0F));
                }

                vehicle1.jniSpeed = 0.0F;
              }
            }
          }
        }

        void UnCollision(IsoObject object) {}

        float GetVehicleSlowFactor(BaseVehicle vehicle) {
          if (this.getProperties().Is("CarSlowFactor")) {
            int int0 =
                Integer.parseInt(this.getProperties().Val("CarSlowFactor"));
            return 33.0F - (10 - int0);
          } else {
            return 0.0F;
          }
        }

        /**
         * @return the rerouteCollide
         */
        IsoObject getRerouteCollide() { return this.rerouteCollide; }

        /**
         *
         * @param _rerouteCollide the rerouteCollide to set
         */
        void setRerouteCollide(IsoObject _rerouteCollide) {
          this.rerouteCollide = _rerouteCollide;
        }

        /**
         * @return the table
         */
        KahluaTable getTable() { return this.table; }

        /**
         *
         * @param _table the table to set
         */
        void setTable(KahluaTable _table) { this.table = _table; }

        /**
         *
         * @param _alpha the alpha to set
         */
        void setAlpha(float _alpha) {
          this.setAlpha(IsoPlayer.getPlayerIndex(), _alpha);
        }

        /**
         *
         * @param playerIndex
         * @param _alpha the alpha to set
         */
        void setAlpha(int playerIndex, float _alpha) {
          this.alpha[playerIndex] = PZMath.clamp(_alpha, 0.0F, 1.0F);
        }

        /**
         *
         * @param playerIndex The playerIndex to use
         */
        void setAlphaToTarget(int playerIndex) {
          this.setAlpha(playerIndex, this.getTargetAlpha(playerIndex));
        }

        /**
         *
         * @param _alpha the alpha to set
         */
        void setAlphaAndTarget(float _alpha) {
          int int0 = IsoPlayer.getPlayerIndex();
          this.setAlphaAndTarget(int0, _alpha);
        }

        /**
         *
         * @param playerIndex The playerIndex to use
         * @param _alpha
         */
        void setAlphaAndTarget(int playerIndex, float _alpha) {
          this.setAlpha(playerIndex, _alpha);
          this.setTargetAlpha(playerIndex, _alpha);
        }

        /**
         * @return the alpha
         */
        float getAlpha() { return this.getAlpha(IsoPlayer.getPlayerIndex()); }

        float getAlpha(int playerIndex) { return this.alpha[playerIndex]; }

        /**
         * @return the AttachedAnimSprite
         */
      public
        ArrayList<IsoSpriteInstance> getAttachedAnimSprite() {
          return this.AttachedAnimSprite;
        }

        /**
         *
         * @param _AttachedAnimSprite the AttachedAnimSprite to set
         */
        void setAttachedAnimSprite(
            ArrayList<IsoSpriteInstance> _AttachedAnimSprite) {
          this.AttachedAnimSprite = _AttachedAnimSprite;
        }

        /**
         * @return the cell
         */
        IsoCell getCell() { return IsoWorld.instance.CurrentCell; }

        /**
         * @return the AttachedAnimSprite
         */
      public
        ArrayList<IsoSpriteInstance> getChildSprites() {
          return this.AttachedAnimSprite;
        }

        /**
         *
         * @param _AttachedAnimSprite the AttachedAnimSprite to set
         */
        void setChildSprites(ArrayList<IsoSpriteInstance> _AttachedAnimSprite) {
          this.AttachedAnimSprite = _AttachedAnimSprite;
        }

        void clearAttachedAnimSprite() {
          if (this.AttachedAnimSprite != nullptr) {
            for (int int0 = 0; int0 < this.AttachedAnimSprite.size(); int0++) {
              IsoSpriteInstance.add(this.AttachedAnimSprite.get(int0));
            }

            this.AttachedAnimSprite.clear();
          }
        }

        /**
         * @return the container
         */
        ItemContainer getContainer() { return this.container; }

        /**
         *
         * @param _container the container to set
         */
        void setContainer(ItemContainer _container) {
          _container.parent = this;
          this.container = _container;
        }

        /**
         * @return the dir
         */
        IsoDirections getDir() { return this.dir; }

        /**
         *
         * @param _dir the dir to set
         */
        void setDir(IsoDirections _dir) { this.dir = _dir; }

        /**
         *
         * @param _dir the dir to set
         */
        void setDir(int _dir) { this.dir = IsoDirections.fromIndex(_dir); }

        /**
         * @return the Damage
         */
        short getDamage() { return this.Damage; }

        /**
         *
         * @param _Damage the Damage to set
         */
        void setDamage(short _Damage) { this.Damage = _Damage; }

        /**
         * @return the NoPicking
         */
        bool isNoPicking() { return this.NoPicking; }

        /**
         *
         * @param _NoPicking the NoPicking to set
         */
        void setNoPicking(bool _NoPicking) { this.NoPicking = _NoPicking; }

        /**
         * @return the OutlineOnMouseover
         */
        bool isOutlineOnMouseover() { return this.OutlineOnMouseover; }

        /**
         *
         * @param _OutlineOnMouseover the OutlineOnMouseover to set
         */
        void setOutlineOnMouseover(bool _OutlineOnMouseover) {
          this.OutlineOnMouseover = _OutlineOnMouseover;
        }

        /**
         * @return the rerouteMask
         */
        IsoObject getRerouteMask() { return this.rerouteMask; }

        /**
         *
         * @param _rerouteMask the rerouteMask to set
         */
        void setRerouteMask(IsoObject _rerouteMask) {
          this.rerouteMask = _rerouteMask;
        }

        /**
         * @return the sprite
         */
        IsoSprite getSprite() { return this.sprite; }

        /**
         *
         * @param _sprite the sprite to set
         */
        void setSprite(IsoSprite _sprite) {
          this.sprite = _sprite;
          this.windRenderEffects = nullptr;
          this.checkMoveWithWind();
        }

        void setSprite(const std::string &_name) {
          this.sprite = IsoSprite.CreateSprite(IsoSpriteManager.instance);
          this.sprite.LoadFramesNoDirPageSimple(_name);
          this.tile = _name;
          this.spriteName = _name;
          this.windRenderEffects = nullptr;
          this.checkMoveWithWind();
        }

        void setSpriteFromName(const std::string &_name) {
          this.sprite = IsoSpriteManager.instance.getSprite(_name);
          this.windRenderEffects = nullptr;
          this.checkMoveWithWind();
        }

        /**
         * @return the targetAlpha
         */
        float getTargetAlpha() {
          return this.getTargetAlpha(IsoPlayer.getPlayerIndex());
        }

        /**
         *
         * @param _targetAlpha the targetAlpha to set
         */
        void setTargetAlpha(float _targetAlpha) {
          this.setTargetAlpha(IsoPlayer.getPlayerIndex(), _targetAlpha);
        }

        /**
         *
         * @param playerIndex
         * @param _targetAlpha the targetAlpha to set
         */
        void setTargetAlpha(int playerIndex, float _targetAlpha) {
          this.targetAlpha[playerIndex] =
              PZMath.clamp(_targetAlpha, 0.0F, 1.0F);
        }

        float getTargetAlpha(int playerIndex) {
          return this.targetAlpha[playerIndex];
        }

        /**
         * Returns TRUE if both Alpha nad TargetAlpha are transparent, or
         * near-zero.
         */
        bool isAlphaAndTargetZero() {
          int int0 = IsoPlayer.getPlayerIndex();
          return this.isAlphaAndTargetZero(int0);
        }

        bool isAlphaAndTargetZero(int playerIndex) {
          return this.isAlphaZero(playerIndex) &&
                 this.isTargetAlphaZero(playerIndex);
        }

        /**
         * Returns TRUE if Alpha is transparent, or near-zero.
         */
        bool isAlphaZero() {
          int int0 = IsoPlayer.getPlayerIndex();
          return this.isAlphaZero(int0);
        }

        bool isAlphaZero(int playerIndex) {
          return this.alpha[playerIndex] <= 0.001F;
        }

        bool isTargetAlphaZero(int playerIndex) {
          return this.targetAlpha[playerIndex] <= 0.001F;
        }

        /**
         * @return the type
         */
        IsoObjectType getType() {
          return this.sprite == nullptr ? IsoObjectType.MAX
                                        : this.sprite.getType();
        }

        void setType(IsoObjectType type) {
          if (this.sprite != nullptr) {
            this.sprite.setType(type);
          }
        }

        void addChild(IsoObject child) {
          if (this.Children == nullptr) {
            this.Children = new ArrayList<>(4);
          }

          this.Children.add(child);
        }

        void debugPrintout() {
          System.out.println(this.getClass().toString());
          System.out.println(this.getObjectName());
        }

        void checkMoveWithWind() {
          this.checkMoveWithWind(this.sprite != nullptr && this.sprite.isBush);
        }

        void checkMoveWithWind(bool boolean0) {
          if (!GameServer.bServer) {
            if (this.sprite != nullptr && this.windRenderEffects == nullptr &&
                this.sprite.moveWithWind) {
              if (this.getSquare() != nullptr) {
                IsoGridSquare square0 = this.getCell().getGridSquare(
                    this.getSquare().x - 1, this.getSquare().y,
                    this.getSquare().z);
                if (square0 != nullptr) {
                  IsoGridSquare square1 = this.getCell().getGridSquare(
                      square0.x, square0.y + 1, square0.z);
                  if (square1 != nullptr && !square1.isExteriorCache &&
                      square1.getWall(true) != nullptr) {
                    this.windRenderEffects = nullptr;
                    return;
                  }
                }

                IsoGridSquare square2 = this.getCell().getGridSquare(
                    this.getSquare().x, this.getSquare().y - 1,
                    this.getSquare().z);
                if (square2 != nullptr) {
                  IsoGridSquare square3 = this.getCell().getGridSquare(
                      square2.x + 1, square2.y, square2.z);
                  if (square3 != nullptr && !square3.isExteriorCache &&
                      square3.getWall(false) != nullptr) {
                    this.windRenderEffects = nullptr;
                    return;
                  }
                }
              }

              this.windRenderEffects = ObjectRenderEffects.getNextWindEffect(
                  this.sprite.windType, boolean0);
            } else {
              if (this.windRenderEffects != nullptr &&
                  (this.sprite == nullptr || !this.sprite.moveWithWind)) {
                this.windRenderEffects = nullptr;
              }
            }
          }
        }

        void reset() {
          this.tintr = 1.0F;
          this.tintg = 1.0F;
          this.tintb = 1.0F;
          this.name = nullptr;
          this.table = nullptr;
          this.rerouteCollide = nullptr;
          if (this.AttachedAnimSprite != nullptr) {
            for (int int0 = 0; int0 < this.AttachedAnimSprite.size(); int0++) {
              IsoSpriteInstance spriteInstance =
                  this.AttachedAnimSprite.get(int0);
              IsoSpriteInstance.add(spriteInstance);
            }

            this.AttachedAnimSprite.clear();
          }

          if (this.wallBloodSplats != nullptr) {
            this.wallBloodSplats.clear();
          }

          this.overlaySprite = nullptr;
          this.overlaySpriteColor = nullptr;
          this.customColor = nullptr;
          if (this.container != nullptr) {
            this.container.Items.clear();
            this.container.IncludingObsoleteItems.clear();
            this.container.setParent(nullptr);
            this.container.setSourceGrid(nullptr);
            this.container.vehiclePart = nullptr;
          }

          this.container = nullptr;
          this.dir = IsoDirections.N;
          this.Damage = 100;
          this.partialThumpDmg = 0.0F;
          this.NoPicking = false;
          this.offsetX = 32 * Core.TileScale;
          this.offsetY = 96 * Core.TileScale;
          this.OutlineOnMouseover = false;
          this.rerouteMask = nullptr;
          this.sprite = nullptr;
          this.square = nullptr;

          for (int int1 = 0; int1 < 4; int1++) {
            this.setAlphaAndTarget(int1, 1.0F);
          }

          this.bNeverDoneAlpha = true;
          this.bAlphaForced = false;
          this.highlightFlags = 0;
          this.tile = nullptr;
          this.spriteName = nullptr;
          this.specialTooltip = false;
          this.usesExternalWaterSource = false;
          this.externalWaterSource = nullptr;
          if (this.secondaryContainers != nullptr) {
            for (int int2 = 0; int2 < this.secondaryContainers.size(); int2++) {
              ItemContainer containerx = this.secondaryContainers.get(int2);
              containerx.Items.clear();
              containerx.IncludingObsoleteItems.clear();
              containerx.setParent(nullptr);
              containerx.setSourceGrid(nullptr);
              containerx.vehiclePart = nullptr;
            }

            this.secondaryContainers.clear();
          }

          this.renderYOffset = 0.0F;
          this.sx = 0.0F;
          this.windRenderEffects = nullptr;
          this.objectRenderEffects = nullptr;
          this.sheetRope = false;
          this.sheetRopeHealth = 100.0F;
          this.bMovedThumpable = false;
        }

        long customHashCode() {
          if (this.doNotSync) {
            return 0L;
          } else {
            try {
              long long0 = 1L;
              if (this.getObjectName() != nullptr) {
                long0 = long0 * 3L + this.getObjectName().hashCode();
              }

              if (this.name != nullptr) {
                long0 = long0 * 2L + this.name.hashCode();
              }

              if (this.container != nullptr) {
                long0 = ++long0 + this.container.Items.size();

                for (int int0 = 0; int0 < this.container.Items.size(); int0++) {
                  long0 +=
                      this.container.Items.get(int0).getModule().hashCode() +
                      this.container.Items.get(int0).getType().hashCode() +
                      this.container.Items.get(int0).id;
                }
              }

              return long0 + this.square.getObjects().indexOf(this);
            } catch (Throwable throwable) {
              DebugLog.log("ERROR: " + throwable.getMessage());
              return 0L;
            }
          }
        }

        void SetName(const std::string &_name) { this.name = _name; }

        std::string getName() { return this.name; }

        /**
         *
         * @param _name the name to set
         */
        void setName(const std::string &_name) { this.name = _name; }

        std::string getSpriteName() { return this.spriteName; }

        std::string getTile() { return this.tile; }

        bool isCharacter() { return this instanceof IsoLivingCharacter; }

        bool isZombie() { return false; }

        std::string getScriptName() { return "none"; }

      public
        void AttachAnim(String ObjectName, String AnimName, int NumFrames,
                        float frameIncrease, int OffsetX, int OffsetY,
                        boolean Looping, int FinishHoldFrameIndex,
                        boolean DeleteWhenFinished, float zBias,
                        ColorInfo TintMod) {
          if (this.AttachedAnimSprite == nullptr) {
            this.AttachedAnimSprite = new ArrayList<>(4);
          }

          IsoSprite spritex =
              IsoSprite.CreateSpriteUsingCache(ObjectName, AnimName, NumFrames);
          spritex.TintMod.set(TintMod);
          spritex.soffX = (short)(-OffsetX);
          spritex.soffY = (short)(-OffsetY);
          spritex.Animate = true;
          spritex.Loop = Looping;
          spritex.DeleteWhenFinished = DeleteWhenFinished;
          spritex.PlayAnim(AnimName);
          IsoSpriteInstance spriteInstance = spritex.def;
          spriteInstance.AnimFrameIncrease = frameIncrease;
          spriteInstance.Frame = 0.0F;
          this.AttachedAnimSprite.add(spriteInstance);
        }

      public
        void AttachExistingAnim(IsoSprite spr, int OffsetX, int OffsetY,
                                boolean Looping, int FinishHoldFrameIndex,
                                boolean DeleteWhenFinished, float zBias,
                                ColorInfo TintMod) {
          if (this.AttachedAnimSprite == nullptr) {
            this.AttachedAnimSprite = new ArrayList<>(4);
          }

          spr.TintMod.r = TintMod.r;
          spr.TintMod.g = TintMod.g;
          spr.TintMod.b = TintMod.b;
          spr.TintMod.a = TintMod.a;
          int integer0 = OffsetX;
          int integer1 = OffsetY;
          spr.soffX = (short)(-integer0);
          spr.soffY = (short)(-integer1);
          spr.Animate = true;
          spr.Loop = Looping;
          spr.DeleteWhenFinished = DeleteWhenFinished;
          IsoSpriteInstance spriteInstance = IsoSpriteInstance.get(spr);
          this.AttachedAnimSprite.add(spriteInstance);
        }

        void AttachExistingAnim(IsoSprite spr, int OffsetX, int OffsetY,
                                bool Looping, int FinishHoldFrameIndex,
                                bool DeleteWhenFinished, float zBias) {
          this.AttachExistingAnim(spr, OffsetX, OffsetY, Looping,
                                  FinishHoldFrameIndex, DeleteWhenFinished,
                                  zBias, std::make_unique<ColorInfo>());
        }

        void DoTooltip(ObjectTooltip tooltipUI) {}

        void DoSpecialTooltip(ObjectTooltip tooltipUI, IsoGridSquare _square) {
          if (this.haveSpecialTooltip()) {
            tooltipUI.setHeight(0.0);
            LuaEventManager.triggerEvent("DoSpecialTooltip", tooltipUI,
                                         _square);
            if (tooltipUI.getHeight() == 0.0) {
              tooltipUI.hide();
            }
          }
        }

        ItemContainer getItemContainer() { return this.container; }

        float getOffsetX() { return this.offsetX; }

        /**
         *
         * @param _offsetX the offsetX to set
         */
        void setOffsetX(float _offsetX) { this.offsetX = _offsetX; }

        float getOffsetY() { return this.offsetY; }

        /**
         *
         * @param _offsetY the offsetY to set
         */
        void setOffsetY(float _offsetY) { this.offsetY = _offsetY; }

        IsoObject getRerouteMaskObject() { return this.rerouteMask; }

        bool HasTooltip() { return false; }

        bool getUsesExternalWaterSource() {
          return this.usesExternalWaterSource;
        }

        void setUsesExternalWaterSource(bool b) {
          this.usesExternalWaterSource = b;
        }

        bool hasExternalWaterSource() {
          return this.externalWaterSource != nullptr;
        }

        void doFindExternalWaterSource() {
          this.externalWaterSource = FindExternalWaterSource(this.getSquare());
        }

        static IsoObject FindExternalWaterSource(IsoGridSquare _square) {
          return _square = = null ? null
                                  : FindExternalWaterSource(_square.getX(),
                                                            _square.getY(),
                                                            _square.getZ());
        }

        static IsoObject FindExternalWaterSource(int x, int y, int z) {
          IsoGridSquare squarex =
              IsoWorld.instance.CurrentCell.getGridSquare(x, y, z + 1);
          IsoObject object0 = null;
          IsoObject object1 = FindWaterSourceOnSquare(squarex);
          if (object1 != nullptr) {
            if (object1.hasWater()) {
              return object1;
            }

            object0 = object1;
          }

          for (int int0 = -1; int0 <= 1; int0++) {
            for (int int1 = -1; int1 <= 1; int1++) {
              if (int1 != 0 || int0 != 0) {
                squarex = IsoWorld.instance.CurrentCell.getGridSquare(
                    x + int1, y + int0, z + 1);
                object1 = FindWaterSourceOnSquare(squarex);
                if (object1 != nullptr) {
                  if (object1.hasWater()) {
                    return object1;
                  }

                  if (object0 == nullptr) {
                    object0 = object1;
                  }
                }
              }
            }
          }

          return object0;
        }

        static IsoObject FindWaterSourceOnSquare(IsoGridSquare _square) {
          if (_square == nullptr) {
            return null;
          } else {
            PZArrayList pZArrayList = _square.getObjects();

            for (int int0 = 0; int0 < pZArrayList.size(); int0++) {
              IsoObject object = (IsoObject)pZArrayList.get(int0);
              if (object instanceof IsoThumpable &&
                                        (object.getSprite() == nullptr ||
                                         !object.getSprite().solidfloor) &&
                                        !object.getUsesExternalWaterSource() &&
                                        object.getWaterMax() > 0) {
                return object;
              }
            }

            return null;
          }
        }

        int getPipedFuelAmount() {
          if (this.sprite == nullptr) {
            return 0;
          } else {
            double double0 = 0.0;
            if (this.hasModData() && !this.getModData().isEmpty()) {
              void *object1 = this.getModData().rawget("fuelAmount");
              if (object1 != nullptr) {
                double0 = (Double)object1;
              }
            }

            if (this.sprite.getProperties().Is("fuelAmount")) {
              if (SandboxOptions.instance.FuelStationGas.getValue() == 7) {
                return 1000;
              }

              if (double0 == 0.0 &&
                  (SandboxOptions.getInstance()
                           .AllowExteriorGenerator.getValue() &&
                       this.getSquare().haveElectricity() ||
                   IsoWorld.instance.isHydroPowerOn())) {
                float float0 = 0.8F;
                float float1 = 1.0F;
                switch (
                    SandboxOptions.getInstance().FuelStationGas.getValue()) {
                case 1:
                  float1 = 0.0F;
                  float0 = 0.0F;
                  break;
                case 2:
                  float0 = 0.0F;
                  float1 = 0.01F;
                  break;
                case 3:
                  float0 = 0.01F;
                  float1 = 0.1F;
                  break;
                case 4:
                  float0 = 0.1F;
                  float1 = 0.5F;
                  break;
                case 5:
                  float0 = 0.5F;
                  float1 = 0.7F;
                  break;
                case 6:
                  float0 = 0.7F;
                  float1 = 0.8F;
                  break;
                case 7:
                  float0 = 0.8F;
                  float1 = 0.9F;
                  break;
                case 8:
                  float1 = 1.0F;
                  float0 = 1.0F;
                }

                double0 = (int)Rand.Next(
                    Integer.parseInt(
                        this.sprite.getProperties().Val("fuelAmount")) *
                        float0,
                    Integer.parseInt(
                        this.sprite.getProperties().Val("fuelAmount")) *
                        float1);
                this.getModData().rawset("fuelAmount", double0);
                this.transmitModData();
                return (int)double0;
              }
            }

            return (int)double0;
          }
        }

        void setPipedFuelAmount(int units) {
          units = Math.max(0, units);
          int int0 = this.getPipedFuelAmount();
          if (units != int0) {
            if (units == 0 && int0 != 0) {
              units = -1;
            }

            this.getModData().rawset("fuelAmount", (double)units);
            this.transmitModData();
          }
        }

        bool isWaterInfinite() {
          if (this.sprite == nullptr) {
            return false;
          } else if (this.square != nullptr &&
                     this.square.getRoom() != nullptr) {
            if (!this.sprite.getProperties().Is(IsoFlagType.waterPiped)) {
              return false;
            } else {
              return GameTime.getInstance().getNightsSurvived() >=
                             SandboxOptions.instance.getWaterShutModifier()
                         ? false
                         : !this.hasModData() ||
                               !(this.getModData().rawget("canBeWaterPiped")
                                     instanceof Boolean) ||
                               !(Boolean)this.getModData().rawget(
                                   "canBeWaterPiped");
            }
          } else {
            return false;
          }
        }

        IsoObject checkExternalWaterSource() {
          if (!this.usesExternalWaterSource) {
            return null;
          } else {
            if (this.externalWaterSource == nullptr ||
                !this.externalWaterSource.hasWater()) {
              this.doFindExternalWaterSource();
            }

            return this.externalWaterSource;
          }
        }

        int getWaterAmount() {
          if (this.sprite == nullptr) {
            return 0;
          } else if (this.usesExternalWaterSource) {
            if (this.isWaterInfinite()) {
              return 10000;
            } else {
              IsoObject object1 = this.checkExternalWaterSource();
              return object1 = = null ? 0 : object1.getWaterAmount();
            }
          } else if (this.isWaterInfinite()) {
            return 10000;
          } else {
            if (this.hasModData() && !this.getModData().isEmpty()) {
              void *object2 = this.getModData().rawget("waterAmount");
              if (object2 != nullptr) {
                if (object2 instanceof Double) {
                  return (int)Math.max(0.0, (Double)object2);
                }

                if (object2 instanceof String) {
                  return Math.max(0, Integer.parseInt((String)object2));
                }

                return 0;
              }
            }

            if (this.square != nullptr &&
                !this.square.getProperties().Is(IsoFlagType.water) &&
                this.sprite != nullptr &&
                this.sprite.getProperties().Is(IsoFlagType.solidfloor) &&
                this.square.getPuddlesInGround() > 0.09F) {
              return (int)(this.square.getPuddlesInGround() * 10.0F);
            } else {
              return !this.sprite.Properties.Is("waterAmount")
                         ? 0
                         : Integer.parseInt(
                               this.sprite.getProperties().Val("waterAmount"));
            }
          }
        }

        void setWaterAmount(int units) {
          if (this.usesExternalWaterSource) {
            if (!this.isWaterInfinite()) {
              IsoObject object = this.checkExternalWaterSource();
              if (object != nullptr) {
                object.setWaterAmount(units);
              }
            }
          } else {
            units = Math.max(0, units);
            int int0 = this.getWaterAmount();
            if (units != int0) {
              bool boolean0 = true;
              if (this.hasModData() && !this.getModData().isEmpty()) {
                boolean0 = this.getModData().rawget("waterAmount") == nullptr;
              }

              if (boolean0) {
                this.getModData().rawset("waterMax", (double)int0);
              }

              this.getModData().rawset("waterAmount", (double)units);
              if (units <= 0) {
                this.setTaintedWater(false);
              }

              LuaEventManager.triggerEvent("OnWaterAmountChange", this, int0);
            }
          }
        }

        int getWaterMax() {
          if (this.sprite == nullptr) {
            return 0;
          } else if (this.usesExternalWaterSource) {
            if (this.isWaterInfinite()) {
              return 10000;
            } else {
              IsoObject object1 = this.checkExternalWaterSource();
              return object1 != nullptr ? object1.getWaterMax() : 0;
            }
          } else if (this.isWaterInfinite()) {
            return 10000;
          } else {
            if (this.hasModData() && !this.getModData().isEmpty()) {
              void *object2 = this.getModData().rawget("waterMax");
              if (object2 != nullptr) {
                if (object2 instanceof Double) {
                  return (int)Math.max(0.0, (Double)object2);
                }

                if (object2 instanceof String) {
                  return Math.max(0, Integer.parseInt((String)object2));
                }

                return 0;
              }
            }

            if (this.square != nullptr &&
                !this.square.getProperties().Is(IsoFlagType.water) &&
                this.sprite != nullptr &&
                this.sprite.getProperties().Is(IsoFlagType.solidfloor) &&
                this.square.getPuddlesInGround() > 0.09F) {
              return (int)(this.square.getPuddlesInGround() * 10.0F);
            } else if (this.sprite.Properties.Is("waterMaxAmount")) {
              return Integer.parseInt(
                  this.sprite.getProperties().Val("waterMaxAmount"));
            } else {
              return this.sprite.Properties.Is("waterAmount")
                         ? Integer.parseInt(
                               this.sprite.getProperties().Val("waterAmount"))
                         : 0;
            }
          }
        }

        int useWater(int amount) {
          if (this.sprite == nullptr) {
            return 0;
          } else {
            int int0 = this.getWaterAmount();
            int int1 = 0;
            if (int0 >= amount) {
              int1 = amount;
            } else {
              int1 = int0;
            }

            if (this.square != nullptr && this.sprite != nullptr &&
                this.sprite.getProperties().Is(IsoFlagType.solidfloor) &&
                this.square.getPuddlesInGround() > 0.09F) {
              return int1;
            } else {
              if (!this.usesExternalWaterSource) {
                if (this.sprite.getProperties().Is(IsoFlagType.water)) {
                  return int1;
                }

                if (this.isWaterInfinite()) {
                  return int1;
                }
              }

              this.setWaterAmount(int0 - int1);
              return int1;
            }
          }
        }

        bool hasWater() {
          return this.square != nullptr && this.sprite != nullptr &&
                         this.sprite.getProperties().Is(
                             IsoFlagType.solidfloor) &&
                         this.square.getPuddlesInGround() > 0.09F
                     ? true
                     : this.getWaterAmount() > 0;
        }

        bool isTaintedWater() {
          if (this.square != nullptr && this.sprite != nullptr &&
              this.sprite.getProperties().Is(IsoFlagType.solidfloor) &&
              this.square.getPuddlesInGround() > 0.09F) {
            return true;
          } else {
            if (this.hasModData()) {
              void *object1 = this.getModData().rawget("taintedWater");
              if (object1 instanceof Boolean) {
                return (Boolean)object1;
              }
            }

            return this.sprite != nullptr &&
                   this.sprite.getProperties().Is(IsoFlagType.taintedWater);
          }
        }

        void setTaintedWater(bool tainted) {
          this.getModData().rawset("taintedWater", tainted);
        }

        InventoryItem replaceItem(InventoryItem item) {
          std::string string = null;
          InventoryItem _item = null;
          if (item != nullptr) {
            if (item.hasReplaceType(this.getObjectName())) {
              string = item.getReplaceType(this.getObjectName());
            } else if (item.hasReplaceType("WaterSource")) {
              string = item.getReplaceType("WaterSource");
            }
          }

          if (string != nullptr) {
            _item = item.getContainer().AddItem(
                InventoryItemFactory.CreateItem(string));
            if (item.getContainer().getParent() instanceof IsoGameCharacter) {
              IsoGameCharacter character =
                  (IsoGameCharacter)item.getContainer().getParent();
              if (character.getPrimaryHandItem() == item) {
                character.setPrimaryHandItem(_item);
              }

              if (character.getSecondaryHandItem() == item) {
                character.setSecondaryHandItem(_item);
              }
            }

            item.getContainer().Remove(item);
          }

          return _item;
        }

        void useItemOn(InventoryItem item) {
          std::string string = null;
          if (item != nullptr) {
            if (item.hasReplaceType(this.getObjectName())) {
              string = item.getReplaceType(this.getObjectName());
            } else if (item.hasReplaceType("WaterSource")) {
              string = item.getReplaceType("WaterSource");
              this.useWater(10);
            }
          }

          if (string != nullptr) {
            InventoryItem _item = item.getContainer().AddItem(
                InventoryItemFactory.CreateItem(string));
            item.setUses(item.getUses() - 1);
            if (item.getUses() <= 0 && item.getContainer() != nullptr) {
              item.getContainer().Items.remove(item);
            }
          }
        }

        float getX() { return this.square.getX(); }

        float getY() { return this.square.getY(); }

        float getZ() { return this.square.getZ(); }

        bool onMouseLeftClick(int x, int y) { return false; }

        PropertyContainer getProperties() {
          return this.sprite == nullptr ? nullptr : this.sprite.getProperties();
        }

        void RemoveAttachedAnims() {
          if (this.AttachedAnimSprite != nullptr) {
            for (int int0 = 0; int0 < this.AttachedAnimSprite.size(); int0++) {
              this.AttachedAnimSprite.get(int0).Dispose();
            }

            this.AttachedAnimSprite.clear();
          }
        }

        void RemoveAttachedAnim(int index) {
          if (this.AttachedAnimSprite != nullptr) {
            if (index >= 0 && index < this.AttachedAnimSprite.size()) {
              this.AttachedAnimSprite.get(index).Dispose();
              this.AttachedAnimSprite.remove(index);
            }
          }
        }

        Vector2 getFacingPosition(Vector2 pos) {
          if (this.square == nullptr) {
            return pos.set(0.0F, 0.0F);
          } else {
            PropertyContainer propertyContainer = this.getProperties();
            if (propertyContainer != nullptr) {
              if (this.getType() == IsoObjectType.wall) {
                if (propertyContainer.Is(IsoFlagType.collideN) &&
                    propertyContainer.Is(IsoFlagType.collideW)) {
                  return pos.set(this.getX(), this.getY());
                }

                if (propertyContainer.Is(IsoFlagType.collideN)) {
                  return pos.set(this.getX() + 0.5F, this.getY());
                }

                if (propertyContainer.Is(IsoFlagType.collideW)) {
                  return pos.set(this.getX(), this.getY() + 0.5F);
                }

                if (propertyContainer.Is(IsoFlagType.DoorWallN)) {
                  return pos.set(this.getX() + 0.5F, this.getY());
                }

                if (propertyContainer.Is(IsoFlagType.DoorWallW)) {
                  return pos.set(this.getX(), this.getY() + 0.5F);
                }
              } else {
                if (propertyContainer.Is(IsoFlagType.attachedN)) {
                  return pos.set(this.getX() + 0.5F, this.getY());
                }

                if (propertyContainer.Is(IsoFlagType.attachedS)) {
                  return pos.set(this.getX() + 0.5F, this.getY() + 1.0F);
                }

                if (propertyContainer.Is(IsoFlagType.attachedW)) {
                  return pos.set(this.getX(), this.getY() + 0.5F);
                }

                if (propertyContainer.Is(IsoFlagType.attachedE)) {
                  return pos.set(this.getX() + 1.0F, this.getY() + 0.5F);
                }
              }
            }

            return pos.set(this.getX() + 0.5F, this.getY() + 0.5F);
          }
        }

        Vector2 getFacingPositionAlt(Vector2 pos) {
          return this.getFacingPosition(pos);
        }

        float getRenderYOffset() { return this.renderYOffset; }

        void setRenderYOffset(float f) {
          this.renderYOffset = f;
          this.sx = 0.0F;
        }

        bool isTableSurface() {
          PropertyContainer propertyContainer = this.getProperties();
          return propertyContainer != nullptr ? propertyContainer.isTable()
                                              : false;
        }

        bool isTableTopObject() {
          PropertyContainer propertyContainer = this.getProperties();
          return propertyContainer != nullptr ? propertyContainer.isTableTop()
                                              : false;
        }

        bool getIsSurfaceNormalOffset() {
          PropertyContainer propertyContainer = this.getProperties();
          return propertyContainer != nullptr
                     ? propertyContainer.isSurfaceOffset()
                     : false;
        }

        float getSurfaceNormalOffset() {
          float float0 = 0.0F;
          PropertyContainer propertyContainer = this.getProperties();
          if (propertyContainer.isSurfaceOffset()) {
            float0 = propertyContainer.getSurface();
          }

          return float0;
        }

        float getSurfaceOffsetNoTable() {
          float float0 = 0.0F;
          int int0 = 0;
          PropertyContainer propertyContainer = this.getProperties();
          if (propertyContainer != nullptr) {
            float0 = propertyContainer.getSurface();
            int0 = propertyContainer.getItemHeight();
          }

          return float0 + this.getRenderYOffset() + int0;
        }

        float getSurfaceOffset() {
          float float0 = 0.0F;
          if (this.isTableSurface()) {
            PropertyContainer propertyContainer = this.getProperties();
            if (propertyContainer != nullptr) {
              float0 = propertyContainer.getSurface();
            }
          }

          return float0;
        }

        bool isStairsNorth() {
          return this.getType() == IsoObjectType.stairsTN ||
                 this.getType() == IsoObjectType.stairsMN ||
                 this.getType() == IsoObjectType.stairsBN;
        }

        bool isStairsWest() {
          return this.getType() == IsoObjectType.stairsTW ||
                 this.getType() == IsoObjectType.stairsMW ||
                 this.getType() == IsoObjectType.stairsBW;
        }

        bool isStairsObject() {
          return this.isStairsNorth() || this.isStairsWest();
        }

        bool isHoppable() {
          return this.sprite != nullptr &&
                 (this.sprite.getProperties().Is(IsoFlagType.HoppableN) ||
                  this.sprite.getProperties().Is(IsoFlagType.HoppableW));
        }

        bool isNorthHoppable() {
          return this.sprite != nullptr && this.isHoppable() &&
                 this.sprite.getProperties().Is(IsoFlagType.HoppableN);
        }

        bool haveSheetRope() {
          return IsoWindow.isTopOfSheetRopeHere(this.square,
                                                this.isNorthHoppable());
        }

        int countAddSheetRope() {
          return IsoWindow.countAddSheetRope(this.square,
                                             this.isNorthHoppable());
        }

        bool canAddSheetRope() {
          return IsoWindow.canAddSheetRope(this.square, this.isNorthHoppable());
        }

        bool addSheetRope(IsoPlayer player, const std::string &itemType) {
          return !this.canAddSheetRope()
                     ? false
                     : IsoWindow.addSheetRope(player, this.square,
                                              this.isNorthHoppable(), itemType);
        }

        bool removeSheetRope(IsoPlayer player) {
          return this.haveSheetRope()
                     ? IsoWindow.removeSheetRope(player, this.square,
                                                 this.isNorthHoppable())
                     : false;
        }

        void render(float x, float y, float z, ColorInfo col, bool bDoAttached,
                    bool bWallLightingPass, Shader shader) {
          if (!this.isSpriteInvisible()) {
            this.prepareToRender(col);
            int int0 = IsoCamera.frameState.playerIndex;
            if (this.shouldDrawMainSprite()) {
              this.sprite.render(this, x, y, z, this.dir, this.offsetX,
                                 this.offsetY +
                                     this.renderYOffset * Core.TileScale,
                                 stCol, !this.isBlink());
              if (this.isOutlineHighlight(int0) &&
                  !this.isOutlineHlAttached(int0) &&
                  IsoObject.OutlineShader.instance.StartShader()) {
                int int1 = this.outlineHighlightCol[int0];
                float float0 = Color.getRedChannelFromABGR(int1);
                float float1 = Color.getGreenChannelFromABGR(int1);
                float float2 = Color.getBlueChannelFromABGR(int1);
                IsoObject.OutlineShader.instance.setOutlineColor(
                    float0, float1, float2,
                    this.isOutlineHlBlink(int0) ? Core.blinkAlpha : 1.0F);
                Texture texture0 =
                    this.sprite.getTextureForCurrentFrame(this.dir);
                if (texture0 != nullptr) {
                  IsoObject.OutlineShader.instance.setStepSize(
                      this.outlineThickness, texture0.getWidth(),
                      texture0.getHeight());
                }

                this.sprite.render(this, x, y, z, this.dir, this.offsetX,
                                   this.offsetY +
                                       this.renderYOffset * Core.TileScale,
                                   stCol, !this.isBlink());
                IndieGL.EndShader();
              }
            }

            this.renderAttachedAndOverlaySpritesInternal(
                x, y, z, col, bDoAttached, bWallLightingPass, shader, nullptr);
            if (this.isOutlineHighlight(int0) &&
                this.isOutlineHlAttached(int0) &&
                IsoObject.OutlineShader.instance.StartShader()) {
              int int2 = this.outlineHighlightCol[int0];
              float float3 = Color.getRedChannelFromABGR(int2);
              float float4 = Color.getGreenChannelFromABGR(int2);
              float float5 = Color.getBlueChannelFromABGR(int2);
              IsoObject.OutlineShader.instance.setOutlineColor(
                  float3, float4, float5,
                  this.isOutlineHlBlink(int0) ? Core.blinkAlpha : 1.0F);
              Texture texture1 =
                  this.sprite.getTextureForCurrentFrame(this.dir);
              if (texture1 != nullptr) {
                IsoObject.OutlineShader.instance.setStepSize(
                    this.outlineThickness, texture1.getWidth(),
                    texture1.getHeight());
              }

              if (this.shouldDrawMainSprite()) {
                this.sprite.render(this, x, y, z, this.dir, this.offsetX,
                                   this.offsetY +
                                       this.renderYOffset * Core.TileScale,
                                   stCol, !this.isBlink());
              }

              this.renderAttachedAndOverlaySpritesInternal(
                  x, y, z, col, bDoAttached, bWallLightingPass, shader,
                  nullptr);
              IndieGL.EndShader();
            }

            if (!this.bAlphaForced && this.isUpdateAlphaDuringRender()) {
              this.updateAlpha(int0);
            }

            this.debugRenderItemHeight(x, y, z);
            this.debugRenderSurface(x, y, z);
          }
        }

        void debugRenderItemHeight(float float0, float float1, float float2) {
          if (DebugOptions.instance.IsoSprite.ItemHeight.getValue()) {
            if (this.square != nullptr &&
                IsoCamera.frameState.CamCharacterSquare != nullptr &&
                this.square.z == IsoCamera.frameState.CamCharacterSquare.z) {
              int int0 = this.sprite.getProperties().getItemHeight();
              if (int0 > 0) {
                int int1 = 0;
                if (this.sprite != nullptr &&
                    this.sprite.getProperties().getSurface() > 0 &&
                    this.sprite.getProperties().isSurfaceOffset()) {
                  int1 = this.sprite.getProperties().getSurface();
                }

                LineDrawer.addRectYOffset(float0, float1, float2, 1.0F, 1.0F,
                                          (int)this.getRenderYOffset() + int1 +
                                              int0,
                                          0.66F, 0.66F, 0.66F);
              }
            }
          }
        }

        void debugRenderSurface(float float0, float float1, float float2) {
          if (DebugOptions.instance.IsoSprite.Surface.getValue()) {
            if (this.square != nullptr &&
                IsoCamera.frameState.CamCharacterSquare != nullptr &&
                this.square.z == IsoCamera.frameState.CamCharacterSquare.z) {
              int int0 = 0;
              if (this.sprite != nullptr &&
                  this.sprite.getProperties().getSurface() > 0 &&
                  !this.sprite.getProperties().isSurfaceOffset()) {
                int0 = this.sprite.getProperties().getSurface();
              }

              if (int0 > 0) {
                LineDrawer.addRectYOffset(float0, float1, float2, 1.0F, 1.0F,
                                          (int)this.getRenderYOffset() + int0,
                                          1.0F, 1.0F, 1.0F);
              }
            }
          }
        }

      public
        void renderFloorTile(float x, float y, float z, ColorInfo col,
                             boolean bDoAttached, boolean bWallLightingPass,
                             Shader shader, Consumer<TextureDraw> texdModifier,
                             Consumer<TextureDraw> attachedAndOverlayModifier) {
          if (!this.isSpriteInvisible()) {
            this.prepareToRender(col);
            FloorShaper floorShaper0 =
                Type.tryCastTo(texdModifier, FloorShaper.class);
            FloorShaper floorShaper1 =
                Type.tryCastTo(attachedAndOverlayModifier, FloorShaper.class);
            if ((floorShaper0 != nullptr || floorShaper1 != nullptr) &&
                this.isHighlighted() && this.getHighlightColor() != nullptr) {
              ColorInfo colorInfo = this.getHighlightColor();
              float float0 =
                  colorInfo.a * (this.isBlink() ? Core.blinkAlpha : 1.0F);
              int int0 = Color.colorToABGR(colorInfo.r, colorInfo.g,
                                           colorInfo.b, float0);
              if (floorShaper0 != nullptr) {
                floorShaper0.setTintColor(int0);
              }

              if (floorShaper1 != nullptr) {
                floorShaper1.setTintColor(int0);
              }
            }

            if (this.shouldDrawMainSprite()) {
              IndieGL.shaderSetValue(shader, "floorLayer", 0);
              this.sprite.render(this, x, y, z, this.dir, this.offsetX,
                                 this.offsetY +
                                     this.renderYOffset * Core.TileScale,
                                 stCol, !this.isBlink(), texdModifier);
            }

            this.renderAttachedAndOverlaySpritesInternal(
                x, y, z, col, bDoAttached, bWallLightingPass, shader,
                attachedAndOverlayModifier);
            if (floorShaper0 != nullptr) {
              floorShaper0.setTintColor(0);
            }

            if (floorShaper1 != nullptr) {
              floorShaper1.setTintColor(0);
            }
          }
        }

      public
        void renderWallTile(float x, float y, float z, ColorInfo col,
                            boolean bDoAttached, boolean bWallLightingPass,
                            Shader shader, Consumer<TextureDraw> texdModifier) {
          if (!this.isSpriteInvisible()) {
            this.renderWallTileOnly(x, y, z, col, shader, texdModifier);
            this.renderAttachedAndOverlaySpritesInternal(
                x, y, z, col, bDoAttached, bWallLightingPass, shader,
                texdModifier);
            int int0 = IsoCamera.frameState.playerIndex;
            if (this.isOutlineHighlight(int0) &&
                !this.isOutlineHlAttached(int0) &&
                IsoObject.OutlineShader.instance.StartShader()) {
              int int1 = this.outlineHighlightCol[int0];
              float float0 = Color.getRedChannelFromABGR(int1);
              float float1 = Color.getGreenChannelFromABGR(int1);
              float float2 = Color.getBlueChannelFromABGR(int1);
              IsoObject.OutlineShader.instance.setOutlineColor(
                  float0, float1, float2,
                  this.isOutlineHlBlink(int0) ? Core.blinkAlpha : 1.0F);
              Texture texture = this.sprite.getTextureForCurrentFrame(this.dir);
              if (texture != nullptr) {
                IsoObject.OutlineShader.instance.setStepSize(
                    this.outlineThickness, texture.getWidth(),
                    texture.getHeight());
              }

              this.sprite.render(this, x, y, z, this.dir, this.offsetX,
                                 this.offsetY +
                                     this.renderYOffset * Core.TileScale,
                                 stCol, !this.isBlink());
              IndieGL.EndShader();
            }
          }
        }

        void renderWallTileOnly(float x, float y, float z, ColorInfo col,
                                Shader shader,
                                Consumer<TextureDraw> texdModifier) {
          if (!this.isSpriteInvisible()) {
            this.prepareToRender(col);
            WallShaper wallShaper =
                Type.tryCastTo(texdModifier, WallShaper.class);
            if (wallShaper != nullptr && this.isHighlighted() &&
                this.getHighlightColor() != nullptr) {
              ColorInfo colorInfo = this.getHighlightColor();
              float float0 =
                  colorInfo.a * (this.isBlink() ? Core.blinkAlpha : 1.0F);
              int int0 = Color.colorToABGR(colorInfo.r, colorInfo.g,
                                           colorInfo.b, float0);
              wallShaper.setTintColor(int0);
            }

            if (this.shouldDrawMainSprite()) {
              IndieGL.pushShader(shader);
              this.sprite.render(this, x, y, z, this.dir, this.offsetX,
                                 this.offsetY +
                                     this.renderYOffset * Core.TileScale,
                                 stCol, !this.isBlink(), texdModifier);
              IndieGL.popShader(shader);
            }

            if (wallShaper != nullptr) {
              wallShaper.setTintColor(0);
            }
          }
        }

        bool shouldDrawMainSprite() {
          return this.sprite == nullptr
                     ? false
                     : DebugOptions.instance.Terrain.RenderTiles.RenderSprites
                           .getValue();
        }

      public
        void renderAttachedAndOverlaySprites(
            float x, float y, float z, ColorInfo col, boolean bDoAttached,
            boolean bWallLightingPass, Shader shader,
            Consumer<TextureDraw> texdModifier) {
          if (!this.isSpriteInvisible()) {
            this.renderAttachedAndOverlaySpritesInternal(
                x, y, z, col, bDoAttached, bWallLightingPass, shader,
                texdModifier);
          }
        }

      private
        void renderAttachedAndOverlaySpritesInternal(
            float float0, float float1, float float2, ColorInfo colorInfo,
            boolean boolean0, boolean boolean1, Shader shader,
            Consumer<TextureDraw> consumer) {
          if (this.isHighlighted()) {
            colorInfo = stCol;
          }

          this.renderOverlaySprites(float0, float1, float2, colorInfo);
          if (boolean0) {
            this.renderAttachedSprites(float0, float1, float2, colorInfo,
                                       boolean1, shader, consumer);
          }
        }

        void prepareToRender(ColorInfo colorInfo) {
          stCol.set(colorInfo);
          if (this.isHighlighted()) {
            stCol.set(this.getHighlightColor());
            if (this.isBlink()) {
              stCol.a = Core.blinkAlpha;
            } else {
              stCol.a = 1.0F;
            }

            stCol.r = colorInfo.r * (1.0F - stCol.a) +
                      this.getHighlightColor().r * stCol.a;
            stCol.g = colorInfo.g * (1.0F - stCol.a) +
                      this.getHighlightColor().g * stCol.a;
            stCol.b = colorInfo.b * (1.0F - stCol.a) +
                      this.getHighlightColor().b * stCol.a;
            stCol.a = colorInfo.a;
          }

          if (this.customColor != nullptr) {
            float float0 =
                this.square != null
                    ? this.square.getDarkMulti(IsoPlayer.getPlayerIndex())
                    : 1.0F;
            if (this.isHighlighted()) {
              stCol.r = stCol.r * (this.customColor.r * float0);
              stCol.g = stCol.g * (this.customColor.g * float0);
              stCol.b = stCol.b * (this.customColor.b * float0);
            } else {
              stCol.r = this.customColor.r * float0;
              stCol.g = this.customColor.g * float0;
              stCol.b = this.customColor.b * float0;
            }
          }

          if (this.sprite != nullptr && this.sprite.forceAmbient) {
            float float1 = rmod * this.tintr;
            float float2 = gmod * this.tintg;
            float float3 = bmod * this.tintb;
            if (!this.isHighlighted()) {
              stCol.r = RenderSettings.getInstance().getAmbientForPlayer(
                            IsoPlayer.getPlayerIndex()) *
                        float1;
              stCol.g = RenderSettings.getInstance().getAmbientForPlayer(
                            IsoPlayer.getPlayerIndex()) *
                        float2;
              stCol.b = RenderSettings.getInstance().getAmbientForPlayer(
                            IsoPlayer.getPlayerIndex()) *
                        float3;
            }
          }

          int int0 = IsoPlayer.getPlayerIndex();
          float float4 = IsoCamera.frameState.CamCharacterX;
          float float5 = IsoCamera.frameState.CamCharacterY;
          float float6 = IsoCamera.frameState.CamCharacterZ;
          if (IsoWorld.instance.CurrentCell.IsPlayerWindowPeeking(int0)) {
            IsoPlayer player = IsoPlayer.players[int0];
            IsoDirections directions =
                IsoDirections.fromAngle(player.getForwardDirection());
            if (directions == IsoDirections.N ||
                directions == IsoDirections.NW) {
              float5 = (float)(float5 - 1.0);
            }

            if (directions == IsoDirections.W ||
                directions == IsoDirections.NW) {
              float4 = (float)(float4 - 1.0);
            }
          }

          if (this == IsoCamera.CamCharacter) {
            this.setAlphaAndTarget(int0, 1.0F);
          }

          lastRenderedRendered = lastRendered;
          lastRendered = this;
          if (this.sprite != nullptr && !(this instanceof IsoPhysicsObject) &&
              IsoCamera.CamCharacter != nullptr) {
            bool boolean0 = this instanceof
                IsoWindow || this.sprite.getType() == IsoObjectType.doorW ||
                    this.sprite.getType() == IsoObjectType.doorN;
            if (this.sprite.getProperties().Is("GarageDoor")) {
              boolean0 = false;
            }

            if (!boolean0 &&
                (this.square.getX() > float4 || this.square.getY() > float5) &&
                (int)float6 <= this.square.getZ()) {
              bool boolean1 = false;
              float float7 = 0.2F;
              bool boolean2 =
                  (this.sprite.cutW ||
                   this.sprite.getProperties().Is(IsoFlagType.doorW)) &&
                  this.square.getX() > float4;
              bool boolean3 =
                  (this.sprite.cutN ||
                   this.sprite.getProperties().Is(IsoFlagType.doorN)) &&
                  this.square.getY() > float5;
              if (boolean2 &&
                  this.square.getProperties().Is(IsoFlagType.WallSE) &&
                  this.square.getY() <= float5) {
                boolean2 = false;
              }

              if (!boolean2 && !boolean3) {
                boolean boolean4 = this.getType() == IsoObjectType.WestRoofB ||
                                   this.getType() == IsoObjectType.WestRoofM ||
                                   this.getType() == IsoObjectType.WestRoofT;
                bool boolean5 = boolean4 && (int)float6 == this.square.getZ() &&
                                this.square.getBuilding() == null;
                if (boolean5 &&
                    IsoWorld.instance.CurrentCell
                        .CanBuildingSquareOccludePlayer(this.square, int0)) {
                  boolean1 = true;
                  float7 = 0.05F;
                }
              } else {
                boolean1 = true;
              }

              if (this.sprite.getProperties().Is(IsoFlagType.halfheight)) {
                boolean1 = false;
              }

              if (boolean1) {
                if (boolean3 &&
                    this.sprite.getProperties().Is(IsoFlagType.HoppableN)) {
                  float7 = 0.25F;
                }

                if (boolean2 &&
                    this.sprite.getProperties().Is(IsoFlagType.HoppableW)) {
                  float7 = 0.25F;
                }

                if (this.bAlphaForced) {
                  if (this.getTargetAlpha(int0) == 1.0F) {
                    this.setAlphaAndTarget(int0, 0.99F);
                  }
                } else {
                  this.setTargetAlpha(int0, float7);
                }

                LowLightingQualityHack = true;
                this.NoPicking =
                    this.rerouteMask == nullptr &&
                    !(this instanceof IsoThumpable) &&
                    !IsoWindowFrame.isWindowFrame(this) &&
                    !this.sprite.getProperties().Is(IsoFlagType.doorN) &&
                    !this.sprite.getProperties().Is(IsoFlagType.doorW) &&
                    !this.sprite.getProperties().Is(IsoFlagType.HoppableN) &&
                    !this.sprite.getProperties().Is(IsoFlagType.HoppableW);
              } else {
                this.NoPicking = false;
              }
            } else {
              this.NoPicking = false;
            }
          }

          if (this == IsoCamera.CamCharacter) {
            this.setTargetAlpha(int0, 1.0F);
          }
        }

        float getAlphaUpdateRateDiv() { return 14.0F; }

        float getAlphaUpdateRateMul() {
          float float0 = 0.25F;
          if (this.square != nullptr && this.square.room != nullptr) {
            float0 *= 2.0F;
          }

          return float0;
        }

        bool isUpdateAlphaEnabled() { return true; }

        bool isUpdateAlphaDuringRender() { return true; }

        void updateAlpha() {
          if (!GameServer.bServer) {
            for (int int0 = 0; int0 < IsoPlayer.numPlayers; int0++) {
              if (IsoPlayer.players[int0] != nullptr) {
                this.updateAlpha(int0);
              }
            }
          }
        }

        void updateAlpha(int int0) {
          if (!GameServer.bServer) {
            float float0 = this.getAlphaUpdateRateMul();
            float float1 = this.getAlphaUpdateRateDiv();
            this.updateAlpha(int0, float0, float1);
          }
        }

        void updateAlpha(int int0, float float0, float float1) {
          if (this.isUpdateAlphaEnabled()) {
            if (!DebugOptions.instance.Character.Debug.UpdateAlpha.getValue()) {
              this.setAlphaToTarget(int0);
            } else {
              if (this.bNeverDoneAlpha) {
                this.setAlpha(0.0F);
                this.bNeverDoneAlpha = false;
              }

              if (DebugOptions.instance.Character.Debug.UpdateAlphaEighthSpeed
                      .getValue()) {
                float0 /= 8.0F;
                float1 *= 8.0F;
              }

              float float2 = GameTime.getInstance().getMultiplier();
              float float3 = float2 * 0.28F;
              float float4 = this.getAlpha(int0);
              float float5 = this.targetAlpha[int0];
              if (float4 < float5) {
                float4 += float3 * float0;
                if (float4 > float5) {
                  float4 = float5;
                }
              } else if (float4 > float5) {
                float4 -= float3 / float1;
                if (float4 < float5) {
                  float4 = float5;
                }
              }

              this.setAlpha(int0, float4);
            }
          }
        }

        void renderOverlaySprites(float float1, float float2, float float3,
                                  ColorInfo colorInfo1) {
          if (this.getOverlaySprite() != nullptr &&
              DebugOptions.instance.Terrain.RenderTiles.OverlaySprites
                  .getValue()) {
            ColorInfo colorInfo0 = stCol2;
            colorInfo0.set(colorInfo1);
            if (this.overlaySpriteColor != nullptr) {
              colorInfo0.set(this.overlaySpriteColor);
            }

            if (colorInfo0.a != 1.0F && this.overlaySprite.def != nullptr &&
                this.overlaySprite.def.bCopyTargetAlpha) {
              int int0 = IsoPlayer.getPlayerIndex();
              float float0 = this.alpha[int0];
              this.alpha[int0] = this.alpha[int0] * colorInfo0.a;
              this.getOverlaySprite().render(
                  this, float1, float2, float3, this.dir, this.offsetX,
                  this.offsetY + this.renderYOffset * Core.TileScale,
                  colorInfo0, true);
              this.alpha[int0] = float0;
            } else {
              this.getOverlaySprite().render(
                  this, float1, float2, float3, this.dir, this.offsetX,
                  this.offsetY + this.renderYOffset * Core.TileScale,
                  colorInfo0, true);
            }
          }
        }

      private
        void renderAttachedSprites(float float1, float float2, float float3,
                                   ColorInfo colorInfo, boolean boolean0,
                                   Shader shader,
                                   Consumer<TextureDraw> consumer) {
          if (this.AttachedAnimSprite != nullptr &&
              DebugOptions.instance.Terrain.RenderTiles.AttachedAnimSprites
                  .getValue()) {
            int int0 = this.AttachedAnimSprite.size();

            for (int int1 = 0; int1 < int0; int1++) {
              IsoSpriteInstance spriteInstance =
                  this.AttachedAnimSprite.get(int1);
              if (!boolean0 || !spriteInstance.parentSprite.Properties.Is(
                                   IsoFlagType.NoWallLighting)) {
                float float0 = colorInfo.a;
                IndieGL.shaderSetValue(shader, "floorLayer", 1);
                colorInfo.a = spriteInstance.alpha;
                void *object1 = consumer;
                if (consumer == WallShaperW.instance) {
                  if (spriteInstance.parentSprite.getProperties().Is(
                          IsoFlagType.attachedN)) {
                    Texture texture =
                        spriteInstance.parentSprite.getTextureForCurrentFrame(
                            this.dir);
                    if (texture != nullptr &&
                        texture.getWidth() < 32 * Core.TileScale) {
                      continue;
                    }
                  }

                  if (spriteInstance.parentSprite.getProperties().Is(
                          IsoFlagType.attachedW)) {
                    object1 = WallShaperWhole.instance;
                  }
                } else if (consumer == WallShaperN.instance) {
                  if (spriteInstance.parentSprite.getProperties().Is(
                          IsoFlagType.attachedW)) {
                    continue;
                  }

                  if (spriteInstance.parentSprite.getProperties().Is(
                          IsoFlagType.attachedN)) {
                    object1 = WallShaperWhole.instance;
                  }
                }

                spriteInstance.parentSprite.render(
                    spriteInstance, this, float1, float2, float3, this.dir,
                    this.offsetX,
                    this.offsetY + this.renderYOffset * Core.TileScale,
                    colorInfo, true, (Consumer<TextureDraw>)object1);
                colorInfo.a = float0;
                spriteInstance.update();
              }
            }
          }

          if (this.Children != nullptr &&
              DebugOptions.instance.Terrain.RenderTiles.AttachedChildren
                  .getValue()) {
            int int2 = this.Children.size();

            for (int int3 = 0; int3 < int2; int3++) {
              IsoObject object2 = this.Children.get(int3);
              if (object2 instanceof IsoMovingObject) {
                IndieGL.shaderSetValue(shader, "floorLayer", 1);
                object2.render(((IsoMovingObject)object2).x,
                               ((IsoMovingObject)object2).y,
                               ((IsoMovingObject)object2).z, colorInfo, true,
                               false, nullptr);
              }
            }
          }

          if (this.wallBloodSplats != nullptr &&
              DebugOptions.instance.Terrain.RenderTiles.AttachedWallBloodSplats
                  .getValue()) {
            if (Core.OptionBloodDecals == 0) {
              return;
            }

            IndieGL.shaderSetValue(shader, "floorLayer", 0);

            for (int int4 = 0; int4 < this.wallBloodSplats.size(); int4++) {
              this.wallBloodSplats.get(int4).render(float1, float2, float3,
                                                    colorInfo);
            }
          }
        }

        bool isSpriteInvisible() {
          return this.sprite != nullptr &&
                 this.sprite.getProperties().Is(IsoFlagType.invisible);
        }

        void renderFxMask(float x, float y, float z, bool bDoAttached) {
          if (this.sprite != nullptr) {
            if (this.getType() == IsoObjectType.wall) {
            }

            this.sprite.render(this, x, y, z, this.dir, this.offsetX,
                               this.offsetY +
                                   this.renderYOffset * Core.TileScale,
                               colFxMask, false);
          }

          if (this.getOverlaySprite() != nullptr) {
            this.getOverlaySprite().render(
                this, x, y, z, this.dir, this.offsetX,
                this.offsetY + this.renderYOffset * Core.TileScale, colFxMask,
                false);
          }

          if (bDoAttached) {
            if (this.AttachedAnimSprite != nullptr) {
              int int0 = this.AttachedAnimSprite.size();

              for (int int1 = 0; int1 < int0; int1++) {
                IsoSpriteInstance spriteInstance =
                    this.AttachedAnimSprite.get(int1);
                spriteInstance.render(this, x, y, z, this.dir, this.offsetX,
                                      this.offsetY +
                                          this.renderYOffset * Core.TileScale,
                                      colFxMask);
              }
            }

            if (this.Children != nullptr) {
              int int2 = this.Children.size();

              for (int int3 = 0; int3 < int2; int3++) {
                IsoObject object = this.Children.get(int3);
                if (object instanceof IsoMovingObject) {
                  object.render(((IsoMovingObject)object).x,
                                ((IsoMovingObject)object).y,
                                ((IsoMovingObject)object).z, colFxMask,
                                bDoAttached, false, nullptr);
                }
              }
            }

            if (this.wallBloodSplats != nullptr) {
              if (Core.OptionBloodDecals == 0) {
                return;
              }

              for (int int4 = 0; int4 < this.wallBloodSplats.size(); int4++) {
                this.wallBloodSplats.get(int4).render(x, y, z, colFxMask);
              }
            }
          }
        }

        void renderObjectPicker(float x, float y, float z,
                                ColorInfo lightInfo) {
          if (this.sprite != nullptr) {
            if (!this.sprite.getProperties().Is(IsoFlagType.invisible)) {
              this.sprite.renderObjectPicker(this.sprite.def, this, this.dir);
            }
          }
        }

        bool TestPathfindCollide(IsoMovingObject obj, IsoGridSquare from,
                                 IsoGridSquare to) {
          return false;
        }

        bool TestCollide(IsoMovingObject obj, IsoGridSquare from,
                         IsoGridSquare to) {
          return false;
        }

      public
        IsoObject.VisionResult TestVision(IsoGridSquare from,
                                          IsoGridSquare to) {
          return IsoObject.VisionResult.Unblocked;
        }

        Texture getCurrentFrameTex() {
          if (this.sprite == nullptr) {
            return null;
          } else if (this.sprite.CurrentAnim == nullptr) {
            return null;
          } else {
            return this.sprite.CurrentAnim.Frames.size() <=
                           this.sprite.def.Frame
                       ? nullptr
                       : this.sprite.CurrentAnim.Frames
                             .get((int)this.sprite.def.Frame)
                             .getTexture(this.dir);
          }
        }

        bool isMaskClicked(int x, int y) {
          return this.sprite == nullptr
                     ? false
                     : this.sprite.isMaskClicked(this.dir, x, y);
        }

        bool isMaskClicked(int x, int y, bool flip) {
          if (this.sprite == nullptr) {
            return false;
          } else {
            return this.overlaySprite != nullptr &&
                           this.overlaySprite.isMaskClicked(this.dir, x, y,
                                                            flip)
                       ? true
                       : this.sprite.isMaskClicked(this.dir, x, y, flip);
          }
        }

        float getMaskClickedY(int x, int y, bool flip) {
          return this.sprite == nullptr
                     ? 10000.0F
                     : this.sprite.getMaskClickedY(this.dir, x, y, flip);
        }

        ColorInfo getCustomColor() { return this.customColor; }

        void setCustomColor(ColorInfo col) { this.customColor = col; }

        void setCustomColor(float r, float g, float b, float a) {
          ColorInfo colorInfo = new ColorInfo(r, g, b, a);
          this.customColor = colorInfo;
        }

        void loadFromRemoteBuffer(ByteBuffer b) {
          this.loadFromRemoteBuffer(b, true);
        }

        void loadFromRemoteBuffer(ByteBuffer b, bool addToObjects) {
          try {
            this.load(b, 195);
          } catch (IOException iOException) {
            iOException.printStackTrace();
            return;
          }

          if (this instanceof
              IsoWorldInventoryObject &&
                  ((IsoWorldInventoryObject)this).getItem() == nullptr) {
            DebugLog.log(
                "loadFromRemoteBuffer() failed due to an unknown item type");
          } else {
            int int0 = b.getInt();
            int int1 = b.getInt();
            int int2 = b.getInt();
            int int3 = b.getInt();
            bool boolean0 = b.get() != 0;
            bool boolean1 = b.get() != 0;
            IsoWorld.instance.CurrentCell.EnsureSurroundNotNull(int0, int1,
                                                                int2);
            this.square =
                IsoWorld.instance.CurrentCell.getGridSquare(int0, int1, int2);
            if (this.square != nullptr) {
              if (GameServer.bServer &&
                  !(this instanceof IsoWorldInventoryObject)) {
                IsoRegions.setPreviousFlags(this.square);
              }

              if (boolean0) {
                this.square.getSpecialObjects().add(this);
              }

              if (boolean1 && this instanceof IsoWorldInventoryObject) {
                this.square.getWorldObjects().add(
                    (IsoWorldInventoryObject)this);
                this.square.chunk.recalcHashCodeObjects();
              }

              if (addToObjects) {
                if (int3 != -1 && int3 >= 0 &&
                    int3 <= this.square.getObjects().size()) {
                  this.square.getObjects().add(int3, this);
                } else {
                  this.square.getObjects().add(this);
                }
              }

              for (int int4 = 0; int4 < this.getContainerCount(); int4++) {
                ItemContainer containerx = this.getContainerByIndex(int4);
                containerx.parent = this;
                containerx.parent.square = this.square;
                containerx.SourceGrid = this.square;
              }

              for (int int5 = -1; int5 <= 1; int5++) {
                for (int int6 = -1; int6 <= 1; int6++) {
                  IsoGridSquare squarex =
                      IsoWorld.instance.CurrentCell.getGridSquare(
                          int5 + int0, int6 + int1, int2);
                  if (squarex != nullptr) {
                    squarex.RecalcAllWithNeighbours(true);
                  }
                }
              }
            }
          }
        }

        bool hasObjectAmbientEmitter() {
          IsoChunk chunk = this.getChunk();
          return chunk = = null ? false : chunk.hasObjectAmbientEmitter(this);
        }

        void addObjectAmbientEmitter(
            ObjectAmbientEmitters.PerObjectLogic perObjectLogic) {
          IsoChunk chunk = this.getChunk();
          if (chunk != nullptr) {
            chunk.addObjectAmbientEmitter(this, perObjectLogic);
          }
        }

        void addToWorld() {
          for (int int0 = 0; int0 < this.getContainerCount(); int0++) {
            ItemContainer container0 = this.getContainerByIndex(int0);
            container0.addItemsToProcessItems();
          }

          if (!GameServer.bServer) {
            void *object1 = null;
            ItemContainer container1 =
                this.getContainerByEitherType("fridge", "freezer");
            if (container1 != nullptr && container1.isPowered()) {
              this.addObjectAmbientEmitter(
                  new ObjectAmbientEmitters.FridgeHumLogic().init(this));
              object1 = "FridgeHum";
              IsoWorld.instance.getCell().addToProcessIsoObject(this);
            } else if (this.sprite != nullptr &&
                       this.sprite.getProperties().Is(IsoFlagType.waterPiped) &&
                       this.getWaterAmount() > 0.0F && Rand.Next(15) == 0) {
              this.addObjectAmbientEmitter(
                  new ObjectAmbientEmitters.WaterDripLogic().init(this));
              object1 = "WaterDrip";
            } else if (this.sprite == nullptr ||
                       this.sprite.getName() == nullptr ||
                       !this.sprite.getName().startsWith("camping_01") ||
                       this.sprite.tileSheetIndex != 0 &&
                           this.sprite.tileSheetIndex != 3) {
              if (this instanceof IsoDoor) {
                if (((IsoDoor)this).isExterior()) {
                  this.addObjectAmbientEmitter(
                      new ObjectAmbientEmitters.DoorLogic().init(this));
                }
              } else if (this instanceof IsoWindow) {
                if (((IsoWindow)this).isExterior()) {
                  this.addObjectAmbientEmitter(
                      new ObjectAmbientEmitters.WindowLogic().init(this));
                }
              } else if (this instanceof IsoTree && Rand.Next(40) == 0) {
                this.addObjectAmbientEmitter(
                    new ObjectAmbientEmitters.TreeAmbianceLogic().init(this));
                object1 = "TreeAmbiance";
              }
            } else {
              this.addObjectAmbientEmitter(
                  new ObjectAmbientEmitters.TentAmbianceLogic().init(this));
              object1 = "TentAmbiance";
            }

            PropertyContainer propertyContainer = this.getProperties();
            if (propertyContainer != nullptr &&
                propertyContainer.Is("AmbientSound")) {
              this.addObjectAmbientEmitter(
                  new ObjectAmbientEmitters.AmbientSoundLogic().init(this));
              object1 = propertyContainer.Val("AmbientSound");
            }

            this.checkMoveWithWind();
          }
        }

        void removeFromWorld() {
          IsoCell cell = this.getCell();
          cell.addToProcessIsoObjectRemove(this);
          cell.getStaticUpdaterObjectList().remove(this);

          for (int int0 = 0; int0 < this.getContainerCount(); int0++) {
            ItemContainer containerx = this.getContainerByIndex(int0);
            containerx.removeItemsFromProcessItems();
          }

          if (this.emitter != nullptr) {
            this.emitter.stopAll();
            this.emitter = nullptr;
          }

          if (this.getChunk() != nullptr) {
            this.getChunk().removeObjectAmbientEmitter(this);
          }
        }

        void reuseGridSquare() {}

        void removeFromSquare() {
          if (this.square != nullptr) {
            this.square.getObjects().remove(this);
            this.square.getSpecialObjects().remove(this);
          }
        }

        void transmitCustomColor() {
          if (GameClient.bClient && this.getCustomColor() != nullptr) {
            GameClient.instance.sendCustomColor(this);
          }
        }

        void transmitCompleteItemToClients() {
          if (GameServer.bServer) {
            if (GameServer.udpEngine == nullptr) {
              return;
            }

            if (SystemDisabler.doWorldSyncEnable) {
              for (int int0 = 0; int0 < GameServer.udpEngine.connections.size();
                   int0++) {
                UdpConnection udpConnection0 =
                    GameServer.udpEngine.connections.get(int0);
                if (udpConnection0.RelevantTo(this.square.x, this.square.y)) {
                  GameServer.SyncObjectChunkHashes(this.square.chunk,
                                                   udpConnection0);
                }
              }

              return;
            }

            for (int int1 = 0; int1 < GameServer.udpEngine.connections.size();
                 int1++) {
              UdpConnection udpConnection1 =
                  GameServer.udpEngine.connections.get(int1);
              if (udpConnection1 != nullptr && this.square != nullptr &&
                  udpConnection1.RelevantTo(this.square.x, this.square.y)) {
                ByteBufferWriter byteBufferWriter =
                    udpConnection1.startPacket();
                PacketTypes.PacketType.AddItemToMap.doPacket(byteBufferWriter);
                this.writeToRemoteBuffer(byteBufferWriter);
                PacketTypes.PacketType.AddItemToMap.send(udpConnection1);
              }
            }
          }
        }

        void transmitUpdatedSpriteToClients(UdpConnection connection) {
          if (GameServer.bServer) {
            for (int int0 = 0; int0 < GameServer.udpEngine.connections.size();
                 int0++) {
              UdpConnection udpConnection =
                  GameServer.udpEngine.connections.get(int0);
              if (udpConnection != nullptr && this.square != nullptr &&
                  (connection == nullptr ||
                   udpConnection.getConnectedGUID() !=
                       connection.getConnectedGUID()) &&
                  udpConnection.RelevantTo(this.square.x, this.square.y)) {
                ByteBufferWriter byteBufferWriter = udpConnection.startPacket();
                PacketTypes.PacketType.UpdateItemSprite.doPacket(
                    byteBufferWriter);
                byteBufferWriter.putInt(this.getSprite().ID);
                GameWindow.WriteStringUTF(byteBufferWriter.bb, this.spriteName);
                byteBufferWriter.putInt(this.getSquare().getX());
                byteBufferWriter.putInt(this.getSquare().getY());
                byteBufferWriter.putInt(this.getSquare().getZ());
                byteBufferWriter.putInt(
                    this.getSquare().getObjects().indexOf(this));
                if (this.AttachedAnimSprite != nullptr) {
                  byteBufferWriter.putByte(
                      (byte)this.AttachedAnimSprite.size());

                  for (int int1 = 0; int1 < this.AttachedAnimSprite.size();
                       int1++) {
                    IsoSpriteInstance spriteInstance =
                        this.AttachedAnimSprite.get(int1);
                    byteBufferWriter.putInt(spriteInstance.parentSprite.ID);
                  }
                } else {
                  byteBufferWriter.putByte((byte)0);
                }

                PacketTypes.PacketType.UpdateItemSprite.send(udpConnection);
              }
            }
          }
        }

        void transmitUpdatedSpriteToClients() {
          this.transmitUpdatedSpriteToClients(nullptr);
        }

        void transmitUpdatedSprite() {
          if (GameClient.bClient) {
            this.transmitUpdatedSpriteToServer();
          }

          if (GameServer.bServer) {
            this.transmitUpdatedSpriteToClients();
          }
        }

        void sendObjectChange(const std::string &change) {
          if (GameServer.bServer) {
            GameServer.sendObjectChange(this, change, (KahluaTable) nullptr);
          } else if (GameClient.bClient) {
            DebugLog.log("sendObjectChange() can only be called on the server");
          } else {
            SinglePlayerServer.sendObjectChange(this, change,
                                                (KahluaTable) nullptr);
          }
        }

        void sendObjectChange(const std::string &change, KahluaTable tbl) {
          if (GameServer.bServer) {
            GameServer.sendObjectChange(this, change, tbl);
          } else if (GameClient.bClient) {
            DebugLog.log("sendObjectChange() can only be called on the server");
          } else {
            SinglePlayerServer.sendObjectChange(this, change, tbl);
          }
        }

        void sendObjectChange(const std::string &change, Object... args) {
          if (GameServer.bServer) {
            GameServer.sendObjectChange(this, change, args);
          } else if (GameClient.bClient) {
            DebugLog.log("sendObjectChange() can only be called on the server");
          } else {
            SinglePlayerServer.sendObjectChange(this, change, args);
          }
        }

        void saveChange(const std::string &change, KahluaTable tbl,
                        ByteBuffer bb) {
          if ("containers" == change)) {
              bb.put((byte)this.getContainerCount());

              for (int int0 = 0; int0 < this.getContainerCount(); int0++) {
                ItemContainer containerx = this.getContainerByIndex(int0);

                try {
                  containerx.save(bb);
                } catch (Throwable throwable) {
                  ExceptionLogger.logException(throwable);
                }
              }
            }
          else if ("container.customTemperature" == change)) {
              if (this.getContainer() != nullptr) {
                bb.putFloat(this.getContainer().getCustomTemperature());
              } else {
                bb.putFloat(0.0F);
              }
            }
          else if ("name" == change)) {
            GameWindow.WriteStringUTF(bb, this.getName());
        }
          else if ("replaceWith" == change)) {
              if (tbl != nullptr && tbl.rawget("object") instanceof IsoObject) {
                IsoObject object = (IsoObject)tbl.rawget("object");

                try {
                  object.save(bb);
                } catch (IOException iOException) {
                  iOException.printStackTrace();
                }
              }
            }
          else if ("usesExternalWaterSource" == change)) {
              bool boolean0 =
                  tbl != null && Boolean.TRUE.equals(tbl.rawget("value"));
              bb.put((byte)(boolean0 ? 1 : 0));
            }
          else if ("sprite" == change)) {
              if (this.sprite == nullptr) {
                bb.putInt(0);
              } else {
                bb.putInt(this.sprite.ID);
                GameWindow.WriteStringUTF(bb, this.spriteName);
              }
            }
        }

        void loadChange(const std::string &change, ByteBuffer bb) {
          if ("containers" == change)) {
              for (int int0 = 0; int0 < this.getContainerCount(); int0++) {
                ItemContainer container0 = this.getContainerByIndex(int0);
                container0.removeItemsFromProcessItems();
                container0.removeAllItems();
              }

              this.removeAllContainers();
              uint8_t byte0 = bb.get();

              for (int int1 = 0; int1 < byte0; int1++) {
                ItemContainer container1 = new ItemContainer();
                container1.ID = 0;
                container1.parent = this;
                container1.SourceGrid = this.square;

                try {
                  container1.load(bb, 195);
                  if (int1 == 0) {
                    if (this instanceof IsoDeadBody) {
                      container1.Capacity = 8;
                    }

                    this.container = container1;
                  } else {
                    this.addSecondaryContainer(container1);
                  }
                } catch (Throwable throwable) {
                  ExceptionLogger.logException(throwable);
                }
              }
            }
          else if ("container.customTemperature" == change)) {
              float float0 = bb.getFloat();
              if (this.getContainer() != nullptr) {
                this.getContainer().setCustomTemperature(float0);
              }
            }
          else if ("name" == change)) {
              std::string string = GameWindow.ReadStringUTF(bb);
              this.setName(string);
            }
          else if ("replaceWith" == change)) {
              try {
                int int2 = this.getObjectIndex();
                if (int2 >= 0) {
                  IsoObject object = factoryFromFileInput(this.getCell(), bb);
                  object.load(bb, 195);
                  object.setSquare(this.square);
                  this.square.getObjects().set(int2, object);
                  this.square.getSpecialObjects().remove(this);
                  this.square.RecalcAllWithNeighbours(true);
                  if (this.getContainerCount() > 0) {
                    for (int int3 = 0; int3 < this.getContainerCount();
                         int3++) {
                      ItemContainer container2 = this.getContainerByIndex(int3);
                      container2.removeItemsFromProcessItems();
                    }

                    LuaEventManager.triggerEvent("OnContainerUpdate");
                  }
                }
              } catch (IOException iOException) {
                iOException.printStackTrace();
              }
            }
          else if ("usesExternalWaterSource" == change)) {
            this.usesExternalWaterSource = bb.get() == 1;
        }
          else if ("sprite" == change)) {
              int int4 = bb.getInt();
              if (int4 == 0) {
                this.sprite = nullptr;
                this.spriteName = nullptr;
                this.tile = nullptr;
              } else {
                this.spriteName = GameWindow.ReadString(bb);
                this.sprite =
                    IsoSprite.getSprite(IsoSpriteManager.instance, int4);
                if (this.sprite == nullptr) {
                  this.sprite =
                      IsoSprite.CreateSprite(IsoSpriteManager.instance);
                  this.sprite.LoadFramesNoDirPageSimple(this.spriteName);
                }
              }
            }
          else if ("emptyTrash" == change)) {
              this.getContainer().clear();
              if (this.getOverlaySprite() != nullptr) {
                ItemPickerJava.updateOverlaySprite(this);
              }
            }

          this.checkMoveWithWind();
        }

        void transmitUpdatedSpriteToServer() {
          if (GameClient.bClient) {
            ByteBufferWriter byteBufferWriter =
                GameClient.connection.startPacket();
            PacketTypes.PacketType.UpdateItemSprite.doPacket(byteBufferWriter);
            byteBufferWriter.putInt(this.getSprite().ID);
            GameWindow.WriteStringUTF(byteBufferWriter.bb, this.spriteName);
            byteBufferWriter.putInt(this.getSquare().getX());
            byteBufferWriter.putInt(this.getSquare().getY());
            byteBufferWriter.putInt(this.getSquare().getZ());
            byteBufferWriter.putInt(
                this.getSquare().getObjects().indexOf(this));
            if (this.AttachedAnimSprite != nullptr) {
              byteBufferWriter.putByte((byte)this.AttachedAnimSprite.size());

              for (int int0 = 0; int0 < this.AttachedAnimSprite.size();
                   int0++) {
                IsoSpriteInstance spriteInstance =
                    this.AttachedAnimSprite.get(int0);
                byteBufferWriter.putInt(spriteInstance.parentSprite.ID);
              }
            } else {
              byteBufferWriter.putByte((byte)0);
            }

            PacketTypes.PacketType.UpdateItemSprite.send(GameClient.connection);
          }
        }

        void transmitCompleteItemToServer() {
          if (GameClient.bClient) {
            ByteBufferWriter byteBufferWriter =
                GameClient.connection.startPacket();
            PacketTypes.PacketType.AddItemToMap.doPacket(byteBufferWriter);
            this.writeToRemoteBuffer(byteBufferWriter);
            PacketTypes.PacketType.AddItemToMap.send(GameClient.connection);
          }
        }

        void transmitModData() {
          if (this.square != nullptr) {
            if (GameClient.bClient) {
              ByteBufferWriter byteBufferWriter =
                  GameClient.connection.startPacket();
              PacketTypes.PacketType.ObjectModData.doPacket(byteBufferWriter);
              byteBufferWriter.putInt(this.getSquare().getX());
              byteBufferWriter.putInt(this.getSquare().getY());
              byteBufferWriter.putInt(this.getSquare().getZ());
              byteBufferWriter.putInt(
                  this.getSquare().getObjects().indexOf(this));
              if (this.getModData().isEmpty()) {
                byteBufferWriter.putByte((byte)0);
              } else {
                byteBufferWriter.putByte((byte)1);

                try {
                  this.getModData().save(byteBufferWriter.bb);
                } catch (IOException iOException) {
                  iOException.printStackTrace();
                }
              }

              PacketTypes.PacketType.ObjectModData.send(GameClient.connection);
            } else if (GameServer.bServer) {
              GameServer.sendObjectModData(this);
            }
          }
        }

        void writeToRemoteBuffer(ByteBufferWriter b) {
          try {
            this.save(b.bb);
          } catch (IOException iOException) {
            iOException.printStackTrace();
          }

          b.putInt(this.square.getX());
          b.putInt(this.square.getY());
          b.putInt(this.square.getZ());
          b.putInt(this.getObjectIndex());
          b.putBoolean(this.square.getSpecialObjects().contains(this));
          b.putBoolean(this.square.getWorldObjects().contains(this));
        }

        int getObjectIndex() {
          return this.square == nullptr
                     ? -1
                     : this.square.getObjects().indexOf(this);
        }

        int getMovingObjectIndex() {
          return this.square == nullptr
                     ? -1
                     : this.square.getMovingObjects().indexOf(this);
        }

        int getSpecialObjectIndex() {
          return this.square == nullptr
                     ? -1
                     : this.square.getSpecialObjects().indexOf(this);
        }

        int getStaticMovingObjectIndex() {
          return this.square == nullptr
                     ? -1
                     : this.square.getStaticMovingObjects().indexOf(this);
        }

        int getWorldObjectIndex() {
          return this.square == nullptr
                     ? -1
                     : this.square.getWorldObjects().indexOf(this);
        }

        IsoSprite getOverlaySprite() { return this.overlaySprite; }

        void setOverlaySprite(const std::string &_spriteName) {
          this.setOverlaySprite(_spriteName, -1.0F, -1.0F, -1.0F, -1.0F, true);
        }

        void setOverlaySprite(const std::string &_spriteName, bool bTransmit) {
          this.setOverlaySprite(_spriteName, -1.0F, -1.0F, -1.0F, -1.0F,
                                bTransmit);
        }

        void setOverlaySpriteColor(float r, float g, float b, float a) {
          this.overlaySpriteColor = new ColorInfo(r, g, b, a);
        }

        ColorInfo getOverlaySpriteColor() { return this.overlaySpriteColor; }

        void setOverlaySprite(const std::string &_spriteName, float r, float g,
                              float b, float a) {
          this.setOverlaySprite(_spriteName, r, g, b, a, true);
        }

        bool setOverlaySprite(const std::string &_spriteName, float r, float g,
                              float b, float a, bool bTransmit) {
          if (StringUtils.isNullOrWhitespace(_spriteName)) {
            if (this.overlaySprite == nullptr) {
              return false;
            }

            this.overlaySprite = nullptr;
            _spriteName = "";
          } else {
            bool boolean0;
            if (!(r > -1.0F)) {
              boolean0 = this.overlaySpriteColor == nullptr;
            } else {
              boolean0 = this.overlaySpriteColor != nullptr &&
                         this.overlaySpriteColor.r == r &&
                         this.overlaySpriteColor.g == g &&
                         this.overlaySpriteColor.b == b &&
                         this.overlaySpriteColor.a == a;
            }

            if (this.overlaySprite != nullptr &&
                _spriteName == this.overlaySprite.name) && boolean0) {
    return false;
            }

            this.overlaySprite =
                IsoSpriteManager.instance.getSprite(_spriteName);
            this.overlaySprite.name = _spriteName;
          }

          if (r > -1.0F) {
            this.overlaySpriteColor = new ColorInfo(r, g, b, a);
          } else {
            this.overlaySpriteColor = nullptr;
          }

          if (!bTransmit) {
            return true;
          } else {
            if (GameServer.bServer) {
              GameServer.updateOverlayForClients(this, _spriteName, r, g, b, a,
                                                 nullptr);
            } else if (GameClient.bClient) {
              ByteBufferWriter byteBufferWriter =
                  GameClient.connection.startPacket();
              PacketTypes.PacketType.UpdateOverlaySprite.doPacket(
                  byteBufferWriter);
              GameWindow.WriteStringUTF(byteBufferWriter.bb, _spriteName);
              byteBufferWriter.putInt(this.getSquare().getX());
              byteBufferWriter.putInt(this.getSquare().getY());
              byteBufferWriter.putInt(this.getSquare().getZ());
              byteBufferWriter.putFloat(r);
              byteBufferWriter.putFloat(g);
              byteBufferWriter.putFloat(b);
              byteBufferWriter.putFloat(a);
              byteBufferWriter.putInt(
                  this.getSquare().getObjects().indexOf(this));
              PacketTypes.PacketType.UpdateOverlaySprite.send(
                  GameClient.connection);
            }

            return true;
          }
        }

        bool haveSpecialTooltip() { return this.specialTooltip; }

        void setSpecialTooltip(bool _specialTooltip) {
          this.specialTooltip = _specialTooltip;
        }

        int getKeyId() { return this.keyId; }

        void setKeyId(int _keyId) { this.keyId = _keyId; }

        bool isHighlighted() { return (this.highlightFlags & 1) != 0; }

        void setHighlighted(bool highlight) {
          this.setHighlighted(highlight, true);
        }

        void setHighlighted(bool highlight, bool renderOnce) {
          if (highlight) {
            this.highlightFlags = (byte)(this.highlightFlags | 1);
          } else {
            this.highlightFlags &= -2;
          }

          if (renderOnce) {
            this.highlightFlags = (byte)(this.highlightFlags | 2);
          } else {
            this.highlightFlags &= -3;
          }
        }

        ColorInfo getHighlightColor() { return this.highlightColor; }

        void setHighlightColor(ColorInfo _highlightColor) {
          this.highlightColor.set(_highlightColor);
        }

        void setHighlightColor(float r, float g, float b, float a) {
          if (this.highlightColor == nullptr) {
            this.highlightColor = new ColorInfo(r, g, b, a);
          } else {
            this.highlightColor.set(r, g, b, a);
          }
        }

        bool isBlink() { return (this.highlightFlags & 4) != 0; }

        void setBlink(bool blink) {
          if (blink) {
            this.highlightFlags = (byte)(this.highlightFlags | 4);
          } else {
            this.highlightFlags &= -5;
          }
        }

        void checkHaveElectricity() {
          if (!GameServer.bServer) {
            ItemContainer containerx =
                this.getContainerByEitherType("fridge", "freezer");
            if (containerx != nullptr && containerx.isPowered()) {
              IsoWorld.instance.getCell().addToProcessIsoObject(this);
              if (this.getChunk() != nullptr &&
                  !this.hasObjectAmbientEmitter()) {
                this.getChunk().addObjectAmbientEmitter(
                    this,
                    new ObjectAmbientEmitters.FridgeHumLogic().init(this));
              }
            }

            this.checkAmbientSound();
          }
        }

        void checkAmbientSound() {
          PropertyContainer propertyContainer = this.getProperties();
          if (propertyContainer != nullptr &&
              propertyContainer.Is("AmbientSound") &&
              this.getChunk() != nullptr && !this.hasObjectAmbientEmitter()) {
            this.getChunk().addObjectAmbientEmitter(
                this, new ObjectAmbientEmitters.AmbientSoundLogic().init(this));
          }
        }

        int getContainerCount() {
          int int0 = this.container == null ? 0 : 1;
          int int1 = this.secondaryContainers == null
                         ? 0
                         : this.secondaryContainers.size();
          return int0 + int1;
        }

        ItemContainer getContainerByIndex(int index) {
          if (this.container != nullptr) {
            if (index == 0) {
              return this.container;
            } else if (this.secondaryContainers == nullptr) {
              return null;
            } else {
              return index >= 1 && index <= this.secondaryContainers.size()
                         ? this.secondaryContainers.get(index - 1)
                         : nullptr;
            }
          } else if (this.secondaryContainers == nullptr) {
            return null;
          } else {
            return index >= 0 && index < this.secondaryContainers.size()
                       ? this.secondaryContainers.get(index)
                       : nullptr;
          }
        }

        ItemContainer getContainerByType(const std::string &type) {
          for (int int0 = 0; int0 < this.getContainerCount(); int0++) {
            ItemContainer containerx = this.getContainerByIndex(int0);
            if (containerx.getType() == type)) {
    return containerx;
            }
          }

          return null;
        }

        ItemContainer getContainerByEitherType(const std::string &type1,
                                               const std::string &type2) {
          for (int int0 = 0; int0 < this.getContainerCount(); int0++) {
            ItemContainer containerx = this.getContainerByIndex(int0);
            if (containerx.getType() == type1) || containerx.getType() == type2)) {
    return containerx;
            }
          }

          return null;
        }

        void addSecondaryContainer(ItemContainer _container) {
          if (this.secondaryContainers == nullptr) {
            this.secondaryContainers = std::make_unique<ArrayList<>>();
          }

          this.secondaryContainers.add(_container);
          _container.parent = this;
        }

        int getContainerIndex(ItemContainer _container) {
          if (_container == this.container) {
            return 0;
          } else if (this.secondaryContainers == nullptr) {
            return -1;
          } else {
            for (int int0 = 0; int0 < this.secondaryContainers.size(); int0++) {
              if (this.secondaryContainers.get(int0) == _container) {
                return (this.container == nullptr ? 0 : 1) + int0;
              }
            }

            return -1;
          }
        }

        void removeAllContainers() {
          this.container = nullptr;
          if (this.secondaryContainers != nullptr) {
            this.secondaryContainers.clear();
          }
        }

        void createContainersFromSpriteProperties() {
          if (this.sprite != nullptr) {
            if (this.container == nullptr) {
              if (this.sprite.getProperties().Is(IsoFlagType.container) &&
                  this.container == nullptr) {
                this.container = new ItemContainer(
                    this.sprite.getProperties().Val("container"), this.square,
                    this);
                this.container.parent = this;
                this.OutlineOnMouseover = true;
                if (this.sprite.getProperties().Is("ContainerCapacity")) {
                  this.container.Capacity = Integer.parseInt(
                      this.sprite.getProperties().Val("ContainerCapacity"));
                }

                if (this.sprite.getProperties().Is("ContainerPosition")) {
                  this.container.setContainerPosition(
                      this.sprite.getProperties().Val("ContainerPosition"));
                }
              }

              if (this.getSprite().getProperties().Is("Freezer")) {
                ItemContainer containerx =
                    new ItemContainer("freezer", this.square, this);
                if (this.getSprite().getProperties().Is("FreezerCapacity")) {
                  containerx.Capacity = Integer.parseInt(
                      this.sprite.getProperties().Val("FreezerCapacity"));
                } else {
                  containerx.Capacity = 15;
                }

                if (this.container == nullptr) {
                  this.container = containerx;
                  this.container.parent = this;
                } else {
                  this.addSecondaryContainer(containerx);
                }

                if (this.sprite.getProperties().Is("FreezerPosition")) {
                  containerx.setFreezerPosition(
                      this.sprite.getProperties().Val("FreezerPosition"));
                }
              }
            }
          }
        }

        bool isItemAllowedInContainer(ItemContainer _container,
                                      InventoryItem item) {
          return true;
        }

        bool isRemoveItemAllowedFromContainer(ItemContainer _container,
                                              InventoryItem item) {
          return true;
        }

        void cleanWallBlood() { this.square.removeBlood(false, true); }

        ObjectRenderEffects getWindRenderEffects() {
          return this.windRenderEffects;
        }

        ObjectRenderEffects getObjectRenderEffects() {
          return this.objectRenderEffects;
        }

        void setRenderEffect(RenderEffectType type) {
          this.setRenderEffect(type, false);
        }

        IsoObject getRenderEffectMaster() { return this; }

        void setRenderEffect(RenderEffectType type, bool reuseEqualType) {
          if (!GameServer.bServer) {
            IsoObject object = this.getRenderEffectMaster();
            if (object.objectRenderEffects == nullptr || reuseEqualType) {
              object.objectRenderEffects =
                  ObjectRenderEffects.getNew(this, type, reuseEqualType);
            }
          }
        }

        void removeRenderEffect(ObjectRenderEffects o) {
          IsoObject object = this.getRenderEffectMaster();
          if (object.objectRenderEffects != nullptr &&
              object.objectRenderEffects == o) {
            object.objectRenderEffects = nullptr;
          }
        }

        ObjectRenderEffects getObjectRenderEffectsToApply() {
          IsoObject object0 = this.getRenderEffectMaster();
          if (object0.objectRenderEffects != nullptr) {
            return object0.objectRenderEffects;
          } else {
            return Core.getInstance().getOptionDoWindSpriteEffects() &&
                           object0.windRenderEffects != nullptr
                       ? object0.windRenderEffects
                       : nullptr;
          }
        }

        void destroyFence(IsoDirections _dir) {
          BrokenFences.getInstance().destroyFence(this, _dir);
        }

        void getSpriteGridObjects(ArrayList<IsoObject> result) {
          result.clear();
          IsoSprite spritex = this.getSprite();
          if (spritex != nullptr) {
            IsoSpriteGrid spriteGrid = spritex.getSpriteGrid();
            if (spriteGrid != nullptr) {
              int int0 = spriteGrid.getSpriteGridPosX(spritex);
              int int1 = spriteGrid.getSpriteGridPosY(spritex);
              int int2 = this.getSquare().getX();
              int int3 = this.getSquare().getY();
              int int4 = this.getSquare().getZ();

              for (int int5 = int3 - int1;
                   int5 < int3 - int1 + spriteGrid.getHeight(); int5++) {
                for (int int6 = int2 - int0;
                     int6 < int2 - int0 + spriteGrid.getWidth(); int6++) {
                  IsoGridSquare squarex =
                      this.getCell().getGridSquare(int6, int5, int4);
                  if (squarex != nullptr) {
                    for (int int7 = 0; int7 < squarex.getObjects().size();
                         int7++) {
                      IsoObject object = squarex.getObjects().get(int7);
                      if (object.getSprite() != nullptr &&
                          object.getSprite().getSpriteGrid() == spriteGrid) {
                        result.add(object);
                      }
                    }
                  }
                }
              }
            }
          }
        }

        int getOutlineHighlightCol() { return this.outlineHighlightCol[0]; }

        void setOutlineHighlightCol(ColorInfo _outlineHighlightCol) {
          if (_outlineHighlightCol != nullptr) {
            for (int int0 = 0; int0 < this.outlineHighlightCol.length; int0++) {
              this.outlineHighlightCol[int0] = Color.colorToABGR(
                  _outlineHighlightCol.r, _outlineHighlightCol.g,
                  _outlineHighlightCol.b, _outlineHighlightCol.a);
            }
          }
        }

        int getOutlineHighlightCol(int playerIndex) {
          return this.outlineHighlightCol[playerIndex];
        }

        void setOutlineHighlightCol(int playerIndex,
                                    ColorInfo _outlineHighlightCol) {
          if (_outlineHighlightCol != nullptr) {
            this.outlineHighlightCol[playerIndex] = Color.colorToABGR(
                _outlineHighlightCol.r, _outlineHighlightCol.g,
                _outlineHighlightCol.b, _outlineHighlightCol.a);
          }
        }

        void setOutlineHighlightCol(float r, float g, float b, float a) {
          for (int int0 = 0; int0 < this.outlineHighlightCol.length; int0++) {
            this.outlineHighlightCol[int0] = Color.colorToABGR(r, g, b, a);
          }
        }

        void setOutlineHighlightCol(int playerIndex, float r, float g, float b,
                                    float a) {
          this.outlineHighlightCol[playerIndex] = Color.colorToABGR(r, g, b, a);
        }

        bool isOutlineHighlight() { return this.isOutlineHighlight != 0; }

        bool isOutlineHighlight(int playerIndex) {
          return (this.isOutlineHighlight & 1 << playerIndex) != 0;
        }

        void setOutlineHighlight(bool _isOutlineHighlight) {
          this.isOutlineHighlight = (byte)(_isOutlineHighlight ? -1 : 0);
        }

        void setOutlineHighlight(int playerIndex, bool _isOutlineHighlight) {
          if (_isOutlineHighlight) {
            this.isOutlineHighlight =
                (byte)(this.isOutlineHighlight | 1 << playerIndex);
          } else {
            this.isOutlineHighlight =
                (byte)(this.isOutlineHighlight & ~(1 << playerIndex));
          }
        }

        bool isOutlineHlAttached() { return this.isOutlineHlAttached != 0; }

        bool isOutlineHlAttached(int playerIndex) {
          return (this.isOutlineHlAttached & 1 << playerIndex) != 0;
        }

        void setOutlineHlAttached(bool _isOutlineHlAttached) {
          this.isOutlineHlAttached = (byte)(_isOutlineHlAttached ? -1 : 0);
        }

        void setOutlineHlAttached(int playerIndex, bool _isOutlineHlAttached) {
          if (_isOutlineHlAttached) {
            this.isOutlineHlAttached =
                (byte)(this.isOutlineHlAttached | 1 << playerIndex);
          } else {
            this.isOutlineHlAttached =
                (byte)(this.isOutlineHlAttached & ~(1 << playerIndex));
          }
        }

        bool isOutlineHlBlink() { return this.isOutlineHlBlink != 0; }

        bool isOutlineHlBlink(int playerIndex) {
          return (this.isOutlineHlBlink & 1 << playerIndex) != 0;
        }

        void setOutlineHlBlink(bool _isOutlineHlBlink) {
          this.isOutlineHlBlink = (byte)(_isOutlineHlBlink ? -1 : 0);
        }

        void setOutlineHlBlink(int playerIndex, bool _isOutlineHlBlink) {
          if (_isOutlineHlBlink) {
            this.isOutlineHlBlink =
                (byte)(this.isOutlineHlBlink | 1 << playerIndex);
          } else {
            this.isOutlineHlBlink =
                (byte)(this.isOutlineHlBlink & ~(1 << playerIndex));
          }
        }

        void unsetOutlineHighlight() {
          this.isOutlineHighlight = 0;
          this.isOutlineHlBlink = 0;
          this.isOutlineHlAttached = 0;
        }

        float getOutlineThickness() { return this.outlineThickness; }

        void setOutlineThickness(float _outlineThickness) {
          this.outlineThickness = _outlineThickness;
        }

        void addItemsFromProperties() {
          PropertyContainer propertyContainer = this.getProperties();
          if (propertyContainer != nullptr) {
            std::string string0 = propertyContainer.Val("Material");
            std::string string1 = propertyContainer.Val("Material2");
            std::string string2 = propertyContainer.Val("Material3");
            if ("Wood" == string0) || "Wood" == string1) || "Wood" == string2)) {
                this.square.AddWorldInventoryItem(
                    InventoryItemFactory.CreateItem("Base.UnusableWood"),
                    Rand.Next(0.0F, 0.5F), Rand.Next(0.0F, 0.5F), 0.0F);
                if (Rand.NextBool(5)) {
                  this.square.AddWorldInventoryItem(
                      InventoryItemFactory.CreateItem("Base.UnusableWood"),
                      Rand.Next(0.0F, 0.5F), Rand.Next(0.0F, 0.5F), 0.0F);
                }
              }

            if (("MetalBars" == string0) || "MetalBars" == string1) || "MetalBars" == string2)) && Rand.NextBool(2)) {
                this.square.AddWorldInventoryItem(
                    InventoryItemFactory.CreateItem("Base.MetalBar"),
                    Rand.Next(0.0F, 0.5F), Rand.Next(0.0F, 0.5F), 0.0F);
              }

            if (("MetalPlates" == string0) || "MetalPlates" == string1) || "MetalPlates" == string2)) && Rand.NextBool(2)) {
                this.square.AddWorldInventoryItem(
                    InventoryItemFactory.CreateItem("Base.SheetMetal"),
                    Rand.Next(0.0F, 0.5F), Rand.Next(0.0F, 0.5F), 0.0F);
              }

            if (("MetalPipe" == string0) || "MetalPipe" == string1) || "MetalPipe" == string2)) && Rand.NextBool(2)) {
                this.square.AddWorldInventoryItem(
                    InventoryItemFactory.CreateItem("Base.MetalPipe"),
                    Rand.Next(0.0F, 0.5F), Rand.Next(0.0F, 0.5F), 0.0F);
              }

            if (("MetalWire" == string0) || "MetalWire" == string1) || "MetalWire" == string2)) && Rand.NextBool(3)) {
                this.square.AddWorldInventoryItem(
                    InventoryItemFactory.CreateItem("Base.Wire"),
                    Rand.Next(0.0F, 0.5F), Rand.Next(0.0F, 0.5F), 0.0F);
              }

            if (("Nails" == string0) || "Nails" == string1) || "Nails" == string2)) && Rand.NextBool(2)) {
                this.square.AddWorldInventoryItem(
                    InventoryItemFactory.CreateItem("Base.Nails"),
                    Rand.Next(0.0F, 0.5F), Rand.Next(0.0F, 0.5F), 0.0F);
              }

            if (("Screws" == string0) || "Screws" == string1) || "Screws" == string2)) && Rand.NextBool(2)) {
                this.square.AddWorldInventoryItem(
                    InventoryItemFactory.CreateItem("Base.Screws"),
                    Rand.Next(0.0F, 0.5F), Rand.Next(0.0F, 0.5F), 0.0F);
              }
          }
        }

        bool isDestroyed() { return this.Damage <= 0; }

        void Thump(IsoMovingObject thumper) {
          IsoGameCharacter character =
              Type.tryCastTo(thumper, IsoGameCharacter.class);
          if (character != nullptr) {
            Thumpable thumpable = this.getThumpableFor(character);
            if (thumpable == nullptr) {
              return;
            }

            if (thumpable != this) {
              thumpable.Thump(thumper);
              return;
            }
          }

          bool boolean0 = BrokenFences.getInstance().isBreakableObject(this);
          uint8_t byte0 = 8;
          if (thumper instanceof IsoZombie) {
            int int0 = thumper.getCurrentSquare().getMovingObjects().size();
            if (thumper.getCurrentSquare().getW() != nullptr) {
              int0 +=
                  thumper.getCurrentSquare().getW().getMovingObjects().size();
            }

            if (thumper.getCurrentSquare().getE() != nullptr) {
              int0 +=
                  thumper.getCurrentSquare().getE().getMovingObjects().size();
            }

            if (thumper.getCurrentSquare().getS() != nullptr) {
              int0 +=
                  thumper.getCurrentSquare().getS().getMovingObjects().size();
            }

            if (thumper.getCurrentSquare().getN() != nullptr) {
              int0 +=
                  thumper.getCurrentSquare().getN().getMovingObjects().size();
            }

            if (int0 >= byte0) {
              int int1 = 1 * ThumpState.getFastForwardDamageMultiplier();
              this.Damage = (short)(this.Damage - int1);
            } else {
              this.partialThumpDmg =
                  this.partialThumpDmg +
                  (float)int0 / byte0 *
                      ThumpState.getFastForwardDamageMultiplier();
              if ((int)this.partialThumpDmg > 0) {
                int int2 = (int)this.partialThumpDmg;
                this.Damage = (short)(this.Damage - int2);
                this.partialThumpDmg -= int2;
              }
            }

            WorldSoundManager.instance.addSound(
                thumper, this.square.getX(), this.square.getY(),
                this.square.getZ(), 20, 20, true, 4.0F, 15.0F);
          }

          if (this.Damage <= 0) {
            std::string string = "BreakObject";
            if (character != nullptr) {
              character.getEmitter().playSound(string, this);
            }

            if (GameServer.bServer) {
              GameServer.PlayWorldSoundServer(string, false,
                                              thumper.getCurrentSquare(), 0.2F,
                                              20.0F, 1.1F, true);
            }

            WorldSoundManager.instance.addSound(
                nullptr, this.square.getX(), this.square.getY(),
                this.square.getZ(), 10, 20, true, 4.0F, 15.0F);
            thumper.setThumpTarget(nullptr);
            if (boolean0) {
              PropertyContainer propertyContainer = this.getProperties();
              IsoDirections directions;
              if (propertyContainer.Is(IsoFlagType.collideN) &&
                  propertyContainer.Is(IsoFlagType.collideW)) {
                directions = thumper.getY() >= this.getY() ? IsoDirections.N
                                                           : IsoDirections.S;
              } else if (propertyContainer.Is(IsoFlagType.collideN)) {
                directions = thumper.getY() >= this.getY() ? IsoDirections.N
                                                           : IsoDirections.S;
              } else {
                directions = thumper.getX() >= this.getX() ? IsoDirections.W
                                                           : IsoDirections.E;
              }

              BrokenFences.getInstance().destroyFence(this, directions);
              return;
            }

            std::vector arrayList = new ArrayList();

            for (int int3 = 0; int3 < this.getContainerCount(); int3++) {
              ItemContainer containerx = this.getContainerByIndex(int3);
              arrayList.clear();
              arrayList.addAll(containerx.getItems());
              containerx.removeItemsFromProcessItems();
              containerx.removeAllItems();

              for (int int4 = 0; int4 < arrayList.size(); int4++) {
                this.getSquare().AddWorldInventoryItem(
                    (InventoryItem)arrayList.get(int4), 0.0F, 0.0F, 0.0F);
              }
            }

            this.square.transmitRemoveItemFromSquare(this);
          }
        }

        void setMovedThumpable(bool movedThumpable) {
          this.bMovedThumpable = movedThumpable;
        }

        bool isMovedThumpable() { return this.bMovedThumpable; }

        void WeaponHit(IsoGameCharacter chr, HandWeapon weapon) {}

        Thumpable getThumpableFor(IsoGameCharacter chr) {
          if (this.isDestroyed()) {
            return null;
          } else if (this.isMovedThumpable()) {
            return this;
          } else if (!BrokenFences.getInstance().isBreakableObject(this)) {
            return null;
          } else {
            IsoZombie zombie0 = Type.tryCastTo(chr, IsoZombie.class);
            return zombie0 != nullptr && zombie0.isCrawling() ? this : nullptr;
          }
        }

        bool isExistInTheWorld() {
          return this.square.getMovingObjects().contains(this);
        }

        float getThumpCondition() {
          return PZMath.clamp(this.getDamage(), 0, 100) / 100.0F;
        }

        static { initFactory(); }

      public
        static class IsoObjectFactory {
          const uint8_t classID;
          const std::string objectName;
          const int hashCode;

        public
          IsoObjectFactory(uint8_t _classID, const std::string &_objectName) {
            this.classID = _classID;
            this.objectName = _objectName;
            this.hashCode = _objectName.hashCode();
          }

          IsoObject InstantiateObject(IsoCell cell) {
            return new IsoObject(cell);
          }

          uint8_t getClassID() { return this.classID; }

          std::string getObjectName() { return this.objectName; }
        }

        public static class OutlineShader {
        public
          static final IsoObject.OutlineShader instance =
              new IsoObject.OutlineShader();
          ShaderProgram shaderProgram;
          int stepSize;
          int outlineColor;

          void initShader() {
            this.shaderProgram =
                ShaderProgram.createShaderProgram("outline", false, true);
            if (this.shaderProgram.isCompiled()) {
              this.stepSize = ARBShaderObjects.glGetUniformLocationARB(
                  this.shaderProgram.getShaderID(), "stepSize");
              this.outlineColor = ARBShaderObjects.glGetUniformLocationARB(
                  this.shaderProgram.getShaderID(), "outlineColor");
              ARBShaderObjects.glUseProgramObjectARB(
                  this.shaderProgram.getShaderID());
              ARBShaderObjects.glUniform2fARB(this.stepSize, 0.001F, 0.001F);
              ARBShaderObjects.glUseProgramObjectARB(0);
            }
          }

          void setOutlineColor(float float0, float float1, float float2,
                               float float3) {
            SpriteRenderer.instance.ShaderUpdate4f(
                this.shaderProgram.getShaderID(), this.outlineColor, float0,
                float1, float2, float3);
          }

          void setStepSize(float float0, int int1, int int0) {
            SpriteRenderer.instance.ShaderUpdate2f(
                this.shaderProgram.getShaderID(), this.stepSize, float0 / int1,
                float0 / int0);
          }

          bool StartShader() {
            if (this.shaderProgram == nullptr) {
              RenderThread.invokeOnRenderContext(this ::initShader);
            }

            if (this.shaderProgram.isCompiled()) {
              IndieGL.StartShader(this.shaderProgram.getShaderID(), 0);
              return true;
            } else {
              return false;
            }
          }
        }

        public static enum VisionResult {
          NoEffect, Blocked, Unblocked;
        }
        }
        } // namespace iso
        } // namespace zombie
