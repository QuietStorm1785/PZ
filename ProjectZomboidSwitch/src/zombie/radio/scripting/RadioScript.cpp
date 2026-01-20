#include <string>
#include "zombie\radio\scripting/RadioScript.h"

namespace zombie {
namespace radio {
namespace scripting {

public RadioScript::RadioScript(const std::string& var1, int var2, int var3) {
    // TODO: Implement RadioScript
    return nullptr;
}

public RadioScript::RadioScript(const std::string& var1, int var2, int var3, const std::string& var4) {
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

void RadioScript::setStartDayStamp(int var1) {
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

RadioBroadCast RadioScript::getBroadcastWithID(const std::string& var1) {
    // TODO: Implement getBroadcastWithID
    return nullptr;
}

bool RadioScript::UpdateScript(int var1) {
    // TODO: Implement UpdateScript
    return false;
}

ExitOption RadioScript::getNextScript() {
    // TODO: Implement getNextScript
    return nullptr;
}

void RadioScript::AddBroadcast(RadioBroadCast var1) {
    // TODO: Implement AddBroadcast
}

void RadioScript::AddBroadcast(RadioBroadCast var1, bool var2) {
    // TODO: Implement AddBroadcast
}

void RadioScript::AddExitOption(const std::string& var1, int var2, int var3) {
    // TODO: Implement AddExitOption
}

RadioBroadCast RadioScript::getValidAirBroadcastDebug() {
    // TODO: Implement getValidAirBroadcastDebug
    return nullptr;
}

} // namespace scripting
} // namespace radio
} // namespace zombie
