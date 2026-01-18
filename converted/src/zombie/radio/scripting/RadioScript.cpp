#include "zombie/radio/scripting/RadioScript.h"

namespace zombie {
namespace radio {
namespace scripting {

public RadioScript::RadioScript(const std::string& n, int loopmin, int loopmax) {
 // TODO: Implement RadioScript
 return nullptr;
}

public RadioScript::RadioScript(const std::string& n, int loopmin, int loopmax, const std::string& guid) {
 // TODO: Implement RadioScript
 return nullptr;
}

std::string RadioScript::GetGUID() {
 // TODO: Implement GetGUID
 return "";
}

std::string RadioScript::GetName() {
 // TODO: Implement GetName
 return "";
}

int RadioScript::getStartDayStamp() {
 // TODO: Implement getStartDayStamp
 return 0;
}

int RadioScript::getStartDay() {
 // TODO: Implement getStartDay
 return 0;
}

int RadioScript::getLoopMin() {
 // TODO: Implement getLoopMin
 return 0;
}

int RadioScript::getLoopMax() {
 // TODO: Implement getLoopMax
 return 0;
}

RadioBroadCast RadioScript::getCurrentBroadcast() {
 // TODO: Implement getCurrentBroadcast
 return nullptr;
}

void RadioScript::clearExitOptions() {
 // TODO: Implement clearExitOptions
}

void RadioScript::setStartDayStamp(int day) {
 // TODO: Implement setStartDayStamp
}

RadioBroadCast RadioScript::getValidAirBroadcast() {
 // TODO: Implement getValidAirBroadcast
 return nullptr;
}

void RadioScript::Reset() {
 // TODO: Implement Reset
}

RadioBroadCast RadioScript::getNextBroadcast() {
 // TODO: Implement getNextBroadcast
 return nullptr;
}

RadioBroadCast RadioScript::getBroadcastWithID(const std::string& guid) {
 // TODO: Implement getBroadcastWithID
 return nullptr;
}

bool RadioScript::UpdateScript(int timeStamp) {
 // TODO: Implement UpdateScript
 return false;
}

void RadioScript::AddBroadcast(RadioBroadCast broadcast) {
 // TODO: Implement AddBroadcast
}

void RadioScript::AddBroadcast(RadioBroadCast broadcast, bool ignoreTimestamps) {
 // TODO: Implement AddBroadcast
}

void RadioScript::AddExitOption(const std::string& scriptname, int chance, int startdelay) {
 // TODO: Implement AddExitOption
}

RadioBroadCast RadioScript::getValidAirBroadcastDebug() {
 // TODO: Implement getValidAirBroadcastDebug
 return nullptr;
}

public RadioScript::ExitOption(const std::string& name, int rollchance, int startdelay) {
 // TODO: Implement ExitOption
 return nullptr;
}

std::string RadioScript::getScriptname() {
 // TODO: Implement getScriptname
 return "";
}

int RadioScript::getChance() {
 // TODO: Implement getChance
 return 0;
}

int RadioScript::getStartDelay() {
 // TODO: Implement getStartDelay
 return 0;
}

} // namespace scripting
} // namespace radio
} // namespace zombie
