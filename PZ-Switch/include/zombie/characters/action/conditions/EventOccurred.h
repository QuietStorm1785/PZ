#pragma once
#include "org/w3c/dom/Element.h"
#include "zombie/characters/action/ActionContext.h"
#include "zombie/characters/action/IActionCondition.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace characters {
namespace action {
namespace conditions {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class EventOccurred {
public:
 std::string eventName;

 std::string getDescription() {
 return "EventOccurred(" + this->eventName + ")";
 }

 bool load(Element element) {
 this->eventName = element.getTextContent().toLowerCase();
 return true;
 }

 bool passes(ActionContext actionContext, int int0) {
 return actionContext.hasEventOccurred(this->eventName, int0);
 }

 IActionCondition clone() { return nullptr; }

public
 static class Factory implements IActionCondition.IFactory {
 IActionCondition create(Element element) {
 EventOccurred eventOccurred = new EventOccurred();
 return eventOccurred.load(element) ? eventOccurred : nullptr;
 }
 }
}
} // namespace conditions
} // namespace action
} // namespace characters
} // namespace zombie
