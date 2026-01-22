#pragma once
#include <queue>
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/ZomboidFileSystem.h"
#include "zombie/config/ConfigFile.h"
#include "zombie/config/ConfigOption.h"
#include "zombie/core/Core.h"
#include "zombie/core/Rand.h"
#include "zombie/core/Translator.h"
#include "zombie/core/logger/LoggerManager.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/network/ServerOptions/BooleanServerOption.h"
#include "zombie/network/ServerOptions/DoubleServerOption.h"
#include "zombie/network/ServerOptions/IntegerServerOption.h"
#include "zombie/network/ServerOptions/ServerOption.h"
#include "zombie/network/ServerOptions/StringServerOption.h"
#include "zombie/network/ServerOptions/TextServerOption.h"
#include <fstream>
#include <iostream>
#include <iterator>

namespace zombie {
namespace network {


class ServerOptions {
public:
    static const ServerOptions instance = std::make_shared<ServerOptions>();
   private std::vector<std::string> publicOptions = std::make_unique<std::vector<>>();
   public static std::unordered_map<std::string, std::string> clientOptionsList = nullptr;
    static const int MAX_PORT = 65535;
   private std::vector<ServerOption> options = std::make_unique<std::vector<>>();
   private std::unordered_map<std::string, ServerOption> optionByName = std::make_unique<std::unordered_map<>>();
    BooleanServerOption PVP = std::make_shared<BooleanServerOption>(this, "PVP", true);
    BooleanServerOption PauseEmpty = std::make_shared<BooleanServerOption>(this, "PauseEmpty", true);
    BooleanServerOption GlobalChat = std::make_shared<BooleanServerOption>(this, "GlobalChat", true);
    StringServerOption ChatStreams = std::make_shared<StringServerOption>(this, "ChatStreams", "s,r,a,w,y,sh,f,all", -1);
    BooleanServerOption Open = std::make_shared<BooleanServerOption>(this, "Open", true);
   public TextServerOption ServerWelcomeMessage = std::make_shared<TextServerOption>(
      this,
      "ServerWelcomeMessage",
      "Welcome to Project Zomboid Multiplayer! <LINE> <LINE> To interact with the Chat panel: press Tab, T, or Enter. <LINE> <LINE> The Tab key will change the target stream of the message. <LINE> <LINE> Global Streams: /all <LINE> Local Streams: /say, /yell <LINE> Special Steams: /whisper, /safehouse, /faction. <LINE> <LINE> Press the Up arrow to cycle through your message history. Click the Gear icon to customize chat. <LINE> <LINE> Happy surviving!",
      -1
   );
    BooleanServerOption AutoCreateUserInWhiteList = std::make_shared<BooleanServerOption>(this, "AutoCreateUserInWhiteList", false);
    BooleanServerOption DisplayUserName = std::make_shared<BooleanServerOption>(this, "DisplayUserName", true);
    BooleanServerOption ShowFirstAndLastName = std::make_shared<BooleanServerOption>(this, "ShowFirstAndLastName", false);
    StringServerOption SpawnPoint = std::make_shared<StringServerOption>(this, "SpawnPoint", "0,0,0", -1);
    BooleanServerOption SafetySystem = std::make_shared<BooleanServerOption>(this, "SafetySystem", true);
    BooleanServerOption ShowSafety = std::make_shared<BooleanServerOption>(this, "ShowSafety", true);
    IntegerServerOption SafetyToggleTimer = std::make_shared<IntegerServerOption>(this, "SafetyToggleTimer", 0, 1000, 2);
    IntegerServerOption SafetyCooldownTimer = std::make_shared<IntegerServerOption>(this, "SafetyCooldownTimer", 0, 1000, 3);
    StringServerOption SpawnItems = std::make_shared<StringServerOption>(this, "SpawnItems", "", -1);
    IntegerServerOption DefaultPort = std::make_shared<IntegerServerOption>(this, "DefaultPort", 0, 65535, 16261);
    IntegerServerOption UDPPort = std::make_shared<IntegerServerOption>(this, "UDPPort", 0, 65535, 16262);
    IntegerServerOption ResetID = std::make_shared<IntegerServerOption>(this, "ResetID", 0, int.MAX_VALUE, Rand.Next(1000000000));
    StringServerOption Mods = std::make_shared<StringServerOption>(this, "Mods", "", -1);
    StringServerOption Map = std::make_shared<StringServerOption>(this, "Map", "Muldraugh, KY", -1);
    BooleanServerOption DoLuaChecksum = std::make_shared<BooleanServerOption>(this, "DoLuaChecksum", true);
    BooleanServerOption DenyLoginOnOverloadedServer = std::make_shared<BooleanServerOption>(this, "DenyLoginOnOverloadedServer", true);
    BooleanServerOption Public = std::make_shared<BooleanServerOption>(this, "Public", false);
    StringServerOption PublicName = std::make_shared<StringServerOption>(this, "PublicName", "My PZ Server", 64);
    TextServerOption PublicDescription = std::make_shared<TextServerOption>(this, "PublicDescription", "", 256);
    IntegerServerOption MaxPlayers = std::make_shared<IntegerServerOption>(this, "MaxPlayers", 1, 100, 32);
    IntegerServerOption PingLimit = std::make_shared<IntegerServerOption>(this, "PingLimit", 100, int.MAX_VALUE, 400);
    IntegerServerOption HoursForLootRespawn = std::make_shared<IntegerServerOption>(this, "HoursForLootRespawn", 0, int.MAX_VALUE, 0);
    IntegerServerOption MaxItemsForLootRespawn = std::make_shared<IntegerServerOption>(this, "MaxItemsForLootRespawn", 1, int.MAX_VALUE, 4);
    BooleanServerOption ConstructionPreventsLootRespawn = std::make_shared<BooleanServerOption>(this, "ConstructionPreventsLootRespawn", true);
    BooleanServerOption DropOffWhiteListAfterDeath = std::make_shared<BooleanServerOption>(this, "DropOffWhiteListAfterDeath", false);
    BooleanServerOption NoFire = std::make_shared<BooleanServerOption>(this, "NoFire", false);
    BooleanServerOption AnnounceDeath = std::make_shared<BooleanServerOption>(this, "AnnounceDeath", false);
    DoubleServerOption MinutesPerPage = std::make_shared<DoubleServerOption>(this, "MinutesPerPage", 0.0, 60.0, 1.0);
    IntegerServerOption SaveWorldEveryMinutes = std::make_shared<IntegerServerOption>(this, "SaveWorldEveryMinutes", 0, int.MAX_VALUE, 0);
    BooleanServerOption PlayerSafehouse = std::make_shared<BooleanServerOption>(this, "PlayerSafehouse", false);
    BooleanServerOption AdminSafehouse = std::make_shared<BooleanServerOption>(this, "AdminSafehouse", false);
    BooleanServerOption SafehouseAllowTrepass = std::make_shared<BooleanServerOption>(this, "SafehouseAllowTrepass", true);
    BooleanServerOption SafehouseAllowFire = std::make_shared<BooleanServerOption>(this, "SafehouseAllowFire", true);
    BooleanServerOption SafehouseAllowLoot = std::make_shared<BooleanServerOption>(this, "SafehouseAllowLoot", true);
    BooleanServerOption SafehouseAllowRespawn = std::make_shared<BooleanServerOption>(this, "SafehouseAllowRespawn", false);
    IntegerServerOption SafehouseDaySurvivedToClaim = std::make_shared<IntegerServerOption>(this, "SafehouseDaySurvivedToClaim", 0, int.MAX_VALUE, 0);
    IntegerServerOption SafeHouseRemovalTime = std::make_shared<IntegerServerOption>(this, "SafeHouseRemovalTime", 0, int.MAX_VALUE, 144);
    BooleanServerOption SafehouseAllowNonResidential = std::make_shared<BooleanServerOption>(this, "SafehouseAllowNonResidential", false);
    BooleanServerOption AllowDestructionBySledgehammer = std::make_shared<BooleanServerOption>(this, "AllowDestructionBySledgehammer", true);
    BooleanServerOption SledgehammerOnlyInSafehouse = std::make_shared<BooleanServerOption>(this, "SledgehammerOnlyInSafehouse", false);
    BooleanServerOption KickFastPlayers = std::make_shared<BooleanServerOption>(this, "KickFastPlayers", false);
    StringServerOption ServerPlayerID = std::make_shared<StringServerOption>(this, "ServerPlayerID", int.toString(Rand.Next(int.MAX_VALUE)), -1);
    IntegerServerOption RCONPort = std::make_shared<IntegerServerOption>(this, "RCONPort", 0, 65535, 27015);
    StringServerOption RCONPassword = std::make_shared<StringServerOption>(this, "RCONPassword", "", -1);
    BooleanServerOption DiscordEnable = std::make_shared<BooleanServerOption>(this, "DiscordEnable", false);
    StringServerOption DiscordToken = std::make_shared<StringServerOption>(this, "DiscordToken", "", -1);
    StringServerOption DiscordChannel = std::make_shared<StringServerOption>(this, "DiscordChannel", "", -1);
    StringServerOption DiscordChannelID = std::make_shared<StringServerOption>(this, "DiscordChannelID", "", -1);
    StringServerOption Password = std::make_shared<StringServerOption>(this, "Password", "", -1);
    IntegerServerOption MaxAccountsPerUser = std::make_shared<IntegerServerOption>(this, "MaxAccountsPerUser", 0, int.MAX_VALUE, 0);
    BooleanServerOption AllowCoop = std::make_shared<BooleanServerOption>(this, "AllowCoop", true);
    BooleanServerOption SleepAllowed = std::make_shared<BooleanServerOption>(this, "SleepAllowed", false);
    BooleanServerOption SleepNeeded = std::make_shared<BooleanServerOption>(this, "SleepNeeded", false);
    BooleanServerOption KnockedDownAllowed = std::make_shared<BooleanServerOption>(this, "KnockedDownAllowed", true);
    BooleanServerOption SneakModeHideFromOtherPlayers = std::make_shared<BooleanServerOption>(this, "SneakModeHideFromOtherPlayers", true);
    StringServerOption WorkshopItems = std::make_shared<StringServerOption>(this, "WorkshopItems", "", -1);
    StringServerOption SteamScoreboard = std::make_shared<StringServerOption>(this, "SteamScoreboard", "true", -1);
    BooleanServerOption SteamVAC = std::make_shared<BooleanServerOption>(this, "SteamVAC", true);
    BooleanServerOption UPnP = std::make_shared<BooleanServerOption>(this, "UPnP", true);
    BooleanServerOption VoiceEnable = std::make_shared<BooleanServerOption>(this, "VoiceEnable", true);
    DoubleServerOption VoiceMinDistance = std::make_shared<DoubleServerOption>(this, "VoiceMinDistance", 0.0, 100000.0, 10.0);
    DoubleServerOption VoiceMaxDistance = std::make_shared<DoubleServerOption>(this, "VoiceMaxDistance", 0.0, 100000.0, 100.0);
    BooleanServerOption Voice3D = std::make_shared<BooleanServerOption>(this, "Voice3D", true);
    DoubleServerOption SpeedLimit = std::make_shared<DoubleServerOption>(this, "SpeedLimit", 10.0, 150.0, 70.0);
    BooleanServerOption LoginQueueEnabled = std::make_shared<BooleanServerOption>(this, "LoginQueueEnabled", false);
    IntegerServerOption LoginQueueConnectTimeout = std::make_shared<IntegerServerOption>(this, "LoginQueueConnectTimeout", 20, 1200, 60);
    StringServerOption server_browser_announced_ip = std::make_shared<StringServerOption>(this, "server_browser_announced_ip", "", -1);
    BooleanServerOption PlayerRespawnWithSelf = std::make_shared<BooleanServerOption>(this, "PlayerRespawnWithSelf", false);
    BooleanServerOption PlayerRespawnWithOther = std::make_shared<BooleanServerOption>(this, "PlayerRespawnWithOther", false);
    DoubleServerOption FastForwardMultiplier = std::make_shared<DoubleServerOption>(this, "FastForwardMultiplier", 1.0, 100.0, 40.0);
    BooleanServerOption DisableSafehouseWhenPlayerConnected = std::make_shared<BooleanServerOption>(this, "DisableSafehouseWhenPlayerConnected", false);
    BooleanServerOption Faction = std::make_shared<BooleanServerOption>(this, "Faction", true);
    IntegerServerOption FactionDaySurvivedToCreate = std::make_shared<IntegerServerOption>(this, "FactionDaySurvivedToCreate", 0, int.MAX_VALUE, 0);
    IntegerServerOption FactionPlayersRequiredForTag = std::make_shared<IntegerServerOption>(this, "FactionPlayersRequiredForTag", 1, int.MAX_VALUE, 1);
    BooleanServerOption DisableRadioStaff = std::make_shared<BooleanServerOption>(this, "DisableRadioStaff", false);
    BooleanServerOption DisableRadioAdmin = std::make_shared<BooleanServerOption>(this, "DisableRadioAdmin", true);
    BooleanServerOption DisableRadioGM = std::make_shared<BooleanServerOption>(this, "DisableRadioGM", true);
    BooleanServerOption DisableRadioOverseer = std::make_shared<BooleanServerOption>(this, "DisableRadioOverseer", false);
    BooleanServerOption DisableRadioModerator = std::make_shared<BooleanServerOption>(this, "DisableRadioModerator", false);
    BooleanServerOption DisableRadioInvisible = std::make_shared<BooleanServerOption>(this, "DisableRadioInvisible", true);
   public StringServerOption ClientCommandFilter = std::make_shared<StringServerOption>(
      this, "ClientCommandFilter", "-vehicle.*;+vehicle.damageWindow;+vehicle.fixPart;+vehicle.installPart;+vehicle.uninstallPart", -1
   );
    StringServerOption ClientActionLogs = std::make_shared<StringServerOption>(this, "ClientActionLogs", "ISEnterVehicle;
    BooleanServerOption PerkLogs = std::make_shared<BooleanServerOption>(this, "PerkLogs", true);
    IntegerServerOption ItemNumbersLimitPerContainer = std::make_shared<IntegerServerOption>(this, "ItemNumbersLimitPerContainer", 0, 9000, 0);
    IntegerServerOption BloodSplatLifespanDays = std::make_shared<IntegerServerOption>(this, "BloodSplatLifespanDays", 0, 365, 0);
    BooleanServerOption AllowNonAsciiUsername = std::make_shared<BooleanServerOption>(this, "AllowNonAsciiUsername", false);
    BooleanServerOption BanKickGlobalSound = std::make_shared<BooleanServerOption>(this, "BanKickGlobalSound", true);
    BooleanServerOption RemovePlayerCorpsesOnCorpseRemoval = std::make_shared<BooleanServerOption>(this, "RemovePlayerCorpsesOnCorpseRemoval", false);
    BooleanServerOption TrashDeleteAll = std::make_shared<BooleanServerOption>(this, "TrashDeleteAll", false);
    BooleanServerOption PVPMeleeWhileHitReaction = std::make_shared<BooleanServerOption>(this, "PVPMeleeWhileHitReaction", false);
    BooleanServerOption MouseOverToSeeDisplayName = std::make_shared<BooleanServerOption>(this, "MouseOverToSeeDisplayName", true);
    BooleanServerOption HidePlayersBehindYou = std::make_shared<BooleanServerOption>(this, "HidePlayersBehindYou", true);
    DoubleServerOption PVPMeleeDamageModifier = std::make_shared<DoubleServerOption>(this, "PVPMeleeDamageModifier", 0.0, 500.0, 30.0);
    DoubleServerOption PVPFirearmDamageModifier = std::make_shared<DoubleServerOption>(this, "PVPFirearmDamageModifier", 0.0, 500.0, 50.0);
    DoubleServerOption CarEngineAttractionModifier = std::make_shared<DoubleServerOption>(this, "CarEngineAttractionModifier", 0.0, 10.0, 0.5);
    BooleanServerOption PlayerBumpPlayer = std::make_shared<BooleanServerOption>(this, "PlayerBumpPlayer", false);
    IntegerServerOption MapRemotePlayerVisibility = std::make_shared<IntegerServerOption>(this, "MapRemotePlayerVisibility", 1, 3, 1);
    IntegerServerOption BackupsCount = std::make_shared<IntegerServerOption>(this, "BackupsCount", 1, 300, 5);
    BooleanServerOption BackupsOnStart = std::make_shared<BooleanServerOption>(this, "BackupsOnStart", true);
    BooleanServerOption BackupsOnVersionChange = std::make_shared<BooleanServerOption>(this, "BackupsOnVersionChange", true);
    IntegerServerOption BackupsPeriod = std::make_shared<IntegerServerOption>(this, "BackupsPeriod", 0, 1500, 0);
    BooleanServerOption AntiCheatProtectionType1 = std::make_shared<BooleanServerOption>(this, "AntiCheatProtectionType1", true);
    BooleanServerOption AntiCheatProtectionType2 = std::make_shared<BooleanServerOption>(this, "AntiCheatProtectionType2", true);
    BooleanServerOption AntiCheatProtectionType3 = std::make_shared<BooleanServerOption>(this, "AntiCheatProtectionType3", true);
    BooleanServerOption AntiCheatProtectionType4 = std::make_shared<BooleanServerOption>(this, "AntiCheatProtectionType4", true);
    BooleanServerOption AntiCheatProtectionType5 = std::make_shared<BooleanServerOption>(this, "AntiCheatProtectionType5", true);
    BooleanServerOption AntiCheatProtectionType6 = std::make_shared<BooleanServerOption>(this, "AntiCheatProtectionType6", true);
    BooleanServerOption AntiCheatProtectionType7 = std::make_shared<BooleanServerOption>(this, "AntiCheatProtectionType7", true);
    BooleanServerOption AntiCheatProtectionType8 = std::make_shared<BooleanServerOption>(this, "AntiCheatProtectionType8", true);
    BooleanServerOption AntiCheatProtectionType9 = std::make_shared<BooleanServerOption>(this, "AntiCheatProtectionType9", true);
    BooleanServerOption AntiCheatProtectionType10 = std::make_shared<BooleanServerOption>(this, "AntiCheatProtectionType10", true);
    BooleanServerOption AntiCheatProtectionType11 = std::make_shared<BooleanServerOption>(this, "AntiCheatProtectionType11", true);
    BooleanServerOption AntiCheatProtectionType12 = std::make_shared<BooleanServerOption>(this, "AntiCheatProtectionType12", true);
    BooleanServerOption AntiCheatProtectionType13 = std::make_shared<BooleanServerOption>(this, "AntiCheatProtectionType13", true);
    BooleanServerOption AntiCheatProtectionType14 = std::make_shared<BooleanServerOption>(this, "AntiCheatProtectionType14", true);
    BooleanServerOption AntiCheatProtectionType15 = std::make_shared<BooleanServerOption>(this, "AntiCheatProtectionType15", true);
    BooleanServerOption AntiCheatProtectionType16 = std::make_shared<BooleanServerOption>(this, "AntiCheatProtectionType16", true);
    BooleanServerOption AntiCheatProtectionType17 = std::make_shared<BooleanServerOption>(this, "AntiCheatProtectionType17", true);
    BooleanServerOption AntiCheatProtectionType18 = std::make_shared<BooleanServerOption>(this, "AntiCheatProtectionType18", true);
    BooleanServerOption AntiCheatProtectionType19 = std::make_shared<BooleanServerOption>(this, "AntiCheatProtectionType19", true);
    BooleanServerOption AntiCheatProtectionType20 = std::make_shared<BooleanServerOption>(this, "AntiCheatProtectionType20", true);
    BooleanServerOption AntiCheatProtectionType21 = std::make_shared<BooleanServerOption>(this, "AntiCheatProtectionType21", true);
    BooleanServerOption AntiCheatProtectionType22 = std::make_shared<BooleanServerOption>(this, "AntiCheatProtectionType22", true);
    BooleanServerOption AntiCheatProtectionType23 = std::make_shared<BooleanServerOption>(this, "AntiCheatProtectionType23", true);
    BooleanServerOption AntiCheatProtectionType24 = std::make_shared<BooleanServerOption>(this, "AntiCheatProtectionType24", true);
   public DoubleServerOption AntiCheatProtectionType2ThresholdMultiplier = std::make_shared<DoubleServerOption>(
      this, "AntiCheatProtectionType2ThresholdMultiplier", 1.0, 10.0, 3.0
   );
   public DoubleServerOption AntiCheatProtectionType3ThresholdMultiplier = std::make_shared<DoubleServerOption>(
      this, "AntiCheatProtectionType3ThresholdMultiplier", 1.0, 10.0, 1.0
   );
   public DoubleServerOption AntiCheatProtectionType4ThresholdMultiplier = std::make_shared<DoubleServerOption>(
      this, "AntiCheatProtectionType4ThresholdMultiplier", 1.0, 10.0, 1.0
   );
   public DoubleServerOption AntiCheatProtectionType9ThresholdMultiplier = std::make_shared<DoubleServerOption>(
      this, "AntiCheatProtectionType9ThresholdMultiplier", 1.0, 10.0, 1.0
   );
   public DoubleServerOption AntiCheatProtectionType15ThresholdMultiplier = std::make_shared<DoubleServerOption>(
      this, "AntiCheatProtectionType15ThresholdMultiplier", 1.0, 10.0, 1.0
   );
   public DoubleServerOption AntiCheatProtectionType20ThresholdMultiplier = std::make_shared<DoubleServerOption>(
      this, "AntiCheatProtectionType20ThresholdMultiplier", 1.0, 10.0, 1.0
   );
   public DoubleServerOption AntiCheatProtectionType22ThresholdMultiplier = std::make_shared<DoubleServerOption>(
      this, "AntiCheatProtectionType22ThresholdMultiplier", 1.0, 10.0, 1.0
   );
   public DoubleServerOption AntiCheatProtectionType24ThresholdMultiplier = std::make_shared<DoubleServerOption>(
      this, "AntiCheatProtectionType24ThresholdMultiplier", 1.0, 10.0, 6.0
   );
   public static std::vector<std::string> cardList = nullptr;

    public ServerOptions() {
      this.publicOptions.clear();
      this.publicOptions.addAll(this.optionByName.keySet());
      this.publicOptions.remove("Password");
      this.publicOptions.remove("RCONPort");
      this.publicOptions.remove("RCONPassword");
      this.publicOptions.remove(this.DiscordToken.getName());
      this.publicOptions.remove(this.DiscordChannel.getName());
      this.publicOptions.remove(this.DiscordChannelID.getName());
      Collections.sort(this.publicOptions);
   }

    void initOptions() {
      initClientCommandsHelp();

      for (ServerOption var2 : this.options) {
         var2.asConfigOption().resetToDefault();
      }
   }

   public std::vector<std::string> getPublicOptions() {
      return this.publicOptions;
   }

   public std::vector<ServerOption> getOptions() {
      return this.options;
   }

    static void initClientCommandsHelp() {
      clientOptionsList = std::make_unique<std::unordered_map<>>();
      clientOptionsList.put("help", Translator.getText("UI_ServerOptionDesc_Help"));
      clientOptionsList.put("changepwd", Translator.getText("UI_ServerOptionDesc_ChangePwd"));
      clientOptionsList.put("roll", Translator.getText("UI_ServerOptionDesc_Roll"));
      clientOptionsList.put("card", Translator.getText("UI_ServerOptionDesc_Card"));
      clientOptionsList.put("safehouse", Translator.getText("UI_ServerOptionDesc_SafeHouse"));
   }

    void init() {
      this.initOptions();
    File var1 = std::make_shared<File>(ZomboidFileSystem.instance.getCacheDir() + File.separator + "Server");
      if (!var1.exists()) {
         var1.mkdirs();
      }

    File var2 = std::make_shared<File>(ZomboidFileSystem.instance.getCacheDir() + File.separator + "Server" + File.separator + GameServer.ServerName + ".ini");
      if (var2.exists()) {
         try {
            Core.getInstance().loadOptions();
         } catch (IOException var4) {
            var4.printStackTrace();
         }

         if (this.loadServerTextFile(GameServer.ServerName)) {
            this.saveServerTextFile(GameServer.ServerName);
         }
      } else {
         this.initSpawnRegionsFile(
    std::make_shared<File>();
         );
         this.saveServerTextFile(GameServer.ServerName);
      }

      LoggerManager.init();
   }

    void resetRegionFile() {
    File var1 = std::make_shared<File>(ZomboidFileSystem.instance.getCacheDir() + File.separator + "Server" + File.separator + GameServer.ServerName + "_spawnregions.lua");
      var1.delete();
      this.initSpawnRegionsFile(var1);
   }

    void initSpawnRegionsFile(File var1) {
      if (!var1.exists()) {
         DebugLog.log("creating server spawnregions file \"" + var1.getPath() + "\"");

         try {
            var1.createNewFile();
    FileWriter var2 = std::make_shared<FileWriter>(var1);
            var2.write("function SpawnRegions()" + System.lineSeparator());
            var2.write("\treturn {" + System.lineSeparator());
            var2.write("\t\t{ name = \"Muldraugh, KY\", file = \"media/maps/Muldraugh, KY/spawnpoints.lua\" }," + System.lineSeparator());
            var2.write("\t\t{ name = \"West Point, KY\", file = \"media/maps/West Point, KY/spawnpoints.lua\" }," + System.lineSeparator());
            var2.write("\t\t{ name = \"Rosewood, KY\", file = \"media/maps/Rosewood, KY/spawnpoints.lua\" }," + System.lineSeparator());
            var2.write("\t\t{ name = \"Riverside, KY\", file = \"media/maps/Riverside, KY/spawnpoints.lua\" }," + System.lineSeparator());
            var2.write("\t\t-- Uncomment the line below to add a custom spawnpoint for this server." + System.lineSeparator());
            var2.write("--\t\t{ name = \"Twiggy's Bar\", serverfile = \"" + GameServer.ServerName + "_spawnpoints.lua\" }," + System.lineSeparator());
            var2.write("\t}" + System.lineSeparator());
            var2.write("end" + System.lineSeparator());
            var2.close();
            var2 = std::make_shared<FileWriter>(var1.getParent() + File.separator + GameServer.ServerName + "_spawnpoints.lua");
            var2.write("function SpawnPoints()" + System.lineSeparator());
            var2.write("\treturn {" + System.lineSeparator());
            var2.write("\t\tunemployed = {" + System.lineSeparator());
            var2.write("\t\t\t{ worldX = 40, worldY = 22, posX = 67, posY = 201 }" + System.lineSeparator());
            var2.write("\t\t}" + System.lineSeparator());
            var2.write("\t}" + System.lineSeparator());
            var2.write("end" + System.lineSeparator());
            var2.close();
         } catch (Exception var3) {
            var3.printStackTrace();
         }
      }
   }

    std::string getOption(const std::string& var1) {
    ServerOption var2 = this.getOptionByName(var1);
    return var2 = = nullptr ? nullptr : var2.asConfigOption().getValueAsString();
   }

    bool getBoolean(const std::string& var1) {
    ServerOption var2 = this.getOptionByName(var1);
      return dynamic_cast<BooleanServerOption*>(var2) != nullptr ? (bool)((BooleanServerOption)var2).getValueAsObject() : nullptr;
   }

    float getFloat(const std::string& var1) {
    ServerOption var2 = this.getOptionByName(var1);
      return dynamic_cast<DoubleServerOption*>(var2) != nullptr ? (float)((DoubleServerOption)var2).getValue() : nullptr;
   }

    double getDouble(const std::string& var1) {
    ServerOption var2 = this.getOptionByName(var1);
      return dynamic_cast<DoubleServerOption*>(var2) != nullptr ? ((DoubleServerOption)var2).getValue() : nullptr;
   }

    int getInteger(const std::string& var1) {
    ServerOption var2 = this.getOptionByName(var1);
      return dynamic_cast<IntegerServerOption*>(var2) != nullptr ? ((IntegerServerOption)var2).getValue() : nullptr;
   }

    void putOption(const std::string& var1, const std::string& var2) {
    ServerOption var3 = this.getOptionByName(var1);
      if (var3 != nullptr) {
         var3.asConfigOption().parse(var2);
      }
   }

    void putSaveOption(const std::string& var1, const std::string& var2) {
      this.putOption(var1, var2);
      this.saveServerTextFile(GameServer.ServerName);
   }

    std::string changeOption(const std::string& var1, const std::string& var2) {
    ServerOption var3 = this.getOptionByName(var1);
      if (var3 == nullptr) {
         return "Option " + var1 + " doesn't exist.";
      } else {
         var3.asConfigOption().parse(var2);
         return !this.saveServerTextFile(GameServer.ServerName)
            ? "An error as occured."
            : "Option : " + var1 + " is now : " + var3.asConfigOption().getValueAsString();
      }
   }

    static ServerOptions getInstance() {
    return instance;
   }

   public static std::vector<std::string> getClientCommandList(boolean var0) {
    std::string var1 = " <LINE> ";
      if (!var0) {
         var1 = "\n";
      }

      if (clientOptionsList == nullptr) {
         initClientCommandsHelp();
      }

    std::vector var2 = new std::vector();
    Iterator var3 = clientOptionsList.keySet().iterator();
    void* var4 = nullptr;
      var2.push_back("List of commands : " + var1);

      while (var3.hasNext()) {
         var4 = (std::string)var3.next();
         var2.push_back("* " + var4 + " : " + clientOptionsList.get(var4) + (var3.hasNext() ? var1 : ""));
      }

    return var2;
   }

    static std::string getRandomCard() {
      if (cardList == nullptr) {
         cardList = std::make_unique<std::vector<>>();
         cardList.push_back("the Ace of Clubs");
         cardList.push_back("a Two of Clubs");
         cardList.push_back("a Three of Clubs");
         cardList.push_back("a Four of Clubs");
         cardList.push_back("a Five of Clubs");
         cardList.push_back("a Six of Clubs");
         cardList.push_back("a Seven of Clubs");
         cardList.push_back("a Height of Clubs");
         cardList.push_back("a Nine of Clubs");
         cardList.push_back("a Ten of Clubs");
         cardList.push_back("the Jack of Clubs");
         cardList.push_back("the Queen of Clubs");
         cardList.push_back("the King of Clubs");
         cardList.push_back("the Ace of Diamonds");
         cardList.push_back("a Two of Diamonds");
         cardList.push_back("a Three of Diamonds");
         cardList.push_back("a Four of Diamonds");
         cardList.push_back("a Five of Diamonds");
         cardList.push_back("a Six of Diamonds");
         cardList.push_back("a Seven of Diamonds");
         cardList.push_back("a Height of Diamonds");
         cardList.push_back("a Nine of Diamonds");
         cardList.push_back("a Ten of Diamonds");
         cardList.push_back("the Jack of Diamonds");
         cardList.push_back("the Queen of Diamonds");
         cardList.push_back("the King of Diamonds");
         cardList.push_back("the Ace of Hearts");
         cardList.push_back("a Two of Hearts");
         cardList.push_back("a Three of Hearts");
         cardList.push_back("a Four of Hearts");
         cardList.push_back("a Five of Hearts");
         cardList.push_back("a Six of Hearts");
         cardList.push_back("a Seven of Hearts");
         cardList.push_back("a Height of Hearts");
         cardList.push_back("a Nine of Hearts");
         cardList.push_back("a Ten of Hearts");
         cardList.push_back("the Jack of Hearts");
         cardList.push_back("the Queen of Hearts");
         cardList.push_back("the King of Hearts");
         cardList.push_back("the Ace of Spades");
         cardList.push_back("a Two of Spades");
         cardList.push_back("a Three of Spades");
         cardList.push_back("a Four of Spades");
         cardList.push_back("a Five of Spades");
         cardList.push_back("a Six of Spades");
         cardList.push_back("a Seven of Spades");
         cardList.push_back("a Height of Spades");
         cardList.push_back("a Nine of Spades");
         cardList.push_back("a Ten of Spades");
         cardList.push_back("the Jack of Spades");
         cardList.push_back("the Queen of Spades");
         cardList.push_back("the King of Spades");
      }

      return cardList.get(Rand.Next(cardList.size()));
   }

    void addOption(ServerOption var1) {
      if (this.optionByName.containsKey(var1.asConfigOption().getName())) {
         throw std::make_unique<IllegalArgumentException>();
      } else {
         this.options.push_back(var1);
         this.optionByName.put(var1.asConfigOption().getName(), var1);
      }
   }

    int getNumOptions() {
      return this.options.size();
   }

    ServerOption getOptionByIndex(int var1) {
      return this.options.get(var1);
   }

    ServerOption getOptionByName(const std::string& var1) {
      return this.optionByName.get(var1);
   }

    bool loadServerTextFile(const std::string& var1) {
    ConfigFile var2 = std::make_shared<ConfigFile>();
    std::string var3 = ZomboidFileSystem.instance.getCacheDir() + File.separator + "Server" + File.separator + var1 + ".ini";
      if (var2.read(var3)) {
         for (ConfigOption var5 : var2.getOptions()) {
    ServerOption var6 = this.optionByName.get(var5.getName());
            if (var6 != nullptr) {
               var6.asConfigOption().parse(var5.getValueAsString());
            }
         }

    return true;
      } else {
    return false;
      }
   }

    bool saveServerTextFile(const std::string& var1) {
    ConfigFile var2 = std::make_shared<ConfigFile>();
    std::string var3 = ZomboidFileSystem.instance.getCacheDir() + File.separator + "Server" + File.separator + var1 + ".ini";
    std::vector var4 = new std::vector();

      for (ServerOption var6 : this.options) {
         var4.push_back(var6.asConfigOption());
      }

      return var2.write(var3, 0, var4);
   }

    int getMaxPlayers() {
      return Math.min(100, getInstance().MaxPlayers.getValue());
   }
}
} // namespace network
} // namespace zombie
