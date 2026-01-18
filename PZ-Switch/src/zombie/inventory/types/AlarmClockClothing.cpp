#include "zombie/inventory/types/AlarmClockClothing.h"

namespace zombie {
namespace inventory {
namespace types {

public
AlarmClockClothing::AlarmClockClothing(const std::string &module,
 const std::string &name,
 const std::string &itemType,
 const std::string &texName,
 const std::string &palette,
 const std::string &SpriteName) {
 // TODO: Implement AlarmClockClothing
 return nullptr;
}

public
AlarmClockClothing::AlarmClockClothing(const std::string &module,
 const std::string &name,
 const std::string &itemType, Item item,
 const std::string &palette,
 const std::string &SpriteName) {
 // TODO: Implement AlarmClockClothing
 return nullptr;
}

void AlarmClockClothing::randomizeAlarm() {
 // TODO: Implement randomizeAlarm
}

IsoGridSquare AlarmClockClothing::getAlarmSquare() {
 // TODO: Implement getAlarmSquare
 return nullptr;
}

bool AlarmClockClothing::shouldUpdateInWorld() {
 // TODO: Implement shouldUpdateInWorld
 return false;
}

void AlarmClockClothing::update() {
 // TODO: Implement update
}

void AlarmClockClothing::updateSound(BaseSoundEmitter emitter) {
 // TODO: Implement updateSound
}

void AlarmClockClothing::wakeUpPlayers(IsoGridSquare square0) {
 // TODO: Implement wakeUpPlayers
}

void AlarmClockClothing::wakeUp(IsoPlayer player) {
 // TODO: Implement wakeUp
}

bool AlarmClockClothing::isRinging() {
 // TODO: Implement isRinging
 return false;
}

bool AlarmClockClothing::finishupdate() {
 // TODO: Implement finishupdate
 return false;
}

void AlarmClockClothing::DoTooltip(ObjectTooltip tooltipUI,
 ObjectTooltip.Layout layout) {
 // TODO: Implement DoTooltip
}

void AlarmClockClothing::save(ByteBuffer output, bool net) {
 // TODO: Implement save
}

void AlarmClockClothing::load(ByteBuffer input, int WorldVersion) {
 // TODO: Implement load
}

int AlarmClockClothing::getSaveType() {
 // TODO: Implement getSaveType
 return 0;
}

std::string AlarmClockClothing::getCategory() {
 // TODO: Implement getCategory
 return "";
}

void AlarmClockClothing::setAlarmSet(bool _alarmSet) {
 // TODO: Implement setAlarmSet
}

bool AlarmClockClothing::isAlarmSet() {
 // TODO: Implement isAlarmSet
 return false;
}

void AlarmClockClothing::setHour(int hour) {
 // TODO: Implement setHour
}

void AlarmClockClothing::setMinute(int min) {
 // TODO: Implement setMinute
}

int AlarmClockClothing::getHour() {
 // TODO: Implement getHour
 return 0;
}

int AlarmClockClothing::getMinute() {
 // TODO: Implement getMinute
 return 0;
}

void AlarmClockClothing::syncAlarmClock() {
 // TODO: Implement syncAlarmClock
}

IsoPlayer AlarmClockClothing::getOwnerPlayer(ItemContainer container) {
 // TODO: Implement getOwnerPlayer
 return nullptr;
}

void AlarmClockClothing::syncAlarmClock_Player(IsoPlayer player) {
 // TODO: Implement syncAlarmClock_Player
}

void AlarmClockClothing::syncAlarmClock_World() {
 // TODO: Implement syncAlarmClock_World
}

void AlarmClockClothing::syncStopRinging() {
 // TODO: Implement syncStopRinging
}

void AlarmClockClothing::stopRinging() {
 // TODO: Implement stopRinging
}

std::string AlarmClockClothing::getAlarmSound() {
 // TODO: Implement getAlarmSound
 return "";
}

void AlarmClockClothing::setAlarmSound(const std::string &_alarmSound) {
 // TODO: Implement setAlarmSound
}

int AlarmClockClothing::getSoundRadius() {
 // TODO: Implement getSoundRadius
 return 0;
}

void AlarmClockClothing::setSoundRadius(int _soundRadius) {
 // TODO: Implement setSoundRadius
}

bool AlarmClockClothing::isDigital() {
 // TODO: Implement isDigital
 return false;
}

} // namespace types
} // namespace inventory
} // namespace zombie
