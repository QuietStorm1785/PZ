#include "zombie/inventory/types/AlarmClock.h"

namespace zombie {
namespace inventory {
namespace types {

public
AlarmClock::AlarmClock(const std::string &module, const std::string &name,
 const std::string &itemType,
 const std::string &texName) {
 // TODO: Implement AlarmClock
 return nullptr;
}

public
AlarmClock::AlarmClock(const std::string &module, const std::string &name,
 const std::string &itemType, Item item) {
 // TODO: Implement AlarmClock
 return nullptr;
}

void AlarmClock::randomizeAlarm() {
 // TODO: Implement randomizeAlarm
}

IsoGridSquare AlarmClock::getAlarmSquare() {
 // TODO: Implement getAlarmSquare
 return nullptr;
}

bool AlarmClock::shouldUpdateInWorld() {
 // TODO: Implement shouldUpdateInWorld
 return false;
}

void AlarmClock::update() {
 // TODO: Implement update
}

void AlarmClock::updateSound(BaseSoundEmitter emitter) {
 // TODO: Implement updateSound
}

void AlarmClock::wakeUpPlayers(IsoGridSquare square0) {
 // TODO: Implement wakeUpPlayers
}

void AlarmClock::wakeUp(IsoPlayer player) {
 // TODO: Implement wakeUp
}

bool AlarmClock::isRinging() {
 // TODO: Implement isRinging
 return false;
}

bool AlarmClock::finishupdate() {
 // TODO: Implement finishupdate
 return false;
}

bool AlarmClock::isDigital() {
 // TODO: Implement isDigital
 return false;
}

void AlarmClock::DoTooltip(ObjectTooltip tooltipUI,
 ObjectTooltip.Layout layout) {
 // TODO: Implement DoTooltip
}

void AlarmClock::save(ByteBuffer output, bool net) {
 // TODO: Implement save
}

void AlarmClock::load(ByteBuffer input, int WorldVersion) {
 // TODO: Implement load
}

int AlarmClock::getSaveType() {
 // TODO: Implement getSaveType
 return 0;
}

std::string AlarmClock::getCategory() {
 // TODO: Implement getCategory
 return "";
}

void AlarmClock::setAlarmSet(bool _alarmSet) {
 // TODO: Implement setAlarmSet
}

bool AlarmClock::isAlarmSet() {
 // TODO: Implement isAlarmSet
 return false;
}

void AlarmClock::setHour(int hour) {
 // TODO: Implement setHour
}

void AlarmClock::setMinute(int min) {
 // TODO: Implement setMinute
}

int AlarmClock::getHour() {
 // TODO: Implement getHour
 return 0;
}

int AlarmClock::getMinute() {
 // TODO: Implement getMinute
 return 0;
}

void AlarmClock::syncAlarmClock() {
 // TODO: Implement syncAlarmClock
}

IsoPlayer AlarmClock::getOwnerPlayer(ItemContainer container) {
 // TODO: Implement getOwnerPlayer
 return nullptr;
}

void AlarmClock::syncAlarmClock_Player(IsoPlayer player) {
 // TODO: Implement syncAlarmClock_Player
}

void AlarmClock::syncAlarmClock_World() {
 // TODO: Implement syncAlarmClock_World
}

void AlarmClock::syncStopRinging() {
 // TODO: Implement syncStopRinging
}

void AlarmClock::stopRinging() {
 // TODO: Implement stopRinging
}

std::string AlarmClock::getAlarmSound() {
 // TODO: Implement getAlarmSound
 return "";
}

void AlarmClock::setAlarmSound(const std::string &_alarmSound) {
 // TODO: Implement setAlarmSound
}

int AlarmClock::getSoundRadius() {
 // TODO: Implement getSoundRadius
 return 0;
}

void AlarmClock::setSoundRadius(int _soundRadius) {
 // TODO: Implement setSoundRadius
}

} // namespace types
} // namespace inventory
} // namespace zombie
