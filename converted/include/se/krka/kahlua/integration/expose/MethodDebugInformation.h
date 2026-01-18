#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace se {
namespace krka {
namespace kahlua {
namespace integration {
namespace expose {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class MethodDebugInformation {
public:
 const std::string luaName;
 const bool isMethod;
 private List<MethodParameter> parameters;
 const std::string returnType;
 const std::string returnDescription;

 public MethodDebugInformation(const std::string& string0, bool boolean0, List<MethodParameter> list, const std::string& string2, const std::string& string1) {
 this->parameters = list;
 this->luaName = string0;
 this->isMethod = boolean0;
 this->returnDescription = string1;
 if (list.size() > 0 && ((MethodParameter)list.get(0).getType() == ReturnValues.class.getName())) {
 string2 = "...";
 list.remove(0);
 }

 this->returnType = string2;
 }

 std::string getLuaName() {
 return this->luaName;
 }

 std::string getLuaDescription() {
 std::string string0 = this->isMethod ? "obj:" : "";
 std::string string1 = TypeUtil.removePackages(this->returnType) + " " + string0 + this->luaName + "(" + this->getLuaParameterList() + ")\n";
 if (this->getReturnDescription() != nullptr) {
 string1 = string1 + this->getReturnDescription() + "\n";
 }

 return string1;
 }

 bool isMethod() {
 return this->isMethod;
 }

 public List<MethodParameter> getParameters() {
 return this->parameters;
 }

 std::string getReturnDescription() {
 return this->returnDescription;
 }

 std::string getReturnType() {
 return this->returnType;
 }

 std::string toString() {
 return this->getLuaDescription();
 }

 std::string getLuaParameterList() {
 StringBuilder stringBuilder = new StringBuilder();
 bool boolean0 = true;

 for (MethodParameter methodParameter : this->parameters) {
 if (boolean0) {
 boolean0 = false;
 } else {
 stringBuilder.append(", ");
 }

 std::string string = TypeUtil.removePackages(methodParameter.getType());
 stringBuilder.append(string).append(" ").append(methodParameter.getName());
 }

 return stringBuilder.toString();
 }

 std::string getParameterList() {
 StringBuilder stringBuilder = new StringBuilder();
 bool boolean0 = true;

 for (MethodParameter methodParameter : this->parameters) {
 if (boolean0) {
 boolean0 = false;
 } else {
 stringBuilder.append(", ");
 }

 stringBuilder.append(methodParameter.getType()).append(" ").append(methodParameter.getName());
 }

 return stringBuilder.toString();
 }
}
} // namespace expose
} // namespace integration
} // namespace kahlua
} // namespace krka
} // namespace se
