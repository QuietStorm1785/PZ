#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/SystemDisabler.h"
#include "zombie/characters/Faction.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/characters/IsoZombie.h"
#include "zombie/characters/SafetySystemManager.h"
#include "zombie/commands/PlayerType.h"
#include "zombie/core/Core.h"
#include "zombie/core/Rand.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/core/utils/UpdateLimit.h"
#include "zombie/core/znet/SteamUtils.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/iso/IsoMovingObject.h"
#include "zombie/iso/IsoUtils.h"
#include "zombie/iso/areas/NonPvpZone.h"
#include "zombie/network/PacketValidator/RecipeDetails.h"
#include "zombie/network/Userlog/UserlogType.h"
#include "zombie/network/packets/hit/char.h"
#include "zombie/network/packets/hit/Hit.h"
#include "zombie/network/packets/hit/IMovable.h"
#include "zombie/network/packets/hit/IPositional.h"
#include "zombie/network/packets/hit/Player.h"
#include "zombie/network/packets/hit/Zombie.h"
#include "zombie/util/StringUtils.h"
#include "zombie/util/Type.h"
#include <algorithm>

namespace zombie {
namespace network {


class PacketValidator {
public:
    static const int SUSPICIOUS_ACTIVITIES_MAX = 4;
    const UpdateLimit ulSuspiciousActivity = std::make_shared<UpdateLimit>(150000L);
   public const std::unordered_map<std::string, RecipeDetails> details = std::make_unique<std::unordered_map<>>();
   public const std::unordered_map<std::string, RecipeDetails> detailsFromClient = std::make_unique<std::unordered_map<>>();
    bool failed = false;
    static const long USER_LOG_INTERVAL_MS = 1000L;
    static const int MAX_TYPE_3 = 10;
    static const int MAX_TYPE_4 = 101;
    const UdpConnection connection;
    const UpdateLimit ulTimeMultiplier = std::make_shared<UpdateLimit>(this.getTimeMultiplierTimeout());
    const UpdateLimit ulRecipeChecksumInterval = std::make_shared<UpdateLimit>(this.getChecksumInterval());
    const UpdateLimit ulRecipeChecksumTimeout = std::make_shared<UpdateLimit>(this.getChecksumTimeout());
    int salt;
    int suspiciousActivityCounter;
    std::string suspiciousActivityDescription;

    public PacketValidator(UdpConnection var1) {
      this.connection = var1;
      this.suspiciousActivityCounter = 0;
   }

    void reset() {
      this.salt = Rand.Next(int.MAX_VALUE);
   }

    bool isReady() {
    IsoPlayer var1 = GameServer.getPlayerByRealUserName(this.connection.username);
      return this.connection.isFullyConnected()
         && this.connection.isConnectionGraceIntervalTimeout()
         && !GameServer.bFastForward
         && var1 != nullptr
         && var1.isAlive();
   }

    int getSalt() {
      return this.salt;
   }

    long getChecksumDelay() {
      return (long)(1000.0 * ServerOptions.getInstance().AntiCheatProtectionType22ThresholdMultiplier.getValue());
   }

    long getChecksumInterval() {
      return (long)(4000.0 * ServerOptions.getInstance().AntiCheatProtectionType22ThresholdMultiplier.getValue());
   }

    long getChecksumTimeout() {
      return (long)(10000.0 * ServerOptions.getInstance().AntiCheatProtectionType22ThresholdMultiplier.getValue());
   }

    void failChecksum() {
      if (ServerOptions.instance.AntiCheatProtectionType21.getValue() && checkUser(this.connection)) {
         DebugLog.Multiplayer.warn("Checksum fail for \"%s\" (Type21)", new Object[]{this.connection.username});
         this.failed = true;
      }

      this.ulRecipeChecksumTimeout.Reset(this.getChecksumDelay());
   }

    bool isFailed() {
      return this.failed;
   }

    void timeoutChecksum() {
      if (this.failed) {
         doKickUser(this.connection, this.getClass().getSimpleName(), "Type21", this.getDescription());
      } else {
         if (ServerOptions.instance.AntiCheatProtectionType22.getValue() && checkUser(this.connection)) {
            doKickUser(this.connection, this.getClass().getSimpleName(), "Type22", nullptr);
         }

         this.ulRecipeChecksumTimeout.Reset(this.getChecksumTimeout());
      }
   }

    void successChecksum() {
      this.ulRecipeChecksumTimeout.Reset(this.getChecksumTimeout());
   }

    void sendChecksum(bool var1, bool var2, bool var3) {
      this.salt = Rand.Next(int.MAX_VALUE);
      GameServer.sendValidatePacket(this.connection, var1, var2, var3);
      this.ulRecipeChecksumInterval.Reset(this.getChecksumInterval());
   }

    long getTimeMultiplierTimeout() {
      return (long)(10000.0 * ServerOptions.getInstance().AntiCheatProtectionType24ThresholdMultiplier.getValue());
   }

    void failTimeMultiplier(float var1) {
      if (ServerOptions.instance.AntiCheatProtectionType23.getValue() && checkUser(this.connection)) {
         doKickUser(this.connection, this.getClass().getSimpleName(), "Type23", std::string.valueOf(var1));
      }

      this.ulTimeMultiplier.Reset(this.getTimeMultiplierTimeout());
   }

    void timeoutTimeMultiplier() {
      if (ServerOptions.instance.AntiCheatProtectionType24.getValue() && checkUser(this.connection)) {
         doKickUser(this.connection, this.getClass().getSimpleName(), "Type24", nullptr);
      }

      this.ulTimeMultiplier.Reset(this.getTimeMultiplierTimeout());
   }

    void successTimeMultiplier() {
      this.ulTimeMultiplier.Reset(this.getTimeMultiplierTimeout());
   }

    void update() {
      if (GameServer.bServer) {
         if (this.ulSuspiciousActivity.Check()) {
            this.updateSuspiciousActivityCounter();
         }

         if (this.isReady()) {
            if (!this.failed && this.ulRecipeChecksumInterval.Check()) {
               this.sendChecksum(false, false, false);
            }

            if (this.ulRecipeChecksumTimeout.Check()) {
               this.timeoutChecksum();
            }

            if (this.ulTimeMultiplier.Check()) {
               this.timeoutTimeMultiplier();
            }
         } else {
            this.ulRecipeChecksumInterval.Reset(this.getChecksumInterval());
            this.ulRecipeChecksumTimeout.Reset(this.getChecksumTimeout());
            this.ulTimeMultiplier.Reset(this.getTimeMultiplierTimeout());
            this.failed = false;
         }
      }
   }

    static bool checkPVP(UdpConnection var0, char var1, char var2, const std::string& var3) {
    bool var4 = checkPVP(var1.getCharacter(), var2.getCharacter()) || SafetySystemManager.checkUpdateDelay(var1.getCharacter(), var2.getCharacter());
      if (!var4 && ServerOptions.instance.AntiCheatProtectionType1.getValue() && checkUser(var0)) {
         doKickUser(var0, var3, "Type1", nullptr);
      }

    return var4;
   }

    static bool checkSpeed(UdpConnection var0, IMovable var1, const std::string& var2) {
    float var3 = var1.getSpeed();
    double var4 = var1.isVehicle() ? ServerOptions.instance.SpeedLimit.getValue() : 10.0;
    bool var6 = var3 <= var4 * ServerOptions.instance.AntiCheatProtectionType2ThresholdMultiplier.getValue();
      if (!var6 && ServerOptions.instance.AntiCheatProtectionType2.getValue() && checkUser(var0)) {
         doKickUser(var0, var2, "Type2", std::string.valueOf(var3));
      }

    return var6;
   }

    static bool checkLongDistance(UdpConnection var0, IPositional var1, IPositional var2, const std::string& var3) {
    float var4 = IsoUtils.DistanceTo(var2.getX(), var2.getY(), var1.getX(), var1.getY());
    bool var5 = var4 <= var0.ReleventRange * 10 * ServerOptions.instance.AntiCheatProtectionType3ThresholdMultiplier.getValue();
      if (!var5 && ServerOptions.instance.AntiCheatProtectionType3.getValue() && checkUser(var0)) {
         if (var0.validator.checkSuspiciousActivity("Type3")) {
            doKickUser(var0, var3, "Type3", std::string.valueOf(var4));
         } else {
            doLogUser(var0, UserlogType.SuspiciousActivity, var3, "Type3");
         }
      }

    return var5;
   }

    static bool checkDamage(UdpConnection var0, Hit var1, const std::string& var2) {
    float var3 = var1.getDamage();
    bool var4 = var3 <= 101.0 * ServerOptions.instance.AntiCheatProtectionType4ThresholdMultiplier.getValue();
      if (!var4 && ServerOptions.instance.AntiCheatProtectionType4.getValue() && checkUser(var0)) {
         doKickUser(var0, var2, "Type4", std::string.valueOf(var3));
      }

    return var4;
   }

    static bool checkOwner(UdpConnection var0, Zombie var1, const std::string& var2) {
    IsoZombie var3 = (IsoZombie)var1.getCharacter();
    UdpConnection var4 = var3.authOwner;
    bool var5 = var4 == var0 && System.currentTimeMillis() - var3.lastChangeOwner > 2000L;
      if (!var5 && ServerOptions.instance.AntiCheatProtectionType5.getValue() && checkUser(var0)) {
         if (var0.validator.checkSuspiciousActivity("Type5")) {
            doKickUser(var0, var2, "Type5", Optional.ofNullable(var4).map(var0x -> var0x.username).orElse(""));
         } else {
            doLogUser(var0, UserlogType.SuspiciousActivity, var2, "Type5");
         }
      }

    return var5;
   }

    static bool checkTarget(UdpConnection var0, Player var1, const std::string& var2) {
    IsoPlayer var3 = var1.getPlayer();
    bool var4 = Arrays.stream(var0.players).anyMatch(var1x -> var1x.getOnlineID() == var3.getOnlineID());
      if (!var4 && ServerOptions.instance.AntiCheatProtectionType6.getValue() && checkUser(var0)) {
         doKickUser(var0, var2, "Type6", var3.getUsername());
      }

    return var4;
   }

    static bool checkSafehouseAuth(UdpConnection var0, const std::string& var1, const std::string& var2) {
    bool var3 = StringUtils.isNullOrEmpty(var1) || var1 == var0.username) || var0.accessLevel >= 16;
      if (!var3 && ServerOptions.instance.AntiCheatProtectionType7.getValue() && checkUser(var0)) {
         doKickUser(var0, var2, "Type7", var1);
      }

    return var3;
   }

    static bool checkShortDistance(UdpConnection var0, IPositional var1, IPositional var2, const std::string& var3) {
    float var4 = IsoUtils.DistanceTo(var2.getX(), var2.getY(), var1.getX(), var1.getY());
    bool var5 = var4 <= 10.0 * ServerOptions.instance.AntiCheatProtectionType3ThresholdMultiplier.getValue();
      if (!var5 && ServerOptions.instance.AntiCheatProtectionType3.getValue() && checkUser(var0)) {
         doKickUser(var0, var3, "Type3", std::string.valueOf(var4));
      }

    return var5;
   }

    static bool isUntouchable(UdpConnection var0) {
      return !var0.isFullyConnected()
         || PlayerType.isPrivileged(var0.accessLevel)
         || Arrays.stream(var0.players).filter(Objects::nonNull).anyMatch(IsoGameCharacter::isGodMod);
   }

    static bool checkUser(UdpConnection var0) {
    return doAntiCheatProtection();
   }

    bool checkSuspiciousActivity(const std::string& var1) {
      if (this.suspiciousActivityCounter <= 4) {
         this.suspiciousActivityCounter++;
         this.suspiciousActivityDescription = std::string.format("player=\"%s\" type=\"%s\"", this.connection.username, var1);
         DebugLog.Multiplayer.noise("SuspiciousActivity increase: counter=%d %s", this.suspiciousActivityCounter, this.suspiciousActivityDescription);
      }

      return this.suspiciousActivityCounter > 4;
   }

    void updateSuspiciousActivityCounter() {
      if (this.suspiciousActivityCounter > 0) {
         this.suspiciousActivityCounter--;
         DebugLog.Multiplayer
            .warn("SuspiciousActivity decrease: counter=%d %s", new Object[]{this.suspiciousActivityCounter, this.suspiciousActivityDescription});
      } else {
         this.suspiciousActivityCounter = 0;
      }
   }

    static void doLogUser(UdpConnection var0, UserlogType var1, const std::string& var2, const std::string& var3) {
    long var4 = System.currentTimeMillis();
      DebugLog.Multiplayer.warn("Log: player=\"%s\" type=\"%s\" issuer=\"%s\"", new Object[]{var0.username, var2, var3});
      if (var4 > var0.lastUnauthorizedPacket) {
         var0.lastUnauthorizedPacket = var4 + 1000L;
         ServerWorldDatabase.instance.addUserlog(var0.username, var1, var2, "AntiCheat" + var3, 1);
      }
   }

    static void doKickUser(UdpConnection var0, const std::string& var1, const std::string& var2, const std::string& var3) {
      ServerWorldDatabase.instance.addUserlog(var0.username, UserlogType.Kicked, var1, "AntiCheat" + var2, 1);
      DebugLog.Multiplayer.warn("Kick: player=\"%s\" type=\"%s\" issuer=\"%s\" description=\"%s\"", new Object[]{var0.username, var1, var2, var3});
      GameServer.kick(var0, "UI_Policy_Kick", var2);
      var0.forceDisconnect(var1);
      GameServer.addDisconnect(var0);
   }

    static void doBanUser(UdpConnection var0, const std::string& var1, const std::string& var2) {
      ServerWorldDatabase.instance.addUserlog(var0.username, UserlogType.Banned, var1, "AntiCheat" + var2, 1);
      DebugLog.Multiplayer.warn("Ban: player=\"%s\" type=\"%s\" issuer=\"%s\"", new Object[]{var0.username, var1, var2});
      ServerWorldDatabase.instance.banUser(var0.username, true);
      if (SteamUtils.isSteamModeEnabled()) {
    std::string var3 = SteamUtils.convertSteamIDToString(var0.steamID);
         ServerWorldDatabase.instance.banSteamID(var3, var1, true);
      } else {
         ServerWorldDatabase.instance.banIp(var0.ip, var0.username, var1, true);
      }

      GameServer.kick(var0, "UI_Policy_Ban", var2);
      var0.forceDisconnect(var1);
      GameServer.addDisconnect(var0);
   }

    static bool checkPVP(IsoGameCharacter var0, IsoMovingObject var1) {
    IsoPlayer var2 = (IsoPlayer)Type.tryCastTo(var0, IsoPlayer.class);
    IsoPlayer var3 = (IsoPlayer)Type.tryCastTo(var1, IsoPlayer.class);
      if (var3 != nullptr) {
         if (var3.isGodMod()
            || !ServerOptions.instance.PVP.getValue()
            || ServerOptions.instance.SafetySystem.getValue() && var0.getSafety().isEnabled() && ((IsoGameCharacter)var1).getSafety().isEnabled()) {
    return false;
         }

         if (NonPvpZone.getNonPvpZone((int)var1.getX(), (int)var1.getY()) != nullptr) {
    return false;
         }

         if (var2 != nullptr && NonPvpZone.getNonPvpZone((int)var0.getX(), (int)var0.getY()) != nullptr) {
    return false;
         }

         if (var2 != nullptr && !var2.factionPvp && !var3.factionPvp) {
    Faction var4 = Faction.getPlayerFaction(var2);
    Faction var5 = Faction.getPlayerFaction(var3);
            if (var5 != nullptr && var4 == var5) {
    return false;
            }
         }
      }

    return true;
   }

    static bool doAntiCheatProtection() {
      return !GameServer.bCoop && (!Core.bDebug || SystemDisabler.doKickInDebug);
   }

    std::string getDescription() {
    std::stringstream var1 = new std::stringstream("Recipes CRC details");
      if (GameServer.bServer) {
         Set var2 = this.details
            .entrySet()
            .stream()
            .filter(var1x -> this.detailsFromClient.get(var1x.getKey()) != nullptr && this.detailsFromClient.get(var1x.getKey()).crc == var1x.getValue().crc)
            .map(Entry::getKey)
            .collect(Collectors.toSet());
         var2.forEach(var1x -> {
            this.detailsFromClient.remove(var1x);
            this.details.remove(var1x);
         });
         var1.append("\nServer start size=").append(this.details.size());
         this.details.values().forEach(var1x -> var1.append(var1x.getDescription()));
         var1.append("\nServer end\nClient start size=").append(this.detailsFromClient.size());
         this.detailsFromClient.values().forEach(var1x -> var1.append(var1x.getDescription()));
         var1.append("\nClient end");
      }

      return var1;
   }
}
} // namespace network
} // namespace zombie
