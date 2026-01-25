
// NAMESPACE WRAP BEGIN
namespace zombie {
namespace network {

void ServerOptions::putOption(const std::string& key, const std::string& value) {
    setOption(key, value);
}

void ServerOptions::putSaveOption(const std::string& key, const std::string& value, const std::string& filename) {
    putOption(key, value);
    saveServerTextFile(filename);
}

std::string ServerOptions::changeOption(const std::string& key, const std::string& value, const std::string& filename) {
    auto* opt = getOptionByName(key);
    if (!opt) {
        return "Option " + key + " doesn't exist.";
    }
    opt->parse(value);
    if (!saveServerTextFile(filename)) {
        return "An error has occurred.";
    }
    return "Option : " + key + " is now : " + opt->getValueAsString();
}
#include <cstdio>

void ServerOptions::resetRegionFile(const std::string& serverName) {
    std::string cacheDir = "."; // Replace with actual cache dir logic if needed
    std::string regionFile = cacheDir + "/Server/" + serverName + "_spawnregions.lua";
    std::remove(regionFile.c_str());
    initSpawnRegionsFile(regionFile, serverName);
}

void ServerOptions::initSpawnRegionsFile(const std::string& filePath, const std::string& serverName) {
    std::ifstream check(filePath);
    if (check.good()) return;
    check.close();
    std::ofstream file(filePath);
    if (!file.is_open()) return;
    file << "function SpawnRegions()\n";
    file << "\treturn {\n";
    file << "\t\t{ name = \"Muldraugh, KY\", file = \"media/maps/Muldraugh, KY/spawnpoints.lua\" },\n";
    file << "\t\t{ name = \"West Point, KY\", file = \"media/maps/West Point, KY/spawnpoints.lua\" },\n";
    file << "\t\t{ name = \"Rosewood, KY\", file = \"media/maps/Rosewood, KY/spawnpoints.lua\" },\n";
    file << "\t\t{ name = \"Riverside, KY\", file = \"media/maps/Riverside, KY/spawnpoints.lua\" },\n";
    file << "\t\t-- Uncomment the line below to add a custom spawnpoint for this server.\n";
    file << "--\t\t{ name = \"Twiggy's Bar\", serverfile = \"" << serverName << "_spawnpoints.lua\" },\n";
    file << "\t}\n";
    file << "end\n";
    file.close();

    std::string spawnpointsFile = filePath.substr(0, filePath.find("_spawnregions.lua")) + "_spawnpoints.lua";
    std::ofstream spfile(spawnpointsFile);
    if (!spfile.is_open()) return;
    spfile << "function SpawnPoints()\n";
    spfile << "\treturn {\n";
    spfile << "\t\tunemployed = {\n";
    spfile << "\t\t\t{ worldX = 40, worldY = 22, posX = 67, posY = 201 }\n";
    spfile << "\t\t}\n";
    spfile << "\t}\n";
    spfile << "end\n";
    spfile.close();
}
#include <random>

} // namespace network
} // namespace zombie
// NAMESPACE WRAP END

std::unordered_map<std::string, std::string> ServerOptions::clientOptionsList;
std::vector<std::string> ServerOptions::cardList;

void ServerOptions::initClientCommandsHelp() {
    clientOptionsList.clear();
    clientOptionsList["help"] = "Show help information.";
    clientOptionsList["changepwd"] = "Change your password.";
    clientOptionsList["roll"] = "Roll a dice.";
    clientOptionsList["card"] = "Draw a card.";
    clientOptionsList["safehouse"] = "Safehouse commands.";
}

std::vector<std::string> ServerOptions::getClientCommandList(bool useLineBreaks) {
    std::string line = useLineBreaks ? " <LINE> " : "\n";
    if (clientOptionsList.empty()) initClientCommandsHelp();
    std::vector<std::string> result;
    result.push_back("List of commands : " + line);
    for (auto it = clientOptionsList.begin(); it != clientOptionsList.end(); ++it) {
        result.push_back("* " + it->first + " : " + it->second + (std::next(it) != clientOptionsList.end() ? line : ""));
    }
    return result;
}

std::string ServerOptions::getRandomCard() {
    if (cardList.empty()) {
        cardList = {
            "the Ace of Clubs", "a Two of Clubs", "a Three of Clubs", "a Four of Clubs", "a Five of Clubs", "a Six of Clubs", "a Seven of Clubs", "a Height of Clubs", "a Nine of Clubs", "a Ten of Clubs", "the Jack of Clubs", "the Queen of Clubs", "the King of Clubs",
            "the Ace of Diamonds", "a Two of Diamonds", "a Three of Diamonds", "a Four of Diamonds", "a Five of Diamonds", "a Six of Diamonds", "a Seven of Diamonds", "a Height of Diamonds", "a Nine of Diamonds", "a Ten of Diamonds", "the Jack of Diamonds", "the Queen of Diamonds", "the King of Diamonds",
            "the Ace of Hearts", "a Two of Hearts", "a Three of Hearts", "a Four of Hearts", "a Five of Hearts", "a Six of Hearts", "a Seven of Hearts", "a Height of Hearts", "a Nine of Hearts", "a Ten of Hearts", "the Jack of Hearts", "the Queen of Hearts", "the King of Hearts",
            "the Ace of Spades", "a Two of Spades", "a Three of Spades", "a Four of Spades", "a Five of Spades", "a Six of Spades", "a Seven of Spades", "a Height of Spades", "a Nine of Spades", "a Ten of Spades", "the Jack of Spades", "the Queen of Spades", "the King of Spades"
        };
    }
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, static_cast<int>(cardList.size()) - 1);
    return cardList[dis(gen)];
}
#include <fstream>
#include <sstream>

bool ServerOptions::loadServerTextFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) return false;
    std::string line;
    while (std::getline(file, line)) {
        // Simple INI-style: key=value
        size_t eq = line.find('=');
        if (eq == std::string::npos) continue;
        std::string key = line.substr(0, eq);
        std::string value = line.substr(eq + 1);
        setOption(key, value);
    }
    return true;
}

bool ServerOptions::saveServerTextFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) return false;
    for (const auto* opt : options) {
        file << opt->getName() << "=" << opt->getValueAsString() << "\n";
    }
    return true;
}
// ServerOptions.cpp
// Merged from Java source, including all inner classes as nested C++ classes.
#include "ServerOptions.h"
#include <fstream>
#include <sstream>

namespace zombie {
namespace network {


#include <algorithm>


ServerOptions& ServerOptions::getInstance() {
    static ServerOptions instance;
    return instance;
}

ServerOptions::BooleanServerOption::BooleanServerOption(const std::string& n, bool def)
    : name(n), value(def) {}
std::string ServerOptions::BooleanServerOption::getName() const { return name; }
std::string ServerOptions::BooleanServerOption::getValueAsString() const { return value ? "true" : "false"; }
void ServerOptions::BooleanServerOption::parse(const std::string& v) { value = (v == "true" || v == "1"); }
bool ServerOptions::BooleanServerOption::getValue() const { return value; }
void ServerOptions::BooleanServerOption::setValue(bool v) { value = v; }

ServerOptions::IntegerServerOption::IntegerServerOption(const std::string& n, int min_, int max_, int def)
    : name(n), value(def), min(min_), max(max_) {}
std::string ServerOptions::IntegerServerOption::getName() const { return name; }
std::string ServerOptions::IntegerServerOption::getValueAsString() const { return std::to_string(value); }
void ServerOptions::IntegerServerOption::parse(const std::string& v) { value = std::stoi(v); if (value < min) value = min; if (value > max) value = max; }
int ServerOptions::IntegerServerOption::getValue() const { return value; }
void ServerOptions::IntegerServerOption::setValue(int v) { value = v; }

ServerOptions::DoubleServerOption::DoubleServerOption(const std::string& n, double min_, double max_, double def)
    : name(n), value(def), min(min_), max(max_) {}
std::string ServerOptions::DoubleServerOption::getName() const { return name; }
std::string ServerOptions::DoubleServerOption::getValueAsString() const { return std::to_string(value); }
void ServerOptions::DoubleServerOption::parse(const std::string& v) { value = std::stod(v); if (value < min) value = min; if (value > max) value = max; }
double ServerOptions::DoubleServerOption::getValue() const { return value; }
void ServerOptions::DoubleServerOption::setValue(double v) { value = v; }

ServerOptions::StringServerOption::StringServerOption(const std::string& n, const std::string& def, int maxL)
    : name(n), value(def), maxLen(maxL) {}
std::string ServerOptions::StringServerOption::getName() const { return name; }
std::string ServerOptions::StringServerOption::getValueAsString() const { return value; }
void ServerOptions::StringServerOption::parse(const std::string& v) { value = v; if (maxLen > 0 && value.length() > (size_t)maxLen) value.resize(maxLen); }
std::string ServerOptions::StringServerOption::getValue() const { return value; }
void ServerOptions::StringServerOption::setValue(const std::string& v) { value = v; }

ServerOptions::TextServerOption::TextServerOption(const std::string& n, const std::string& def, int maxL)
    : name(n), value(def), maxLen(maxL) {}
std::string ServerOptions::TextServerOption::getName() const { return name; }
std::string ServerOptions::TextServerOption::getValueAsString() const { return value; }
void ServerOptions::TextServerOption::parse(const std::string& v) { value = v; if (maxLen > 0 && value.length() > (size_t)maxLen) value.resize(maxLen); }
std::string ServerOptions::TextServerOption::getValue() const { return value; }
void ServerOptions::TextServerOption::setValue(const std::string& v) { value = v; }

ServerOptions::ServerOptions()
    :
      // Boolean options
      PVP("PVP", true),
      PauseEmpty("PauseEmpty", true),
      GlobalChat("GlobalChat", true),
      Open("Open", true),
      AutoCreateUserInWhiteList("AutoCreateUserInWhiteList", false),
      DisplayUserName("DisplayUserName", true),
      ShowFirstAndLastName("ShowFirstAndLastName", false),
      SafetySystem("SafetySystem", true),
      ShowSafety("ShowSafety", true),
      DoLuaChecksum("DoLuaChecksum", true),
      DenyLoginOnOverloadedServer("DenyLoginOnOverloadedServer", true),
      Public("Public", false),
      ConstructionPreventsLootRespawn("ConstructionPreventsLootRespawn", true),
      DropOffWhiteListAfterDeath("DropOffWhiteListAfterDeath", false),
      NoFire("NoFire", false),
      AnnounceDeath("AnnounceDeath", false),
      PlayerSafehouse("PlayerSafehouse", false),
      AdminSafehouse("AdminSafehouse", false),
      SafehouseAllowTrepass("SafehouseAllowTrepass", true),
      SafehouseAllowFire("SafehouseAllowFire", true),
      SafehouseAllowLoot("SafehouseAllowLoot", true),
      SafehouseAllowRespawn("SafehouseAllowRespawn", false),
      SafehouseAllowNonResidential("SafehouseAllowNonResidential", false),
      AllowDestructionBySledgehammer("AllowDestructionBySledgehammer", true),
      SledgehammerOnlyInSafehouse("SledgehammerOnlyInSafehouse", false),
      KickFastPlayers("KickFastPlayers", false),
      DiscordEnable("DiscordEnable", false),
      AllowCoop("AllowCoop", true),
      SleepAllowed("SleepAllowed", false),
      SleepNeeded("SleepNeeded", false),
      KnockedDownAllowed("KnockedDownAllowed", true),
      SneakModeHideFromOtherPlayers("SneakModeHideFromOtherPlayers", true),
      SteamVAC("SteamVAC", true),
      UPnP("UPnP", true),
      VoiceEnable("VoiceEnable", true),
      Voice3D("Voice3D", true),
      LoginQueueEnabled("LoginQueueEnabled", false),
      PlayerRespawnWithSelf("PlayerRespawnWithSelf", false),
      PlayerRespawnWithOther("PlayerRespawnWithOther", false),
      DisableSafehouseWhenPlayerConnected("DisableSafehouseWhenPlayerConnected", false),
      Faction("Faction", true),
      DisableRadioStaff("DisableRadioStaff", false),
      DisableRadioAdmin("DisableRadioAdmin", true),
      DisableRadioGM("DisableRadioGM", true),
      DisableRadioOverseer("DisableRadioOverseer", false),
      DisableRadioModerator("DisableRadioModerator", false),
      DisableRadioInvisible("DisableRadioInvisible", true),
      PerkLogs("PerkLogs", true),
      AllowNonAsciiUsername("AllowNonAsciiUsername", false),
      BanKickGlobalSound("BanKickGlobalSound", true),
      RemovePlayerCorpsesOnCorpseRemoval("RemovePlayerCorpsesOnCorpseRemoval", false),
      TrashDeleteAll("TrashDeleteAll", false),
      PVPMeleeWhileHitReaction("PVPMeleeWhileHitReaction", false),
      MouseOverToSeeDisplayName("MouseOverToSeeDisplayName", true),
      HidePlayersBehindYou("HidePlayersBehindYou", true),
      PlayerBumpPlayer("PlayerBumpPlayer", false),
      BackupsOnStart("BackupsOnStart", true),
      BackupsOnVersionChange("BackupsOnVersionChange", true),
      AntiCheatProtectionType1("AntiCheatProtectionType1", true),
      AntiCheatProtectionType2("AntiCheatProtectionType2", true),
      AntiCheatProtectionType3("AntiCheatProtectionType3", true),
      AntiCheatProtectionType4("AntiCheatProtectionType4", true),
      AntiCheatProtectionType5("AntiCheatProtectionType5", true),
      AntiCheatProtectionType6("AntiCheatProtectionType6", true),
      AntiCheatProtectionType7("AntiCheatProtectionType7", true),
      AntiCheatProtectionType8("AntiCheatProtectionType8", true),
      AntiCheatProtectionType9("AntiCheatProtectionType9", true),
      AntiCheatProtectionType10("AntiCheatProtectionType10", true),
      AntiCheatProtectionType11("AntiCheatProtectionType11", true),
      AntiCheatProtectionType12("AntiCheatProtectionType12", true),
      AntiCheatProtectionType13("AntiCheatProtectionType13", true),
      AntiCheatProtectionType14("AntiCheatProtectionType14", true),
      AntiCheatProtectionType15("AntiCheatProtectionType15", true),
      AntiCheatProtectionType16("AntiCheatProtectionType16", true),
      AntiCheatProtectionType17("AntiCheatProtectionType17", true),
      AntiCheatProtectionType18("AntiCheatProtectionType18", true),
      AntiCheatProtectionType19("AntiCheatProtectionType19", true),
      AntiCheatProtectionType20("AntiCheatProtectionType20", true),
      AntiCheatProtectionType21("AntiCheatProtectionType21", true),
      AntiCheatProtectionType22("AntiCheatProtectionType22", true),
      AntiCheatProtectionType23("AntiCheatProtectionType23", true),
      AntiCheatProtectionType24("AntiCheatProtectionType24", true),

      // Integer options
      SafetyToggleTimer("SafetyToggleTimer", 0, 1000, 2),
      SafetyCooldownTimer("SafetyCooldownTimer", 0, 1000, 3),
      DefaultPort("DefaultPort", 0, 65535, 16261),
      UDPPort("UDPPort", 0, 65535, 16262),
      ResetID("ResetID", 0, INT32_MAX, 1000000000),
      MaxPlayers("MaxPlayers", 1, 100, 32),
      PingLimit("PingLimit", 100, INT32_MAX, 400),
      HoursForLootRespawn("HoursForLootRespawn", 0, INT32_MAX, 0),
      MaxItemsForLootRespawn("MaxItemsForLootRespawn", 1, INT32_MAX, 4),
      SafehouseDaySurvivedToClaim("SafehouseDaySurvivedToClaim", 0, INT32_MAX, 0),
      SafeHouseRemovalTime("SafeHouseRemovalTime", 0, INT32_MAX, 144),
      RCONPort("RCONPort", 0, 65535, 27015),
      MaxAccountsPerUser("MaxAccountsPerUser", 0, INT32_MAX, 0),
      FactionDaySurvivedToCreate("FactionDaySurvivedToCreate", 0, INT32_MAX, 0),
      FactionPlayersRequiredForTag("FactionPlayersRequiredForTag", 1, INT32_MAX, 1),
      ItemNumbersLimitPerContainer("ItemNumbersLimitPerContainer", 0, 9000, 0),
      BloodSplatLifespanDays("BloodSplatLifespanDays", 0, 365, 0),
      MapRemotePlayerVisibility("MapRemotePlayerVisibility", 1, 3, 1),
      BackupsCount("BackupsCount", 1, 300, 5),
      BackupsPeriod("BackupsPeriod", 0, 1500, 0),
      LoginQueueConnectTimeout("LoginQueueConnectTimeout", 20, 1200, 60),
      SaveWorldEveryMinutes("SaveWorldEveryMinutes", 0, INT32_MAX, 0),

      // Double options
      MinutesPerPage("MinutesPerPage", 0.0, 60.0, 1.0),
      VoiceMinDistance("VoiceMinDistance", 0.0, 100000.0, 10.0),
      VoiceMaxDistance("VoiceMaxDistance", 0.0, 100000.0, 100.0),
      SpeedLimit("SpeedLimit", 10.0, 150.0, 70.0),
      FastForwardMultiplier("FastForwardMultiplier", 1.0, 100.0, 40.0),
      PVPMeleeDamageModifier("PVPMeleeDamageModifier", 0.0, 500.0, 30.0),
      PVPFirearmDamageModifier("PVPFirearmDamageModifier", 0.0, 500.0, 50.0),
      CarEngineAttractionModifier("CarEngineAttractionModifier", 0.0, 10.0, 0.5),
      AntiCheatProtectionType2ThresholdMultiplier("AntiCheatProtectionType2ThresholdMultiplier", 1.0, 10.0, 3.0),
      AntiCheatProtectionType3ThresholdMultiplier("AntiCheatProtectionType3ThresholdMultiplier", 1.0, 10.0, 1.0),
      AntiCheatProtectionType4ThresholdMultiplier("AntiCheatProtectionType4ThresholdMultiplier", 1.0, 10.0, 1.0),
      AntiCheatProtectionType9ThresholdMultiplier("AntiCheatProtectionType9ThresholdMultiplier", 1.0, 10.0, 1.0),
      AntiCheatProtectionType15ThresholdMultiplier("AntiCheatProtectionType15ThresholdMultiplier", 1.0, 10.0, 1.0),
      AntiCheatProtectionType20ThresholdMultiplier("AntiCheatProtectionType20ThresholdMultiplier", 1.0, 10.0, 1.0),
      AntiCheatProtectionType22ThresholdMultiplier("AntiCheatProtectionType22ThresholdMultiplier", 1.0, 10.0, 1.0),
      AntiCheatProtectionType24ThresholdMultiplier("AntiCheatProtectionType24ThresholdMultiplier", 1.0, 10.0, 6.0),

      // String options
      ChatStreams("ChatStreams", "s,r,a,w,y,sh,f,all", -1),
      SpawnPoint("SpawnPoint", "0,0,0", -1),
      SpawnItems("SpawnItems", "", -1),
      Mods("Mods", "", -1),
      Map("Map", "Muldraugh, KY", -1),
      PublicName("PublicName", "My PZ Server", 64),
      RCONPassword("RCONPassword", "", -1),
      DiscordToken("DiscordToken", "", -1),
      DiscordChannel("DiscordChannel", "", -1),
      DiscordChannelID("DiscordChannelID", "", -1),
      Password("Password", "", -1),
      ServerPlayerID("ServerPlayerID", "", -1),
      WorkshopItems("WorkshopItems", "", -1),
      SteamScoreboard("SteamScoreboard", "true", -1),
      ClientCommandFilter("ClientCommandFilter", "-vehicle.*;+vehicle.damageWindow;+vehicle.fixPart;+vehicle.installPart;+vehicle.uninstallPart", -1),
      ClientActionLogs("ClientActionLogs", "ISEnterVehicle;ISExitVehicle;ISTakeEngineParts;", -1),
      server_browser_announced_ip("server_browser_announced_ip", "", -1),

      // Text options
      ServerWelcomeMessage("ServerWelcomeMessage", "Welcome to Project Zomboid Multiplayer! <LINE> <LINE> To interact with the Chat panel: press Tab, T, or Enter. <LINE> <LINE> The Tab key will change the target stream of the message. <LINE> <LINE> Global Streams: /all <LINE> Local Streams: /say, /yell <LINE> Special Steams: /whisper, /safehouse, /faction. <LINE> <LINE> Press the Up arrow to cycle through your message history. Click the Gear icon to customize chat. <LINE> <LINE> Happy surviving!", -1),
      PublicDescription("PublicDescription", "", 256)
{
    // Register all options
    options = {
        &PVP, &PauseEmpty, &GlobalChat, &Open, &AutoCreateUserInWhiteList, &DisplayUserName, &ShowFirstAndLastName, &SafetySystem, &ShowSafety, &DoLuaChecksum, &DenyLoginOnOverloadedServer, &Public, &ConstructionPreventsLootRespawn, &DropOffWhiteListAfterDeath, &NoFire, &AnnounceDeath, &PlayerSafehouse, &AdminSafehouse, &SafehouseAllowTrepass, &SafehouseAllowFire, &SafehouseAllowLoot, &SafehouseAllowRespawn, &SafehouseAllowNonResidential, &AllowDestructionBySledgehammer, &SledgehammerOnlyInSafehouse, &KickFastPlayers, &DiscordEnable, &AllowCoop, &SleepAllowed, &SleepNeeded, &KnockedDownAllowed, &SneakModeHideFromOtherPlayers, &SteamVAC, &UPnP, &VoiceEnable, &Voice3D, &LoginQueueEnabled, &PlayerRespawnWithSelf, &PlayerRespawnWithOther, &DisableSafehouseWhenPlayerConnected, &Faction, &DisableRadioStaff, &DisableRadioAdmin, &DisableRadioGM, &DisableRadioOverseer, &DisableRadioModerator, &DisableRadioInvisible, &PerkLogs, &AllowNonAsciiUsername, &BanKickGlobalSound, &RemovePlayerCorpsesOnCorpseRemoval, &TrashDeleteAll, &PVPMeleeWhileHitReaction, &MouseOverToSeeDisplayName, &HidePlayersBehindYou, &PlayerBumpPlayer, &BackupsOnStart, &BackupsOnVersionChange, &AntiCheatProtectionType1, &AntiCheatProtectionType2, &AntiCheatProtectionType3, &AntiCheatProtectionType4, &AntiCheatProtectionType5, &AntiCheatProtectionType6, &AntiCheatProtectionType7, &AntiCheatProtectionType8, &AntiCheatProtectionType9, &AntiCheatProtectionType10, &AntiCheatProtectionType11, &AntiCheatProtectionType12, &AntiCheatProtectionType13, &AntiCheatProtectionType14, &AntiCheatProtectionType15, &AntiCheatProtectionType16, &AntiCheatProtectionType17, &AntiCheatProtectionType18, &AntiCheatProtectionType19, &AntiCheatProtectionType20, &AntiCheatProtectionType21, &AntiCheatProtectionType22, &AntiCheatProtectionType23, &AntiCheatProtectionType24,
        &SafetyToggleTimer, &SafetyCooldownTimer, &DefaultPort, &UDPPort, &ResetID, &MaxPlayers, &PingLimit, &HoursForLootRespawn, &MaxItemsForLootRespawn, &SafehouseDaySurvivedToClaim, &SafeHouseRemovalTime, &RCONPort, &MaxAccountsPerUser, &FactionDaySurvivedToCreate, &FactionPlayersRequiredForTag, &ItemNumbersLimitPerContainer, &BloodSplatLifespanDays, &MapRemotePlayerVisibility, &BackupsCount, &BackupsPeriod, &LoginQueueConnectTimeout, &SaveWorldEveryMinutes,
        &MinutesPerPage, &VoiceMinDistance, &VoiceMaxDistance, &SpeedLimit, &FastForwardMultiplier, &PVPMeleeDamageModifier, &PVPFirearmDamageModifier, &CarEngineAttractionModifier, &AntiCheatProtectionType2ThresholdMultiplier, &AntiCheatProtectionType3ThresholdMultiplier, &AntiCheatProtectionType4ThresholdMultiplier, &AntiCheatProtectionType9ThresholdMultiplier, &AntiCheatProtectionType15ThresholdMultiplier, &AntiCheatProtectionType20ThresholdMultiplier, &AntiCheatProtectionType22ThresholdMultiplier, &AntiCheatProtectionType24ThresholdMultiplier,
        &ChatStreams, &SpawnPoint, &SpawnItems, &Mods, &Map, &PublicName, &RCONPassword, &DiscordToken, &DiscordChannel, &DiscordChannelID, &Password, &ServerPlayerID, &WorkshopItems, &SteamScoreboard, &ClientCommandFilter, &ClientActionLogs, &server_browser_announced_ip,
        &ServerWelcomeMessage, &PublicDescription
    };
    for (auto* opt : options) {
        optionByName[opt->getName()] = opt;
    }
}

ServerOptions::~ServerOptions() {}


std::string ServerOptions::getOption(const std::string& key) const {
    auto it = optionByName.find(key);
    if (it != optionByName.end() && it->second) {
        return it->second->getValueAsString();
    }
    return "";
}

void ServerOptions::setOption(const std::string& key, const std::string& value) {
    auto it = optionByName.find(key);
    if (it != optionByName.end() && it->second) {
        it->second->parse(value);
    }
}

int ServerOptions::getNumOptions() const {
    return static_cast<int>(options.size());
}

const std::vector<std::string>& ServerOptions::getPublicOptions() {
    if (publicOptions.empty()) {
        // Fill publicOptions with all option names except sensitive ones
        for (const auto& pair : optionByName) {
            const std::string& name = pair.first;
            if (name != "Password" && name != "RCONPort" && name != "RCONPassword" &&
                name != "DiscordToken" && name != "DiscordChannel" && name != "DiscordChannelID") {
                publicOptions.push_back(name);
            }
        }
        std::sort(publicOptions.begin(), publicOptions.end());
    }
    return publicOptions;
}

const std::vector<ServerOptions::ServerOption*>& ServerOptions::getOptions() const {
    return options;
}

ServerOptions::ServerOption* ServerOptions::getOptionByName(const std::string& name) {
    auto it = optionByName.find(name);
    if (it != optionByName.end()) return it->second;
    return nullptr;
}

ServerOptions::ServerOption* ServerOptions::getOptionByIndex(int idx) {
    if (idx < 0 || idx >= static_cast<int>(options.size())) return nullptr;
    return options[idx];
}

int ServerOptions::getMaxPlayers() const {
    // Clamp to 100 as in Java
    int val = MaxPlayers.getValue();
    return val > 100 ? 100 : val;
}

// ...implement more ported logic as needed...

} // namespace network
} // namespace zombie
