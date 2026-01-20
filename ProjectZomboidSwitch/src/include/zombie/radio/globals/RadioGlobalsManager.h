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


class RadioGlobalsManager {
public:
   private const Map<std::string, RadioGlobal> globals = std::make_unique<std::unordered_map<>>();
    const RadioGlobalInt bufferInt = std::make_shared<RadioGlobalInt>("bufferInt", 0);
    const RadioGlobalString bufferString = std::make_shared<RadioGlobalString>("bufferString", "");
    const RadioGlobalBool bufferBoolean = std::make_shared<RadioGlobalBool>("bufferBoolean", false);
    const RadioGlobalFloat bufferFloat = std::make_shared<RadioGlobalFloat>("bufferFloat", 0.0F);
    static RadioGlobalsManager instance;

    static RadioGlobalsManager getInstance() {
      if (instance == nullptr) {
         instance = std::make_unique<RadioGlobalsManager>();
      }

    return instance;
   }

    private RadioGlobalsManager() {
   }

    void reset() {
      instance = nullptr;
   }

    bool exists(const std::string& var1) {
      return this.globals.containsKey(var1);
   }

    RadioGlobalType getType(const std::string& var1) {
      return this.globals.containsKey(var1) ? this.globals.get(var1).getType() : RadioGlobalType.Invalid;
   }

    std::string getString(const std::string& var1) {
    RadioGlobal var2 = this.getGlobal(var1);
      return var2 != nullptr ? var2.getString() : nullptr;
   }

    bool addGlobal(const std::string& var1, RadioGlobal var2) {
      if (!this.exists(var1) && var2 != nullptr) {
         this.globals.put(var1, var2);
    return true;
      } else {
         DebugLog.log(DebugType.Radio, "Error adding global: " + var1 + " to globals (already exists or global==nullptr)");
    return false;
      }
   }

    bool addGlobalString(const std::string& var1, const std::string& var2) {
      return this.addGlobal(var1, std::make_shared<RadioGlobalString>(var1, var2));
   }

    bool addGlobalBool(const std::string& var1, bool var2) {
      return this.addGlobal(var1, std::make_shared<RadioGlobalBool>(var1, var2));
   }

    bool addGlobalInt(const std::string& var1, int var2) {
      return this.addGlobal(var1, std::make_shared<RadioGlobalInt>(var1, var2));
   }

    bool addGlobalFloat(const std::string& var1, float var2) {
      return this.addGlobal(var1, std::make_shared<RadioGlobalFloat>(var1, var2));
   }

    RadioGlobal getGlobal(const std::string& var1) {
      return this.exists(var1) ? this.globals.get(var1) : nullptr;
   }

    RadioGlobalString getGlobalString(const std::string& var1) {
    RadioGlobal var2 = this.getGlobal(var1);
      return var2 != nullptr && dynamic_cast<RadioGlobalString*>(var2) != nullptr ? (RadioGlobalString)var2 : nullptr;
   }

    RadioGlobalInt getGlobalInt(const std::string& var1) {
    RadioGlobal var2 = this.getGlobal(var1);
      return var2 != nullptr && dynamic_cast<RadioGlobalInt*>(var2) != nullptr ? (RadioGlobalInt)var2 : nullptr;
   }

    RadioGlobalFloat getGlobalFloat(const std::string& var1) {
    RadioGlobal var2 = this.getGlobal(var1);
      return var2 != nullptr && dynamic_cast<RadioGlobalFloat*>(var2) != nullptr ? (RadioGlobalFloat)var2 : nullptr;
   }

    RadioGlobalBool getGlobalBool(const std::string& var1) {
    RadioGlobal var2 = this.getGlobal(var1);
      return var2 != nullptr && dynamic_cast<RadioGlobalBool*>(var2) != nullptr ? (RadioGlobalBool)var2 : nullptr;
   }

    bool setGlobal(const std::string& var1, RadioGlobal var2, EditGlobalOps var3) {
    RadioGlobal var4 = this.getGlobal(var1);
      return var4 != nullptr && var2 != nullptr ? var4.setValue(var2, var3) : false;
   }

    bool setGlobal(const std::string& var1, const std::string& var2) {
      this.bufferString.setValue(var2);
      return this.setGlobal(var1, this.bufferString, EditGlobalOps.set);
   }

    bool setGlobal(const std::string& var1, int var2) {
      this.bufferInt.setValue(var2);
      return this.setGlobal(var1, this.bufferInt, EditGlobalOps.set);
   }

    bool setGlobal(const std::string& var1, float var2) {
      this.bufferFloat.setValue(var2);
      return this.setGlobal(var1, this.bufferFloat, EditGlobalOps.set);
   }

    bool setGlobal(const std::string& var1, bool var2) {
      this.bufferBoolean.setValue(var2);
      return this.setGlobal(var1, this.bufferBoolean, EditGlobalOps.set);
   }

    CompareResult compare(RadioGlobal var1, RadioGlobal var2, CompareMethod var3) {
      return var1 != nullptr && var2 != nullptr && var1.getType() == var2.getType()) ? var1.compare(var2, var3) : CompareResult.Invalid;
   }

    CompareResult compare(const std::string& var1, const std::string& var2, CompareMethod var3) {
      return this.compare(this.getGlobal(var1), this.getGlobal(var2), var3);
   }
}
} // namespace globals
} // namespace radio
} // namespace zombie
