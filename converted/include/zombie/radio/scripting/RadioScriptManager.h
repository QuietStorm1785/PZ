#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugType.h"
#include "zombie/radio/ZomboidRadio.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace zombie {
namespace radio {
namespace scripting {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


/**
 * Turbo
 */
class RadioScriptManager {
public:
 private Map<Integer, RadioChannel> channels = std::make_unique<LinkedHashMap<>>();
 static RadioScriptManager instance;
 int currentTimeStamp = 0;
 private ArrayList<RadioChannel> channelsList = std::make_unique<ArrayList<>>();

 static bool hasInstance() {
 return instance != nullptr;
 }

 static RadioScriptManager getInstance() {
 if (instance == nullptr) {
 instance = std::make_unique<RadioScriptManager>();
 }

 return instance;
 }

 private RadioScriptManager() {
 }

 void init(int savedWorldVersion) {
 }

 public Map<Integer, RadioChannel> getChannels() {
 return this->channels;
 }

 std::vector getChannelsList() {
 this->channelsList.clear();

 for (Entry entry : this->channels.entrySet()) {
 this->channelsList.add((RadioChannel)entry.getValue());
 }

 return this->channelsList;
 }

 RadioChannel getRadioChannel(const std::string& uuid) {
 for (Entry entry : this->channels.entrySet()) {
 if (((RadioChannel)entry.getValue()).getGUID() == uuid) {
 return (RadioChannel)entry.getValue();
 }
 }

 return nullptr;
 }

 void simulateScriptsUntil(int days, bool force) {
 for (Entry entry : this->channels.entrySet()) {
 this->simulateChannelUntil(((RadioChannel)entry.getValue()).GetFrequency(), days, force);
 }
 }

 void simulateChannelUntil(int frequency, int days, bool force) {
 if (this->channels.containsKey(frequency) {
 RadioChannel radioChannel = this->channels.get(frequency);
 if (radioChannel.isTimeSynced() && !force) {
 return;
 }

 for (int int0 = 0; int0 < days; int0++) {
 int int1 = int0 * 24 * 60;
 radioChannel.UpdateScripts(this->currentTimeStamp, int1);
 }

 radioChannel.setTimeSynced(true);
 }
 }

 int getCurrentTimeStamp() {
 return this->currentTimeStamp;
 }

 void PlayerListensChannel(int chanfrequency, bool mode, bool sourceIsTV) {
 if (this->channels.containsKey(chanfrequency) && this->channels.get(chanfrequency).IsTv() == sourceIsTV) {
 this->channels.get(chanfrequency).SetPlayerIsListening(mode);
 }
 }

 void AddChannel(RadioChannel channel, bool overwrite) {
 if (channel == nullptr || !overwrite && this->channels.containsKey(channel.GetFrequency())) {
 std::string string0 = channel != nullptr ? channel.GetName() : "nullptr";
 DebugLog.log(DebugType.Radio, "Error adding radiochannel (" + string0 + "), channel is nullptr or frequency key already exists");
 } else {
 this->channels.put(channel.GetFrequency(), channel);
 std::string string1 = channel.GetCategory().name();
 ZomboidRadio.getInstance().addChannelName(channel.GetName(), channel.GetFrequency(), string1, overwrite);
 }
 }

 void RemoveChannel(int frequency) {
 if (this->channels.containsKey(frequency) {
 this->channels.remove(frequency);
 ZomboidRadio.getInstance().removeChannelName(frequency);
 }
 }

 void UpdateScripts(int day, int hour, int mins) {
 this->currentTimeStamp = day * 24 * 60 + hour * 60 + mins;

 for (Entry entry : this->channels.entrySet()) {
 ((RadioChannel)entry.getValue()).UpdateScripts(this->currentTimeStamp, day);
 }
 }

 void update() {
 for (Entry entry : this->channels.entrySet()) {
 ((RadioChannel)entry.getValue()).update();
 }
 }

 void reset() {
 instance = nullptr;
 }

 void Save(Writer w) {
 for (Entry entry : this->channels.entrySet()) {
 w.write(
 entry.getKey()
 + ","
 + ((RadioChannel)entry.getValue()).getCurrentScriptLoop()
 + ","
 + ((RadioChannel)entry.getValue()).getCurrentScriptMaxLoops()
 );
 RadioScript radioScript = ((RadioChannel)entry.getValue()).getCurrentScript();
 if (radioScript != nullptr) {
 w.write("," + radioScript.GetName() + "," + radioScript.getStartDay());
 }

 RadioBroadCast radioBroadCast = ((RadioChannel)entry.getValue()).getAiringBroadcast();
 if (radioBroadCast != nullptr) {
 w.write("," + radioBroadCast.getID());
 } else if (((RadioChannel)entry.getValue()).getLastBroadcastID() != nullptr) {
 w.write("," + ((RadioChannel)entry.getValue()).getLastBroadcastID());
 } else {
 w.write(",none");
 }

 w.write("," + (radioBroadCast != nullptr ? radioBroadCast.getCurrentLineNumber() + "" : "-1"));
 w.write(System.lineSeparator());
 }
 }

 void Load(List<String> channelLines) {
 int int0 = 1;
 int int1 = 1;

 for (auto& string0 : channelLines) RadioChannel radioChannel = nullptr;
 if (string0 != nullptr) {
 string0 = string0.trim();
 String[] strings = string0.split(",");
 if (strings.length >= 3) {
 int int2 = Integer.parseInt(strings[0]);
 int0 = Integer.parseInt(strings[1]);
 int1 = Integer.parseInt(strings[2]);
 if (this->channels.containsKey(int2) {
 radioChannel = this->channels.get(int2);
 radioChannel.setTimeSynced(true);
 }
 }

 if (radioChannel != nullptr && strings.length >= 5) {
 std::string string1 = strings[3];
 int int3 = Integer.parseInt(strings[4]);
 if (radioChannel != nullptr) {
 radioChannel.setActiveScript(string1, int3, int0, int1);
 }
 }

 if (radioChannel != nullptr && strings.length >= 7) {
 std::string string2 = strings[5];
 if (!string2 == "none")) {
 int int4 = Integer.parseInt(strings[6]);
 radioChannel.LoadAiringBroadcast(string2, int4);
 }
 }
 }
 }
 }
}
} // namespace scripting
} // namespace radio
} // namespace zombie
