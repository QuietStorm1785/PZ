#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace advancedanimation {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class AnimCondition {
public:
 std::string m_Name = "";
public
 AnimCondition.Type m_Type = AnimCondition.Type.STRING;
 float m_FloatValue = 0.0F;
 bool m_BoolValue = false;
 std::string m_StringValue = "";
 AnimationVariableHandle m_variableHandle;

 std::string toString() {
 return String.format("AnimCondition{name:%s type:%s value:%s }",
 this->m_Name, this->m_Type.toString(),
 this->getValueString());
 }

 std::string getConditionString() {
 return this->m_Type == AnimCondition.Type.OR
 ? "OR"
 : String.format("( %s %s %s )", this->m_Name,
 this->m_Type.toString(), this->getValueString());
 }

 std::string getValueString() {
 switch (this->m_Type) {
 case EQU:
 case NEQ:
 case LESS:
 case GTR:
 return String.valueOf(this->m_FloatValue);
 case BOOL:
 return this->m_BoolValue ? "true" : "false";
 case STRING:
 case STRNEQ:
 return this->m_StringValue;
 case OR:
 return " -- OR -- ";
 default:
 throw RuntimeException("Unexpected internal type:" + this->m_Type);
 }
 }

 bool check(IAnimationVariableSource varSource) {
 return this->checkInternal(varSource);
 }

 bool checkInternal(IAnimationVariableSource iAnimationVariableSource) {
 AnimCondition.Type type = this->m_Type;
 if (type == AnimCondition.Type.OR) {
 return false;
 } else {
 if (this->m_variableHandle.empty()) {
 this->m_variableHandle = AnimationVariableHandle.alloc(this->m_Name);
 }

 IAnimationVariableSlot iAnimationVariableSlot =
 iAnimationVariableSource.getVariable(this->m_variableHandle);
 switch (type) {
 case EQU:
 return iAnimationVariableSlot != nullptr &&
 this->m_FloatValue == iAnimationVariableSlot.getValueFloat();
 case NEQ:
 return iAnimationVariableSlot != nullptr &&
 this->m_FloatValue != iAnimationVariableSlot.getValueFloat();
 case LESS:
 return iAnimationVariableSlot != nullptr &&
 iAnimationVariableSlot.getValueFloat() < this->m_FloatValue;
 case GTR:
 return iAnimationVariableSlot != nullptr &&
 iAnimationVariableSlot.getValueFloat() > this->m_FloatValue;
 case BOOL:
 return (iAnimationVariableSlot != nullptr &&
 iAnimationVariableSlot.getValueBool()) == this->m_BoolValue;
 case STRING:
 return this->m_StringValue.equalsIgnoreCase(
 iAnimationVariableSlot != nullptr
 ? iAnimationVariableSlot.getValueString()
 : "");
 case STRNEQ:
 return !this->m_StringValue.equalsIgnoreCase(
 iAnimationVariableSlot != nullptr
 ? iAnimationVariableSlot.getValueString()
 : "");
 case OR:
 return false;
 default:
 throw RuntimeException("Unexpected internal type:" + this->m_Type);
 }
 }
 }

 static bool pass(IAnimationVariableSource varSource,
 List<AnimCondition> conditions) {
 bool boolean0 = true;

 for (int int0 = 0; int0 < conditions.size(); int0++) {
 AnimCondition animCondition = (AnimCondition)conditions.get(int0);
 if (animCondition.m_Type == AnimCondition.Type.OR) {
 if (boolean0) {
 break;
 }

 boolean0 = true;
 } else {
 boolean0 = boolean0 && animCondition.check(varSource);
 }
 }

 return boolean0;
 }

public
 static enum Type { STRING, STRNEQ, BOOL, EQU, NEQ, LESS, GTR, OR; }
}
} // namespace advancedanimation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
