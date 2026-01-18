#include "zombie/radio/devices/DevicePresets.h"

namespace zombie {
namespace radio {
namespace devices {

void *DevicePresets::clone() {
  // TODO: Implement clone
  return nullptr;
}

KahluaTable DevicePresets::getPresetsLua() {
  // TODO: Implement getPresetsLua
  return nullptr;
}

void DevicePresets::setPresets(ArrayList<PresetEntry> p) {
  // TODO: Implement setPresets
}

int DevicePresets::getMaxPresets() {
  // TODO: Implement getMaxPresets
  return 0;
}

void DevicePresets::setMaxPresets(int m) {
  // TODO: Implement setMaxPresets
}

void DevicePresets::addPreset(const std::string &name, int frequency) {
  // TODO: Implement addPreset
}

void DevicePresets::removePreset(int id) {
  // TODO: Implement removePreset
}

std::string DevicePresets::getPresetName(int id) {
  // TODO: Implement getPresetName
  return "";
}

int DevicePresets::getPresetFreq(int id) {
  // TODO: Implement getPresetFreq
  return 0;
}

void DevicePresets::setPresetName(int id, const std::string &name) {
  // TODO: Implement setPresetName
}

void DevicePresets::setPresetFreq(int id, int frequency) {
  // TODO: Implement setPresetFreq
}

void DevicePresets::setPreset(int id, const std::string &name, int frequency) {
  // TODO: Implement setPreset
}

void DevicePresets::clearPresets() {
  // TODO: Implement clearPresets
}

void DevicePresets::save(ByteBuffer output, bool net) {
  // TODO: Implement save
}

void DevicePresets::load(ByteBuffer input, int WorldVersion, bool net) {
  // TODO: Implement load
}

} // namespace devices
} // namespace radio
} // namespace zombie
