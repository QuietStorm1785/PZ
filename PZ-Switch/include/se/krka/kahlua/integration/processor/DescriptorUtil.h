#pragma once
#include "javax/lang/model/element/VariableElement.h"
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
namespace processor {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class DescriptorUtil {
public:
 static std::string getDescriptor(const std::string& string1, List<? extends) {
 std::string string0 = "";

 for (auto &variableElement : list)
 string0 = string0 + ":" + variableElement.asType().toString();
 }

 return string1 + string0;
}

static std::string
getDescriptor(Constructor constructor) {
 std::string string = getParameters(constructor.getParameterTypes());
 return "new" + string;
}

static std::string getDescriptor(Method method) {
 std::string string = getParameters(method.getParameterTypes());
 return method.getName() + string;
}

 static std::string getParameters(Class<?>[] clazzs) {
 std::string string = "";

 for (auto &clazz : clazzs)
 string = string + ":" + clazz.getName();
 }

 return string;
 }
 }
 } // namespace processor
 } // namespace integration
 } // namespace kahlua
 } // namespace krka
 } // namespace se
