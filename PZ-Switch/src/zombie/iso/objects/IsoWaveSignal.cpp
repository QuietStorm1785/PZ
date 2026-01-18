#include "zombie/iso/objects/IsoWaveSignal.h"

namespace zombie {
namespace iso {
namespace objects {

public
IsoWaveSignal::IsoWaveSignal(IsoCell cell) {
 // TODO: Implement IsoWaveSignal
 return nullptr;
}

public
IsoWaveSignal::IsoWaveSignal(IsoCell cell, IsoGridSquare sq, IsoSprite spr) {
 // TODO: Implement IsoWaveSignal
 return nullptr;
}

void IsoWaveSignal::init(bool boolean0) {
 // TODO: Implement init
}

DeviceData IsoWaveSignal::cloneDeviceDataFromItem(const std::string &itemfull) {
 // TODO: Implement cloneDeviceDataFromItem
 return nullptr;
}

bool IsoWaveSignal::hasChatToDisplay() {
 // TODO: Implement hasChatToDisplay
 return false;
}

bool IsoWaveSignal::HasPlayerInRange() {
 // TODO: Implement HasPlayerInRange
 return false;
}

float IsoWaveSignal::getDelta() {
 // TODO: Implement getDelta
 return 0;
}

void IsoWaveSignal::setDelta(float delta) {
 // TODO: Implement setDelta
}

DeviceData IsoWaveSignal::getDeviceData() {
 // TODO: Implement getDeviceData
 return nullptr;
}

void IsoWaveSignal::setDeviceData(DeviceData data) {
 // TODO: Implement setDeviceData
}

bool IsoWaveSignal::IsSpeaking() {
 // TODO: Implement IsSpeaking
 return false;
}

std::string IsoWaveSignal::getTalkerType() {
 // TODO: Implement getTalkerType
 return "";
}

void IsoWaveSignal::setTalkerType(const std::string &type) {
 // TODO: Implement setTalkerType
}

std::string IsoWaveSignal::getSayLine() {
 // TODO: Implement getSayLine
 return "";
}

void IsoWaveSignal::Say(const std::string &line) {
 // TODO: Implement Say
}

void IsoWaveSignal::AddDeviceText(const std::string &line, float r, float g,
 float b, const std::string &guid,
 const std::string &codes, int distance) {
 // TODO: Implement AddDeviceText
}

void IsoWaveSignal::AddDeviceText(const std::string &line, int r, int g, int b,
 const std::string &guid,
 const std::string &codes, int distance) {
 // TODO: Implement AddDeviceText
}

void IsoWaveSignal::AddDeviceText(const std::string &line, int r, int g, int b,
 const std::string &guid,
 const std::string &codes, int distance,
 bool attractZombies) {
 // TODO: Implement AddDeviceText
}

void IsoWaveSignal::AddDeviceText(const std::string &line, float r, float g,
 float b, const std::string &guid,
 const std::string &codes, int distance,
 bool attractZombies) {
 // TODO: Implement AddDeviceText
}

void IsoWaveSignal::renderlast() {
 // TODO: Implement renderlast
}

void IsoWaveSignal::renderlastold2() {
 // TODO: Implement renderlastold2
}

bool IsoWaveSignal::playerWithinBounds(IsoPlayer player, float float0) {
 // TODO: Implement playerWithinBounds
 return false;
}

void IsoWaveSignal::update() {
 // TODO: Implement update
}

void IsoWaveSignal::updateLightSource() {
 // TODO: Implement updateLightSource
}

void IsoWaveSignal::removeLightSourceFromWorld() {
 // TODO: Implement removeLightSourceFromWorld
}

void IsoWaveSignal::load(ByteBuffer input, int WorldVersion,
 bool IS_DEBUG_SAVE) {
 // TODO: Implement load
}

void IsoWaveSignal::save(ByteBuffer output, bool IS_DEBUG_SAVE) {
 // TODO: Implement save
}

void IsoWaveSignal::addToWorld() {
 // TODO: Implement addToWorld
}

void IsoWaveSignal::removeFromWorld() {
 // TODO: Implement removeFromWorld
}

void IsoWaveSignal::removeFromSquare() {
 // TODO: Implement removeFromSquare
}

void IsoWaveSignal::saveState(ByteBuffer bb) {
 // TODO: Implement saveState
}

void IsoWaveSignal::loadState(ByteBuffer bb) {
 // TODO: Implement loadState
}

ChatElement IsoWaveSignal::getChatElement() {
 // TODO: Implement getChatElement
 return nullptr;
}

void IsoWaveSignal::Reset() {
 // TODO: Implement Reset
}

} // namespace objects
} // namespace iso
} // namespace zombie
