#pragma once
#include "zombie/core/Rand.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugType.h"
#include <algorithm>
#include <cstdint>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace radio {
namespace scripting {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

/**
 * Turbo
 */
class RadioScript {
public:
private
 ArrayList<RadioBroadCast> broadcasts = std::make_unique<ArrayList<>>();
private
 ArrayList<RadioScript.ExitOption> exitOptions =
 std::make_unique<ArrayList<>>();
 std::string GUID;
 std::string name = "Unnamed radioscript";
 int startDay = 0;
 int startDayStamp = 0;
 int loopMin = 1;
 int loopMax = 1;
 int internalStamp = 0;
 RadioBroadCast currentBroadcast = nullptr;
 bool currentHasAired = false;

public
 RadioScript(std::string_view n, int loopmin, int loopmax) {
 this(n, loopmin, loopmax, UUID.randomUUID().toString());
 }

public
 RadioScript(std::string_view n, int loopmin, int loopmax,
 std::string_view guid) {
 this->name = n;
 this->loopMin = loopmin;
 this->loopMax = loopmax;
 this->GUID = guid;
 }

 std::string GetGUID() { return this->GUID; }

 std::string GetName() { return this->name; }

 int getStartDayStamp() { return this->startDayStamp; }

 int getStartDay() { return this->startDay; }

 int getLoopMin() { return this->loopMin; }

 int getLoopMax() { return this->loopMax; }

 RadioBroadCast getCurrentBroadcast() { return this->currentBroadcast; }

public
 ArrayList<RadioBroadCast> getBroadcastList() { return this->broadcasts; }

 void clearExitOptions() { this->exitOptions.clear(); }

 void setStartDayStamp(int day) {
 this->startDay = day;
 this->startDayStamp = day * 24 * 60;
 }

 RadioBroadCast getValidAirBroadcast() {
 if (!this->currentHasAired && this->currentBroadcast != nullptr &&
 this->internalStamp >= this->currentBroadcast.getStartStamp() &&
 this->internalStamp < this->currentBroadcast.getEndStamp()) {
 this->currentHasAired = true;
 return this->currentBroadcast;
 } else {
 return nullptr;
 }
 }

 void Reset() {
 this->currentBroadcast = nullptr;
 this->currentHasAired = false;
 }

 RadioBroadCast getNextBroadcast() {
 if (this->currentBroadcast != nullptr &&
 this->currentBroadcast.getEndStamp() > this->internalStamp) {
 return this->currentBroadcast;
 } else {
 for (int int0 = 0; int0 < this->broadcasts.size(); int0++) {
 RadioBroadCast radioBroadCast = this->broadcasts.get(int0);
 if (radioBroadCast.getEndStamp() > this->internalStamp) {
 this->currentHasAired = false;
 return radioBroadCast;
 }
 }

 return nullptr;
 }
 }

 RadioBroadCast getBroadcastWithID(std::string_view guid) {
 for (int int0 = 0; int0 < this->broadcasts.size(); int0++) {
 RadioBroadCast radioBroadCast = this->broadcasts.get(int0);
 if (radioBroadCast.getID() == guid) {
 this->currentBroadcast = radioBroadCast;
 this->currentHasAired = true;
 return radioBroadCast;
 }
 }

 return nullptr;
 }

 bool UpdateScript(int timeStamp) {
 this->internalStamp = timeStamp - this->startDayStamp;
 this->currentBroadcast = this->getNextBroadcast();
 return this->currentBroadcast != nullptr;
 }

public
 RadioScript.ExitOption getNextScript() {
 int int0 = 0;
 int int1 = Rand.Next(100);

 for (RadioScript.ExitOption exitOption : this->exitOptions) {
 if (int1 >= int0 && int1 < int0 + exitOption.getChance()) {
 return exitOption;
 }

 int0 += exitOption.getChance();
 }

 return nullptr;
 }

 void AddBroadcast(RadioBroadCast broadcast) {
 this->AddBroadcast(broadcast, false);
 }

 void AddBroadcast(RadioBroadCast broadcast, bool ignoreTimestamps) {
 bool boolean0 = false;
 if (broadcast != nullptr && broadcast.getID() != nullptr) {
 if (ignoreTimestamps) {
 this->broadcasts.add(broadcast);
 boolean0 = true;
 } else if (broadcast.getStartStamp() >= 0 &&
 broadcast.getEndStamp() > broadcast.getStartStamp()) {
 if (this->broadcasts.size() == 0 ||
 this->broadcasts.get(this->broadcasts.size() - 1).getEndStamp() <=
 broadcast.getStartStamp()) {
 this->broadcasts.add(broadcast);
 boolean0 = true;
 } else if (this->broadcasts.size() > 0) {
 DebugLog.log(DebugType.Radio,
 "startstamp = '" + broadcast.getStartStamp() +
 "', endstamp = '" + broadcast.getEndStamp() +
 "', previous endstamp = '" +
 this->broadcasts.get(this->broadcasts.size() - 1)
 .getEndStamp() +
 "'.");
 }
 } else {
 DebugLog.log(DebugType.Radio,
 "startstamp = '" + broadcast.getStartStamp() +
 "', endstamp = '" + broadcast.getEndStamp() + "'.");
 }
 }

 if (!boolean0) {
 std::string string = broadcast != nullptr ? broadcast.getID() : "nullptr";
 DebugLog.log(DebugType.Radio, "Error cannot add broadcast ID: '" +
 string + "' to script '" + this->name +
 "', nullptr or timestamp error");
 }
 }

 void AddExitOption(std::string_view scriptname, int chance,
 int startdelay) {
 int int0 = chance;

 for (RadioScript.ExitOption exitOption : this->exitOptions) {
 int0 += exitOption.getChance();
 }

 if (int0 <= 100) {
 this->exitOptions.add(
 new RadioScript.ExitOption(scriptname, chance, startdelay);
 } else {
 DebugLog.log(DebugType.Radio,
 "Error cannot add exitoption with scriptname '" +
 scriptname + "' to script '" + this->name +
 "', total chance exceeding 100");
 }
 }

 RadioBroadCast getValidAirBroadcastDebug() {
 if (this->currentBroadcast != nullptr &&
 this->currentBroadcast.getEndStamp() > this->internalStamp) {
 return this->currentBroadcast;
 } else {
 for (int int0 = 0; int0 < this->broadcasts.size(); int0++) {
 RadioBroadCast radioBroadCast = this->broadcasts.get(int0);
 if (radioBroadCast.getEndStamp() > this->internalStamp) {
 return radioBroadCast;
 }
 }

 return nullptr;
 }
 }

public
 ArrayList<RadioScript.ExitOption> getExitOptions() {
 return this->exitOptions;
 }

public
 static class ExitOption {
 std::string scriptname = "";
 int chance = 0;
 int startDelay = 0;

 public
 ExitOption(std::string_view name, int rollchance, int startdelay) {
 this->scriptname = name;
 this->chance = rollchance;
 this->startDelay = startdelay;
 }

 std::string getScriptname() { return this->scriptname; }

 int getChance() { return this->chance; }

 int getStartDelay() { return this->startDelay; }
 }
}
} // namespace scripting
} // namespace radio
} // namespace zombie
