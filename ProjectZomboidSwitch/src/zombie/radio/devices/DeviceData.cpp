#include <cstdint>
#include <string>
#include "zombie\radio\devices/DeviceData.h"

namespace zombie {
namespace radio {
namespace devices {

public DeviceData::DeviceData() {
    // TODO: Implement DeviceData
    return nullptr;
}

public DeviceData::DeviceData(WaveSignalDevice var1) {
    // TODO: Implement DeviceData
    return nullptr;
}

void DeviceData::generatePresets() {
    // TODO: Implement generatePresets
}

void* DeviceData::clone() {
    // TODO: Implement clone
    return nullptr;
}

DeviceData DeviceData::getClone() {
    // TODO: Implement getClone
    return nullptr;
}

WaveSignalDevice DeviceData::getParent() {
    // TODO: Implement getParent
    return nullptr;
}

void DeviceData::setParent(WaveSignalDevice var1) {
    // TODO: Implement setParent
}

DevicePresets DeviceData::getDevicePresets() {
    // TODO: Implement getDevicePresets
    return {};
}

void DeviceData::setDevicePresets(DevicePresets var1) {
    // TODO: Implement setDevicePresets
}

void DeviceData::cloneDevicePresets(DevicePresets var1) {
    // TODO: Implement cloneDevicePresets
}

int DeviceData::getMinChannelRange() {
    // TODO: Implement getMinChannelRange
    return 0;
}

void DeviceData::setMinChannelRange(int var1) {
    // TODO: Implement setMinChannelRange
}

int DeviceData::getMaxChannelRange() {
    // TODO: Implement getMaxChannelRange
    return 0;
}

void DeviceData::setMaxChannelRange(int var1) {
    // TODO: Implement setMaxChannelRange
}

bool DeviceData::getIsHighTier() {
    // TODO: Implement getIsHighTier
    return false;
}

void DeviceData::setIsHighTier(bool var1) {
    // TODO: Implement setIsHighTier
}

bool DeviceData::getIsBatteryPowered() {
    // TODO: Implement getIsBatteryPowered
    return false;
}

void DeviceData::setIsBatteryPowered(bool var1) {
    // TODO: Implement setIsBatteryPowered
}

bool DeviceData::getHasBattery() {
    // TODO: Implement getHasBattery
    return false;
}

void DeviceData::setHasBattery(bool var1) {
    // TODO: Implement setHasBattery
}

void DeviceData::addBattery(DrainableComboItem var1) {
    // TODO: Implement addBattery
}

InventoryItem DeviceData::getBattery(ItemContainer var1) {
    // TODO: Implement getBattery
    return nullptr;
}

void DeviceData::transmitBattryChange() {
    // TODO: Implement transmitBattryChange
}

void DeviceData::addHeadphones(InventoryItem var1) {
    // TODO: Implement addHeadphones
}

InventoryItem DeviceData::getHeadphones(ItemContainer var1) {
    // TODO: Implement getHeadphones
    return nullptr;
}

int DeviceData::getMicRange() {
    // TODO: Implement getMicRange
    return 0;
}

void DeviceData::setMicRange(int var1) {
    // TODO: Implement setMicRange
}

bool DeviceData::getMicIsMuted() {
    // TODO: Implement getMicIsMuted
    return false;
}

void DeviceData::setMicIsMuted(bool var1) {
    // TODO: Implement setMicIsMuted
}

int DeviceData::getHeadphoneType() {
    // TODO: Implement getHeadphoneType
    return 0;
}

void DeviceData::setHeadphoneType(int var1) {
    // TODO: Implement setHeadphoneType
}

float DeviceData::getBaseVolumeRange() {
    // TODO: Implement getBaseVolumeRange
    return 0;
}

void DeviceData::setBaseVolumeRange(float var1) {
    // TODO: Implement setBaseVolumeRange
}

float DeviceData::getDeviceVolume() {
    // TODO: Implement getDeviceVolume
    return 0;
}

void DeviceData::setDeviceVolume(float var1) {
    // TODO: Implement setDeviceVolume
}

void DeviceData::setDeviceVolumeRaw(float var1) {
    // TODO: Implement setDeviceVolumeRaw
}

bool DeviceData::getIsTelevision() {
    // TODO: Implement getIsTelevision
    return false;
}

void DeviceData::setIsTelevision(bool var1) {
    // TODO: Implement setIsTelevision
}

std::string DeviceData::getDeviceName() {
    // TODO: Implement getDeviceName
    return "";
}

void DeviceData::setDeviceName(const std::string& var1) {
    // TODO: Implement setDeviceName
}

bool DeviceData::getIsTwoWay() {
    // TODO: Implement getIsTwoWay
    return false;
}

void DeviceData::setIsTwoWay(bool var1) {
    // TODO: Implement setIsTwoWay
}

int DeviceData::getTransmitRange() {
    // TODO: Implement getTransmitRange
    return 0;
}

void DeviceData::setTransmitRange(int var1) {
    // TODO: Implement setTransmitRange
}

bool DeviceData::getIsPortable() {
    // TODO: Implement getIsPortable
    return false;
}

void DeviceData::setIsPortable(bool var1) {
    // TODO: Implement setIsPortable
}

bool DeviceData::getIsTurnedOn() {
    // TODO: Implement getIsTurnedOn
    return false;
}

void DeviceData::setIsTurnedOn(bool var1) {
    // TODO: Implement setIsTurnedOn
}

void DeviceData::setTurnedOnRaw(bool var1) {
    // TODO: Implement setTurnedOnRaw
}

bool DeviceData::canBePoweredHere() {
    // TODO: Implement canBePoweredHere
    return false;
}

void DeviceData::setRandomChannel() {
    // TODO: Implement setRandomChannel
}

int DeviceData::getChannel() {
    // TODO: Implement getChannel
    return 0;
}

void DeviceData::setChannel(int var1) {
    // TODO: Implement setChannel
}

void DeviceData::setChannel(int var1, bool var2) {
    // TODO: Implement setChannel
}

void DeviceData::setChannelRaw(int var1) {
    // TODO: Implement setChannelRaw
}

float DeviceData::getUseDelta() {
    // TODO: Implement getUseDelta
    return 0;
}

void DeviceData::setUseDelta(float var1) {
    // TODO: Implement setUseDelta
}

float DeviceData::getPower() {
    // TODO: Implement getPower
    return 0;
}

void DeviceData::setPower(float var1) {
    // TODO: Implement setPower
}

void DeviceData::setInitialPower() {
    // TODO: Implement setInitialPower
}

void DeviceData::TriggerPlayerListening(bool var1) {
    // TODO: Implement TriggerPlayerListening
}

void DeviceData::playSoundSend(const std::string& var1, bool var2) {
    // TODO: Implement playSoundSend
}

void DeviceData::playSoundLocal(const std::string& var1, bool var2) {
    // TODO: Implement playSoundLocal
}

void DeviceData::playSound(const std::string& var1, float var2, bool var3) {
    // TODO: Implement playSound
}

void DeviceData::cleanSoundsAndEmitter() {
    // TODO: Implement cleanSoundsAndEmitter
}

void DeviceData::setEmitterAndPos() {
    // TODO: Implement setEmitterAndPos
}

void DeviceData::updateEmitter() {
    // TODO: Implement updateEmitter
}

BaseSoundEmitter DeviceData::getEmitter() {
    // TODO: Implement getEmitter
    return nullptr;
}

void DeviceData::update(bool var1, bool var2) {
    // TODO: Implement update
}

void DeviceData::updateSimple() {
    // TODO: Implement updateSimple
}

void DeviceData::updateStaticSounds() {
    // TODO: Implement updateStaticSounds
}

void DeviceData::setNextStaticSound() {
    // TODO: Implement setNextStaticSound
}

int DeviceData::getDeviceVolumeRange() {
    // TODO: Implement getDeviceVolumeRange
    return 0;
}

int DeviceData::getDeviceSoundVolumeRange() {
    // TODO: Implement getDeviceSoundVolumeRange
    return 0;
}

void DeviceData::doReceiveSignal(int var1) {
    // TODO: Implement doReceiveSignal
}

void DeviceData::doReceiveMPSignal(float var1) {
    // TODO: Implement doReceiveMPSignal
}

bool DeviceData::isReceivingSignal() {
    // TODO: Implement isReceivingSignal
    return false;
}

int DeviceData::getLastRecordedDistance() {
    // TODO: Implement getLastRecordedDistance
    return 0;
}

bool DeviceData::isIsoDevice() {
    // TODO: Implement isIsoDevice
    return false;
}

bool DeviceData::isInventoryDevice() {
    // TODO: Implement isInventoryDevice
    return false;
}

bool DeviceData::isVehicleDevice() {
    // TODO: Implement isVehicleDevice
    return false;
}

void DeviceData::transmitPresets() {
    // TODO: Implement transmitPresets
}

void DeviceData::transmitDeviceDataState(short var1) {
    // TODO: Implement transmitDeviceDataState
}

void DeviceData::transmitDeviceDataStateServer(short var1, UdpConnection var2) {
    // TODO: Implement transmitDeviceDataStateServer
}

void DeviceData::sendDeviceDataStatePacket(UdpConnection var1, short var2) {
    // TODO: Implement sendDeviceDataStatePacket
}

void DeviceData::receiveDeviceDataStatePacket(ByteBuffer var1, UdpConnection var2) {
    // TODO: Implement receiveDeviceDataStatePacket
}

void DeviceData::save(ByteBuffer var1, bool var2) {
    // TODO: Implement save
}

void DeviceData::load(ByteBuffer var1, int var2, bool var3) {
    // TODO: Implement load
}

bool DeviceData::hasMedia() {
    // TODO: Implement hasMedia
    return false;
}

short DeviceData::getMediaIndex() {
    // TODO: Implement getMediaIndex
    return 0;
}

void DeviceData::setMediaIndex(short var1) {
    // TODO: Implement setMediaIndex
}

uint8_t DeviceData::getMediaType() {
    // TODO: Implement getMediaType
    return 0;
}

void DeviceData::setMediaType(uint8_t var1) {
    // TODO: Implement setMediaType
}

void DeviceData::addMediaItem(InventoryItem var1) {
    // TODO: Implement addMediaItem
}

InventoryItem DeviceData::removeMediaItem(ItemContainer var1) {
    // TODO: Implement removeMediaItem
    return nullptr;
}

bool DeviceData::isPlayingMedia() {
    // TODO: Implement isPlayingMedia
    return false;
}

void DeviceData::StartPlayMedia() {
    // TODO: Implement StartPlayMedia
}

void DeviceData::prePlayingMedia() {
    // TODO: Implement prePlayingMedia
}

void DeviceData::postPlayingMedia() {
    // TODO: Implement postPlayingMedia
}

void DeviceData::televisionMediaSwitch() {
    // TODO: Implement televisionMediaSwitch
}

void DeviceData::StopPlayMedia() {
    // TODO: Implement StopPlayMedia
}

void DeviceData::updateMediaPlaying() {
    // TODO: Implement updateMediaPlaying
}

MediaData DeviceData::getMediaData() {
    // TODO: Implement getMediaData
    return nullptr;
}

bool DeviceData::isNoTransmit() {
    // TODO: Implement isNoTransmit
    return false;
}

void DeviceData::setNoTransmit(bool var1) {
    // TODO: Implement setNoTransmit
}

} // namespace devices
} // namespace radio
} // namespace zombie
