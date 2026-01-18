#include "zombie/radio/scripting/RadioChannel.h"

namespace zombie {
namespace radio {
namespace scripting {

public
RadioChannel::RadioChannel(const std::string &n, int freq, ChannelCategory c) {
  // TODO: Implement RadioChannel
  return nullptr;
}

public
RadioChannel::RadioChannel(const std::string &n, int freq, ChannelCategory c,
                           const std::string &guid) {
  // TODO: Implement RadioChannel
  return nullptr;
}

std::string RadioChannel::getGUID() {
  // TODO: Implement getGUID
  return "";
}

int RadioChannel::GetFrequency() {
  // TODO: Implement GetFrequency
  return 0;
}

std::string RadioChannel::GetName() {
  // TODO: Implement GetName
  return "";
}

bool RadioChannel::IsTv() {
  // TODO: Implement IsTv
  return false;
}

ChannelCategory RadioChannel::GetCategory() {
  // TODO: Implement GetCategory
  return nullptr;
}

RadioScript RadioChannel::getCurrentScript() {
  // TODO: Implement getCurrentScript
  return nullptr;
}

RadioBroadCast RadioChannel::getAiringBroadcast() {
  // TODO: Implement getAiringBroadcast
  return nullptr;
}

std::string RadioChannel::getLastAiredLine() {
  // TODO: Implement getLastAiredLine
  return "";
}

int RadioChannel::getCurrentScriptLoop() {
  // TODO: Implement getCurrentScriptLoop
  return 0;
}

int RadioChannel::getCurrentScriptMaxLoops() {
  // TODO: Implement getCurrentScriptMaxLoops
  return 0;
}

std::string RadioChannel::getLastBroadcastID() {
  // TODO: Implement getLastBroadcastID
  return "";
}

RadioData RadioChannel::getRadioData() {
  // TODO: Implement getRadioData
  return nullptr;
}

void RadioChannel::setRadioData(RadioData _radioData) {
  // TODO: Implement setRadioData
}

bool RadioChannel::isTimeSynced() {
  // TODO: Implement isTimeSynced
  return false;
}

void RadioChannel::setTimeSynced(bool _isTimeSynced) {
  // TODO: Implement setTimeSynced
}

bool RadioChannel::isVanilla() {
  // TODO: Implement isVanilla
  return false;
}

void RadioChannel::setLouisvilleObfuscate(bool b) {
  // TODO: Implement setLouisvilleObfuscate
}

void RadioChannel::LoadAiringBroadcast(const std::string &guid, int line) {
  // TODO: Implement LoadAiringBroadcast
}

void RadioChannel::SetPlayerIsListening(bool isListening) {
  // TODO: Implement SetPlayerIsListening
}

bool RadioChannel::GetPlayerIsListening() {
  // TODO: Implement GetPlayerIsListening
  return false;
}

void RadioChannel::setActiveScriptNull() {
  // TODO: Implement setActiveScriptNull
}

void RadioChannel::setActiveScript(const std::string &scriptName, int day) {
  // TODO: Implement setActiveScript
}

void RadioChannel::setActiveScript(const std::string &scriptName, int day,
                                   int loop, int maxloops) {
  // TODO: Implement setActiveScript
}

void RadioChannel::getNextScript(int int0) {
  // TODO: Implement getNextScript
}

void RadioChannel::UpdateScripts(int timestamp, int day) {
  // TODO: Implement UpdateScripts
}

void RadioChannel::update() {
  // TODO: Implement update
}

void RadioChannel::AddRadioScript(RadioScript script) {
  // TODO: Implement AddRadioScript
}

RadioScript RadioChannel::getRadioScript(const std::string &script) {
  // TODO: Implement getRadioScript
  return nullptr;
}

void RadioChannel::setAiringBroadcast(RadioBroadCast bc) {
  // TODO: Implement setAiringBroadcast
}

float RadioChannel::getAirCounterMultiplier() {
  // TODO: Implement getAirCounterMultiplier
  return 0;
}

void RadioChannel::setAirCounterMultiplier(float _airCounterMultiplier) {
  // TODO: Implement setAirCounterMultiplier
}

} // namespace scripting
} // namespace radio
} // namespace zombie
