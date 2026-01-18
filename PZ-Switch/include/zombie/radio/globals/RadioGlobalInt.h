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

class RadioGlobalInt : public RadioGlobal {
public:
public
 RadioGlobalInt(int int0) { super(int0, RadioGlobalType.Integer); }

public
 RadioGlobalInt(const std::string &string, int int0) {
 super(string, int0, RadioGlobalType.Integer);
 }

 int getValue() { return this->value; }

 void setValue(int int0) { this->value = int0; }

 std::string getString() { return this->value.toString(); }

 CompareResult compare(RadioGlobal radioGlobal, CompareMethod compareMethod) {
 if (radioGlobal instanceof RadioGlobalInt radioGlobalInt0) {
 switch (compareMethod) {
 case equals:
 return this->value == radioGlobalInt0.getValue() ? CompareResult.True
 : CompareResult.False;
 case notequals:
 return this->value != radioGlobalInt0.getValue() ? CompareResult.True
 : CompareResult.False;
 case lessthan:
 return this->value < radioGlobalInt0.getValue() ? CompareResult.True
 : CompareResult.False;
 case morethan:
 return this->value > radioGlobalInt0.getValue() ? CompareResult.True
 : CompareResult.False;
 case lessthanorequals:
 return this->value <= radioGlobalInt0.getValue() ? CompareResult.True
 : CompareResult.False;
 case morethanorequals:
 return this->value >= radioGlobalInt0.getValue() ? CompareResult.True
 : CompareResult.False;
 default:
 return CompareResult.Invalid;
 }
 } else {
 return CompareResult.Invalid;
 }
 }

 bool setValue(RadioGlobal radioGlobal, EditGlobalOps editGlobalOps) {
 if (radioGlobal instanceof RadioGlobalInt radioGlobalInt0) {
 switch (editGlobalOps) {
 case set:
 this->value = radioGlobalInt0.getValue();
 return true;
 case add:
 this->value = this->value + radioGlobalInt0.getValue();
 return true;
 case sub:
 this->value = this->value - radioGlobalInt0.getValue();
 return true;
 }
 }

 return false;
 }
}
} // namespace globals
} // namespace radio
} // namespace zombie
