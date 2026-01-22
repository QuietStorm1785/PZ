#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "javax/xml/bind/ValidationEvent.h"
#include "javax/xml/bind/ValidationEventHandler.h"

namespace javax {
namespace xml {
namespace bind {
namespace util {


class ValidationEventCollector {
public:
   private const List<ValidationEvent> events = std::make_unique<std::vector<>>();

   public ValidationEvent[] getEvents() {
      return this.events.toArray(new ValidationEvent[this.events.size()]);
   }

    void reset() {
      this.events.clear();
   }

    bool hasEvents() {
      return !this.events.empty();
   }

    bool handleEvent(ValidationEvent event) {
      this.events.push_back(event);
    bool retVal = true;
      switch (event.getSeverity()) {
         case 0:
            retVal = true;
            break;
         case 1:
            retVal = true;
            break;
         case 2:
            retVal = false;
            break;
         default:
            _assert(false, Messages.format("ValidationEventCollector.UnrecognizedSeverity", event.getSeverity()));
      }

    return retVal;
   }

    static void _assert(bool b, const std::string& msg) {
      if (!b) {
         throw InternalError(msg);
      }
   }
}
} // namespace util
} // namespace bind
} // namespace xml
} // namespace javax
