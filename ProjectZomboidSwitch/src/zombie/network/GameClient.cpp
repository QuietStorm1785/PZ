#include <cstdint>
#include <queue>
#include <string>
#include <vector>
#include "zombie/network/GameClient.h"

namespace zombie {
namespace network {

IsoPlayer GameClient::getPlayerByOnlineID(short var1) {
    // TODO: Implement getPlayerByOnlineID
    return nullptr;
}

void GameClient::init() {
    // TODO: Implement init
}

void GameClient::startClient() {
    // TODO: Implement startClient
}

void GameClient::receiveStatistic(ByteBuffer var0, short var1) {
    // TODO: Implement receiveStatistic
}

void GameClient::receiveStatisticRequest(ByteBuffer var0, short var1) {
    // TODO: Implement receiveStatisticRequest
}

void GameClient::receivePlayerUpdate(ByteBuffer var0, short var1) {
    // TODO: Implement receivePlayerUpdate
}

void GameClient::receiveZombieSimulation(ByteBuffer var0, short var1) {
    // TODO: Implement receiveZombieSimulation
}

void GameClient::receiveZombieControl(ByteBuffer var0, short var1) {
    // TODO: Implement receiveZombieControl
}

void GameClient::Shutdown() {
    // TODO: Implement Shutdown
}

void GameClient::update() {
    // TODO: Implement update
}

void GameClient::smashWindow(IsoWindow var1, int var2) {
    // TODO: Implement smashWindow
}

void GameClient::getCustomModData() {
    // TODO: Implement getCustomModData
}

void GameClient::receiveStitch(ByteBuffer var0, short var1) {
    // TODO: Implement receiveStitch
}

void GameClient::receiveBandage(ByteBuffer var0, short var1) {
    // TODO: Implement receiveBandage
}

void GameClient::receivePingFromClient(ByteBuffer var0, short var1) {
    // TODO: Implement receivePingFromClient
}

void GameClient::receiveWoundInfection(ByteBuffer var0, short var1) {
    // TODO: Implement receiveWoundInfection
}

void GameClient::receiveDisinfect(ByteBuffer var0, short var1) {
    // TODO: Implement receiveDisinfect
}

void GameClient::receiveSplint(ByteBuffer var0, short var1) {
    // TODO: Implement receiveSplint
}

void GameClient::receiveRemoveGlass(ByteBuffer var0, short var1) {
    // TODO: Implement receiveRemoveGlass
}

void GameClient::receiveRemoveBullet(ByteBuffer var0, short var1) {
    // TODO: Implement receiveRemoveBullet
}

void GameClient::receiveCleanBurn(ByteBuffer var0, short var1) {
    // TODO: Implement receiveCleanBurn
}

void GameClient::receiveAdditionalPain(ByteBuffer var0, short var1) {
    // TODO: Implement receiveAdditionalPain
}

void GameClient::delayPacket(int var1, int var2, int var3) {
    // TODO: Implement delayPacket
}

void GameClient::mainLoopDealWithNetData(ZomboidNetData var1) {
    // TODO: Implement mainLoopDealWithNetData
}

void GameClient::mainLoopHandlePacketInternal(ZomboidNetData var1, ByteBuffer var2) {
    // TODO: Implement mainLoopHandlePacketInternal
}

void GameClient::receiveAddBrokenGlass(ByteBuffer var0, short var1) {
    // TODO: Implement receiveAddBrokenGlass
}

void GameClient::receivePlayerDamageFromCarCrash(ByteBuffer var0, short var1) {
    // TODO: Implement receivePlayerDamageFromCarCrash
}

void GameClient::receivePacketCounts(ByteBuffer var0, short var1) {
    // TODO: Implement receivePacketCounts
}

void GameClient::requestPacketCounts() {
    // TODO: Implement requestPacketCounts
}

bool GameClient::IsClientPaused() {
    // TODO: Implement IsClientPaused
    return false;
}

void GameClient::receiveStartPause(ByteBuffer var0, short var1) {
    // TODO: Implement receiveStartPause
}

void GameClient::receiveStopPause(ByteBuffer var0, short var1) {
    // TODO: Implement receiveStopPause
}

void GameClient::receiveChatMessageToPlayer(ByteBuffer var0, short var1) {
    // TODO: Implement receiveChatMessageToPlayer
}

void GameClient::receivePlayerConnectedToChat(ByteBuffer var0, short var1) {
    // TODO: Implement receivePlayerConnectedToChat
}

void GameClient::receivePlayerJoinChat(ByteBuffer var0, short var1) {
    // TODO: Implement receivePlayerJoinChat
}

void GameClient::receiveInvMngRemoveItem(ByteBuffer var0, short var1) {
    // TODO: Implement receiveInvMngRemoveItem
}

void GameClient::receiveInvMngGetItem(ByteBuffer var0, short var1) {
    // TODO: Implement receiveInvMngGetItem
}

void GameClient::receiveInvMngReqItem(ByteBuffer var0, short var1) {
    // TODO: Implement receiveInvMngReqItem
}

void GameClient::invMngRequestItem(int var0, const std::string& var1, IsoPlayer var2) {
    // TODO: Implement invMngRequestItem
}

void GameClient::invMngRequestRemoveItem(int var0, IsoPlayer var1) {
    // TODO: Implement invMngRequestRemoveItem
}

void GameClient::receiveSyncFaction(ByteBuffer var0, short var1) {
    // TODO: Implement receiveSyncFaction
}

void GameClient::receiveSyncNonPvpZone(ByteBuffer var0, short var1) {
    // TODO: Implement receiveSyncNonPvpZone
}

void GameClient::receiveChangeTextColor(ByteBuffer var0, short var1) {
    // TODO: Implement receiveChangeTextColor
}

void GameClient::receivePlaySoundEveryPlayer(ByteBuffer var0, short var1) {
    // TODO: Implement receivePlaySoundEveryPlayer
}

void GameClient::receiveCataplasm(ByteBuffer var0, short var1) {
    // TODO: Implement receiveCataplasm
}

void GameClient::receiveStopFire(ByteBuffer var0, short var1) {
    // TODO: Implement receiveStopFire
}

void GameClient::receiveAddAlarm(ByteBuffer var0, short var1) {
    // TODO: Implement receiveAddAlarm
}

void GameClient::receiveAddExplosiveTrap(ByteBuffer var0, short var1) {
    // TODO: Implement receiveAddExplosiveTrap
}

void GameClient::receiveTeleport(ByteBuffer var0, short var1) {
    // TODO: Implement receiveTeleport
}

void GameClient::receiveRemoveBlood(ByteBuffer var0, short var1) {
    // TODO: Implement receiveRemoveBlood
}

void GameClient::receiveSyncThumpable(ByteBuffer var0, short var1) {
    // TODO: Implement receiveSyncThumpable
}

void GameClient::receiveSyncDoorKey(ByteBuffer var0, short var1) {
    // TODO: Implement receiveSyncDoorKey
}

void GameClient::receiveConstructedZone(ByteBuffer var0, short var1) {
    // TODO: Implement receiveConstructedZone
}

void GameClient::receiveAddCoopPlayer(ByteBuffer var0, short var1) {
    // TODO: Implement receiveAddCoopPlayer
}

void GameClient::receiveZombieDescriptors(ByteBuffer var0, short var1) {
    // TODO: Implement receiveZombieDescriptors
}

void GameClient::checksumServer() {
    // TODO: Implement checksumServer
}

void GameClient::receiveRegisterZone(ByteBuffer var0, short var1) {
    // TODO: Implement receiveRegisterZone
}

void GameClient::receiveAddXpCommand(ByteBuffer var0, short var1) {
    // TODO: Implement receiveAddXpCommand
}

void GameClient::sendAddXp(IsoPlayer var1, Perk var2, int var3) {
    // TODO: Implement sendAddXp
}

void GameClient::receiveSyncXP(ByteBuffer var0, short var1) {
    // TODO: Implement receiveSyncXP
}

void GameClient::sendSyncXp(IsoPlayer var1) {
    // TODO: Implement sendSyncXp
}

void GameClient::sendTransactionID(IsoPlayer var1) {
    // TODO: Implement sendTransactionID
}

void GameClient::receiveUserlog(ByteBuffer var0, short var1) {
    // TODO: Implement receiveUserlog
}

void GameClient::receiveAddXp(ByteBuffer var0, short var1) {
    // TODO: Implement receiveAddXp
}

void GameClient::receivePing(ByteBuffer var0, short var1) {
    // TODO: Implement receivePing
}

void GameClient::receiveChecksumLoading(ByteBuffer var0, short var1) {
    // TODO: Implement receiveChecksumLoading
}

void GameClient::receiveServerMapLoading(ByteBuffer var0, short var1) {
    // TODO: Implement receiveServerMapLoading
}

void GameClient::receiveChangeSafety(ByteBuffer var0, short var1) {
    // TODO: Implement receiveChangeSafety
}

void GameClient::sendChangeSafety(Safety var0) {
    // TODO: Implement sendChangeSafety
}

void GameClient::receiveAddItemInInventory(ByteBuffer var0, short var1) {
    // TODO: Implement receiveAddItemInInventory
}

void GameClient::receiveKicked(ByteBuffer var0, short var1) {
    // TODO: Implement receiveKicked
}

void GameClient::addDisconnectPacket(int var1) {
    // TODO: Implement addDisconnectPacket
}

void GameClient::connectionLost() {
    // TODO: Implement connectionLost
}

void GameClient::SendCommandToServer(const std::string& var0) {
    // TODO: Implement SendCommandToServer
}

void GameClient::sendServerPing(long var0) {
    // TODO: Implement sendServerPing
}

bool GameClient::gameLoadingDealWithNetData(ZomboidNetData var1) {
    // TODO: Implement gameLoadingDealWithNetData
    return false;
}

void GameClient::receiveWorldMessage(ByteBuffer var0, short var1) {
    // TODO: Implement receiveWorldMessage
}

void GameClient::receiveReloadOptions(ByteBuffer var0, short var1) {
    // TODO: Implement receiveReloadOptions
}

void GameClient::receiveStartRain(ByteBuffer var0, short var1) {
    // TODO: Implement receiveStartRain
}

void GameClient::receiveStopRain(ByteBuffer var0, short var1) {
    // TODO: Implement receiveStopRain
}

void GameClient::receiveWeather(ByteBuffer var0, short var1) {
    // TODO: Implement receiveWeather
}

void GameClient::receiveWorldMapPlayerPosition(ByteBuffer var0, short var1) {
    // TODO: Implement receiveWorldMapPlayerPosition
}

void GameClient::receiveSyncClock(ByteBuffer var0, short var1) {
    // TODO: Implement receiveSyncClock
}

void GameClient::receiveClientCommand(ByteBuffer var0, short var1) {
    // TODO: Implement receiveClientCommand
}

void GameClient::receiveGlobalObjects(ByteBuffer var0, short var1) {
    // TODO: Implement receiveGlobalObjects
}

void GameClient::setRequest(RequestState var1) {
    // TODO: Implement setRequest
}

void GameClient::receiveRequestData(ByteBuffer var0, short var1) {
    // TODO: Implement receiveRequestData
}

void GameClient::GameLoadingRequestData() {
    // TODO: Implement GameLoadingRequestData
}

void GameClient::receiveMetaGrid(ByteBuffer var0, short var1) {
    // TODO: Implement receiveMetaGrid
}

void GameClient::receiveSendCustomColor(ByteBuffer var0, short var1) {
    // TODO: Implement receiveSendCustomColor
}

void GameClient::receiveUpdateItemSprite(ByteBuffer var0, short var1) {
    // TODO: Implement receiveUpdateItemSprite
}

void GameClient::receiveUpdateOverlaySprite(ByteBuffer var0, short var1) {
    // TODO: Implement receiveUpdateOverlaySprite
}

KahluaTable GameClient::copyTable(KahluaTable var1) {
    // TODO: Implement copyTable
    return nullptr;
}

KahluaTable GameClient::getServerSpawnRegions() {
    // TODO: Implement getServerSpawnRegions
    return nullptr;
}

void GameClient::receiveStartFire(ByteBuffer var0, short var1) {
    // TODO: Implement receiveStartFire
}

void GameClient::receiveBecomeCorpse(ByteBuffer var0, short var1) {
    // TODO: Implement receiveBecomeCorpse
}

void GameClient::receiveAddCorpseToMap(ByteBuffer var0, short var1) {
    // TODO: Implement receiveAddCorpseToMap
}

void GameClient::receiveReceiveModData(ByteBuffer var0, short var1) {
    // TODO: Implement receiveReceiveModData
}

void GameClient::receiveObjectModData(ByteBuffer var0, short var1) {
    // TODO: Implement receiveObjectModData
}

void GameClient::receiveObjectChange(ByteBuffer var0, short var1) {
    // TODO: Implement receiveObjectChange
}

void GameClient::receiveKeepAlive(ByteBuffer var0, short var1) {
    // TODO: Implement receiveKeepAlive
}

void GameClient::receiveSmashWindow(ByteBuffer var0, short var1) {
    // TODO: Implement receiveSmashWindow
}

void GameClient::receiveRemoveContestedItemsFromInventory(ByteBuffer var0, short var1) {
    // TODO: Implement receiveRemoveContestedItemsFromInventory
}

void GameClient::receiveServerQuit(ByteBuffer var0, short var1) {
    // TODO: Implement receiveServerQuit
}

void GameClient::receiveHitCharacter(ByteBuffer var0, short var1) {
    // TODO: Implement receiveHitCharacter
}

void GameClient::sendHitVehicle(IsoPlayer var0, IsoGameCharacter var1, BaseVehicle var2, float var3, bool var4, int var5, float var6, bool var7) {
    // TODO: Implement sendHitVehicle
}

void GameClient::receiveZombieDeath(ByteBuffer var0, short var1) {
    // TODO: Implement receiveZombieDeath
}

void GameClient::sendZombieDeath(IsoZombie var0) {
    // TODO: Implement sendZombieDeath
}

void GameClient::receivePlayerDeath(ByteBuffer var0, short var1) {
    // TODO: Implement receivePlayerDeath
}

void GameClient::sendPlayerDeath(IsoPlayer var0) {
    // TODO: Implement sendPlayerDeath
}

void GameClient::receivePlayerDamage(ByteBuffer var0, short var1) {
    // TODO: Implement receivePlayerDamage
}

void GameClient::sendPlayerDamage(IsoPlayer var0) {
    // TODO: Implement sendPlayerDamage
}

void GameClient::receiveSyncInjuries(ByteBuffer var0, short var1) {
    // TODO: Implement receiveSyncInjuries
}

void GameClient::sendPlayerInjuries(IsoPlayer var0) {
    // TODO: Implement sendPlayerInjuries
}

void GameClient::receiveRemoveCorpseFromMap(ByteBuffer var0, short var1) {
    // TODO: Implement receiveRemoveCorpseFromMap
}

void GameClient::sendRemoveCorpseFromMap(IsoDeadBody var0) {
    // TODO: Implement sendRemoveCorpseFromMap
}

void GameClient::sendEvent(IsoPlayer var0, const std::string& var1) {
    // TODO: Implement sendEvent
}

void GameClient::receiveEventPacket(ByteBuffer var0, short var1) {
    // TODO: Implement receiveEventPacket
}

void GameClient::sendAction(BaseAction var0, bool var1) {
    // TODO: Implement sendAction
}

void GameClient::receiveActionPacket(ByteBuffer var0, short var1) {
    // TODO: Implement receiveActionPacket
}

void GameClient::sendEatBody(IsoZombie var0, IsoMovingObject var1) {
    // TODO: Implement sendEatBody
}

void GameClient::receiveEatBody(ByteBuffer var0, short var1) {
    // TODO: Implement receiveEatBody
}

void GameClient::sendThump(IsoGameCharacter var0, Thumpable var1) {
    // TODO: Implement sendThump
}

void GameClient::receiveSyncRadioData(ByteBuffer var0, short var1) {
    // TODO: Implement receiveSyncRadioData
}

void GameClient::receiveThump(ByteBuffer var0, short var1) {
    // TODO: Implement receiveThump
}

void GameClient::sendWorldSound(WorldSound var1) {
    // TODO: Implement sendWorldSound
}

void GameClient::receiveRemoveItemFromSquare(ByteBuffer var0, short var1) {
    // TODO: Implement receiveRemoveItemFromSquare
}

void GameClient::receiveLoadPlayerProfile(ByteBuffer var0, short var1) {
    // TODO: Implement receiveLoadPlayerProfile
}

void GameClient::sendLoginQueueRequest2() {
    // TODO: Implement sendLoginQueueRequest2
}

void GameClient::sendLoginQueueDone2(long var1) {
    // TODO: Implement sendLoginQueueDone2
}

void GameClient::receiveRemoveInventoryItemFromContainer(ByteBuffer var0, short var1) {
    // TODO: Implement receiveRemoveInventoryItemFromContainer
}

void GameClient::receiveAddInventoryItemToContainer(ByteBuffer var0, short var1) {
    // TODO: Implement receiveAddInventoryItemToContainer
}

void GameClient::readItemStats(ByteBuffer var1, InventoryItem var2) {
    // TODO: Implement readItemStats
}

void GameClient::receiveItemStats(ByteBuffer var0, short var1) {
    // TODO: Implement receiveItemStats
}

bool GameClient::canSeePlayerStats() {
    // TODO: Implement canSeePlayerStats
    return false;
}

bool GameClient::canModifyPlayerStats() {
    // TODO: Implement canModifyPlayerStats
    return false;
}

void GameClient::sendPersonalColor(IsoPlayer var1) {
    // TODO: Implement sendPersonalColor
}

void GameClient::sendChangedPlayerStats(IsoPlayer var1) {
    // TODO: Implement sendChangedPlayerStats
}

void GameClient::receiveChangePlayerStats(ByteBuffer var0, short var1) {
    // TODO: Implement receiveChangePlayerStats
}

void GameClient::writePlayerConnectData(ByteBufferWriter var1, IsoPlayer var2) {
    // TODO: Implement writePlayerConnectData
}

void GameClient::sendPlayerConnect(IsoPlayer var1) {
    // TODO: Implement sendPlayerConnect
}

void GameClient::sendPlayerSave(IsoPlayer var1) {
    // TODO: Implement sendPlayerSave
}

void GameClient::sendPlayer2(IsoPlayer var1) {
    // TODO: Implement sendPlayer2
}

void GameClient::sendPlayer(IsoPlayer var1) {
    // TODO: Implement sendPlayer
}

void GameClient::heartBeat() {
    // TODO: Implement heartBeat
}

IsoZombie GameClient::getZombie(short var0) {
    // TODO: Implement getZombie
    return nullptr;
}

void GameClient::sendPlayerExtraInfo(IsoPlayer var0) {
    // TODO: Implement sendPlayerExtraInfo
}

void GameClient::receiveExtraInfo(ByteBuffer var0, short var1) {
    // TODO: Implement receiveExtraInfo
}

void GameClient::setResetID(int var1) {
    // TODO: Implement setResetID
}

void GameClient::loadResetID() {
    // TODO: Implement loadResetID
}

void GameClient::saveResetID() {
    // TODO: Implement saveResetID
}

void GameClient::receivePlayerConnect(ByteBuffer var0, short var1) {
    // TODO: Implement receivePlayerConnect
}

void GameClient::receiveScoreboardUpdate(ByteBuffer var0, short var1) {
    // TODO: Implement receiveScoreboardUpdate
}

bool GameClient::receivePlayerConnectWhileLoading(ByteBuffer var1) {
    // TODO: Implement receivePlayerConnectWhileLoading
    return false;
}

IsoObject GameClient::getIsoObjectRefFromByteBuffer(ByteBuffer var1) {
    // TODO: Implement getIsoObjectRefFromByteBuffer
    return nullptr;
}

void GameClient::sendWeaponHit(IsoPlayer var1, HandWeapon var2, IsoObject var3) {
    // TODO: Implement sendWeaponHit
}

void GameClient::receiveSyncCustomLightSettings(ByteBuffer var0, short var1) {
    // TODO: Implement receiveSyncCustomLightSettings
}

void GameClient::receiveSyncIsoObjectReq(ByteBuffer var0, short var1) {
    // TODO: Implement receiveSyncIsoObjectReq
}

void GameClient::receiveSyncWorldObjectsReq(ByteBuffer var0, short var1) {
    // TODO: Implement receiveSyncWorldObjectsReq
}

void GameClient::receiveSyncObjects(ByteBuffer var0, short var1) {
    // TODO: Implement receiveSyncObjects
}

void GameClient::receiveSyncIsoObject(ByteBuffer var0, short var1) {
    // TODO: Implement receiveSyncIsoObject
}

void GameClient::receiveSyncAlarmClock(ByteBuffer var0, short var1) {
    // TODO: Implement receiveSyncAlarmClock
}

void GameClient::receiveAddItemToMap(ByteBuffer var0, short var1) {
    // TODO: Implement receiveAddItemToMap
}

void GameClient::skipPacket(ByteBuffer var0, short var1) {
    // TODO: Implement skipPacket
}

void GameClient::receiveAccessDenied(ByteBuffer var0, short var1) {
    // TODO: Implement receiveAccessDenied
}

void GameClient::receivePlayerTimeout(ByteBuffer var0, short var1) {
    // TODO: Implement receivePlayerTimeout
}

void GameClient::receivePlayerTimeout(short var0) {
    // TODO: Implement receivePlayerTimeout
}

void GameClient::disconnect() {
    // TODO: Implement disconnect
}

void GameClient::resetDisconnectTimer() {
    // TODO: Implement resetDisconnectTimer
}

std::string GameClient::getReconnectCountdownTimer() {
    // TODO: Implement getReconnectCountdownTimer
    return "";
}

bool GameClient::canConnect() {
    // TODO: Implement canConnect
    return false;
}

void GameClient::addIncoming(short var1, ByteBuffer var2) {
    // TODO: Implement addIncoming
}

void GameClient::doDisconnect(const std::string& var1) {
    // TODO: Implement doDisconnect
}

void GameClient::removeZombieFromCache(IsoZombie var1) {
    // TODO: Implement removeZombieFromCache
}

void GameClient::receiveEquip(ByteBuffer var0, short var1) {
    // TODO: Implement receiveEquip
}

void GameClient::equip(IsoPlayer var1, int var2) {
    // TODO: Implement equip
}

void GameClient::sendWorldMessage(const std::string& var1) {
    // TODO: Implement sendWorldMessage
}

void GameClient::convertGameSaveWorldDirectory(const std::string& var1, const std::string& var2) {
    // TODO: Implement convertGameSaveWorldDirectory
}

void GameClient::doConnect(const std::string& var1, const std::string& var2, const std::string& var3, const std::string& var4, const std::string& var5, const std::string& var6, const std::string& var7, bool var8) {
    // TODO: Implement doConnect
}

void GameClient::doConnectCoop(const std::string& var1) {
    // TODO: Implement doConnectCoop
}

void GameClient::scoreboardUpdate() {
    // TODO: Implement scoreboardUpdate
}

void GameClient::sendWorldSound(void* var1, int var2, int var3, int var4, int var5, int var6, bool var7, float var8, float var9) {
    // TODO: Implement sendWorldSound
}

void GameClient::receivePlayWorldSound(ByteBuffer var0, short var1) {
    // TODO: Implement receivePlayWorldSound
}

void GameClient::receivePlaySound(ByteBuffer var0, short var1) {
    // TODO: Implement receivePlaySound
}

void GameClient::receiveStopSound(ByteBuffer var0, short var1) {
    // TODO: Implement receiveStopSound
}

void GameClient::receiveWorldSound(ByteBuffer var0, short var1) {
    // TODO: Implement receiveWorldSound
}

void GameClient::receiveAddAmbient(ByteBuffer var0, short var1) {
    // TODO: Implement receiveAddAmbient
}

void GameClient::sendClientCommand(IsoPlayer var1, const std::string& var2, const std::string& var3, KahluaTable var4) {
    // TODO: Implement sendClientCommand
}

void GameClient::sendClientCommandV(IsoPlayer var1, const std::string& var2, const std::string& var3, Object... var4) {
    // TODO: Implement sendClientCommandV
}

void GameClient::sendClothing(IsoPlayer var1, const std::string& var2, InventoryItem var3) {
    // TODO: Implement sendClothing
}

void GameClient::receiveSyncClothing(ByteBuffer var0, short var1) {
    // TODO: Implement receiveSyncClothing
}

void GameClient::sendAttachedItem(IsoPlayer var1, const std::string& var2, InventoryItem var3) {
    // TODO: Implement sendAttachedItem
}

void GameClient::receivePlayerAttachedItem(ByteBuffer var0, short var1) {
    // TODO: Implement receivePlayerAttachedItem
}

void GameClient::sendVisual(IsoPlayer var1) {
    // TODO: Implement sendVisual
}

void GameClient::receiveHumanVisual(ByteBuffer var0, short var1) {
    // TODO: Implement receiveHumanVisual
}

void GameClient::receiveBloodSplatter(ByteBuffer var0, short var1) {
    // TODO: Implement receiveBloodSplatter
}

new GameClient::IsoZombieGiblets(var18 *) {
    // TODO: Implement IsoZombieGiblets
    return nullptr;
}

new GameClient::IsoZombieGiblets(var6 *, var7 *) {
    // TODO: Implement IsoZombieGiblets
    return nullptr;
}

new GameClient::IsoZombieGiblets(var6 *, var7 *) {
    // TODO: Implement IsoZombieGiblets
    return nullptr;
}

new GameClient::IsoZombieGiblets(var6 *, var7 *) {
    // TODO: Implement IsoZombieGiblets
    return nullptr;
}

new GameClient::IsoZombieGiblets(var6 *, var7 *) {
    // TODO: Implement IsoZombieGiblets
    return nullptr;
}

new GameClient::IsoZombieGiblets(var6 *, var7 *) {
    // TODO: Implement IsoZombieGiblets
    return nullptr;
}

new GameClient::IsoZombieGiblets(var6 *, var7 *) {
    // TODO: Implement IsoZombieGiblets
    return nullptr;
}

new GameClient::IsoZombieGiblets(var6 *, var7 *) {
    // TODO: Implement IsoZombieGiblets
    return nullptr;
}

new GameClient::IsoZombieGiblets(var6 *, var7 *) {
    // TODO: Implement IsoZombieGiblets
    return nullptr;
}

new GameClient::IsoZombieGiblets(var6 *, var7 *) {
    // TODO: Implement IsoZombieGiblets
    return nullptr;
}

new GameClient::IsoZombieGiblets(var6 *, var7 *) {
    // TODO: Implement IsoZombieGiblets
    return nullptr;
}

new GameClient::IsoZombieGiblets(var6 *, var7 *) {
    // TODO: Implement IsoZombieGiblets
    return nullptr;
}

new GameClient::IsoZombieGiblets(var6 *, var7 *) {
    // TODO: Implement IsoZombieGiblets
    return nullptr;
}

new GameClient::IsoZombieGiblets(var6 *, var7 *) {
    // TODO: Implement IsoZombieGiblets
    return nullptr;
}

void GameClient::receiveZombieSound(ByteBuffer var0, short var1) {
    // TODO: Implement receiveZombieSound
}

void GameClient::receiveSlowFactor(ByteBuffer var0, short var1) {
    // TODO: Implement receiveSlowFactor
}

void GameClient::sendCustomColor(IsoObject var1) {
    // TODO: Implement sendCustomColor
}

void GameClient::sendBandage(int var1, int var2, bool var3, float var4, bool var5, const std::string& var6) {
    // TODO: Implement sendBandage
}

void GameClient::sendStitch(IsoGameCharacter var1, IsoGameCharacter var2, BodyPart var3, InventoryItem var4, bool var5) {
    // TODO: Implement sendStitch
}

void GameClient::sendWoundInfection(int var1, int var2, bool var3) {
    // TODO: Implement sendWoundInfection
}

void GameClient::sendDisinfect(IsoGameCharacter var1, IsoGameCharacter var2, BodyPart var3, InventoryItem var4) {
    // TODO: Implement sendDisinfect
}

void GameClient::sendSplint(int var1, int var2, bool var3, float var4, const std::string& var5) {
    // TODO: Implement sendSplint
}

void GameClient::sendAdditionalPain(int var1, int var2, float var3) {
    // TODO: Implement sendAdditionalPain
}

void GameClient::sendRemoveGlass(IsoGameCharacter var1, IsoGameCharacter var2, BodyPart var3, bool var4) {
    // TODO: Implement sendRemoveGlass
}

void GameClient::sendRemoveBullet(IsoGameCharacter var1, IsoGameCharacter var2, BodyPart var3) {
    // TODO: Implement sendRemoveBullet
}

void GameClient::sendCleanBurn(IsoGameCharacter var1, IsoGameCharacter var2, BodyPart var3, InventoryItem var4) {
    // TODO: Implement sendCleanBurn
}

void GameClient::eatFood(IsoPlayer var1, Food var2, float var3) {
    // TODO: Implement eatFood
}

void GameClient::drink(IsoPlayer var1, float var2) {
    // TODO: Implement drink
}

void GameClient::addToItemSendBuffer(IsoObject var1, ItemContainer var2, InventoryItem var3) {
    // TODO: Implement addToItemSendBuffer
}

void GameClient::addToItemRemoveSendBuffer(IsoObject var1, ItemContainer var2, InventoryItem var3) {
    // TODO: Implement addToItemRemoveSendBuffer
}

void GameClient::sendAddedRemovedItems(bool var1) {
    // TODO: Implement sendAddedRemovedItems
}

void GameClient::checkAddedRemovedItems(IsoObject var1) {
    // TODO: Implement checkAddedRemovedItems
}

void GameClient::sendReplaceOnCooked(InventoryItem var1) {
    // TODO: Implement sendReplaceOnCooked
}

void GameClient::writeItemStats(ByteBufferWriter var1, InventoryItem var2) {
    // TODO: Implement writeItemStats
}

void GameClient::sendItemStats(InventoryItem var1) {
    // TODO: Implement sendItemStats
}

void GameClient::PlayWorldSound(const std::string& var1, int var2, int var3, uint8_t var4) {
    // TODO: Implement PlayWorldSound
}

void GameClient::PlaySound(const std::string& var1, bool var2, IsoMovingObject var3) {
    // TODO: Implement PlaySound
}

void GameClient::StopSound(IsoMovingObject var1, const std::string& var2, bool var3) {
    // TODO: Implement StopSound
}

void GameClient::startLocalServer() {
    // TODO: Implement startLocalServer
}

void GameClient::sendPing() {
    // TODO: Implement sendPing
}

void GameClient::registerZone(Zone var0, bool var1) {
    // TODO: Implement registerZone
}

void GameClient::receiveHelicopter(ByteBuffer var0, short var1) {
    // TODO: Implement receiveHelicopter
}

void GameClient::receiveVehicles(ByteBuffer var0, short var1) {
    // TODO: Implement receiveVehicles
}

void GameClient::receiveVehicleAuthorization(ByteBuffer var0, short var1) {
    // TODO: Implement receiveVehicleAuthorization
}

void GameClient::receiveTimeSync(ByteBuffer var0, short var1) {
    // TODO: Implement receiveTimeSync
}

void GameClient::sendSafehouse(SafeHouse var0, bool var1) {
    // TODO: Implement sendSafehouse
}

void GameClient::receiveSyncSafehouse(ByteBuffer var0, short var1) {
    // TODO: Implement receiveSyncSafehouse
}

void GameClient::sendKickOutOfSafehouse(IsoPlayer var0) {
    // TODO: Implement sendKickOutOfSafehouse
}

IsoPlayer GameClient::getPlayerFromUsername(const std::string& var1) {
    // TODO: Implement getPlayerFromUsername
    return nullptr;
}

void GameClient::destroy(IsoObject var0) {
    // TODO: Implement destroy
}

void GameClient::sendTeleport(IsoPlayer var0, float var1, float var2, float var3) {
    // TODO: Implement sendTeleport
}

void GameClient::sendStopFire(IsoGridSquare var0) {
    // TODO: Implement sendStopFire
}

void GameClient::sendStopFire(IsoGameCharacter var0) {
    // TODO: Implement sendStopFire
}

void GameClient::sendCataplasm(int var1, int var2, float var3, float var4, float var5) {
    // TODO: Implement sendCataplasm
}

void GameClient::receiveBodyDamageUpdate(ByteBuffer var0, short var1) {
    // TODO: Implement receiveBodyDamageUpdate
}

void GameClient::receiveRadioDeviceDataState(ByteBuffer var0, short var1) {
    // TODO: Implement receiveRadioDeviceDataState
}

void GameClient::sendRadioServerDataRequest() {
    // TODO: Implement sendRadioServerDataRequest
}

void GameClient::receiveRadioServerData(ByteBuffer var0, short var1) {
    // TODO: Implement receiveRadioServerData
}

void GameClient::receiveRadioPostSilence(ByteBuffer var0, short var1) {
    // TODO: Implement receiveRadioPostSilence
}

void GameClient::receiveWaveSignal(ByteBuffer var0, short var1) {
    // TODO: Implement receiveWaveSignal
}

void GameClient::sendPlayerListensChannel(int var0, bool var1, bool var2) {
    // TODO: Implement sendPlayerListensChannel
}

void GameClient::receiveSyncFurnace(ByteBuffer var0, short var1) {
    // TODO: Implement receiveSyncFurnace
}

void GameClient::sendFurnaceChange(BSFurnace var0) {
    // TODO: Implement sendFurnaceChange
}

void GameClient::sendCompost(IsoCompost var0) {
    // TODO: Implement sendCompost
}

void GameClient::receiveSyncCompost(ByteBuffer var0, short var1) {
    // TODO: Implement receiveSyncCompost
}

void GameClient::requestUserlog(const std::string& var1) {
    // TODO: Implement requestUserlog
}

void GameClient::addUserlog(const std::string& var1, const std::string& var2, const std::string& var3) {
    // TODO: Implement addUserlog
}

void GameClient::removeUserlog(const std::string& var1, const std::string& var2, const std::string& var3) {
    // TODO: Implement removeUserlog
}

void GameClient::addWarningPoint(const std::string& var1, const std::string& var2, int var3) {
    // TODO: Implement addWarningPoint
}

void GameClient::receiveMessageForAdmin(ByteBuffer var0, short var1) {
    // TODO: Implement receiveMessageForAdmin
}

void GameClient::wakeUpPlayer(IsoPlayer var1) {
    // TODO: Implement wakeUpPlayer
}

void GameClient::receiveWakeUpPlayer(ByteBuffer var0, short var1) {
    // TODO: Implement receiveWakeUpPlayer
}

void GameClient::getDBSchema() {
    // TODO: Implement getDBSchema
}

void GameClient::receiveGetDBSchema(ByteBuffer var0, short var1) {
    // TODO: Implement receiveGetDBSchema
}

void GameClient::getTableResult(const std::string& var1, int var2) {
    // TODO: Implement getTableResult
}

void GameClient::receiveGetTableResult(ByteBuffer var0, short var1) {
    // TODO: Implement receiveGetTableResult
}

void GameClient::executeQuery(const std::string& var1, KahluaTable var2) {
    // TODO: Implement executeQuery
}

void GameClient::sendNonPvpZone(NonPvpZone var0, bool var1) {
    // TODO: Implement sendNonPvpZone
}

void GameClient::sendFaction(Faction var0, bool var1) {
    // TODO: Implement sendFaction
}

void GameClient::sendFactionInvite(Faction var0, IsoPlayer var1, const std::string& var2) {
    // TODO: Implement sendFactionInvite
}

void GameClient::receiveSendFactionInvite(ByteBuffer var0, short var1) {
    // TODO: Implement receiveSendFactionInvite
}

void GameClient::acceptFactionInvite(Faction var0, const std::string& var1) {
    // TODO: Implement acceptFactionInvite
}

void GameClient::receiveAcceptedFactionInvite(ByteBuffer var0, short var1) {
    // TODO: Implement receiveAcceptedFactionInvite
}

void GameClient::addTicket(const std::string& var0, const std::string& var1, int var2) {
    // TODO: Implement addTicket
}

void GameClient::getTickets(const std::string& var0) {
    // TODO: Implement getTickets
}

void GameClient::receiveViewTickets(ByteBuffer var0, short var1) {
    // TODO: Implement receiveViewTickets
}

void GameClient::receiveChecksum(ByteBuffer var0, short var1) {
    // TODO: Implement receiveChecksum
}

void GameClient::removeTicket(int var0) {
    // TODO: Implement removeTicket
}

bool GameClient::sendItemListNet(IsoPlayer var0, std::vector<InventoryItem> var1, IsoPlayer var2, const std::string& var3, const std::string& var4) {
    // TODO: Implement sendItemListNet
    return false;
}

void GameClient::receiveSendItemListNet(ByteBuffer var0, short var1) {
    // TODO: Implement receiveSendItemListNet
}

void GameClient::requestTrading(IsoPlayer var1, IsoPlayer var2) {
    // TODO: Implement requestTrading
}

void GameClient::acceptTrading(IsoPlayer var1, IsoPlayer var2, bool var3) {
    // TODO: Implement acceptTrading
}

void GameClient::receiveRequestTrading(ByteBuffer var0, short var1) {
    // TODO: Implement receiveRequestTrading
}

void GameClient::tradingUISendAddItem(IsoPlayer var1, IsoPlayer var2, InventoryItem var3) {
    // TODO: Implement tradingUISendAddItem
}

void GameClient::receiveTradingUIAddItem(ByteBuffer var0, short var1) {
    // TODO: Implement receiveTradingUIAddItem
}

void GameClient::tradingUISendRemoveItem(IsoPlayer var1, IsoPlayer var2, int var3) {
    // TODO: Implement tradingUISendRemoveItem
}

void GameClient::receiveTradingUIRemoveItem(ByteBuffer var0, short var1) {
    // TODO: Implement receiveTradingUIRemoveItem
}

void GameClient::tradingUISendUpdateState(IsoPlayer var1, IsoPlayer var2, int var3) {
    // TODO: Implement tradingUISendUpdateState
}

void GameClient::receiveTradingUIUpdateState(ByteBuffer var0, short var1) {
    // TODO: Implement receiveTradingUIUpdateState
}

void GameClient::sendBuildingStashToDo(const std::string& var0) {
    // TODO: Implement sendBuildingStashToDo
}

void GameClient::setServerStatisticEnable(bool var0) {
    // TODO: Implement setServerStatisticEnable
}

bool GameClient::getServerStatisticEnable() {
    // TODO: Implement getServerStatisticEnable
    return false;
}

void GameClient::sendRequestInventory(IsoPlayer var0) {
    // TODO: Implement sendRequestInventory
}

int GameClient::sendInventoryPutItems(ByteBufferWriter var1, InventoryItem> var2, long var3) {
    // TODO: Implement sendInventoryPutItems
    return 0;
}

void GameClient::receiveRequestInventory(ByteBuffer var0, short var1) {
    // TODO: Implement receiveRequestInventory
}

void GameClient::receiveSendInventory(ByteBuffer var0, short var1) {
    // TODO: Implement receiveSendInventory
}

void GameClient::sendGetItemInvMng(long var0) {
    // TODO: Implement sendGetItemInvMng
}

void GameClient::receiveSpawnRegion(ByteBuffer var0, short var1) {
    // TODO: Implement receiveSpawnRegion
}

void GameClient::receivePlayerConnectLoading(ByteBuffer var0) {
    // TODO: Implement receivePlayerConnectLoading
}

void GameClient::receiveClimateManagerPacket(ByteBuffer var0, short var1) {
    // TODO: Implement receiveClimateManagerPacket
}

void GameClient::receiveServerMap(ByteBuffer var0, short var1) {
    // TODO: Implement receiveServerMap
}

void GameClient::receivePassengerMap(ByteBuffer var0, short var1) {
    // TODO: Implement receivePassengerMap
}

void GameClient::receiveIsoRegionServerPacket(ByteBuffer var0, short var1) {
    // TODO: Implement receiveIsoRegionServerPacket
}

void GameClient::sendIsoRegionDataRequest() {
    // TODO: Implement sendIsoRegionDataRequest
}

void GameClient::sendSandboxOptionsToServer(SandboxOptions var1) {
    // TODO: Implement sendSandboxOptionsToServer
}

void GameClient::receiveSandboxOptions(ByteBuffer var0, short var1) {
    // TODO: Implement receiveSandboxOptions
}

void GameClient::receiveChunkObjectState(ByteBuffer var0, short var1) {
    // TODO: Implement receiveChunkObjectState
}

void GameClient::receivePlayerLeaveChat(ByteBuffer var0, short var1) {
    // TODO: Implement receivePlayerLeaveChat
}

void GameClient::receiveInitPlayerChat(ByteBuffer var0, short var1) {
    // TODO: Implement receiveInitPlayerChat
}

void GameClient::receiveAddChatTab(ByteBuffer var0, short var1) {
    // TODO: Implement receiveAddChatTab
}

void GameClient::receiveRemoveChatTab(ByteBuffer var0, short var1) {
    // TODO: Implement receiveRemoveChatTab
}

void GameClient::receivePlayerNotFound(ByteBuffer var0, short var1) {
    // TODO: Implement receivePlayerNotFound
}

void GameClient::sendZombieHelmetFall(IsoPlayer var0, IsoGameCharacter var1, InventoryItem var2) {
    // TODO: Implement sendZombieHelmetFall
}

void GameClient::receiveZombieHelmetFalling(ByteBuffer var0, short var1) {
    // TODO: Implement receiveZombieHelmetFalling
}

void GameClient::sendPerks(IsoPlayer var0) {
    // TODO: Implement sendPerks
}

void GameClient::receiveSyncPerks(ByteBuffer var0, short var1) {
    // TODO: Implement receiveSyncPerks
}

void GameClient::sendWeight(IsoPlayer var0) {
    // TODO: Implement sendWeight
}

void GameClient::receiveSyncWeight(ByteBuffer var0, short var1) {
    // TODO: Implement receiveSyncWeight
}

void GameClient::receiveGlobalModData(ByteBuffer var0, short var1) {
    // TODO: Implement receiveGlobalModData
}

void GameClient::sendSafehouseInvite(SafeHouse var0, IsoPlayer var1, const std::string& var2) {
    // TODO: Implement sendSafehouseInvite
}

void GameClient::receiveSendSafehouseInvite(ByteBuffer var0, short var1) {
    // TODO: Implement receiveSendSafehouseInvite
}

void GameClient::acceptSafehouseInvite(SafeHouse var0, const std::string& var1) {
    // TODO: Implement acceptSafehouseInvite
}

void GameClient::receiveAcceptedSafehouseInvite(ByteBuffer var0, short var1) {
    // TODO: Implement receiveAcceptedSafehouseInvite
}

void GameClient::sendEquippedRadioFreq(IsoPlayer var0) {
    // TODO: Implement sendEquippedRadioFreq
}

void GameClient::receiveSyncEquippedRadioFreq(ByteBuffer var0, short var1) {
    // TODO: Implement receiveSyncEquippedRadioFreq
}

void GameClient::sendSneezingCoughing(short var0, int var1, uint8_t var2) {
    // TODO: Implement sendSneezingCoughing
}

void GameClient::receiveSneezeCough(ByteBuffer var0, short var1) {
    // TODO: Implement receiveSneezeCough
}

void GameClient::sendBurnCorpse(short var0, short var1) {
    // TODO: Implement sendBurnCorpse
}

void GameClient::rememberPlayerPosition(IsoPlayer var0, float var1, float var2) {
    // TODO: Implement rememberPlayerPosition
}

void GameClient::receiveValidatePacket(ByteBuffer var0, short var1) {
    // TODO: Implement receiveValidatePacket
}

void GameClient::sendValidatePacket(ValidatePacket var0) {
    // TODO: Implement sendValidatePacket
}

} // namespace network
} // namespace zombie
