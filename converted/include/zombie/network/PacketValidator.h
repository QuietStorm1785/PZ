#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameWindow.h"
#include "zombie/SystemDisabler.h"
#include "zombie/characters/Faction.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/characters/IsoZombie.h"
#include "zombie/characters/SafetySystemManager.h"
#include "zombie/commands/PlayerType.h"
#include "zombie/core/Core.h"
#include "zombie/core/Rand.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/core/utils/UpdateLimit.h"
#include "zombie/core/znet/SteamUtils.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/iso/IsoMovingObject.h"
#include "zombie/iso/IsoUtils.h"
#include "zombie/iso/areas/NonPvpZone.h"
#include "zombie/network/packets/hit/Character.h"
#include "zombie/network/packets/hit/Hit.h"
#include "zombie/network/packets/hit/IMovable.h"
#include "zombie/network/packets/hit/IPositional.h"
#include "zombie/network/packets/hit/Player.h"
#include "zombie/network/packets/hit/Zombie.h"
#include "zombie/scripting/objects/Recipe.h"
#include "zombie/util/StringUtils.h"
#include "zombie/util/Type.h"
#include <algorithm>
#include <filesystem>

namespace zombie {
namespace network {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class PacketValidator {
public:
 static const int SUSPICIOUS_ACTIVITIES_MAX = 4;
 const UpdateLimit ulSuspiciousActivity = new UpdateLimit(150000L);
 public HashMap<String, PacketValidator.RecipeDetails> details = std::make_unique<HashMap<>>();
 public HashMap<String, PacketValidator.RecipeDetails> detailsFromClient = std::make_unique<HashMap<>>();
 bool failed = false;
 static const long USER_LOG_INTERVAL_MS = 1000L;
 static const int MAX_TYPE_3 = 10;
 static const int MAX_TYPE_4 = 101;
 const UdpConnection connection;
 const UpdateLimit ulTimeMultiplier = new UpdateLimit(this->getTimeMultiplierTimeout());
 const UpdateLimit ulRecipeChecksumInterval = new UpdateLimit(this->getChecksumInterval());
 const UpdateLimit ulRecipeChecksumTimeout = new UpdateLimit(this->getChecksumTimeout());
 int salt;
 int suspiciousActivityCounter;
 std::string suspiciousActivityDescription;

 public PacketValidator(UdpConnection udpConnection) {
 this->connection = udpConnection;
 this->suspiciousActivityCounter = 0;
 }

 void reset() {
 this->salt = Rand.Next(Integer.MAX_VALUE);
 }

 bool isReady() {
 IsoPlayer player = GameServer.getPlayerByRealUserName(this->connection.username);
 return this->connection.isFullyConnected()
 && this->connection.isConnectionGraceIntervalTimeout()
 && !GameServer.bFastForward
 && player != nullptr
 && player.isAlive();
 }

 int getSalt() {
 return this->salt;
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
 if (ServerOptions.instance.AntiCheatProtectionType21.getValue() && checkUser(this->connection) {
 DebugLog.Multiplayer.warn("Checksum fail for \"%s\" (Type21)", this->connection.username);
 this->failed = true;
 }

 this->ulRecipeChecksumTimeout.Reset(this->getChecksumDelay());
 }

 bool isFailed() {
 return this->failed;
 }

 void timeoutChecksum() {
 if (this->failed) {
 doKickUser(this->connection, this->getClass().getSimpleName(), "Type21", this->getDescription());
 } else {
 if (ServerOptions.instance.AntiCheatProtectionType22.getValue() && checkUser(this->connection) {
 doKickUser(this->connection, this->getClass().getSimpleName(), "Type22", nullptr);
 }

 this->ulRecipeChecksumTimeout.Reset(this->getChecksumTimeout());
 }
 }

 void successChecksum() {
 this->ulRecipeChecksumTimeout.Reset(this->getChecksumTimeout());
 }

 void sendChecksum(bool boolean0, bool boolean1, bool boolean2) {
 this->salt = Rand.Next(Integer.MAX_VALUE);
 GameServer.sendValidatePacket(this->connection, boolean0, boolean1, boolean2);
 this->ulRecipeChecksumInterval.Reset(this->getChecksumInterval());
 }

 long getTimeMultiplierTimeout() {
 return (long)(10000.0 * ServerOptions.getInstance().AntiCheatProtectionType24ThresholdMultiplier.getValue());
 }

 void failTimeMultiplier(float float0) {
 if (ServerOptions.instance.AntiCheatProtectionType23.getValue() && checkUser(this->connection) {
 doKickUser(this->connection, this->getClass().getSimpleName(), "Type23", String.valueOf(float0);
 }

 this->ulTimeMultiplier.Reset(this->getTimeMultiplierTimeout());
 }

 void timeoutTimeMultiplier() {
 if (ServerOptions.instance.AntiCheatProtectionType24.getValue() && checkUser(this->connection) {
 doKickUser(this->connection, this->getClass().getSimpleName(), "Type24", nullptr);
 }

 this->ulTimeMultiplier.Reset(this->getTimeMultiplierTimeout());
 }

 void successTimeMultiplier() {
 this->ulTimeMultiplier.Reset(this->getTimeMultiplierTimeout());
 }

 void update() {
 if (GameServer.bServer) {
 if (this->ulSuspiciousActivity.Check()) {
 this->updateSuspiciousActivityCounter();
 }

 if (this->isReady()) {
 if (!this->failed && this->ulRecipeChecksumInterval.Check()) {
 this->sendChecksum(false, false, false);
 }

 if (this->ulRecipeChecksumTimeout.Check()) {
 this->timeoutChecksum();
 }

 if (this->ulTimeMultiplier.Check()) {
 this->timeoutTimeMultiplier();
 }
 } else {
 this->ulRecipeChecksumInterval.Reset(this->getChecksumInterval());
 this->ulRecipeChecksumTimeout.Reset(this->getChecksumTimeout());
 this->ulTimeMultiplier.Reset(this->getTimeMultiplierTimeout());
 this->failed = false;
 }
 }
 }

 static bool checkPVP(UdpConnection udpConnection, char character1, char character0, const std::string& string) {
 boolean boolean0 = checkPVP(character1.getCharacter(), character0.getCharacter())
 || SafetySystemManager.checkUpdateDelay(character1.getCharacter(), character0.getCharacter());
 if (!boolean0 && ServerOptions.instance.AntiCheatProtectionType1.getValue() && checkUser(udpConnection) {
 doKickUser(udpConnection, string, "Type1", nullptr);
 }

 return boolean0;
 }

 static bool checkSpeed(UdpConnection udpConnection, IMovable iMovable, const std::string& string) {
 float float0 = iMovable.getSpeed();
 double double0 = iMovable.isVehicle() ? ServerOptions.instance.SpeedLimit.getValue() : 10.0;
 bool boolean0 = float0 <= double0 * ServerOptions.instance.AntiCheatProtectionType2ThresholdMultiplier.getValue();
 if (!boolean0 && ServerOptions.instance.AntiCheatProtectionType2.getValue() && checkUser(udpConnection) {
 doKickUser(udpConnection, string, "Type2", String.valueOf(float0);
 }

 return boolean0;
 }

 static bool checkLongDistance(UdpConnection udpConnection, IPositional iPositional0, IPositional iPositional1, const std::string& string) {
 float float0 = IsoUtils.DistanceTo(iPositional1.getX(), iPositional1.getY(), iPositional0.getX(), iPositional0.getY());
 bool boolean0 = float0 <= udpConnection.ReleventRange * 10 * ServerOptions.instance.AntiCheatProtectionType3ThresholdMultiplier.getValue();
 if (!boolean0 && ServerOptions.instance.AntiCheatProtectionType3.getValue() && checkUser(udpConnection) {
 if (udpConnection.validator.checkSuspiciousActivity("Type3")) {
 doKickUser(udpConnection, string, "Type3", String.valueOf(float0);
 } else {
 doLogUser(udpConnection, Userlog.UserlogType.SuspiciousActivity, string, "Type3");
 }
 }

 return boolean0;
 }

 static bool checkDamage(UdpConnection udpConnection, Hit hit, const std::string& string) {
 float float0 = hit.getDamage();
 bool boolean0 = float0 <= 101.0 * ServerOptions.instance.AntiCheatProtectionType4ThresholdMultiplier.getValue();
 if (!boolean0 && ServerOptions.instance.AntiCheatProtectionType4.getValue() && checkUser(udpConnection) {
 doKickUser(udpConnection, string, "Type4", String.valueOf(float0);
 }

 return boolean0;
 }

 static bool checkOwner(UdpConnection udpConnection1, Zombie zombie1, const std::string& string) {
 IsoZombie zombie0 = (IsoZombie)zombie1.getCharacter();
 UdpConnection udpConnection0 = zombie0.authOwner;
 bool boolean0 = udpConnection0 == udpConnection1 && System.currentTimeMillis() - zombie0.lastChangeOwner > 2000L;
 if (!boolean0 && ServerOptions.instance.AntiCheatProtectionType5.getValue() && checkUser(udpConnection1) {
 if (udpConnection1.validator.checkSuspiciousActivity("Type5")) {
 doKickUser(udpConnection1, string, "Type5", Optional.ofNullable(udpConnection0).map(udpConnection -> udpConnection.username).orElse(""));
 } else {
 doLogUser(udpConnection1, Userlog.UserlogType.SuspiciousActivity, string, "Type5");
 }
 }

 return boolean0;
 }

 static bool checkTarget(UdpConnection udpConnection, Player player1, const std::string& string) {
 IsoPlayer player0 = player1.getPlayer();
 bool boolean0 = Arrays.stream(udpConnection.players).anyMatch(player1x -> player1x.getOnlineID() == player0.getOnlineID());
 if (!boolean0 && ServerOptions.instance.AntiCheatProtectionType6.getValue() && checkUser(udpConnection) {
 doKickUser(udpConnection, string, "Type6", player0.getUsername());
 }

 return boolean0;
 }

 static bool checkSafehouseAuth(UdpConnection udpConnection, const std::string& string0, const std::string& string1) {
 bool boolean0 = StringUtils.isNullOrEmpty(string0) || string0.equals(udpConnection.username) || udpConnection.accessLevel >= 16;
 if (!boolean0 && ServerOptions.instance.AntiCheatProtectionType7.getValue() && checkUser(udpConnection) {
 doKickUser(udpConnection, string1, "Type7", string0);
 }

 return boolean0;
 }

 static bool checkShortDistance(UdpConnection udpConnection, IPositional iPositional0, IPositional iPositional1, const std::string& string) {
 float float0 = IsoUtils.DistanceTo(iPositional1.getX(), iPositional1.getY(), iPositional0.getX(), iPositional0.getY());
 bool boolean0 = float0 <= 10.0 * ServerOptions.instance.AntiCheatProtectionType3ThresholdMultiplier.getValue();
 if (!boolean0 && ServerOptions.instance.AntiCheatProtectionType3.getValue() && checkUser(udpConnection) {
 doKickUser(udpConnection, string, "Type3", String.valueOf(float0);
 }

 return boolean0;
 }

 static bool isUntouchable(UdpConnection udpConnection) {
 return !udpConnection.isFullyConnected()
 || PlayerType.isPrivileged(udpConnection.accessLevel)
 || Arrays.stream(udpConnection.players).filter(Objects::nonNull).anyMatch(IsoGameCharacter::isGodMod);
 }

 static bool checkUser(UdpConnection udpConnection) {
 return doAntiCheatProtection();
 }

 bool checkSuspiciousActivity(const std::string& string) {
 if (this->suspiciousActivityCounter <= 4) {
 this->suspiciousActivityCounter++;
 this->suspiciousActivityDescription = String.format("player=\"%s\" type=\"%s\"", this->connection.username, string);
 DebugLog.Multiplayer.noise("SuspiciousActivity increase: counter=%d %s", this->suspiciousActivityCounter, this->suspiciousActivityDescription);
 }

 return this->suspiciousActivityCounter > 4;
 }

 void updateSuspiciousActivityCounter() {
 if (this->suspiciousActivityCounter > 0) {
 this->suspiciousActivityCounter--;
 DebugLog.Multiplayer.warn("SuspiciousActivity decrease: counter=%d %s", this->suspiciousActivityCounter, this->suspiciousActivityDescription);
 } else {
 this->suspiciousActivityCounter = 0;
 }
 }

 static void doLogUser(UdpConnection udpConnection, Userlog.UserlogType userlogType, const std::string& string0, const std::string& string1) {
 long long0 = System.currentTimeMillis();
 DebugLog.Multiplayer.warn("Log: player=\"%s\" type=\"%s\" issuer=\"%s\"", udpConnection.username, string0, string1);
 if (long0 > udpConnection.lastUnauthorizedPacket) {
 udpConnection.lastUnauthorizedPacket = long0 + 1000L;
 ServerWorldDatabase.instance.addUserlog(udpConnection.username, userlogType, string0, "AntiCheat" + string1, 1);
 }
 }

 static void doKickUser(UdpConnection udpConnection, const std::string& string0, const std::string& string1, const std::string& string2) {
 ServerWorldDatabase.instance.addUserlog(udpConnection.username, Userlog.UserlogType.Kicked, string0, "AntiCheat" + string1, 1);
 DebugLog.Multiplayer.warn("Kick: player=\"%s\" type=\"%s\" issuer=\"%s\" description=\"%s\"", udpConnection.username, string0, string1, string2);
 GameServer.kick(udpConnection, "UI_Policy_Kick", string1);
 udpConnection.forceDisconnect(string0);
 GameServer.addDisconnect(udpConnection);
 }

 static void doBanUser(UdpConnection udpConnection, const std::string& string0, const std::string& string1) {
 ServerWorldDatabase.instance.addUserlog(udpConnection.username, Userlog.UserlogType.Banned, string0, "AntiCheat" + string1, 1);
 DebugLog.Multiplayer.warn("Ban: player=\"%s\" type=\"%s\" issuer=\"%s\"", udpConnection.username, string0, string1);
 ServerWorldDatabase.instance.banUser(udpConnection.username, true);
 if (SteamUtils.isSteamModeEnabled()) {
 std::string string2 = SteamUtils.convertSteamIDToString(udpConnection.steamID);
 ServerWorldDatabase.instance.banSteamID(string2, string0, true);
 } else {
 ServerWorldDatabase.instance.banIp(udpConnection.ip, udpConnection.username, string0, true);
 }

 GameServer.kick(udpConnection, "UI_Policy_Ban", string1);
 udpConnection.forceDisconnect(string0);
 GameServer.addDisconnect(udpConnection);
 }

 static bool checkPVP(IsoGameCharacter character, IsoMovingObject movingObject) {
 IsoPlayer player0 = Type.tryCastTo(character, IsoPlayer.class);
 IsoPlayer player1 = Type.tryCastTo(movingObject, IsoPlayer.class);
 if (player1 != nullptr) {
 if (player1.isGodMod()
 || !ServerOptions.instance.PVP.getValue()
 || ServerOptions.instance.SafetySystem.getValue()
 && character.getSafety().isEnabled()
 && ((IsoGameCharacter)movingObject).getSafety().isEnabled()) {
 return false;
 }

 if (NonPvpZone.getNonPvpZone((int)movingObject.getX(), (int)movingObject.getY()) != nullptr) {
 return false;
 }

 if (player0 != nullptr && NonPvpZone.getNonPvpZone((int)character.getX(), (int)character.getY()) != nullptr) {
 return false;
 }

 if (player0 != nullptr && !player0.factionPvp && !player1.factionPvp) {
 Faction faction0 = Faction.getPlayerFaction(player0);
 Faction faction1 = Faction.getPlayerFaction(player1);
 if (faction1 != nullptr && faction0 == faction1) {
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
 StringBuilder stringBuilder = new StringBuilder("Recipes CRC details");
 if (GameServer.bServer) {
 Set set = this->details
 .entrySet()
 .stream()
 .filter(entry -> this->detailsFromClient.get(entry.getKey()) != nullptr && this->detailsFromClient.get(entry.getKey()).crc == entry.getValue().crc)
 .map(Entry::getKey)
 .collect(Collectors.toSet());
 set.forEach(string -> {
 this->detailsFromClient.remove(string);
 this->details.remove(string);
 });
 stringBuilder.append("\nServer start size=").append(this->details.size());
 this->details.values().forEach(recipeDetails -> stringBuilder.append(recipeDetails.getDescription()));
 stringBuilder.append("\nServer end\nClient start size=").append(this->detailsFromClient.size());
 this->detailsFromClient.values().forEach(recipeDetails -> stringBuilder.append(recipeDetails.getDescription()));
 stringBuilder.append("\nClient end");
 }

 return stringBuilder.toString();
 }

 public static enum CheckState {
 None,
 Sent,
 Success;
 }

 public static class RecipeDetails {
 const std::string name;
 const long crc;
 const int timeToMake;
 private ArrayList<PacketValidator.RecipeDetails.Skill> skills = std::make_unique<ArrayList<>>();
 private ArrayList<String> items = std::make_unique<ArrayList<>>();
 const std::string type;
 const std::string module;
 const int count;

 long getCRC() {
 return this->crc;
 }

 public RecipeDetails(
 String string0,
 long long0,
 int int0,
 ArrayList<Recipe.RequiredSkill> arrayList0,
 ArrayList<Recipe.Source> arrayList1,
 String string1,
 String string2,
 int int1
 ) {
 this->name = string0;
 this->crc = long0;
 this->timeToMake = int0;
 this->type = string1;
 this->module = string2;
 this->count = int1;
 if (arrayList0 != nullptr) {
 for (Recipe.RequiredSkill requiredSkill : arrayList0) {
 this->skills.add(new PacketValidator.RecipeDetails.Skill(requiredSkill.getPerk().getName(), requiredSkill.getLevel()));
 }
 }

 for (Recipe.Source source : arrayList1) {
 this->items.addAll(source.getItems());
 }
 }

 public RecipeDetails(ByteBuffer byteBuffer) {
 this->name = GameWindow.ReadString(byteBuffer);
 this->crc = byteBuffer.getLong();
 this->timeToMake = byteBuffer.getInt();
 this->type = GameWindow.ReadString(byteBuffer);
 this->module = GameWindow.ReadString(byteBuffer);
 this->count = byteBuffer.getInt();
 int int0 = byteBuffer.getInt();

 for (int int1 = 0; int1 < int0; int1++) {
 this->items.add(GameWindow.ReadString(byteBuffer);
 }

 int int2 = byteBuffer.getInt();

 for (int int3 = 0; int3 < int2; int3++) {
 this->skills.add(new PacketValidator.RecipeDetails.Skill(GameWindow.ReadString(byteBuffer), byteBuffer.getInt()));
 }
 }

 void write(ByteBufferWriter byteBufferWriter) {
 byteBufferWriter.putUTF(this->name);
 byteBufferWriter.putLong(this->crc);
 byteBufferWriter.putInt(this->timeToMake);
 byteBufferWriter.putUTF(this->type);
 byteBufferWriter.putUTF(this->module);
 byteBufferWriter.putInt(this->count);
 byteBufferWriter.putInt(this->items.size());

 for (String string : this->items) {
 byteBufferWriter.putUTF(string);
 }

 byteBufferWriter.putInt(this->skills.size());

 for (PacketValidator.RecipeDetails.Skill skill : this->skills) {
 byteBufferWriter.putUTF(skill.name);
 byteBufferWriter.putInt(skill.value);
 }
 }

 std::string getDescription() {
 return "\n\tRecipe: name=\""
 + this->name
 + "\" crc="
 + this->crc
 + " time="
 + this->timeToMake
 + " type=\""
 + this->type
 + "\" module=\""
 + this->module
 + "\" count="
 + this->count
 + " items=["
 + String.join(",", this->items)
 + "] skills=["
 + this->skills.stream().map(skill -> "\"" + skill.name + "\": " + skill.value).collect(Collectors.joining(","))
 + "]";
 }

 public static class Skill {
 const std::string name;
 const int value;

 public Skill(const std::string& string, int int0) {
 this->name = string;
 this->value = int0;
 }
 }
 }
}
} // namespace network
} // namespace zombie
