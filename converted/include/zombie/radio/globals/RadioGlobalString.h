#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace radio {
namespace globals {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class RadioGlobalString : public RadioGlobal {
public:
public
  RadioGlobalString(const std::string &string) {
    super(string, RadioGlobalType.String);
  }

public
  RadioGlobalString(const std::string &string0, const std::string &string1) {
    super(string0, string1, RadioGlobalType.String);
  }

  std::string getValue() { return this.value; }

  void setValue(const std::string &string) { this.value = string; }

  std::string getString() { return this.value; }

  CompareResult compare(RadioGlobal radioGlobal, CompareMethod compareMethod) {
    if (radioGlobal instanceof RadioGlobalString radioGlobalString0) {
      switch (compareMethod) {
      case equals:
                    return this.value == radioGlobalString0.getValue()) ? CompareResult.True : CompareResult.False;
      case notequals:
                    return !this.value == radioGlobalString0.getValue()) ? CompareResult.True : CompareResult.False;
      default:
        return CompareResult.Invalid;
      }
    } else {
      return CompareResult.Invalid;
    }
  }

  bool setValue(RadioGlobal radioGlobal, EditGlobalOps editGlobalOps) {
    if (editGlobalOps == EditGlobalOps.set) && radioGlobal instanceof RadioGlobalString) {
        this.value = ((RadioGlobalString)radioGlobal).getValue();
        return true;
      }
    else {
      return false;
    }
  }
}
} // namespace globals
} // namespace radio
} // namespace zombie
