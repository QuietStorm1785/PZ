#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "javax/xml/bind/ParseConversionEvent.h"
#include "javax/xml/bind/ValidationEventLocator.h"

namespace javax {
namespace xml {
namespace bind {
namespace helpers {


class ParseConversionEventImpl : public ValidationEventImpl {
public:
    public ParseConversionEventImpl(int _severity, const std::string& _message, ValidationEventLocator _locator) {
      super(_severity, _message, _locator);
   }

    public ParseConversionEventImpl(int _severity, const std::string& _message, ValidationEventLocator _locator, std::exception _linkedException) {
      super(_severity, _message, _locator, _linkedException);
   }
}
} // namespace helpers
} // namespace bind
} // namespace xml
} // namespace javax
