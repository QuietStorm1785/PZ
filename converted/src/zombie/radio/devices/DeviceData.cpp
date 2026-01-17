#include "zombie/radio/devices/DeviceData.h"

namespace zombie {
namespace radio {
namespace devices {

public
DeviceData::DeviceData() {
  // TODO: Implement DeviceData
  return nullptr;
}

public
DeviceData::DeviceData(WaveSignalDevice _parent) {
  // TODO: Implement DeviceData
  return nullptr;
}

void DeviceData::generatePresets() {
  // TODO: Implement generatePresets
}

void *DeviceData::clone() {
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

void DeviceData::setParent(WaveSignalDevice p) {
  // TODO: Implement setParent
}

DevicePresets DeviceData::getDevicePresets() {
  // TODO: Implement getDevicePresets
  return {};
}

void DeviceData::setDevicePresets(DevicePresets p) {
  // TODO: Implement setDevicePresets
}

void DeviceData::cloneDevicePresets(DevicePresets p) {
  // TODO: Implement cloneDevicePresets
}

int DeviceData::getMinChannelRange() {
  // TODO: Implement getMinChannelRange
  return 0;
}

void DeviceData::setMinChannelRange(int i) {
  // TODO: Implement setMinChannelRange
}

int DeviceData::getMaxChannelRange() {
  // TODO: Implement getMaxChannelRange
  return 0;
}

void DeviceData::setMaxChannelRange(int i) {
  // TODO: Implement setMaxChannelRange
}

bool DeviceData::getIsHighTier() {
  // TODO: Implement getIsHighTier
  return false;
}

void DeviceData::setIsHighTier(bool b) {
  // TODO: Implement setIsHighTier
}

bool DeviceData::getIsBatteryPowered() {
  // TODO: Implement getIsBatteryPowered
  return false;
}

void DeviceData::setIsBatteryPowered(bool b) {
  // TODO: Implement setIsBatteryPowered
}

bool DeviceData::getHasBattery() {
  // TODO: Implement getHasBattery
  return false;
}

void DeviceData::setHasBattery(bool b) {
  // TODO: Implement setHasBattery
}

void DeviceData::addBattery(DrainableComboItem bat) {
  // TODO: Implement addBattery
}

InventoryItem DeviceData::getBattery(ItemContainer inventory) {
  // TODO: Implement getBattery
  return nullptr;
}

void DeviceData::transmitBattryChange() {
  // TODO: Implement transmitBattryChange
}

void DeviceData::addHeadphones(InventoryItem headphones) {
  // TODO: Implement addHeadphones
}

InventoryItem DeviceData::getHeadphones(ItemContainer inventory) {
  // TODO: Implement getHeadphones
  return nullptr;
}

int DeviceData::getMicRange() {
  // TODO: Implement getMicRange
  return 0;
}

void DeviceData::setMicRange(int i) {
  // TODO: Implement setMicRange
}

bool DeviceData::getMicIsMuted() {
  // TODO: Implement getMicIsMuted
  return false;
}

void DeviceData::setMicIsMuted(bool b) {
  // TODO: Implement setMicIsMuted
}

int DeviceData::getHeadphoneType() {
  // TODO: Implement getHeadphoneType
  return 0;
}

void DeviceData::setHeadphoneType(int i) {
  // TODO: Implement setHeadphoneType
}

float DeviceData::getBaseVolumeRange() {
  // TODO: Implement getBaseVolumeRange
  return 0;
}

void DeviceData::setBaseVolumeRange(float f) {
  // TODO: Implement setBaseVolumeRange
}

float DeviceData::getDeviceVolume() {
  // TODO: Implement getDeviceVolume
  return 0;
}

void DeviceData::setDeviceVolume(float f) {
  // TODO: Implement setDeviceVolume
}

void DeviceData::setDeviceVolumeRaw(float f) {
  // TODO: Implement setDeviceVolumeRaw
}

bool DeviceData::getIsTelevision() {
  // TODO: Implement getIsTelevision
  return false;
}

void DeviceData::setIsTelevision(bool b) {
  // TODO: Implement setIsTelevision
}

std::string DeviceData::getDeviceName() {
  // TODO: Implement getDeviceName
  return "";
}

void DeviceData::setDeviceName(const std::string &name) {
  // TODO: Implement setDeviceName
}

bool DeviceData::getIsTwoWay() {
  // TODO: Implement getIsTwoWay
  return false;
}

void DeviceData::setIsTwoWay(bool b) {
  // TODO: Implement setIsTwoWay
}

int DeviceData::getTransmitRange() {
  // TODO: Implement getTransmitRange
  return 0;
}

void DeviceData::setTransmitRange(int range) {
  // TODO: Implement setTransmitRange
}

bool DeviceData::getIsPortable() {
  // TODO: Implement getIsPortable
  return false;
}

void DeviceData::setIsPortable(bool b) {
  // TODO: Implement setIsPortable
}

bool DeviceData::getIsTurnedOn() {
  // TODO: Implement getIsTurnedOn
  return false;
}

void DeviceData::setIsTurnedOn(bool b) {
  // TODO: Implement setIsTurnedOn
}

void DeviceData::setTurnedOnRaw(bool b) {
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

void DeviceData::setChannel(int c) {
  // TODO: Implement setChannel
}

void DeviceData::setChannel(int chan, bool setislistening) {
  // TODO: Implement setChannel
}

void DeviceData::setChannelRaw(int chan) {
  // TODO: Implement setChannelRaw
}

float DeviceData::getUseDelta() {
  // TODO: Implement getUseDelta
  return 0;
}

void DeviceData::setUseDelta(float f) {
  // TODO: Implement setUseDelta
}

float DeviceData::getPower() {
  // TODO: Implement getPower
  return 0;
}

void DeviceData::setPower(float p) {
  // TODO: Implement setPower
}

void DeviceData::setInitialPower() {
  // TODO: Implement setInitialPower
}

void DeviceData::TriggerPlayerListening(bool listening) {
  // TODO: Implement TriggerPlayerListening
}

void DeviceData::playSoundSend(const std::string &soundname,
                               bool useDeviceVolume) {
  // TODO: Implement playSoundSend
}

void DeviceData::playSoundLocal(const std::string &soundname,
                                bool useDeviceVolume) {
  // TODO: Implement playSoundLocal
}

void DeviceData::playSound(const std::string &soundname, float volume,
                           bool transmit) {
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

void DeviceData::update(bool isIso, bool playerInRange) {
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

void DeviceData::doReceiveSignal(int distance) {
  // TODO: Implement doReceiveSignal
}

void DeviceData::doReceiveMPSignal(float distance) {
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

void DeviceData::transmitDeviceDataState(short short0) {
  // TODO: Implement transmitDeviceDataState
}

void DeviceData::transmitDeviceDataStateServer(short short0,
                                               UdpConnection udpConnection1) {
  // TODO: Implement transmitDeviceDataStateServer
}

void DeviceData::sendDeviceDataStatePacket(UdpConnection udpConnection,
                                           short short0) {
  // TODO: Implement sendDeviceDataStatePacket
}

void DeviceData::receiveDeviceDataStatePacket(ByteBuffer bb,
                                              UdpConnection ignoreConnection) {
  // TODO: Implement receiveDeviceDataStatePacket
}

void DeviceData::save(ByteBuffer output, bool net) {
  // TODO: Implement save
}

void DeviceData::load(ByteBuffer input, int WorldVersion, bool net) {
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

void DeviceData::setMediaIndex(short _mediaIndex) {
  // TODO: Implement setMediaIndex
}

uint8_t DeviceData::getMediaType() {
  // TODO: Implement getMediaType
  return 0;
}

void DeviceData::setMediaType(uint8_t _mediaType) {
  // TODO: Implement setMediaType
}

void DeviceData::addMediaItem(InventoryItem media) {
  // TODO: Implement addMediaItem
}

InventoryItem DeviceData::removeMediaItem(ItemContainer inventory) {
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

void DeviceData::setNoTransmit(bool _noTransmit) {
  // TODO: Implement setNoTransmit
}

} // namespace devices
} // namespace radio
} // namespace zombie
