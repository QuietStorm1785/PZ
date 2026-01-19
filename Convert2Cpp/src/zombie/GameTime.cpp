#include "zombie/GameTime.h"

namespace zombie {

public GameTime::GameTime() {
    // TODO: Implement GameTime
    return nullptr;
}

GameTime GameTime::getInstance() {
    // TODO: Implement getInstance
    return nullptr;
}

void GameTime::setInstance(GameTime var0) {
    // TODO: Implement setInstance
}

void GameTime::syncServerTime(long var0, long var2, long var4) {
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

void GameTime::setServerTimeShift(long var0) {
    // TODO: Implement setServerTimeShift
}

void GameTime::sendTimeSync() {
    // TODO: Implement sendTimeSync
}

void GameTime::receiveTimeSync(ByteBuffer var0, UdpConnection var1) {
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

int GameTime::daysInMonth(int var1, int var2) {
    // TODO: Implement daysInMonth
    return 0;
}

std::string GameTime::getDeathString(IsoPlayer var1) {
    // TODO: Implement getDeathString
    return "";
}

int GameTime::getDaysSurvived() {
    // TODO: Implement getDaysSurvived
    return 0;
}

std::string GameTime::getTimeSurvived(IsoPlayer var1) {
    // TODO: Implement getTimeSurvived
    return "";
}

std::string GameTime::getZombieKilledText(IsoPlayer var1) {
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

float GameTime::Lerp(float var1, float var2, float var3) {
    // TODO: Implement Lerp
    return 0;
}

void GameTime::RemoveZombiesIndiscriminate(int var1) {
    // TODO: Implement RemoveZombiesIndiscriminate
}

float GameTime::TimeLerp(float var1, float var2, float var3, float var4) {
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

void GameTime::setNightMin(float var1) {
    // TODO: Implement setNightMin
}

float GameTime::getNightMax() {
    // TODO: Implement getNightMax
    return 0;
}

void GameTime::setNightMax(float var1) {
    // TODO: Implement setNightMax
}

int GameTime::getMinutes() {
    // TODO: Implement getMinutes
    return 0;
}

void GameTime::setMoon(float var1) {
    // TODO: Implement setMoon
}

void GameTime::update(bool var1) {
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

void GameTime::setAmbient(float var1) {
    // TODO: Implement setAmbient
}

float GameTime::getAmbientMax() {
    // TODO: Implement getAmbientMax
    return 0;
}

void GameTime::setAmbientMax(float var1) {
    // TODO: Implement setAmbientMax
}

float GameTime::getAmbientMin() {
    // TODO: Implement getAmbientMin
    return 0;
}

void GameTime::setAmbientMin(float var1) {
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

void GameTime::setDay(int var1) {
    // TODO: Implement setDay
}

int GameTime::getStartDay() {
    // TODO: Implement getStartDay
    return 0;
}

void GameTime::setStartDay(int var1) {
    // TODO: Implement setStartDay
}

float GameTime::getMaxZombieCountStart() {
    // TODO: Implement getMaxZombieCountStart
    return 0;
}

void GameTime::setMaxZombieCountStart(float var1) {
    // TODO: Implement setMaxZombieCountStart
}

float GameTime::getMinZombieCountStart() {
    // TODO: Implement getMinZombieCountStart
    return 0;
}

void GameTime::setMinZombieCountStart(float var1) {
    // TODO: Implement setMinZombieCountStart
}

float GameTime::getMaxZombieCount() {
    // TODO: Implement getMaxZombieCount
    return 0;
}

void GameTime::setMaxZombieCount(float var1) {
    // TODO: Implement setMaxZombieCount
}

float GameTime::getMinZombieCount() {
    // TODO: Implement getMinZombieCount
    return 0;
}

void GameTime::setMinZombieCount(float var1) {
    // TODO: Implement setMinZombieCount
}

int GameTime::getMonth() {
    // TODO: Implement getMonth
    return 0;
}

void GameTime::setMonth(int var1) {
    // TODO: Implement setMonth
}

int GameTime::getStartMonth() {
    // TODO: Implement getStartMonth
    return 0;
}

void GameTime::setStartMonth(int var1) {
    // TODO: Implement setStartMonth
}

float GameTime::getNightTint() {
    // TODO: Implement getNightTint
    return 0;
}

void GameTime::setNightTint(float var1) {
    // TODO: Implement setNightTint
}

float GameTime::getNight() {
    // TODO: Implement getNight
    return 0;
}

void GameTime::setNight(float var1) {
    // TODO: Implement setNight
}

float GameTime::getTimeOfDay() {
    // TODO: Implement getTimeOfDay
    return 0;
}

void GameTime::setTimeOfDay(float var1) {
    // TODO: Implement setTimeOfDay
}

float GameTime::getStartTimeOfDay() {
    // TODO: Implement getStartTimeOfDay
    return 0;
}

void GameTime::setStartTimeOfDay(float var1) {
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

void GameTime::setViewDistMax(float var1) {
    // TODO: Implement setViewDistMax
}

float GameTime::getViewDistMin() {
    // TODO: Implement getViewDistMin
    return 0;
}

void GameTime::setViewDistMin(float var1) {
    // TODO: Implement setViewDistMin
}

int GameTime::getYear() {
    // TODO: Implement getYear
    return 0;
}

void GameTime::setYear(int var1) {
    // TODO: Implement setYear
}

int GameTime::getStartYear() {
    // TODO: Implement getStartYear
    return 0;
}

void GameTime::setStartYear(int var1) {
    // TODO: Implement setStartYear
}

int GameTime::getNightsSurvived() {
    // TODO: Implement getNightsSurvived
    return 0;
}

void GameTime::setNightsSurvived(int var1) {
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

void GameTime::setHoursSurvived(double var1) {
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

void GameTime::setCalender(PZCalendar var1) {
    // TODO: Implement setCalender
}

void GameTime::updateCalendar(int var1, int var2, int var3, int var4, int var5) {
    // TODO: Implement updateCalendar
}

float GameTime::getMinutesPerDay() {
    // TODO: Implement getMinutesPerDay
    return 0;
}

void GameTime::setMinutesPerDay(float var1) {
    // TODO: Implement setMinutesPerDay
}

float GameTime::getLastTimeOfDay() {
    // TODO: Implement getLastTimeOfDay
    return 0;
}

void GameTime::setLastTimeOfDay(float var1) {
    // TODO: Implement setLastTimeOfDay
}

void GameTime::setTargetZombies(int var1) {
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

void GameTime::setMultiplier(float var1) {
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

void GameTime::save(DataOutputStream var1) {
    // TODO: Implement save
}

void GameTime::save(ByteBuffer var1) {
    // TODO: Implement save
}

void GameTime::load(DataInputStream var1) {
    // TODO: Implement load
}

void GameTime::load(ByteBuffer var1) {
    // TODO: Implement load
}

void GameTime::load() {
    // TODO: Implement load
}

int GameTime::getDawn() {
    // TODO: Implement getDawn
    return 0;
}

void GameTime::setDawn(int var1) {
    // TODO: Implement setDawn
}

int GameTime::getDusk() {
    // TODO: Implement getDusk
    return 0;
}

void GameTime::setDusk(int var1) {
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

void GameTime::setThunderDay(bool var1) {
    // TODO: Implement setThunderDay
}

void GameTime::saveToPacket(ByteBuffer var1) {
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

void GameTime::setHelicopterDay(int var1) {
    // TODO: Implement setHelicopterDay
}

int GameTime::getHelicopterStartHour() {
    // TODO: Implement getHelicopterStartHour
    return 0;
}

void GameTime::setHelicopterStartHour(int var1) {
    // TODO: Implement setHelicopterStartHour
}

int GameTime::getHelicopterEndHour() {
    // TODO: Implement getHelicopterEndHour
    return 0;
}

void GameTime::setHelicopterEndHour(int var1) {
    // TODO: Implement setHelicopterEndHour
}

bool GameTime::isGamePaused() {
    // TODO: Implement isGamePaused
    return false;
}

} // namespace zombie
