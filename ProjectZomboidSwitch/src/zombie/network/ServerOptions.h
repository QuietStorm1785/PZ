                // Option change commands
                void putOption(const std::string& key, const std::string& value);
                void putSaveOption(const std::string& key, const std::string& value, const std::string& filename);
                std::string changeOption(const std::string& key, const std::string& value, const std::string& filename);
            // Region file and spawn region logic
            void resetRegionFile(const std::string& serverName);
            void initSpawnRegionsFile(const std::string& filePath, const std::string& serverName);
        // Advanced features
        static std::vector<std::string> getClientCommandList(bool useLineBreaks);
        static std::string getRandomCard();
        static void initClientCommandsHelp();

    private:
        static std::unordered_map<std::string, std::string> clientOptionsList;
        static std::vector<std::string> cardList;
    // File I/O
    bool loadServerTextFile(const std::string& filename);
    bool saveServerTextFile(const std::string& filename) const;
// ServerOptions.h
// Merged from Java source, including all inner classes as nested C++ classes.
#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <memory>

namespace zombie {
namespace network {


#include <vector>
#include <unordered_map>
#include <string>

class ServerOptions {
public:
    static ServerOptions& getInstance();
    ServerOptions();
    ~ServerOptions();

    // Ported API (partial, expand as needed)

    std::string getOption(const std::string& key) const;
    void setOption(const std::string& key, const std::string& value);
    int getNumOptions() const;
    const std::vector<std::string>& getPublicOptions();
    const std::vector<ServerOption*>& getOptions() const;
    ServerOption* getOptionByName(const std::string& name);
    ServerOption* getOptionByIndex(int idx);
    int getMaxPlayers() const;

    // ...add more ported methods as needed...

    // Nested class stubs (expand as needed)

    class ServerOption {
    public:
        virtual ~ServerOption() = default;
        virtual std::string getName() const = 0;
        virtual std::string getValueAsString() const = 0;
        virtual void parse(const std::string& value) = 0;
    };

    class BooleanServerOption : public ServerOption {
    public:
        BooleanServerOption(const std::string& name, bool defaultValue);
        std::string getName() const override;
        std::string getValueAsString() const override;
        void parse(const std::string& value) override;
        bool getValue() const;
        void setValue(bool v);
    private:
        std::string name;
        bool value;
    };

    class IntegerServerOption : public ServerOption {
    public:
        IntegerServerOption(const std::string& name, int min, int max, int defaultValue);
        std::string getName() const override;
        std::string getValueAsString() const override;
        void parse(const std::string& value) override;
        int getValue() const;
        void setValue(int v);
    private:
        std::string name;
        int value, min, max;
    };

    class DoubleServerOption : public ServerOption {
    public:
        DoubleServerOption(const std::string& name, double min, double max, double defaultValue);
        std::string getName() const override;
        std::string getValueAsString() const override;
        void parse(const std::string& value) override;
        double getValue() const;
        void setValue(double v);
    private:
        std::string name;
        double value, min, max;
    };

    class StringServerOption : public ServerOption {
    public:
        StringServerOption(const std::string& name, const std::string& defaultValue, int maxLen = -1);
        std::string getName() const override;
        std::string getValueAsString() const override;
        void parse(const std::string& value) override;
        std::string getValue() const;
        void setValue(const std::string& v);
    private:
        std::string name, value;
        int maxLen;
    };

    class TextServerOption : public ServerOption {
    public:
        TextServerOption(const std::string& name, const std::string& defaultValue, int maxLen = -1);
        std::string getName() const override;
        std::string getValueAsString() const override;
        void parse(const std::string& value) override;
        std::string getValue() const;
        void setValue(const std::string& v);
    private:
        std::string name, value;
        int maxLen;
    };

    // Example: add a few real options (expand as needed)
    // Boolean options
    BooleanServerOption PVP;
    BooleanServerOption PauseEmpty;
    BooleanServerOption GlobalChat;
    BooleanServerOption Open;
    BooleanServerOption AutoCreateUserInWhiteList;
    BooleanServerOption DisplayUserName;
    BooleanServerOption ShowFirstAndLastName;
    BooleanServerOption SafetySystem;
    BooleanServerOption ShowSafety;
    BooleanServerOption DoLuaChecksum;
    BooleanServerOption DenyLoginOnOverloadedServer;
    BooleanServerOption Public;
    BooleanServerOption ConstructionPreventsLootRespawn;
    BooleanServerOption DropOffWhiteListAfterDeath;
    BooleanServerOption NoFire;
    BooleanServerOption AnnounceDeath;
    BooleanServerOption PlayerSafehouse;
    BooleanServerOption AdminSafehouse;
    BooleanServerOption SafehouseAllowTrepass;
    BooleanServerOption SafehouseAllowFire;
    BooleanServerOption SafehouseAllowLoot;
    BooleanServerOption SafehouseAllowRespawn;
    BooleanServerOption SafehouseAllowNonResidential;
    BooleanServerOption AllowDestructionBySledgehammer;
    BooleanServerOption SledgehammerOnlyInSafehouse;
    BooleanServerOption KickFastPlayers;
    BooleanServerOption DiscordEnable;
    BooleanServerOption AllowCoop;
    BooleanServerOption SleepAllowed;
    BooleanServerOption SleepNeeded;
    BooleanServerOption KnockedDownAllowed;
    BooleanServerOption SneakModeHideFromOtherPlayers;
    BooleanServerOption SteamVAC;
    BooleanServerOption UPnP;
    BooleanServerOption VoiceEnable;
    BooleanServerOption Voice3D;
    BooleanServerOption LoginQueueEnabled;
    BooleanServerOption PlayerRespawnWithSelf;
    BooleanServerOption PlayerRespawnWithOther;
    BooleanServerOption DisableSafehouseWhenPlayerConnected;
    BooleanServerOption Faction;
    BooleanServerOption DisableRadioStaff;
    BooleanServerOption DisableRadioAdmin;
    BooleanServerOption DisableRadioGM;
    BooleanServerOption DisableRadioOverseer;
    BooleanServerOption DisableRadioModerator;
    BooleanServerOption DisableRadioInvisible;
    BooleanServerOption PerkLogs;
    BooleanServerOption AllowNonAsciiUsername;
    BooleanServerOption BanKickGlobalSound;
    BooleanServerOption RemovePlayerCorpsesOnCorpseRemoval;
    BooleanServerOption TrashDeleteAll;
    BooleanServerOption PVPMeleeWhileHitReaction;
    BooleanServerOption MouseOverToSeeDisplayName;
    BooleanServerOption HidePlayersBehindYou;
    BooleanServerOption PlayerBumpPlayer;
    BooleanServerOption BackupsOnStart;
    BooleanServerOption BackupsOnVersionChange;
    BooleanServerOption AntiCheatProtectionType1;
    BooleanServerOption AntiCheatProtectionType2;
    BooleanServerOption AntiCheatProtectionType3;
    BooleanServerOption AntiCheatProtectionType4;
    BooleanServerOption AntiCheatProtectionType5;
    BooleanServerOption AntiCheatProtectionType6;
    BooleanServerOption AntiCheatProtectionType7;
    BooleanServerOption AntiCheatProtectionType8;
    BooleanServerOption AntiCheatProtectionType9;
    BooleanServerOption AntiCheatProtectionType10;
    BooleanServerOption AntiCheatProtectionType11;
    BooleanServerOption AntiCheatProtectionType12;
    BooleanServerOption AntiCheatProtectionType13;
    BooleanServerOption AntiCheatProtectionType14;
    BooleanServerOption AntiCheatProtectionType15;
    BooleanServerOption AntiCheatProtectionType16;
    BooleanServerOption AntiCheatProtectionType17;
    BooleanServerOption AntiCheatProtectionType18;
    BooleanServerOption AntiCheatProtectionType19;
    BooleanServerOption AntiCheatProtectionType20;
    BooleanServerOption AntiCheatProtectionType21;
    BooleanServerOption AntiCheatProtectionType22;
    BooleanServerOption AntiCheatProtectionType23;
    BooleanServerOption AntiCheatProtectionType24;

    // Integer options
    IntegerServerOption SafetyToggleTimer;
    IntegerServerOption SafetyCooldownTimer;
    IntegerServerOption DefaultPort;
    IntegerServerOption UDPPort;
    IntegerServerOption ResetID;
    IntegerServerOption MaxPlayers;
    IntegerServerOption PingLimit;
    IntegerServerOption HoursForLootRespawn;
    IntegerServerOption MaxItemsForLootRespawn;
    IntegerServerOption SafehouseDaySurvivedToClaim;
    IntegerServerOption SafeHouseRemovalTime;
    IntegerServerOption RCONPort;
    IntegerServerOption MaxAccountsPerUser;
    IntegerServerOption FactionDaySurvivedToCreate;
    IntegerServerOption FactionPlayersRequiredForTag;
    IntegerServerOption ItemNumbersLimitPerContainer;
    IntegerServerOption BloodSplatLifespanDays;
    IntegerServerOption MapRemotePlayerVisibility;
    IntegerServerOption BackupsCount;
    IntegerServerOption BackupsPeriod;
    IntegerServerOption LoginQueueConnectTimeout;
    IntegerServerOption SaveWorldEveryMinutes;

    // Double options
    DoubleServerOption MinutesPerPage;
    DoubleServerOption VoiceMinDistance;
    DoubleServerOption VoiceMaxDistance;
    DoubleServerOption SpeedLimit;
    DoubleServerOption FastForwardMultiplier;
    DoubleServerOption PVPMeleeDamageModifier;
    DoubleServerOption PVPFirearmDamageModifier;
    DoubleServerOption CarEngineAttractionModifier;
    DoubleServerOption AntiCheatProtectionType2ThresholdMultiplier;
    DoubleServerOption AntiCheatProtectionType3ThresholdMultiplier;
    DoubleServerOption AntiCheatProtectionType4ThresholdMultiplier;
    DoubleServerOption AntiCheatProtectionType9ThresholdMultiplier;
    DoubleServerOption AntiCheatProtectionType15ThresholdMultiplier;
    DoubleServerOption AntiCheatProtectionType20ThresholdMultiplier;
    DoubleServerOption AntiCheatProtectionType22ThresholdMultiplier;
    DoubleServerOption AntiCheatProtectionType24ThresholdMultiplier;

    // String options
    StringServerOption ChatStreams;
    StringServerOption SpawnPoint;
    StringServerOption SpawnItems;
    StringServerOption Mods;
    StringServerOption Map;
    StringServerOption PublicName;
    StringServerOption RCONPassword;
    StringServerOption DiscordToken;
    StringServerOption DiscordChannel;
    StringServerOption DiscordChannelID;
    StringServerOption Password;
    StringServerOption ServerPlayerID;
    StringServerOption WorkshopItems;
    StringServerOption SteamScoreboard;
    StringServerOption ClientCommandFilter;
    StringServerOption ClientActionLogs;
    StringServerOption server_browser_announced_ip;

    // Text options
    TextServerOption ServerWelcomeMessage;
    TextServerOption PublicDescription;


private:
    std::vector<std::string> publicOptions;
    std::vector<ServerOption*> options;
    std::unordered_map<std::string, ServerOption*> optionByName;
    // ...add all public option fields as in Java...
};

} // namespace network
} // namespace zombie
