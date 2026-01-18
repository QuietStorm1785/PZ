#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameTime.h"
#include "zombie/core/Rand.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugType.h"
#include "zombie/radio/ChannelCategory.h"
#include "zombie/radio/RadioData.h"
#include "zombie/radio/ZomboidRadio.h"
#include <algorithm>

namespace zombie {
namespace radio {
namespace scripting {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


/**
 * Turbo
 */
class RadioChannel {
public:
 std::string GUID;
 RadioData radioData;
 bool isTimeSynced = false;
 private Map<String, RadioScript> scripts = std::make_unique<HashMap<>>();
 int frequency = -1;
 std::string name = "Unnamed channel";
 bool isTv = false;
 ChannelCategory category = ChannelCategory.Undefined;
 bool playerIsListening = false;
 RadioScript currentScript = nullptr;
 int currentScriptLoop = 1;
 int currentScriptMaxLoops = 1;
 RadioBroadCast airingBroadcast = nullptr;
 float airCounter = 0.0F;
 std::string lastAiredLine = "";
 std::string lastBroadcastID = nullptr;
 float airCounterMultiplier = 1.0F;
 bool louisvilleObfuscate = false;
 float minmod = 1.5F;
 float maxmod = 5.0F;

 public RadioChannel(const std::string& n, int freq, ChannelCategory c) {
 this(n, freq, c, UUID.randomUUID().toString());
 }

 public RadioChannel(const std::string& n, int freq, ChannelCategory c, const std::string& guid) {
 this->name = n;
 this->frequency = freq;
 this->category = c;
 this->isTv = this->category == ChannelCategory.Television;
 this->GUID = guid;
 }

 std::string getGUID() {
 return this->GUID;
 }

 int GetFrequency() {
 return this->frequency;
 }

 std::string GetName() {
 return this->name;
 }

 bool IsTv() {
 return this->isTv;
 }

 ChannelCategory GetCategory() {
 return this->category;
 }

 RadioScript getCurrentScript() {
 return this->currentScript;
 }

 RadioBroadCast getAiringBroadcast() {
 return this->airingBroadcast;
 }

 std::string getLastAiredLine() {
 return this->lastAiredLine;
 }

 int getCurrentScriptLoop() {
 return this->currentScriptLoop;
 }

 int getCurrentScriptMaxLoops() {
 return this->currentScriptMaxLoops;
 }

 std::string getLastBroadcastID() {
 return this->lastBroadcastID;
 }

 RadioData getRadioData() {
 return this->radioData;
 }

 void setRadioData(RadioData _radioData) {
 this->radioData = _radioData;
 }

 bool isTimeSynced() {
 return this->isTimeSynced;
 }

 void setTimeSynced(bool _isTimeSynced) {
 this->isTimeSynced = _isTimeSynced;
 }

 bool isVanilla() {
 return this->radioData == nullptr || this->radioData.isVanilla();
 }

 void setLouisvilleObfuscate(bool b) {
 this->louisvilleObfuscate = b;
 }

 void LoadAiringBroadcast(const std::string& guid, int line) {
 if (this->currentScript != nullptr) {
 this->airingBroadcast = this->currentScript.getBroadcastWithID(guid);
 if (line < 0) {
 this->airingBroadcast = nullptr;
 }

 if (this->airingBroadcast != nullptr && line >= 0) {
 this->airingBroadcast.resetLineCounter();
 this->airingBroadcast.setCurrentLineNumber(line);
 this->airCounter = 120.0F;
 this->playerIsListening = true;
 }
 }
 }

 void SetPlayerIsListening(bool isListening) {
 this->playerIsListening = isListening;
 if (this->playerIsListening && this->airingBroadcast == nullptr && this->currentScript != nullptr) {
 this->airingBroadcast = this->currentScript.getValidAirBroadcast();
 if (this->airingBroadcast != nullptr) {
 this->airingBroadcast.resetLineCounter();
 }

 this->airCounter = 0.0F;
 }
 }

 bool GetPlayerIsListening() {
 return this->playerIsListening;
 }

 void setActiveScriptNull() {
 this->currentScript = nullptr;
 this->airingBroadcast = nullptr;
 }

 void setActiveScript(const std::string& scriptName, int day) {
 this->setActiveScript(scriptName, day, 1, -1);
 }

 void setActiveScript(const std::string& scriptName, int day, int loop, int maxloops) {
 if (scriptName != nullptr && this->scripts.containsKey(scriptName) {
 this->currentScript = this->scripts.get(scriptName);
 if (this->currentScript != nullptr) {
 this->currentScript.Reset();
 this->currentScript.setStartDayStamp(day);
 this->currentScriptLoop = loop;
 if (maxloops == -1) {
 int int0 = this->currentScript.getLoopMin();
 int int1 = this->currentScript.getLoopMax();
 if (int0 != int1 && int0 <= int1) {
 maxloops = Rand.Next(int0, int1);
 } else {
 maxloops = int0;
 }
 }

 this->currentScriptMaxLoops = maxloops;
 if (DebugLog.isEnabled(DebugType.Radio) {
 DebugLog.Radio
 .println(
 "Script: "
 + scriptName
 + ", day = "
 + day
 + ", minloops = "
 + this->currentScript.getLoopMin()
 + ", maxloops = "
 + this->currentScriptMaxLoops
 );
 }
 }
 }
 }

 void getNextScript(int int0) {
 if (this->currentScript != nullptr) {
 if (this->currentScriptLoop < this->currentScriptMaxLoops) {
 this->currentScriptLoop++;
 this->currentScript.Reset();
 this->currentScript.setStartDayStamp(int0);
 } else {
 RadioScript.ExitOption exitOption = this->currentScript.getNextScript();
 this->currentScript = nullptr;
 if (exitOption != nullptr) {
 this->setActiveScript(exitOption.getScriptname(), int0 + exitOption.getStartDelay());
 }
 }
 }
 }

 void UpdateScripts(int timestamp, int day) {
 this->playerIsListening = false;
 if (this->currentScript != nullptr && !this->currentScript.UpdateScript(timestamp) {
 this->getNextScript(day + 1);
 }
 }

 void update() {
 if (this->airingBroadcast != nullptr) {
 this->airCounter = this->airCounter - 1.25F * GameTime.getInstance().getMultiplier();
 if (this->airCounter < 0.0F) {
 RadioLine radioLine = this->airingBroadcast.getNextLine();
 if (radioLine == nullptr) {
 this->lastBroadcastID = this->airingBroadcast.getID();
 this->airingBroadcast = nullptr;
 this->playerIsListening = false;
 } else {
 this->lastAiredLine = radioLine.getText();
 if (!ZomboidRadio.DISABLE_BROADCASTING) {
 std::string string = radioLine.getText();
 if (this->louisvilleObfuscate && ZomboidRadio.LOUISVILLE_OBFUSCATION) {
 string = ZomboidRadio.getInstance().scrambleString(string, 85, true, nullptr);
 ZomboidRadio.getInstance().SendTransmission(0, 0, this->frequency, string, nullptr, "", 0.7F, 0.5F, 0.5F, -1, this->isTv);
 } else {
 ZomboidRadio.getInstance()
 .SendTransmission(
 0,
 0,
 this->frequency,
 string,
 nullptr,
 radioLine.getEffectsString(),
 radioLine.getR(),
 radioLine.getG(),
 radioLine.getB(),
 -1,
 this->isTv
 );
 }
 }

 if (radioLine.isCustomAirTime()) {
 this->airCounter = radioLine.getAirTime() * 60.0F;
 } else {
 this->airCounter = radioLine.getText().length() / 10.0F * 60.0F;
 if (this->airCounter < 60.0F * this->minmod) {
 this->airCounter = 60.0F * this->minmod;
 } else if (this->airCounter > 60.0F * this->maxmod) {
 this->airCounter = 60.0F * this->maxmod;
 }

 this->airCounter = this->airCounter * this->airCounterMultiplier;
 }
 }
 }
 }
 }

 void AddRadioScript(RadioScript script) {
 if (script != nullptr && !this->scripts.containsKey(script.GetName())) {
 this->scripts.put(script.GetName(), script);
 } else {
 std::string string = script != nullptr ? script.GetName() : "nullptr";
 DebugLog.log(DebugType.Radio, "Error while attempting to add script (" + string + "), nullptr or name already exists.");
 }
 }

 RadioScript getRadioScript(const std::string& script) {
 return script != nullptr && this->scripts.containsKey(script) ? this->scripts.get(script) : nullptr;
 }

 void setAiringBroadcast(RadioBroadCast bc) {
 this->airingBroadcast = bc;
 }

 float getAirCounterMultiplier() {
 return this->airCounterMultiplier;
 }

 void setAirCounterMultiplier(float _airCounterMultiplier) {
 this->airCounterMultiplier = PZMath.clamp(_airCounterMultiplier, 0.1F, 10.0F);
 }
}
} // namespace scripting
} // namespace radio
} // namespace zombie
