#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "java/text/MessageFormat.h"
#include "javax/xml/bind/ValidationEvent.h"
#include "javax/xml/bind/ValidationEventLocator.h"

namespace javax {
namespace xml {
namespace bind {
namespace helpers {


class ValidationEventImpl {
public:
    int severity;
    std::string message;
    std::exception linkedException;
    ValidationEventLocator locator;

    public ValidationEventImpl(int _severity, const std::string& _message, ValidationEventLocator _locator) {
      this(_severity, _message, _locator, nullptr);
   }

    public ValidationEventImpl(int _severity, const std::string& _message, ValidationEventLocator _locator, std::exception _linkedException) {
      this.setSeverity(_severity);
      this.message = _message;
      this.locator = _locator;
      this.linkedException = _linkedException;
   }

    int getSeverity() {
      return this.severity;
   }

    void setSeverity(int _severity) {
      if (_severity != 0 && _severity != 1 && _severity != 2) {
         throw IllegalArgumentException(Messages.format("ValidationEventImpl.IllegalSeverity"));
      } else {
         this.severity = _severity;
      }
   }

    std::string getMessage() {
      return this.message;
   }

    void setMessage(const std::string& _message) {
      this.message = _message;
   }

    std::exception getLinkedException() {
      return this.linkedException;
   }

    void setLinkedException(std::exception _linkedException) {
      this.linkedException = _linkedException;
   }

    ValidationEventLocator getLocator() {
      return this.locator;
   }

    void setLocator(ValidationEventLocator _locator) {
      this.locator = _locator;
   }

    std::string toString() {
    std::string s;
      switch (this.getSeverity()) {
         case 0:
            s = "WARNING";
            break;
         case 1:
            s = "ERROR";
            break;
         case 2:
            s = "FATAL_ERROR";
            break;
         default:
            s = std::string.valueOf(this.getSeverity());
      }

      return MessageFormat.format("[severity={0},message={1},locator={2}]", s, this.getMessage(), this.getLocator());
   }
}
} // namespace helpers
} // namespace bind
} // namespace xml
} // namespace javax
