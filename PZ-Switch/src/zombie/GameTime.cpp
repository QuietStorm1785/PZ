#include "zombie/GameTime.h"

namespace zombie {

public
GameTime::GameTime() {
 // TODO: Implement GameTime
 return nullptr;
}

GameTime GameTime::getInstance() {
 // TODO: Implement getInstance
 return nullptr;
}

void GameTime::setInstance(GameTime aInstance) {
 // TODO: Implement setInstance
}

void GameTime::syncServerTime(long timeClientSend, long timeServer,
 long timeClientReceive) {
 // TODO: Implement syncServerTime
}

long GameTime::getServerTime() {
 // TODO: Implement getServerTime
 return 0;
}

long GameTime::getServerTimeMills() {
 // TODO: Implement getServerTimeMills
 return 0;
}

bool GameTime::getServerTimeShiftIsSet() {
 // TODO: Implement getServerTimeShiftIsSet
 return false;
}

void GameTime::setServerTimeShift(long tshift) {
 // TODO: Implement setServerTimeShift
}

void GameTime::sendTimeSync() {
 // TODO: Implement sendTimeSync
}

void GameTime::receiveTimeSync(ByteBuffer bb, UdpConnection connection) {
 // TODO: Implement receiveTimeSync
}

float GameTime::getRealworldSecondsSinceLastUpdate() {
 // TODO: Implement getRealworldSecondsSinceLastUpdate
 return 0;
}

float GameTime::getMultipliedSecondsSinceLastUpdate() {
 // TODO: Implement getMultipliedSecondsSinceLastUpdate
 return 0;
}

float GameTime::getGameWorldSecondsSinceLastUpdate() {
 // TODO: Implement getGameWorldSecondsSinceLastUpdate
 return 0;
}

int GameTime::daysInMonth(int year, int month) {
 // TODO: Implement daysInMonth
 return 0;
}

std::string GameTime::getDeathString(IsoPlayer playerObj) {
 // TODO: Implement getDeathString
 return "";
}

int GameTime::getDaysSurvived() {
 // TODO: Implement getDaysSurvived
 return 0;
}

std::string GameTime::getTimeSurvived(IsoPlayer playerObj) {
 // TODO: Implement getTimeSurvived
 return "";
}

std::string GameTime::getZombieKilledText(IsoPlayer playerObj) {
 // TODO: Implement getZombieKilledText
 return "";
}

std::string GameTime::getGameModeText() {
 // TODO: Implement getGameModeText
 return "";
}

void GameTime::init() {
 // TODO: Implement init
}

float GameTime::Lerp(float start, float end, float delta) {
 // TODO: Implement Lerp
 return 0;
}

void GameTime::RemoveZombiesIndiscriminate(int i) {
 // TODO: Implement RemoveZombiesIndiscriminate
}

float GameTime::TimeLerp(float startVal, float endVal, float startTime,
 float endTime) {
 // TODO: Implement TimeLerp
 return 0;
}

float GameTime::getDeltaMinutesPerDay() {
 // TODO: Implement getDeltaMinutesPerDay
 return 0;
}

float GameTime::getNightMin() {
 // TODO: Implement getNightMin
 return 0;
}

void GameTime::setNightMin(float min) {
 // TODO: Implement setNightMin
}

float GameTime::getNightMax() {
 // TODO: Implement getNightMax
 return 0;
}

void GameTime::setNightMax(float max) {
 // TODO: Implement setNightMax
}

int GameTime::getMinutes() {
 // TODO: Implement getMinutes
 return 0;
}

void GameTime::setMoon(float moon) {
 // TODO: Implement setMoon
}

void GameTime::update(bool bSleeping) {
 // TODO: Implement update
}

void GameTime::updateRoomLight() {
 // TODO: Implement updateRoomLight
}

void GameTime::setMinutesStamp() {
 // TODO: Implement setMinutesStamp
}

long GameTime::getMinutesStamp() {
 // TODO: Implement getMinutesStamp
 return 0;
}

bool GameTime::getThunderStorm() {
 // TODO: Implement getThunderStorm
 return false;
}

void GameTime::doMetaEvents() {
 // TODO: Implement doMetaEvents
}

float GameTime::getAmbient() {
 // TODO: Implement getAmbient
 return 0;
}

void GameTime::setAmbient(float _Ambient) {
 // TODO: Implement setAmbient
}

float GameTime::getAmbientMax() {
 // TODO: Implement getAmbientMax
 return 0;
}

void GameTime::setAmbientMax(float _AmbientMax) {
 // TODO: Implement setAmbientMax
}

float GameTime::getAmbientMin() {
 // TODO: Implement getAmbientMin
 return 0;
}

void GameTime::setAmbientMin(float _AmbientMin) {
 // TODO: Implement setAmbientMin
}

int GameTime::getDay() {
 // TODO: Implement getDay
 return 0;
}

int GameTime::getDayPlusOne() {
 // TODO: Implement getDayPlusOne
 return 0;
}

void GameTime::setDay(int _Day) {
 // TODO: Implement setDay
}

int GameTime::getStartDay() {
 // TODO: Implement getStartDay
 return 0;
}

void GameTime::setStartDay(int _StartDay) {
 // TODO: Implement setStartDay
}

float GameTime::getMaxZombieCountStart() {
 // TODO: Implement getMaxZombieCountStart
 return 0;
}

void GameTime::setMaxZombieCountStart(float _MaxZombieCountStart) {
 // TODO: Implement setMaxZombieCountStart
}

float GameTime::getMinZombieCountStart() {
 // TODO: Implement getMinZombieCountStart
 return 0;
}

void GameTime::setMinZombieCountStart(float _MinZombieCountStart) {
 // TODO: Implement setMinZombieCountStart
}

float GameTime::getMaxZombieCount() {
 // TODO: Implement getMaxZombieCount
 return 0;
}

void GameTime::setMaxZombieCount(float _MaxZombieCount) {
 // TODO: Implement setMaxZombieCount
}

float GameTime::getMinZombieCount() {
 // TODO: Implement getMinZombieCount
 return 0;
}

void GameTime::setMinZombieCount(float _MinZombieCount) {
 // TODO: Implement setMinZombieCount
}

int GameTime::getMonth() {
 // TODO: Implement getMonth
 return 0;
}

void GameTime::setMonth(int _Month) {
 // TODO: Implement setMonth
}

int GameTime::getStartMonth() {
 // TODO: Implement getStartMonth
 return 0;
}

void GameTime::setStartMonth(int _StartMonth) {
 // TODO: Implement setStartMonth
}

float GameTime::getNightTint() {
 // TODO: Implement getNightTint
 return 0;
}

void GameTime::setNightTint(float NightTint) {
 // TODO: Implement setNightTint
}

float GameTime::getNight() {
 // TODO: Implement getNight
 return 0;
}

void GameTime::setNight(float NightTint) {
 // TODO: Implement setNight
}

float GameTime::getTimeOfDay() {
 // TODO: Implement getTimeOfDay
 return 0;
}

void GameTime::setTimeOfDay(float _TimeOfDay) {
 // TODO: Implement setTimeOfDay
}

float GameTime::getStartTimeOfDay() {
 // TODO: Implement getStartTimeOfDay
 return 0;
}

void GameTime::setStartTimeOfDay(float _StartTimeOfDay) {
 // TODO: Implement setStartTimeOfDay
}

float GameTime::getViewDist() {
 // TODO: Implement getViewDist
 return 0;
}

float GameTime::getViewDistMax() {
 // TODO: Implement getViewDistMax
 return 0;
}

void GameTime::setViewDistMax(float _ViewDistMax) {
 // TODO: Implement setViewDistMax
}

float GameTime::getViewDistMin() {
 // TODO: Implement getViewDistMin
 return 0;
}

void GameTime::setViewDistMin(float _ViewDistMin) {
 // TODO: Implement setViewDistMin
}

int GameTime::getYear() {
 // TODO: Implement getYear
 return 0;
}

void GameTime::setYear(int _Year) {
 // TODO: Implement setYear
}

int GameTime::getStartYear() {
 // TODO: Implement getStartYear
 return 0;
}

void GameTime::setStartYear(int _StartYear) {
 // TODO: Implement setStartYear
}

int GameTime::getNightsSurvived() {
 // TODO: Implement getNightsSurvived
 return 0;
}

void GameTime::setNightsSurvived(int _NightsSurvived) {
 // TODO: Implement setNightsSurvived
}

double GameTime::getWorldAgeHours() {
 // TODO: Implement getWorldAgeHours
 return 0;
}

double GameTime::getHoursSurvived() {
 // TODO: Implement getHoursSurvived
 return 0;
}

void GameTime::setHoursSurvived(double _HoursSurvived) {
 // TODO: Implement setHoursSurvived
}

int GameTime::getHour() {
 // TODO: Implement getHour
 return 0;
}

PZCalendar GameTime::getCalender() {
 // TODO: Implement getCalender
 return nullptr;
}

void GameTime::setCalender(PZCalendar _Calender) {
 // TODO: Implement setCalender
}

void GameTime::updateCalendar(int year, int month, int dayOfMonth,
 int hourOfDay, int minute) {
 // TODO: Implement updateCalendar
}

float GameTime::getMinutesPerDay() {
 // TODO: Implement getMinutesPerDay
 return 0;
}

void GameTime::setMinutesPerDay(float _MinutesPerDay) {
 // TODO: Implement setMinutesPerDay
}

float GameTime::getLastTimeOfDay() {
 // TODO: Implement getLastTimeOfDay
 return 0;
}

void GameTime::setLastTimeOfDay(float _LastTimeOfDay) {
 // TODO: Implement setLastTimeOfDay
}

void GameTime::setTargetZombies(int _TargetZombies) {
 // TODO: Implement setTargetZombies
}

bool GameTime::isRainingToday() {
 // TODO: Implement isRainingToday
 return false;
}

float GameTime::getMultiplier() {
 // TODO: Implement getMultiplier
 return 0;
}

float GameTime::getTimeDelta() {
 // TODO: Implement getTimeDelta
 return 0;
}

float GameTime::getAnimSpeedFix() {
 // TODO: Implement getAnimSpeedFix
 return 0;
}

void GameTime::setMultiplier(float _Multiplier) {
 // TODO: Implement setMultiplier
}

float GameTime::getServerMultiplier() {
 // TODO: Implement getServerMultiplier
 return 0;
}

float GameTime::getUnmoddedMultiplier() {
 // TODO: Implement getUnmoddedMultiplier
 return 0;
}

float GameTime::getInvMultiplier() {
 // TODO: Implement getInvMultiplier
 return 0;
}

float GameTime::getTrueMultiplier() {
 // TODO: Implement getTrueMultiplier
 return 0;
}

void GameTime::save() {
 // TODO: Implement save
}

void GameTime::save(DataOutputStream output) {
 // TODO: Implement save
}

void GameTime::save(ByteBuffer output) {
 // TODO: Implement save
}

void GameTime::load(DataInputStream input) {
 // TODO: Implement load
}

void GameTime::load(ByteBuffer input) {
 // TODO: Implement load
}

void GameTime::load() {
 // TODO: Implement load
}

int GameTime::getDawn() {
 // TODO: Implement getDawn
 return 0;
}

void GameTime::setDawn(int _dawn) {
 // TODO: Implement setDawn
}

int GameTime::getDusk() {
 // TODO: Implement getDusk
 return 0;
}

void GameTime::setDusk(int _dusk) {
 // TODO: Implement setDusk
}

KahluaTable GameTime::getModData() {
 // TODO: Implement getModData
 return nullptr;
}

bool GameTime::isThunderDay() {
 // TODO: Implement isThunderDay
 return false;
}

void GameTime::setThunderDay(bool _thunderDay) {
 // TODO: Implement setThunderDay
}

void GameTime::saveToPacket(ByteBuffer bb) {
 // TODO: Implement saveToPacket
}

int GameTime::getHelicopterDay1() {
 // TODO: Implement getHelicopterDay1
 return 0;
}

int GameTime::getHelicopterDay() {
 // TODO: Implement getHelicopterDay
 return 0;
}

void GameTime::setHelicopterDay(int day) {
 // TODO: Implement setHelicopterDay
}

int GameTime::getHelicopterStartHour() {
 // TODO: Implement getHelicopterStartHour
 return 0;
}

void GameTime::setHelicopterStartHour(int hour) {
 // TODO: Implement setHelicopterStartHour
}

int GameTime::getHelicopterEndHour() {
 // TODO: Implement getHelicopterEndHour
 return 0;
}

void GameTime::setHelicopterEndHour(int hour) {
 // TODO: Implement setHelicopterEndHour
}

bool GameTime::isGamePaused() {
 // TODO: Implement isGamePaused
 return false;
}

void GameTime::init(int ticks) {
 // TODO: Implement init
}

void GameTime::update() {
 // TODO: Implement update
}

float GameTime::ratio() {
 // TODO: Implement ratio
 return 0;
}

bool GameTime::finished() {
 // TODO: Implement finished
 return false;
}

} // namespace zombie
