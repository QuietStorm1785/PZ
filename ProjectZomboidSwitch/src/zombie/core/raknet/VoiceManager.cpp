#include <string>
#include "zombie\core\raknet/VoiceManager.h"

namespace zombie {
namespace core {
namespace raknet {

VoiceManager VoiceManager::getInstance() {
    // TODO: Implement getInstance
    return nullptr;
}

void VoiceManager::DeinitRecSound() {
    // TODO: Implement DeinitRecSound
}

void VoiceManager::ResetRecSound() {
    // TODO: Implement ResetRecSound
}

void VoiceManager::VoiceRestartClient(bool var1) {
    // TODO: Implement VoiceRestartClient
}

void VoiceManager::VoiceInitClient() {
    // TODO: Implement VoiceInitClient
}

void VoiceManager::VoiceInitServer(bool var1, int var2, int var3, int var4, int var5, double var6, double var8, bool var10) {
    // TODO: Implement VoiceInitServer
}

void VoiceManager::VoiceConnectAccept(long var1) {
    // TODO: Implement VoiceConnectAccept
}

void VoiceManager::InitRecDeviceForTest() {
    // TODO: Implement InitRecDeviceForTest
}

void VoiceManager::VoiceOpenChannelReply(long var1, ByteBuffer var3) {
    // TODO: Implement VoiceOpenChannelReply
}

void VoiceManager::VoiceConnectReq(long var1) {
    // TODO: Implement VoiceConnectReq
}

void VoiceManager::VoiceConnectClose(long var1) {
    // TODO: Implement VoiceConnectClose
}

void VoiceManager::setMode(int var1) {
    // TODO: Implement setMode
}

void VoiceManager::setVADMode(int var1) {
    // TODO: Implement setVADMode
}

void VoiceManager::setAGCMode(int var1) {
    // TODO: Implement setAGCMode
}

void VoiceManager::setVolumePlayers(int var1) {
    // TODO: Implement setVolumePlayers
}

void VoiceManager::setVolumeMic(int var1) {
    // TODO: Implement setVolumeMic
}

void VoiceManager::playerSetMute(const std::string& var0) {
    // TODO: Implement playerSetMute
}

bool VoiceManager::playerGetMute(const std::string& var0) {
    // TODO: Implement playerGetMute
    return false;
}

void VoiceManager::LuaRegister(Platform var1, KahluaTable var2) {
    // TODO: Implement LuaRegister
}

void VoiceManager::setUserPlaySound(long var1, float var3) {
    // TODO: Implement setUserPlaySound
}

long VoiceManager::getUserPlaySound(short var1) {
    // TODO: Implement getUserPlaySound
    return 0;
}

void VoiceManager::InitVMClient() {
    // TODO: Implement InitVMClient
}

void VoiceManager::loadConfig() {
    // TODO: Implement loadConfig
}

void VoiceManager::UpdateRecordDevice() {
    // TODO: Implement UpdateRecordDevice
}

void VoiceManager::UpdateRecordDeviceInternal() {
    // TODO: Implement UpdateRecordDeviceInternal
}

void VoiceManager::DeinitVMClient() {
    // TODO: Implement DeinitVMClient
}

void VoiceManager::setTestingMicrophone(bool var1) {
    // TODO: Implement setTestingMicrophone
}

void VoiceManager::notifyThread() {
    // TODO: Implement notifyThread
}

void VoiceManager::update() {
    // TODO: Implement update
}

float VoiceManager::getCanHearAllVolume(float var1) {
    // TODO: Implement getCanHearAllVolume
    return 0;
}

void VoiceManager::threadSafeCode(Runnable var1) {
    // TODO: Implement threadSafeCode
}

void VoiceManager::logFrame(IsoPlayer var0, IsoPlayer var1, float var2) {
    // TODO: Implement logFrame
}

RadioData VoiceManager::checkForNearbyRadios(VoiceManagerData var1) {
    // TODO: Implement checkForNearbyRadios
    return nullptr;
}

void VoiceManager::UpdateChannelsRoaming(UdpConnection var1) {
    // TODO: Implement UpdateChannelsRoaming
}

void VoiceManager::InitVMServer() {
    // TODO: Implement InitVMServer
}

int VoiceManager::getMicVolumeIndicator() {
    // TODO: Implement getMicVolumeIndicator
    return 0;
}

bool VoiceManager::getMicVolumeError() {
    // TODO: Implement getMicVolumeError
    return false;
}

bool VoiceManager::getServerVOIPEnable() {
    // TODO: Implement getServerVOIPEnable
    return false;
}

void VoiceManager::VMServerBan(short var1, bool var2) {
    // TODO: Implement VMServerBan
}

} // namespace raknet
} // namespace core
} // namespace zombie
