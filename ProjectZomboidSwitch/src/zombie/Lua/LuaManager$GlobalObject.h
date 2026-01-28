#pragma once
#include <queue>
#include <sstream>
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
// #include "OpenAL/OpenALManager.h" // Use OpenAL equivalents if needed
#include "java/net/URI.h"
#include "java/net/URL.h"
#include "java/text/SimpleDateFormat.h"
#include "javax/xml/parsers/DocumentBuilder.h"
#include "javax/xml/parsers/DocumentBuilderFactory.h"
#include "org/lwjglx/input/Controller.h"
#include "org/lwjglx/input/Controllers.h"
#include "org/lwjglx/input/KeyCodes.h"
#include "org/w3c/dom/Document.h"
#include "org/w3c/dom/Element.h"
#include "org/w3c/dom/Node.h"
#include "org/w3c/dom/NodeList.h"
#include "org/xml/sax/InputSource.h"
#include "se/krka/kahlua/integration/annotations/LuaMethod.h"
#include "se/krka/kahlua/j2se/KahluaTableImpl.h"
#include "se/krka/kahlua/vm/Coroutine.h"
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "se/krka/kahlua/vm/KahluaTableIterator.h"
#include "se/krka/kahlua/vm/KahluaThread.h"
#include "se/krka/kahlua/vm/LuaCallFrame.h"
#include "se/krka/kahlua/vm/LuaClosure.h"
#include "zombie/AmbientStreamManager.h"
#include "zombie/AmbientStreamManager/Ambient.h"
#include "zombie/BaseAmbientStreamManager.h"
#include "zombie/BaseSoundManager.h"
#include "zombie/GameSounds.h"
#include "zombie/GameTime.h"
#include "zombie/GameWindow.h"
#include "zombie/Lua/LuaManager/GlobalObject/1.h"
#include "zombie/Lua/LuaManager/GlobalObject/3.h"
#include "zombie/Lua/LuaManager/GlobalObject/ItemQuery.h"
#include "zombie/Lua/LuaManager/GlobalObject/ItemQueryJava.h"
#include "zombie/Lua/LuaManager/GlobalObject/LuaFileWriter.h"
#include "zombie/Lua/LuaManager/GlobalObject/TimSortComparator.h"
#include "zombie/MapGroups.h"
#include "zombie/SandboxOptions.h"
#include "zombie/SoundManager.h"
#include "zombie/VirtualZombieManager.h"
#include "zombie/WorldSoundManager.h"
#include "zombie/ZombieSpawnRecorder.h"
#include "zombie/ZomboidFileSystem.h"
#include "zombie/ai/sadisticAIDirector/SleepingEvent.h"
#include "zombie/asset/Asset.h"
#include "zombie/asset/AssetPath.h"
#include "zombie/audio/BaseSoundBank.h"
#include "zombie/audio/parameters/ParameterRoomType.h"
#include "zombie/characters/BodyDamage/BodyPart.h"
#include "zombie/characters/Faction.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/characters/IsoZombie.h"
#include "zombie/characters/SurvivorDesc.h"
#include "zombie/characters/SurvivorFactory.h"
#include "zombie/characters/action/ActionGroup.h"
#include "zombie/characters/professions/ProfessionFactory.h"
#include "zombie/characters/professions/ProfessionFactory/Profession.h"
#include "zombie/characters/skills/PerkFactory/Perk.h"
#include "zombie/characters/traits/TraitFactory.h"
#include "zombie/characters/traits/TraitFactory/Trait.h"
#include "zombie/chat/ChatManager.h"
#include "zombie/commands/PlayerType.h"
#include "zombie/core/BoxedStaticValues.h"
#include "zombie/core/Core.h"
#include "zombie/core/Language.h"
#include "zombie/core/PerformanceSettings.h"
#include "zombie/core/Rand.h"
#include "zombie/core/SpriteRenderer.h"
#include "zombie/core/Translator.h"
#include "zombie/core/input/Input.h"
#include "zombie/core/logger/ExceptionLogger.h"
#include "zombie/core/logger/LoggerManager.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/opengl/RenderThread.h"
#include "zombie/core/physics/Bullet.h"
#include "zombie/core/physics/WorldSimulation.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/core/skinnedmodel/ModelManager.h"
#include "zombie/core/skinnedmodel/advancedanimation/AnimNodeAssetManager.h"
#include "zombie/core/skinnedmodel/advancedanimation/AnimationSet.h"
#include "zombie/core/skinnedmodel/model/Model.h"
#include "zombie/core/skinnedmodel/model/Model/ModelAssetParams.h"
#include "zombie/core/skinnedmodel/model/ModelAssetManager.h"
#include "zombie/core/skinnedmodel/model/WorldItemModelDrawer.h"
#include "zombie/core/skinnedmodel/population/BeardStyle.h"
#include "zombie/core/skinnedmodel/population/BeardStyles.h"
#include "zombie/core/skinnedmodel/population/ClothingDecalGroup.h"
#include "zombie/core/skinnedmodel/population/ClothingDecals.h"
#include "zombie/core/skinnedmodel/population/ClothingItem.h"
#include "zombie/core/skinnedmodel/population/HairStyle.h"
#include "zombie/core/skinnedmodel/population/HairStyles.h"
#include "zombie/core/skinnedmodel/population/Outfit.h"
#include "zombie/core/skinnedmodel/population/OutfitManager.h"
#include "zombie/core/textures/Texture.h"
#include "zombie/core/textures/TextureID.h"
#include "zombie/core/znet/GameServerDetails.h"
#include "zombie/core/znet/ServerBrowser.h"
#include "zombie/core/znet/SteamFriend.h"
#include "zombie/core/znet/SteamFriends.h"
#include "zombie/core/znet/SteamUser.h"
#include "zombie/core/znet/SteamUtils.h"
#include "zombie/core/znet/SteamWorkshop.h"
#include "zombie/core/znet/SteamWorkshopItem.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugOptions.h"
#include "zombie/debug/LineDrawer.h"
#include "zombie/erosion/ErosionData.h"
#include "zombie/erosion/ErosionMain.h"
#include "zombie/gameStates/AnimationViewerState.h"
#include "zombie/gameStates/AttachmentEditorState.h"
#include "zombie/gameStates/ChooseGameInfo.h"
#include "zombie/gameStates/ChooseGameInfo/Map.h"
#include "zombie/gameStates/ChooseGameInfo/Mod.h"
#include "zombie/gameStates/ConnectToServerState.h"
#include "zombie/gameStates/GameState.h"
#include "zombie/gameStates/IngameState.h"
#include "zombie/input/GameKeyboard.h"
#include "zombie/input/JoypadManager.h"
#include "zombie/input/JoypadManager/Joypad.h"
#include "zombie/input/Mouse.h"
#include "zombie/inventory/InventoryItem.h"
#include "zombie/inventory/InventoryItemFactory.h"
#include "zombie/inventory/ItemContainer.h"
#include "zombie/inventory/ItemPickerJava.h"
#include "zombie/inventory/ItemPickerJava/ItemPickerRoom.h"
#include "zombie/iso/BuildingDef.h"
#include "zombie/iso/CellLoader.h"
#include "zombie/iso/ContainerOverlays.h"
#include "zombie/iso/IsoCamera.h"
#include "zombie/iso/IsoCell.h"
#include "zombie/iso/IsoChunk.h"
#include "zombie/iso/IsoDirections.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoMarkers.h"
#include "zombie/iso/IsoMetaGrid/VehicleZone.h"
#include "zombie/iso/IsoMetaGrid/Zone.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/IsoPuddles.h"
#include "zombie/iso/IsoPuddles/PuddlesFloat.h"
#include "zombie/iso/IsoPushableObject.h"
#include "zombie/iso/IsoUtils.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/LightingJNI.h"
#include "zombie/iso/RoomDef.h"
#include "zombie/iso/SearchMode.h"
#include "zombie/iso/TileOverlays.h"
#include "zombie/iso/Vector2.h"
#include "zombie/iso/WorldMarkers.h"
#include "zombie/iso/areas/SafeHouse.h"
#include "zombie/iso/areas/isoregion/IsoRegionsRenderer.h"
#include "zombie/iso/objects/IsoDeadBody.h"
#include "zombie/iso/objects/IsoFireManager.h"
#include "zombie/iso/sprite/IsoSprite.h"
#include "zombie/iso/sprite/IsoSpriteManager.h"
#include "zombie/iso/weather/ClimateManager.h"
#include "zombie/iso/weather/ClimateMoon.h"
#include "zombie/modding/ActiveMods.h"
#include "zombie/modding/ActiveModsFile.h"
#include "zombie/modding/ModUtilsJava.h"
#include "zombie/network/ConnectionManager.h"
#include "zombie/network/CoopMaster.h"
#include "zombie/network/DesktopBrowser.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/ItemTransactionManager.h"
#include "zombie/network/MPStatistic.h"
#include "zombie/network/MPStatistics.h"
#include "zombie/network/NetworkAIParams.h"
#include "zombie/network/PacketTypes.h"
#include "zombie/network/Server.h"
#include "zombie/network/ServerOptions.h"
#include "zombie/network/ServerSettingsManager.h"
#include "zombie/network/ServerWorldDatabase.h"
#include "zombie/network/chat/ChatType.h"
#include "zombie/popman/ZombiePopulationManager.h"
#include "zombie/popman/ZombiePopulationRenderer.h"
#include "zombie/profanity/ProfanityFilter.h"
#include "zombie/radio/RadioAPI.h"
#include "zombie/radio/RadioData.h"
#include "zombie/radio/StorySounds/SLSoundManager.h"
#include "zombie/radio/ZomboidRadio.h"
#include "zombie/randomizedWorld/randomizedBuilding/RandomizedBuildingBase.h"
#include "zombie/randomizedWorld/randomizedBuilding/RandomizedBuildingBase/HumanCorpse.h"
#include "zombie/savefile/ClientPlayerDB.h"
#include "zombie/savefile/PlayerDBHelper.h"
#include "zombie/scripting/ScriptManager.h"
#include "zombie/scripting/objects/EvolvedRecipe.h"
#include "zombie/scripting/objects/Item.h"
#include "zombie/scripting/objects/Item/Type.h"
#include "zombie/scripting/objects/Recipe.h"
#include "zombie/scripting/objects/VehicleScript.h"
#include "zombie/scripting/objects/VehicleScript/Skin.h"
#include "zombie/spnetwork/SinglePlayerClient.h"
#include "zombie/ui/TextManager.h"
#include "zombie/ui/UIElement.h"
#include "zombie/ui/UIManager.h"
#include "zombie/util/AddCoopPlayer.h"
#include "zombie/util/PublicServerUtil.h"
#include "zombie/util/StringUtils.h"
#include "zombie/util/list/PZArrayUtil.h"
#include "zombie/vehicles/BaseVehicle.h"
#include "zombie/vehicles/EditVehicleState.h"
#include "zombie/vehicles/VehicleManager.h"
#include "zombie/vehicles/VehiclePart.h"
#include "zombie/vehicles/VehicleWindow.h"
#include "zombie/vehicles/VehiclesDB2.h"
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace Lua {


class LuaManager {
public:
    static FileOutputStream outStream;
    static FileInputStream inStream;
    static FileReader inFileReader = nullptr;
    static BufferedReader inBufferedReader = nullptr;
    static long timeLastRefresh = 0L;
    static const TimSortComparator timSortComparator = std::make_shared<TimSortComparator>();

    static Model loadVehicleModel(const std::string& var0, const std::string& var1, const std::string& var2) {
    return loadZomboidModel();
   }

    static Model loadStaticZomboidModel(const std::string& var0, const std::string& var1, const std::string& var2) {
    return loadZomboidModel();
   }

    static Model loadSkinnedZomboidModel(const std::string& var0, const std::string& var1, const std::string& var2) {
    return loadZomboidModel();
   }

    static Model loadZomboidModel(const std::string& var0, const std::string& var1, const std::string& var2, const std::string& var3, bool var4) {
      try {
         if (var1.startsWith("/")) {
            var1 = var1.substr(1);
         }

         if (var2.startsWith("/")) {
            var2 = var2.substr(1);
         }

         if (StringUtils.isNullOrWhitespace(var3)) {
            var3 = "basicEffect";
         }

         if ("vehicle" == var3) && !Core.getInstance().getPerfReflectionsOnLoad()) {
            var3 = var3 + "_noreflect";
         }

    Model var5 = ModelManager.instance.tryGetLoadedModel(var1, var2, var4, var3, false);
         if (var5 != nullptr) {
    return var5;
         } else {
            ModelManager.instance.setModelMetaData(var0, var1, var2, var3, var4);
    ModelAssetParams var6 = std::make_shared<ModelAssetParams>();
            var6.bStatic = var4;
            var6.meshName = var1;
            var6.shaderName = var3;
            var6.textureName = var2;
            var6.textureFlags = ModelManager.instance.getTextureFlags();
            var5 = (Model)ModelAssetManager.instance.load(std::make_shared<AssetPath>(var0), var6);
            if (var5 != nullptr) {
               ModelManager.instance.putLoadedModel(var1, var2, var4, var3, var5);
            }

    return var5;
         }
      } catch (Exception var7) {
         DebugLog.General
            .error(
               "LuaManager.loadZomboidModel> Exception thrown loading model: "
                  + var0
                  + " mesh:"
                  + var1
                  + " tex:"
                  + var2
                  + " shader:"
                  + var3
                  + " isStatic:"
                  + var4
            );
         var7.printStackTrace();
    return nullptr;
      }
   }

    static void setModelMetaData(const std::string& var0, const std::string& var1, const std::string& var2, const std::string& var3, bool var4) {
      if (var1.startsWith("/")) {
         var1 = var1.substr(1);
      }

      if (var2.startsWith("/")) {
         var2 = var2.substr(1);
      }

      ModelManager.instance.setModelMetaData(var0, var1, var2, var3, var4);
   }

    static void reloadModelsMatching(const std::string& var0) {
      ModelManager.instance.reloadModelsMatching(var0);
   }

    static SLSoundManager getSLSoundManager() {
    return nullptr;
   }

    static RadioAPI getRadioAPI() {
      return RadioAPI.hasInstance() ? RadioAPI.getInstance() : nullptr;
   }

   public static std::vector<std::string> getRadioTranslators(Language var0) {
      return RadioData.getTranslatorNames(var0);
   }

   public static std::vector<std::string> getTranslatorCredits(Language var0) {
    File var1 = std::make_shared<File>(ZomboidFileSystem.instance.getString("media/lua/shared/Translate/" + var0.name() + "/credits.txt"));

      try {
    std::vector var6;
         try (
    FileReader var2 = std::make_shared<FileReader>(var1, Charset.forName(var0.charset()));
    BufferedReader var3 = std::make_shared<BufferedReader>(var2);
         ) {
    std::vector var4 = new std::vector();

    std::string var5;
            while ((var5 = var3.readLine()) != nullptr) {
               if (!StringUtils.isNullOrWhitespace(var5)) {
                  var4.push_back(var5.trim());
               }
            }

            var6 = var4;
         }

    return var6;
      } catch (FileNotFoundException var11) {
    return nullptr;
      } catch (Exception var12) {
         ExceptionLogger.logException(var12);
    return nullptr;
      }
   }

    static IsoGameCharacter getBehaviourDebugPlayer() {
    return nullptr;
   }

    static void setBehaviorStep(bool var0) {
   }

    static IsoPuddles getPuddlesManager() {
      return IsoPuddles.getInstance();
   }

    static void setPuddles(float var0) {
    PuddlesFloat var1 = IsoPuddles.getInstance().getPuddlesFloat(3);
      var1.setEnableAdmin(true);
      var1.setAdminValue(var0);
      var1 = IsoPuddles.getInstance().getPuddlesFloat(1);
      var1.setEnableAdmin(true);
      var1.setAdminValue(PZMath.clamp_01(var0 * 1.2F));
   }

    static ZomboidRadio getZomboidRadio() {
      return ZomboidRadio.hasInstance() ? ZomboidRadio.getInstance() : nullptr;
   }

    static std::string getRandomUUID() {
      return ModUtilsJava.getRandomUUID();
   }

    static bool sendItemListNet(IsoPlayer var0, std::vector<InventoryItem> var1, IsoPlayer var2, const std::string& var3, const std::string& var4) {
      return ModUtilsJava.sendItemListNet(var0, var1, var2, var3, var4);
   }

    static bool instof(void* var0, const std::string& var1) {
      if ("PZKey" == var1)) {
    bool var2 = false;
      }

      if (var0 == nullptr) {
    return false;
      } else if (LuaManager.exposer.TypeMap.containsKey(var1)) {
    Class var3 = (Class)LuaManager.exposer.TypeMap.get(var1);
         return var3.isInstance(var0);
      } else {
         return var1 == "LuaClosure") && dynamic_cast<LuaClosure*>(var0) != nullptr ? true : var1 == "KahluaTableImpl") && dynamic_cast<KahluaTableImpl*>(var0) != nullptr;
      }
   }

    static void serverConnect(const std::string& var0, const std::string& var1, const std::string& var2, const std::string& var3, const std::string& var4, const std::string& var5, const std::string& var6, bool var7) {
      Core.GameMode = "Multiplayer";
      Core.setDifficulty("Hardcore");
      if (GameClient.connection != nullptr) {
         GameClient.connection.forceDisconnect("lua-connect");
      }

      GameClient.instance.resetDisconnectTimer();
      GameClient.bClient = true;
      GameClient.bCoopInvite = false;
      ZomboidFileSystem.instance.cleanMultiplayerSaves();
      GameClient.instance.doConnect(var0, var1, var2, var3, var4, var5, var6, var7);
   }

    static void serverConnectCoop(const std::string& var0) {
      Core.GameMode = "Multiplayer";
      Core.setDifficulty("Hardcore");
      if (GameClient.connection != nullptr) {
         GameClient.connection.forceDisconnect("lua-connect-coop");
      }

      GameClient.bClient = true;
      GameClient.bCoopInvite = true;
      GameClient.instance.doConnectCoop(var0);
   }

    static void sendPing() {
      if (GameClient.bClient) {
    ByteBufferWriter var0 = GameClient.connection.startPingPacket();
         PacketTypes.doPingPacket(var0);
         var0.putLong(System.currentTimeMillis());
         GameClient.connection.endPingPacket();
      }
   }

    static void connectionManagerLog(const std::string& var0, const std::string& var1) {
      ConnectionManager.log(var0, var1, nullptr);
   }

    static void forceDisconnect() {
      if (GameClient.connection != nullptr) {
         GameClient.connection.forceDisconnect("lua-force-disconnect");
      }
   }

    static void backToSinglePlayer() {
      if (GameClient.bClient) {
         GameClient.instance.doDisconnect("going back to single-player");
         GameClient.bClient = false;
         timeLastRefresh = 0L;
      }
   }

    static bool isIngameState() {
      return GameWindow.states.current == IngameState.instance;
   }

    static void requestPacketCounts() {
      if (GameClient.bClient) {
         GameClient.instance.requestPacketCounts();
      }
   }

    static bool canConnect() {
      return GameClient.instance.canConnect();
   }

    static std::string getReconnectCountdownTimer() {
      return GameClient.instance.getReconnectCountdownTimer();
   }

    static KahluaTable getPacketCounts(int var0) {
      return GameClient.bClient ? PacketTypes.getPacketCounts(var0) : nullptr;
   }

   public static std::vector<Item> getAllItems() {
      return ScriptManager.instance.getAllItems();
   }

    static void scoreboardUpdate() {
      GameClient.instance.scoreboardUpdate();
   }

    static void save(bool var0) {
      try {
         GameWindow.save(var0);
      } catch (Throwable var2) {
         ExceptionLogger.logException(var2);
      }
   }

    static void saveGame() {
      save(true);
   }

   public static std::vector<Recipe> getAllRecipes() {
      return new std::vector<>(ScriptManager.instance.getAllRecipes());
   }

    static void requestUserlog(const std::string& var0) {
      if (GameClient.bClient) {
         GameClient.instance.requestUserlog(var0);
      }
   }

    static void addUserlog(const std::string& var0, const std::string& var1, const std::string& var2) {
      if (GameClient.bClient) {
         GameClient.instance.addUserlog(var0, var1, var2);
      }
   }

    static void removeUserlog(const std::string& var0, const std::string& var1, const std::string& var2) {
      if (GameClient.bClient) {
         GameClient.instance.removeUserlog(var0, var1, var2);
      }
   }

    static std::string tabToX(const std::string& var0, int var1) {
      while (var0.length() < var1) {
         var0 = var0 + " ";
      }

    return var0;
   }

    static bool isType(void* var0, const std::string& var1) {
      if (LuaManager.exposer.TypeMap.containsKey(var1)) {
    Class var2 = (Class)LuaManager.exposer.TypeMap.get(var1);
         return var2 == var0.getClass());
      } else {
    return false;
      }
   }

    static float isoToScreenX(int var0, float var1, float var2, float var3) {
    float var4 = IsoUtils.XToScreen(var1, var2, var3, 0) - IsoCamera.cameras[var0].getOffX();
      var4 /= Core.getInstance().getZoom(var0);
      return IsoCamera.getScreenLeft(var0) + var4;
   }

    static float isoToScreenY(int var0, float var1, float var2, float var3) {
    float var4 = IsoUtils.YToScreen(var1, var2, var3, 0) - IsoCamera.cameras[var0].getOffY();
      var4 /= Core.getInstance().getZoom(var0);
      return IsoCamera.getScreenTop(var0) + var4;
   }

    static float screenToIsoX(int var0, float var1, float var2, float var3) {
    float var4 = Core.getInstance().getZoom(var0);
      var1 -= IsoCamera.getScreenLeft(var0);
      var2 -= IsoCamera.getScreenTop(var0);
      return IsoCamera.cameras[var0].XToIso(var1 * var4, var2 * var4, var3);
   }

    static float screenToIsoY(int var0, float var1, float var2, float var3) {
    float var4 = Core.getInstance().getZoom(var0);
      var1 -= IsoCamera.getScreenLeft(var0);
      var2 -= IsoCamera.getScreenTop(var0);
      return IsoCamera.cameras[var0].YToIso(var1 * var4, var2 * var4, var3);
   }

    static BaseAmbientStreamManager getAmbientStreamManager() {
      return AmbientStreamManager.instance;
   }

    static SleepingEvent getSleepingEvent() {
      return SleepingEvent.instance;
   }

    static void setPlayerMovementActive(int var0, bool var1) {
      IsoPlayer.players[var0].bJoypadMovementActive = var1;
   }

    static void setActivePlayer(int var0) {
      if (!GameClient.bClient) {
         IsoPlayer.setInstance(IsoPlayer.players[var0]);
         IsoCamera.CamCharacter = IsoPlayer.getInstance();
      }
   }

    static IsoPlayer getPlayer() {
      return IsoPlayer.getInstance();
   }

    static int getNumActivePlayers() {
      return IsoPlayer.numPlayers;
   }

    static void playServerSound(const std::string& var0, IsoGridSquare var1) {
      GameServer.PlayWorldSoundServer(var0, false, var1, 0.2F, 5.0F, 1.1F, true);
   }

    static int getMaxActivePlayers() {
    return 4;
   }

    static int getPlayerScreenLeft(int var0) {
      return IsoCamera.getScreenLeft(var0);
   }

    static int getPlayerScreenTop(int var0) {
      return IsoCamera.getScreenTop(var0);
   }

    static int getPlayerScreenWidth(int var0) {
      return IsoCamera.getScreenWidth(var0);
   }

    static int getPlayerScreenHeight(int var0) {
      return IsoCamera.getScreenHeight(var0);
   }

    static IsoPlayer getPlayerByOnlineID(int var0) {
      if (GameServer.bServer) {
         return (IsoPlayer)GameServer.IDToPlayerMap.get((short)var0);
      } else {
         return GameClient.bClient ? (IsoPlayer)GameClient.IDToPlayerMap.get((short)var0) : nullptr;
      }
   }

    static void initUISystem() {
      UIManager.init();
      LuaEventManager.triggerEvent("OnCreatePlayer", 0, IsoPlayer.players[0]);
   }

    static PerformanceSettings getPerformance() {
      return PerformanceSettings.instance;
   }

    static void getDBSchema() {
      GameClient.instance.getDBSchema();
   }

    static void getTableResult(const std::string& var0, int var1) {
      GameClient.instance.getTableResult(var0, var1);
   }

    static WorldSoundManager getWorldSoundManager() {
      return WorldSoundManager.instance;
   }

    static void AddWorldSound(IsoPlayer var0, int var1, int var2) {
      WorldSoundManager.instance.addSound(nullptr, (int)var0.getX(), (int)var0.getY(), (int)var0.getZ(), var1, var2, false);
   }

    static void AddNoiseToken(IsoGridSquare var0, int var1) {
   }

    static void pauseSoundAndMusic() {
      DebugLog.log("EXITDEBUG: pauseSoundAndMusic 1");
      SoundManager.instance.pauseSoundAndMusic();
      DebugLog.log("EXITDEBUG: pauseSoundAndMusic 2");
   }

    static void resumeSoundAndMusic() {
      SoundManager.instance.resumeSoundAndMusic();
   }

    static bool isDemo() {
      Core.getInstance();
    return false;
   }

    static long getTimeInMillis() {
      return System.currentTimeMillis();
   }

    static Coroutine getCurrentCoroutine() {
      return LuaManager.thread.getCurrentCoroutine();
   }

    static void reloadLuaFile(const std::string& var0) {
      LuaManager.loaded.remove(var0);
      LuaManager.RunLua(var0, true);
   }

    static void reloadServerLuaFile(const std::string& var0) {
      if (GameServer.bServer) {
         var0 = ZomboidFileSystem.instance.getCacheDir() + File.separator + "Server" + File.separator + var0;
         LuaManager.loaded.remove(var0);
         LuaManager.RunLua(var0, true);
      }
   }

    static KahluaTable getServerSpawnRegions() {
      return !GameClient.bClient ? nullptr : GameClient.instance.getServerSpawnRegions();
   }

    static ServerOptions getServerOptions() {
      return ServerOptions.instance;
   }

    static std::string getServerName() {
      if (GameServer.bServer) {
         return GameServer.ServerName;
      } else {
         return GameClient.bClient ? GameClient.ServerName : "";
      }
   }

    static std::string getServerIP() {
      if (GameServer.bServer) {
         return GameServer.IPCommandline == nullptr ? GameServer.ip : GameServer.IPCommandline;
      } else {
         return GameClient.bClient ? GameClient.ip : "";
      }
   }

    static std::string getServerPort() {
      if (GameServer.bServer) {
         return std::string.valueOf(GameServer.DEFAULT_PORT);
      } else {
         return GameClient.bClient ? std::string.valueOf(GameClient.port) : "";
      }
   }

    static bool isShowConnectionInfo() {
      return NetworkAIParams.isShowConnectionInfo();
   }

    static void setShowConnectionInfo(bool var0) {
      NetworkAIParams.setShowConnectionInfo(var0);
   }

    static bool isShowServerInfo() {
      return NetworkAIParams.isShowServerInfo();
   }

    static void setShowServerInfo(bool var0) {
      NetworkAIParams.setShowServerInfo(var0);
   }

    static bool isShowPingInfo() {
      return NetworkAIParams.isShowPingInfo();
   }

    static void setShowPingInfo(bool var0) {
      NetworkAIParams.setShowPingInfo(var0);
   }

    static IsoPlayer getSpecificPlayer(int var0) {
      return IsoPlayer.players[var0];
   }

    static float getCameraOffX() {
      return IsoCamera.getOffX();
   }

    static KahluaTable getLatestSave() {
    KahluaTable var0 = LuaManager.platform.newTable();
    BufferedReader var1 = nullptr;

      try {
         var1 = std::make_shared<BufferedReader>(std::make_shared<FileReader>(std::make_shared<File>(ZomboidFileSystem.instance.getCacheDir() + File.separator + "latestSave.ini")));
      } catch (FileNotFoundException var4) {
    return var0;
      }

      try {
    void* var2 = nullptr;

         for (int var3 = 1; (var2 = var1.readLine()) != nullptr; var3++) {
            var0.rawset(var3, var2);
         }

         var1.close();
    return var0;
      } catch (Exception var5) {
    return var0;
      }
   }

    static bool isCurrentExecutionPoint(const std::string& var0, int var1) {
    int var2 = LuaManager.thread.currentCoroutine.getCallframeTop() - 1;
      if (var2 < 0) {
         var2 = 0;
      }

    LuaCallFrame var3 = LuaManager.thread.currentCoroutine.getCallFrame(var2);
      return var3.closure == nullptr ? false : var3.closure.prototype.lines[var3.pc] == var1 && var0 == var3.closure.prototype.filename);
   }

    static void toggleBreakOnChange(KahluaTable var0, void* var1) {
      if (Core.bDebug) {
         LuaManager.thread.toggleBreakOnChange(var0, var1);
      }
   }

    static bool isDebugEnabled() {
      return Core.bDebug;
   }

    static void toggleBreakOnRead(KahluaTable var0, void* var1) {
      if (Core.bDebug) {
         LuaManager.thread.toggleBreakOnRead(var0, var1);
      }
   }

    static void toggleBreakpoint(const std::string& var0, int var1) {
      var0 = var0.replace("\\", "/");
      if (Core.bDebug) {
         LuaManager.thread.breakpointToggle(var0, var1);
      }
   }

    static void sendVisual(IsoPlayer var0) {
      if (GameClient.bClient) {
         GameClient.instance.sendVisual(var0);
      }
   }

    static void sendClothing(IsoPlayer var0) {
      if (GameClient.bClient) {
         GameClient.instance.sendClothing(var0, "", nullptr);
      }
   }

    static bool hasDataReadBreakpoint(KahluaTable var0, void* var1) {
      return LuaManager.thread.hasReadDataBreakpoint(var0, var1);
   }

    static bool hasDataBreakpoint(KahluaTable var0, void* var1) {
      return LuaManager.thread.hasDataBreakpoint(var0, var1);
   }

    static bool hasBreakpoint(const std::string& var0, int var1) {
      return LuaManager.thread.hasBreakpoint(var0, var1);
   }

    static int getLoadedLuaCount() {
      return LuaManager.loaded.size();
   }

    static std::string getLoadedLua(int var0) {
      return (std::string)LuaManager.loaded.get(var0);
   }

    static bool isServer() {
      return GameServer.bServer;
   }

    static bool isServerSoftReset() {
      return GameServer.bServer && GameServer.bSoftReset;
   }

    static bool isClient() {
      return GameClient.bClient;
   }

    static bool canModifyPlayerStats() {
      return !GameClient.bClient ? true : GameClient.canModifyPlayerStats();
   }

    static void executeQuery(const std::string& var0, KahluaTable var1) {
      GameClient.instance.executeQuery(var0, var1);
   }

    static bool canSeePlayerStats() {
      return GameClient.canSeePlayerStats();
   }

    static std::string getAccessLevel() {
      return PlayerType.toString(GameClient.connection.accessLevel);
   }

   public static std::vector<IsoPlayer> getOnlinePlayers() {
      if (GameServer.bServer) {
         return GameServer.getPlayers();
      } else {
         return GameClient.bClient ? GameClient.instance.getPlayers() : nullptr;
      }
   }

    static bool getDebug() {
      return Core.bDebug || GameServer.bServer && GameServer.bDebug;
   }

    static float getCameraOffY() {
      return IsoCamera.getOffY();
   }

    static KahluaTable createRegionFile() {
    KahluaTable var0 = LuaManager.platform.newTable();
    std::string var1 = IsoWorld.instance.getMap();
      if (var1 == "DEFAULT")) {
    MapGroups var2 = std::make_shared<MapGroups>();
         var2.createGroups();
         if (var2.getNumberOfGroups() != 1) {
            throw RuntimeException("GameMap is DEFAULT but there are multiple worlds to choose from");
         }

         var2.setWorld(0);
         var1 = IsoWorld.instance.getMap();
      }

      if (!GameClient.bClient && !GameServer.bServer) {
         var1 = MapGroups.addMissingVanillaDirectories(var1);
      }

      std::string[] var10 = var1.split(";");
    int var3 = 1;

    for (auto& var7 : var10)         var7 = var7.trim();
         if (!var7.empty()) {
    File var8 = std::make_shared<File>(ZomboidFileSystem.instance.getString("media/maps/" + var7 + "/spawnpoints.lua"));
            if (var8.exists()) {
    KahluaTable var9 = LuaManager.platform.newTable();
               var9.rawset("name", var7);
               var9.rawset("file", "media/maps/" + var7 + "/spawnpoints.lua");
               var0.rawset(var3, var9);
               var3++;
            }
         }
      }

    return var0;
   }

    static KahluaTable getMapDirectoryTable() {
    KahluaTable var0 = LuaManager.platform.newTable();
    File var1 = ZomboidFileSystem.instance.getMediaFile("maps");
      std::string[] var2 = var1.list();
      if (var2 == nullptr) {
    return var0;
      } else {
    int var3 = 1;

         for (int var4 = 0; var4 < var2.length; var4++) {
    std::string var5 = var2[var4];
            if (!var5 == "challengemaps")) {
               var0.rawset(var3, var5);
               var3++;
            }
         }

         for (std::string var14 : ZomboidFileSystem.instance.getModIDs()) {
    Mod var6 = nullptr;

            try {
               var6 = ChooseGameInfo.getAvailableModDetails(var14);
            } catch (Exception var10) {
            }

            if (var6 != nullptr) {
               var1 = std::make_shared<File>(var6.getDir() + "/media/maps/");
               if (var1.exists()) {
                  var2 = var1.list();
                  if (var2 != nullptr) {
                     for (int var7 = 0; var7 < var2.length; var7++) {
    std::string var8 = var2[var7];
    std::unordered_map var9 = ChooseGameInfo.getMapDetails(var8);
                        if (var9.getLotDirectories() != nullptr && !var9.getLotDirectories().empty() && !var8 == "challengemaps")) {
                           var0.rawset(var3, var8);
                           var3++;
                        }
                     }
                  }
               }
            }
         }

    return var0;
      }
   }

    static void deleteSave(const std::string& var0) {
      if (StringUtils.containsDoubleDot(var0)) {
         DebugLog.Lua.warn("relative paths not allowed");
      } else {
    File var1 = std::make_shared<File>(ZomboidFileSystem.instance.getSaveDirSub(var0));
         std::string[] var2 = var1.list();
         if (var2 != nullptr) {
            for (int var3 = 0; var3 < var2.length; var3++) {
    File var4 = std::make_shared<File>(ZomboidFileSystem.instance.getSaveDirSub(var0 + File.separator + var2[var3]));
               if (var4.isDirectory()) {
                  deleteSave(var0 + File.separator + var4.getName());
               }

               var4.delete();
            }

            var1.delete();
         }
      }
   }

    static void sendPlayerExtraInfo(IsoPlayer var0) {
      GameClient.sendPlayerExtraInfo(var0);
   }

    static std::string getServerAddressFromArgs() {
      if (System.getProperty("args.server.connect") != nullptr) {
    std::string var0 = System.getProperty("args.server.connect");
         System.clearProperty("args.server.connect");
    return var0;
      } else {
    return nullptr;
      }
   }

    static std::string getServerPasswordFromArgs() {
      if (System.getProperty("args.server.password") != nullptr) {
    std::string var0 = System.getProperty("args.server.password");
         System.clearProperty("args.server.password");
    return var0;
      } else {
    return nullptr;
      }
   }

    static std::string getServerListFile() {
      return SteamUtils.isSteamModeEnabled() ? "ServerListSteam.txt" : "ServerList.txt";
   }

    static KahluaTable getServerList() {
    std::vector var0 = new std::vector();
    KahluaTable var1 = LuaManager.platform.newTable();
    BufferedReader var2 = nullptr;

      try {
    File var3 = std::make_shared<File>(LuaManager.getLuaCacheDir() + File.separator + getServerListFile());
         if (!var3.exists()) {
            var3.createNewFile();
         }

         var2 = std::make_shared<BufferedReader>(std::make_shared<FileReader>(var3, StandardCharsets.UTF_8));
    void* var4 = nullptr;
    Server var5 = nullptr;

         while ((var4 = var2.readLine()) != nullptr) {
            if (var4.startsWith("name=")) {
               var5 = std::make_unique<Server>();
               var0.push_back(var5);
               var5.setName(var4.replaceFirst("name=", ""));
            } else if (var4.startsWith("ip=")) {
               var5.setIp(var4.replaceFirst("ip=", ""));
            } else if (var4.startsWith("localip=")) {
               var5.setLocalIP(var4.replaceFirst("localip=", ""));
            } else if (var4.startsWith("description=")) {
               var5.setDescription(var4.replaceFirst("description=", ""));
            } else if (var4.startsWith("port=")) {
               var5.setPort(var4.replaceFirst("port=", ""));
            } else if (var4.startsWith("user=")) {
               var5.setUserName(var4.replaceFirst("user=", ""));
            } else if (var4.startsWith("password=")) {
               var5.setPwd(var4.replaceFirst("password=", ""));
            } else if (var4.startsWith("serverpassword=")) {
               var5.setServerPassword(var4.replaceFirst("serverpassword=", ""));
            } else if (var4.startsWith("usesteamrelay=")) {
               var5.setUseSteamRelay(bool.parseBoolean(var4.replaceFirst("usesteamrelay=", "")));
            }
         }

    int var6 = 1;

         for (int var7 = 0; var7 < var0.size(); var7++) {
    Server var8 = (Server)var0.get(var7);
    double var9 = (double)var6;
            var1.rawset(var9, var8);
            var6++;
         }
      } catch (Exception var18) {
         var18.printStackTrace();
      } finally {
         try {
            var2.close();
         } catch (Exception var17) {
         }
      }

    return var1;
   }

    static void ping(const std::string& var0, const std::string& var1, const std::string& var2, const std::string& var3) {
      GameClient.askPing = true;
      serverConnect(var0, var1, var2, "", var3, "", "", false);
   }

    static void stopPing() {
      GameClient.askPing = false;
   }

    static KahluaTable transformIntoKahluaTable(Object> var0) {
    KahluaTable var1 = LuaManager.platform.newTable();

      for (Entry var3 : var0.entrySet()) {
         var1.rawset(var3.getKey(), var3.getValue());
      }

    return var1;
   }

   public static std::vector<File> getSaveDirectory(std::string var0) {
    File var1 = std::make_shared<File>(var0 + File.separator);
      if (!var1.exists() && !Core.getInstance().isNoSave()) {
         var1.mkdir();
      }

      std::string[] var2 = var1.list();
      if (var2 == nullptr) {
    return nullptr;
      } else {
    std::vector var3 = new std::vector();

         for (int var4 = 0; var4 < var2.length; var4++) {
    File var5 = std::make_shared<File>(var0 + File.separator + var2[var4]);
            if (var5.isDirectory()) {
               var3.push_back(var5);
            }
         }

    return var3;
      }
   }

    static KahluaTable getFullSaveDirectoryTable() {
    KahluaTable var0 = LuaManager.platform.newTable();
    File var1 = std::make_shared<File>(ZomboidFileSystem.instance.getSaveDir() + File.separator);
      if (!var1.exists()) {
         var1.mkdir();
      }

      std::string[] var2 = var1.list();
      if (var2 == nullptr) {
    return var0;
      } else {
    std::vector var3 = new std::vector();

         for (int var4 = 0; var4 < var2.length; var4++) {
    File var5 = std::make_shared<File>(ZomboidFileSystem.instance.getSaveDir() + File.separator + var2[var4]);
            if (var5.isDirectory() && !"Multiplayer" == var2[var4])) {
    std::vector var6 = getSaveDirectory(ZomboidFileSystem.instance.getSaveDir() + File.separator + var2[var4]);
               var3.addAll(var6);
            }
         }

         Collections.sort(var3, std::make_unique<1>());
    int var9 = 1;

         for (int var10 = 0; var10 < var3.size(); var10++) {
    File var11 = (File)var3.get(var10);
    std::string var7 = getSaveName(var11);
    double var8 = (double)var9;
            var0.rawset(var8, var7);
            var9++;
         }

    return var0;
      }
   }

    static std::string getSaveName(File var0) {
      std::string[] var1 = var0.getAbsolutePath().split("\\" + File.separator);
      return var1[var1.length - 2] + File.separator + var0.getName();
   }

    static KahluaTable getSaveDirectoryTable() {
      return LuaManager.platform.newTable();
   }

   public static List<std::string> getMods() {
    std::vector var0 = new std::vector();
      ZomboidFileSystem.instance.getAllModFolders(var0);
    return var0;
   }

    static void doChallenge(KahluaTable var0) {
      Core.GameMode = var0.rawget("gameMode");
      Core.ChallengeID = var0.rawget("id");
      Core.bLastStand = Core.GameMode == "LastStand");
      Core.getInstance().setChallenge(true);
      getWorld().setMap(var0.getString("world"));
    int var1 = Rand.Next(100000000);
      IsoWorld.instance.setWorld(var1);
      getWorld().bDoChunkMapUpdate = false;
   }

    static void doTutorial(KahluaTable var0) {
      Core.GameMode = "Tutorial";
      Core.bLastStand = false;
      Core.ChallengeID = nullptr;
      Core.getInstance().setChallenge(false);
      Core.bTutorial = true;
      getWorld().setMap(var0.getString("world"));
      getWorld().bDoChunkMapUpdate = false;
   }

    static void deleteAllGameModeSaves(const std::string& var0) {
    std::string var1 = Core.GameMode;
      Core.GameMode = var0;
    Path var2 = Paths.get(ZomboidFileSystem.instance.getGameModeCacheDir());
      if (!Files.exists(var2)) {
         Core.GameMode = var1;
      } else {
         try {
            Files.walkFileTree(var2, std::make_unique<3>());
         } catch (IOException var4) {
            var4.printStackTrace();
         }

         Core.GameMode = var1;
      }
   }

    static void sledgeDestroy(IsoObject var0) {
      if (GameClient.bClient) {
         GameClient.destroy(var0);
      }
   }

    static void getTickets(const std::string& var0) {
      if (GameClient.bClient) {
         GameClient.getTickets(var0);
      }
   }

    static void addTicket(const std::string& var0, const std::string& var1, int var2) {
      if (GameClient.bClient) {
         GameClient.addTicket(var0, var1, var2);
      }
   }

    static void removeTicket(int var0) {
      if (GameClient.bClient) {
         GameClient.removeTicket(var0);
      }
   }

    static void sendFactionInvite(Faction var0, IsoPlayer var1, const std::string& var2) {
      if (GameClient.bClient) {
         GameClient.sendFactionInvite(var0, var1, var2);
      }
   }

    static void acceptFactionInvite(Faction var0, const std::string& var1) {
      if (GameClient.bClient) {
         GameClient.acceptFactionInvite(var0, var1);
      }
   }

    static void sendSafehouseInvite(SafeHouse var0, IsoPlayer var1, const std::string& var2) {
      if (GameClient.bClient) {
         GameClient.sendSafehouseInvite(var0, var1, var2);
      }
   }

    static void acceptSafehouseInvite(SafeHouse var0, const std::string& var1) {
      if (GameClient.bClient) {
         GameClient.acceptSafehouseInvite(var0, var1);
      }
   }

    static void createHordeFromTo(float var0, float var1, float var2, float var3, int var4) {
      ZombiePopulationManager.instance.createHordeFromTo((int)var0, (int)var1, (int)var2, (int)var3, var4);
   }

    static void createHordeInAreaTo(int var0, int var1, int var2, int var3, int var4, int var5, int var6) {
      ZombiePopulationManager.instance.createHordeInAreaTo(var0, var1, var2, var3, var4, var5, var6);
   }

    static void spawnHorde(float var0, float var1, float var2, float var3, float var4, int var5) {
      for (int var6 = 0; var6 < var5; var6++) {
         VirtualZombieManager.instance.choices.clear();
    IsoGridSquare var7 = IsoWorld.instance.CurrentCell.getGridSquare(Rand.Next(var0, var2), Rand.Next(var1, var3), var4);
         if (var7 != nullptr) {
            VirtualZombieManager.instance.choices.push_back(var7);
    IsoZombie var8 = VirtualZombieManager.instance.createRealZombieAlways(IsoDirections.fromIndex(Rand.Next(IsoDirections.Max.index())).index(), false);
            var8.dressInRandomOutfit();
            ZombieSpawnRecorder.instance.record(var8, "LuaManager.spawnHorde");
         }
      }
   }

    static IsoZombie createZombie(float var0, float var1, float var2, SurvivorDesc var3, int var4, IsoDirections var5) {
      VirtualZombieManager.instance.choices.clear();
    IsoGridSquare var6 = IsoWorld.instance.CurrentCell.getGridSquare(var0, var1, var2);
      VirtualZombieManager.instance.choices.push_back(var6);
    IsoZombie var7 = VirtualZombieManager.instance.createRealZombieAlways(var5.index(), false);
      ZombieSpawnRecorder.instance.record(var7, "LuaManager.createZombie");
    return var7;
   }

    static void triggerEvent(const std::string& var0) {
      LuaEventManager.triggerEvent(var0);
   }

    static void triggerEvent(const std::string& var0, void* var1) {
      LuaEventManager.triggerEventGarbage(var0, var1);
   }

    static void triggerEvent(const std::string& var0, void* var1, void* var2) {
      LuaEventManager.triggerEventGarbage(var0, var1, var2);
   }

    static void triggerEvent(const std::string& var0, void* var1, void* var2, void* var3) {
      LuaEventManager.triggerEventGarbage(var0, var1, var2, var3);
   }

    static void triggerEvent(const std::string& var0, void* var1, void* var2, void* var3, void* var4) {
      LuaEventManager.triggerEventGarbage(var0, var1, var2, var3, var4);
   }

    static void debugLuaTable(void* var0, int var1) {
      if (var1 <= 1) {
         if (dynamic_cast<KahluaTable*>(var0) != nullptr var2) {
    KahluaTableIterator var3 = var2.iterator();
    void* var4 = "";

            for (int var5 = 0; var5 < var1; var5++) {
               var4 = var4 + "\t";
            }

            do {
    void* var7 = var3.getKey();
    void* var6 = var3.getValue();
               if (var7 != nullptr) {
                  if (var6 != nullptr) {
                     DebugLog.Lua.debugln(var4 + var7 + " : " + var6);
                  }

                  if (dynamic_cast<KahluaTable*>(var6) != nullptr) {
                     debugLuaTable(var6, var1 + 1);
                  }
               }
            } while (var3.advance());

            if (var2.getMetatable() != nullptr) {
               debugLuaTable(var2.getMetatable(), var1);
            }
         }
      }
   }

    static void debugLuaTable(void* var0) {
      debugLuaTable(var0, 0);
   }

    static void sendItemsInContainer(IsoObject var0, ItemContainer var1) {
      GameServer.sendItemsInContainer(var0, var1 == nullptr ? var0.getContainer() : var1);
   }

    static KahluaTable getModDirectoryTable() {
    KahluaTable var0 = LuaManager.platform.newTable();
    std::vector var1 = getMods();
    int var2 = 1;

      for (int var3 = 0; var3 < var1.size(); var3++) {
    std::string var4 = (std::string)var1.get(var3);
    double var5 = (double)var2;
         var0.rawset(var5, var4);
         var2++;
      }

    return var0;
   }

    static Mod getModInfoByID(const std::string& var0) {
      try {
         return ChooseGameInfo.getModDetails(var0);
      } catch (Exception var2) {
         var2.printStackTrace();
    return nullptr;
      }
   }

    static Mod getModInfo(const std::string& var0) {
      try {
         return ChooseGameInfo.readModInfo(var0);
      } catch (Exception var2) {
         ExceptionLogger.logException(var2);
    return nullptr;
      }
   }

   public static std::vector<std::string> getMapFoldersForMod(std::string var0) {
      try {
    Mod var1 = ChooseGameInfo.getModDetails(var0);
         if (var1 == nullptr) {
    return nullptr;
         } else {
    std::string var2 = var1.getDir() + File.separator + "media" + File.separator + "maps";
    File var3 = std::make_shared<File>(var2);
            if (var3.exists() && var3.isDirectory()) {
    std::vector var4 = nullptr;

               try (DirectoryStream var5 = Files.newDirectoryStream(var3.toPath())) {
    for (auto& var7 : var5)                     if (Files.isDirectory(var7)) {
                        var3 = std::make_shared<File>(var2 + File.separator + var7.getFileName() + File.separator + "map.info");
                        if (var3.exists()) {
                           if (var4 == nullptr) {
                              var4 = std::make_unique<std::vector>();
                           }

                           var4.push_back(var7.getFileName());
                        }
                     }
                  }
               }

    return var4;
            } else {
    return nullptr;
            }
         }
      } catch (Exception var10) {
         var10.printStackTrace();
    return nullptr;
      }
   }

    static bool spawnpointsExistsForMod(const std::string& var0, const std::string& var1) {
      try {
    Mod var2 = ChooseGameInfo.getModDetails(var0);
         if (var2 == nullptr) {
    return false;
         } else {
    std::string var3 = var2.getDir() + File.separator + "media" + File.separator + "maps" + File.separator + var1 + File.separator + "spawnpoints.lua";
            return std::make_shared<File>(var3).exists();
         }
      } catch (Exception var4) {
         var4.printStackTrace();
    return false;
      }
   }

    static std::string getFileSeparator() {
      return File.separator;
   }

    static ScriptManager getScriptManager() {
      return ScriptManager.instance;
   }

    static bool checkSaveFolderExists(const std::string& var0) {
    File var1 = std::make_shared<File>(ZomboidFileSystem.instance.getSaveDir() + File.separator + var0);
      return var1.exists();
   }

    static std::string getAbsoluteSaveFolderName(const std::string& var0) {
    File var1 = std::make_shared<File>(ZomboidFileSystem.instance.getSaveDir() + File.separator + var0);
      return var1.getAbsolutePath();
   }

    static bool checkSaveFileExists(const std::string& var0) {
    File var1 = std::make_shared<File>(ZomboidFileSystem.instance.getFileNameInCurrentSave(var0));
      return var1.exists();
   }

    static bool checkSavePlayerExists() {
      if (!GameClient.bClient) {
         return PlayerDBHelper.isPlayerAlive(ZomboidFileSystem.instance.getCurrentSaveDir(), 1);
      } else {
         return ClientPlayerDB.getInstance() == nullptr
            ? false
            : ClientPlayerDB.getInstance().clientLoadNetworkPlayer() && ClientPlayerDB.getInstance().isAliveMainNetworkPlayer();
      }
   }

    static bool fileExists(const std::string& var0) {
    std::string var1 = var0.replace("/", File.separator);
      var1 = var1.replace("\\", File.separator);
    File var2 = std::make_shared<File>(ZomboidFileSystem.instance.getString(var1));
      return var2.exists();
   }

    static bool serverFileExists(const std::string& var0) {
    std::string var1 = var0.replace("/", File.separator);
      var1 = var1.replace("\\", File.separator);
    File var2 = std::make_shared<File>(ZomboidFileSystem.instance.getCacheDir() + File.separator + "Server" + File.separator + var1);
      return var2.exists();
   }

    static void takeScreenshot() {
      Core.getInstance().TakeFullScreenshot(nullptr);
   }

    static void takeScreenshot(const std::string& var0) {
      Core.getInstance().TakeFullScreenshot(var0);
   }

    static bool checkStringPattern(const std::string& var0) {
      return !var0.contains("[");
   }

    static InventoryItem instanceItem(Item var0) {
      return InventoryItemFactory.CreateItem(var0.moduleDotType);
   }

    static InventoryItem instanceItem(const std::string& var0) {
      return InventoryItemFactory.CreateItem(var0);
   }

    static Item createNewScriptItem(const std::string& var0, const std::string& var1, const std::string& var2, const std::string& var3, const std::string& var4) {
    Item var5 = std::make_shared<Item>();
      var5.module = ScriptManager.instance.getModule(var0);
      var5.module.ItemMap.put(var1, var5);
      var5.Icon = "Item_" + var4;
      var5.DisplayName = var2;
      var5.name = var1;
      var5.moduleDotType = var5.module.name + "." + var1;

      try {
         var5.type = Type.valueOf(var3);
      } catch (Exception var7) {
      }

    return var5;
   }

    static Item cloneItemType(const std::string& var0, const std::string& var1) {
    Item var2 = ScriptManager.instance.FindItem(var1);
    Item var3 = std::make_shared<Item>();
      var3.module = var2.getModule();
      var3.module.ItemMap.put(var0, var3);
    return var3;
   }

    static std::string moduleDotType(const std::string& var0, const std::string& var1) {
      return StringUtils.moduleDotType(var0, var1);
   }

    static void* require(const std::string& var0) {
    std::string var1 = var0;
      if (!var0.endsWith(".lua")) {
         var1 = var0 + ".lua";
      }

      for (int var2 = 0; var2 < LuaManager.paths.size(); var2++) {
    std::string var3 = (std::string)LuaManager.paths.get(var2);
    std::string var4 = ZomboidFileSystem.instance.getAbsolutePath(var3 + var1);
         if (var4 != nullptr) {
            return LuaManager.RunLua(ZomboidFileSystem.instance.getString(var4));
         }
      }

      DebugLog.Lua.warn("require(\"" + var0 + "\") failed");
    return nullptr;
   }

    static SpriteRenderer getRenderer() {
      return SpriteRenderer.instance;
   }

    static GameTime getGameTime() {
      return GameTime.instance;
   }

    static KahluaTable getStatistics() {
      return MPStatistics.getLuaStatistics();
   }

    static KahluaTable getMPStatus() {
      return MPStatistics.getLuaStatus();
   }

    static double getMaxPlayers() {
      return (double)GameClient.connection.maxPlayers;
   }

    static IsoWorld getWorld() {
      return IsoWorld.instance;
   }

    static IsoCell getCell() {
      return IsoWorld.instance.getCell();
   }

    static SandboxOptions getSandboxOptions() {
      return SandboxOptions.instance;
   }

    static DataOutputStream getFileOutput(const std::string& var0) {
      if (StringUtils.containsDoubleDot(var0)) {
         DebugLog.Lua.warn("relative paths not allowed");
    return nullptr;
      } else {
    std::string var1 = LuaManager.getLuaCacheDir() + File.separator + var0;
         var1 = var1.replace("/", File.separator);
         var1 = var1.replace("\\", File.separator);
    std::string var2 = var1.substr(0, var1.lastIndexOf(File.separator));
         var2 = var2.replace("\\", "/");
    File var3 = std::make_shared<File>(var2);
         if (!var3.exists()) {
            var3.mkdirs();
         }

    File var4 = std::make_shared<File>(var1);

         try {
            outStream = std::make_shared<FileOutputStream>(var4);
         } catch (FileNotFoundException var6) {
            Logger.getLogger(LuaManager.class.getName()).log(Level.SEVERE, nullptr, var6);
         }

         return std::make_shared<DataOutputStream>(outStream);
      }
   }

    static std::string getLastStandPlayersDirectory() {
      return "LastStand";
   }

   public static List<std::string> getLastStandPlayerFileNames() throws IOException {
    std::vector var0 = new std::vector();
    std::string var1 = LuaManager.getLuaCacheDir() + File.separator + getLastStandPlayersDirectory();
      var1 = var1.replace("/", File.separator);
      var1 = var1.replace("\\", File.separator);
    File var2 = std::make_shared<File>(var1);
      if (!var2.exists()) {
         var2.mkdir();
      }

      for (File var6 : var2.listFiles()) {
         if (!var6.isDirectory() && var6.getName().endsWith(".txt")) {
            var0.push_back(getLastStandPlayersDirectory() + File.separator + var6.getName());
         }
      }

    return var0;
   }

   public static List<BufferedReader> getAllSavedPlayers() throws IOException {
    std::vector var0 = new std::vector();
    std::string var1 = LuaManager.getLuaCacheDir() + File.separator + getLastStandPlayersDirectory();
      var1 = var1.replace("/", File.separator);
      var1 = var1.replace("\\", File.separator);
    File var2 = std::make_shared<File>(var1);
      if (!var2.exists()) {
         var2.mkdir();
      }

      for (File var6 : var2.listFiles()) {
         var0.push_back(std::make_shared<BufferedReader>(std::make_shared<FileReader>(var6)));
      }

    return var0;
   }

   public static List<std::string> getSandboxPresets() throws IOException {
    std::vector var0 = new std::vector();
    std::string var1 = LuaManager.getSandboxCacheDir();
    File var2 = std::make_shared<File>(var1);
      if (!var2.exists()) {
         var2.mkdir();
      }

      for (File var6 : var2.listFiles()) {
         if (var6.getName().endsWith(".cfg")) {
            var0.push_back(var6.getName().replace(".cfg", ""));
         }
      }

      Collections.sort(var0);
    return var0;
   }

    static void deleteSandboxPreset(const std::string& var0) {
      if (StringUtils.containsDoubleDot(var0)) {
         DebugLog.Lua.warn("relative paths not allowed");
      } else {
    std::string var1 = LuaManager.getSandboxCacheDir() + File.separator + var0 + ".cfg";
    File var2 = std::make_shared<File>(var1);
         if (var2.exists()) {
            var2.delete();
         }
      }
   }

    static BufferedReader getFileReader(const std::string& var0, bool var1) {
      if (StringUtils.containsDoubleDot(var0)) {
         DebugLog.Lua.warn("relative paths not allowed");
    return nullptr;
      } else {
    std::string var2 = LuaManager.getLuaCacheDir() + File.separator + var0;
         var2 = var2.replace("/", File.separator);
         var2 = var2.replace("\\", File.separator);
    File var3 = std::make_shared<File>(var2);
         if (!var3.exists() && var1) {
            var3.createNewFile();
         }

         if (var3.exists()) {
    BufferedReader var4 = nullptr;

            try {
    FileInputStream var5 = std::make_shared<FileInputStream>(var3);
    InputStreamReader var6 = std::make_shared<InputStreamReader>(var5, StandardCharsets.UTF_8);
               var4 = std::make_shared<BufferedReader>(var6);
            } catch (IOException var7) {
               Logger.getLogger(LuaManager.class.getName()).log(Level.SEVERE, nullptr, var7);
            }

    return var4;
         } else {
    return nullptr;
         }
      }
   }

    static BufferedReader getModFileReader(const std::string& var0, const std::string& var1, bool var2) {
      if (!var1.empty() && !StringUtils.containsDoubleDot(var1) && !std::make_shared<File>(var1).isAbsolute()) {
    std::string var3 = ZomboidFileSystem.instance.getCacheDir() + File.separator + "mods" + File.separator + var1;
         if (var0 != nullptr) {
    Mod var4 = ChooseGameInfo.getModDetails(var0);
            if (var4 == nullptr) {
    return nullptr;
            }

            var3 = var4.getDir() + File.separator + var1;
         }

         var3 = var3.replace("/", File.separator);
         var3 = var3.replace("\\", File.separator);
    File var11 = std::make_shared<File>(var3);
         if (!var11.exists() && var2) {
    std::string var5 = var3.substr(0, var3.lastIndexOf(File.separator));
    File var6 = std::make_shared<File>(var5);
            if (!var6.exists()) {
               var6.mkdirs();
            }

            var11.createNewFile();
         }

         if (var11.exists()) {
    BufferedReader var12 = nullptr;

            try {
    FileInputStream var13 = std::make_shared<FileInputStream>(var11);
    InputStreamReader var7 = std::make_shared<InputStreamReader>(var13, StandardCharsets.UTF_8);
               var12 = std::make_shared<BufferedReader>(var7);
            } catch (IOException var8) {
               Logger.getLogger(LuaManager.class.getName()).log(Level.SEVERE, nullptr, var8);
            }

    return var12;
         } else {
    return nullptr;
         }
      } else {
    return nullptr;
      }
   }

    static void refreshAnimSets(bool var0) {
      try {
         if (var0) {
            AnimationSet.Reset();

            for (Asset var2 : AnimNodeAssetManager.instance.getAssetTable().values()) {
               AnimNodeAssetManager.instance.reload(var2);
            }
         }

         AnimationSet.GetAnimationSet("player", true);
         AnimationSet.GetAnimationSet("player-vehicle", true);
         AnimationSet.GetAnimationSet("zombie", true);
         AnimationSet.GetAnimationSet("zombie-crawler", true);

         for (int var4 = 0; var4 < IsoPlayer.numPlayers; var4++) {
    IsoPlayer var6 = IsoPlayer.players[var4];
            if (var6 != nullptr) {
               var6.advancedAnimator.OnAnimDataChanged(var0);
            }
         }

         for (IsoZombie var7 : IsoWorld.instance.CurrentCell.getZombieList()) {
            var7.advancedAnimator.OnAnimDataChanged(var0);
         }
      } catch (Exception var3) {
         ExceptionLogger.logException(var3);
      }
   }

    static void reloadActionGroups() {
      try {
         ActionGroup.reloadAll();
      } catch (Exception var1) {
      }
   }

    static LuaFileWriter getModFileWriter(const std::string& var0, const std::string& var1, bool var2, bool var3) {
      if (!var1.empty() && !StringUtils.containsDoubleDot(var1) && !std::make_shared<File>(var1).isAbsolute()) {
    Mod var4 = ChooseGameInfo.getModDetails(var0);
         if (var4 == nullptr) {
    return nullptr;
         } else {
    std::string var5 = var4.getDir() + File.separator + var1;
            var5 = var5.replace("/", File.separator);
            var5 = var5.replace("\\", File.separator);
    std::string var6 = var5.substr(0, var5.lastIndexOf(File.separator));
    File var7 = std::make_shared<File>(var6);
            if (!var7.exists()) {
               var7.mkdirs();
            }

    File var8 = std::make_shared<File>(var5);
            if (!var8.exists() && var2) {
               try {
                  var8.createNewFile();
               } catch (IOException var13) {
                  Logger.getLogger(LuaManager.class.getName()).log(Level.SEVERE, nullptr, var13);
               }
            }

    PrintWriter var9 = nullptr;

            try {
    FileOutputStream var10 = std::make_shared<FileOutputStream>(var8, var3);
    OutputStreamWriter var11 = std::make_shared<OutputStreamWriter>(var10, StandardCharsets.UTF_8);
               var9 = std::make_shared<PrintWriter>(var11);
            } catch (IOException var12) {
               Logger.getLogger(LuaManager.class.getName()).log(Level.SEVERE, nullptr, var12);
            }

            return std::make_shared<LuaFileWriter>(var9);
         }
      } else {
    return nullptr;
      }
   }

    static void updateFire() {
      IsoFireManager.Update();
   }

    static void deletePlayerSave(const std::string& var0) {
    std::string var1 = LuaManager.getLuaCacheDir() + File.separator + "Players" + File.separator + "player" + var0 + ".txt";
      var1 = var1.replace("/", File.separator);
      var1 = var1.replace("\\", File.separator);
    File var2 = std::make_shared<File>(var1);
      var2.delete();
   }

    static int getControllerCount() {
      return GameWindow.GameInput.getControllerCount();
   }

    static bool isControllerConnected(int var0) {
      return var0 >= 0 && var0 <= GameWindow.GameInput.getControllerCount() ? GameWindow.GameInput.getController(var0) != nullptr : false;
   }

    static std::string getControllerGUID(int var0) {
      if (var0 >= 0 && var0 < GameWindow.GameInput.getControllerCount()) {
    Controller var1 = GameWindow.GameInput.getController(var0);
         return var1 != nullptr ? var1.getGUID() : "???";
      } else {
         return "???";
      }
   }

    static std::string getControllerName(int var0) {
      if (var0 >= 0 && var0 < GameWindow.GameInput.getControllerCount()) {
    Controller var1 = GameWindow.GameInput.getController(var0);
         return var1 != nullptr ? var1.getGamepadName() : "???";
      } else {
         return "???";
      }
   }

    static int getControllerAxisCount(int var0) {
      if (var0 >= 0 && var0 < GameWindow.GameInput.getControllerCount()) {
    Controller var1 = GameWindow.GameInput.getController(var0);
    return var1 = = nullptr ? 0 : var1.getAxisCount();
      } else {
    return 0;
      }
   }

    static float getControllerAxisValue(int var0, int var1) {
      if (var0 >= 0 && var0 < GameWindow.GameInput.getControllerCount()) {
    Controller var2 = GameWindow.GameInput.getController(var0);
         if (var2 == nullptr) {
            return 0.0F;
         } else {
            return var1 >= 0 && var1 < var2.getAxisCount() ? var2.getAxisValue(var1) : 0.0F;
         }
      } else {
         return 0.0F;
      }
   }

    static float getControllerDeadZone(int var0, int var1) {
      if (var0 < 0 || var0 >= GameWindow.GameInput.getControllerCount()) {
         return 0.0F;
      } else {
         return var1 >= 0 && var1 < GameWindow.GameInput.getAxisCount(var0) ? JoypadManager.instance.getDeadZone(var0, var1) : 0.0F;
      }
   }

    static void setControllerDeadZone(int var0, int var1, float var2) {
      if (var0 >= 0 && var0 < GameWindow.GameInput.getControllerCount()) {
         if (var1 >= 0 && var1 < GameWindow.GameInput.getAxisCount(var0)) {
            JoypadManager.instance.setDeadZone(var0, var1, var2);
         }
      }
   }

    static void saveControllerSettings(int var0) {
      if (var0 >= 0 && var0 < GameWindow.GameInput.getControllerCount()) {
         JoypadManager.instance.saveControllerSettings(var0);
      }
   }

    static int getControllerButtonCount(int var0) {
      if (var0 >= 0 && var0 < GameWindow.GameInput.getControllerCount()) {
    Controller var1 = GameWindow.GameInput.getController(var0);
    return var1 = = nullptr ? 0 : var1.getButtonCount();
      } else {
    return 0;
      }
   }

    static float getControllerPovX(int var0) {
      if (var0 >= 0 && var0 < GameWindow.GameInput.getControllerCount()) {
    Controller var1 = GameWindow.GameInput.getController(var0);
    return var1 = = nullptr ? 0.0F : var1.getPovX();
      } else {
         return 0.0F;
      }
   }

    static float getControllerPovY(int var0) {
      if (var0 >= 0 && var0 < GameWindow.GameInput.getControllerCount()) {
    Controller var1 = GameWindow.GameInput.getController(var0);
    return var1 = = nullptr ? 0.0F : var1.getPovY();
      } else {
         return 0.0F;
      }
   }

    static void reloadControllerConfigFiles() {
      JoypadManager.instance.reloadControllerFiles();
   }

    static bool isJoypadPressed(int var0, int var1) {
      return GameWindow.GameInput.isButtonPressedD(var1, var0);
   }

    static bool isJoypadDown(int var0) {
      return JoypadManager.instance.isDownPressed(var0);
   }

    static bool isJoypadLTPressed(int var0) {
      return JoypadManager.instance.isLTPressed(var0);
   }

    static bool isJoypadRTPressed(int var0) {
      return JoypadManager.instance.isRTPressed(var0);
   }

    static bool isJoypadLeftStickButtonPressed(int var0) {
      return JoypadManager.instance.isL3Pressed(var0);
   }

    static bool isJoypadRightStickButtonPressed(int var0) {
      return JoypadManager.instance.isR3Pressed(var0);
   }

    static float getJoypadAimingAxisX(int var0) {
      return JoypadManager.instance.getAimingAxisX(var0);
   }

    static float getJoypadAimingAxisY(int var0) {
      return JoypadManager.instance.getAimingAxisY(var0);
   }

    static float getJoypadMovementAxisX(int var0) {
      return JoypadManager.instance.getMovementAxisX(var0);
   }

    static float getJoypadMovementAxisY(int var0) {
      return JoypadManager.instance.getMovementAxisY(var0);
   }

    static int getJoypadAButton(int var0) {
    Joypad var1 = JoypadManager.instance.getFromControllerID(var0);
      return var1 != nullptr ? var1.getAButton() : -1;
   }

    static int getJoypadBButton(int var0) {
    Joypad var1 = JoypadManager.instance.getFromControllerID(var0);
      return var1 != nullptr ? var1.getBButton() : -1;
   }

    static int getJoypadXButton(int var0) {
    Joypad var1 = JoypadManager.instance.getFromControllerID(var0);
      return var1 != nullptr ? var1.getXButton() : -1;
   }

    static int getJoypadYButton(int var0) {
    Joypad var1 = JoypadManager.instance.getFromControllerID(var0);
      return var1 != nullptr ? var1.getYButton() : -1;
   }

    static int getJoypadLBumper(int var0) {
    Joypad var1 = JoypadManager.instance.getFromControllerID(var0);
      return var1 != nullptr ? var1.getLBumper() : -1;
   }

    static int getJoypadRBumper(int var0) {
    Joypad var1 = JoypadManager.instance.getFromControllerID(var0);
      return var1 != nullptr ? var1.getRBumper() : -1;
   }

    static int getJoypadBackButton(int var0) {
    Joypad var1 = JoypadManager.instance.getFromControllerID(var0);
      return var1 != nullptr ? var1.getBackButton() : -1;
   }

    static int getJoypadStartButton(int var0) {
    Joypad var1 = JoypadManager.instance.getFromControllerID(var0);
      return var1 != nullptr ? var1.getStartButton() : -1;
   }

    static int getJoypadLeftStickButton(int var0) {
    Joypad var1 = JoypadManager.instance.getFromControllerID(var0);
      return var1 != nullptr ? var1.getL3() : -1;
   }

    static int getJoypadRightStickButton(int var0) {
    Joypad var1 = JoypadManager.instance.getFromControllerID(var0);
      return var1 != nullptr ? var1.getR3() : -1;
   }

    static bool wasMouseActiveMoreRecentlyThanJoypad() {
      if (IsoPlayer.players[0] == nullptr) {
    Joypad var1 = GameWindow.ActivatedJoyPad;
         return var1 != nullptr && !var1.isDisabled() ? JoypadManager.instance.getLastActivity(var1.getID()) < Mouse.lastActivity : true;
      } else {
    int var0 = IsoPlayer.players[0].getJoypadBind();
    return var0 = = -1 ? true : JoypadManager.instance.getLastActivity(var0) < Mouse.lastActivity;
      }
   }

    static void activateJoypadOnSteamDeck() {
      if (GameWindow.ActivatedJoyPad == nullptr) {
         JoypadManager.instance.isAPressed(0);
         if (JoypadManager.instance.JoypadList.empty()) {
            return;
         }

    Joypad var0 = (Joypad)JoypadManager.instance.JoypadList.get(0);
         GameWindow.ActivatedJoyPad = var0;
      }

      if (IsoPlayer.getInstance() != nullptr) {
         LuaEventManager.triggerEvent("OnJoypadActivate", GameWindow.ActivatedJoyPad.getID());
      } else {
         LuaEventManager.triggerEvent("OnJoypadActivateUI", GameWindow.ActivatedJoyPad.getID());
      }
   }

    static bool reactivateJoypadAfterResetLua() {
      if (GameWindow.ActivatedJoyPad != nullptr) {
         LuaEventManager.triggerEvent("OnJoypadActivateUI", GameWindow.ActivatedJoyPad.getID());
    return true;
      } else {
    return false;
      }
   }

    static bool isJoypadConnected(int var0) {
      return JoypadManager.instance.isJoypadConnected(var0);
   }

    static void addPlayerToWorld(int var0, IsoPlayer var1, bool var2) {
      if (IsoPlayer.players[var0] != nullptr) {
         IsoPlayer.players[var0].getEmitter().stopAll();
         IsoPlayer.players[var0].getEmitter().unregister();
         IsoPlayer.players[var0].updateUsername();
         IsoPlayer.players[var0].setSceneCulled(true);
         IsoPlayer.players[var0] = nullptr;
      }

      var1.PlayerIndex = var0;
      if (GameClient.bClient && var0 != 0 && var1.serverPlayerIndex != 1) {
         ClientPlayerDB.getInstance().forgetPlayer(var1.serverPlayerIndex);
      }

      if (GameClient.bClient && var0 != 0 && var1.serverPlayerIndex == 1) {
         var1.serverPlayerIndex = ClientPlayerDB.getInstance().getNextServerPlayerIndex();
      }

      if (var0 == 0) {
         var1.sqlID = 1;
      }

      if (var2) {
         var1.applyTraits(IsoWorld.instance.getLuaTraits());
         var1.createKeyRing();
    Profession var3 = ProfessionFactory.getProfession(var1.getDescriptor().getProfession());
         if (var3 != nullptr && !var3.getFreeRecipes().empty()) {
            for (std::string var5 : var3.getFreeRecipes()) {
               var1.getKnownRecipes().push_back(var5);
            }
         }

         for (std::string var10 : IsoWorld.instance.getLuaTraits()) {
    Trait var6 = TraitFactory.getTrait(var10);
            if (var6 != nullptr && !var6.getFreeRecipes().empty()) {
               for (std::string var8 : var6.getFreeRecipes()) {
                  var1.getKnownRecipes().push_back(var8);
               }
            }
         }

         var1.setDir(IsoDirections.SE);
         LuaEventManager.triggerEvent("OnNewGame", var1, var1.getCurrentSquare());
      }

      IsoPlayer.numPlayers = Math.max(IsoPlayer.numPlayers, var0 + 1);
      IsoWorld.instance.AddCoopPlayers.push_back(std::make_shared<AddCoopPlayer>(var1));
      if (var0 == 0) {
         IsoPlayer.setInstance(var1);
      }
   }

    static int toInt(double var0) {
      return (int)var0;
   }

    static std::string getClientUsername() {
      return GameClient.bClient ? GameClient.username : nullptr;
   }

    static void setPlayerJoypad(int var0, int var1, IsoPlayer var2, const std::string& var3) {
      if (IsoPlayer.players[var0] == nullptr || IsoPlayer.players[var0].isDead()) {
    bool var4 = var2 == nullptr;
         if (var2 == nullptr) {
    IsoPlayer var5 = IsoPlayer.getInstance();
    IsoWorld var6 = IsoWorld.instance;
    int var7 = var6.getLuaPosX() + 300 * var6.getLuaSpawnCellX();
    int var8 = var6.getLuaPosY() + 300 * var6.getLuaSpawnCellY();
    int var9 = var6.getLuaPosZ();
            DebugLog.Lua.debugln("coop player spawning at " + var7 + "," + var8 + "," + var9);
            var2 = std::make_shared<IsoPlayer>(var6.CurrentCell, var6.getLuaPlayerDesc(), var7, var8, var9);
            IsoPlayer.setInstance(var5);
            var6.CurrentCell.getAddList().remove(var2);
            var6.CurrentCell.getObjectList().remove(var2);
            var2.SaveFileName = IsoPlayer.getUniqueFileName();
         }

         if (GameClient.bClient) {
            if (var3 != nullptr) {
               if (!$assertionsDisabled && var0 == 0) {
                  throw std::make_unique<AssertionError>();
               }

               var2.username = var3;
               var2.getModData().rawset("username", var3);
            } else {
               if (!$assertionsDisabled && var0 != 0) {
                  throw std::make_unique<AssertionError>();
               }

               var2.username = GameClient.username;
            }
         }

         addPlayerToWorld(var0, var2, var4);
      }

      var2.JoypadBind = var1;
      JoypadManager.instance.assignJoypad(var1, var0);
   }

    static void setPlayerMouse(IsoPlayer var0) {
    uint8_t var1 = 0;
    bool var2 = var0 == nullptr;
      if (var0 == nullptr) {
    IsoPlayer var3 = IsoPlayer.getInstance();
    IsoWorld var4 = IsoWorld.instance;
    int var5 = var4.getLuaPosX() + 300 * var4.getLuaSpawnCellX();
    int var6 = var4.getLuaPosY() + 300 * var4.getLuaSpawnCellY();
    int var7 = var4.getLuaPosZ();
         DebugLog.Lua.debugln("coop player spawning at " + var5 + "," + var6 + "," + var7);
         var0 = std::make_shared<IsoPlayer>(var4.CurrentCell, var4.getLuaPlayerDesc(), var5, var6, var7);
         IsoPlayer.setInstance(var3);
         var4.CurrentCell.getAddList().remove(var0);
         var4.CurrentCell.getObjectList().remove(var0);
         var0.SaveFileName = nullptr;
      }

      if (GameClient.bClient) {
         var0.username = GameClient.username;
      }

      addPlayerToWorld(var1, var0, var2);
   }

    static void revertToKeyboardAndMouse() {
      JoypadManager.instance.revertToKeyboardAndMouse();
   }

    static bool isJoypadUp(int var0) {
      return JoypadManager.instance.isUpPressed(var0);
   }

    static bool isJoypadLeft(int var0) {
      return JoypadManager.instance.isLeftPressed(var0);
   }

    static bool isJoypadRight(int var0) {
      return JoypadManager.instance.isRightPressed(var0);
   }

    static bool isJoypadLBPressed(int var0) {
      return JoypadManager.instance.isLBPressed(var0);
   }

    static bool isJoypadRBPressed(int var0) {
      return JoypadManager.instance.isRBPressed(var0);
   }

    static int getButtonCount(int var0) {
      if (var0 >= 0 && var0 < GameWindow.GameInput.getControllerCount()) {
    Controller var1 = GameWindow.GameInput.getController(var0);
    return var1 = = nullptr ? 0 : var1.getButtonCount();
      } else {
    return 0;
      }
   }

    static void setDebugToggleControllerPluggedIn(int var0) {
      Controllers.setDebugToggleControllerPluggedIn(var0);
   }

    static LuaFileWriter getFileWriter(const std::string& var0, bool var1, bool var2) {
      if (StringUtils.containsDoubleDot(var0)) {
         DebugLog.Lua.warn("relative paths not allowed");
    return nullptr;
      } else {
    std::string var3 = LuaManager.getLuaCacheDir() + File.separator + var0;
         var3 = var3.replace("/", File.separator);
         var3 = var3.replace("\\", File.separator);
    std::string var4 = var3.substr(0, var3.lastIndexOf(File.separator));
         var4 = var4.replace("\\", "/");
    File var5 = std::make_shared<File>(var4);
         if (!var5.exists()) {
            var5.mkdirs();
         }

    File var6 = std::make_shared<File>(var3);
         if (!var6.exists() && var1) {
            try {
               var6.createNewFile();
            } catch (IOException var11) {
               Logger.getLogger(LuaManager.class.getName()).log(Level.SEVERE, nullptr, var11);
            }
         }

    PrintWriter var7 = nullptr;

         try {
    FileOutputStream var8 = std::make_shared<FileOutputStream>(var6, var2);
    OutputStreamWriter var9 = std::make_shared<OutputStreamWriter>(var8, StandardCharsets.UTF_8);
            var7 = std::make_shared<PrintWriter>(var9);
         } catch (IOException var10) {
            Logger.getLogger(LuaManager.class.getName()).log(Level.SEVERE, nullptr, var10);
         }

         return std::make_shared<LuaFileWriter>(var7);
      }
   }

    static LuaFileWriter getSandboxFileWriter(const std::string& var0, bool var1, bool var2) {
      if (StringUtils.containsDoubleDot(var0)) {
         DebugLog.Lua.warn("relative paths not allowed");
    return nullptr;
      } else {
    std::string var3 = LuaManager.getSandboxCacheDir() + File.separator + var0;
         var3 = var3.replace("/", File.separator);
         var3 = var3.replace("\\", File.separator);
    std::string var4 = var3.substr(0, var3.lastIndexOf(File.separator));
         var4 = var4.replace("\\", "/");
    File var5 = std::make_shared<File>(var4);
         if (!var5.exists()) {
            var5.mkdirs();
         }

    File var6 = std::make_shared<File>(var3);
         if (!var6.exists() && var1) {
            try {
               var6.createNewFile();
            } catch (IOException var11) {
               Logger.getLogger(LuaManager.class.getName()).log(Level.SEVERE, nullptr, var11);
            }
         }

    PrintWriter var7 = nullptr;

         try {
    FileOutputStream var8 = std::make_shared<FileOutputStream>(var6, var2);
    OutputStreamWriter var9 = std::make_shared<OutputStreamWriter>(var8, StandardCharsets.UTF_8);
            var7 = std::make_shared<PrintWriter>(var9);
         } catch (IOException var10) {
            Logger.getLogger(LuaManager.class.getName()).log(Level.SEVERE, nullptr, var10);
         }

         return std::make_shared<LuaFileWriter>(var7);
      }
   }

    static void createStory(const std::string& var0) {
      Core.GameMode = var0;
    std::string var1 = ZomboidFileSystem.instance.getGameModeCacheDir();
      var1 = var1.replace("/", File.separator);
      var1 = var1.replace("\\", File.separator);
    int var2 = 1;
    void* var3 = nullptr;
    bool var4 = false;

      while (!var4) {
         var3 = std::make_shared<File>(var1 + File.separator + "Game" + var2);
         if (!var3.exists()) {
            var4 = true;
         } else {
            var2++;
         }
      }

      Core.GameSaveWorld = "newstory";
   }

    static void createWorld(const std::string& var0) {
      if (var0 == nullptr || var0.empty()) {
         var0 = "blah";
      }

      var0 = sanitizeWorldName(var0);
    std::string var1 = ZomboidFileSystem.instance.getGameModeCacheDir() + File.separator + var0 + File.separator;
      var1 = var1.replace("/", File.separator);
      var1 = var1.replace("\\", File.separator);
    std::string var2 = var1.substr(0, var1.lastIndexOf(File.separator));
      var2 = var2.replace("\\", "/");
    File var3 = std::make_shared<File>(var2);
      if (!var3.exists() && !Core.getInstance().isNoSave()) {
         var3.mkdirs();
      }

      Core.GameSaveWorld = var0;
   }

    static std::string sanitizeWorldName(const std::string& var0) {
      return var0.replace(" ", "_")
         .replace("/", "")
         .replace("\\", "")
         .replace("?", "")
         .replace("*", "")
         .replace("<", "")
         .replace(">", "")
         .replace(":", "")
         .replace("|", "")
         .trim();
   }

    static void forceChangeState(GameState var0) {
      GameWindow.states.forceNextState(var0);
   }

    static void endFileOutput() {
      if (outStream != nullptr) {
         try {
            outStream.close();
         } catch (IOException var1) {
            Logger.getLogger(LuaManager.class.getName()).log(Level.SEVERE, nullptr, var1);
         }
      }

      outStream = nullptr;
   }

    static DataInputStream getFileInput(const std::string& var0) {
      if (StringUtils.containsDoubleDot(var0)) {
         DebugLog.Lua.warn("relative paths not allowed");
    return nullptr;
      } else {
    std::string var1 = LuaManager.getLuaCacheDir() + File.separator + var0;
         var1 = var1.replace("/", File.separator);
         var1 = var1.replace("\\", File.separator);
    File var2 = std::make_shared<File>(var1);
         if (var2.exists()) {
            try {
               inStream = std::make_shared<FileInputStream>(var2);
            } catch (FileNotFoundException var4) {
               Logger.getLogger(LuaManager.class.getName()).log(Level.SEVERE, nullptr, var4);
            }

            return std::make_shared<DataInputStream>(inStream);
         } else {
    return nullptr;
         }
      }
   }

    static DataInputStream getGameFilesInput(const std::string& var0) {
    std::string var1 = var0.replace("/", File.separator);
      var1 = var1.replace("\\", File.separator);
      if (!ZomboidFileSystem.instance.isKnownFile(var1)) {
    return nullptr;
      } else {
    File var2 = std::make_shared<File>(ZomboidFileSystem.instance.getString(var1));
         if (var2.exists()) {
            try {
               inStream = std::make_shared<FileInputStream>(var2);
            } catch (FileNotFoundException var4) {
               Logger.getLogger(LuaManager.class.getName()).log(Level.SEVERE, nullptr, var4);
            }

            return std::make_shared<DataInputStream>(inStream);
         } else {
    return nullptr;
         }
      }
   }

    static BufferedReader getGameFilesTextInput(const std::string& var0) {
      if (!Core.getInstance().getDebug()) {
    return nullptr;
      } else {
    std::string var1 = var0.replace("/", File.separator);
         var1 = var1.replace("\\", File.separator);
         if (!ZomboidFileSystem.instance.isKnownFile(var1)) {
    return nullptr;
         } else {
    File var2 = std::make_shared<File>(ZomboidFileSystem.instance.getString(var1));
            if (var2.exists()) {
               try {
                  inFileReader = std::make_shared<FileReader>(var0);
                  inBufferedReader = std::make_shared<BufferedReader>(inFileReader);
    return inBufferedReader;
               } catch (FileNotFoundException var4) {
                  Logger.getLogger(LuaManager.class.getName()).log(Level.SEVERE, nullptr, var4);
               }
            }

    return nullptr;
         }
      }
   }

    static void endTextFileInput() {
      if (inBufferedReader != nullptr) {
         try {
            inBufferedReader.close();
            inFileReader.close();
         } catch (IOException var1) {
            Logger.getLogger(LuaManager.class.getName()).log(Level.SEVERE, nullptr, var1);
         }
      }

      inBufferedReader = nullptr;
      inFileReader = nullptr;
   }

    static void endFileInput() {
      if (inStream != nullptr) {
         try {
            inStream.close();
         } catch (IOException var1) {
            Logger.getLogger(LuaManager.class.getName()).log(Level.SEVERE, nullptr, var1);
         }
      }

      inStream = nullptr;
   }

    static int getLineNumber(LuaCallFrame var0) {
      if (var0.closure == nullptr) {
    return 0;
      } else {
    int var1 = var0.pc;
         if (var1 < 0) {
            var1 = 0;
         }

         if (var1 >= var0.closure.prototype.lines.length) {
            var1 = var0.closure.prototype.lines.length - 1;
         }

         return var0.closure.prototype.lines[var1];
      }
   }

    static double ZombRand(double var0) {
      if (var0 == 0.0) {
         return 0.0;
      } else {
         return var0 < 0.0 ? -Rand.Next(-((long)var0), Rand.randlua) : Rand.Next((long)var0, Rand.randlua);
      }
   }

    static double ZombRandBetween(double var0, double var2) {
      return Rand.Next((long)var0, (long)var2, Rand.randlua);
   }

    static double ZombRand(double var0, double var2) {
      return Rand.Next((int)var0, (int)var2, Rand.randlua);
   }

    static float ZombRandFloat(float var0, float var1) {
      return Rand.Next(var0, var1, Rand.randlua);
   }

    static std::string getShortenedFilename(const std::string& var0) {
      return var0.substr(var0.indexOf("lua/") + 4);
   }

    static bool isKeyDown(int var0) {
      return GameKeyboard.isKeyDown(var0);
   }

    static bool wasKeyDown(int var0) {
      return GameKeyboard.wasKeyDown(var0);
   }

    static bool isKeyPressed(int var0) {
      return GameKeyboard.isKeyPressed(var0);
   }

      static BaseSoundBank getOpenALSoundBank() {
         return BaseSoundBank.instance;
    }

      static bool isSoundPlaying(void* var0) {
         return dynamic_cast<double*>(var0) != nullptr ? OpenALManager::instance.isPlaying(((double)var0).longValue()) : false;
    }

      static void stopSound(long var0) {
         OpenALManager::instance.stopSound(var0);
    }

    static bool isShiftKeyDown() {
      return GameKeyboard.isKeyDown(42) || GameKeyboard.isKeyDown(54);
   }

    static bool isCtrlKeyDown() {
      return GameKeyboard.isKeyDown(29) || GameKeyboard.isKeyDown(157);
   }

    static bool isAltKeyDown() {
      return GameKeyboard.isKeyDown(56) || GameKeyboard.isKeyDown(184);
   }

    static Core getCore() {
      return Core.getInstance();
   }

    static std::string getGameVersion() {
      return Core.getInstance().getGameVersion();
   }

    static IsoGridSquare getSquare(double var0, double var2, double var4) {
      return IsoCell.getInstance().getGridSquare(var0, var2, var4);
   }

    static DebugOptions getDebugOptions() {
      return DebugOptions.instance;
   }

    static void setShowPausedMessage(bool var0) {
      DebugLog.log("EXITDEBUG: setShowPausedMessage 1");
      UIManager.setShowPausedMessage(var0);
      DebugLog.log("EXITDEBUG: setShowPausedMessage 2");
   }

    static std::string getFilenameOfCallframe(LuaCallFrame var0) {
      return var0.closure == nullptr ? nullptr : var0.closure.prototype.filename;
   }

    static std::string getFilenameOfClosure(LuaClosure var0) {
    return var0 = = nullptr ? nullptr : var0.prototype.filename;
   }

    static int getFirstLineOfClosure(LuaClosure var0) {
    return var0 = = nullptr ? 0 : var0.prototype.lines[0];
   }

    static int getLocalVarCount(Coroutine var0) {
    LuaCallFrame var1 = var0.currentCallFrame();
    return var1 = = nullptr ? 0 : var1.LocalVarNames.size();
   }

    static bool isSystemLinux() {
      return !isSystemMacOS() && !isSystemWindows();
   }

    static bool isSystemMacOS() {
      return System.getProperty("os.name").contains("OS X");
   }

    static bool isSystemWindows() {
      return System.getProperty("os.name").startsWith("Win");
   }

    static bool isModActive(Mod var0) {
    std::string var1 = var0.getDir();
      if (!StringUtils.isNullOrWhitespace(var0.getId())) {
         var1 = var0.getId();
      }

      return ZomboidFileSystem.instance.getModIDs().contains(var1);
   }

    static void openURl(const std::string& var0) {
    Desktop var1 = Desktop.isDesktopSupported() ? Desktop.getDesktop() : nullptr;
      if (var1 != nullptr && var1.isSupported(Action.BROWSE)) {
         try {
    URI var2 = std::make_shared<URI>(var0);
            var1.browse(var2);
         } catch (Exception var3) {
            ExceptionLogger.logException(var3);
         }
      } else {
         DesktopBrowser.openURL(var0);
      }
   }

    static bool isDesktopOpenSupported() {
      return !Desktop.isDesktopSupported() ? false : Desktop.getDesktop().isSupported(Action.OPEN);
   }

    static void showFolderInDesktop(const std::string& var0) {
    File var1 = std::make_shared<File>(var0);
      if (var1.exists() && var1.isDirectory()) {
    Desktop var2 = Desktop.isDesktopSupported() ? Desktop.getDesktop() : nullptr;
         if (var2 != nullptr && var2.isSupported(Action.OPEN)) {
            try {
               var2.open(var1);
            } catch (Exception var4) {
               ExceptionLogger.logException(var4);
            }
         }
      }
   }

   public static std::vector<std::string> getActivatedMods() {
      return ZomboidFileSystem.instance.getModIDs();
   }

    static void toggleModActive(Mod var0, bool var1) {
    std::string var2 = var0.getDir();
      if (!StringUtils.isNullOrWhitespace(var0.getId())) {
         var2 = var0.getId();
      }

      ActiveMods.getById("default").setModActive(var2, var1);
   }

    static void saveModsFile() {
      ZomboidFileSystem.instance.saveModsFile();
   }

    static void deleteSavefileFilesMatching(File var0, const std::string& var1) {
    Filter var2 = var1x -> var1x.getFileName().matches(var1);

      try (DirectoryStream var3 = Files.newDirectoryStream(var0.toPath(), var2)) {
    for (auto& var5 : var3)            System.out.println("DELETE " + var5);
            Files.deleteIfExists(var5);
         }
      } catch (Exception var8) {
         ExceptionLogger.logException(var8);
      }
   }

    static void manipulateSavefile(const std::string& var0, const std::string& var1) {
      if (!StringUtils.isNullOrWhitespace(var0)) {
         if (!StringUtils.containsDoubleDot(var0)) {
    std::string var2 = ZomboidFileSystem.instance.getSaveDir() + File.separator + var0;
    File var3 = std::make_shared<File>(var2);
            if (var3.exists() && var3.isDirectory()) {
               switch (var1) {
                  case "DeleteChunkDataXYBin":
                     deleteSavefileFilesMatching(var3, "chunkdata_[0-9]+_[0-9]+\\.bin");
                     break;
                  case "DeleteMapXYBin":
                     deleteSavefileFilesMatching(var3, "map_[0-9]+_[0-9]+\\.bin");
                     break;
                  case "DeleteMapMetaBin":
                     deleteSavefileFilesMatching(var3, "map_meta\\.bin");
                     break;
                  case "DeleteMapTBin":
                     deleteSavefileFilesMatching(var3, "map_t\\.bin");
                     break;
                  case "DeleteMapZoneBin":
                     deleteSavefileFilesMatching(var3, "map_zone\\.bin");
                     break;
                  case "DeletePlayersDB":
                     deleteSavefileFilesMatching(var3, "players\\.db");
                     break;
                  case "DeleteReanimatedBin":
                     deleteSavefileFilesMatching(var3, "reanimated\\.bin");
                     break;
                  case "DeleteVehiclesDB":
                     deleteSavefileFilesMatching(var3, "vehicles\\.db");
                     break;
                  case "DeleteZOutfitsBin":
                     deleteSavefileFilesMatching(var3, "z_outfits\\.bin");
                     break;
                  case "DeleteZPopVirtualBin":
                     deleteSavefileFilesMatching(var3, "zpop_virtual\\.bin");
                     break;
                  case "DeleteZPopXYBin":
                     deleteSavefileFilesMatching(var3, "zpop_[0-9]+_[0-9]+\\.bin");
                     break;
                  case "WriteModsDotTxt":
    ActiveMods var6 = ActiveMods.getById("currentGame");
    ActiveModsFile var7 = std::make_shared<ActiveModsFile>();
                     var7.write(var2 + File.separator + "mods.txt", var6);
                     break;
                  default:
                     throw IllegalArgumentException("unknown action \"" + var1 + "\"");
               }
            }
         }
      }
   }

    static std::string getLocalVarName(Coroutine var0, int var1) {
    LuaCallFrame var2 = var0.currentCallFrame();
      return (std::string)var2.LocalVarNames.get(var1);
   }

    static int getLocalVarStack(Coroutine var0, int var1) {
    LuaCallFrame var2 = var0.currentCallFrame();
      return (int)var2.LocalVarToStackMap.get(var2.LocalVarNames.get(var1));
   }

    static int getCallframeTop(Coroutine var0) {
      return var0.getCallframeTop();
   }

    static int getCoroutineTop(Coroutine var0) {
      return var0.getTop();
   }

    static void* getCoroutineObjStack(Coroutine var0, int var1) {
      return var0.getObjectFromStack(var1);
   }

    static void* getCoroutineObjStackWithBase(Coroutine var0, int var1) {
      return var0.getObjectFromStack(var1 - var0.currentCallFrame().localBase);
   }

    static std::string localVarName(Coroutine var0, int var1) {
    int var2 = var0.getCallframeTop() - 1;
      if (var2 < 0) {
    bool var3 = false;
      }

      return "";
   }

    static LuaCallFrame getCoroutineCallframeStack(Coroutine var0, int var1) {
      return var0.getCallFrame(var1);
   }

    static void createTile(const std::string& var0, IsoGridSquare var1) {
      /* synchronized - TODO: add std::mutex */ (IsoSpriteManager.instance.NamedMap) {
    IsoSprite var3 = (IsoSprite)IsoSpriteManager.instance.NamedMap.get(var0);
         if (var3 != nullptr) {
    int var4 = 0;
    int var5 = 0;
    int var6 = 0;
            if (var1 != nullptr) {
               var4 = var1.getX();
               var5 = var1.getY();
               var6 = var1.getZ();
            }

            CellLoader.DoTileObjectCreation(var3, var3.getType(), var1, IsoWorld.instance.CurrentCell, var4, var5, var6, var0);
         }
      }
   }

    static int getNumClassFunctions(void* var0) {
      return var0.getClass().getDeclaredMethods().length;
   }

    static Method getClassFunction(void* var0, int var1) {
      return var0.getClass().getDeclaredMethods()[var1];
   }

    static int getNumClassFields(void* var0) {
      return var0.getClass().getDeclaredFields().length;
   }

    static Field getClassField(void* var0, int var1) {
    Field var2 = var0.getClass().getDeclaredFields()[var1];
      var2.setAccessible(true);
    return var2;
   }

    static IsoDirections getDirectionTo(IsoGameCharacter var0, IsoObject var1) {
    Vector2 var2 = std::make_shared<Vector2>(var1.getX(), var1.getY());
      var2.x = var2.x - var0.x;
      var2.y = var2.y - var0.y;
      return IsoDirections.fromAngle(var2);
   }

    static float translatePointXInOverheadMapToWindow(float var0, UIElement var1, float var2, float var3) {
      IngameState.draww = var1.getWidth().intValue();
      return IngameState.translatePointX(var0, var3, var2, 0.0F);
   }

    static float translatePointYInOverheadMapToWindow(float var0, UIElement var1, float var2, float var3) {
      IngameState.drawh = var1.getHeight().intValue();
      return IngameState.translatePointY(var0, var3, var2, 0.0F);
   }

    static float translatePointXInOverheadMapToWorld(float var0, UIElement var1, float var2, float var3) {
      IngameState.draww = var1.getWidth().intValue();
      return IngameState.invTranslatePointX(var0, var3, var2, 0.0F);
   }

    static float translatePointYInOverheadMapToWorld(float var0, UIElement var1, float var2, float var3) {
      IngameState.drawh = var1.getHeight().intValue();
      return IngameState.invTranslatePointY(var0, var3, var2, 0.0F);
   }

    static void drawOverheadMap(UIElement var0, float var1, float var2, float var3) {
      IngameState.renderDebugOverhead2(
         getCell(),
         0,
         var1,
         var0.getAbsoluteX().intValue(),
         var0.getAbsoluteY().intValue(),
         var2,
         var3,
         var0.getWidth().intValue(),
         var0.getHeight().intValue()
      );
   }

    static void assaultPlayer() {
      if (!$assertionsDisabled) {
         throw std::make_unique<AssertionError>();
      }
   }

    static IsoRegionsRenderer isoRegionsRenderer() {
      return std::make_unique<IsoRegionsRenderer>();
   }

    static ZombiePopulationRenderer zpopNewRenderer() {
      return std::make_unique<ZombiePopulationRenderer>();
   }

    static void zpopSpawnTimeToZero(int var0, int var1) {
      ZombiePopulationManager.instance.dbgSpawnTimeToZero(var0, var1);
   }

    static void zpopClearZombies(int var0, int var1) {
      ZombiePopulationManager.instance.dbgClearZombies(var0, var1);
   }

    static void zpopSpawnNow(int var0, int var1) {
      ZombiePopulationManager.instance.dbgSpawnNow(var0, var1);
   }

    static void addVirtualZombie(int var0, int var1) {
   }

    static void luaDebug() {
      try {
         throw Exception("LuaDebug");
      } catch (Exception var1) {
         var1.printStackTrace();
      }
   }

    static void setAggroTarget(int var0, int var1, int var2) {
      ZombiePopulationManager.instance.setAggroTarget(var0, var1, var2);
   }

    static void debugFullyStreamedIn(int var0, int var1) {
      IngameState.instance.debugFullyStreamedIn(var0, var1);
   }

    static void* getClassFieldVal(void* var0, Field var1) {
      try {
         return var1.get(var0);
      } catch (Exception var3) {
         return "<private>";
      }
   }

    static std::string getMethodParameter(Method var0, int var1) {
      return var0.getParameterTypes()[var1].getSimpleName();
   }

    static int getMethodParameterCount(Method var0) {
      return var0.getParameterTypes().length;
   }

    static void breakpoint() {
    bool var0 = false;
   }

    static int getLuaDebuggerErrorCount() {
      return KahluaThread.m_error_count;
   }

   public static std::vector<std::string> getLuaDebuggerErrors() {
      return new std::vector<>(KahluaThread.m_errors_list);
   }

    static void doLuaDebuggerAction(const std::string& var0) {
      UIManager.luaDebuggerAction = var0;
   }

    static int getGameSpeed() {
      return UIManager.getSpeedControls() != nullptr ? UIManager.getSpeedControls().getCurrentGameSpeed() : 0;
   }

    static void setGameSpeed(int var0) {
      DebugLog.log("EXITDEBUG: setGameSpeed 1");
      if (UIManager.getSpeedControls() == nullptr) {
         DebugLog.log("EXITDEBUG: setGameSpeed 2");
      } else {
         UIManager.getSpeedControls().SetCurrentGameSpeed(var0);
         DebugLog.log("EXITDEBUG: setGameSpeed 3");
      }
   }

    static bool isGamePaused() {
      return GameTime.isGamePaused();
   }

    static int getMouseXScaled() {
      return Mouse.getX();
   }

    static int getMouseYScaled() {
      return Mouse.getY();
   }

    static int getMouseX() {
      return Mouse.getXA();
   }

    static void setMouseXY(int var0, int var1) {
      Mouse.setXY(var0, var1);
   }

    static bool isMouseButtonDown(int var0) {
      return Mouse.isButtonDown(var0);
   }

    static int getMouseY() {
      return Mouse.getYA();
   }

    static BaseSoundManager getSoundManager() {
      return SoundManager.instance;
   }

    static std::string getLastPlayedDate(const std::string& var0) {
    File var1 = std::make_shared<File>(ZomboidFileSystem.instance.getSaveDir() + File.separator + var0);
      if (!var1.exists()) {
         return Translator.getText("UI_LastPlayed") + "???";
      } else {
    Date var2 = std::make_shared<Date>(var1.lastModified());
    SimpleDateFormat var3 = std::make_shared<SimpleDateFormat>("dd/MM/yyyy HH:mm");
    std::string var4 = var3.format(var2);
         return Translator.getText("UI_LastPlayed") + var4;
      }
   }

    static Texture getTextureFromSaveDir(const std::string& var0, const std::string& var1) {
      TextureID.UseFiltering = true;
    std::string var2 = ZomboidFileSystem.instance.getSaveDir() + File.separator + var1 + File.separator + var0;
    Texture var3 = Texture.getSharedTexture(var2);
      TextureID.UseFiltering = false;
    return var3;
   }

    static KahluaTable getSaveInfo(const std::string& var0) {
      if (!var0.contains(File.separator)) {
         var0 = IsoWorld.instance.getGameMode() + File.separator + var0;
      }

    KahluaTable var1 = LuaManager.platform.newTable();
    File var2 = std::make_shared<File>(ZomboidFileSystem.instance.getSaveDir() + File.separator + var0);
      if (var2.exists()) {
    Date var3 = std::make_shared<Date>(var2.lastModified());
    SimpleDateFormat var4 = std::make_shared<SimpleDateFormat>("dd/MM/yyyy HH:mm");
    std::string var5 = var4.format(var3);
         var1.rawset("lastPlayed", var5);
         std::string[] var6 = var0.split("\\" + File.separator);
         var1.rawset("saveName", var2.getName());
         var1.rawset("gameMode", var6[var6.length - 2]);
      }

      var2 = std::make_shared<File>(ZomboidFileSystem.instance.getSaveDir() + File.separator + var0 + File.separator + "map_ver.bin");
      if (var2.exists()) {
         try (
    FileInputStream var23 = std::make_shared<FileInputStream>(var2);
    DataInputStream var25 = std::make_shared<DataInputStream>(var23);
         ) {
    int var27 = var25.readInt();
            var1.rawset("worldVersion", (double)var27);
            if (var27 >= 18) {
               try {
    std::string var29 = GameWindow.ReadString(var25);
                  if (var29 == "DEFAULT")) {
                     var29 = "Muldraugh, KY";
                  }

                  var1.rawset("mapName", var29);
               } catch (Exception var17) {
               }
            }

            if (var27 >= 74) {
               try {
    std::string var30 = GameWindow.ReadString(var25);
                  var1.rawset("difficulty", var30);
               } catch (Exception var16) {
               }
            }
         } catch (Exception var21) {
            ExceptionLogger.logException(var21);
         }
      }

    std::string var24 = ZomboidFileSystem.instance.getSaveDir() + File.separator + var0 + File.separator + "mods.txt";
    ActiveMods var26 = std::make_shared<ActiveMods>(var0);
    ActiveModsFile var28 = std::make_shared<ActiveModsFile>();
      if (var28.read(var24, var26)) {
         var1.rawset("activeMods", var26);
      }

    std::string var31 = ZomboidFileSystem.instance.getSaveDir() + File.separator + var0;
      var1.rawset("playerAlive", PlayerDBHelper.isPlayerAlive(var31, 1));
    KahluaTable var7 = LuaManager.platform.newTable();

      try {
    std::vector var8 = PlayerDBHelper.getPlayers(var31);

         for (byte var9 = 0; var9 < var8.size(); var9 += 3) {
    double var10 = (double)var8.get(var9);
    std::string var11 = (std::string)var8.get(var9 + 1);
    bool var12 = (bool)var8.get(var9 + 2);
    KahluaTable var13 = LuaManager.platform.newTable();
            var13.rawset("sqlID", var10);
            var13.rawset("name", var11);
            var13.rawset("isDead", var12);
            var7.rawset(var9 / 3 + 1, var13);
         }
      } catch (Exception var18) {
         ExceptionLogger.logException(var18);
      }

      var1.rawset("players", var7);
    return var1;
   }

    static bool renameSaveFile(const std::string& var0, const std::string& var1, const std::string& var2) {
      if (var0 == nullptr || var0.contains("/") || var0.contains("\\") || var0.contains(File.separator) || StringUtils.containsDoubleDot(var0)) {
    return false;
      } else if (var1 == nullptr || var1.contains("/") || var1.contains("\\") || var1.contains(File.separator) || StringUtils.containsDoubleDot(var1)) {
    return false;
      } else if (var2 != nullptr && !var2.contains("/") && !var2.contains("\\") && !var2.contains(File.separator) && !StringUtils.containsDoubleDot(var2)) {
    std::string var3 = sanitizeWorldName(var2);
         if (var3 == var2) && !var3.startsWith(".") && !var3.endsWith(".")) {
            if (!std::make_shared<File>(ZomboidFileSystem.instance.getSaveDirSub(var0)).exists()) {
    return false;
            } else {
    Path var4 = FileSystems.getDefault().getPath(ZomboidFileSystem.instance.getSaveDirSub(var0 + File.separator + var1));
    Path var5 = FileSystems.getDefault().getPath(ZomboidFileSystem.instance.getSaveDirSub(var0 + File.separator + var3));

               try {
                  Files.move(var4, var5);
    return true;
               } catch (IOException var7) {
    return false;
               }
            }
         } else {
    return false;
         }
      } else {
    return false;
      }
   }

    static void setSavefilePlayer1(const std::string& var0, const std::string& var1, int var2) {
    std::string var3 = ZomboidFileSystem.instance.getSaveDirSub(var0 + File.separator + var1);

      try {
         PlayerDBHelper.setPlayer1(var3, var2);
      } catch (Exception var5) {
         ExceptionLogger.logException(var5);
      }
   }

    static int getServerSavedWorldVersion(const std::string& var0) {
    File var1 = std::make_shared<File>(ZomboidFileSystem.instance.getSaveDir() + File.separator + var0 + File.separator + "map_t.bin");
      if (var1.exists()) {
         try {
    uint8_t var14;
            try (
    FileInputStream var2 = std::make_shared<FileInputStream>(var1);
    DataInputStream var3 = std::make_shared<DataInputStream>(var2);
            ) {
    uint8_t var4 = var3.readByte();
    uint8_t var5 = var3.readByte();
    uint8_t var6 = var3.readByte();
    uint8_t var7 = var3.readByte();
               if (var4 == 71 && var5 == 77 && var6 == 84 && var7 == 77) {
                  return var3.readInt();
               }

               var14 = 1;
            }

    return var14;
         } catch (Exception var13) {
            var13.printStackTrace();
         }
      }

    return 0;
   }

    static KahluaTable getZombieInfo(IsoZombie var0) {
    KahluaTable var1 = LuaManager.platform.newTable();
      if (var0 == nullptr) {
    return var1;
      } else {
         var1.rawset("OnlineID", var0.OnlineID);
         var1.rawset("RealX", var0.realx);
         var1.rawset("RealY", var0.realy);
         var1.rawset("X", var0.x);
         var1.rawset("Y", var0.y);
         var1.rawset("TargetX", var0.networkAI.targetX);
         var1.rawset("TargetY", var0.networkAI.targetY);
         var1.rawset("PathLength", var0.getPathFindBehavior2().getPathLength());
         var1.rawset(
            "TargetLength",
            Math.sqrt(
               (var0.x - var0.getPathFindBehavior2().getTargetX()) * (var0.x - var0.getPathFindBehavior2().getTargetX())
                  + (var0.y - var0.getPathFindBehavior2().getTargetY()) * (var0.y - var0.getPathFindBehavior2().getTargetY())
            )
         );
         var1.rawset("clientActionState", var0.getActionStateName());
         var1.rawset("clientAnimationState", var0.getAnimationStateName());
         var1.rawset("finderProgress", var0.getFinder().progress.name());
         var1.rawset("usePathFind", bool.toString(var0.networkAI.usePathFind));
         var1.rawset("owner", var0.authOwner.username);
         var0.networkAI.DebugInterfaceActive = true;
    return var1;
      }
   }

    static KahluaTable getPlayerInfo(IsoPlayer var0) {
    KahluaTable var1 = LuaManager.platform.newTable();
      if (var0 == nullptr) {
    return var1;
      } else {
    long var2 = GameTime.getServerTime() / 1000000L;
         var1.rawset("OnlineID", var0.OnlineID);
         var1.rawset("RealX", var0.realx);
         var1.rawset("RealY", var0.realy);
         var1.rawset("X", var0.x);
         var1.rawset("Y", var0.y);
         var1.rawset("TargetX", var0.networkAI.targetX);
         var1.rawset("TargetY", var0.networkAI.targetY);
         var1.rawset("TargetT", var0.networkAI.targetZ);
         var1.rawset("ServerT", var2);
         var1.rawset("PathLength", var0.getPathFindBehavior2().getPathLength());
         var1.rawset(
            "TargetLength",
            Math.sqrt(
               (var0.x - var0.getPathFindBehavior2().getTargetX()) * (var0.x - var0.getPathFindBehavior2().getTargetX())
                  + (var0.y - var0.getPathFindBehavior2().getTargetY()) * (var0.y - var0.getPathFindBehavior2().getTargetY())
            )
         );
         var1.rawset("clientActionState", var0.getActionStateName());
         var1.rawset("clientAnimationState", var0.getAnimationStateName());
         var1.rawset("finderProgress", var0.getFinder().progress.name());
         var1.rawset("usePathFind", bool.toString(var0.networkAI.usePathFind));
    return var1;
      }
   }

    static KahluaTable getMapInfo(const std::string& var0) {
      if (var0.contains(";")) {
         var0 = var0.split(";")[0];
      }

    std::unordered_map var1 = ChooseGameInfo.getMapDetails(var0);
      if (var1 == nullptr) {
    return nullptr;
      } else {
    KahluaTable var2 = LuaManager.platform.newTable();
         var2.rawset("description", var1.getDescription());
         var2.rawset("dir", var1.getDirectory());
    KahluaTable var3 = LuaManager.platform.newTable();
    uint8_t var4 = 1;

         for (std::string var6 : var1.getLotDirectories()) {
            var3.rawset((double)var4, var6);
         }

         var2.rawset("lots", var3);
         var2.rawset("thumb", var1.getThumbnail());
         var2.rawset("title", var1.getTitle());
    return var2;
      }
   }

    static KahluaTable getVehicleInfo(BaseVehicle var0) {
      if (var0 == nullptr) {
    return nullptr;
      } else {
    KahluaTable var1 = LuaManager.platform.newTable();
         var1.rawset("name", var0.getScript().getName());
         var1.rawset("weight", var0.getMass());
         var1.rawset("speed", var0.getMaxSpeed());
         var1.rawset("frontEndDurability", int.toString(var0.frontEndDurability));
         var1.rawset("rearEndDurability", int.toString(var0.rearEndDurability));
         var1.rawset("currentFrontEndDurability", int.toString(var0.currentFrontEndDurability));
         var1.rawset("currentRearEndDurability", int.toString(var0.currentRearEndDurability));
         var1.rawset("engine_running", var0.isEngineRunning());
         var1.rawset("engine_started", var0.isEngineStarted());
         var1.rawset("engine_quality", var0.getEngineQuality());
         var1.rawset("engine_loudness", var0.getEngineLoudness());
         var1.rawset("engine_power", var0.getEnginePower());
         var1.rawset("battery_isset", var0.getBattery() != nullptr);
         var1.rawset("battery_charge", var0.getBatteryCharge());
         var1.rawset("gas_amount", var0.getPartById("GasTank").getContainerContentAmount());
         var1.rawset("gas_capacity", var0.getPartById("GasTank").getContainerCapacity());
    VehiclePart var2 = var0.getPartById("DoorFrontLeft");
         var1.rawset("doorleft_exist", var2 != nullptr);
         if (var2 != nullptr) {
            var1.rawset("doorleft_open", var2.getDoor().isOpen());
            var1.rawset("doorleft_locked", var2.getDoor().isLocked());
            var1.rawset("doorleft_lockbroken", var2.getDoor().isLockBroken());
    VehicleWindow var3 = var2.findWindow();
            var1.rawset("windowleft_exist", var3 != nullptr);
            if (var3 != nullptr) {
               var1.rawset("windowleft_open", var3.isOpen());
               var1.rawset("windowleft_health", var3.getHealth());
            }
         }

    VehiclePart var5 = var0.getPartById("DoorFrontRight");
         var1.rawset("doorright_exist", var5 != nullptr);
         if (var2 != nullptr) {
            var1.rawset("doorright_open", var5.getDoor().isOpen());
            var1.rawset("doorright_locked", var5.getDoor().isLocked());
            var1.rawset("doorright_lockbroken", var5.getDoor().isLockBroken());
    VehicleWindow var4 = var5.findWindow();
            var1.rawset("windowright_exist", var4 != nullptr);
            if (var4 != nullptr) {
               var1.rawset("windowright_open", var4.isOpen());
               var1.rawset("windowright_health", var4.getHealth());
            }
         }

         var1.rawset("headlights_set", var0.hasHeadlights());
         var1.rawset("headlights_on", var0.getHeadlightsOn());
         if (var0.getPartById("Heater") != nullptr) {
            var1.rawset("heater_isset", true);
    void* var6 = var0.getPartById("Heater").getModData().rawget("active");
            if (var6 == nullptr) {
               var1.rawset("heater_on", false);
            } else {
               var1.rawset("heater_on", var6 == bool.TRUE);
            }
         } else {
            var1.rawset("heater_isset", false);
         }

    return var1;
      }
   }

   public static std::vector<std::string> getLotDirectories() {
      return IsoWorld.instance.MetaGrid != nullptr ? IsoWorld.instance.MetaGrid.getLotDirectories() : nullptr;
   }

    static void useTextureFiltering(bool var0) {
      TextureID.UseFiltering = var0;
   }

    static Texture getTexture(const std::string& var0) {
      return Texture.getSharedTexture(var0);
   }

    static TextManager getTextManager() {
      return TextManager.instance;
   }

    static void setProgressBarValue(IsoPlayer var0, int var1) {
      if (var0.isLocalPlayer()) {
         UIManager.getProgressBar(var0.getPlayerNum()).setValue(var1);
      }
   }

    static std::string getText(const std::string& var0) {
      return Translator.getText(var0);
   }

    static std::string getText(const std::string& var0, void* var1) {
      return Translator.getText(var0, var1);
   }

    static std::string getText(const std::string& var0, void* var1, void* var2) {
      return Translator.getText(var0, var1, var2);
   }

    static std::string getText(const std::string& var0, void* var1, void* var2, void* var3) {
      return Translator.getText(var0, var1, var2, var3);
   }

    static std::string getText(const std::string& var0, void* var1, void* var2, void* var3, void* var4) {
      return Translator.getText(var0, var1, var2, var3, var4);
   }

    static std::string getTextOrNull(const std::string& var0) {
      return Translator.getTextOrNull(var0);
   }

    static std::string getTextOrNull(const std::string& var0, void* var1) {
      return Translator.getTextOrNull(var0, var1);
   }

    static std::string getTextOrNull(const std::string& var0, void* var1, void* var2) {
      return Translator.getTextOrNull(var0, var1, var2);
   }

    static std::string getTextOrNull(const std::string& var0, void* var1, void* var2, void* var3) {
      return Translator.getTextOrNull(var0, var1, var2, var3);
   }

    static std::string getTextOrNull(const std::string& var0, void* var1, void* var2, void* var3, void* var4) {
      return Translator.getTextOrNull(var0, var1, var2, var3, var4);
   }

    static std::string getItemText(const std::string& var0) {
      return Translator.getDisplayItemName(var0);
   }

    static std::string getRadioText(const std::string& var0) {
      return Translator.getRadioText(var0);
   }

    static std::string getTextMediaEN(const std::string& var0) {
      return Translator.getTextMediaEN(var0);
   }

    static std::string getItemNameFromFullType(const std::string& var0) {
      return Translator.getItemNameFromFullType(var0);
   }

    static std::string getRecipeDisplayName(const std::string& var0) {
      return Translator.getRecipeName(var0);
   }

    static std::string getMyDocumentFolder() {
      return Core.getMyDocumentFolder();
   }

    static IsoSpriteManager getSpriteManager(const std::string& var0) {
      return IsoSpriteManager.instance;
   }

    static IsoSprite getSprite(const std::string& var0) {
      return IsoSpriteManager.instance.getSprite(var0);
   }

    static void getServerModData() {
      GameClient.getCustomModData();
   }

    static bool isXBOXController() {
      for (int var0 = 0; var0 < GameWindow.GameInput.getControllerCount(); var0++) {
    Controller var1 = GameWindow.GameInput.getController(var0);
         if (var1 != nullptr && var1.getGamepadName().contains("XBOX 360")) {
    return true;
         }
      }

    return false;
   }

    static void sendClientCommand(const std::string& var0, const std::string& var1, KahluaTable var2) {
      if (GameClient.bClient && GameClient.bIngame) {
         GameClient.instance.sendClientCommand(nullptr, var0, var1, var2);
      } else {
         if (GameServer.bServer) {
            throw IllegalStateException("can't call this function on the server");
         }

         SinglePlayerClient.sendClientCommand(nullptr, var0, var1, var2);
      }
   }

    static void sendClientCommand(IsoPlayer var0, const std::string& var1, const std::string& var2, KahluaTable var3) {
      if (var0 != nullptr && var0.isLocalPlayer()) {
         if (GameClient.bClient && GameClient.bIngame) {
            GameClient.instance.sendClientCommand(var0, var1, var2, var3);
         } else {
            if (GameServer.bServer) {
               throw IllegalStateException("can't call this function on the server");
            }

            SinglePlayerClient.sendClientCommand(var0, var1, var2, var3);
         }
      }
   }

    static void sendServerCommand(const std::string& var0, const std::string& var1, KahluaTable var2) {
      if (GameServer.bServer) {
         GameServer.sendServerCommand(var0, var1, var2);
      }
   }

    static void sendServerCommand(IsoPlayer var0, const std::string& var1, const std::string& var2, KahluaTable var3) {
      if (GameServer.bServer) {
         GameServer.sendServerCommand(var0, var1, var2, var3);
      }
   }

    static std::string getOnlineUsername() {
      return IsoPlayer.getInstance().getDisplayName();
   }

    static bool isValidUserName(const std::string& var0) {
      return ServerWorldDatabase.isValidUserName(var0);
   }

    static std::string getHourMinute() {
      return LuaManager.getHourMinuteJava();
   }

    static void SendCommandToServer(const std::string& var0) {
      GameClient.SendCommandToServer(var0);
   }

    static bool isAdmin() {
      return GameClient.bClient && GameClient.connection.accessLevel == 32;
   }

    static bool canModifyPlayerScoreboard() {
      return GameClient.bClient && GameClient.connection.accessLevel != 1;
   }

    static bool isAccessLevel(const std::string& var0) {
      if (GameClient.bClient) {
         return GameClient.connection.accessLevel == 1 ? false : GameClient.connection.accessLevel == PlayerType.fromString(var0);
      } else {
    return false;
      }
   }

    static void sendBandage(int var0, int var1, bool var2, float var3, bool var4, const std::string& var5) {
      GameClient.instance.sendBandage(var0, var1, var2, var3, var4, var5);
   }

    static void sendCataplasm(int var0, int var1, float var2, float var3, float var4) {
      GameClient.instance.sendCataplasm(var0, var1, var2, var3, var4);
   }

    static void sendStitch(IsoGameCharacter var0, IsoGameCharacter var1, BodyPart var2, InventoryItem var3, bool var4) {
      GameClient.instance.sendStitch(var0, var1, var2, var3, var4);
   }

    static void sendDisinfect(IsoGameCharacter var0, IsoGameCharacter var1, BodyPart var2, InventoryItem var3) {
      GameClient.instance.sendDisinfect(var0, var1, var2, var3);
   }

    static void sendSplint(int var0, int var1, bool var2, float var3, const std::string& var4) {
      GameClient.instance.sendSplint(var0, var1, var2, var3, var4);
   }

    static void sendRemoveGlass(IsoGameCharacter var0, IsoGameCharacter var1, BodyPart var2, bool var3) {
      GameClient.instance.sendRemoveGlass(var0, var1, var2, var3);
   }

    static void sendRemoveBullet(IsoGameCharacter var0, IsoGameCharacter var1, BodyPart var2) {
      GameClient.instance.sendRemoveBullet(var0, var1, var2);
   }

    static void sendCleanBurn(IsoGameCharacter var0, IsoGameCharacter var1, BodyPart var2, InventoryItem var3) {
      GameClient.instance.sendCleanBurn(var0, var1, var2, var3);
   }

    static GameClient getGameClient() {
      return GameClient.instance;
   }

    static void sendRequestInventory(IsoPlayer var0) {
      GameClient.sendRequestInventory(var0);
   }

    static void InvMngGetItem(long var0, const std::string& var2, IsoPlayer var3) {
      GameClient.invMngRequestItem((int)var0, var2, var3);
   }

    static void InvMngRemoveItem(long var0, IsoPlayer var2) {
      GameClient.invMngRequestRemoveItem((int)var0, var2);
   }

   public static std::vector<IsoPlayer> getConnectedPlayers() {
      return GameClient.instance.getConnectedPlayers();
   }

    static IsoPlayer getPlayerFromUsername(const std::string& var0) {
      return GameClient.instance.getPlayerFromUsername(var0);
   }

    static bool isCoopHost() {
      return GameClient.connection != nullptr && GameClient.connection.isCoopHost;
   }

    static void setAdmin() {
      if (CoopMaster.instance.isRunning()) {
    std::string var0 = "admin";
         if (GameClient.connection.accessLevel == 32) {
            var0 = "";
         }

         GameClient.connection.accessLevel = PlayerType.fromString(var0);
         IsoPlayer.getInstance().accessLevel = var0;
         GameClient.SendCommandToServer("/setaccesslevel \"" + IsoPlayer.getInstance().username + "\" \"" + (var0 == "") ? "none" : var0) + "\"");
         if (var0 == "") && IsoPlayer.getInstance().isInvisible() || var0 == "admin") && !IsoPlayer.getInstance().isInvisible()) {
            GameClient.SendCommandToServer("/invisible");
         }
      }
   }

    static void addWarningPoint(const std::string& var0, const std::string& var1, int var2) {
      if (GameClient.bClient) {
         GameClient.instance.addWarningPoint(var0, var1, var2);
      }
   }

    static void toggleSafetyServer(IsoPlayer var0) {
   }

    static void disconnect() {
      GameClient.connection.forceDisconnect("lua-disconnect");
   }

    static void writeLog(const std::string& var0, const std::string& var1) {
      LoggerManager.getLogger(var0).write(var1);
   }

    static void doKeyPress(bool var0) {
      GameKeyboard.doLuaKeyPressed = var0;
   }

   public static std::stack<EvolvedRecipe> getEvolvedRecipes() {
      return ScriptManager.instance.getAllEvolvedRecipes();
   }

    static Zone getZone(int var0, int var1, int var2) {
      return IsoWorld.instance.MetaGrid.getZoneAt(var0, var1, var2);
   }

   public static std::vector<Zone> getZones(int var0, int var1, int var2) {
      return IsoWorld.instance.MetaGrid.getZonesAt(var0, var1, var2);
   }

    static VehicleZone getVehicleZoneAt(int var0, int var1, int var2) {
      return IsoWorld.instance.MetaGrid.getVehicleZoneAt(var0, var1, var2);
   }

    static std::string replaceWith(const std::string& var0, const std::string& var1, const std::string& var2) {
      return var0.replaceFirst(var1, var2);
   }

    static long getTimestamp() {
      return System.currentTimeMillis() / 1000L;
   }

    static long getTimestampMs() {
      return System.currentTimeMillis();
   }

    static void forceSnowCheck() {
      ErosionMain.getInstance().snowCheck();
   }

    static long getGametimeTimestamp() {
      return GameTime.instance.getCalender().getTimeInMillis() / 1000L;
   }

    static bool canInviteFriends() {
      return GameClient.bClient && SteamUtils.isSteamModeEnabled() ? CoopMaster.instance.isRunning() || !GameClient.bCoopInvite : false;
   }

    static void inviteFriend(const std::string& var0) {
      if (CoopMaster.instance != nullptr && CoopMaster.instance.isRunning()) {
         CoopMaster.instance.sendMessage("invite-add", var0);
      }

      SteamFriends.InviteUserToGame(SteamUtils.convertStringToSteamID(var0), "+connect " + GameClient.ip + ":" + GameClient.port);
   }

    static KahluaTable getFriendsList() {
    KahluaTable var0 = LuaManager.platform.newTable();
      if (!getSteamModeActive()) {
    return var0;
      } else {
    std::vector var1 = SteamFriends.GetFriendList();
    int var2 = 1;

         for (int var3 = 0; var3 < var1.size(); var3++) {
    SteamFriend var4 = (SteamFriend)var1.get(var3);
    double var5 = (double)var2;
            var0.rawset(var5, var4);
            var2++;
         }

    return var0;
      }
   }

    static bool getSteamModeActive() {
      return SteamUtils.isSteamModeEnabled();
   }

    static bool isValidSteamID(const std::string& var0) {
      return var0 != nullptr && !var0.empty() ? SteamUtils.isValidSteamID(var0) : false;
   }

    static std::string getCurrentUserSteamID() {
      return SteamUtils.isSteamModeEnabled() && !GameServer.bServer ? SteamUser.GetSteamIDString() : nullptr;
   }

    static std::string getCurrentUserProfileName() {
      return SteamUtils.isSteamModeEnabled() && !GameServer.bServer ? SteamFriends.GetFriendPersonaName(SteamUser.GetSteamID()) : nullptr;
   }

    static bool getSteamScoreboard() {
      if (SteamUtils.isSteamModeEnabled() && GameClient.bClient) {
    std::string var0 = ServerOptions.instance.SteamScoreboard.getValue();
         return "true" == var0) || GameClient.connection.accessLevel == 32 && "admin" == var0);
      } else {
    return false;
      }
   }

    static bool isSteamOverlayEnabled() {
      return SteamUtils.isOverlayEnabled();
   }

    static void activateSteamOverlayToWorkshop() {
      if (SteamUtils.isOverlayEnabled()) {
         SteamFriends.ActivateGameOverlayToWebPage("steam://url/SteamWorkshopPage/108600");
      }
   }

    static void activateSteamOverlayToWorkshopUser() {
      if (SteamUtils.isOverlayEnabled()) {
         SteamFriends.ActivateGameOverlayToWebPage("steam://url/SteamIDCommunityFilesPage/" + SteamUser.GetSteamIDString() + "/108600");
      }
   }

    static void activateSteamOverlayToWorkshopItem(const std::string& var0) {
      if (SteamUtils.isOverlayEnabled() && SteamUtils.isValidSteamID(var0)) {
         SteamFriends.ActivateGameOverlayToWebPage("steam://url/CommunityFilePage/" + var0);
      }
   }

    static void activateSteamOverlayToWebPage(const std::string& var0) {
      if (SteamUtils.isOverlayEnabled()) {
         SteamFriends.ActivateGameOverlayToWebPage(var0);
      }
   }

    static std::string getSteamProfileNameFromSteamID(const std::string& var0) {
      if (SteamUtils.isSteamModeEnabled() && GameClient.bClient) {
    long var1 = SteamUtils.convertStringToSteamID(var0);
         if (var1 != -1L) {
            return SteamFriends.GetFriendPersonaName(var1);
         }
      }

    return nullptr;
   }

    static Texture getSteamAvatarFromSteamID(const std::string& var0) {
      if (SteamUtils.isSteamModeEnabled() && GameClient.bClient) {
    long var1 = SteamUtils.convertStringToSteamID(var0);
         if (var1 != -1L) {
            return Texture.getSteamAvatar(var1);
         }
      }

    return nullptr;
   }

    static std::string getSteamIDFromUsername(const std::string& var0) {
      if (SteamUtils.isSteamModeEnabled() && GameClient.bClient) {
    IsoPlayer var1 = GameClient.instance.getPlayerFromUsername(var0);
         if (var1 != nullptr) {
            return SteamUtils.convertSteamIDToString(var1.getSteamID());
         }
      }

    return nullptr;
   }

    static void resetRegionFile() {
      ServerOptions.getInstance().resetRegionFile();
   }

    static std::string getSteamProfileNameFromUsername(const std::string& var0) {
      if (SteamUtils.isSteamModeEnabled() && GameClient.bClient) {
    IsoPlayer var1 = GameClient.instance.getPlayerFromUsername(var0);
         if (var1 != nullptr) {
            return SteamFriends.GetFriendPersonaName(var1.getSteamID());
         }
      }

    return nullptr;
   }

    static Texture getSteamAvatarFromUsername(const std::string& var0) {
      if (SteamUtils.isSteamModeEnabled() && GameClient.bClient) {
    IsoPlayer var1 = GameClient.instance.getPlayerFromUsername(var0);
         if (var1 != nullptr) {
            return Texture.getSteamAvatar(var1.getSteamID());
         }
      }

    return nullptr;
   }

   public static std::vector<SteamWorkshopItem> getSteamWorkshopStagedItems() {
      return SteamUtils.isSteamModeEnabled() ? SteamWorkshop.instance.loadStagedItems() : nullptr;
   }

   public static std::vector<std::string> getSteamWorkshopItemIDs() {
      if (SteamUtils.isSteamModeEnabled()) {
    std::vector var0 = new std::vector();
         std::string[] var1 = SteamWorkshop.instance.GetInstalledItemFolders();
         if (var1 == nullptr) {
    return var0;
         } else {
            for (int var2 = 0; var2 < var1.length; var2++) {
    std::string var3 = SteamWorkshop.instance.getIDFromItemInstallFolder(var1[var2]);
               if (var3 != nullptr) {
                  var0.push_back(var3);
               }
            }

    return var0;
         }
      } else {
    return nullptr;
      }
   }

   public static std::vector<Mod> getSteamWorkshopItemMods(std::string var0) {
      if (SteamUtils.isSteamModeEnabled()) {
    long var1 = SteamUtils.convertStringToSteamID(var0);
         if (var1 > 0L) {
            return ZomboidFileSystem.instance.getWorkshopItemMods(var1);
         }
      }

    return nullptr;
   }

    static bool isSteamRunningOnSteamDeck() {
      return SteamUtils.isSteamModeEnabled() ? SteamUtils.isRunningOnSteamDeck() : false;
   }

    static bool showSteamGamepadTextInput(bool var0, bool var1, const std::string& var2, int var3, const std::string& var4) {
      return SteamUtils.isSteamModeEnabled() ? SteamUtils.showGamepadTextInput(var0, var1, var2, var3, var4) : false;
   }

    static bool showSteamFloatingGamepadTextInput(bool var0, int var1, int var2, int var3, int var4) {
      return SteamUtils.isSteamModeEnabled() ? SteamUtils.showFloatingGamepadTextInput(var0, var1, var2, var3, var4) : false;
   }

    static bool isFloatingGamepadTextInputVisible() {
      return SteamUtils.isSteamModeEnabled() ? SteamUtils.isFloatingGamepadTextInputVisible() : false;
   }

    static void sendPlayerStatsChange(IsoPlayer var0) {
      if (GameClient.bClient) {
         GameClient.instance.sendChangedPlayerStats(var0);
      }
   }

    static void sendPersonalColor(IsoPlayer var0) {
      if (GameClient.bClient) {
         GameClient.instance.sendPersonalColor(var0);
      }
   }

    static void requestTrading(IsoPlayer var0, IsoPlayer var1) {
      GameClient.instance.requestTrading(var0, var1);
   }

    static void acceptTrading(IsoPlayer var0, IsoPlayer var1, bool var2) {
      GameClient.instance.acceptTrading(var0, var1, var2);
   }

    static void tradingUISendAddItem(IsoPlayer var0, IsoPlayer var1, InventoryItem var2) {
      GameClient.instance.tradingUISendAddItem(var0, var1, var2);
   }

    static void tradingUISendRemoveItem(IsoPlayer var0, IsoPlayer var1, int var2) {
      GameClient.instance.tradingUISendRemoveItem(var0, var1, var2);
   }

    static void tradingUISendUpdateState(IsoPlayer var0, IsoPlayer var1, int var2) {
      GameClient.instance.tradingUISendUpdateState(var0, var1, var2);
   }

    static void querySteamWorkshopItemDetails(std::vector<std::string> var0, LuaClosure var1, void* var2) {
      if (var0 == nullptr || var1 == nullptr) {
         throw std::make_unique<NullPointerException>();
      } else if (var0.empty()) {
         if (var2 == nullptr) {
            LuaManager.caller.pcall(LuaManager.thread, var1, new Object[]{"Completed", std::make_unique<std::vector>()});
         } else {
            LuaManager.caller.pcall(LuaManager.thread, var1, new Object[]{var2, "Completed", std::make_unique<std::vector>()});
         }
      } else {
    std::make_shared<ItemQuery>();
      }
   }

    static void connectToServerStateCallback(const std::string& var0) {
      if (ConnectToServerState.instance != nullptr) {
         ConnectToServerState.instance.FromLua(var0);
      }
   }

    static KahluaTable getPublicServersList() {
    KahluaTable var0 = LuaManager.platform.newTable();
      if (!SteamUtils.isSteamModeEnabled() && !PublicServerUtil.isEnabled()) {
    return var0;
      } else if (System.currentTimeMillis() - timeLastRefresh < 60000L) {
    return var0;
      } else {
    std::vector var1 = new std::vector();

         try {
            if (getSteamModeActive()) {
               ServerBrowser.RefreshInternetServers();
    std::vector var2 = ServerBrowser.GetServerList();

    for (auto& var4 : var2)    Server var5 = std::make_shared<Server>();
                  var5.setName(var4.name);
                  var5.setDescription(var4.gameDescription);
                  var5.setSteamId(int64_t.toString(var4.steamId));
                  var5.setPing(int.toString(var4.ping));
                  var5.setPlayers(int.toString(var4.numPlayers));
                  var5.setMaxPlayers(int.toString(var4.maxPlayers));
                  var5.setOpen(true);
                  var5.setIp(var4.address);
                  var5.setPort(int.toString(var4.port));
                  var5.setMods(var4.tags);
                  var5.setVersion(Core.getInstance().getVersion());
                  var5.setLastUpdate(1);
                  var1.push_back(var5);
               }

               System.out.printf("%d servers\n", var2.size());
            } else {
    URL var18 = std::make_shared<URL>(PublicServerUtil.webSite + "servers.xml");
    InputStreamReader var20 = std::make_shared<InputStreamReader>(var18.openStream());
    BufferedReader var22 = std::make_shared<BufferedReader>(var20);
    void* var24 = nullptr;
    std::stringstream var6 = new std::stringstream();

               while ((var24 = var22.readLine()) != nullptr) {
                  var6.append((std::string)var24).append('\n');
               }

               var22.close();
    DocumentBuilderFactory var7 = DocumentBuilderFactory.newInstance();
    DocumentBuilder var8 = var7.newDocumentBuilder();
    Document var9 = var8.parse(std::make_shared<InputSource>(std::make_shared<StringReader>(var6)));
               var9.getDocumentElement().normalize();
    NodeList var10 = var9.getElementsByTagName("server");

               for (int var11 = 0; var11 < var10.getLength(); var11++) {
    Node var12 = var10.item(var11);
                  if (var12.getNodeType() == 1) {
    Element var13 = (Element)var12;
    Server var14 = std::make_shared<Server>();
                     var14.setName(var13.getElementsByTagName("name").item(0).getTextContent());
                     if (var13.getElementsByTagName("desc").item(0) != nullptr && !"" == var13.getElementsByTagName("desc").item(0).getTextContent())) {
                        var14.setDescription(var13.getElementsByTagName("desc").item(0).getTextContent());
                     }

                     var14.setIp(var13.getElementsByTagName("ip").item(0).getTextContent());
                     var14.setPort(var13.getElementsByTagName("port").item(0).getTextContent());
                     var14.setPlayers(var13.getElementsByTagName("players").item(0).getTextContent());
                     var14.setMaxPlayers(var13.getElementsByTagName("maxPlayers").item(0).getTextContent());
                     if (var13.getElementsByTagName("version") != nullptr && var13.getElementsByTagName("version").item(0) != nullptr) {
                        var14.setVersion(var13.getElementsByTagName("version").item(0).getTextContent());
                     }

                     var14.setOpen(var13.getElementsByTagName("open").item(0).getTextContent() == "1"));
    int var15 = int.parseInt(var13.getElementsByTagName("lastUpdate").item(0).getTextContent());
                     if (var13.getElementsByTagName("mods").item(0) != nullptr && !"" == var13.getElementsByTagName("mods").item(0).getTextContent())) {
                        var14.setMods(var13.getElementsByTagName("mods").item(0).getTextContent());
                     }

                     var14.setLastUpdate(std::make_shared<double>(Math.floor((getTimestamp() - var15.intValue()) / 60L)).intValue());
    NodeList var16 = var13.getElementsByTagName("password");
                     var14.setPasswordProtected(var16 != nullptr && var16.getLength() != 0 && var16.item(0).getTextContent() == "1"));
                     var1.push_back(var14);
                  }
               }
            }

    int var19 = 1;

            for (int var21 = 0; var21 < var1.size(); var21++) {
    Server var23 = (Server)var1.get(var21);
    double var26 = (double)var19;
               var0.rawset(var26, var23);
               var19++;
            }

            timeLastRefresh = Calendar.getInstance().getTimeInMillis();
    return var0;
         } catch (Exception var17) {
            var17.printStackTrace();
    return nullptr;
         }
      }
   }

    static void steamRequestInternetServersList() {
      ServerBrowser.RefreshInternetServers();
   }

    static void steamReleaseInternetServersRequest() {
      ServerBrowser.Release();
   }

    static int steamRequestInternetServersCount() {
      return ServerBrowser.GetServerCount();
   }

    static Server steamGetInternetServerDetails(int var0) {
      if (!ServerBrowser.IsRefreshing()) {
    return nullptr;
      } else {
    GameServerDetails var1 = ServerBrowser.GetServerDetails(var0);
         if (var1 == nullptr) {
    return nullptr;
         } else if (var1.tags.contains("hidden") || var1.tags.contains("hosted")) {
    return nullptr;
         } else if (!var1.tags.contains("hidden") && !var1.tags.contains("hosted")) {
    Server var2 = std::make_shared<Server>();
            var2.setName(var1.name);
            var2.setDescription("");
            var2.setSteamId(int64_t.toString(var1.steamId));
            var2.setPing(int.toString(var1.ping));
            var2.setPlayers(int.toString(var1.numPlayers));
            var2.setMaxPlayers(int.toString(var1.maxPlayers));
            var2.setOpen(true);
            var2.setPublic(true);
            if (var1.tags.contains("hidden")) {
               var2.setOpen(false);
               var2.setPublic(false);
            }

            var2.setIp(var1.address);
            var2.setPort(int.toString(var1.port));
            var2.setMods("");
            if (!var1.tags.replace("hidden", "").replace("hosted", "").replace(";", "").empty()) {
               var2.setMods(var1.tags.replace(";hosted", "").replace("hidden", ""));
            }

            var2.setHosted(var1.tags.contains("hosted"));
            var2.setVersion("");
            var2.setLastUpdate(1);
            var2.setPasswordProtected(var1.passwordProtected);
    return var2;
         } else {
    return nullptr;
         }
      }
   }

    static bool steamRequestServerRules(const std::string& var0, int var1) {
      return ServerBrowser.RequestServerRules(var0, var1);
   }

    static bool steamRequestServerDetails(const std::string& var0, int var1) {
      return ServerBrowser.QueryServer(var0, var1);
   }

    static bool isPublicServerListAllowed() {
      return SteamUtils.isSteamModeEnabled() ? true : PublicServerUtil.isEnabled();
   }

    static bool is64bit() {
      return "64" == System.getProperty("sun.arch.data.model"));
   }

    static void testSound() {
    float var0 = Mouse.getX();
    float var1 = Mouse.getY();
    int var2 = (int)IsoPlayer.getInstance().getZ();
    int var3 = (int)IsoUtils.XToIso(var0, var1, var2);
    int var4 = (int)IsoUtils.YToIso(var0, var1, var2);
    float var5 = 50.0F;
    float var6 = 1.0F;
    Ambient var7 = std::make_shared<Ambient>("Meta/House Alarm", var3, var4, var5, var6);
      var7.trackMouse = true;
      ((AmbientStreamManager)AmbientStreamManager.instance).ambient.push_back(var7);
   }

    static void debugSetRoomType(double var0) {
      ParameterRoomType.setRoomType(var0.intValue());
   }

    static KahluaTable copyTable(KahluaTable var0) {
      return LuaManager.copyTable(var0);
   }

    static KahluaTable copyTable(KahluaTable var0, KahluaTable var1) {
      return LuaManager.copyTable(var0, var1);
   }

    static DataInputStream getUrlInputStream(const std::string& var0) {
      if (var0 != nullptr && (var0.startsWith("https://") || var0.startsWith("http://"))) {
         try {
            return std::make_shared<DataInputStream>(std::make_shared<URL>(var0).openStream());
         } catch (IOException var2) {
            var2.printStackTrace();
    return nullptr;
         }
      } else {
    return nullptr;
      }
   }

    static void renderIsoCircle(float var0, float var1, float var2, float var3, float var4, float var5, float var6, float var7, int var8) {
    double var9 = Math.PI / 9;

      for (double var11 = 0.0; var11 < Math.PI * 2; var11 += var9) {
    float var13 = var0 + var3 * (float)Math.cos(var11);
    float var14 = var1 + var3 * (float)Math.sin(var11);
    float var15 = var0 + var3 * (float)Math.cos(var11 + var9);
    float var16 = var1 + var3 * (float)Math.sin(var11 + var9);
    float var17 = IsoUtils.XToScreenExact(var13, var14, var2, 0);
    float var18 = IsoUtils.YToScreenExact(var13, var14, var2, 0);
    float var19 = IsoUtils.XToScreenExact(var15, var16, var2, 0);
    float var20 = IsoUtils.YToScreenExact(var15, var16, var2, 0);
         LineDrawer.drawLine(var17, var18, var19, var20, var4, var5, var6, var7, var8);
      }
   }

    static void configureLighting(float var0) {
      if (LightingJNI.init) {
         LightingJNI.configure(var0);
      }
   }

    static void testHelicopter() {
      if (GameClient.bClient) {
         GameClient.SendCommandToServer("/chopper start");
      } else {
         IsoWorld.instance.helicopter.pickRandomTarget();
      }
   }

    static void endHelicopter() {
      if (GameClient.bClient) {
         GameClient.SendCommandToServer("/chopper stop");
      } else {
         IsoWorld.instance.helicopter.deactivate();
      }
   }

    static ServerSettingsManager getServerSettingsManager() {
      return ServerSettingsManager.instance;
   }

    static void rainConfig(const std::string& var0, int var1) {
      if ("alpha" == var0)) {
         IsoWorld.instance.CurrentCell.setRainAlpha(var1);
      }

      if ("intensity" == var0)) {
         IsoWorld.instance.CurrentCell.setRainIntensity(var1);
      }

      if ("speed" == var0)) {
         IsoWorld.instance.CurrentCell.setRainSpeed(var1);
      }

      if ("reloadTextures" == var0)) {
         IsoWorld.instance.CurrentCell.reloadRainTextures();
      }
   }

    static void sendSwitchSeat(BaseVehicle var0, IsoGameCharacter var1, int var2, int var3) {
      if (GameClient.bClient) {
         VehicleManager.instance.sendSwitchSeat(GameClient.connection, var0, var1, var2, var3);
      }
   }

    static BaseVehicle getVehicleById(int var0) {
      return VehicleManager.instance.getVehicleByID((short)var0);
   }

    void addBloodSplat(IsoGridSquare var1, int var2) {
      for (int var3 = 0; var3 < var2; var3++) {
         var1.getChunk().addBloodSplat(var1.x + Rand.Next(-0.5F, 0.5F), var1.y + Rand.Next(-0.5F, 0.5F), var1.z, Rand.Next(8));
      }
   }

    static void addCarCrash() {
    IsoGridSquare var0 = IsoPlayer.getInstance().getCurrentSquare();
      if (var0 != nullptr) {
    IsoChunk var1 = var0.getChunk();
         if (var1 != nullptr) {
    Zone var2 = var0.getZone();
            if (var2 != nullptr) {
               if (var1.canAddRandomCarCrash(var2, true)) {
                  var0.chunk.addRandomCarCrash(var2, true);
               }
            }
         }
      }
   }

    static IsoDeadBody createRandomDeadBody(IsoGridSquare var0, int var1) {
      if (var0 == nullptr) {
    return nullptr;
      } else {
    ItemPickerRoom var2 = (ItemPickerRoom)ItemPickerJava.rooms.get("all");
    HumanCorpse var3 = std::make_shared<HumanCorpse>(IsoWorld.instance.getCell(), var0.x, var0.y, var0.z);
         var3.setDir(IsoDirections.getRandom());
         var3.setDescriptor(SurvivorFactory.CreateSurvivor());
         var3.setFemale(var3.getDescriptor().isFemale());
         var3.initWornItems("Human");
         var3.initAttachedItems("Human");
    Outfit var4 = var3.getRandomDefaultOutfit();
         var3.dressInNamedOutfit(var4.m_Name);
         var3.initSpritePartsEmpty();
         var3.Dressup(var3.getDescriptor());

         for (int var5 = 0; var5 < var1; var5++) {
            var3.addBlood(nullptr, false, true, false);
         }

    IsoDeadBody var6 = std::make_shared<IsoDeadBody>(var3, true);
         ItemPickerJava.fillContainerType(var2, var6.getContainer(), var3.isFemale() ? "inventoryfemale" : "inventorymale", nullptr);
    return var6;
      }
   }

    void addZombieSitting(int var1, int var2, int var3) {
    IsoGridSquare var4 = IsoCell.getInstance().getGridSquare(var1, var2, var3);
      if (var4 != nullptr) {
         VirtualZombieManager.instance.choices.clear();
         VirtualZombieManager.instance.choices.push_back(var4);
    IsoZombie var5 = VirtualZombieManager.instance.createRealZombieAlways(IsoDirections.getRandom().index(), false);
         var5.bDressInRandomOutfit = true;
         ZombiePopulationManager.instance.sitAgainstWall(var5, var4);
      }
   }

    void addZombiesEating(int var1, int var2, int var3, int var4, bool var5) {
    IsoGridSquare var6 = IsoCell.getInstance().getGridSquare(var1, var2, var3);
      if (var6 != nullptr) {
         VirtualZombieManager.instance.choices.clear();
         VirtualZombieManager.instance.choices.push_back(var6);
    IsoZombie var7 = VirtualZombieManager.instance.createRealZombieAlways(Rand.Next(8), false);
         var7.setX(var6.x);
         var7.setY(var6.y);
         var7.setFakeDead(false);
         var7.setHealth(0.0F);
         var7.upKillCount = false;
         if (!var5) {
            var7.dressInRandomOutfit();

            for (int var8 = 0; var8 < 10; var8++) {
               var7.addHole(nullptr);
               var7.addBlood(nullptr, false, true, false);
            }

            var7.DoZombieInventory();
         }

         var7.setSkeleton(var5);
         if (var5) {
            var7.getHumanVisual().setSkinTextureIndex(2);
         }

    IsoDeadBody var9 = std::make_shared<IsoDeadBody>(var7, true);
         VirtualZombieManager.instance.createEatingZombies(var9, var4);
      }
   }

   public std::vector<IsoZombie> addZombiesInOutfitArea(int var1, int var2, int var3, int var4, int var5, int var6, std::string var7, int var8) {
    std::vector var9 = new std::vector();

      for (int var10 = 0; var10 < var6; var10++) {
         var9.addAll(addZombiesInOutfit(Rand.Next(var1, var3), Rand.Next(var2, var4), var5, 1, var7, var8));
      }

    return var9;
   }

   public static std::vector<IsoZombie> addZombiesInOutfit(int var0, int var1, int var2, int var3, std::string var4, int var5) {
    return addZombiesInOutfit();
   }

   public static std::vector<IsoZombie> addZombiesInOutfit(
      int var0, int var1, int var2, int var3, std::string var4, int var5, boolean var6, boolean var7, boolean var8, boolean var9, float var10
   ) {
    std::vector var11 = new std::vector();
      if (IsoWorld.getZombiesDisabled()) {
    return var11;
      } else {
    IsoGridSquare var12 = IsoCell.getInstance().getGridSquare(var0, var1, var2);
         if (var12 == nullptr) {
    return var11;
         } else {
            for (int var13 = 0; var13 < var3; var13++) {
               if (var10 <= 0.0F) {
                  var12.getChunk().AddCorpses(var0 / 10, var1 / 10);
               } else {
                  VirtualZombieManager.instance.choices.clear();
                  VirtualZombieManager.instance.choices.push_back(var12);
    IsoZombie var14 = VirtualZombieManager.instance.createRealZombieAlways(IsoDirections.getRandom().index(), false);
                  if (var14 != nullptr) {
                     if (var5 != nullptr) {
                        var14.setFemaleEtc(Rand.Next(100) < var5);
                     }

                     if (var4 != nullptr) {
                        var14.dressInPersistentOutfit(var4);
                        var14.bDressInRandomOutfit = false;
                     } else {
                        var14.bDressInRandomOutfit = true;
                     }

                     var14.bLunger = true;
                     var14.setKnockedDown(var9);
                     if (var6) {
                        var14.setCrawler(true);
                        var14.setCanWalk(false);
                        var14.setOnFloor(true);
                        var14.setKnockedDown(true);
                        var14.setCrawlerType(1);
                        var14.DoZombieStats();
                     }

                     var14.setFakeDead(var8);
                     var14.setFallOnFront(var7);
                     var14.setHealth(var10);
                     var11.push_back(var14);
                  }
               }
            }

            ZombieSpawnRecorder.instance.record(var11, LuaManager$GlobalObject.class.getSimpleName());
    return var11;
         }
      }
   }

   public std::vector<IsoZombie> addZombiesInBuilding(BuildingDef var1, int var2, std::string var3, RoomDef var4, int var5) {
    bool var6 = var4 == nullptr;
    std::vector var7 = new std::vector();
      if (IsoWorld.getZombiesDisabled()) {
    return var7;
      } else {
         if (var4 == nullptr) {
            var4 = var1.getRandomRoom(6);
         }

    int var8 = 2;
    int var9 = var4.area / 2;
         if (var2 == 0) {
            if (SandboxOptions.instance.Zombies.getValue() == 1) {
               var9 += 4;
            } else if (SandboxOptions.instance.Zombies.getValue() == 2) {
               var9 += 3;
            } else if (SandboxOptions.instance.Zombies.getValue() == 3) {
               var9 += 2;
            } else if (SandboxOptions.instance.Zombies.getValue() == 5) {
               var9 -= 4;
            }

            if (var9 > 8) {
               var9 = 8;
            }

            if (var9 < var8) {
               var9 = var8 + 1;
            }
         } else {
            var8 = var2;
            var9 = var2;
         }

    int var10 = Rand.Next(var8, var9);

         for (int var11 = 0; var11 < var10; var11++) {
    IsoGridSquare var12 = RandomizedBuildingBase.getRandomSpawnSquare(var4);
            if (var12 == nullptr) {
               break;
            }

            VirtualZombieManager.instance.choices.clear();
            VirtualZombieManager.instance.choices.push_back(var12);
    IsoZombie var13 = VirtualZombieManager.instance.createRealZombieAlways(IsoDirections.getRandom().index(), false);
            if (var13 != nullptr) {
               if (var5 != nullptr) {
                  var13.setFemaleEtc(Rand.Next(100) < var5);
               }

               if (var3 != nullptr) {
                  var13.dressInPersistentOutfit(var3);
                  var13.bDressInRandomOutfit = false;
               } else {
                  var13.bDressInRandomOutfit = true;
               }

               var7.push_back(var13);
               if (var6) {
                  var4 = var1.getRandomRoom(6);
               }
            }
         }

         ZombieSpawnRecorder.instance.record(var7, this.getClass().getSimpleName());
    return var7;
      }
   }

    static BaseVehicle addVehicleDebug(const std::string& var0, IsoDirections var1, int var2, IsoGridSquare var3) {
      if (var1 == nullptr) {
         var1 = IsoDirections.getRandom();
      }

    BaseVehicle var4 = std::make_shared<BaseVehicle>(IsoWorld.instance.CurrentCell);
      if (!StringUtils.isNullOrEmpty(var0)) {
         var4.setScriptName(var0);
         var4.setScript();
         if (var2 != nullptr) {
            var4.setSkinIndex(var2);
         }
      }

      var4.setDir(var1);
    float var5 = var1.toAngle() + (float) Math.PI + Rand.Next(-0.2F, 0.2F);

      while (var5 > Math.PI * 2) {
         var5 = (float)(var5 - (Math.PI * 2));
      }

      var4.savedRot.setAngleAxis(var5, 0.0F, 1.0F, 0.0F);
      var4.jniTransform.setRotation(var4.savedRot);
      var4.setX(var3.x);
      var4.setY(var3.y);
      var4.setZ(var3.z);
      if (IsoChunk.doSpawnedVehiclesInInvalidPosition(var4)) {
         var4.setSquare(var3);
         var3.chunk.vehicles.push_back(var4);
         var4.chunk = var3.chunk;
         var4.addToWorld();
         VehiclesDB2.instance.addVehicle(var4);
      }

      var4.setGeneralPartCondition(1.3F, 10.0F);
      var4.rust = 0.0F;
    return var4;
   }

    static BaseVehicle addVehicle(const std::string& var0) {
      if (!StringUtils.isNullOrWhitespace(var0) && ScriptManager.instance.getVehicle(var0) == nullptr) {
         DebugLog.Lua.warn("No such vehicle script \"" + var0 + "\"");
    return nullptr;
      } else {
    std::vector var1 = ScriptManager.instance.getAllVehicleScripts();
         if (var1.empty()) {
            DebugLog.Lua.warn("No vehicle scripts defined");
    return nullptr;
         } else {
            WorldSimulation.instance.create();
    BaseVehicle var2 = std::make_shared<BaseVehicle>(IsoWorld.instance.CurrentCell);
            if (StringUtils.isNullOrWhitespace(var0)) {
    VehicleScript var3 = (VehicleScript)PZArrayUtil.pickRandom(var1);
               var0 = var3.getFullName();
            }

            var2.setScriptName(var0);
            var2.setX(IsoPlayer.getInstance().getX());
            var2.setY(IsoPlayer.getInstance().getY());
            var2.setZ(0.0F);
            if (IsoChunk.doSpawnedVehiclesInInvalidPosition(var2)) {
               var2.setSquare(IsoPlayer.getInstance().getSquare());
               var2.square.chunk.vehicles.push_back(var2);
               var2.chunk = var2.square.chunk;
               var2.addToWorld();
               VehiclesDB2.instance.addVehicle(var2);
            } else {
               DebugLog.Lua.error("ERROR: I can not spawn the vehicle. Invalid position. Try to change position.");
            }

    return nullptr;
         }
      }
   }

    static void attachTrailerToPlayerVehicle(int var0) {
    IsoPlayer var1 = IsoPlayer.players[var0];
    IsoGridSquare var2 = var1.getCurrentSquare();
    BaseVehicle var3 = var1.getVehicle();
      if (var3 == nullptr) {
         var3 = addVehicleDebug("Base.OffRoad", IsoDirections.N, 0, var2);
         var3.repair();
         var1.getInventory().AddItem(var3.createVehicleKey());
      }

      var2 = IsoWorld.instance.CurrentCell.getGridSquare(var2.x, var2.y + 5, var2.z);
    BaseVehicle var4 = addVehicleDebug("Base.Trailer", IsoDirections.N, 0, var2);
      var4.repair();
      var3.addPointConstraint(var1, var4, "trailer", "trailer");
   }

    static std::string getKeyName(int var0) {
      return Input.getKeyName(var0);
   }

    static int getKeyCode(const std::string& var0) {
      return Input.getKeyCode(var0);
   }

    static void queueCharEvent(const std::string& var0) {
      RenderThread.queueInvokeOnRenderContext(() -> GameKeyboard.getEventQueuePolling().addCharEvent(var0.charAt(0)));
   }

    static void queueKeyEvent(int var0) {
      RenderThread.queueInvokeOnRenderContext(() -> {
    int var1 = KeyCodes.toGlfwKey(var0);
         GameKeyboard.getEventQueuePolling().addKeyEvent(var1, 1);
         GameKeyboard.getEventQueuePolling().addKeyEvent(var1, 0);
      });
   }

    static void addAllVehicles() {
      addAllVehicles(var0 -> !var0.getName().contains("Smashed") && !var0.getName().contains("Burnt"));
   }

    static void addAllBurntVehicles() {
      addAllVehicles(var0 -> var0.getName().contains("Burnt"));
   }

    static void addAllSmashedVehicles() {
      addAllVehicles(var0 -> var0.getName().contains("Smashed"));
   }

    static void addAllVehicles(Predicate<VehicleScript> var0) {
    std::vector var1 = ScriptManager.instance.getAllVehicleScripts();
      Collections.sort(var1, Comparator.comparing(VehicleScript::getName));
    float var2 = IsoWorld.instance.CurrentCell.ChunkMap[0].getWorldXMinTiles() + 5;
    float var3 = IsoPlayer.getInstance().getY();
    float var4 = 0.0F;

      for (int var5 = 0; var5 < var1.size(); var5++) {
    VehicleScript var6 = (VehicleScript)var1.get(var5);
         if (var6.getModel() != nullptr && var0.test(var6) && IsoWorld.instance.CurrentCell.getGridSquare(var2, var3, var4) != nullptr) {
            WorldSimulation.instance.create();
    BaseVehicle var7 = std::make_shared<BaseVehicle>(IsoWorld.instance.CurrentCell);
            var7.setScriptName(var6.getFullName());
            var7.setX(var2);
            var7.setY(var3);
            var7.setZ(var4);
            if (IsoChunk.doSpawnedVehiclesInInvalidPosition(var7)) {
               var7.setSquare(IsoPlayer.getInstance().getSquare());
               var7.square.chunk.vehicles.push_back(var7);
               var7.chunk = var7.square.chunk;
               var7.addToWorld();
               VehiclesDB2.instance.addVehicle(var7);
               IsoChunk.addFromCheckedVehicles(var7);
            } else {
               DebugLog.Lua.warn(var6.getName() + " not spawned, position invalid");
            }

            var2 += 4.0F;
            if (var2 > IsoWorld.instance.CurrentCell.ChunkMap[0].getWorldXMaxTiles() - 5) {
               var2 = IsoWorld.instance.CurrentCell.ChunkMap[0].getWorldXMinTiles() + 5;
               var3 += 8.0F;
            }
         }
      }
   }

    static BaseVehicle addPhysicsObject() {
      MPStatistic.getInstance().Bullet.Start();
    int var0 = Bullet.addPhysicsObject(getPlayer().getX(), getPlayer().getY());
      MPStatistic.getInstance().Bullet.End();
      IsoPushableObject var1 = std::make_shared<IsoPushableObject>(
         IsoWorld.instance.getCell(), IsoPlayer.getInstance().getCurrentSquare(), IsoSpriteManager.instance.getSprite("trashcontainers_01_16")
      );
      WorldSimulation.instance.physicsObjectMap.put(var0, var1);
    return nullptr;
   }

    static void toggleVehicleRenderToTexture() {
      BaseVehicle.RENDER_TO_TEXTURE = !BaseVehicle.RENDER_TO_TEXTURE;
   }

    static void reloadSoundFiles() {
      try {
         for (std::string var1 : ZomboidFileSystem.instance.ActiveFileMap.keySet()) {
            if (var1.matches(".*/sounds_.+\\.txt")) {
               GameSounds.ReloadFile(var1);
            }
         }
      } catch (Throwable var2) {
         ExceptionLogger.logException(var2);
      }
   }

    static AnimationViewerState getAnimationViewerState() {
      return AnimationViewerState.instance;
   }

    static AttachmentEditorState getAttachmentEditorState() {
      return AttachmentEditorState.instance;
   }

    static EditVehicleState getEditVehicleState() {
      return EditVehicleState.instance;
   }

    static void showAnimationViewer() {
      IngameState.instance.showAnimationViewer = true;
   }

    static void showAttachmentEditor() {
      IngameState.instance.showAttachmentEditor = true;
   }

    static void showChunkDebugger() {
      IngameState.instance.showChunkDebugger = true;
   }

    static void showGlobalObjectDebugger() {
      IngameState.instance.showGlobalObjectDebugger = true;
   }

    static void showVehicleEditor(const std::string& var0) {
      IngameState.instance.showVehicleEditor = StringUtils.isNullOrWhitespace(var0) ? "" : var0;
   }

    static void showWorldMapEditor(const std::string& var0) {
      IngameState.instance.showWorldMapEditor = StringUtils.isNullOrWhitespace(var0) ? "" : var0;
   }

    static void reloadVehicles() {
      try {
         for (std::string var1 : ScriptManager.instance.scriptsWithVehicleTemplates) {
            ScriptManager.instance.LoadFile(var1, true);
         }

         for (std::string var5 : ScriptManager.instance.scriptsWithVehicles) {
            ScriptManager.instance.LoadFile(var5, true);
         }

         BaseVehicle.LoadAllVehicleTextures();

         for (BaseVehicle var6 : IsoWorld.instance.CurrentCell.vehicles) {
            var6.scriptReloaded();
         }
      } catch (Exception var2) {
         var2.printStackTrace();
      }
   }

    static void reloadEngineRPM() {
      try {
         ScriptManager.instance.LoadFile(ZomboidFileSystem.instance.getString("media/scripts/vehicles/engine_rpm.txt"), true);
      } catch (Exception var1) {
         var1.printStackTrace();
      }
   }

    static std::string proceedPM(const std::string& var0) {
      var0 = var0.trim();
    std::string var1 = nullptr;
    void* var2 = nullptr;
    Matcher var3 = Pattern.compile("(\"[^\"]*\\s+[^\"]*\"|[^\"]\\S*)\\s(.+)").matcher(var0);
      if (var3.matches()) {
         var1 = var3.group(1);
         var2 = var3.group(2);
         var1 = var1.replaceAll("\"", "");
         ChatManager.getInstance().sendWhisperMessage(var1, (std::string)var2);
    return var1;
      } else {
         ChatManager.getInstance().addMessage("Error", getText("IGUI_Commands_Whisper"));
         return "";
      }
   }

    static void processSayMessage(const std::string& var0) {
      if (var0 != nullptr && !var0.empty()) {
         var0 = var0.trim();
         ChatManager.getInstance().sendMessageToChat(ChatType.say, var0);
      }
   }

    static void processGeneralMessage(const std::string& var0) {
      if (var0 != nullptr && !var0.empty()) {
         var0 = var0.trim();
         ChatManager.getInstance().sendMessageToChat(ChatType.general, var0);
      }
   }

    static void processShoutMessage(const std::string& var0) {
      if (var0 != nullptr && !var0.empty()) {
         var0 = var0.trim();
         ChatManager.getInstance().sendMessageToChat(ChatType.shout, var0);
      }
   }

    static void ProceedFactionMessage(const std::string& var0) {
      if (var0 != nullptr && !var0.empty()) {
         var0 = var0.trim();
         ChatManager.getInstance().sendMessageToChat(ChatType.faction, var0);
      }
   }

    static void ProcessSafehouseMessage(const std::string& var0) {
      if (var0 != nullptr && !var0.empty()) {
         var0 = var0.trim();
         ChatManager.getInstance().sendMessageToChat(ChatType.safehouse, var0);
      }
   }

    static void ProcessAdminChatMessage(const std::string& var0) {
      if (var0 != nullptr && !var0.empty()) {
         var0 = var0.trim();
         ChatManager.getInstance().sendMessageToChat(ChatType.admin, var0);
      }
   }

    static void showWrongChatTabMessage(int var0, int var1, const std::string& var2) {
    std::string var3 = ChatManager.getInstance().getTabName((short)var0);
    std::string var4 = ChatManager.getInstance().getTabName((short)var1);
    std::string var5 = Translator.getText("UI_chat_wrong_tab", var3, var4, var2);
      ChatManager.getInstance().showServerChatMessage(var5);
   }

    static void focusOnTab(short var0) {
      ChatManager.getInstance().focusOnTab(var0);
   }

    static void updateChatSettings(const std::string& var0, bool var1, bool var2) {
      ChatManager.getInstance().updateChatSettings(var0, var1, var2);
   }

    static bool checkPlayerCanUseChat(const std::string& var0) {
      var0 = var0.trim();
    ChatType var1;
      switch (var0) {
         case "/all":
            var1 = ChatType.general;
            break;
         case "/a":
         case "/admin":
            var1 = ChatType.admin;
            break;
         case "/s":
         case "/say":
            var1 = ChatType.say;
            break;
         case "/y":
         case "/yell":
            var1 = ChatType.shout;
            break;
         case "/f":
         case "/faction":
            var1 = ChatType.faction;
            break;
         case "/sh":
         case "/safehouse":
            var1 = ChatType.safehouse;
            break;
         case "/w":
         case "/whisper":
            var1 = ChatType.whisper;
            break;
         case "/radio":
         case "/r":
            var1 = ChatType.radio;
            break;
         default:
            var1 = ChatType.notDefined;
            DebugLog.Lua.warn("Chat command not found");
      }

      return ChatManager.getInstance().isPlayerCanUseChat(var1);
   }

    static void reloadVehicleTextures(const std::string& var0) {
    VehicleScript var1 = ScriptManager.instance.getVehicle(var0);
      if (var1 == nullptr) {
         DebugLog.Lua.warn("no such vehicle script");
      } else {
         for (int var2 = 0; var2 < var1.getSkinCount(); var2++) {
    Skin var3 = var1.getSkin(var2);
            if (var3.texture != nullptr) {
               Texture.reload("media/textures/" + var3.texture + ".png");
            }

            if (var3.textureRust != nullptr) {
               Texture.reload("media/textures/" + var3.textureRust + ".png");
            }

            if (var3.textureMask != nullptr) {
               Texture.reload("media/textures/" + var3.textureMask + ".png");
            }

            if (var3.textureLights != nullptr) {
               Texture.reload("media/textures/" + var3.textureLights + ".png");
            }

            if (var3.textureDamage1Overlay != nullptr) {
               Texture.reload("media/textures/" + var3.textureDamage1Overlay + ".png");
            }

            if (var3.textureDamage1Shell != nullptr) {
               Texture.reload("media/textures/" + var3.textureDamage1Shell + ".png");
            }

            if (var3.textureDamage2Overlay != nullptr) {
               Texture.reload("media/textures/" + var3.textureDamage2Overlay + ".png");
            }

            if (var3.textureDamage2Shell != nullptr) {
               Texture.reload("media/textures/" + var3.textureDamage2Shell + ".png");
            }

            if (var3.textureShadow != nullptr) {
               Texture.reload("media/textures/" + var3.textureShadow + ".png");
            }
         }
      }
   }

    static void useStaticErosionRand(bool var0) {
      ErosionData.staticRand = var0;
   }

    static ClimateManager getClimateManager() {
      return ClimateManager.getInstance();
   }

    static ClimateMoon getClimateMoon() {
      return ClimateMoon.getInstance();
   }

    static WorldMarkers getWorldMarkers() {
      return WorldMarkers.instance;
   }

    static IsoMarkers getIsoMarkers() {
      return IsoMarkers.instance;
   }

    static ErosionMain getErosion() {
      return ErosionMain.getInstance();
   }

   public static std::vector<std::string> getAllOutfits(boolean var0) {
    std::vector var1 = new std::vector();
      ModelManager.instance.create();
      if (OutfitManager.instance == nullptr) {
    return var1;
      } else {
         for (Outfit var4 : var0 ? OutfitManager.instance.m_FemaleOutfits : OutfitManager.instance.m_MaleOutfits) {
            var1.push_back(var4.m_Name);
         }

         Collections.sort(var1);
    return var1;
      }
   }

   public static std::vector<std::string> getAllVehicles() {
      return ScriptManager.instance
         .getAllVehicleScripts()
         .stream()
         .<std::string>map(VehicleScript::getFullName)
         .sorted()
         .collect(Collectors.toCollection(std::vector::new));
   }

   public static std::vector<std::string> getAllHairStyles(boolean var0) {
    std::vector var1 = new std::vector();
      if (HairStyles.instance == nullptr) {
    return var1;
      } else {
    std::vector var2 = new std::vector(var0 ? HairStyles.instance.m_FemaleStyles : HairStyles.instance.m_MaleStyles);
         var2.sort((var0x, var1x) -> {
            if (var0x.name.empty()) {
               return -1;
            } else if (var1x.name.empty()) {
    return 1;
            } else {
    std::string var2x = getText("IGUI_Hair_" + var0x.name);
    std::string var3 = getText("IGUI_Hair_" + var1x.name);
               return var2x.compareTo(var3);
            }
         });

    for (auto& var4 : var2)            var1.push_back(var4.name);
         }

    return var1;
      }
   }

    static HairStyles getHairStylesInstance() {
      return HairStyles.instance;
   }

    static BeardStyles getBeardStylesInstance() {
      return BeardStyles.instance;
   }

   public static std::vector<std::string> getAllBeardStyles() {
    std::vector var0 = new std::vector();
      if (BeardStyles.instance == nullptr) {
    return var0;
      } else {
    std::vector var1 = new std::vector(BeardStyles.instance.m_Styles);
         var1.sort((var0x, var1x) -> {
            if (var0x.name.empty()) {
               return -1;
            } else if (var1x.name.empty()) {
    return 1;
            } else {
    std::string var2 = getText("IGUI_Beard_" + var0x.name);
    std::string var3x = getText("IGUI_Beard_" + var1x.name);
               return var2.compareTo(var3x);
            }
         });

    for (auto& var3 : var1)            var0.push_back(var3.name);
         }

    return var0;
      }
   }

    static KahluaTable getAllItemsForBodyLocation(const std::string& var0) {
    KahluaTable var1 = LuaManager.platform.newTable();
      if (StringUtils.isNullOrWhitespace(var0)) {
    return var1;
      } else {
    int var2 = 1;

         for (Item var5 : ScriptManager.instance.getAllItems()) {
            if (!StringUtils.isNullOrWhitespace(var5.getClothingItem()) && (var0 == var5.getBodyLocation()) || var0 == var5.CanBeEquipped))) {
               var1.rawset(var2++, var5.getFullName());
            }
         }

    return var1;
      }
   }

   public static std::vector<std::string> getAllDecalNamesForItem(InventoryItem var0) {
    std::vector var1 = new std::vector();
      if (var0 != nullptr && ClothingDecals.instance != nullptr) {
    ClothingItem var2 = var0.getClothingItem();
         if (var2 == nullptr) {
    return var1;
         } else {
    std::string var3 = var2.getDecalGroup();
            if (StringUtils.isNullOrWhitespace(var3)) {
    return var1;
            } else {
    ClothingDecalGroup var4 = ClothingDecals.instance.FindGroup(var3);
               if (var4 == nullptr) {
    return var1;
               } else {
                  var4.getDecals(var1);
    return var1;
               }
            }
         }
      } else {
    return var1;
      }
   }

    void screenZoomIn() {
   }

    void screenZoomOut() {
   }

    void addSound(IsoObject var1, int var2, int var3, int var4, int var5, int var6) {
      WorldSoundManager.instance.addSound(var1, var2, var3, var4, var5, var6);
   }

    void sendAddXp(IsoPlayer var1, Perk var2, int var3) {
      if (GameClient.bClient && var1.isExistInTheWorld()) {
         GameClient.instance.sendAddXp(var1, var2, var3);
      }
   }

    void SyncXp(IsoPlayer var1) {
      if (GameClient.bClient) {
         GameClient.instance.sendSyncXp(var1);
      }
   }

    std::string checkServerName(const std::string& var1) {
    std::string var2 = ProfanityFilter.getInstance().validateString(var1, true, true, true);
      return !StringUtils.isNullOrEmpty(var2) ? Translator.getText("UI_BadWordCheck", var2) : nullptr;
   }

    void Render3DItem(InventoryItem var1, IsoGridSquare var2, float var3, float var4, float var5, float var6) {
      WorldItemModelDrawer.renderMain(var1, var2, var3, var4, var5, 0.0F, var6);
   }

    ContainerOverlays getContainerOverlays() {
      return ContainerOverlays.instance;
   }

    TileOverlays getTileOverlays() {
      return TileOverlays.instance;
   }

    double getAverageFSP() {
    float var1 = GameWindow.averageFPS;
      if (!PerformanceSettings.isUncappedFPS()) {
         var1 = Math.min(var1, (float)PerformanceSettings.getLockFPS());
      }

      return BoxedStaticValues.toDouble(Math.floor(var1));
   }

    static void createItemTransaction(InventoryItem var0, ItemContainer var1, ItemContainer var2) {
      if (GameClient.bClient && var0 != nullptr) {
    int var3 = Optional.ofNullable(var1).map(ItemContainer::getContainingItem).<int>map(InventoryItem::getID).orElse(-1);
    int var4 = Optional.ofNullable(var2).map(ItemContainer::getContainingItem).<int>map(InventoryItem::getID).orElse(-1);
         ItemTransactionManager.createItemTransaction(var0.getID(), var3, var4);
      }
   }

    static void removeItemTransaction(InventoryItem var0, ItemContainer var1, ItemContainer var2) {
      if (GameClient.bClient && var0 != nullptr) {
    int var3 = Optional.ofNullable(var1).map(ItemContainer::getContainingItem).<int>map(InventoryItem::getID).orElse(-1);
    int var4 = Optional.ofNullable(var2).map(ItemContainer::getContainingItem).<int>map(InventoryItem::getID).orElse(-1);
         ItemTransactionManager.removeItemTransaction(var0.getID(), var3, var4);
      }
   }

    static bool isItemTransactionConsistent(InventoryItem var0, ItemContainer var1, ItemContainer var2) {
      if (GameClient.bClient && var0 != nullptr) {
    int var3 = Optional.ofNullable(var1).map(ItemContainer::getContainingItem).<int>map(InventoryItem::getID).orElse(-1);
    int var4 = Optional.ofNullable(var2).map(ItemContainer::getContainingItem).<int>map(InventoryItem::getID).orElse(-1);
         return ItemTransactionManager.isConsistent(var0.getID(), var3, var4);
      } else {
    return true;
      }
   }

    static KahluaTable getServerStatistic() {
      return MPStatistic.getInstance().getStatisticTableForLua();
   }

    static void setServerStatisticEnable(bool var0) {
      if (GameClient.bClient) {
         GameClient.setServerStatisticEnable(var0);
      }
   }

    static bool getServerStatisticEnable() {
      return GameClient.bClient ? GameClient.getServerStatisticEnable() : false;
   }

    static void checkModsNeedUpdate(UdpConnection var0) {
      DebugLog.log("CheckModsNeedUpdate: Checking...");
      if (SteamUtils.isSteamModeEnabled() && isServer()) {
    std::vector var1 = getSteamWorkshopItemIDs();
    std::make_shared<ItemQueryJava>();
      }
   }

    static SearchMode getSearchMode() {
      return SearchMode.getInstance();
   }

    static void timSort(KahluaTable var0, void* var1) {
    KahluaTableImpl var2 = (KahluaTableImpl)zombie.util.Type.tryCastTo(var0, KahluaTableImpl.class);
      if (var2 != nullptr && var2.len() >= 2 && var1 != nullptr) {
         timSortComparator.comp = var1;
         Object[] var3 = var2.delegate.values().toArray();
         Arrays.sort(var3, timSortComparator);

         for (int var4 = 0; var4 < var3.length; var4++) {
            var2.rawset(var4 + 1, var3[var4]);
            var3[var4] = nullptr;
         }
      }
   }
}
} // namespace Lua
} // namespace zombie
