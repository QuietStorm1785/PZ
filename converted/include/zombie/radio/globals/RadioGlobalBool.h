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

class RadioGlobalBool : public RadioGlobal {
public:
public
  RadioGlobalBool(bool boolean0) { super(boolean0, RadioGlobalType.Boolean); }

public
  RadioGlobalBool(const std::string &string, bool boolean0) {
    super(string, boolean0, RadioGlobalType.Boolean);
  }

  bool getValue() { return this.value; }

  void setValue(bool boolean0) { this.value = boolean0; }

  std::string getString() { return this.value.toString(); }

  CompareResult compare(RadioGlobal radioGlobal, CompareMethod compareMethod) {
    if (radioGlobal instanceof RadioGlobalBool radioGlobalBool0) {
      switch (compareMethod) {
      case equals:
                    return this.value == radioGlobalBool0.getValue()) ? CompareResult.True : CompareResult.False;
      case notequals:
                    return !this.value == radioGlobalBool0.getValue()) ? CompareResult.True : CompareResult.False;
      default:
        return CompareResult.Invalid;
      }
    } else {
      return CompareResult.Invalid;
    }
  }

  bool setValue(RadioGlobal radioGlobal, EditGlobalOps editGlobalOps) {
    if (editGlobalOps == EditGlobalOps.set) && radioGlobal instanceof RadioGlobalBool) {
        this.value = ((RadioGlobalBool)radioGlobal).getValue();
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
