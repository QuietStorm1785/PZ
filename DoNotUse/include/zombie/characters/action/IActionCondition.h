#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/w3c/dom/Element.h"
#include "zombie/characters/action/IActionCondition/IFactory.h"

namespace zombie {
namespace characters {
namespace action {


class IActionCondition {
public:
    virtual ~IActionCondition() = default;
   std::unordered_map<std::string, IFactory> s_factoryMap = std::make_unique<std::unordered_map<>>();

    std::string getDescription();

    bool passes(ActionContext var1, int var2);

    IActionCondition clone();

    static IActionCondition createInstance(Element var0) {
    IFactory var1 = s_factoryMap.get(var0.getNodeName());
      return var1 != nullptr ? var1.create(var0) : nullptr;
   }

    static void registerFactory(const std::string& var0, IFactory var1) {
      s_factoryMap.put(var0, var1);
   }
}
} // namespace action
} // namespace characters
} // namespace zombie
