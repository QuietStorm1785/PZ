#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "fmod/fmod/FMODManager.h"
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
#include "zombie/audio/ObjectAmbientEmitters/DoorLogic.h"
#include "zombie/audio/ObjectAmbientEmitters/FridgeHumLogic.h"
#include "zombie/audio/ObjectAmbientEmitters/PerObjectLogic.h"
#include "zombie/audio/ObjectAmbientEmitters/TentAmbianceLogic.h"
#include "zombie/audio/ObjectAmbientEmitters/TreeAmbianceLogic.h"
#include "zombie/audio/ObjectAmbientEmitters/WaterDripLogic.h"
#include "zombie/audio/ObjectAmbientEmitters/WindowLogic.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoLivingCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/characters/IsoSurvivor.h"
#include "zombie/characters/IsoZombie.h"
#include "zombie/core/Color.h"
#include "zombie/core/Core.h"
#include "zombie/core/Rand.h"
#include "zombie/core/logger/ExceptionLogger.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/opengl/RenderSettings.h"
#include "zombie/core/opengl/Shader.h"
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
#include "zombie/iso/IsoObject/1.h"
#include "zombie/iso/IsoObject/10.h"
#include "zombie/iso/IsoObject/11.h"
#include "zombie/iso/IsoObject/12.h"
#include "zombie/iso/IsoObject/13.h"
#include "zombie/iso/IsoObject/14.h"
#include "zombie/iso/IsoObject/15.h"
#include "zombie/iso/IsoObject/16.h"
#include "zombie/iso/IsoObject/17.h"
#include "zombie/iso/IsoObject/18.h"
#include "zombie/iso/IsoObject/19.h"
#include "zombie/iso/IsoObject/2.h"
#include "zombie/iso/IsoObject/20.h"
#include "zombie/iso/IsoObject/21.h"
#include "zombie/iso/IsoObject/22.h"
#include "zombie/iso/IsoObject/23.h"
#include "zombie/iso/IsoObject/24.h"
#include "zombie/iso/IsoObject/25.h"
#include "zombie/iso/IsoObject/26.h"
#include "zombie/iso/IsoObject/27.h"
#include "zombie/iso/IsoObject/28.h"
#include "zombie/iso/IsoObject/29.h"
#include "zombie/iso/IsoObject/3.h"
#include "zombie/iso/IsoObject/30.h"
#include "zombie/iso/IsoObject/31.h"
#include "zombie/iso/IsoObject/32.h"
#include "zombie/iso/IsoObject/33.h"
#include "zombie/iso/IsoObject/34.h"
#include "zombie/iso/IsoObject/35.h"
#include "zombie/iso/IsoObject/36.h"
#include "zombie/iso/IsoObject/4.h"
#include "zombie/iso/IsoObject/5.h"
#include "zombie/iso/IsoObject/6.h"
#include "zombie/iso/IsoObject/7.h"
#include "zombie/iso/IsoObject/8.h"
#include "zombie/iso/IsoObject/9.h"
#include "zombie/iso/IsoObject/IsoObjectFactory.h"
#include "zombie/iso/IsoObject/OutlineShader.h"
#include "zombie/iso/IsoObject/VisionResult.h"
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
#include "zombie/iso/sprite/IsoDirectionFrame.h"
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
#include "zombie/network/PacketTypes/PacketType.h"
#include "zombie/network/ServerOptions.h"
#include "zombie/spnetwork/SinglePlayerServer.h"
#include "zombie/ui/ObjectTooltip.h"
#include "zombie/util/StringUtils.h"
#include "zombie/util/Type.h"
#include "zombie/util/io/BitHeader.h"
#include "zombie/util/io/BitHeader/HeaderSize.h"
#include "zombie/util/io/BitHeaderRead.h"
#include "zombie/util/io/BitHeaderWrite.h"
#include "zombie/util/list/PZArrayList.h"
#include "zombie/vehicles/BaseVehicle.h"
#include "zombie/world/WorldDictionary.h"
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace iso {


class IsoObject {
public:
    static const uint8_t OBF_Highlighted = 1;
    static const uint8_t OBF_HighlightRenderOnce = 2;
    static const uint8_t OBF_Blink = 4;
    static const int MAX_WALL_SPLATS = 32;
    static const std::string PropMoveWithWind = "MoveWithWind";
    static IsoObject lastRendered = nullptr;
    static IsoObject lastRenderedRendered = nullptr;
    static const ColorInfo stCol = std::make_shared<ColorInfo>();
    static float rmod;
    static float gmod;
    static float bmod;
    static bool LowLightingQualityHack = false;
    static int DefaultCondition = 0;
    static const ColorInfo stCol2 = std::make_shared<ColorInfo>();
    static const ColorInfo colFxMask = std::make_shared<ColorInfo>(1.0F, 1.0F, 1.0F, 1.0F);
    uint8_t highlightFlags;
    int keyId = -1;
    BaseSoundEmitter emitter;
    float sheetRopeHealth = 100.0F;
    bool sheetRope = false;
    bool bNeverDoneAlpha = true;
    bool bAlphaForced = false;
   public std::vector<IsoSpriteInstance> AttachedAnimSprite;
   public std::vector<IsoWallBloodSplat> wallBloodSplats;
    ItemContainer container = nullptr;
    IsoDirections dir = IsoDirections.N;
    short Damage = 100;
    float partialThumpDmg = 0.0F;
    bool NoPicking = false;
    float offsetX = (float)(32 * Core.TileScale);
    float offsetY = (float)(96 * Core.TileScale);
    bool OutlineOnMouseover = false;
    IsoObject rerouteMask = nullptr;
    IsoSprite sprite = nullptr;
    IsoSprite overlaySprite = nullptr;
    ColorInfo overlaySpriteColor = nullptr;
    IsoGridSquare square;
   private const float[] alpha = new float[4];
   private const float[] targetAlpha = new float[4];
    IsoObject rerouteCollide = nullptr;
    KahluaTable table = nullptr;
    std::string name = nullptr;
    float tintr = 1.0F;
    float tintg = 1.0F;
    float tintb = 1.0F;
    std::string spriteName = nullptr;
    float sx;
    float sy;
    bool doNotSync = false;
    ObjectRenderEffects windRenderEffects;
    ObjectRenderEffects objectRenderEffects;
    IsoObject externalWaterSource = nullptr;
    bool usesExternalWaterSource = false;
   std::vector<IsoObject> Children;
    std::string tile;
    bool specialTooltip = false;
    ColorInfo highlightColor = std::make_shared<ColorInfo>(0.9F, 1.0F, 0.0F, 1.0F);
   private std::vector<ItemContainer> secondaryContainers;
    ColorInfo customColor = nullptr;
    float renderYOffset = 0.0F;
    uint8_t isOutlineHighlight = 0;
    uint8_t isOutlineHlAttached = 0;
    uint8_t isOutlineHlBlink = 0;
   protected const int[] outlineHighlightCol = new int[4];
    float outlineThickness = 0.15F;
    bool bMovedThumpable = false;
   private static const Map<uint8_t, IsoObjectFactory> byteToObjectMap = std::make_unique<std::unordered_map<>>();
   private static const Map<int, IsoObjectFactory> hashCodeToObjectMap = std::make_unique<std::unordered_map<>>();
   private static const Map<std::string, IsoObjectFactory> nameToObjectMap = std::make_unique<std::unordered_map<>>();
    static IsoObjectFactory factoryIsoObject;
    static IsoObjectFactory factoryVehicle;

    public IsoObject(IsoCell var1) {
      this();
   }

    public IsoObject() {
      for (int var1 = 0; var1 < 4; var1++) {
         this.setAlphaAndTarget(var1, 1.0F);
         this.outlineHighlightCol[var1] = -1;
      }
   }

    public IsoObject(IsoCell var1, IsoGridSquare var2, IsoSprite var3) {
      this();
      this.sprite = var3;
      this.square = var2;
   }

    public IsoObject(IsoCell var1, IsoGridSquare var2, const std::string& var3) {
      this();
      this.sprite = IsoSpriteManager.instance.getSprite(var3);
      this.square = var2;
      this.tile = var3;
   }

    public IsoObject(IsoGridSquare var1, const std::string& var2, const std::string& var3) {
      this();
      this.sprite = IsoSpriteManager.instance.getSprite(var2);
      this.square = var1;
      this.tile = var2;
      this.spriteName = var2;
      this.name = var3;
   }

    public IsoObject(IsoGridSquare var1, const std::string& var2, const std::string& var3, bool var4) {
      this();
      if (var4) {
         this.sprite = IsoSprite.CreateSprite(IsoSpriteManager.instance);
         this.sprite.LoadFramesNoDirPageSimple(var2);
      } else {
         this.sprite = (IsoSprite)IsoSpriteManager.instance.NamedMap.get(var2);
      }

      this.tile = var2;
      this.square = var1;
      this.name = var3;
   }

    bool isFloor() {
      return this.getProperties() != nullptr ? this.getProperties().Is(IsoFlagType.solidfloor) : false;
   }

    public IsoObject(IsoGridSquare var1, const std::string& var2, bool var3) {
      this();
      if (var3) {
         this.sprite = IsoSprite.CreateSprite(IsoSpriteManager.instance);
         this.sprite.LoadFramesNoDirPageSimple(var2);
      } else {
         this.sprite = (IsoSprite)IsoSpriteManager.instance.NamedMap.get(var2);
      }

      this.tile = var2;
      this.square = var1;
   }

    public IsoObject(IsoGridSquare var1, const std::string& var2) {
      this();
      this.sprite = IsoSprite.CreateSprite(IsoSpriteManager.instance);
      this.sprite.LoadFramesNoDirPageSimple(var2);
      this.square = var1;
   }

    static IsoObject getNew(IsoGridSquare var0, const std::string& var1, const std::string& var2, bool var3) {
    IsoObject var4 = nullptr;
      /* synchronized - TODO: add std::mutex */ (CellLoader.isoObjectCache) {
         if (CellLoader.isoObjectCache.empty()) {
            var4 = std::make_shared<IsoObject>(var0, var1, var2, var3);
         } else {
            var4 = (IsoObject)CellLoader.isoObjectCache.pop();
            var4.reset();
            var4.tile = var1;
         }
      }

      if (var3) {
         var4.sprite = IsoSprite.CreateSprite(IsoSpriteManager.instance);
         var4.sprite.LoadFramesNoDirPageSimple(var4.tile);
      } else {
         var4.sprite = (IsoSprite)IsoSpriteManager.instance.NamedMap.get(var4.tile);
      }

      var4.square = var0;
      var4.name = var2;
    return var4;
   }

    static IsoObject getLastRendered() {
    return lastRendered;
   }

    static void setLastRendered(IsoObject var0) {
      lastRendered = var0;
   }

    static IsoObject getLastRenderedRendered() {
    return lastRenderedRendered;
   }

    static void setLastRenderedRendered(IsoObject var0) {
      lastRenderedRendered = var0;
   }

    static void setDefaultCondition(int var0) {
      DefaultCondition = var0;
   }

    static IsoObject getNew() {
      /* synchronized - TODO: add std::mutex */ (CellLoader.isoObjectCache) {
         return CellLoader.isoObjectCache.empty() ? std::make_unique<IsoObject>() : (IsoObject)CellLoader.isoObjectCache.pop();
      }
   }

    static IsoObjectFactory addIsoObjectFactory(IsoObjectFactory var0) {
      if (byteToObjectMap.containsKey(var0.classID)) {
         throw RuntimeException("Class id already exists, " + var0.objectName);
      } else {
         byteToObjectMap.put(var0.classID, var0);
         if (hashCodeToObjectMap.containsKey(var0.hashCode)) {
            throw RuntimeException("Hashcode already exists, " + var0.objectName);
         } else {
            hashCodeToObjectMap.put(var0.hashCode, var0);
            if (nameToObjectMap.containsKey(var0.objectName)) {
               throw RuntimeException("ObjectName already exists, " + var0.objectName);
            } else {
               nameToObjectMap.put(var0.objectName, var0);
    return var0;
            }
         }
      }
   }

    static IsoObjectFactory getFactoryVehicle() {
    return factoryVehicle;
   }

    static void initFactory() {
      factoryIsoObject = addIsoObjectFactory(std::make_shared<1>((byte)0, "IsoObject"));
      addIsoObjectFactory(std::make_shared<2>((byte)1, "Player"));
      addIsoObjectFactory(std::make_shared<3>((byte)2, "Survivor"));
      addIsoObjectFactory(std::make_shared<4>((byte)3, "Zombie"));
      addIsoObjectFactory(std::make_shared<5>((byte)4, "Pushable"));
      addIsoObjectFactory(std::make_shared<6>((byte)5, "WheelieBin"));
      addIsoObjectFactory(std::make_shared<7>((byte)6, "WorldInventoryItem"));
      addIsoObjectFactory(std::make_shared<8>((byte)7, "Jukebox"));
      addIsoObjectFactory(std::make_shared<9>((byte)8, "Curtain"));
      addIsoObjectFactory(std::make_shared<10>((byte)9, "Radio"));
      addIsoObjectFactory(std::make_shared<11>((byte)10, "Television"));
      addIsoObjectFactory(std::make_shared<12>((byte)11, "DeadBody"));
      addIsoObjectFactory(std::make_shared<13>((byte)12, "Barbecue"));
      addIsoObjectFactory(std::make_shared<14>((byte)13, "ClothingDryer"));
      addIsoObjectFactory(std::make_shared<15>((byte)14, "ClothingWasher"));
      addIsoObjectFactory(std::make_shared<16>((byte)15, "Fireplace"));
      addIsoObjectFactory(std::make_shared<17>((byte)16, "Stove"));
      addIsoObjectFactory(std::make_shared<18>((byte)17, "Door"));
      addIsoObjectFactory(std::make_shared<19>((byte)18, "Thumpable"));
      addIsoObjectFactory(std::make_shared<20>((byte)19, "IsoTrap"));
      addIsoObjectFactory(std::make_shared<21>((byte)20, "IsoBrokenGlass"));
      addIsoObjectFactory(std::make_shared<22>((byte)21, "IsoCarBatteryCharger"));
      addIsoObjectFactory(std::make_shared<23>((byte)22, "IsoGenerator"));
      addIsoObjectFactory(std::make_shared<24>((byte)23, "IsoCompost"));
      addIsoObjectFactory(std::make_shared<25>((byte)24, "Mannequin"));
      addIsoObjectFactory(std::make_shared<26>((byte)25, "StoneFurnace"));
      addIsoObjectFactory(std::make_shared<27>((byte)26, "Window"));
      addIsoObjectFactory(std::make_shared<28>((byte)27, "Barricade"));
      addIsoObjectFactory(std::make_shared<29>((byte)28, "Tree"));
      addIsoObjectFactory(std::make_shared<30>((byte)29, "LightSwitch"));
      addIsoObjectFactory(std::make_shared<31>((byte)30, "ZombieGiblets"));
      addIsoObjectFactory(std::make_shared<32>((byte)31, "MolotovCocktail"));
      addIsoObjectFactory(std::make_shared<33>((byte)32, "Fire"));
      factoryVehicle = addIsoObjectFactory(std::make_shared<34>((byte)33, "Vehicle"));
      addIsoObjectFactory(std::make_shared<35>((byte)34, "CombinationWasherDryer"));
      addIsoObjectFactory(std::make_shared<36>((byte)35, "StackedWasherDryer"));
   }

    static uint8_t factoryGetClassID(const std::string& var0) {
    IsoObjectFactory var1 = hashCodeToObjectMap.get(var0.hashCode());
      return var1 != nullptr ? var1.classID : factoryIsoObject.classID;
   }

    static IsoObject factoryFromFileInput(IsoCell var0, uint8_t var1) {
    IsoObjectFactory var2 = byteToObjectMap.get(var1);
      if (var2 == nullptr || var2.objectName == "Vehicle") && GameClient.bClient) {
         if (var2 == nullptr && Core.bDebug) {
            throw RuntimeException("Cannot get IsoObject from classID: " + var1);
         } else {
            return std::make_shared<IsoObject>(var0);
         }
      } else {
         return var2.InstantiateObject(var0);
      }
   }

    static IsoObject factoryFromFileInput_OLD(IsoCell var0, int var1) {
      if (var1 == "IsoObject".hashCode()) {
    IsoObject var2 = getNew();
         var2.sx = 0.0F;
    return var2;
      } else if (var1 == "Player".hashCode()) {
         return std::make_shared<IsoPlayer>(var0);
      } else if (var1 == "Survivor".hashCode()) {
         return std::make_shared<IsoSurvivor>(var0);
      } else if (var1 == "Zombie".hashCode()) {
         return std::make_shared<IsoZombie>(var0);
      } else if (var1 == "Pushable".hashCode()) {
         return std::make_shared<IsoPushableObject>(var0);
      } else if (var1 == "WheelieBin".hashCode()) {
         return std::make_shared<IsoWheelieBin>(var0);
      } else if (var1 == "WorldInventoryItem".hashCode()) {
         return std::make_shared<IsoWorldInventoryObject>(var0);
      } else if (var1 == "Jukebox".hashCode()) {
         return std::make_shared<IsoJukebox>(var0);
      } else if (var1 == "Curtain".hashCode()) {
         return std::make_shared<IsoCurtain>(var0);
      } else if (var1 == "Radio".hashCode()) {
         return std::make_shared<IsoRadio>(var0);
      } else if (var1 == "Television".hashCode()) {
         return std::make_shared<IsoTelevision>(var0);
      } else if (var1 == "DeadBody".hashCode()) {
         return std::make_shared<IsoDeadBody>(var0);
      } else if (var1 == "Barbecue".hashCode()) {
         return std::make_shared<IsoBarbecue>(var0);
      } else if (var1 == "ClothingDryer".hashCode()) {
         return std::make_shared<IsoClothingDryer>(var0);
      } else if (var1 == "ClothingWasher".hashCode()) {
         return std::make_shared<IsoClothingWasher>(var0);
      } else if (var1 == "Fireplace".hashCode()) {
         return std::make_shared<IsoFireplace>(var0);
      } else if (var1 == "Stove".hashCode()) {
         return std::make_shared<IsoStove>(var0);
      } else if (var1 == "Door".hashCode()) {
         return std::make_shared<IsoDoor>(var0);
      } else if (var1 == "Thumpable".hashCode()) {
         return std::make_shared<IsoThumpable>(var0);
      } else if (var1 == "IsoTrap".hashCode()) {
         return std::make_shared<IsoTrap>(var0);
      } else if (var1 == "IsoBrokenGlass".hashCode()) {
         return std::make_shared<IsoBrokenGlass>(var0);
      } else if (var1 == "IsoCarBatteryCharger".hashCode()) {
         return std::make_shared<IsoCarBatteryCharger>(var0);
      } else if (var1 == "IsoGenerator".hashCode()) {
         return std::make_shared<IsoGenerator>(var0);
      } else if (var1 == "IsoCompost".hashCode()) {
         return std::make_shared<IsoCompost>(var0);
      } else if (var1 == "Mannequin".hashCode()) {
         return std::make_shared<IsoMannequin>(var0);
      } else if (var1 == "StoneFurnace".hashCode()) {
         return std::make_shared<BSFurnace>(var0);
      } else if (var1 == "Window".hashCode()) {
         return std::make_shared<IsoWindow>(var0);
      } else if (var1 == "Barricade".hashCode()) {
         return std::make_shared<IsoBarricade>(var0);
      } else if (var1 == "Tree".hashCode()) {
         return IsoTree.getNew();
      } else if (var1 == "LightSwitch".hashCode()) {
         return std::make_shared<IsoLightSwitch>(var0);
      } else if (var1 == "ZombieGiblets".hashCode()) {
         return std::make_shared<IsoZombieGiblets>(var0);
      } else if (var1 == "MolotovCocktail".hashCode()) {
         return std::make_shared<IsoMolotovCocktail>(var0);
      } else if (var1 == "Fire".hashCode()) {
         return std::make_shared<IsoFire>(var0);
      } else {
         return (IsoObject)(var1 == "Vehicle".hashCode() && !GameClient.bClient ? std::make_shared<BaseVehicle>(var0) : std::make_shared<IsoObject>(var0));
      }
   }

    static Class factoryClassFromFileInput(IsoCell var0, int var1) {
      if (var1 == "IsoObject".hashCode()) {
         return IsoObject.class;
      } else if (var1 == "Player".hashCode()) {
         return IsoPlayer.class;
      } else if (var1 == "Survivor".hashCode()) {
         return IsoSurvivor.class;
      } else if (var1 == "Zombie".hashCode()) {
         return IsoZombie.class;
      } else if (var1 == "Pushable".hashCode()) {
         return IsoPushableObject.class;
      } else if (var1 == "WheelieBin".hashCode()) {
         return IsoWheelieBin.class;
      } else if (var1 == "WorldInventoryItem".hashCode()) {
         return IsoWorldInventoryObject.class;
      } else if (var1 == "Jukebox".hashCode()) {
         return IsoJukebox.class;
      } else if (var1 == "Curtain".hashCode()) {
         return IsoCurtain.class;
      } else if (var1 == "Radio".hashCode()) {
         return IsoRadio.class;
      } else if (var1 == "Television".hashCode()) {
         return IsoTelevision.class;
      } else if (var1 == "DeadBody".hashCode()) {
         return IsoDeadBody.class;
      } else if (var1 == "Barbecue".hashCode()) {
         return IsoBarbecue.class;
      } else if (var1 == "ClothingDryer".hashCode()) {
         return IsoClothingDryer.class;
      } else if (var1 == "ClothingWasher".hashCode()) {
         return IsoClothingWasher.class;
      } else if (var1 == "Fireplace".hashCode()) {
         return IsoFireplace.class;
      } else if (var1 == "Stove".hashCode()) {
         return IsoStove.class;
      } else if (var1 == "Mannequin".hashCode()) {
         return IsoMannequin.class;
      } else if (var1 == "Door".hashCode()) {
         return IsoDoor.class;
      } else if (var1 == "Thumpable".hashCode()) {
         return IsoThumpable.class;
      } else if (var1 == "Window".hashCode()) {
         return IsoWindow.class;
      } else if (var1 == "Barricade".hashCode()) {
         return IsoBarricade.class;
      } else if (var1 == "Tree".hashCode()) {
         return IsoTree.class;
      } else if (var1 == "LightSwitch".hashCode()) {
         return IsoLightSwitch.class;
      } else if (var1 == "ZombieGiblets".hashCode()) {
         return IsoZombieGiblets.class;
      } else if (var1 == "MolotovCocktail".hashCode()) {
         return IsoMolotovCocktail.class;
      } else {
    return var1 = = "Vehicle".hashCode() ? BaseVehicle.class : IsoObject.class;
      }
   }

    static IsoObject factoryFromFileInput(IsoCell var0, DataInputStream var1) {
    bool var2 = var1.readBoolean();
      if (!var2) {
    return nullptr;
      } else {
    uint8_t var3 = var1.readByte();
    return factoryFromFileInput();
      }
   }

    static IsoObject factoryFromFileInput(IsoCell var0, ByteBuffer var1) {
    bool var2 = var1.get() != 0;
      if (!var2) {
    return nullptr;
      } else {
    uint8_t var3 = var1.get();
    return factoryFromFileInput();
      }
   }

    void syncIsoObject(bool var1, uint8_t var2, UdpConnection var3, ByteBuffer var4) {
   }

    void syncIsoObjectSend(ByteBufferWriter var1) {
      var1.putInt(this.square.getX());
      var1.putInt(this.square.getY());
      var1.putInt(this.square.getZ());
      var1.putByte((byte)this.square.getObjects().indexOf(this));
      var1.putByte((byte)0);
      var1.putByte((byte)0);
   }

    std::string getTextureName() {
      return this.sprite == nullptr ? nullptr : this.sprite.name;
   }

    bool Serialize() {
    return true;
   }

    KahluaTable getModData() {
      if (this.table == nullptr) {
         this.table = LuaManager.platform.newTable();
      }

      return this.table;
   }

    bool hasModData() {
      return this.table != nullptr && !this.table.empty();
   }

    IsoGridSquare getSquare() {
      return this.square;
   }

    void setSquare(IsoGridSquare var1) {
      this.square = var1;
   }

    IsoChunk getChunk() {
    IsoGridSquare var1 = this.getSquare();
    return var1 = = nullptr ? nullptr : var1.getChunk();
   }

    void update() {
   }

    void renderlast() {
   }

    void DirtySlice() {
   }

    std::string getObjectName() {
      if (this.name != nullptr) {
         return this.name;
      } else {
         return this.sprite != nullptr && this.sprite.getParentObjectName() != nullptr ? this.sprite.getParentObjectName() : "IsoObject";
      }
   }

    void load(ByteBuffer var1, int var2) {
      this.load(var1, var2, false);
   }

    void load(ByteBuffer var1, int var2, bool var3) {
    int var4 = var1.getInt();
      var4 = IsoChunk.Fix2x(this.square, var4);
      this.sprite = IsoSprite.getSprite(IsoSpriteManager.instance, var4);
      if (var4 == -1) {
         this.sprite = IsoSpriteManager.instance.getSprite("");

         assert this.sprite != nullptr;

         assert this.sprite.ID == -1;
      }

    BitHeaderRead var5 = BitHeader.allocRead(HeaderSize.uint8_t, var1);
      if (!var5 == 0)) {
         if (var5.hasFlags(1)) {
    int var6;
            if (var5.hasFlags(2)) {
               var6 = 1;
            } else {
               var6 = var1.get() & 255;
            }

            if (var3) {
    std::string var7 = GameWindow.ReadStringUTF(var1);
               DebugLog.log(var7 + ", read = " + var6);
            }

            for (int var26 = 0; var26 < var6; var26++) {
               if (this.AttachedAnimSprite == nullptr) {
                  this.AttachedAnimSprite = std::make_unique<std::vector<>>();
               }

    int var8 = var1.getInt();
    IsoSprite var9 = IsoSprite.getSprite(IsoSpriteManager.instance, var8);
    IsoSpriteInstance var10 = nullptr;
               if (var9 != nullptr) {
                  var10 = var9.newInstance();
               } else if (Core.bDebug) {
                  DebugLog.General.warn("discarding attached sprite because it has no tile properties");
               }

    uint8_t var11 = var1.get();
    bool var12 = false;
    bool var13 = false;
               if ((var11 & 2) != 0) {
                  var12 = true;
               }

               if ((var11 & 4) != 0 && var10 != nullptr) {
                  var10.Flip = true;
               }

               if ((var11 & 8) != 0 && var10 != nullptr) {
                  var10.bCopyTargetAlpha = true;
               }

               if ((var11 & 16) != 0) {
                  var13 = true;
                  if (var10 != nullptr) {
                     var10.bMultiplyObjectAlpha = true;
                  }
               }

               if (var12) {
    float var14 = var1.getFloat();
    float var15 = var1.getFloat();
    float var16 = var1.getFloat();
    float var17 = Bits.unpackByteToFloatUnit(var1.get());
    float var18 = Bits.unpackByteToFloatUnit(var1.get());
    float var19 = Bits.unpackByteToFloatUnit(var1.get());
                  if (var10 != nullptr) {
                     var10.offX = var14;
                     var10.offY = var15;
                     var10.offZ = var16;
                     var10.tintr = var17;
                     var10.tintg = var18;
                     var10.tintb = var19;
                  }
               } else if (var10 != nullptr) {
                  var10.offX = 0.0F;
                  var10.offY = 0.0F;
                  var10.offZ = 0.0F;
                  var10.tintr = 1.0F;
                  var10.tintg = 1.0F;
                  var10.tintb = 1.0F;
                  var10.alpha = 1.0F;
                  var10.targetAlpha = 1.0F;
               }

               if (var13) {
    float var44 = var1.getFloat();
                  if (var10 != nullptr) {
                     var10.alpha = var44;
                  }
               }

               if (var9 != nullptr) {
                  if (var9.name != nullptr && var9.name.startsWith("overlay_blood_")) {
    float var45 = (float)GameTime.getInstance().getWorldAgeHours();
    IsoWallBloodSplat var46 = std::make_shared<IsoWallBloodSplat>(var45, var9);
                     if (this.wallBloodSplats == nullptr) {
                        this.wallBloodSplats = std::make_unique<std::vector<>>();
                     }

                     this.wallBloodSplats.push_back(var46);
                  } else {
                     this.AttachedAnimSprite.push_back(var10);
                  }
               }
            }
         }

         if (var5.hasFlags(4)) {
            if (var3) {
    std::string var22 = GameWindow.ReadStringUTF(var1);
               DebugLog.log(var22);
            }

    uint8_t var23 = var1.get();
            if ((var23 & 2) != 0) {
               this.name = "Grass";
            } else if ((var23 & 4) != 0) {
               this.name = WorldDictionary.getObjectNameFromID(var1.get());
            } else if ((var23 & 8) != 0) {
               this.name = GameWindow.ReadString(var1);
            }

            if ((var23 & 16) != 0) {
               this.spriteName = WorldDictionary.getSpriteNameFromID(var1.getInt());
            } else if ((var23 & 32) != 0) {
               this.spriteName = GameWindow.ReadString(var1);
            }
         }

         if (var5.hasFlags(8)) {
    float var24 = Bits.unpackByteToFloatUnit(var1.get());
    float var27 = Bits.unpackByteToFloatUnit(var1.get());
    float var34 = Bits.unpackByteToFloatUnit(var1.get());
            this.customColor = std::make_shared<ColorInfo>(var24, var27, var34, 1.0F);
         }

         this.doNotSync = var5.hasFlags(16);
         this.setOutlineOnMouseover(var5.hasFlags(32));
         if (var5.hasFlags(64)) {
    BitHeaderRead var25 = BitHeader.allocRead(HeaderSize.int16_t, var1);
            if (var25.hasFlags(1)) {
    uint8_t var28 = var1.get();
               if (var28 > 0) {
                  if (this.wallBloodSplats == nullptr) {
                     this.wallBloodSplats = std::make_unique<std::vector<>>();
                  }

    int var35 = 0;
                  if (GameClient.bClient || GameServer.bServer) {
                     var35 = ServerOptions.getInstance().BloodSplatLifespanDays.getValue();
                  }

    float var38 = (float)GameTime.getInstance().getWorldAgeHours();

                  for (int var41 = 0; var41 < var28; var41++) {
    IsoWallBloodSplat var43 = std::make_shared<IsoWallBloodSplat>();
                     var43.load(var1, var2);
                     if (var43.worldAge > var38) {
                        var43.worldAge = var38;
                     }

                     if (var35 <= 0 || !(var38 - var43.worldAge >= var35 * 24)) {
                        this.wallBloodSplats.push_back(var43);
                     }
                  }
               }
            }

            if (var25.hasFlags(2)) {
               if (var3) {
    std::string var29 = GameWindow.ReadStringUTF(var1);
                  DebugLog.log(var29);
               }

    uint8_t var30 = var1.get();

               for (int var36 = 0; var36 < var30; var36++) {
                  try {
    ItemContainer var39 = std::make_shared<ItemContainer>();
                     var39.ID = 0;
                     var39.parent = this;
                     var39.parent.square = this.square;
                     var39.SourceGrid = this.square;
                     var39.load(var1, var2);
                     if (var36 == 0) {
                        if (dynamic_cast<IsoDeadBody*>(this) != nullptr) {
                           var39.Capacity = 8;
                        }

                        this.container = var39;
                     } else {
                        this.addSecondaryContainer(var39);
                     }
                  } catch (Exception var20) {
                     if (this.container != nullptr) {
                        DebugLog.log("Failed to stream in container ID: " + this.container.ID);
                     }

                     throw RuntimeException(var20);
                  }
               }
            }

            if (var25.hasFlags(4)) {
               if (this.table == nullptr) {
                  this.table = LuaManager.platform.newTable();
               }

               this.table.load(var1, var2);
            }

            this.setSpecialTooltip(var25.hasFlags(8));
            if (var25.hasFlags(16)) {
               this.keyId = var1.getInt();
            }

            this.usesExternalWaterSource = var25.hasFlags(32);
            if (var25.hasFlags(64)) {
               this.sheetRope = true;
               this.sheetRopeHealth = var1.getFloat();
            } else {
               this.sheetRope = false;
            }

            if (var25.hasFlags(128)) {
               this.renderYOffset = var1.getFloat();
            }

            if (var25.hasFlags(256)) {
    void* var31 = nullptr;
               if (var25.hasFlags(512)) {
                  var31 = GameWindow.ReadString(var1);
               } else {
                  var31 = WorldDictionary.getSpriteNameFromID(var1.getInt());
               }

               if (var31 != nullptr && !var31.empty()) {
                  this.overlaySprite = IsoSpriteManager.instance.getSprite((std::string)var31);
                  this.overlaySprite.name = (std::string)var31;
               }
            }

            if (var25.hasFlags(1024)) {
    float var33 = Bits.unpackByteToFloatUnit(var1.get());
    float var37 = Bits.unpackByteToFloatUnit(var1.get());
    float var40 = Bits.unpackByteToFloatUnit(var1.get());
    float var42 = Bits.unpackByteToFloatUnit(var1.get());
               if (this.overlaySprite != nullptr) {
                  this.setOverlaySpriteColor(var33, var37, var40, var42);
               }
            }

            this.setMovedThumpable(var25.hasFlags(2048));
            var25.release();
         }
      }

      var5.release();
      if (this.sprite == nullptr) {
         this.sprite = IsoSprite.CreateSprite(IsoSpriteManager.instance);
         this.sprite.LoadFramesNoDirPageSimple(this.spriteName);
      }
   }

    void save(ByteBuffer var1) {
      this.save(var1, false);
   }

    void save(ByteBuffer var1, bool var2) {
      var1.put((byte)(this.Serialize() ? 1 : 0));
      if (this.Serialize()) {
         var1.put(factoryGetClassID(this.getObjectName()));
         var1.putInt(this.sprite == nullptr ? -1 : this.sprite.ID);
    BitHeaderWrite var3 = BitHeader.allocWrite(HeaderSize.uint8_t, var1);
         if (this.AttachedAnimSprite != nullptr) {
            var3.addFlags(1);
            if (this.AttachedAnimSprite.size() == 1) {
               var3.addFlags(2);
            }

    int var4 = this.AttachedAnimSprite.size() > 255 ? 255 : this.AttachedAnimSprite.size();
            if (var4 != 1) {
               var1.put((byte)var4);
            }

            if (var2) {
               GameWindow.WriteString(var1, "Writing attached sprites (" + var4 + ")");
            }

            for (int var5 = 0; var5 < var4; var5++) {
    IsoSpriteInstance var6 = this.AttachedAnimSprite.get(var5);
               var1.putInt(var6.getID());
    uint8_t var7 = 0;
    bool var8 = false;
               if (var6.offX != 0.0F || var6.offY != 0.0F || var6.offZ != 0.0F || var6.tintr != 1.0F || var6.tintg != 1.0F || var6.tintb != 1.0F) {
                  var7 = (byte)(var7 | 2);
                  var8 = true;
               }

               if (var6.Flip) {
                  var7 = (byte)(var7 | 4);
               }

               if (var6.bCopyTargetAlpha) {
                  var7 = (byte)(var7 | 8);
               }

               if (var6.bMultiplyObjectAlpha) {
                  var7 = (byte)(var7 | 16);
               }

               var1.put(var7);
               if (var8) {
                  var1.putFloat(var6.offX);
                  var1.putFloat(var6.offY);
                  var1.putFloat(var6.offZ);
                  var1.put(Bits.packFloatUnitToByte(var6.tintr));
                  var1.put(Bits.packFloatUnitToByte(var6.tintg));
                  var1.put(Bits.packFloatUnitToByte(var6.tintb));
               }

               if (var6.bMultiplyObjectAlpha) {
                  var1.putFloat(var6.alpha);
               }
            }
         }

         if (this.name != nullptr || this.spriteName != nullptr) {
            var3.addFlags(4);
            if (var2) {
               GameWindow.WriteString(var1, "Writing name");
            }

    uint8_t var9 = 0;
    uint8_t var11 = -1;
    int var15 = -1;
            if (this.name != nullptr) {
               if (this.name == "Grass")) {
                  var9 = (byte)(var9 | 2);
               } else {
                  var11 = WorldDictionary.getIdForObjectName(this.name);
                  if (var11 >= 0) {
                     var9 = (byte)(var9 | 4);
                  } else {
                     var9 = (byte)(var9 | 8);
                  }
               }
            }

            if (this.spriteName != nullptr) {
               var15 = WorldDictionary.getIdForSpriteName(this.spriteName);
               if (var15 >= 0) {
                  var9 = (byte)(var9 | 16);
               } else {
                  var9 = (byte)(var9 | 32);
               }
            }

            var1.put(var9);
            if (this.name != nullptr && !this.name == "Grass")) {
               if (var11 >= 0) {
                  var1.put(var11);
               } else {
                  GameWindow.WriteString(var1, this.name);
               }
            }

            if (this.spriteName != nullptr) {
               if (var15 >= 0) {
                  var1.putInt(var15);
               } else {
                  GameWindow.WriteString(var1, this.spriteName);
               }
            }
         }

         if (this.customColor != nullptr) {
            var3.addFlags(8);
            var1.put(Bits.packFloatUnitToByte(this.customColor.r));
            var1.put(Bits.packFloatUnitToByte(this.customColor.g));
            var1.put(Bits.packFloatUnitToByte(this.customColor.b));
         }

         if (this.doNotSync) {
            var3.addFlags(16);
         }

         if (this.isOutlineOnMouseover()) {
            var3.addFlags(32);
         }

    BitHeaderWrite var10 = BitHeader.allocWrite(HeaderSize.int16_t, var1);
         if (this.wallBloodSplats != nullptr) {
            var10.addFlags(1);
    int var12 = Math.min(this.wallBloodSplats.size(), 32);
    int var16 = this.wallBloodSplats.size() - var12;
            var1.put((byte)var12);

            for (int var17 = var16; var17 < this.wallBloodSplats.size(); var17++) {
               this.wallBloodSplats.get(var17).save(var1);
            }
         }

         if (this.getContainerCount() > 0) {
            var10.addFlags(2);
            if (var2) {
               GameWindow.WriteString(var1, "Writing container");
            }

            var1.put((byte)this.getContainerCount());

            for (int var13 = 0; var13 < this.getContainerCount(); var13++) {
               this.getContainerByIndex(var13).save(var1);
            }
         }

         if (this.table != nullptr && !this.table.empty()) {
            var10.addFlags(4);
            this.table.save(var1);
         }

         if (this.haveSpecialTooltip()) {
            var10.addFlags(8);
         }

         if (this.getKeyId() != -1) {
            var10.addFlags(16);
            var1.putInt(this.getKeyId());
         }

         if (this.usesExternalWaterSource) {
            var10.addFlags(32);
         }

         if (this.sheetRope) {
            var10.addFlags(64);
            var1.putFloat(this.sheetRopeHealth);
         }

         if (this.renderYOffset != 0.0F) {
            var10.addFlags(128);
            var1.putFloat(this.renderYOffset);
         }

         if (this.getOverlaySprite() != nullptr) {
            var10.addFlags(256);
    int var14 = WorldDictionary.getIdForSpriteName(this.getOverlaySprite().name);
            if (var14 < 0) {
               var10.addFlags(512);
               GameWindow.WriteString(var1, this.getOverlaySprite().name);
            } else {
               var1.putInt(var14);
            }

            if (this.getOverlaySpriteColor() != nullptr) {
               var10.addFlags(1024);
               var1.put(Bits.packFloatUnitToByte(this.getOverlaySpriteColor().r));
               var1.put(Bits.packFloatUnitToByte(this.getOverlaySpriteColor().g));
               var1.put(Bits.packFloatUnitToByte(this.getOverlaySpriteColor().b));
               var1.put(Bits.packFloatUnitToByte(this.getOverlaySpriteColor().a));
            }
         }

         if (this.isMovedThumpable()) {
            var10.addFlags(2048);
         }

         if (!var10 == 0)) {
            var3.addFlags(64);
            var10.write();
         } else {
            var1.position(var10.getStartPosition());
         }

         var3.write();
         var3.release();
         var10.release();
      }
   }

    void saveState(ByteBuffer var1) {
   }

    void loadState(ByteBuffer var1) {
   }

    void softReset() {
      if (this.container != nullptr) {
         this.container.Items.clear();
         this.container.bExplored = false;
         this.setOverlaySprite(nullptr, -1.0F, -1.0F, -1.0F, -1.0F, false);
      }

      if (this.AttachedAnimSprite != nullptr && !this.AttachedAnimSprite.empty()) {
         for (int var1 = 0; var1 < this.AttachedAnimSprite.size(); var1++) {
    IsoSprite var2 = this.AttachedAnimSprite.get(var1).parentSprite;
            if (var2.name != nullptr && var2.name.contains("blood")) {
               this.AttachedAnimSprite.remove(var1);
               var1--;
            }
         }
      }
   }

    void AttackObject(IsoGameCharacter var1) {
      this.Damage = (short)(this.Damage - 10);
    HandWeapon var2 = (HandWeapon)var1.getPrimaryHandItem();
      SoundManager.instance.PlaySound(var2.getDoorHitSound(), false, 2.0F);
      WorldSoundManager.instance.addSound(var1, this.square.getX(), this.square.getY(), this.square.getZ(), 20, 20, false, 0.0F, 15.0F);
      if (this.Damage <= 0) {
         this.square.getObjects().remove(this);
         this.square.RecalcAllWithNeighbours(true);
         if (this.getType() == IsoObjectType.stairsBN
            || this.getType() == IsoObjectType.stairsMN
            || this.getType() == IsoObjectType.stairsTN
            || this.getType() == IsoObjectType.stairsBW
            || this.getType() == IsoObjectType.stairsMW
            || this.getType() == IsoObjectType.stairsTW) {
            this.square.RemoveAllWith(IsoFlagType.attachtostairs);
         }

    uint8_t var3 = 1;

         for (int var4 = 0; var4 < var3; var4++) {
    InventoryItem var5 = this.square.AddWorldInventoryItem("Base.Plank", Rand.Next(-1.0F, 1.0F), Rand.Next(-1.0F, 1.0F), 0.0F);
            var5.setUses(1);
         }
      }
   }

    void onMouseRightClick(int var1, int var2) {
   }

    void onMouseRightReleased() {
   }

    void Hit(Vector2 var1, IsoObject var2, float var3) {
      if (dynamic_cast<BaseVehicle*>(var2) != nullptr) {
         this.HitByVehicle((BaseVehicle)var2, var3);
         if (this.Damage <= 0 && BrokenFences.getInstance().isBreakableObject(this)) {
    PropertyContainer var5 = this.getProperties();
    IsoDirections var4;
            if (var5.Is(IsoFlagType.collideN) && var5.Is(IsoFlagType.collideW)) {
               var4 = var2.getY() >= this.getY() ? IsoDirections.N : IsoDirections.S;
            } else if (var5.Is(IsoFlagType.collideN)) {
               var4 = var2.getY() >= this.getY() ? IsoDirections.N : IsoDirections.S;
            } else {
               var4 = var2.getX() >= this.getX() ? IsoDirections.W : IsoDirections.E;
            }

            BrokenFences.getInstance().destroyFence(this, var4);
         }
      }
   }

    void Damage(float var1) {
      this.Damage = (short)(this.Damage - var1 * 0.1);
   }

    void HitByVehicle(BaseVehicle var1, float var2) {
    short var3 = this.Damage;
      this.Damage = (short)(this.Damage - var2 * 0.1);
    BaseSoundEmitter var4 = IsoWorld.instance.getFreeEmitter(this.square.x + 0.5F, this.square.y + 0.5F, this.square.z);
    long var5 = var4.playSound("VehicleHitObject");
      var4.setParameterValue(var5, FMODManager.instance.getParameterDescription("VehicleSpeed"), var1.getCurrentSpeedKmHour());
      WorldSoundManager.instance.addSound(nullptr, this.square.getX(), this.square.getY(), this.square.getZ(), 20, 20, true, 4.0F, 15.0F);
      if (this.getProperties().Is("HitByCar")
         && this.getSprite().getProperties().Val("DamagedSprite") != nullptr
         && !this.getSprite().getProperties().Val("DamagedSprite") == "")
         && this.Damage <= 90
         && var3 > 90) {
         this.setSprite(IsoSpriteManager.instance.getSprite(this.getSprite().getProperties().Val("DamagedSprite")));
         if (this.getSprite().getProperties().Is("StopCar")) {
            this.getSprite().setType(IsoObjectType.isMoveAbleObject);
         } else {
            this.getSprite().setType(IsoObjectType.MAX);
         }

         if (dynamic_cast<IsoThumpable*>(this) != nullptr) {
            ((IsoThumpable)this).setBlockAllTheSquare(false);
         }

         if (GameServer.bServer) {
            this.transmitUpdatedSpriteToClients();
         }

         this.getSquare().RecalcProperties();
         this.Damage = 50;
      }

      if (this.Damage <= 40 && this.getProperties().Is("HitByCar") && !BrokenFences.getInstance().isBreakableObject(this)) {
         this.getSquare().transmitRemoveItemFromSquare(this);
      }
   }

    void Collision(Vector2 var1, IsoObject var2) {
      if (dynamic_cast<BaseVehicle*>(var2) != nullptr) {
         if (this.getProperties().Is("CarSlowFactor")) {
    int var3 = int.parseInt(this.getProperties().Val("CarSlowFactor"));
    BaseVehicle var4 = (BaseVehicle)var2;
            var4.ApplyImpulse(this, Math.abs(var4.getFudgedMass() * var4.getCurrentSpeedKmHour() * var3 / 100.0F));
         }

         if (this.getProperties().Is("HitByCar")) {
    BaseVehicle var7 = (BaseVehicle)var2;
    std::string var8 = this.getSprite().getProperties().Val("MinimumCarSpeedDmg");
            if (var8 == nullptr) {
               var8 = "150";
            }

            if (Math.abs(var7.getCurrentSpeedKmHour()) > int.parseInt(var8)) {
               this.HitByVehicle(var7, Math.abs(var7.getFudgedMass() * var7.getCurrentSpeedKmHour()) / 300.0F);
               if (this.Damage <= 0 && BrokenFences.getInstance().isBreakableObject(this)) {
    PropertyContainer var6 = this.getProperties();
    IsoDirections var5;
                  if (var6.Is(IsoFlagType.collideN) && var6.Is(IsoFlagType.collideW)) {
                     var5 = var7.getY() >= this.getY() ? IsoDirections.N : IsoDirections.S;
                  } else if (var6.Is(IsoFlagType.collideN)) {
                     var5 = var7.getY() >= this.getY() ? IsoDirections.N : IsoDirections.S;
                  } else {
                     var5 = var7.getX() >= this.getX() ? IsoDirections.W : IsoDirections.E;
                  }

                  BrokenFences.getInstance().destroyFence(this, var5);
               }
            } else if (!this.square.getProperties().Is(IsoFlagType.collideN) && !this.square.getProperties().Is(IsoFlagType.collideW)) {
               var7.ApplyImpulse(this, Math.abs(var7.getFudgedMass() * var7.getCurrentSpeedKmHour() * 10.0F / 200.0F));
               if (var7.getCurrentSpeedKmHour() > 3.0F) {
                  var7.ApplyImpulse(this, Math.abs(var7.getFudgedMass() * var7.getCurrentSpeedKmHour() * 10.0F / 150.0F));
               }

               var7.jniSpeed = 0.0F;
            }
         }
      }
   }

    void UnCollision(IsoObject var1) {
   }

    float GetVehicleSlowFactor(BaseVehicle var1) {
      if (this.getProperties().Is("CarSlowFactor")) {
    int var2 = int.parseInt(this.getProperties().Val("CarSlowFactor"));
         return 33.0F - (10 - var2);
      } else {
         return 0.0F;
      }
   }

    IsoObject getRerouteCollide() {
      return this.rerouteCollide;
   }

    void setRerouteCollide(IsoObject var1) {
      this.rerouteCollide = var1;
   }

    KahluaTable getTable() {
      return this.table;
   }

    void setTable(KahluaTable var1) {
      this.table = var1;
   }

    void setAlpha(float var1) {
      this.setAlpha(IsoPlayer.getPlayerIndex(), var1);
   }

    void setAlpha(int var1, float var2) {
      this.alpha[var1] = PZMath.clamp(var2, 0.0F, 1.0F);
   }

    void setAlphaToTarget(int var1) {
      this.setAlpha(var1, this.getTargetAlpha(var1));
   }

    void setAlphaAndTarget(float var1) {
    int var2 = IsoPlayer.getPlayerIndex();
      this.setAlphaAndTarget(var2, var1);
   }

    void setAlphaAndTarget(int var1, float var2) {
      this.setAlpha(var1, var2);
      this.setTargetAlpha(var1, var2);
   }

    float getAlpha() {
      return this.getAlpha(IsoPlayer.getPlayerIndex());
   }

    float getAlpha(int var1) {
      return this.alpha[var1];
   }

   public std::vector<IsoSpriteInstance> getAttachedAnimSprite() {
      return this.AttachedAnimSprite;
   }

    void setAttachedAnimSprite(std::vector<IsoSpriteInstance> var1) {
      this.AttachedAnimSprite = var1;
   }

    IsoCell getCell() {
      return IsoWorld.instance.CurrentCell;
   }

   public std::vector<IsoSpriteInstance> getChildSprites() {
      return this.AttachedAnimSprite;
   }

    void setChildSprites(std::vector<IsoSpriteInstance> var1) {
      this.AttachedAnimSprite = var1;
   }

    void clearAttachedAnimSprite() {
      if (this.AttachedAnimSprite != nullptr) {
         for (int var1 = 0; var1 < this.AttachedAnimSprite.size(); var1++) {
            IsoSpriteInstance.push_back(this.AttachedAnimSprite.get(var1));
         }

         this.AttachedAnimSprite.clear();
      }
   }

    ItemContainer getContainer() {
      return this.container;
   }

    void setContainer(ItemContainer var1) {
      var1.parent = this;
      this.container = var1;
   }

    IsoDirections getDir() {
      return this.dir;
   }

    void setDir(IsoDirections var1) {
      this.dir = var1;
   }

    void setDir(int var1) {
      this.dir = IsoDirections.fromIndex(var1);
   }

    short getDamage() {
      return this.Damage;
   }

    void setDamage(short var1) {
      this.Damage = var1;
   }

    bool isNoPicking() {
      return this.NoPicking;
   }

    void setNoPicking(bool var1) {
      this.NoPicking = var1;
   }

    bool isOutlineOnMouseover() {
      return this.OutlineOnMouseover;
   }

    void setOutlineOnMouseover(bool var1) {
      this.OutlineOnMouseover = var1;
   }

    IsoObject getRerouteMask() {
      return this.rerouteMask;
   }

    void setRerouteMask(IsoObject var1) {
      this.rerouteMask = var1;
   }

    IsoSprite getSprite() {
      return this.sprite;
   }

    void setSprite(IsoSprite var1) {
      this.sprite = var1;
      this.windRenderEffects = nullptr;
      this.checkMoveWithWind();
   }

    void setSprite(const std::string& var1) {
      this.sprite = IsoSprite.CreateSprite(IsoSpriteManager.instance);
      this.sprite.LoadFramesNoDirPageSimple(var1);
      this.tile = var1;
      this.spriteName = var1;
      this.windRenderEffects = nullptr;
      this.checkMoveWithWind();
   }

    void setSpriteFromName(const std::string& var1) {
      this.sprite = IsoSpriteManager.instance.getSprite(var1);
      this.windRenderEffects = nullptr;
      this.checkMoveWithWind();
   }

    float getTargetAlpha() {
      return this.getTargetAlpha(IsoPlayer.getPlayerIndex());
   }

    void setTargetAlpha(float var1) {
      this.setTargetAlpha(IsoPlayer.getPlayerIndex(), var1);
   }

    void setTargetAlpha(int var1, float var2) {
      this.targetAlpha[var1] = PZMath.clamp(var2, 0.0F, 1.0F);
   }

    float getTargetAlpha(int var1) {
      return this.targetAlpha[var1];
   }

    bool isAlphaAndTargetZero() {
    int var1 = IsoPlayer.getPlayerIndex();
      return this.isAlphaAndTargetZero(var1);
   }

    bool isAlphaAndTargetZero(int var1) {
      return this.isAlphaZero(var1) && this.isTargetAlphaZero(var1);
   }

    bool isAlphaZero() {
    int var1 = IsoPlayer.getPlayerIndex();
      return this.isAlphaZero(var1);
   }

    bool isAlphaZero(int var1) {
      return this.alpha[var1] <= 0.001F;
   }

    bool isTargetAlphaZero(int var1) {
      return this.targetAlpha[var1] <= 0.001F;
   }

    IsoObjectType getType() {
      return this.sprite == nullptr ? IsoObjectType.MAX : this.sprite.getType();
   }

    void setType(IsoObjectType var1) {
      if (this.sprite != nullptr) {
         this.sprite.setType(var1);
      }
   }

    void addChild(IsoObject var1) {
      if (this.Children == nullptr) {
         this.Children = new std::vector<>(4);
      }

      this.Children.push_back(var1);
   }

    void debugPrintout() {
      System.out.println(this.getClass());
      System.out.println(this.getObjectName());
   }

    void checkMoveWithWind() {
      this.checkMoveWithWind(this.sprite != nullptr && this.sprite.isBush);
   }

    void checkMoveWithWind(bool var1) {
      if (!GameServer.bServer) {
         if (this.sprite != nullptr && this.windRenderEffects == nullptr && this.sprite.moveWithWind) {
            if (this.getSquare() != nullptr) {
    IsoGridSquare var2 = this.getCell().getGridSquare(this.getSquare().x - 1, this.getSquare().y, this.getSquare().z);
               if (var2 != nullptr) {
    IsoGridSquare var3 = this.getCell().getGridSquare(var2.x, var2.y + 1, var2.z);
                  if (var3 != nullptr && !var3.isExteriorCache && var3.getWall(true) != nullptr) {
                     this.windRenderEffects = nullptr;
                     return;
                  }
               }

    IsoGridSquare var5 = this.getCell().getGridSquare(this.getSquare().x, this.getSquare().y - 1, this.getSquare().z);
               if (var5 != nullptr) {
    IsoGridSquare var4 = this.getCell().getGridSquare(var5.x + 1, var5.y, var5.z);
                  if (var4 != nullptr && !var4.isExteriorCache && var4.getWall(false) != nullptr) {
                     this.windRenderEffects = nullptr;
                     return;
                  }
               }
            }

            this.windRenderEffects = ObjectRenderEffects.getNextWindEffect(this.sprite.windType, var1);
         } else {
            if (this.windRenderEffects != nullptr && (this.sprite == nullptr || !this.sprite.moveWithWind)) {
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
         for (int var1 = 0; var1 < this.AttachedAnimSprite.size(); var1++) {
    IsoSpriteInstance var2 = this.AttachedAnimSprite.get(var1);
            IsoSpriteInstance.push_back(var2);
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

      for (int var3 = 0; var3 < 4; var3++) {
         this.setAlphaAndTarget(var3, 1.0F);
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
         for (int var4 = 0; var4 < this.secondaryContainers.size(); var4++) {
    ItemContainer var5 = this.secondaryContainers.get(var4);
            var5.Items.clear();
            var5.IncludingObsoleteItems.clear();
            var5.setParent(nullptr);
            var5.setSourceGrid(nullptr);
            var5.vehiclePart = nullptr;
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
    long var1 = 1L;
            if (this.getObjectName() != nullptr) {
               var1 = var1 * 3L + this.getObjectName().hashCode();
            }

            if (this.name != nullptr) {
               var1 = var1 * 2L + this.name.hashCode();
            }

            if (this.container != nullptr) {
               var1 = ++var1 + this.container.Items.size();

               for (int var3 = 0; var3 < this.container.Items.size(); var3++) {
                  var1 += ((InventoryItem)this.container.Items.get(var3)).getModule().hashCode()
                     + ((InventoryItem)this.container.Items.get(var3)).getType().hashCode()
                     + ((InventoryItem)this.container.Items.get(var3)).id;
               }
            }

            return var1 + this.square.getObjects().indexOf(this);
         } catch (Throwable var4) {
            DebugLog.log("ERROR: " + var4.getMessage());
    return 0L;
         }
      }
   }

    void SetName(const std::string& var1) {
      this.name = var1;
   }

    std::string getName() {
      return this.name;
   }

    void setName(const std::string& var1) {
      this.name = var1;
   }

    std::string getSpriteName() {
      return this.spriteName;
   }

    std::string getTile() {
      return this.tile;
   }

    bool isCharacter() {
      return dynamic_cast<IsoLivingCharacter*>(this) != nullptr;
   }

    bool isZombie() {
    return false;
   }

    std::string getScriptName() {
      return "none";
   }

   public void AttachAnim(
      std::string var1, std::string var2, int var3, float var4, int var5, int var6, boolean var7, int var8, boolean var9, float var10, ColorInfo var11
   ) {
      if (this.AttachedAnimSprite == nullptr) {
         this.AttachedAnimSprite = new std::vector<>(4);
      }

    IsoSprite var12 = IsoSprite.CreateSpriteUsingCache(var1, var2, var3);
      var12.TintMod.set(var11);
      var12.soffX = (short)(-var5);
      var12.soffY = (short)(-var6);
      var12.Animate = true;
      var12.Loop = var7;
      var12.DeleteWhenFinished = var9;
      var12.PlayAnim(var2);
    IsoSpriteInstance var13 = var12.def;
      var13.AnimFrameIncrease = var4;
      var13.Frame = 0.0F;
      this.AttachedAnimSprite.push_back(var13);
   }

    void AttachExistingAnim(IsoSprite var1, int var2, int var3, bool var4, int var5, bool var6, float var7, ColorInfo var8) {
      if (this.AttachedAnimSprite == nullptr) {
         this.AttachedAnimSprite = new std::vector<>(4);
      }

      var1.TintMod.r = var8.r;
      var1.TintMod.g = var8.g;
      var1.TintMod.b = var8.b;
      var1.TintMod.a = var8.a;
    int var10 = var2;
    int var11 = var3;
      var1.soffX = (short)(-var10);
      var1.soffY = (short)(-var11);
      var1.Animate = true;
      var1.Loop = var4;
      var1.DeleteWhenFinished = var6;
    IsoSpriteInstance var12 = IsoSpriteInstance.get(var1);
      this.AttachedAnimSprite.push_back(var12);
   }

    void AttachExistingAnim(IsoSprite var1, int var2, int var3, bool var4, int var5, bool var6, float var7) {
      this.AttachExistingAnim(var1, var2, var3, var4, var5, var6, var7, std::make_unique<ColorInfo>());
   }

    void DoTooltip(ObjectTooltip var1) {
   }

    void DoSpecialTooltip(ObjectTooltip var1, IsoGridSquare var2) {
      if (this.haveSpecialTooltip()) {
         var1.setHeight(0.0);
         LuaEventManager.triggerEvent("DoSpecialTooltip", var1, var2);
         if (var1.getHeight() == 0.0) {
            var1.hide();
         }
      }
   }

    ItemContainer getItemContainer() {
      return this.container;
   }

    float getOffsetX() {
      return this.offsetX;
   }

    void setOffsetX(float var1) {
      this.offsetX = var1;
   }

    float getOffsetY() {
      return this.offsetY;
   }

    void setOffsetY(float var1) {
      this.offsetY = var1;
   }

    IsoObject getRerouteMaskObject() {
      return this.rerouteMask;
   }

    bool HasTooltip() {
    return false;
   }

    bool getUsesExternalWaterSource() {
      return this.usesExternalWaterSource;
   }

    void setUsesExternalWaterSource(bool var1) {
      this.usesExternalWaterSource = var1;
   }

    bool hasExternalWaterSource() {
      return this.externalWaterSource != nullptr;
   }

    void doFindExternalWaterSource() {
      this.externalWaterSource = FindExternalWaterSource(this.getSquare());
   }

    static IsoObject FindExternalWaterSource(IsoGridSquare var0) {
    return var0 = = nullptr ? nullptr : FindExternalWaterSource(var0.getX(), var0.getY(), var0.getZ());
   }

    static IsoObject FindExternalWaterSource(int var0, int var1, int var2) {
    IsoGridSquare var3 = IsoWorld.instance.CurrentCell.getGridSquare(var0, var1, var2 + 1);
    IsoObject var4 = nullptr;
    IsoObject var5 = FindWaterSourceOnSquare(var3);
      if (var5 != nullptr) {
         if (var5.hasWater()) {
    return var5;
         }

         var4 = var5;
      }

      for (int var6 = -1; var6 <= 1; var6++) {
         for (int var7 = -1; var7 <= 1; var7++) {
            if (var7 != 0 || var6 != 0) {
               var3 = IsoWorld.instance.CurrentCell.getGridSquare(var0 + var7, var1 + var6, var2 + 1);
               var5 = FindWaterSourceOnSquare(var3);
               if (var5 != nullptr) {
                  if (var5.hasWater()) {
    return var5;
                  }

                  if (var4 == nullptr) {
                     var4 = var5;
                  }
               }
            }
         }
      }

    return var4;
   }

    static IsoObject FindWaterSourceOnSquare(IsoGridSquare var0) {
      if (var0 == nullptr) {
    return nullptr;
      } else {
    PZArrayList var1 = var0.getObjects();

         for (int var2 = 0; var2 < var1.size(); var2++) {
    IsoObject var3 = (IsoObject)var1.get(var2);
            if (dynamic_cast<IsoThumpable*>(var3) != nullptr
               && (var3.getSprite() == nullptr || !var3.getSprite().solidfloor)
               && !var3.getUsesExternalWaterSource()
               && var3.getWaterMax() > 0) {
    return var3;
            }
         }

    return nullptr;
      }
   }

    int getPipedFuelAmount() {
      if (this.sprite == nullptr) {
    return 0;
      } else {
    double var1 = 0.0;
         if (this.hasModData() && !this.getModData().empty()) {
    void* var3 = this.getModData().rawget("fuelAmount");
            if (var3 != nullptr) {
               var1 = (double)var3;
            }
         }

         if (this.sprite.getProperties().Is("fuelAmount")) {
            if (SandboxOptions.instance.FuelStationGas.getValue() == 7) {
    return 1000;
            }

            if (var1 == 0.0
               && (SandboxOptions.getInstance().AllowExteriorGenerator.getValue() && this.getSquare().haveElectricity() || IsoWorld.instance.isHydroPowerOn())) {
    float var6 = 0.8F;
    float var4 = 1.0F;
               switch (SandboxOptions.getInstance().FuelStationGas.getValue()) {
                  case 1:
                     var4 = 0.0F;
                     var6 = 0.0F;
                     break;
                  case 2:
                     var6 = 0.0F;
                     var4 = 0.01F;
                     break;
                  case 3:
                     var6 = 0.01F;
                     var4 = 0.1F;
                     break;
                  case 4:
                     var6 = 0.1F;
                     var4 = 0.5F;
                     break;
                  case 5:
                     var6 = 0.5F;
                     var4 = 0.7F;
                     break;
                  case 6:
                     var6 = 0.7F;
                     var4 = 0.8F;
                     break;
                  case 7:
                     var6 = 0.8F;
                     var4 = 0.9F;
                     break;
                  case 8:
                     var4 = 1.0F;
                     var6 = 1.0F;
               }

               var1 = (int)Rand.Next(
                  int.parseInt(this.sprite.getProperties().Val("fuelAmount")) * var6,
                  int.parseInt(this.sprite.getProperties().Val("fuelAmount")) * var4
               );
               this.getModData().rawset("fuelAmount", var1);
               this.transmitModData();
               return (int)var1;
            }
         }

         return (int)var1;
      }
   }

    void setPipedFuelAmount(int var1) {
      var1 = Math.max(0, var1);
    int var2 = this.getPipedFuelAmount();
      if (var1 != var2) {
         if (var1 == 0 && var2 != 0) {
            var1 = -1;
         }

         this.getModData().rawset("fuelAmount", (double)var1);
         this.transmitModData();
      }
   }

    bool isWaterInfinite() {
      if (this.sprite == nullptr) {
    return false;
      } else if (this.square != nullptr && this.square.getRoom() != nullptr) {
         if (!this.sprite.getProperties().Is(IsoFlagType.waterPiped)) {
    return false;
         } else {
            return GameTime.getInstance().getNightsSurvived() >= SandboxOptions.instance.getWaterShutModifier()
               ? false
               : !this.hasModData()
                  || !(this.getModData().rawget("canBeWaterPiped") instanceof bool)
                  || !(bool)this.getModData().rawget("canBeWaterPiped");
         }
      } else {
    return false;
      }
   }

    IsoObject checkExternalWaterSource() {
      if (!this.usesExternalWaterSource) {
    return nullptr;
      } else {
         if (this.externalWaterSource == nullptr || !this.externalWaterSource.hasWater()) {
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
    IsoObject var2 = this.checkExternalWaterSource();
    return var2 = = nullptr ? 0 : var2.getWaterAmount();
         }
      } else if (this.isWaterInfinite()) {
    return 10000;
      } else {
         if (this.hasModData() && !this.getModData().empty()) {
    void* var1 = this.getModData().rawget("waterAmount");
            if (var1 != nullptr) {
               if (dynamic_cast<double*>(var1) != nullptr) {
                  return (int)Math.max(0.0, (double)var1);
               }

               if (dynamic_cast<std*>(var1) != nullptr::string) {
                  return Math.max(0, int.parseInt((std::string)var1));
               }

    return 0;
            }
         }

         if (this.square != nullptr
            && !this.square.getProperties().Is(IsoFlagType.water)
            && this.sprite != nullptr
            && this.sprite.getProperties().Is(IsoFlagType.solidfloor)
            && this.square.getPuddlesInGround() > 0.09F) {
            return (int)(this.square.getPuddlesInGround() * 10.0F);
         } else {
            return !this.sprite.Properties.Is("waterAmount") ? 0 : int.parseInt(this.sprite.getProperties().Val("waterAmount"));
         }
      }
   }

    void setWaterAmount(int var1) {
      if (this.usesExternalWaterSource) {
         if (!this.isWaterInfinite()) {
    IsoObject var5 = this.checkExternalWaterSource();
            if (var5 != nullptr) {
               var5.setWaterAmount(var1);
            }
         }
      } else {
         var1 = Math.max(0, var1);
    int var2 = this.getWaterAmount();
         if (var1 != var2) {
    bool var3 = true;
            if (this.hasModData() && !this.getModData().empty()) {
               var3 = this.getModData().rawget("waterAmount") == nullptr;
            }

            if (var3) {
               this.getModData().rawset("waterMax", (double)var2);
            }

            this.getModData().rawset("waterAmount", (double)var1);
            if (var1 <= 0) {
               this.setTaintedWater(false);
            }

            LuaEventManager.triggerEvent("OnWaterAmountChange", this, var2);
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
    IsoObject var2 = this.checkExternalWaterSource();
            return var2 != nullptr ? var2.getWaterMax() : 0;
         }
      } else if (this.isWaterInfinite()) {
    return 10000;
      } else {
         if (this.hasModData() && !this.getModData().empty()) {
    void* var1 = this.getModData().rawget("waterMax");
            if (var1 != nullptr) {
               if (dynamic_cast<double*>(var1) != nullptr) {
                  return (int)Math.max(0.0, (double)var1);
               }

               if (dynamic_cast<std*>(var1) != nullptr::string) {
                  return Math.max(0, int.parseInt((std::string)var1));
               }

    return 0;
            }
         }

         if (this.square != nullptr
            && !this.square.getProperties().Is(IsoFlagType.water)
            && this.sprite != nullptr
            && this.sprite.getProperties().Is(IsoFlagType.solidfloor)
            && this.square.getPuddlesInGround() > 0.09F) {
            return (int)(this.square.getPuddlesInGround() * 10.0F);
         } else if (this.sprite.Properties.Is("waterMaxAmount")) {
            return int.parseInt(this.sprite.getProperties().Val("waterMaxAmount"));
         } else {
            return this.sprite.Properties.Is("waterAmount") ? int.parseInt(this.sprite.getProperties().Val("waterAmount")) : 0;
         }
      }
   }

    int useWater(int var1) {
      if (this.sprite == nullptr) {
    return 0;
      } else {
    int var2 = this.getWaterAmount();
    int var3 = 0;
         if (var2 >= var1) {
            var3 = var1;
         } else {
            var3 = var2;
         }

         if (this.square != nullptr && this.sprite != nullptr && this.sprite.getProperties().Is(IsoFlagType.solidfloor) && this.square.getPuddlesInGround() > 0.09F) {
    return var3;
         } else {
            if (!this.usesExternalWaterSource) {
               if (this.sprite.getProperties().Is(IsoFlagType.water)) {
    return var3;
               }

               if (this.isWaterInfinite()) {
    return var3;
               }
            }

            this.setWaterAmount(var2 - var3);
    return var3;
         }
      }
   }

    bool hasWater() {
      return this.square != nullptr && this.sprite != nullptr && this.sprite.getProperties().Is(IsoFlagType.solidfloor) && this.square.getPuddlesInGround() > 0.09F
         ? true
         : this.getWaterAmount() > 0;
   }

    bool isTaintedWater() {
      if (this.square != nullptr && this.sprite != nullptr && this.sprite.getProperties().Is(IsoFlagType.solidfloor) && this.square.getPuddlesInGround() > 0.09F) {
    return true;
      } else {
         if (this.hasModData()) {
    void* var1 = this.getModData().rawget("taintedWater");
            if (dynamic_cast<bool*>(var1) != nullptr) {
               return (bool)var1;
            }
         }

         return this.sprite != nullptr && this.sprite.getProperties().Is(IsoFlagType.taintedWater);
      }
   }

    void setTaintedWater(bool var1) {
      this.getModData().rawset("taintedWater", var1);
   }

    InventoryItem replaceItem(InventoryItem var1) {
    std::string var2 = nullptr;
    InventoryItem var3 = nullptr;
      if (var1 != nullptr) {
         if (var1.hasReplaceType(this.getObjectName())) {
            var2 = var1.getReplaceType(this.getObjectName());
         } else if (var1.hasReplaceType("WaterSource")) {
            var2 = var1.getReplaceType("WaterSource");
         }
      }

      if (var2 != nullptr) {
         var3 = var1.getContainer().AddItem(InventoryItemFactory.CreateItem(var2));
         if (var1.getContainer().getParent() instanceof IsoGameCharacter) {
    IsoGameCharacter var4 = (IsoGameCharacter)var1.getContainer().getParent();
            if (var4.getPrimaryHandItem() == var1) {
               var4.setPrimaryHandItem(var3);
            }

            if (var4.getSecondaryHandItem() == var1) {
               var4.setSecondaryHandItem(var3);
            }
         }

         var1.getContainer().Remove(var1);
      }

    return var3;
   }

    void useItemOn(InventoryItem var1) {
    std::string var2 = nullptr;
      if (var1 != nullptr) {
         if (var1.hasReplaceType(this.getObjectName())) {
            var2 = var1.getReplaceType(this.getObjectName());
         } else if (var1.hasReplaceType("WaterSource")) {
            var2 = var1.getReplaceType("WaterSource");
            this.useWater(10);
         }
      }

      if (var2 != nullptr) {
    InventoryItem var3 = var1.getContainer().AddItem(InventoryItemFactory.CreateItem(var2));
         var1.setUses(var1.getUses() - 1);
         if (var1.getUses() <= 0 && var1.getContainer() != nullptr) {
            var1.getContainer().Items.remove(var1);
         }
      }
   }

    float getX() {
      return this.square.getX();
   }

    float getY() {
      return this.square.getY();
   }

    float getZ() {
      return this.square.getZ();
   }

    bool onMouseLeftClick(int var1, int var2) {
    return false;
   }

    PropertyContainer getProperties() {
      return this.sprite == nullptr ? nullptr : this.sprite.getProperties();
   }

    void RemoveAttachedAnims() {
      if (this.AttachedAnimSprite != nullptr) {
         for (int var1 = 0; var1 < this.AttachedAnimSprite.size(); var1++) {
            this.AttachedAnimSprite.get(var1).Dispose();
         }

         this.AttachedAnimSprite.clear();
      }
   }

    void RemoveAttachedAnim(int var1) {
      if (this.AttachedAnimSprite != nullptr) {
         if (var1 >= 0 && var1 < this.AttachedAnimSprite.size()) {
            this.AttachedAnimSprite.get(var1).Dispose();
            this.AttachedAnimSprite.remove(var1);
         }
      }
   }

    Vector2 getFacingPosition(Vector2 var1) {
      if (this.square == nullptr) {
         return var1.set(0.0F, 0.0F);
      } else {
    PropertyContainer var2 = this.getProperties();
         if (var2 != nullptr) {
            if (this.getType() == IsoObjectType.wall) {
               if (var2.Is(IsoFlagType.collideN) && var2.Is(IsoFlagType.collideW)) {
                  return var1.set(this.getX(), this.getY());
               }

               if (var2.Is(IsoFlagType.collideN)) {
                  return var1.set(this.getX() + 0.5F, this.getY());
               }

               if (var2.Is(IsoFlagType.collideW)) {
                  return var1.set(this.getX(), this.getY() + 0.5F);
               }

               if (var2.Is(IsoFlagType.DoorWallN)) {
                  return var1.set(this.getX() + 0.5F, this.getY());
               }

               if (var2.Is(IsoFlagType.DoorWallW)) {
                  return var1.set(this.getX(), this.getY() + 0.5F);
               }
            } else {
               if (var2.Is(IsoFlagType.attachedN)) {
                  return var1.set(this.getX() + 0.5F, this.getY());
               }

               if (var2.Is(IsoFlagType.attachedS)) {
                  return var1.set(this.getX() + 0.5F, this.getY() + 1.0F);
               }

               if (var2.Is(IsoFlagType.attachedW)) {
                  return var1.set(this.getX(), this.getY() + 0.5F);
               }

               if (var2.Is(IsoFlagType.attachedE)) {
                  return var1.set(this.getX() + 1.0F, this.getY() + 0.5F);
               }
            }
         }

         return var1.set(this.getX() + 0.5F, this.getY() + 0.5F);
      }
   }

    Vector2 getFacingPositionAlt(Vector2 var1) {
      return this.getFacingPosition(var1);
   }

    float getRenderYOffset() {
      return this.renderYOffset;
   }

    void setRenderYOffset(float var1) {
      this.renderYOffset = var1;
      this.sx = 0.0F;
   }

    bool isTableSurface() {
    PropertyContainer var1 = this.getProperties();
      return var1 != nullptr ? var1.isTable() : false;
   }

    bool isTableTopObject() {
    PropertyContainer var1 = this.getProperties();
      return var1 != nullptr ? var1.isTableTop() : false;
   }

    bool getIsSurfaceNormalOffset() {
    PropertyContainer var1 = this.getProperties();
      return var1 != nullptr ? var1.isSurfaceOffset() : false;
   }

    float getSurfaceNormalOffset() {
    float var1 = 0.0F;
    PropertyContainer var2 = this.getProperties();
      if (var2.isSurfaceOffset()) {
         var1 = var2.getSurface();
      }

    return var1;
   }

    float getSurfaceOffsetNoTable() {
    float var1 = 0.0F;
    int var2 = 0;
    PropertyContainer var3 = this.getProperties();
      if (var3 != nullptr) {
         var1 = var3.getSurface();
         var2 = var3.getItemHeight();
      }

      return var1 + this.getRenderYOffset() + var2;
   }

    float getSurfaceOffset() {
    float var1 = 0.0F;
      if (this.isTableSurface()) {
    PropertyContainer var2 = this.getProperties();
         if (var2 != nullptr) {
            var1 = var2.getSurface();
         }
      }

    return var1;
   }

    bool isStairsNorth() {
      return this.getType() == IsoObjectType.stairsTN || this.getType() == IsoObjectType.stairsMN || this.getType() == IsoObjectType.stairsBN;
   }

    bool isStairsWest() {
      return this.getType() == IsoObjectType.stairsTW || this.getType() == IsoObjectType.stairsMW || this.getType() == IsoObjectType.stairsBW;
   }

    bool isStairsObject() {
      return this.isStairsNorth() || this.isStairsWest();
   }

    bool isHoppable() {
      return this.sprite != nullptr && (this.sprite.getProperties().Is(IsoFlagType.HoppableN) || this.sprite.getProperties().Is(IsoFlagType.HoppableW));
   }

    bool isNorthHoppable() {
      return this.sprite != nullptr && this.isHoppable() && this.sprite.getProperties().Is(IsoFlagType.HoppableN);
   }

    bool haveSheetRope() {
      return IsoWindow.isTopOfSheetRopeHere(this.square, this.isNorthHoppable());
   }

    int countAddSheetRope() {
      return IsoWindow.countAddSheetRope(this.square, this.isNorthHoppable());
   }

    bool canAddSheetRope() {
      return IsoWindow.canAddSheetRope(this.square, this.isNorthHoppable());
   }

    bool addSheetRope(IsoPlayer var1, const std::string& var2) {
      return !this.canAddSheetRope() ? false : IsoWindow.addSheetRope(var1, this.square, this.isNorthHoppable(), var2);
   }

    bool removeSheetRope(IsoPlayer var1) {
      return this.haveSheetRope() ? IsoWindow.removeSheetRope(var1, this.square, this.isNorthHoppable()) : false;
   }

    void render(float var1, float var2, float var3, ColorInfo var4, bool var5, bool var6, Shader var7) {
      if (!this.isSpriteInvisible()) {
         this.prepareToRender(var4);
    int var8 = IsoCamera.frameState.playerIndex;
         if (this.shouldDrawMainSprite()) {
            this.sprite.render(this, var1, var2, var3, this.dir, this.offsetX, this.offsetY + this.renderYOffset * Core.TileScale, stCol, !this.isBlink());
            if (this.isOutlineHighlight(var8) && !this.isOutlineHlAttached(var8) && OutlineShader.instance.StartShader()) {
    int var9 = this.outlineHighlightCol[var8];
    float var10 = Color.getRedChannelFromABGR(var9);
    float var11 = Color.getGreenChannelFromABGR(var9);
    float var12 = Color.getBlueChannelFromABGR(var9);
               OutlineShader.instance.setOutlineColor(var10, var11, var12, this.isOutlineHlBlink(var8) ? Core.blinkAlpha : 1.0F);
    Texture var13 = this.sprite.getTextureForCurrentFrame(this.dir);
               if (var13 != nullptr) {
                  OutlineShader.instance.setStepSize(this.outlineThickness, var13.getWidth(), var13.getHeight());
               }

               this.sprite.render(this, var1, var2, var3, this.dir, this.offsetX, this.offsetY + this.renderYOffset * Core.TileScale, stCol, !this.isBlink());
               IndieGL.EndShader();
            }
         }

         this.renderAttachedAndOverlaySpritesInternal(var1, var2, var3, var4, var5, var6, var7, nullptr);
         if (this.isOutlineHighlight(var8) && this.isOutlineHlAttached(var8) && OutlineShader.instance.StartShader()) {
    int var14 = this.outlineHighlightCol[var8];
    float var15 = Color.getRedChannelFromABGR(var14);
    float var16 = Color.getGreenChannelFromABGR(var14);
    float var17 = Color.getBlueChannelFromABGR(var14);
            OutlineShader.instance.setOutlineColor(var15, var16, var17, this.isOutlineHlBlink(var8) ? Core.blinkAlpha : 1.0F);
    Texture var18 = this.sprite.getTextureForCurrentFrame(this.dir);
            if (var18 != nullptr) {
               OutlineShader.instance.setStepSize(this.outlineThickness, var18.getWidth(), var18.getHeight());
            }

            if (this.shouldDrawMainSprite()) {
               this.sprite.render(this, var1, var2, var3, this.dir, this.offsetX, this.offsetY + this.renderYOffset * Core.TileScale, stCol, !this.isBlink());
            }

            this.renderAttachedAndOverlaySpritesInternal(var1, var2, var3, var4, var5, var6, var7, nullptr);
            IndieGL.EndShader();
         }

         if (!this.bAlphaForced && this.isUpdateAlphaDuringRender()) {
            this.updateAlpha(var8);
         }

         this.debugRenderItemHeight(var1, var2, var3);
         this.debugRenderSurface(var1, var2, var3);
      }
   }

    void debugRenderItemHeight(float var1, float var2, float var3) {
      if (DebugOptions.instance.IsoSprite.ItemHeight.getValue()) {
         if (this.square != nullptr && IsoCamera.frameState.CamCharacterSquare != nullptr && this.square.z == IsoCamera.frameState.CamCharacterSquare.z) {
    int var4 = this.sprite.getProperties().getItemHeight();
            if (var4 > 0) {
    int var5 = 0;
               if (this.sprite != nullptr && this.sprite.getProperties().getSurface() > 0 && this.sprite.getProperties().isSurfaceOffset()) {
                  var5 = this.sprite.getProperties().getSurface();
               }

               LineDrawer.addRectYOffset(var1, var2, var3, 1.0F, 1.0F, (int)this.getRenderYOffset() + var5 + var4, 0.66F, 0.66F, 0.66F);
            }
         }
      }
   }

    void debugRenderSurface(float var1, float var2, float var3) {
      if (DebugOptions.instance.IsoSprite.Surface.getValue()) {
         if (this.square != nullptr && IsoCamera.frameState.CamCharacterSquare != nullptr && this.square.z == IsoCamera.frameState.CamCharacterSquare.z) {
    int var4 = 0;
            if (this.sprite != nullptr && this.sprite.getProperties().getSurface() > 0 && !this.sprite.getProperties().isSurfaceOffset()) {
               var4 = this.sprite.getProperties().getSurface();
            }

            if (var4 > 0) {
               LineDrawer.addRectYOffset(var1, var2, var3, 1.0F, 1.0F, (int)this.getRenderYOffset() + var4, 1.0F, 1.0F, 1.0F);
            }
         }
      }
   }

   public void renderFloorTile(
      float var1, float var2, float var3, ColorInfo var4, boolean var5, boolean var6, Shader var7, Consumer<TextureDraw> var8, Consumer<TextureDraw> var9
   ) {
      if (!this.isSpriteInvisible()) {
         this.prepareToRender(var4);
    FloorShaper var10 = (FloorShaper)Type.tryCastTo(var8, FloorShaper.class);
    FloorShaper var11 = (FloorShaper)Type.tryCastTo(var9, FloorShaper.class);
         if ((var10 != nullptr || var11 != nullptr) && this.isHighlighted() && this.getHighlightColor() != nullptr) {
    ColorInfo var12 = this.getHighlightColor();
    float var13 = var12.a * (this.isBlink() ? Core.blinkAlpha : 1.0F);
    int var14 = Color.colorToABGR(var12.r, var12.g, var12.b, var13);
            if (var10 != nullptr) {
               var10.setTintColor(var14);
            }

            if (var11 != nullptr) {
               var11.setTintColor(var14);
            }
         }

         if (this.shouldDrawMainSprite()) {
            IndieGL.shaderSetValue(var7, "floorLayer", 0);
            this.sprite
               .render(this, var1, var2, var3, this.dir, this.offsetX, this.offsetY + this.renderYOffset * Core.TileScale, stCol, !this.isBlink(), var8);
         }

         this.renderAttachedAndOverlaySpritesInternal(var1, var2, var3, var4, var5, var6, var7, var9);
         if (var10 != nullptr) {
            var10.setTintColor(0);
         }

         if (var11 != nullptr) {
            var11.setTintColor(0);
         }
      }
   }

    void renderWallTile(float var1, float var2, float var3, ColorInfo var4, bool var5, bool var6, Shader var7, Consumer<TextureDraw> var8) {
      if (!this.isSpriteInvisible()) {
         this.renderWallTileOnly(var1, var2, var3, var4, var7, var8);
         this.renderAttachedAndOverlaySpritesInternal(var1, var2, var3, var4, var5, var6, var7, var8);
    int var9 = IsoCamera.frameState.playerIndex;
         if (this.isOutlineHighlight(var9) && !this.isOutlineHlAttached(var9) && OutlineShader.instance.StartShader()) {
    int var10 = this.outlineHighlightCol[var9];
    float var11 = Color.getRedChannelFromABGR(var10);
    float var12 = Color.getGreenChannelFromABGR(var10);
    float var13 = Color.getBlueChannelFromABGR(var10);
            OutlineShader.instance.setOutlineColor(var11, var12, var13, this.isOutlineHlBlink(var9) ? Core.blinkAlpha : 1.0F);
    Texture var14 = this.sprite.getTextureForCurrentFrame(this.dir);
            if (var14 != nullptr) {
               OutlineShader.instance.setStepSize(this.outlineThickness, var14.getWidth(), var14.getHeight());
            }

            this.sprite.render(this, var1, var2, var3, this.dir, this.offsetX, this.offsetY + this.renderYOffset * Core.TileScale, stCol, !this.isBlink());
            IndieGL.EndShader();
         }
      }
   }

    void renderWallTileOnly(float var1, float var2, float var3, ColorInfo var4, Shader var5, Consumer<TextureDraw> var6) {
      if (!this.isSpriteInvisible()) {
         this.prepareToRender(var4);
    WallShaper var7 = (WallShaper)Type.tryCastTo(var6, WallShaper.class);
         if (var7 != nullptr && this.isHighlighted() && this.getHighlightColor() != nullptr) {
    ColorInfo var8 = this.getHighlightColor();
    float var9 = var8.a * (this.isBlink() ? Core.blinkAlpha : 1.0F);
    int var10 = Color.colorToABGR(var8.r, var8.g, var8.b, var9);
            var7.setTintColor(var10);
         }

         if (this.shouldDrawMainSprite()) {
            IndieGL.pushShader(var5);
            this.sprite
               .render(this, var1, var2, var3, this.dir, this.offsetX, this.offsetY + this.renderYOffset * Core.TileScale, stCol, !this.isBlink(), var6);
            IndieGL.popShader(var5);
         }

         if (var7 != nullptr) {
            var7.setTintColor(0);
         }
      }
   }

    bool shouldDrawMainSprite() {
      return this.sprite == nullptr ? false : DebugOptions.instance.Terrain.RenderTiles.RenderSprites.getValue();
   }

   public void renderAttachedAndOverlaySprites(
      float var1, float var2, float var3, ColorInfo var4, boolean var5, boolean var6, Shader var7, Consumer<TextureDraw> var8
   ) {
      if (!this.isSpriteInvisible()) {
         this.renderAttachedAndOverlaySpritesInternal(var1, var2, var3, var4, var5, var6, var7, var8);
      }
   }

   private void renderAttachedAndOverlaySpritesInternal(
      float var1, float var2, float var3, ColorInfo var4, boolean var5, boolean var6, Shader var7, Consumer<TextureDraw> var8
   ) {
      if (this.isHighlighted()) {
         var4 = stCol;
      }

      this.renderOverlaySprites(var1, var2, var3, var4);
      if (var5) {
         this.renderAttachedSprites(var1, var2, var3, var4, var6, var7, var8);
      }
   }

    void prepareToRender(ColorInfo var1) {
      stCol.set(var1);
      if (this.isHighlighted()) {
         stCol.set(this.getHighlightColor());
         if (this.isBlink()) {
            stCol.a = Core.blinkAlpha;
         } else {
            stCol.a = 1.0F;
         }

         stCol.r = var1.r * (1.0F - stCol.a) + this.getHighlightColor().r * stCol.a;
         stCol.g = var1.g * (1.0F - stCol.a) + this.getHighlightColor().g * stCol.a;
         stCol.b = var1.b * (1.0F - stCol.a) + this.getHighlightColor().b * stCol.a;
         stCol.a = var1.a;
      }

      if (this.customColor != nullptr) {
    float var2 = this.square != nullptr ? this.square.getDarkMulti(IsoPlayer.getPlayerIndex()) : 1.0F;
         if (this.isHighlighted()) {
            stCol.r = stCol.r * (this.customColor.r * var2);
            stCol.g = stCol.g * (this.customColor.g * var2);
            stCol.b = stCol.b * (this.customColor.b * var2);
         } else {
            stCol.r = this.customColor.r * var2;
            stCol.g = this.customColor.g * var2;
            stCol.b = this.customColor.b * var2;
         }
      }

      if (this.sprite != nullptr && this.sprite.forceAmbient) {
    float var13 = rmod * this.tintr;
    float var3 = gmod * this.tintg;
    float var4 = bmod * this.tintb;
         if (!this.isHighlighted()) {
            stCol.r = RenderSettings.getInstance().getAmbientForPlayer(IsoPlayer.getPlayerIndex()) * var13;
            stCol.g = RenderSettings.getInstance().getAmbientForPlayer(IsoPlayer.getPlayerIndex()) * var3;
            stCol.b = RenderSettings.getInstance().getAmbientForPlayer(IsoPlayer.getPlayerIndex()) * var4;
         }
      }

    int var14 = IsoPlayer.getPlayerIndex();
    float var15 = IsoCamera.frameState.CamCharacterX;
    float var16 = IsoCamera.frameState.CamCharacterY;
    float var5 = IsoCamera.frameState.CamCharacterZ;
      if (IsoWorld.instance.CurrentCell.IsPlayerWindowPeeking(var14)) {
    IsoPlayer var6 = IsoPlayer.players[var14];
    IsoDirections var7 = IsoDirections.fromAngle(var6.getForwardDirection());
         if (var7 == IsoDirections.N || var7 == IsoDirections.NW) {
            var16 = (float)(var16 - 1.0);
         }

         if (var7 == IsoDirections.W || var7 == IsoDirections.NW) {
            var15 = (float)(var15 - 1.0);
         }
      }

      if (this == IsoCamera.CamCharacter) {
         this.setAlphaAndTarget(var14, 1.0F);
      }

      lastRenderedRendered = lastRendered;
      lastRendered = this;
      if (this.sprite != nullptr && !(dynamic_cast<IsoPhysicsObject*>(this) != nullptr) && IsoCamera.CamCharacter != nullptr) {
    bool var17 = dynamic_cast<IsoWindow*>(this) != nullptr || this.sprite.getType() == IsoObjectType.doorW || this.sprite.getType() == IsoObjectType.doorN;
         if (this.sprite.getProperties().Is("GarageDoor")) {
            var17 = false;
         }

         if (!var17 && (this.square.getX() > var15 || this.square.getY() > var16) && (int)var5 <= this.square.getZ()) {
    bool var18 = false;
    float var8 = 0.2F;
    bool var9 = (this.sprite.cutW || this.sprite.getProperties().Is(IsoFlagType.doorW)) && this.square.getX() > var15;
    bool var10 = (this.sprite.cutN || this.sprite.getProperties().Is(IsoFlagType.doorN)) && this.square.getY() > var16;
            if (var9 && this.square.getProperties().Is(IsoFlagType.WallSE) && this.square.getY() <= var16) {
               var9 = false;
            }

            if (!var9 && !var10) {
               boolean var11 = this.getType() == IsoObjectType.WestRoofB
                  || this.getType() == IsoObjectType.WestRoofM
                  || this.getType() == IsoObjectType.WestRoofT;
    bool var12 = var11 && (int)var5 == this.square.getZ() && this.square.getBuilding() == nullptr;
               if (var12 && IsoWorld.instance.CurrentCell.CanBuildingSquareOccludePlayer(this.square, var14)) {
                  var18 = true;
                  var8 = 0.05F;
               }
            } else {
               var18 = true;
            }

            if (this.sprite.getProperties().Is(IsoFlagType.halfheight)) {
               var18 = false;
            }

            if (var18) {
               if (var10 && this.sprite.getProperties().Is(IsoFlagType.HoppableN)) {
                  var8 = 0.25F;
               }

               if (var9 && this.sprite.getProperties().Is(IsoFlagType.HoppableW)) {
                  var8 = 0.25F;
               }

               if (this.bAlphaForced) {
                  if (this.getTargetAlpha(var14) == 1.0F) {
                     this.setAlphaAndTarget(var14, 0.99F);
                  }
               } else {
                  this.setTargetAlpha(var14, var8);
               }

               LowLightingQualityHack = true;
               this.NoPicking = this.rerouteMask == nullptr
                  && !(dynamic_cast<IsoThumpable*>(this) != nullptr)
                  && !IsoWindowFrame.isWindowFrame(this)
                  && !this.sprite.getProperties().Is(IsoFlagType.doorN)
                  && !this.sprite.getProperties().Is(IsoFlagType.doorW)
                  && !this.sprite.getProperties().Is(IsoFlagType.HoppableN)
                  && !this.sprite.getProperties().Is(IsoFlagType.HoppableW);
            } else {
               this.NoPicking = false;
            }
         } else {
            this.NoPicking = false;
         }
      }

      if (this == IsoCamera.CamCharacter) {
         this.setTargetAlpha(var14, 1.0F);
      }
   }

    float getAlphaUpdateRateDiv() {
      return 14.0F;
   }

    float getAlphaUpdateRateMul() {
    float var1 = 0.25F;
      if (this.square != nullptr && this.square.room != nullptr) {
         var1 *= 2.0F;
      }

    return var1;
   }

    bool isUpdateAlphaEnabled() {
    return true;
   }

    bool isUpdateAlphaDuringRender() {
    return true;
   }

    void updateAlpha() {
      if (!GameServer.bServer) {
         for (int var1 = 0; var1 < IsoPlayer.numPlayers; var1++) {
            if (IsoPlayer.players[var1] != nullptr) {
               this.updateAlpha(var1);
            }
         }
      }
   }

    void updateAlpha(int var1) {
      if (!GameServer.bServer) {
    float var2 = this.getAlphaUpdateRateMul();
    float var3 = this.getAlphaUpdateRateDiv();
         this.updateAlpha(var1, var2, var3);
      }
   }

    void updateAlpha(int var1, float var2, float var3) {
      if (this.isUpdateAlphaEnabled()) {
         if (!DebugOptions.instance.char.Debug.UpdateAlpha.getValue()) {
            this.setAlphaToTarget(var1);
         } else {
            if (this.bNeverDoneAlpha) {
               this.setAlpha(0.0F);
               this.bNeverDoneAlpha = false;
            }

            if (DebugOptions.instance.char.Debug.UpdateAlphaEighthSpeed.getValue()) {
               var2 /= 8.0F;
               var3 *= 8.0F;
            }

    float var4 = GameTime.getInstance().getMultiplier();
    float var5 = var4 * 0.28F;
    float var6 = this.getAlpha(var1);
    float var7 = this.targetAlpha[var1];
            if (var6 < var7) {
               var6 += var5 * var2;
               if (var6 > var7) {
                  var6 = var7;
               }
            } else if (var6 > var7) {
               var6 -= var5 / var3;
               if (var6 < var7) {
                  var6 = var7;
               }
            }

            this.setAlpha(var1, var6);
         }
      }
   }

    void renderOverlaySprites(float var1, float var2, float var3, ColorInfo var4) {
      if (this.getOverlaySprite() != nullptr && DebugOptions.instance.Terrain.RenderTiles.OverlaySprites.getValue()) {
    ColorInfo var5 = stCol2;
         var5.set(var4);
         if (this.overlaySpriteColor != nullptr) {
            var5.set(this.overlaySpriteColor);
         }

         if (var5.a != 1.0F && this.overlaySprite.def != nullptr && this.overlaySprite.def.bCopyTargetAlpha) {
    int var6 = IsoPlayer.getPlayerIndex();
    float var7 = this.alpha[var6];
            this.alpha[var6] = this.alpha[var6] * var5.a;
            this.getOverlaySprite().render(this, var1, var2, var3, this.dir, this.offsetX, this.offsetY + this.renderYOffset * Core.TileScale, var5, true);
            this.alpha[var6] = var7;
         } else {
            this.getOverlaySprite().render(this, var1, var2, var3, this.dir, this.offsetX, this.offsetY + this.renderYOffset * Core.TileScale, var5, true);
         }
      }
   }

    void renderAttachedSprites(float var1, float var2, float var3, ColorInfo var4, bool var5, Shader var6, Consumer<TextureDraw> var7) {
      if (this.AttachedAnimSprite != nullptr && DebugOptions.instance.Terrain.RenderTiles.AttachedAnimSprites.getValue()) {
    int var8 = this.AttachedAnimSprite.size();

         for (int var9 = 0; var9 < var8; var9++) {
    IsoSpriteInstance var10 = this.AttachedAnimSprite.get(var9);
            if (!var5 || !var10.parentSprite.Properties.Is(IsoFlagType.NoWallLighting)) {
    float var11 = var4.a;
               IndieGL.shaderSetValue(var6, "floorLayer", 1);
               var4.a = var10.alpha;
    void* var12 = var7;
               if (var7 == WallShaperW.instance) {
                  if (var10.parentSprite.getProperties().Is(IsoFlagType.attachedN)) {
    Texture var13 = var10.parentSprite.getTextureForCurrentFrame(this.dir);
                     if (var13 != nullptr && var13.getWidth() < 32 * Core.TileScale) {
                        continue;
                     }
                  }

                  if (var10.parentSprite.getProperties().Is(IsoFlagType.attachedW)) {
                     var12 = WallShaperWhole.instance;
                  }
               } else if (var7 == WallShaperN.instance) {
                  if (var10.parentSprite.getProperties().Is(IsoFlagType.attachedW)) {
                     continue;
                  }

                  if (var10.parentSprite.getProperties().Is(IsoFlagType.attachedN)) {
                     var12 = WallShaperWhole.instance;
                  }
               }

               var10.parentSprite
                  .render(
                     var10, this, var1, var2, var3, this.dir, this.offsetX, this.offsetY + this.renderYOffset * Core.TileScale, var4, true, (Consumer)var12
                  );
               var4.a = var11;
               var10.update();
            }
         }
      }

      if (this.Children != nullptr && DebugOptions.instance.Terrain.RenderTiles.AttachedChildren.getValue()) {
    int var14 = this.Children.size();

         for (int var16 = 0; var16 < var14; var16++) {
    IsoObject var17 = this.Children.get(var16);
            if (dynamic_cast<IsoMovingObject*>(var17) != nullptr) {
               IndieGL.shaderSetValue(var6, "floorLayer", 1);
               var17.render(((IsoMovingObject)var17).x, ((IsoMovingObject)var17).y, ((IsoMovingObject)var17).z, var4, true, false, nullptr);
            }
         }
      }

      if (this.wallBloodSplats != nullptr && DebugOptions.instance.Terrain.RenderTiles.AttachedWallBloodSplats.getValue()) {
         if (Core.OptionBloodDecals == 0) {
            return;
         }

         IndieGL.shaderSetValue(var6, "floorLayer", 0);

         for (int var15 = 0; var15 < this.wallBloodSplats.size(); var15++) {
            this.wallBloodSplats.get(var15).render(var1, var2, var3, var4);
         }
      }
   }

    bool isSpriteInvisible() {
      return this.sprite != nullptr && this.sprite.getProperties().Is(IsoFlagType.invisible);
   }

    void renderFxMask(float var1, float var2, float var3, bool var4) {
      if (this.sprite != nullptr) {
         if (this.getType() == IsoObjectType.wall) {
         }

         this.sprite.render(this, var1, var2, var3, this.dir, this.offsetX, this.offsetY + this.renderYOffset * Core.TileScale, colFxMask, false);
      }

      if (this.getOverlaySprite() != nullptr) {
         this.getOverlaySprite().render(this, var1, var2, var3, this.dir, this.offsetX, this.offsetY + this.renderYOffset * Core.TileScale, colFxMask, false);
      }

      if (var4) {
         if (this.AttachedAnimSprite != nullptr) {
    int var5 = this.AttachedAnimSprite.size();

            for (int var6 = 0; var6 < var5; var6++) {
    IsoSpriteInstance var7 = this.AttachedAnimSprite.get(var6);
               var7.render(this, var1, var2, var3, this.dir, this.offsetX, this.offsetY + this.renderYOffset * Core.TileScale, colFxMask);
            }
         }

         if (this.Children != nullptr) {
    int var8 = this.Children.size();

            for (int var10 = 0; var10 < var8; var10++) {
    IsoObject var11 = this.Children.get(var10);
               if (dynamic_cast<IsoMovingObject*>(var11) != nullptr) {
                  var11.render(((IsoMovingObject)var11).x, ((IsoMovingObject)var11).y, ((IsoMovingObject)var11).z, colFxMask, var4, false, nullptr);
               }
            }
         }

         if (this.wallBloodSplats != nullptr) {
            if (Core.OptionBloodDecals == 0) {
               return;
            }

            for (int var9 = 0; var9 < this.wallBloodSplats.size(); var9++) {
               this.wallBloodSplats.get(var9).render(var1, var2, var3, colFxMask);
            }
         }
      }
   }

    void renderObjectPicker(float var1, float var2, float var3, ColorInfo var4) {
      if (this.sprite != nullptr) {
         if (!this.sprite.getProperties().Is(IsoFlagType.invisible)) {
            this.sprite.renderObjectPicker(this.sprite.def, this, this.dir);
         }
      }
   }

    bool TestPathfindCollide(IsoMovingObject var1, IsoGridSquare var2, IsoGridSquare var3) {
    return false;
   }

    bool TestCollide(IsoMovingObject var1, IsoGridSquare var2, IsoGridSquare var3) {
    return false;
   }

    VisionResult TestVision(IsoGridSquare var1, IsoGridSquare var2) {
      return VisionResult.Unblocked;
   }

    Texture getCurrentFrameTex() {
      if (this.sprite == nullptr) {
    return nullptr;
      } else if (this.sprite.CurrentAnim == nullptr) {
    return nullptr;
      } else {
         return this.sprite.CurrentAnim.Frames.size() <= this.sprite.def.Frame
            ? nullptr
            : ((IsoDirectionFrame)this.sprite.CurrentAnim.Frames.get((int)this.sprite.def.Frame)).getTexture(this.dir);
      }
   }

    bool isMaskClicked(int var1, int var2) {
      return this.sprite == nullptr ? false : this.sprite.isMaskClicked(this.dir, var1, var2);
   }

    bool isMaskClicked(int var1, int var2, bool var3) {
      if (this.sprite == nullptr) {
    return false;
      } else {
         return this.overlaySprite != nullptr && this.overlaySprite.isMaskClicked(this.dir, var1, var2, var3)
            ? true
            : this.sprite.isMaskClicked(this.dir, var1, var2, var3);
      }
   }

    float getMaskClickedY(int var1, int var2, bool var3) {
      return this.sprite == nullptr ? 10000.0F : this.sprite.getMaskClickedY(this.dir, var1, var2, var3);
   }

    ColorInfo getCustomColor() {
      return this.customColor;
   }

    void setCustomColor(ColorInfo var1) {
      this.customColor = var1;
   }

    void setCustomColor(float var1, float var2, float var3, float var4) {
    ColorInfo var5 = std::make_shared<ColorInfo>(var1, var2, var3, var4);
      this.customColor = var5;
   }

    void loadFromRemoteBuffer(ByteBuffer var1) {
      this.loadFromRemoteBuffer(var1, true);
   }

    void loadFromRemoteBuffer(ByteBuffer var1, bool var2) {
      try {
         this.load(var1, 195);
      } catch (IOException var12) {
         var12.printStackTrace();
         return;
      }

      if (dynamic_cast<IsoWorldInventoryObject*>(this) != nullptr && ((IsoWorldInventoryObject)this).getItem() == nullptr) {
         DebugLog.log("loadFromRemoteBuffer() failed due to an unknown item type");
      } else {
    int var3 = var1.getInt();
    int var4 = var1.getInt();
    int var5 = var1.getInt();
    int var6 = var1.getInt();
    bool var7 = var1.get() != 0;
    bool var8 = var1.get() != 0;
         IsoWorld.instance.CurrentCell.EnsureSurroundNotNull(var3, var4, var5);
         this.square = IsoWorld.instance.CurrentCell.getGridSquare(var3, var4, var5);
         if (this.square != nullptr) {
            if (GameServer.bServer && !(dynamic_cast<IsoWorldInventoryObject*>(this) != nullptr)) {
               IsoRegions.setPreviousFlags(this.square);
            }

            if (var7) {
               this.square.getSpecialObjects().push_back(this);
            }

            if (var8 && dynamic_cast<IsoWorldInventoryObject*>(this) != nullptr) {
               this.square.getWorldObjects().push_back((IsoWorldInventoryObject)this);
               this.square.chunk.recalcHashCodeObjects();
            }

            if (var2) {
               if (var6 != -1 && var6 >= 0 && var6 <= this.square.getObjects().size()) {
                  this.square.getObjects().push_back(var6, this);
               } else {
                  this.square.getObjects().push_back(this);
               }
            }

            for (int var9 = 0; var9 < this.getContainerCount(); var9++) {
    ItemContainer var10 = this.getContainerByIndex(var9);
               var10.parent = this;
               var10.parent.square = this.square;
               var10.SourceGrid = this.square;
            }

            for (int var13 = -1; var13 <= 1; var13++) {
               for (int var14 = -1; var14 <= 1; var14++) {
    IsoGridSquare var11 = IsoWorld.instance.CurrentCell.getGridSquare(var13 + var3, var14 + var4, var5);
                  if (var11 != nullptr) {
                     var11.RecalcAllWithNeighbours(true);
                  }
               }
            }
         }
      }
   }

    bool hasObjectAmbientEmitter() {
    IsoChunk var1 = this.getChunk();
    return var1 = = nullptr ? false : var1.hasObjectAmbientEmitter(this);
   }

    void addObjectAmbientEmitter(PerObjectLogic var1) {
    IsoChunk var2 = this.getChunk();
      if (var2 != nullptr) {
         var2.addObjectAmbientEmitter(this, var1);
      }
   }

    void addToWorld() {
      for (int var1 = 0; var1 < this.getContainerCount(); var1++) {
    ItemContainer var2 = this.getContainerByIndex(var1);
         var2.addItemsToProcessItems();
      }

      if (!GameServer.bServer) {
    void* var4 = nullptr;
    ItemContainer var10 = this.getContainerByEitherType("fridge", "freezer");
         if (var10 != nullptr && var10.isPowered()) {
            this.addObjectAmbientEmitter(std::make_unique<FridgeHumLogic>().init(this));
            var4 = "FridgeHum";
            IsoWorld.instance.getCell().addToProcessIsoObject(this);
         } else if (this.sprite != nullptr && this.sprite.getProperties().Is(IsoFlagType.waterPiped) && this.getWaterAmount() > 0.0F && Rand.Next(15) == 0) {
            this.addObjectAmbientEmitter(std::make_unique<WaterDripLogic>().init(this));
            var4 = "WaterDrip";
         } else if (this.sprite == nullptr
            || this.sprite.getName() == nullptr
            || !this.sprite.getName().startsWith("camping_01")
            || this.sprite.tileSheetIndex != 0 && this.sprite.tileSheetIndex != 3) {
            if (dynamic_cast<IsoDoor*>(this) != nullptr) {
               if (((IsoDoor)this).isExterior()) {
                  this.addObjectAmbientEmitter(std::make_unique<DoorLogic>().init(this));
               }
            } else if (dynamic_cast<IsoWindow*>(this) != nullptr) {
               if (((IsoWindow)this).isExterior()) {
                  this.addObjectAmbientEmitter(std::make_unique<WindowLogic>().init(this));
               }
            } else if (dynamic_cast<IsoTree*>(this) != nullptr && Rand.Next(40) == 0) {
               this.addObjectAmbientEmitter(std::make_unique<TreeAmbianceLogic>().init(this));
               var4 = "TreeAmbiance";
            }
         } else {
            this.addObjectAmbientEmitter(std::make_unique<TentAmbianceLogic>().init(this));
            var4 = "TentAmbiance";
         }

    PropertyContainer var3 = this.getProperties();
         if (var3 != nullptr && var3.Is("AmbientSound")) {
            this.addObjectAmbientEmitter(std::make_unique<AmbientSoundLogic>().init(this));
            var4 = var3.Val("AmbientSound");
         }

         this.checkMoveWithWind();
      }
   }

    void removeFromWorld() {
    IsoCell var1 = this.getCell();
      var1.addToProcessIsoObjectRemove(this);
      var1.getStaticUpdaterObjectList().remove(this);

      for (int var2 = 0; var2 < this.getContainerCount(); var2++) {
    ItemContainer var3 = this.getContainerByIndex(var2);
         var3.removeItemsFromProcessItems();
      }

      if (this.emitter != nullptr) {
         this.emitter.stopAll();
         this.emitter = nullptr;
      }

      if (this.getChunk() != nullptr) {
         this.getChunk().removeObjectAmbientEmitter(this);
      }
   }

    void reuseGridSquare() {
   }

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
            for (int var4 = 0; var4 < GameServer.udpEngine.connections.size(); var4++) {
    UdpConnection var5 = (UdpConnection)GameServer.udpEngine.connections.get(var4);
               if (var5.RelevantTo(this.square.x, this.square.y)) {
                  GameServer.SyncObjectChunkHashes(this.square.chunk, var5);
               }
            }

            return;
         }

         for (int var1 = 0; var1 < GameServer.udpEngine.connections.size(); var1++) {
    UdpConnection var2 = (UdpConnection)GameServer.udpEngine.connections.get(var1);
            if (var2 != nullptr && this.square != nullptr && var2.RelevantTo(this.square.x, this.square.y)) {
    ByteBufferWriter var3 = var2.startPacket();
               PacketType.AddItemToMap.doPacket(var3);
               this.writeToRemoteBuffer(var3);
               PacketType.AddItemToMap.send(var2);
            }
         }
      }
   }

    void transmitUpdatedSpriteToClients(UdpConnection var1) {
      if (GameServer.bServer) {
         for (int var2 = 0; var2 < GameServer.udpEngine.connections.size(); var2++) {
    UdpConnection var3 = (UdpConnection)GameServer.udpEngine.connections.get(var2);
            if (var3 != nullptr
               && this.square != nullptr
               && (var1 == nullptr || var3.getConnectedGUID() != var1.getConnectedGUID())
               && var3.RelevantTo(this.square.x, this.square.y)) {
    ByteBufferWriter var4 = var3.startPacket();
               PacketType.UpdateItemSprite.doPacket(var4);
               var4.putInt(this.getSprite().ID);
               GameWindow.WriteStringUTF(var4.bb, this.spriteName);
               var4.putInt(this.getSquare().getX());
               var4.putInt(this.getSquare().getY());
               var4.putInt(this.getSquare().getZ());
               var4.putInt(this.getSquare().getObjects().indexOf(this));
               if (this.AttachedAnimSprite != nullptr) {
                  var4.putByte((byte)this.AttachedAnimSprite.size());

                  for (int var5 = 0; var5 < this.AttachedAnimSprite.size(); var5++) {
    IsoSpriteInstance var6 = this.AttachedAnimSprite.get(var5);
                     var4.putInt(var6.parentSprite.ID);
                  }
               } else {
                  var4.putByte((byte)0);
               }

               PacketType.UpdateItemSprite.send(var3);
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

    void sendObjectChange(const std::string& var1) {
      if (GameServer.bServer) {
         GameServer.sendObjectChange(this, var1, (KahluaTable)nullptr);
      } else if (GameClient.bClient) {
         DebugLog.log("sendObjectChange() can only be called on the server");
      } else {
         SinglePlayerServer.sendObjectChange(this, var1, (KahluaTable)nullptr);
      }
   }

    void sendObjectChange(const std::string& var1, KahluaTable var2) {
      if (GameServer.bServer) {
         GameServer.sendObjectChange(this, var1, var2);
      } else if (GameClient.bClient) {
         DebugLog.log("sendObjectChange() can only be called on the server");
      } else {
         SinglePlayerServer.sendObjectChange(this, var1, var2);
      }
   }

    void sendObjectChange(const std::string& var1, Object... var2) {
      if (GameServer.bServer) {
         GameServer.sendObjectChange(this, var1, var2);
      } else if (GameClient.bClient) {
         DebugLog.log("sendObjectChange() can only be called on the server");
      } else {
         SinglePlayerServer.sendObjectChange(this, var1, var2);
      }
   }

    void saveChange(const std::string& var1, KahluaTable var2, ByteBuffer var3) {
      if ("containers" == var1)) {
         var3.put((byte)this.getContainerCount());

         for (int var4 = 0; var4 < this.getContainerCount(); var4++) {
    ItemContainer var5 = this.getContainerByIndex(var4);

            try {
               var5.save(var3);
            } catch (Throwable var8) {
               ExceptionLogger.logException(var8);
            }
         }
      } else if ("container.customTemperature" == var1)) {
         if (this.getContainer() != nullptr) {
            var3.putFloat(this.getContainer().getCustomTemperature());
         } else {
            var3.putFloat(0.0F);
         }
      } else if ("name" == var1)) {
         GameWindow.WriteStringUTF(var3, this.getName());
      } else if ("replaceWith" == var1)) {
         if (var2 != nullptr && var2.rawget("object") instanceof IsoObject) {
    IsoObject var9 = (IsoObject)var2.rawget("object");

            try {
               var9.save(var3);
            } catch (IOException var7) {
               var7.printStackTrace();
            }
         }
      } else if ("usesExternalWaterSource" == var1)) {
    bool var10 = var2 != nullptr && bool.TRUE == var2.rawget("value"));
         var3.put((byte)(var10 ? 1 : 0));
      } else if ("sprite" == var1)) {
         if (this.sprite == nullptr) {
            var3.putInt(0);
         } else {
            var3.putInt(this.sprite.ID);
            GameWindow.WriteStringUTF(var3, this.spriteName);
         }
      }
   }

    void loadChange(const std::string& var1, ByteBuffer var2) {
      if ("containers" == var1)) {
         for (int var3 = 0; var3 < this.getContainerCount(); var3++) {
    ItemContainer var4 = this.getContainerByIndex(var3);
            var4.removeItemsFromProcessItems();
            var4.removeAllItems();
         }

         this.removeAllContainers();
    uint8_t var9 = var2.get();

         for (int var14 = 0; var14 < var9; var14++) {
    ItemContainer var5 = std::make_shared<ItemContainer>();
            var5.ID = 0;
            var5.parent = this;
            var5.SourceGrid = this.square;

            try {
               var5.load(var2, 195);
               if (var14 == 0) {
                  if (dynamic_cast<IsoDeadBody*>(this) != nullptr) {
                     var5.Capacity = 8;
                  }

                  this.container = var5;
               } else {
                  this.addSecondaryContainer(var5);
               }
            } catch (Throwable var7) {
               ExceptionLogger.logException(var7);
            }
         }
      } else if ("container.customTemperature" == var1)) {
    float var10 = var2.getFloat();
         if (this.getContainer() != nullptr) {
            this.getContainer().setCustomTemperature(var10);
         }
      } else if ("name" == var1)) {
    std::string var11 = GameWindow.ReadStringUTF(var2);
         this.setName(var11);
      } else if ("replaceWith" == var1)) {
         try {
    int var12 = this.getObjectIndex();
            if (var12 >= 0) {
    IsoObject var15 = factoryFromFileInput(this.getCell(), var2);
               var15.load(var2, 195);
               var15.setSquare(this.square);
               this.square.getObjects().set(var12, var15);
               this.square.getSpecialObjects().remove(this);
               this.square.RecalcAllWithNeighbours(true);
               if (this.getContainerCount() > 0) {
                  for (int var16 = 0; var16 < this.getContainerCount(); var16++) {
    ItemContainer var6 = this.getContainerByIndex(var16);
                     var6.removeItemsFromProcessItems();
                  }

                  LuaEventManager.triggerEvent("OnContainerUpdate");
               }
            }
         } catch (IOException var8) {
            var8.printStackTrace();
         }
      } else if ("usesExternalWaterSource" == var1)) {
         this.usesExternalWaterSource = var2.get() == 1;
      } else if ("sprite" == var1)) {
    int var13 = var2.getInt();
         if (var13 == 0) {
            this.sprite = nullptr;
            this.spriteName = nullptr;
            this.tile = nullptr;
         } else {
            this.spriteName = GameWindow.ReadString(var2);
            this.sprite = IsoSprite.getSprite(IsoSpriteManager.instance, var13);
            if (this.sprite == nullptr) {
               this.sprite = IsoSprite.CreateSprite(IsoSpriteManager.instance);
               this.sprite.LoadFramesNoDirPageSimple(this.spriteName);
            }
         }
      } else if ("emptyTrash" == var1)) {
         this.getContainer().clear();
         if (this.getOverlaySprite() != nullptr) {
            ItemPickerJava.updateOverlaySprite(this);
         }
      }

      this.checkMoveWithWind();
   }

    void transmitUpdatedSpriteToServer() {
      if (GameClient.bClient) {
    ByteBufferWriter var1 = GameClient.connection.startPacket();
         PacketType.UpdateItemSprite.doPacket(var1);
         var1.putInt(this.getSprite().ID);
         GameWindow.WriteStringUTF(var1.bb, this.spriteName);
         var1.putInt(this.getSquare().getX());
         var1.putInt(this.getSquare().getY());
         var1.putInt(this.getSquare().getZ());
         var1.putInt(this.getSquare().getObjects().indexOf(this));
         if (this.AttachedAnimSprite != nullptr) {
            var1.putByte((byte)this.AttachedAnimSprite.size());

            for (int var2 = 0; var2 < this.AttachedAnimSprite.size(); var2++) {
    IsoSpriteInstance var3 = this.AttachedAnimSprite.get(var2);
               var1.putInt(var3.parentSprite.ID);
            }
         } else {
            var1.putByte((byte)0);
         }

         PacketType.UpdateItemSprite.send(GameClient.connection);
      }
   }

    void transmitCompleteItemToServer() {
      if (GameClient.bClient) {
    ByteBufferWriter var1 = GameClient.connection.startPacket();
         PacketType.AddItemToMap.doPacket(var1);
         this.writeToRemoteBuffer(var1);
         PacketType.AddItemToMap.send(GameClient.connection);
      }
   }

    void transmitModData() {
      if (this.square != nullptr) {
         if (GameClient.bClient) {
    ByteBufferWriter var1 = GameClient.connection.startPacket();
            PacketType.ObjectModData.doPacket(var1);
            var1.putInt(this.getSquare().getX());
            var1.putInt(this.getSquare().getY());
            var1.putInt(this.getSquare().getZ());
            var1.putInt(this.getSquare().getObjects().indexOf(this));
            if (this.getModData().empty()) {
               var1.putByte((byte)0);
            } else {
               var1.putByte((byte)1);

               try {
                  this.getModData().save(var1.bb);
               } catch (IOException var3) {
                  var3.printStackTrace();
               }
            }

            PacketType.ObjectModData.send(GameClient.connection);
         } else if (GameServer.bServer) {
            GameServer.sendObjectModData(this);
         }
      }
   }

    void writeToRemoteBuffer(ByteBufferWriter var1) {
      try {
         this.save(var1.bb);
      } catch (IOException var3) {
         var3.printStackTrace();
      }

      var1.putInt(this.square.getX());
      var1.putInt(this.square.getY());
      var1.putInt(this.square.getZ());
      var1.putInt(this.getObjectIndex());
      var1.putBoolean(this.square.getSpecialObjects().contains(this));
      var1.putBoolean(this.square.getWorldObjects().contains(this));
   }

    int getObjectIndex() {
      return this.square == nullptr ? -1 : this.square.getObjects().indexOf(this);
   }

    int getMovingObjectIndex() {
      return this.square == nullptr ? -1 : this.square.getMovingObjects().indexOf(this);
   }

    int getSpecialObjectIndex() {
      return this.square == nullptr ? -1 : this.square.getSpecialObjects().indexOf(this);
   }

    int getStaticMovingObjectIndex() {
      return this.square == nullptr ? -1 : this.square.getStaticMovingObjects().indexOf(this);
   }

    int getWorldObjectIndex() {
      return this.square == nullptr ? -1 : this.square.getWorldObjects().indexOf(this);
   }

    IsoSprite getOverlaySprite() {
      return this.overlaySprite;
   }

    void setOverlaySprite(const std::string& var1) {
      this.setOverlaySprite(var1, -1.0F, -1.0F, -1.0F, -1.0F, true);
   }

    void setOverlaySprite(const std::string& var1, bool var2) {
      this.setOverlaySprite(var1, -1.0F, -1.0F, -1.0F, -1.0F, var2);
   }

    void setOverlaySpriteColor(float var1, float var2, float var3, float var4) {
      this.overlaySpriteColor = std::make_shared<ColorInfo>(var1, var2, var3, var4);
   }

    ColorInfo getOverlaySpriteColor() {
      return this.overlaySpriteColor;
   }

    void setOverlaySprite(const std::string& var1, float var2, float var3, float var4, float var5) {
      this.setOverlaySprite(var1, var2, var3, var4, var5, true);
   }

    bool setOverlaySprite(const std::string& var1, float var2, float var3, float var4, float var5, bool var6) {
      if (StringUtils.isNullOrWhitespace(var1)) {
         if (this.overlaySprite == nullptr) {
    return false;
         }

         this.overlaySprite = nullptr;
         var1 = "";
      } else {
    bool var7;
         if (!(var2 > -1.0F)) {
            var7 = this.overlaySpriteColor == nullptr;
         } else {
            var7 = this.overlaySpriteColor != nullptr
               && this.overlaySpriteColor.r == var2
               && this.overlaySpriteColor.g == var3
               && this.overlaySpriteColor.b == var4
               && this.overlaySpriteColor.a == var5;
         }

         if (this.overlaySprite != nullptr && var1 == this.overlaySprite.name) && var7) {
    return false;
         }

         this.overlaySprite = IsoSpriteManager.instance.getSprite(var1);
         this.overlaySprite.name = var1;
      }

      if (var2 > -1.0F) {
         this.overlaySpriteColor = std::make_shared<ColorInfo>(var2, var3, var4, var5);
      } else {
         this.overlaySpriteColor = nullptr;
      }

      if (!var6) {
    return true;
      } else {
         if (GameServer.bServer) {
            GameServer.updateOverlayForClients(this, var1, var2, var3, var4, var5, nullptr);
         } else if (GameClient.bClient) {
    ByteBufferWriter var8 = GameClient.connection.startPacket();
            PacketType.UpdateOverlaySprite.doPacket(var8);
            GameWindow.WriteStringUTF(var8.bb, var1);
            var8.putInt(this.getSquare().getX());
            var8.putInt(this.getSquare().getY());
            var8.putInt(this.getSquare().getZ());
            var8.putFloat(var2);
            var8.putFloat(var3);
            var8.putFloat(var4);
            var8.putFloat(var5);
            var8.putInt(this.getSquare().getObjects().indexOf(this));
            PacketType.UpdateOverlaySprite.send(GameClient.connection);
         }

    return true;
      }
   }

    bool haveSpecialTooltip() {
      return this.specialTooltip;
   }

    void setSpecialTooltip(bool var1) {
      this.specialTooltip = var1;
   }

    int getKeyId() {
      return this.keyId;
   }

    void setKeyId(int var1) {
      this.keyId = var1;
   }

    bool isHighlighted() {
      return (this.highlightFlags & 1) != 0;
   }

    void setHighlighted(bool var1) {
      this.setHighlighted(var1, true);
   }

    void setHighlighted(bool var1, bool var2) {
      if (var1) {
         this.highlightFlags = (byte)(this.highlightFlags | 1);
      } else {
         this.highlightFlags &= -2;
      }

      if (var2) {
         this.highlightFlags = (byte)(this.highlightFlags | 2);
      } else {
         this.highlightFlags &= -3;
      }
   }

    ColorInfo getHighlightColor() {
      return this.highlightColor;
   }

    void setHighlightColor(ColorInfo var1) {
      this.highlightColor.set(var1);
   }

    void setHighlightColor(float var1, float var2, float var3, float var4) {
      if (this.highlightColor == nullptr) {
         this.highlightColor = std::make_shared<ColorInfo>(var1, var2, var3, var4);
      } else {
         this.highlightColor.set(var1, var2, var3, var4);
      }
   }

    bool isBlink() {
      return (this.highlightFlags & 4) != 0;
   }

    void setBlink(bool var1) {
      if (var1) {
         this.highlightFlags = (byte)(this.highlightFlags | 4);
      } else {
         this.highlightFlags &= -5;
      }
   }

    void checkHaveElectricity() {
      if (!GameServer.bServer) {
    ItemContainer var1 = this.getContainerByEitherType("fridge", "freezer");
         if (var1 != nullptr && var1.isPowered()) {
            IsoWorld.instance.getCell().addToProcessIsoObject(this);
            if (this.getChunk() != nullptr && !this.hasObjectAmbientEmitter()) {
               this.getChunk().addObjectAmbientEmitter(this, std::make_unique<FridgeHumLogic>().init(this));
            }
         }

         this.checkAmbientSound();
      }
   }

    void checkAmbientSound() {
    PropertyContainer var1 = this.getProperties();
      if (var1 != nullptr && var1.Is("AmbientSound") && this.getChunk() != nullptr && !this.hasObjectAmbientEmitter()) {
         this.getChunk().addObjectAmbientEmitter(this, std::make_unique<AmbientSoundLogic>().init(this));
      }
   }

    int getContainerCount() {
    int var1 = this.container == nullptr ? 0 : 1;
    int var2 = this.secondaryContainers == nullptr ? 0 : this.secondaryContainers.size();
      return var1 + var2;
   }

    ItemContainer getContainerByIndex(int var1) {
      if (this.container != nullptr) {
         if (var1 == 0) {
            return this.container;
         } else if (this.secondaryContainers == nullptr) {
    return nullptr;
         } else {
            return var1 >= 1 && var1 <= this.secondaryContainers.size() ? this.secondaryContainers.get(var1 - 1) : nullptr;
         }
      } else if (this.secondaryContainers == nullptr) {
    return nullptr;
      } else {
         return var1 >= 0 && var1 < this.secondaryContainers.size() ? this.secondaryContainers.get(var1) : nullptr;
      }
   }

    ItemContainer getContainerByType(const std::string& var1) {
      for (int var2 = 0; var2 < this.getContainerCount(); var2++) {
    ItemContainer var3 = this.getContainerByIndex(var2);
         if (var3.getType() == var1)) {
    return var3;
         }
      }

    return nullptr;
   }

    ItemContainer getContainerByEitherType(const std::string& var1, const std::string& var2) {
      for (int var3 = 0; var3 < this.getContainerCount(); var3++) {
    ItemContainer var4 = this.getContainerByIndex(var3);
         if (var4.getType() == var1) || var4.getType() == var2)) {
    return var4;
         }
      }

    return nullptr;
   }

    void addSecondaryContainer(ItemContainer var1) {
      if (this.secondaryContainers == nullptr) {
         this.secondaryContainers = std::make_unique<std::vector<>>();
      }

      this.secondaryContainers.push_back(var1);
      var1.parent = this;
   }

    int getContainerIndex(ItemContainer var1) {
      if (var1 == this.container) {
    return 0;
      } else if (this.secondaryContainers == nullptr) {
         return -1;
      } else {
         for (int var2 = 0; var2 < this.secondaryContainers.size(); var2++) {
            if (this.secondaryContainers.get(var2) == var1) {
               return (this.container == nullptr ? 0 : 1) + var2;
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
            if (this.sprite.getProperties().Is(IsoFlagType.container) && this.container == nullptr) {
               this.container = std::make_shared<ItemContainer>(this.sprite.getProperties().Val("container"), this.square, this);
               this.container.parent = this;
               this.OutlineOnMouseover = true;
               if (this.sprite.getProperties().Is("ContainerCapacity")) {
                  this.container.Capacity = int.parseInt(this.sprite.getProperties().Val("ContainerCapacity"));
               }

               if (this.sprite.getProperties().Is("ContainerPosition")) {
                  this.container.setContainerPosition(this.sprite.getProperties().Val("ContainerPosition"));
               }
            }

            if (this.getSprite().getProperties().Is("Freezer")) {
    ItemContainer var1 = std::make_shared<ItemContainer>("freezer", this.square, this);
               if (this.getSprite().getProperties().Is("FreezerCapacity")) {
                  var1.Capacity = int.parseInt(this.sprite.getProperties().Val("FreezerCapacity"));
               } else {
                  var1.Capacity = 15;
               }

               if (this.container == nullptr) {
                  this.container = var1;
                  this.container.parent = this;
               } else {
                  this.addSecondaryContainer(var1);
               }

               if (this.sprite.getProperties().Is("FreezerPosition")) {
                  var1.setFreezerPosition(this.sprite.getProperties().Val("FreezerPosition"));
               }
            }
         }
      }
   }

    bool isItemAllowedInContainer(ItemContainer var1, InventoryItem var2) {
    return true;
   }

    bool isRemoveItemAllowedFromContainer(ItemContainer var1, InventoryItem var2) {
    return true;
   }

    void cleanWallBlood() {
      this.square.removeBlood(false, true);
   }

    ObjectRenderEffects getWindRenderEffects() {
      return this.windRenderEffects;
   }

    ObjectRenderEffects getObjectRenderEffects() {
      return this.objectRenderEffects;
   }

    void setRenderEffect(RenderEffectType var1) {
      this.setRenderEffect(var1, false);
   }

    IsoObject getRenderEffectMaster() {
    return this;
   }

    void setRenderEffect(RenderEffectType var1, bool var2) {
      if (!GameServer.bServer) {
    IsoObject var3 = this.getRenderEffectMaster();
         if (var3.objectRenderEffects == nullptr || var2) {
            var3.objectRenderEffects = ObjectRenderEffects.getNew(this, var1, var2);
         }
      }
   }

    void removeRenderEffect(ObjectRenderEffects var1) {
    IsoObject var2 = this.getRenderEffectMaster();
      if (var2.objectRenderEffects != nullptr && var2.objectRenderEffects == var1) {
         var2.objectRenderEffects = nullptr;
      }
   }

    ObjectRenderEffects getObjectRenderEffectsToApply() {
    IsoObject var1 = this.getRenderEffectMaster();
      if (var1.objectRenderEffects != nullptr) {
         return var1.objectRenderEffects;
      } else {
         return Core.getInstance().getOptionDoWindSpriteEffects() && var1.windRenderEffects != nullptr ? var1.windRenderEffects : nullptr;
      }
   }

    void destroyFence(IsoDirections var1) {
      BrokenFences.getInstance().destroyFence(this, var1);
   }

    void getSpriteGridObjects(std::vector<IsoObject> var1) {
      var1.clear();
    IsoSprite var2 = this.getSprite();
      if (var2 != nullptr) {
    IsoSpriteGrid var3 = var2.getSpriteGrid();
         if (var3 != nullptr) {
    int var4 = var3.getSpriteGridPosX(var2);
    int var5 = var3.getSpriteGridPosY(var2);
    int var6 = this.getSquare().getX();
    int var7 = this.getSquare().getY();
    int var8 = this.getSquare().getZ();

            for (int var9 = var7 - var5; var9 < var7 - var5 + var3.getHeight(); var9++) {
               for (int var10 = var6 - var4; var10 < var6 - var4 + var3.getWidth(); var10++) {
    IsoGridSquare var11 = this.getCell().getGridSquare(var10, var9, var8);
                  if (var11 != nullptr) {
                     for (int var12 = 0; var12 < var11.getObjects().size(); var12++) {
    IsoObject var13 = (IsoObject)var11.getObjects().get(var12);
                        if (var13.getSprite() != nullptr && var13.getSprite().getSpriteGrid() == var3) {
                           var1.push_back(var13);
                        }
                     }
                  }
               }
            }
         }
      }
   }

    int getOutlineHighlightCol() {
      return this.outlineHighlightCol[0];
   }

    void setOutlineHighlightCol(ColorInfo var1) {
      if (var1 != nullptr) {
         for (int var2 = 0; var2 < this.outlineHighlightCol.length; var2++) {
            this.outlineHighlightCol[var2] = Color.colorToABGR(var1.r, var1.g, var1.b, var1.a);
         }
      }
   }

    int getOutlineHighlightCol(int var1) {
      return this.outlineHighlightCol[var1];
   }

    void setOutlineHighlightCol(int var1, ColorInfo var2) {
      if (var2 != nullptr) {
         this.outlineHighlightCol[var1] = Color.colorToABGR(var2.r, var2.g, var2.b, var2.a);
      }
   }

    void setOutlineHighlightCol(float var1, float var2, float var3, float var4) {
      for (int var5 = 0; var5 < this.outlineHighlightCol.length; var5++) {
         this.outlineHighlightCol[var5] = Color.colorToABGR(var1, var2, var3, var4);
      }
   }

    void setOutlineHighlightCol(int var1, float var2, float var3, float var4, float var5) {
      this.outlineHighlightCol[var1] = Color.colorToABGR(var2, var3, var4, var5);
   }

    bool isOutlineHighlight() {
      return this.isOutlineHighlight != 0;
   }

    bool isOutlineHighlight(int var1) {
      return (this.isOutlineHighlight & 1 << var1) != 0;
   }

    void setOutlineHighlight(bool var1) {
      this.isOutlineHighlight = (byte)(var1 ? -1 : 0);
   }

    void setOutlineHighlight(int var1, bool var2) {
      if (var2) {
         this.isOutlineHighlight = (byte)(this.isOutlineHighlight | 1 << var1);
      } else {
         this.isOutlineHighlight = (byte)(this.isOutlineHighlight & ~(1 << var1));
      }
   }

    bool isOutlineHlAttached() {
      return this.isOutlineHlAttached != 0;
   }

    bool isOutlineHlAttached(int var1) {
      return (this.isOutlineHlAttached & 1 << var1) != 0;
   }

    void setOutlineHlAttached(bool var1) {
      this.isOutlineHlAttached = (byte)(var1 ? -1 : 0);
   }

    void setOutlineHlAttached(int var1, bool var2) {
      if (var2) {
         this.isOutlineHlAttached = (byte)(this.isOutlineHlAttached | 1 << var1);
      } else {
         this.isOutlineHlAttached = (byte)(this.isOutlineHlAttached & ~(1 << var1));
      }
   }

    bool isOutlineHlBlink() {
      return this.isOutlineHlBlink != 0;
   }

    bool isOutlineHlBlink(int var1) {
      return (this.isOutlineHlBlink & 1 << var1) != 0;
   }

    void setOutlineHlBlink(bool var1) {
      this.isOutlineHlBlink = (byte)(var1 ? -1 : 0);
   }

    void setOutlineHlBlink(int var1, bool var2) {
      if (var2) {
         this.isOutlineHlBlink = (byte)(this.isOutlineHlBlink | 1 << var1);
      } else {
         this.isOutlineHlBlink = (byte)(this.isOutlineHlBlink & ~(1 << var1));
      }
   }

    void unsetOutlineHighlight() {
      this.isOutlineHighlight = 0;
      this.isOutlineHlBlink = 0;
      this.isOutlineHlAttached = 0;
   }

    float getOutlineThickness() {
      return this.outlineThickness;
   }

    void setOutlineThickness(float var1) {
      this.outlineThickness = var1;
   }

    void addItemsFromProperties() {
    PropertyContainer var1 = this.getProperties();
      if (var1 != nullptr) {
    std::string var2 = var1.Val("Material");
    std::string var3 = var1.Val("Material2");
    std::string var4 = var1.Val("Material3");
         if ("Wood" == var2) || "Wood" == var3) || "Wood" == var4)) {
            this.square.AddWorldInventoryItem(InventoryItemFactory.CreateItem("Base.UnusableWood"), Rand.Next(0.0F, 0.5F), Rand.Next(0.0F, 0.5F), 0.0F);
            if (Rand.NextBool(5)) {
               this.square.AddWorldInventoryItem(InventoryItemFactory.CreateItem("Base.UnusableWood"), Rand.Next(0.0F, 0.5F), Rand.Next(0.0F, 0.5F), 0.0F);
            }
         }

         if (("MetalBars" == var2) || "MetalBars" == var3) || "MetalBars" == var4)) && Rand.NextBool(2)) {
            this.square.AddWorldInventoryItem(InventoryItemFactory.CreateItem("Base.MetalBar"), Rand.Next(0.0F, 0.5F), Rand.Next(0.0F, 0.5F), 0.0F);
         }

         if (("MetalPlates" == var2) || "MetalPlates" == var3) || "MetalPlates" == var4)) && Rand.NextBool(2)) {
            this.square.AddWorldInventoryItem(InventoryItemFactory.CreateItem("Base.SheetMetal"), Rand.Next(0.0F, 0.5F), Rand.Next(0.0F, 0.5F), 0.0F);
         }

         if (("MetalPipe" == var2) || "MetalPipe" == var3) || "MetalPipe" == var4)) && Rand.NextBool(2)) {
            this.square.AddWorldInventoryItem(InventoryItemFactory.CreateItem("Base.MetalPipe"), Rand.Next(0.0F, 0.5F), Rand.Next(0.0F, 0.5F), 0.0F);
         }

         if (("MetalWire" == var2) || "MetalWire" == var3) || "MetalWire" == var4)) && Rand.NextBool(3)) {
            this.square.AddWorldInventoryItem(InventoryItemFactory.CreateItem("Base.Wire"), Rand.Next(0.0F, 0.5F), Rand.Next(0.0F, 0.5F), 0.0F);
         }

         if (("Nails" == var2) || "Nails" == var3) || "Nails" == var4)) && Rand.NextBool(2)) {
            this.square.AddWorldInventoryItem(InventoryItemFactory.CreateItem("Base.Nails"), Rand.Next(0.0F, 0.5F), Rand.Next(0.0F, 0.5F), 0.0F);
         }

         if (("Screws" == var2) || "Screws" == var3) || "Screws" == var4)) && Rand.NextBool(2)) {
            this.square.AddWorldInventoryItem(InventoryItemFactory.CreateItem("Base.Screws"), Rand.Next(0.0F, 0.5F), Rand.Next(0.0F, 0.5F), 0.0F);
         }
      }
   }

    bool isDestroyed() {
      return this.Damage <= 0;
   }

    void Thump(IsoMovingObject var1) {
    IsoGameCharacter var2 = (IsoGameCharacter)Type.tryCastTo(var1, IsoGameCharacter.class);
      if (var2 != nullptr) {
    Thumpable var3 = this.getThumpableFor(var2);
         if (var3 == nullptr) {
            return;
         }

         if (var3 != this) {
            var3.Thump(var1);
            return;
         }
      }

    bool var10 = BrokenFences.getInstance().isBreakableObject(this);
    uint8_t var4 = 8;
      if (dynamic_cast<IsoZombie*>(var1) != nullptr) {
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

         if (var5 >= var4) {
    int var7 = 1 * ThumpState.getFastForwardDamageMultiplier();
            this.Damage = (short)(this.Damage - var7);
         } else {
            this.partialThumpDmg = this.partialThumpDmg + (float)var5 / var4 * ThumpState.getFastForwardDamageMultiplier();
            if ((int)this.partialThumpDmg > 0) {
    int var13 = (int)this.partialThumpDmg;
               this.Damage = (short)(this.Damage - var13);
               this.partialThumpDmg -= var13;
            }
         }

         WorldSoundManager.instance.addSound(var1, this.square.getX(), this.square.getY(), this.square.getZ(), 20, 20, true, 4.0F, 15.0F);
      }

      if (this.Damage <= 0) {
    std::string var11 = "BreakObject";
         if (var2 != nullptr) {
            var2.getEmitter().playSound(var11, this);
         }

         if (GameServer.bServer) {
            GameServer.PlayWorldSoundServer(var11, false, var1.getCurrentSquare(), 0.2F, 20.0F, 1.1F, true);
         }

         WorldSoundManager.instance.addSound(nullptr, this.square.getX(), this.square.getY(), this.square.getZ(), 10, 20, true, 4.0F, 15.0F);
         var1.setThumpTarget(nullptr);
         if (var10) {
    PropertyContainer var15 = this.getProperties();
    IsoDirections var12;
            if (var15.Is(IsoFlagType.collideN) && var15.Is(IsoFlagType.collideW)) {
               var12 = var1.getY() >= this.getY() ? IsoDirections.N : IsoDirections.S;
            } else if (var15.Is(IsoFlagType.collideN)) {
               var12 = var1.getY() >= this.getY() ? IsoDirections.N : IsoDirections.S;
            } else {
               var12 = var1.getX() >= this.getX() ? IsoDirections.W : IsoDirections.E;
            }

            BrokenFences.getInstance().destroyFence(this, var12);
            return;
         }

    std::vector var6 = new std::vector();

         for (int var14 = 0; var14 < this.getContainerCount(); var14++) {
    ItemContainer var8 = this.getContainerByIndex(var14);
            var6.clear();
            var6.addAll(var8.getItems());
            var8.removeItemsFromProcessItems();
            var8.removeAllItems();

            for (int var9 = 0; var9 < var6.size(); var9++) {
               this.getSquare().AddWorldInventoryItem((InventoryItem)var6.get(var9), 0.0F, 0.0F, 0.0F);
            }
         }

         this.square.transmitRemoveItemFromSquare(this);
      }
   }

    void setMovedThumpable(bool var1) {
      this.bMovedThumpable = var1;
   }

    bool isMovedThumpable() {
      return this.bMovedThumpable;
   }

    void WeaponHit(IsoGameCharacter var1, HandWeapon var2) {
   }

    Thumpable getThumpableFor(IsoGameCharacter var1) {
      if (this.isDestroyed()) {
    return nullptr;
      } else if (this.isMovedThumpable()) {
    return this;
      } else if (!BrokenFences.getInstance().isBreakableObject(this)) {
    return nullptr;
      } else {
    IsoZombie var2 = (IsoZombie)Type.tryCastTo(var1, IsoZombie.class);
         return var2 != nullptr && var2.isCrawling() ? this : nullptr;
      }
   }

    bool isExistInTheWorld() {
      return this.square.getMovingObjects().contains(this);
   }

    float getThumpCondition() {
      return PZMath.clamp(this.getDamage(), 0, 100) / 100.0F;
   }

   static {
      initFactory();
   }
}
} // namespace iso
} // namespace zombie
