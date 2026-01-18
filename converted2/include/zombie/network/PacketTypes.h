#pragma once
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "zombie/Lua/LuaManager.h"
#include "zombie/SystemDisabler.h"
#include "zombie/commands/PlayerType.h"
#include "zombie/core/Core.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/core/znet/SteamUtils.h"
#include "zombie/debug/DebugLog.h"
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
namespace network {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class PacketTypes {
public:
  static const short ContainerDeadBody = 0;
  static const short ContainerWorldObject = 1;
  static const short ContainerObject = 2;
  static const short ContainerVehicle = 3;
public
  static final Map<Short, PacketTypes.PacketType> packetTypes =
      std::make_unique<TreeMap<>>();
  static const KahluaTable packetCountTable = LuaManager.platform.newTable();

  static void doPingPacket(ByteBufferWriter byteBufferWriter) {
    byteBufferWriter.putInt(28);
  }

  static KahluaTable getPacketCounts(int int0) {
    packetCountTable.wipe();
    if (GameClient.bClient) {
      for (PacketTypes.PacketType packetType : packetTypes.values()) {
        if (int0 == 1) {
          packetCountTable.rawset(
              String.format("%03d-%s", packetType.id, packetType.name()),
              String.valueOf(packetType.serverPacketCount));
        } else {
          packetCountTable.rawset(
              String.format("%03d-%s", packetType.id, packetType.name()),
              String.valueOf(packetType.clientPacketCount));
        }
      }
    }

    return packetCountTable;
  }

  static {
    for (PacketTypes.PacketType packetType0 : PacketTypes.PacketType.values()) {
      PacketTypes.PacketType packetType1 =
          packetTypes.put(packetType0.getId(), packetType0);
      if (packetType1 != nullptr) {
        DebugLog.Multiplayer.error(String.format(
            "PacketType: duplicate \"%s\" \"%s\" id=%d", packetType1.name(),
            packetType0.name(), packetType0.getId()));
      }
    }
  }

public
  interface CallbackClientProcess {
    void call(ByteBuffer bb, short packetType);
  }

public
  interface CallbackServerProcess {
    void call(ByteBuffer bb, UdpConnection connection, short packetType);
  }

private
  static class PacketAuthorization {
    static void unauthorizedPacketPolicyLogUser(UdpConnection udpConnection,
                                                const std::string &string) {
      if (ServerOptions.instance.AntiCheatProtectionType8.getValue() &&
          PacketValidator.checkUser(udpConnection)) {
        PacketValidator.doLogUser(udpConnection,
                                  Userlog.UserlogType.UnauthorizedPacket,
                                  string, "Type8");
      }
    }

    static void unauthorizedPacketPolicyKickUser(UdpConnection udpConnection,
                                                 const std::string &string) {
      if (ServerOptions.instance.AntiCheatProtectionType8.getValue() &&
          PacketValidator.checkUser(udpConnection)) {
        PacketValidator.doKickUser(udpConnection, string, "Type8", nullptr);
      }
    }

    static void unauthorizedPacketPolicyBanUser(UdpConnection udpConnection,
                                                const std::string &string) {
      if (ServerOptions.instance.AntiCheatProtectionType8.getValue() &&
          PacketValidator.checkUser(udpConnection)) {
        PacketValidator.doBanUser(udpConnection, string, "Type8");
      }
    }

    static bool isAuthorized(UdpConnection udpConnection,
                             PacketTypes.PacketType packetType) {
      bool boolean0 =
          (udpConnection.accessLevel & packetType.requiredAccessLevel) != 0;
      if ((!boolean0 || packetType.serverProcess == nullptr) &&
          (!Core.bDebug || SystemDisabler.doKickInDebug)) {
        DebugLog.Multiplayer.warn(String.format(
            "Unauthorized packet %s (%s) was received from user=\"%s\" (%s) ip "
            "%s %s",
            packetType.name(),
            PlayerType.toString(packetType.requiredAccessLevel),
            udpConnection.username,
            PlayerType.toString(udpConnection.accessLevel), udpConnection.ip,
            SteamUtils.isSteamModeEnabled() ? udpConnection.steamID : ""));
        packetType.unauthorizedPacketPolicy.apply(udpConnection,
                                                  packetType.name());
      }

      return boolean0;
    }

  public
    static enum Policy {
      Log(PacketTypes.PacketAuthorization::unauthorizedPacketPolicyLogUser),
      Kick(PacketTypes.PacketAuthorization::unauthorizedPacketPolicyKickUser),
      Ban(PacketTypes.PacketAuthorization::unauthorizedPacketPolicyBanUser);

      private final PacketTypes.PacketAuthorization
          .UnauthorizedPacketPolicy policy;

      private Policy(PacketTypes.PacketAuthorization
                         .UnauthorizedPacketPolicy unauthorizedPacketPolicy){
          this.policy = unauthorizedPacketPolicy;}

    void apply(UdpConnection udpConnection, const std::string &string) {
      this.policy.call(udpConnection, string);
    }
  }

  public interface UnauthorizedPacketPolicy {
    void call(UdpConnection var1, const std::string &var2);
  }
}

public static enum PacketType {
  Validate(1, 0, 3, 63, PacketTypes.PacketAuthorization.Policy.Kick,
           GameServer::receiveValidatePacket, GameClient::receiveValidatePacket,
           GameClient::receiveValidatePacket),
  Login(2, 1, 3, 63, PacketTypes.PacketAuthorization.Policy.Kick,
        GameServer::receiveLogin, nullptr, nullptr),
  HumanVisual(3, 1, 2, 63, PacketTypes.PacketAuthorization.Policy.Kick,
              GameServer::receiveHumanVisual, GameClient::receiveHumanVisual,
              nullptr),
  KeepAlive(4, 1, 0, 63, PacketTypes.PacketAuthorization.Policy.Kick,
            GameServer::receiveKeepAlive, GameClient::receiveKeepAlive,
            GameClient::skipPacket),
  Vehicles(5, 1, 2, 63, PacketTypes.PacketAuthorization.Policy.Kick,
           GameServer::receiveVehicles, GameClient::receiveVehicles, nullptr),
  PlayerConnect(6, 1, 3, 63, PacketTypes.PacketAuthorization.Policy.Kick,
                GameServer::receivePlayerConnect,
                GameClient::receivePlayerConnect, nullptr),
  VehiclesUnreliable(7, 2, 0, 63, PacketTypes.PacketAuthorization.Policy.Kick,
                     GameServer::receiveVehicles, GameClient::receiveVehicles,
                     nullptr),
  VehicleAuthorization(8, 2, 3, 0, PacketTypes.PacketAuthorization.Policy.Kick,
                       nullptr, GameClient::receiveVehicleAuthorization,
                       nullptr),
  MetaGrid(9, 1, 2, 0, PacketTypes.PacketAuthorization.Policy.Kick, nullptr,
           GameClient::receiveMetaGrid, nullptr),
  Helicopter(11, 1, 2, 0, PacketTypes.PacketAuthorization.Policy.Kick, nullptr,
             GameClient::receiveHelicopter, nullptr),
  SyncIsoObject(12, 1, 2, 63, PacketTypes.PacketAuthorization.Policy.Kick,
                GameServer::receiveSyncIsoObject,
                GameClient::receiveSyncIsoObject, nullptr),
  PlayerTimeout(13, 1, 2, 0, PacketTypes.PacketAuthorization.Policy.Kick,
                nullptr, GameClient::receivePlayerTimeout,
                GameClient::receivePlayerTimeout),
  ServerMap(15, 1, 3, 0, PacketTypes.PacketAuthorization.Policy.Kick, nullptr,
            GameClient::receiveServerMap, GameClient::receiveServerMapLoading),
  PassengerMap(16, 1, 2, 63, PacketTypes.PacketAuthorization.Policy.Kick,
               GameServer::receivePassengerMap, GameClient::receivePassengerMap,
               nullptr),
  AddItemToMap(17, 1, 2, 63, PacketTypes.PacketAuthorization.Policy.Kick,
               GameServer::receiveAddItemToMap, GameClient::receiveAddItemToMap,
               nullptr),
  SentChunk(18, 1, 2, 0, PacketTypes.PacketAuthorization.Policy.Kick, nullptr,
            nullptr, nullptr),
  SyncClock(19, 1, 2, 0, PacketTypes.PacketAuthorization.Policy.Kick, nullptr,
            GameClient::receiveSyncClock, nullptr),
  AddInventoryItemToContainer(
      20, 1, 2, 63, PacketTypes.PacketAuthorization.Policy.Kick,
      GameServer::receiveAddInventoryItemToContainer,
      GameClient::receiveAddInventoryItemToContainer, nullptr),
  RemoveInventoryItemFromContainer(
      22, 1, 2, 63, PacketTypes.PacketAuthorization.Policy.Kick,
      GameServer::receiveRemoveInventoryItemFromContainer,
      GameClient::receiveRemoveInventoryItemFromContainer, nullptr),
  RemoveItemFromSquare(23, 1, 2, 63,
                       PacketTypes.PacketAuthorization.Policy.Kick,
                       GameServer::receiveRemoveItemFromSquare,
                       GameClient::receiveRemoveItemFromSquare, nullptr),
  RequestLargeAreaZip(24, 1, 2, 63, PacketTypes.PacketAuthorization.Policy.Kick,
                      GameServer::receiveRequestLargeAreaZip, nullptr, nullptr),
  Equip(25, 1, 2, 63, PacketTypes.PacketAuthorization.Policy.Kick,
        GameServer::receiveEquip, GameClient::receiveEquip, nullptr),
  HitCharacter(26, 0, 3, 63, PacketTypes.PacketAuthorization.Policy.Kick,
               GameServer::receiveHitCharacter, GameClient::receiveHitCharacter,
               nullptr),
  AddCoopPlayer(27, 1, 2, 63, PacketTypes.PacketAuthorization.Policy.Kick,
                GameServer::receiveAddCoopPlayer,
                GameClient::receiveAddCoopPlayer, nullptr),
  WeaponHit(28, 1, 2, 63, PacketTypes.PacketAuthorization.Policy.Kick,
            GameServer::receiveWeaponHit, nullptr, nullptr),
  KillZombie(30, 1, 2, 0, PacketTypes.PacketAuthorization.Policy.Kick, nullptr,
             nullptr, nullptr),
  SandboxOptions(31, 1, 2, 32, PacketTypes.PacketAuthorization.Policy.Kick,
                 GameServer::receiveSandboxOptions,
                 GameClient::receiveSandboxOptions, nullptr),
  SmashWindow(32, 1, 2, 63, PacketTypes.PacketAuthorization.Policy.Kick,
              GameServer::receiveSmashWindow, GameClient::receiveSmashWindow,
              nullptr),
  PlayerDeath(33, 0, 3, 63, PacketTypes.PacketAuthorization.Policy.Kick,
              GameServer::receivePlayerDeath, GameClient::receivePlayerDeath,
              nullptr),
  RequestZipList(34, 0, 2, 63, PacketTypes.PacketAuthorization.Policy.Kick,
                 GameServer::receiveRequestZipList, nullptr, nullptr),
  ItemStats(35, 1, 2, 63, PacketTypes.PacketAuthorization.Policy.Kick,
            GameServer::receiveItemStats, GameClient::receiveItemStats,
            nullptr),
  NotRequiredInZip(36, 0, 0, 63, PacketTypes.PacketAuthorization.Policy.Kick,
                   GameServer::receiveNotRequiredInZip, nullptr, nullptr),
  RequestData(37, 1, 2, 63, PacketTypes.PacketAuthorization.Policy.Kick,
              GameServer::receiveRequestData, GameClient::receiveRequestData,
              GameClient::receiveRequestData),
  GlobalObjects(38, 1, 2, 63, PacketTypes.PacketAuthorization.Policy.Kick,
                GameServer::receiveGlobalObjects,
                GameClient::receiveGlobalObjects, nullptr),
  ZombieDeath(39, 1, 3, 63, PacketTypes.PacketAuthorization.Policy.Kick,
              GameServer::receiveZombieDeath, GameClient::receiveZombieDeath,
              nullptr),
  AccessDenied(40, 0, 2, 0, PacketTypes.PacketAuthorization.Policy.Kick,
               nullptr, nullptr, GameClient::receiveAccessDenied),
  PlayerDamage(41, 1, 2, 63, PacketTypes.PacketAuthorization.Policy.Kick,
               GameServer::receivePlayerDamage, GameClient::receivePlayerDamage,
               nullptr),
  Bandage(42, 1, 2, 63, PacketTypes.PacketAuthorization.Policy.Kick,
          GameServer::receiveBandage, GameClient::receiveBandage, nullptr),
  EatFood(43, 1, 2, 63, PacketTypes.PacketAuthorization.Policy.Kick,
          GameServer::receiveEatFood, nullptr, nullptr),
  RequestItemsForContainer(
      44, 1, 2, 63, PacketTypes.PacketAuthorization.Policy.Kick,
      GameServer::receiveRequestItemsForContainer, nullptr, nullptr),
  Drink(45, 1, 2, 63, PacketTypes.PacketAuthorization.Policy.Kick,
        GameServer::receiveDrink, nullptr, nullptr),
  SyncAlarmClock(46, 1, 2, 63, PacketTypes.PacketAuthorization.Policy.Kick,
                 GameServer::receiveSyncAlarmClock,
                 GameClient::receiveSyncAlarmClock, nullptr),
  PacketCounts(47, 1, 2, 62, PacketTypes.PacketAuthorization.Policy.Kick,
               GameServer::receivePacketCounts, GameClient::receivePacketCounts,
               nullptr),
  SendModData(48, 1, 2, 63, PacketTypes.PacketAuthorization.Policy.Kick,
              GameServer::receiveSendModData, nullptr, nullptr),
  RemoveContestedItemsFromInventory(
      49, 1, 2, 0, PacketTypes.PacketAuthorization.Policy.Kick, nullptr,
      GameClient::receiveRemoveContestedItemsFromInventory, nullptr),
  ScoreboardUpdate(50, 1, 2, 63, PacketTypes.PacketAuthorization.Policy.Kick,
                   GameServer::receiveScoreboardUpdate,
                   GameClient::receiveScoreboardUpdate, nullptr),
  ReceiveModData(51, 1, 2, 0, PacketTypes.PacketAuthorization.Policy.Kick,
                 nullptr, GameClient::receiveReceiveModData, nullptr),
  ServerQuit(52, 1, 2, 0, PacketTypes.PacketAuthorization.Policy.Kick, nullptr,
             GameClient::receiveServerQuit, nullptr),
  PlaySound(53, 1, 2, 63, PacketTypes.PacketAuthorization.Policy.Kick,
            GameServer::receivePlaySound, GameClient::receivePlaySound,
            nullptr),
  WorldSound(54, 1, 2, 63, PacketTypes.PacketAuthorization.Policy.Kick,
             GameServer::receiveWorldSound, GameClient::receiveWorldSound,
             nullptr),
  AddAmbient(55, 1, 2, 0, PacketTypes.PacketAuthorization.Policy.Kick, nullptr,
             GameClient::receiveAddAmbient, nullptr),
  SyncClothing(56, 1, 2, 63, PacketTypes.PacketAuthorization.Policy.Kick,
               GameServer::receiveSyncClothing, GameClient::receiveSyncClothing,
               nullptr),
  ClientCommand(57, 1, 2, 63, PacketTypes.PacketAuthorization.Policy.Kick,
                GameServer::receiveClientCommand,
                GameClient::receiveClientCommand, nullptr),
  ObjectModData(58, 2, 2, 63, PacketTypes.PacketAuthorization.Policy.Kick,
                GameServer::receiveObjectModData,
                GameClient::receiveObjectModData, nullptr),
  ObjectChange(59, 1, 2, 0, PacketTypes.PacketAuthorization.Policy.Kick,
               nullptr, GameClient::receiveObjectChange, nullptr),
  BloodSplatter(60, 1, 2, 0, PacketTypes.PacketAuthorization.Policy.Kick,
                nullptr, GameClient::receiveBloodSplatter, nullptr),
  ZombieSound(61, 1, 2, 0, PacketTypes.PacketAuthorization.Policy.Kick, nullptr,
              GameClient::receiveZombieSound, nullptr),
  ZombieDescriptors(62, 1, 2, 0, PacketTypes.PacketAuthorization.Policy.Kick,
                    nullptr, GameClient::receiveZombieDescriptors, nullptr),
  SlowFactor(63, 1, 2, 0, PacketTypes.PacketAuthorization.Policy.Kick, nullptr,
             GameClient::receiveSlowFactor, nullptr),
  Weather(64, 1, 2, 0, PacketTypes.PacketAuthorization.Policy.Kick, nullptr,
          GameClient::receiveWeather, nullptr),
  WorldMapPlayerPosition(65, 3, 1, 63,
                         PacketTypes.PacketAuthorization.Policy.Kick,
                         GameServer::receiveWorldMapPlayerPosition,
                         GameClient::receiveWorldMapPlayerPosition, nullptr),
  RequestPlayerData(67, 1, 2, 0, PacketTypes.PacketAuthorization.Policy.Kick,
                    GameServer::receiveRequestPlayerData, nullptr, nullptr),
  RemoveCorpseFromMap(68, 1, 2, 63, PacketTypes.PacketAuthorization.Policy.Kick,
                      GameServer::receiveRemoveCorpseFromMap,
                      GameClient::receiveRemoveCorpseFromMap, nullptr),
  AddCorpseToMap(69, 1, 3, 63, PacketTypes.PacketAuthorization.Policy.Kick,
                 GameServer::receiveAddCorpseToMap,
                 GameClient::receiveAddCorpseToMap, nullptr),
  BecomeCorpse(70, 1, 3, 63, PacketTypes.PacketAuthorization.Policy.Kick,
               nullptr, GameClient::receiveBecomeCorpse, nullptr),
  StartFire(75, 1, 2, 0, PacketTypes.PacketAuthorization.Policy.Kick,
            GameServer::receiveStartFire, GameClient::receiveStartFire,
            nullptr),
  UpdateItemSprite(76, 1, 2, 63, PacketTypes.PacketAuthorization.Policy.Kick,
                   GameServer::receiveUpdateItemSprite,
                   GameClient::receiveUpdateItemSprite, nullptr),
  StartRain(77, 1, 2, 0, PacketTypes.PacketAuthorization.Policy.Kick, nullptr,
            GameClient::receiveStartRain, nullptr),
  StopRain(78, 1, 2, 0, PacketTypes.PacketAuthorization.Policy.Kick, nullptr,
           GameClient::receiveStopRain, nullptr),
  WorldMessage(79, 1, 2, 56, PacketTypes.PacketAuthorization.Policy.Kick,
               GameServer::receiveWorldMessage, GameClient::receiveWorldMessage,
               nullptr),
  getModData(80, 1, 2, 63, PacketTypes.PacketAuthorization.Policy.Kick,
             GameServer::receiveGetModData, nullptr, nullptr),
  ReceiveCommand(81, 2, 3, 63, PacketTypes.PacketAuthorization.Policy.Kick,
                 GameServer::receiveReceiveCommand, nullptr, nullptr),
  ReloadOptions(82, 1, 2, 0, PacketTypes.PacketAuthorization.Policy.Kick,
                nullptr, GameClient::receiveReloadOptions, nullptr),
  Kicked(83, 0, 2, 0, PacketTypes.PacketAuthorization.Policy.Kick, nullptr,
         GameClient::receiveKicked, GameClient::receiveKicked),
  ExtraInfo(84, 1, 2, 62, PacketTypes.PacketAuthorization.Policy.Kick,
            GameServer::receiveExtraInfo, GameClient::receiveExtraInfo,
            nullptr),
  AddItemInInventory(85, 1, 2, 0, PacketTypes.PacketAuthorization.Policy.Kick,
                     nullptr, GameClient::receiveAddItemInInventory, nullptr),
  ChangeSafety(86, 1, 2, 63, PacketTypes.PacketAuthorization.Policy.Kick,
               GameServer::receiveChangeSafety, GameClient::receiveChangeSafety,
               nullptr),
  Ping(87, 0, 0, 63, PacketTypes.PacketAuthorization.Policy.Kick,
       GameServer::receivePing, GameClient::receivePing,
       GameClient::receivePing),
  WriteLog(88, 1, 2, 0, PacketTypes.PacketAuthorization.Policy.Kick,
           GameServer::receiveWriteLog, nullptr, nullptr),
  AddXP(89, 1, 2, 63, PacketTypes.PacketAuthorization.Policy.Kick,
        GameServer::receiveAddXp, GameClient::receiveAddXp, nullptr),
  UpdateOverlaySprite(90, 1, 2, 63, PacketTypes.PacketAuthorization.Policy.Kick,
                      GameServer::receiveUpdateOverlaySprite,
                      GameClient::receiveUpdateOverlaySprite, nullptr),
  Checksum(91, 1, 3, 63, PacketTypes.PacketAuthorization.Policy.Kick,
           GameServer::receiveChecksum, GameClient::receiveChecksum,
           GameClient::receiveChecksumLoading),
  ConstructedZone(92, 1, 2, 63, PacketTypes.PacketAuthorization.Policy.Kick,
                  GameServer::receiveConstructedZone,
                  GameClient::receiveConstructedZone, nullptr),
  RegisterZone(94, 1, 2, 63, PacketTypes.PacketAuthorization.Policy.Kick,
               GameServer::receiveRegisterZone, GameClient::receiveRegisterZone,
               nullptr),
  WoundInfection(97, 1, 2, 0, PacketTypes.PacketAuthorization.Policy.Kick,
                 GameServer::receiveWoundInfection,
                 GameClient::receiveWoundInfection, nullptr),
  Stitch(98, 1, 2, 63, PacketTypes.PacketAuthorization.Policy.Kick,
         GameServer::receiveStitch, GameClient::receiveStitch, nullptr),
  Disinfect(99, 1, 2, 63, PacketTypes.PacketAuthorization.Policy.Kick,
            GameServer::receiveDisinfect, GameClient::receiveDisinfect,
            nullptr),
  AdditionalPain(100, 1, 2, 0, PacketTypes.PacketAuthorization.Policy.Kick,
                 nullptr, GameClient::receiveAdditionalPain, nullptr),
  RemoveGlass(101, 1, 2, 63, PacketTypes.PacketAuthorization.Policy.Kick,
              GameServer::receiveRemoveGlass, GameClient::receiveRemoveGlass,
              nullptr),
  Splint(102, 1, 2, 63, PacketTypes.PacketAuthorization.Policy.Kick,
         GameServer::receiveSplint, GameClient::receiveSplint, nullptr),
  RemoveBullet(103, 1, 2, 63, PacketTypes.PacketAuthorization.Policy.Kick,
               GameServer::receiveRemoveBullet, GameClient::receiveRemoveBullet,
               nullptr),
  CleanBurn(104, 1, 2, 63, PacketTypes.PacketAuthorization.Policy.Kick,
            GameServer::receiveCleanBurn, GameClient::receiveCleanBurn,
            nullptr),
  SyncThumpable(105, 1, 2, 63, PacketTypes.PacketAuthorization.Policy.Kick,
                GameServer::receiveSyncThumpable,
                GameClient::receiveSyncThumpable, nullptr),
  SyncDoorKey(106, 1, 2, 63, PacketTypes.PacketAuthorization.Policy.Kick,
              GameServer::receiveSyncDoorKey, GameClient::receiveSyncDoorKey,
              nullptr),
  AddXpCommand(107, 1, 2, 0, PacketTypes.PacketAuthorization.Policy.Kick,
               nullptr, GameClient::receiveAddXpCommand, nullptr),
  Teleport(108, 1, 2, 62, PacketTypes.PacketAuthorization.Policy.Kick,
           GameServer::receiveTeleport, GameClient::receiveTeleport, nullptr),
  RemoveBlood(109, 1, 2, 63, PacketTypes.PacketAuthorization.Policy.Kick,
              GameServer::receiveRemoveBlood, GameClient::receiveRemoveBlood,
              nullptr),
  AddExplosiveTrap(110, 1, 2, 63, PacketTypes.PacketAuthorization.Policy.Kick,
                   GameServer::receiveAddExplosiveTrap,
                   GameClient::receiveAddExplosiveTrap, nullptr),
  BodyDamageUpdate(112, 1, 2, 63, PacketTypes.PacketAuthorization.Policy.Kick,
                   GameServer::receiveBodyDamageUpdate,
                   GameClient::receiveBodyDamageUpdate, nullptr),
  SyncSafehouse(114, 1, 2, 63, PacketTypes.PacketAuthorization.Policy.Kick,
                GameServer::receiveSyncSafehouse,
                GameClient::receiveSyncSafehouse, nullptr),
  SledgehammerDestroy(115, 1, 2, 63,
                      PacketTypes.PacketAuthorization.Policy.Kick,
                      GameServer::receiveSledgehammerDestroy, nullptr, nullptr),
  StopFire(116, 1, 2, 63, PacketTypes.PacketAuthorization.Policy.Kick,
           GameServer::receiveStopFire, GameClient::receiveStopFire, nullptr),
  Cataplasm(117, 1, 2, 63, PacketTypes.PacketAuthorization.Policy.Kick,
            GameServer::receiveCataplasm, GameClient::receiveCataplasm,
            nullptr),
  AddAlarm(118, 1, 2, 0, PacketTypes.PacketAuthorization.Policy.Kick, nullptr,
           GameClient::receiveAddAlarm, nullptr),
  PlaySoundEveryPlayer(119, 1, 2, 0,
                       PacketTypes.PacketAuthorization.Policy.Kick, nullptr,
                       GameClient::receivePlaySoundEveryPlayer, nullptr),
  SyncFurnace(120, 1, 2, 63, PacketTypes.PacketAuthorization.Policy.Kick,
              GameServer::receiveSyncFurnace, GameClient::receiveSyncFurnace,
              nullptr),
  SendCustomColor(121, 1, 2, 63, PacketTypes.PacketAuthorization.Policy.Kick,
                  GameServer::receiveSendCustomColor,
                  GameClient::receiveSendCustomColor, nullptr),
  SyncCompost(122, 1, 2, 63, PacketTypes.PacketAuthorization.Policy.Kick,
              GameServer::receiveSyncCompost, GameClient::receiveSyncCompost,
              nullptr),
  ChangePlayerStats(123, 1, 2, 63, PacketTypes.PacketAuthorization.Policy.Kick,
                    GameServer::receiveChangePlayerStats,
                    GameClient::receiveChangePlayerStats, nullptr),
  AddXpFromPlayerStatsUI(
      124, 1, 2, 0, PacketTypes.PacketAuthorization.Policy.Kick,
      GameServer::receiveAddXp, GameClient::receiveAddXp, nullptr),
  SyncXP(126, 1, 2, 63, PacketTypes.PacketAuthorization.Policy.Kick,
         GameServer::receiveSyncXP, GameClient::receiveSyncXP, nullptr),
  PacketTypeShort(127, 1, 2, 0, PacketTypes.PacketAuthorization.Policy.Kick,
                  nullptr, nullptr, nullptr),
  Userlog(128, 1, 2, 62, PacketTypes.PacketAuthorization.Policy.Kick,
          GameServer::receiveUserlog, GameClient::receiveUserlog, nullptr),
  AddUserlog(129, 1, 2, 62, PacketTypes.PacketAuthorization.Policy.Kick,
             GameServer::receiveAddUserlog, nullptr, nullptr),
  RemoveUserlog(130, 1, 2, 56, PacketTypes.PacketAuthorization.Policy.Kick,
                GameServer::receiveRemoveUserlog, nullptr, nullptr),
  AddWarningPoint(131, 1, 2, 56, PacketTypes.PacketAuthorization.Policy.Kick,
                  GameServer::receiveAddWarningPoint, nullptr, nullptr),
  MessageForAdmin(132, 1, 2, 0, PacketTypes.PacketAuthorization.Policy.Kick,
                  nullptr, GameClient::receiveMessageForAdmin, nullptr),
  WakeUpPlayer(133, 1, 2, 63, PacketTypes.PacketAuthorization.Policy.Kick,
               GameServer::receiveWakeUpPlayer, GameClient::receiveWakeUpPlayer,
               nullptr),
  SendTransactionID(134, 1, 2, 0, PacketTypes.PacketAuthorization.Policy.Kick,
                    nullptr, nullptr, nullptr),
  GetDBSchema(135, 1, 2, 60, PacketTypes.PacketAuthorization.Policy.Kick,
              GameServer::receiveGetDBSchema, GameClient::receiveGetDBSchema,
              nullptr),
  GetTableResult(136, 1, 2, 60, PacketTypes.PacketAuthorization.Policy.Kick,
                 GameServer::receiveGetTableResult,
                 GameClient::receiveGetTableResult, nullptr),
  ExecuteQuery(137, 1, 2, 32, PacketTypes.PacketAuthorization.Policy.Kick,
               GameServer::receiveExecuteQuery, nullptr, nullptr),
  ChangeTextColor(138, 1, 2, 63, PacketTypes.PacketAuthorization.Policy.Kick,
                  GameServer::receiveChangeTextColor,
                  GameClient::receiveChangeTextColor, nullptr),
  SyncNonPvpZone(139, 1, 2, 32, PacketTypes.PacketAuthorization.Policy.Kick,
                 GameServer::receiveSyncNonPvpZone,
                 GameClient::receiveSyncNonPvpZone, nullptr),
  SyncFaction(140, 1, 2, 63, PacketTypes.PacketAuthorization.Policy.Kick,
              GameServer::receiveSyncFaction, GameClient::receiveSyncFaction,
              nullptr),
  SendFactionInvite(141, 1, 2, 63, PacketTypes.PacketAuthorization.Policy.Kick,
                    GameServer::receiveSendFactionInvite,
                    GameClient::receiveSendFactionInvite, nullptr),
  AcceptedFactionInvite(142, 1, 2, 63,
                        PacketTypes.PacketAuthorization.Policy.Kick,
                        GameServer::receiveAcceptedFactionInvite,
                        GameClient::receiveAcceptedFactionInvite, nullptr),
  AddTicket(143, 1, 2, 63, PacketTypes.PacketAuthorization.Policy.Kick,
            GameServer::receiveAddTicket, nullptr, nullptr),
  ViewTickets(144, 1, 2, 63, PacketTypes.PacketAuthorization.Policy.Kick,
              GameServer::receiveViewTickets, GameClient::receiveViewTickets,
              nullptr),
  RemoveTicket(145, 1, 2, 62, PacketTypes.PacketAuthorization.Policy.Kick,
               GameServer::receiveRemoveTicket, nullptr, nullptr),
  RequestTrading(146, 1, 2, 63, PacketTypes.PacketAuthorization.Policy.Kick,
                 GameServer::receiveRequestTrading,
                 GameClient::receiveRequestTrading, nullptr),
  TradingUIAddItem(147, 1, 2, 63, PacketTypes.PacketAuthorization.Policy.Kick,
                   GameServer::receiveTradingUIAddItem,
                   GameClient::receiveTradingUIAddItem, nullptr),
  TradingUIRemoveItem(148, 1, 2, 63,
                      PacketTypes.PacketAuthorization.Policy.Kick,
                      GameServer::receiveTradingUIRemoveItem,
                      GameClient::receiveTradingUIRemoveItem, nullptr),
  TradingUIUpdateState(149, 1, 2, 63,
                       PacketTypes.PacketAuthorization.Policy.Kick,
                       GameServer::receiveTradingUIUpdateState,
                       GameClient::receiveTradingUIUpdateState, nullptr),
  SendItemListNet(150, 1, 2, 0, PacketTypes.PacketAuthorization.Policy.Kick,
                  GameServer::receiveSendItemListNet,
                  GameClient::receiveSendItemListNet, nullptr),
  ChunkObjectState(151, 1, 2, 63, PacketTypes.PacketAuthorization.Policy.Kick,
                   GameServer::receiveChunkObjectState,
                   GameClient::receiveChunkObjectState, nullptr),
  ReadAnnotedMap(152, 1, 2, 63, PacketTypes.PacketAuthorization.Policy.Kick,
                 GameServer::receiveReadAnnotedMap, nullptr, nullptr),
  RequestInventory(153, 1, 2, 56, PacketTypes.PacketAuthorization.Policy.Kick,
                   GameServer::receiveRequestInventory,
                   GameClient::receiveRequestInventory, nullptr),
  SendInventory(154, 1, 2, 63, PacketTypes.PacketAuthorization.Policy.Kick,
                GameServer::receiveSendInventory,
                GameClient::receiveSendInventory, nullptr),
  InvMngReqItem(155, 1, 2, 56, PacketTypes.PacketAuthorization.Policy.Kick,
                GameServer::receiveInvMngReqItem,
                GameClient::receiveInvMngReqItem, nullptr),
  InvMngGetItem(156, 1, 2, 63, PacketTypes.PacketAuthorization.Policy.Kick,
                GameServer::receiveInvMngGetItem,
                GameClient::receiveInvMngGetItem, nullptr),
  InvMngRemoveItem(157, 1, 2, 56, PacketTypes.PacketAuthorization.Policy.Kick,
                   GameServer::receiveInvMngRemoveItem,
                   GameClient::receiveInvMngRemoveItem, nullptr),
  StartPause(158, 1, 3, 63, PacketTypes.PacketAuthorization.Policy.Kick,
             nullptr, GameClient::receiveStartPause, nullptr),
  StopPause(159, 1, 3, 63, PacketTypes.PacketAuthorization.Policy.Kick, nullptr,
            GameClient::receiveStopPause, nullptr),
  TimeSync(160, 1, 2, 63, PacketTypes.PacketAuthorization.Policy.Kick,
           GameServer::receiveTimeSync, GameClient::receiveTimeSync, nullptr),
  SyncIsoObjectReq(161, 1, 2, 0, PacketTypes.PacketAuthorization.Policy.Kick,
                   GameServer::receiveSyncIsoObjectReq,
                   GameClient::receiveSyncIsoObjectReq, nullptr),
  PlayerSave(162, 1, 2, 0, PacketTypes.PacketAuthorization.Policy.Kick,
             GameServer::receivePlayerSave, nullptr, nullptr),
  SyncWorldObjectsReq(163, 1, 2, 0, PacketTypes.PacketAuthorization.Policy.Kick,
                      nullptr, GameClient::receiveSyncWorldObjectsReq, nullptr),
  SyncObjects(164, 1, 2, 0, PacketTypes.PacketAuthorization.Policy.Kick,
              GameServer::receiveSyncObjects, GameClient::receiveSyncObjects,
              nullptr),
  SendPlayerProfile(166, 1, 3, 63, PacketTypes.PacketAuthorization.Policy.Kick,
                    GameServer::receiveSendPlayerProfile, nullptr, nullptr),
  LoadPlayerProfile(167, 1, 3, 63, PacketTypes.PacketAuthorization.Policy.Kick,
                    GameServer::receiveLoadPlayerProfile,
                    GameClient::receiveLoadPlayerProfile, nullptr),
  SpawnRegion(171, 1, 2, 0, PacketTypes.PacketAuthorization.Policy.Kick,
              nullptr, GameClient::receiveSpawnRegion,
              GameClient::receiveSpawnRegion),
  PlayerDamageFromCarCrash(
      172, 1, 2, 0, PacketTypes.PacketAuthorization.Policy.Kick, nullptr,
      GameClient::receivePlayerDamageFromCarCrash, nullptr),
  PlayerAttachedItem(173, 1, 2, 63, PacketTypes.PacketAuthorization.Policy.Kick,
                     GameServer::receivePlayerAttachedItem,
                     GameClient::receivePlayerAttachedItem, nullptr),
  ZombieHelmetFalling(174, 1, 2, 63,
                      PacketTypes.PacketAuthorization.Policy.Kick,
                      GameServer::receiveZombieHelmetFalling,
                      GameClient::receiveZombieHelmetFalling, nullptr),
  AddBrokenGlass(175, 1, 2, 0, PacketTypes.PacketAuthorization.Policy.Kick,
                 nullptr, GameClient::receiveAddBrokenGlass, nullptr),
  SyncPerks(177, 1, 2, 63, PacketTypes.PacketAuthorization.Policy.Kick,
            GameServer::receiveSyncPerks, GameClient::receiveSyncPerks,
            nullptr),
  SyncWeight(178, 1, 2, 63, PacketTypes.PacketAuthorization.Policy.Kick,
             GameServer::receiveSyncWeight, GameClient::receiveSyncWeight,
             nullptr),
  SyncInjuries(179, 1, 2, 63, PacketTypes.PacketAuthorization.Policy.Kick,
               GameServer::receiveSyncInjuries, GameClient::receiveSyncInjuries,
               nullptr),
  SyncEquippedRadioFreq(181, 1, 2, 63,
                        PacketTypes.PacketAuthorization.Policy.Kick,
                        GameServer::receiveSyncEquippedRadioFreq,
                        GameClient::receiveSyncEquippedRadioFreq, nullptr),
  InitPlayerChat(182, 1, 2, 0, PacketTypes.PacketAuthorization.Policy.Kick,
                 nullptr, GameClient::receiveInitPlayerChat, nullptr),
  PlayerJoinChat(183, 1, 2, 0, PacketTypes.PacketAuthorization.Policy.Kick,
                 nullptr, GameClient::receivePlayerJoinChat, nullptr),
  PlayerLeaveChat(184, 1, 2, 0, PacketTypes.PacketAuthorization.Policy.Kick,
                  nullptr, GameClient::receivePlayerLeaveChat, nullptr),
  ChatMessageFromPlayer(
      185, 1, 2, 63, PacketTypes.PacketAuthorization.Policy.Kick,
      GameServer::receiveChatMessageFromPlayer, nullptr, nullptr),
  ChatMessageToPlayer(186, 1, 2, 0, PacketTypes.PacketAuthorization.Policy.Kick,
                      nullptr, GameClient::receiveChatMessageToPlayer, nullptr),
  PlayerStartPMChat(187, 1, 2, 63, PacketTypes.PacketAuthorization.Policy.Kick,
                    GameServer::receivePlayerStartPMChat, nullptr, nullptr),
  AddChatTab(189, 1, 2, 0, PacketTypes.PacketAuthorization.Policy.Kick, nullptr,
             GameClient::receiveAddChatTab, nullptr),
  RemoveChatTab(190, 1, 2, 0, PacketTypes.PacketAuthorization.Policy.Kick,
                nullptr, GameClient::receiveRemoveChatTab, nullptr),
  PlayerConnectedToChat(191, 1, 2, 0,
                        PacketTypes.PacketAuthorization.Policy.Kick, nullptr,
                        GameClient::receivePlayerConnectedToChat, nullptr),
  PlayerNotFound(192, 1, 2, 0, PacketTypes.PacketAuthorization.Policy.Kick,
                 nullptr, GameClient::receivePlayerNotFound, nullptr),
  SendSafehouseInvite(193, 1, 2, 63,
                      PacketTypes.PacketAuthorization.Policy.Kick,
                      GameServer::receiveSendSafehouseInvite,
                      GameClient::receiveSendSafehouseInvite, nullptr),
  AcceptedSafehouseInvite(194, 1, 2, 63,
                          PacketTypes.PacketAuthorization.Policy.Kick,
                          GameServer::receiveAcceptedSafehouseInvite,
                          GameClient::receiveAcceptedSafehouseInvite, nullptr),
  ClimateManagerPacket(200, 1, 2, 62,
                       PacketTypes.PacketAuthorization.Policy.Kick,
                       GameServer::receiveClimateManagerPacket,
                       GameClient::receiveClimateManagerPacket, nullptr),
  IsoRegionServerPacket(201, 1, 2, 0,
                        PacketTypes.PacketAuthorization.Policy.Kick, nullptr,
                        GameClient::receiveIsoRegionServerPacket, nullptr),
  IsoRegionClientRequestFullUpdate(
      202, 1, 2, 63, PacketTypes.PacketAuthorization.Policy.Kick,
      GameServer::receiveIsoRegionClientRequestFullUpdate, nullptr, nullptr),
  EventPacket(210, 0, 3, 63, PacketTypes.PacketAuthorization.Policy.Kick,
              GameServer::receiveEventPacket, GameClient::receiveEventPacket,
              nullptr),
  Statistic(211, 1, 0, 63, PacketTypes.PacketAuthorization.Policy.Kick,
            GameServer::receiveStatistic, GameClient::receiveStatistic,
            nullptr),
  StatisticRequest(212, 1, 2, 32, PacketTypes.PacketAuthorization.Policy.Kick,
                   GameServer::receiveStatisticRequest,
                   GameClient::receiveStatisticRequest, nullptr),
  PlayerUpdateReliable(213, 0, 2, 63,
                       PacketTypes.PacketAuthorization.Policy.Kick,
                       GameServer::receivePlayerUpdate,
                       GameClient::receivePlayerUpdate, nullptr),
  ActionPacket(214, 1, 3, 63, PacketTypes.PacketAuthorization.Policy.Kick,
               GameServer::receiveActionPacket, GameClient::receiveActionPacket,
               nullptr),
  ZombieControl(215, 0, 2, 0, PacketTypes.PacketAuthorization.Policy.Kick,
                nullptr, GameClient::receiveZombieControl, nullptr),
  PlayWorldSound(216, 1, 2, 63, PacketTypes.PacketAuthorization.Policy.Kick,
                 GameServer::receivePlayWorldSound,
                 GameClient::receivePlayWorldSound, nullptr),
  StopSound(217, 1, 2, 63, PacketTypes.PacketAuthorization.Policy.Kick,
            GameServer::receiveStopSound, GameClient::receiveStopSound,
            nullptr),
  PlayerUpdate(218, 2, 0, 63, PacketTypes.PacketAuthorization.Policy.Kick,
               GameServer::receivePlayerUpdate, GameClient::receivePlayerUpdate,
               nullptr),
  ZombieSimulation(219, 2, 0, 63, PacketTypes.PacketAuthorization.Policy.Kick,
                   GameServer::receiveZombieSimulation,
                   GameClient::receiveZombieSimulation, nullptr),
  PingFromClient(220, 1, 0, 63, PacketTypes.PacketAuthorization.Policy.Kick,
                 GameServer::receivePingFromClient,
                 GameClient::receivePingFromClient, nullptr),
  ZombieSimulationReliable(221, 0, 2, 63,
                           PacketTypes.PacketAuthorization.Policy.Kick,
                           GameServer::receiveZombieSimulation,
                           GameClient::receiveZombieSimulation, nullptr),
  EatBody(222, 1, 2, 63, PacketTypes.PacketAuthorization.Policy.Kick,
          GameServer::receiveEatBody, GameClient::receiveEatBody, nullptr),
  Thump(223, 1, 2, 63, PacketTypes.PacketAuthorization.Policy.Kick,
        GameServer::receiveThump, GameClient::receiveThump, nullptr),
  SyncRadioData(224, 0, 3, 63, PacketTypes.PacketAuthorization.Policy.Kick,
                GameServer::receiveSyncRadioData,
                GameClient::receiveSyncRadioData, nullptr),
  LoginQueueRequest2(225, 0, 3, 63, PacketTypes.PacketAuthorization.Policy.Kick,
                     LoginQueue::receiveServerLoginQueueRequest, nullptr,
                     LoginQueue::receiveClientLoginQueueRequest),
  LoginQueueDone2(226, 0, 3, 63, PacketTypes.PacketAuthorization.Policy.Kick,
                  LoginQueue::receiveLoginQueueDone, nullptr, nullptr),
  ItemTransaction(227, 0, 3, 63, PacketTypes.PacketAuthorization.Policy.Kick,
                  ItemTransactionManager::receiveOnServer,
                  ItemTransactionManager::receiveOnClient, nullptr),
  KickOutOfSafehouse(228, 1, 2, 63, PacketTypes.PacketAuthorization.Policy.Kick,
                     GameServer::receiveKickOutOfSafehouse,
                     GameClient::receiveTeleport, nullptr),
  SneezeCough(229, 3, 0, 63, PacketTypes.PacketAuthorization.Policy.Kick,
              GameServer::receiveSneezeCough, GameClient::receiveSneezeCough,
              nullptr),
  BurnCorpse(230, 2, 2, 63, PacketTypes.PacketAuthorization.Policy.Kick,
             GameServer::receiveBurnCorpse, nullptr, nullptr),
  WaveSignal(300, 1, 2, 63, PacketTypes.PacketAuthorization.Policy.Kick,
             GameServer::receiveWaveSignal, GameClient::receiveWaveSignal,
             nullptr),
  PlayerListensChannel(
      301, 1, 2, 63, PacketTypes.PacketAuthorization.Policy.Kick,
      GameServer::receivePlayerListensChannel, nullptr, nullptr),
  RadioServerData(302, 1, 2, 63, PacketTypes.PacketAuthorization.Policy.Kick,
                  GameServer::receiveRadioServerData,
                  GameClient::receiveRadioServerData, nullptr),
  RadioDeviceDataState(303, 1, 2, 63,
                       PacketTypes.PacketAuthorization.Policy.Kick,
                       GameServer::receiveRadioDeviceDataState,
                       GameClient::receiveRadioDeviceDataState, nullptr),
  SyncCustomLightSettings(304, 1, 2, 63,
                          PacketTypes.PacketAuthorization.Policy.Kick,
                          GameServer::receiveSyncCustomLightSettings,
                          GameClient::receiveSyncCustomLightSettings, nullptr),
  ReplaceOnCooked(305, 1, 2, 63, PacketTypes.PacketAuthorization.Policy.Kick,
                  GameServer::receiveReplaceOnCooked, nullptr, nullptr),
  PlayerDataRequest(306, 1, 2, 63, PacketTypes.PacketAuthorization.Policy.Kick,
                    GameServer::receivePlayerDataRequest, nullptr, nullptr),
  GlobalModData(32000, 0, 2, 63, PacketTypes.PacketAuthorization.Policy.Kick,
                GameServer::receiveGlobalModData,
                GameClient::receiveGlobalModData, nullptr),
  GlobalModDataRequest(32001, 0, 2, 63,
                       PacketTypes.PacketAuthorization.Policy.Kick,
                       GameServer::receiveGlobalModDataRequest, nullptr,
                       nullptr),
  RadioPostSilenceEvent(32002, 0, 2, 0,
                        PacketTypes.PacketAuthorization.Policy.Kick, nullptr,
                        GameClient::receiveRadioPostSilence, nullptr);

  const short id; const uint8_t requiredAccessLevel;
  private final PacketTypes.PacketAuthorization.Policy unauthorizedPacketPolicy;
  const int PacketPriority; const int PacketReliability;
  const uint8_t OrderingChannel;
  private final PacketTypes.CallbackServerProcess serverProcess;
  private final PacketTypes.CallbackClientProcess mainLoopHandlePacketInternal;
  private final PacketTypes.CallbackClientProcess gameLoadingDealWithNetData;
  int incomePackets; int outcomePackets; int incomeBytes; int outcomeBytes;
  long clientPacketCount; long serverPacketCount;

  private PacketType(int int1, int int2, int int3, int int4,
                     PacketTypes.PacketAuthorization.Policy policy,
                     PacketTypes.CallbackServerProcess callbackServerProcess,
                     PacketTypes.CallbackClientProcess callbackClientProcess0,
                     PacketTypes.CallbackClientProcess callbackClientProcess1){
      this(int1, int2, int3, (byte)0, (byte)int4, policy, callbackServerProcess,
           callbackClientProcess0, callbackClientProcess1);}

private PacketType(int int1, int int2, int int3, byte byte1, byte byte0,
                   PacketTypes.PacketAuthorization.Policy policy,
                   PacketTypes.CallbackServerProcess callbackServerProcess,
                   PacketTypes.CallbackClientProcess callbackClientProcess0,
                   PacketTypes.CallbackClientProcess callbackClientProcess1) {
  this.id = (short)int1;
  this.requiredAccessLevel = byte0;
  this.unauthorizedPacketPolicy = policy;
  this.PacketPriority = int2;
  this.PacketReliability = int3;
  this.OrderingChannel = byte1;
  this.serverProcess = callbackServerProcess;
  this.mainLoopHandlePacketInternal = callbackClientProcess0;
  this.gameLoadingDealWithNetData = callbackClientProcess1;
  this.resetStatistics();
}

void resetStatistics() {
  this.incomePackets = 0;
  this.outcomePackets = 0;
  this.incomeBytes = 0;
  this.outcomeBytes = 0;
  this.clientPacketCount = 0L;
  this.serverPacketCount = 0L;
}

void send(UdpConnection connection) {
  connection.endPacket(this.PacketPriority, this.PacketReliability,
                       this.OrderingChannel);
  DebugLog.Packet.noise("type=%s username=%s connection=%d ip=%s size=%d",
                        this.name(), connection.username,
                        connection.getConnectedGUID(), connection.ip,
                        connection.getBufferPosition());
}

void doPacket(ByteBufferWriter bb) {
  bb.putByte((byte)-122);
  bb.putShort(this.getId());
}

short getId() { return this.id; }

void onServerPacket(ByteBuffer bb, UdpConnection connection) {
  if (PacketTypes.PacketAuthorization.isAuthorized(connection, this)) {
    DebugLog.Packet.noise("type=%s username=%s connection=%d ip=%s",
                          this.name(), connection.username,
                          connection.getConnectedGUID(), connection.ip);
    this.serverProcess.call(bb, connection, this.getId());
  }
}

void onMainLoopHandlePacketInternal(ByteBuffer bb) {
  DebugLog.Packet.noise("type=%s", this.name());
  this.mainLoopHandlePacketInternal.call(bb, this.getId());
}

bool onGameLoadingDealWithNetData(ByteBuffer bb) {
  DebugLog.Packet.noise("type=%s", this.name());
  if (this.gameLoadingDealWithNetData == nullptr) {
    DebugLog.Network.noise(
        "Delay processing packet of type %s while loading game", this.name());
    return false;
  } else {
    try {
      this.gameLoadingDealWithNetData.call(bb, this.getId());
      return true;
    } catch (Exception exception) {
      return false;
    }
  }
}

void onUnauthorized(UdpConnection connection) {
  DebugLog.Multiplayer.warn(
      String.format("On unauthorized packet %s (%d) was received from "
                    "user=\"%s\" (%d) ip %s %s",
                    this.name(), this.requiredAccessLevel, connection.username,
                    connection.accessLevel, connection.ip,
                    SteamUtils.isSteamModeEnabled() ? connection.steamID : ""));

  try {
    this.unauthorizedPacketPolicy.apply(connection, this.name());
  } catch (Exception exception) {
    exception.printStackTrace();
  }
}
} // namespace network
} // namespace zombie
} // namespace network
} // namespace zombie
