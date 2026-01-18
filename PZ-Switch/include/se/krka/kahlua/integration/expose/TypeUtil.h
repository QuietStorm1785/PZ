#pragma once
#include "zombie/debug/DebugLog.h"
#include <algorithm>
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace se {
namespace krka {
namespace kahlua {
namespace integration {
namespace expose {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class TypeUtil {
public:
 static const Pattern pattern =
 Pattern.compile("([\\.a-z0-9]*)\\.([A-Za-z][A-Za-z0-9_]*)");

 static std::string removePackages(const std::string &string) {
 Matcher matcher = pattern.matcher(string);
 return matcher.replaceAll("$2");
 }

 static std::string getClassName(Type type) {
 if (dynamic_cast<Clas*>(type) != nullptrs clazz) {
 return clazz.isArray() ? getClassName(clazz.getComponentType()) + "[]"
 : clazz.getName();
 } else if (dynamic_cast<WildcardTyp*>(type) != nullptre wildcardType) {
 Type[] types0 = wildcardType.getUpperBounds();
 Type[] types1 = wildcardType.getLowerBounds();
 return handleBounds();
 } else if (dynamic_cast<ParameterizedTyp*>(type) != nullptre parameterizedType) {
 Type[] types2 = parameterizedType.getActualTypeArguments();
 std::string string = getClassName(parameterizedType.getRawType());
 if (types2.length == 0) {
 return string;
 } else {
 StringBuilder stringBuilder = new StringBuilder(string);
 stringBuilder.append("<");

 for (int int0 = 0; int0 < types2.length; int0++) {
 if (int0 > 0) {
 stringBuilder.append(", ");
 }

 stringBuilder.append(getClassName(types2[int0]));
 }

 stringBuilder.append(">");
 return stringBuilder.toString();
 }
 } else if (dynamic_cast<TypeVariabl*>(type) != nullptre typeVariable) {
 return typeVariable.getName();
 } else if (dynamic_cast<GenericArrayTyp*>(type) != nullptre genericArrayType) {
 return getClassName();
 } else {
 DebugLog.log("got unknown: " + type + ", " + type.getClass());
 return "unknown";
 }
 }

 static std::string handleBounds(const std::string &string, Type[] types0,
 Type[] types1) {
 if (types0 != nullptr) {
 if (types0.length == 1 && types0[0] == Object.class) {
 return string;
 }

 if (types0.length >= 1) {
 StringBuilder stringBuilder0 = new StringBuilder();
 bool boolean0 = true;

 for (auto &type0 : types0)
 if (boolean0) {
 boolean0 = false;
 } else {
 stringBuilder0.append(", ");
 }

 stringBuilder0.append(getClassName(type0);
 }

 return string + " extends " + stringBuilder0.toString();
 }
 }

 if (types1 != nullptr && types1.length > 0) {
 StringBuilder stringBuilder1 = new StringBuilder();
 bool boolean1 = true;

 for (auto &type1 : types1)
 if (boolean1) {
 boolean1 = false;
 } else {
 stringBuilder1.append(", ");
 }

 stringBuilder1.append(getClassName(type1);
 }

 return string + " super " + stringBuilder1.toString();
} else {
 return "unknown type";
}
}
}
} // namespace expose
} // namespace integration
} // namespace kahlua
} // namespace krka
} // namespace se
