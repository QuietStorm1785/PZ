#include "zombie/core/raknet/VoiceManager.h"

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

void VoiceManager::VoiceRestartClient(bool boolean0) {
 // TODO: Implement VoiceRestartClient
}

void VoiceManager::VoiceInitClient() {
 // TODO: Implement VoiceInitClient
}

void VoiceManager::VoiceInitServer(bool boolean0, int int1, int int0, int int2,
 int int3, double double1, double double0,
 bool boolean1) {
 // TODO: Implement VoiceInitServer
}

void VoiceManager::VoiceConnectAccept(long long0) {
 // TODO: Implement VoiceConnectAccept
}

void VoiceManager::InitRecDeviceForTest() {
 // TODO: Implement InitRecDeviceForTest
}

void VoiceManager::VoiceOpenChannelReply(long long0, ByteBuffer byteBuffer) {
 // TODO: Implement VoiceOpenChannelReply
}

void VoiceManager::VoiceConnectReq(long long0) {
 // TODO: Implement VoiceConnectReq
}

void VoiceManager::VoiceConnectClose(long long0) {
 // TODO: Implement VoiceConnectClose
}

void VoiceManager::setMode(int int0) {
 // TODO: Implement setMode
}

void VoiceManager::setVADMode(int int0) {
 // TODO: Implement setVADMode
}

void VoiceManager::setAGCMode(int int0) {
 // TODO: Implement setAGCMode
}

void VoiceManager::setVolumePlayers(int int0) {
 // TODO: Implement setVolumePlayers
}

void VoiceManager::setVolumeMic(int int0) {
 // TODO: Implement setVolumeMic
}

void VoiceManager::playerSetMute(const std::string &string) {
 // TODO: Implement playerSetMute
}

bool VoiceManager::playerGetMute(const std::string &string) {
 // TODO: Implement playerGetMute
 return false;
}

void VoiceManager::LuaRegister(Platform platform, KahluaTable table1) {
 // TODO: Implement LuaRegister
}

int VoiceManager::call(LuaCallFrame luaCallFrame, int var2) {
 // TODO: Implement call
 return 0;
}

int VoiceManager::call(LuaCallFrame luaCallFrame, int var2) {
 // TODO: Implement call
 return 0;
}

int VoiceManager::call(LuaCallFrame luaCallFrame, int var2) {
 // TODO: Implement call
 return 0;
}

void VoiceManager::setUserPlaySound(long long0, float float0) {
 // TODO: Implement setUserPlaySound
}

long VoiceManager::getUserPlaySound(short short0) {
 // TODO: Implement getUserPlaySound
 return 0;
}

void VoiceManager::InitVMClient() {
 // TODO: Implement InitVMClient
}

void VoiceManager::run() {
 // TODO: Implement run
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

void VoiceManager::setTestingMicrophone(bool boolean0) {
 // TODO: Implement setTestingMicrophone
}

void VoiceManager::notifyThread() {
 // TODO: Implement notifyThread
}

void VoiceManager::update() {
 // TODO: Implement update
}

float VoiceManager::getCanHearAllVolume(float float0) {
 // TODO: Implement getCanHearAllVolume
 return 0;
}

void VoiceManager::threadSafeCode(Runnable runnable) {
 // TODO: Implement threadSafeCode
}

void VoiceManager::logFrame(IsoPlayer player1, IsoPlayer player0,
 float float0) {
 // TODO: Implement logFrame
}

void VoiceManager::UpdateChannelsRoaming(UdpConnection udpConnection) {
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

void VoiceManager::VMServerBan(short short0, bool boolean0) {
 // TODO: Implement VMServerBan
}

} // namespace raknet
} // namespace core
} // namespace zombie
