#pragma once
#include "org/w3c/dom/Element.h"
#include <cstdint>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace characters {
namespace action {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class IActionCondition {
public:
 virtual ~IActionCondition() = default;
 HashMap<String, IActionCondition.IFactory> s_factoryMap =
 std::make_unique<HashMap<>>();

 std::string getDescription();

 bool passes(ActionContext var1, int var2);

 IActionCondition clone();

 static IActionCondition createInstance(Element element) {
 IActionCondition.IFactory iFactory =
 s_factoryMap.get(element.getNodeName());
 return iFactory != nullptr ? iFactory.create(element) : nullptr;
 }

 static void registerFactory(std::string_view string,
 IActionCondition.IFactory iFactory) {
 s_factoryMap.put(string, iFactory);
 }

public
 interface IFactory { IActionCondition create(Element var1); }
}
} // namespace action
} // namespace characters
} // namespace zombie
