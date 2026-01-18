#pragma once
#include "zombie/radio/globals/CompareMethod.h"
#include "zombie/radio/globals/CompareResult.h"
#include "zombie/radio/globals/RadioGlobal.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace radio {
namespace script {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class ConditionContainer {
public:
private
 List<ConditionIter> conditions = std::make_unique<ArrayList<>>();
 OperatorType operatorType = OperatorType.NONE;

public
 ConditionContainer() { this(OperatorType.NONE); }

public
 ConditionContainer(OperatorType operatorTypex) {
 this->operatorType = operatorTypex;
 }

 CompareResult Evaluate() {
 bool boolean0 = false;

 for (int int0 = 0; int0 < this->conditions.size(); int0++) {
 ConditionIter conditionIter = this->conditions.get(int0);
 CompareResult compareResult = conditionIter != nullptr
 ? conditionIter.Evaluate()
 : CompareResult.Invalid;
 if (compareResult == CompareResult.Invalid) {
 return compareResult;
 }

 OperatorType operatorTypex = conditionIter.getNextOperator();
 if (int0 == this->conditions.size() - 1) {
 return !operatorTypex == OperatorType.NONE) ? CompareResult.Invalid : (!boolean0 ? compareResult : CompareResult.False);
 }

 if (operatorTypex == OperatorType.OR) {
 if (!boolean0 && compareResult == CompareResult.True) {
 return compareResult;
 }

 boolean0 = false;
 }
 else if (operatorTypex == OperatorType.AND) {
 boolean0 = boolean0 || compareResult == CompareResult.False);
 }
 else if (operatorTypex == OperatorType.NONE) {
 return CompareResult.Invalid;
 }
 }

 return CompareResult.Invalid;
 }

 OperatorType getNextOperator() { return this->operatorType; }

 void setNextOperator(OperatorType operatorTypex) {
 this->operatorType = operatorTypex;
 }

 void Add(ConditionContainer conditionContainer0) {
 this->conditions.add(conditionContainer0);
 }

 void Add(RadioGlobal radioGlobal0, RadioGlobal radioGlobal1,
 CompareMethod compareMethod, OperatorType operatorTypex) {
 ConditionContainer.Condition condition = new ConditionContainer.Condition(
 radioGlobal0, radioGlobal1, compareMethod, operatorTypex);
 this->conditions.add(condition);
 }

private
 static class Condition implements ConditionIter {
 OperatorType operatorType = OperatorType.NONE;
 CompareMethod compareMethod;
 RadioGlobal valueA;
 RadioGlobal valueB;

 public
 Condition(RadioGlobal radioGlobal0, RadioGlobal radioGlobal1,
 CompareMethod compareMethodx) {
 this(radioGlobal0, radioGlobal1, compareMethodx, OperatorType.NONE);
 }

 public
 Condition(RadioGlobal radioGlobal0, RadioGlobal radioGlobal1,
 CompareMethod compareMethodx, OperatorType operatorTypex) {
 this->valueA = radioGlobal0;
 this->valueB = radioGlobal1;
 this->operatorType = operatorTypex;
 this->compareMethod = compareMethodx;
 }

 CompareResult Evaluate() {
 return this->valueA != nullptr && this->valueB != nullptr
 ? this->valueA.compare(this->valueB, this->compareMethod)
 : CompareResult.Invalid;
 }

 OperatorType getNextOperator() { return this->operatorType; }

 void setNextOperator(OperatorType operatorTypex) {
 this->operatorType = operatorTypex;
 }
 }
}
} // namespace script
} // namespace radio
} // namespace zombie
