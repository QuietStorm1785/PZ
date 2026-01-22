#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "java/net/URL.h"
#include "javax/xml/bind/ValidationEvent.h"
#include "javax/xml/bind/ValidationEventHandler.h"
#include "javax/xml/bind/ValidationEventLocator.h"
#include "org/w3c/dom/Node.h"

namespace javax {
namespace xml {
namespace bind {
namespace helpers {


class DefaultValidationEventHandler {
public:
    bool handleEvent(ValidationEvent event) {
      if (event == nullptr) {
         throw std::make_unique<IllegalArgumentException>();
      } else {
    std::string severity = nullptr;
    bool retVal = false;
         switch (event.getSeverity()) {
            case 0:
               severity = Messages.format("DefaultValidationEventHandler.Warning");
               retVal = true;
               break;
            case 1:
               severity = Messages.format("DefaultValidationEventHandler.Error");
               retVal = false;
               break;
            case 2:
               severity = Messages.format("DefaultValidationEventHandler.FatalError");
               retVal = false;
               break;
            default:
               assert false : Messages.format("DefaultValidationEventHandler.UnrecognizedSeverity", event.getSeverity());
         }

    std::string location = this.getLocation(event);
         System.out.println(Messages.format("DefaultValidationEventHandler.SeverityMessage", severity, event.getMessage(), location));
    return retVal;
      }
   }

    std::string getLocation(ValidationEvent event) {
    std::stringstream msg = new std::stringstream();
    ValidationEventLocator locator = event.getLocator();
      if (locator != nullptr) {
    URL url = locator.getURL();
    void* obj = locator.getObject();
    Node node = locator.getNode();
    int line = locator.getLineNumber();
         if (url != nullptr || line != -1) {
            msg.append("line " + line);
            if (url != nullptr) {
               msg.append(" of " + url);
            }
         } else if (obj != nullptr) {
            msg.append(" obj: " + obj);
         } else if (node != nullptr) {
            msg.append(" node: " + node);
         }
      } else {
         msg.append(Messages.format("DefaultValidationEventHandler.LocationUnavailable"));
      }

      return msg;
   }
}
} // namespace helpers
} // namespace bind
} // namespace xml
} // namespace javax
