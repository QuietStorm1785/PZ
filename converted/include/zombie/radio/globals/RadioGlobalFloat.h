#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace radio {
namespace globals {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.

class RadioGlobalFloat : public RadioGlobal {
public:
 public RadioGlobalFloat(float float0) {
 super(float0, RadioGlobalType.Float);
 }

 public RadioGlobalFloat(const std::string& string, float float0) {
 super(string, float0, RadioGlobalType.Float);
 }

 float getValue() {
 return this->value;
 }

 void setValue(float float0) {
 this->value = float0;
 }

 std::string getString() {
 return this->value.toString();
 }

 CompareResult compare(RadioGlobal radioGlobal, CompareMethod compareMethod) {
 if (radioGlobal instanceof RadioGlobalFloat radioGlobalFloat0) {
 switch (compareMethod) {
 case equals:
 return this->value == radioGlobalFloat0.getValue() ? CompareResult.True : CompareResult.False;
 case notequals:
 return this->value != radioGlobalFloat0.getValue() ? CompareResult.True : CompareResult.False;
 case lessthan:
 return this->value < radioGlobalFloat0.getValue() ? CompareResult.True : CompareResult.False;
 case morethan:
 return this->value > radioGlobalFloat0.getValue() ? CompareResult.True : CompareResult.False;
 case lessthanorequals:
 return this->value <= radioGlobalFloat0.getValue() ? CompareResult.True : CompareResult.False;
 case morethanorequals:
 return this->value >= radioGlobalFloat0.getValue() ? CompareResult.True : CompareResult.False;
 default:
 return CompareResult.Invalid;
 }
 } else {
 return CompareResult.Invalid;
 }
 }

 bool setValue(RadioGlobal radioGlobal, EditGlobalOps editGlobalOps) {
 if (radioGlobal instanceof RadioGlobalFloat radioGlobalFloat0) {
 switch (editGlobalOps) {
 case set:
 this->value = radioGlobalFloat0.getValue();
 return true;
 case add:
 this->value = this->value + radioGlobalFloat0.getValue();
 return true;
 case sub:
 this->value = this->value - radioGlobalFloat0.getValue();
 return true;
 }
 }

 return false;
 }
}
} // namespace globals
} // namespace radio
} // namespace zombie
