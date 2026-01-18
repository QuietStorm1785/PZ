#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugType.h"

namespace zombie {
namespace radio {
namespace globals {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class RadioGlobalsManager {
public:
 private Map<String, RadioGlobal> globals = std::make_unique<HashMap<>>();
 const RadioGlobalInt bufferInt = new RadioGlobalInt("bufferInt", 0);
 const RadioGlobalString bufferString = new RadioGlobalString("bufferString", "");
 const RadioGlobalBool bufferBoolean = new RadioGlobalBool("bufferBoolean", false);
 const RadioGlobalFloat bufferFloat = new RadioGlobalFloat("bufferFloat", 0.0F);
 static RadioGlobalsManager instance;

 static RadioGlobalsManager getInstance() {
 if (instance.empty()) {
 instance = std::make_unique<RadioGlobalsManager>();
 }

 return instance;
 }

 private RadioGlobalsManager() {
 }

 void reset() {
 instance = nullptr;
 }

 bool exists(const std::string& string) {
 return this->globals.containsKey(string);
 }

 RadioGlobalType getType(const std::string& string) {
 return this->globals.containsKey(string) ? this->globals.get(string).getType() : RadioGlobalType.Invalid;
 }

 std::string getString(const std::string& string) {
 RadioGlobal radioGlobal = this->getGlobal(string);
 return radioGlobal != nullptr ? radioGlobal.getString() : nullptr;
 }

 bool addGlobal(const std::string& string, RadioGlobal radioGlobal) {
 if (!this->exists(string) && radioGlobal != nullptr) {
 this->globals.put(string, radioGlobal);
 return true;
 } else {
 DebugLog.log(DebugType.Radio, "Error adding global: " + string + " to globals (already exists or global.empty())");
 return false;
 }
 }

 bool addGlobalString(const std::string& string0, const std::string& string1) {
 return this->addGlobal(string0, new RadioGlobalString(string0, string1);
 }

 bool addGlobalBool(const std::string& string, bool boolean0) {
 return this->addGlobal(string, new RadioGlobalBool(string, boolean0);
 }

 bool addGlobalInt(const std::string& string, int int0) {
 return this->addGlobal(string, new RadioGlobalInt(string, int0);
 }

 bool addGlobalFloat(const std::string& string, float float0) {
 return this->addGlobal(string, new RadioGlobalFloat(string, float0);
 }

 RadioGlobal getGlobal(const std::string& string) {
 return this->exists(string) ? this->globals.get(string) : nullptr;
 }

 RadioGlobalString getGlobalString(const std::string& string) {
 RadioGlobal radioGlobal = this->getGlobal(string);
 return radioGlobal != nullptr && radioGlobal instanceof RadioGlobalString ? (RadioGlobalString)radioGlobal : nullptr;
 }

 RadioGlobalInt getGlobalInt(const std::string& string) {
 RadioGlobal radioGlobal = this->getGlobal(string);
 return radioGlobal != nullptr && radioGlobal instanceof RadioGlobalInt ? (RadioGlobalInt)radioGlobal : nullptr;
 }

 RadioGlobalFloat getGlobalFloat(const std::string& string) {
 RadioGlobal radioGlobal = this->getGlobal(string);
 return radioGlobal != nullptr && radioGlobal instanceof RadioGlobalFloat ? (RadioGlobalFloat)radioGlobal : nullptr;
 }

 RadioGlobalBool getGlobalBool(const std::string& string) {
 RadioGlobal radioGlobal = this->getGlobal(string);
 return radioGlobal != nullptr && radioGlobal instanceof RadioGlobalBool ? (RadioGlobalBool)radioGlobal : nullptr;
 }

 bool setGlobal(const std::string& string, RadioGlobal radioGlobal1, EditGlobalOps editGlobalOps) {
 RadioGlobal radioGlobal0 = this->getGlobal(string);
 return radioGlobal0 != nullptr && radioGlobal1 != nullptr ? radioGlobal0.setValue(radioGlobal1, editGlobalOps) : false;
 }

 bool setGlobal(const std::string& string1, const std::string& string0) {
 this->bufferString.setValue(string0);
 return this->setGlobal(string1, this->bufferString, EditGlobalOps.set);
 }

 bool setGlobal(const std::string& string, int int0) {
 this->bufferInt.setValue(int0);
 return this->setGlobal(string, this->bufferInt, EditGlobalOps.set);
 }

 bool setGlobal(const std::string& string, float float0) {
 this->bufferFloat.setValue(float0);
 return this->setGlobal(string, this->bufferFloat, EditGlobalOps.set);
 }

 bool setGlobal(const std::string& string, bool boolean0) {
 this->bufferBoolean.setValue(boolean0);
 return this->setGlobal(string, this->bufferBoolean, EditGlobalOps.set);
 }

 CompareResult compare(RadioGlobal radioGlobal0, RadioGlobal radioGlobal1, CompareMethod compareMethod) {
 return radioGlobal0 != nullptr && radioGlobal1 != nullptr && radioGlobal0.getType() == radioGlobal1.getType())
 ? radioGlobal0.compare(radioGlobal1, compareMethod)
 : CompareResult.Invalid;
 }

 CompareResult compare(const std::string& string1, const std::string& string0, CompareMethod compareMethod) {
 return this->compare(this->getGlobal(string1), this->getGlobal(string0), compareMethod);
 }
}
} // namespace globals
} // namespace radio
} // namespace zombie
