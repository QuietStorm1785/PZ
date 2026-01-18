#include "zombie/iso/weather/WeatherPeriod.h"

namespace zombie {
namespace iso {
namespace weather {

public
WeatherPeriod::WeatherPeriod(ClimateManager climmgr, ThunderStorm ts) {
 // TODO: Implement WeatherPeriod
 return nullptr;
}

void WeatherPeriod::setDummy(bool b) {
 // TODO: Implement setDummy
}

float WeatherPeriod::getMaxTemperatureInfluence() {
 // TODO: Implement getMaxTemperatureInfluence
 return 0;
}

void WeatherPeriod::setKateBobStormProgress(float progress) {
 // TODO: Implement setKateBobStormProgress
}

void WeatherPeriod::setKateBobStormCoords(int x, int y) {
 // TODO: Implement setKateBobStormCoords
}

ClimateColorInfo WeatherPeriod::getCloudColorReddish() {
 // TODO: Implement getCloudColorReddish
 return nullptr;
}

ClimateColorInfo WeatherPeriod::getCloudColorGreenish() {
 // TODO: Implement getCloudColorGreenish
 return nullptr;
}

ClimateColorInfo WeatherPeriod::getCloudColorBlueish() {
 // TODO: Implement getCloudColorBlueish
 return nullptr;
}

ClimateColorInfo WeatherPeriod::getCloudColorPurplish() {
 // TODO: Implement getCloudColorPurplish
 return nullptr;
}

ClimateColorInfo WeatherPeriod::getCloudColorTropical() {
 // TODO: Implement getCloudColorTropical
 return nullptr;
}

ClimateColorInfo WeatherPeriod::getCloudColorBlizzard() {
 // TODO: Implement getCloudColorBlizzard
 return nullptr;
}

bool WeatherPeriod::isRunning() {
 // TODO: Implement isRunning
 return false;
}

double WeatherPeriod::getDuration() {
 // TODO: Implement getDuration
 return 0;
}

int WeatherPeriod::getCurrentStageID() {
 // TODO: Implement getCurrentStageID
 return 0;
}

double WeatherPeriod::getWeatherNoise() {
 // TODO: Implement getWeatherNoise
 return 0;
}

float WeatherPeriod::getCurrentStrength() {
 // TODO: Implement getCurrentStrength
 return 0;
}

float WeatherPeriod::getRainThreshold() {
 // TODO: Implement getRainThreshold
 return 0;
}

bool WeatherPeriod::isThunderStorm() {
 // TODO: Implement isThunderStorm
 return false;
}

bool WeatherPeriod::isTropicalStorm() {
 // TODO: Implement isTropicalStorm
 return false;
}

bool WeatherPeriod::isBlizzard() {
 // TODO: Implement isBlizzard
 return false;
}

float WeatherPeriod::getPrecipitationFinal() {
 // TODO: Implement getPrecipitationFinal
 return 0;
}

ClimateColorInfo WeatherPeriod::getCloudColor() {
 // TODO: Implement getCloudColor
 return nullptr;
}

void WeatherPeriod::setCloudColor(ClimateColorInfo cloudcol) {
 // TODO: Implement setCloudColor
}

float WeatherPeriod::getTotalProgress() {
 // TODO: Implement getTotalProgress
 return 0;
}

float WeatherPeriod::getStageProgress() {
 // TODO: Implement getStageProgress
 return 0;
}

bool WeatherPeriod::hasTropical() {
 // TODO: Implement hasTropical
 return false;
}

bool WeatherPeriod::hasStorm() {
 // TODO: Implement hasStorm
 return false;
}

bool WeatherPeriod::hasBlizzard() {
 // TODO: Implement hasBlizzard
 return false;
}

bool WeatherPeriod::hasHeavyRain() {
 // TODO: Implement hasHeavyRain
 return false;
}

float WeatherPeriod::getTotalStrength() {
 // TODO: Implement getTotalStrength
 return 0;
}

float WeatherPeriod::getWindAngleDegrees() {
 // TODO: Implement getWindAngleDegrees
 return 0;
}

int WeatherPeriod::getFrontType() {
 // TODO: Implement getFrontType
 return 0;
}

void WeatherPeriod::print(const std::string &string) {
 // TODO: Implement print
}

void WeatherPeriod::setPrintStuff(bool b) {
 // TODO: Implement setPrintStuff
}

bool WeatherPeriod::getPrintStuff() {
 // TODO: Implement getPrintStuff
 return false;
}

void WeatherPeriod::initSimulationDebug(ClimateManager.AirFront front,
 double hoursSinceStart) {
 // TODO: Implement initSimulationDebug
}

void WeatherPeriod::initSimulationDebug(ClimateManager.AirFront front,
 double hoursSinceStart,
 int doThisStageOnly,
 float singleStageDuration) {
 // TODO: Implement initSimulationDebug
}

void WeatherPeriod::init(ClimateManager.AirFront airFront, double double0,
 int int0, int int1, int int2) {
 // TODO: Implement init
}

void WeatherPeriod::init(ClimateManager.AirFront airFront, double double0,
 int int0, int int1, int int2, int int3, float float0) {
 // TODO: Implement init
}

void WeatherPeriod::reseed(int int2, int int3, int int4) {
 // TODO: Implement reseed
}

float WeatherPeriod::RandNext(float float0, float float1) {
 // TODO: Implement RandNext
 return 0;
}

float WeatherPeriod::RandNext(float float0) {
 // TODO: Implement RandNext
 return 0;
}

int WeatherPeriod::RandNext(int int0, int int1) {
 // TODO: Implement RandNext
 return 0;
}

int WeatherPeriod::RandNext(int int0) {
 // TODO: Implement RandNext
 return 0;
}

bool WeatherPeriod::startCreateModdedPeriod(bool warmFront, float strength,
 float angle) {
 // TODO: Implement startCreateModdedPeriod
 return false;
}

bool WeatherPeriod::endCreateModdedPeriod() {
 // TODO: Implement endCreateModdedPeriod
 return false;
}

bool WeatherPeriod::startInit(ClimateManager.AirFront airFront,
 double double0) {
 // TODO: Implement startInit
 return false;
}

bool WeatherPeriod::endInit() {
 // TODO: Implement endInit
 return false;
}

void WeatherPeriod::stopWeatherPeriod() {
 // TODO: Implement stopWeatherPeriod
}

void WeatherPeriod::writeNetWeatherData(ByteBuffer output) {
 // TODO: Implement writeNetWeatherData
}

void WeatherPeriod::readNetWeatherData(ByteBuffer input) {
 // TODO: Implement readNetWeatherData
}

void WeatherPeriod::linkWeatherStages() {
 // TODO: Implement linkWeatherStages
}

void WeatherPeriod::clearCurrentWeatherStages() {
 // TODO: Implement clearCurrentWeatherStages
}

void WeatherPeriod::createSingleStage(int int0, float float0) {
 // TODO: Implement createSingleStage
}

void WeatherPeriod::createWeatherPattern() {
 // TODO: Implement createWeatherPattern
}

void WeatherPeriod::updateCurrentStage() {
 // TODO: Implement updateCurrentStage
}

void WeatherPeriod::update(double hoursSinceStart) {
 // TODO: Implement update
}

void WeatherPeriod::resetClimateManagerOverrides() {
 // TODO: Implement resetClimateManagerOverrides
}

void WeatherPeriod::save(DataOutputStream output) {
 // TODO: Implement save
}

void WeatherPeriod::load(DataInputStream input, int worldVersion) {
 // TODO: Implement load
}

private
WeatherPeriod::StrLerpVal(int int1) {
 // TODO: Implement StrLerpVal
 return nullptr;
}

int WeatherPeriod::getValue() {
 // TODO: Implement getValue
 return 0;
}

public
WeatherPeriod::WeatherStage() {
 // TODO: Implement WeatherStage
 return nullptr;
}

public
WeatherPeriod::WeatherStage(int id) {
 // TODO: Implement WeatherStage
 return nullptr;
}

void WeatherPeriod::setStageID(int id) {
 // TODO: Implement setStageID
}

double WeatherPeriod::getStageStart() {
 // TODO: Implement getStageStart
 return 0;
}

double WeatherPeriod::getStageEnd() {
 // TODO: Implement getStageEnd
 return 0;
}

double WeatherPeriod::getStageDuration() {
 // TODO: Implement getStageDuration
 return 0;
}

int WeatherPeriod::getStageID() {
 // TODO: Implement getStageID
 return 0;
}

std::string WeatherPeriod::getModID() {
 // TODO: Implement getModID
 return "";
}

float WeatherPeriod::getLinearT() {
 // TODO: Implement getLinearT
 return 0;
}

float WeatherPeriod::getParabolicT() {
 // TODO: Implement getParabolicT
 return 0;
}

void WeatherPeriod::setTargetStrength(float t) {
 // TODO: Implement setTargetStrength
}

bool WeatherPeriod::getHasStartedCloud() {
 // TODO: Implement getHasStartedCloud
 return false;
}

void WeatherPeriod::setHasStartedCloud(bool b) {
 // TODO: Implement setHasStartedCloud
}

void WeatherPeriod::save(DataOutputStream output) {
 // TODO: Implement save
}

void WeatherPeriod::load(DataInputStream input, int worldVersion) {
 // TODO: Implement load
}

void WeatherPeriod::reset() {
 // TODO: Implement reset
}

double WeatherPeriod::setStageStart(double double0) {
 // TODO: Implement setStageStart
 return 0;
}

void WeatherPeriod::lerpEntryTo(int mid, int __end__) {
 // TODO: Implement lerpEntryTo
}

void WeatherPeriod::lerpEntryTo(WeatherPeriod.StrLerpVal strLerpVal) {
 // TODO: Implement lerpEntryTo
}

void WeatherPeriod::lerpEntryTo(WeatherPeriod.StrLerpVal strLerpVal0,
 WeatherPeriod.StrLerpVal strLerpVal1) {
 // TODO: Implement lerpEntryTo
}

float WeatherPeriod::getStageCurrentStrength() {
 // TODO: Implement getStageCurrentStrength
 return 0;
}

float WeatherPeriod::getLerpValue(WeatherPeriod.StrLerpVal strLerpVal) {
 // TODO: Implement getLerpValue
 return 0;
}

float WeatherPeriod::getPeriodLerpT(double double0) {
 // TODO: Implement getPeriodLerpT
 return 0;
}

} // namespace weather
} // namespace iso
} // namespace zombie
