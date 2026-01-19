#pragma once
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugType.h"
#include <cstdint>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace radio {
namespace globals {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class RadioGlobalsManager {
public:
private
 Map<String, RadioGlobal> globals = std::make_unique<HashMap<>>();
 const RadioGlobalInt bufferInt = new RadioGlobalInt("bufferInt", 0);
 const RadioGlobalString bufferString =
 new RadioGlobalString("bufferString", "");
 const RadioGlobalBool bufferBoolean =
 new RadioGlobalBool("bufferBoolean", false);
 const RadioGlobalFloat bufferFloat =
 new RadioGlobalFloat("bufferFloat", 0.0F);
 static RadioGlobalsManager instance;

 static RadioGlobalsManager getInstance() {
 if (instance.empty()) {
 instance = std::make_unique<RadioGlobalsManager>();
 }

 return instance;
 }

private
 RadioGlobalsManager() {}

 void reset() { instance = nullptr; }

 bool exists(std::string_view string) {
 return this->globals.containsKey(string);
 }

 RadioGlobalType getType(std::string_view string) {
 return this->globals.containsKey(string) ? this->globals.get(string).getType()
 : RadioGlobalType.Invalid;
 }

 std::string getString(std::string_view string) {
 RadioGlobal radioGlobal = this->getGlobal(string);
 return radioGlobal != nullptr ? radioGlobal.getString() : nullptr;
 }

 bool addGlobal(std::string_view string, RadioGlobal radioGlobal) {
 if (!this->exists(string) && radioGlobal != nullptr) {
 this->globals.put(string, radioGlobal);
 return true;
 } else {
 DebugLog.log(DebugType.Radio,
 "Error adding global: " + string +
 " to globals (already exists or global.empty())");
 return false;
 }
 }

 bool addGlobalString(std::string_view string0, std::string_view string1) {
 return this->addGlobal(string0, new RadioGlobalString(string0, string1);
 }

 bool addGlobalBool(std::string_view string, bool boolean0) {
 return this->addGlobal(string, new RadioGlobalBool(string, boolean0);
 }

 bool addGlobalInt(std::string_view string, int int0) {
 return this->addGlobal(string, new RadioGlobalInt(string, int0);
 }

 bool addGlobalFloat(std::string_view string, float float0) {
 return this->addGlobal(string, new RadioGlobalFloat(string, float0);
 }

 RadioGlobal getGlobal(std::string_view string) {
 return this->exists(string) ? this->globals.get(string) : nullptr;
 }

 RadioGlobalString getGlobalString(std::string_view string) {
 RadioGlobal radioGlobal = this->getGlobal(string);
 return radioGlobal != nullptr && radioGlobal instanceof
 RadioGlobalString ? (RadioGlobalString)radioGlobal : nullptr;
 }

 RadioGlobalInt getGlobalInt(std::string_view string) {
 RadioGlobal radioGlobal = this->getGlobal(string);
 return radioGlobal != nullptr && radioGlobal instanceof
 RadioGlobalInt ? (RadioGlobalInt)radioGlobal : nullptr;
 }

 RadioGlobalFloat getGlobalFloat(std::string_view string) {
 RadioGlobal radioGlobal = this->getGlobal(string);
 return radioGlobal != nullptr && radioGlobal instanceof
 RadioGlobalFloat ? (RadioGlobalFloat)radioGlobal : nullptr;
 }

 RadioGlobalBool getGlobalBool(std::string_view string) {
 RadioGlobal radioGlobal = this->getGlobal(string);
 return radioGlobal != nullptr && radioGlobal instanceof
 RadioGlobalBool ? (RadioGlobalBool)radioGlobal : nullptr;
 }

 bool setGlobal(std::string_view string, RadioGlobal radioGlobal1,
 EditGlobalOps editGlobalOps) {
 RadioGlobal radioGlobal0 = this->getGlobal(string);
 return radioGlobal0 != nullptr && radioGlobal1 != nullptr
 ? radioGlobal0.setValue(radioGlobal1, editGlobalOps)
 : false;
 }

 bool setGlobal(std::string_view string1, std::string_view string0) {
 this->bufferString.setValue(string0);
 return this->setGlobal(string1, this->bufferString, EditGlobalOps.set);
 }

 bool setGlobal(std::string_view string, int int0) {
 this->bufferInt.setValue(int0);
 return this->setGlobal(string, this->bufferInt, EditGlobalOps.set);
 }

 bool setGlobal(std::string_view string, float float0) {
 this->bufferFloat.setValue(float0);
 return this->setGlobal(string, this->bufferFloat, EditGlobalOps.set);
 }

 bool setGlobal(std::string_view string, bool boolean0) {
 this->bufferBoolean.setValue(boolean0);
 return this->setGlobal(string, this->bufferBoolean, EditGlobalOps.set);
 }

 CompareResult compare(RadioGlobal radioGlobal0, RadioGlobal radioGlobal1,
 CompareMethod compareMethod) {
 return radioGlobal0 != nullptr && radioGlobal1 != nullptr && radioGlobal0.getType() == radioGlobal1.getType())
 ? radioGlobal0.compare(radioGlobal1, compareMethod)
 : CompareResult.Invalid;
 }

 CompareResult compare(std::string_view string1, std::string_view string0,
 CompareMethod compareMethod) {
 return this->compare(this->getGlobal(string1), this->getGlobal(string0),
 compareMethod);
 }
}
} // namespace globals
} // namespace radio
} // namespace zombie
